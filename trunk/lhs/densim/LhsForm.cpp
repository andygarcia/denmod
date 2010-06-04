#include "StdAfx.h"
#include "LhsForm.h"
#include "SensitivityAnalysis.h"

using namespace lhsmod;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Text;
using namespace System::Text::RegularExpressions;



LhsForm::LhsForm(void)
: _simulationThreads(gcnew List<BackgroundWorker^>()),
  _simulationStack(gcnew SimulationStack()),
  _simulationThreadsCompleted(0),
  _closeForm(false),
  _runningStudy(false)
{
	InitializeComponent();

  _fileReader = gcnew BackgroundWorker();
  _fileReader->WorkerReportsProgress = true;
  _fileReader->WorkerSupportsCancellation = true;
  _fileReader->DoWork += gcnew DoWorkEventHandler( this, &LhsForm::ReadFiles );
  _fileReader->ProgressChanged += gcnew ProgressChangedEventHandler( this, &LhsForm::ReadFilesProgressChanged );
  _fileReader->RunWorkerCompleted += gcnew RunWorkerCompletedEventHandler( this, &LhsForm::ReadFilesCompleted );

  // create a background worker thread
  for( int i = 0; i < Environment::ProcessorCount * 2; ++i ) {
    BackgroundWorker ^ worker = gcnew BackgroundWorker();
    worker->WorkerReportsProgress = true;
    worker->WorkerSupportsCancellation = true;
    worker->DoWork += gcnew DoWorkEventHandler( this, &LhsForm::StartSimulations );
    worker->ProgressChanged += gcnew ProgressChangedEventHandler( this, &LhsForm::SimulationsProgressChanged );
    worker->RunWorkerCompleted += gcnew RunWorkerCompletedEventHandler( this, &LhsForm::SimulationsCompleted );
    _simulationThreads->Add( worker );
  }
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
    tboxDml->Enabled = false;
    tboxLsp->Enabled = false;
    tboxOutput->Enabled = false;
    btnRun->Enabled = false;
    //btnRun->Text = "Pause";

    // signal start of study to user
    AppendToOutput( "Beginning sensitivity analysis study" + Environment::NewLine );

    // create study and start by reading and parsing input files
    SensitivityAnalysisParser ^ parser = gcnew SensitivityAnalysisParser( tboxDml->Text, tboxLsp->Text, tboxOutput->Text );
    _fileReader->RunWorkerAsync( parser );
  }

  //// run already in progress
  //else if( btnRun->Text == "Cancel" ) {
  //  ::DialogResult dr = MessageBox::Show( "Are you sure you want to stop this study?", "Stop study?",
  //                                      MessageBoxButtons::OKCancel, MessageBoxIcon::Question, MessageBoxDefaultButton::Button2 );

  //  if( dr == ::DialogResult::OK ) {
  //    // cancel study
  //    //_backgroundWorker->CancelAsync();
  //  }
  //  else if( dr == ::DialogResult::Cancel ) {
  //    // do nothing
  //  }
  //}
}



System::Void
LhsForm::ReadFiles( Object ^ sender, DoWorkEventArgs ^ e )
{
  // background worker to read and parse files before moving onto simulation
  BackgroundWorker ^ bw = static_cast<BackgroundWorker^>( sender );
  List<String^> ^ filenames = gcnew List<String^>();
  SensitivityAnalysisParser ^ parser = static_cast<SensitivityAnalysisParser^>( e->Argument );

  // parse study passing bw to allow progress reporting
  _runningStudy = true;
  SimulationStack ^ ss = parser->ParseStudy( bw, e );

  // return files that were parsed
  e->Result = ss;
}  



System::Void
LhsForm::ReadFilesProgressChanged( Object ^ sender, ProgressChangedEventArgs ^ e )
{
  FileReadProgress ^ frp = static_cast<FileReadProgress^>( e->UserState );
  double percent = (double) frp->TotalFileCount / frp->CurrentFileCount;
  pbarRuns->Maximum = frp->TotalFileCount;
  _numberOfRuns = frp->TotalFileCount;
  pbarRuns->Value = frp->CurrentFileCount;
  for each( String ^ s in frp->Messages ) {
    AppendToOutput( s + Environment::NewLine );
  }
}



System::Void
LhsForm::ReadFilesCompleted( Object ^ sender, RunWorkerCompletedEventArgs ^ e )
{
  if( e->Error != nullptr ) {
    AppendToOutput( "Error while reading input files: " + e->Error->Message + Environment::NewLine );
  }
  else if( e->Cancelled ) {
    AppendToOutput( "Sensitivity analysis study cancelled during file reading phase." + Environment::NewLine );
    _runningStudy = false;
    Close();
    return;
  }
  else {
    // successful, flip flop stack from parser for now, fix with heap/queue
    _simulationStack = gcnew SimulationStack();
    SimulationStack ^ ss = static_cast<SimulationStack^>( e->Result );
    while( ss->Count != 0 ) {
      _simulationStack->Push(ss->Pop());
    }

    // reset progress bar
    pbarRuns->Value = 0;
    pbarRuns->Maximum = _simulationStack->Count;

    // move on to running simulation and spawn threads
    _simulationThreadsCompleted = 0;
    for( int i = 0; i < _simulationThreads->Count; ++i ) {
      _simulationThreads[i]->RunWorkerAsync( _simulationStack );
    }
    lblActiveSimulationThreads->Visible = true;
    lblActiveSimulationThreads->Text = String::Format( "Active simulation threads: {0}", _simulationThreads->Count );
  }
}



void
LhsForm::StartSimulations( Object ^ sender, DoWorkEventArgs ^ e )
{
  // access simulation stack
  BackgroundWorker ^ bw = dynamic_cast<BackgroundWorker^>( sender );
  SimulationStack ^ simStack = static_cast<SimulationStack^>( e->Argument );
  
  // open excel via interop and disable errors and warnings
  Excel::Application ^ ea = gcnew Excel::Application();
  ea->DisplayAlerts = false;

  // filenames we will convert for each run
  array<String^> ^ _outputFilenames;

  // process files from stack until empty
  String ^ filename = nullptr;
  while( true ) {
    // check for cancel
    if( bw->CancellationPending ) {
      e->Cancel = true;
      return;
    }

    // attempt to pop next simulation filename
    try {
      filename = simStack->Pop();
    }
    catch (InvalidOperationException ^ ioe ) {
      // stack should be empty
      Diagnostics::Debug::WriteLine( ioe->ToString() );
      break;
    }

    // create process info for running models in batch mode via dmcli.exe
    Diagnostics::Process ^ proc = gcnew Diagnostics::Process();

    proc->StartInfo->UseShellExecute = false;
    proc->StartInfo->CreateNoWindow = true;

    proc->StartInfo->FileName = Path::Combine( Path::GetDirectoryName(Application::ExecutablePath), "dmcli.exe" );
    proc->StartInfo->Arguments = "/densim " + "\"" + filename + "\"";

    // start dmcli and block until it has completed
    proc->Start();
    proc->BeginOutputReadLine();
    proc->WaitForExit();

    if( bw->CancellationPending ) {
      e->Cancel = true;
      return;
    }


    // report based on dmlcli's exit code
    StudyProgress ^ sp = gcnew StudyProgress();
    if( proc->ExitCode == 2 ) {
      sp->NumberOfRunsDiscarded = 1;
      sp->NumberOfRunsCompleted = 0;
      sp->Messages->Add( "Parameter errors in " + filename +". See errors.txt." );
      bw->ReportProgress( 0, sp );
      continue;
    }
    else if( proc->ExitCode == 0 ) {
      sp = gcnew StudyProgress();
      sp->NumberOfRunsDiscarded = 0;
      sp->NumberOfRunsCompleted = 1;
      sp->Messages->Add( "Completed simulation for " + filename +"." );
      bw->ReportProgress( 0, sp );
    }

    // check for cancel
    if( bw->CancellationPending ) {
      e->Cancel = true;
      return;
    }

    // first time generate list of filenames that will be converted post simulation for each subsequent run
    DirectoryInfo ^ runDir = gcnew DirectoryInfo( Path::GetDirectoryName(filename) );
    if( _outputFilenames == nullptr ) {
      // first look for all excel .xml files in current run directory
      array<FileInfo^> ^ xmlFiles = runDir->GetFiles( "*.xml", SearchOption::TopDirectoryOnly );
      
      // we only want the filename, not path (changes each time)
      _outputFilenames = gcnew array<String^>(xmlFiles->Length);
      for( int i = 0; i < xmlFiles->Length; ++i ) {
        _outputFilenames[i] = xmlFiles[i]->Name;
      }
    }

    // convert output files from Excel's xml format to binary format
    for each( String ^ filename in _outputFilenames ) {
      // open from this directory
      String ^ xmlFilename = Path::Combine( runDir->FullName, filename );

      // open and disable compatability check
      Excel::Workbook ^ xmlFile = ea->Workbooks->Open(xmlFilename, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing );
      xmlFile->CheckCompatibility = false;

      // save as excel 97-2003 format, changing extension, close and delete old workbook
      xmlFile->SaveAs( Path::ChangeExtension( xmlFilename, ".xls" ), Excel::XlFileFormat::xlExcel8, Type::Missing, Type::Missing, Type::Missing, false, Excel::XlSaveAsAccessMode::xlNoChange, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing );
      xmlFile->Close( false, Type::Missing, Type::Missing );
      //ea->Workbooks->Close();
      delete xmlFile;
      File::Delete( xmlFilename );
    }

    // check for cancel
    if( bw->CancellationPending ) {
      e->Cancel = true;
      return;
    }
  }
}



System::Void
LhsForm::SimulationsProgressChanged( Object ^ sender, ProgressChangedEventArgs ^ e )
{
  // check current state
  StudyProgress ^ sp = dynamic_cast<StudyProgress^>( e->UserState );

  // update progress bar
  pbarRuns->Value += sp->NumberOfRunsDiscarded;
  pbarRuns->Value += sp->NumberOfRunsCompleted;

  // write message to output
  for each( String ^ s in sp->Messages ) {
    AppendToOutput( s + Environment::NewLine );
  }
}



System::Void
LhsForm::SimulationsCompleted( Object ^ sender, RunWorkerCompletedEventArgs ^ e )
{
  // a simulation thread has completed, calculate how many threads are active
  _simulationThreadsCompleted++;
  int activeThreads = _simulationThreads->Count - _simulationThreadsCompleted;
  lblActiveSimulationThreads->Text = String::Format("Active simulation threads: {0}", activeThreads);

  if( e->Error != nullptr ) {
    AppendToOutput( "Error while running simulations: " + e->Error->Message + Environment::NewLine );
    // start a replacement thread

  }
  else if( e->Cancelled == true ) {
    AppendToOutput( "Simulation thread stopped." + Environment::NewLine );
    if( activeThreads == 0 && _closeForm ) {
      AppendToOutput( "Sensitivity analysis study cancelled during simulation phase." + Environment::NewLine );
      _runningStudy = false;
      Close();
      return;
    }
  }
  else {
    AppendToOutput( "Simulation thread completed." + Environment::NewLine );
    if( activeThreads == 0 ) {
      btnBrowseDml->Enabled = true;
      btnBrowseLsp->Enabled = true;
      btnBrowseOutput->Enabled = true;
      tboxDml->Enabled = true;
      tboxLsp->Enabled = true;
      tboxOutput->Enabled = true;
      btnRun->Enabled = true;

      AppendToOutput( "Completed sensitivity analysis study." + Environment::NewLine );
      lblActiveSimulationThreads->Visible = false;
      _runningStudy = false;
    }
  }
}



void
LhsForm::AppendToOutput( String ^ s )
{
  rboxOutput->AppendText( s );
  rboxOutput->SelectionStart = rboxOutput->Text->Length;
}



System::Void
LhsForm::OnFormClosing( Object ^ sender, FormClosingEventArgs ^ e )
{
  if( _runningStudy && e->CloseReason == ::CloseReason::UserClosing ) {
    e->Cancel = true;

    // check if already in process of closing while study is running
    if( _closeForm == true ) {
      return;
    }

    // confirm user wants to stop study
    if( ConfirmStudyCancel() ) {
      AppendToOutput( "Program is closing, please while wait background operations are stopped." + Environment::NewLine );
      _fileReader->CancelAsync();
      for each( BackgroundWorker ^ bw in _simulationThreads ) {
        bw->CancelAsync();
      }
      _closeForm = true;
    }
  }
}



System::Void
LhsForm::OnFormClosed( Object ^ sender, FormClosedEventArgs ^ e )
{
  AppendToOutput( "Program closed." );

  String ^ filename = Path::Combine( tboxOutput->Text, "lhsmodlog.txt" );
  rboxOutput->SaveFile( filename, RichTextBoxStreamType::PlainText );
}



bool
LhsForm::ConfirmStudyCancel(void)
{
  ::DialogResult dr = MessageBox::Show( "A study is currently running.  Do you want to stop the study?",
                                        "Stop running study?",
                                        MessageBoxButtons::YesNo,
                                        MessageBoxIcon::Hand,
                                        MessageBoxDefaultButton::Button2 );

  if( dr == ::DialogResult::Yes ) {
    return true;
  }
  else {
    return false;
  }
}
