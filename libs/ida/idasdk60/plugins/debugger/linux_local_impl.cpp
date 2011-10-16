#include <loader.hpp>
#include "../../ldr/elf/elfbase.h"

//--------------------------------------------------------------------------
// installs or uninstalls debugger specific idc functions
inline bool register_idc_funcs(bool)
{
  return true;
}

//--------------------------------------------------------------------------
void idaapi rebase_if_required_to(ea_t new_base)
{
  if ( is_miniidb() || inf.is_snapshot() )
    return;

  ea_t base = get_imagebase();
  if ( base != BADADDR && new_base != BADADDR && base != new_base )
  {
    int code = rebase_program(new_base - base, MSF_FIXONCE);
    if ( code != MOVE_SEGM_OK )
    {
      msg("Failed to rebase program, error code %d\n", code);
      warning("IDA Pro failed to rebase the program.\n"
              "Most likely it happened because of the debugger\n"
              "segments created to reflect the real memory state.\n\n"
              "Please stop the debugger and rebase the program manually.\n"
              "For that, please select the whole program and\n"
              "use Edit, Segments, Rebase program with delta 0x%a",
                                        new_base - base);
    }
  }
}

//--------------------------------------------------------------------------
static bool init_plugin(void)
{
#ifndef RPC_CLIENT
  if ( !init_subsystem() )
    return false;
#endif

  bool ok = false;
  do
  {
    if ( !netnode::inited() || is_miniidb() || inf.is_snapshot() )
    {
#ifdef __LINUX__
      // local debugger is available if we are running under Linux
      return true;
#else
      // for other systems only the remote debugger is available
      if ( debugger.is_remote() )
        return true;
      break; // failed
#endif
    }

    if ( inf.filetype != f_ELF )
      break;
    if ( ph.id != TARGET_PROCESSOR )
      break;

    is_dll = false;
    netnode elfnode(ELFNODE);
    Elf64_Ehdr ehdr;
    is_dll = false;
    if ( elfnode.valobj(&ehdr, sizeof(ehdr)) == sizeof(ehdr) )
    {
      is_dll = (ehdr.e_type == ET_DYN || ehdr.e_type == ET_REL);
    }
    ok = true;
  } while ( false );
#ifndef RPC_CLIENT
  if ( !ok )
    term_subsystem();
#endif
  return ok;
}

//--------------------------------------------------------------------------
inline void term_plugin(void)
{
#ifndef RPC_CLIENT
  term_subsystem();
#endif
}

//--------------------------------------------------------------------------
char comment[] = "Userland linux debugger plugin.";

char help[] =
        "A sample Userland linux debugger plugin\n"
        "\n"
        "This module shows you how to create debugger plugins.\n";

