/*
 *      CPP/D Demangler.
 *      Copyright (c) 2000-2011 by Iouri Kharon.
 *                        E-mail: yjh@styx.cabel.net
 *
 *      ALL RIGHTS RESERVED.
 *
 */

#ifndef _DEMANGLE_HPP
#define _DEMANGLE_HPP

// int32 result code
#define ME_INTERR   -1  // Internal error
#define ME_PARAMERR -2  // Input parameters are wrong
#define ME_ILLSTR   -3  // Incorrectly mangled name
#define ME_SMALLANS -4  // Output buffer is too small
                        // This code is possible only with the 'old' calling
                        // form. With the new calling form the output buffer
                        // will have '...' as the last characters and the
                        // result code or'ed with the sign bit
#define ME_FRAME    -5  // Partial demanging is possible (the input name has
                        // unrecognized suffix)
#define ME_NOCOMP   -6  // Could not determine the compiler
#define ME_ERRAUTO  -7  // Specified compiler is impossible for the input name
#define ME_NOHASHMEM -8 // Out of internal indexes-most likely bad input name
#define ME_NOSTRMEM  -9 // Out of internal buffers (can't be!:)

#define ME_NOERROR_LIMIT  -10 // Lowest error number. Lower values
                              // signal about the truncated output name
                              // (the output buffer is too small)

#define M_PRCMSK     0x0000000F // If = 0, then data
#define MT_DEFAULT    0x00000001 // 1 - default (for  watcom/gnu only this)
#define MT_CDECL      0x00000002 // 2 - __cdecl
#define MT_PASCAL     0x00000003 // 3 - __pascal
#define MT_STDCALL    0x00000004 // 4 - __stdcall
#define MT_FASTCALL   0x00000005 // 5 - __fastcall
#define MT_THISCALL   0x00000006 // 6 - __thiscall [ms & bc => pragma only]
#define MT_FORTRAN    0x00000007 // 7 - __fortran
#define MT_SYSCALL    0x00000008 // 8 - __syscall  [without ms]
#define MT_INTERRUPT  0x00000009 // 9 - __interrupt (only with __cdecl!)
#define MT_MSFASTCALL 0x0000000A // A - __msfastcall (bc)
#define MT_CLRCALL    0x0000000B // B - __clrcall (vc7)
#define MT_DMDCALL    0x0000000C // C - __dcall (dm D language abi)

//   reserved
#define MT_LOCALNAME  0x0000000F // f - might be function or data. Currently
                                 //     is used only for bc - as the
                                 //     identifier for local pascal labels

#define M_SAVEREGS   0x00000010 // For functions with "__saveregs"

#define M_CLASS     0x000000E0  // 0 - no keyword (not a member field)
#define MT_PUBLIC    0x00000020 // 1 - public
#define MT_PRIVATE   0x00000040 // 2 - private
#define MT_PROTECT   0x00000060 // 3 - protected
#define MT_MEMBER    0x00000080 // 4 - undetermined (bc/wat/gcc)
#define MT_VTABLE    0x000000A0 // 5 - vtable (bc/gnu)
#define MT_RTTI      0x000000C0 // 6 - typeinfo table (gcc3)
//   reserved

#define M_PARMSK   0x0000FF00 // Parameter number mask (excluding ellipsis)
                              // 255 - >= 255
#define MT_PARSHF      8      // shift to PARMSK
#define MT_PARMAX     0xFF    // Number limiter
#define M_ELLIPSIS 0x00010000   // The function _certainly_ has '...'
#define MT_VOIDARG  0x0001FF00  // If = 0, the func(void), i.e. no parameters
#define M_STATIC   0x00020000   // static
                                // gcc3 - static data in a function
                                // might be encountered in object files and
                                // (possibly) in binaries with debug info
#define M_VIRTUAL  0x00040000   // virtual
                                // NOTE: for (D) not virtual -- this (counted!)
#define M_AUTOCRT  0x00080000   // Most likely "autogenerated" function (data)
                                // NOTE: +M_STATIC => "__linkproc__" (bc)

#define M_TYPMASK  0x00700000   // Special functions (0-regular function)
#define MT_OPERAT   0x00100000    // 1 - operator
#define MT_CONSTR   0x00200000    // 2 - constructor
#define MT_DESTR    0x00300000    // 3 - destructor
#define MT_CASTING  0x00400000    // 4 - type conversion
#define MT_CLRCDTOR 0x00500000    // 5 - delphi2010 CLR ctor/dtor for packages
//  reserved

#define M_TRUNCATE 0x00800000 // Name was truncated by the compiler (bc/va)
#define M_THUNK    0x01000000 // [thunk]:
#define M_ANONNSP  0x02000000 // ms  => Anonymous Namespace for field
                              // gc3 => Item placed in Anonymous namespace
                              // wat => anonymous_enum
                              // bc  => + TMPLNAM = PascalTemplate (for DCC)
                              //  If separate - "automatic" except_t
                              //  from CBuilder for "external" variables
                              //  or a template for global object
                              //  constructor/destructor tables (for CBuilder
                              //  as well)
#define M_TMPLNAM  0x04000000 // ms  => template name (?)
                              // wat =>
                              // bc  => template name => its description table
                              // gc3 => any template funciton/data
#define M_DBGNAME  0x08000000 // ms  =>  CV:
                              // wat => xxxx: (T?xxxx-form)
                              // bc  => old pascal format (capitalized)
                              // gc3 => unicode symbols or 'vendor-extension'
                              //        qualifiers are present

#define M_COMPILER 0x70000000 // Compiler mask (0-unknown)
#define MT_MSCOMP   0x10000000  // 1 - microsoft/symantec
#define MT_BORLAN   0x20000000  // 2 - borland
#define MT_WATCOM   0x30000000  // 3 - watcom
#define MT_DMD      0x40000000  // 4 - digital mars D language
// !!! The following definitions must be last and in this order!
#define MT_GNU      0x50000000  // 5 - GNU - (over VA for autodetection)
#define MT_GCC3     0x60000000  // 6 - gcc-v3
                                 // In the short form this answer is possible
                                 // for GNU/VA as well, but gcc3 can be
                                 // explicitly requested only with it.
                                 // Autodetection works but not very reliable.
#define MT_VISAGE   0x70000000  // 7 - Visual Age - never autodetected
                                 // In the short form this answer means VA
                                 // or GNU. In the automatic mode GNU will
                                 // be used!
//---------------------------------------------------------------------------
// Flags to inhibit different parts of the demangled name
#define MNG_PTRMSK       0x7  // Memory model mask
// DO NOT change order in this group (PtrType)
#define MNG_DEFNEAR       0x0 // inhibit near, display everything else
#define MNG_DEFNEARANY    0x1 // inhibit near/__ptr64, display everything else
#define MNG_DEFFAR        0x2 // inhibit far, display everything else
#define MNG_NOPTRTYP16    0x3 // inhibit everything (disables vc7-extensions)
#define MNG_DEFHUGE       0x4 // inhibit huge, display everything else
#define MNG_DEFPTR64      0x5 // inhibit __pt64, display everything else
                              // ATT: in 64bit must be + MNG_NOTYPE|MNG_NOCALLC
#define MNG_DEFNONE       0x6 // display everything
#define MNG_NOPTRTYP      0x7 // inhibit everything
//
#define MNG_NODEFINIT    0x00000008 // Inhibit everything except the main name
                                    // This flag is not recommended
                                    // for __fastcall/__stdcall GCC3 names
                                    // because there is a high probablity of
                                    // incorrect demangling. Use it only when
                                    // you are sure that the input is a
                                    // cygwin/mingw function name
//
#define MNG_NOUNDERSCORE 0x00000010 // Inhibit underscores in __ccall, __pascal... +
#define MNG_NOTYPE       0x00000020 // Inhibit callc&based
#define MNG_NORETTYPE    0x00000040 // Inhibit return type of functions
#define MNG_NOBASEDT     0x00000080 // Inhibit base types
                                    //   NOTE: also inhibits "__linkproc__"
#define MNG_NOCALLC      0x00000100 // Inhibit __pascal/__ccall/etc
                                    //   NOTE: also inhibits "extern (cc)" (D)
#define MNG_NOPOSTFC     0x00000200 // Inhibit postfix const
#define MNG_NOSCTYP      0x00000400 // Inhibit public/private/protected
                                    //   NOTE: also inhibits in/out/lazy for args (D)
#define MNG_NOTHROW      0x00000800 // Inhibit throw description
                                    //   NOTE: for (D) also inhibits all funcattr
#define MNG_NOSTVIR      0x00001000 // Inhibit "static" & "virtual"
                                    //   NOTE: also inhibits (D) top-level procs (<=)
#define MNG_NOECSU       0x00002000 // Inhibit class/struct/union/enum[/D:typedef]
#define MNG_NOCSVOL      0x00004000 // Inhibit const/volatile/restrict
                                    //   NOTE: also inhibits "__unaligned"
                                    //   NOTE: also inhibits shared/immutable (D)
#define MNG_NOCLOSUR     0x00008000 // Inhibit __closure for borland
#define MNG_NOUNALG      0x00010000 // Inhibit __unaligned (see NOCSVOL)
#define MNG_NOMANAGE     0x00020000 // Inhibit __pin/__box/__gc for ms(.net)
//                       0x00040000
//                       0x00080000
//++++++
#define MNG_SHORT_S      0x00100000 // signed (int) is displayed as s(int)
#define MNG_SHORT_U      0x00200000 // unsigned (int) is displayed as u(int)
#define MNG_ZPT_SPACE    0x00400000 // Display space after comma in the arglist
#define MNG_DROP_IMP     0x00800000 // Inhibit __declspec(dllimport)
//
//                       0x01000000
#define MNG_IGN_ANYWAY   0x02000000 // Ingore '_nn' at the end of name
#define MNG_IGN_JMP      0x04000000 // Ingore 'j_'  at the beginning of name
#define MNG_MOVE_JMP     0x08000000 // Move 'j_' prefix to the demangled name
                                      // If both MNG_IGN_JMP and MNG_MOVE_JMP
                                      // are set then move the prefix only if
                                      // the name was not truncated
//
#define MNG_COMPILER_MSK 0x70000000 // Compiler mask (0-autodetect)

#define MNG_SHORT_FORM  (MNG_NOTYPE|MNG_NORETTYPE|MNG_NOPOSTFC|MNG_NOPTRTYP| \
        MNG_NOSCTYP|MNG_NOTHROW|MNG_NOSTVIR|MNG_NOECSU|MNG_NOCLOSUR| \
             MNG_SHORT_U|MNG_DROP_IMP|MNG_NOUNALG|MNG_NOMANAGE| \
             MNG_IGN_JMP|MNG_MOVE_JMP|MNG_IGN_ANYWAY)
#define MNG_LONG_FORM (MNG_ZPT_SPACE | MNG_IGN_JMP | MNG_IGN_ANYWAY | MNG_NOPTRTYP)

// The description of the following symbol is in the notes
#define MNG_CALC_VALID (MNG_COMPILER_MSK|MNG_IGN_JMP|MNG_IGN_ANYWAY)

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef H2ASH

typedef int32 ida_export demangler_t(
        char *answer,
        uint answer_length,
        const char *str,
        uint32 disable_mask);

idaman demangler_t demangle;

// If answer_length == 0 then no demangling is performed neither. The function
// will check if demangling is possible and what compiler is used to mangle
// the name. If the name can not be demangled then the function will return 0.
// NOTE: the answer MT_MSCOMP+1 means __msfastcall
//       (or borland class name with "_4" suffix) and the demangling is possible
//        either as MS (__fastcall) or as bc (__msfastcall)
// NOTE: the answer MT_GCC3+1 means POSSIBLE mingw/cygwin with
//       __stdcall/__fastcall but it might also mean ms-stdcall.
//       In essense it means that the demangler can not determine the compiler
//       precisely.
//       It also means that the demangling is possible in the gcc3 mode
//       ONLY when the compiler is explicitly set to gcc3 and MNG_NODEFINIT
//       bit is not set.

// If answer == NULL then the demangler will return check if the demangling
// is possible and only return the flags.
// In this case answer_length should be enough to hold the demangled name.

// NOTE: If int32(answer_length) < 0 then the demangler will calcuate the
//       the number of purged bytes for the given name. In this case
//       disable_mask may contain only bits included in MNG_CALC_VALID,
//       and -answer_length must be equal to the register size (e.g.
//       sizeof(uint16/uint32/uint64)). The value of the register size
//       is used to check the numeric value in the ms stdcall/fastcall
//       encoding (it is used in the gcc mode too).
//       if return value <= 0 - no purged bytes or valid information.
//       If (value & 1) != 0 - ms stdcall (definite npurged is value-1.
//       If (value & 1) == 0 - 'encoded' counter (not implemented yet).

// If answer != NULL (and answer_length != 0) - perform demangling and fill out.
// NOTE: if int32(answer_length) < 0 then the buffer size will be -answer_length
//       but 'answer' is interpreted not as a pointer to the output buffer but
//       as a pointer to pointer to the output buffer (char**).
//       In this case if the function succeeds,a pointer to the answer end
//       will be returned in the pointer (like stpcpy). In this form 'answer'
//       can not be NULL and *(char**)answer can not be NULL.
//       answer_length must be greater than 9 for the 'truncated' answer.

typedef int mangled_name_type_t;
const mangled_name_type_t MANGLED_CODE = 0;
const mangled_name_type_t MANGLED_DATA = 1;
const mangled_name_type_t MANGLED_UNKNOWN = 2;

idaman mangled_name_type_t ida_export get_mangled_name_type(const char *name);

enum dem_mode_t
{
  dem_mode16 = 0,
  dem_mode32 = 1,
  dem_mode64 = 2
};
void init_demangler(dem_mode_t mode);

bool is_mangled_string_name(const char *name);

#endif // H2ASH
#endif // _DEMANGLE_HPP
