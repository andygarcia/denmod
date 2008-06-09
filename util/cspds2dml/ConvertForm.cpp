#include "StdAfx.h"
#include "ConvertForm.h"
#include "CsPdsFile.h"

using namespace cspds2dml;



ConvertForm::ConvertForm()
{
	InitializeComponent();
}



ConvertForm::~ConvertForm()
{
	if( components ) {
		delete components;
	}
}



System::Void
ConvertForm::OnConvert(System::Object^  sender, System::EventArgs^  e)
{
  CsPdsFile ^ cpf = gcnew CsPdsFile( tboxInput->Text );

  // save in same directory as source
  IO::FileInfo ^ fi = gcnew IO::FileInfo( tboxInput->Text );
  String ^ filename = fi->Directory + "\\CIMSiM.dml";

  gui::DmlFile ^ df = gcnew gui::DmlFile( filename, cpf->Location );
  df->Save();
}



System::Void
ConvertForm::OnBrowse(System::Object^  sender, System::EventArgs^  e)
{
  // allow user to brose for .pds file
  OpenFileDialog ^ ofd = gcnew OpenFileDialog();
  ofd->Filter = "CIMSiM PDS Files (*.pds)|*.pds";
  if( ofd->ShowDialog(this) != ::DialogResult::OK ) {
    return;
  }
  tboxInput->Text = ofd->FileName;
}



System::Void
ConvertForm::OnDragDropInput(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
{
  if( e->Data->GetDataPresent( DataFormats::FileDrop ) ) {
    array<Object ^> ^ a = (array<Object ^>^) e->Data->GetData( DataFormats::FileDrop );
    if( a != nullptr ) {
      if( a->Length > 1 ) {}  // more than one file dragged... ignore and simply read first filedrop
      tboxInput->Text = a[0]->ToString();
    }
  }
}



System::Void
ConvertForm::OnDragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
{
  if( e->Data->GetDataPresent( DataFormats::FileDrop ) ) {
    e->Effect = DragDropEffects::Copy;
  }
  else {

  }
}