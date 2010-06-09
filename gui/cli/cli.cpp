#include "stdafx.h"

using namespace System;
using namespace System::Collections;
using namespace System::IO;
using namespace gui;

void PrintUsage(void);


int main( array<String ^> ^args )
{
  int numArguments = args->Length;


  // no command line arguments, print usage
  if( numArguments == 0 ) {
    PrintUsage();
    return 0;
  }


  // assume single argument is dml file
  if( numArguments == 1 ) {

    // check for file existing before running
    String ^ filename = args[0];
    if( !IO::File::Exists(filename) ) {
      System::Console::WriteLine( filename + " does not exist" );
      return 1;
    }
    else {
      // file exists, but no other arguments
      PrintUsage();
      return 0;
    }
  }


  // multiple arguments
  else {
    String ^ filename;
    Generic::List<String^> ^ slashArgs = gcnew Generic::List<String^>();

    // parse filename and slash arguments
    for( int i = 0; i < args->Length; ++i ) {
      if( args[i]->StartsWith( "/" ) ) {
        slashArgs->Add( args[i]->Substring(1)->ToLower() );
      }
      else {
        filename = args[i];
      }
    }

    // open dml file
    Console::WriteLine( "Opening " + filename );
    gui::DmlFile ^ df = gcnew gui::DmlFile( filename );
    gui::Location ^ location = df->Location;
    DirectoryInfo ^ dir = gcnew DirectoryInfo( Path::GetDirectoryName(df->Filename) );
    if( df->IsValid == false ) {
      Console::WriteLine( "DML file is corrupt." );
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

      // create log file with error message and signal error in return
      FileStream ^ fs = gcnew FileStream( Path::Combine(dir->FullName, "errorLog.txt"), System::IO::FileMode::Create );
      StreamWriter ^ sw = gcnew StreamWriter( fs );
      sw->Write( ValidationFramework::ResultFormatter::GetConcatenatedErrorMessages("\n", location->Biology->PropertyValidationManager->ValidatorResultsInError) );
      sw->Close();
      return 2;
    }

    bool saveCimsim = slashArgs->Contains( "cimsim" );
    bool saveDensim = slashArgs->Contains( "densim" );
    bool doExtendedOutput = slashArgs->Contains( "extoutput" );

    // create user settings
    gui::UserSettings ^ us = gcnew UserSettings();
    us->DoSimulationDiskOutput = false;
    us->EstablishedPopulationDefault = true;
    location->UserSettings = us;

    // run and save cimsim only
    if( saveCimsim && !saveDensim ) {
      Console::WriteLine( "Running cimsim" );
      location->RunCimsim( true );
      Console::WriteLine( "Saving cimsim output" );
      location->CimsimOutput->SaveToDisk( dir );
    }


    // run densim (and cimsim) and save densim only
    if( !saveCimsim && saveDensim ) {
      Console::WriteLine( "Running cimsim" );
      location->RunCimsim( true );
      Console::WriteLine( "Running densim " );
      location->RunDensim();
      Console::WriteLine( "Saving densim output" );
      location->DensimOutput->SaveToDisk( dir );
    }


    // run and save densim and cimsim
    if( saveCimsim && saveDensim ) {
      Console::WriteLine( "Running cimsim" );
      location->RunCimsim( true );
      Console::WriteLine( "Saving cimsim output" );
      location->CimsimOutput->SaveToDisk( dir );
      Console::WriteLine( "Running densim " );
      location->RunDensim();
      Console::WriteLine( "Saving densim output" );
      location->DensimOutput->SaveToDisk( dir );
    }
  }
  return 0;
}



void PrintUsage(void)
{
  Console::WriteLine( "Runs cimsim and densim on specified DML file, saving output to same   " );
  Console::WriteLine( "directory where DML file is located.                                  " );
  Console::WriteLine( "                                                                      " );
  Console::WriteLine( "dmcli.exe /cimsim /densim filename.dml                                " );
  Console::WriteLine( "                                                                      " );
  Console::WriteLine( "  /cimsim - runs cimsim and saves cimsim output                       " );
  Console::WriteLine( "  /densim - runs densim (and cimsim), saves densim output             " );
  Console::WriteLine( "                                                                      " );
  Console::WriteLine( "Note that if only /densim is used, only densim output is saved.       " );
  Console::WriteLine( "Use both /cimsim and /densim to run and save outputs from both models." );
}


