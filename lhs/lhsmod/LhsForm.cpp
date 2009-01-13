#include "StdAfx.h"
#include "LhsForm.h"
#include "SensitivityAnalysis.h"

using namespace lhsmod;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Text;
using namespace System::Text::RegularExpressions;




LhsForm::LhsForm(void)
{
	InitializeComponent();
}



LhsForm::~LhsForm()
{
	if( components ) {
		delete components;
	}
}



System::Void
LhsForm::OnBrowseDml(System::Object^  sender, System::EventArgs^  e)
{
  OpenFileDialog ^ ofd = gcnew OpenFileDialog();
  ofd->Filter = "Dengue Model Locations (*.dml)|*.dml";
  if( ofd->ShowDialog() == ::DialogResult::OK ) {
    tboxDml->Text = ofd->FileName;
  }
}



System::Void
LhsForm::OnBrowseLsp(System::Object^  sender, System::EventArgs^  e)
{
  OpenFileDialog ^ ofd = gcnew OpenFileDialog();
  ofd->Filter = "LHSWIN Output File (*.lsp)|*.lsp";
  if( ofd->ShowDialog() == ::DialogResult::OK ) {
    tboxLsp->Text = ofd->FileName;
  }
}



System::Void
LhsForm::OnBrowseOutput(System::Object^  sender, System::EventArgs^  e)
{
  FolderBrowserDialog ^ fbd = gcnew FolderBrowserDialog();
  fbd->SelectedPath = Environment::CurrentDirectory;
  if( fbd->ShowDialog() == ::DialogResult::OK ) {
    tboxOutput->Text = fbd->SelectedPath;
  }
}



System::Void
LhsForm::OnRun(System::Object^  sender, System::EventArgs^  e)
{
  // sanity checks on filenames and directories
  if( !File::Exists( tboxDml->Text ) ) {
    MessageBox::Show( "Unable to locate specified DML file.", "Error" );
    return;
  }
  if( !File::Exists( tboxLsp->Text ) ) {
    MessageBox::Show( "Unable to locate specified LSP file.", "Error" );
    return;
  }
  if( !Directory::Exists( tboxOutput->Text ) ) {
    MessageBox::Show( "Unable to locate specified root directory.", "Error" );
    return;
  }


  // read base dml file
  String ^ baseDmlFilename = tboxDml->Text;
  gui::DmlFile ^ baseDml = gcnew gui::DmlFile( baseDmlFilename );
  gui::Location ^ baseLocation = baseDml->Location;


  // read lsp file
  System::IO::StreamReader ^ sr = gcnew System::IO::StreamReader( tboxLsp->Text );
  String ^ s;

  // advance to UNCERTAINTY block
  while( true ) {
    String ^ s = sr->ReadLine();
    if( s == "@UNCERTAINTY" ) {
      break;
    }
  }

  // read number of params and runs for this file
  Regex ^ r = gcnew Regex( "\\d+" );
  Match ^ m;

  s = sr->ReadLine();
  m = r->Match( s );
  int numRuns = Convert::ToInt32( m->Value );

  s = sr->ReadLine();
  m = r->Match( s );
  int numParams = Convert::ToInt32( m->Value );


  // parameter names in ordered parsed
  Generic::List<String^> ^ sampledParameterNamesInOrder = gcnew Generic::List<String^>();

  for( int i = 1; i <= numParams; ++i ) {
    s = sr->ReadLine();
    s = s->Trim( gcnew array<wchar_t>{' ',':'} );
    sampledParameterNamesInOrder->Add( s );
  }


  // advance to SAMPLEDATA block
  while( true ) {
    String ^ s = sr->ReadLine();
    if( s == "@SAMPLEDATA" ) {
      break;
    }
  }


  // collection of sampled parameter values in order encountered
  Generic::List<Generic::List<double>^> ^ allRuns = gcnew   Generic::List<Generic::List<double>^>();

  // parse each run
  for( int i = 1; i <= numRuns; ++i ) {

    // sampled parameters for current run
    Generic::List<double> ^ thisRun = gcnew Generic::List<double>();

    while( true ) {
      // parse line into separate values
      s = sr->ReadLine();
      Regex ^ rr = gcnew Regex( "\\-?\\d+(\\.\\d+)?([E|D]\\-?\\d+)?" );
      MatchCollection ^ mc = rr->Matches( s );
      for each( Match ^ m in mc ) {
        thisRun->Add( Convert::ToDouble(m->Value) );
      }

      // check if all params have been read and then cleanup
      if( thisRun->Count >= numParams + 2 ) {
        // remove first two values (index and param count)
        thisRun->RemoveAt(0);
        thisRun->RemoveAt(0);
        break;
      }
    }


    // create directory for this run
    DirectoryInfo ^ baseDir = gcnew DirectoryInfo( tboxOutput->Text );
    DirectoryInfo ^ runDir = gcnew DirectoryInfo( baseDir->FullName + "\\run " + i );
    if( !runDir->Exists ) {
      runDir->Create();
    }

    // create dml file for this run
    SensitivityAnalysis::ModifyLocation( baseLocation, sampledParameterNamesInOrder, thisRun );
    FileInfo ^ baseFile = gcnew FileInfo( tboxDml->Text );
    String ^ baseFileName = baseFile->Name;

    gui::DmlFile ^ runFile = gcnew gui::DmlFile( runDir + "\\run " + i + ".dml", baseLocation );
    runFile->Save();

    // save current run
    allRuns->Add( thisRun );
  }



}
