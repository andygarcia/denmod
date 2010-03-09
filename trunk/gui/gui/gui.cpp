// gui.cpp : main project file.

#include "stdafx.h"
#include "MainForm.h"

using namespace gui;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 


#ifdef _DEBUG
  // resize console
  System::Console::BufferWidth = 120;
  System::Console::BufferHeight = 1024;
  System::Console::SetWindowSize( 120, 48 );

  // have console listen to trace output
  System::Diagnostics::ConsoleTraceListener ^ ctl = gcnew System::Diagnostics::ConsoleTraceListener();
  System::Diagnostics::Trace::Listeners->Add(ctl);
  System::Diagnostics::Trace::WriteLine( "Dengue Models Startup" );

  // write args
  for each( System::String ^ s in args ) {
    System::Console::WriteLine( "args[{0}] = {1}", Array::IndexOf( args, s ), s );
  }
#endif

  if( args->Length > 0 ) {
    // dml file was double clicked
    Application::Run(gcnew MainForm(args[0]));
  }
  else {
    Application::Run(gcnew MainForm());
  }
  return 0;
}
