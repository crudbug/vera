#include <dbg.hpp>

#include "deb_arm.hpp"

//--------------------------------------------------------------------------
//
//      DEBUGGER REGISTER AND INSTRUCTIONS INFORMATIONS
//
//--------------------------------------------------------------------------

const char *arm_register_classes[] =
{
  "General registers",
//  "FPU registers",
  NULL
};


static const char *const psr[] =
{
  "MODE",       // 0
  "MODE",       // 1
  "MODE",       // 2
  "MODE",       // 3
  "MODE",       // 4
  "T",          // 5
  "F",          // 6
  "I",          // 7
  "A",          // 8
  "E",          // 9
  "IT",         // 10
  "IT",         // 11
  "IT",         // 12
  "IT",         // 13
  "IT",         // 14
  "IT",         // 15
  "GE",         // 16
  "GE",         // 17
  "GE",         // 18
  "GE",         // 19
  NULL,         // 20
  NULL,         // 21
  NULL,         // 22
  NULL,         // 23
  "J",          // 24
  "IT",         // 25
  "IT",         // 26
  "Q",          // 27
  "V",          // 28
  "C",          // 29
  "Z",          // 30
  "N",          // 31
};

register_info_t arm_registers[] =
{
  // FPU registers
//  { "VFP0",   0,                            ARM_RC_FPU,      dt_tbyte, NULL,   0 },
//  { "VFP1",   0,                            ARM_RC_FPU,      dt_tbyte, NULL,   0 },
//  { "VFP2",   0,                            ARM_RC_FPU,      dt_tbyte, NULL,   0 },
//  { "VFP3",   0,                            ARM_RC_FPU,      dt_tbyte, NULL,   0 },
//  { "VFP4",   0,                            ARM_RC_FPU,      dt_tbyte, NULL,   0 },
//  { "VFP5",   0,                            ARM_RC_FPU,      dt_tbyte, NULL,   0 },
//  { "VFP6",   0,                            ARM_RC_FPU,      dt_tbyte, NULL,   0 },
//  { "VFP7",   0,                            ARM_RC_FPU,      dt_tbyte, NULL,   0 },
//  { "SCR",    0,                            ARM_RC_FPU,      dt_word,  NULL,   0 },
//  { "EXC",    0,                            ARM_RC_FPU,      dt_word,  NULL,   0 },
  { "R0",    REGISTER_ADDRESS,             ARM_RC_GENERAL,  dt_dword, NULL,   0 },
  { "R1",    REGISTER_ADDRESS,             ARM_RC_GENERAL,  dt_dword, NULL,   0 },
  { "R2",    REGISTER_ADDRESS,             ARM_RC_GENERAL,  dt_dword, NULL,   0 },
  { "R3",    REGISTER_ADDRESS,             ARM_RC_GENERAL,  dt_dword, NULL,   0 },
  { "R4",    REGISTER_ADDRESS,             ARM_RC_GENERAL,  dt_dword, NULL,   0 },
  { "R5",    REGISTER_ADDRESS,             ARM_RC_GENERAL,  dt_dword, NULL,   0 },
  { "R6",    REGISTER_ADDRESS,             ARM_RC_GENERAL,  dt_dword, NULL,   0 },
  { "R7",    REGISTER_ADDRESS,             ARM_RC_GENERAL,  dt_dword, NULL,   0 },
  { "R8",    REGISTER_ADDRESS,             ARM_RC_GENERAL,  dt_dword, NULL,   0 },
  { "R9",    REGISTER_ADDRESS,             ARM_RC_GENERAL,  dt_dword, NULL,   0 },
  { "R10",   REGISTER_ADDRESS,             ARM_RC_GENERAL,  dt_dword, NULL,   0 },
  { "R11",   REGISTER_ADDRESS,             ARM_RC_GENERAL,  dt_dword, NULL,   0 },
  { "R12",   REGISTER_ADDRESS|REGISTER_FP, ARM_RC_GENERAL,  dt_dword, NULL,   0 },
  { "SP",    REGISTER_ADDRESS|REGISTER_SP, ARM_RC_GENERAL,  dt_dword, NULL,   0 },
  { "LR",    REGISTER_ADDRESS,             ARM_RC_GENERAL,  dt_dword, NULL,   0 },
  { "PC",    REGISTER_ADDRESS|REGISTER_IP, ARM_RC_GENERAL,  dt_dword, NULL,   0 },
  { "PSR",   0,                            ARM_RC_GENERAL,  dt_dword, psr,    0xF800007F },
};

//--------------------------------------------------------------------------
int idaapi arm_thread_read_registers(thid_t thread_id, regval_t *values, int count)
{
  return s_thread_read_registers(thread_id, values, count);
}

//--------------------------------------------------------------------------
int idaapi arm_thread_write_register(thid_t thread_id, int reg_idx, const regval_t *value)
{
  return s_thread_write_register(thread_id, reg_idx, value);
}

//--------------------------------------------------------------------------
int is_arm_valid_bpt(bpttype_t type, ea_t ea, int len)
{
  if ( type != BPT_SOFT )
  {
    if ( type != BPT_RDWR         // type is good?
      && type != BPT_WRITE
      && type != BPT_EXEC)
        return BPT_BAD_TYPE;

    if ( (ea & (len-1)) != 0 )    // alignment is good?
      return BPT_BAD_ALIGN;

    if ( len != 1 )
    {
      warning("AUTOHIDE REGISTRY\n"
              "xScale supports only 1 byte length hardware breakpoints");
      return BPT_BAD_LEN;
    }
  }
  return BPT_OK;
}

