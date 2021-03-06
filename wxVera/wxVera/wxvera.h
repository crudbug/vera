#ifndef _WXVERA_H_
#define _WXVERA_H_

#ifdef _WIN32

// Windows stuff
#include <winsock2.h>
#include <windows.h>

#elif defined __GNUC__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "wincompat.h"

#endif

#include <float.h>

// For compilers that support precompilation, includes "wx/wx.h".
// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#else
    #include "wx/wxprec.h"
#endif

// C++ Stuff
#include <map>

// Windows specialness
#ifdef _WIN32

using namespace stdext;
#include <hash_map>
#define snprintf sprintf_s

// Mac, Linux, etc.
#elif defined __GNUC__

using namespace __gnu_cxx;
#include <ext/hash_map>

#endif

#include <cmath>

// wxWidgets includes
#include "wx/app.h"
#include "wx/button.h"
#include "wx/checkbox.h"
#include "wx/event.h"
#include "wx/filefn.h"
#include "wx/filename.h"
#include "wx/file.h"
#include "wx/glcanvas.h"
#include "wx/notebook.h"
#include "wx/progdlg.h"
#include "wx/sizer.h"
#include "wx/sstream.h"
#include "wx/stattext.h"
#include "wx/stdpaths.h"
#include "wx/string.h"
#include "wx/textctrl.h"
#include "wx/textfile.h"
#include "wx/url.h"
#include "wx/utils.h"
#include "wx/wizard.h"
#include "wx/thread.h"
#include "wx/checkbox.h"
#include "wx/richtext/richtextctrl.h"
#include "wx/stdpaths.h"
#include "wx/filename.h"

// wxVera includes
#include "threadTraceBuilder.h"
#include "threadIdaServer.h"
#include "Viz.h"
#include "VizFrame.h"
#include "LegendFrame.h"
#include "Trace.h"
#include "traceWizard.h"
#include "Config.h"
#include "configFrame.h"
#include "LegendFrame.h"
#include "util.h"

// Icons
#ifndef __XPM_DATA__
#define __XPM_DATA__
#include "icons/vera.xpm"
#include "icons/vera-med.xpm"
#include "icons/vera-small.xpm"

#include "icons/folder_32.xpm"
#include "icons/gear_32.xpm"
#include "icons/ida_32.xpm"
#include "icons/ether_32.xpm"
#include "icons/help_32.xpm"
#include "icons/idaConnected_32.xpm"
#include "icons/find.xpm"
#include "icons/home.xpm"
#include "icons/play.xpm"
#include "icons/stop.xpm"
#include "icons/rewind.xpm"
#include "icons/fastforward.xpm"
#endif

// Identifier strings
#define __VERA_VERSION__				"0.50"
#define __VERA_UPDATE_URL__				"http://www.offensivecomputing.net/vera/currentversion"
#define __VERA_UPDATE_DOWNLOAD_URL__	"http://www.offensivecomputing.net/vera/"
#define VERA_OBJECT_ARGS				{WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0}
#define VERA_QUIET_UPDATE_CHECK			1
#define __VERA_WINDOW_TITLE__			"VERA - Version " __VERA_VERSION__

#ifdef _WIN32
#define TRACEGEN_CMD "tracegen.exe"
#else
#define TRACEGEN_CMD "tracegen"
#endif

// Custom event message IDs
enum CUSTOM_EVENT_IDS
{
	THREAD_TRACE_NONE_PROCESSED				= 0,
	THREAD_TRACE_BASIC_BLOCKS_PROCESSED,
	THREAD_TRACE_ALL_ADDRESSES_PROCESSED,
	THREAD_TRACE_BOTH_PROCESSED,
	THREAD_TRACE_ERROR,
	THREAD_TRACE_UPDATE_PROGRESS,
	THREAD_IDA_FINISHED_ERROR,
	THREAD_IDA_FINISHED_NOERROR,
	THREAD_IDA_MSG_RECEIVED,
};

// IDA Commands
#define NAV_CMD "NAV"
#define MAX_IDA_SERVER_MSG_SIZE 128

// Thread creation stack size
#define DEFAULT_THREAD_STACK_SIZE 1024*1000*8

class LegendFrame;

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
	friend class VizFrame;
public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool		OnInit();
	virtual int			OnExit();
	bool				isNewVersionAvailable(void);

	Config				*config;

private:
	VizFrame *			vizFrame;
	LegendFrame *		legendFrame;
	int FilterEvent(wxEvent &event);
};



#endif

