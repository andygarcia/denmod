#include "stdafx.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <sstream>
#include "dsport.h"
#include "Population.h"
#include "SimConstants.h"

using namespace sim::dsport;



dsport::dsport( const input::Location * location, sim::output::MosData * mosData, bool doDiskOutput )
: _location(location),
  _mosData(mosData),
  _doDiskOutput(doDiskOutput),
  GasCoef(1.987f),
  Virus(std::vector<VirusDesc>( 4+1 )),
  EIPFactor(std::vector<float>( 4+1, 0 )),
  NewMosqSusc(std::vector<float>( (MaxAgeMosq+1) + 1, 0 )),
  NewMosqSuscCD(std::vector<float>( (MaxAgeMosq+1) + 1, 0 )),
  OldMosqSusc(std::vector<float>( (MaxAgeMosq+1) + 1, 0 )),
  OldMosqSuscCD(std::vector<float>( (MaxAgeMosq+1) + 1, 0 )),
  NewMosqInfd(std::vector<std::vector<float>>( (MaxAgeMosq+1) + 1, std::vector<float>( 4+1, 0 ) )),
  NewMosqInfdCD(std::vector<std::vector<float>>( (MaxAgeMosq+1) + 1, std::vector<float>( 4+1, 0 ) )),
  NewMosqInfdEIP(std::vector<std::vector<float>>( (MaxAgeMosq+1) + 1, std::vector<float>( 4+1, 0 ) )),
  OldMosqInfd(std::vector<std::vector<float>>( (MaxAgeMosq+1) + 1, std::vector<float>( 4+1, 0 ) )),
  OldMosqInfdCD(std::vector<std::vector<float>>( (MaxAgeMosq+1) + 1, std::vector<float>( 4+1, 0 ) )),
  OldMosqInfdEIP(std::vector<std::vector<float>>( (MaxAgeMosq+1) + 1, std::vector<float>( 4+1, 0 ) )),
  MosqInfv(std::vector<std::vector<float>>( (MaxAgeMosq+1) + 1, std::vector<float>( 4+1, 0 ) )),
  MosqInfvCD(std::vector<std::vector<float>>( (MaxAgeMosq+1) + 1, std::vector<float>( 4+1, 0 ) )),
  BitersInfdNewDB(std::vector<float>( 4+1, 0 )),
  BitersInfdOldDB(std::vector<float>( 4+1, 0 )),
  BitersInfv(std::vector<float>( 4+1, 0 )),
  EIPDevRate(std::vector<float>( 4+1, 0 )),
  MosqInfvTotal(std::vector<float>( 4+1, 0 ))
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
  this->DBloodLProp = _location->Biology_->Adult->DoubleBloodMeal->LowWeightRatio;
  this->DBloodUWt = _location->Biology_->Adult->DoubleBloodMeal->HighWeightLimit;
  this->DBloodUProp = _location->Biology_->Adult->DoubleBloodMeal->HighWeightRatio;

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
}



dsport::~dsport(void)
{
  if( _doDiskOutput ) {
    _locationLog->Write();
    delete _locationLog;
  }

  delete _humanPopulation;  
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

    // advance mosquitoes
    MosquitoLifeCycle();

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
      float Slope = (EipLFactor - EipHFactor) / (EipHTiter - EipLTiter);
      EIPFactor[i] = EipLFactor - (Virus[i].Viremia - EipLTiter) * Slope;
    }
  }
}



// emulate DS 1.0 CINT() which does banker's rounding
int
dsport::CINT( float value )
{
  float absoluteValue = std::abs( value );
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
dsport::INT( float value )
{
  return (int)floor(value);
}



// emulate PDS 7.1 RND
// PDS 7.1 RND returns single precision values in the range of [0,1)
// the only problem with our emulation is the exclusion of
// ( RAND_MAX/(RAND_MAX+1), 1 ) from the range of generation
float
dsport::RND(std::string callingMethod)
{
  if( EMULATE_PDS_RAND ) {
    float nextRnd = _pdsRng.Next();
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
          break;
        }
      }
      if( ifound != true ) {
        // no open position found, accumulate into the oldest cohort of old infecteds
        OldMosqInfd[MaxAgeMosq][serotype] = OldMosqInfd[MaxAgeMosq][serotype] + serotypeIntro->Mosquitoes_;
        OldMosqInfdCD[MaxAgeMosq][serotype] = 1.1f;
        OldMosqInfdEIP[MaxAgeMosq][serotype] = 1.1f;
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



float
dsport::EIPEnzKin( float temp )
{
  float TempExpr1 = (EnzKinEA / GasCoef) * ((1 / (float) 298) - (1 / temp));
  float TempExpr2 = (EnzKinEI / GasCoef) * ((1 / EnzKinTI) - (1 / temp));

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

  float Numerator = EnzKinDR * (temp / 298) * exp(TempExpr1);
  float Denominator = 1 + exp(TempExpr2);
  return (Numerator / Denominator) * 24;
}



void
dsport::MosquitoLifeCycle(void)
{
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

  std::vector<float> BitersInfd( 4+1, 0 );        // infected biters
  std::vector<float> EIPTranNew( 4+1, 0 );        // Infective class from infected new
  std::vector<float> EIPTranOld( 4+1, 0 );        // Infective class from infected old
  std::vector<float> EggersInfv( 4+1, 0 );        // Infective egg transfers
  BitersInfv = std::vector<float>( 4+1, 0 );      // total infective biters
  
  if( _currentDate == _startDate )  {
    // initialize static variables
    BitersInfdNewDB = std::vector<float>( 4+1, 0 );
    BitersInfdOldDB = std::vector<float>( 4+1, 0 );
  }


  // calculate proportion taking a double blood meal
  float DMealProp = 0;
  if( _dailyMosData.AverageWeight <= DBloodLWt ) {
    DMealProp = DBloodUProp;
  }
  else if( _dailyMosData.AverageWeight >= DBloodUWt ) {
    DMealProp = DBloodLProp;
  }
  else {
    if( (DBloodUWt - DBloodLWt) == 0 ) {
      throw;  // STOP
    }
    float Slope = (DBloodUProp - DBloodLProp) / (DBloodUWt - DBloodLWt);
    DMealProp = DBloodUProp - ((_dailyMosData.AverageWeight - DBloodLWt) * Slope);
  }

  // Advance Susceptibles - First Gonotrophic Cycle
  // Last position in the array does not accumulate
  BitersNew = 0;
  float EggersNew = 0;
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

  // Advance Susceptibles - Successive Gonotrophic Cycles
  // Last position in the array does not accumulate
  BitersOld = 0;
  float EggersOld = 0;
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

  // Advance infected - From New Mosquitoes - First and successive Gonotrophic Cycles
  // Last position in the array does not accumumlate
  for( int j = 1; j <= 4; ++j ) {
    BitersInfd[j] = BitersInfdNewDB[j];
    BitersInfdNewDB[j] = 0;
    for( int i = MaxAgeMosq; i >= 1; --i ) {
      if( NewMosqInfd[i][j] <= 0 ) {
        continue; //go to next cohort
      }
      else {
        // calculate CD cutoff
        float OldAdultDev = _yesterdayMosData.AdultDevelopment;

        // superceeded by using _yesterdayMosData & _dailyMosData
        //if( Day == 1 ) {
        //  OldAdultDev = _yesterdayMosData.AdultDevelopment;
        //}
        //else {
        //  OldAdultDev = _yesterdayMosData.AdultDevelopment;
        //}

        float CDYest = NewMosqInfdCD[i][j] - OldAdultDev;
        float CDTest;
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

  BitersTotal = BitersNew + BitersOld;
  for( int j =1; j <= 4; ++j ) {
    BitersTotal = BitersTotal + BitersInfd[j] + BitersInfv[j];
  }
  MosqTotal = 0;
  MosqInfvTotal = std::vector<float>( 4+1, 0 );
  for( int i = 1; i <= MaxAgeMosq; ++i ) {
    MosqTotal = MosqTotal + NewMosqSusc[i] + OldMosqSusc[i];
    for( int j =1; j <= 4; ++j ) {
      MosqTotal = MosqTotal + NewMosqInfd[i][j] + OldMosqInfd[i][j] + MosqInfv[i][j];
      MosqInfvTotal[j] = MosqInfvTotal[j] + MosqInfv[i][j];
    }
  }
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
}



void
dsport::InoculateMosquitoes( int iType )
{
  int r;                    // for poisson distribution
  float InocEstimate;       // number of mosquitoes to be infected
  int NewDlyMosqInoc;       // actual number of new infected mosq. (differs due to/if stochastic routines enabled)
  int OldInfd = 0;          // new infected from old susceptible
  int NewInfd = 0;          // new infected from new susceptible

  // calculate probability of infection and  estimate newly inoculated mosquitoes
  // Viremia is in scientific notation and Titers are in logs
  float ProbInf = 0;
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
    float Slope = (HumToMosHInf - HumToMosLInf) / (HumToMosHTiter - HumToMosLTiter);
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
    float num = RND("CalcNewInocMosquitoes");
    float SumOfProb = 0;
    for( r = 0; r <= 150; ++r ) {
      float rfact = Factorial(r);
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

    // calculate new infected from new and old susceptible
    OldInfd = CINT( (BitersOld / (BitersOld + BitersNew)) * NewDlyMosqInoc );
    NewInfd = NewDlyMosqInoc - OldInfd;

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
  }
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
  float InocEstimate;         // number of infv bites to humans

  InocEstimate = ((BitersInfv[serotype] * PropOnHum) + ((BitersInfv[serotype] * PropOnHum) * (FdAttempts - 1) * PropDifHost)) * MosqToHumProb;

  if( InocEstimate > StochTransNum ) {
    // discrete
    NewDlyHumInoc = CINT( InocEstimate );
  }

  else if( InocEstimate > 0 ) {
    // stochastic
    float num = RND("CalcNewInocHumans");
    float SumOfProb = 0;
    for( r = 0; r <= 150; ++r ) {
      float rfact = Factorial(r);
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



float
dsport::Factorial( int n )
{
  int result = 1;
  for( int i = n; i > 0; --i ) {
    result = result * i;
  }
  return static_cast<float>( result );
}



sim::output::DensimOutput *
dsport::GetDensimOutput(void)
{
  return _densimOutput;
}
