#include <pro.h>
#include <err.h>
#include "rpc_engine.h"

#ifndef RECV_TIMEOUT_PERIOD
#  define RECV_TIMEOUT_PERIOD 10000
#endif

using namespace std;

void dmsg(void *ud, const char *format, va_list va)
{
  dvmsg(0, ud, format, va);
}

void derror(void *ud, const char *format, va_list va)
{
  dvmsg(-1, ud, format, va);
}

void dwarning(void *ud, const char *format, va_list va)
{
  dvmsg(1, ud, format, va);
}

rpc_engine_t::~rpc_engine_t()
{
}

//--------------------------------------------------------------------------
void rpc_engine_t::term_irs()
{
  if (irs == NULL)
    return;
  term_server_irs(irs);
  irs = NULL;
}

//--------------------------------------------------------------------------
rpc_engine_t::rpc_engine_t(SOCKET rpc_socket)
{
  this->rpc_socket = rpc_socket;
  irs = (idarpc_stream_t *)this->rpc_socket;
  poll_debug_events = has_pending_event = false;
  network_error_code = 0;
  verbose = false;
  poll_required = true;
}

//--------------------------------------------------------------------------
// returns error code
int rpc_engine_t::send_request(qstring &s)
{
  // if nothing is initialized yet or error occurred, silently fail
  if ( irs == NULL || network_error_code != 0 )
    return -1;

  finalize_packet(s);
  const char *ptr = s.c_str();
  ssize_t left = s.length();
#ifdef DEBUG_NETWORK
  rpc_packet_t *rp = (rpc_packet_t *)ptr;
  int len = qntohl(rp->length);
  show_hex(rp+1, len, "SEND %s %d bytes:\n", get_rpc_name(rp->code), len);
  //  msg("SEND %s\n", get_rpc_name(rp->code));
#endif
  while ( left > 0 )
  {
    ssize_t code = irs_send(irs, ptr, left);
    if ( code == -1 )
    {
      code = irs_error(irs);
      network_error_code = code;
      warning("irs_send: %s", winerr((int)code));
      return (int)code;
    }
    left -= code;
    ptr += code;
  }
  return 0;
}

//--------------------------------------------------------------------------
// receives a buffer from the network
// this may block if polling is required, then virtual poll_event is called
int rpc_engine_t::recv_all(void *ptr, int left, int flags, bool poll)
{
  ssize_t code;
  while ( true )
  {
    code = 0;
    if ( left <= 0 )
      break;

    // the server needs to wait and poll till events are ready
    if ( poll_required )
    {
      if ( poll && irs_ready(irs, TIMEOUT) == 0 )
      {
        code = poll_events((flags & PRF_POLL) != 0);
        if ( code != 0 )
          break;
        if ( (flags & PRF_DONT_BLOCK) == 0 )
          continue;
      }
    }
    if ( (flags & PRF_DONT_BLOCK) != 0 && irs_ready(irs, TIMEOUT) == 0 )
      return -1;
    code = irs_recv(irs, ptr, left, poll_required ? 0 : RECV_TIMEOUT_PERIOD);
    if ( code <= 0 )
    {
      code = irs_error(irs);
      if ( code == 0 )
      {
        code = -1; // anything but not success
      }
      else
      {
        network_error_code = code;
        dmsg("irs_recv: %s", winerr(uint32(code)));
      }
      break;
    }
    left -= (uint32)code;
    // visual studio 64 does not like simple
    // (char*)ptr += code;
    char *p2 = (char *)ptr;
    p2 += code;
    ptr = p2;
  }
  return code;
}

//-------------------------------------------------------------------------
rpc_packet_t *rpc_engine_t::recv_request(int flags)
{
  // if nothing is initialized yet or error occurred, silently fail
  if ( irs == NULL || network_error_code != 0 )
    return NULL;

  rpc_packet_t p;
  int code = recv_all(&p, sizeof(rpc_packet_t), flags, poll_debug_events);
  if ( code != 0 )
    return NULL;

  int size = p.length = qntohl(p.length);
  if ( size < 0 )
  {
    dwarning("rpc: bad packet length");
    return NULL;
  }

  size += sizeof(rpc_packet_t);
  uchar *urp = (uchar *)qalloc(size);
  if ( urp == NULL )
  {
    dwarning("rpc: no local memory");
    return NULL;
  }

  memcpy(urp, &p, sizeof(rpc_packet_t));
  int left = size - sizeof(rpc_packet_t);
  uchar *ptr = urp + sizeof(rpc_packet_t);

  code = recv_all(ptr, left, flags, false);
  if ( code != 0 )
  {
    qfree(urp);
    return NULL;
  }

  rpc_packet_t *rp = (rpc_packet_t *)urp;
#ifdef DEBUG_NETWORK
  int len = rp->length;
  show_hex(rp+1, len, "RECV %s %d bytes:\n", get_rpc_name(rp->code), len);
  //  msg("RECV %s\n", get_rpc_name(rp->code));
#endif
  return rp;
}

//--------------------------------------------------------------------------
// sends a request and waits for a reply
// may occasionally sends another request based on the reply
rpc_packet_t *rpc_engine_t::process_request(qstring &cmd, int flags)
{
  bool only_events = cmd.empty();
  while (true)
  {
    if ( !cmd.empty() )
    {
      int code = send_request(cmd);
      if ( code != 0 )
        return NULL;

      rpc_packet_t *rp = (rpc_packet_t *)cmd.c_str();
      if ( only_events && rp->code == RPC_EVOK )
        return NULL;

      if ( rp->code == RPC_ERROR )
        qexit(1);
    }

    rpc_packet_t *rp = recv_request(flags);
    if ( rp == NULL )
      return NULL;

    switch ( rp->code )
    {
    case RPC_UNK:
      dwarning("rpc: remote did not understand our request");
      goto FAILED;
    case RPC_MEM:
      dwarning("rpc: no remote memory");
      goto FAILED;
    case RPC_OK:
      return rp;
    }

    if ( (flags & PRF_LOGIN) != 0 )
    {
      lprintf("Exploit packet has been detected\n");
FAILED:
      qfree(rp);
      return NULL;
    }
    cmd = perform_request(rp);
    qfree(rp);
  }
}

//--------------------------------------------------------------------------
// processes a request and returns a int32
int rpc_engine_t::process_long(qstring &cmd)
{
  rpc_packet_t *rp = process_request(cmd);
  if ( rp == NULL )
    return -1;

  const uchar *answer = (uchar *)(rp+1);
  const uchar *end = answer + rp->length;

  int result = extract_long(&answer, end);
  qfree(rp);
  return result;
}

//--------------------------------------------------------------------------
int rpc_engine_t::send_ioctl(int fn, const void *buf, size_t size, void **poutbuf, ssize_t *poutsize)
{
  qstring cmd = prepare_rpc_packet(RPC_IOCTL);

  append_long(cmd, fn);
  append_long(cmd, (uint32)size);
  append_memory(cmd, buf, size);

  rpc_packet_t *rp = process_request(cmd);
  if ( rp == NULL )
    return -1;

  const uchar *answer = (uchar *)(rp+1);
  const uchar *end = answer + rp->length;

  int code = extract_long(&answer, end);
  ssize_t outsize = extract_long(&answer, end);

  if ( outsize > 0 && poutbuf != NULL )
  {
    *poutbuf = qalloc(outsize);
    if ( *poutbuf != NULL )
      extract_memory(&answer, end, *poutbuf, outsize);
  }
  if ( poutsize != NULL )
    *poutsize = outsize;
  qfree(rp);
  return code;
}

//--------------------------------------------------------------------------
// process an ioctl request and return the reply packet
int rpc_engine_t::handle_ioctl_packet(qstring &cmd, const uchar *ptr, const uchar *end)
{
  if ( ioctl_handler == NULL )
    return RPC_UNK;

  char *buf = NULL;
  int fn = extract_long(&ptr, end);
  size_t size = extract_long(&ptr, end);
  if ( size > 0 )
  {
    buf = new char[size];
    if ( buf == NULL )
      return RPC_MEM;
  }
  extract_memory(&ptr, end, buf, size);
  void *outbuf = NULL;
  ssize_t outsize = 0;
  int code = ioctl_handler(this, fn, buf, size, &outbuf, &outsize);
  append_long(cmd, code);
  append_long(cmd, (uint32)outsize);
  if ( outsize > 0 )
    append_memory(cmd, outbuf, outsize);
  qfree(outbuf);
  verb(("ioctl(%d) => %d\n", fn, code));
  return RPC_OK;
}
