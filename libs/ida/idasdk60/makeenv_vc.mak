
# Create configuration files

!include "allmake.mak"

all:    w32vs.cfg$(CFGSUF) w64vs.cfg$(CFGSUF) wx64vs.cfg$(CFGSUF) \
        cearm.cfg$(CFGSUF)

w32vs.cfg$(CFGSUF):     __vc.cfg
        $(CP) __vc.cfg $@
        echo /Foobj\vc.w32$(OBJDIRSUF)\ >>$@
!ifdef NDEBUG
        @echo /DNDEBUG >>$@
!else
        @echo /GS >>$@
!endif

w64vs.cfg$(CFGSUF):     __vc.cfg
        $(CP) __vc.cfg $@
        echo /Foobj\vc.w64$(OBJDIRSUF)\ >>$@
        @echo /D__EA64__ >>$@
!ifdef NDEBUG
        @echo /DNDEBUG >>$@
!else
        @echo /GS >>$@
!endif

wx64vs.cfg$(CFGSUF):    __vc.cfg
        $(CP) __vc.cfg $@
        echo /Foobj\vc.x64$(OBJDIRSUF)\ >>$@
        @echo /D__EA64__ >>$@
        @echo /D__X64__ >>$@
!ifdef NDEBUG
        @echo /DNDEBUG >>$@
!else
        @echo /GS >>$@
!endif

__vc.cfg: makeenv_vc.mak allmake.mak defaults.mk
        $(CP) &&|
#this file is generated by make, don't edit
/nologo
/I$(IDA)include
/I$(MSVCDIR)Include
!ifndef VC_WITHOUT_PSDK
/I$(MSVCDIR)PlatformSDK\Include
!elif defined(MSSDK)
/I$(MSSDK)Include
!endif
!ifdef VC_USE_CPUS
#       Use up to 'n' processes for compilation (VC9 or higher)
/MP$(VC_USE_CPUS)
!endif
#       Optimize code for Windows application
/GA
#       Merge duplicate strings
/GF
#       Exception handling (C++ and SEH)
/EHa
#       Enable RTTI
/GR
#	Separate function's for linker
/Gy
#       No standard stack frame
/Oy
#	Enable intrinsic functions
/Oi
/DMAXSTR=1024
/DNO_TV_STREAMS
-DNO_OBSOLETE_FUNCS
/D__VC__
/D__NT__
#       show full paths
/FC
#       All warnings on
/Wall
#       warning C4018: '>=' : signed/unsigned mismatch
/wd4018
#       warning C4061: enumerator 'xxx' in switch of enum 'yyy' is not explicitly handled by a case label
/wd4061
#       warning C4121: 'xxx': alignment of a member was sensitive to packing
/wd4121
#       warning C4127: conditional expression is constant
/wd4127
#       warning C4146: unary minus operator applied to unsigned type, result still unsigned
/wd4146
#       warning C4200: nonstandard extension used: zero-sized array in struct/union
/wd4200
#       warning C4201: nonstandard extension used : nameless struct/union
/wd4201
#       warning C4239: nonstandard extension used : non-const refernece=>lvalue
/wd4239
#       warning C4242: 'initializing' : conversion from 'a' to 'b', possible loss of data
/wd4242
#       warning C4244: 'xxx' : conversion from 'a' to 'b', possible loss of data
/wd4244
#       warning C4245: 'xxx' : conversion from 'a' to 'b', signed/unsigned mismatch
/wd4245
#       warning C4267: 'xxx' : conversion from 'size_t' to 'b', possible loss of data
/wd4267
#       warning C4310: cast truncates constant value
/wd4310
#       warning C4324: 'xxx' : structure was padded due to __declspec(align())
/wd4324
#       warning C4334: 'xx' : result of 32-bit shift implicitly converted to 64 bits (was 64-bit shift intended?)
/wd4334
#       warning C4355: 'this' : used in base member initializer list
/wd4355
#       warning C4365: 'xx' : signed/unsigned mismatch (= or return)
/wd4365
#       warning C4366: The result of the unary '& operator may be unaligned
/wd4366
#       warning C4371: 'xxx' : layout of class may have changed from a previous version of the compiler due to better packing of member 'xxx'
/wd4371
#       warning C4389: '!=' : signed/unsigned mismatch
/wd4389
#       warning C4480: '!=' :  nonstandard extension used: ....
/wd4480
#       warning C4512: 'xxx' : assignment operator could not be generated
/wd4512
#       warning C4514: 'xxx' : unreferenced inline function has been removed
/wd4514
#       warning C4548: expression before comma has no effect; expected expression with side-effect
/wd4548
#       warning C4611: interaction between '_setjmp' and C++ object destruction is non-portable
/wd4611
#       warning C4619: pragma warning : there is no warning number 'xxx'
/wd4619
#       warning C4625: 'xxx' : copy constructor could not be generated because a base class copy constructor is inaccessible
/wd4625
#       warning C4626: 'xxx' : assignment operator could not be generated because a base class assignment operator is inaccessible
/wd4626
#       warning C4640: 'p' : construction of local static object is not thread-safe
/wd4640
#       warning C4668: 'xxx' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
/wd4668
#       warning C4686: 'xxx' : possible change in behavior, change in UDT return calling convention
/wd4686
!ifdef DEBUG
#       warning C4701: 'xxx' : potentially uninitialized local variable
/wd4701
!endif
#       warning C4710: 'xxx' : function not inlined
/wd4710
#       warning C4711: 'xxx' : function select for automatic inline expansion
/wd4711
#       warning C4738: storing 32-bit float result in memory, possible loss of performance
/wd4738
#       warning C4800: 'BOOL' : forcing value to bool 'true' or 'false' (performance warning)
/wd4800
#       warning C4820: 'xxx' : 'x' bytes padding added after member 'xxx'
/wd4820
#       warning C4917: 'xxx' : a GUID can only be associated with a class, interface or namespace
/wd4917
#       warning C4986: 'operator new[]': exception specification does not match previous declaration entered the game.
/wd4986
#       warning C4996: 'xxx' was declared deprecated
/wd4996
#
| $@


cearm.cfg$(CFGSUF): makeenv_vc.mak allmake.mak defaults.mk
        $(CP) &&|
#this file is generated by make, don't edit
/I"$(IDA)include"
/I"$(MSVCARMDIR)Include"
/I"$(ARMSDK)Include"
/nologo
#       Merge duplicate strings
/GF
#       Enable RTTI
/GR
#       No standard stack frame
/Oy
#       Maximum optimization
/Ox
#       All warnings on
/W2
#       Exception handling (C++ and SEH)
/EHa
#	Separate functions for linker
/Gy
#       show full paths
/FC
/DMAXSTR=1024
/DNO_TV_STREAMS
/D__NT__
/DARM
/DUNDER_CE
/DUNICODE
/D_WIN32_WCE=0x420
| $@
        echo /Foobj\armc.e32$(OBJDIRSUF)\ >>$@
