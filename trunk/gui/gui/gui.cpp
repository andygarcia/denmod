#include "stdafx.h"
#include "MainForm.h"

using namespace gui;
using namespace System;
using namespace System::IO;


[STAThreadAttribute]
int main( array<String ^> ^args )
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

#ifdef _DEBUG
  // resize console
  Console::BufferWidth = 120;
  Console::BufferHeight = 1024;
  Console::SetWindowSize( 120, 48 );

  // have console listen to trace output
  Diagnostics::ConsoleTraceListener ^ ctl = gcnew System::Diagnostics::ConsoleTraceListener();
  Diagnostics::Trace::Listeners->Add(ctl);

  // write args
  for each( String ^ s in args ) {
    Console::WriteLine( "args[{0}] = {1}", Array::IndexOf( args, s ), s );
  }
#endif

  // command line arguments
  int numArguments = args->Length;

  // no filename specified
  if( numArguments == 0 ) {
    Application::Run(gcnew MainForm());
    return 0;
  }

  // open specified filename
  if( numArguments == 1 ) {

    // check for file existing before running
    String ^ filename = args[0];
    if( !IO::File::Exists(filename) ) {
      System::Console::WriteLine( filename + " does not exist" );
      return 1;
    }

    // run application, opening the specified dml file
    Application::Run( gcnew MainForm(filename) );
    return 0;
  }

  return 1;
}
