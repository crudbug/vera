/*
 * 	Panasonic MN102 (PanaXSeries) processor module for IDA Pro.
 *	Copyright (c) 2000-2006 Konstantin Norvatoff, <konnor@bk.ru>
 *	Freeware.
 */

#include "pan.hpp"

instruc_t Instructions[] = {
{"",            0                               },
{"ADD",         CF_USE1|CF_USE2|CF_CHG2         },
{"ADDC",        CF_USE1|CF_USE2|CF_CHG2         },
{"ADDNF",       CF_USE1|CF_USE2|CF_CHG2         },
{"AND",         CF_USE1|CF_USE2|CF_CHG2         },
{"ASR",         CF_USE1|CF_CHG1                 },
{"BCC",         CF_USE1|CF_JUMP                 },
{"BCCX",        CF_USE1|CF_JUMP                 },
{"BCLR",        CF_USE1|CF_USE2|CF_CHG2         },
{"BCS",         CF_USE1|CF_JUMP                 },
{"BCSX",        CF_USE1|CF_JUMP                 },
{"BEQ",         CF_USE1|CF_JUMP                 },
{"BEQX",        CF_USE1|CF_JUMP                 },
{"BGE",         CF_USE1|CF_JUMP                 },
{"BGEX",        CF_USE1|CF_JUMP                 },
{"BGT",         CF_USE1|CF_JUMP                 },
{"BGTX",        CF_USE1|CF_JUMP                 },
{"BHI",         CF_USE1|CF_JUMP                 },
{"BHIX",        CF_USE1|CF_JUMP                 },
{"BLE",         CF_USE1|CF_JUMP                 },
{"BLEX",        CF_USE1|CF_JUMP                 },
{"BLS",         CF_USE1|CF_JUMP                 },
{"BLSX",        CF_USE1|CF_JUMP                 },
{"BLT",         CF_USE1|CF_JUMP                 },
{"BLTX",        CF_USE1|CF_JUMP                 },
{"BNC",         CF_USE1|CF_JUMP                 },
{"BNCX",        CF_USE1|CF_JUMP                 },
{"BNE",         CF_USE1|CF_JUMP                 },
{"BNEX",        CF_USE1|CF_JUMP                 },
{"BNS",         CF_USE1|CF_JUMP                 },
{"BNSX",        CF_USE1|CF_JUMP                 },
{"BRA",         CF_USE1|CF_JUMP|CF_STOP         },
{"BSET",        CF_USE1|CF_USE2|CF_CHG2         },
{"BTST",        CF_USE1|CF_USE2|CF_CHG2         },
{"BVC",         CF_USE1|CF_JUMP                 },
{"BVCX",        CF_USE1|CF_JUMP                 },
{"BVS",         CF_USE1|CF_JUMP                 },
{"BVSX",        CF_USE1|CF_JUMP                 },
{"CMP",         CF_USE1|CF_USE2                 },
{"DIVU",        CF_USE1|CF_USE2|CF_CHG2         },
{"EXT",         CF_USE1                         },
{"EXTX",        CF_USE1|CF_CHG1                 },
{"EXTXB",       CF_USE1|CF_CHG1                 },
{"EXTXBU",      CF_USE1|CF_CHG1                 },
{"EXTXU",       CF_USE1|CF_CHG1                 },
{"JMP",         CF_USE1|CF_JUMP|CF_STOP         },
{"JSR",         CF_USE1|CF_CALL                 },
{"LSR",         CF_USE1|CF_CHG1                 },
{"MOV",         CF_USE1|CF_USE2|CF_CHG2         },
{"MOVB",        CF_USE1|CF_USE2|CF_CHG2         },
{"MOVBU",       CF_USE1|CF_USE2|CF_CHG2         },
{"MOVX",        CF_USE1|CF_USE2|CF_CHG2         },
{"MUL",         CF_USE1|CF_USE2|CF_CHG2         },
{"MULQ",        CF_USE1|CF_USE2                 },
{"MULQH",       CF_USE1|CF_USE2                 },
{"MULQL",       CF_USE1|CF_USE2                 },
{"MULU",        CF_USE1|CF_USE2|CF_CHG2         },
{"NOP",         0                               },
{"NOT",         CF_USE1|CF_CHG1                 },
{"OR",          CF_USE1|CF_USE2|CF_CHG2         },
{"PXST",        0                               },
{"ROL",         CF_USE1|CF_CHG1                 },
{"ROR",         CF_USE1|CF_CHG1                 },
{"RTI",         CF_STOP                         },
{"RTS",         CF_STOP                         },
{"SUB",         CF_USE1|CF_USE2|CF_CHG2         },
{"SUBC",        CF_USE1|CF_USE2|CF_CHG2         },
{"TBNZ",        CF_USE1|CF_USE2|CF_USE3|CF_JUMP },
{"TBZ",         CF_USE1|CF_USE2|CF_USE3|CF_JUMP },
{"XOR",         CF_USE1|CF_USE2|CF_CHG2         }
};

#ifdef __BORLANDC__
#if sizeof(Instructions)/sizeof(Instructions[0]) != mn102_last
#error		No match:  sizeof(InstrNames) !!!
#endif
#endif
