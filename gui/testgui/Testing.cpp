#include "StdAfx.h"
#include "Testing.h"

using namespace System::IO;
using namespace testgui;



Testing::Testing(void)
{
	InitializeComponent();
}



Testing::~Testing()
{
	if( components ) {
		delete components;
	}
}



System::Void
Testing::OnBrowseDml( System::Object ^ sender, System::EventArgs ^ e )
{
  // allow user to browse and select file
  OpenFileDialog ^ ofd = gcnew OpenFileDialog();
  ofd->Filter = "Dengue Model Locations (*.dml)|*.dml";
  if( ofd->ShowDialog(this) != ::DialogResult::OK ) {
    return;
  }
  tboxDmlFile->Text = ofd->FileName;
}



System::Void
Testing::OnBrowseOutput( System::Object ^ sender, System::EventArgs ^ e )
{
  FolderBrowserDialog ^ fbd = gcnew FolderBrowserDialog();
  if( Directory::Exists( tboxOutput->Text ) ) {
    fbd->SelectedPath = tboxOutput->Text;
  }
  if( fbd->ShowDialog() != ::DialogResult::OK ) {
    return;
  }
  tboxOutput->Text = fbd->SelectedPath;
}


    
System::Void
Testing::OnRun( System::Object ^ sender, System::EventArgs ^ e )
{
  // make sure output directory exists
  if( !Directory::Exists( tboxOutput->Text ) ) {
    MessageBox::Show( "Output directory does not exist." );
    return;
  }

  System::Environment::CurrentDirectory = tboxOutput->Text;

  // try opening dml file
  gui::DmlFile ^ df = gcnew gui::DmlFile( tboxDmlFile->Text );
  if( df->IsValid == false ) {
    MessageBox::Show( "Error loading DML file." );
    return;
  }

  // do run(s)
  if( numRuns->Value == 1 ) {
    df->Location->TestingRunCimsim();
    MessageBox::Show("Simulation Complete");
  }
  else {
    // TODO: multiple runs, use progress bar
    ProgressBar ^ pb = gcnew ProgressBar();

    // create/change directories as needed
    DirectoryInfo ^ di = gcnew DirectoryInfo( tboxOutput->Text );
    for( int i = 1; i <= numRuns->Value; ++i ) {
      // create directory for current iteration
      String ^ iterDir = String::Format( "\\iter{0}", i );
      String ^ iterPath = di->FullName + iterDir;
      Directory::CreateDirectory( iterPath );
      System::Environment::CurrentDirectory = iterPath;

      // run simulation for this iteration
      df->Location->TestingRunCimsim();
    }
    MessageBox::Show("Simulations Complete");
  }
}



System::Void
Testing::OnDragDropInput(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
{
  if( e->Data->GetDataPresent( DataFormats::FileDrop ) ) {
    array<Object ^> ^ ao = (array<Object ^>^) e->Data->GetData( DataFormats::FileDrop );
    if( ao != nullptr ) {
      if( ao->Length > 1 )
      {
        // more than one file dragged... ignore and simply read first filedrop
      }
      String ^ fileDropText = ao[0]->ToString();

      // set focus to force validation
      if( sender == tboxDmlFile ) {
        tboxDmlFile->Text = fileDropText;
        tboxDmlFile->Focus();
      }
      if( sender == tboxOutput ) {
        tboxOutput->Text = fileDropText;
        tboxOutput->Focus();
      }
    }
  }
}



System::Void
Testing::OnDragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
{
  if( e->Data->GetDataPresent( DataFormats::FileDrop ) ) {
    e->Effect = DragDropEffects::Copy;
  }
  else {
    e->Effect = DragDropEffects::None;
  }
}




System::Void
Testing::OnValidatingOutputDirectory(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
{
  // check valid directory
  String ^ s = tboxOutput->Text;
  try {
    DirectoryInfo ^ di = gcnew DirectoryInfo( s );
    if( !di->Exists ) {
      errPro->SetError( tboxOutput, "Directory does not exist." );
    }
  }
  catch( Exception ^ ex ) {
    errPro->SetError( tboxOutput, ex->Message );
  }

  // allows user to exit input box, no lockdown!
}
