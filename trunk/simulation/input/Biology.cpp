// ============================================================================ //
// BioClass.cpp                                                                 //
//                                                                              //
// Specifiy default values for mosquito biology by using initializer lists with //
// default constructors.                                                        //
// ============================================================================ //
#include "StdAfx.h"
#include "Biology.h"

using namespace input;



Biology::Biology(void)
: Egg(new EggParameters()),
  Larvae(new LarvaeParameters()),
  Pupae(new PupaeParameters()),
  Adult(new AdultParameters())
{}



Biology::~Biology(void)
{
  delete Egg;
  delete Larvae;
  delete Pupae;
  delete Adult;
}



Biology::EggParameters::EggParameters(void)
: MinimumHatchTemperature( 22.0 ),
  FloodHatchRatio( 0.596 ),
  SpontaneousHatchRatio( 0.197 ),
  NominalSurvival( 0.99 ),
  Development(new DevelopmentParameters()),
  Temperature(new TemperatureParameters()),
  SaturationDeficit(new SaturationDeficitParameters),
  Predation(new PredationParameters())
{}



Biology::EggParameters::~EggParameters(void)
{
  delete Development;
  delete Temperature;
  delete SaturationDeficit;
  delete Predation;
}




Biology::EggParameters::DevelopmentParameters::DevelopmentParameters(void)
: RO25( 0.01066 ),
  DHA( 10798.18 ),
  DHH( 100000 ),
  THALF( 14184.5 )
{}



Biology::EggParameters::DevelopmentParameters::~DevelopmentParameters(void)
{}



Biology::EggParameters::TemperatureParameters::TemperatureParameters(void)
: LowLethalSurvival( 0.05 ),
  LowLethalThreshold( -14 ),
  LowThreshold( -6 ),
  HighThreshold( 30 ),
  HighLethalThreshold( 47 ),
  HighLethalSurvival( 0.05 )
{}



Biology::EggParameters::TemperatureParameters::~TemperatureParameters(void)
{}



Biology::EggParameters::SaturationDeficitParameters::SaturationDeficitParameters(void)
: WetSurvival( 1 ),
  HighSunExposureThreshold( 0.85 ),
  HighSunExposureSurvival( 0.95 ),
  LowThreshold( 10 ),
  HighThreshold( 40 ),
  LowSurvival( 0.99 ),
  HighSurvival( 0.95 )
{}



Biology::EggParameters::SaturationDeficitParameters::~SaturationDeficitParameters(void)
{}



Biology::EggParameters::PredationParameters::PredationParameters(void)
: LowSurvival( 1 ),
  LowThreshold( 20 ),
  HighThreshold( 30 ),
  HighSurvival( 0.7 )
{}



Biology::EggParameters::PredationParameters::~PredationParameters(void)
{}



Biology::LarvaeParameters::LarvaeParameters(void)
: WeightAtHatch( 0.001 ),
  ChronologicalBasisAt26C( 0.001 ),
  NominalSurvival( 0.99 ),
  PupationSurvival( 0.95 ),
  DryContainerSurvival( 0.05 ),
  MinimumWeightForSurvival( 0.0009 ),
  NumberEulerSteps( 8),
  CadaverFoodRatio( 0.4 ),
  Development(new DevelopmentParameters()),
  PupationWeight(new PupationWeightParameters()),
  Temperature(new TemperatureParameters()),
  Food(new FoodParameters()),
  Fasting(new FastingParameters())
{}



Biology::LarvaeParameters::~LarvaeParameters(void)
{
  delete Development;
  delete PupationWeight;
  delete Temperature;
  delete Food;
  delete Fasting;
}




Biology::LarvaeParameters::DevelopmentParameters::DevelopmentParameters(void)
: RO25( 0.00873 ),
  DHA( 26018.51 ),
  DHH( 55990.75 ),
  THALF( 304.58 )
{}



Biology::LarvaeParameters::DevelopmentParameters::~DevelopmentParameters(void)
{}



Biology::LarvaeParameters::PupationWeightParameters::PupationWeightParameters(void)
: Slope( -0.0389 ),
  Intercept( 2.11 ),
  MinimumWeightForPupation( 0.1 ),
  MaximumDevelopment( 8.0 )
{}



Biology::LarvaeParameters::PupationWeightParameters::~PupationWeightParameters(void)
{}



Biology::LarvaeParameters::TemperatureParameters::TemperatureParameters(void)
: LowLethalSurvival( 0.05 ),
  LowLethalThreshold( 5 ),
  LowThreshold( 10 ),
  HighThreshold( 39 ),
  HighLethalThreshold( 44 ),
  HighLethalSurvival( 0.05 )
{}



Biology::LarvaeParameters::TemperatureParameters::~TemperatureParameters(void)
{}



Biology::LarvaeParameters::FoodParameters::FoodParameters(void)
: UseRandomFood(false),
  AssimilationRate( 0.3 ),
  ExploitationRate( 0.8 ),
  ExploitationRateIndependence( 0.1 ),
  MetabolicWeightLossRate( 0.016 ),
  MetabolicWeightLossExponent( 0.667 )
{}



Biology::LarvaeParameters::FoodParameters::~FoodParameters(void)
{}



Biology::LarvaeParameters::FastingParameters::FastingParameters(void)
: NoFastingSurvival( 1.0 ),
   LipidReserveSurvival( 0.95 ),
   NoLipidReserveSurvival( 0.5 ),
   NonDepletableLipidReserve( 0.15 ),
   WeightToLipidSlope( 0.059 ),
   WeightToLipidConstant( 6.9 )
{}



Biology::LarvaeParameters::FastingParameters::~FastingParameters(void)
{}



Biology::PupaeParameters::PupaeParameters(void)
: NominalSurvival( 0.99 ),
  EmergenceSurvival( 0.83 ),
  FemaleEmergence( 0.5 ),
  Development(new DevelopmentParameters()),
  Temperature(new TemperatureParameters())
{}



Biology::PupaeParameters::~PupaeParameters(void)
{
  delete Development;
  delete Temperature;
}



Biology::PupaeParameters::DevelopmentParameters::DevelopmentParameters(void)
: RO25( 0.0161 ),
  DHA( 14931.94 ),
  DHH( -472379 ),
  THALF( 148.45 )
{}



Biology::PupaeParameters::DevelopmentParameters::~DevelopmentParameters(void)
{}



Biology::PupaeParameters::TemperatureParameters::TemperatureParameters(void)
: LowLethalSurvival( 0.05 ),
  LowLethalThreshold( 5 ),
  LowThreshold( 10 ),
  HighThreshold( 39 ),
  HighLethalThreshold( 44 ),
  HighLethalSurvival( 0.05 )
{}



Biology::PupaeParameters::TemperatureParameters::~TemperatureParameters(void)
{}



Biology::AdultParameters::AdultParameters(void)
: SecondDevelopmentThreshold( 0.58 ),
  NominalSurvival( 0.91 ),
  DryToWetWeightFactor( 1.655 ),
  FecundityFactor( 45.9 ),
  MinimumOvipositionTemperature( 18 ),
  ProportionOfFeedsOnHumans( 0.9 ),
  InterruptedFeedsPerMeal( 2 ),
  ProportionOfInterruptedFeedsOnDifferentHost( 0.6 ),
  ProportionOfAdultsRestingOutdoors( 0.6 ),
  AgeDependentSurvival(new AgeDependentSurvivalParameters()),
  Development(new DevelopmentParameters()),
  Temperature(new TemperatureParameters()),
  SaturationDeficit(new SaturationDeficitParameters()),
  DoubleBloodMeal(new DoubleBloodMealParameters())
{}



Biology::AdultParameters::~AdultParameters(void)
{
  delete AgeDependentSurvival;
  delete Development;
  delete Temperature;
  delete SaturationDeficit;
  delete DoubleBloodMeal;
}



Biology::AdultParameters::AgeDependentSurvivalParameters::AgeDependentSurvivalParameters(void)
: CutoffAge( 10 ),
  YoungSurvival( 0.99 ),
  OldSurvival( 0.85 )
{}



Biology::AdultParameters::AgeDependentSurvivalParameters::~AgeDependentSurvivalParameters(void)
{}



double
Biology::AdultParameters::AgeDependentSurvivalParameters::GetSurvival( int age )
{
  if( age <= CutoffAge ) {
    return YoungSurvival;
  }
  else {
    return OldSurvival;
  }
}



Biology::AdultParameters::DevelopmentParameters::DevelopmentParameters(void)
: RO25( 0.00898 ),
  DHA( 15725.23 ),
  DHH( 1756481 ),
  THALF( 447.17 )
{}



Biology::AdultParameters::DevelopmentParameters::~DevelopmentParameters(void)
{}



Biology::AdultParameters::TemperatureParameters::TemperatureParameters(void)
: LowLethalSurvival( 0.05 ),
  LowLethalThreshold( 0 ),
  LowThreshold( 4 ),
  HighThreshold( 40 ),
  HighLethalThreshold( 50 ),
  HighLethalSurvival( 0.05 )
{}



Biology::AdultParameters::TemperatureParameters::~TemperatureParameters(void)
{}



Biology::AdultParameters::SaturationDeficitParameters::SaturationDeficitParameters(void)
: LowSurvival( 1 ),
  LowThreshold( 10 ),
  HighThreshold( 30 ),
  HighSurvival( 0.95 )
{}



Biology::AdultParameters::SaturationDeficitParameters::~SaturationDeficitParameters(void)
{}



Biology::AdultParameters::DoubleBloodMealParameters::DoubleBloodMealParameters(void)
: LowWeightLimit( 0.5 ),
  LowWeightRatio( 1 ),
  HighWeightLimit( 3.5 ),
  HighWeightRatio( 0.1 )
{}



Biology::AdultParameters::DoubleBloodMealParameters::~DoubleBloodMealParameters(void)
{}
