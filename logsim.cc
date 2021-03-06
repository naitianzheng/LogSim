#include "logsim.h"
#include "userint.h"
#include "gui.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define USE_GUI

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
  // This function is automatically called when the application starts
{

  // Construct the six classes required by the innards of the logic simulator
  nmz = new names();
  netz = new network(nmz);
  dmz = new devices(nmz, netz);
  mmz = new monitor(nmz, netz);

#ifdef USE_GUI
  // glutInit cannot cope with Unicode command line arguments, so we pass
  // it some fake ASCII ones instead
  char **tmp1; int tmp2 = 0; glutInit(&tmp2, tmp1);
  // Construct the GUI
  MyFrame *frame = new MyFrame(
    NULL, 
    "Logic simulator", 
    wxDefaultPosition,  
    wxSize(800, 600), 
    nmz, dmz, mmz, netz);
    if((argc==1)||(argc==2))
    {
      frame->Show(true);
	  if(argc==2)
	  {
		frame->filePath = wxString(argv[1]);
		frame->loadFile(wxString(argv[1]));
	  }
	  return(true); 
	}
  else if ((argc==3)&&(argv[2]=="-c"))
  {
	  std::cout << "Command line user interface is invoked.\n";
	  smz = new scanner(nmz, wxString(argv[1]).mb_str());
	  pmz = new parser(netz, dmz, mmz, smz, nmz);
	  if (pmz->readin ()) { // check the logic file parsed correctly
		// Construct the text-based interface
		userint umz(nmz, dmz, mmz);
		umz.userinterface();	
	}  
  }
  else
  {
	  if(argc==3)
	  {
		  std::cout << "Wrong arguments.\n";
	  }
	  else
	  {
		std::cout << "Too many arguments\n";
	  }
	  std::cout << "Usage:    " << argv[0] << "                to invoke GUI." << endl;
	  std::cout << "Usage:    " << argv[0] << " [filename],    to invoke GUI with [filename loaded]" << endl;
	  std::cout << "Usage:    " << argv[0] << " [filename] -c, to invoke command user interface." << endl;
  }
  return(false); // enter the GUI event loop
#else
  if (argc != 2) { // check we have one command line argument
    wcout << "Usage:      " << argv[0] << " [filename]" << endl;
    exit(1);
  }
  smz = new scanner(nmz, wxString(argv[1]).mb_str());
  pmz = new parser(netz, dmz, mmz, smz, nmz);
  if (pmz->readin ()) { // check the logic file parsed correctly
    // Construct the text-based interface
    userint umz(nmz, dmz, mmz);
    umz.userinterface();
  }
#endif /* USE_GUI */

  return(false); // exit the application
}
