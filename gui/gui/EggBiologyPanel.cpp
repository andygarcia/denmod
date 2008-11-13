#include "StdAfx.h"
#include "EggBiologyPanel.h"
#include "ParameterDisplayBinding.h"

using namespace gui;



EggBiologyPanel::EggBiologyPanel( BindingSource ^ locationBinding )
: LocationBinding(locationBinding)
{
	InitializeComponent();
}



EggBiologyPanel::~EggBiologyPanel()
{
	if( components ) {
		delete components;
	}
}



System::Void
EggBiologyPanel::OnLoad( System::Object ^ sender, System::EventArgs ^ e )
{
  snboxNominalSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.NominalSurvival") );

  snboxRO25->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.Development.RO25") );
  snboxDHA->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.Development.DHA") );
  snboxDHH->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.Development.DHH") );
  snboxTHALF->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.Development.THALF") );

  snboxMinimumHatchTemperature->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.MinimumHatchTemperature") );
  snboxFloodHatchRatio->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.FloodHatchRatio") );
  snboxSpontaneousHatchRatio->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.SpontaneousHatchRatio") );

  snboxTempLowLethalThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.Temperature.LowLethalThreshold") );
  snboxTempLowLethalSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.Temperature.LowLethalSurvival") );
  snboxTempLowThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.Temperature.LowThreshold") );
  snboxTempHighThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.Temperature.HighThreshold") );
  snboxTempHighLethalThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.Temperature.HighLethalThreshold") );
  snboxTempHighLethalSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.Temperature.HighLethalSurvival") );

  snboxHighSunExposureThrehsold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.SaturationDeficit.HighSunExposureThreshold") );
  snboxHighSunExposureSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.SaturationDeficit.HighSunExposureSurvival") );
  snboxSatDefLowThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.SaturationDeficit.LowThreshold") );
  snboxSatDefLowSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.SaturationDeficit.LowSurvival") );
  snboxSatDefHighThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.SaturationDeficit.HighThreshold") );
  snboxSatDefHighSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.SaturationDeficit.HighSurvival") );

  snboxPredLowThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.Predation.LowThreshold") );
  snboxPredLowSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.Predation.LowSurvival") );
  snboxPredHighThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.Predation.HighThreshold") );
  snboxPredHighSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Egg.Predation.HighSurvival") );
}
