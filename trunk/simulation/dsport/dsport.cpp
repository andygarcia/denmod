#include "stdafx.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <sstream>

#include "dsport.h"
#include "Constants.h"
#include "Humans.h"

using namespace sim::dsport;



dsport::dsport( const input::Location * location, sim::output::MosData * mosData, bool doDiskOutput )
: _location(location),
  _mosData(mosData),
  _doDiskOutput(doDiskOutput),
  GasCoef(1.987f),
  Virus(std::vector<VirusDesc>( 4+1 )),
  EIPFactor(std::vector<double>( 4+1, 0 )),
  NewMosqSusc(std::vector<double>( (MaxAgeMosq+1) + 1, 0 )),
  NewMosqSuscCD(std::vector<double>( (MaxAgeMosq+1) + 1, 0 )),
  OldMosqSusc(std::vector<double>( (MaxAgeMosq+1) + 1, 0 )),
  OldMosqSuscCD(std::vector<double>( (MaxAgeMosq+1) + 1, 0 )),
  NewMosqInfd(std::vector<std::vector<double>>( (MaxAgeMosq+1) + 1, std::vector<double>( 4+1, 0 ) )),
  NewMosqInfdCD(std::vector<std::vector<double>>( (MaxAgeMosq+1) + 1, std::vector<double>( 4+1, 0 ) )),
  NewMosqInfdEIP(std::vector<std::vector<double>>( (MaxAgeMosq+1) + 1, std::vector<double>( 4+1, 0 ) )),
  OldMosqInfd(std::vector<std::vector<double>>( (MaxAgeMosq+1) + 1, std::vector<double>( 4+1, 0 ) )),
  OldMosqInfdCD(std::vector<std::vector<double>>( (MaxAgeMosq+1) + 1, std::vector<double>( 4+1, 0 ) )),
  OldMosqInfdEIP(std::vector<std::vector<double>>( (MaxAgeMosq+1) + 1, std::vector<double>( 4+1, 0 ) )),
  MosqInfv(std::vector<std::vector<double>>( (MaxAgeMosq+1) + 1, std::vector<double>( 4+1, 0 ) )),
  MosqInfvCD(std::vector<std::vector<double>>( (MaxAgeMosq+1) + 1, std::vector<double>( 4+1, 0 ) )),
  BitersInfdNewDB(std::vector<double>( 4+1, 0 )),
  BitersInfdOldDB(std::vector<double>( 4+1, 0 )),
  BitersInfv(std::vector<double>( 4+1, 0 )),
  EIPDevRate(std::vector<double>( 4+1, 0 )),
  MosqInfvTotal(std::vector<double>( 4+1, 0 )),
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
  oldLog(std::ofstream( "oldLog.txt" )),
  newLog(std::ofstream( "newLog.txt" ))
{
  // initialize random number generator
#ifdef _DEBUG
  _pdsRng = PdsRng(0);
#else
  // change once done with densim issues
  //_pdsRng = PdsRng( static_cast<unsigned int>(time(NULL)) );
  _pdsRng = PdsRng(0);
#endif

  // initialize human population
  _humanPopulation = new HumanPopulation( this, _location );
  
  // demographics
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

  this->MANADurat = _location->Serology_->ManaDuration_;
  this->MAEADurat = _location->Serology_->MaeaDuration_;
  this->HetImmunDurat = _location->Serology_->HetDuration_;


  // biology parameters
  this->PropOnHum = _location->Biology_->Adult->ProportionOfFeedsOnHumans;
  this->FdAttempts = _location->Biology_->Adult->InterruptedFeedsPerMeal;
  this->PropDifHost = _location->Biology_->Adult->ProportionOfInterruptedFeedsOnDifferentHost;

  this->DBloodLWt = _location->Biology_->Adult->DoubleBloodMeal->LowWeightLimit;
  this->DBloodUProp = _location->Biology_->Adult->DoubleBloodMeal->LowWeightRatio;
  this->DBloodUWt = _location->Biology_->Adult->DoubleBloodMeal->HighWeightLimit;
  this->DBloodLProp = _location->Biology_->Adult->DoubleBloodMeal->HighWeightRatio;

  this->_minimumOvipositionTemperature = _location->Biology_->Adult->MinimumOvipositionTemperature;

  // initialize mosquito population
  double initialArea = _humanPopulation->GetInitialPopulationSize() / HumHostDensity;
  for( sim::cs::PreOviAdultCohortCollection::iterator itAdult = _mosData->PreOviAdultCohorts.begin();
       itAdult != _mosData->PreOviAdultCohorts.end(); ++itAdult ) {
    NewMosqSusc[itAdult->Age] = itAdult->Number * initialArea;
    NewMosqSuscCD[itAdult->Age] = itAdult->Development;
  }
  for( sim::cs::OviAdultCohortCollection::iterator itAdult = _mosData->OviAdultCohorts.begin();
       itAdult != _mosData->OviAdultCohorts.end(); ++itAdult ) {
    OldMosqSusc[itAdult->Age] = itAdult->Number * initialArea;
    OldMosqSuscCD[itAdult->Age] = itAdult->Development;
  }

  // initialize new mosquito collections
  for( sim::cs::PreOviAdultCohortCollection::iterator itAdult = _mosData->PreOviAdultCohorts.begin();
       itAdult != _mosData->PreOviAdultCohorts.end(); ++itAdult ) {
    AdultCohort cohort = AdultCohort( *itAdult );
    cohort.Number *= initialArea;
    _susceptibleNulliparous.push_back( cohort );
  }
  for( sim::cs::OviAdultCohortCollection::iterator itAdult = _mosData->OviAdultCohorts.begin();
       itAdult != _mosData->OviAdultCohorts.end(); ++itAdult ) {
    AdultCohort cohort = AdultCohort( *itAdult );
    cohort.Number *= initialArea;
    _susceptibleParous.push_back( cohort );
  }


  // weather and default dates
  boost::gregorian::date_period wxAvailable = _location->Weather_->GetWeatherPeriod();
  _startDate = wxAvailable.begin();
  _stopDate = wxAvailable.end();

  // initialize infection schedules
  _location->InfectionIntroduction_->Dengue1_->Schedule_->CalculateSchedule( _startDate, _stopDate );
  _location->InfectionIntroduction_->Dengue2_->Schedule_->CalculateSchedule( _startDate, _stopDate );
  _location->InfectionIntroduction_->Dengue3_->Schedule_->CalculateSchedule( _startDate, _stopDate );
  _location->InfectionIntroduction_->Dengue4_->Schedule_->CalculateSchedule( _startDate, _stopDate );

  if( _doDiskOutput ) {
    InitializeDiskLogs();
  }

  oldLog << "Year , Day , Age , Number, Development, Weight" << std::endl;
  newLog << "Year , Day , Age , Number, Development, Weight" << std::endl;
}



dsport::~dsport(void)
{
  if( _doDiskOutput ) {
    _locationLog->Write();
    delete _locationLog;
  }

  delete _humanPopulation;

  oldLog.close();
  newLog.close();
}



void
dsport::InitializeDiskLogs(void)
{
  std::vector<std::string> headers = std::vector<std::string>();
  headers.push_back( "Population Size" );
  headers.push_back( "Female Mosquitoes in Area" );
  headers.push_back( "Potentially Infective Bites" );

  _locationLog = new output::Log( "DENSiM Location Data.csv", headers );
}



void
dsport::Start(void)
{
  denmain();  
}



void
dsport::Start( boost::gregorian::date startDate, boost::gregorian::date stopDate )
{
  _startDate = startDate;
  _stopDate = stopDate;

  _densimOutput = new sim::output::DensimOutput( _startDate, _stopDate );

  Start();
}



void
dsport::denmain(void)
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
      InitInfectives();
    }

    // purge maternal antibodies
    _humanPopulation->PurgeMaternalAntibodies();

    // calculate daily eip development rate
    for( int k = 1; k <=4; ++k ) {
      EIPDevRate[k] = EIPEnzKin( _averageAirTemperature + 273.15f ) / EIPFactor[k];
    }

    if( _year == 1954 && _day == 145 ) {
      std::cout << "Breakpoint" << std::endl;
    }
  
    // advance mosquitoes
    MosquitoLifeCycle();
    NewMosquitoLifeCycle();

    // calculate transmission
    HumanToMosquitoTransmission();
    MosquitoToHumanTransmission();

    // housekeeping
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
dsport::CalculateEipFactors(void)
{
  // calculate EIP by titer
  for( int i = 1; i <= 4; ++i ) {
    if( Virus[i].Viremia < EipLTiter ) {
      EIPFactor[i] = EipLFactor;
    }
    else if( Virus[i].Viremia > EipHTiter ) {
      EIPFactor[i] = EipHFactor;
    }
    else {
      double Slope = (EipLFactor - EipHFactor) / (EipHTiter - EipLTiter);
      EIPFactor[i] = EipLFactor - (Virus[i].Viremia - EipLTiter) * Slope;
    }
  }
}



// emulate DS 1.0 CINT() which does banker's rounding
int
dsport::CINT( double value )
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
dsport::INT( double value )
{
  return (int)floor(value);
}



// emulate PDS 7.1 RND
// PDS 7.1 RND returns single precision values in the range of [0,1)
// the only problem with our emulation is the exclusion of
// ( RAND_MAX/(RAND_MAX+1), 1 ) from the range of generation
double
dsport::RND(std::string callingMethod)
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
dsport::InitInfectives(void)
{
  for( int serotype = 1; serotype <= 4; ++serotype ) {
    // get serotype introduction object for this serotype
    input::SerotypeIntroduction * serotypeIntro = _location->InfectionIntroduction_->GetSerotype(serotype);

    if( serotypeIntro->Schedule_->IsDateScheduled( _currentDate ) && serotypeIntro->Mosquitoes_ > 0 ) {
      // look for empty position in the old infected array and add.  This way the
      // new infectives will drop to position 1 in the infective array and
      // become new blood feeders on this day.
      // If no free space is found, then add to last position in the array.
      bool ifound = false;
      for( int i = 1; i <= MaxAgeMosq; ++i ) {
        if( OldMosqInfd[i][serotype] == 0 ) {
          OldMosqInfd[i][serotype] = serotypeIntro->Mosquitoes_;
          OldMosqInfdCD[i][serotype] = 1.1f;
          OldMosqInfdEIP[i][serotype] = 1.1f;
          ifound = true;

          oldLog << "InitInfectives , "
                 << serotype << " , "
                 << i << " , "
                 << OldMosqInfd[i][serotype] << " , "
                 << std::endl;

          // insert into new colletions
          AdultCohort newCohort = AdultCohort( i, serotypeIntro->Mosquitoes_, 1.1, _dailyMosData.AverageWeight );
          newCohort.Infected = true;
          newCohort.Eip = 1.1;
          newCohort.Serotype = serotype;
          _infectedParous[serotype].push_back( newCohort );

          newLog << "InitInfectives , "
                 << serotype << " , "
                 << newCohort.Age << " , "
                 << newCohort.Number << " , "
                 << std::endl;

          break;
        }
      }
      if( ifound != true ) {
        // no open position found, accumulate into the oldest cohort of old infecteds
        OldMosqInfd[MaxAgeMosq][serotype] = OldMosqInfd[MaxAgeMosq][serotype] + serotypeIntro->Mosquitoes_;
        OldMosqInfdCD[MaxAgeMosq][serotype] = 1.1f;
        OldMosqInfdEIP[MaxAgeMosq][serotype] = 1.1f;

        oldLog << "InitInfectives , "
               << serotype << " , "
               << MaxAgeMosq << " , "
               << OldMosqInfd[MaxAgeMosq][serotype] << " , "
               << std::endl;

        // accumulate into oldest infected parous cohort
        MosquitoIterator itMosq = _infectedParous[serotype].begin();
        itMosq->Number += serotypeIntro->Mosquitoes_;
        itMosq->Development = 1.1;
        itMosq->Eip = 1.1;

        newLog << "InitInfectives , "
               << serotype << " , "
               << itMosq->Age << " , "
               << itMosq->Number << " , "
               << std::endl;
      }
    }
  }

  // initialize infective humans
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
dsport::EIPEnzKin( double temp )
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
dsport::MosquitoLifeCycle(void)
{
  oldLog << "MosquitoLifeCycle" << std::endl;

  // BitersNew         - First time susceptible biters
  // BitersOld         - Old susceptible biters
  // BitersInfdNewDB() - Yesterdays double blood feeders from new infd - Global
  // BitersInfdOldDB() - Yesterdays double blood feeders from old infd - Global
  // BitersInfv()      - Infective biters - Global
  // EggersNew         - First time egg layers
  // EggersOld         - Old egg layers
  // DMealProp         - Prop. taking double blood meals
  // OldAdultDev       - Yesterdays adult development
  // BitersTotal       - Total biters (susc/infd/infv).  Global
  // InSurviving       - Indoor surviving mosquitoes
  // OutSurviving      - Outdoor surviving mosquitoes

  std::vector<double> BitersInfd( 4+1, 0 );        // infected biters
  std::vector<double> EIPTranNew( 4+1, 0 );        // Infective class from infected new
  std::vector<double> EIPTranOld( 4+1, 0 );        // Infective class from infected old
  std::vector<double> EggersInfv( 4+1, 0 );        // Infective egg transfers
  BitersInfv = std::vector<double>( 4+1, 0 );      // total infective biters
  
  if( _currentDate == _startDate )  {
    // initialize static variables
    BitersInfdNewDB = std::vector<double>( 4+1, 0 );
    BitersInfdOldDB = std::vector<double>( 4+1, 0 );
  }


  // calculate proportion taking a double blood meal
  double DMealProp = 0;
  if( _dailyMosData.AverageWeight <= DBloodLWt ) {
    DMealProp = DBloodUProp;
  }
  else if( _dailyMosData.AverageWeight >= DBloodUWt ) {
    DMealProp = DBloodLProp;
  }
  else {
    // TODO - verify these equations
    double Slope = (DBloodUProp - DBloodLProp) / (DBloodUWt - DBloodLWt);
    DMealProp = DBloodUProp - ((_dailyMosData.AverageWeight - DBloodLWt) * Slope);
  }

  // Advance Susceptibles - First Gonotrophic Cycle
  // Last position in the array does not accumulate
  BitersNew = 0;
  double EggersNew = 0;
  for( int i = MaxAgeMosq; i >= 1; --i ) {
    if( NewMosqSusc[i] <= 0 ) {
      continue; // move to next youngest cohort
    }
    else {
      if( NewMosqSuscCD[i] <= 1 ) {
        NewMosqSusc[i + 1] = NewMosqSusc[i] * _dailyMosData.OverallSurvival;
        NewMosqSuscCD[i + 1] = NewMosqSuscCD[i] + _dailyMosData.AdultDevelopment;
      }
      else {
        EggersNew = EggersNew + (NewMosqSusc[i] * _dailyMosData.OverallSurvival);
      }
      NewMosqSusc[i] = 0;
      NewMosqSuscCD[i] = 0;
    }
  }

  //adjust cimsim mosq pop(per ha) for current population size
  if( HumHostDensity == 0 ) {
    throw; // STOP 
  }
  int numberOfHumans = _humanPopulation->GetPopulationSize();
  NewMosqSusc[1] = _dailyMosData.NewFemales * (numberOfHumans / HumHostDensity) * _dailyMosData.OverallSurvival;
  NewMosqSuscCD[1] = _dailyMosData.AdultDevelopment;
  BitersNew = NewMosqSusc[2] + (NewMosqSusc[3] * DMealProp);

  OutputNewMosqSusc();
  oldLog << "  " << BitersNew << std::endl;

  // Advance Susceptibles - Successive Gonotrophic Cycles
  // Last position in the array does not accumulate
  BitersOld = 0;
  double EggersOld = 0;
  for( int i = MaxAgeMosq; i >= 1; --i ) {
    if( OldMosqSusc[i] <= 0 ) {
      continue;
    }
    else {
      if( OldMosqSuscCD[i] <= .58 ) {
        OldMosqSusc[i + 1] = OldMosqSusc[i] * _dailyMosData.OverallSurvival;
        OldMosqSuscCD[i + 1] = OldMosqSuscCD[i] + _dailyMosData.AdultDevelopment;
      }
      else {
        EggersOld = EggersOld + (OldMosqSusc[i] * _dailyMosData.OverallSurvival);
      }
      OldMosqSusc[i] = 0;
      OldMosqSuscCD[i] = 0;
    }
  }

  OldMosqSusc[1] = EggersNew + EggersOld;
  OldMosqSuscCD[1] = _dailyMosData.AdultDevelopment;
  BitersOld = OldMosqSusc[1] + (OldMosqSusc[2] * DMealProp);

  OutputOldMosqSusc();
  oldLog << "  " << BitersOld << std::endl;

  // Advance infected - From New Mosquitoes - First and successive Gonotrophic Cycles
  // Last position in the array does not accumumlate
  for( int j = 1; j <= 4; ++j ) {
    // double blood meal parameters were used on yesterday's infected biters to calculate how many
    // would bite again today, transfer into todays biting counts, then clear for today's calculations
    BitersInfd[j] = BitersInfdNewDB[j];
    BitersInfdNewDB[j] = 0;
    for( int i = MaxAgeMosq; i >= 1; --i ) {
      if( NewMosqInfd[i][j] <= 0 ) {
        continue; //go to next cohort
      }
      else {
        // calculate CD cutoff
        double OldAdultDev = _yesterdayMosData.AdultDevelopment;

        // superceeded by using _yesterdayMosData & _dailyMosData
        //if( Day == 1 ) {
        //  OldAdultDev = _yesterdayMosData.AdultDevelopment;
        //}
        //else {
        //  OldAdultDev = _yesterdayMosData.AdultDevelopment;
        //}

        double CDYest = NewMosqInfdCD[i][j] - OldAdultDev;
        double CDTest;
        int CDFactor;
        if( CDYest < 1 ) {
          CDTest = 1;
        }
        else {
          CDFactor = INT((CDYest - 1) / .58f) + 1;
          CDTest = 1 + (CDFactor * .58f);
        }

        if( NewMosqInfdEIP[i][j] > 1 && NewMosqInfdCD[i][j] > CDTest ) {
          EIPTranNew[j] = EIPTranNew[j] + (NewMosqInfd[i][j] * _dailyMosData.OverallSurvival);
        }
        else {
          NewMosqInfd[i + 1][j] = NewMosqInfd[i][j] * _dailyMosData.OverallSurvival;
          NewMosqInfdCD[i + 1][j] = NewMosqInfdCD[i][j] + _dailyMosData.AdultDevelopment;
          NewMosqInfdEIP[i + 1][j] = NewMosqInfdEIP[i][j] + EIPDevRate[j];
          if( NewMosqInfdCD[i][j] > CDTest ) {
            BitersInfd[j] = BitersInfd[j] + NewMosqInfd[i + 1][j];
            BitersInfdNewDB[j] = BitersInfdNewDB[j] + (NewMosqInfd[i + 1][j] * DMealProp);
          }
        }
        NewMosqInfd[i][j] = 0;
        NewMosqInfdCD[i][j] = 0;
        NewMosqInfdEIP[i][j] = 0;
      }
    }
  }

  OutputNewMosqInfd();
  oldLog << "  BitersInfd/_infectedBites , "
         << BitersInfd[1] << " , "
         << BitersInfd[2] << " , "
         << BitersInfd[3] << " , "
         << BitersInfd[4] << std::endl;

  // Advance infected - From old Mosquitoes - Second and successive Gonotrophic Cycles
  // Last position in the array does not accumumlate
  for( int j = 1; j <= 4; ++j ) {
    BitersInfd[j] = BitersInfd[j] + BitersInfdOldDB[j];
    BitersInfdOldDB[j] = 0;
    for( int i = MaxAgeMosq; i >= 1; --i ) {
      if( OldMosqInfd[i][j] <= 0 ) {
        continue; // go to next cohort
      }
      else {
        if( OldMosqInfdEIP[i][j] > 1 && OldMosqInfdCD[i][j] > .58 ) {
          EIPTranOld[j] = EIPTranOld[j] + (OldMosqInfd[i][j] * _dailyMosData.OverallSurvival);
        }
        else {
          OldMosqInfd[i+1][j] = OldMosqInfd[i][j] * _dailyMosData.OverallSurvival;
          if( OldMosqInfdCD[i][j] > .58 ) {
            BitersInfd[j] = BitersInfd[j] + OldMosqInfd[i+1][j];
            BitersInfdOldDB[j] = BitersInfdOldDB[j] + (OldMosqInfd[i+1][j] * DMealProp);
            OldMosqInfdCD[i+1][j] = _dailyMosData.AdultDevelopment;
          }
          else {
            OldMosqInfdCD[i+1][j] = OldMosqInfdCD[i][j] + _dailyMosData.AdultDevelopment;
          }
          OldMosqInfdEIP[i+1][j] = OldMosqInfdEIP[i][j] + EIPDevRate[j];
        }
        OldMosqInfd[i][j] = 0;
        OldMosqInfdCD[i][j] = 0;
        OldMosqInfdEIP[i][j] = 0;
      }
    }
  }

  OutputOldMosqInfd();
  oldLog << "  BitersInfd/_infectedBites , "
         << BitersInfd[1] << " , "
         << BitersInfd[2] << " , "
         << BitersInfd[3] << " , "
         << BitersInfd[4] << std::endl;


  // Advance infective - Successive Gonotrophic Cycles
  // Last position in the array does not accumulate
  for( int j = 1; j <= 4; ++j ) {   // serotypes
    for( int i = MaxAgeMosq; i >= 1; --i ) {
      if( MosqInfv[i][j] <= 0 ) {
        continue;  // go to next cohort
      }
      else {
        if( MosqInfvCD[i][j] <= .58 ) {
          MosqInfv[i+1][j] = MosqInfv[i][j] * _dailyMosData.OverallSurvival;
          MosqInfvCD[i+1][j] = MosqInfvCD[i][j] + _dailyMosData.AdultDevelopment;
        }
        else {
          EggersInfv[j] = EggersInfv[j] + (MosqInfv[i][j] * _dailyMosData.OverallSurvival);
        }
        MosqInfv[i][j] = 0;
        MosqInfvCD[i][j] = 0;
      }
    }

    MosqInfv[1][j] = EggersInfv[j] + EIPTranNew[j] + EIPTranOld[j];
    MosqInfvCD[1][j] = _dailyMosData.AdultDevelopment;
    BitersInfv[j] = MosqInfv[1][j] + (MosqInfv[2][j] * DMealProp);
  }

  OutputMosqInfv();
  oldLog << "  BitersInfv/_infectiveBites , "
         << BitersInfv[1] << " , "
         << BitersInfv[2] << " , "
         << BitersInfv[3] << " , "
         << BitersInfv[4] << std::endl;

  BitersTotal = BitersNew + BitersOld;
  for( int j =1; j <= 4; ++j ) {
    BitersTotal = BitersTotal + BitersInfd[j] + BitersInfv[j];
  }
  MosqTotal = 0;
  MosqInfvTotal = std::vector<double>( 4+1, 0 );
  for( int i = 1; i <= MaxAgeMosq; ++i ) {
    MosqTotal = MosqTotal + NewMosqSusc[i] + OldMosqSusc[i];
    for( int j =1; j <= 4; ++j ) {
      MosqTotal = MosqTotal + NewMosqInfd[i][j] + OldMosqInfd[i][j] + MosqInfv[i][j];
      MosqInfvTotal[j] = MosqInfvTotal[j] + MosqInfv[i][j];
    }
  }
}



void
dsport::NewMosquitoLifeCycle(void)
{
  newLog << "MosquitoLifeCycle" << std::endl;

  _susceptibleOvipositing.clear();

  AdvanceSusceptibleNulliparous();
  AdvanceSusceptibleParous();

  _infectedBites = std::vector<double>( 4+1, 0 );
  _newlyInfectiveNulliparous = std::vector<MosquitoCollection>( 4+1 );
  _newlyInfectiveParous = std::vector<MosquitoCollection>( 4+1 );

  AdvanceInfectedNulliparous();
  AdvanceInfectedParous();

  _infectiveBites = std::vector<double>( 4+1, 0 );
  _infectiveOvipositing = std::vector<MosquitoCollection>( 4+1 );
  AdvanceInfectives();

  _totalBites = _susceptibleNulliparousBites + _susceptibleParousBites;
  for( int iSerotype = 1; iSerotype <=4; ++iSerotype ) {
    _totalBites += _infectedBites[iSerotype] + _infectiveBites[iSerotype];
  }

  _totalInfectiveMosquitoes = GetTotalMosquitoes( _infectives );
  _totalMosquitoes = GetTotalMosquitoes( _susceptibleNulliparous )
                     + GetTotalMosquitoes( _susceptibleParous )
                     + GetTotalMosquitoes( _infectedNulliparous )
                     + GetTotalMosquitoes( _infectedParous )
                     + _totalInfectiveMosquitoes;

}



void
dsport::AdvanceSusceptibleNulliparous(void)
{
  // clear susceptible nulliparous bite count and collections
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
      // not done developing, advance by applying survival and development
      itMosq->Development += _dailyMosData.AdultDevelopment;
      ++itMosq;
    }
    else {
      // apply survival and move to ovipositing collection
      _susceptibleOvipositing.push_back( *itMosq );

      // remove from current collection
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

  // determine biting status
  for( MosquitoIterator itMosq = _susceptibleNulliparous.begin(); itMosq != _susceptibleNulliparous.end(); ++itMosq ) {

    // nulliparous seek blood meal on day after emergence
    if( itMosq->Age == 2 ) {
      _susceptibleNulliparousBiters.push_back( &*itMosq );
      _susceptibleNulliparousBites += itMosq->Number;
    }
    // nulliparous also seek a potential second blood meal on second day after emergence based on weight
    if( itMosq->Age == 3 ) {
      _susceptibleNulliparousDoubleBiters.push_back( &*itMosq );
      _susceptibleNulliparousBites += itMosq->Number * CalculateDoubleBloodMealProportion( _dailyMosData.AverageWeight );
    }
  }

  OutputSusceptibleNulliparous();
  newLog << "  " << _susceptibleNulliparousBites << std::endl;
}



void
dsport::AdvanceSusceptibleParous(void)
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
    
    // insert new cohort return iterator
    _susceptibleParous.push_back( AdultCohort(age, number, dev, weight) );
  }

  // track biting
  for( MosquitoIterator itMosq = _susceptibleParous.begin(); itMosq != _susceptibleParous.end(); ++itMosq ) {

    // parous always seek blood meal on same day they oviposit
    if( itMosq->Age == 1 ) {
      _susceptibleParousBiters.push_back( &*itMosq );
      _susceptibleParousBites += itMosq->Number;
    }
    // parous also seek a second blood meal on the day after oviposition based on weight
    if( itMosq->Age == 2 ) {
      _susceptibleParousDoubleBiters.push_back( &*itMosq );
      _susceptibleParousBites += itMosq->Number * CalculateDoubleBloodMealProportion( _dailyMosData.AverageWeight );
    }
  }

  OutputSusceptibleParous();
  newLog << "  " << _susceptibleParousBites << std::endl;
}



void
dsport::AdvanceInfectedNulliparous(void)
{
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
        itMosq->Eip += EIPDevRate[iSerotype];

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

  OutputInfectedNulliparous();
  newLog << "  BitersInfd/_infectedBites , "
         << _infectedBites[1] << " , "
         << _infectedBites[2] << " , "
         << _infectedBites[3] << " , "
         << _infectedBites[4] << std::endl;
}



void
dsport::AdvanceInfectedParous(void)
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
        itMosq->Eip += EIPDevRate[iSerotype];
        ++itMosq;
      }
    }
  }

  OutputInfectedParous();
  newLog  << "  BitersInfd/_infectedBites , "
         << _infectedBites[1] << " , "
         << _infectedBites[2] << " , "
         << _infectedBites[3] << " , "
         << _infectedBites[4] << std::endl;
}



void
dsport::AdvanceInfectives(void)
{
  // TODO - Last position in the array does not accumulate
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

  OutputInfectives();
  newLog  << "  BitersInfv/_infectiveBites , "
         << _infectiveBites[1] << " , "
         << _infectiveBites[2] << " , "
         << _infectiveBites[3] << " , "
         << _infectiveBites[4] << std::endl;
}



void
dsport::HumanToMosquitoTransmission(void)
{
  int numberOfHumans = _humanPopulation->GetPopulationSize();

  // handle dead population gracefully
  if( numberOfHumans == 0 ) {
    BitesPerPerson = 0;
    return;
  }

  // number of susceptible probes per individual
  BitesPerPerson = (BitersNew + BitersOld) * PropOnHum;
  BitesPerPerson = BitesPerPerson + (BitesPerPerson * (FdAttempts - 1) * PropDifHost);
  BitesPerPerson = BitesPerPerson / numberOfHumans;

  // TODO - new code
  _bitesPerPerson = (_susceptibleNulliparousBites + _susceptibleParousBites) * PropOnHum;
  _bitesPerPerson += _bitesPerPerson * (FdAttempts - 1) * PropDifHost;
  _bitesPerPerson /= numberOfHumans;

  // randomly calculate new mosquito infections for four serotypes
  std::vector<int> seroTypesCompleted;
  // loop until all four sero types are processed
  while(true) {
    int i = INT( (4 - 1 + 1) * RND("HumanToMosquitoTransmission") + 1 );
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

  OutputNewMosqInfd();
  OutputOldMosqInfd();
  OutputInfectedNulliparous();
  OutputInfectedParous();
}



void
dsport::InoculateMosquitoes( int iType )
{
  int r;                    // for poisson distribution
  double InocEstimate;       // number of mosquitoes to be infected
  int NewDlyMosqInoc;       // actual number of new infected mosq. (differs due to/if stochastic routines enabled)
  int OldInfd = 0;          // new infected from old susceptible
  int NewInfd = 0;          // new infected from new susceptible

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

  InocEstimate = _humanPopulation->GetInfectiveBySerotype(iType) * BitesPerPerson * ProbInf;
  
  // find new infected mosquitoes
  if( InocEstimate > StochTransNum ) {
    // discrete
    //NewDlyMosqInoc = CLNG(InocEstimate) where DS 1.0 used CLNG for a 4 bit integer, an int in c++, although machine dependent, can hold a word
    NewDlyMosqInoc = CINT(InocEstimate);
  }
  else if( InocEstimate > 0 ) {
    // stochastic
    double num = RND("CalcNewInocMosquitoes");
    double SumOfProb = 0;
    for( r = 0; r <= 150; ++r ) {
      double rfact = Factorial(r);
      if( rfact == 0 ) {
        break; // STOP
      }
      SumOfProb = SumOfProb + ( (pow(InocEstimate,r) * exp(-InocEstimate)) / rfact);
      if( SumOfProb > num ) {
        break;  // exit for
      }
    }
    NewDlyMosqInoc = r;
  }
  else {
    NewDlyMosqInoc = 0;
  }

  // Adjust mosquito arrays - add/subtract infected/susceptible mosquitoes
  if( NewDlyMosqInoc > 0 ) {

    if( _year == 1954 && _day == 144 ) {
      std::cout << "Breakpoint" << std::endl;
    }

    // calculate new infected from new and old susceptible
    OldInfd = CINT( (BitersOld / (BitersOld + BitersNew)) * NewDlyMosqInoc );
    NewInfd = NewDlyMosqInoc - OldInfd;

    oldLog << "Inoculate Mosquitoes , " << OldInfd << " , " << NewInfd << std::endl;

    // divide infections between parous and nulliparous susceptibles
    double parousProportion = _susceptibleParousBites / (_susceptibleParousBites + _susceptibleNulliparousBites);
    int numParousInfections = CINT( parousProportion * NewDlyMosqInoc );
    int numNulliparousInfections = NewDlyMosqInoc - numParousInfections;

    newLog << "Inoculate Mosquitoes , " << numParousInfections << " , " << numNulliparousInfections << std::endl;

    // adjust susceptible arrays
    // see if there are enough mosquitoes
    if( OldMosqSusc[1] + OldMosqSusc[2] < OldInfd ) {
      OldInfd = CINT( OldMosqSusc[1] + OldMosqSusc[2] );
    }
    OldMosqSusc[1] = OldMosqSusc[1] - OldInfd;
    if( OldMosqSusc[1] < 0 ) {
      OldMosqSusc[2] = OldMosqSusc[2] + OldMosqSusc[1];
      OldMosqSusc[1] = 0;
      OldMosqSuscCD[1] = 0;
    }

    if( NewMosqSusc[2] + NewMosqSusc[3] < NewInfd ) {
      NewInfd = CINT( NewMosqSusc[2] + NewMosqSusc[3] );
    }
    NewMosqSusc[2] = NewMosqSusc[2] - NewInfd;
    if( NewMosqSusc[2] < 0 ) {
      NewMosqSusc[3] = NewMosqSusc[3] + NewMosqSusc[2];
      NewMosqSusc[2] = 0;
      NewMosqSuscCD[2] = 0;
    }

    // adjust infected mosquito arrays
    OldMosqInfd[1][iType] = OldInfd;
    NewMosqInfd[1][iType] = NewInfd;
    OldMosqInfdCD[1][iType] = _dailyMosData.AdultDevelopment;
    NewMosqInfdCD[1][iType] = _dailyMosData.AdultDevelopment;
    OldMosqInfdEIP[1][iType] = EIPDevRate[iType];
    NewMosqInfdEIP[1][iType] = EIPDevRate[iType];

    if( _year == 1954 && (_day == 144 || _day == 145) ) {
      OutputOldMosqSusc();
    }

    // NEW CODE
    InfectParous( numParousInfections, iType );
    InfectNulliparous( numNulliparousInfections, iType );

    if( _year == 1954 && (_day == 144 || _day == 145) ) {
      OutputSusceptibleParous();
    }
  }
}



void
dsport::InfectParous( int numParousInfections, int iSerotype )
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
  newCohort.Eip = EIPDevRate[iSerotype];
  _infectedParous[iSerotype].push_back( newCohort );
}



void
dsport::InfectNulliparous( int numNulliparousInfections, int iSerotype )
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
  newCohort.Eip = EIPDevRate[iSerotype];
  _infectedNulliparous[iSerotype].push_back( newCohort );
}



void
dsport::MosquitoToHumanTransmission(void)
{
  // randomly calculate new human infections for four serotypes
  std::vector<int> seroTypesCompleted;
  // loop until all four sero types are processed
  while(true) {
    // select a serotype randomly
    int serotype = INT( (4 - 1 + 1) * RND("MosquitoToHumanTransmission") + 1 );

    // see if it has been previously selected or not
    std::vector<int>::iterator findResult;
    findResult = std::find( seroTypesCompleted.begin(), seroTypesCompleted.end(), serotype );

    // do serotype innoculation if not previously selected
    if( findResult == seroTypesCompleted.end() ) {
      InoculateHumans( serotype );
      seroTypesCompleted.push_back( serotype );
    }

    // continue until all 4 serotypes have been selected
    if( seroTypesCompleted.size() == 4 ) {
      break;
    }
  }
}




void
dsport::InoculateHumans( int serotype )
{
  int r;                      // for poisson distribution
  double InocEstimate;         // number of infv bites to humans

  InocEstimate = ((BitersInfv[serotype] * PropOnHum) + ((BitersInfv[serotype] * PropOnHum) * (FdAttempts - 1) * PropDifHost)) * MosqToHumProb;

  double totalInoculations = _infectiveBites[serotype] * PropOnHum;
  totalInoculations += (BitersInfv[serotype] * PropOnHum) * (FdAttempts - 1) * PropDifHost;
  totalInoculations *= MosqToHumProb;

  oldLog << "InoculateHumans , " << BitersInfv[serotype] << " , " << InocEstimate << std::endl;
  newLog << "InoculateHumans , " << _infectiveBites[serotype] << " , " << totalInoculations << std::endl;

  if( InocEstimate > StochTransNum ) {
    // discrete
    NewDlyHumInoc = CINT( InocEstimate );
  }

  else if( InocEstimate > 0 ) {
    // stochastic
    double num = RND("CalcNewInocHumans");
    double SumOfProb = 0;
    for( r = 0; r <= 150; ++r ) {
      double rfact = Factorial(r);
      if( rfact == 0 ) {
        throw; // STOP
      }
      SumOfProb = SumOfProb + ((pow(InocEstimate,r) * exp(-InocEstimate)) / rfact);
      if( SumOfProb > num ) {
        break;
      }
    }
    NewDlyHumInoc = r;
  }
  else {
    NewDlyHumInoc = 0;
  }
  
  for( int i = 1; i <= NewDlyHumInoc; ++i ) {
    _humanPopulation->InoculateRandomHuman( serotype );
  }
}



void
dsport::SaveDailyOutput(void)
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

  dlo.MosqTotal = MosqTotal;
  for( int i = 1; i <= 4; ++i ) {
    dlo.MosqInfvTotal[i] = MosqInfvTotal[i];
    dlo.NewHumCases[i] = _humanPopulation->GetNewInfectiveBySerotype( i );
  }
  dlo.InfvBites = NewDlyHumInoc;
  for( int i = 1; i <= 4; ++i ) {
    dlo.EIPDevRate[i] = EIPDevRate[i];
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
    _locationLog->AddData( MosqTotal );
    _locationLog->AddData( NewDlyHumInoc );
  }
}



double
dsport::Factorial( int n )
{
  int result = 1;
  for( int i = n; i > 0; --i ) {
    result = result * i;
  }
  return static_cast<double>( result );
}



sim::output::DensimOutput *
dsport::GetDensimOutput(void)
{
  return _densimOutput;
}



double
dsport::GetTotalMosquitoes( MosquitoCollection & collection )
{
  double totalNumber = 0.0;

  for( MosquitoIterator itMosq = collection.begin(); itMosq != collection.end(); ++itMosq ) {
    totalNumber += itMosq->Number;
  }

  return totalNumber;
}



double
dsport::GetTotalMosquitoes( std::vector<MosquitoCollection> & collections )
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
dsport::CalculateDoubleBloodMealProportion( double weight )
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
dsport::GetSusceptibleOvipositingAverageWeight(void)
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
dsport::CombineCohorts( MosquitoCollection & collection, int age, double development )
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



void
dsport::OutputNewMosqSusc(void)
{
  oldLog << "Susceptible Nulliparous" << std::endl;
  for( int i = MaxAgeMosq; i >= 1; --i ) {
    if( NewMosqSusc[i] <= 0 ) continue;
    else {
      oldLog << _currentDate.year() << " , "
             << _currentDate.day_of_year() << " , "
             << i << " , "
             << NewMosqSusc[i] << " , "
             << NewMosqSuscCD[i] << " , "
             //<< _dailyMosData.AverageWeight
             << std::endl;
    }
  }
}



void
dsport::OutputOldMosqSusc(void)
{
  oldLog << "Susceptible Parous" << std::endl;
  for( int i = MaxAgeMosq; i >= 1; --i ) {
    if( OldMosqSusc[i] <= 0 ) continue;
    else {
      oldLog << _currentDate.year() << " , "
             << _currentDate.day_of_year() << " , "
             << i << " , "
             << OldMosqSusc[i] << " , "
             << OldMosqSuscCD[i] << " , "
             //<< _dailyMosData.AverageWeight
             << std::endl;
    }
  }
}



void
dsport::OutputNewMosqInfd(void)
{
  oldLog << "Infected Nulliparous" << std::endl;
  for( int iSerotype = 1; iSerotype <= 4; ++iSerotype ) {
    for( int i = MaxAgeMosq; i >= 1; --i ) {
      if( NewMosqInfd[i][iSerotype] <= 0 ) continue;
      else {
        oldLog << _currentDate.year() << " , "
               << _currentDate.day_of_year() << " , "
               << iSerotype << " , "
               << i << " , "
               << NewMosqInfd[i][iSerotype] << " , "
               << NewMosqInfdCD[i][iSerotype] << " , "
               << NewMosqInfdEIP[i][iSerotype] << " , "
               //<< _dailyMosData.AverageWeight
               << std::endl;
      }
    }
  }
}



void
dsport::OutputOldMosqInfd(void)
{
  oldLog << "Infected Parous" << std::endl;
  for( int iSerotype = 1; iSerotype <= 4; ++iSerotype ) {
    for( int i = MaxAgeMosq; i >= 1; --i ) {
      if( OldMosqInfd[i][iSerotype] <= 0 ) continue;
      else {
        oldLog << _currentDate.year() << " , "
               << _currentDate.day_of_year() << " , "
               << iSerotype << " , "
               << i << " , "
               << OldMosqInfd[i][iSerotype] << " , "
               << OldMosqInfdCD[i][iSerotype] << " , "
               << OldMosqInfdEIP[i][iSerotype] << " , "
               //<< _dailyMosData.AverageWeight
               << std::endl;
      }
    }
  }
}



void
dsport::OutputMosqInfv(void)
{
  oldLog << "Infectives" << std::endl;
  for( int iSerotype = 1; iSerotype <= 4; ++iSerotype ) {
    for( int i = MaxAgeMosq; i >= 1; --i ) {
      if( MosqInfv[i][iSerotype] <= 0 ) continue;
      else {
        oldLog << _currentDate.year() << " , "
               << _currentDate.day_of_year() << " , "
               << iSerotype << " , "
               << i << " , "
               << MosqInfv[i][iSerotype] << " , "
               << MosqInfvCD[i][iSerotype] << " , "
               //<< _dailyMosData.AverageWeight
               << std::endl;
      }
    }
  }
}



void
dsport::OutputSusceptibleNulliparous(void)
{
  newLog << "Susceptible Nulliparous" << std::endl;
  for( MosquitoIterator itMosq = _susceptibleNulliparous.begin(); itMosq != _susceptibleNulliparous.end(); ++itMosq ) {
    newLog << _currentDate.year() << " , "
           << _currentDate.day_of_year() << " , "
           << itMosq->Age << " , "
           << itMosq->Number << " , "
           << itMosq->Development << " , "
           //<< itMosq->Weight
           << std::endl;
  }
}



void
dsport::OutputSusceptibleParous(void)
{
  newLog << "Susceptible Parous" << std::endl;
  for( MosquitoIterator itMosq = _susceptibleParous.begin(); itMosq != _susceptibleParous.end(); ++itMosq ) {
    newLog << _currentDate.year() << " , "
           << _currentDate.day_of_year() << " , "
           << itMosq->Age << " , "
           << itMosq->Number << " , "
           << itMosq->Development << " , "
           //<< itMosq->Weight
           << std::endl;
  }
}



void
dsport::OutputInfectedNulliparous(void)
{
  newLog << "Infected Nulliparous" << std::endl;
  for( int iSerotype = 1; iSerotype <= 4; ++iSerotype ) {
    for( MosquitoIterator itMosq = _infectedNulliparous[iSerotype].begin(); itMosq != _infectedNulliparous[iSerotype].end(); ++itMosq ) {
      newLog << _currentDate.year() << " , "
             << _currentDate.day_of_year() << " , "
             << iSerotype << " , "
             << itMosq->Age << " , "
             << itMosq->Number << " , "
             << itMosq->Development << " , "
             << itMosq->Eip << " , "
             //<< itMosq->Weight
             << std::endl;
    }
  }
}



void
dsport::OutputInfectedParous(void)
{
  newLog << "Infected Parous" << std::endl;
  for( int iSerotype = 1; iSerotype <= 4; ++iSerotype ) {
    for( MosquitoIterator itMosq = _infectedParous[iSerotype].begin(); itMosq != _infectedParous[iSerotype].end(); ++itMosq ) {
      newLog << _currentDate.year() << " , "
             << _currentDate.day_of_year() << " , "
             << iSerotype << " , "
             << itMosq->Age << " , "
             << itMosq->Number << " , "
             << itMosq->Development << " , "
             << itMosq->Eip << " , "
             //<< itMosq->Weight
             << std::endl;
    }
  }
}




void
dsport::OutputInfectives(void)
{
  newLog << "Infectives" << std::endl;
  for( int iSerotype = 1; iSerotype <= 4; ++iSerotype ) {
    for( MosquitoIterator itMosq = _infectives[iSerotype].begin(); itMosq != _infectives[iSerotype].end(); ++itMosq ) {
      newLog << _currentDate.year() << " , "
             << _currentDate.day_of_year() << " , "
             << iSerotype << " , "
             << itMosq->Age << " , "
             << itMosq->Number << " , "
             << itMosq->Development << " , "
             //<< itMosq->Weight
             << std::endl;
    }
  }
}
