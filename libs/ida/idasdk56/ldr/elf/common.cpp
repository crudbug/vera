/*
 *      Interactive disassembler (IDA)
 *      Copyright (c) 1990-98 by Ilfak Guilfanov.
 *                        E-mail: ig@datarescue.com
 *      ELF-bynary loader.
 *      Copyright (c) 1995-2006 by Iouri Kharon.
 *                        E-mail: yjh@styx.cabel.net
 *
 *      ALL RIGHTS RESERVED.
 *
 */

bool unpatched;
bool elf64;
Elf64_Ehdr ehdr;

static bool mf;
static linput_t *li;
static char name[MAXSTR];
static size_t dynstr_off, dynstr_size;
static size_t dynsym_off, dynsym_size;
static size_t dynrel_off, dynrel_size;
static size_t dynrela_off, dynrela_size;

#ifndef _LOADER_HPP
#define loader_failure() qexit(1)
#endif

#ifndef NO_ERRSTRUCT
//--------------------------------------------------------------------------
#ifndef EFD_COMPILE
static void ask_for_exit(const char *str)
{
  if ( askyn_c(1, "HIDECANCEL\n%s. Continue?", str) <= 0 )
    loader_failure();
}
#endif // BUILD_EFD

//--------------------------------------------------------------------------
static void _errstruct(int line)
{
  static bool asked = false;
  if ( !asked )
  {
    if ( askyn_c(1, "HIDECANCEL\n"
                    "Bad file structure or read error (line %d). Continue?", line)
                <= 0 ) loader_failure();
    asked = true;
  }
}

#define errstruct() _errstruct(__LINE__)
#endif

//--------------------------------------------------------------------------
inline void errnomem(void) { nomem("ELF"); }

//--------------------------------------------------------------------------
// read 64 or 32 bit number depending on the ELF type
static bool read_uword(uint64 *p, bool sign=false)
{
  if ( elf64 )
  {
#if defined(__EA64__) || !defined(BUILD_LOADER)
    return lread8bytes(li, p, mf) == 0;
#else
    loader_failure("Please use IDA Pro 64-bit to load 64-bit files");
#ifdef __BORLANDC__
    return false;
#endif
#endif
  }
  else
  {
    uint32 x;
    if ( lread4bytes(li, &x, mf) != 0 )
      return false;
    *p = sign ? int32(x) : x;
    return true;
  }
}

inline bool read_sword(int64 *p) { return read_uword((uint64 *)p, true); }
inline bool read_uval(uval_t *p)
{
  uint64 x;
  if ( !read_uword(&x, true) )
    return false;
  *p = (uval_t)x;
  return true;
}

//--------------------------------------------------------------------------
// FILE-MEMORY mapping
struct mapping_t
{
  uint32 offset;
  uint32 size;
  uint64 ea;
};

static mapping_t *fmap = NULL;
static int nmap = 0;

static void add_mapping(size_t offset, size_t size, uint64 ea)
{
  fmap = (mapping_t *)qrealloc(fmap, (nmap+1)*sizeof(mapping_t));
  if ( fmap == NULL ) errnomem();
  fmap[nmap].offset = (uint32)offset;
  fmap[nmap].size   = (uint32)size;
  fmap[nmap].ea     = ea;
  nmap++;
}

#if !defined(EFD_COMPILE) && !defined(BUILD_LOADER)
static void clear_mappings(void)
{
  qfree(fmap);
  fmap = NULL;
  nmap = 0;
}
#endif // BUILD_EFD || LOADER

static uint32 map_ea(uint64 ea)
{
  for ( int i=0; i < nmap; i++ )
  {
    if ( fmap[i].ea <= ea && fmap[i].ea+fmap[i].size > ea )
      return low(ea - fmap[i].ea) + fmap[i].offset;
  }
  char buf[64];
  warning("Could not map address 0x%s", print(ea, buf, sizeof(buf), 16));
  return low(ea);
}

//--------------------------------------------------------------------------
typedef qvector<Elf64_Dyn> dyninfo_t;

static void read_dyninfo(size_t offset, size_t size, dyninfo_t *dyninfo)
{
  if ( size == 0 )
    return;

  qlseek(li, offset);
  const int entsize = elf64 ? sizeof(Elf64_Dyn) : sizeof(Elf32_Dyn);
  for ( int i=0; i < size; i+=entsize )
  {
    Elf64_Dyn d;
    if ( elf64 )
    {
      if ( qlread(li, &d, sizeof(d)) != sizeof(d) )
        errstruct();
      if ( mf )
      {
        d.d_tag = swap64(d.d_tag);
        d.d_un  = swap64(d.d_un);
      }
    }
    else
    {
      Elf32_Dyn d32;
      if ( qlread(li, &d32, sizeof(d32)) != sizeof(d32) )
        errstruct();
      if ( mf )
      {
        d.d_tag = swap32(d32.d_tag);
        d.d_un  = swap32(d32.d_un.d_val);
      }
      else
      {
        d.d_tag = d32.d_tag;
        d.d_un  = d32.d_un.d_val;
      }
    }
    dyninfo->push_back(d);
    if ( d.d_tag == DT_NULL )
      break;
  }
}

//--------------------------------------------------------------------------
//      Functions common for EFD & DEBUGGER
//--------------------------------------------------------------------------

static Elf32_Shdr   *shdr32;
static Elf64_Shdr   *shdr64;
static uint32        symcnt;

static ushort got_sec, plt_sec, str_sec, sym_sec, dst_sec, dsm_sec, int_sec,
              gpt_sec;

static size_t dyn_offset, dyn_size;
static int dyn_link;

static sym_rel *stb, *dstb;

static uint32  borext_offset, borext_size; // for Kylix (currently - efd only)

//--------------------------------------------------------------------------
// common.cpp is included from debugger/symelf.cpp and can be reused
// for different files. we have to reinitialize static variables
// each time.
static void init_elf_vars(void)
{
  mf        = false;
  li        = NULL;
  dynstr_size  = 0;
  dynsym_size  = 0;
  dynrel_size  = 0;
  dynrela_size = 0;

  shdr32 = NULL;
  shdr64 = NULL;
  symcnt = 0;

  got_sec = 0;
  plt_sec = 0;
  str_sec = 0;
  sym_sec = 0;
  dst_sec = 0;
  dsm_sec = 0;
  int_sec = 0;
  gpt_sec = 0;

  dyn_offset = 0;
  dyn_size   = 0;
  dyn_link   = 0;

  stb  = NULL;
  dstb = NULL;

  borext_offset = 0;
  borext_size = 0;
}

//--------------------------------------------------------------------------
bool is_elf_file(linput_t *li)
{
  Elf32_Ehdr h;
  qlseek(li, 0);
  if ( qlread(li, &h, sizeof(h)) != sizeof(h)
    || h.e_ident[EI_MAG0] != ELFMAG0
    || h.e_ident[EI_MAG1] != ELFMAG1
    || h.e_ident[EI_MAG2] != ELFMAG2
    || h.e_ident[EI_MAG3] != ELFMAG3 ) return false;
  return true;
}

//--------------------------------------------------------------------------
#ifndef BUILD_LOADER
static void load_sht32(void)
{
  register int i;
  register Elf32_Shdr *sh;

  qlseek(li, uint32(ehdr.e_shoff));
  for(i = 0, sh = shdr32; i < ehdr.e_shnum; i++, sh++) {
    if(lread4bytes(li,          &sh->sh_name,      mf) ||
       lread4bytes(li,          &sh->sh_type,      mf) ||
       lread4bytes(li,          &sh->sh_flags,     mf) ||
       lread4bytes(li, (uint32*)&sh->sh_addr,      mf) ||
       lread4bytes(li,          &sh->sh_offset,    mf) ||
       lread4bytes(li,          &sh->sh_size,      mf) ||
       lread4bytes(li,          &sh->sh_link,      mf) ||
       lread4bytes(li,          &sh->sh_info,      mf) ||
       lread4bytes(li,          &sh->sh_addralign, mf) ||
       lread4bytes(li,          &sh->sh_entsize,   mf))  errstruct();
  }
}

//--------------------------------------------------------------------------
static void load_sht64(void)
{
  register int i;
  register Elf64_Shdr *sh;

  qlseek(li, uint32(ehdr.e_shoff));
  for(i = 0, sh = shdr64; i < ehdr.e_shnum; i++, sh++) {
    if(lread4bytes(li, &sh->sh_name,      mf) ||
       lread4bytes(li, &sh->sh_type,      mf) ||
       lread8bytes(li, &sh->sh_flags,     mf) ||
       lread8bytes(li, &sh->sh_addr,      mf) ||
       lread8bytes(li, &sh->sh_offset,    mf) ||
       lread8bytes(li, &sh->sh_size,      mf) ||
       lread4bytes(li, &sh->sh_link,      mf) ||
       lread4bytes(li, &sh->sh_info,      mf) ||
       lread8bytes(li, &sh->sh_addralign, mf) ||
       lread8bytes(li, &sh->sh_entsize,   mf))  errstruct();
  }
}

//--------------------------------------------------------------------------
static int parse_dyninfo(const dyninfo_t &dyninfo)
{
  for ( int i=0; i < dyninfo.size(); i++ )
  {
    const Elf64_Dyn &dyn = dyninfo[i];
    switch ( dyn.d_tag )
    {
      case DT_STRTAB:
        dynstr_off = map_ea(dyn.d_un);
        break;
      case DT_SYMTAB:
        dynsym_off = map_ea(dyn.d_un);
        break;
      case DT_REL:
        dynrel_off = map_ea(dyn.d_un);
        break;
      case DT_RELA:
        dynrela_off = map_ea(dyn.d_un);
        break;
      case DT_STRSZ:
        dynstr_size = uint32(dyn.d_un);
        break;
      case DT_RELSZ:
        dynrel_size = uint32(dyn.d_un);
        break;
      case DT_RELASZ:
        dynrela_size = uint32(dyn.d_un);
        break;
    }
  }
  size_t off = dynstr_off;
  if ( dynrel_off  ) off = qmin(dynrel_off, off);
  if ( dynrela_off ) off = qmin(dynrela_off, off);
  dynsym_size = off - dynsym_off;
  return 0;
}

//--------------------------------------------------------------------------
static bool load_name2(ushort index, uint32 offset)
{
  uint64 off, size;
  if ( index == ushort(-1) )
  {
    off = dynstr_off;
    size = dynstr_size;
  }
  else
  {
    off  = elf64 ? shdr64[index].sh_offset : shdr32[index].sh_offset;
    size = elf64 ? shdr64[index].sh_size   : shdr32[index].sh_size;
  }
  if ( offset >= size )
  {
    qsnprintf(name, sizeof(name), "bad offset %08x", low(offset+off));
    return false;
  }
  uint32 pos = qltell(li);
  offset = low(offset + off);
  qlseek(li, offset);

  register char *p;
  register int  i, j;
  bool ok = true;
  for(i = 0, p = name; i < sizeof(name)-1; i++, p++)
    if((j = qlgetc(li)) == EOF)
    {
      qstrncpy(p, "{truncated name}", sizeof(name)-(p-name));
      ok = false;
      break;
    }
    else if((*p = (char)j) == '\0') break;
  if(i == sizeof(name)-1)
  {
    qstrncpy(p-5, "...", 5);
    ok = false;
  }
  qlseek(li, pos);
  return ok;
}
#endif // BUILD_LOADER

//--------------------------------------------------------------------------
static const char *get_pht_type(int type)
{
  switch ( type )
  {
    case PT_NULL:     return "NULL";
    case PT_LOAD:     return "LOAD";
    case PT_DYNAMIC:  return "DYNAMIC";
    case PT_INTERP:   return "INTERP";
    case PT_NOTE:     return "NOTE";
    case PT_SHLIB:    return "SHLIB";
    case PT_PHDR:     return "PHDR";
    case PT_TLS:      return "TLS";

    case PT_GNU_EH_FRAME: return "EH_FRAME";
    case PT_GNU_STACK:    return "STACK";
    case PT_GNU_RELRO:    return "RO-AFTER";

    default:
#ifndef EFD_COMPILE
      return  "'?'";
#else
      {
        static char buf[10];
        qsnprintf(buf, sizeof(buf), "%08X", type);
        return buf;
      }
#endif
  }
}

//--------------------------------------------------------------------------
template<class Elf32_Shdr>
static void get_section_name(Elf32_Shdr *sh)
{
    if(ehdr.e_shstrndx) load_name2(ehdr.e_shstrndx, sh->sh_name);
    else if(sh->sh_size != 0) name[0] = '\0'; //nonamed sections ?
}

//--------------------------------------------------------------------------
template<class Elf32_Shdr>
static void analyze_sht(Elf32_Shdr *sh)
{
  int i;

  for(i = 1, sh++; i < ehdr.e_shnum; i++, sh++)
  {
    if(sh->sh_size==0 && (ehdr.e_type != ET_REL ||  //skip zero segment's
       (sh->sh_type != SHT_PROGBITS && sh->sh_type != SHT_NOBITS))) continue;

    if ( sh->sh_size == 0 ) continue;
    get_section_name(sh);
    switch(sh->sh_type) {
      case SHT_STRTAB:
        if(!strcmp(name, ".strtab"))
          str_sec = ushort(i);
        else if(!strcmp(name, ".dynstr"))
          dst_sec = ushort(i);
        break;

      case SHT_DYNAMIC:
      case SHT_DYNSYM:
      case SHT_SYMTAB:
          switch(sh->sh_type)
          {
            case SHT_SYMTAB:
              sym_sec = ushort(i);
              symcnt += (uint32)sh->sh_size;
              break;
            case SHT_DYNSYM:
              dsm_sec = ushort(i);
              symcnt += (uint32)sh->sh_size;
              break;
            case SHT_DYNAMIC:
              dyn_offset = (uint32)sh->sh_offset;
              dyn_size   = (uint32)sh->sh_size;
              dyn_link   = sh->sh_link;
              break;
          }
          break;

      case SHT_PROGBITS:
        if(!strcmp(name, ".interp"))
        {
          int_sec = ushort(i);
          break;
        }
        if(!strcmp(name, ".got"))
        {
          got_sec = ushort(i);
          break;
        }
        if(!strcmp(name, ".got.plt"))
        {
          gpt_sec = ushort(i);
          break;
        }
        // no break
      case SHT_NOBITS:
        if(!strcmp(name, ".plt")) plt_sec = ushort(i);
        break;

      // For Kylix (currently - efd only)
      case SHT_LOPROC:
        if(!strcmp(name, "borland.coment")) {
          borext_offset = (uint32)sh->sh_offset;
          borext_size   = (uint32)sh->sh_size;
        }
        break;
    }
  }
  if(!gpt_sec) gpt_sec = got_sec; // unification for ABI 2
  else if(!got_sec) gpt_sec = 0;  // unsupported format
}
