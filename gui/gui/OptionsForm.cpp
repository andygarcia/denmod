#include "StdAfx.h"
#include "OptionsForm.h"

using namespace gui;



OptionsForm::OptionsForm( Settings ^ userSettings )
: _settings(userSettings)
{
	InitializeComponent();
  _settings->BeginEdit();
}



OptionsForm::~OptionsForm()
{
	if( components )	{
		delete components;
	}
}



System::Void
OptionsForm::OnLoad(System::Object^  sender, System::EventArgs^  e)
{
  chkScaleCimsimMainGraph->DataBindings->Add( "Checked", _settings, "ScaleCimsimMainGraph" );
  chkStochasticAdvancement->DataBindings->Add( "Checked", _settings, "StochasticAdvancement" );
}



System::Void
OptionsForm::OnOk(System::Object^  sender, System::EventArgs^  e)
{
  _settings->EndEdit();
}



System::Void
OptionsForm::OnCancel(System::Object^  sender, System::EventArgs^  e)
{
  _settings->CancelEdit();
}
