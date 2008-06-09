#include "StdAfx.h"
#include "BiologyForm.h"

using namespace gui;



BiologyForm::BiologyForm( BindingSource ^ locationBinding)
: LocationBinding( locationBinding )
{
	InitializeComponent();

  EggBiologyPanel_ = gcnew EggBiologyPanel( LocationBinding );
  this->tabPageEgg->Controls->Add( EggBiologyPanel_ );

  LarvaeBiologyPanel_ = gcnew LarvaeBiologyPanel( LocationBinding );
  this->tabPageLarvae->Controls->Add( LarvaeBiologyPanel_ );

  PupaeBiologyPanel_ = gcnew PupaeBiologyPanel( LocationBinding );
  this->tabPagePupae->Controls->Add( PupaeBiologyPanel_ );

  AdultBiologyPanel_ = gcnew AdultBiologyPanel( LocationBinding );
  this->tabPageAdult->Controls->Add( AdultBiologyPanel_ );
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