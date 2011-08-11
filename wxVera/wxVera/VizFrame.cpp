#include "wxvera.h"

#include "wx/thread.h"
#include "VizFrame.h"

#ifdef _USE_WX_EVENTS_
BEGIN_EVENT_TABLE(VizFrame, wxFrame)
    EVT_MENU(Vera_Quit,  VizFrame::OnQuit)
	EVT_MENU(Vera_Open, VizFrame::OnOpen)
    EVT_MENU(Vera_About, VizFrame::OnAbout)
	EVT_CLOSE(VizFrame::OnCloseWindow)
	EVT_MENU(Vera_Check_Updates, VizFrame::CheckForUpdate)
	EVT_MENU(Vera_ConnectToIDA, VizFrame::OnIda)
	EVT_MENU(Vera_Config, VizFrame::OnConfig)
	EVT_MOUSEWHEEL(VizFrame::mouseWheelMoved)
	EVT_KEY_DOWN(VizFrame::keyPressed)
	EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_BUTTON_CLICKED, VizFrame::ProcessEvent)
	EVT_TEXT(Vera_Search, VizFrame::SearchTextFocused)
	EVT_TEXT_ENTER(Vera_Search, VizFrame::SearchTextEvent)
END_EVENT_TABLE()
#endif

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
VizFrame::VizFrame(const wxString& title, wxPoint pnt, wxSize size, MyApp *parent)
       : wxFrame(NULL, wxID_ANY, title, pnt, size)
{
	page1		= NULL;
	traceWiz	= NULL;
	parentApp	= parent;
	tbThread    = NULL;
	idaServer   = NULL;
	textSearchIsCleared = false;

	// This is for the "tabbed" view at the top of the application
	noteBook = new wxNotebook(this, wxID_ANY, pnt, size, wxNB_TOP);

	if (noteBook == NULL)
	{
		wxLogDebug(wxString::Format(wxT("Could not allocate memory: %s:%u"), __FILE__, __LINE__));
		return;
	}

	// Create the VeraPane rendering class
	int args[] = VERA_OBJECT_ARGS;
	veraPane = new VeraPane(noteBook, args, this);

	if (veraPane == NULL)
	{
		wxLogDebug(wxString::Format(wxT("Could not allocate memory: %s:%u"), __FILE__, __LINE__));
		return;
	}

	// First page to be displayed.
	noteBook->AddPage(veraPane, wxT("Visualization"));

	// Create the File Menu
	wxMenu *fileMenu = new wxMenu;

	if (fileMenu == NULL)
	{
		wxLogDebug(wxString::Format(wxT("Could not allocate memory: %s:%u"), __FILE__, __LINE__));
		return;
	}

	// File Menu Items
	fileMenu->Append(Vera_Open, wxT("&Open\tCtrl-O"), wxT("Open a GML file"));
	fileMenu->Append(Vera_Quit, wxT("E&xit\tAlt-X"), wxT("Quit this program"));

	// Create the tools menu
	wxMenu *toolsMenu = new wxMenu;

	if (toolsMenu == NULL)
	{ 
		wxLogDebug(wxString::Format(wxT("Could not allocate memory: %s:%u"), __FILE__, __LINE__));
		return;
	}

	toolsMenu->Append(Vera_ConnectToIDA, wxT("Start &IDA Server\tCtrl-I"), wxT("Start IDA Pro connection"));
	toolsMenu->Append(wxID_PROPERTIES, wxT("O&ptions"), wxT("Open Options and Configuration"));

	// Create the Help Menu
	wxMenu *helpMenu = new wxMenu;

	if (helpMenu == NULL)
	{
		wxLogDebug(wxString::Format(wxT("Could not allocate memory: %s:%u"), __FILE__, __LINE__));
		return;
	}

	// Help Menu Items
	helpMenu->Append(Vera_About, wxT("&About...\tF1"), wxT("Show about dialog"));
	helpMenu->Append(Vera_Check_Updates, wxT("&Updates"), wxT("Check for updates"));

	// now append the freshly created menu to the menu bar...
	wxMenuBar *menuBar = new wxMenuBar();

	if (menuBar == NULL)
	{
		wxLogDebug(wxString::Format(wxT("Could not allocate memory: %s:%u"), __FILE__, __LINE__));
		return;
	}

	menuBar->Append(fileMenu, wxT("&File"));
	menuBar->Append(toolsMenu, wxT("&Tools"));
	menuBar->Append(helpMenu, wxT("&Help"));

	// ... and attach this menu bar to the frame
	SetMenuBar(menuBar);

	// Create the Tool Bar
	// Open, IDA, Configuration, Search for Address

	toolBar = new wxToolBar(this, wxID_ANY);

	if (NULL == toolBar)
	{
		wxLogDebug(wxString::Format(wxT("Could not allocate memory: %s:%u"), __FILE__, __LINE__));
		return;
	}

	// Icons for the toolBar
	bmpOpen = new wxBitmap(folder_32_xpm);
	bmpConfig = new wxBitmap(gear_32_xpm);
	bmpAbout = new wxBitmap(help_32_xpm);
	bmpIda = new wxBitmap(ida_32_xpm);
	//bmpEther = new wxBitmap(ether_32_xpm);

	textSearch = NULL; // This is initialized in SetVeraToolbar to give the search box the right toolbar base

	// Call the code to add the toolbar
	SetVeraToolbar(toolBar);

	CreateStatusBar(2);
	SetStatusText(wxT("Ready"));

}

void VizFrame::SetVeraToolbar(wxToolBar *tb)
{
	// Add the icons, and reuse events where able
	tb->AddTool(wxID_OPEN, *bmpOpen, wxT("Open GML graph or trace file"));
	tb->AddTool(Vera_ConnectToIDA, *bmpIda, wxT("Start IDA Pro module listener"));
	tb->AddTool(wxID_PROPERTIES, *bmpConfig, wxT("Configure VERA"));
	tb->AddTool(wxID_ABOUT, *bmpAbout, wxT("About VERA"));
	
	// Actual controls have to have the new toolbar as the base, so set that up here.
	if (NULL != textSearch)
		delete textSearch;
	
	textSearch = new wxTextCtrl(tb, Vera_Search, wxT(TEXT_SEARCH_DEFAULT));

	if (NULL == textSearch)
	{
		wxLogDebug(wxString::Format(wxT("Could not allocate memory: %s:%u"), __FILE__, __LINE__));
		return;
	}
	
	tb->AddControl(textSearch);
	tb->Realize();

	SetToolBar(tb);
}

VizFrame::~VizFrame(void)
{
	cleanupThreads();

	// Clean up all the allocated icons
	delete bmpOpen;
	delete bmpConfig;
	delete bmpAbout;
	delete bmpIda;

	bmpOpen = bmpConfig = bmpAbout = bmpIda = NULL;

}

// event handlers

void VizFrame::cleanupThreads(void)
{
	if(idaServer)
	{
		idaServer->Delete();
		idaServer = NULL;
	}

}

void VizFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{

	cleanupThreads();

	// true is to force the frame to close
	Close(true);
}

void VizFrame::OnOpen(wxCommandEvent& WXUNUSED(event))
{
	// Open a dialog for just the .gml files
	wxFileDialog OpenDialog(
		this, 
		wxT("Choose a file to open"),
		wxEmptyString,
		wxEmptyString,
		wxT("GML files (*.gml;*.trace)|*.gml;*.trace"),
		wxFD_OPEN, 
		wxDefaultPosition);

	

	// If the user clicks the ok box, then present the image
	if (OpenDialog.ShowModal() == wxID_OK)
	{
		wxString path = OpenDialog.GetPath();

		/*
		  There are multiple ways of opening files. First a .trace file can be used to generate
		  the graph files. Second a .gml extension can be used to open the graphs directly.

		  The trace files have two different supported types. First, traces from the Ether system.
		  Second, traces from a veratrace (Intel PIN) based system.
		  
		 */

		if (path.EndsWith(wxT(".gml")))
		{
			// Check the return value here.
			veraPane->openFile(path);
			this->SetStatusText(wxString::Format(wxT("Loaded %s"), path.c_str()));
		}
		else if (path.EndsWith(wxT(".trace")))
		{
			// We need more information to open a trace file, so use that to open the file.
			traceWiz = new wxWizard(this, 
						wxID_ANY, 
						wxT("Process trace files"), 
						wxNullBitmap, 
						wxDefaultPosition, 
						wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);
			
			if (traceWiz == NULL)
			{
				wxLogDebug(wxString::Format(wxT("Could not allocate memory: %s:%u"),
							    __FILE__, __LINE__));
				return;
			}

			page1 = new traceWizard(traceWiz);

			if (page1 == NULL)
			{
				wxLogDebug(wxString::Format(wxT("Could not allocate memory: %s:%u"),
							    __FILE__, __LINE__));
				return;
			}

			traceWiz->GetPageAreaSizer()->Add(page1);

			if (traceWiz->RunWizard(page1))
			{
				// Make sure the check boxes are actually selected
				if (! (page1->m_genBblAddressesCheckBox->GetValue() ||
				       page1->m_genAllAddressesCheckBox->GetValue()) )
				{
					wxMessageBox(wxT("You must select at least one\n"
							 "address processing mode"),
						     wxT("Trace Processing Error"), 
						     wxICON_ERROR);
					return;

				}

				// Check for invalid exe files

				if ( page1->m_origExeFile->GetValue().StartsWith(wxT("Enter")) )
				{
					wxMessageBox(wxT("You must select the original executable\n"
							 "file for processing."),
						     wxT("Trace Processing Error"), 
						     wxICON_ERROR);
					return;
				}

				// Check for invalid save file or duplicates
				if ( page1->m_saveFile->GetValue().StartsWith(wxT("Enter")) )
				{
					wxMessageBox(wxT("You must choose where to save\nthe graph data file."),
						     wxT("Trace Processing Error"), 
						     wxICON_ERROR);
					return;
				}

				// Begin the actual processing
				dlgProgress = new wxProgressDialog(wxT("Processing trace file"),
								   wxT("Processing the tracefile"),
								   100,
								   this);
				
				if (dlgProgress == NULL)
				{
					wxLogDebug(wxString::Format(wxT("Could not allocate memory: %s:%u"),
								    __FILE__, __LINE__));
					return;
				}

				dlgProgress->Show(true);

				// Create a new thread to handle the actual trace generation
				tbThread = new threadTraceBuilder(path, 
								  page1->m_origExeFile->GetValue(),
								  page1->m_saveFile->GetValue(), 
								  page1->m_genBblAddressesCheckBox->GetValue(),
								  page1->m_genAllAddressesCheckBox->GetValue(),
								  this,
								  dlgProgress);

				if (tbThread == NULL)
				{
					wxLogDebug(wxString::Format(wxT("Could not allocate memory: %s:%u"), __FILE__, __LINE__));
					return;
				}

				wxThreadError err = tbThread->Create();

				if (wxTHREAD_NO_ERROR != err)
				{
					wxLogDebug(wxT("Error creating the trace builder thread %d"), err);
					return;
				}

				// Actually run the thread
				err = tbThread->Run();

				if (wxTHREAD_NO_ERROR != err)
				{
					wxLogDebug(wxT("Error running the trace builder thread %d"), err);
					return;
				}

			}
			
			this->SetStatusText(wxString::Format(wxT("Processing %s..."), path.c_str()));
			traceWiz->Destroy();

		}

	}

	// Clean up the dialog
	OpenDialog.Destroy();

	// Trigger a render event
	veraPane->DrawAndRender();
}

// This function strikes me as ugly and non-optimal -Danny
void VizFrame::ProcessEvent(wxCommandEvent & event)
{
	int		traceType		= event.GetInt();
	wxString	filename;

	// Only print out the trace message for the trace messages
	switch(traceType)
	{
	case THREAD_TRACE_NONE_PROCESSED: // There was an error with one of the traces
		wxLogDebug(wxT("No trace processed"));
		return;
		break;
	case THREAD_TRACE_BASIC_BLOCKS_PROCESSED: // Processed a basic block graph
	case THREAD_TRACE_BOTH_PROCESSED: // Processed both a basic block and an instruction graph
	case THREAD_TRACE_ALL_ADDRESSES_PROCESSED: // All instruction graph processed
		wxLogDebug(wxT("Trying to open %s %d"), event.GetString(), event.GetInt());
		break;
	default:
		break;
	}
	
	
	// Right now try to open the all-%s file. Later open both into different notebook tabs
	switch (traceType)
	{
	case THREAD_TRACE_BASIC_BLOCKS_PROCESSED:		// Open the basic block if it's the only one available
		filename = prependFileName(event.GetString(), wxT("bbl-"));
		break;
	case THREAD_TRACE_BOTH_PROCESSED:				// Prefer the all-%s.gml file over the basic block version
	case THREAD_TRACE_ALL_ADDRESSES_PROCESSED:
		filename = prependFileName(event.GetString(), wxT("all-"));
		break;
	case THREAD_IDA_FINISHED_NOERROR:
		wxLogDebug(wxT("IDA Thread finished without errors"));
		break;
	case THREAD_IDA_FINISHED_ERROR:
		wxLogDebug(wxT("IDA Thread finished with error"));
		break;
	case THREAD_IDA_MSG_RECEIVED:
		wxLogDebug(wxT("Received a message from IDA: (%s)"), event.GetString());
		
		if (strcmp(event.GetString().ToAscii(), "OK  \n") == 0)
			wxLogDebug(wxT("Navigate succeeded"));
		else
			wxLogDebug(wxT("Navigate Failed"));
		
		break;
	default:
		wxLogDebug(wxT("Strange trace state received"));
		return;
		break;
	}

	// Open the file if it's a trace processing event
	switch(traceType)
	{
	case THREAD_TRACE_BASIC_BLOCKS_PROCESSED:
	case THREAD_TRACE_BOTH_PROCESSED:
	case THREAD_TRACE_ALL_ADDRESSES_PROCESSED:
		veraPane->openFile(filename);
		this->SetStatusText(wxString::Format(wxT("Loaded %s"), filename.c_str()));
		veraPane->DrawAndRender();
		break;
	default:
		break;
	}
	
}

void VizFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	// Tech Transfer's contribution to the product.
	wxMessageBox(wxT("VERA version " __VERA_VERSION__ " built " __TIMESTAMP__ "\n\n")
				 wxT("Copyright (C) 2011 Los Alamos National Laboratory, All Rights Reserved\n")
				 wxT("Patent Pending, LA-CC-10-131\n\n")
				 wxT("This program was prepared by Los Alamos National Security, LLC at Los ")
				 wxT("Alamos National Laboratory (LANL) under contract No. DE-AC52-06NA25396 ")
				 wxT("with the U.S. Department of Energy (DOE). All rights in the program are ")
				 wxT("reserved by the DOE and Los Alamos National Security, LLC. The U.S. ")
				 wxT("Government retains ownership of all rights in the program and copyright ")
				 wxT("subsisting therein. All rights not granted below are reserved.\n\n")
				 wxT("This program may be used for noncommercial, nonexclusive purposes for ")
				 wxT("internal research, development and evaluation and demonstration purposes ")
				 wxT("only. The right to reproduce, distribute, display publicly, prepare ")
				 wxT("derivative works or compilations thereof is prohibited.\n\n")
				 wxT("NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, ")
				 wxT("NOR THE LOS ALAMOS NATIONAL SECURITY, LLC, NOR ANY OF THEIR EMPLOYEES, ")
				 wxT("MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY ")
				 wxT("OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY ")
				 wxT("INFORMATION, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS ")
				 wxT("THAT ITS USEWOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.\n\n")
				 wxT("Email dquist@offensivecomputing.net for more information\n\n")
				 wxT("Portions of this software are copyright (C) 2009\n")
				 wxT("The FreeType Project (www.freetype.org), All Rights Reserved"),
                 wxT("About VERA"),
                 wxOK | wxICON_INFORMATION,
                 this);
}

void VizFrame::OnConfig(wxCommandEvent &event)
{
	// Create a new configuration frame for VERA
	confFrame = new ConfigFrame(parentApp->config, this);
	confFrame->Show(true);
}

// The text search box gets focused. 
void VizFrame::SearchTextFocused(wxCommandEvent &event)
{
	if (!textSearchIsCleared && event.GetString().Len() != 0)
	{
		textSearch->Clear();
		textSearchIsCleared = true;
	}
}

void VizFrame::SearchTextEvent(wxCommandEvent &event)
{
	if (event.GetString().Find(wxT(TEXT_SEARCH_DEFAULT)) != wxNOT_FOUND)
		wxMessageBox(wxT("Please search for an address or function name"),
					 wxT("Invalid Search"),
					 wxICON_ERROR);

	node_t *s = veraPane->nodeHashMap[string(event.GetString().ToAscii())];

	if (s != NULL)
		wxLogDebug(wxT("BOINK: %s"), s->label);
}

void VizFrame::CheckForUpdate(wxCommandEvent& event)
{
	if (parentApp->config->checkForNewVersion == true && parentApp->isNewVersionAvailable())
	{
		int ret = wxMessageBox(wxT("A new version of VERA is available, \n"
					   "would you like to go download it?"), 
				       wxT("New version is available"), 
				       wxYES_NO);
		
		if (ret == wxYES)
		{
			// Open VERA URL
			wxLaunchDefaultBrowser(wxT(__VERA_UPDATE_DOWNLOAD_URL__));
		}
		else if (ret == wxNO)
		{
			ret = wxMessageBox(wxT("Would you like to check for updates on startup?"),
					   wxT("Check for updates"), wxYES_NO);

			if (ret == wxNO)
			{
				parentApp->config->checkForNewVersion = false;
				parentApp->config->writeConfig(this);
			}
		}
	}
	else if (event.GetInt() != VERA_QUIET_UPDATE_CHECK)
	{
		wxMessageBox(wxT("You are at the latest version of VERA"), wxT("Up-to-date"), wxOK);
	}
}

void VizFrame::OnCloseWindow(wxCloseEvent &event)
{
	// Set the configuration info
	parentApp->config->writeConfig(this);

	wxFrame::OnCloseWindow(event);
}

void VizFrame::SetProxy(wxString &p)
{
	if (p.Length() > 0)
	{
		this->proxy = p;
	}
}

// Event handlers that pass to the underlying Notebook pages

void VizFrame::mouseMoved(wxMouseEvent& event)
{
	wxWindow *curWin = noteBook->GetCurrentPage();

	// If the name is a GLCanvas, this means we have a VeraPane object we can send the event to.
	if ( curWin->GetName().Contains(wxT("GLCanvas")) )
	{
		((VeraPane *) curWin)->mouseMoved(event);
	}

}

void VizFrame::leftMouseDown(wxMouseEvent& event)
{
	wxWindow *curWin = noteBook->GetCurrentPage();

	// If the name is a GLCanvas, this means we have a VeraPane object we can send the event to.
	if ( curWin->GetName().Contains(wxT("GLCanvas")) )
	{
		((VeraPane *) curWin)->leftMouseDown(event);
	}

}

void VizFrame::mouseWheelMoved(wxMouseEvent& event)
{
	wxWindow *curWin = noteBook->GetCurrentPage();

	// If the name is a GLCanvas, this means we have a VeraPane object we can send the event to.
	if ( curWin->GetName().Contains(wxT("GLCanvas")) )
	{
		((VeraPane *) curWin)->mouseWheelMoved(event);
	}

}

void VizFrame::mouseReleased(wxMouseEvent& event)
{
	wxWindow *curWin = noteBook->GetCurrentPage();

	// If the name is a GLCanvas, this means we have a VeraPane object we can send the event to.
	if ( curWin->GetName().Contains(wxT("GLCanvas")) )
	{
		((VeraPane *) curWin)->mouseReleased(event);
	}
}

void VizFrame::rightMouseDown(wxMouseEvent& event)
{
	wxWindow *curWin = noteBook->GetCurrentPage();

	// If the name is a GLCanvas, this means we have a VeraPane object we can send the event to.
	if ( curWin->GetName().Contains(wxT("GLCanvas")) )
	{
		((VeraPane *) curWin)->rightMouseDown(event);
	}
}

void VizFrame::mouseLeftWindow(wxMouseEvent& event)
{
	wxWindow *curWin = noteBook->GetCurrentPage();

	// If the name is a GLCanvas, this means we have a VeraPane object we can send the event to.
	if ( curWin->GetName().Contains(wxT("GLCanvas")) )
	{
		((VeraPane *) curWin)->mouseLeftWindow(event);
	}
}

void VizFrame::keyPressed(wxKeyEvent& event)
{
	wxWindow *curWin = noteBook->GetCurrentPage();

	// If the name is a GLCanvas, this means we have a VeraPane object we can send the event to.
	if ( curWin->GetName().Contains(wxT("GLCanvas")) )
	{
		((VeraPane *) curWin)->keyPressed(event);
	}
}

void VizFrame::keyReleased(wxKeyEvent& event)
{
	wxWindow *curWin = noteBook->GetCurrentPage();

	// If the name is a GLCanvas, this means we have a VeraPane object we can send the event to.
	if ( curWin->GetName().Contains(wxT("GLCanvas")) )
	{
		((VeraPane *) curWin)->keyReleased(event);
	}
}

void VizFrame::render(wxPaintEvent& event)
{
	wxWindow *curWin = noteBook->GetCurrentPage();

	// If the name is a GLCanvas, this means we have a VeraPane object we can send the event to.
	if ( curWin->GetName().Contains(wxT("GLCanvas")) )
	{
		((VeraPane *) curWin)->render(event);
	}
}

void VizFrame::resized(wxSizeEvent& event)
{
	wxWindow *curWin = noteBook->GetCurrentPage();

	// If the name is a GLCanvas, this means we have a VeraPane object we can send the event to.
	if ( curWin->GetName().Contains(wxT("GLCanvas")) )
	{
		((VeraPane *) curWin)->resized(event);
	}
}

void VizFrame::OnIda(wxCommandEvent& event)
{
	wxToolBar *newToolBar = new wxToolBar(this, wxID_ANY);
	wxBitmap * tmp = bmpIda;

	// Disabled to get IDA ready to run code
	if (this->idaServer == NULL)
	{
		//idaServer = new threadIdaServer(this);
		//idaServer->Create();
		//idaServer->Run();

		bmpIda = new wxBitmap(idaConnected_32_xpm);
	}
	else
	{
		//idaServer->Delete();
		//idaServer = NULL;

		bmpIda = new wxBitmap(ida_32_xpm);
	}
	
	delete tmp;

	// Draw the new toolbar with the new buttons
	this->SetVeraToolbar(newToolBar);
	newToolBar->Realize();

	// Clear the memory of the old one
	delete toolBar;
	toolBar = newToolBar;
}

// Stub, needs to be finished
bool VizFrame::sendIdaMsg(char *msg)
{
	/*if (idaServer != NULL)
		return idaServer->sendData(msg, strlen(msg));
	else
	return false;*/

	return true;
}