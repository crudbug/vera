/*
 *      Interactive disassembler (IDA).
 *      Version 3.05
 *      Copyright (c) 1990-95 by Ilfak Guilfanov. (2:5020/209@fidonet)
 *      ALL RIGHTS RESERVED.
 *
 */

//
//      Portable Executable file format (MS Windows 95, MS Windows NT)
//

#ifndef _PE_H_
#define _PE_H_

#include <time.h>
#include <stddef.h>

#pragma pack(push, 1)           // IDA uses 1 byte alignments!
//-----------------------------------------------------------------------
//
// 32-bit Portable EXE Header
//
//-----------------------------------------------------------------------
struct petab_t
{
  uint32 rva;           // relative virtual address
  uint32 size;          // size
};                      // PE va/size array element

template <class pointer_t>
struct peheader_tpl
{
  int32 signature;      // 00 Current value is "PE/0/0".

#define PEEXE_ID   0x4550   // 'PE' followed by two zeroes
#define BPEEXE_ID  0x455042 // Borland's extenson for DPMI'host
  uint16 machine;       // 04 This field specifies the type of CPU
                  // compatibility required by this image to run.
                  // The values are:
#define PECPU_UNKNOWN 0x0000    // unknown

#define PECPU_80386   0x014C    // 80386
#define PECPU_80486   0x014D    // 80486
#define PECPU_80586   0x014E    // 80586

#define PECPU_R3000   0x0162    // MIPS Mark I (R2000, R3000)
#define PECPU_R6000   0x0163    // MIPS Mark II (R6000)
#define PECPU_R4000   0x0166    // MIPS Mark III (R4000)
#define PECPU_R10000  0x0168    // MIPS Mark IV (R10000)
#define PECPU_WCEMIPSV2 0x0169  // MIPS little-endian WCE v2
#define PECPU_MIPS16    0x0266  // MIPS16
#define PECPU_MIPSFPU   0x0366  // MIPS with FPU
#define PECPU_MIPSFPU16 0x0466  // MIPS16 with FPU

#define PECPU_ALPHA   0x0184    // DEC Alpha
#define PECPU_ALPHA64 0x0284    // Dec Alpha 64-bit

#define PECPU_SH3     0x01A2    // SH3
#define PECPU_SH3DSP  0x01A3    // SH3DSP
#define PECPU_SH3E    0x01A4    // SH3E
#define PECPU_SH4     0x01A6    // SH4
#define PECPU_SH5     0x01A8    // SH5

#define PECPU_ARM     0x01C0    // ARM
#define PECPU_ARMI    0x01C2    // ARM with Thumb

#define PECPU_AM33    0x01D3    // Matsushita (Panasonic) AM33/MN10300

#define PECPU_PPC     0x01F0    // PowerPC
#define PECPU_PPCFP   0x01F1    // PowerPC with floating-point
#define PECPU_PPCBE   0x01F2    // PowerPC Big-Endian

#define PECPU_M32R    0x9041    // M32R little-endian

#define PECPU_IA64    0x0200    // Intel Itanium IA64
#define PECPU_EPOC    0x0A00    // ARM EPOC
#define PECPU_AMD64   0x8664    // AMD64 (x64)
#define PECPU_M68K    0x0268    // Motorola 68000 series
#define PECPU_EBC     0x0EBC    // EFI Bytecode
#define PECPU_CEF     0x0CEF    // ?
#define PECPU_CEE     0xC0EE    // ?
#define PECPU_TRICORE 0x0520    // TRICORE (Infineon)

  bool is_64bit_cpu(void) const { return (machine == PECPU_AMD64) || (machine == PECPU_IA64); }

  uint16 nobjs;     // 06 This field specifies the number of entries
                    // in the Object Table.
  qtime32_t datetime; // 08 Used to store the time and date the file was
                    // created or modified by the linker.
  uint32 symtof;    // 0C Symbol Table Offset
  uint32 nsyms;     // 10 Number of Symbols in Symbol Table
  uint16 hdrsize;   // 14 This is the number of remaining bytes in the NT
                    // header that follow the FLAGS field.
  uint16 flags;     // 16 Flag bits for the image.  0000h Program image.
#define PEF_BRVHI 0x8000        // Big endian: MSB precedes LSB in memory
#define PEF_UP    0x4000        // File should be run only on a UP machine
#define PEF_DLL   0x2000        // Dynamic Link Library (DLL)
#define PEF_SYS   0x1000        // System file
#define PEF_0800  0x0800        // Reserved
#define PEF_SWAP  0x0400        // If image is on removable media,
                                // copy and run from swap file
#define PEF_NODEB 0x0200        // Debugging info stripped
#define PEF_32BIT 0x0100        // 32-bit word machine
#define PEF_BRVLO 0x0080        // Little endian: LSB precedes MSB in memory
#define PEF_16BIT 0x0040        // 16-bit word machine
#define PEF_2GB   0x0020        // App can handle > 2gb addresses
#define PEF_TMWKS 0x0010        // Aggressively trim working set
#define PEF_NOSYM 0x0008        // Local symbols stripped
#define PEF_NOLIN 0x0004        // Line numbers stripped
#define PEF_EXEC  0x0002        // Image is executable
#define PEF_NOFIX 0x0001        // Relocation info stripped

  int32 first_section_pos(int32 peoff) const
    { return peoff + offsetof(peheader_tpl, magic) + hdrsize; }

        // COFF fields:

  uint16 magic;       // 18 Magic
#define MAGIC_ROM       0x107   // ROM image
#define MAGIC_P32       0x10B   // Normal PE file
#define MAGIC_P32_PLUS  0x20B   // 64-bit image
  bool is_pe_plus(void) const { return magic == MAGIC_P32_PLUS; }
  uchar vstamp_major; // 1A Major Linker Version
  uchar vstamp_minor; // 1B Minor Linker Version
  uint32 tsize;        // 1C TEXT size (padded)
  uint32 dsize;        // 20 DATA size (padded)
  uint32 bsize;        // 24 BSS  size (padded)
  uint32 entry;        // 28 Entry point
  uint32 text_start;   // 2C Base of text
  union
  {
    struct
    {
      uint32 data_start;   // 30 Base of data

        // Win32/NT extensions:

      uint32 imagebase32;    // 34 Virtual base of the image.
    };
    uint32 imagebase64[2];
  };
  uint64 imagebase() const
  {
    if ( is_pe_plus() )
      return make_ulonglong(imagebase64[0], imagebase64[1]);
    else
      return imagebase32;
  }
                      // This will be the virtual address of the first
                      // byte of the file (Dos Header).  This must be
                      // a multiple of 64K.
  uint32 objalign;    // 38 The alignment of the objects. This must be a power
                      // of 2 between 512 and 256M inclusive. The default
                      // is 64K.
  uint32 filealign;   // 3C Alignment factor used to align image pages.
                      // The alignment factor (in bytes) used to align the
                      // base of the image pages and to determine the
                      // granularity of per-object trailing zero pad.
                      // Larger alignment factors will cost more file space;
                      // smaller alignment factors will impact demand load
                      // performance, perhaps significantly. Of the two,
                      // wasting file space is preferable.  This value
                      // should be a power of 2 between 512 and 64K inclusive.
                      // Get the file position aligned:
#define FILEALIGN 512 // IDA5.1: it seems that for standard object alignment (if 4096)
                      // the Windows kernel does not use filealign
                      // (just checks that it is in the valid range) but uses 512
  uint32 get_align_mask(void) const { return (objalign == 4096 ? FILEALIGN : filealign) - 1; }
  uint32 align_up_in_file(uint32 pos) const
  {
    if (is_efi())  //apparently EFI images are not aligned
      return pos;
    uint32 mask = get_align_mask();
    return (pos+mask) & ~mask;
  }
  uint32 align_down_in_file(uint32 pos) const
  {
    return is_efi() ? pos : (pos & ~get_align_mask());
  }
  uint16 osmajor;     // 40 OS version number required to run this image.
  uint16 osminor;     // 42 OS version number required to run this image.
  uint16 imagemajor;  // 44 User major version number.
  uint16 imageminor;  // 46 User minor version number.
  uint16 subsysmajor; // 48 Subsystem major version number.
  uint16 subsysminor; // 4A Subsystem minor version number.
  uint32 reserved;    // 4C
  uint32 imagesize;   // 50 The virtual size (in bytes) of the image.
                      // This includes all headers.  The total image size
                      // must be a multiple of Object Align.
  uint32 allhdrsize;  // 54 Total header size. The combined size of the Dos
                      // Header, PE Header and Object Table.
  uint32 checksum;    // 58 Checksum for entire file.  Set to 0 by the linker.
  uint16 subsys;      // 5C NT Subsystem required to run this image.
#define PES_UNKNOWN 0x0000      // Unknown
#define PES_NATIVE  0x0001      // Native
#define PES_WINGUI  0x0002      // Windows GUI
#define PES_WINCHAR 0x0003      // Windows Character
#define PES_OS2CHAR 0x0005      // OS/2 Character
#define PES_POSIX   0x0007      // Posix Character
#define PES_NAT9x   0x0008      // image is a native Win9x driver
#define PES_WINCE   0x0009      // Runs on Windows CE.
#define PES_EFI_APP 0x000A      // EFI application.
#define PES_EFI_BDV 0x000B      // EFI driver that provides boot services.
#define PES_EFI_RDV 0x000C      // EFI driver that provides runtime services.
#define PES_EFI_ROM 0x000D      // EFI ROM image
#define PES_XBOX    0x000E      // Xbox system
#define PES_BOOTAPP 0x0010      // Windows Boot Application

  bool is_efi(void) const
  {
    return subsys == PES_EFI_APP
        || subsys == PES_EFI_BDV
        || subsys == PES_EFI_RDV
        || subsys == PES_EFI_ROM;
  }
  bool is_console_app(void) const
  {
    return subsys == PES_WINCHAR
        || subsys == PES_OS2CHAR
        || subsys == PES_POSIX;
  }
  bool is_userland(void) const
  {
      return subsys == PES_WINGUI
          || subsys == PES_WINCHAR
          || subsys == PES_OS2CHAR
          || subsys == PES_POSIX
          || subsys == PES_WINCE;
  }
  uint16 dllflags;    // 5E Indicates special loader requirements.
#define PEL_PINIT           0x0001 // Per-Process Library Initialization.
#define PEL_PTERM           0x0002 // Per-Process Library Termination.
#define PEL_TINIT           0x0004 // Per-Thread Library Initialization.
#define PEL_TTERM           0x0008 // Per-Thread Library Termination.
#define PEL_DYNAMIC_BASE    0x0040 // The DLL can be relocated at load time.
#define PEL_FORCE_INTEGRITY 0x0080 // Code integrity checks are forced.
#define PEF_NX              0x0100 // The image is compatible with data execution prevention (DEP).
#define PEF_NO_ISOLATION    0x0200 // The image is isolation aware, but should not be isolated.
#define PEF_NO_SEH          0x0400 // The image does not use structured exception handling (SEH). No handlers can be called in this image.
#define PEL_NO_BIND         0x0800 // Do not bind image
#define PEL_WDM_DRV         0x2000 // Driver is a WDM Driver
#define PEL_TSRVAWA         0x8000 // Image is Terminal Server aware

  pointer_t stackres; // 60 Stack size needed for image. The memory is
                      // reserved, but only the STACK COMMIT SIZE is
                      // committed. The next page of the stack is a
                      // 'guarded page'. When the application hits the
                      // guarded page, the guarded page becomes valid,
                      // and the next page becomes the guarded page.
                      // This continues until the RESERVE SIZE is reached.
  pointer_t stackcom; // 64 Stack commit size.
  pointer_t heapres;  // 68 Size of local heap to reserve.
  pointer_t heapcom;  // 6C Amount to commit in local heap.
  uint32 loaderflags;  // 70 ?
  uint32 nrvas;        // 74 Indicates the size of the VA/SIZE array
                      // that follows.
  petab_t expdir;     // 0 78 Export Directory
  petab_t impdir;     // 1 80 Import Directory
  petab_t resdir;     // 2 88 Resource Directory
  petab_t excdir;     // 3 90 Exception Directory
  petab_t secdir;     // 4 98 Security Directory
                      //      The Certificate Table entry points to a table of
                      //      attribute certificates. These certificates are not
                      //      loaded into memory as part of the image. As such,
                      //      the first field of this entry, which is normally
                      //      an RVA, is a File Pointer instead
  petab_t reltab;     // 5 A0 Relocation Table
  petab_t debdir;     // 6 A8 Debug Directory
  petab_t desstr;     // 7 B0 Description String
  petab_t cputab;     // 8 B8 Machine Value
  petab_t tlsdir;     // 9 C0 TLS Directory
  petab_t loddir;     //10 Load Configuration Directory
  petab_t bimtab;     //11 Bound Import Table address and size.
  petab_t iat;        //12 Import Address Table address and size.
  petab_t didtab;     //13 Address and size of the Delay Import Descriptor.
  petab_t comhdr;     //14 COM+ Runtime Header address and size
  petab_t x00tab;     //15 Reserved
};

typedef peheader_tpl<uint32> peheader_t;
typedef peheader_tpl<uint64> peheader64_t;

const int total_rvatab_size = sizeof(peheader_t) - offsetof(peheader_t, expdir);
const int total_rvatab_count = total_rvatab_size / sizeof(petab_t);

//-----------------------------------------------------------------------
struct diheader_t
{
  uint16 signature;     // 00 Current value is "DI"
#define DBG_ID 0x4944
  uint16 flags2;        // 02 ?? pedump mentions about this
                        //    I've never seen something other than 0
  uint16 machine;       // 04 This field specifies the type of CPU
                        //    compatibility required by this image to run.
  uint16 flags;         // 06 Flag bits for the image.
  qtime32_t datetime;   // 08 Used to store the time and date the file was
                        //    created or modified by the linker.
  uint32 checksum;      // 12 Checksum
  uint32 imagebase;     // 16 Virtual base of the image.
                        //    This will be the virtual address of the first
                        //    byte of the file (Dos Header).  This must be
                        //    a multiple of 64K.
  uint32 imagesize;     // 20 The virtual size (in bytes) of the image.
                        //    This includes all headers.  The total image size
                        //    must be a multiple of Object Align.
  uint32 n_secs;        // 24 Number of sections
  uint32 exp_name_size; // 28 Exported Names Size
  uint32 dbg_dir_size;  // 32 Debug Directory Size
  uint32 reserved[3];   // 36 Reserved fields
};

//-------------------------------------------------------------------------
//
//      S E C T I O N S
//
struct pesection_t
{
  char   s_name[8];   /* section name */
  uint32 s_vsize;     /* virtual size */
  uint32 s_vaddr;     /* virtual address */
  uint32 s_psize;     /* physical size */
  int32  s_scnptr;    /* file ptr to raw data for section */
  int32  s_relptr;    /* file ptr to relocation */
  int32  s_lnnoptr;   /* file ptr to line numbers */
  uint16 s_nreloc;    /* number of relocation entries */
  uint16 s_nlnno;     /* number of line number entries */
  int32  s_flags;     /* flags */
#define PEST_REG     0x00000000 // obsolete: regular: allocated, relocated, loaded
#define PEST_DUMMY   0x00000001 // obsolete: dummy: not allocated, relocated, not loaded
#define PEST_NOLOAD  0x00000002 // obsolete: noload: allocated, relocated, not loaded
#define PEST_GROUP   0x00000004 // obsolete: grouped: formed of input sections
#define PEST_PAD     0x00000008 // obsolete: padding: not allocated, not relocated, loaded
#define PEST_COPY    0x00000010 // obsolete: copy: for decision function used
                                //    by field update; not
                                //    allocated, not relocated,
                                //    loaded; reloc & lineno
                                //    entries processed normally */
#define PEST_TEXT    0x00000020L// section contains text only
#define PEST_DATA    0x00000040L// section contains data only
#define PEST_BSS     0x00000080L// section contains bss only
#define PEST_EXCEPT  0x00000100L// obsolete: Exception section
#define PEST_INFO    0x00000200L// Comment: not allocated, not relocated, not loaded
#define PEST_OVER    0x00000400L// obsolete: Overlay: not allocated, relocated, not loaded
#define PEST_LIB     0x00000800L// ".lib" section: treated like PEST_INFO

#define PEST_LOADER  0x00001000L// Loader section: COMDAT
#define PEST_DEBUG   0x00002000L// Debug section:
#define PEST_TYPCHK  0x00004000L// Type check section:
#define PEST_OVRFLO  0x00008000L// obsolete: RLD and line number overflow sec hdr
#define PEST_F0000   0x000F0000L// Unknown
#define PEST_ALIGN   0x00F00000L// Alignment 2^(x-1):
  uint32 get_sect_alignment(void) const
  {
    int align = ((s_flags >> 20) & 15);
    if ( align == 0 ) return 0;
    return 1 << (align-1);
  }
  asize_t get_vsize(const peheader_t &pe) const
  {
    return align_up(s_vsize ? s_vsize : s_psize, pe.objalign);
  }
  asize_t get_psize(const peheader_t &pe) const
  {
    return qmin(s_psize, get_vsize(pe));
  }

#define PEST_1000000 0x01000000L// Unknown
#define PEST_DISCARD 0x02000000L// Discardable
#define PEST_NOCACHE 0x04000000L// Not cachable
#define PEST_NOPAGE  0x08000000L// Not pageable
#define PEST_SHARED  0x10000000L// Shareable
#define PEST_EXEC    0x20000000L// Executable
#define PEST_READ    0x40000000L// Readable
#define PEST_WRITE   0x80000000L// Writable
};

//-------------------------------------------------------------------------
//
//      E X P O R T S
//
struct peexpdir_t
{
  uint32 flags;     // Currently set to zero.
  qtime32_t datetime; // Time/Date the export data was created.
  uint16 major;     // A user settable major/minor version number.
  uint16 minor;
  uint32 dllname;   // Relative Virtual Address of the Dll asciiz Name.
                    // This is the address relative to the Image Base.
  uint32 ordbase;   // First valid exported ordinal. This field specifies
                    // the starting ordinal number for the export
                    // address table for this image. Normally set to 1.
  uint32 naddrs;    // Indicates number of entries in the Export Address
                    // Table.
  uint32 nnames;    // This indicates the number of entries in the Name
                    // Ptr Table (and parallel Ordinal Table).
  uint32 adrtab;    // Relative Virtual Address of the Export Address
                    // Table. This address is relative to the Image Base.
  uint32 namtab;    // Relative Virtual Address of the Export Name Table
                    // Pointers. This address is relative to the
                    // beginning of the Image Base. This table is an
                    // array of RVA's with # NAMES entries.
  uint32 ordtab;    // Relative Virtual Address of Export Ordinals
                    // Table Entry. This address is relative to the
                    // beginning of the Image Base.
};

//-------------------------------------------------------------------------
//
//      I M P O R T S
//
struct peimpdir_t
{
  uint32 table1;    //aka OriginalFirstThunk
  qtime32_t datetime;  // Time/Date the import data was pre-snapped or
                    // zero if not pre-snapped.
  uint32 fchain;    // Forwarder chain
  uint32 dllname;   // Relative Virtual Address of the Dll asciiz Name.
                    // This is the address relative to the Image Base.
  uint32 looktab;   // aka FirstThunk
                    // This field contains the address of the start of
                    // the import lookup table for this image. The address
                    // is relative to the beginning of the Image Base.
#define hibit(type) ((type(-1)>>1) ^ type(-1))
#define IMP_BY_ORD32 hibit(uint32)  // Import by ordinal, otherwise by name
#define IMP_BY_ORD64 hibit(uint64)  // Import by ordinal, otherwise by name

  peimpdir_t(void) { memset(this, 0, sizeof(peimpdir_t)); }
};

struct dimpdir_t    // delayed load import table
{
  uint32 attrs;      // Attributes.
#define DIMP_NOBASE 0x0001  // pe.imagebase was not added to addresses
  uint32 dllname;    // Relative virtual address of the name of the DLL
                    // to be loaded. The name resides in the read-only
                    // data section of the image.
  uint32 handle;    // Relative virtual address of the module handle
                    // (in the data section of the image) of the DLL to
                    // be delay-loaded. Used for storage by the routine
                    // supplied to manage delay-loading.
  uint32 diat;      // Relative virtual address of the delay-load import
                    // address table. See below for further details.
  uint32 dint;      // Relative virtual address of the delay-load name
                    // table, which contains the names of the imports
                    // that may need to be loaded. Matches the layout of
                    // the Import Name Table, Section 6.4.3. Hint/Name Table.
  uint32 dbiat;     // Bound Delay Import Table. Relative virtual address
                    // of the bound delay-load address table, if it exists.
  uint32 duiat;     // Unload Delay Import Table. Relative virtual address
                    // of the unload delay-load address table, if it exists.
                    // This is an exact copy of the Delay Import Address
                    // Table. In the event that the caller unloads the DLL,
                    // this table should be copied back over the Delay IAT
                    // such that subsequent calls to the DLL continue to
                    // use the thunking mechanism correctly.
  qtime32_t datetime;  // Time stamp of DLL to which this image has been bound.
};


// Bound Import Table format:

struct BOUND_IMPORT_DESCRIPTOR
{
  qtime32_t TimeDateStamp;
  uint16 OffsetModuleName;
  uint16 NumberOfModuleForwarderRefs;
// Array of zero or more IMAGE_BOUND_FORWARDER_REF follows
};

struct BOUND_FORWARDER_REF
{
  qtime32_t TimeDateStamp;
  uint16 OffsetModuleName;
  uint16 Reserved;
};


//-------------------------------------------------------------------------
//
//      T H R E A D  L O C A L  D A T A
//

struct image_tls_directory64
{
  uint64 StartAddressOfRawData;
  uint64 EndAddressOfRawData;
  uint64 AddressOfIndex;         // PDWORD
  uint64 AddressOfCallBacks;     // PIMAGE_TLS_CALLBACK *;
  uint32  SizeOfZeroFill;
  uint32  Characteristics;
};

struct image_tls_directory32
{
  uint32  StartAddressOfRawData;
  uint32  EndAddressOfRawData;
  uint32  AddressOfIndex;        // PDWORD
  uint32  AddressOfCallBacks;    // PIMAGE_TLS_CALLBACK *
  uint32  SizeOfZeroFill;
  uint32  Characteristics;
};

//-------------------------------------------------------------------------
//
//      Exception Tables (.pdata)
//

//ARM, PowerPC, SH3 and SH4 WindowsCE platforms
struct function_entry_ce {
    uint32 FuncStart;          //Virtual address of the corresponding function.
    uint32 PrologLen : 8;      //Number of instructions in the function's prolog.
    uint32 FuncLen : 22;       //Number of instructions in the function.
    uint32 ThirtyTwoBit : 1;   //Set if the function is comprised of 32-bit instructions, cleared for a 16-bit function.
    uint32 ExceptionFlag : 1;  //Set if an exception handler exists for the function.
};

//for MIPS and 32-bit Alpha
struct function_entry_alpha {
    uint32 BeginAddress;       //Virtual address of the corresponding function.
    uint32 EndAddress;         //Virtual address of the end of the function.
    uint32 ExceptionHandler;   //Pointer to the exception handler to be executed.
    uint32 HandlerData;        //Pointer to additional information to be passed to the handler.
    uint32 PrologEndAddress;   //Virtual address of the end of the function's prolog.
};

//-------------------------------------------------------------------------
//
//      F I X U P S
//
struct pefixup_t
{
  uint32 page;// The image base plus the page rva is added to each offset
              // to create the virtual address of where the fixup needs to
              // be applied.
  uint32 size;// Number of bytes in the fixup block. This includes the
              // PAGE RVA and SIZE fields.
};

#define PER_OFF  0x0FFF
#define PER_TYPE 0xF000
#define PER_ABS         0x0000  // This is a NOP. The fixup is skipped.
#define PER_HIGH        0x1000  // Add the high 16-bits of the delta to the
                                // 16-bit field at Offset. The 16-bit field
                                // represents the high value of a 32-bit word.
#define PER_LOW         0x2000  // Add the low 16-bits of the delta to the
                                // 16-bit field at Offset. The 16-bit field
                                // represents the low half value of a
                                // 32-bit word.  This fixup will only be
                                // emitted for a RISC machine when the image
                                // Object Align isn't the default of 64K.
#define PER_HIGHLOW     0x3000  // Apply the 32-bit delta to the 32-bit field
                                // at Offset.
#define PER_HIGHADJUST  0x4000  // This fixup requires a full 32-bit value.
                                // The high 16-bits is located at Offset, and
                                // the low 16-bits is located in the next
                                // Offset array element (this array element
                                // is included in the SIZE field). The two
                                // need to be combined into a signed variable.
                                // Add the 32-bit delta. Then add 0x8000 and
                                // store the high 16-bits of the signed
                                // variable to the 16-bit field at Offset.
#define PER_MIPSJMPADDR  0x5000 // Fixup applies to a MIPS jump instruction.
#define PER_SECTION      0x6000 // Reserved for future use
#define PER_REL32        0x7000 // Reserved for future use
#define PER_MIPS_JMPADDR16 0x9000 // Fixup applies to a MIPS16 jump instruction.
#define PER_DIR64        0xA000 // This fixup applies the delta to the 64-bit
                                // field at Offset
#define PER_HIGH3ADJ     0xB000 // The fixup adds the high 16 bits of the delta
                                // to the 16-bit field at Offset. The 16-bit
                                // field represents the high value of a 48-bit
                                // word. The low 32 bits of the 48-bit value are
                                // stored in the 32-bit word that follows this
                                // base relocation. This means that this base
                                // relocation occupies three slots.

//-------------------------------------------------------------------------
//
//      DBG file debug entry format
//
struct debug_entry_t
{
  uint32 flags;                  // usually zero
  qtime32_t datetime;
  uint16 major;
  uint16 minor;
  int32 type;
#define DBG_COFF          1
#define DBG_CV            2
#define DBG_FPO           3
#define DBG_MISC          4
#define DBG_EXCEPTION     5
#define DBG_FIXUP         6
#define DBG_OMAP_TO_SRC   7
#define DBG_OMAP_FROM_SRC 8
#define DBG_BORLAND       9
#define DBG_CLSID         11
  uint32 size;
  uint32 rva;       // virtual address
  uint32 seek;      // ptr to data in the file
};

//-------------------------------------------------------------------------
//
//      DBG file COFF debug information header
//
struct coff_debug_t
{
  uint32 NumberOfSymbols;
  uint32 LvaToFirstSymbol;
  uint32 NumberOfLinenumbers;
  uint32 LvaToFirstLinenumber;
  uint32 RvaToFirstByteOfCode;
  uint32 RvaToLastByteOfCode;
  uint32 RvaToFirstByteOfData;
  uint32 RvaToLastByteOfData;
};

//-------------------------------------------------------------------------
//
//      DBG file FPO debug information
//
struct fpo_t
{
  uint32 address;
  uint32 size;
  uint32 locals;
  uint16 params;
  uchar prolog;
  uchar regs;
#define FPO_REGS      0x07  // register number
#define FPO_SEH       0x08  //
#define FPO_BP        0x10  // has BP frame?
#define FPO_TYPE      0xC0
#define FPO_T_FPO     0x00
#define FPO_T_TRAP    0x40
#define FPO_T_TSS     0x80
#define FPO_T_NONFPO    0xC0
};


//      DBG file OMAP debug information

struct omap_t
{
  uint32 a1;
  uint32 a2;
};

//----------------------------------------------------------------------
// Resource information
struct rsc_dir_t
{
  uint32 Characteristics;
  uint32 TimeDateStamp;
  uint16 MajorVersion;
  uint16 MinorVersion;
  uint16 NumberOfNamedEntries;
  uint16 NumberOfIdEntries;
};

struct rsc_dir_entry_t
{
  union
  {
    struct
    {
      uint32 NameOffset:31;
      uint32 NameIsString:1;
    };
    uint32 Name;
    uint16 Id;
  };
  union
  {
    uint32 OffsetToData;
    struct
    {
      uint32 OffsetToDirectory:31;
      uint32 DataIsDirectory:1;
    };
  };
};

struct rsc_data_entry_t
{
  uint32 OffsetToData;
  uint32 Size;
  uint32 CodePage;
  uint32 Reserved;
};


// Resource types
#define PE_RT_CURSOR       1
#define PE_RT_BITMAP       2
#define PE_RT_ICON         3
#define PE_RT_MENU         4
#define PE_RT_DIALOG       5
#define PE_RT_STRING       6
#define PE_RT_FONTDIR      7
#define PE_RT_FONT         8
#define PE_RT_ACCELERATOR  9
#define PE_RT_RCDATA       10
#define PE_RT_MESSAGETABLE 11
#define PE_RT_GROUP_CURSOR 12
#define PE_RT_GROUP_ICON   14
#define PE_RT_VERSION      16
#define PE_RT_DLGINCLUDE   17
#define PE_RT_PLUGPLAY     19
#define PE_RT_VXD          20
#define PE_RT_ANICURSOR    21
#define PE_RT_ANIICON      22
#define PE_RT_HTML         23
#define PE_RT_MANIFEST     24

// Language codes
#define PE_LANG_NEUTRAL     0x00
#define PE_LANG_INVARIANT   0x7f

#define PE_LANG_AFRIKAANS   0x36
#define PE_LANG_ALBANIAN    0x1c
#define PE_LANG_ARABIC      0x01
#define PE_LANG_ARMENIAN    0x2b
#define PE_LANG_ASSAMESE    0x4d
#define PE_LANG_AZERI       0x2c
#define PE_LANG_BASQUE      0x2d
#define PE_LANG_BELARUSIAN  0x23
#define PE_LANG_BENGALI     0x45
#define PE_LANG_BULGARIAN   0x02
#define PE_LANG_CATALAN     0x03
#define PE_LANG_CHINESE     0x04
#define PE_LANG_CROATIAN    0x1a
#define PE_LANG_CZECH       0x05
#define PE_LANG_DANISH      0x06
#define PE_LANG_DIVEHI      0x65
#define PE_LANG_DUTCH       0x13
#define PE_LANG_ENGLISH     0x09
#define PE_LANG_ESTONIAN    0x25
#define PE_LANG_FAEROESE    0x38
#define PE_LANG_FARSI       0x29
#define PE_LANG_FINNISH     0x0b
#define PE_LANG_FRENCH      0x0c
#define PE_LANG_GALICIAN    0x56
#define PE_LANG_GEORGIAN    0x37
#define PE_LANG_GERMAN      0x07
#define PE_LANG_GREEK       0x08
#define PE_LANG_GUJARATI    0x47
#define PE_LANG_HEBREW      0x0d
#define PE_LANG_HINDI       0x39
#define PE_LANG_HUNGARIAN   0x0e
#define PE_LANG_ICELANDIC   0x0f
#define PE_LANG_INDONESIAN  0x21
#define PE_LANG_ITALIAN     0x10
#define PE_LANG_JAPANESE    0x11
#define PE_LANG_KANNADA     0x4b
#define PE_LANG_KASHMIRI    0x60
#define PE_LANG_KAZAK       0x3f
#define PE_LANG_KONKANI     0x57
#define PE_LANG_KOREAN      0x12
#define PE_LANG_KYRGYZ      0x40
#define PE_LANG_LATVIAN     0x26
#define PE_LANG_LITHUANIAN  0x27
#define PE_LANG_MACEDONIAN  0x2f   // the Former Yugoslav Republic of Macedonia
#define PE_LANG_MALAY       0x3e
#define PE_LANG_MALAYALAM   0x4c
#define PE_LANG_MANIPURI    0x58
#define PE_LANG_MARATHI     0x4e
#define PE_LANG_MONGOLIAN   0x50
#define PE_LANG_NEPALI      0x61
#define PE_LANG_NORWEGIAN   0x14
#define PE_LANG_ORIYA       0x48
#define PE_LANG_POLISH      0x15
#define PE_LANG_PORTUGUESE  0x16
#define PE_LANG_PUNJABI     0x46
#define PE_LANG_ROMANIAN    0x18
#define PE_LANG_RUSSIAN     0x19
#define PE_LANG_SANSKRIT    0x4f
#define PE_LANG_SINDHI      0x59
#define PE_LANG_SLOVAK      0x1b
#define PE_LANG_SLOVENIAN   0x24
#define PE_LANG_SPANISH     0x0a
#define PE_LANG_SWAHILI     0x41
#define PE_LANG_SWEDISH     0x1d
#define PE_LANG_SYRIAC      0x5a
#define PE_LANG_TAMIL       0x49
#define PE_LANG_TATAR       0x44
#define PE_LANG_TELUGU      0x4a
#define PE_LANG_THAI        0x1e
#define PE_LANG_TURKISH     0x1f
#define PE_LANG_UKRAINIAN   0x22
#define PE_LANG_URDU        0x20
#define PE_LANG_UZBEK       0x43
#define PE_LANG_VIETNAMESE  0x2a

//----------------------------------------------------------------------

#define PE_NODE "$ PE header" // netnode name for PE header
                              // value()        -> peheader_t
                              // altval(segnum) -> s->startEA
#define PE_ALT_DBG_FPOS   nodeidx_t(-1)  // altval() -> translated fpos of debuginfo
#define PE_ALT_IMAGEBASE  nodeidx_t(-2)  // altval() -> loading address (usually pe.imagebase)
#define PE_ALT_PEHDR_OFF  nodeidx_t(-3)  // altval() -> offset of PE header
#define PE_ALT_NEFLAGS    nodeidx_t(-4)  // altval() -> neflags
#define PE_ALT_TDS_LOADED nodeidx_t(-5)  // altval() -> tds already loaded(1) or invalid(-1)
#define PE_ALT_PSXDLL     nodeidx_t(-6)  // altval() -> if POSIX(x86) imports from PSXDLL netnode
                              // supval(segnum) -> pesection_t
                              // blob(0, PE_NODE_RELOC)  -> relocation info
#define PE_NODE_RELOC 'r'

#define TDS_AT_PE_LOAD  0x100AD  // 100==L => LOAD. Magic constant to pass to
                                // the TDS plugin

const char *get_pe_machine_name(uint16 machine);
void print_pe_flags(uint16 flags);

#pragma pack(pop)
#endif
