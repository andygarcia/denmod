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

  if( args->Length == 0 ) {
    Application::Run(gcnew MainForm());
  }

  else if( args->Length == 1 ) {
    // assume only argument is dml file
    String ^ filename = args[0];

    // check for file existing before running
    if( !IO::File::Exists(filename) ) {
      System::Console::WriteLine( filename + " does not exist" );
      MessageBox::Show( filename + " does not exist" );
      return 1;
    }

    // run application, opening the specified dml file
    Application::Run( gcnew MainForm(filename) );
  }

  else {
    // more than one argument
    String ^ filename;
    Generic::List<String^> ^ slashArgs = gcnew Generic::List<String^>();

    // parse filename and slash arguments
    for( int i = 0; i < args->Length; ++i ) {
      if( args[i]->StartsWith( "/" ) ) {
        slashArgs->Add( args[i]->Substring(1) );
      }
      else {
        filename = args[i];
      }
    }

    // see if we're running and saving output
    if( slashArgs->Contains("saverun") ) {

      // open dml file
      gui::DmlFile ^ df = gcnew gui::DmlFile( filename );
      gui::Location ^ location = df->Location;
      DirectoryInfo ^ dir = gcnew DirectoryInfo( Path::GetDirectoryName(filename) );

      if( df->IsValid == false ) {
        Console::WriteLine( "DML file is corrupt." );
        MessageBox::Show( "DML file is corrupt." );
        return 1;
      }

      // check for errors in location's parameters
      location->Biology->PropertyValidationManager->ValidateAllProperties();
      if( !location->Biology->IsValid ) {
        // delete error log if already present
        String ^ logFilename = Path::Combine( dir->FullName, "errors.txt" );
        if( File::Exists( logFilename ) ) {
          File::Delete( logFilename );
        }

        // create log file with error message
        FileStream ^ fs = gcnew FileStream( Path::Combine(dir->FullName, "errorLog.txt"), System::IO::FileMode::Create );
        StreamWriter ^ sw = gcnew StreamWriter( fs );
        sw->Write( ValidationFramework::ResultFormatter::GetConcatenatedErrorMessages("\n", location->Biology->PropertyValidationManager->ValidatorResultsInError) );
        sw->Close();

        // signal parameter error in return value
        return 2;
      }

      // run cimsim using established population and continuous cohort counts
      Console::WriteLine( "Running cimsim" );
      location->RunCimsim( true, false);

      // save cimsim output if requested
      if( slashArgs->Contains("cimsim") ) {
        Console::WriteLine( "Saving cimsim output" );
        location->CimsimOutput->SaveToDisk( dir );
      }

      // run densim and save output only if specified
      if( slashArgs->Contains("densim") ) {
        Console::WriteLine( "Running densim " );
        location->RunDensim();
        Console::WriteLine( "Saving densim output" );
        location->DensimOutput->SaveToDisk( dir );
      }
    }

  }

  return 0;
}
