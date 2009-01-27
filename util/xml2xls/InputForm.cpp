#include "StdAfx.h"
#include "InputForm.h"

using namespace xml2xls;



InputForm::InputForm(void)
{
	InitializeComponent();
}



InputForm::~InputForm()
{
	if( components ) {
		delete components;
	}
}


    
System::Void
InputForm::OnBrowse(System::Object^  sender, System::EventArgs^  e)
{
  // browse and select files
  OpenFileDialog ^ ofd = gcnew OpenFileDialog();
  ofd->Filter = "Excel Spreadsheets (*.xml)|*.xml";
  ofd->Multiselect = true;
  if( ofd->ShowDialog(this) != ::DialogResult::OK ) {
    return;
  }

  int numSelectedFiles = ofd->FileNames->Length;
  int numAdded = 0;

  for each( String ^ filename  in ofd->FileNames ) {
    IO::FileInfo ^ fi = gcnew IO::FileInfo( filename );
    ListViewItem ^ lvi = lvFiles->Items->Add( fi->FullName );
    lvi->SubItems->Add( "no" );
    numAdded++;
  }
}



System::Void
InputForm::OnConvert(System::Object^  sender, System::EventArgs^  e)
{
  using namespace Microsoft::Office::Interop;
  Excel::Application ^ ea = gcnew Excel::Application();
  ea->DisplayAlerts = false;

  int filesConverted = 0;

  for each( ListViewItem ^ lvi in lvFiles->Items ) {
    String ^ xmlFilename = lvi->Text;

    // open and disable compatability check
    Excel::Workbook ^ xmlFile = ea->Workbooks->Open(xmlFilename, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing );
    xmlFile->CheckCompatibility = false;

    // save as excel 97-2003 format, changing extension, close and delete old workbook
    xmlFile->SaveAs( IO::Path::ChangeExtension( xmlFilename, ".xls" ), Excel::XlFileFormat::xlExcel8, Type::Missing, Type::Missing, Type::Missing, false, Excel::XlSaveAsAccessMode::xlNoChange, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing );
    ea->Workbooks->Close();
    //IO::File::Delete( xmlFilename );
    lvi->SubItems[1]->Text = "yes";
    filesConverted++;
  }

  MessageBox::Show( "" + filesConverted + " files were converted." );
}



System::Void
InputForm::OnDragDropInput(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
{
  if( e->Data->GetDataPresent( DataFormats::FileDrop ) ) {
    array<Object ^> ^ ao = (array<Object ^>^) e->Data->GetData( DataFormats::FileDrop );
    if( ao != nullptr ) {
      for each( System::Object ^ o in ao ) {
        String ^ filename = o->ToString();

        if( filename->EndsWith( ".xml", StringComparison::InvariantCultureIgnoreCase ) ) {
          IO::FileInfo ^ fi = gcnew IO::FileInfo( filename );
          String ^ ext = IO::Path::GetExtension( fi->FullName );
          ListViewItem ^ lvi = lvFiles->Items->Add( fi->FullName );
          lvi->SubItems->Add( "no" );
        }
      }
    }
  }
}



System::Void
InputForm::OnDragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
{
  if( e->Data->GetDataPresent( DataFormats::FileDrop ) ) {
    e->Effect = DragDropEffects::Copy;
  }
  else {
    e->Effect = DragDropEffects::None;
  }
}

