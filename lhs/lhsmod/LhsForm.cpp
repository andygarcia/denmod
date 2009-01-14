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
  InitializeBackgroundWorker();
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



void
LhsForm::InitializeBackgroundWorker(void)
{
  _backgroundWorkerCimsim = gcnew BackgroundWorker();

  _backgroundWorkerCimsim->DoWork += gcnew DoWorkEventHandler( this, &LhsForm::DoRuns );
  
  _backgroundWorkerCimsim->WorkerReportsProgress = true;
  _backgroundWorkerCimsim->ProgressChanged += gcnew ProgressChangedEventHandler( this, &LhsForm::RunProgressChanged );

  _backgroundWorkerCimsim->WorkerSupportsCancellation = true;
  _backgroundWorkerCimsim->RunWorkerCompleted += gcnew RunWorkerCompletedEventHandler( this, &LhsForm::FinishedRuns );
}




void
LhsForm::DoRuns( Object ^ sender, DoWorkEventArgs ^ e )
{
  BackgroundWorker ^ bw = dynamic_cast<BackgroundWorker^>( sender );

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

  // initial update
  StudyState ^ ss = gcnew StudyState();
  ss->NumberRuns = numRuns;
  ss->CurrentRun = 0;
  bw->ReportProgress( 0, ss );
    
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
    // begin run
    DateTime runStartTime = DateTime::Now;

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

    // save current run
    allRuns->Add( thisRun );

    // create directory for this run
    DirectoryInfo ^ baseDir = gcnew DirectoryInfo( tboxOutput->Text );
    DirectoryInfo ^ runDir = gcnew DirectoryInfo( baseDir->FullName + "\\run " + i );
    if( !runDir->Exists ) {
      runDir->Create();
    }

    // modify location with sampled parameters values
    SensitivityAnalysis::ModifyLocation( baseLocation, sampledParameterNamesInOrder, thisRun );
    // create dml file for this run
    gui::DmlFile ^ runFile = gcnew gui::DmlFile( runDir + "\\run " + i + ".dml", baseLocation );
    runFile->Save();


    if( bw->CancellationPending ) {
      e->Cancel = true;
      return;
    }

    baseLocation->RunCimsim( true );

    if( bw->CancellationPending ) {
      e->Cancel = true;
      return;
    }

    baseLocation->SaveCimsimOutput( runDir );

    if( bw->CancellationPending ) {
      e->Cancel = true;
      return;
    }

    // end run
    DateTime runStopTime = DateTime::Now;


    // update progress
    StudyState ^ ss = gcnew StudyState();
    ss->NumberRuns = numRuns;
    ss->CurrentRun = i;
    ss->RunTime = runStopTime - runStartTime;
    bw->ReportProgress( i, ss );
  }
}



void
LhsForm::RunProgressChanged( Object ^ sender, ProgressChangedEventArgs ^ e )
{
  // check current state
  StudyState ^ ss = dynamic_cast<StudyState^>( e->UserState );

  // update progress bar
  pbarRuns->Maximum = ss->NumberRuns;
  pbarRuns->Value = ss->CurrentRun;

  // update run status
  lblCompletedRuns->Text = "Runs Completed: " + ss->CurrentRun + "/" + ss->NumberRuns;

  // update estimated time
  int runsRemaining = ss->NumberRuns - ss->CurrentRun;
  Int64 ticksRemaining = ss->RunTime.Ticks * runsRemaining;
  TimeSpan timeRemaining = TimeSpan( ticksRemaining );

  int hours = timeRemaining.Hours;
  int minutes = timeRemaining.Minutes;
  int seconds = timeRemaining.Seconds;
  String ^ update = String::Format( "Estimated Time Left: {0:D2}:{1:D2}:{2:D2}", hours, minutes, seconds );
  lblEstimatedTime->Text = update;
}



void
LhsForm::FinishedRuns( Object ^ sender, RunWorkerCompletedEventArgs ^ e )
{
  btnBrowseDml->Enabled = true;
  btnBrowseLsp->Enabled = true;
  btnBrowseOutput->Enabled = true;
  tboxDml->Enabled = true;
  tboxLsp->Enabled = true;
  tboxOutput->Enabled = true;
  btnRun->Text = "Run";
}



System::Void
LhsForm::OnRun(System::Object^  sender, System::EventArgs^  e)
{
  if( btnRun->Text == "Run" ) {
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

    // disable ui elements during run
    btnBrowseDml->Enabled = false;
    btnBrowseLsp->Enabled = false;
    btnBrowseOutput->Enabled = false;
    tboxDml->Enabled = false;
    tboxLsp->Enabled = false;
    tboxOutput->Enabled = false;
    btnRun->Text = "Cancel";

    _backgroundWorkerCimsim->RunWorkerAsync();
  }
  else if( btnRun->Text == "Cancel" ) {
    ::DialogResult dr = MessageBox::Show( "Are you sure you want to stop execution of this study?", "Stop study?",
                                        MessageBoxButtons::OKCancel, MessageBoxIcon::Question, MessageBoxDefaultButton::Button2 );

    if( dr == ::DialogResult::OK ) {
      // cancel DoRuns threads
      _backgroundWorkerCimsim->CancelAsync();
    }
    else if( dr == ::DialogResult::Cancel ) {
      // do nothing
    }
    else {
      throw gcnew InvalidOperationException();
    }
  }
  else {
    throw gcnew InvalidOperationException();
  }
}
