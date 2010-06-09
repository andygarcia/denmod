#include "StdAfx.h"
#include "AddControlForm.h"

using namespace gui;



AddControlForm::AddControlForm(void)
: ControlMap( gcnew Collections::Generic::Dictionary<System::String^,System::Type^>() )
{
  InitializeComponent();

  ControlMap->Add( gcnew String("Source Reduction"), SourceReduction::typeid );
  ControlMap->Add( gcnew String("Oviposition Exclusion"), OvipositionExclusion::typeid );
  ControlMap->Add( gcnew String("Egg Destruction"), EggDestruction::typeid );
  ControlMap->Add( gcnew String("Larvicide"), Larvicide::typeid );
  ControlMap->Add( gcnew String("Sterile Male Release"), SterileMaleRelease::typeid );
  ControlMap->Add( gcnew String("Space Spray"), SpaceSpray::typeid );
  ControlMap->Add( gcnew String("Residual Spray"), ResidualSpray::typeid );

  for each( String ^ s in ControlMap->Keys ) {
    lboxControlTypes->Items->Add( s );
  }
}



AddControlForm::~AddControlForm()
{
	if( components ) {
		delete components;
	}
}



Type ^
AddControlForm::GetNewControlType(void)
{
  if( lboxControlTypes->SelectedItem == nullptr ) {
    return nullptr;
  }

  return ControlMap[lboxControlTypes->SelectedItem->ToString()];
}



System::Void
AddControlForm::OnAdd( System::Object ^ sender, System::EventArgs ^ e )
{
  if( lboxControlTypes->SelectedItem == nullptr ) {
    MessageBox::Show( "Please select a control type to add." );
    this->DialogResult = ::DialogResult::None;
  }
  else {
    this->DialogResult = ::DialogResult::OK;
  }
}
