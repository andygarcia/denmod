#include "StdAfx.h"
#include "Biology.h"

using namespace gui;



DevelopmentParameters::DevelopmentParameters( const DevelopmentParameters ^ dp )
{
  this->RO25 = dp->RO25_;
  this->DHA = dp->DHA_;
  this->DHH = dp->DHH_;
  this->THALF = dp->THALF_;
}



TemperatureParameters::TemperatureParameters( const TemperatureParameters ^ tp )
{
  this->LowLethalSurvival = tp->LowLethalSurvival_;
  this->LowLethalThreshold = tp->LowLethalThreshold_;
  this->LowThreshold = tp->LowThreshold_;
  this->HighThreshold = tp->HighThreshold_;
  this->HighLethalThreshold = tp->HighLethalThreshold_;
  this->HighLethalSurvival = tp->HighLethalSurvival_;
}



void
TemperatureParameters::CheckValidLowLethalThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e )
{
  TemperatureParameters ^ tp = static_cast<TemperatureParameters^>( e->TargetObjectValue );
  double lowLethalThreshold = System::Convert::ToDouble( e->TargetMemberValue );

  if( lowLethalThreshold < tp->LowThreshold_ ) {
    e->IsValid = true;
  }
  else {
    e->IsValid = false;
    e->ErrorMessage = "Low lethal threshold must be less than low threshold.";
  }
}



void
TemperatureParameters::CheckValidLowThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e )
{
  TemperatureParameters ^ tp = static_cast<TemperatureParameters^>( e->TargetObjectValue );
  double lowThreshold = System::Convert::ToDouble( e->TargetMemberValue );

  if( lowThreshold <= tp->LowLethalThreshold_ ) {
    e->IsValid = false;
    e->ErrorMessage = "Low threshold must be greater than low lethal threshold.";
  }
  else if( lowThreshold > tp->HighThreshold_ ) {
    e->IsValid = false;
    e->ErrorMessage = "Low threshold must be less than high threshold.";
  }
  else {
    e->IsValid = true;
  }
}



void
TemperatureParameters::CheckValidHighThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e )
{
  TemperatureParameters ^ tp = static_cast<TemperatureParameters^>( e->TargetObjectValue );
  double highThreshold = System::Convert::ToDouble( e->TargetMemberValue);

  if( highThreshold <= tp->LowThreshold_ ) {
    e->IsValid = false;
    e->ErrorMessage = "High threshold must be greater than low threshold.";
  }
  else if( highThreshold > tp->HighLethalThreshold_ ) {
    e->IsValid = false;
    e->ErrorMessage = "High threshold must be less than high lethal threshold.";
  }
  else {
    e->IsValid = true;
  }
}



void
TemperatureParameters::CheckValidHighLethalThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e )
{
  TemperatureParameters ^ tp = static_cast<TemperatureParameters^>( e->TargetObjectValue );
  double highLethalThreshold = System::Convert::ToDouble( e->TargetMemberValue );

  if( highLethalThreshold > tp->HighThreshold_ ) {
    e->IsValid = true;
  }
  else {
    e->IsValid = false;
    e->ErrorMessage = "High lethal threshold must be greather than high threshold.";
  }
}



EggDevelopment::EggDevelopment(void)
{
  input::Biology::EggParameters::DevelopmentParameters defVals;
  this->RO25_ = defVals.RO25;
  this->DHA_ = defVals.DHA;
  this->DHH_ = defVals.DHH;
  this->THALF_ = defVals.THALF;
}



EggDevelopment::EggDevelopment( const EggDevelopment ^ ed )
: DevelopmentParameters( ed )
{}



input::Biology::EggParameters::DevelopmentParameters *
EggDevelopment::GetSimObject(void)
{
  input::Biology::EggParameters::DevelopmentParameters * dp = new input::Biology::EggParameters::DevelopmentParameters();

  dp->RO25 = this->RO25_;
  dp->DHA = this->DHA_;
  dp->DHH = this->DHH_;
  dp->THALF = this->THALF_;

  return dp;
}



EggTemperature::EggTemperature(void)
{
  input::Biology::EggParameters::TemperatureParameters defVals;
  this->LowLethalSurvival_ = defVals.LowLethalSurvival;
  this->LowLethalThreshold_ = defVals.LowLethalThreshold;
  this->LowThreshold_ = defVals.LowThreshold;
  this->HighThreshold_ = defVals.HighThreshold;
  this->HighLethalThreshold_ = defVals.HighLethalThreshold;
  this->HighLethalSurvival_ = defVals.HighLethalSurvival;
}



EggTemperature::EggTemperature( const EggTemperature ^ et )
: TemperatureParameters( et )
{}



input::Biology::EggParameters::TemperatureParameters *
EggTemperature::GetSimObject(void)
{
  input::Biology::EggParameters::TemperatureParameters * tp = new input::Biology::EggParameters::TemperatureParameters();

  tp->LowLethalSurvival = this->LowLethalSurvival_;
  tp->LowLethalThreshold = this->LowLethalThreshold_;
  tp->LowThreshold = this->LowThreshold_;
  tp->HighThreshold = this->HighThreshold_;
  tp->HighLethalThreshold = this->HighLethalThreshold_;
  tp->HighLethalSurvival = this->HighLethalSurvival_;

  return tp;
}



EggSaturationDeficit::EggSaturationDeficit(void)
{
  input::Biology::EggParameters::SaturationDeficitParameters defVals;
  this->WetSurvival_ = defVals.WetSurvival;
  this->HighSunExposureThreshold_ = defVals.HighSunExposureThreshold;
  this->HighSunExposureSurvival_ = defVals.HighSunExposureSurvival;
  this->LowThreshold_ = defVals.LowThreshold;
  this->HighThreshold_ = defVals.HighThreshold;
  this->LowSurvival_ = defVals.LowSurvival;
  this->HighSurvival_ = defVals.HighSurvival;
}



EggSaturationDeficit::EggSaturationDeficit( const EggSaturationDeficit ^ esd )
{
  this->WetSurvival = esd->WetSurvival_;
  this->HighSunExposureThreshold = esd->HighSunExposureThreshold_;
  this->HighSunExposureSurvival = esd->HighSunExposureSurvival_;
  this->LowThreshold = esd->LowThreshold_;
  this->HighThreshold = esd->HighThreshold_;
  this->LowSurvival = esd->LowSurvival_;
  this->HighSurvival = esd->HighSurvival_;
}



input::Biology::EggParameters::SaturationDeficitParameters *
EggSaturationDeficit::GetSimObject(void)
{
  input::Biology::EggParameters::SaturationDeficitParameters * sdp = new input::Biology::EggParameters::SaturationDeficitParameters();

  sdp->WetSurvival = this->WetSurvival_;
  sdp->HighSunExposureThreshold = this->HighSunExposureThreshold_;
  sdp->HighSunExposureSurvival = this->HighSunExposureSurvival_;
  sdp->LowThreshold = this->LowThreshold_;
  sdp->HighThreshold = this->HighThreshold_;
  sdp->LowSurvival = this->LowSurvival_;
  sdp->HighSurvival = this->HighSurvival_;

  return sdp;
}



void
EggSaturationDeficit::CheckValidLowThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e )
{
  EggSaturationDeficit ^ esd = static_cast<EggSaturationDeficit^>( e->TargetObjectValue );
  double lowThreshold = System::Convert::ToDouble( e->TargetMemberValue );

  if( lowThreshold < esd->HighThreshold_ ) {
    e->IsValid = true;
  }
  else {
    e->IsValid = false;
    e->ErrorMessage = "Low threshold must be less than high threshold.";
  }
}



void
EggSaturationDeficit::CheckValidHighThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e )
{
  EggSaturationDeficit ^ esd = static_cast<EggSaturationDeficit^>( e->TargetObjectValue );
  double highThreshold = System::Convert::ToDouble( e->TargetMemberValue );

  if( highThreshold > esd->LowThreshold_ ) {
    e->IsValid = true;
  }
  else {
    e->IsValid = false;
    e->ErrorMessage = "High threshold must be greather than low threshold.";
  }
}



EggPredation::EggPredation(void)
{
  input::Biology::EggParameters::PredationParameters defVals;
  this->LowSurvival_ = defVals.LowSurvival;
  this->LowThreshold_ = defVals.LowThreshold;
  this->HighThreshold_ = defVals.HighThreshold;
  this->HighSurvival_ = defVals.HighSurvival;
}



EggPredation::EggPredation( const EggPredation ^ ep )
{
  this->LowSurvival = ep->LowSurvival_;
  this->LowThreshold = ep->LowThreshold_;
  this->HighThreshold = ep->HighThreshold_;
  this->HighSurvival = ep->HighSurvival_;
}



input::Biology::EggParameters::PredationParameters *
EggPredation::GetSimObject(void)
{
  input::Biology::EggParameters::PredationParameters * pp = new input::Biology::EggParameters::PredationParameters();

  pp->LowSurvival = this->LowSurvival_;
  pp->LowThreshold = this->LowThreshold_;
  pp->HighThreshold = this->HighThreshold_;
  pp->HighSurvival = this->HighSurvival_;

  return pp;
}



void
EggPredation::CheckValidLowThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e )
{
  EggPredation ^ ep = static_cast<EggPredation^>( e->TargetObjectValue );
  double lowThreshold = System::Convert::ToDouble( e->TargetMemberValue );

  if( lowThreshold < ep->HighThreshold_ ) {
    e->IsValid = true;
  }
  else {
    e->IsValid = false;
    e->ErrorMessage = "Low threshold must be less than high threshold.";
  }
}



void
EggPredation::CheckValidHighThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e )
{
  EggPredation ^ ep = static_cast<EggPredation^>( e->TargetObjectValue );
  double highThreshold = System::Convert::ToDouble( e->TargetMemberValue );

  if( highThreshold > ep->LowThreshold_ ) {
    e->IsValid = true;
  }
  else {
    e->IsValid = false;
    e->ErrorMessage = "High threshold must be greather than low threshold.";
  }
}



EggBiology::EggBiology(void)
: Development_(gcnew EggDevelopment()),
  Temperature_(gcnew EggTemperature()),
  SaturationDeficit_(gcnew EggSaturationDeficit()),
  Predation_(gcnew EggPredation())
{
  input::Biology::EggParameters defVals;
  this->MinimumHatchTemperature_ = defVals.MinimumHatchTemperature;
  this->FloodHatchRatio_ = defVals.FloodHatchRatio;
  this->SpontaneousHatchRatio_ = defVals.SpontaneousHatchRatio;
  this->NominalSurvival_ = defVals.NominalSurvival;
}



EggBiology::EggBiology( const EggBiology ^ eb )
{
  this->MinimumHatchTemperature = eb->MinimumHatchTemperature_;
  this->FloodHatchRatio = eb->FloodHatchRatio_;
  this->SpontaneousHatchRatio = eb->SpontaneousHatchRatio_;
  this->NominalSurvival = eb->NominalSurvival_;
  this->Development_ = gcnew EggDevelopment( eb->Development_ );
  this->Temperature_ = gcnew EggTemperature( eb->Temperature_ );
  this->SaturationDeficit_ = gcnew EggSaturationDeficit( eb->SaturationDeficit_ );
  this->Predation_ = gcnew EggPredation( eb->Predation_ );
}



input::Biology::EggParameters *
EggBiology::GetSimObject(void)
{
  input::Biology::EggParameters * ep = new input::Biology::EggParameters();

  ep->MinimumHatchTemperature = this->MinimumHatchTemperature_;
  ep->FloodHatchRatio = this->FloodHatchRatio_;
  ep->SpontaneousHatchRatio = this->SpontaneousHatchRatio_;
  ep->NominalSurvival = this->NominalSurvival_;
  ep->Development = this->Development_->GetSimObject();
  ep->Temperature = this->Temperature_->GetSimObject();
  ep->SaturationDeficit = this->SaturationDeficit_->GetSimObject();
  ep->Predation = this->Predation_->GetSimObject();

  return ep;
}



LarvaeDevelopment::LarvaeDevelopment(void)
{
  input::Biology::LarvaeParameters::DevelopmentParameters defVals;
  this->RO25_ = defVals.RO25;
  this->DHA_ = defVals.DHA;
  this->DHH_ = defVals.DHH;
  this->THALF_ = defVals.THALF;
}



LarvaeDevelopment::LarvaeDevelopment( const LarvaeDevelopment ^ ld )
: DevelopmentParameters( ld )
{}



input::Biology::LarvaeParameters::DevelopmentParameters *
LarvaeDevelopment::GetSimObject(void)
{
  input::Biology::LarvaeParameters::DevelopmentParameters * dp = new input::Biology::LarvaeParameters::DevelopmentParameters();

  dp->RO25 = this->RO25_;
  dp->DHA = this->DHA_;
  dp->DHH = this->DHH_;
  dp->THALF = this->THALF_;

  return dp;
}



LarvaePupationWeight::LarvaePupationWeight(void)
{
  input::Biology::LarvaeParameters::PupationWeightParameters defVals;
  this->Slope_ = defVals.Slope;
  this->Intercept_ = defVals.Intercept;
  this->MinimumWeightForPupation_ = defVals.MinimumWeightForPupation;
  this->MaximumDevelopment_ = defVals.MaximumDevelopment;
}



LarvaePupationWeight::LarvaePupationWeight( const LarvaePupationWeight ^ lpw )
{
  this->Slope = lpw->Slope_;
  this->Intercept = lpw->Intercept_;
  this->MinimumWeightForPupation = lpw->MinimumWeightForPupation_;
  this->MaximumDevelopment = lpw->MaximumDevelopment_;
}



input::Biology::LarvaeParameters::PupationWeightParameters *
LarvaePupationWeight::GetSimObject(void)
{
  input::Biology::LarvaeParameters::PupationWeightParameters * pwp = new input::Biology::LarvaeParameters::PupationWeightParameters();

  pwp->Slope = this->Slope_;
  pwp->Intercept = this->Intercept_;
  pwp->MinimumWeightForPupation = this->MinimumWeightForPupation_;
  pwp->MaximumDevelopment = this->MaximumDevelopment_;

  return pwp;
}



LarvaeTemperature::LarvaeTemperature(void)
{
  input::Biology::LarvaeParameters::TemperatureParameters defVals;
  this->LowLethalSurvival_ = defVals.LowLethalSurvival;
  this->LowLethalThreshold_ = defVals.LowLethalThreshold;
  this->LowThreshold_ = defVals.LowThreshold;
  this->HighThreshold_ = defVals.HighThreshold;
  this->HighLethalThreshold_ = defVals.HighLethalThreshold;
  this->HighLethalSurvival_ = defVals.HighLethalSurvival;
}



LarvaeTemperature::LarvaeTemperature( const LarvaeTemperature ^ lt )
: TemperatureParameters( lt )
{}



input::Biology::LarvaeParameters::TemperatureParameters *
LarvaeTemperature::GetSimObject(void)
{
  input::Biology::LarvaeParameters::TemperatureParameters * tp = new input::Biology::LarvaeParameters::TemperatureParameters();

  tp->LowLethalSurvival = this->LowLethalSurvival_;
  tp->LowLethalThreshold = this->LowLethalThreshold_;
  tp->LowThreshold = this->LowThreshold_;
  tp->HighThreshold = this->HighThreshold_;
  tp->HighLethalThreshold = this->HighLethalThreshold_;
  tp->HighLethalSurvival = this->HighLethalSurvival_;

  return tp;
}



LarvaeFood::LarvaeFood(void)
{
  input::Biology::LarvaeParameters::FoodParameters defVals;
  this->UseRandomFood = defVals.UseRandomFood;
  this->AssimilationRate_ = defVals.AssimilationRate;
  this->ExploitationRate_ = defVals.ExploitationRate;
  this->ExploitationRateIndependence_ = defVals.ExploitationRateIndependence;
  this->MetabolicWeightLossRate_ = defVals.MetabolicWeightLossRate;
  this->MetabolicWeightLossExponent_ = defVals.MetabolicWeightLossExponent;
}



LarvaeFood::LarvaeFood( const LarvaeFood ^ lf )
{
  this->UseRandomFood = lf->UseRandomFood_;
  this->AssimilationRate = lf->AssimilationRate_;
  this->ExploitationRate = lf->ExploitationRate_;
  this->ExploitationRateIndependence = lf->ExploitationRateIndependence_;
  this->MetabolicWeightLossRate = lf->MetabolicWeightLossRate_;
  this->MetabolicWeightLossExponent = lf->MetabolicWeightLossExponent_;
}



input::Biology::LarvaeParameters::FoodParameters *
LarvaeFood::GetSimObject(void)
{
  input::Biology::LarvaeParameters::FoodParameters * fp = new input::Biology::LarvaeParameters::FoodParameters();

  fp->UseRandomFood = this->UseRandomFood;
  fp->AssimilationRate = this->AssimilationRate_;
  fp->ExploitationRate = this->ExploitationRate_;
  fp->ExploitationRateIndependence = this->ExploitationRateIndependence_;
  fp->MetabolicWeightLossRate = this->MetabolicWeightLossRate_;
  fp->MetabolicWeightLossExponent = this->MetabolicWeightLossExponent_;

  return fp;
}



LarvaeFasting::LarvaeFasting(void)
{
  input::Biology::LarvaeParameters::FastingParameters defVals;
  this->NoFastingSurvival_ = defVals.NoFastingSurvival;
  this->LipidReserveSurvival_ = defVals.LipidReserveSurvival;
  this->NoLipidReserveSurvival_ = defVals.NoLipidReserveSurvival;
  this->NonDepletableLipidReserve_ = defVals.NonDepletableLipidReserve;
  this->WeightToLipidSlope_ = defVals.WeightToLipidSlope;
  this->WeightToLipidConstant_ = defVals.WeightToLipidConstant;
}



LarvaeFasting::LarvaeFasting( const LarvaeFasting ^ lf )
{
  this->NoFastingSurvival = lf->NoFastingSurvival_;
  this->LipidReserveSurvival = lf->LipidReserveSurvival_;
  this->NoLipidReserveSurvival = lf->NoLipidReserveSurvival_;
  this->NonDepletableLipidReserve = lf->NonDepletableLipidReserve_;
  this->WeightToLipidSlope = lf->WeightToLipidSlope_;
  this->WeightToLipidConstant = lf->WeightToLipidConstant_;
}



input::Biology::LarvaeParameters::FastingParameters *
LarvaeFasting::GetSimObject(void)
{
  input::Biology::LarvaeParameters::FastingParameters * fp = new input::Biology::LarvaeParameters::FastingParameters();

  fp->NoFastingSurvival = this->NoFastingSurvival_;
  fp->LipidReserveSurvival = this->LipidReserveSurvival_;
  fp->NoLipidReserveSurvival = this->NoLipidReserveSurvival_;
  fp->NonDepletableLipidReserve = this->NonDepletableLipidReserve_;
  fp->WeightToLipidSlope = this->WeightToLipidSlope_;
  fp->WeightToLipidConstant = this->WeightToLipidConstant_;

  return fp;
}



LarvaeBiology::LarvaeBiology(void)
: Development_(gcnew LarvaeDevelopment()),
  PupationWeight_(gcnew LarvaePupationWeight()),
  Temperature_(gcnew LarvaeTemperature()),
  Food_(gcnew LarvaeFood()),
  Fasting_(gcnew LarvaeFasting())
{
  input::Biology::LarvaeParameters defVals;
  this->WeightAtHatch_ = defVals.WeightAtHatch;
  this->ChronologicalBasisAt26C_ = defVals.ChronologicalBasisAt26C;
  this->NominalSurvival_ = defVals.NominalSurvival;
  this->PupationSurvival_ = defVals.PupationSurvival;
  this->DryContainerSurvival_ = defVals.DryContainerSurvival;
  this->MinimumWeightForSurvival_ = defVals.MinimumWeightForSurvival;
  this->NumberEulerSteps_ = defVals.NumberEulerSteps;
  this->CadaverFoodRatio_ = defVals.CadaverFoodRatio;
}



LarvaeBiology::LarvaeBiology( const LarvaeBiology ^ lb )
{
  this->WeightAtHatch = lb->WeightAtHatch_;
  this->ChronologicalBasisAt26C = lb->ChronologicalBasisAt26C_;
  this->NominalSurvival = lb->NominalSurvival_;
  this->PupationSurvival = lb->PupationSurvival_;
  this->DryContainerSurvival = lb->DryContainerSurvival_;
  this->MinimumWeightForSurvival = lb->MinimumWeightForSurvival_;
  this->NumberEulerSteps = lb->NumberEulerSteps_;
  this->CadaverFoodRatio = lb->CadaverFoodRatio_;
  this->Development = gcnew LarvaeDevelopment( lb->Development_ );
  this->PupationWeight = gcnew LarvaePupationWeight( lb->PupationWeight_ );
  this->Temperature = gcnew LarvaeTemperature( lb->Temperature_ );
  this->Food = gcnew LarvaeFood( lb->Food_ );
  this->Fasting = gcnew LarvaeFasting( lb->Fasting_ );
}




input::Biology::LarvaeParameters *
LarvaeBiology::GetSimObject(void)
{
  input::Biology::LarvaeParameters * lp = new input::Biology::LarvaeParameters();

  lp->WeightAtHatch = this->WeightAtHatch_;
  lp->ChronologicalBasisAt26C = this->ChronologicalBasisAt26C_;
  lp->NominalSurvival = this->NominalSurvival_;
  lp->PupationSurvival = this->PupationSurvival_;
  lp->DryContainerSurvival = this->DryContainerSurvival_;
  lp->MinimumWeightForSurvival = this->MinimumWeightForSurvival_;
  lp->NumberEulerSteps = this->NumberEulerSteps_;
  lp->CadaverFoodRatio = this->CadaverFoodRatio_;
  lp->Development = this->Development_->GetSimObject();
  lp->PupationWeight = this->PupationWeight_->GetSimObject();
  lp->Temperature = this->Temperature_->GetSimObject();
  lp->Food = this->Food_->GetSimObject();
  lp->Fasting = this->Fasting_->GetSimObject();

  return lp;
}



PupaeDevelopment::PupaeDevelopment(void)
{
  input::Biology::PupaeParameters::DevelopmentParameters defVals;
  this->RO25_ = defVals.RO25;
  this->DHA_ = defVals.DHA;
  this->DHH_ = defVals.DHH;
  this->THALF_ = defVals.THALF;
}



PupaeDevelopment::PupaeDevelopment( const PupaeDevelopment ^ pd )
: DevelopmentParameters( pd )
{}



input::Biology::PupaeParameters::DevelopmentParameters *
PupaeDevelopment::GetSimObject(void)
{
  input::Biology::PupaeParameters::DevelopmentParameters * dp = new input::Biology::PupaeParameters::DevelopmentParameters();

  dp->RO25 = this->RO25_;
  dp->DHA = this->DHA_;
  dp->DHH = this->DHH_;
  dp->THALF = this->THALF_;

  return dp;
}



PupaeTemperature::PupaeTemperature(void)
{
  input::Biology::PupaeParameters::TemperatureParameters defVals;
  this->LowLethalSurvival_ = defVals.LowLethalSurvival;
  this->LowLethalThreshold_ = defVals.LowLethalThreshold;
  this->LowThreshold_ = defVals.LowThreshold;
  this->HighThreshold_ = defVals.HighThreshold;
  this->HighLethalThreshold_ = defVals.HighLethalThreshold;
  this->HighLethalSurvival_ = defVals.HighLethalSurvival;
}



PupaeTemperature::PupaeTemperature( const PupaeTemperature ^ pt )
: TemperatureParameters( pt )
{}



input::Biology::PupaeParameters::TemperatureParameters *
PupaeTemperature::GetSimObject(void)
{
  input::Biology::PupaeParameters::TemperatureParameters * tp = new input::Biology::PupaeParameters::TemperatureParameters();

  tp->LowLethalSurvival = this->LowLethalSurvival_;
  tp->LowLethalThreshold = this->LowLethalThreshold_;
  tp->LowThreshold = this->LowThreshold_;
  tp->HighThreshold = this->HighThreshold_;
  tp->HighLethalThreshold = this->HighLethalThreshold_;
  tp->HighLethalSurvival = this->HighLethalSurvival_;

  return tp;
}



PupaeBiology::PupaeBiology(void)
: Development_(gcnew PupaeDevelopment()),
  Temperature_(gcnew PupaeTemperature())
{
  input::Biology::PupaeParameters defVals;
  this->NominalSurvival_ = defVals.NominalSurvival;
  this->EmergenceSurvival_ = defVals.EmergenceSurvival;
  this->FemaleEmergence_ = defVals.FemaleEmergence;
}



PupaeBiology::PupaeBiology( const PupaeBiology ^ pb )
{
  this->NominalSurvival = pb->NominalSurvival_;
  this->EmergenceSurvival = pb->EmergenceSurvival_;
  this->FemaleEmergence = pb->FemaleEmergence_;
  this->Development = gcnew PupaeDevelopment( pb->Development_ );
  this->Temperature = gcnew PupaeTemperature( pb->Temperature_ );
}



input::Biology::PupaeParameters *
PupaeBiology::GetSimObject(void)
{
  input::Biology::PupaeParameters * pp = new input::Biology::PupaeParameters();

  pp->NominalSurvival = this->NominalSurvival_;
  pp->EmergenceSurvival = this->EmergenceSurvival_;
  pp->FemaleEmergence = this->FemaleEmergence_;
  pp->Development = this->Development_->GetSimObject();
  pp->Temperature = this->Temperature_->GetSimObject();

  return pp;
}



AdultAgeDependentSurvival::AdultAgeDependentSurvival(void)
{
  input::Biology::AdultParameters::AgeDependentSurvivalParameters defVals;
  this->CutoffAge_ = defVals.CutoffAge;
  this->YoungSurvival_ = defVals.YoungSurvival;
  this->OldSurvival_ = defVals.OldSurvival;
}



AdultAgeDependentSurvival::AdultAgeDependentSurvival( const AdultAgeDependentSurvival ^ aads )
{
  this->CutoffAge_ = aads->CutoffAge_;
  this->YoungSurvival_ = aads->YoungSurvival_;
  this->OldSurvival_ = aads->OldSurvival_;
}



input::Biology::AdultParameters::AgeDependentSurvivalParameters *
AdultAgeDependentSurvival::GetSimObject(void)
{
  input::Biology::AdultParameters::AgeDependentSurvivalParameters * adsp = new input::Biology::AdultParameters::AgeDependentSurvivalParameters();

  adsp->CutoffAge = this->CutoffAge_;
  adsp->YoungSurvival = this->YoungSurvival_;
  adsp->OldSurvival = this->OldSurvival_;

  return adsp;
}



AdultDevelopment::AdultDevelopment(void)
{
  input::Biology::AdultParameters::DevelopmentParameters defVals;
  this->RO25_ = defVals.RO25;
  this->DHA_ = defVals.DHA;
  this->DHH_ = defVals.DHH;
  this->THALF_ = defVals.THALF;  
}



AdultDevelopment::AdultDevelopment( const AdultDevelopment ^ ad )
: DevelopmentParameters( ad )
{}


input::Biology::AdultParameters::DevelopmentParameters *
AdultDevelopment::GetSimObject(void)
{
  input::Biology::AdultParameters::DevelopmentParameters * dp = new input::Biology::AdultParameters::DevelopmentParameters();

  dp->RO25 = this->RO25_;
  dp->DHA = this->DHA_;
  dp->DHH = this->DHH_;
  dp->THALF = this->THALF_;

  return dp;
}



AdultTemperature::AdultTemperature(void)
{
  input::Biology::AdultParameters::TemperatureParameters defVals;
  this->LowLethalSurvival_ = defVals.LowLethalSurvival;
  this->LowLethalThreshold_ = defVals.LowLethalThreshold;
  this->LowThreshold_ = defVals.LowThreshold;
  this->HighThreshold_ = defVals.HighThreshold;
  this->HighLethalThreshold_ = defVals.HighLethalThreshold;
  this->HighLethalSurvival_ = defVals.HighLethalSurvival;
}



AdultTemperature::AdultTemperature( const AdultTemperature ^ at )
: TemperatureParameters( at )
{}



input::Biology::AdultParameters::TemperatureParameters *
AdultTemperature::GetSimObject(void)
{
  input::Biology::AdultParameters::TemperatureParameters * tp = new input::Biology::AdultParameters::TemperatureParameters();

  tp->LowLethalSurvival = this->LowLethalSurvival_;
  tp->LowLethalThreshold = this->LowLethalThreshold_;
  tp->LowThreshold = this->LowThreshold_;
  tp->HighThreshold = this->HighThreshold_;
  tp->HighLethalThreshold = this->HighLethalThreshold_;
  tp->HighLethalSurvival = this->HighLethalSurvival_;

  return tp;
}



AdultSaturationDeficit::AdultSaturationDeficit(void)
{
  input::Biology::AdultParameters::SaturationDeficitParameters defVals;
  this->LowThreshold_ = defVals.LowThreshold;
  this->HighThreshold_ = defVals.HighThreshold;
  this->LowSurvival_ = defVals.LowSurvival;
  this->HighSurvival_ = defVals.HighSurvival;
}



AdultSaturationDeficit::AdultSaturationDeficit( const AdultSaturationDeficit ^ asd )
{
  this->LowThreshold = asd->LowThreshold_;
  this->HighThreshold = asd->HighThreshold_;
  this->LowSurvival = asd->LowSurvival_;
  this->HighSurvival = asd->HighSurvival_;
}



void
AdultSaturationDeficit::CheckValidLowThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e )
{
  AdultSaturationDeficit ^ asd = static_cast<AdultSaturationDeficit^>( e->TargetObjectValue );
  double lowThreshold = System::Convert::ToDouble( e->TargetMemberValue );

  if( lowThreshold < asd->HighThreshold_ ) {
    e->IsValid = true;
  }
  else {
    e->IsValid = false;
    e->ErrorMessage = "Low threshold must be less than high threshold.";
  }
}



void
AdultSaturationDeficit::CheckValidHighThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e )
{
  AdultSaturationDeficit ^ asd = static_cast<AdultSaturationDeficit^>( e->TargetObjectValue );
  double highThreshold = System::Convert::ToDouble( e->TargetMemberValue );

  if( highThreshold > asd->LowThreshold_ ) {
    e->IsValid = true;
  }
  else {
    e->IsValid = false;
    e->ErrorMessage = "High threshold must be greather than low threshold.";
  }
}



input::Biology::AdultParameters::SaturationDeficitParameters *
AdultSaturationDeficit::GetSimObject(void)
{
  input::Biology::AdultParameters::SaturationDeficitParameters * sdp = new input::Biology::AdultParameters::SaturationDeficitParameters();

  sdp->LowSurvival = this->LowSurvival_;
  sdp->LowThreshold = this->LowThreshold_;
  sdp->HighThreshold = this->HighThreshold_;
  sdp->HighSurvival = this->HighSurvival_;

  return sdp;
}



AdultDoubleBloodMeal::AdultDoubleBloodMeal(void)
{
  input::Biology::AdultParameters::DoubleBloodMealParameters defVals;
  this->LowWeightLimit_ = defVals.LowWeightLimit;
  this->LowWeightRatio_ = defVals.LowWeightRatio;
  this->HighWeightLimit_ = defVals.HighWeightLimit;
  this->HighWeightRatio_ = defVals.HighWeightRatio;
}



AdultDoubleBloodMeal::AdultDoubleBloodMeal( const AdultDoubleBloodMeal ^ adbm )
{
  this->LowWeightLimit = adbm->LowWeightLimit_;
  this->LowWeightRatio = adbm->LowWeightRatio_;
  this->HighWeightLimit = adbm->HighWeightLimit_;
  this->HighWeightRatio = adbm->HighWeightRatio_;
}



input::Biology::AdultParameters::DoubleBloodMealParameters *
AdultDoubleBloodMeal::GetSimObject(void)
{
  input::Biology::AdultParameters::DoubleBloodMealParameters * dbmp = new input::Biology::AdultParameters::DoubleBloodMealParameters();

  dbmp->LowWeightLimit = this->LowWeightLimit_;
  dbmp->LowWeightRatio = this->LowWeightRatio_;
  dbmp->HighWeightLimit = this->HighWeightLimit_;
  dbmp->HighWeightRatio = this->HighWeightRatio_;

  return dbmp;
}



void
AdultDoubleBloodMeal::CheckValidLowThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e )
{
  AdultDoubleBloodMeal ^ adbm = static_cast<AdultDoubleBloodMeal^>( e->TargetObjectValue );
  double lowWeight = System::Convert::ToDouble( e->TargetMemberValue );

  if( lowWeight < adbm->HighWeightLimit_ ) {
    e->IsValid = true;
  }
  else {
    e->IsValid = false;
    e->ErrorMessage = "Low weight must be less than high weight.";
  }
}



void
AdultDoubleBloodMeal::CheckValidHighThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e )
{
  AdultDoubleBloodMeal ^ adbm = static_cast<AdultDoubleBloodMeal^>( e->TargetObjectValue );
  double highWeight = System::Convert::ToDouble( e->TargetMemberValue );

  if( highWeight > adbm->LowWeightLimit_ ) {
    e->IsValid = true;
  }
  else {
    e->IsValid = false;
    e->ErrorMessage = "High weight must be greather than low weight.";
  }
}



AdultBiology::AdultBiology(void)
: AgeDependentSurvival_(gcnew AdultAgeDependentSurvival()),
  Development_(gcnew AdultDevelopment()),
  Temperature_(gcnew AdultTemperature()),
  SaturationDeficit_(gcnew AdultSaturationDeficit()),
  DoubleBloodMeal_(gcnew AdultDoubleBloodMeal())
{
  input::Biology::AdultParameters defVals;
  this->SecondDevelopmentThreshold_ = defVals.SecondDevelopmentThreshold;
  this->NominalSurvival_ = defVals.NominalSurvival;
  this->DryToWetWeightFactor_ = defVals.DryToWetWeightFactor;
  this->FecundityFactor_ = defVals.FecundityFactor;
  this->MinimumOvipositionTemperature_ = defVals.MinimumOvipositionTemperature;
  this->ProportionOfFeedsOnHumans_ = defVals.ProportionOfFeedsOnHumans;
  this->InterruptedFeedsPerMeal_ = defVals.InterruptedFeedsPerMeal;
  this->ProportionOfInterruptedFeedsOnDifferentHost_ = defVals.ProportionOfInterruptedFeedsOnDifferentHost;
  this->ProportionOfAdultsRestingOutdoors_ = defVals.ProportionOfAdultsRestingOutdoors;
}



AdultBiology::AdultBiology( const AdultBiology ^ ab )
{
  this->SecondDevelopmentThreshold = ab->SecondDevelopmentThreshold_;
  this->NominalSurvival = ab->NominalSurvival_;
  this->DryToWetWeightFactor = ab->DryToWetWeightFactor_;
  this->FecundityFactor = ab->FecundityFactor_;
  this->MinimumOvipositionTemperature = ab->MinimumOvipositionTemperature_;
  this->ProportionOfFeedsOnHumans = ab->ProportionOfFeedsOnHumans_;
  this->InterruptedFeedsPerMeal = ab->InterruptedFeedsPerMeal_;
  this->ProportionOfInterruptedFeedsOnDifferentHost = ab->ProportionOfInterruptedFeedsOnDifferentHost_;
  this->ProportionOfAdultsRestingOutdoors = ab->ProportionOfAdultsRestingOutdoors_;
  this->AgeDependentSurvival = gcnew AdultAgeDependentSurvival( ab->AgeDependentSurvival_ );
  this->Development = gcnew AdultDevelopment( ab->Development_ );
  this->Temperature = gcnew AdultTemperature( ab->Temperature_ );
  this->SaturationDeficit = gcnew AdultSaturationDeficit( ab->SaturationDeficit_ );
  this->DoubleBloodMeal = gcnew AdultDoubleBloodMeal( ab->DoubleBloodMeal_ );
}



input::Biology::AdultParameters *
AdultBiology::GetSimObject(void)
{
  input::Biology::AdultParameters * ap = new input::Biology::AdultParameters();

  ap->SecondDevelopmentThreshold = this->SecondDevelopmentThreshold_;
  ap->NominalSurvival = this->NominalSurvival_;
  ap->DryToWetWeightFactor = this->DryToWetWeightFactor_;
  ap->FecundityFactor = this->FecundityFactor_;
  ap->MinimumOvipositionTemperature = this->MinimumOvipositionTemperature_;
  ap->ProportionOfFeedsOnHumans = this->ProportionOfFeedsOnHumans_;
  ap->InterruptedFeedsPerMeal = this->InterruptedFeedsPerMeal_;
  ap->ProportionOfInterruptedFeedsOnDifferentHost = this->ProportionOfInterruptedFeedsOnDifferentHost_;
  ap->ProportionOfAdultsRestingOutdoors = this->ProportionOfAdultsRestingOutdoors_;
  ap->AgeDependentSurvival = this->AgeDependentSurvival->GetSimObject();
  ap->Development = this->Development_->GetSimObject();
  ap->Temperature = this->Temperature_->GetSimObject();
  ap->SaturationDeficit = this->SaturationDeficit_->GetSimObject();
  ap->DoubleBloodMeal = this->DoubleBloodMeal_->GetSimObject();

  return ap;
}



BiologyParameters::BiologyParameters(void)
: Egg_(gcnew EggBiology()),
  Larvae_(gcnew LarvaeBiology()),
  Pupae_(gcnew PupaeBiology()),
  Adult_(gcnew gui::AdultBiology())
{}



BiologyParameters::BiologyParameters( const BiologyParameters ^ bp )
{
  this->Egg = gcnew EggBiology( bp->Egg_ );
  this->Larvae = gcnew LarvaeBiology( bp->Larvae_ );
  this->Pupae = gcnew PupaeBiology( bp->Pupae_ );
  this->Adult = gcnew AdultBiology( bp->Adult_ );
}



input::Biology *
BiologyParameters::GetSimObject(void)
{
  input::Biology * biology = new input::Biology();
  
  biology->Egg = this->Egg_->GetSimObject();
  biology->Larvae = this->Larvae_->GetSimObject();
  biology->Pupae = this->Pupae_->GetSimObject();
  biology->Adult = this->Adult_->GetSimObject();

  return biology;
}



void
BiologyParameters::LoadDefaultValues(void)
{
  // property access to provide notification
  Egg = gcnew EggBiology();
  Larvae = gcnew LarvaeBiology();
  Pupae = gcnew PupaeBiology();
  Adult = gcnew AdultBiology();
}
