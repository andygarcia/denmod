#include "stdafx.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <sstream>
#include "dsport.h"
#include "Location.h"
#include "Population.h"
#include "SimConstants.h"
#include "../output/Workbook.h"

using namespace ds::port;


#define END_YEAR 10


dsport::dsport( Location * location, bool doInfection, bool infectFirstYearOnly, bool useRdsSequences )
: _pdsRng(0),
  GasCoef(1.987f),
  Virus(std::vector<VirusDesc>( 4+1 )),
  EIPFactor(std::vector<float>( 4+1, 0 )),
  TemperatureMax(std::vector<float>( YrLen+1, 0 )),
  TemperatureMin(std::vector<float>( YrLen+1, 0 )),
  TemperatureAvg(std::vector<float>( YrLen+1, 0 )),
  SD(std::vector<float>( YrLen+1, 0 )),
  Rain(std::vector<float>( YrLen+1, 0 )),
  RelHumid(std::vector<float>( YrLen+1, 0 )),
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
  CimSimData(std::vector<CimSimOutDescription>( YrLen+1 )),
  BitesPerPerson(std::vector<float>( YrLen+1, 0 )),
  VirusIntro(std::vector<VirusIntroductionProfile>( 4+1 )),
  AddedInfections(std::vector<std::vector<bool>>( 4+1, std::vector<bool>(YrLen+1,false) )),
  BitersInfdNewDB(std::vector<float>( 4+1, 0 )),
  BitersInfdOldDB(std::vector<float>( 4+1, 0 )),
  BitersInfv(std::vector<float>( 4+1, 0 )),
  EIPDevRate(std::vector<float>( 4+1, 0 )),
  MosqInfvTotal(std::vector<float>( 4+1, 0 ))
{
  //srand( time(NULL) );
  // DENDYNAM.INC

  _humanPopulation = new HumanPopulation( this, location );

  // initialize from location object
  this->VirusIntro = location->VirusIntro;

  this->HumHostDensity = location->HumHostDensity;
  this->ClusterSize = location->ClusterSize;

  this->Virus = location->Virus;
  this->HumToMosLTiter = location->HumToMosLTiter;
  this->HumToMosLInf = location->HumToMosLInf;
  this->HumToMosHTiter = location->HumToMosHTiter;
  this->HumToMosHInf = location->HumToMosHInf;
  this->EipLTiter = location->EipLTiter;
  this->EipLFactor = location->EipLFactor;
  this->EipHTiter = location->EipHTiter;
  this->EipHFactor = location->EipHFactor;
  this->StochTransNum = location->StochTransNum;
  this->MosqToHumProb = location->MosqToHumProb;
  this->EnzKinDR = location->EnzKinDR;
  this->EnzKinEA = location->EnzKinEA;
  this->EnzKinEI = location->EnzKinEI;
  this->EnzKinTI = location->EnzKinTI;

  this->MANADurat = location->MANADurat;
  this->MAEADurat = location->MAEADurat;
  this->HetImmunDurat = location->HetImmunDurat;

  this->PropOnHum = location->PropOnHum;
  this->FdAttempts = location->FdAttempts;
  this->PropDifHost = location->PropDifHost;
  this->PropOutdoor = location->PropOutdoor;
  this->DBloodLWt = location->DBloodLWt;
  this->DBloodUWt = location->DBloodUWt;
  this->DBloodUProp = location->DBloodUProp;
  this->DBloodLProp = location->DBloodLProp;

  this->CimsimDataByYear_ = location->CimsimDataByYear;

  this->NewMosqSusc = location->NewMosqSusc;
  this->NewMosqSuscCD = location->NewMosqSuscCD;

  this->OldMosqSusc = location->OldMosqSusc;
  this->OldMosqSuscCD = location->OldMosqSuscCD;

  this->Weather_ = location->Weather_;

  // initialize infections schedules based on VirusIntro
  for( int i = 1; i <= 4; ++i ) {
    if( VirusIntro[i].Trts > 0 ) {
      AddInfvFlag = doInfection;
      int j = VirusIntro[i].SDay;
      for( int ii = 1; ii <= VirusIntro[i].Trts; ++ii ) {
        AddedInfections[i][j] = true;
        j = j + VirusIntro[i].Intv;
        if( j > YrLen ) {
          break;
        }
      }
    }
  }

  Year = 1;
  SimYear = 0;
  EndYear = END_YEAR;

  LocationOutput_.reserve( END_YEAR * 365 );
}



dsport::~dsport(void)
{
  delete _humanPopulation;  
}



void
dsport::Start(void)
{
  denmain();
}



void
dsport::denmain(void)
{
  do {
    CalculateEipFactors();

    for( Year = 1; Year <= EndYear; ++Year ) {
      ReadWeather( Year );
      ReadMos( Year );
  
      for( Day = 1; Day <= YrLen; ++Day ) {

        _humanPopulation->DoDailyDeaths();
        _humanPopulation->DoDailyBirths();
        _humanPopulation->AgePopulation();

        if( AddInfvFlag && (AddedInfections[1][Day] || AddedInfections[2][Day] || AddedInfections[3][Day] || AddedInfections[4][Day]) ) {
          InitInfectives();
        }

        _humanPopulation->PurgeMaternalAntibodies();

        for( int k = 1; k <=4; ++k ) {
          EIPDevRate[k] = EIPEnzKin(TemperatureAvg[Day] + 273.15f) / EIPFactor[k];
        }

        MosqLifeCycle();
        HumToMosqTrans();
        MosqToHumTrans();

        _humanPopulation->RankPopulation();
        _dailyDebugOutput.CalcDeathsArraySize = static_cast<float>( _humanPopulation->GetPopulationSize() );
        _humanPopulation->PurgeHfDeaths();

        SpoolToDisk();
      }

      SimYear = SimYear + 1;

      if( Year < EndYear ) {
        ReadWeather( Year );
        ReadMos( Year );
      }
    }

    MenuPostSim();

    WriteOutput();

    return;
  } while (true) ;
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
  // Initialize infective mosquitoes for the 4 serotypes
  for( int i = 1; i <= 4; ++i ) {      
    if( AddedInfections[i][Day] && VirusIntro[i].Mosq > 0 ) {
      // look for empty position in the old infected array and add.  This way the
      // new infectives will drop to position 1 in the infective array and
      // become new blood feeders on this day.
      // If no free space is found, then add to last position in the array.
      bool ifound = false;
      for( int j = 1; j <= MaxAgeMosq; ++j ) {
        if( OldMosqInfd[j][i] == 0 ) {
          OldMosqInfd[j][i] = VirusIntro[i].Mosq;
          OldMosqInfdCD[j][i] = 1.1f;
          OldMosqInfdEIP[j][i] = 1.1f;
          ifound = true;
          break;
        }
      }
      if( ifound != true ) {
        // no open position found, accumulate into the oldest cohort of old infecteds
        OldMosqInfd[MaxAgeMosq][i] = OldMosqInfd[MaxAgeMosq][i] + VirusIntro[i].Mosq;
        OldMosqInfdCD[MaxAgeMosq][i] = 1.1f;
        OldMosqInfdEIP[MaxAgeMosq][i] = 1.1f;
      }
    }
  }

  // initialize infective humans
  for( int i = 1; i <= 4; ++i ) {
    if( AddedInfections[i][Day] && VirusIntro[i].Hums > 0 ) {
      for( int j = 1; j <= VirusIntro[i].Hums; ++j ) {
        _humanPopulation->IntroduceInfectedHuman( i );
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
dsport::MosqLifeCycle(void)
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
  
  if( SimYear == 1 && Day == 1 ) {
    // initialize static variables
    BitersInfdNewDB = std::vector<float>( 4+1, 0 );
    BitersInfdOldDB = std::vector<float>( 4+1, 0 );
  }


  // calculate proportion taking a double blood meal
  float DMealProp = 0;
  if( CimSimData[Day].AvgDlyWeight <= DBloodLWt ) {
    DMealProp = DBloodUProp;
  }
  else if( CimSimData[Day].AvgDlyWeight >= DBloodUWt ) {
    DMealProp = DBloodLProp;
  }
  else {
    if( (DBloodUWt - DBloodLWt) == 0 ) {
      throw;  // STOP
    }
    float Slope = (DBloodUProp - DBloodLProp) / (DBloodUWt - DBloodLWt);
    DMealProp = DBloodUProp - ((CimSimData[Day].AvgDlyWeight - DBloodLWt) * Slope);
  }

  _dailyDebugOutput.DMealProp = DMealProp;

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
        NewMosqSusc[i + 1] = NewMosqSusc[i] * CimSimData[Day].OverallSurv;
        NewMosqSuscCD[i + 1] = NewMosqSuscCD[i] + CimSimData[Day].AdultDev;
      }
      else {
        EggersNew = EggersNew + (NewMosqSusc[i] * CimSimData[Day].OverallSurv);
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
  NewMosqSusc[1] = CimSimData[Day].NewDlyFemales * (numberOfHumans / HumHostDensity) * CimSimData[Day].OverallSurv;
  NewMosqSuscCD[1] = CimSimData[Day].AdultDev;
  BitersNew = NewMosqSusc[2] + (NewMosqSusc[3] * DMealProp);

  _dailyDebugOutput.EggersNew = EggersNew;
  _dailyDebugOutput.BitersNew = BitersNew;

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
        OldMosqSusc[i + 1] = OldMosqSusc[i] * CimSimData[Day].OverallSurv;
        OldMosqSuscCD[i + 1] = OldMosqSuscCD[i] + CimSimData[Day].AdultDev;
      }
      else {
        EggersOld = EggersOld + (OldMosqSusc[i] * CimSimData[Day].OverallSurv);
      }
      OldMosqSusc[i] = 0;
      OldMosqSuscCD[i] = 0;
    }
  }

  OldMosqSusc[1] = EggersNew + EggersOld;
  OldMosqSuscCD[1] = CimSimData[Day].AdultDev;
  BitersOld = OldMosqSusc[1] + (OldMosqSusc[2] * DMealProp);

  _dailyDebugOutput.EggersOld = EggersOld;
  _dailyDebugOutput.BitersOld = BitersOld;


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
        float OldAdultDev;
        if( Day == 1 ) {
          OldAdultDev = CimSimData[365].AdultDev;
        }
        else {
          OldAdultDev = CimSimData[Day - 1].AdultDev;
        }

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
          EIPTranNew[j] = EIPTranNew[j] + (NewMosqInfd[i][j] * CimSimData[Day].OverallSurv);
        }
        else {
          NewMosqInfd[i + 1][j] = NewMosqInfd[i][j] * CimSimData[Day].OverallSurv;
          NewMosqInfdCD[i + 1][j] = NewMosqInfdCD[i][j] + CimSimData[Day].AdultDev;
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
          EIPTranOld[j] = EIPTranOld[j] + (OldMosqInfd[i][j] * CimSimData[Day].OverallSurv);
        }
        else {
          OldMosqInfd[i+1][j] = OldMosqInfd[i][j] * CimSimData[Day].OverallSurv;
          if( OldMosqInfdCD[i][j] > .58 ) {
            BitersInfd[j] = BitersInfd[j] + OldMosqInfd[i+1][j];
            BitersInfdOldDB[j] = BitersInfdOldDB[j] + (OldMosqInfd[i+1][j] * DMealProp);
            OldMosqInfdCD[i+1][j] = CimSimData[Day].AdultDev;
          }
          else {
            OldMosqInfdCD[i+1][j] = OldMosqInfdCD[i][j] + CimSimData[Day].AdultDev;
          }
          OldMosqInfdEIP[i+1][j] = OldMosqInfdEIP[i][j] + EIPDevRate[j];
        }
        OldMosqInfd[i][j] = 0;
        OldMosqInfdCD[i][j] = 0;
        OldMosqInfdEIP[i][j] = 0;
      }
    }
  }

  for( int i = 1; i <= 4; ++i ) {
    _dailyDebugOutput.EIPTranNew[i] = EIPTranNew[i];
    _dailyDebugOutput.BitersInfdNewDB[i] = BitersInfdNewDB[i];
    _dailyDebugOutput.EIPTranOld[i] = EIPTranOld[i];
    _dailyDebugOutput.BitersInfdOldDB[i] = BitersInfdOldDB[i];
    _dailyDebugOutput.BitersInfd[i] = BitersInfd[i];
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
          MosqInfv[i+1][j] = MosqInfv[i][j] * CimSimData[Day].OverallSurv;
          MosqInfvCD[i+1][j] = MosqInfvCD[i][j] + CimSimData[Day].AdultDev;
        }
        else {
          EggersInfv[j] = EggersInfv[j] + (MosqInfv[i][j] * CimSimData[Day].OverallSurv);
        }
        MosqInfv[i][j] = 0;
        MosqInfvCD[i][j] = 0;
      }
    }

    _dailyDebugOutput.EggersInfv[j] = EggersInfv[j];

    MosqInfv[1][j] = EggersInfv[j] + EIPTranNew[j] + EIPTranOld[j];
    MosqInfvCD[1][j] = CimSimData[Day].AdultDev;
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

  for( int i = 1; i <=4; ++i ) {
    _dailyDebugOutput.BitersInfv[i] = BitersInfv[i];
    _dailyDebugOutput.MosqInfvTotal[i] = MosqInfvTotal[i];

  }
  _dailyDebugOutput.BitersTotal = BitersTotal;
  _dailyDebugOutput.MosqTotal = MosqTotal;
}



void
dsport::HumToMosqTrans(void)
{
  int numberOfHumans = _humanPopulation->GetPopulationSize();

  // number of susceptible probes per individual
  BitesPerPerson[Day] = (BitersNew + BitersOld) * PropOnHum;
  BitesPerPerson[Day] = BitesPerPerson[Day] + (BitesPerPerson[Day] * (FdAttempts - 1) * PropDifHost);
  BitesPerPerson[Day] = BitesPerPerson[Day] / numberOfHumans;

  // handle dead population gracefully
  if( numberOfHumans == 0 ) {
    BitesPerPerson[Day] = 0;
    return;
  }

  _dailyDebugOutput.BitesPerPerson = BitesPerPerson[Day];

  // randomly calculate new mosquito infections for four serotypes
  std::vector<int> seroTypesCompleted;
  // loop until all four sero types are processed
  while(true) {
    int i = INT( (4 - 1 + 1) * RND("HumToMosqTrans") + 1 );
    std::vector<int>::iterator findResult;
    findResult = std::find( seroTypesCompleted.begin(), seroTypesCompleted.end(), i );
    if( findResult == seroTypesCompleted.end() ) {
      // serotype "i" has not been processed yet
      CalcNewInocMosquitoes(i);
      seroTypesCompleted.push_back(i);
    }
    if( seroTypesCompleted.size() == 4 ) {
      // all 4 serotypes completed
      break;
    }
  }
}



void
dsport::CalcNewInocMosquitoes( int iType )
{
  int r;                    // for poisson distribution
  float InocEstimate;       // Number of mosq to be infected
  int NewDlyMosqInoc;       // actual number of new infected mosq. (differs due to/if stochastic routines enabled)
  //int OldInfd;              // new infected from old susceptible
  int OldInfd = 0;              // new infected from old susceptible
  //int NewInfd;              // new infected from new susceptible
  int NewInfd = 0;              // new infected from new susceptible

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

  InocEstimate = _humanPopulation->GetInfectiveBySerotype(iType) * BitesPerPerson[Day] * ProbInf;
  
  _dailyDebugOutput.MosqInocEstimate[iType] = InocEstimate;

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

  _dailyDebugOutput.NewDlyMosqInoc[iType] = NewDlyMosqInoc;

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
    OldMosqInfdCD[1][iType] = CimSimData[Day].AdultDev;
    NewMosqInfdCD[1][iType] = CimSimData[Day].AdultDev;
    OldMosqInfdEIP[1][iType] = EIPDevRate[iType];
    NewMosqInfdEIP[1][iType] = EIPDevRate[iType];
  }

  _dailyDebugOutput.NewInfd[iType] = NewInfd;
  _dailyDebugOutput.OldInfd[iType] = OldInfd;
}



void
dsport::MosqToHumTrans(void)
{
  // randomly calculate new human infections for four serotypes
  std::vector<int> seroTypesCompleted;
  // loop until all four sero types are processed
  while(true) {
    int iType = INT( (4 - 1 + 1) * RND("MosqToHumTrans") + 1 );
    std::vector<int>::iterator findResult;
    findResult = std::find( seroTypesCompleted.begin(), seroTypesCompleted.end(), iType );
    if( findResult == seroTypesCompleted.end() ) {
      // process serotype, and mark it as done
      CalcNewInocHumans( iType );
      seroTypesCompleted.push_back(iType);
    }
    if( seroTypesCompleted.size() == 4 ) {
      // all 4 serotypes completed
      break;
    }
  }
}




void
dsport::CalcNewInocHumans( int iType )
{
  int r;                      // for poisson distribution
  float InocEstimate;         // number of infv bites to humans

  InocEstimate = ((BitersInfv[iType] * PropOnHum) + ((BitersInfv[iType] * PropOnHum) * (FdAttempts - 1) * PropDifHost)) * MosqToHumProb;

  _dailyDebugOutput.HumInocEstimate[iType] = InocEstimate;

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
  
  _dailyDebugOutput.NewDlyHumInoc[iType] = NewDlyHumInoc;

  for( int i = 1; i <= NewDlyHumInoc; ++i ) {
    _humanPopulation->InnoculateRandomHuman( iType );
  }
}



void
dsport::SpoolToDisk(void)
{
  DiskSpooler DiskData;

  DiskData.Incubate1 = _humanPopulation->GetIncubatingBySerotype( 1 );
  DiskData.Incubate2 = _humanPopulation->GetIncubatingBySerotype( 2 );
  DiskData.Incubate3 = _humanPopulation->GetIncubatingBySerotype( 3 );
  DiskData.Incubate4 = _humanPopulation->GetIncubatingBySerotype( 4 );
      
  DiskData.Viremic1 = _humanPopulation->GetInfectiveBySerotype( 1 );
  DiskData.Viremic2 = _humanPopulation->GetInfectiveBySerotype( 2 );
  DiskData.Viremic3 = _humanPopulation->GetInfectiveBySerotype( 3 );
  DiskData.Viremic4 = _humanPopulation->GetInfectiveBySerotype( 4 );

  DiskData.MosqTotal = MosqTotal;
  for( int i = 1; i <= 4; ++i ) {
    DiskData.MosqInfvTotal[i] = MosqInfvTotal[i];
    DiskData.NewHumCases[i] = _humanPopulation->GetNewInfectiveBySerotype( i );
  }
  DiskData.InfvBites = NewDlyHumInoc;
  for( int i = 1; i <= 4; ++i ) {
    DiskData.EIPDevRate[i] = EIPDevRate[i];
  }
  DiskData.NumHumans = _humanPopulation->GetPopulationSize();

  HumanPopulation::ClassSpecificSeroprevalence css = _humanPopulation->GetClassSpecificSeroprevalence();
  for( int i = 1; i <= 23; ++i ) {
    for( int j = 1; j <= 4; ++j ) {
      DiskData.SerPos[i][j] = css[i][j];
    }
  }

  HumanPopulation::DailySequentialInfections dsi = _humanPopulation->GetDailySequentialInfections();
  DiskData.SeqInfVals.F1T2 = dsi[D1][D2];
  DiskData.SeqInfVals.F1T3 = dsi[D1][D3];
  DiskData.SeqInfVals.F1T4 = dsi[D1][D4];
  DiskData.SeqInfVals.F2T1 = dsi[D2][D1];
  DiskData.SeqInfVals.F2T3 = dsi[D2][D3];
  DiskData.SeqInfVals.F2T4 = dsi[D2][D4];
  DiskData.SeqInfVals.F3T1 = dsi[D3][D1];
  DiskData.SeqInfVals.F3T2 = dsi[D3][D2];
  DiskData.SeqInfVals.F3T4 = dsi[D3][D4];
  DiskData.SeqInfVals.F4T1 = dsi[D4][D1];
  DiskData.SeqInfVals.F4T2 = dsi[D4][D2];
  DiskData.SeqInfVals.F4T3 = dsi[D4][D3];
  DiskData.SeqInfVals.FMT1 = dsi[Maternal][D1];
  DiskData.SeqInfVals.FMT2 = dsi[Maternal][D2];
  DiskData.SeqInfVals.FMT3 = dsi[Maternal][D3];
  DiskData.SeqInfVals.FMT4 = dsi[Maternal][D4];

  DiskData._debugOutput = _dailyDebugOutput;

  LocationOutput_.push_back( DiskData );
}



void
dsport::ReadWeather( int year )
{
  using namespace csinput;

  WeatherYear * wy = Weather_->GetWeatherForIndex(year);

  for( int i = 1; i <= YrLen; i++ ) {
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
dsport::ReadMos( int year )
{
  this->CimSimData = CimsimDataByYear_[year];
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



void
dsport::MenuPostSim()
{
}



void
dsport::WriteOutput()
{
  unsigned int days = static_cast<unsigned int>( LocationOutput_.size() );

  // create location worksheet
  std::vector<std::string> headers;
  headers.push_back( "Day" );
  headers.push_back( "Simulation Area" );
  headers.push_back( "Mosquitoes In Area" );
  headers.push_back( "Mosquitoes Per Hectare" );
  headers.push_back( "Mosquitoes Per Person" );
  headers.push_back( "Mosquito Wet Weight" );
  headers.push_back( "Mosquito Survival" );
  headers.push_back( "Infective Bites" );
  headers.push_back( "CalcDeathsArraySize" );
  headers.push_back( "CalcBirthsArraySize" );
  headers.push_back( "InitInfectivesArraySize" );
  headers.push_back( "DMealProp" );
  headers.push_back( "EggersNew" );
  headers.push_back( "BitersNew" );
  headers.push_back( "EggersOld" );
  headers.push_back( "BitersOld" );
  headers.push_back( "BitersTotal" );
  headers.push_back( "MosqTotal" );
  headers.push_back( "BitesPerPerson" );

  Worksheet * location = new Worksheet( "Location", headers );

  // create serotype worksheets
  headers.clear();
  headers.push_back( "Day" );
  headers.push_back( "EIP Development Rate" );
  headers.push_back( "Infective Mosquitoes" );
  headers.push_back( "Persons Incubating" );
  headers.push_back( "Persons Viremic" );
  headers.push_back( "Persons With Virus" );
  headers.push_back( "New Cases" );
  headers.push_back( "MANA Infants" );
  headers.push_back( "MAEA Infants" );
  headers.push_back( "< 1 year" );
  headers.push_back( "1-4 years" );
  headers.push_back( "5-9 years" );
  headers.push_back( "10-14 years" );
  headers.push_back( "15-19 years" );
  headers.push_back( "20-24 years" );
  headers.push_back( "25-29 years" );
  headers.push_back( "30-34 years" );
  headers.push_back( "35-39 years" );
  headers.push_back( "40-44 years" );
  headers.push_back( "45-49 years" );
  headers.push_back( "50-54 years" );
  headers.push_back( "55-59 years" );
  headers.push_back( "60-64 years" );
  headers.push_back( "65-69 years" );
  headers.push_back( "70-74 years" );
  headers.push_back( "75-79 years" );
  headers.push_back( "80+ years" );
  headers.push_back( "15-44 years" );
  headers.push_back( "45+ years" );
  headers.push_back( "All ages" );
  headers.push_back( "EIPTranNew" );
  headers.push_back( "BitersInfdNewDB" );
  headers.push_back( "EIPTranOld" );
  headers.push_back( "BitersInfdOldDB" );
  headers.push_back( "BitersInfd" );
  headers.push_back( "EggersInfv" );
  headers.push_back( "BitersInfv" );
  headers.push_back( "MosqInfvTotal" );
  headers.push_back( "MosqInocEstimate" );
  headers.push_back( "NewDlyMosqInoc" );
  headers.push_back( "NewInfd" );
  headers.push_back( "OldInfd" );
  headers.push_back( "HumInocEstimate" );
  headers.push_back( "NewDlyHumInoc" );

  std::vector<Worksheet*> serotypes;
  for( int i = 1; i <=4; ++i ) {
    std::stringstream ss;
    ss << "Dengue " << i;
    std::string title = ss.str();
    serotypes.push_back( new Worksheet( title, headers ) );
  }

  for( unsigned int i = 1; i <= days; ++i ) {
    // get output for this day
    DailyLocationOutput & dlo = LocationOutput_[i-1];
    int year = static_cast<int>( ceil(i / 365.0));
    int day = i - ((year - 1) * 365);

    float simulationArea = dlo.NumHumans / HumHostDensity;
    float mosquitoesInArea = dlo.MosqTotal;
    float mosquitoesPerHectare = dlo.MosqTotal / simulationArea;
    float mosquitoesPerPerson = dlo.MosqTotal / dlo.NumHumans;
    float mosquitoWetWeight = CimsimDataByYear_[year][day].AvgDlyWeight;
    float mosquitoSurvival = CimsimDataByYear_[year][day].OverallSurv;
    int infectiveBites = dlo.InfvBites;

    float calcDeathsArraySize = dlo._debugOutput.CalcDeathsArraySize;
    float calcBirthsArraySize = dlo._debugOutput.CalcBirthsArraySize;
    float initInfectivesArraySize = dlo._debugOutput.InitInfectivesArraySize;
    float dMealProp = dlo._debugOutput.DMealProp;
    float eggersNew = dlo._debugOutput.EggersNew;
    float bitersNew = dlo._debugOutput.BitersNew;
    float eggersOld = dlo._debugOutput.EggersOld;
    float bitersOld = dlo._debugOutput.BitersOld;
    float bitersTotal = dlo._debugOutput.BitersTotal;
    float mosqTotal = dlo._debugOutput.MosqTotal;
    float bitesPerPerson = dlo._debugOutput.BitesPerPerson;

    // push to log
    *location << i << simulationArea << mosquitoesInArea << mosquitoesPerHectare << mosquitoesPerPerson
             << mosquitoWetWeight << mosquitoSurvival << infectiveBites
             << calcDeathsArraySize << calcBirthsArraySize << initInfectivesArraySize
             << dMealProp << eggersNew << bitersNew << eggersOld << bitersOld
             << bitersTotal << mosqTotal << bitesPerPerson;


    // kludges for iteration
    float Incubating[5];
    Incubating[1] = dlo.Incubate1;
    Incubating[2] = dlo.Incubate2;
    Incubating[3] = dlo.Incubate3;
    Incubating[4] = dlo.Incubate4;
    float Viremic[5];
    Viremic[1] = dlo.Viremic1;
    Viremic[2] = dlo.Viremic2;
    Viremic[3] = dlo.Viremic3;
    Viremic[4] = dlo.Viremic4;

    // serotype output for this day
    for( int j = 1; j <=4; ++j ) {
      // current serotype's worksheet
      Worksheet & seroWorksheet = *serotypes[j-1];

      // get output
      float eipDevRate = dlo.EIPDevRate[j];
      float infectiveMosquitoes = dlo.MosqInfvTotal[j];
      float incubating = Incubating[j];
      float viremic = Viremic[j];
      float withVirus = Incubating[j] + Viremic[j];
      float newCases = dlo.NewHumCases[j];
      float detailedSerologies[24];
      for( int k = 1; k <= 23; ++k ) {
        detailedSerologies[k] =  dlo.SerPos[k][j];
      }

      float EIPTranNew = dlo._debugOutput.EIPTranNew[j];
      float BitersInfdNewDB = dlo._debugOutput.BitersInfdNewDB[j];
      float EIPTranOld = dlo._debugOutput.EIPTranOld[j];
      float BitersInfdOldDB = dlo._debugOutput.BitersInfdOldDB[j];
      float BitersInfd = dlo._debugOutput.BitersInfd[j];
      float EggersInfv = dlo._debugOutput.EggersInfv[j];
      float BitersInfv = dlo._debugOutput.BitersInfv[j];
      float MosqInfvTotal = dlo._debugOutput.MosqInfvTotal[j];
      float MosqInocEstimate = dlo._debugOutput.MosqInocEstimate[j];
      float NewDlyMosqInoc = dlo._debugOutput.NewDlyMosqInoc[j];
      float NewInfd = dlo._debugOutput.NewInfd[j];
      float OldInfd = dlo._debugOutput.OldInfd[j];
      float HumInocEstimate = dlo._debugOutput.HumInocEstimate[j];
      float NewDlyHumInoc = dlo._debugOutput.NewDlyHumInoc[j];


      seroWorksheet << i << eipDevRate << infectiveMosquitoes << incubating << viremic << withVirus << newCases;
      for( int k = 1; k <= 23; ++k ) {
        seroWorksheet << detailedSerologies[k];
      }
      seroWorksheet << EIPTranNew << BitersInfdNewDB << EIPTranOld << BitersInfdOldDB << BitersInfd
                    << EggersInfv << BitersInfv << MosqInfvTotal
                    << MosqInocEstimate << NewDlyMosqInoc << NewInfd << OldInfd
                    << HumInocEstimate << NewDlyHumInoc;

    }
  }

  Workbook wb( "dsport r.237" );
  wb.AddWorksheet( location );
  for( std::vector<Worksheet*>::iterator itWs = serotypes.begin(); itWs != serotypes.end(); ++itWs ) {
    wb.AddWorksheet( *itWs );
  }
  wb.SaveToDisk( "DSR 3.0 - Location and Serotypes.xml" );


  // create demographics worksheet
  headers.clear();
  headers.push_back( "Class" );
  headers.push_back( "Initial age distribution" );
  headers.push_back( "Initial percentages" );
  headers.push_back( "Births" );
  headers.push_back( "Birth percentages" );
  headers.push_back( "Deaths" );
  headers.push_back( "Death percentages" );
  headers.push_back( "Final age distribution" );
  headers.push_back( "Final percentages" );
  Worksheet * demographics = new Worksheet( "Demographics", headers );


  std::vector<int> initAgeDist = _humanPopulation->GetInitialAgeDistribution();
  std::vector<float> initAgeProp = _humanPopulation->GetInitialAgeProportions();
  std::vector<int> ageDist = _humanPopulation->GetAgeDistribution();
  std::vector<float> ageProp = _humanPopulation->GetAgeProportions();

  std::vector<int> births = _humanPopulation->GetBirthsByClass();
  std::vector<float> birthPercentages = _humanPopulation->GetBirthPercentagesByClass();
  std::vector<int> deaths = _humanPopulation->GetDeathsByClass();
  std::vector<float> deathPercentages = _humanPopulation->GetDeathPercentagesByClass();

  for( int i = 1; i <= 18; ++i ) {

    Worksheet & ws = *demographics;
    ws << i;
    ws << initAgeDist[i];
    ws << initAgeProp[i];
    ws << births[i];
    ws << birthPercentages[i];
    ws << deaths[i];
    ws << deathPercentages[i];
    ws << ageDist[i];
    ws << ageProp[i];
  }

  Workbook demoWorkbook( "dsport r.237" );
  demoWorkbook.AddWorksheet( demographics );
  demoWorkbook.SaveToDisk( "DSR 3.0 - Demographics.xml" );


  // create serology worksheet
  headers.clear();
  headers.push_back( "Class" );
  std::stringstream ss;
  for( int i = 1; i <=4; ++i ) {
    ss.str("");
    ss << "Dengue " << i << " Initial Distribution";
    headers.push_back( ss.str() );

    ss.str("");
    ss << "Dengue " << i << " Initial Distribution Percentage";
    headers.push_back( ss.str() );
  }
  for( int i = 1; i <=4; ++i ) {
    ss.str("");
    ss << "Dengue " << i << " Final Distribution";
    headers.push_back( ss.str() );

    ss.str("");
    ss << "Dengue " << i << " Final Distribution Percentage";
    headers.push_back( ss.str() );
  }

  Worksheet * serologyWorksheet = new Worksheet( "Serology", headers );

  std::vector<std::vector<int>> initSerDist = _humanPopulation->GetInitialSeroDistribution();
  std::vector<std::vector<int>> serDist = _humanPopulation->GetSeroDistribution();

  for( int i = 1; i <= 18; ++i ) {
    *serologyWorksheet << i;
    for( int j = 1; j <= 4; ++j ) {
      *serologyWorksheet << initSerDist[i][j];
      *serologyWorksheet << static_cast<float>( initSerDist[i][j] ) / static_cast<float>( initAgeDist[i] ) * 100;
    }
    for( int j = 1; j <= 4; ++j ) {
      *serologyWorksheet << serDist[i][j];
      *serologyWorksheet << static_cast<float>( serDist[i][j] ) / static_cast<float>( ageDist[i] ) * 100;
    }
  }

  Workbook serologyWorkbook( "dsport r.237" );
  serologyWorkbook.AddWorksheet( serologyWorksheet );
  serologyWorkbook.SaveToDisk( "DSR 3.0 - Serology.xml" );
}
