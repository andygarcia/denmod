#include "stdafx.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <sstream>

#include "Location.h"
#include "Constants.h"
#include "Humans.h"

using namespace sim::ds;



Location::Location( const input::Location * location, sim::output::MosData * mosData, bool doDiskOutput )
: _location(location),
  _mosData(mosData),
  _doDiskOutput(doDiskOutput),

  GasCoef(1.987f),
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
  _infectiveOvipositing(std::vector<MosquitoCollection>( 4+1 )),
  _infectiveBites(std::vector<double>( 4+1, 0 )),
  _infectiveMosquitoesBySerotype(std::vector<double>( 4+1, 0 )),
  _humanInoculationsBySerotype(std::vector<int>( 4+1, 0 ))
{
  // initialize random number generator
#ifdef _DEBUG
  _pdsRng = PdsRng(0);
#else
  // change once done with densim issues
  //_pdsRng = PdsRng( static_cast<unsigned int>(time(NULL)) );
  _pdsRng = PdsRng(0);
#endif

  // human population and demographics
  _humanPopulation = new HumanPopulation( this, _location );
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

  // biology parameters
  this->_minimumOvipositionTemperature = _location->Biology_->Adult->MinimumOvipositionTemperature;

  this->PropOnHum = _location->Biology_->Adult->ProportionOfFeedsOnHumans;
  this->FdAttempts = _location->Biology_->Adult->InterruptedFeedsPerMeal;
  this->PropDifHost = _location->Biology_->Adult->ProportionOfInterruptedFeedsOnDifferentHost;

  this->DBloodLWt = _location->Biology_->Adult->DoubleBloodMeal->LowWeightLimit;
  this->DBloodUProp = _location->Biology_->Adult->DoubleBloodMeal->LowWeightRatio;
  this->DBloodUWt = _location->Biology_->Adult->DoubleBloodMeal->HighWeightLimit;
  this->DBloodLProp = _location->Biology_->Adult->DoubleBloodMeal->HighWeightRatio;


  // initialize mosquito population from cimsim
  // TODO - for now set oviposition and blood meal seeking status based off age until
  // cimsim reports this as part of the cohort data
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
      AdultCohort newCohort = AdultCohort( 1, serotypeIntro->Mosquitoes_, 1.1, _dailyMosData.AverageWeight );
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
  _susceptibleOvipositing.clear();
  _susceptibleNulliparousBites = 0;
  _susceptibleNulliparousBiters.clear();
  _susceptibleNulliparousDoubleBiters.clear();

  // susceptible nulliparous cohorts
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
      _susceptibleOvipositing.push_back( *itMosq );
      itMosq = _susceptibleNulliparous.erase( itMosq );
    }
  }


  // create new nulliparous cohort from cimsim's emerged females
  if( _dailyMosData.NewFemales > 0 ) {
    // TODO this weight needs to be the newly emerged female weight not the average,
    //AdultCohort newCohort = AdultCohort( 1, _dailyMosData.NewFemales, _dailyMosData.AdultDevelopment, _dailyMosData.NewFemaleWeight );
    AdultCohort newCohort = AdultCohort( 1, _dailyMosData.NewFemales, _dailyMosData.AdultDevelopment, _dailyMosData.AverageWeight );

    // adjust cohort count for both simulation size and survival
    // TODO - remove survival application, this cohort already had survival applied today at its pupae stage
    int numberOfHumans = _humanPopulation->GetPopulationSize();
    newCohort.Number *= (numberOfHumans / HumHostDensity) * _dailyMosData.OverallSurvival;

    _susceptibleNulliparous.push_back( newCohort );
  }


  // accumulate cohorts seeking blood meals
  for( MosquitoIterator itMosq = _susceptibleNulliparous.begin(); itMosq != _susceptibleNulliparous.end(); ++itMosq ) {
    if( itMosq->SeekingBloodMeal ) {
      _susceptibleNulliparousBiters.push_back( &*itMosq );
      _susceptibleNulliparousBites += itMosq->Number;
    }
    if( itMosq->SeekingDoubleBloodMeal ) {
      _susceptibleNulliparousDoubleBiters.push_back( &*itMosq );
      _susceptibleNulliparousBites += itMosq->Number * CalculateDoubleBloodMealProportion( _dailyMosData.AverageWeight );
    }
  }
}



void
Location::AdvanceSusceptibleParous(void)
{
  // clear susceptible parous bite count and collections
  _susceptibleParousBites = 0;
  _susceptibleParousBiters.clear();
  _susceptibleParousDoubleBiters.clear();
  
  // advance susceptible parous cohorts
  for( MosquitoIterator itMosq = _susceptibleParous.begin(); itMosq != _susceptibleParous.end(); ) {

    // advance in age and apply survival
    itMosq->Age++;
    itMosq->Number *= _dailyMosData.OverallSurvival;

    if( itMosq->Development <= .58 ) {
      // accumulate development
      itMosq->Development += _dailyMosData.AdultDevelopment;
        
      SetParousBloodMealStatus( *itMosq );

      ++itMosq;
    }
    else {
      // apply survival and move to ovipositing collection
      _susceptibleOvipositing.push_back( *itMosq );

      // remove from current collection
      itMosq = _susceptibleParous.erase( itMosq );
    }
  }


  // create new ovi adult cohort based on all susceptible ovipositing today, reseting dev cycle and "age"
  if( _susceptibleOvipositing.size()  > 0 ) {
    // pull values for new cohort
    int age = 1;
    double number = GetTotalMosquitoes( _susceptibleOvipositing );
    double dev = _dailyMosData.AdultDevelopment;
    // TODO - move to using true average as part of per cohort weights
    //double weight = GetSusceptibleOvipositingAverageWeight();
    double weight = _dailyMosData.AverageWeight;

    // parous cohorts seek blood meal on same day they oviposit
    AdultCohort newParousCohort = AdultCohort( age, number, dev, weight );
    newParousCohort.Ovipositing = true;
    newParousCohort.SeekingBloodMeal = true;
    newParousCohort.SeekingDoubleBloodMeal = false;
    _susceptibleParous.push_back( newParousCohort );
  }


  // accumulate cohorts seeking blood meals
  for( MosquitoIterator itMosq = _susceptibleParous.begin(); itMosq != _susceptibleParous.end(); ++itMosq ) {
    if( itMosq->SeekingBloodMeal ) {
      _susceptibleParousBiters.push_back( &*itMosq );
      _susceptibleParousBites += itMosq->Number;
    }
    if( itMosq->SeekingDoubleBloodMeal ) {
      _susceptibleParousDoubleBiters.push_back( &*itMosq );
      _susceptibleParousBites += itMosq->Number * CalculateDoubleBloodMealProportion( _dailyMosData.AverageWeight );
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

      // calculate CD cutoff
      double OldAdultDev = _yesterdayMosData.AdultDevelopment;

      double CDYest = itMosq->Development - OldAdultDev;
      double CDTest;
      int CDFactor;
      if( CDYest < 1 ) {
        CDTest = 1;
      }
      else {
        CDFactor = INT((CDYest - 1) / .58f) + 1;
        CDTest = 1 + (CDFactor * .58f);
      }


      if( itMosq->Eip > 1.0 && itMosq->Development > CDTest ) {
        // mosquito finished development and EIP, apply survival
        // apply survival and transfer into newly infective nulliparous collection
        itMosq->Age++;
        itMosq->Number *= _dailyMosData.OverallSurvival;
        _newlyInfectiveNulliparous[iSerotype].push_back( *itMosq );
        itMosq = _infectedNulliparous[iSerotype].erase( itMosq );
      }
      else {
        // not finished with eip but not neccesarily not finished development
        // apply survival, accumulate development, and accumulate eip
        itMosq->Age++;
        itMosq->Number *= _dailyMosData.OverallSurvival;
        itMosq->Development += _dailyMosData.AdultDevelopment;
        itMosq->Eip += _eipDevelopmentRate[iSerotype];

        // finished development, this isn't a transfer rather a count of infected
        if( (itMosq->Development - _dailyMosData.AdultDevelopment) > CDTest ) {
          _infectedBites[iSerotype] += itMosq->Number;
          _infectedNulliparousBites[iSerotype] += itMosq->Number;
          _infectedNulliparousDoubleBites[iSerotype] += itMosq->Number * CalculateDoubleBloodMealProportion( _dailyMosData.AverageWeight );
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

    for( MosquitoIterator itMosq = _infectedParous[iSerotype].begin(); itMosq != _infectedParous[iSerotype].end(); )
    {
      if( itMosq->Eip > 1 && itMosq->Development > .58 ) {
        // finished eip and development, transfer to newly infective parous collection
        itMosq->Age++;
        itMosq->Number *= _dailyMosData.OverallSurvival;
        _newlyInfectiveParous[iSerotype].push_back( *itMosq );
        itMosq = _infectedParous[iSerotype].erase( itMosq );
      }
      else {
        // not finished eip, but potentially having finished another gonotropic cycle
        itMosq->Age++;
        itMosq->Number *= _dailyMosData.OverallSurvival;

        if( itMosq->Development > .58 ) {
          // finished a gonotropic cycle
          _infectedBites[iSerotype] += itMosq->Number;
          _infectedParousBites[iSerotype] += itMosq->Number;
          _infectedParousDoubleBites[iSerotype] += itMosq->Number * CalculateDoubleBloodMealProportion( _dailyMosData.AverageWeight );

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
  _infectiveOvipositing = std::vector<MosquitoCollection>( 4+1 );


  for( int iSerotype = 1; iSerotype <= 4; ++iSerotype ) {
    for( MosquitoIterator itMosq = _infectives[iSerotype].begin(); itMosq != _infectives[iSerotype].end(); ) {

      if( itMosq->Development <= .58 ) {
        // not yet completed current gonotrophic cycle
        // apply survival and accumulate development
        itMosq->Age++;
        itMosq->Number *= _dailyMosData.OverallSurvival;
        itMosq->Development += _dailyMosData.AdultDevelopment;
        ++itMosq;
      }
      else {
        // finish current gonotropic cycle
        // apply survival and moving ovipositing collection
        itMosq->Age++;
        itMosq->Number *= _dailyMosData.OverallSurvival;
        _infectiveOvipositing[iSerotype].push_back( *itMosq );
        itMosq = _infectives[iSerotype].erase( itMosq );
      }
    }

    // three collections contribute to the newest infective cohort
    MosquitoCollection mc;
    // previously infective that are ovipositing and starting a new cycle
    if( _infectiveOvipositing[iSerotype].size() > 0 ) {
      mc.push_back( CombineCohorts(_infectiveOvipositing[iSerotype], 1, _dailyMosData.AdultDevelopment) );
    }
    // newly infective nulliparous
    if( _newlyInfectiveNulliparous[iSerotype].size() > 0 ) {
      mc.push_back( CombineCohorts(_newlyInfectiveNulliparous[iSerotype], 1, _dailyMosData.AdultDevelopment) );
    }
    // newly infective parous
    if( _newlyInfectiveParous[iSerotype].size() > 0 ) {
      mc.push_back( CombineCohorts(_newlyInfectiveParous[iSerotype], 1, _dailyMosData.AdultDevelopment) );
    }
    // if any of these exists, combine all of them into the new cohort
    if( mc.size() > 0 ) {
      AdultCohort newInfective = CombineCohorts( mc, 1, _dailyMosData.AdultDevelopment );
      _infectives[iSerotype].push_back( newInfective );

    }

    // track infective biting
    for( MosquitoIterator itMosq = _infectives[iSerotype].begin(); itMosq != _infectives[iSerotype].end(); ++itMosq ) {
      if( itMosq->Age == 1 ) {
        _infectiveBites[iSerotype] += itMosq->Number;
      }
      if( itMosq->Age ==2 ) {
        _infectiveBites[iSerotype] += itMosq->Number * CalculateDoubleBloodMealProportion( _dailyMosData.AverageWeight );
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
  _bitesPerPerson = (_susceptibleNulliparousBites + _susceptibleParousBites) * PropOnHum;
  _bitesPerPerson += _bitesPerPerson * (FdAttempts - 1) * PropDifHost;
  _bitesPerPerson /= numberOfHumans;


  // randomly calculate new mosquito infections for four serotypes
  std::vector<int> seroTypesCompleted;
  // loop until all four sero types are processed
  while(true) {
    int i = INT( (4 - 1 + 1) * RND() + 1 );
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
    double num = RND();
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

    InfectParous( numParousInfections, iType );
    InfectNulliparous( numNulliparousInfections, iType );
  }
}



void
Location::InfectParous( int numParousInfections, int iSerotype )
{
  if( numParousInfections == 0 ) {
    return;
  }

  // TODO don't infect seperate cohorts for now
  // track newly infected cohorts to create combination
  MosquitoCollection newlyInfected;

  // first, distribute infectious among susceptible parous mosquitoes seeking a first blood meal
  for( MosquitoReferenceIterator itMosq = _susceptibleParousBiters.begin(); itMosq != _susceptibleParousBiters.end(); ++itMosq ) {
    // pull values from cohort to be infected
    AdultCohort & cohort = **itMosq;
    int age = cohort.Age;
    double numInfected = 0.0;
    double development = _dailyMosData.AdultDevelopment;
    double weight = cohort.Weight;

    if( numParousInfections < cohort.Number ) {
      // some portion infected
      numInfected = numParousInfections;
      cohort.Number -= numInfected;
      numParousInfections = 0;
    }
    else {
      // entire cohort infected
      numInfected = cohort.Number;
      numParousInfections -= numParousInfections;

      // remove cohort from susceptible parous collection
      _susceptibleParous.remove( cohort );
    }
 
    // create new infected cohort and add to serotype specific collection
    AdultCohort newlyInfectedCohort = AdultCohort( age, numInfected, development, weight );
    newlyInfectedCohort.Infected = true;
    newlyInfectedCohort.Serotype = iSerotype;
    // TODO don't make separet cohorts for now
    //_infectedParous[iSerotype].push_back( newlyInfectedCohort );
    newlyInfected.push_back( newlyInfectedCohort );

    // stop if all infections distributed
    if( numParousInfections > 0 ) {
      break;
    }
  }

  // second, if parous infections remaining, distribute among susceptible parous mosquitoes seeking a double blood meal
  if( numParousInfections > 0 ) {
    for( MosquitoReferenceIterator itMosq = _susceptibleParousDoubleBiters.begin(); itMosq != _susceptibleParousDoubleBiters.end(); ++itMosq ) {
      // pull values from cohort to be infected
      AdultCohort & cohort = **itMosq;
      int age = cohort.Age;
      double numInfected = 0.0;
      double development = _dailyMosData.AdultDevelopment;
      double weight = cohort.Weight;

      if( numParousInfections < cohort.Number ) {
        // some portion infected
        numInfected = numParousInfections;
        cohort.Number -= numInfected;
        numParousInfections = 0;
      }
      else {
        // entire cohort infected
        numInfected = cohort.Number;
        numParousInfections -= numParousInfections;

        // remove cohort from susceptible parous collection
        _susceptibleParous.remove( cohort );
      }
   
      // create new infected cohort and add to serotype specific collection
      AdultCohort newlyInfectedCohort = AdultCohort( age, numInfected, development, weight );
      newlyInfectedCohort.Infected = true;
      newlyInfectedCohort.Serotype = iSerotype;
      //_infectedParous[iSerotype].push_back( newlyInfectedCohort );
      newlyInfected.push_back( newlyInfectedCohort );
    }
  }

  // TODO - combine cohort for now
  AdultCohort newCohort = CombineCohorts( newlyInfected, 1, _dailyMosData.AdultDevelopment );
  newCohort.Infected = true;
  newCohort.Serotype = iSerotype;
  newCohort.Eip = _eipDevelopmentRate[iSerotype];
  _infectedParous[iSerotype].push_back( newCohort );
}



void
Location::InfectNulliparous( int numNulliparousInfections, int iSerotype )
{
  if( numNulliparousInfections == 0 ) {
    return;
  }

  MosquitoCollection newlyInfected;

  // now distribute infectious among susceptible nullparous mosquitoes seeking a first blood meal
  for( MosquitoReferenceIterator itMosq = _susceptibleNulliparousBiters.begin(); itMosq != _susceptibleNulliparousBiters.end(); ++itMosq ) {
    // pull values from cohort to be infected
    AdultCohort & cohort = **itMosq;
    int age = cohort.Age;
    double numInfected = 0.0;
    double development = _dailyMosData.AdultDevelopment;
    double weight = cohort.Weight;

    if( numNulliparousInfections < cohort.Number ) {
      // some portion infected
      numInfected = numNulliparousInfections;
      cohort.Number -= numInfected;
      numNulliparousInfections = 0;
    }
    else {
      // entire cohort infected
      numInfected = cohort.Number;
      numNulliparousInfections -= numNulliparousInfections;

      // remove cohort from susceptible nulliparous collection
      _susceptibleNulliparous.remove( cohort );
    }
 
    // create new infected cohort and add to serotype specific collection
    AdultCohort newlyInfectedCohort = AdultCohort( age, numInfected, development, weight );
    newlyInfectedCohort.Infected = true;
    newlyInfectedCohort.Serotype = iSerotype;
    //_infectedNulliparous[iSerotype].push_back( newlyInfectedCohort );
    newlyInfected.push_back( newlyInfectedCohort );

    // stop once infections are all distributed
    if( numNulliparousInfections > 0 ) {
      break;
    }
  }

  // second, if infections remain, distribute among susceptible nulliparous mosquitoes seeking a double blood meal
  if( numNulliparousInfections > 0 ) {
    for( MosquitoReferenceIterator itMosq = _susceptibleNulliparousDoubleBiters.begin(); itMosq != _susceptibleNulliparousDoubleBiters.end(); ++itMosq ) {
      // pull values from cohort to be infected
      AdultCohort & cohort = **itMosq;
      int age = cohort.Age;
      double numInfected = 0.0;
      double development = _dailyMosData.AdultDevelopment;
      double weight = cohort.Weight;

      if( numNulliparousInfections < cohort.Number ) {
        // some portion infected
        numInfected = numNulliparousInfections;
        cohort.Number -= numInfected;
        numNulliparousInfections = 0;
      }
      else {
        // all infected
        numInfected = cohort.Number;
        numNulliparousInfections -= numNulliparousInfections;

        // remove cohort from susceptible Nulliparous collection
        _susceptibleNulliparous.remove( cohort );
      }
   
      // create new infected cohort and add to serotype specific collection
      AdultCohort newlyInfectedCohort = AdultCohort( age, numInfected, development, weight );
      newlyInfectedCohort.Infected = true;
      newlyInfectedCohort.Serotype = iSerotype;
      //_infectedNulliparous[iSerotype].push_back( newlyInfectedCohort );
      newlyInfected.push_back( newlyInfectedCohort );
    }
  }

  // TODO - combine cohort for now
  AdultCohort newCohort = CombineCohorts( newlyInfected, 1, _dailyMosData.AdultDevelopment );
  newCohort.Infected = true;
  newCohort.Serotype = iSerotype;
  newCohort.Eip = _eipDevelopmentRate[iSerotype];
  _infectedNulliparous[iSerotype].push_back( newCohort );
}



void
Location::MosquitoToHumanTransmission(void)
{
  // clear daily human inoculation count
  _humanInoculations = 0;

  // randomly calculate new human infections for four serotypes
  std::vector<int> seroTypesCompleted;
  // loop until all four sero types are processed
  while(true) {
    // select a serotype randomly
    int serotype = INT( (4 - 1 + 1) * RND() + 1 );

    // see if it has been previously selected or not
    std::vector<int>::iterator findResult;
    findResult = std::find( seroTypesCompleted.begin(), seroTypesCompleted.end(), serotype );

    // do serotype innoculation if not previously selected
    if( findResult == seroTypesCompleted.end() ) {
      _humanInoculations += InoculateHumans( serotype );
      seroTypesCompleted.push_back( serotype );
    }

    // continue until all 4 serotypes have been selected
    if( seroTypesCompleted.size() == 4 ) {
      break;
    }
  }
}



int
Location::InoculateHumans( int serotype )
{
  // first calculate a floating point value based off bites
  double inoculationEstimate = _infectiveBites[serotype] * PropOnHum;
  inoculationEstimate += (_infectiveBites[serotype] * PropOnHum) * (FdAttempts - 1) * PropDifHost;
  inoculationEstimate *= MosqToHumProb;

  // then change into a discrete value
  int numInoculations = 0;
  if( inoculationEstimate > StochTransNum ) {
    // rouding
    numInoculations = CINT( inoculationEstimate );
  }
  else if( inoculationEstimate > 0 ) {
    // stochasticity
    double num = RND();
    double SumOfProb = 0;
    int r;
    for( r = 0; r <= 150; ++r ) {
      double rfact = Factorial(r);
      if( rfact == 0 ) {
        throw; // STOP
      }
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
  _humanInoculationsBySerotype[serotype] = numInoculations;
  

  // distribute new human inoculations into the human population
  for( int i = 1; i <= numInoculations; ++i ) {
    _humanPopulation->InoculateRandomHuman( serotype );
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
    _locationLog->AddData( GetTotalMosquitoes( _susceptibleOvipositing ) );
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
  const double & lowWeight = DBloodLWt;
  const double & lowWeightProportion = DBloodUProp;
  
  const double & highWeight = DBloodUWt;
  const double & highWeightProportion = DBloodLProp;

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



double
Location::GetSusceptibleOvipositingAverageWeight(void)
{
  // DS 1.0 takes all females that oviposit on the current day
  // and sticks them into a new OviAdultCohort (with AdultWt however, which was in error),
  // we establish the same cohort (TODO: change?) but use the true average weight of
  // females contributing to new cohort
  double totalWeight = 0.0;
  double totalNumber = 0.0;

  for( MosquitoIterator itMosq = _susceptibleOvipositing.begin(); itMosq != _susceptibleOvipositing.end(); ++itMosq ) {
    totalNumber += itMosq->Number;
    totalWeight += itMosq->Weight * itMosq->Number;
  }

  if( totalNumber == 0.0 ) {
    return 0.0;
  }
  else {
    return totalWeight / totalNumber;
  }
}



AdultCohort
Location::CombineCohorts( MosquitoCollection & collection, int age, double development )
{
  double totalWeight = 0.0;
  double totalNumber = 0.0;

  for( MosquitoIterator itMosq = collection.begin(); itMosq != collection.end(); ++itMosq ) {
    totalNumber += itMosq->Number;
    totalWeight += itMosq->Weight * itMosq->Number;
  }

  double averageWeight;
  if( totalNumber == 0.0 ) {
    averageWeight = 0.0;
  }
  else {
    averageWeight = totalWeight / totalNumber;
  }

  AdultCohort newCohort = AdultCohort( age, totalNumber, development, averageWeight );
  return newCohort;
}



// emulate DS 1.0 CINT() which does banker's rounding
int
Location::CINT( double value )
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
Location::INT( double value )
{
  return (int)floor(value);
}



// emulate PDS 7.1 RND
// PDS 7.1 RND returns single precision values in the range of [0,1)
// the only problem with our emulation is the exclusion of
// ( RAND_MAX/(RAND_MAX+1), 1 ) from the range of generation
double
Location::RND(void)
{
  if( EMULATE_PDS_RAND ) {
    double nextRnd = _pdsRng.Next();
    return nextRnd;
  }
  else {
    return rand() / (float) (RAND_MAX + 1); 
  }
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
