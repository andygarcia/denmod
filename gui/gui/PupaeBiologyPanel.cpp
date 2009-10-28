#include "StdAfx.h"
#include "PupaeBiologyPanel.h"
#include "ParameterDisplayBinding.h"

using namespace gui;



PupaeBiologyPanel::PupaeBiologyPanel( BindingSource ^ locationBinding )
: LocationBinding( locationBinding )
{
	InitializeComponent();
}



PupaeBiologyPanel::~PupaeBiologyPanel()
{
	if( components ) {
		delete components;
	}
}



System::Void
PupaeBiologyPanel::OnLoad( System::Object ^ sender, System::EventArgs ^ e )
{
  snboxNominalSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Pupae.NominalSurvival") );
  snboxEmergenceSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Pupae.EmergenceSurvival") );
  snboxFemaleEmergence->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Pupae.FemaleEmergence") );

  snboxRO25->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Pupae.Development.RO25") );
  snboxDHA->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Pupae.Development.DHA") );
  snboxDHH->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Pupae.Development.DHH") );
  snboxTHALF->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Pupae.Development.THALF") );

  snboxTempLowLethalThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Pupae.Temperature.LowLethalThreshold") );
  snboxTempLowLethalSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Pupae.Temperature.LowLethalSurvival") );
  snboxTempLowThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Pupae.Temperature.LowThreshold") );
  snboxTempHighThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Pupae.Temperature.HighThreshold") );
  snboxTempHighLethalThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Pupae.Temperature.HighLethalThreshold") );
  snboxTempHighLethalSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Pupae.Temperature.HighLethalSurvival") );

  errproPupae->DataSource = LocationBinding;
  errproPupae->DataMember = "Biology.Pupae";

  errproTemperature->DataSource = LocationBinding;
  errproPupae->DataMember = "Biology.Pupae.Temperature";
}
