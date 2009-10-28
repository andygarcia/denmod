#include "StdAfx.h"
#include "EggBiologyPanel.h"
#include "ParameterDisplayBinding.h"

using namespace gui;



EggBiologyPanel::EggBiologyPanel( BindingSource ^ locationBinding )
: _locationBinding(locationBinding)
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
  snboxNominalSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.NominalSurvival") );

  snboxRO25->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.Development.RO25") );
  snboxDHA->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.Development.DHA") );
  snboxDHH->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.Development.DHH") );
  snboxTHALF->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.Development.THALF") );

  snboxMinimumHatchTemperature->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.MinimumHatchTemperature") );
  snboxFloodHatchRatio->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.FloodHatchRatio") );
  snboxSpontaneousHatchRatio->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.SpontaneousHatchRatio") );

  snboxTempLowLethalThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.Temperature.LowLethalThreshold") );
  snboxTempLowLethalSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.Temperature.LowLethalSurvival") );
  snboxTempLowThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.Temperature.LowThreshold") );
  snboxTempHighThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.Temperature.HighThreshold") );
  snboxTempHighLethalThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.Temperature.HighLethalThreshold") );
  snboxTempHighLethalSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.Temperature.HighLethalSurvival") );

  snboxHighSunExposureThrehsold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.SaturationDeficit.HighSunExposureThreshold") );
  snboxHighSunExposureSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.SaturationDeficit.HighSunExposureSurvival") );
  snboxSatDefLowThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.SaturationDeficit.LowThreshold") );
  snboxSatDefLowSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.SaturationDeficit.LowSurvival") );
  snboxSatDefHighThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.SaturationDeficit.HighThreshold") );
  snboxSatDefHighSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.SaturationDeficit.HighSurvival") );

  snboxPredLowThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.Predation.LowThreshold") );
  snboxPredLowSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.Predation.LowSurvival") );
  snboxPredHighThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.Predation.HighThreshold") );
  snboxPredHighSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Biology.Egg.Predation.HighSurvival") );

  errproEgg->DataSource = _locationBinding;
  errproEgg->DataMember = "Biology.Egg";

  errproTemperature->DataSource = _locationBinding;
  errproTemperature->DataMember = "Biology.Egg.Temperature";

  errproSaturationDeficit->DataSource = _locationBinding;
  errproSaturationDeficit->DataMember = "Biology.Egg.SaturationDeficit";

  errproPredation->DataSource = _locationBinding;
  errproPredation->DataMember = "Biology.Egg.Predation";
}
