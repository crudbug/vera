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
BK_DEPS = /Users/dquist/dev/work/vera/libs/mac/wxMac-2.8.12/bk-deps
srcdir = .
top_srcdir = ../..
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
EXTRALIBS_XML =  -lexpat
EXTRALIBS_HTML = 
EXTRALIBS_GUI = -framework WebKit
EXTRALIBS_SDL = 
HOST_SUFFIX = 
SAMPLES_RPATH_FLAG = 
SAMPLES_RPATH_POSTLINK = $(wx_top_builddir)/change-install-names $(LIBDIRNAME) $(prefix) $@
wx_top_builddir = /Users/dquist/dev/work/vera/libs/mac/wxMac-2.8.12

### Variables: ###

DESTDIR = 
WX_RELEASE = 2.8
WX_VERSION = $(WX_RELEASE).12
LIBDIRNAME = $(wx_top_builddir)/lib
WIDGETS_CXXFLAGS = -D__WX$(TOOLKIT)__ $(__WXUNIV_DEFINE_p) \
	$(__EXCEPTIONS_DEFINE_p) $(__RTTI_DEFINE_p) $(__THREAD_DEFINE_p) \
	-I$(srcdir) $(__DLLFLAG_p) -I$(srcdir)/../../samples $(CPPFLAGS) $(CXXFLAGS)
WIDGETS_OBJECTS =  \
	$(__widgets_os2_lib_res) \
	widgets_bmpcombobox.o \
	widgets_button.o \
	widgets_checkbox.o \
	widgets_clrpicker.o \
	widgets_combobox.o \
	widgets_datepick.o \
	widgets_dirctrl.o \
	widgets_dirpicker.o \
	widgets_filepicker.o \
	widgets_fontpicker.o \
	widgets_gauge.o \
	widgets_hyperlnk.o \
	widgets_listbox.o \
	widgets_notebook.o \
	widgets_odcombobox.o \
	widgets_radiobox.o \
	widgets_searchctrl.o \
	widgets_slider.o \
	widgets_spinbtn.o \
	widgets_static.o \
	widgets_textctrl.o \
	widgets_toggle.o \
	widgets_widgets.o \
	$(__widgets___win32rc)

### Conditionally set variables: ###

#CXXC = $(CXX)
CXXC = $(BK_DEPS) $(CXX)
PLUGIN_ADV_EXTRALIBS = $(EXTRALIBS_SDL)
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
#__widgets___mac_setfilecmd = @true
__widgets___mac_setfilecmd = \
	$(SETFILE) -a C widgets$(EXEEXT)
__widgets___mac_rezcmd = $(__MACOSX_RESOURCES_p_1)
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
COND_PLATFORM_OS2_1___widgets___os2_emxbindcmd = $(NM) widgets$(EXEEXT) | if \
	grep -q pmwin.763 ; then emxbind -ep widgets$(EXEEXT) ; fi
#__widgets___os2_emxbindcmd = $(COND_PLATFORM_OS2_1___widgets___os2_emxbindcmd)
#__RCDEFDIR_p = -i \
#	$(LIBDIRNAME)/wx/include/$(TOOLCHAIN_FULLNAME)
#__RCDEFDIR_p_1 = --include-dir \
#	$(LIBDIRNAME)/wx/include/$(TOOLCHAIN_FULLNAME)
#__widgets_os2_lib_res = \
#	$(top_srcdir)/include/wx/os2/wx.res
__widgets_app_Contents_PkgInfo___depname \
	= widgets.app/Contents/PkgInfo
__widgets_bundle___depname = widgets_bundle
#____widgets_BUNDLE_TGT_REF_DEP = \
#	$(__widgets_app_Contents_PkgInfo___depname)
____widgets_BUNDLE_TGT_REF_DEP = \
	$(__widgets_app_Contents_PkgInfo___depname)
COND_MONOLITHIC_0___WXLIB_XML_p = \
	-lwx_base$(WXBASEPORT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_xml-$(WX_RELEASE)$(HOST_SUFFIX)
__WXLIB_XML_p = $(COND_MONOLITHIC_0___WXLIB_XML_p)
COND_MONOLITHIC_0___WXLIB_ADV_p = \
	-lwx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_adv-$(WX_RELEASE)$(HOST_SUFFIX)
__WXLIB_ADV_p = $(COND_MONOLITHIC_0___WXLIB_ADV_p)
COND_MONOLITHIC_0___WXLIB_HTML_p = \
	-lwx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_html-$(WX_RELEASE)$(HOST_SUFFIX)
__WXLIB_HTML_p = $(COND_MONOLITHIC_0___WXLIB_HTML_p)
COND_MONOLITHIC_0___WXLIB_CORE_p = \
	-lwx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_core-$(WX_RELEASE)$(HOST_SUFFIX)
__WXLIB_CORE_p = $(COND_MONOLITHIC_0___WXLIB_CORE_p)
COND_MONOLITHIC_0___WXLIB_BASE_p = \
	-lwx_base$(WXBASEPORT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
__WXLIB_BASE_p = $(COND_MONOLITHIC_0___WXLIB_BASE_p)
#__widgets___win32rc = widgets_sample_rc.o
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
	widgets$(EXEEXT) Carbon.r sample.r
__MACOSX_RESOURCES_p_1 = $(COND_TOOLKIT_MAC___MACOSX_RESOURCES_p_1)

### Targets: ###

all: widgets$(EXEEXT) $(__widgets_bundle___depname)

install: 

uninstall: 

install-strip: install

clean: 
	rm -rf ./.deps ./.pch
	rm -f ./*.o
	rm -f widgets$(EXEEXT)
	rm -rf widgets.app

distclean: clean
	rm -f config.cache config.log config.status bk-deps bk-make-pch shared-ld-sh Makefile

widgets$(EXEEXT): $(WIDGETS_OBJECTS) $(__widgets___win32rc)
	$(CXX) -o $@ $(WIDGETS_OBJECTS)    -L$(LIBDIRNAME) $(LDFLAGS_GUI) $(SAMPLES_RPATH_FLAG) $(LDFLAGS)  $(__WXLIB_XML_p) $(EXTRALIBS_XML) $(__WXLIB_ADV_p) $(PLUGIN_ADV_EXTRALIBS) $(__WXLIB_HTML_p) $(EXTRALIBS_HTML) $(__WXLIB_CORE_p)  $(__WXLIB_BASE_p)  $(__WXLIB_MONO_p) $(__LIB_TIFF_p) $(__LIB_JPEG_p) $(__LIB_PNG_p) $(EXTRALIBS_FOR_GUI) $(__LIB_ZLIB_p) $(__LIB_ODBC_p) $(__LIB_REGEX_p) $(__LIB_EXPAT_p) $(EXTRALIBS_FOR_BASE) $(LIBS)
	$(__widgets___mac_rezcmd)
	$(__widgets___mac_setfilecmd)
	$(__widgets___os2_emxbindcmd)
	$(SAMPLES_RPATH_POSTLINK)

widgets.app/Contents/PkgInfo: widgets$(EXEEXT) $(top_srcdir)/src/mac/carbon/Info.plist.in $(top_srcdir)/src/mac/carbon/wxmac.icns
	mkdir -p widgets.app/Contents
	mkdir -p widgets.app/Contents/MacOS
	mkdir -p widgets.app/Contents/Resources
	
	
	sed -e "s/IDENTIFIER/`echo $(srcdir) | sed -e 's,\.\./,,g' | sed -e 's,/,.,g'`/" \
	-e "s/EXECUTABLE/widgets/" \
	-e "s/VERSION/$(WX_VERSION)/" \
	$(top_srcdir)/src/mac/carbon/Info.plist.in >widgets.app/Contents/Info.plist
	
	
	echo -n "APPL????" >widgets.app/Contents/PkgInfo
	
	
	ln -f widgets$(EXEEXT) widgets.app/Contents/MacOS/widgets
	
	
	cp -f $(top_srcdir)/src/mac/carbon/wxmac.icns widgets.app/Contents/Resources/wxmac.icns

widgets_bundle: $(____widgets_BUNDLE_TGT_REF_DEP)

widgets_bmpcombobox.o: $(srcdir)/bmpcombobox.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/bmpcombobox.cpp

widgets_button.o: $(srcdir)/button.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/button.cpp

widgets_checkbox.o: $(srcdir)/checkbox.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/checkbox.cpp

widgets_clrpicker.o: $(srcdir)/clrpicker.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/clrpicker.cpp

widgets_combobox.o: $(srcdir)/combobox.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/combobox.cpp

widgets_datepick.o: $(srcdir)/datepick.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/datepick.cpp

widgets_dirctrl.o: $(srcdir)/dirctrl.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/dirctrl.cpp

widgets_dirpicker.o: $(srcdir)/dirpicker.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/dirpicker.cpp

widgets_filepicker.o: $(srcdir)/filepicker.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/filepicker.cpp

widgets_fontpicker.o: $(srcdir)/fontpicker.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/fontpicker.cpp

widgets_gauge.o: $(srcdir)/gauge.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/gauge.cpp

widgets_hyperlnk.o: $(srcdir)/hyperlnk.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/hyperlnk.cpp

widgets_listbox.o: $(srcdir)/listbox.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/listbox.cpp

widgets_notebook.o: $(srcdir)/notebook.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/notebook.cpp

widgets_odcombobox.o: $(srcdir)/odcombobox.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/odcombobox.cpp

widgets_radiobox.o: $(srcdir)/radiobox.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/radiobox.cpp

widgets_searchctrl.o: $(srcdir)/searchctrl.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/searchctrl.cpp

widgets_slider.o: $(srcdir)/slider.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/slider.cpp

widgets_spinbtn.o: $(srcdir)/spinbtn.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/spinbtn.cpp

widgets_static.o: $(srcdir)/static.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/static.cpp

widgets_textctrl.o: $(srcdir)/textctrl.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/textctrl.cpp

widgets_toggle.o: $(srcdir)/toggle.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/toggle.cpp

widgets_widgets.o: $(srcdir)/widgets.cpp
	$(CXXC) -c -o $@ $(WIDGETS_CXXFLAGS) $(srcdir)/widgets.cpp

widgets_sample_rc.o: $(srcdir)/../sample.rc
	$(WINDRES) -i$< -o$@    --define __WX$(TOOLKIT)__ $(__WXUNIV_DEFINE_p_2)   $(__EXCEPTIONS_DEFINE_p_2) $(__RTTI_DEFINE_p_2) $(__THREAD_DEFINE_p_2)   --include-dir $(srcdir) $(__DLLFLAG_p_2) --include-dir $(srcdir)/../../samples $(__RCDEFDIR_p_1) --include-dir $(top_srcdir)/include


# Include dependency info, if present:
-include ./.deps/*.d

.PHONY: all install uninstall clean distclean widgets_bundle
