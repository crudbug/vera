#include "rpc_debmod.h"

//--------------------------------------------------------------------------
rpc_debmod_t::rpc_debmod_t() : rpc_client_t(0)
{
  const register_info_t *regs = debugger.registers;
  nregs = debugger.registers_size;
  for ( int i=0; i < nregs; i++, regs++ )
  {
    if ( (regs->flags & REGISTER_SP) != 0 )
      sp_idx = i;
    if ( (regs->flags & REGISTER_IP) != 0 )
      pc_idx = i;
  }
  bpt_code.append(debugger.bpt_bytes, debugger.bpt_size);

  dmsg_ud = (void *)this;
}

//--------------------------------------------------------------------------
int idaapi rpc_debmod_t::handle_ioctl(
  int fn,
  const void *buf,
  size_t size,
  void **poutbuf,
  ssize_t *poutsize)
{
  return rpc_engine_t::send_ioctl(fn, buf, size, poutbuf, poutsize);
}

//--------------------------------------------------------------------------
bool rpc_debmod_t::open_remote(const char *hostname, int port_number, const char *password)
{
  rpc_packet_t *rp = NULL;
  irs = init_client_irs(hostname, port_number);
  if (irs == NULL)
  {
failed:
    connection_failed(rp);
    return false;
  }

  rp = recv_request(PRF_DONT_POLL);
  if ( rp == NULL )
    goto failed;

  if ( rp->code != RPC_OPEN )  // is this an ida debugger server?
  {
    connection_failed(rp);
    rpc_client_t::dwarning("ICON ERROR\nAUTOHIDE NONE\n"
      "Bogus remote server");
    return false;
  }

  const uchar *answer = (uchar *)(rp+1);
  const uchar *end = answer + rp->length;
  int version = extract_long(&answer, end);
  int remote_debugger_id = extract_long(&answer, end);
  int easize = extract_long(&answer, end);
  qstring errstr;
  if ( version != IDD_INTERFACE_VERSION )
    errstr.sprnt("protocol version is %d, expected %d", version, IDD_INTERFACE_VERSION);
  else if ( remote_debugger_id != debugger.id )
    errstr.sprnt("debugger id is %d, expected %d (%s)", remote_debugger_id, debugger.id, debugger.name);
  else if ( easize != (inf.is_64bit() ? 8 : 4) )
    errstr.sprnt("address size is %d bytes, expected %d", easize, inf.is_64bit() ? 8 : 4);
  if ( !errstr.empty() )
  {
    connection_failed(rp);
    qstring cmd = prepare_rpc_packet(RPC_OK);
    append_long(cmd, false);
    send_request(cmd);
    warning("ICON ERROR\nAUTOHIDE NONE\n"
      "Incompatible debugging server:\n"
      "%s\n", errstr.c_str());
    return false;
  }
  qfree(rp);

  qstring cmd = prepare_rpc_packet(RPC_OK);
  append_long(cmd, true);
  append_str(cmd, password);
  send_request(cmd);

  rp = recv_request(PRF_DONT_POLL);
  if ( rp == NULL || rp->code != RPC_OK )
    goto failed;

  answer = (uchar *)(rp+1);
  end = answer + rp->length;
  bool password_ok = extract_long(&answer, end);
  if ( !password_ok )  // is this an ida debugger server?
  {
    connection_failed(rp);
    warning("ICON ERROR\nAUTOHIDE NONE\n"
      "Bad password");
    return false;
  }

  qfree(rp);
  return true;
}

//--------------------------------------------------------------------------
int rpc_debmod_t::bpt(uchar code, bpttype_t type, ea_t ea, int len)
{
  qstring cmd = prepare_rpc_packet(code);
  append_long(cmd, type);
  append_ea(cmd, ea);
  append_long(cmd, len);

  return process_long(cmd);
}

//--------------------------------------------------------------------------
int rpc_debmod_t::dbg_add_bpt(bpttype_t type, ea_t ea, int len)
{
  return bpt(RPC_ADD_BPT, type, ea, len);
}

//--------------------------------------------------------------------------
int rpc_debmod_t::dbg_del_bpt(ea_t ea, const uchar *orig_bytes, int len)
{
  qstring cmd = prepare_rpc_packet(RPC_DEL_BPT);
  append_ea(cmd, ea);
  append_long(cmd, len);
  append_memory(cmd, orig_bytes, len);

  return process_long(cmd);
}

//--------------------------------------------------------------------------
int rpc_debmod_t::dbg_thread_get_sreg_base(thid_t tid, int sreg_value, ea_t *ea)
{
  qstring cmd = prepare_rpc_packet(RPC_GET_SREG_BASE);
  append_long(cmd, tid);
  append_long(cmd, sreg_value);

  rpc_packet_t *rp = process_request(cmd);
  if ( rp == NULL )
    return -1;

  const uchar *answer = (uchar *)(rp+1);
  const uchar *end = answer + rp->length;

  bool result = extract_long(&answer, end);

  if ( result )
    *ea = extract_ea(&answer, end);

  qfree(rp);
  return result;
}

//--------------------------------------------------------------------------
void rpc_debmod_t::dbg_set_exception_info(const exception_info_t *table, int qty)
{
  qstring cmd = prepare_rpc_packet(RPC_SET_EXCEPTION_INFO);
  append_long(cmd, qty);
  append_exception_info(cmd, table, qty);

  qfree(process_request(cmd));
}

//--------------------------------------------------------------------------
int rpc_debmod_t::dbg_open_file(const char *file, uint32 *fsize, bool readonly)
{
  qstring cmd = prepare_rpc_packet(RPC_OPEN_FILE);
  append_str(cmd, file);
  append_long(cmd, readonly);

  rpc_packet_t *rp = process_request(cmd);
  if ( rp == NULL )
    return -1;

  const uchar *answer = (uchar *)(rp+1);
  const uchar *end = answer + rp->length;

  int fn = extract_long(&answer, end);
  if ( fn != -1 )
  {
    if ( fsize != NULL && readonly )
      *fsize = extract_long(&answer, end);
  }
  else
  {
    qerrcode(extract_long(&answer, end));
  }
  qfree(rp);
  return fn;
}

//--------------------------------------------------------------------------
void rpc_debmod_t::dbg_close_file(int fn)
{
  qstring cmd = prepare_rpc_packet(RPC_CLOSE_FILE);
  append_long(cmd, fn);

  qfree(process_request(cmd));
}

//--------------------------------------------------------------------------
ssize_t idaapi rpc_debmod_t::dbg_read_file(int fn, uint32 off, void *buf, size_t size)
{
  qstring cmd = prepare_rpc_packet(RPC_READ_FILE);
  append_long(cmd, fn);
  append_long(cmd, off);
  append_long(cmd, (uint32)size);

  rpc_packet_t *rp = process_request(cmd);
  if ( rp == NULL )
    return -1;

  const uchar *answer = (uchar *)(rp+1);
  const uchar *end = answer + rp->length;

  int32 rsize = extract_long(&answer, end);
  if ( size != rsize )
    qerrcode(extract_long(&answer, end));

  if ( rsize > 0 )
  {
    if ( rsize > size )
      error("rpc_read_file: protocol error");
    extract_memory(&answer, end, buf, rsize);
  }
  qfree(rp);
  return rsize;
}

//--------------------------------------------------------------------------
ssize_t idaapi rpc_debmod_t::dbg_write_file(int fn, uint32 off, const void *buf, size_t size)
{
  qstring cmd = prepare_rpc_packet(RPC_WRITE_FILE);
  append_long(cmd, fn);
  append_long(cmd, off);
  append_long(cmd, (uint32)size);
  append_memory(cmd, buf, size);

  rpc_packet_t *rp = process_request(cmd);
  if ( rp == NULL )
    return -1;

  const uchar *answer = (uchar *)(rp+1);
  const uchar *end = answer + rp->length;

  int32 rsize = extract_long(&answer, end);
  if ( size != rsize )
    qerrcode(extract_long(&answer, end));

  qfree(rp);
  return rsize;
}

//--------------------------------------------------------------------------
int idaapi rpc_debmod_t::dbg_is_ok_bpt(bpttype_t type, ea_t ea, int len)
{
  return bpt(RPC_ISOK_BPT, type, ea, len);
}

//--------------------------------------------------------------------------
int rpc_debmod_t::getint2(uchar code, int x)
{
  qstring cmd = prepare_rpc_packet(code);
  append_long(cmd, x);

  return process_long(cmd);
}

//--------------------------------------------------------------------------
int rpc_debmod_t::dbg_init(bool _debug_debugger)
{
  has_pending_event = false;
  poll_debug_events = false;
  return getint2(RPC_INIT, _debug_debugger);
}

//--------------------------------------------------------------------------
void rpc_debmod_t::dbg_term(void)
{
  qstring cmd = prepare_rpc_packet(RPC_TERM);

  qfree(process_request(cmd));
}

//--------------------------------------------------------------------------
// input is valid only if n==0
int rpc_debmod_t::dbg_process_get_info(int n, const char *input, process_info_t *info)
{
  qstring cmd = prepare_rpc_packet(RPC_GET_PROCESS_INFO);
  append_long(cmd, n);
  if ( n == 0 )
    append_str(cmd, input);

  rpc_packet_t *rp = process_request(cmd);
  if ( rp == NULL ) return -1;
  const uchar *answer = (uchar *)(rp+1);
  const uchar *end = answer + rp->length;

  bool result = extract_long(&answer, end);
  if ( result )
    extract_process_info(&answer, end, info);
  qfree(rp);
  return result;
}

//--------------------------------------------------------------------------
int rpc_debmod_t::dbg_detach_process(void)
{
  return getint(RPC_DETACH_PROCESS);
}

//--------------------------------------------------------------------------
int rpc_debmod_t::dbg_start_process(
  const char *path,
  const char *args,
  const char *startdir,
  int flags,
  const char *input_path,
  uint32 input_file_crc32)
{
  qstring cmd = prepare_rpc_packet(RPC_START_PROCESS);
  append_str(cmd, path);
  append_str(cmd, args);
  append_str(cmd, startdir);
  append_long(cmd, flags);
  append_str(cmd, input_path);
  append_long(cmd, input_file_crc32);

  return process_long(cmd);
}

//--------------------------------------------------------------------------
int rpc_debmod_t::dbg_get_debug_event(debug_event_t *event, bool ida_is_idle)
{
  if ( has_pending_event )
  {
    verbev(("get_debug_event => has pending event, returning it\n"));
    *event = pending_event;
    has_pending_event = false;
    poll_debug_events = false;
    return 1;
  }

  int result = false;
  if ( poll_debug_events )
  {
    // do we have something waiting?
    // we must use TIMEOUT here to avoid competition between
    // IDA analyzer and the debugger program.
    // The analysis will be slow during the application run.
    // As soon as the program is suspended, the analysis will be fast
    // because get_debug_event() will not be called.
    if ( irs_ready(irs, TIMEOUT) != 0 )
    {
      verbev(("get_debug_event => remote has an event for us\n"));
      // get the packet - it should be RPC_EVENT (nothing else can be)
      qstring empty;
      rpc_packet_t *rp = process_request(empty, ida_is_idle ? PRF_POLL : PRF_DONT_POLL);
      verbev(("get_debug_event => processed remote event, has=%d\n", has_pending_event));
      if ( rp != NULL || !has_pending_event )
      {
        warning("rpc: event protocol error (rp=%p has_event=%d)", rp, has_pending_event);
        return -1;
      }
    }
  }
  else
  {
    verbev(("get_debug_event => first time, send GET_DEBUG_EVENT\n"));
    qstring cmd = prepare_rpc_packet(RPC_GET_DEBUG_EVENT);
    append_long(cmd, ida_is_idle);

    rpc_packet_t *rp = process_request(cmd);
    if ( rp == NULL )
      return -1;
    const uchar *answer = (uchar *)(rp+1);
    const uchar *end = answer + rp->length;

    result = extract_long(&answer, end);
    if ( result == 1 )
      extract_debug_event(&answer, end, event);
    else
      poll_debug_events = true;
    verbev(("get_debug_event => remote said %d, poll=%d now\n", result, poll_debug_events));
    qfree(rp);
  }
  return result;
}

//--------------------------------------------------------------------------
int rpc_debmod_t::dbg_attach_process(pid_t pid, int event_id)
{
  qstring cmd = prepare_rpc_packet(RPC_ATTACH_PROCESS);
  append_long(cmd, pid);
  append_long(cmd, event_id);

  return process_long(cmd);
}

//--------------------------------------------------------------------------
int rpc_debmod_t::dbg_prepare_to_pause_process(void)
{
  return getint(RPC_PREPARE_TO_PAUSE_PROCESS);
}

//--------------------------------------------------------------------------
int rpc_debmod_t::dbg_exit_process(void)
{
  return getint(RPC_EXIT_PROCESS);
}

//--------------------------------------------------------------------------
int rpc_debmod_t::dbg_continue_after_event(const debug_event_t *event)
{
  qstring cmd = prepare_rpc_packet(RPC_CONTINUE_AFTER_EVENT);
  append_debug_event(cmd, event);

  return process_long(cmd);
}

//--------------------------------------------------------------------------
void rpc_debmod_t::dbg_stopped_at_debug_event(void)
{
  qstring cmd = prepare_rpc_packet(RPC_STOPPED_AT_DEBUG_EVENT);

  qfree(process_request(cmd));
}

//--------------------------------------------------------------------------
int rpc_debmod_t::dbg_thread_suspend(thid_t tid)
{
  return getint2(RPC_TH_SUSPEND, tid);
}

//--------------------------------------------------------------------------
int rpc_debmod_t::dbg_thread_continue(thid_t tid)
{
  return getint2(RPC_TH_CONTINUE, tid);
}

//--------------------------------------------------------------------------
int rpc_debmod_t::dbg_thread_set_step(thid_t tid)
{
  return getint2(RPC_TH_SET_STEP, tid);
}

//--------------------------------------------------------------------------
int rpc_debmod_t::dbg_thread_read_registers(thid_t tid, regval_t *values, int n)
{
  qstring cmd = prepare_rpc_packet(RPC_READ_REGS);
  append_long(cmd, tid);
  append_long(cmd, n);

  rpc_packet_t *rp = process_request(cmd);
  if ( rp == NULL )
    return -1;
  const uchar *answer = (uchar *)(rp+1);
  const uchar *end = answer + rp->length;

  int result = extract_long(&answer, end);
  extract_regvals(&answer, end, values, n);
  qfree(rp);
  return result;
}

//--------------------------------------------------------------------------
int rpc_debmod_t::dbg_thread_write_register(thid_t tid, int reg_idx, const regval_t *value)
{
  qstring cmd = prepare_rpc_packet(RPC_WRITE_REG);
  append_long(cmd, tid);
  append_long(cmd, reg_idx);
  append_regvals(cmd, value, 1);

  return process_long(cmd);
}

//--------------------------------------------------------------------------
int idaapi rpc_debmod_t::dbg_get_memory_info(meminfo_vec_t &areas)
{
  qstring cmd = prepare_rpc_packet(RPC_GET_MEMORY_INFO);

  rpc_packet_t *rp = process_request(cmd);
  if ( rp == NULL )
    return -1;

  const uchar *answer = (uchar *)(rp+1);
  const uchar *end = answer + rp->length;

  int result = extract_long(&answer, end);
  if ( result > 0 )
  {
    int n = extract_long(&answer, end);
    areas.resize(n);
    for ( int i=0; i < n; i++ )
      extract_memory_info(&answer, end, &areas[i]);
  }
  qfree(rp);
  return result;
}

//--------------------------------------------------------------------------
ssize_t rpc_debmod_t::dbg_read_memory(ea_t ea, void *buffer, size_t size)
{
  qstring cmd = prepare_rpc_packet(RPC_READ_MEMORY);
  append_ea(cmd, ea);
  append_long(cmd, (uint32)size);

  rpc_packet_t *rp = process_request(cmd);
  if ( rp == NULL )
    return -1;

  const uchar *answer = (uchar *)(rp+1);
  const uchar *end = answer + rp->length;

  int result = extract_long(&answer, end);
  extract_memory(&answer, end, buffer, size);
  qfree(rp);
  return result;
}

//--------------------------------------------------------------------------
ssize_t rpc_debmod_t::dbg_write_memory(ea_t ea, const void *buffer, size_t size)
{
  qstring cmd = prepare_rpc_packet(RPC_WRITE_MEMORY);
  append_ea(cmd, ea);
  append_long(cmd, (uint32)size);
  append_memory(cmd, buffer, size);

  return process_long(cmd);
}

//--------------------------------------------------------------------------
bool rpc_debmod_t::dbg_update_call_stack(thid_t tid, call_stack_t *trace)
{
  qstring cmd = prepare_rpc_packet(RPC_UPDATE_CALL_STACK);
  append_long(cmd, tid);

  rpc_packet_t *rp = process_request(cmd);
  if ( rp == NULL )
    return false;

  const uchar *answer = (uchar *)(rp+1);
  const uchar *end = answer + rp->length;

  bool result = extract_long(&answer, end);
  if ( result )
    extract_call_stack(&answer, end, trace);
  qfree(rp);
  return result;
}

//--------------------------------------------------------------------------
ea_t rpc_debmod_t::dbg_appcall(
  ea_t func_ea,
  thid_t tid,
  const struct func_type_info_t *fti,
  int nargs,
  const struct regobjs_t *regargs,
  struct relobj_t *stkargs,
  struct regobjs_t *retregs,
  qstring *errbuf,
  debug_event_t *event,
  int flags)
{
  qstring cmd = prepare_rpc_packet(RPC_APPCALL);
  append_ea(cmd, func_ea);
  append_long(cmd, tid);
  append_long(cmd, nargs);
  append_long(cmd, flags);
  append_appcall(cmd, *fti, *regargs, *stkargs, *retregs);

  rpc_packet_t *rp = process_request(cmd);
  if ( rp == NULL )
    return -1;

  const uchar *answer = (uchar *)(rp+1);
  const uchar *end = answer + rp->length;

  ea_t sp = extract_ea(&answer, end);
  if ( sp == BADADDR )
  {
    if ( (flags & APPCALL_DEBEV) != 0 )
      extract_debug_event(&answer, end, event);
    if ( errbuf != NULL )
      *errbuf = extract_str(&answer, end);
  }
  else
  {
    if ( retregs != NULL )
      extract_regobjs(&answer, end, retregs, true);
  }
  qfree(rp);
  return sp;
}

//--------------------------------------------------------------------------
int rpc_debmod_t::dbg_cleanup_appcall(thid_t tid)
{
  qstring cmd = prepare_rpc_packet(RPC_CLEANUP_APPCALL);
  append_long(cmd, tid);
  return process_long(cmd);
}

//--------------------------------------------------------------------------
bool rpc_debmod_t::close_remote()
{
  qstring cmd = prepare_rpc_packet(RPC_OK);
  send_request(cmd);
  term_client_irs(irs);
  irs = NULL;
  network_error_code = 0;
  return true;
}

//--------------------------------------------------------------------------
void rpc_debmod_t::neterr(const char *module)
{
  int code = irs_error(irs);
  error("%s: %s", module, winerr(code));
}

//--------------------------------------------------------------------------
int rpc_debmod_t::get_system_specific_errno(void) const
{
  return irs_error(irs);
}

//--------------------------------------------------------------------------
void rpc_debmod_t::connection_failed(rpc_packet_t *rp)
{
  if (rp != NULL)
    qfree(rp);
  term_irs();
}

