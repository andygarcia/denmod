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

  _fileReader;


  _backgroundWorker = gcnew BackgroundWorker();
  _backgroundWorker->WorkerReportsProgress = true;
  _backgroundWorker->WorkerSupportsCancellation = true;
  _backgroundWorker->DoWork += gcnew DoWorkEventHandler( this, &LhsForm::StartStudy);
  _backgroundWorker->ProgressChanged += gcnew ProgressChangedEventHandler( this, &LhsForm::StudyProgressChanged);
  _backgroundWorker->RunWorkerCompleted += gcnew RunWorkerCompletedEventHandler( this, &LhsForm::StudyCompleted);
}



LhsForm::~LhsForm()
{
	if( components ) {
		delete components;
	}
}



System::Void
LhsForm::OnBrowseDml( System::Object ^ sender, System::EventArgs ^ e )
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
  if( btnRun->Text == "Run" ) {
    // check that specified files and directory exists
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
    chkDiscrete->Enabled = false;
    tboxDml->Enabled = false;
    tboxLsp->Enabled = false;
    tboxOutput->Enabled = false;
    btnRun->Enabled = false;
    //btnRun->Text = "Pause";

    // create and run study
    _study = gcnew SensitivityAnalysisStudy( _backgroundWorker, tboxDml->Text, tboxLsp->Text, tboxOutput->Text, chkDiscrete->Checked, chkProcessOnly->Checked );
    _backgroundWorker->RunWorkerAsync();
  }

  // run already in progress
  else if( btnRun->Text == "Cancel" ) {
    ::DialogResult dr = MessageBox::Show( "Are you sure you want to stop this study?", "Stop study?",
                                        MessageBoxButtons::OKCancel, MessageBoxIcon::Question, MessageBoxDefaultButton::Button2 );

    if( dr == ::DialogResult::OK ) {
      // cancel study
      _backgroundWorker->CancelAsync();
    }
    else if( dr == ::DialogResult::Cancel ) {
      // do nothing
    }
  }
}



void
LhsForm::StartStudy( Object ^ sender, DoWorkEventArgs ^ e )
{
  BackgroundWorker ^ bw = dynamic_cast<BackgroundWorker^>( sender );
  _study->StartStudy( bw );
}



void
LhsForm::StudyProgressChanged( Object ^ sender, ProgressChangedEventArgs ^ e )
{
  // check current state
  SensitivityAnalysisStudy::StudyState ^ ss = dynamic_cast<SensitivityAnalysisStudy::StudyState^>( e->UserState );

  // update progress bar
  pbarRuns->Maximum = ss->NumberOfRuns;
  pbarRuns->Value = static_cast<int>(pbarRuns->Maximum * ss->PercentCompleted);

  // write message to output
  for each( String ^ s in ss->Messages ) {
    rboxOutput->AppendText( s + Environment::NewLine );
  }
}



void
LhsForm::StudyCompleted( Object ^ sender, RunWorkerCompletedEventArgs ^ e )
{
  btnBrowseDml->Enabled = true;
  btnBrowseLsp->Enabled = true;
  btnBrowseOutput->Enabled = true;
  chkDiscrete->Enabled = true;
  tboxDml->Enabled = true;
  tboxLsp->Enabled = true;
  tboxOutput->Enabled = true;
  btnRun->Enabled = true;
}



// This method is executed in a separate thread created by the background worker.
// so don't try to access any UI controls here!! (unless you use a delegate to do it)
// this attribute will prevent the debugger to stop here if any exception is raised.
//[System.Diagnostics.DebuggerNonUserCodeAttribute()]
System::Void
LhsForm::ReadFiles( Object ^ sender, DoWorkEventArgs ^ e )
{
  // get reference to the BackgroundWorker
  BackgroundWorker ^ bw = static_cast<BackgroundWorker^>( sender );
  List<String^> ^ filenames = gcnew List<String^> ^ filenames;

  for( int i = 0; i < threadOptions->TaskCount; ++i ) {
    // loop for some amount of time between 20 and 30 seconds
    Random ^ r = gcnew Random();
    int taskTime = r->Next( minTime, maxTime );
    //int startTime = Environment::TickCount;
    //while( Environment::TickCount - startTime < taskTime ) {}

    managed_library::Simulation ^ simulation = gcnew managed_library::Simulation();
    simulation->Start( taskTime );

    // notify progress to main thread showing UserState property
    double progress = (i+1) * 100.0 / threadOptions->TaskCount;
    bw->ReportProgress( static_cast<int>( progress ), DateTime::Now );

    // Error handling: uncomment this code if you want to test how an exception is
    // handled by the background worker.  Also uncomment the mentioned attribute above
    // so it doesn't stop in the debugger.  
    //if( i == 34 ) {
    //  throw gcnew Exception( "something wrong here!!" );
    //}

    // if cancellation is pending, cancel work.
    if( bw->CancellationPending) {  
      e->Cancel = true;
      return;
    }
  }  

  e->Result = filenames;
}  
