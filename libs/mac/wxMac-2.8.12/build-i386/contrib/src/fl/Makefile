# =========================================================================
#     This makefile was generated by
#     Bakefile 0.2.9 (http://www.bakefile.org)
#     Do not modify, all changes will be overwritten!
# =========================================================================




prefix = /usr/local
exec_prefix = ${prefix}
datarootdir = @datarootdir@
INSTALL = /usr/bin/install -c
SHARED_LD_CXX = ${CXX} -dynamiclib -single_module -headerpad_max_install_names -o
LIBEXT = .a
LIBPREFIX = lib
SO_SUFFIX = dylib
DLLIMP_SUFFIX = dylib
LN_S = ln -s
WINDRES = 
PIC_FLAG = -dynamic -fPIC -DPIC
SONAME_FLAG = 
STRIP = strip
INSTALL_PROGRAM = cp -fp
INSTALL_DATA = cp -fp
INSTALL_DIR = $(INSTALL) -d
ICC_PCH_USE_SWITCH = 
BK_DEPS = /Users/dquist/Downloads/wxMac-2.8.12/build-i386/bk-deps
BK_MAKE_PCH = /Users/dquist/Downloads/wxMac-2.8.12/build-i386/bk-make-pch
srcdir = ../../../../contrib/src/fl
top_srcdir = ../../../..
libdir = ${exec_prefix}/lib
includedir = ${prefix}/include
DLLPREFIX = lib
LIBS = -lz -lpthread -liconv
AR = ar
AROPTIONS = rcu
RANLIB = ranlib
CXX = g++ -isysroot /Developer/SDKs/MacOSX10.6.sdk -mmacosx-version-min=10.6
CXXFLAGS = -DWX_PRECOMP -Wall -Wundef -Wno-ctor-dtor-privacy -O2 -fno-strict-aliasing -arch i386 -fno-common
CPPFLAGS = -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES -I${wx_top_builddir}/lib/wx/include/mac-ansi-release-2.8 -I${top_srcdir}/include -fpascal-strings -I${top_srcdir}/src/mac/carbon/morefilex -I/Developer/Headers/FlatCarbon -arch i386
LDFLAGS =  -arch i386 -framework IOKit -framework Carbon -framework Cocoa -framework System -framework QuickTime -framework OpenGL -framework AGL 
VENDOR = custom
WX_FLAVOUR = 
WX_LIB_FLAVOUR = 
TOOLKIT = MAC
TOOLKIT_LOWERCASE = mac
TOOLKIT_VERSION = 
TOOLCHAIN_FULLNAME = mac-ansi-release-2.8
EXTRALIBS =  -arch i386 -framework IOKit -framework Carbon -framework Cocoa -framework System -framework QuickTime -framework OpenGL -framework AGL  -lz -lpthread -liconv 
EXTRALIBS_GUI = -framework WebKit
HOST_SUFFIX = 
wx_top_builddir = /Users/dquist/Downloads/wxMac-2.8.12/build-i386

### Variables: ###

DESTDIR = 
WX_RELEASE = 2.8
WX_RELEASE_NODOT = 28
LIBDIRNAME = $(wx_top_builddir)/lib
FLDLL_CXXFLAGS = $(__fldll_PCH_INC) -D__WX$(TOOLKIT)__ $(__WXUNIV_DEFINE_p) \
	$(__EXCEPTIONS_DEFINE_p) $(__RTTI_DEFINE_p) $(__THREAD_DEFINE_p) \
	-DWXBUILDING -I$(srcdir)/../../include -DWXUSINGDLL -DWXMAKINGDLL_FL \
	$(PIC_FLAG) $(CPPFLAGS) $(CXXFLAGS)
FLDLL_OBJECTS =  \
	$(__fldll___win32rc) \
	fldll_antiflickpl.o \
	fldll_bardragpl.o \
	fldll_barhintspl.o \
	fldll_cbcustom.o \
	fldll_controlbar.o \
	fldll_dyntbar.o \
	fldll_dyntbarhnd.o \
	fldll_frmview.o \
	fldll_garbagec.o \
	fldll_gcupdatesmgr.o \
	fldll_hintanimpl.o \
	fldll_newbmpbtn.o \
	fldll_panedrawpl.o \
	fldll_rowdragpl.o \
	fldll_rowlayoutpl.o \
	fldll_toolwnd.o \
	fldll_updatesmgr.o
FLDLL_ODEP =  $(_____pch_wxprec_fldll_wx_wxprec_h_gch___depname)
FLLIB_CXXFLAGS = $(__fllib_PCH_INC) -D__WX$(TOOLKIT)__ $(__WXUNIV_DEFINE_p) \
	$(__EXCEPTIONS_DEFINE_p) $(__RTTI_DEFINE_p) $(__THREAD_DEFINE_p) \
	-DWXBUILDING -I$(srcdir)/../../include $(CPPFLAGS) $(CXXFLAGS)
FLLIB_OBJECTS =  \
	fllib_antiflickpl.o \
	fllib_bardragpl.o \
	fllib_barhintspl.o \
	fllib_cbcustom.o \
	fllib_controlbar.o \
	fllib_dyntbar.o \
	fllib_dyntbarhnd.o \
	fllib_frmview.o \
	fllib_garbagec.o \
	fllib_gcupdatesmgr.o \
	fllib_hintanimpl.o \
	fllib_newbmpbtn.o \
	fllib_panedrawpl.o \
	fllib_rowdragpl.o \
	fllib_rowlayoutpl.o \
	fllib_toolwnd.o \
	fllib_updatesmgr.o
FLLIB_ODEP =  $(_____pch_wxprec_fllib_wx_wxprec_h_gch___depname)

### Conditionally set variables: ###

#CXXC = $(CXX)
CXXC = $(BK_DEPS) $(CXX)
WXMACVERSION_CMD = \
	-compatibility_version 9.0 -current_version 9.0
#PORTNAME = base
PORTNAME = $(TOOLKIT_LOWERCASE)$(TOOLKIT_VERSION)
WXBASEPORT = _carbon
#WXCOMPILER = _gcc
#VENDORTAG = _$(VENDOR)
#VENDORTAG = 
#WXDEBUGFLAG = d
#WXDEBUGFLAG = d
#WXUNICODEFLAG = u
#WXUNIVNAME = univ
WXDLLNAMEPREFIXGUI = wx_$(PORTNAME)$(WXUNIVNAME)
#WXDLLNAMEPREFIXGUI = \
#	wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)
WXDLLVERSIONTAG = -$(WX_RELEASE)
#WXDLLVERSIONTAG = 
EXTRALIBS_FOR_BASE = $(EXTRALIBS)
#EXTRALIBS_FOR_BASE = $(EXTRALIBS) $(EXTRALIBS_GUI)
EXTRALIBS_FOR_GUI = $(EXTRALIBS_GUI)
#EXTRALIBS_FOR_GUI = 
COND_SHARED_1___fldll___depname = \
	$(LIBDIRNAME)/$(DLLPREFIX)$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG)$(__fldll___targetsuf3)
__fldll___depname = $(COND_SHARED_1___fldll___depname)
#__WXUNIV_DEFINE_p_1 = --define __WXUNIVERSAL__
#__EXCEPTIONS_DEFINE_p_1 = --define wxNO_EXCEPTIONS
#__RTTI_DEFINE_p_1 = --define wxNO_RTTI
#__THREAD_DEFINE_p_1 = --define wxNO_THREADS
__install_fldll___depname = install_fldll
__uninstall_fldll___depname = uninstall_fldll
COND_PLATFORM_MACOSX_1___fldll___macinstnamecmd = -install_name \
	$(libdir)/$(DLLPREFIX)$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG)$(__fldll___targetsuf2)
__fldll___macinstnamecmd = $(COND_PLATFORM_MACOSX_1___fldll___macinstnamecmd)
COND_PLATFORM_OS2_1___fldll___importlib = -import \
	$(LIBDIRNAME)/$(LIBPREFIX)wx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl-$(WX_RELEASE)$(HOST_SUFFIX).$(DLLIMP_SUFFIX)
#__fldll___importlib = $(COND_PLATFORM_OS2_1___fldll___importlib)
COND_WINDOWS_IMPLIB_1___fldll___importlib = \
	-Wl,--out-implib=$(LIBDIRNAME)/$(LIBPREFIX)wx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl-$(WX_RELEASE)$(HOST_SUFFIX).$(DLLIMP_SUFFIX)
#__fldll___importlib = $(COND_WINDOWS_IMPLIB_1___fldll___importlib)
__fldll_PCH_INC = -I./.pch/wxprec_fldll
#__fldll_PCH_INC = $(ICC_PCH_USE_SWITCH) \
#	./.pch/wxprec_fldll/wx/wxprec.h.gch
_____pch_wxprec_fldll_wx_wxprec_h_gch___depname \
	= ./.pch/wxprec_fldll/wx/wxprec.h.gch
#__fldll___targetsuf2 \
#	= .$(SO_SUFFIX).0
__fldll___targetsuf2 \
	= .0.$(SO_SUFFIX)
#__fldll___targetsuf2 = .$(SO_SUFFIX)
#__fldll___targetsuf3 \
#	= \
#	.$(SO_SUFFIX).0.8.0
__fldll___targetsuf3 \
	= .0.8.0.$(SO_SUFFIX)
#__fldll___targetsuf3 \
#	= .$(SO_SUFFIX).0
#__fldll___targetsuf3 \
#	= -0.$(SO_SUFFIX)
#__fldll___targetsuf3 = .$(SO_SUFFIX)
COND_USE_SOVERLINUX_1___fldll___soname_flags = \
	$(SONAME_FLAG)$(DLLPREFIX)$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG)$(__fldll___targetsuf2)
#__fldll___soname_flags = $(COND_USE_SOVERLINUX_1___fldll___soname_flags)
COND_USE_SOVERSOLARIS_1___fldll___soname_flags = \
	$(SONAME_FLAG)$(DLLPREFIX)$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG)$(__fldll___targetsuf3)
#__fldll___soname_flags = $(COND_USE_SOVERSOLARIS_1___fldll___soname_flags)
COND_USE_SOTWOSYMLINKS_1___fldll___so_symlinks_cmd = (cd $(LIBDIRNAME)/; rm -f \
	$(LIBPREFIX)wx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl-$(WX_RELEASE)$(HOST_SUFFIX).$(DLLIMP_SUFFIX) \
	$(DLLPREFIX)$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG)$(__fldll___targetsuf2); \
	$(LN_S) \
	$(DLLPREFIX)$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG)$(__fldll___targetsuf3) \
	$(DLLPREFIX)$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG)$(__fldll___targetsuf2); \
	$(LN_S) \
	$(DLLPREFIX)$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG)$(__fldll___targetsuf2) \
	$(LIBPREFIX)wx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl-$(WX_RELEASE)$(HOST_SUFFIX).$(DLLIMP_SUFFIX))
__fldll___so_symlinks_cmd = $(COND_USE_SOTWOSYMLINKS_1___fldll___so_symlinks_cmd)
COND_USE_SOVERSOLARIS_1___fldll___so_symlinks_cmd = (cd $(LIBDIRNAME)/; rm -f \
	$(LIBPREFIX)wx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl-$(WX_RELEASE)$(HOST_SUFFIX).$(DLLIMP_SUFFIX); \
	$(LN_S) \
	$(DLLPREFIX)$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG)$(__fldll___targetsuf3) \
	$(LIBPREFIX)wx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl-$(WX_RELEASE)$(HOST_SUFFIX).$(DLLIMP_SUFFIX))
#__fldll___so_symlinks_cmd = $(COND_USE_SOVERSOLARIS_1___fldll___so_symlinks_cmd)
COND_USE_SOTWOSYMLINKS_1___fldll___so_symlinks_inst_cmd = rm -f \
	$(LIBPREFIX)wx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl-$(WX_RELEASE)$(HOST_SUFFIX).$(DLLIMP_SUFFIX) \
	$(DLLPREFIX)$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG)$(__fldll___targetsuf2); \
	$(LN_S) \
	$(DLLPREFIX)$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG)$(__fldll___targetsuf3) \
	$(DLLPREFIX)$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG)$(__fldll___targetsuf2); \
	$(LN_S) \
	$(DLLPREFIX)$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG)$(__fldll___targetsuf2) \
	$(LIBPREFIX)wx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl-$(WX_RELEASE)$(HOST_SUFFIX).$(DLLIMP_SUFFIX)
__fldll___so_symlinks_inst_cmd = $(COND_USE_SOTWOSYMLINKS_1___fldll___so_symlinks_inst_cmd)
COND_USE_SOVERSOLARIS_1___fldll___so_symlinks_inst_cmd = rm -f \
	$(LIBPREFIX)wx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl-$(WX_RELEASE)$(HOST_SUFFIX).$(DLLIMP_SUFFIX); \
	$(LN_S) \
	$(DLLPREFIX)$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG)$(__fldll___targetsuf3) \
	$(LIBPREFIX)wx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl-$(WX_RELEASE)$(HOST_SUFFIX).$(DLLIMP_SUFFIX);
#__fldll___so_symlinks_inst_cmd = $(COND_USE_SOVERSOLARIS_1___fldll___so_symlinks_inst_cmd)
COND_USE_SOTWOSYMLINKS_1___fldll___so_symlinks_uninst_cmd = rm -f \
	$(DLLPREFIX)$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG)$(__fldll___targetsuf2) \
	$(LIBPREFIX)wx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl-$(WX_RELEASE)$(HOST_SUFFIX).$(DLLIMP_SUFFIX)
__fldll___so_symlinks_uninst_cmd = $(COND_USE_SOTWOSYMLINKS_1___fldll___so_symlinks_uninst_cmd)
COND_USE_SOVERSOLARIS_1___fldll___so_symlinks_uninst_cmd = rm -f \
	$(LIBPREFIX)wx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl-$(WX_RELEASE)$(HOST_SUFFIX).$(DLLIMP_SUFFIX)
#__fldll___so_symlinks_uninst_cmd = $(COND_USE_SOVERSOLARIS_1___fldll___so_symlinks_uninst_cmd)
#__RCDEFDIR_p = --include-dir \
#	$(LIBDIRNAME)/wx/include/$(TOOLCHAIN_FULLNAME)
COND_MONOLITHIC_1___WXLIB_MONO_p = \
	-lwx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
#__WXLIB_MONO_p = $(COND_MONOLITHIC_1___WXLIB_MONO_p)
__LIB_TIFF_p \
	= \
	-lwxtiff$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
__LIB_JPEG_p \
	= \
	-lwxjpeg$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
__LIB_PNG_p \
	= \
	-lwxpng$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
#__LIB_ZLIB_p = \
#	-lwxzlib$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
#__LIB_ODBC_p = \
#	-lwxodbc$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
COND_wxUSE_REGEX_builtin___LIB_REGEX_p = \
	-lwxregex$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
#__LIB_REGEX_p = $(COND_wxUSE_REGEX_builtin___LIB_REGEX_p)
#__LIB_EXPAT_p = \
#	-lwxexpat$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
#__fldll___win32rc = fldll_version_rc.o
COND_MONOLITHIC_0___WXLIB_CORE_p = \
	-lwx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_core-$(WX_RELEASE)$(HOST_SUFFIX)
__WXLIB_CORE_p = $(COND_MONOLITHIC_0___WXLIB_CORE_p)
COND_MONOLITHIC_0___WXLIB_BASE_p = \
	-lwx_base$(WXBASEPORT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
__WXLIB_BASE_p = $(COND_MONOLITHIC_0___WXLIB_BASE_p)
COND_SHARED_0___fllib___depname = \
	$(LIBDIRNAME)/$(LIBPREFIX)wx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl-$(WX_RELEASE)$(HOST_SUFFIX)$(LIBEXT)
#__fllib___depname = $(COND_SHARED_0___fllib___depname)
#__install_fllib___depname = install_fllib
#__uninstall_fllib___depname = uninstall_fllib
__fllib_PCH_INC = -I./.pch/wxprec_fllib
#__fllib_PCH_INC = $(ICC_PCH_USE_SWITCH) \
#	./.pch/wxprec_fllib/wx/wxprec.h.gch
_____pch_wxprec_fllib_wx_wxprec_h_gch___depname \
	= ./.pch/wxprec_fllib/wx/wxprec.h.gch
#__WXUNIV_DEFINE_p = -D__WXUNIVERSAL__
#__EXCEPTIONS_DEFINE_p = -DwxNO_EXCEPTIONS
#__RTTI_DEFINE_p = -DwxNO_RTTI
#__THREAD_DEFINE_p = -DwxNO_THREADS

### Targets: ###

all: $(__fldll___depname) $(__fllib___depname)

install: $(__install_fldll___depname) $(__install_fllib___depname)
	$(INSTALL_DIR) $(DESTDIR)$(includedir)/wx-$(WX_RELEASE)$(WX_FLAVOUR)
	for f in wx/fl/antiflickpl.h wx/fl/bardragpl.h wx/fl/barhintspl.h wx/fl/cbcustom.h wx/fl/controlbar.h wx/fl/dynbarhnd.h wx/fl/dyntbar.h wx/fl/dyntbarhnd.h wx/fl/fldefs.h wx/fl/frmview.h wx/fl/garbagec.h wx/fl/gcupdatesmgr.h wx/fl/hintanimpl.h wx/fl/newbmpbtn.h wx/fl/panedrawpl.h wx/fl/rowdragpl.h wx/fl/rowlayoutpl.h wx/fl/toolwnd.h wx/fl/updatesmgr.h; do \
	if test ! -d $(DESTDIR)$(includedir)/wx-$(WX_RELEASE)$(WX_FLAVOUR)/`dirname $$f` ; then \
	$(INSTALL_DIR) $(DESTDIR)$(includedir)/wx-$(WX_RELEASE)$(WX_FLAVOUR)/`dirname $$f`; \
	fi; \
	$(INSTALL_DATA) $(srcdir)/../../include/$$f $(DESTDIR)$(includedir)/wx-$(WX_RELEASE)$(WX_FLAVOUR)/$$f; \
	done

uninstall: $(__uninstall_fldll___depname) $(__uninstall_fllib___depname)
	for f in wx/fl/antiflickpl.h wx/fl/bardragpl.h wx/fl/barhintspl.h wx/fl/cbcustom.h wx/fl/controlbar.h wx/fl/dynbarhnd.h wx/fl/dyntbar.h wx/fl/dyntbarhnd.h wx/fl/fldefs.h wx/fl/frmview.h wx/fl/garbagec.h wx/fl/gcupdatesmgr.h wx/fl/hintanimpl.h wx/fl/newbmpbtn.h wx/fl/panedrawpl.h wx/fl/rowdragpl.h wx/fl/rowlayoutpl.h wx/fl/toolwnd.h wx/fl/updatesmgr.h; do \
	rm -f $(DESTDIR)$(includedir)/wx-$(WX_RELEASE)$(WX_FLAVOUR)/$$f; \
	done

install-strip: install
	$(STRIP) $(DESTDIR)$(libdir)/$(DLLPREFIX)$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG)$(__fldll___targetsuf3)

clean: 
	rm -rf ./.deps ./.pch
	rm -f ./*.o
	rm -f $(LIBDIRNAME)/$(DLLPREFIX)$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG)$(__fldll___targetsuf3)
	rm -f $(LIBDIRNAME)/$(LIBPREFIX)wx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl-$(WX_RELEASE)$(HOST_SUFFIX).$(DLLIMP_SUFFIX)
	rm -f $(LIBDIRNAME)/$(LIBPREFIX)wx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl-$(WX_RELEASE)$(HOST_SUFFIX).$(DLLIMP_SUFFIX) $(LIBDIRNAME)/$(DLLPREFIX)$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG)$(__fldll___targetsuf2)
	rm -f $(LIBDIRNAME)/$(LIBPREFIX)wx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl-$(WX_RELEASE)$(HOST_SUFFIX)$(LIBEXT)

distclean: clean
	rm -f config.cache config.log config.status bk-deps bk-make-pch shared-ld-sh Makefile

$(LIBDIRNAME)/$(DLLPREFIX)$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG)$(__fldll___targetsuf3): $(FLDLL_OBJECTS) $(__fldll___win32rc)
	$(SHARED_LD_CXX) $@ $(FLDLL_OBJECTS)    -L$(LIBDIRNAME) $(__fldll___macinstnamecmd) $(__fldll___importlib) $(__fldll___soname_flags) $(WXMACVERSION_CMD) $(LDFLAGS)  $(__WXLIB_MONO_p) $(__LIB_TIFF_p) $(__LIB_JPEG_p) $(__LIB_PNG_p) $(EXTRALIBS_FOR_GUI) $(__LIB_ZLIB_p) $(__LIB_ODBC_p) $(__LIB_REGEX_p) $(__LIB_EXPAT_p) $(EXTRALIBS_FOR_BASE) $(__WXLIB_CORE_p)  $(__WXLIB_BASE_p)  $(LIBS)
	
	$(__fldll___so_symlinks_cmd)

install_fldll: $(__fldll___depname)
	$(INSTALL_DIR) $(DESTDIR)$(libdir)
	$(INSTALL_DATA) $(LIBDIRNAME)/$(LIBPREFIX)wx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl-$(WX_RELEASE)$(HOST_SUFFIX).$(DLLIMP_SUFFIX) $(DESTDIR)$(libdir)
	$(INSTALL_PROGRAM) $(LIBDIRNAME)/$(DLLPREFIX)$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG)$(__fldll___targetsuf3) $(DESTDIR)$(libdir)
	(cd $(DESTDIR)$(libdir) ; $(__fldll___so_symlinks_inst_cmd))

uninstall_fldll: 
	rm -f $(DESTDIR)$(libdir)/$(LIBPREFIX)wx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl-$(WX_RELEASE)$(HOST_SUFFIX).$(DLLIMP_SUFFIX)
	rm -f $(DESTDIR)$(libdir)/$(DLLPREFIX)$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG)$(__fldll___targetsuf3)
	(cd $(DESTDIR)$(libdir) ; $(__fldll___so_symlinks_uninst_cmd))

./.pch/wxprec_fldll/wx/wxprec.h.gch: 
	$(BK_MAKE_PCH) ./.pch/wxprec_fldll/wx/wxprec.h.gch wx/wxprec.h $(CXX) $(FLDLL_CXXFLAGS)

#$(LIBDIRNAME)/$(LIBPREFIX)wx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl-$(WX_RELEASE)$(HOST_SUFFIX)$(LIBEXT): $(FLLIB_OBJECTS)
#	rm -f $@
#	$(AR) $(AROPTIONS) $@ $(FLLIB_OBJECTS)
#	$(RANLIB) $@

#install_fllib: $(__fllib___depname)
#	$(INSTALL_DIR) $(DESTDIR)$(libdir)
#	$(INSTALL_DATA) $(LIBDIRNAME)/$(LIBPREFIX)wx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl-$(WX_RELEASE)$(HOST_SUFFIX)$(LIBEXT) $(DESTDIR)$(libdir)

#uninstall_fllib: 
#	rm -f $(DESTDIR)$(libdir)/$(LIBPREFIX)wx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl-$(WX_RELEASE)$(HOST_SUFFIX)$(LIBEXT)

./.pch/wxprec_fllib/wx/wxprec.h.gch: 
	$(BK_MAKE_PCH) ./.pch/wxprec_fllib/wx/wxprec.h.gch wx/wxprec.h $(CXX) $(FLLIB_CXXFLAGS)

fldll_version_rc.o: $(srcdir)/../../../src/msw/version.rc $(FLDLL_ODEP)
	$(WINDRES) -i$< -o$@    --define __WX$(TOOLKIT)__ $(__WXUNIV_DEFINE_p_1)   $(__EXCEPTIONS_DEFINE_p_1) $(__RTTI_DEFINE_p_1) $(__THREAD_DEFINE_p_1)   --define WXBUILDING --define WXDLLNAME=$(WXDLLNAMEPREFIXGUI)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_fl$(WXCOMPILER)$(VENDORTAG)$(WXDLLVERSIONTAG) $(__RCDEFDIR_p) --include-dir $(top_srcdir)/include --include-dir $(srcdir)/../../include --define WXUSINGDLL --define WXMAKINGDLL_FL

fldll_antiflickpl.o: $(srcdir)/antiflickpl.cpp $(FLDLL_ODEP)
	$(CXXC) -c -o $@ $(FLDLL_CXXFLAGS) $(srcdir)/antiflickpl.cpp

fldll_bardragpl.o: $(srcdir)/bardragpl.cpp $(FLDLL_ODEP)
	$(CXXC) -c -o $@ $(FLDLL_CXXFLAGS) $(srcdir)/bardragpl.cpp

fldll_barhintspl.o: $(srcdir)/barhintspl.cpp $(FLDLL_ODEP)
	$(CXXC) -c -o $@ $(FLDLL_CXXFLAGS) $(srcdir)/barhintspl.cpp

fldll_cbcustom.o: $(srcdir)/cbcustom.cpp $(FLDLL_ODEP)
	$(CXXC) -c -o $@ $(FLDLL_CXXFLAGS) $(srcdir)/cbcustom.cpp

fldll_controlbar.o: $(srcdir)/controlbar.cpp $(FLDLL_ODEP)
	$(CXXC) -c -o $@ $(FLDLL_CXXFLAGS) $(srcdir)/controlbar.cpp

fldll_dyntbar.o: $(srcdir)/dyntbar.cpp $(FLDLL_ODEP)
	$(CXXC) -c -o $@ $(FLDLL_CXXFLAGS) $(srcdir)/dyntbar.cpp

fldll_dyntbarhnd.o: $(srcdir)/dyntbarhnd.cpp $(FLDLL_ODEP)
	$(CXXC) -c -o $@ $(FLDLL_CXXFLAGS) $(srcdir)/dyntbarhnd.cpp

fldll_frmview.o: $(srcdir)/frmview.cpp $(FLDLL_ODEP)
	$(CXXC) -c -o $@ $(FLDLL_CXXFLAGS) $(srcdir)/frmview.cpp

fldll_garbagec.o: $(srcdir)/garbagec.cpp $(FLDLL_ODEP)
	$(CXXC) -c -o $@ $(FLDLL_CXXFLAGS) $(srcdir)/garbagec.cpp

fldll_gcupdatesmgr.o: $(srcdir)/gcupdatesmgr.cpp $(FLDLL_ODEP)
	$(CXXC) -c -o $@ $(FLDLL_CXXFLAGS) $(srcdir)/gcupdatesmgr.cpp

fldll_hintanimpl.o: $(srcdir)/hintanimpl.cpp $(FLDLL_ODEP)
	$(CXXC) -c -o $@ $(FLDLL_CXXFLAGS) $(srcdir)/hintanimpl.cpp

fldll_newbmpbtn.o: $(srcdir)/newbmpbtn.cpp $(FLDLL_ODEP)
	$(CXXC) -c -o $@ $(FLDLL_CXXFLAGS) $(srcdir)/newbmpbtn.cpp

fldll_panedrawpl.o: $(srcdir)/panedrawpl.cpp $(FLDLL_ODEP)
	$(CXXC) -c -o $@ $(FLDLL_CXXFLAGS) $(srcdir)/panedrawpl.cpp

fldll_rowdragpl.o: $(srcdir)/rowdragpl.cpp $(FLDLL_ODEP)
	$(CXXC) -c -o $@ $(FLDLL_CXXFLAGS) $(srcdir)/rowdragpl.cpp

fldll_rowlayoutpl.o: $(srcdir)/rowlayoutpl.cpp $(FLDLL_ODEP)
	$(CXXC) -c -o $@ $(FLDLL_CXXFLAGS) $(srcdir)/rowlayoutpl.cpp

fldll_toolwnd.o: $(srcdir)/toolwnd.cpp $(FLDLL_ODEP)
	$(CXXC) -c -o $@ $(FLDLL_CXXFLAGS) $(srcdir)/toolwnd.cpp

fldll_updatesmgr.o: $(srcdir)/updatesmgr.cpp $(FLDLL_ODEP)
	$(CXXC) -c -o $@ $(FLDLL_CXXFLAGS) $(srcdir)/updatesmgr.cpp

fllib_antiflickpl.o: $(srcdir)/antiflickpl.cpp $(FLLIB_ODEP)
	$(CXXC) -c -o $@ $(FLLIB_CXXFLAGS) $(srcdir)/antiflickpl.cpp

fllib_bardragpl.o: $(srcdir)/bardragpl.cpp $(FLLIB_ODEP)
	$(CXXC) -c -o $@ $(FLLIB_CXXFLAGS) $(srcdir)/bardragpl.cpp

fllib_barhintspl.o: $(srcdir)/barhintspl.cpp $(FLLIB_ODEP)
	$(CXXC) -c -o $@ $(FLLIB_CXXFLAGS) $(srcdir)/barhintspl.cpp

fllib_cbcustom.o: $(srcdir)/cbcustom.cpp $(FLLIB_ODEP)
	$(CXXC) -c -o $@ $(FLLIB_CXXFLAGS) $(srcdir)/cbcustom.cpp

fllib_controlbar.o: $(srcdir)/controlbar.cpp $(FLLIB_ODEP)
	$(CXXC) -c -o $@ $(FLLIB_CXXFLAGS) $(srcdir)/controlbar.cpp

fllib_dyntbar.o: $(srcdir)/dyntbar.cpp $(FLLIB_ODEP)
	$(CXXC) -c -o $@ $(FLLIB_CXXFLAGS) $(srcdir)/dyntbar.cpp

fllib_dyntbarhnd.o: $(srcdir)/dyntbarhnd.cpp $(FLLIB_ODEP)
	$(CXXC) -c -o $@ $(FLLIB_CXXFLAGS) $(srcdir)/dyntbarhnd.cpp

fllib_frmview.o: $(srcdir)/frmview.cpp $(FLLIB_ODEP)
	$(CXXC) -c -o $@ $(FLLIB_CXXFLAGS) $(srcdir)/frmview.cpp

fllib_garbagec.o: $(srcdir)/garbagec.cpp $(FLLIB_ODEP)
	$(CXXC) -c -o $@ $(FLLIB_CXXFLAGS) $(srcdir)/garbagec.cpp

fllib_gcupdatesmgr.o: $(srcdir)/gcupdatesmgr.cpp $(FLLIB_ODEP)
	$(CXXC) -c -o $@ $(FLLIB_CXXFLAGS) $(srcdir)/gcupdatesmgr.cpp

fllib_hintanimpl.o: $(srcdir)/hintanimpl.cpp $(FLLIB_ODEP)
	$(CXXC) -c -o $@ $(FLLIB_CXXFLAGS) $(srcdir)/hintanimpl.cpp

fllib_newbmpbtn.o: $(srcdir)/newbmpbtn.cpp $(FLLIB_ODEP)
	$(CXXC) -c -o $@ $(FLLIB_CXXFLAGS) $(srcdir)/newbmpbtn.cpp

fllib_panedrawpl.o: $(srcdir)/panedrawpl.cpp $(FLLIB_ODEP)
	$(CXXC) -c -o $@ $(FLLIB_CXXFLAGS) $(srcdir)/panedrawpl.cpp

fllib_rowdragpl.o: $(srcdir)/rowdragpl.cpp $(FLLIB_ODEP)
	$(CXXC) -c -o $@ $(FLLIB_CXXFLAGS) $(srcdir)/rowdragpl.cpp

fllib_rowlayoutpl.o: $(srcdir)/rowlayoutpl.cpp $(FLLIB_ODEP)
	$(CXXC) -c -o $@ $(FLLIB_CXXFLAGS) $(srcdir)/rowlayoutpl.cpp

fllib_toolwnd.o: $(srcdir)/toolwnd.cpp $(FLLIB_ODEP)
	$(CXXC) -c -o $@ $(FLLIB_CXXFLAGS) $(srcdir)/toolwnd.cpp

fllib_updatesmgr.o: $(srcdir)/updatesmgr.cpp $(FLLIB_ODEP)
	$(CXXC) -c -o $@ $(FLLIB_CXXFLAGS) $(srcdir)/updatesmgr.cpp


# Include dependency info, if present:
-include ./.deps/*.d

.PHONY: all install uninstall clean distclean install_fldll uninstall_fldll \
	install_fllib uninstall_fllib
