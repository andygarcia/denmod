#include "StdAfx.h"
#include "SimLocation.h"
#include <cmath>
#include <algorithm>

using namespace boost::gregorian;
using namespace input;
using namespace sim::cs;

extern double DevelopmentRate( double p25, double tempt, double dha, double dh, double th2 );



SimLocation::SimLocation( const input::Location * location, boost::gregorian::date startDate, boost::gregorian::date stopDate, const sim::output::PopData * popData )
: _location(location),
  Output_(new output::CimsimOutput()),
  _outputReleased(false),
  TotalSterileMalesYesterday(0),
  MosqAgeDistr(std::vector<double>( MaxAgeOviAdults+1, 0 )),
  _preOviBiters(0),
  _oviBiters(0)
{
  BeginDate_ = startDate;
  EndDate_ = stopDate;

  // read initial population/container data
  if( popData == NULL ) {
    UsingPop_ = false;

    InitialPreOviAdultCohorts = PreOviAdultCohortCollection();
    InitialOviAdultCohorts = OviAdultCohortCollection();

    // read containers
    std::vector<input::Container*>::const_iterator itCtnr;
    for( itCtnr = _location->Containers_.begin(); itCtnr != _location->Containers_.end(); itCtnr++ ) {
      // no pop data to use
      SimContainer * newContainer = new SimContainer( *itCtnr, _location->Biology_ );
      Containers_.push_back( newContainer );
    }
  }
  else {
    UsingPop_ = true;

    this->PreOviAdultCohorts = popData->PreOviAdultCohorts;
    this->OviAdultCohorts = popData->OviAdultCohorts;
    this->MosqAgeDistr = popData->MosqAgeDistr;

    // save initial state for DENSiM
    InitialPreOviAdultCohorts = PreOviAdultCohorts;
    InitialOviAdultCohorts = OviAdultCohorts;

    // read containers
    std::vector<input::Container*>::const_iterator itCtnr;
    for( itCtnr = _location->Containers_.begin(); itCtnr != _location->Containers_.end(); itCtnr++ ) {
      if( popData->Containers_.count((*itCtnr)->Name_) == 0 ) {
        // TODO - pop data was not found for this container even though pop is in use, what to do?
        // need to have a gui check for this?
        SimContainer * newContainer = new SimContainer( *itCtnr, _location->Biology_ );
        Containers_.push_back( newContainer );
      }
      else {
        SimContainer * newContainer = new SimContainer( *itCtnr, _location->Biology_, popData->Containers_.find((*itCtnr)->Name_)->second );
        Containers_.push_back( newContainer );
      }
    }


  }

  // read controls and initialize schedules
  Controls_ = std::vector<Control*>( _location->Controls_ );

  date_period wxAvailable = _location->Weather_->GetWeatherPeriod();
  date wxMinDate = wxAvailable.begin();
  date wxMaxDate = wxAvailable.end();

  std::vector<Control*>::iterator itCtrl;
  for( itCtrl = Controls_.begin(); itCtrl != Controls_.end(); ++itCtrl ) {
    Control * ctrl = *itCtrl;

    if( ctrl->GetControlType() == Control::SourceReduction ) {
      SourceReduction * sr = dynamic_cast<SourceReduction*>(ctrl);
      sr->GetTargets();
      sr->CalculateSchedule(wxMinDate, wxMaxDate);
      SourceReductions_.push_back(sr);
    }
    else if( (*itCtrl)->GetControlType() == Control::OvipositionExclusion ) {
      OvipositionExclusion * oe = dynamic_cast<OvipositionExclusion*>((*itCtrl));
      oe->CalculateSchedule(wxMinDate,wxMaxDate);
      OvipositionExclusions_.push_back(oe);
    }
    else if( (*itCtrl)->GetControlType() == Control::EggDestruction ) {
      EggDestruction * ed = dynamic_cast<EggDestruction*>((*itCtrl));
      ed->CalculateSchedule(wxMinDate,wxMaxDate);
      EggDestructions_.push_back(ed);
    }
    else if( (*itCtrl)->GetControlType() == Control::Larvicide ) {
      Larvicide * li = dynamic_cast<Larvicide*>((*itCtrl));
      li->CalculateSchedule(wxMinDate,wxMaxDate);
      li->CalculateMortality();
      Larvicides_.push_back(li);
    }
    else if( ctrl->GetControlType() == Control::SterileMaleRelease) {
      SterileMaleRelease * sm = dynamic_cast<SterileMaleRelease*>(ctrl);
      sm->CalculateSchedule(wxMinDate,wxMaxDate);
      SterileMaleReleases_.push_back(sm);
    }
    else if( ctrl->GetControlType() == Control::SpaceSpray ) {
      SpaceSpray * ss = dynamic_cast<SpaceSpray*>(ctrl);
      ss->CalculateSchedule(wxMinDate,wxMaxDate);
      SpaceSprays_.push_back(ss);
    }
    else if( ctrl->GetControlType() == Control::ResidualSpray ) {
      ResidualSpray * rs = dynamic_cast<ResidualSpray*>(ctrl);
      rs->CalculateSchedule(wxMinDate,wxMaxDate);
      rs->CalculateMortality();
      ResidualSprays_.push_back(rs);
    }
  }

  // biology
  _adultP25 = _location->Biology_->Adult->Development->RO25;
  _adultDHA = _location->Biology_->Adult->Development->DHA;
  _adultDHH = _location->Biology_->Adult->Development->DHH;
  _adultTH2 = _location->Biology_->Adult->Development->THALF;
  _adultFirstDevelopmentThreshold = _location->Biology_->Adult->FirstDevelopmentThreshold;
  _adultSecondDevelopmentThreshold = _location->Biology_->Adult->SecondDevelopmentThreshold;

  _adultNominalSurvival = _location->Biology_->Adult->NominalSurvival;
  _adultTemperatureSurvival = _location->Biology_->Adult->Temperature;
  _adultSatDefSurvival = _location->Biology_->Adult->SaturationDeficit;

  _minimumOvipositionTemperature = _location->Biology_->Adult->MinimumOvipositionTemperature;
  _fecundityCoefficient = _location->Biology_->Adult->FecundityFactor;
  _proportionAdultsOutdoor = _location->Biology_->Adult->ProportionOfAdultsRestingOutdoors;
  _interruptedFeedsPerMeal = _location->Biology_->Adult->InterruptedFeedsPerMeal;
  _adultDoubleBloodMeals = _location->Biology_->Adult->DoubleBloodMeal;
}



SimLocation::~SimLocation(void)
{
  std::vector<SimContainer*>::iterator itCont;
  for( itCont = Containers_.begin(); itCont != Containers_.end(); ++itCont ) {
    delete *itCont;
  }

  if( !_outputReleased ) {
    // still managing output data, delete
    delete Output_;
  }
}



void
SimLocation::Start(void)
{
  StartSimulation();
}



void
SimLocation::StartSimulation(void)
{
  // initialize container for simulation
  ContainerCollection::iterator itCont;
  for( itCont = Containers_.begin(); itCont != Containers_.end(); ++itCont ) {
    (*itCont)->Initialize( BeginDate_ );
  }

  // iterate through years
  for( Year = BeginDate_.year(); Year <= EndDate_.year(); Year++ ) {
    // read current year's weather
    ReadWeather(Year);

    // yearly initialization of container
    for( itCont = Containers_.begin(); itCont != Containers_.end(); ++itCont ) {
      (*itCont)->InitializeYear(Year);
    }

    // run simulation for a year or up to stop date
    DoYear();
    if( CurrentDate_ > EndDate_ ) {
      break;
    }
  }
  Output_->SetPopData( GeneratePopData() );
}



void
SimLocation::DoYear(void)
{
#ifdef _DEBUG
  // create log files for this year
  std::ostringstream oss;
  oss << Year;
  std::string ssYear = oss.str();

  _locationLog = output::LocationLog( "CS 3.0 - " + ssYear + " - Location" );
  _adultSurvivalLog = output::AdultSurvivalLog( "CS 3.0 - " + ssYear + " - Adult Survival" );
#endif

  // simulate each day in this year
  ContainerCollection::iterator itCont;
  day_iterator itDay = day_iterator( date(Year,1,1) );
  int numDays = gregorian_calendar::is_leap_year( Year ) ? 366 : 365;
  for( Day = 1; Day <= numDays; ++Day, ++itDay) {

    CurrentDate_ = *itDay;
    if( CurrentDate_ > EndDate_ ) {
      return;
    }

    for( itCont = Containers_.begin(); itCont != Containers_.end(); ++itCont ) {
      // current container
      SimContainer * c = *itCont;
      c->DoDay( CurrentDate_ );

      // calculate water depth and temp
      c->CalculateWaterDepth( Rain[Day], RelHumid[Day] );
      c->CalculateWaterTemperature( TemperatureMin[Day], TemperatureAvg[Day], TemperatureMax[Day] );


      // calculate immature development rates
      c->CalculateDevelopmentRates(Day);


      // possibly initialize eggs on first day it not using PopData
      if( !UsingPop_ && CurrentDate_ == BeginDate_ ) {
        c->InitializeEggs();
      }


      // adjust container densities for nominal losses and gains
      if( IsEndOfMonth(CurrentDate_) ) {
        c->ApplyMonthlyDensityAdjustment();
      }

      // apply source reduction
      for( std::vector<SourceReduction*>::iterator itSr = SourceReductions_.begin(); itSr != SourceReductions_.end(); ++itSr ) {
        if( (*itSr)->IsDateScheduled( CurrentDate_ ) ) {
          if( (*itSr)->IsTarget( c->Name ) ) {
            // for each source redution, if today is scheduled, and container is targetted, apply the reduction
            double rateOfReduction = (*itSr)->GetTargetParams(c->Name)->RateOfReduction;
            c->ApplySourceReduction( rateOfReduction );
          }
        }
      }

      // recover excluded containers
      if( IsEndOfMonth(CurrentDate_) ) {
        c->RecoverExcluded();
      }

      // apply oviposition exclusion
      for( std::vector<OvipositionExclusion*>::iterator itOe = OvipositionExclusions_.begin(); itOe != OvipositionExclusions_.end(); ++itOe ) {
        if( (*itOe)->IsDateScheduled( CurrentDate_ ) ) {
          if( (*itOe)->IsTarget( c->Name ) ) {
            // for each oviposition exclusion, if today is scheduled, and container is targetted, apply the exclusion
            double rateOfExclusion = (*itOe)->GetTargetParams(c->Name)->RateOfExclusion;
            double rateOfRecovery = (*itOe)->GetTargetParams(c->Name)->RateOfRecovery;
            c->ApplyOvipositionExclusion( rateOfExclusion, rateOfRecovery );
          }
        }
      }

      // recover treated containers
      if( IsEndOfMonth(CurrentDate_) ) {
        c->RecoverTreated();
      }

      // for each larvicide
      for( std::vector<Larvicide*>::iterator itLi = Larvicides_.begin(); itLi != Larvicides_.end(); ++itLi ) {
        if( (*itLi)->IsDateScheduled( CurrentDate_ ) ) {
          if( (*itLi)->IsTarget( c->Name ) ) {
            // for each larvicide, if today is scheduled and container is targetted, begin a new treatment
            c->BeginNewLarvicideTreatment( *itLi );
          }
        }
      }

      // apply egg destruction
      for( std::vector<EggDestruction*>::iterator itEd = EggDestructions_.begin(); itEd != EggDestructions_.end(); ++itEd ) {
        if( (*itEd)->IsDateScheduled( CurrentDate_ ) ) {
          if( (*itEd)->IsTarget( c->Name ) ) {
            // for each egg destruction, if today is scheduled, and container is targetted, apply the exclusion
            double rateOfDestruction = (*itEd)->GetTargetParams(c->Name)->RateOfDestruction;
            c->ApplyEggDestruction( rateOfDestruction );
          }
        }
      }


      // calculate egg survival, hatch/advance embryonating eggs
      c->CalculateSaturationDeficitEggSurvival( Day, SD[Day] );
      c->CalculateTemperatureEggSurvival(Day);
      c->CalculatePredationEggSurvival(Day);
      c->CalculateCumulativeEggSurvival();
      c->AdvanceEggs(Day);


      // calculate larvae survivals, food levels and consumption, weight gain, and advance
      int numEulerSteps =  _location->Biology_->Larvae->NumberEulerSteps;
      c->ApplyDryContainerToNewLarvae(Day);
      c->AdjustFood(CurrentDate_);
      c->CalculateTemperatureLarvalSurvival(Day);
      c->CalculateLarvicideLarvalSurvival(CurrentDate_);
      c->CalculateWaterDepthLarvalSurvival(Day);
      c->CalculateLarvalFoodConsumptionAndWeight( Day, numEulerSteps );
      c->AdvanceLarvae(Day);
      c->ApplyGeneticPupationDeath(Day);

      // hatch mature eggs if flooded and at the proper temperature
      c->HatchEggs(Day);


      // calculate pupal survivals and advance pupae
      c->CalculateTemperaturePupalSurvival(Day);
      c->AdvancePupae();
      c->SelectFemales();
    }

    // calculate adult development rate
    double DevRateAdult = DevelopmentRate(_adultP25, TemperatureAvg[Day] + 273.15f, _adultDHA, _adultDHH, _adultTH2 );

    // sum new female counts and weight for each container, scaling from per container to per ha
    NewFemales = 0;
    double totalWeight = 0;
    for( itCont = Containers_.begin(); itCont != Containers_.end(); ++itCont ) {
      NewFemales += (*itCont)->CalculateDensityAdjustedNewFemaleCount();
      totalWeight += (*itCont)->CalculateDensityAdjustedNewFemaleWeight();
    }

    // calculate new female wet weight for all newly emerged females per ha
    if( NewFemales > 0 ) {
      NewFemaleWeight = totalWeight / NewFemales;
      NewFemaleWeight = NewFemaleWeight * _location->Biology_->Adult->DryToWetWeightFactor;
    }
    // at this point the number and weight for the newly emerged female cohort has been calculated
    

    // calculate adult survival
    CalculateAdultTemperatureSurvival();
    CalculateAdultSatDefSurvival();
    AdultSurvival = _adultNominalSurvival * AdultSurvivalTemperature * AdultSurvivalSatDef;


    // advance pre-oviposition adults
    double newEggLayersCohorts = 0.0;
    OvipositingCohorts.clear();
    for( PreOviAdultIterator itAdult = PreOviAdultCohorts.begin(); itAdult != PreOviAdultCohorts.end(); ) {
      if( itAdult->Development < _adultFirstDevelopmentThreshold || TemperatureAvg[Day] <= _minimumOvipositionTemperature ) {
        itAdult->Age++;
        itAdult->Number = itAdult->Number * AdultSurvival;
        itAdult->Development += DevRateAdult;
        ++itAdult;
      }
      else {
        itAdult->Number = itAdult->Number * AdultSurvival;
        newEggLayersCohorts += itAdult->Number;
        OvipositingCohorts.push_back( *itAdult );
        itAdult = PreOviAdultCohorts.erase( itAdult );
      }
    }

    // establish newly emerged female cohort
    if( NewFemales > 0 ) {
      PreOviAdultCohorts.push_back( PreOviAdultCohort(1, NewFemales, DevRateAdult, NewFemaleWeight) );
    }

    // apply space spray to pre ovi adults
    for( std::vector<SpaceSpray*>::iterator itSs = SpaceSprays_.begin(); itSs != SpaceSprays_.end(); ++itSs ) {
      if( (*itSs)->IsDateScheduled(CurrentDate_) ) {
        SpaceSpray * ss = *itSs;

        for( PreOviAdultIterator itAdult = PreOviAdultCohorts.begin(); itAdult != PreOviAdultCohorts.end(); ) {
          double indoorSurvival = itAdult->Number * (1 - ss->GetIndoorMortality()) * (1 - _proportionAdultsOutdoor);
          double outdoorSurvival = itAdult->Number * (1 - ss->GetOutdoorMortality()) * _proportionAdultsOutdoor;
          itAdult->Number = indoorSurvival + outdoorSurvival;
          if( itAdult->Number == 0 ) {
            itAdult = PreOviAdultCohorts.erase(itAdult);
          }
          else {
            ++itAdult;
          }
        }
      }
    }

    // apply residual spray to pre ovi adults
    if( ResidualSprays_.size() > 0 ) {
      ResidualSpray * rs = ResidualSprays_.at(0);
      if( rs->GetSurvival(CurrentDate_) < 1 ) {
        double surfaceRatio = rs->GetTreatedInteriorProportion();
        double houseRatio = rs->GetTreatedHousesProportion();
        double survival = rs->GetSurvival(CurrentDate_);

        for( PreOviAdultIterator itAdult = PreOviAdultCohorts.begin(); itAdult != PreOviAdultCohorts.end(); ) {
          double IndoorSurviving = itAdult->Number * (1 - _proportionAdultsOutdoor) * surfaceRatio * houseRatio * survival;
          double OutdoorSurviving = itAdult->Number * _proportionAdultsOutdoor;
          itAdult->Number = IndoorSurviving + OutdoorSurviving;
          if( itAdult->Number == 0 ) {
            itAdult = PreOviAdultCohorts.erase(itAdult);
          }
          else {
            ++itAdult;
          }
        }
      }
    }


    // advanced post oviposition adults
    double eggLayersCohorts = 0.0;
    for( OviAdultIterator itAdult = OviAdultCohorts.begin(); itAdult != OviAdultCohorts.end(); ) {
      if( itAdult->Development < _adultSecondDevelopmentThreshold || TemperatureAvg[Day] <= _minimumOvipositionTemperature ) {
        itAdult->Age++;
        itAdult->Number = itAdult->Number * AdultSurvival;
        itAdult->Development += DevRateAdult;
        ++itAdult;
      }
      else {
        itAdult->Number = itAdult->Number * AdultSurvival;
        eggLayersCohorts += itAdult->Number;
        OvipositingCohorts.push_back( *itAdult );
        itAdult = OviAdultCohorts.erase( itAdult );
      }
    }

    // create new ovi adult cohort based on all females who will ovipositiong today, reseting dev cycle
    if( newEggLayersCohorts + eggLayersCohorts > 0 ) {
      OviAdultCohorts.push_back( OviAdultCohort(1, newEggLayersCohorts + eggLayersCohorts, DevRateAdult, GetOvipositingFemaleAverageWeight()) );
    }

    // apply space spray to ovi adults
    for( std::vector<SpaceSpray*>::iterator itSs = SpaceSprays_.begin(); itSs != SpaceSprays_.end(); ++itSs ) {
      if( (*itSs)->IsDateScheduled(CurrentDate_) ) {
        SpaceSpray * ss = *itSs;

        for( OviAdultIterator itAdult = OviAdultCohorts.begin(); itAdult != OviAdultCohorts.end(); ) {
          double indoorSurvival = itAdult->Number * (1 - ss->GetIndoorMortality()) * (1 - _proportionAdultsOutdoor);
          double outdoorSurvival = itAdult->Number * (1 - ss->GetOutdoorMortality()) * _proportionAdultsOutdoor;
          itAdult->Number = indoorSurvival + outdoorSurvival;
          if( itAdult->Number == 0 ) {
            itAdult = OviAdultCohorts.erase(itAdult);
          }
          else {
            ++itAdult;
          }
        }
      }
    }

    // apply residual spray to ovi adults
    if( ResidualSprays_.size() > 0 ) {
      ResidualSpray * rs = ResidualSprays_.at(0);
      if( rs->GetSurvival(CurrentDate_) < 1 ) {
        double surfaceRatio = rs->GetTreatedInteriorProportion();
        double houseRatio = rs->GetTreatedHousesProportion();
        double survival = rs->GetSurvival(CurrentDate_);

        for( OviAdultIterator itAdult = OviAdultCohorts.begin(); itAdult != OviAdultCohorts.end(); ) {
          double IndoorSurviving = itAdult->Number * (1 - _proportionAdultsOutdoor) * surfaceRatio * houseRatio * survival;
          double OutdoorSurviving = itAdult->Number * _proportionAdultsOutdoor;
          itAdult->Number = IndoorSurviving + OutdoorSurviving;
          if( itAdult->Number == 0 ) {
            itAdult = OviAdultCohorts.erase(itAdult);
          }
          else {
            ++itAdult;
          }
        }
      }
    }


    // advance adult age distribution
    for( int Age = MaxAgeOviAdults - 1; Age >= 1; Age-- ) {
      MosqAgeDistr[Age + 1] = MosqAgeDistr[Age] * AdultSurvival;
    }
    MosqAgeDistr[1] = NewFemales;

    // apply space spray to age distribution
    for( std::vector<SpaceSpray*>::iterator itSs = SpaceSprays_.begin(); itSs != SpaceSprays_.end(); ++itSs ) {
      if( (*itSs)->IsDateScheduled(CurrentDate_) ) {
        SpaceSpray * ss = *itSs;
        for( int Age = MaxAgeOviAdults; Age >= 1; Age-- ) {
          double IndoorSurviving = MosqAgeDistr[Age] * (1 - ss->GetIndoorMortality()) * (1 - _proportionAdultsOutdoor);
          double OutdoorSurviving = MosqAgeDistr[Age] * (1 - ss->GetOutdoorMortality()) * _proportionAdultsOutdoor;
          MosqAgeDistr[Age] = IndoorSurviving + OutdoorSurviving;
        }
      }
    }

    // apply residual spray to mosquito age distr
    if( ResidualSprays_.size() > 0 ) {    
      ResidualSpray * rs = ResidualSprays_.at(0);
      if( rs->GetSurvival(CurrentDate_) < 1 ) {
        double surfaceRatio = rs->GetTreatedInteriorProportion();
        double houseRatio = rs->GetTreatedHousesProportion();
        double survival = rs->GetSurvival(CurrentDate_);
        for( int Age = MaxAgeOviAdults; Age >= 1; --Age ) {
          MosqAgeDistr[Age] = MosqAgeDistr[Age] * (1 - _proportionAdultsOutdoor) * surfaceRatio * houseRatio * survival;
        }
      }
    }


    // calculate proportion of double blood meals as a function of female wet weight
    // TODO: this should be per cohort
    double doubleBloodMealProp = CalculateDoubleBloodMealProportion();


    // calculate number of blood seeking females
    // note this is different than CS 1.0 that used host parameters to determine densities
    // CS 3.0 just outputs absolute number of females that are seeking blood meals
    // this does account for double blood meals, but not for "interrupted" feeds

    // a peculiarity in CS 1.0 is that survival against density as well as bites per hosts/humans/mammals
    // were all calculated before the current day's biters were updated.  This means that survival against density
    // as well as bites per hosts were using yesterday's counts for biters
    _totalBiters = _preOviBiters + _oviBiters;


    // calculate today's biters
    _preOviBiters = GetPreOviBiters( doubleBloodMealProp );
    _oviBiters = GetOviBiters( doubleBloodMealProp );



    // track wild male population - needed for sterile male releases.
    // survivals and treatments have already been applied to the female arrays.
    double percentFemale = this->_location->Biology_->Pupae->FemaleEmergence;
    double totalFemales = GetPreOviFemaleCount() + GetOviFemaleCount();
    TotalMales = (totalFemales / percentFemale) - totalFemales;


    // advance/update sterile males
    if( SterileMaleReleases_.size() > 0 ) {
      SterileMaleRelease * sm = SterileMaleReleases_.at(0);
      TotalSterileMales = TotalSterileMalesYesterday * AdultSurvival * sm->GetRatioMaleToFemaleSurvival();
      if( sm->IsDateScheduled(CurrentDate_) ) {
        TotalSterileMales = TotalSterileMales + sm->GetNumberReleased();
      }
    }


    // calculate container volume preference for oviposition
    double normTotal = 0;
    for( itCont = Containers_.begin(); itCont != Containers_.end(); ++itCont ) {
      double contPref = 0;
      if( !(*itCont)->IsDry() ) {
        contPref = (*itCont)->CalculateContPref(Day);
      }
      else {
        // container dry, no volume oviposition
        (*itCont)->ResetContPref();
      }
      normTotal = normTotal + contPref;
    }

    if( normTotal == 0 ) {    // TODO - this could be 0 if no container types have non excluded containers...
      // all containers are possibly dry - treat as if all are full
      // TODO - this is slightly akward.  If only one container is dry, it loses any share
      // of volume preference oviposition, which might make sense - if it is dry, would oviposition
      // occur?  However now that all containers are dry, the situation is treated as if none are dry.
      for( itCont = Containers_.begin(); itCont != Containers_.end(); ++itCont ) {
        double contPref = (*itCont)->CalculateContPref(Day);
        normTotal = normTotal + contPref;
      }
    }

    for( itCont = Containers_.begin(); itCont != Containers_.end(); ++itCont ) {
      if( normTotal == 0 ) {
        // there are no untreated and treated containers
        (*itCont)->ResetContPref();
      }
      else {
        (*itCont)->NormalizeContPref( normTotal );

      }
    }


    // determine level of input for new eggs
    for( itCont = Containers_.begin(); itCont != Containers_.end(); ++itCont ) {
      (*itCont)->CalculateEggInputLevel(Day);
    }


    // calculate sterile male effect on fecundity
    double sterileFactor = 1;
    if( SterileMaleReleases_.size() > 0 ) {
      SterileMaleRelease * sm = SterileMaleReleases_.at(0);
      if( (TotalSterileMales * sm->GetCompetitiveness()) + TotalMales <= 0 ) {
        sterileFactor = 1;
      }
      else {
        sterileFactor = 1 - ((TotalSterileMales * sm->GetCompetitiveness() * sm->GetSterilityRate()) / ((TotalSterileMales * sm->GetCompetitiveness()) + TotalMales));
      }
    }


    // calculate new egg amounts
    double newEggs = 0.0;
    double totalOvipositingFemales = newEggLayersCohorts + eggLayersCohorts;
    if( totalOvipositingFemales > 0 ) {
      newEggs = totalOvipositingFemales * _fecundityCoefficient * GetOvipositingFemaleAverageWeight() * sterileFactor;
    }


    // distribute new eggs among containers
    for( itCont = Containers_.begin(); itCont != Containers_.end(); ++itCont ) {
      (*itCont)->DistributeNewEggs( newEggs );
    }


    // prepare for next day
    TotalSterileMalesYesterday = TotalSterileMales;

    CalculateDailyTotals();

    // initialize container for next day
    for( itCont = Containers_.begin(); itCont != Containers_.end(); ++itCont ) {
      (*itCont)->EndDay();
    }

    UpdateOutput( CurrentDate_, NewFemaleWeight, DevRateAdult, newEggs );

  } // year completed

#ifdef _DEBUG
  // write log files for completed year
  _locationLog.WriteToDisk();
#endif

  // initialize container for next year
  for( itCont = Containers_.begin(); itCont != Containers_.end(); ++itCont ) {
    (*itCont)->EndYear();
  }
}



void
SimLocation::CalculateAdultTemperatureSurvival(void)
{
  const double & lowLethalThreshold = _adultTemperatureSurvival->LowLethalThreshold;
  const double & lowLethalSurvival = _adultTemperatureSurvival->LowLethalSurvival;

  const double & lowThreshold = _adultTemperatureSurvival->LowThreshold;
  const double & highThreshold = _adultTemperatureSurvival->HighThreshold;

  const double & highLethalThreshold = _adultTemperatureSurvival->HighLethalThreshold;
  const double & highLethalSurvival = _adultTemperatureSurvival->HighLethalSurvival;


  // vs. minimum temperature
  if( TemperatureMin[Day] <= lowLethalThreshold ) {
    AdultSurvivalTemperature = lowLethalSurvival;
  }
  else if( TemperatureMin[Day] >= lowThreshold ) {
    AdultSurvivalTemperature = 1.0;
  }
  else {
    double slope = (lowLethalSurvival - 1) / (lowLethalThreshold - lowThreshold);
    AdultSurvivalTemperature = 1 - ((lowThreshold - (TemperatureMin[Day])) * slope);
  }


  // vs. maximum temperature
  if( TemperatureMax[Day] >= highLethalThreshold ) {
    AdultSurvivalTemperature = AdultSurvivalTemperature * highLethalSurvival;
  }
  else if( TemperatureMax[Day] <= highThreshold ) {
    AdultSurvivalTemperature = AdultSurvivalTemperature * 1;
  }
  else {
    double slope = (1 - highLethalSurvival) / (highThreshold - highLethalThreshold);
    AdultSurvivalTemperature = AdultSurvivalTemperature * (1 + ((TemperatureMax[Day] - highThreshold) * slope));
  }
}



void
SimLocation::CalculateAdultSatDefSurvival(void)
{
  const double & lowThreshold = _adultSatDefSurvival->LowThreshold;
  const double & lowSurvival = _adultSatDefSurvival->LowSurvival;

  const double & highThreshold = _adultSatDefSurvival->HighThreshold;
  const double & highSurvival = _adultSatDefSurvival->HighSurvival;

  // adult survival vs saturation deficit
  if( SD[Day] <= lowThreshold ) {
    AdultSurvivalSatDef = lowSurvival;
  }
  else if( SD[Day] >= highThreshold ) {
    AdultSurvivalSatDef = highSurvival;
  }
  else {
    double slope = (lowSurvival - highSurvival) / (highThreshold - lowThreshold );
    AdultSurvivalSatDef = lowSurvival - ((SD[Day] - lowThreshold) * slope);
  }
}



double
SimLocation::CalculateDoubleBloodMealProportion(void)
{
  const double & lowWeight = _adultDoubleBloodMeals->LowWeightLimit;
  const double & lowWeightProportion = _adultDoubleBloodMeals->LowWeightRatio;
  
  const double & highWeight = _adultDoubleBloodMeals->HighWeightLimit;
  const double & highWeightProportion = _adultDoubleBloodMeals->HighWeightRatio;

  if( NewFemaleWeight <= lowWeight) {
    return lowWeightProportion;
  }
  else if( NewFemaleWeight >= highWeight ) {
    return highWeightProportion;
  }
  else {
    double slope = (lowWeightProportion - highWeightProportion) / (highWeight - lowWeight);
    return lowWeightProportion - ((NewFemaleWeight - lowWeight) * slope);
  }
}



void
SimLocation::ReadWeather( int year )
{
  // read specified year's worth of weather
  WeatherYear * wy = _location->Weather_->GetWeatherForYear( year );

  // adjust vector length for leap years
  int numDays = gregorian_calendar::is_leap_year( year ) ? 366 : 365;
  TemperatureMax = std::vector<double>( numDays+1, 0.0f );
  TemperatureMin = std::vector<double>( numDays+1, 0.0f );
  TemperatureAvg = std::vector<double>( numDays+1, 0.0f );
  Rain = std::vector<double>( numDays+1, 0.0f );
  RelHumid = std::vector<double>( numDays+1, 0.0f );
  SD = std::vector<double>( numDays+1, 0.0f );

  for( int i = 1; i <= numDays; i++ ) {
    WeatherDay * wd = wy->GetDay(i);
    TemperatureMax[i] = wd->MaxTemp_;
    TemperatureMin[i] = wd->MinTemp_;
    TemperatureAvg[i] = wd->AvgTemp_;
    SD[i] = wd->SatDef_;
    Rain[i] = wd->Precip_;
    RelHumid[i] = wd->RelHum_;
  }
}



void
SimLocation::CalculateDailyTotals(void)
{
  // container calculations (eggs, larvae, pupae)
  ContainerCollection::iterator itCont;
  for( itCont = Containers_.begin(); itCont != Containers_.end(); ++itCont ) {
    (*itCont)->CalcDailyTotals();

  }
}



void
SimLocation::UpdateOutput( date d, double adultWeight, double adultDev, double newEggs )
{
  // get day of year index
  int dayOfYear = d.day_of_year();

  // record location outputs for current date
  output::DailyLocationOutput dlo;
  dlo.Females = GetPreOviFemaleCount() + GetOviFemaleCount();
  dlo.Oviposition = newEggs;
  dlo.NewFemales = NewFemales;
  dlo.AverageWeight = GetFemaleAverageWeight();
  dlo.AdultDevelopment = adultDev;
  dlo.OverallSurvival = AdultSurvival;
  Output_->AddDailyLocationOutput( dlo, d );

#ifdef _DEBUG
  _locationLog << dayOfYear << dlo.Females << dlo.NewFemales
               << _totalBiters << 0 << _totalBiters << 0
               << TemperatureMax[dayOfYear] << TemperatureMin[dayOfYear] << Rain[dayOfYear]
               << RelHumid[dayOfYear] << SD[dayOfYear] << output::Log::eor;
#endif

  // record container outputs for current date
  ContainerCollection::iterator itCont;
  for( itCont = Containers_.begin(); itCont != Containers_.end(); ++itCont ) {
    Output_->AddDailyContainerOutput( (*itCont)->GetOutput(d), d, (*itCont)->Id );
  }
}



sim::output::CimsimOutput *
SimLocation::GetSimOutput(void)
{
  // TODO - this is dependent on a client calling GetSimOutput, does this need to be changed?
  Output_->InitialPreOviAdultCohorts = InitialPreOviAdultCohorts;
  Output_->InitialOviAdultCohorts = InitialOviAdultCohorts;

  _outputReleased = true;
  return Output_;
}



sim::output::PopData *
SimLocation::GeneratePopData(void)
{
  sim::output::PopData * pd = new output::PopData();

  pd->PreOviAdultCohorts = PreOviAdultCohorts;
  pd->OviAdultCohorts = OviAdultCohorts;

  pd->MosqAgeDistr = MosqAgeDistr;

  ContainerCollection::iterator itCont;
  for( itCont = Containers_.begin(); itCont != Containers_.end(); ++itCont ) {
    output::ContainerPopData * cpd = (*itCont)->GeneratePopData();
    pd->Containers_[cpd->Name] = cpd;
  }

  return pd;
}



bool
SimLocation::IsEndOfMonth( boost::gregorian::date d )
{
  return (d == d.end_of_month());
}



double
SimLocation::GetPreOviFemaleCount(void)
{
  double totalNumber = 0.0;

  for( PreOviAdultIterator itAdult = PreOviAdultCohorts.begin(); itAdult != PreOviAdultCohorts.end(); ++itAdult) {
    totalNumber += itAdult->Number;
  }

  return totalNumber;
}



double
SimLocation::GetOviFemaleCount(void)
{
  double totalNumber = 0.0;

  for( OviAdultIterator itAdult = OviAdultCohorts.begin(); itAdult != OviAdultCohorts.end(); ++itAdult) {
    totalNumber += itAdult->Number;
  }

  return totalNumber;
}


  
double
SimLocation::GetFemaleAverageWeight(void)
{
  // using new cohort classes, calculate true female mean weight for this location
  double totalWeight = 0.0;
  double totalNumber = 0.0;

  for( PreOviAdultIterator itAdult = PreOviAdultCohorts.begin(); itAdult != PreOviAdultCohorts.end(); ++itAdult) {
    totalNumber += itAdult->Number;
    totalWeight += itAdult->Weight * itAdult->Number;
  }

  for( OviAdultIterator itAdult = OviAdultCohorts.begin(); itAdult != OviAdultCohorts.end(); ++itAdult) {
    totalNumber += itAdult->Number;
    totalWeight += itAdult->Weight * itAdult->Number;
  }

  if( totalNumber == 0.0 ) {
    return 0.0;
  }
  else {
    return totalWeight / totalNumber;
  }
}



double
SimLocation::GetOvipositingFemaleAverageWeight(void)
{
  // CS 1.0 takes all females that oviposit on the current day
  // and sticks them into a new OviAdultCohort (with AdultWt however, which was in error),
  // we establish the same cohort (TODO: change?) but use the true average weight of
  // females contributing to new cohort
  double totalWeight = 0.0;
  double totalNumber = 0.0;

  for( AdultCohortCollection::iterator itAdult = OvipositingCohorts.begin(); itAdult != OvipositingCohorts.end(); ++itAdult) {
    totalNumber += itAdult->Number;
    totalWeight += itAdult->Weight * itAdult->Number;
  }

  if( totalNumber == 0.0 ) {
    return 0.0;
  }
  else {
    return totalWeight / totalNumber;
  }
}



double
SimLocation::GetPreOviBiters( double doubleProp )
{
  // pre ovi biters are defined as females that are 2 days old, as well as some
  // proportion of 3 day old females, based on double blood meal proportion
  double ageTwoCount = 0.0;
  double ageThreeCount = 0.0;

  for( PreOviAdultIterator itAdult = PreOviAdultCohorts.begin(); itAdult != PreOviAdultCohorts.end(); ++itAdult ) {
    if( itAdult->Age == 3 ) {
      ageThreeCount = itAdult->Number;
    }
    if( itAdult->Age == 2 ) {
      ageTwoCount = itAdult->Number;
    }
  }

  // TODO: calculate double prop based on actual cohort age 3, not new female weight
  return ageTwoCount + (ageThreeCount * doubleProp);
}



double
SimLocation::GetOviBiters( double doubleProp )
{
  // ovi biters are defined as ovi females on the same day they complete a cycle
  // as well as some proportion on the day after, based on double blood meal proportion
  // this translates to "age" one and two in the OviAdultCohorts
  double ageOneCount = 0.0;
  double ageTwoCount = 0.0;

  for( OviAdultIterator itAdult = OviAdultCohorts.begin(); itAdult != OviAdultCohorts.end(); ++itAdult ) {
    if( itAdult->Age == 2 ) {
      ageTwoCount = itAdult->Number;
    }
    if( itAdult->Age == 1 ) {
      ageOneCount = itAdult->Number;
    }
  }

  return ageOneCount + (ageTwoCount * doubleProp);
}
