#include "StdAfx.h"
#include "AdultBiologyPanel.h"
#include "ParameterDisplayBinding.h"

using namespace gui;



AdultBiologyPanel::AdultBiologyPanel( BindingSource ^ locationBinding )
: LocationBinding(locationBinding)
{
	InitializeComponent();
}



AdultBiologyPanel::~AdultBiologyPanel()
{
  if( components ) {
		delete components;
	}
}



System::Void
AdultBiologyPanel::OnLoad( System::Object ^ sender, System::EventArgs ^ e )
{
  snboxSecondDevelopmentThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.SecondDevelopmentThreshold") );
  snboxNominalSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.NominalSurvival") );
  snboxDryToWetWeightFactor->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.DryToWetWeightFactor") );
  snboxFecundityFactor->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.FecundityFactor") );
  snboxMinimumOvipositionTemperature->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.MinimumOvipositionTemperature") );

  snboxYoungSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.AgeDependentSurvival.YoungSurvival") );
  snboxCutoffAge->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.AgeDependentSurvival.CutoffAge") );
  snboxOldSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.AgeDependentSurvival.OldSurvival") );

  snboxRO25->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.Development.RO25") );
  snboxDHA->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.Development.DHA") );
  snboxDHH->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.Development.DHH") );
  snboxTHALF->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.Development.THALF") );

  snboxTempLowLethalThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.Temperature.LowLethalThreshold") );
  snboxTempLowLethalSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.Temperature.LowLethalSurvival") );
  snboxTempLowThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.Temperature.LowThreshold") );
  snboxTempHighThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.Temperature.HighThreshold") );
  snboxTempHighLethalThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.Temperature.HighLethalThreshold") );
  snboxTempHighLethalSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.Temperature.HighLethalSurvival") );

  snboxSatDefLowThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.SaturationDeficit.LowThreshold") );
  snboxSatDefLowSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.SaturationDeficit.LowSurvival") );
  snboxSatDefHighThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.SaturationDeficit.HighThreshold") );
  snboxSatDefHighSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.SaturationDeficit.HighSurvival") );

  snboxDoubleBloodMealLowWeightRatio->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.DoubleBloodMeal.LowWeightRatio") );
  snboxDoubleBloodMealLowWeightLimit->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.DoubleBloodMeal.LowWeightLimit") );
  snboxDoubleBloodMealHighWeightRatio->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.DoubleBloodMeal.HighWeightRatio") );
  snboxDoubleBloodMealHighWeightLimit->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.DoubleBloodMeal.HighWeightLimit") );

  snboxFeedingHumanProportion->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.ProportionOfFeedsOnHumans") );
  snboxInterruptedFeedsPerMeal->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.InterruptedFeedsPerMeal") );
  snboxFeedingProportionInterrupedDifferentHost->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Adult.ProportionOfInterruptedFeedsOnDifferentHost") );
}
