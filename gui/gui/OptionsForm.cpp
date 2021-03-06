#include "StdAfx.h"
#include "OptionsForm.h"

using namespace gui;



OptionsForm::OptionsForm( UserSettings ^ userSettings )
: _userSettings(userSettings)
{
	InitializeComponent();
  _userSettings->BeginEdit();
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
  chkSplashScreen->DataBindings->Add( "Checked", _userSettings, "ShowSplashScreen" );
  chkDoSimulationDiskOutput->DataBindings->Add( "Checked", _userSettings, "DoSimulationDiskOutput" );
  chkEstablishedPopulationDefault->DataBindings->Add( "Checked", _userSettings, "EstablishedPopulationDefault" );
  chkScaleCimsimMainGraph->DataBindings->Add( "Checked", _userSettings, "ScaleCimsimMainGraph" );
}



System::Void
OptionsForm::OnOk(System::Object^  sender, System::EventArgs^  e)
{
  _userSettings->EndEdit();
}



System::Void
OptionsForm::OnCancel(System::Object^  sender, System::EventArgs^  e)
{
  _userSettings->CancelEdit();
}
