# =========================================================================
#     This makefile was generated by
#     Bakefile 0.2.9 (http://www.bakefile.org)
#     Do not modify, all changes will be overwritten!
# =========================================================================




prefix = /usr/local
exec_prefix = ${prefix}
datarootdir = @datarootdir@
INSTALL = /usr/bin/install -c
EXEEXT = 
WINDRES = 
REZ = Rez
SETFILE = SetFile
NM = nm
BK_DEPS = /Users/dquist/Downloads/wxMac-2.8.12/build-i386/bk-deps
srcdir = ../../../demos/bombs
top_srcdir = ../../..
LIBS = -lz -lpthread -liconv
LDFLAGS_GUI = 
CXX = g++ -isysroot /Developer/SDKs/MacOSX10.6.sdk -mmacosx-version-min=10.6
CXXFLAGS = -DWX_PRECOMP -Wall -Wundef -Wno-ctor-dtor-privacy -O2 -fno-strict-aliasing -arch i386 -fno-common
CPPFLAGS = -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES -I${wx_top_builddir}/lib/wx/include/mac-ansi-release-2.8 -I${top_srcdir}/include -fpascal-strings -I${top_srcdir}/src/mac/carbon/morefilex -I/Developer/Headers/FlatCarbon -arch i386
LDFLAGS =  -arch i386 -framework IOKit -framework Carbon -framework Cocoa -framework System -framework QuickTime -framework OpenGL -framework AGL 
WX_LIB_FLAVOUR = 
TOOLKIT = MAC
TOOLKIT_LOWERCASE = mac
TOOLKIT_VERSION = 
TOOLCHAIN_FULLNAME = mac-ansi-release-2.8
EXTRALIBS =  -arch i386 -framework IOKit -framework Carbon -framework Cocoa -framework System -framework QuickTime -framework OpenGL -framework AGL  -lz -lpthread -liconv 
EXTRALIBS_GUI = -framework WebKit
HOST_SUFFIX = 
SAMPLES_RPATH_FLAG = 
SAMPLES_RPATH_POSTLINK = $(wx_top_builddir)/change-install-names $(LIBDIRNAME) $(prefix) $@
wx_top_builddir = /Users/dquist/Downloads/wxMac-2.8.12/build-i386

### Variables: ###

DESTDIR = 
WX_RELEASE = 2.8
WX_VERSION = $(WX_RELEASE).12
LIBDIRNAME = $(wx_top_builddir)/lib
BOMBS_CXXFLAGS = -D__WX$(TOOLKIT)__ $(__WXUNIV_DEFINE_p) \
	$(__EXCEPTIONS_DEFINE_p) $(__RTTI_DEFINE_p) $(__THREAD_DEFINE_p) \
	-I$(srcdir) $(__DLLFLAG_p) -I$(srcdir)/../../samples $(CPPFLAGS) $(CXXFLAGS)
BOMBS_OBJECTS =  \
	$(__bombs_os2_lib_res) \
	bombs_bombs.o \
	bombs_bombs1.o \
	bombs_game.o \
	$(__bombs___win32rc)

### Conditionally set variables: ###

#CXXC = $(CXX)
CXXC = $(BK_DEPS) $(CXX)
#PORTNAME = base
PORTNAME = $(TOOLKIT_LOWERCASE)$(TOOLKIT_VERSION)
WXBASEPORT = _carbon
#WXDEBUGFLAG = d
#WXDEBUGFLAG = d
#WXUNICODEFLAG = u
#WXUNIVNAME = univ
EXTRALIBS_FOR_BASE = $(EXTRALIBS)
#EXTRALIBS_FOR_BASE = $(EXTRALIBS) $(EXTRALIBS_GUI)
EXTRALIBS_FOR_GUI = $(EXTRALIBS_GUI)
#EXTRALIBS_FOR_GUI = 
#__bombs___mac_setfilecmd = @true
__bombs___mac_setfilecmd = \
	$(SETFILE) -a C bombs$(EXEEXT)
__bombs___mac_rezcmd = $(__MACOSX_RESOURCES_p_1)
#__WXUNIV_DEFINE_p = -D__WXUNIVERSAL__
#__WXUNIV_DEFINE_p_1 = -d __WXUNIVERSAL__
#__WXUNIV_DEFINE_p_2 = --define __WXUNIVERSAL__
#__EXCEPTIONS_DEFINE_p = -DwxNO_EXCEPTIONS
#__EXCEPTIONS_DEFINE_p_1 = -d wxNO_EXCEPTIONS
#__EXCEPTIONS_DEFINE_p_2 = --define wxNO_EXCEPTIONS
#__RTTI_DEFINE_p = -DwxNO_RTTI
#__RTTI_DEFINE_p_1 = -d wxNO_RTTI
#__RTTI_DEFINE_p_2 = --define wxNO_RTTI
#__THREAD_DEFINE_p = -DwxNO_THREADS
#__THREAD_DEFINE_p_1 = -d wxNO_THREADS
#__THREAD_DEFINE_p_2 = --define wxNO_THREADS
__DLLFLAG_p = -DWXUSINGDLL
__DLLFLAG_p_1 = -d WXUSINGDLL
__DLLFLAG_p_2 = --define WXUSINGDLL
COND_PLATFORM_OS2_1___bombs___os2_emxbindcmd = $(NM) bombs$(EXEEXT) | if grep -q \
	pmwin.763 ; then emxbind -ep bombs$(EXEEXT) ; fi
#__bombs___os2_emxbindcmd = $(COND_PLATFORM_OS2_1___bombs___os2_emxbindcmd)
#__RCDEFDIR_p = -i \
#	$(LIBDIRNAME)/wx/include/$(TOOLCHAIN_FULLNAME)
#__RCDEFDIR_p_1 = --include-dir \
#	$(LIBDIRNAME)/wx/include/$(TOOLCHAIN_FULLNAME)
#__bombs_os2_lib_res = \
#	$(top_srcdir)/include/wx/os2/wx.res
__bombs_app_Contents_PkgInfo___depname \
	= bombs.app/Contents/PkgInfo
__bombs_bundle___depname = bombs_bundle
#____bombs_BUNDLE_TGT_REF_DEP = \
#	$(__bombs_app_Contents_PkgInfo___depname)
____bombs_BUNDLE_TGT_REF_DEP = \
	$(__bombs_app_Contents_PkgInfo___depname)
COND_MONOLITHIC_0___WXLIB_CORE_p = \
	-lwx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_core-$(WX_RELEASE)$(HOST_SUFFIX)
__WXLIB_CORE_p = $(COND_MONOLITHIC_0___WXLIB_CORE_p)
COND_MONOLITHIC_0___WXLIB_BASE_p = \
	-lwx_base$(WXBASEPORT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
__WXLIB_BASE_p = $(COND_MONOLITHIC_0___WXLIB_BASE_p)
#__bombs___win32rc = bombs_bombs_rc.o
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
COND_TOOLKIT_MAC___MACOSX_RESOURCES_p_1 = $(REZ) -d __DARWIN__ -t APPL -d \
	__WX$(TOOLKIT)__ $(__WXUNIV_DEFINE_p_1) $(__EXCEPTIONS_DEFINE_p_1) \
	$(__RTTI_DEFINE_p_1) $(__THREAD_DEFINE_p_1) -i $(srcdir) $(__DLLFLAG_p_1) -i \
	$(srcdir)/../../samples $(__RCDEFDIR_p) -i $(top_srcdir)/include -o \
	bombs$(EXEEXT) Carbon.r sample.r
__MACOSX_RESOURCES_p_1 = $(COND_TOOLKIT_MAC___MACOSX_RESOURCES_p_1)

### Targets: ###

all: bombs$(EXEEXT) $(__bombs_bundle___depname)

install: 

uninstall: 

install-strip: install

clean: 
	rm -rf ./.deps ./.pch
	rm -f ./*.o
	rm -f bombs$(EXEEXT)
	rm -rf bombs.app

distclean: clean
	rm -f config.cache config.log config.status bk-deps bk-make-pch shared-ld-sh Makefile

bombs$(EXEEXT): $(BOMBS_OBJECTS) $(__bombs___win32rc)
	$(CXX) -o $@ $(BOMBS_OBJECTS)    -L$(LIBDIRNAME) $(LDFLAGS_GUI) $(SAMPLES_RPATH_FLAG) $(LDFLAGS)  $(__WXLIB_CORE_p)  $(__WXLIB_BASE_p)  $(__WXLIB_MONO_p) $(__LIB_TIFF_p) $(__LIB_JPEG_p) $(__LIB_PNG_p) $(EXTRALIBS_FOR_GUI) $(__LIB_ZLIB_p) $(__LIB_ODBC_p) $(__LIB_REGEX_p) $(__LIB_EXPAT_p) $(EXTRALIBS_FOR_BASE) $(LIBS)
	$(__bombs___mac_rezcmd)
	$(__bombs___mac_setfilecmd)
	$(__bombs___os2_emxbindcmd)
	$(SAMPLES_RPATH_POSTLINK)

bombs.app/Contents/PkgInfo: bombs$(EXEEXT) $(top_srcdir)/src/mac/carbon/Info.plist.in $(top_srcdir)/src/mac/carbon/wxmac.icns
	mkdir -p bombs.app/Contents
	mkdir -p bombs.app/Contents/MacOS
	mkdir -p bombs.app/Contents/Resources
	
	
	sed -e "s/IDENTIFIER/`echo $(srcdir) | sed -e 's,\.\./,,g' | sed -e 's,/,.,g'`/" \
	-e "s/EXECUTABLE/bombs/" \
	-e "s/VERSION/$(WX_VERSION)/" \
	$(top_srcdir)/src/mac/carbon/Info.plist.in >bombs.app/Contents/Info.plist
	
	
	echo -n "APPL????" >bombs.app/Contents/PkgInfo
	
	
	ln -f bombs$(EXEEXT) bombs.app/Contents/MacOS/bombs
	
	
	cp -f $(top_srcdir)/src/mac/carbon/wxmac.icns bombs.app/Contents/Resources/wxmac.icns

bombs_bundle: $(____bombs_BUNDLE_TGT_REF_DEP)

bombs_bombs.o: $(srcdir)/bombs.cpp
	$(CXXC) -c -o $@ $(BOMBS_CXXFLAGS) $(srcdir)/bombs.cpp

bombs_bombs1.o: $(srcdir)/bombs1.cpp
	$(CXXC) -c -o $@ $(BOMBS_CXXFLAGS) $(srcdir)/bombs1.cpp

bombs_game.o: $(srcdir)/game.cpp
	$(CXXC) -c -o $@ $(BOMBS_CXXFLAGS) $(srcdir)/game.cpp

bombs_bombs_rc.o: $(srcdir)/bombs.rc
	$(WINDRES) -i$< -o$@    --define __WX$(TOOLKIT)__ $(__WXUNIV_DEFINE_p_2)   $(__EXCEPTIONS_DEFINE_p_2) $(__RTTI_DEFINE_p_2) $(__THREAD_DEFINE_p_2)   --include-dir $(srcdir) $(__DLLFLAG_p_2) --include-dir $(srcdir)/../../samples $(__RCDEFDIR_p_1) --include-dir $(top_srcdir)/include


# Include dependency info, if present:
-include ./.deps/*.d

.PHONY: all install uninstall clean distclean bombs_bundle
