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
  _simulationFiles(gcnew List<String^>()),
  _simulationFilesByThread(gcnew List<List<String^>^>()),
  _simulationThreadsCompleted(0)
{
	InitializeComponent();

  _fileReader = gcnew BackgroundWorker();
  _fileReader->WorkerReportsProgress = true;
  _fileReader->WorkerSupportsCancellation = true;
  _fileReader->DoWork += gcnew DoWorkEventHandler( this, &LhsForm::ReadFiles );
  _fileReader->ProgressChanged += gcnew ProgressChangedEventHandler( this, &LhsForm::ReadFilesProgressChanged );
  _fileReader->RunWorkerCompleted += gcnew RunWorkerCompletedEventHandler( this, &LhsForm::ReadFilesCompleted );

  // create a background worker thread
  for( int i = 0; i < Environment::ProcessorCount * 1.5; ++i ) {
    BackgroundWorker ^ worker = gcnew BackgroundWorker();
    worker->WorkerReportsProgress = true;
    worker->WorkerSupportsCancellation = true;
    worker->DoWork += gcnew DoWorkEventHandler( this, &LhsForm::StartSimulations );
    worker->ProgressChanged += gcnew ProgressChangedEventHandler( this, &LhsForm::SimulationsProgressChanged );
    worker->RunWorkerCompleted += gcnew RunWorkerCompletedEventHandler( this, &LhsForm::SimulationsCompleted );
    _simulationThreads->Add( worker );
  }

  // create per thread file lists
  for( int i = 0; i < _simulationThreads->Count; ++i ) {
    _simulationFilesByThread->Add( gcnew List<String^>() );
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
    chkDiscrete->Enabled = false;
    tboxDml->Enabled = false;
    tboxLsp->Enabled = false;
    tboxOutput->Enabled = false;
    btnRun->Enabled = false;
    //btnRun->Text = "Pause";

    rboxOutput->AppendText( "Beginning sensitivity analysis study" );
    rboxOutput->SelectionStart = rboxOutput->Text->Length;

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
  filenames = parser->ParseStudy( bw );

  // return files that were parsed
  e->Result = filenames;
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
    rboxOutput->AppendText( s + Environment::NewLine );
    rboxOutput->SelectionStart = rboxOutput->Text->Length;
  }
}



System::Void
LhsForm::ReadFilesCompleted( Object ^ sender, RunWorkerCompletedEventArgs ^ e )
{
  if( e->Error != nullptr ) {
    rboxOutput->AppendText( "Error while reading input files: " + e->Error->Message + Environment::NewLine );
    rboxOutput->SelectionStart = rboxOutput->Text->Length;
  }
  else if( e->Cancelled ) {
  }
  else {
    // successful, process filenames
    List<String^> ^ _simulationFiles = static_cast<List<String^>^>( e->Result );

    // reset progress bar
    pbarRuns->Value = 0;
    pbarRuns->Maximum = _simulationFiles->Count;

    // into per thread lists
    for( int i = 0; i < _simulationFiles->Count; ) {
      for( int j = 0; j < _simulationThreads->Count; ++j ) {
        _simulationFilesByThread[j]->Add( _simulationFiles[i] );
        ++i;
        if( i == _simulationFiles->Count ) break;
      }
    }
    
    // move on to running simulation and spawn threads
    _simulationThreadsCompleted = 0;
    for( int i = 0; i < _simulationThreads->Count; ++i ) {
      _simulationThreads[i]->RunWorkerAsync( _simulationFilesByThread[i] );
    }   
  }
}



void
LhsForm::StartSimulations( Object ^ sender, DoWorkEventArgs ^ e )
{
  // access simulation files for this thread
  BackgroundWorker ^ bw = dynamic_cast<BackgroundWorker^>( sender );
  List<String^> ^ filenames = static_cast<List<String^>^>( e->Argument );
  
  // open excel via interop and disable errors and warnings
  Excel::Application ^ ea = gcnew Excel::Application();
  ea->DisplayAlerts = false;

  // filenames we will convert for each run
  array<String^> ^ _outputFilenames;

  for each( String ^ filename in filenames ) {
    // open this file and location
    gui::DmlFile ^ dmlFile = gcnew gui::DmlFile( filename );
    gui::Location ^ location = dmlFile->Location;
    DirectoryInfo ^ runDir = gcnew DirectoryInfo( Path::GetDirectoryName(filename) );
    
    // check for errors in location's parameters
    location->Biology->PropertyValidationManager->ValidateAllProperties();
    if( !location->Biology->IsValid ) {
      // delete error log if already present
      String ^ logFilename = Path::Combine( runDir->FullName, "errors.txt" );
      if( File::Exists( logFilename ) ) {
        File::Delete( logFilename );
      }

      // create log file with error message
      FileStream ^ fs = gcnew FileStream( Path::Combine(runDir->FullName, "errorLog.txt"), System::IO::FileMode::Create );
      StreamWriter ^ sw = gcnew StreamWriter( fs );
      sw->Write( ValidationFramework::ResultFormatter::GetConcatenatedErrorMessages("\n", location->Biology->PropertyValidationManager->ValidatorResultsInError) );
      sw->Close();

      // abort this run (errors), continue with next run
      StudyProgress ^ sp = gcnew StudyProgress();
      sp->NumberOfRunsDiscarded = 1;
      sp->NumberOfRunsCompleted = 0;
      sp->Messages->Add( "Parameter errors in " + filename +". See errors.txt." );
      bw->ReportProgress( 0, sp );
      continue;
    }

    // report on starting a simulation
    StudyProgress ^ sp = gcnew StudyProgress();
    sp->NumberOfRunsDiscarded = 0;
    sp->NumberOfRunsCompleted = 0;
    sp->Messages->Add( "Starting simulation for " + filename +"." );
    bw->ReportProgress( 0, sp );

    // do simulation and save output
    location->RunCimsim( true, false );
    location->CimsimOutput->SaveToDisk( runDir );

    // first time generate list of filenames that will be converted post simulation for each subsequent run
    if( _outputFilenames == nullptr ) {
      // first look for all excel .xml files in current run directory
      array<FileInfo^> ^ xmlFiles = runDir->GetFiles( "*.xml", SearchOption::TopDirectoryOnly );
      
      // we only want the filename, not path (changes each time)
      _outputFilenames = gcnew array<String^>(xmlFiles->Length);
      for( int i = 0; i < xmlFiles->Length; ++i ) {
        _outputFilenames[i] = xmlFiles[i]->Name;
      }
    }

    // open excel via interop and disable errors and warnings
    Excel::Application ^ ea = gcnew Excel::Application();
    ea->DisplayAlerts = false;

    // convert output files from Excel's xml format to binary format
    for each( String ^ filename in _outputFilenames ) {
      // open from this directory
      String ^ xmlFilename = Path::Combine( runDir->FullName, filename );

      // open and disable compatability check
      Excel::Workbook ^ xmlFile = ea->Workbooks->Open(xmlFilename, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing );
      xmlFile->CheckCompatibility = false;

      // save as excel 97-2003 format, changing extension, close and delete old workbook
      xmlFile->SaveAs( Path::ChangeExtension( xmlFilename, ".xls" ), Excel::XlFileFormat::xlExcel8, Type::Missing, Type::Missing, Type::Missing, false, Excel::XlSaveAsAccessMode::xlNoChange, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing );
      ea->Workbooks->Close();
      File::Delete( xmlFilename );
    }

    // report progress
    sp = gcnew StudyProgress();
    sp->NumberOfRunsDiscarded = 0;
    sp->NumberOfRunsCompleted = 1;
    sp->Messages->Add( "Completed simulation for " + filename +"." );
    bw->ReportProgress( 0, sp );
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
    rboxOutput->AppendText( s + Environment::NewLine );
  }
}



System::Void
LhsForm::SimulationsCompleted( Object ^ sender, RunWorkerCompletedEventArgs ^ e )
{
  // this is called each a thread completes
  _simulationThreadsCompleted++;

  // so don't actually "complete" until all threads have finished
  if( _simulationThreadsCompleted == _simulationThreads->Count ) {
    btnBrowseDml->Enabled = true;
    btnBrowseLsp->Enabled = true;
    btnBrowseOutput->Enabled = true;
    chkDiscrete->Enabled = true;
    tboxDml->Enabled = true;
    tboxLsp->Enabled = true;
    tboxOutput->Enabled = true;
    btnRun->Enabled = true;

    rboxOutput->AppendText( "Completed sensitivity analysis study" );
    rboxOutput->SelectionStart = rboxOutput->Text->Length;
  }
}
