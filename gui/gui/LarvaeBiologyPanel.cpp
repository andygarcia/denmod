#include "StdAfx.h"
#include "LarvaeBiologyPanel.h"
#include "ParameterDisplayBinding.h"

using namespace gui;



LarvaeBiologyPanel::LarvaeBiologyPanel( BindingSource ^ locationBinding )
: LocationBinding(locationBinding)
{
	InitializeComponent();
}



LarvaeBiologyPanel::~LarvaeBiologyPanel()
{
  if( components ) {
		delete components;
	}
}



System::Void
LarvaeBiologyPanel::OnLoad( System::Object ^ sender, System::EventArgs ^ e )
{
  snboxDevelopmentThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.DevelopmentThreshold" ) );
  snboxMaximumDevelopment->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.MaximumDevelopment") );
  snboxNominalSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.NominalSurvival") );
  snboxPupationSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.PupationSurvival") );
  snboxDryContainerSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.DryContainerSurvival") );
  snboxWeightAtHatch->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.WeightAtHatch") );
  snboxMinimumWeightForSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.MinimumWeightForSurvival") );

  snboxRO25->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.Development.RO25") );
  snboxDHA->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.Development.DHA") );
  snboxDHH->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.Development.DHH") );
  snboxTHALF->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.Development.THALF") );

  snboxPupWtSlope->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.PupationWeight.Slope") );
  snboxPupWtIntercept->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.PupationWeight.Intercept") );
  snboxPupWtMinimumWeight->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.PupationWeight.MinimumWeightForPupation") );
  snboxPupWtMinimumAge->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.PupationWeight.MinimumAgeForPupation") );

  snboxTempLowLethalThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.Temperature.LowLethalThreshold") );
  snboxTempLowLethalSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.Temperature.LowLethalSurvival") );
  snboxTempLowThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.Temperature.LowThreshold") );
  snboxTempHighThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.Temperature.HighThreshold") );
  snboxTempHighLethalThreshold->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.Temperature.HighLethalThreshold") );
  snboxTempHighLethalSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.Temperature.HighLethalSurvival") );

  chkUseRandomFood->DataBindings->Add( "Checked", LocationBinding, "Biology.Larvae.Food.UseRandomFood" );
  snboxNumberEulerSteps->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.NumberEulerSteps") );
  snboxCadaverFoodRatio->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.CadaverFoodRatio") );
  snboxAssimilationRate->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.Food.AssimilationRate") );
  snboxExploitationRate->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.Food.ExploitationRate") );
  snboxExploitationRateIndependence->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.Food.ExploitationRateIndependence") );
  snboxMetabolicWeightLossRate->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.Food.MetabolicWeightLossRate") );
  snboxMetabolicWeightLossExponent->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.Food.MetabolicWeightLossExponent") );

  snboxLipidReserveSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.Fasting.LipidReserveSurvival") );
  snboxNoLipidReserveSurvival->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.Fasting.NoLipidReserveSurvival") );
  snboxNonDepletableLipidReserve->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.Fasting.NonDepletableLipidReserve") );
  snboxWeightToLipidSlope->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.Fasting.WeightToLipidSlope") );
  snboxWeightToLipidConstant->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Biology.Larvae.Fasting.WeightToLipidConstant") );
}
