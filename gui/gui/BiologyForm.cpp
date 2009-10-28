#include "StdAfx.h"
#include "BiologyForm.h"

using namespace gui;



BiologyForm::BiologyForm( BindingSource ^ locationBinding)
: LocationBinding( locationBinding )
{
	InitializeComponent();

  _location = static_cast<gui::Location^>( locationBinding->DataSource );
  _location->Biology->BeginEdit();

  _eggPanel = gcnew EggBiologyPanel( LocationBinding );
  this->tabPageEgg->Controls->Add( _eggPanel );

  _larvaePanel = gcnew LarvaeBiologyPanel( LocationBinding );
  this->tabPageLarvae->Controls->Add( _larvaePanel );

  _pupaePanel = gcnew PupaeBiologyPanel( LocationBinding );
  this->tabPagePupae->Controls->Add( _pupaePanel );

  _adultPanel = gcnew AdultBiologyPanel( LocationBinding );
  this->tabPageAdult->Controls->Add( _adultPanel );
}



BiologyForm::~BiologyForm()
{
  if( components ) {
		delete components;
	}
}



System::Void 
BiologyForm::OnDefault( System::Object ^ sender, System::EventArgs ^ e )
{
  ::DialogResult dr = MessageBox::Show( "Reset all biology parameters to their default values?",
                                        "Reset Biology",
                                        MessageBoxButtons::OKCancel, MessageBoxIcon::Question, MessageBoxDefaultButton::Button2 );

  if( dr == ::DialogResult::OK ) {
    ((gui::Location ^) LocationBinding->Current)->ResetBiology();
  }
}



System::Void
BiologyForm::OnOk( System::Object ^ sender, System::EventArgs ^ e )
{
  using namespace ValidationFramework;
  
  BiologyParameters ^ biology = _location->Biology;

  // validate entire object
  biology->PropertyValidationManager->ValidateAllProperties();
  if( !biology->IsValid ) {
    String ^ errorMessages = ValidationFramework::ResultFormatter::GetConcatenatedErrorMessages( "\n", biology->PropertyValidationManager->ValidatorResultsInError );
    MessageBox::Show( this, errorMessages, "Errors in biology parameters." );
    this->DialogResult = ::DialogResult::None;
    return;
  }
  else {
    _location->Biology->EndEdit();
  }
}



System::Void
BiologyForm::OnCancel(System::Object^  sender, System::EventArgs^  e)
{
  _location->Biology->CancelEdit();
}
