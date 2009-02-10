#include "StdAfx.h"
#include "CsPdsFile.h"
#include "../../gui/objs/Util.h"
#include <string>

using namespace System;
using namespace System::IO;
using namespace cspds2dml;



CsPdsFile::CsPdsFile( String ^ filename )
: _filename(filename)
{
  Parse();
}



CsPdsFile::~CsPdsFile(void)
{}



void
CsPdsFile::Parse(void)
{
  // open pds file and parse
  StreamReader ^ sr;
  sr = gcnew StreamReader( _filename );

  _location = gcnew gui::Location();

  // read location parameters
  //_location->DoDensimOutput_ = Convert::ToBoolean(Convert::ToInt32(sr->ReadLine()));
  sr->ReadLine();
  _location->Biology->Larvae->Food->UseRandomFood = Convert::ToBoolean(Convert::ToInt32(sr->ReadLine()));
  //_location->SimulationLength_ = Convert::ToInt32(sr->ReadLine());
  int simulationLength = Convert::ToInt32(sr->ReadLine());
  //_location->HumanDensity_ = Convert::ToSingle(sr->ReadLine());
  sr->ReadLine();
  //_location->HumanAvailability_ = Convert::ToSingle(sr->ReadLine());
  sr->ReadLine();
  //_location->HumanGrowthRate_ = Convert::ToSingle(sr->ReadLine());
  sr->ReadLine();
  //_location->MammalDensity_ = Convert::ToSingle(sr->ReadLine());
  sr->ReadLine();
  //_location->MammalAvailability_ = Convert::ToSingle(sr->ReadLine());
  sr->ReadLine();
  //_location->MammalGrowthRate_ = Convert::ToSingle(sr->ReadLine());
  sr->ReadLine();
  _location->Biology->Adult->ProportionOfAdultsRestingOutdoors = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Larvae->NumberEulerSteps = Convert::ToInt32(sr->ReadLine());

  int numContainers = Convert::ToInt32(sr->ReadLine());

  // read container parameters
  for( int i = 0; i < numContainers; ++i ) {
    gui::Container ^ container = gcnew gui::Container();
    container->Name = sr->ReadLine()->Trim();
    container->Length = Convert::ToSingle(sr->ReadLine());
    container->Width = Convert::ToSingle(sr->ReadLine());
    container->Height = Convert::ToSingle(sr->ReadLine());
    container->Diameter = Convert::ToSingle(sr->ReadLine());

    if( container->Diameter == 0 ) {
      container->Shape = gui::Container::ShapeType::Rectangular;
    }
    else {
      container->Shape = gui::Container::ShapeType::Circular;
    }

    container->MonthlyTurnoverRate = Convert::ToSingle(sr->ReadLine());
    container->Density = Convert::ToSingle(sr->ReadLine());
    container->IsCovered = Convert::ToBoolean(Convert::ToInt32(sr->ReadLine()));
    container->CoverReduction = Convert::ToSingle(sr->ReadLine());
    container->SunExposure = Convert::ToSingle(sr->ReadLine());
    container->Cooling = Convert::ToSingle(sr->ReadLine());
    container->Drawdown = Convert::ToSingle(sr->ReadLine());
    container->WatershedRatio = Convert::ToSingle(sr->ReadLine());

    if( container->WatershedRatio == 0 ) {
      container->FillMethod = gui::Container::Fill::ManualFill;
    }
    else {
      container->FillMethod = gui::Container::Fill::RainFill;
    }

    container->InitFood = Convert::ToSingle(sr->ReadLine());
    container->FoodGainJan = Convert::ToSingle(sr->ReadLine());
    container->FoodGainFeb = Convert::ToSingle(sr->ReadLine());
    container->FoodGainMar = Convert::ToSingle(sr->ReadLine());
    container->FoodGainApr = Convert::ToSingle(sr->ReadLine());
    container->FoodGainMay = Convert::ToSingle(sr->ReadLine());
    container->FoodGainJun = Convert::ToSingle(sr->ReadLine());
    container->FoodGainJul = Convert::ToSingle(sr->ReadLine());
    container->FoodGainAug = Convert::ToSingle(sr->ReadLine());
    container->FoodGainSep = Convert::ToSingle(sr->ReadLine());
    container->FoodGainOct = Convert::ToSingle(sr->ReadLine());
    container->FoodGainNov = Convert::ToSingle(sr->ReadLine());
    container->FoodGainDec = Convert::ToSingle(sr->ReadLine());
    container->FoodDecayRate = Convert::ToSingle(sr->ReadLine());
    container->InitEggs = Convert::ToSingle(sr->ReadLine());
    _location->Containers->Add( container );
  }

  // biology
  _location->Biology->Egg->Development->RO25 = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Egg->Development->DHA = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Egg->Development->DHH = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Egg->Development->THALF = Convert::ToSingle(sr->ReadLine());

  _location->Biology->Larvae->Development->RO25 = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Larvae->Development->DHA = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Larvae->Development->DHH = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Larvae->Development->THALF = Convert::ToSingle(sr->ReadLine());

  _location->Biology->Pupae->Development->RO25 = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Pupae->Development->DHA = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Pupae->Development->DHH = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Pupae->Development->THALF = Convert::ToSingle(sr->ReadLine());

  _location->Biology->Adult->Development->RO25 = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Adult->Development->DHA = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Adult->Development->DHH = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Adult->Development->THALF = Convert::ToSingle(sr->ReadLine());

  _location->Biology->Egg->SaturationDeficit->HighThreshold = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Egg->SaturationDeficit->LowThreshold = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Egg->SaturationDeficit->HighSurvival = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Egg->SaturationDeficit->LowSurvival = Convert::ToSingle(sr->ReadLine());

  _location->Biology->Egg->Temperature->LowLethalThreshold = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Egg->Temperature->LowThreshold = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Egg->Temperature->HighThreshold = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Egg->Temperature->HighLethalThreshold = Convert::ToSingle(sr->ReadLine());

  _location->Biology->Adult->Temperature->LowLethalThreshold = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Adult->Temperature->LowThreshold = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Adult->Temperature->HighThreshold = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Adult->Temperature->HighLethalThreshold = Convert::ToSingle(sr->ReadLine());

  _location->Biology->Adult->SaturationDeficit->LowThreshold = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Adult->SaturationDeficit->HighThreshold = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Adult->SaturationDeficit->LowSurvival = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Adult->SaturationDeficit->HighSurvival = Convert::ToSingle(sr->ReadLine());

  _location->Biology->Larvae->PupationWeight->Slope = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Larvae->PupationWeight->Intercept = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Larvae->PupationWeight->MinimumWeightForPupation = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Larvae->PupationWeight->MinimumAgeForPupation = Convert::ToSingle(sr->ReadLine());

  _location->Biology->Larvae->Fasting->NoFastingSurvival = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Larvae->Fasting->NoLipidReserveSurvival = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Larvae->Fasting->LipidReserveSurvival = Convert::ToSingle(sr->ReadLine());

  _location->Biology->Egg->SaturationDeficit->WetSurvival = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Egg->SaturationDeficit->HighSunExposureSurvival = Convert::ToSingle(sr->ReadLine());

  _location->Biology->Larvae->Temperature->LowLethalThreshold = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Larvae->Temperature->LowThreshold = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Larvae->Temperature->HighThreshold = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Larvae->Temperature->HighLethalThreshold = Convert::ToSingle(sr->ReadLine());

  _location->Biology->Larvae->MaximumDevelopment = Convert::ToSingle(sr->ReadLine());
  sr->ReadLine();   // dummy var, d

  _location->Biology->Egg->MinimumHatchTemperature = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Egg->FloodHatchRatio = Convert::ToSingle(sr->ReadLine());

  _location->Biology->Larvae->WeightAtHatch = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Adult->NominalSurvival = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Larvae->NominalSurvival = Convert::ToSingle(sr->ReadLine());

  _location->Biology->Pupae->Temperature->LowLethalThreshold = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Pupae->Temperature->LowThreshold = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Pupae->Temperature->HighThreshold = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Pupae->Temperature->HighLethalThreshold = Convert::ToSingle(sr->ReadLine());

  _location->Biology->Pupae->NominalSurvival = Convert::ToSingle(sr->ReadLine());
  
  _location->Biology->Larvae->PupationSurvival = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Egg->SpontaneousHatchRatio = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Egg->NominalSurvival = Convert::ToSingle(sr->ReadLine());

  _location->Biology->Pupae->EmergenceSurvival = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Pupae->FemaleEmergence = Convert::ToSingle(sr->ReadLine());

  //_location->Biology->Adult->Density->LowThreshold = Convert::ToSingle(sr->ReadLine());
  sr->ReadLine();
  //_location->Biology->Adult->Density->HighThreshold = Convert::ToSingle(sr->ReadLine());
  sr->ReadLine();
  //_location->Biology->Adult->Density->LowSurvival = Convert::ToSingle(sr->ReadLine());
  sr->ReadLine();
  //_location->Biology->Adult->Density->HighSurvival = Convert::ToSingle(sr->ReadLine());
  sr->ReadLine();

  _location->Biology->Adult->InterruptedFeedsPerMeal = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Adult->FecundityFactor = Convert::ToSingle(sr->ReadLine());
  //_location->Biology->Adult->ReturnOvipositionRate = Convert::ToSingle(sr->ReadLine());
  sr->ReadLine();

  _location->Biology->Adult->MinimumOvipositionTemperature = Convert::ToSingle(sr->ReadLine());

  _location->Biology->Larvae->Food->AssimilationRate = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Larvae->Food->ExploitationRate = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Larvae->Food->ExploitationRateIndependence = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Larvae->Food->MetabolicWeightLossRate = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Larvae->Food->MetabolicWeightLossExponent = Convert::ToSingle(sr->ReadLine());

  _location->Biology->Adult->DoubleBloodMeal->LowWeightLimit = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Adult->DoubleBloodMeal->HighWeightLimit = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Adult->DoubleBloodMeal->LowWeightRatio = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Adult->DoubleBloodMeal->HighWeightRatio = Convert::ToSingle(sr->ReadLine());

  _location->Biology->Larvae->CadaverFoodRatio = Convert::ToSingle(sr->ReadLine());

  _location->Biology->Egg->Predation->LowThreshold = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Egg->Predation->HighThreshold = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Egg->Predation->LowSurvival = Convert::ToSingle(sr->ReadLine());
  _location->Biology->Egg->Predation->HighSurvival = Convert::ToSingle(sr->ReadLine());

  String ^ weatherDir = sr->ReadLine();
  String ^ weatherFile = sr->ReadLine();

  // done reading pds file
  sr->Close();

  // add first weather file
  gui::WeatherYear ^ firstWeatherYear = gui::WeatherYear::OpenFromDly( weatherDir + weatherFile );
  _location->Weather->AddWeatherYear( firstWeatherYear );

  String ^ base = weatherFile->Substring(0,6);
  int firstYear = Convert::ToInt32( weatherFile->Substring(6,2) );

  for( int i = 1; i <= simulationLength; ++i ) {
    String ^ nextFile = base + (firstYear + i) + ".dly";
    gui::WeatherYear ^ nextWeatherYear = gui::WeatherYear::OpenFromDly( weatherDir + nextFile );
    _location->Weather->AddWeatherYear( nextWeatherYear );
  }

  //_location->StartYear_ = _location->Weather_->GetWeatherPeriod().begin().year();
}



gui::Location ^
CsPdsFile::Location::get(void)
{
  return _location;
}
