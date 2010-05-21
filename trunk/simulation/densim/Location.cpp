#include "stdafx.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <sstream>

#include <boost/random/uniform_int.hpp>

#include "Constants.h"
#include "Humans.h"
#include "Location.h"

using namespace sim::ds;



Location::Location( input::Location const * location, sim::output::MosData * mosData, bool doDiskOutput )
: _location( location ),
  _mosData( mosData ),
  _doDiskOutput( doDiskOutput ),
  _mt19937( boost::mt19937(static_cast<boost::uint32_t>(time(0))) ),
  _rng( boost::variate_generator<boost::mt19937, boost::uniform_01<>>( _mt19937, boost::uniform_01<>() ) ),

  Virus(std::vector<VirusDesc>( 4+1 )),
  _eipAdjustmentFactor(std::vector<double>( 4+1, 0 )),
  _eipDevelopmentRate(std::vector<double>( 4+1, 0 )),

  _infectedNulliparous(std::vector<MosquitoCollection>( 4+1 )),
  _infectedParous(std::vector<MosquitoCollection>( 4+1 )),
  _infectedBites(std::vector<double>( 4+1, 0 )),
  _infectedNulliparousBites(std::vector<double>( 4+1, 0 )),
  _infectedNulliparousDoubleBites(std::vector<double>( 4+1, 0 )),
  _infectedParousBites(std::vector<double>( 4+1, 0 )),
  _infectedParousDoubleBites(std::vector<double>( 4+1, 0 )),
  _newlyInfectiveNulliparous(std::vector<MosquitoCollection>( 4+1 )),
  _newlyInfectiveParous(std::vector<MosquitoCollection>( 4+1 )),
  _infectives(std::vector<MosquitoCollection>( 4+1 )),
  _infectiveBites(std::vector<double>( 4+1, 0 )),
  _infectiveMosquitoesBySerotype(std::vector<double>( 4+1, 0 )),
  _humanInoculationsBySerotype(std::vector<int>( 4+1, 0 ))
{
  // initialize random number generator
#ifdef _DEBUG
  _mt19937 = boost::mt19937(0);
  _rng = boost::variate_generator<boost::mt19937, boost::uniform_01<>>( _mt19937, boost::uniform_01<>() );
#else
  // change once done with densim issues
  //_mt19937 = boost::mt19937(time(0));
  _mt19937 = boost::mt19937(0);
  _rng = boost::variate_generator<boost::mt19937, boost::uniform_01<>>( _mt19937, boost::uniform_01<>() );
#endif

  // human population and demographics
  _humanPopulation = new HumanPopulation( _location, _rng );
  this->HumHostDensity = _location->Demographics_->HumanHostDensity;


  // virology parameters
  this->Virus[1].Viremia = _location->Virology_->Dengue1_.Viremia_;
  this->Virus[1].Incub = _location->Virology_->Dengue1_.IncubationDuration_;
  this->Virus[1].Durat = _location->Virology_->Dengue1_.ViremicDuration_;

  this->Virus[2].Viremia = _location->Virology_->Dengue2_.Viremia_;
  this->Virus[2].Incub = _location->Virology_->Dengue2_.IncubationDuration_;
  this->Virus[2].Durat = _location->Virology_->Dengue2_.ViremicDuration_;

  this->Virus[3].Viremia = _location->Virology_->Dengue3_.Viremia_;
  this->Virus[3].Incub = _location->Virology_->Dengue3_.IncubationDuration_;
  this->Virus[3].Durat = _location->Virology_->Dengue3_.ViremicDuration_;

  this->Virus[4].Viremia = _location->Virology_->Dengue4_.Viremia_;
  this->Virus[4].Incub = _location->Virology_->Dengue4_.IncubationDuration_;
  this->Virus[4].Durat = _location->Virology_->Dengue4_.ViremicDuration_;


  // initialize parameters
  InitializeBiology( location->Biology_ );


  // transmission parameters
  this->HumToMosLTiter = _location->Virology_->HumanToMosquitoInfection_.LowTiterSetPoint_;
  this->HumToMosLInf = _location->Virology_->HumanToMosquitoInfection_.LowTiterInfection_;
  this->HumToMosHTiter = _location->Virology_->HumanToMosquitoInfection_.HighTiterSetPoint_;
  this->HumToMosHInf = _location->Virology_->HumanToMosquitoInfection_.HighTiterInfection_;

  this->EipLTiter = _location->Virology_->Eip_.EipTiterModification_.LowSetPoint_;
  this->EipLFactor = _location->Virology_->Eip_.EipTiterModification_.LowFactor_;
  this->EipHTiter = _location->Virology_->Eip_.EipTiterModification_.HighSetPoint_;
  this->EipHFactor = _location->Virology_->Eip_.EipTiterModification_.HighFactor_;

  this->StochTransNum = _location->Virology_->MosquitoCountForStochasticity;
  this->MosqToHumProb = _location->Virology_->MosquitoToHumanNominalProbabilityOfInfection_;

  this->EnzKinDR = _location->Virology_->Eip_.Development_.RO25;
  this->EnzKinEA = _location->Virology_->Eip_.Development_.DHA;
  this->EnzKinEI = _location->Virology_->Eip_.Development_.DHH;
  this->EnzKinTI = _location->Virology_->Eip_.Development_.THALF;


  // initialize mosquito population from cimsim
  double initialArea = _humanPopulation->GetInitialPopulationSize() / HumHostDensity;
  for( sim::cs::PreOviAdultCohortCollection::iterator itAdult = _mosData->PreOviAdultCohorts.begin();
       itAdult != _mosData->PreOviAdultCohorts.end(); ++itAdult ) {
    AdultCohort cohort = AdultCohort( *itAdult );
    cohort.Number *= initialArea;
    if( cohort.Age == 2 ) {
      cohort.SeekingBloodMeal = true;
    }
    if( cohort.Age == 3 ) {
      cohort.SeekingDoubleBloodMeal = true;
    }
    _susceptibleNulliparous.push_back( cohort );
  }
  for( sim::cs::OviAdultCohortCollection::iterator itAdult = _mosData->OviAdultCohorts.begin();
       itAdult != _mosData->OviAdultCohorts.end(); ++itAdult ) {
    AdultCohort cohort = AdultCohort( *itAdult );
    cohort.Number *= initialArea;
    if( cohort.Age == 1 ) {
      cohort.Ovipositing = true;
      cohort.SeekingBloodMeal = true;
    }
    if( cohort.Age == 2 ) {
      cohort.SeekingDoubleBloodMeal = true;
    }
    _susceptibleParous.push_back( cohort );
  }


  // get default start/stop from available weather data
  boost::gregorian::date_period wxAvailable = _location->Weather_->GetWeatherPeriod();
  _startDate = wxAvailable.begin();
  _stopDate = wxAvailable.end();


  // initialize infection schedules
  _location->InfectionIntroduction_->Dengue1_->Schedule_->CalculateSchedule( _startDate, _stopDate );
  _location->InfectionIntroduction_->Dengue2_->Schedule_->CalculateSchedule( _startDate, _stopDate );
  _location->InfectionIntroduction_->Dengue3_->Schedule_->CalculateSchedule( _startDate, _stopDate );
  _location->InfectionIntroduction_->Dengue4_->Schedule_->CalculateSchedule( _startDate, _stopDate );

  InitializeDiskLogs();
}



Location::~Location(void)
{
  if( _doDiskOutput ) {
    _locationLog->Write();
    delete _locationLog;
  }

  delete _humanPopulation;
}



void
Location::InitializeBiology( input::Biology * biology )
{
  // development and survival
  _firstDevelopmentThreshold = 1.0;
  _secondDevelopmentThreshold = biology->Adult->SecondDevelopmentThreshold;
  _minimumOvipositionTemperature = biology->Adult->MinimumOvipositionTemperature;
  _ageDependentSurvival = biology->Adult->AgeDependentSurvival;  


  // feeding and double blood meals
  _doubleBloodMeals = biology->Adult->DoubleBloodMeal;
  _proportionOfFeedsOnHumans = biology->Adult->ProportionOfFeedsOnHumans;
  _interruptedFeedsPerMeal = biology->Adult->InterruptedFeedsPerMeal;
  _proportionOfInterruptedFeedsOnDifferentHost = biology->Adult->ProportionOfInterruptedFeedsOnDifferentHost;
}



void
Location::InitializeDiskLogs(void)
{
  if( _doDiskOutput ) {
    std::vector<std::string> headers = std::vector<std::string>();
    headers.push_back( "Population Size" );
    headers.push_back( "Female Mosquitoes in Area" );
    headers.push_back( "Potentially Infective Bites" );
    headers.push_back( "Susceptible Nulliparous" );
    headers.push_back( "Susceptible Nulliparous Ovipositing" );
    headers.push_back( "Susceptible Parous" );
    headers.push_back( "Infected Nulliparous" );
    headers.push_back( "Infected Parous" );
    headers.push_back( "Infectives" );

    _locationLog = new output::Log( "DENSiM Location Data.csv", headers );
  }
}



void
Location::Start(void)
{
  RunSimulation();  
}



void
Location::Start( boost::gregorian::date startDate, boost::gregorian::date stopDate )
{
  _startDate = startDate;
  _stopDate = stopDate;

  _densimOutput = new sim::output::DensimOutput( _startDate, _stopDate );

  Start();
}



void
Location::RunSimulation(void)
{
  CalculateEipFactors();

  // seed mosData to start
  boost::gregorian::date lastDayCurrentYear = boost::gregorian::date( _startDate.year(), 12, 31 );
  _dailyMosData = _mosData->GetMosData( lastDayCurrentYear );

  for( _currentDate = _startDate; _currentDate <= _stopDate; _currentDate = _currentDate + boost::gregorian::days(1) ) {
    // pull year and day of year values from currentDate for reference
    _year = _currentDate.year();
    _day = _currentDate.day_of_year();
    
    // read today's average air temperature
    _averageAirTemperature = _location->Weather_->GetWeatherForYear(_currentDate.year())->GetDay(_currentDate.day_of_year())->AvgTemp_;

    // save yesterday's mosData and read today's
    _yesterdayMosData = _dailyMosData;
    _dailyMosData = _mosData->GetMosData( _currentDate );

    // apply deaths, births, and aging to humans
    _humanPopulation->DoDailyDeaths();
    _humanPopulation->DoDailyBirths();
    _humanPopulation->AgePopulation();

    // possibly introduce infection
    if( _location->InfectionIntroduction_->Dengue1_->Schedule_->IsDateScheduled( _currentDate ) ||
        _location->InfectionIntroduction_->Dengue2_->Schedule_->IsDateScheduled( _currentDate ) ||
        _location->InfectionIntroduction_->Dengue3_->Schedule_->IsDateScheduled( _currentDate ) ||
        _location->InfectionIntroduction_->Dengue4_->Schedule_->IsDateScheduled( _currentDate ) )
    {
      IntroduceInfectives();
    }

    // purge maternal antibodies
    _humanPopulation->PurgeMaternalAntibodies();

    // calculate daily eip development rate
    for( int k = 1; k <=4; ++k ) {
      _eipDevelopmentRate[k] = EIPEnzKin( _averageAirTemperature + 273.15f ) / _eipAdjustmentFactor[k];
    }

    // advance mosquitoes
    MosquitoLifeCycle();

    // calculate transmission
    HumanToMosquitoTransmission();
    MosquitoToHumanTransmission();

    // tabulate and output
    _humanPopulation->RankPopulation();
    _humanPopulation->PurgeHfDeaths();
    SaveDailyOutput();
  }

  // save initial and final demographic data
  _densimOutput->SetInitialData( _humanPopulation->GetInitialAgeDistribution(), _humanPopulation->GetInitialSeroDistribution() );
  _densimOutput->SetFinalData( _humanPopulation->GetAgeDistribution(), _humanPopulation->GetBirthsByClass(),
                               _humanPopulation->GetDeathsByClass(), _humanPopulation->GetSeroDistribution() );
}



void
Location::CalculateEipFactors(void)
{
  // calculate EIP by titer
  for( int i = 1; i <= 4; ++i ) {
    if( Virus[i].Viremia < EipLTiter ) {
      _eipAdjustmentFactor[i] = EipLFactor;
    }
    else if( Virus[i].Viremia > EipHTiter ) {
      _eipAdjustmentFactor[i] = EipHFactor;
    }
    else {
      double Slope = (EipLFactor - EipHFactor) / (EipHTiter - EipLTiter);
      _eipAdjustmentFactor[i] = EipLFactor - (Virus[i].Viremia - EipLTiter) * Slope;
    }
  }
}



void
Location::IntroduceInfectives(void)
{
  // introduce infected mosquitoes (which will become infective on the same day)
  for( int serotype = 1; serotype <= 4; ++serotype ) {
    input::SerotypeIntroduction * serotypeIntro = _location->InfectionIntroduction_->GetSerotype(serotype);
    if( serotypeIntro->Schedule_->IsDateScheduled( _currentDate ) && serotypeIntro->Mosquitoes_ > 0 ) {
      AdultCohort newCohort = AdultCohort( 1, serotypeIntro->Mosquitoes_, 1.1, _dailyMosData.NewFemaleWeight );
      newCohort.Infected = true;
      newCohort.Eip = 1.1;
      newCohort.Serotype = serotype;
      _infectedParous[serotype].push_back( newCohort );
    }
  }

  // introduce infected human
  for( int serotype = 1; serotype <= 4; ++serotype ) {
    input::SerotypeIntroduction * serotypeIntro = _location->InfectionIntroduction_->GetSerotype(serotype);
    if( serotypeIntro->Schedule_->IsDateScheduled( _currentDate ) && serotypeIntro->Humans_ > 0 ) {
      for( int i = 1; i <= serotypeIntro->Humans_; ++i ) {
        _humanPopulation->IntroduceInfectedHuman( serotype );
      }
    }
  }
}



double
Location::EIPEnzKin( double temp )
{
  double TempExpr1 = (EnzKinEA / GasCoef) * ((1 / (float) 298) - (1 / temp));
  double TempExpr2 = (EnzKinEI / GasCoef) * ((1 / EnzKinTI) - (1 / temp));

  if( TempExpr1 < -100 ) {
    TempExpr1 = -100;
  }
  else if( TempExpr1 > 150 ) {
    TempExpr1 = 150;
  }

  if( TempExpr2 < -100 ) {
    TempExpr2 = -100;
  }
  else if( TempExpr2 > 150 ) {
    TempExpr2 = 150;
  }

  double Numerator = EnzKinDR * (temp / 298) * exp(TempExpr1);
  double Denominator = 1 + exp(TempExpr2);
  return (Numerator / Denominator) * 24;
}



void
Location::MosquitoLifeCycle(void)
{
  // advance cohorts in each of the five primary collections
  AdvanceSusceptibleNulliparous();
  AdvanceSusceptibleParous();
  AdvanceInfectedNulliparous();
  AdvanceInfectedParous();
  AdvanceInfectives();


  // count bites
  _totalBites = _susceptibleNulliparousBites + _susceptibleParousBites;
  for( int iSerotype = 1; iSerotype <=4; ++iSerotype ) {
    _totalBites += _infectedBites[iSerotype] + _infectiveBites[iSerotype];
  }


  // count each of the five primary mosquitoes collections
  _totalSusceptibleNulliparous = GetTotalMosquitoes( _susceptibleNulliparous );
  _totalSusceptibleParous = GetTotalMosquitoes( _susceptibleParous );
  _totalInfectedNulliparous = GetTotalMosquitoes( _infectedNulliparous );
  _totalInfectedParous = GetTotalMosquitoes( _infectedParous );

  _totalInfectiveMosquitoes = 0;
  for( int iSerotype = 1; iSerotype <= 4; ++iSerotype ) {
    _infectiveMosquitoesBySerotype[iSerotype] = GetTotalMosquitoes( _infectives[iSerotype] );
    _totalInfectiveMosquitoes += _infectiveMosquitoesBySerotype[iSerotype];
  }


  // count all mosquitoes
  _totalMosquitoes = _totalSusceptibleNulliparous
                     + _totalSusceptibleParous
                     + _totalInfectedNulliparous
                     + _totalInfectedParous
                     + _totalInfectiveMosquitoes;
}



void
Location::AdvanceSusceptibleNulliparous(void)
{
  // clear susceptible nulliparous bite count and collections
  _susceptibleNulliparousOvipositing.clear();
  _susceptibleNulliparousBites = 0;
  _susceptibleNulliparousBiters.clear();


  // advance each susceptible nulliparous cohort
  for( MosquitoIterator itMosq = _susceptibleNulliparous.begin(); itMosq != _susceptibleNulliparous.end(); ) {
    // advance in age and apply survival
    itMosq->Age++;
    itMosq->Number *= _dailyMosData.OverallSurvival;

    // TODO include temperature check
    if( itMosq->Development <= 1 ) {
      // not done developing
      itMosq->Development += _dailyMosData.AdultDevelopment;
      SetNulliparousBloodMealStatus( *itMosq );
      ++itMosq;
    }
    else {
      // finished developing, move to ovipositing collection
      itMosq->Ovipositing = true;
      _susceptibleNulliparousOvipositing.push_back( *itMosq );
      itMosq = _susceptibleNulliparous.erase( itMosq );
    }
  }


  // create new nulliparous cohort from cimsim
  if( _dailyMosData.NewFemales > 0 ) {
    AdultCohort newCohort = AdultCohort( 1, _dailyMosData.NewFemales, _dailyMosData.AdultDevelopment, _dailyMosData.NewFemaleWeight );

    // adjust cohort count for simulation size since cimsim reports per hectare counts
    int numberOfHumans = _humanPopulation->GetPopulationSize();
    newCohort.Number *= numberOfHumans / HumHostDensity;

    _susceptibleNulliparous.push_back( newCohort );
  }


  // accumulate cohorts seeking blood meals
  for( MosquitoIterator itMosq = _susceptibleNulliparous.begin(); itMosq != _susceptibleNulliparous.end(); ++itMosq ) {
    if( itMosq->SeekingBloodMeal ) {
      _susceptibleNulliparousBiters.push_back( &*itMosq );
      _susceptibleNulliparousBites += itMosq->Number;
    }
    if( itMosq->SeekingDoubleBloodMeal ) {
      _susceptibleNulliparousBiters.push_back( &*itMosq );
      _susceptibleNulliparousBites += itMosq->Number * CalculateDoubleBloodMealProportion( itMosq->Weight );
    }
  }
}



void
Location::AdvanceSusceptibleParous(void)
{
  // clear susceptible parous bite count and collections
  _susceptibleParousBites = 0;
  _susceptibleParousBiters.clear();


  // advance each susceptible parous cohort
  for( MosquitoIterator itMosq = _susceptibleParous.begin(); itMosq != _susceptibleParous.end(); ++itMosq ) {
    // advance in age and apply survival
    itMosq->Age++;
    itMosq->Number *= _dailyMosData.OverallSurvival;

    if( itMosq->Development <= .58 ) {
      itMosq->Development += _dailyMosData.AdultDevelopment;
      SetParousBloodMealStatus( *itMosq );
    }
    else {
      // ovipositing
      itMosq->Development = _dailyMosData.AdultDevelopment;
      itMosq->Ovipositing = true;
      itMosq->SeekingBloodMeal = true;
      itMosq->SeekingDoubleBloodMeal = false;
    }
  }


  // move each susceptible nulliparous ovipositing cohort into the susceptible parous cohort collection
  if( _susceptibleNulliparousOvipositing.size()  > 0 ) {
    for( MosquitoIterator itMosq = _susceptibleNulliparousOvipositing.begin(); itMosq != _susceptibleNulliparousOvipositing.end(); ++itMosq ) {
      itMosq->Development = _dailyMosData.AdultDevelopment;
      itMosq->Ovipositing = true;
      itMosq->SeekingBloodMeal = true;
      itMosq->SeekingDoubleBloodMeal = false;
      _susceptibleParous.push_back( *itMosq );
    }
  }


  // accumulate cohorts seeking blood meals
  for( MosquitoIterator itMosq = _susceptibleParous.begin(); itMosq != _susceptibleParous.end(); ++itMosq ) {
    if( itMosq->SeekingBloodMeal ) {
      _susceptibleParousBiters.push_back( &*itMosq );
      _susceptibleParousBites += itMosq->Number;
    }
    if( itMosq->SeekingDoubleBloodMeal ) {
      _susceptibleParousBiters.push_back( &*itMosq );
      _susceptibleParousBites += itMosq->Number * CalculateDoubleBloodMealProportion( itMosq->Weight );
    }
  }
}



void
Location::AdvanceInfectedNulliparous(void)
{
  _infectedBites = std::vector<double>( 4+1, 0 );
  _newlyInfectiveNulliparous = std::vector<MosquitoCollection>( 4+1 );
  _newlyInfectiveParous = std::vector<MosquitoCollection>( 4+1 );


  for( int iSerotype = 1; iSerotype <= 4; ++iSerotype ) {
    // some proportion of yesterday's infected nulliparous biters were calculated as seeking another blood meal today
    // also track that count into a per serotype infected count, irregardless of nulli/parous
    _infectedBites[iSerotype] += _infectedNulliparousDoubleBites[iSerotype];
    _infectedNulliparousBites[iSerotype] = _infectedNulliparousDoubleBites[iSerotype];
    _infectedNulliparousDoubleBites[iSerotype] = 0;

    for( MosquitoIterator itMosq = _infectedNulliparous[iSerotype].begin(); itMosq != _infectedNulliparous[iSerotype].end(); ) {
      // calculate true development threshold since these nulliparous cohrots do not advance into
      // parous stage upon ovipositing for first time
      double developmentThreshold;
      double developmentYesterday = itMosq->Development - _yesterdayMosData.AdultDevelopment;
      if( developmentYesterday < 1 ) {
        // development yesterday was less than 1.0, the threshold for the first gonotrophic cycle
        // then the threshold today is still 1.0 since cohort has not finished cycle
        developmentThreshold = 1.0;
      }
      else {
        int numCyclesCompleted = 1 + INT((developmentYesterday - 1) / .58);
        developmentThreshold = 1 + (numCyclesCompleted * .58);
      }

      // advance in age and apply survival
      itMosq->Age++;
      itMosq->Number *= _dailyMosData.OverallSurvival;

      if( itMosq->Eip > 1.0 && itMosq->Development > developmentThreshold ) {
        // mosquito finished development and EIP
        // apply survival and transfer into newly infective nulliparous collection
        _newlyInfectiveNulliparous[iSerotype].push_back( *itMosq );
        itMosq = _infectedNulliparous[iSerotype].erase( itMosq );
      }
      else {
        // not finished with eip but not neccesarily not finished development
        // apply survival, accumulate development, and accumulate eip
        itMosq->Development += _dailyMosData.AdultDevelopment;
        itMosq->Eip += _eipDevelopmentRate[iSerotype];

        // finished development, this isn't a transfer rather a count of infected
        if( (itMosq->Development - _dailyMosData.AdultDevelopment) > developmentThreshold ) {
          _infectedBites[iSerotype] += itMosq->Number;
          _infectedNulliparousBites[iSerotype] += itMosq->Number;
          _infectedNulliparousDoubleBites[iSerotype] += itMosq->Number * CalculateDoubleBloodMealProportion( itMosq->Weight );
        }
        ++itMosq;
      }
    }
  }
}



void
Location::AdvanceInfectedParous(void)
{
  // Advance infected - From old Mosquitoes - Second and successive Gonotrophic Cycles
  // TODO - Last position in the array does not accumumlate
  for( int iSerotype = 1; iSerotype <= 4; ++iSerotype ) {
    _infectedBites[iSerotype]  += _infectedParousDoubleBites[iSerotype];
    _infectedParousBites[iSerotype] = _infectedParousDoubleBites[iSerotype];
    _infectedParousDoubleBites[iSerotype] = 0;

    for( MosquitoIterator itMosq = _infectedParous[iSerotype].begin(); itMosq != _infectedParous[iSerotype].end(); ) {
      itMosq->Age++;
      itMosq->Number *= _dailyMosData.OverallSurvival;
      if( itMosq->Eip > 1 && itMosq->Development > .58 ) {
        // finished eip and development, transfer to newly infective parous collection
        _newlyInfectiveParous[iSerotype].push_back( *itMosq );
        itMosq = _infectedParous[iSerotype].erase( itMosq );
      }
      else {
        // not finished eip, but potentially having finished another gonotropic cycle
        if( itMosq->Development > .58 ) {
          // finished a gonotropic cycle
          _infectedBites[iSerotype] += itMosq->Number;
          _infectedParousBites[iSerotype] += itMosq->Number;
          _infectedParousDoubleBites[iSerotype] += itMosq->Number * CalculateDoubleBloodMealProportion( itMosq->Weight );

          // TODO - why is development simply set here?
          // this means if a cohort is just shy of developing today, with development = .57
          // the next day they are starting with only today's calculated development, and not the accumulation
          // where they would potentially finish a cycle
          itMosq->Development = _dailyMosData.AdultDevelopment;
        }
        else {
          // not finished with current gonotropic cycle
          itMosq->Development += _dailyMosData.AdultDevelopment;
        }
        itMosq->Eip += _eipDevelopmentRate[iSerotype];
        ++itMosq;
      }
    }
  }
}



void
Location::AdvanceInfectives(void)
{
  _infectiveBites = std::vector<double>( 4+1, 0 );


  for( int iSerotype = 1; iSerotype <= 4; ++iSerotype ) {
    for( MosquitoIterator itMosq = _infectives[iSerotype].begin(); itMosq != _infectives[iSerotype].end(); ++itMosq ) {
      // advance in age and apply survival
      itMosq->Age++;
      itMosq->Number *= _dailyMosData.OverallSurvival;

      if( itMosq->Development <= .58 ) {
        // not yet completed current gonotrophic cycle
        itMosq->Development += _dailyMosData.AdultDevelopment;
        SetParousBloodMealStatus( *itMosq );
      }
      else {
        // finish current gonotropic cycle
        itMosq->Development = _dailyMosData.AdultDevelopment;
        itMosq->Ovipositing = true;
        itMosq->SeekingBloodMeal = true;
        itMosq->SeekingDoubleBloodMeal = false;
      }
    }


    // newly infective nulliparous
    for( MosquitoIterator itMosq = _newlyInfectiveNulliparous[iSerotype].begin(); itMosq != _newlyInfectiveNulliparous[iSerotype].end(); ++itMosq ) {
      AdultCohort newInfective = *itMosq;
      newInfective.Ovipositing = true;
      newInfective.SeekingBloodMeal = true;
      newInfective.SeekingDoubleBloodMeal = false;
      _infectives[iSerotype].push_back( newInfective );
    }


    // newly infective parous
    for( MosquitoIterator itMosq = _newlyInfectiveParous[iSerotype].begin(); itMosq != _newlyInfectiveParous[iSerotype].end(); ++itMosq ) {
      AdultCohort newInfective = *itMosq;
      newInfective.Ovipositing = true;
      newInfective.SeekingBloodMeal = true;
      newInfective.SeekingDoubleBloodMeal = false;
      _infectives[iSerotype].push_back( newInfective );
    }


    // track infective biting
    for( MosquitoIterator itMosq = _infectives[iSerotype].begin(); itMosq != _infectives[iSerotype].end(); ++itMosq ) {
      if( itMosq->SeekingBloodMeal ) {
        _infectiveBites[iSerotype] += itMosq->Number;
      }
      if( itMosq->SeekingDoubleBloodMeal ) {
        _infectiveBites[iSerotype] += itMosq->Number * CalculateDoubleBloodMealProportion( itMosq->Weight );
      }
    }
  }
}



void
Location::HumanToMosquitoTransmission(void)
{
  // handle dead population gracefully
  int numberOfHumans = _humanPopulation->GetPopulationSize();
  if( numberOfHumans == 0 ) {
    _bitesPerPerson = 0;
    return;
  }


  // calcualte bites per person taking into account biting parameters
  _bitesPerPerson = (_susceptibleNulliparousBites + _susceptibleParousBites) * _proportionOfFeedsOnHumans;
  _bitesPerPerson += _bitesPerPerson * (_interruptedFeedsPerMeal - 1) * _proportionOfInterruptedFeedsOnDifferentHost;
  _bitesPerPerson /= numberOfHumans;


  // randomly calculate new mosquito infections for four serotypes
  std::vector<int> seroTypesCompleted;
  // loop until all four sero types are processed
  while(true) {
    int i = INT( (4 - 1 + 1) * _rng() + 1 );
    std::vector<int>::iterator findResult;
    findResult = std::find( seroTypesCompleted.begin(), seroTypesCompleted.end(), i );
    if( findResult == seroTypesCompleted.end() ) {
      // serotype "i" has not been processed yet
      InoculateMosquitoes( i );
      seroTypesCompleted.push_back( i );
    }
    if( seroTypesCompleted.size() == 4 ) {
      // all 4 serotypes completed
      break;
    }
  }
}



void
Location::InoculateMosquitoes( int iType )
{
  // actual number of new infected mosq. (differs due to/if stochastic routines enabled)
  int NewDlyMosqInoc;

  // calculate probability of infection and  estimate newly inoculated mosquitoes
  // Viremia is in scientific notation and Titers are in logs
  double ProbInf = 0;
  if( log(Virus[iType].Viremia) / log(10.0) <= HumToMosLTiter ) {
    ProbInf = HumToMosLInf;
  }
  else if( log(Virus[iType].Viremia) / log(10.0) >= HumToMosHTiter ) {
    ProbInf = HumToMosHInf;
  }
  else {
    if( (HumToMosHTiter - HumToMosLTiter) == 0 ) {
      throw; // STOP
    }
    double Slope = (HumToMosHInf - HumToMosLInf) / (HumToMosHTiter - HumToMosLTiter);
    ProbInf = HumToMosHInf - ((HumToMosHTiter - (log(Virus[iType].Viremia) / log(10.0f))) * Slope);
  }

  double numInoculations = _humanPopulation->GetInfectiveBySerotype(iType) * _bitesPerPerson * ProbInf;
  
  // discrete
  if( numInoculations > StochTransNum ) {
    NewDlyMosqInoc = CINT(numInoculations);
  }
  // stochastic
  else if( numInoculations > 0 ) {
    // stochastic
    double num = _rng();
    double SumOfProb = 0;
    int r;
    for( r = 0; r <= 150; ++r ) {
      double rfact = Factorial(r);
      if( rfact == 0 ) {
        break; // STOP
      }
      SumOfProb = SumOfProb + ( (pow(numInoculations,r) * exp(-numInoculations)) / rfact);
      if( SumOfProb > num ) {
        break;  // exit for
      }
    }
    NewDlyMosqInoc = r;
  }
  else {
    NewDlyMosqInoc = 0;
  }


  // divide any new infections between parous and nulliparous susceptibles
  if( NewDlyMosqInoc > 0 ) {
    double parousProportion = _susceptibleParousBites / (_susceptibleParousBites + _susceptibleNulliparousBites);
    int numParousInfections = CINT( parousProportion * NewDlyMosqInoc );
    int numNulliparousInfections = NewDlyMosqInoc - numParousInfections;

    if( numParousInfections > 0 ) {
      InfectMosquitoes( iType, numParousInfections, _susceptibleParousBiters, _susceptibleParous, _infectedParous );
    }

    if( numNulliparousInfections > 0 ) {
      InfectMosquitoes( iType, numNulliparousInfections, _susceptibleNulliparousBiters, _susceptibleNulliparous, _infectedNulliparous );
    }
  }
}



void
Location::InfectMosquitoes( int serotype, double numInfections, std::vector<AdultCohort*> & bitingCollection, MosquitoCollection & susceptibleCollection, std::vector<MosquitoCollection> & infectedCollection )
{
  boost::uniform_int<> indices( 0, static_cast<int>(bitingCollection.size())-1 );

  while( bitingCollection.size() != 0 ) {
    // create index generator
    boost::variate_generator< boost::mt19937&, boost::uniform_int<> > selectIndex( _mt19937, indices);

    // randomly select a biting cohort ...
    int index = selectIndex();
    AdultCohort * bitingCohort = bitingCollection[index];
    // ... that will contribute to a new infected cohort with all the same state but Number
    int age = bitingCohort->Age;
    double development = bitingCohort->Development;
    double weight = bitingCohort->Weight;
    bool ovipositing = bitingCohort->Ovipositing;
    bool seekingBloodMeal = bitingCohort->SeekingBloodMeal;
    bool seekingDoubleBloodMeal = bitingCohort->SeekingDoubleBloodMeal;


    // first calculate mosquito availability
    double availableMosq = 0.0;
    if( bitingCohort->SeekingBloodMeal ) {
      // if cohort is seeking its first blood meal, all are biting
      availableMosq = bitingCohort->Number;
    }
    else if( bitingCohort->SeekingDoubleBloodMeal ) {
      // if cohort is seeking its double blood meal, only a proportion are biting
      availableMosq = bitingCohort->Number * CalculateDoubleBloodMealProportion( bitingCohort->Weight );
    }
    else {
      // exception, if cohort is not seeking blood meal or double blood meal it should not be in bitingCollection
      throw;
    }


    // next calculate mosquito infections
    double infectedMosq = 0.0;
    if( numInfections < availableMosq ) {
      // all infections will be used on available mosquitoes
      bitingCohort->Number -= numInfections;
      infectedMosq = numInfections;
      numInfections = 0;
    }
    else {
      // all available mosquitoes are infected, subtract from remaining infections
      infectedMosq = availableMosq;
      numInfections -= infectedMosq;

      if( availableMosq == bitingCohort->Number ) {
        // entire cohort is infected cohort, remove biting cohort from its susceptible collection
        susceptibleCollection.remove( *bitingCohort );
      }
      else {
        bitingCohort->Number -= availableMosq;
      }
    }

    // create new infected cohort and add to serotype specific collection
    AdultCohort infectedCohort = AdultCohort( age, infectedMosq, development, weight );
    infectedCohort.Ovipositing = ovipositing;
    infectedCohort.SeekingBloodMeal = seekingBloodMeal;
    infectedCohort.SeekingDoubleBloodMeal = seekingDoubleBloodMeal;
    infectedCohort.Infected = true;
    infectedCohort.Serotype = serotype;
    infectedCohort.Eip = _eipDevelopmentRate[serotype];
    infectedCollection[serotype].push_back( infectedCohort );

    if( numInfections <= 0 ) {
      break;
    }

    // remove this biting cohort from further selection and update indices for next generator
    bitingCollection.erase( bitingCollection.begin() + index );
    indices = boost::uniform_int<>( 0, static_cast<int>(bitingCollection.size())-1 );
  }
}



void
Location::MosquitoToHumanTransmission(void)
{
  // clear daily human inoculation counts
  _humanInoculations = 0;
  _humanInoculationsBySerotype = std::vector<int>( 4+1, 0 );

  // calculate per serotype inoculation counts while flagging serotypes with available inoculations
  std::vector<int> availableSerotypes;
  for( int i = 1; i <= 4; ++i ) {
    int inoculations = CalculateHumanInoculations(i);
    _humanInoculations += inoculations;
    _humanInoculationsBySerotype[i] = inoculations;

    if( inoculations > 0 ) {
      availableSerotypes.push_back( i );
    }
  }
  // simple case where no inoculations occur
  if( _humanInoculations == 0 ) {
    return;
  }


  // now distribute bites...
  std::vector<int> distributedBitesBySerotype( 4+1, 0 );

  // randomly until until all bites are distributed
  boost::uniform_int<> indices( 0, static_cast<int>(availableSerotypes.size())-1 );
  for( int i = 0; i < _humanInoculations; ++i ) {
    // select random serotype
    boost::variate_generator< boost::mt19937&, boost::uniform_int<> > selectIndex( _mt19937, indices);
    int index = selectIndex();
    int serotype = availableSerotypes[index];

    // inoculate human with selected serotype
    _humanPopulation->InoculateRandomHuman( serotype );

    distributedBitesBySerotype[serotype]++;
    if( distributedBitesBySerotype[serotype] == _humanInoculationsBySerotype[serotype] ) {
      // all bites for this serotype have been distributed, remove from available collection
      availableSerotypes.erase( availableSerotypes.begin() + index );
      if( availableSerotypes.size() == 0 ) {
        break;
      }
      indices = boost::uniform_int<>( 0, static_cast<int>(availableSerotypes.size())-1 );
    }
  }

}



int
Location::CalculateHumanInoculations( int serotype )
{
  // first calculate a floating point value based off bites
  double inoculationEstimate = _infectiveBites[serotype] * _proportionOfFeedsOnHumans;
  inoculationEstimate += (_infectiveBites[serotype] * _proportionOfFeedsOnHumans) * (_interruptedFeedsPerMeal - 1) * _proportionOfInterruptedFeedsOnDifferentHost;
  inoculationEstimate *= MosqToHumProb;

  // then change into a discrete value
  int numInoculations = 0;
  if( inoculationEstimate > StochTransNum ) {
    // rouding
    numInoculations = CINT( inoculationEstimate );
  }
  else if( inoculationEstimate > 0 ) {
    // stochasticity
    double num = _rng();
    double SumOfProb = 0;
    int r;
    for( r = 0; r <= 150; ++r ) {
      double rfact = Factorial(r);
      SumOfProb = SumOfProb + ((pow(inoculationEstimate,r) * exp(-inoculationEstimate)) / rfact);
      if( SumOfProb > num ) {
        break;
      }
    }
    numInoculations = r;
  }
  else {
    numInoculations = 0;
  }
  
  return numInoculations;
}



void
Location::SaveDailyOutput(void)
{
  output::DensimOutput::DailyLocationOutput dlo;

  dlo.Incubate1 = _humanPopulation->GetIncubatingBySerotype( 1 );
  dlo.Incubate2 = _humanPopulation->GetIncubatingBySerotype( 2 );
  dlo.Incubate3 = _humanPopulation->GetIncubatingBySerotype( 3 );
  dlo.Incubate4 = _humanPopulation->GetIncubatingBySerotype( 4 );

  dlo.Viremic1 = _humanPopulation->GetInfectiveBySerotype( 1 );
  dlo.Viremic2 = _humanPopulation->GetInfectiveBySerotype( 2 );
  dlo.Viremic3 = _humanPopulation->GetInfectiveBySerotype( 3 );
  dlo.Viremic4 = _humanPopulation->GetInfectiveBySerotype( 4 );

  dlo.MosqTotal = _totalMosquitoes;
  for( int i = 1; i <= 4; ++i ) {
    dlo.MosqInfvTotal[i] = _infectiveMosquitoesBySerotype[i];
    dlo.NewHumCases[i] = _humanPopulation->GetNewInfectiveBySerotype( i );
  }
  dlo.InfvBites = _humanInoculations;
  for( int i = 1; i <= 4; ++i ) {
    dlo.EIPDevRate[i] = _eipDevelopmentRate[i];
  }
  dlo.NumHumans = _humanPopulation->GetPopulationSize();

  HumanPopulation::ClassSpecificSeroprevalence css = _humanPopulation->GetClassSpecificSeroprevalence();
  for( int i = 1; i <= 23; ++i ) {
    for( int j = 1; j <= 4; ++j ) {
      dlo.SerPos[i][j] = css[i][j];
    }
  }

  HumanPopulation::DailySequentialInfections dsi = _humanPopulation->GetDailySequentialInfections();
  dlo.SeqInfVals.F1T2 = dsi[D1][D2];
  dlo.SeqInfVals.F1T3 = dsi[D1][D3];
  dlo.SeqInfVals.F1T4 = dsi[D1][D4];
  dlo.SeqInfVals.F2T1 = dsi[D2][D1];
  dlo.SeqInfVals.F2T3 = dsi[D2][D3];
  dlo.SeqInfVals.F2T4 = dsi[D2][D4];
  dlo.SeqInfVals.F3T1 = dsi[D3][D1];
  dlo.SeqInfVals.F3T2 = dsi[D3][D2];
  dlo.SeqInfVals.F3T4 = dsi[D3][D4];
  dlo.SeqInfVals.F4T1 = dsi[D4][D1];
  dlo.SeqInfVals.F4T2 = dsi[D4][D2];
  dlo.SeqInfVals.F4T3 = dsi[D4][D3];
  dlo.SeqInfVals.FMT1 = dsi[Maternal][D1];
  dlo.SeqInfVals.FMT2 = dsi[Maternal][D2];
  dlo.SeqInfVals.FMT3 = dsi[Maternal][D3];
  dlo.SeqInfVals.FMT4 = dsi[Maternal][D4];

  _densimOutput->AddDailyLocationOutput( dlo, _currentDate );

  if( _doDiskOutput ) {
    _locationLog->AddData( _humanPopulation->GetPopulationSize() );
    _locationLog->AddData( _totalMosquitoes );
    _locationLog->AddData( _humanInoculations );
    _locationLog->AddData( _totalSusceptibleNulliparous );
    _locationLog->AddData( GetTotalMosquitoes( _susceptibleNulliparousOvipositing ) );
    _locationLog->AddData( _totalSusceptibleParous );
    _locationLog->AddData( _totalInfectedNulliparous );
    _locationLog->AddData( _totalInfectedParous );
    _locationLog->AddData( _totalInfectiveMosquitoes );
  }
}



double
Location::Factorial( int n )
{
  int result = 1;
  for( int i = n; i > 0; --i ) {
    result = result * i;
  }
  return static_cast<double>( result );
}



sim::output::DensimOutput *
Location::GetDensimOutput(void)
{
  return _densimOutput;
}



double
Location::GetTotalMosquitoes( MosquitoCollection & collection )
{
  double totalNumber = 0.0;

  for( MosquitoIterator itMosq = collection.begin(); itMosq != collection.end(); ++itMosq ) {
    totalNumber += itMosq->Number;
  }

  return totalNumber;
}



double
Location::GetTotalMosquitoes( std::vector<MosquitoCollection> & collections )
{
  double totalNumber = 0.0;

  for( std::vector<MosquitoCollection>::iterator itCollection = collections.begin(); itCollection != collections.end(); ++itCollection ) {
    MosquitoCollection & collection = *itCollection;

    for( MosquitoIterator itMosq = collection.begin(); itMosq != collection.end(); ++itMosq ) {
      totalNumber += itMosq->Number;
    }
  }

  return totalNumber;
}



double
Location::CalculateDoubleBloodMealProportion( double weight )
{
  static const double & lowWeight = _doubleBloodMeals->LowWeightLimit;
  static const double & lowWeightProportion = _doubleBloodMeals->LowWeightRatio;

  static const double & highWeight = _doubleBloodMeals->HighWeightLimit;
  static const double & highWeightProportion = _doubleBloodMeals->HighWeightRatio;

  if( weight <= lowWeight) {
    return lowWeightProportion;
  }
  else if( weight >= highWeight ) {
    return highWeightProportion;
  }
  else {
    double slope = (lowWeightProportion - highWeightProportion) / (highWeight - lowWeight);
    double DMealProp = lowWeightProportion - ((weight - lowWeight) * slope);
    return DMealProp;
  }
}



// emulate DS 1.0 CINT() which does banker's rounding
int
sim::ds::CINT( double value )
{
  double absoluteValue = std::abs( value );
  int sign = (value == 0) ? 0 : ( value < 0 ? -1 : 1 );
  int floorValue = static_cast<int>( std::floor( absoluteValue ) );
  int ceilingValue = static_cast<int>( std::ceil( absoluteValue ) );

  if( absoluteValue - floorValue < 0.5f ) {
    // round down
    return floorValue * sign;
  }
  else if( absoluteValue - floorValue > 0.5f ) {
    // round up
    return ceilingValue * sign;
  }
  else {
    // round to closest even integer
    if( floorValue % 2 == 1 ) {
      // floor is odd, round up to even ceiling
      return ceilingValue * sign;
    }
    else {
      // floor is even, round down
      return floorValue * sign;
    }
  }
}



// emulate CS 1.0 Int()
int
sim::ds::INT( double value )
{
  return (int)floor(value);
}



void
Location::SetNulliparousBloodMealStatus( AdultCohort & cohort )
{
  // nulliparous females seek a blood meal the day after emergence and a potential double blood meal the day after
  if( cohort.Age == 2 ) {
    cohort.SeekingBloodMeal = true;
    cohort.SeekingDoubleBloodMeal = false;
  }
  else if( cohort.Age == 3 ) {
    cohort.SeekingBloodMeal = false;
    cohort.SeekingDoubleBloodMeal = true;
  }
  else {
    cohort.SeekingBloodMeal = false;
    cohort.SeekingDoubleBloodMeal = false;
  }
}



void
Location::SetParousBloodMealStatus( AdultCohort & cohort )
{
  // oviposited yesterday, sought blood meal yesterday, seek double blood meal today
  if( cohort.SeekingBloodMeal == true ) {
    cohort.Ovipositing = false;
    cohort.SeekingBloodMeal = false;        
    cohort.SeekingDoubleBloodMeal = true;        
  }

  // ovipositied 2 days ago, sought double blood meal yesterday
  else if( cohort.SeekingDoubleBloodMeal == true ) {
    cohort.Ovipositing = false;
    cohort.SeekingBloodMeal = false;
    cohort.SeekingDoubleBloodMeal = false;
  }

  // did not seek blood meal or double blood meal yesterday
  else {
    cohort.Ovipositing = false;
    cohort.SeekingBloodMeal = false;
    cohort.SeekingDoubleBloodMeal = false;
  }

}
