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
  _startDate(startDate),
  _stopDate(stopDate),
  _output(new output::CimsimOutput()),
  _outputReleased(false),
  TotalSterileMalesYesterday(0),
  _adultAgeDistribution(std::vector<double>( MaxAgeOviAdults+1, 0 )),
  _preOviBiters(0),
  _oviBiters(0)
{
#ifdef _DEBUG
  // leave whatever seed has been in use until now
  //srand(1);
#else
  srand( time(NULL) );
#endif

  // initialize population/containers
  if( popData == NULL ) {
    _usingPop = false;

    _initialPreOviAdults = PreOviAdultCohortCollection();
    _initialOviAdults = OviAdultCohortCollection();

    // read containers
    std::vector<input::Container*>::const_iterator itCtnr;
    for( itCtnr = _location->Containers_.begin(); itCtnr != _location->Containers_.end(); itCtnr++ ) {
      AddContainer( *itCtnr );
    }
  }
  else {
    InitializePopulation( popData );
  }

  InitializeControls( location->Controls_ );
  InitializeBiology( location->Biology_ );
}



SimLocation::~SimLocation(void)
{
  std::vector<SimContainer*>::iterator itCont;
  for( itCont = _containers.begin(); itCont != _containers.end(); ++itCont ) {
    delete *itCont;
  }

  if( !_outputReleased ) {
    // still managing output data, delete
    delete _output;
  }
}



void
SimLocation::AddContainer( input::Container * container )
{
  // create a SimContainer from the input::Container optionally accounting for container cloning

  if( container->IsCloned_ ) {
    double cloneDensity = container->Density_ / container->NumberOfClones_;

    // create each clone
    for( int cloneId = 1; cloneId <= container->NumberOfClones_; cloneId++ ) {
      SimContainer * newContainer = new SimContainer( container, _location->Biology_ );
      newContainer->MakeClone( cloneId, container->NumberOfClones_, cloneDensity );
      _containers.push_back( newContainer );
    }
  }
  else {
    SimContainer * newContainer = new SimContainer( container, _location->Biology_ );
    _containers.push_back( newContainer );
  }
}



void SimLocation::AddPopContainer( input::Container * container, const sim::output::PopData * population )
{
  // create a SimContainer from the input::Container optionally accounting for container cloning
  // and using existing population data

  if( container->IsCloned_ ) {
    double cloneDensity = container->Density_ / container->NumberOfClones_;

    // create each clone with its correspond population data
    for( int cloneId = 1; cloneId <= container->NumberOfClones_; cloneId++ ) {
      output::ContainerPopData * cpd = population->GetClonedContainerData( container->Id_, cloneId );
      SimContainer * newContainer = new SimContainer( container, _location->Biology_, cpd );
      newContainer->MakeClone( cloneId, container->NumberOfClones_, cloneDensity );
      _containers.push_back( newContainer );
    }
  }
  else {
    output::ContainerPopData * cpd = population->GetContainerData( container->Id_ );
    SimContainer * newContainer = new SimContainer( container, _location->Biology_, cpd );
    _containers.push_back( newContainer );
  }
}



void
SimLocation::InitializePopulation( const sim::output::PopData * population )
{
  _usingPop = true;

  // initialize adults
  _preOviAdults = population->PreOviAdultCohorts;
  _oviAdults = population->OviAdultCohorts;
  _adultAgeDistribution = population->MosqAgeDistr;

  _nulliparousAdults = _preOviAdults;
  _parousAdults = _oviAdults;

  _initialPreOviAdults = _preOviAdults;
  _initialOviAdults = _oviAdults;

  // initialize immatures and containers
  std::vector<input::Container*>::const_iterator itCtnr;
  for( itCtnr = _location->Containers_.begin(); itCtnr != _location->Containers_.end(); itCtnr++ ) {
    AddPopContainer( *itCtnr, population );
  }
}



void
SimLocation::InitializeControls( input::ControlCollection controls )
{
  // read controls and initialize schedules
  _controls = std::vector<Control*>( _location->Controls_ );

  date_period wxAvailable = _location->Weather_->GetWeatherPeriod();
  date wxMinDate = wxAvailable.begin();
  date wxMaxDate = wxAvailable.end();

  std::vector<Control*>::iterator itCtrl;
  for( itCtrl = _controls.begin(); itCtrl != _controls.end(); ++itCtrl ) {
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
}



void
SimLocation::InitializeBiology( input::Biology * biology )
{
  _adultP25 = biology->Adult->Development->RO25;
  _adultDHA = biology->Adult->Development->DHA;
  _adultDHH = biology->Adult->Development->DHH;
  _adultTH2 = biology->Adult->Development->THALF;
  _adultSecondDevelopmentThreshold = biology->Adult->SecondDevelopmentThreshold;

  _adultNominalSurvival = biology->Adult->NominalSurvival;
  _adultTemperatureSurvival = biology->Adult->Temperature;
  _adultSatDefSurvival = biology->Adult->SaturationDeficit;

  _minimumOvipositionTemperature = biology->Adult->MinimumOvipositionTemperature;
  _fecundityCoefficient = biology->Adult->FecundityFactor;
  _proportionAdultsOutdoor = biology->Adult->ProportionOfAdultsRestingOutdoors;
  _interruptedFeedsPerMeal = biology->Adult->InterruptedFeedsPerMeal;
  _adultDoubleBloodMeals = biology->Adult->DoubleBloodMeal;

  _adultAgeDependentSurvival = biology->Adult->AgeDependentSurvival;  
}



void
SimLocation::RunSimulation(void)
{
  // initialize container for simulation
  ContainerCollection::iterator itCont;
  for( itCont = _containers.begin(); itCont != _containers.end(); ++itCont ) {
    (*itCont)->Initialize( _startDate );
  }

  // iterate through years
  for( Year = _startDate.year(); Year <= _stopDate.year(); Year++ ) {
    // read current year's weather
    ReadWeather(Year);

    // yearly initialization of container
    for( itCont = _containers.begin(); itCont != _containers.end(); ++itCont ) {
      (*itCont)->InitializeYear(Year);
    }

    // run simulation for a year or up to stop date
    DoYear();
    if( _currentDate > _stopDate ) {
      break;
    }
  }
  _output->SetPopData( GeneratePopData() );
}



void
SimLocation::DoYear(void)
{
  // simulate each day in this year
  ContainerCollection::iterator itCont;
  day_iterator itDay = day_iterator( date(Year,1,1) );
  int numDays = gregorian_calendar::is_leap_year( Year ) ? 366 : 365;
  for( Day = 1; Day <= numDays; ++Day, ++itDay) {

    _currentDate = *itDay;
    if( _currentDate > _stopDate ) {
      return;
    }

    for( itCont = _containers.begin(); itCont != _containers.end(); ++itCont ) {
      // current container
      SimContainer * c = *itCont;
      c->DoDay( _currentDate );

      // calculate water depth and temp
      c->CalculateWaterDepth( Rain[Day], RelHumid[Day] );
      c->CalculateWaterTemperature( TemperatureMin[Day], TemperatureAvg[Day], TemperatureMax[Day] );


      // calculate immature development rates
      c->CalculateDevelopmentRates(Day);


      // possibly initialize eggs on first day it not using PopData
      if( !_usingPop && _currentDate == _startDate ) {
        c->InitializeEggs();
      }


      // adjust container densities for nominal losses and gains
      if( IsEndOfMonth(_currentDate) ) {
        c->ApplyMonthlyDensityAdjustment();
      }

      // apply source reduction
      for( std::vector<SourceReduction*>::iterator itSr = SourceReductions_.begin(); itSr != SourceReductions_.end(); ++itSr ) {
        if( (*itSr)->IsDateScheduled( _currentDate ) ) {
          if( (*itSr)->IsTarget( c->Name ) ) {
            // for each source redution, if today is scheduled, and container is targetted, apply the reduction
            double rateOfReduction = (*itSr)->GetTargetParams(c->Name)->RateOfReduction;
            c->ApplySourceReduction( rateOfReduction );
          }
        }
      }

      // recover excluded containers
      if( IsEndOfMonth(_currentDate) ) {
        c->RecoverExcluded();
      }

      // apply oviposition exclusion
      for( std::vector<OvipositionExclusion*>::iterator itOe = OvipositionExclusions_.begin(); itOe != OvipositionExclusions_.end(); ++itOe ) {
        if( (*itOe)->IsDateScheduled( _currentDate ) ) {
          if( (*itOe)->IsTarget( c->Name ) ) {
            // for each oviposition exclusion, if today is scheduled, and container is targetted, apply the exclusion
            double rateOfExclusion = (*itOe)->GetTargetParams(c->Name)->RateOfExclusion;
            double rateOfRecovery = (*itOe)->GetTargetParams(c->Name)->RateOfRecovery;
            c->ApplyOvipositionExclusion( rateOfExclusion, rateOfRecovery );
          }
        }
      }

      // recover treated containers
      if( IsEndOfMonth(_currentDate) ) {
        c->RecoverTreated();
      }

      // for each larvicide
      for( std::vector<Larvicide*>::iterator itLi = Larvicides_.begin(); itLi != Larvicides_.end(); ++itLi ) {
        if( (*itLi)->IsDateScheduled( _currentDate ) ) {
          if( (*itLi)->IsTarget( c->Name ) ) {
            // for each larvicide, if today is scheduled and container is targetted, begin a new treatment
            c->BeginNewLarvicideTreatment( *itLi );
          }
        }
      }

      // apply egg destruction
      for( std::vector<EggDestruction*>::iterator itEd = EggDestructions_.begin(); itEd != EggDestructions_.end(); ++itEd ) {
        if( (*itEd)->IsDateScheduled( _currentDate ) ) {
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
      c->AdjustFood(_currentDate);
      c->CalculateTemperatureLarvalSurvival(Day);
      c->CalculateLarvicideLarvalSurvival(_currentDate);
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
    for( itCont = _containers.begin(); itCont != _containers.end(); ++itCont ) {
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


    // clear today's ovipositing cohort collection
    _ovipositingAdults.clear();

    // advance pre-oviposition adults
    double newEggLayersCohorts = 0.0;
    double firstTargetThreshold = 1.0 - (DevRateAdult / 2.0);
    for( PreOviAdultIterator itAdult = _preOviAdults.begin(); itAdult != _preOviAdults.end(); ) {
      if( itAdult->Development < firstTargetThreshold || TemperatureAvg[Day] <= _minimumOvipositionTemperature ) {
        itAdult->Age++;
        itAdult->Number = itAdult->Number * AdultSurvival;
        itAdult->Development += DevRateAdult;
        ++itAdult;
      }
      else {
        itAdult->Number = itAdult->Number * AdultSurvival;
        newEggLayersCohorts += itAdult->Number;
        _ovipositingAdults.push_back( *itAdult );
        itAdult = _preOviAdults.erase( itAdult );
      }
    }

    // establish newly emerged female cohort, since this occurs after above block, newly emerged females
    // are not subjected to adult survival - this makes sense since they were subjected to pupae survival
    if( NewFemales > 0 ) {
      _preOviAdults.push_back( PreOviAdultCohort(1, NewFemales, DevRateAdult, NewFemaleWeight) );
    }
    // they are however subjected to residual and space sprays from the following two code blocks


    // apply space spray to pre ovi adults
    for( std::vector<SpaceSpray*>::iterator itSs = SpaceSprays_.begin(); itSs != SpaceSprays_.end(); ++itSs ) {
      if( (*itSs)->IsDateScheduled(_currentDate) ) {
        SpaceSpray * ss = *itSs;

        for( PreOviAdultIterator itAdult = _preOviAdults.begin(); itAdult != _preOviAdults.end(); ) {
          double indoorSurvival = itAdult->Number * (1 - ss->GetIndoorMortality()) * (1 - _proportionAdultsOutdoor);
          double outdoorSurvival = itAdult->Number * (1 - ss->GetOutdoorMortality()) * _proportionAdultsOutdoor;
          itAdult->Number = indoorSurvival + outdoorSurvival;
          if( itAdult->Number == 0 ) {
            itAdult = _preOviAdults.erase(itAdult);
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
      if( rs->GetSurvival(_currentDate) < 1 ) {
        double surfaceRatio = rs->GetTreatedInteriorProportion();
        double houseRatio = rs->GetTreatedHousesProportion();
        double survival = rs->GetSurvival(_currentDate);

        for( PreOviAdultIterator itAdult = _preOviAdults.begin(); itAdult != _preOviAdults.end(); ) {
          double IndoorSurviving = itAdult->Number * (1 - _proportionAdultsOutdoor) * surfaceRatio * houseRatio * survival;
          double OutdoorSurviving = itAdult->Number * _proportionAdultsOutdoor;
          itAdult->Number = IndoorSurviving + OutdoorSurviving;
          if( itAdult->Number == 0 ) {
            itAdult = _preOviAdults.erase(itAdult);
          }
          else {
            ++itAdult;
          }
        }
      }
    }


    // advanced post oviposition adults
    double eggLayersCohorts = 0.0;
    double secondTargetThreshold = _adultSecondDevelopmentThreshold - (DevRateAdult / 2.0);
    for( OviAdultIterator itAdult = _oviAdults.begin(); itAdult != _oviAdults.end(); ) {
      if( itAdult->Development < secondTargetThreshold || TemperatureAvg[Day] <= _minimumOvipositionTemperature ) {
        itAdult->Age++;
        itAdult->Number = itAdult->Number * AdultSurvival;
        itAdult->Development += DevRateAdult;
        ++itAdult;
      }
      else {
        itAdult->Number = itAdult->Number * AdultSurvival;
        eggLayersCohorts += itAdult->Number;
        _ovipositingAdults.push_back( *itAdult );
        itAdult = _oviAdults.erase( itAdult );
      }
    }

    // create new ovi adult cohort based on all females who will ovipositiong today, reseting dev cycle and "age"
    if( newEggLayersCohorts + eggLayersCohorts > 0 ) {
      _oviAdults.push_back( OviAdultCohort(1, newEggLayersCohorts + eggLayersCohorts, DevRateAdult, GetOvipositingFemaleAverageWeight()) );
    }

    // apply space spray to ovi adults
    for( std::vector<SpaceSpray*>::iterator itSs = SpaceSprays_.begin(); itSs != SpaceSprays_.end(); ++itSs ) {
      if( (*itSs)->IsDateScheduled(_currentDate) ) {
        SpaceSpray * ss = *itSs;

        for( OviAdultIterator itAdult = _oviAdults.begin(); itAdult != _oviAdults.end(); ) {
          double indoorSurvival = itAdult->Number * (1 - ss->GetIndoorMortality()) * (1 - _proportionAdultsOutdoor);
          double outdoorSurvival = itAdult->Number * (1 - ss->GetOutdoorMortality()) * _proportionAdultsOutdoor;
          itAdult->Number = indoorSurvival + outdoorSurvival;
          if( itAdult->Number == 0 ) {
            itAdult = _oviAdults.erase(itAdult);
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
      if( rs->GetSurvival(_currentDate) < 1 ) {
        double surfaceRatio = rs->GetTreatedInteriorProportion();
        double houseRatio = rs->GetTreatedHousesProportion();
        double survival = rs->GetSurvival(_currentDate);

        for( OviAdultIterator itAdult = _oviAdults.begin(); itAdult != _oviAdults.end(); ) {
          double IndoorSurviving = itAdult->Number * (1 - _proportionAdultsOutdoor) * surfaceRatio * houseRatio * survival;
          double OutdoorSurviving = itAdult->Number * _proportionAdultsOutdoor;
          itAdult->Number = IndoorSurviving + OutdoorSurviving;
          if( itAdult->Number == 0 ) {
            itAdult = _oviAdults.erase(itAdult);
          }
          else {
            ++itAdult;
          }
        }
      }
    }


    // advance adult age distribution
    for( int Age = MaxAgeOviAdults - 1; Age >= 1; Age-- ) {
      _adultAgeDistribution[Age + 1] = _adultAgeDistribution[Age] * AdultSurvival;
    }
    _adultAgeDistribution[1] = NewFemales;

    // apply space spray to age distribution
    for( std::vector<SpaceSpray*>::iterator itSs = SpaceSprays_.begin(); itSs != SpaceSprays_.end(); ++itSs ) {
      if( (*itSs)->IsDateScheduled(_currentDate) ) {
        SpaceSpray * ss = *itSs;
        for( int Age = MaxAgeOviAdults; Age >= 1; Age-- ) {
          double IndoorSurviving = _adultAgeDistribution[Age] * (1 - ss->GetIndoorMortality()) * (1 - _proportionAdultsOutdoor);
          double OutdoorSurviving = _adultAgeDistribution[Age] * (1 - ss->GetOutdoorMortality()) * _proportionAdultsOutdoor;
          _adultAgeDistribution[Age] = IndoorSurviving + OutdoorSurviving;
        }
      }
    }

    // apply residual spray to mosquito age distr
    if( ResidualSprays_.size() > 0 ) {    
      ResidualSpray * rs = ResidualSprays_.at(0);
      if( rs->GetSurvival(_currentDate) < 1 ) {
        double surfaceRatio = rs->GetTreatedInteriorProportion();
        double houseRatio = rs->GetTreatedHousesProportion();
        double survival = rs->GetSurvival(_currentDate);
        for( int Age = MaxAgeOviAdults; Age >= 1; --Age ) {
          _adultAgeDistribution[Age] = _adultAgeDistribution[Age] * (1 - _proportionAdultsOutdoor) * surfaceRatio * houseRatio * survival;
        }
      }
    }


    // BEGIN NEW ADULT CODE

    // prepare to track today's ovipositing nulliparous and parous cohorts
    _ovipositingNulliparousAdults.clear();
    _ovipositingParousAdults.clear();

    // calculate survival before applying age dependence
    double nonAgeDependentSurvival = AdultSurvivalTemperature * AdultSurvivalSatDef;

    // advance nulliparous cohorts
    for( PreOviAdultIterator itAdult = _nulliparousAdults.begin(); itAdult != _nulliparousAdults.end(); ) {
      // TODO: should we use the age at beginning of the day or the age at the end of the day?
      itAdult->Age++;
      double survival = nonAgeDependentSurvival * CalculateAdultAgeDependentSurvival( itAdult->Age );
      itAdult->Number = itAdult->Number * survival;

      // check if development and temperature allow for oviposition
      if( itAdult->Development < firstTargetThreshold || TemperatureAvg[Day] <= _minimumOvipositionTemperature ) {
        itAdult->Development += DevRateAdult;
        itAdult->Ovipositing = false;
        ++itAdult;
      }
      else {
        // development will be set later
        itAdult->Ovipositing = true;
        _ovipositingNulliparousAdults.push_back( *itAdult );
        itAdult = _nulliparousAdults.erase( itAdult );
      }
    }
    // establish newly emerged female cohort, which is only subject to space and residual sprays
    if( NewFemales > 0 ) {
      _nulliparousAdults.push_back( PreOviAdultCohort(1, NewFemales, DevRateAdult, NewFemaleWeight) );
    }


    // apply space spray to nulliparous adults
    for( std::vector<SpaceSpray*>::iterator itSs = SpaceSprays_.begin(); itSs != SpaceSprays_.end(); ++itSs ) {
      if( (*itSs)->IsDateScheduled(_currentDate) ) {
        SpaceSpray * ss = *itSs;

        for( PreOviAdultIterator itAdult = _nulliparousAdults.begin(); itAdult != _nulliparousAdults.end(); ) {
          double indoorSurvival = itAdult->Number * (1 - ss->GetIndoorMortality()) * (1 - _proportionAdultsOutdoor);
          double outdoorSurvival = itAdult->Number * (1 - ss->GetOutdoorMortality()) * _proportionAdultsOutdoor;
          itAdult->Number = indoorSurvival + outdoorSurvival;
          if( itAdult->Number == 0 ) {
            itAdult = _nulliparousAdults.erase(itAdult);
          }
          else {
            ++itAdult;
          }
        }
      }
    }

    // apply residual spray to nulliparous adults
    if( ResidualSprays_.size() > 0 ) {
      ResidualSpray * rs = ResidualSprays_.at(0);
      if( rs->GetSurvival(_currentDate) < 1 ) {
        double surfaceRatio = rs->GetTreatedInteriorProportion();
        double houseRatio = rs->GetTreatedHousesProportion();
        double survival = rs->GetSurvival(_currentDate);

        for( PreOviAdultIterator itAdult = _nulliparousAdults.begin(); itAdult != _nulliparousAdults.end(); ) {
          double IndoorSurviving = itAdult->Number * (1 - _proportionAdultsOutdoor) * surfaceRatio * houseRatio * survival;
          double OutdoorSurviving = itAdult->Number * _proportionAdultsOutdoor;
          itAdult->Number = IndoorSurviving + OutdoorSurviving;
          if( itAdult->Number == 0 ) {
            itAdult = _nulliparousAdults.erase(itAdult);
          }
          else {
            ++itAdult;
          }
        }
      }
    }

    // advance parous cohorts
    for( OviAdultIterator itAdult = _parousAdults.begin(); itAdult != _parousAdults.end(); ++itAdult ) {
      itAdult->Age++;
      itAdult->OvipositionAge++;
      double survival = nonAgeDependentSurvival * CalculateAdultAgeDependentSurvival( itAdult->Age );
      itAdult->Number = itAdult->Number * survival;

      // check if devleopment and temperature allow for subsequent oviposition
      if( itAdult->Development < secondTargetThreshold || TemperatureAvg[Day] <= _minimumOvipositionTemperature ) {
        itAdult->Development += DevRateAdult;
        itAdult->Ovipositing = false;
      }
      else {
        // TODO: emulate the age and development reset on oviposition for now
        itAdult->Ovipositing = true;
        itAdult->Development = DevRateAdult;
        itAdult->OvipositionAge = 1;
        _ovipositingParousAdults.push_back( *itAdult );
      }
    }
    // advance ovipositing nulliparous cohorts to parous stage
    for( PreOviAdultIterator itAdult = _ovipositingNulliparousAdults.begin(); itAdult != _ovipositingNulliparousAdults.end(); ++itAdult ) {
      // TODO: emulate development reset for now
      OviAdultCohort newOviCohort;
      newOviCohort.Age = itAdult->Age;
      newOviCohort.Number = itAdult->Number;
      newOviCohort.Development = DevRateAdult;
      newOviCohort.Weight = itAdult->Weight;
      newOviCohort.Ovipositing = true;
      newOviCohort.OvipositionAge = 1;

      _parousAdults.push_back( newOviCohort );
    }


    // apply space spray to ovi adults
    for( std::vector<SpaceSpray*>::iterator itSs = SpaceSprays_.begin(); itSs != SpaceSprays_.end(); ++itSs ) {
      if( (*itSs)->IsDateScheduled(_currentDate) ) {
        SpaceSpray * ss = *itSs;

        for( OviAdultIterator itAdult = _parousAdults.begin(); itAdult != _parousAdults.end(); ) {
          double indoorSurvival = itAdult->Number * (1 - ss->GetIndoorMortality()) * (1 - _proportionAdultsOutdoor);
          double outdoorSurvival = itAdult->Number * (1 - ss->GetOutdoorMortality()) * _proportionAdultsOutdoor;
          itAdult->Number = indoorSurvival + outdoorSurvival;
          if( itAdult->Number == 0 ) {
            itAdult = _parousAdults.erase(itAdult);
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
      if( rs->GetSurvival(_currentDate) < 1 ) {
        double surfaceRatio = rs->GetTreatedInteriorProportion();
        double houseRatio = rs->GetTreatedHousesProportion();
        double survival = rs->GetSurvival(_currentDate);

        for( OviAdultIterator itAdult = _parousAdults.begin(); itAdult != _parousAdults.end(); ) {
          double IndoorSurviving = itAdult->Number * (1 - _proportionAdultsOutdoor) * surfaceRatio * houseRatio * survival;
          double OutdoorSurviving = itAdult->Number * _proportionAdultsOutdoor;
          itAdult->Number = IndoorSurviving + OutdoorSurviving;
          if( itAdult->Number == 0 ) {
            itAdult = _parousAdults.erase(itAdult);
          }
          else {
            ++itAdult;
          }
        }
      }
    }
    // END NEW ADULT CODE


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
    _preOviBiters = GetNulliparousBiters( doubleBloodMealProp );
    _oviBiters = GetParousBiters( doubleBloodMealProp );


    // track wild male population - needed for sterile male releases.
    // survivals and treatments have already been applied to the female arrays.
    double percentFemale = this->_location->Biology_->Pupae->FemaleEmergence;
    double totalFemales = GetNulliparousCount() + GetParousCount();
    TotalMales = (totalFemales / percentFemale) - totalFemales;


    // advance/update sterile males
    if( SterileMaleReleases_.size() > 0 ) {
      SterileMaleRelease * sm = SterileMaleReleases_.at(0);
      TotalSterileMales = TotalSterileMalesYesterday * AdultSurvival * sm->GetRatioMaleToFemaleSurvival();
      if( sm->IsDateScheduled(_currentDate) ) {
        TotalSterileMales = TotalSterileMales + sm->GetNumberReleased();
      }
    }


    // calculate container volume preference for oviposition
    double normTotal = 0;
    for( itCont = _containers.begin(); itCont != _containers.end(); ++itCont ) {
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
      for( itCont = _containers.begin(); itCont != _containers.end(); ++itCont ) {
        double contPref = (*itCont)->CalculateContPref(Day);
        normTotal = normTotal + contPref;
      }
    }

    for( itCont = _containers.begin(); itCont != _containers.end(); ++itCont ) {
      if( normTotal == 0 ) {
        // there are no untreated and treated containers
        (*itCont)->ResetContPref();
      }
      else {
        (*itCont)->NormalizeContPref( normTotal );
      }
    }


    // determine level of input for new eggs
    for( itCont = _containers.begin(); itCont != _containers.end(); ++itCont ) {
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


    // calculate count/weight of ovipositing females
    std::pair<double,double> oviTotals = GetOvipositingTotals();
    double totalOvipositingFemales = oviTotals.first;
    double ovipositingAverageWeight = oviTotals.second;


    // calculate new egg totals
    double newEggs = 0.0;
    if( totalOvipositingFemales > 0 ) {
      newEggs = totalOvipositingFemales * _fecundityCoefficient * ovipositingAverageWeight * sterileFactor;
    }


    // distribute new eggs among containers
    for( itCont = _containers.begin(); itCont != _containers.end(); ++itCont ) {
      (*itCont)->DistributeNewEggs( newEggs );
    }


    // prepare for next day
    TotalSterileMalesYesterday = TotalSterileMales;

    CalculateDailyTotals();

    // initialize container for next day
    for( itCont = _containers.begin(); itCont != _containers.end(); ++itCont ) {
      (*itCont)->EndDay();
    }

    UpdateOutput( _currentDate, NewFemaleWeight, DevRateAdult, newEggs );

  } // year completed


  // initialize container for next year
  for( itCont = _containers.begin(); itCont != _containers.end(); ++itCont ) {
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
SimLocation::CalculateAdultAgeDependentSurvival( int age )
{
  const double & youngSurvival = _adultAgeDependentSurvival->YoungSurvival;
  const double & oldSurvival = _adultAgeDependentSurvival->OldSurvival;
  const double & cutOffAge = _adultAgeDependentSurvival->CutoffAge;

  if( age <= cutOffAge ) {
    return youngSurvival;
  }
  else {
    return oldSurvival;
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
  for( itCont = _containers.begin(); itCont != _containers.end(); ++itCont ) {
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
  dlo.Females = GetNulliparousCount() + GetParousCount();
  dlo.Oviposition = newEggs;
  dlo.NewFemales = NewFemales;
  dlo.AverageWeight = GetFemaleAverageWeight();
  dlo.AdultDevelopment = adultDev;
  dlo.OverallSurvival = AdultSurvival;
  _output->AddDailyLocationOutput( dlo, d );

  // record container outputs for current date
  ContainerCollection::iterator itCont;
  for( itCont = _containers.begin(); itCont != _containers.end(); ++itCont ) {
    _output->AddDailyContainerOutput( (*itCont)->GetOutput(d), d, (*itCont)->Id );
  }
}



sim::output::CimsimOutput *
SimLocation::GetSimOutput(void)
{
  _output->InitialPreOviAdultCohorts = _initialPreOviAdults;
  _output->InitialOviAdultCohorts = _initialOviAdults;

  _outputReleased = true;
  return _output;
}



sim::output::PopData *
SimLocation::GeneratePopData(void)
{
  sim::output::PopData * pd = new output::PopData();

  pd->PreOviAdultCohorts = _preOviAdults;
  pd->OviAdultCohorts = _oviAdults;
  pd->MosqAgeDistr = _adultAgeDistribution;

  ContainerCollection::iterator itCont;
  for( itCont = _containers.begin(); itCont != _containers.end(); ++itCont ) {
    output::ContainerPopData * cpd = (*itCont)->GeneratePopData();
    pd->AddContainerData( cpd );
  }

  return pd;
}



bool
SimLocation::IsEndOfMonth( boost::gregorian::date d )
{
  return (d == d.end_of_month());
}



double
SimLocation::GetFemaleAverageWeight(void)
{
  // using new cohort classes, calculate true female mean weight for this location
  double totalWeight = 0.0;
  double totalNumber = 0.0;

  for( PreOviAdultIterator itAdult = _nulliparousAdults.begin(); itAdult != _nulliparousAdults.end(); ++itAdult) {
    totalNumber += itAdult->Number;
    totalWeight += itAdult->Weight * itAdult->Number;
  }

  for( OviAdultIterator itAdult = _parousAdults.begin(); itAdult != _parousAdults.end(); ++itAdult) {
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

  for( AdultCohortCollection::iterator itAdult = _ovipositingAdults.begin(); itAdult != _ovipositingAdults.end(); ++itAdult) {
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
SimLocation::GetNulliparousCount(void)
{
  double totalNumber = 0.0;

  for( PreOviAdultIterator itAdult = _nulliparousAdults.begin(); itAdult != _nulliparousAdults.end(); ++itAdult) {
    totalNumber += itAdult->Number;
  }

  return totalNumber;
}



double
SimLocation::GetParousCount(void)
{
  double totalNumber = 0.0;

  for( OviAdultIterator itAdult = _parousAdults.begin(); itAdult != _parousAdults.end(); ++itAdult) {
    totalNumber += itAdult->Number;
  }

  return totalNumber;
}



std::pair<double,double>
SimLocation::GetOvipositingTotals(void)
{
  double totalCount = 0.0;
  double totalWeight = 0.0;

  for( PreOviAdultCohortCollection::iterator itAdult = _ovipositingNulliparousAdults.begin(); itAdult != _ovipositingNulliparousAdults.end(); ++itAdult) {
    totalCount += itAdult->Number;
    totalWeight += itAdult->Number * itAdult->Weight;
  }

  for( OviAdultCohortCollection::iterator itAdult = _ovipositingParousAdults.begin(); itAdult != _ovipositingParousAdults.end(); ++itAdult) {
    totalCount += itAdult->Number;
    totalWeight += itAdult->Number * itAdult->Weight;
  }

  std::pair<double,double> countAndWeight;
  if( totalCount == 0 ) {
    countAndWeight.first = 0.0;
    countAndWeight.second = 0.0;
  }
  else {
    countAndWeight.first = totalCount;
    countAndWeight.second = totalWeight / totalCount;
  }

  return countAndWeight;
}


double
SimLocation::GetNulliparousBiters( double doubleProp )
{
  // pre ovi biters are defined as females that are 2 days old, as well as some
  // proportion of 3 day old females, based on double blood meal proportion
  double ageTwoCount = 0.0;
  double ageThreeCount = 0.0;

  for( PreOviAdultIterator itAdult = _nulliparousAdults.begin(); itAdult != _nulliparousAdults.end(); ++itAdult ) {
    if( itAdult->Age == 3 ) {
      ageThreeCount = itAdult->Number;
    }
    if( itAdult->Age == 2 ) {
      ageTwoCount = itAdult->Number;
    }
  }

  return ageTwoCount + (ageThreeCount * doubleProp);
}



double
SimLocation::GetParousBiters( double doubleProp )
{
  // ovi biters are defined as ovi females on the same day they complete a cycle
  // as well as some proportion on the day after, based on double blood meal proportion
  // this translates to "age" one and two in the _oviAdults
  //
  // notice the accumulation compared to above, this is because with new age dependent changes
  // each cohort is kept separate, and hence oviposition ages 1 and 2 occur more than once
  // in the parous collection
  double ageOneCount = 0.0;
  double ageTwoCount = 0.0;

  for( OviAdultIterator itAdult = _parousAdults.begin(); itAdult != _parousAdults.end(); ++itAdult ) {
    if( itAdult->OvipositionAge == 2 ) {
      ageTwoCount += itAdult->Number;
    }
    if( itAdult->OvipositionAge == 1 ) {
      ageOneCount += itAdult->Number;
    }
  }

  return ageOneCount + (ageTwoCount * doubleProp);
}
