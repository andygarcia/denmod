#include "stdafx.h"
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include "dsport.h"
#include "Location.h"


using namespace ds::port;


dsport::dsport( Location * location )
: GasCoef(1.987f)
{
  // DENDYNAM.INC
  CumDeaths = std::vector<float>( 18+1, 0 );
  CumBirths = std::vector<float>( 18+1, 0 );

  TotDeaths = std::vector<int>( 18+1, 0 );
  TotBirths = std::vector<int>( 18+1, 0 );

  Indiv = std::vector<int>( MaxPopSize+1, 0 );
  Deng1 = std::vector<int>( MaxPopSize+1, 0 );
  Deng2 = std::vector<int>( MaxPopSize+1, 0 );
  Deng3 = std::vector<int>( MaxPopSize+1, 0 );
  Deng4 = std::vector<int>( MaxPopSize+1, 0 );

  AgeDistr = std::vector<int>( 18+1, 0 );
  InitAgeDistr = std::vector<int>( 18+1, 0 );
  PopProp = std::vector<HumanDemo>( 18+1 );

  SerProp = std::vector<std::vector<float>>( 18+1, std::vector<float>(4+1) );
  SerDistr = std::vector<std::vector<int>>( 18+1, std::vector<int>(4+1, 0) );
  InitSerDistr = std::vector<std::vector<int>>( 18+1, std::vector<int>(4+1, 0) );

  Incub = std::vector<std::vector<int>>( 18+1, std::vector<int>( 4+1, 0 ) );
  Infective = std::vector<std::vector<int>>( 18+1, std::vector<int>( 4+1, 0 ) );
  HomImm = std::vector<std::vector<int>>( 18+1, std::vector<int>( 4+1, 0 ) );
  HetImm = std::vector<std::vector<int>>( 18+1, std::vector<int>( 4+1, 0 ) );
  MatAnti = std::vector<MaternalTransmission>( 4+1 );
  CumHFDeaths = std::vector<float>( 15+1, 0 );

  TotDlyIncub = std::vector<int>( 4+1, 0 );
  TotDlyInfective = std::vector<int>( 4+1, 0 );
  TotDlyHomImm = std::vector<int>( 4+1, 0 );
  TotDlyHetImm = std::vector<int>( 4+1, 0 );
  NewDlyInfective = std::vector<int>( 4+1, 0 );

  Virus = std::vector<VirusDesc>( 4+1 );

  TemperatureMax = std::vector<float>( YrLen+1, 0 );
  TemperatureMin = std::vector<float>( YrLen+1, 0 );
  TemperatureAvg = std::vector<float>( YrLen+1, 0 );
  SD = std::vector<float>( YrLen+1, 0 );
  Rain = std::vector<float>( YrLen+1, 0 );
  RelHumid = std::vector<float>( YrLen+1, 0 );

  NewMosqSusc = std::vector<float>( (MaxAgeMosq+1) + 1, 0 );
  NewMosqSuscCD = std::vector<float>( (MaxAgeMosq+1) + 1, 0 );
  OldMosqSusc = std::vector<float>( (MaxAgeMosq+1) + 1, 0 );
  OldMosqSuscCD = std::vector<float>( (MaxAgeMosq+1) + 1, 0 );

  NewMosqInfd = std::vector<std::vector<float>>( (MaxAgeMosq+1) + 1, std::vector<float>( 4+1, 0 ) );
  NewMosqInfdCD = std::vector<std::vector<float>>( (MaxAgeMosq+1) + 1, std::vector<float>( 4+1, 0 ) );
  NewMosqInfdEIP = std::vector<std::vector<float>>( (MaxAgeMosq+1) + 1, std::vector<float>( 4+1, 0 ) );

  OldMosqInfd = std::vector<std::vector<float>>( (MaxAgeMosq+1) + 1, std::vector<float>( 4+1, 0 ) );
  OldMosqInfdCD = std::vector<std::vector<float>>( (MaxAgeMosq+1) + 1, std::vector<float>( 4+1, 0 ) );
  OldMosqInfdEIP = std::vector<std::vector<float>>( (MaxAgeMosq+1) + 1, std::vector<float>( 4+1, 0 ) );

  MosqInfv = std::vector<std::vector<float>>( (MaxAgeMosq+1) + 1, std::vector<float>( 4+1, 0 ) );
  MosqInfvCD = std::vector<std::vector<float>>( (MaxAgeMosq+1) + 1, std::vector<float>( 4+1, 0 ) );

  CimSimData = std::vector<CimSimOutDescription>( YrLen+1 );
  BitesPerPerson = std::vector<float>( YrLen+1, 0 );

  MAEAInfPrms = std::vector<MAEAInfectionParms>( 4+1 );
  SeqInfPrms = std::vector<SequentialInfectionParms>( 12+1 );

  VirusIntro = std::vector<VirusIntroductionProfile>( 4+1 );
  AddedInfections = std::vector<std::vector<bool>>( 4+1, std::vector<bool>(YrLen+1,false) );

  BitersInfdNewDB = std::vector<float>( 4+1, 0 );
  BitersInfdOldDB = std::vector<float>( 4+1, 0 );
  BitersInfv = std::vector<float>( 4+1, 0 );

  EIPDevRate = std::vector<float>( 4+1, 0 );
  MosqInfvTotal = std::vector<float>( 4+1, 0 );

  // initialize from location object
  this->VirusIntro = location->VirusIntro;
  this->SeqInfPrms = location->SeqInfPrms;
  this->MAEAInfPrms = location->MAEAInfPrms;

  this->PopProp = location->PopProp;
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

  this->SerProp = location->SerProp;
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
      AddInfvFlag = true;
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

}




void
dsport::Start(void)
{
  denmain();
}



void
dsport::denmain(void)
{
  //DiskSpooler DiskData;
  int SpRecNum;

  std::vector<float> Datum1 = std::vector<float>( YrLen+1, 0 );
  std::vector<float> Datum2 = std::vector<float>( YrLen+1, 0 );
  std::vector<float> Datum3 = std::vector<float>( YrLen+1, 0 );
  std::vector<float> Datum4 = std::vector<float>( YrLen+1, 0 );

  DefineAgeClass();

  // Program.Start

  // TextGraphParms() - loads color/graph environment
  ReadDefaultParms();
  //LocReadData() - reads location's binary record
  LocAssignData();

  MainInitialization();

  InitAgeClasses();

  InitSeroprevalence();

  // main loops

  do {

    // calculate EIP by titer
    //REDIM EIPFactor(1 TO 4)
    std::vector<float> EIPFactor = std::vector<float>( 4+1, 0 );
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

    SpRecNum = 0;
    for( Year = 1; Year <= EndYear; ++Year ) {
      ReadWeather( Year );
      ReadMos( Year );
  
      // IF DisplayGraphics THEN CALL GraphMainPlot(False, True, Datum1(), Datum2(), Datum3(), Datum4(), JulDay)

      for( Day = 1; Day <= YrLen; ++Day ) {
        CalcDeaths( CumDeaths );
        CalcBirths( CumBirths );

        // age population
        for( int k = 1; k <= ArraySize; ++k ) {
          Indiv[k] = Indiv[k] + 1;                   
          if( Indiv[k] > AgeClass[18].LDay ) {
            Indiv[k] = AgeClass[18].LDay;           // don't age individuals older than limits of oldest class
          }
        }

        if( AddInfvFlag && (AddedInfections[1][Day] || AddedInfections[2][Day] || AddedInfections[3][Day] || AddedInfections[4][Day]) ) {
          InitInfectives();
        }

        PurgeMaternal(MANADurat + MAEADurat);

        for( int k = 1; k <=4; ++k ) {
          if( EIPFactor[k] == 0 ) {
            // STOP
          }
          EIPDevRate[k] = EIPEnzKin(TemperatureAvg[Day] + EIPTempAdjust + 273.15f) / EIPFactor[k];
        }

        MosqLifeCycle();

        HumToMosqTrans();

        MosqToHumTrans(AgeClass[18].FDay);

        RankPop();
        PurgeHFDeaths();

        //graph data
        //Datum1(Day) = 0     'Dengue 1
        //Datum2(Day) = 0     'Dengue 2
        //Datum3(Day) = 0     'Dengue 3
        //Datum4(Day) = 0     'Dengue 4
        //FOR i = 1 TO 18
        //  Datum1(Day) = Datum1(Day) + Infective(i, 1)
        //  Datum2(Day) = Datum2(Day) + Infective(i, 2)
        //  Datum3(Day) = Datum3(Day) + Infective(i, 3)
        //  Datum4(Day) = Datum4(Day) + Infective(i, 4)
        //NEXT

        Datum1[Day] = TotDlyInfective[1] + TotDlyIncub[1];   // Dengue 1
        Datum2[Day] = TotDlyInfective[2] + TotDlyIncub[2];   // Dengue 2
        Datum3[Day] = TotDlyInfective[3] + TotDlyIncub[3];   // Dengue 3
        Datum4[Day] = TotDlyInfective[4] + TotDlyIncub[4];   // Dengue 4
        if( ArraySize == 0 ) {
          throw; // STOP
        }
        Datum1[Day] = Datum1[Day] / ArraySize * 100;
        Datum2[Day] = Datum2[Day] / ArraySize * 100;
        Datum3[Day] = Datum3[Day] / ArraySize * 100;
        Datum4[Day] = Datum4[Day] / ArraySize * 100;


        SpoolToDisk( SpRecNum );
        SpRecNum++;
      }

      SimYear = SimYear + 1;

      if( Year < EndYear ) {
        ReadWeather( Year );
        ReadMos( Year );
      }
    }

    MenuPostSim();

    return;
  } while (true) ;
}



void
dsport::DefineAgeClass(void)
{
  AgeClass[1].Rank = 1;
  AgeClass[1].FDay = 1;
  AgeClass[1].LDay = 364;

  AgeClass[2].Rank = 2;
  AgeClass[2].FDay = 365;
  AgeClass[2].LDay = 1824;

  AgeClass[3].Rank = 3;
  AgeClass[3].FDay = 1825;
  AgeClass[3].LDay = 3649;

  AgeClass[4].Rank = 4;
  AgeClass[4].FDay = 3650;
  AgeClass[4].LDay = 5474;

  AgeClass[5].Rank = 5;
  AgeClass[5].FDay = 5475;
  AgeClass[5].LDay = 7299;

  AgeClass[6].Rank = 6;
  AgeClass[6].FDay = 7300;
  AgeClass[6].LDay = 9124;

  AgeClass[7].Rank = 7;
  AgeClass[7].FDay = 9125;
  AgeClass[7].LDay = 10949;

  AgeClass[8].Rank = 8;
  AgeClass[8].FDay = 10950;
  AgeClass[8].LDay = 12774;

  AgeClass[9].Rank = 9;
  AgeClass[9].FDay = 12775;
  AgeClass[9].LDay = 14599;

  AgeClass[10].Rank = 10;
  AgeClass[10].FDay = 14600;
  AgeClass[10].LDay = 16424;

  AgeClass[11].Rank = 11;
  AgeClass[11].FDay = 16425;
  AgeClass[11].LDay = 18249;

  AgeClass[12].Rank = 12;
  AgeClass[12].FDay = 18250;
  AgeClass[12].LDay = 20074;

  AgeClass[13].Rank = 13;
  AgeClass[13].FDay = 20075;
  AgeClass[13].LDay = 21899;

  AgeClass[14].Rank = 14;
  AgeClass[14].FDay = 21900;
  AgeClass[14].LDay = 23724;

  AgeClass[15].Rank = 15;
  AgeClass[15].FDay = 23725;
  AgeClass[15].LDay = 25549;

  AgeClass[16].Rank = 16;
  AgeClass[16].FDay = 25550;
  AgeClass[16].LDay = 27374;

  AgeClass[17].Rank = 17;
  AgeClass[17].FDay = 27375;
  AgeClass[17].LDay = 29199;

  AgeClass[18].Rank = 18;
  AgeClass[18].FDay = 29200;
  AgeClass[18].LDay = 30000;

}



void
dsport::ReadDefaultParms(void)
{
}



void
dsport::LocAssignData(void)
{
}



void
dsport::MainInitialization(void)
{
  // initialize variables
  Year = 1;
  SimYear = 0;
  ArraySize = 0;
  OldArraySize = 0;
  Stepping = true;
  Restart = false;
  EIPTempAdjust = 0;
  Continuation = false;

  // TODO fix this initialization
  EndYear = 5;
  InitialPopSize = 10000;
}



void
dsport::InitAgeClasses(void)
{
  ArraySize = 0;
  AgeDistr = std::vector<int>( 18+1, 0 );
  InitAgeDistr = std::vector<int>( 18+1, 0 );
  Indiv = std::vector<int>( MaxPopSize+1, 0 );
  // Initialize the population - start with InitialPopSize
  // Randomly select individual ages by:
  //  1. Determine the number of individuals in the age class
  //  2. Select a random age for each individual.  Use max and min age
  //     for the age class as the age bounds.
  //  3. Sort the array.  Oldest individuals will have smallest subscript
  //     so that babies can be added to the end of the array.  Bookkeeping
  //     procedures (RankPop) rely on a presorted array.
  for( int iClass = 18; iClass >= 1; --iClass ) {
    // kount = Number of individuals in this age class (age class proportion of initial population)
    int kount = CINT( PopProp[iClass].Prop * InitialPopSize );
    for( int iIndiv = 1; iIndiv <= kount; ++iIndiv ) {
      // kage  = Randomly assigned age (within class bounds) of current individual.
      int kage = INT( (AgeClass[iClass].LDay - AgeClass[iClass].FDay + 1) * RND() + AgeClass[iClass].FDay);
      ArraySize = ArraySize + 1;
      Indiv[ArraySize] = kage;
      AgeDistr[iClass] = AgeDistr[iClass] + 1;
      InitAgeDistr[iClass] = InitAgeDistr[iClass] + 1;
      if( kage < AgeClass[iClass].FDay || kage > AgeClass[iClass].LDay ) {
        // STOP  'debugging code
      }
    }
  }
  // DS 1.0 doesn't specify it, but oldest individuals are first,
  // this means the Indiv vector is reverse sorted, we decrement the reverse end so
  // sort doesn't access position 0, which is not used in 1's indexed vectors
  std::sort( Indiv.rbegin(), --(Indiv.rend()) );
  OldArraySize = ArraySize;
  InitArraySize = ArraySize;
}



// emulate DS 1.0 CINT() which does banker's rounding
int
dsport::CINT( float value )
{
  float integer;
  float fraction;
  fraction = modf( value, &integer );

  // special case for banker's rounding
  if( 0.49 < abs(fraction) && abs(fraction) < 0.51 ) {
    int bitwiseAnd = ( (int) integer ) & 1;

    if( bitwiseAnd ) {
      // integer is odd, return nearest even number
      if( integer > 0 )
        return ((int)integer) + 1;
      else
        return ((int)integer) - 1;
    }
    else {
      // integer is even, return integer
      return ((int)integer);
    }
  }
  else {
    if( abs(fraction) > 0.5 ) {
      if( fraction > 0 )
		    return (int)ceil( value );
      else
        return (int)floor( value );
	  }
    else { 
      if( fraction > 0 )
		    return (int)floor( value );
      else
		    return (int)ceil( value );
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
dsport::RND(void)
{
  return rand() / (float) (RAND_MAX + 1); 
}
  


void
dsport::InitSeroprevalence(void)
{
  // Initialize the seroprevalence data
  // This data confers previous homologous immunity (designated by -2)
  // Oldest individuals have the smallest subscripts.
  
  Deng1 = std::vector<int>( MaxPopSize+1, 0 );
  Deng2 = std::vector<int>( MaxPopSize+1, 0 );
  Deng3 = std::vector<int>( MaxPopSize+1, 0 );
  Deng4 = std::vector<int>( MaxPopSize+1, 0 );
  InitSerDistr = std::vector<std::vector<int>>( 18+1, std::vector<int>(4+1, 0) );

  int iPos = 0;                       // start with array pos 1, oldest indiv.
  for( int i = 18; i >= 1; --i ) {    // each age class
    for( int j = 1; j <= 4; ++j ) {   // each serotype

      // calculate the number of individuals with homologuos immunity to this serotype in this age class
      int iNewInfect = CINT(SerProp[i][j] * AgeDistr[i]);
      if( iNewInfect > 0 ) {
        // assign infections to individuals
        for( int k = 1; k <= iNewInfect; ++k ) {
          bool iSuscept = false;
          do {
            // find an individual in this age class to mark with homologuos immunity
            int iElement = INT( (AgeDistr[i] - 1 + 1) * RND() + 1 );
            switch (j) {
              case 1:
                if( Deng1[iPos + iElement] == 0 ) {
                  iSuscept = true;
                  Deng1[iPos + iElement] = -2;
                  InitSerDistr[i][j] = InitSerDistr[i][j] + 1;
                }
                break;
              case 2:
                if( Deng2[iPos + iElement] == 0 ) {
                  iSuscept = true;
                  Deng2[iPos + iElement] = -2;
                  InitSerDistr[i][j] = InitSerDistr[i][j] + 1;
                }
                break;
              case 3:
                if( Deng3[iPos + iElement] == 0 ) {
                  iSuscept = true;
                  Deng3[iPos + iElement] = -2;
                  InitSerDistr[i][j] = InitSerDistr[i][j] + 1;
                }
                break;
              case 4:
                if( Deng4[iPos + iElement] == 0 ) {
                  iSuscept = true;
                  Deng4[iPos + iElement] = -2;
                  InitSerDistr[i][j] = InitSerDistr[i][j] + 1;
                }
                break;
            }
          } while ( iSuscept != true );
        }
      }
    }
    iPos = iPos + AgeDistr[i];
  }
}



void
dsport::CalcBirths( std::vector<float> & CBirths )
{
  int iPos = 0;           // start with array pos. 1, or the oldest individuals

  for( int i = 18; i >= 1; --i ) {

    // calculate cumulative age class birth rate
    float BRate = (PopProp[i].BRate / 1000) * (1 / (float) YrLen);
    // only females contribute to birth
    CBirths[i] = CBirths[i] + ((AgeDistr[i] / (float) 2) * BRate);

    // add Births to Indiv() array
    if( CBirths[i] >= 1 ) {
      for( int j =1; j <= INT( CBirths[i] ); ++j ) {
        ArraySize = ArraySize + 1;            // add an element, i.e. an individual, to the array
        // TODO - figure out memory limitations
        //IF ArraySize > (MaxPopSize - 50) OR FRE(-1) < 10000 THEN
        //  BEEP: BEEP
        //  IF ArraySize > MaxPopSize - 50 THEN
        //    LOCATE 55, 15: PRINT "About to exceed the bounds of the individual array!"
        //  ELSE
        //    LOCATE 55, 15: PRINT "About to exceed the bounds of memory!"
        //  END IF
        //  LOCATE 56, 30: PRINT "Program Terimated!"
        //  LOCATE 57, 28: PRINT "Press any key to quit"
        //  DO: LOOP WHILE INKEY$ = "": END
        //END IF

        Indiv[ArraySize] = 1;        // one day old

        // record maternally acquired seroprev. type by randomly selecting individual
        // in this age class as the mother
        // -1 denotes maternally acquired
        // -2 denotes homologous immunity for seroprevalence intitialization
        int iElement = INT((AgeDistr[i] - 1 + 1) * RND() + 1);
        if( Deng1[iPos + iElement] > 0 || Deng1[iPos + iElement] == -2 ) {
          // if positive for homologuos immunity, confer maternally acquired immunity on birth
          Deng1[ArraySize] = -1;
        }
        if( Deng2[iPos + iElement] > 0 || Deng2[iPos + iElement] == -2 ) {
          Deng2[ArraySize] = -1;
        }
        if( Deng3[iPos + iElement] > 0 || Deng3[iPos + iElement] == -2 ) {
          Deng3[ArraySize] = -1;
        }
        if( Deng4[iPos + iElement] > 0 || Deng4[iPos + iElement] == -2 ) {
          Deng4[ArraySize] = -1;
        }

        AgeDistr[1] = AgeDistr[1] + 1;        // update age distribution data
        TotBirths[i] = TotBirths[i] + 1;      // simulation tally
      }
      CBirths[i] = CBirths[i] - INT(CBirths[i]);
    }
    iPos = iPos + AgeDistr[i];
  }
}



void
dsport::CalcDeaths( std::vector<float> & CDeaths )
{
  int iPos = 0;     // start with array position 1, or the oldest individual

  for( int i = 18; i >= 1; --i ) {

    // calculate cumulative age class death rate
    float DRate = (PopProp[i].DRate / 1000) * (1 / (float) YrLen);
    // add deaths to previous fractional remainder
    CDeaths[i] = CDeaths[i] + (AgeDistr[i] * DRate);

    // subtract deaths from Indiv() array
    if( CDeaths[i] >= 1 && AgeDistr[i] > 0 ) {
      for( int j = 1; j <= INT(CDeaths[i]); ++j ) {
        // pick a random individual - taken from the number of individuals
        // in an age class - and remove.  Compress the array.
        int iElement = INT((AgeDistr[i] - 1 + 1) * RND() + 1);
        int iNumElsLeft = ArraySize - (iPos + iElement);

        // Erase individual at position iPos + iElement
        std::vector<int>::iterator itIndiv = Indiv.begin() + iPos + iElement;
        Indiv.erase( itIndiv );
        // And fix the resultant decrease in size of vector
        Indiv.push_back(0);

        std::vector<int>::iterator itDeng1 = Deng1.begin() + iPos + iElement;
        Deng1.erase( itDeng1 );
        Deng1.push_back(0);

        std::vector<int>::iterator itDeng2 = Deng2.begin() + iPos + iElement;
        Deng2.erase( itDeng2 );
        Deng2.push_back(0);

        std::vector<int>::iterator itDeng3 = Deng3.begin() + iPos + iElement;
        Deng3.erase( itDeng3 );
        Deng3.push_back(0);

        std::vector<int>::iterator itDeng4 = Deng4.begin() + iPos + iElement;
        Deng4.erase( itDeng4 );
        Deng4.push_back(0);

        // population decreased by one
        ArraySize = ArraySize - 1;
        AgeDistr[i] = AgeDistr[i] - 1;
        TotDeaths[i] = TotDeaths[i] + 1;
        if( AgeDistr[i] <= 0 ) {
          break;
        }
      }
    }
    iPos = iPos + AgeDistr[i];
    CDeaths[i] = CDeaths[i] - INT(CDeaths[i]);
  }
}



void
dsport::InitInfectives(void)
{
  // Add infective humans

  // Initialize infective mosquitoes for the 4 serotypes
  for( int seroType = 1; seroType <= 4; ++seroType ) {      
    if( AddedInfections[seroType][Day] && VirusIntro[seroType].Mosq > 0 ) {
      // look for empty position in the old infected array and add.  This way the
      // new infectives will drop to position 1 in the infective array and
      // become new blood feeders on this day.
      // If no free space is found, then add to last position in the array.
      bool ifound = false;
      for( int i = 1; i <= MaxAgeMosq; ++i ) {
        if( OldMosqInfd[i][seroType] == 0 ) {
          OldMosqInfd[i][seroType] = VirusIntro[seroType].Mosq;
          OldMosqInfdCD[i][seroType] = 1.1f;
          OldMosqInfdEIP[i][seroType] = 1.1f;
          ifound = true;
          break;
        }
      }
      if( ifound != true ) {
        // no open position found, accumulate into the oldest cohort of old infecteds
        OldMosqInfd[MaxAgeMosq][seroType] = OldMosqInfd[MaxAgeMosq][seroType] + VirusIntro[seroType].Mosq;
        OldMosqInfdCD[MaxAgeMosq][seroType] = 1.1f;
        OldMosqInfdEIP[MaxAgeMosq][seroType] = 1.1f;
      }
    }
  }

  // Initialize infective humans
  for( int seroType = 1; seroType <= 4; ++seroType ) {
    if( AddedInfections[seroType][Day] && VirusIntro[seroType].Hums > 0 ) {
      for( int i = 1; i <= VirusIntro[seroType].Hums; ++i ) {
        // Increase current population size
        ArraySize = ArraySize + 1;
        int IAge = 0;
        int iPos = 0;
        switch (seroType) {
          case 1:
            IAge = INT((AgeClass[18].LDay - (Virus[1].Incub + 1) + 1) * RND() + (Virus[1].Incub + 1));
            iPos = DeterminePosition( IAge );
            Indiv[iPos] = IAge;
            Deng1[iPos] = IAge - Virus[1].Incub;
            if( IAge - Virus[1].Incub <= 0) {
              // STOP  'debugging code
            }
            break;
          case 2:
            IAge = INT((AgeClass[18].LDay - (Virus[2].Incub + 1) + 1) * RND() + (Virus[2].Incub + 1));
            iPos = DeterminePosition( IAge );
            Indiv[iPos] = IAge;
            Deng2[iPos] = IAge - Virus[2].Incub;
            if( IAge - Virus[2].Incub <= 0) {
              // STOP  'debugging code
            }
            break;
          case 3:
            IAge = INT((AgeClass[18].LDay - (Virus[3].Incub + 1) + 1) * RND() + (Virus[3].Incub + 1));
            iPos = DeterminePosition( IAge );
            Indiv[iPos] = IAge;
            Deng3[iPos] = IAge - Virus[3].Incub;
            if( IAge - Virus[3].Incub <= 0) {
              // STOP  'debugging code
            }
            break;
          case 4:
            IAge = INT((AgeClass[18].LDay - (Virus[4].Incub + 1) + 1) * RND() + (Virus[4].Incub + 1));
            iPos = DeterminePosition( IAge );
            Indiv[iPos] = IAge;
            Deng4[iPos] = IAge - Virus[4].Incub;
            if( IAge - Virus[4].Incub <= 0) {
              // STOP  'debugging code
            }
            break;
        }
      }
    }
  }
}



// determine where new infectious individual will be inserted
int dsport::DeterminePosition( int IAge )
{
  int iPos;
  // check for extremes
  if( IAge >= Indiv[1] ) {
    // they become the oldest individual
    for( int k = ArraySize; k >= 2; --k ) {
      Indiv[k] = Indiv[k - 1];
      Deng1[k] = Deng1[k - 1];
      Deng2[k] = Deng2[k - 1];
      Deng3[k] = Deng3[k - 1];
      Deng4[k] = Deng4[k - 1];
    }
    iPos = 1;
    return iPos;
  }
  if( IAge <= Indiv[ArraySize - 1] ) {
    // they become the youngest individual
    iPos = ArraySize;
    return iPos;
  }
  // somewhere in the middle
  for( iPos = 2; iPos <= (ArraySize - 1); ++iPos ) {       // last position is new
    if( IAge <= Indiv[iPos - 1] && IAge >= Indiv[iPos] ) {
      // position found
      for( int k = ArraySize; k >= iPos + 1; --k ) {
        Indiv[k] = Indiv[k - 1];
        Deng1[k] = Deng1[k - 1];
        Deng2[k] = Deng2[k - 1];
        Deng3[k] = Deng3[k - 1];
        Deng4[k] = Deng4[k - 1];
      }
      return iPos;
    }
  }
  return -1;    // STOP - debug
}


 
void
dsport::PurgeMaternal( int iOff )
{
  for( int i = ArraySize; i >= 1; --i ) {
    if( Indiv[i] > iOff + 20 ) {
      break;                            // buffer region - ages sequential so no need for further searches
    }
    if( Indiv[i] >= iOff ) {
      if( Deng1[i] == -1 ) {
        Deng1[i] = 0;
      }
      if( Deng2[i] == -1 ) {
        Deng2[i] = 0;
      }
      if( Deng3[i] == -1 ) {
        Deng3[i] = 0;
      }
      if( Deng4[i] == -1 ) {
        Deng4[i] = 0;
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
  NewMosqSusc[1] = CimSimData[Day].NewDlyFemales * (ArraySize / HumHostDensity) * CimSimData[Day].OverallSurv;
  NewMosqSuscCD[1] = CimSimData[Day].AdultDev;
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
}



void
dsport::HumToMosqTrans(void)
{
  // Number of susceptible probes per individual
  BitesPerPerson[Day] = (BitersNew + BitersOld) * PropOnHum;
  BitesPerPerson[Day] = BitesPerPerson[Day] + (BitesPerPerson[Day] * (FdAttempts - 1) * PropDifHost);
  if( ArraySize == 0 ) {
    throw; // STOP
  }
  BitesPerPerson[Day] = BitesPerPerson[Day] / ArraySize;


  // randomly calculate new mosquito infections for four serotypes
  std::vector<int> seroTypesCompleted;
  // loop until all four sero types are processed
  while(true) {
    int i = INT( (4 - 1 + 1) * RND() + 1 );
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
  int OldInfd;              // new infected from old susceptible
  int NewInfd;              // new infected from new susceptible

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
    ProbInf = HumToMosHInf - ((HumToMosHTiter - (log(Virus[iType].Viremia) / log(10.0))) * Slope);
  }

  InocEstimate = TotDlyInfective[iType] * BitesPerPerson[Day] * ProbInf;

  // find new infected mosquitoes
  if( InocEstimate > StochTransNum ) {
    // discrete
    //NewDlyMosqInoc = CLNG(InocEstimate) where DS 1.0 used CLNG for a 4 bit integer, an int in c++, although machine dependent, can hold a word
    NewDlyMosqInoc = CINT(InocEstimate);
  }
  else if( InocEstimate > 0 ) {
    // stochastic
    float num = RND();
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
    OldMosqInfdCD[1][iType] = CimSimData[Day].AdultDev;
    NewMosqInfdCD[1][iType] = CimSimData[Day].AdultDev;
    OldMosqInfdEIP[1][iType] = EIPDevRate[iType];
    NewMosqInfdEIP[1][iType] = EIPDevRate[iType];
  }
}



void
dsport::MosqToHumTrans( int iOldAge )
{
  // randomly calculate new human infections for four serotypes
  std::vector<int> seroTypesCompleted;
  // loop until all four sero types are processed
  while(true) {
    int iType = INT( (4 - 1 + 1) * RND() + 1 );
    std::vector<int>::iterator findResult;
    findResult = std::find( seroTypesCompleted.begin(), seroTypesCompleted.end(), iType );
    if( findResult == seroTypesCompleted.end() ) {
      // process serotype, and mark it as done
      CalcNewInocHumans(iType, iOldAge);
      seroTypesCompleted.push_back(iType);
    }
    if( seroTypesCompleted.size() == 4 ) {
      // all 4 serotypes completed
      break;
    }
  }
}




void
dsport::CalcNewInocHumans( int iType, int iOldAge )
{
  //int iType;                // current serotype for calculations
  int r;                      // for poisson distribution
  float InocEstimate;         // number of infv bites to humans

  InocEstimate = ((BitersInfv[iType] * PropOnHum) + ((BitersInfv[iType] * PropOnHum) * (FdAttempts - 1) * PropDifHost)) * MosqToHumProb;

  if( InocEstimate > StochTransNum ) {
    // discrete
    NewDlyHumInoc = CINT( InocEstimate );
  }

  else if( InocEstimate > 0 ) {
    // stochastic
    float num = RND();
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

    // randomly select individual for new innoculation
    int iElement = INT( (ArraySize - 1 + 1) * RND() + 1);

    switch( iType ) {

      case 1: {                                            // type I infection
        switch( Deng1[iElement] ) {
          case -1: {                                      // maternally acquired antibody
            if( Indiv[iElement] > MANADurat ) {
              // this will be an enhanced infection (MAEA)
              // or a normal infection if age > MAEA duration
              Deng1[iElement] = Indiv[iElement];
            }
            break;
          }
          case 0: {                                        // no previous exposure to this serotype
            // check for heterologous immunity
            // initialized immunity (-2) does not confer heterologous immunity
            bool iHetImmunity = false;
            if( Deng2[iElement] > 0 && Indiv[iElement] - Deng2[iElement] < HetImmunDurat ) {
              iHetImmunity = true;
            }
            if( Deng3[iElement] > 0 && Indiv[iElement] - Deng3[iElement] < HetImmunDurat ) {
              iHetImmunity = true;
            }
            if( Deng4[iElement] > 0 && Indiv[iElement] - Deng4[iElement] < HetImmunDurat ) {
              iHetImmunity = true;
            }

            // if no heterologous immunity then assign infection date
            if( iHetImmunity == false ) {
              if( Indiv[iElement] > iOldAge ) {
                Indiv[iElement] = iOldAge;
              }
              Deng1[iElement] = Indiv[iElement];
            }
            break;
          }
          default: {                                       // previous infection, inoc. age = positive integer or -2
            // homologous immunity, do nothing
            break;
          }
        }
        break;
      }
      
      case 2: {                                            // type II infection
        switch( Deng2[iElement] ) {
          case -1: {                                       // maternally acquired antibody
            if( Indiv[iElement] > MANADurat ) {
              // this will be an enhanced infection (MAEA)
              // or a normal infection if age > MAEA duration
              Deng2[iElement] = Indiv[iElement];
            }
            break;
          }
          case 0: {                                       // no previous exposure to this serotype
            // check for heterologous immunity
            // initialized immunity (-2) does not confer heterologous immunity
            bool iHetImmunity = false;
            if( Deng1[iElement] > 0 && Indiv[iElement] - Deng1[iElement] < HetImmunDurat ) {
              iHetImmunity = true;
            }
            if( Deng3[iElement] > 0 && Indiv[iElement] - Deng3[iElement] < HetImmunDurat ) {
              iHetImmunity = true;
            }
            if( Deng4[iElement] > 0 && Indiv[iElement] - Deng4[iElement] < HetImmunDurat ) {
              iHetImmunity = true;
            }

            // if no heterologous immunity then assign infection date
            if( iHetImmunity == false ) {
              if( Indiv[iElement] > iOldAge ) {
                Indiv[iElement] = iOldAge;
              }
              Deng2[iElement] = Indiv[iElement];
            }
            break;
          }
          default: {                                       // previous infection, inoc. age = positive integer or -2
            // homologous immunity, do nothing
            break;
          }
        }
        break;
      }
      
      case 3: {                                            // type III infection
        switch( Deng3[iElement] ) {
          case -1: {                                       // maternally acquired antibody
            if( Indiv[iElement] > MANADurat ) {
              // this will be an enhanced infection (MAEA)
              // or a normal infection if age > MAEA duration
              Deng3[iElement] = Indiv[iElement];
            }
            break;
          }
          case 0: {                                        // no previous exposure to this serotype
            // check for heterologous immunity
            // initialized immunity (-2) does not confer heterologous immunity
            bool iHetImmunity = false;
            if( Deng1[iElement] > 0 && Indiv[iElement] - Deng1[iElement] < HetImmunDurat ) {
              iHetImmunity = true;
            }
            if( Deng2[iElement] > 0 && Indiv[iElement] - Deng2[iElement] < HetImmunDurat ) {
              iHetImmunity = true;
            }
            if( Deng4[iElement] > 0 && Indiv[iElement] - Deng4[iElement] < HetImmunDurat ) {
              iHetImmunity = true;
            }

            // if no heterologous immunity then assign infection date
            if( iHetImmunity == false ) {
              if( Indiv[iElement] > iOldAge ) {
                Indiv[iElement] = iOldAge;
              }
              Deng3[iElement] = Indiv[iElement];
            }
            break;
          }
          default: {                                    // previous infection, inoc. age = positive integer or -2
            // homologous immunity, do nothing
            break;
          }
        }
        break;
      }

      case 4: {                                          // type IV infection
        switch( Deng4[iElement] ) {
          case -1: {                                     // maternally acquired antibody
            if( Indiv[iElement] > MANADurat ) {
              // this will be an enhanced infection (MAEA)
              // or a normal infection if age > MAEA duration
              Deng4[iElement] = Indiv[iElement];
            }
            break;
          }
          case 0: {                                       // no previous exposure to this serotype
            // check for heterologous immunity
            // initialized immunity (-2) does not confer heterologous immunity
            bool iHetImmunity = false;
            if( Deng1[iElement] > 0 && Indiv[iElement] - Deng1[iElement] < HetImmunDurat ) {
              iHetImmunity = true;
            }
            if( Deng2[iElement] > 0 && Indiv[iElement] - Deng2[iElement] < HetImmunDurat ) {
              iHetImmunity = true;
            }
            if( Deng3[iElement] > 0 && Indiv[iElement] - Deng3[iElement] < HetImmunDurat ) {
              iHetImmunity = true;
            }

            // if no heterologous immunity then assign infection date
            if( iHetImmunity == false ) {
              if( Indiv[iElement] > iOldAge ) {
                Indiv[iElement] = iOldAge;
              }
              Deng4[iElement] = Indiv[iElement];
            }
            break;
          }
          default: {                                     // previous infection, inoc. age = positive integer or -2
            // homologous immunity, do nothing
            break;
          }
        }
        break;
      }
    }
  }
}


  
void
dsport::RankPop(void)
{
  AgeDistr = std::vector<int>( 18+1, 0 );                                             // clear last tally
  SerDistr = std::vector<std::vector<int>>( 18+1, std::vector<int>(4+1, 0) );         // clear last tally
  Incub = std::vector<std::vector<int>>( 18+1, std::vector<int>(4+1, 0) );            // clear last tally
  Infective = std::vector<std::vector<int>>( 18+1, std::vector<int>(4+1, 0) );      // clear last tally
  HomImm = std::vector<std::vector<int>>( 18+1, std::vector<int>(4+1, 0) );           // clear last tally
  HetImm = std::vector<std::vector<int>>( 18+1, std::vector<int>(4+1, 0) );           // clear last tally
  MatAnti = std::vector<MaternalTransmission>( 4+1 );                              // clear last tally
  TotDlyIncub = std::vector<int>( 4+1, 0 );
  TotDlyInfective = std::vector<int>( 4+1, 0 );
  TotDlyHomImm = std::vector<int>( 4+1, 0 );
  TotDlyHetImm = std::vector<int>( 4+1, 0 );
  NewDlyInfective = std::vector<int>( 4+1, 0 );

  // initialize sequential infection statistics record
  DlySeqInfVals.F1T2 = 0;
  DlySeqInfVals.F1T3 = 0;
  DlySeqInfVals.F1T4 = 0;
  DlySeqInfVals.F2T1 = 0;
  DlySeqInfVals.F2T3 = 0;
  DlySeqInfVals.F2T4 = 0;
  DlySeqInfVals.F3T1 = 0;
  DlySeqInfVals.F3T2 = 0;
  DlySeqInfVals.F3T4 = 0;
  DlySeqInfVals.F4T1 = 0;
  DlySeqInfVals.F4T2 = 0;
  DlySeqInfVals.F4T3 = 0;
  DlySeqInfVals.FMT1 = 0;
  DlySeqInfVals.FMT2 = 0;
  DlySeqInfVals.FMT3 = 0;
  DlySeqInfVals.FMT4 = 0;
  
  int iRank = 18;                                   // assume oldest age class first
  for( int i = 1; i <= ArraySize; ++i ) {
    if( Indiv[i] >= AgeClass[iRank].FDay ) {
      AgeDistr[iRank] = AgeDistr[iRank] + 1;
      SeroRank(i, iRank);
    }
    else {
      int j;
      for( j = iRank - 1; j >= 1; --j ) {           // find next ranking
        if( Indiv[i] >= AgeClass[j].FDay ) {
          // found individuals new rank
          break;
        }
      }
      iRank = j;
      if( iRank < 1 ) {
        throw; // STOP
      }
      AgeDistr[iRank] = AgeDistr[iRank] + 1;
      SeroRank(i, iRank);
    }
  }
}



void
dsport::SeroRank( int iElement, int iRank )
{
  // Rank can be -2 for initialized homologous immmunity
  //             -1 for maternally acquired immunity
  //              0 for no previous exposure
  //             >0 inoculation day

  int i = iElement;   // individual's index in population array


  if( Deng1[i] != 0 ) { 
    // show seropositive status
    SerDistr[iRank][1] = SerDistr[iRank][1] + 1;
    
    if( Deng1[i] == -2 ) {
      HomImm[iRank][1] = HomImm[iRank][1] + 1;
      TotDlyHomImm[1] = TotDlyHomImm[1] + 1;
    }
    else if( Deng1[i] == -1 ) {
      // check for neutralizing or enhancing antibody
      if( Indiv[i] < MANADurat ) {
        // MANA individual
        MatAnti[1].MANA = MatAnti[1].MANA + 1;
        HomImm[iRank][1] = HomImm[iRank][1] + 1;
        TotDlyHomImm[1] = TotDlyHomImm[1] + 1;
      }
      else if( Indiv[i] < MAEADurat + MANADurat ) {
        MatAnti[1].MAEA = MatAnti[1].MAEA + 1;
      }
    }
    else {
      int iTemp = Indiv[i] - Deng1[i];

      // check for incubating virus
      if( iTemp < Virus[1].Incub ) {
        Incub[iRank][1] = Incub[iRank][1] + 1;
        TotDlyIncub[1] = TotDlyIncub[1] + 1;
      }
      else if( iTemp < Virus[1].Durat + Virus[1].Incub ) {
        // check for infectious virus
        Infective[iRank][1] = Infective[iRank][1] + 1;
        TotDlyInfective[1] = TotDlyInfective[1] + 1;
        if( iTemp == Virus[1].Incub ) {
          // New infectives for the day
          NewDlyInfective[1] = NewDlyInfective[1] + 1;
        }
        if( iTemp > Virus[1].Incub + (Virus[1].Durat / 2) ) {
          // latter half of viremic phase, check for HF/SS
          CalcSeqInfs(1, Indiv[i], Deng1[i], Deng2[i], Deng3[i], Deng4[i]);
        }
      }
      else {
        // check for heterologous immunity
        if( iTemp < HetImmunDurat + Virus[1].Durat + Virus[1].Incub ) {
          HetImm[iRank][1] = HetImm[iRank][1] + 1;
          TotDlyHetImm[1] = TotDlyHetImm[1] + 1;
        }
        // all have homologous immunity
        HomImm[iRank][1] = HomImm[iRank][1] + 1;
        TotDlyHomImm[1] = TotDlyHomImm[1] + 1;
      }
    }
  }


  if( Deng2[i] != 0 ) {
    // show seropositive status
    SerDistr[iRank][2] = SerDistr[iRank][2] + 1;

    if( Deng2[i] == -2 ) {
      HomImm[iRank][2] = HomImm[iRank][2] + 1;
      TotDlyHomImm[2] = TotDlyHomImm[2] + 1;
    }
    else if( Deng2[i] == -1 ) {
      // check for neutralizing or enhancing antibody
      if( Indiv[i] < MANADurat ) {
        // MANA individual
        MatAnti[2].MANA = MatAnti[2].MANA + 1;
        HomImm[iRank][2] = HomImm[iRank][2] + 1;
        TotDlyHomImm[2] = TotDlyHomImm[2] + 1;
      }
      else if( Indiv[i] < MAEADurat + MANADurat ) {
        MatAnti[2].MAEA = MatAnti[2].MAEA + 1;
      }
    }
    else {
      int iTemp = Indiv[i] - Deng2[i];

      // check for incubating virus
      if( iTemp < Virus[2].Incub ) {
        Incub[iRank][2] = Incub[iRank][2] + 1;
        TotDlyIncub[2] = TotDlyIncub[2] + 1;
      }
      else if( iTemp < Virus[2].Durat + Virus[2].Incub ) {
        // check for infectious virus
        Infective[iRank][2] = Infective[iRank][2] + 1;
        TotDlyInfective[2] = TotDlyInfective[2] + 1;
        if( iTemp == Virus[2].Incub ) {
          // New infectives for the day
          NewDlyInfective[2] = NewDlyInfective[2] + 1;
        }
        if( iTemp > Virus[2].Incub + (Virus[2].Durat / 2) ) {
          // latter half of viremic phase, check for HF/SS
          CalcSeqInfs(2, Indiv[i], Deng1[i], Deng2[i], Deng3[i], Deng4[i]);
        }
      }
      else {
        // check for heterologous immunity
        if( iTemp < HetImmunDurat + Virus[2].Durat + Virus[2].Incub ) {
          HetImm[iRank][2] = HetImm[iRank][2] + 1;
          TotDlyHetImm[2] = TotDlyHetImm[2] + 1;
        }
        // all have homologous immunity
        HomImm[iRank][2] = HomImm[iRank][2] + 1;
        TotDlyHomImm[2] = TotDlyHomImm[2] + 1;
      }
    }
  }


  if( Deng3[i] != 0 ) {
    // show seropositive status
    SerDistr[iRank][3] = SerDistr[iRank][3] + 1;

    if( Deng3[i] == -2 ) {
      HomImm[iRank][3] = HomImm[iRank][3] + 1;
      TotDlyHomImm[3] = TotDlyHomImm[3] + 1;
    }
    else if( Deng3[i] == -1 ) {
      // check for neutralizing or enhancing antibody
      if( Indiv[i] < MANADurat ) {
        // MANA individual
        MatAnti[3].MANA = MatAnti[3].MANA + 1;
        HomImm[iRank][3] = HomImm[iRank][3] + 1;
        TotDlyHomImm[3] = TotDlyHomImm[3] + 1;
      }
      else if( Indiv[i] < MAEADurat + MANADurat ) {
        MatAnti[3].MAEA = MatAnti[3].MAEA + 1;
      }
    }
    else {
      int iTemp = Indiv[i] - Deng3[i];

      // check for incubating virus
      if( iTemp < Virus[3].Incub ) {
        Incub[iRank][3] = Incub[iRank][3] + 1;
        TotDlyIncub[3] = TotDlyIncub[3] + 1;
      }
      else if( iTemp < Virus[3].Durat + Virus[3].Incub ) {
        // check for infectious virus
        Infective[iRank][3] = Infective[iRank][3] + 1;
        TotDlyInfective[3] = TotDlyInfective[3] + 1;
        if( iTemp == Virus[3].Incub ) {
          // New infectives for the day
          NewDlyInfective[3] = NewDlyInfective[3] + 1;
        }
        if( iTemp > Virus[3].Incub + (Virus[3].Durat / 2) ) {
          // latter half of viremic phase, check for HF/SS
          CalcSeqInfs(3, Indiv[i], Deng1[i], Deng2[i], Deng3[i], Deng4[i]);
        }
      }
      else {
        // check for heterologous immunity
        if( iTemp < HetImmunDurat + Virus[3].Durat + Virus[3].Incub ) {
          HetImm[iRank][3] = HetImm[iRank][3] + 1;
          TotDlyHetImm[3] = TotDlyHetImm[3] + 1;
        }
        // all have homologous immunity
        HomImm[iRank][3] = HomImm[iRank][3] + 1;
        TotDlyHomImm[3] = TotDlyHomImm[3] + 1;
      }
    }
  }



  if( Deng4[i] != 0 ) {
    // show seropositive status
    SerDistr[iRank][4] = SerDistr[iRank][4] + 1;

    if( Deng4[i] == -2 ) {
      HomImm[iRank][4] = HomImm[iRank][4] + 1;
      TotDlyHomImm[4] = TotDlyHomImm[4] + 1;
    }
    else if( Deng4[i] == -1 ) {
      // check for neutralizing or enhancing antibody
      if( Indiv[i] < MANADurat ) {
        // MANA individual
        MatAnti[4].MANA = MatAnti[4].MANA + 1;
        HomImm[iRank][4] = HomImm[iRank][4] + 1;
        TotDlyHomImm[4] = TotDlyHomImm[4] + 1;
      }
      else if( Indiv[i] < MAEADurat + MANADurat ) {
        MatAnti[4].MAEA = MatAnti[4].MAEA + 1;
      }
    }
    else {
      int iTemp = Indiv[i] - Deng4[i];

      // check for incubating virus
      if( iTemp < Virus[4].Incub ) {
        Incub[iRank][4] = Incub[iRank][4] + 1;
        TotDlyIncub[4] = TotDlyIncub[4] + 1;
      }
      else if( iTemp < Virus[4].Durat + Virus[4].Incub ) {
        // check for infectious virus
        Infective[iRank][4] = Infective[iRank][4] + 1;
        TotDlyInfective[4] = TotDlyInfective[4] + 1;
        if( iTemp == Virus[4].Incub ) {
          // New infectives for the day
          NewDlyInfective[4] = NewDlyInfective[4] + 1;
        }
        if( iTemp > Virus[4].Incub + (Virus[4].Durat / 2) ) {
          // latter half of viremic phase, check for HF/SS
          CalcSeqInfs(4, Indiv[i], Deng1[i], Deng2[i], Deng3[i], Deng4[i]);
        }
      }
      else {
        // check for heterologous immunity
        if( iTemp < HetImmunDurat + Virus[4].Durat + Virus[4].Incub ) {
          HetImm[iRank][4] = HetImm[iRank][4] + 1;
          TotDlyHetImm[4] = TotDlyHetImm[4] + 1;
        }
        // all have homologous immunity
        HomImm[iRank][4] = HomImm[iRank][4] + 1;
        TotDlyHomImm[4] = TotDlyHomImm[4] + 1;
      }
    }
  }
}



void
dsport::CalcSeqInfs( int iVirType, int iPerAge, int iD1Inoc, int iD2Inoc, int iD3Inoc, int iD4Inoc )
{
  // calculates daily sequential infection and MAEA statistics
  // applies death to those with hf/ss - assigns Indiv(i) age of -999 for later analysis.

  switch( iVirType ) {                                        // what is indiv. viremic for - secondary infection

    case 1: {                                                 // dengue 1 viremia

      if( iD2Inoc > 0 || iD3Inoc > 0 || iD4Inoc > 0 ) {       // with some sort of sequential infection present
        
        // look for 2-1
        if( iD2Inoc > 0 && iPerAge < (SeqInfPrms[1].CutOff * 365) + 365 ) {
          // 2-1 sequence found - indiv is proper age
          int ElapsedTime = iD1Inoc - iD2Inoc;
          if(  ElapsedTime > (SeqInfPrms[1].Min * 30) && ElapsedTime < (SeqInfPrms[1].Max * 30)  ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F2T1 = DlySeqInfVals.F2T1 + (1 * SeqInfPrms[1].Prob);
            if( SeqInfPrms[1].Prob * SeqInfPrms[1].Mortality > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }

        // look for 3-1
        if( iD3Inoc > 0 && iPerAge < (SeqInfPrms[2].CutOff * 365) + 365 ) {
          // 3-1 sequence found - indiv is proper age
          int ElapsedTime = iD1Inoc - iD3Inoc;
          if( ElapsedTime > (SeqInfPrms[2].Min * 30) && ElapsedTime < (SeqInfPrms[2].Max * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F3T1 = DlySeqInfVals.F3T1 + (1 * SeqInfPrms[2].Prob);
            if( SeqInfPrms[2].Prob * SeqInfPrms[2].Mortality > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }

        // look for 4-1
        if( iD4Inoc > 0 && iPerAge < (SeqInfPrms[3].CutOff * 365) + 365 ) {
          // 4-1 sequence found - indiv is proper age
          int ElapsedTime = iD1Inoc - iD4Inoc;
          if( ElapsedTime > (SeqInfPrms[3].Min * 30) && ElapsedTime < (SeqInfPrms[3].Max * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F4T1 = DlySeqInfVals.F4T1 + (1 * SeqInfPrms[3].Prob);
            if( SeqInfPrms[3].Prob * SeqInfPrms[3].Mortality > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }
      }
      else {  // no subtype sequential infection - check for MAEA to subtype sequential
        // look for MAEA-1
        if( iPerAge < MANADurat + MAEADurat ) {
          // indiv is viremic and enhancing
          DlySeqInfVals.FMT1 = DlySeqInfVals.FMT1 + (1 * MAEAInfPrms[1].Prob);
          if( MAEAInfPrms[1].Prob * MAEAInfPrms[1].Mortality > RND() ) {
            // individual dies
            AgeAtDeath( iPerAge );
            iPerAge = -999;
            return;
          }
        }
      }
    }

    case 2: {                                                   // dengue 2 viremia

      if( iD1Inoc > 0 || iD3Inoc > 0 || iD4Inoc > 0 ) {         // with some sort of sequential infection is present

        // look for 1-2
        if( iD1Inoc > 0 && iPerAge < (SeqInfPrms[4].CutOff * 365) + 365 ) {
          // 1-2 sequence found - indiv is proper age
          int ElapsedTime =iD2Inoc - iD1Inoc;
          if( ElapsedTime > (SeqInfPrms[4].Min * 30) && ElapsedTime < (SeqInfPrms[4].Max * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F1T2 = DlySeqInfVals.F1T2 + (1 * SeqInfPrms[4].Prob);
            if( SeqInfPrms[4].Prob * SeqInfPrms[4].Mortality > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }

        // look for 3-2
        if( iD3Inoc > 0 && iPerAge < (SeqInfPrms[5].CutOff * 365) + 365 ) {
          // 3-2 sequence found - indiv is proper age
          int ElapsedTime =iD2Inoc - iD3Inoc;
          if( ElapsedTime > (SeqInfPrms[5].Min * 30) && ElapsedTime < (SeqInfPrms[5].Max * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F3T2 = DlySeqInfVals.F3T2 + (1 * SeqInfPrms[5].Prob);
            if( SeqInfPrms[5].Prob * SeqInfPrms[5].Mortality > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }

        // look for 4-2
        if( iD4Inoc > 0 && iPerAge < (SeqInfPrms[6].CutOff * 365) + 365 ) {
          // 4-2 sequence found - indiv is proper age
          int ElapsedTime =iD2Inoc - iD4Inoc;
          if( ElapsedTime > (SeqInfPrms[6].Min * 30) && ElapsedTime < (SeqInfPrms[6].Max * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F4T2 = DlySeqInfVals.F4T2 + (1 * SeqInfPrms[6].Prob);
            if( SeqInfPrms[6].Prob * SeqInfPrms[6].Mortality > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }
      }
      else {
        // look for MAEA-2
        if( iPerAge < MANADurat + MAEADurat ) {
          // indiv is viremic and enhancing
          DlySeqInfVals.FMT2 = DlySeqInfVals.FMT2 + (1 * MAEAInfPrms[2].Prob);
          if( MAEAInfPrms[2].Prob * MAEAInfPrms[2].Mortality > RND() ) {
            // individual dies
            AgeAtDeath( iPerAge );
            iPerAge = -999;
            return;
          }
        }
      }
    }
    
    case 3: {                                                        // dengue 3 viremia

      if( iD1Inoc > 0 || iD2Inoc > 0 || iD4Inoc > 0 ) {
        // some sort of sequential infection is present

        // look for 1-3
        if( iD1Inoc > 0 && iPerAge < (SeqInfPrms[7].CutOff * 365) + 365 ) {
          // 1-3 sequence found - indiv is proper age
          int ElapsedTime =iD3Inoc - iD1Inoc;
          if( ElapsedTime > (SeqInfPrms[7].Min * 30) && ElapsedTime < (SeqInfPrms[7].Max * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F1T3 = DlySeqInfVals.F1T3 + (1 * SeqInfPrms[7].Prob);
            if( SeqInfPrms[7].Prob * SeqInfPrms[7].Mortality > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }

        // look for 2-3
        if( iD2Inoc > 0 && iPerAge < (SeqInfPrms[8].CutOff * 365) + 365 ) {
          // 2-3 sequence found - indiv is proper age
          int ElapsedTime =iD3Inoc - iD2Inoc;
          if( ElapsedTime > (SeqInfPrms[8].Min * 30) && ElapsedTime < (SeqInfPrms[8].Max * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F2T3 = DlySeqInfVals.F2T3 + (1 * SeqInfPrms[8].Prob);
            if( SeqInfPrms[8].Prob * SeqInfPrms[8].Mortality > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }

        // look for 4-3
        if( iD4Inoc > 0 && iPerAge < (SeqInfPrms[9].CutOff * 365) + 365 ) {
          // 4-3 sequence found - indiv is proper age
          int ElapsedTime =iD3Inoc - iD4Inoc;
          if( ElapsedTime > (SeqInfPrms[9].Min * 30) && ElapsedTime < (SeqInfPrms[9].Max * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F4T3 = DlySeqInfVals.F4T3 + (1 * SeqInfPrms[9].Prob);
            if( SeqInfPrms[9].Prob * SeqInfPrms[9].Mortality > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }
      }
      else {
        // look for MAEA-3
        if( iPerAge < MANADurat + MAEADurat ) {
          // indiv is viremic and enhancing
          DlySeqInfVals.FMT3 = DlySeqInfVals.FMT3 + (1 * MAEAInfPrms[3].Prob);
          if( MAEAInfPrms[3].Prob * MAEAInfPrms[3].Mortality > RND() ) {
            // individual dies
            AgeAtDeath( iPerAge );
            iPerAge = -999;
            return;
          }
        }
      }
    }

    case 4: {                                                   // dengue 4 viremia
    
      if( iD1Inoc > 0 || iD2Inoc > 0 || iD3Inoc > 0 ) {         // some sort of sequential infection
        
        // look for 1-4
        if( iD1Inoc > 0 && iPerAge < (SeqInfPrms[10].CutOff * 365) + 365 ) {
          // 1-4 sequence found - indiv is proper age
          int ElapsedTime =iD4Inoc - iD1Inoc;
          if( ElapsedTime > (SeqInfPrms[10].Min * 30) && ElapsedTime < (SeqInfPrms[10].Max * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F1T4 = DlySeqInfVals.F1T4 + (1 * SeqInfPrms[10].Prob);
            if( SeqInfPrms[10].Prob * SeqInfPrms[10].Mortality > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }

        // look for 2-4
        if( iD2Inoc > 0 && iPerAge < (SeqInfPrms[11].CutOff * 365) + 365 ) {
          // 2-4 sequence found - indiv is proper age
          int ElapsedTime =iD4Inoc - iD2Inoc;
          if( ElapsedTime > (SeqInfPrms[11].Min * 30) && ElapsedTime < (SeqInfPrms[11].Max * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F2T4 = DlySeqInfVals.F2T4 + (1 * SeqInfPrms[11].Prob);
            if( SeqInfPrms[11].Prob * SeqInfPrms[11].Mortality > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }

        // look for 3-4
        if( iD3Inoc > 0 && iPerAge < (SeqInfPrms[12].CutOff * 365) + 365 ) {
          // 3-4 sequence found - indiv is proper age
          int ElapsedTime =iD4Inoc - iD3Inoc;
          if( ElapsedTime > (SeqInfPrms[12].Min * 30) && ElapsedTime < (SeqInfPrms[12].Max * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F3T4 = DlySeqInfVals.F3T4 + (1 * SeqInfPrms[12].Prob);
            if( SeqInfPrms[12].Prob * SeqInfPrms[12].Mortality > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }
      }
      else {
        // look for MAEA-4
        if( iPerAge < MANADurat + MAEADurat ) {
          // indiv is viremic and enhancing
          DlySeqInfVals.FMT4 = DlySeqInfVals.FMT4 + (1 * MAEAInfPrms[4].Prob);
          if( MAEAInfPrms[4].Prob * MAEAInfPrms[4].Mortality > RND() ) {
            // individual dies
            AgeAtDeath( iPerAge );
            iPerAge = -999;
            return;
          }
        }
      }
    }
  }
}



void
dsport::AgeAtDeath( int iPerAge )
{
  if( 0 <= iPerAge && iPerAge <= 365 ) {
    CumHFDeaths[0] = CumHFDeaths[0] + 1;
  }
  else if( 366 <= iPerAge && iPerAge <= 730 ) {
    CumHFDeaths[1] = CumHFDeaths[1] + 1;
  }
  else if( 731 <= iPerAge && iPerAge <= 1095 ) {
    CumHFDeaths[2] = CumHFDeaths[2] + 1;
  }
  else if( 1096 <= iPerAge && iPerAge <= 1460 ) {
    CumHFDeaths[3] = CumHFDeaths[3] + 1;
  }
  else if( 1461 <= iPerAge && iPerAge <= 1825 ) {
    CumHFDeaths[4] = CumHFDeaths[4] + 1;
  }
  else if( 1826 <= iPerAge && iPerAge <= 2190 ) {
    CumHFDeaths[5] = CumHFDeaths[5] + 1;
  }
  else if( 2191 <= iPerAge && iPerAge <= 2555 ) {
    CumHFDeaths[6] = CumHFDeaths[6] + 1;
  }
  else if( 2556 <= iPerAge && iPerAge <= 2920 ) {
    CumHFDeaths[7] = CumHFDeaths[7] + 1;
  }
  else if( 2921 <= iPerAge && iPerAge <= 3285 ) {
    CumHFDeaths[8] = CumHFDeaths[8] + 1;
  }
  else if( 3286 <= iPerAge && iPerAge <= 3650 ) {
    CumHFDeaths[9] = CumHFDeaths[9] + 1;
  }
  else if( 3651 <= iPerAge && iPerAge <= 4015 ) {
    CumHFDeaths[10] = CumHFDeaths[10] + 1;
  }
  else if( 4016 <= iPerAge && iPerAge <= 4380 ) {
    CumHFDeaths[11] = CumHFDeaths[11] + 1;
  }
  else if( 4381 <= iPerAge && iPerAge <= 4745 ) {
    CumHFDeaths[12] = CumHFDeaths[12] + 1;
  }
  else if( 4746 <= iPerAge && iPerAge <= 5110 ) {
    CumHFDeaths[13] = CumHFDeaths[13] + 1;
  }
  else if( 5111 <= iPerAge && iPerAge <= 5475 ) {
    CumHFDeaths[14] = CumHFDeaths[14] + 1;
  }
  else if( 5476 <= iPerAge && iPerAge <= 5840 ) {
    CumHFDeaths[15] = CumHFDeaths[15] + 1;
  }
}


  
void
dsport::PurgeHFDeaths(void)
{
  int iStart = ArraySize;                 // start with youngest individual

  for( int i = iStart; i >= 1; --i ) {

    if( Indiv[i] > 5840 ) { 
      return;     // following individuals are older than 15
    }

    // look for dead indviduals - value of -999
    if( Indiv[i] == -999 ) {
      if( i == iStart ) {
        // last position, simply zero to remove
        Indiv[ArraySize] = 0;
        Deng1[ArraySize] = 0;
        Deng2[ArraySize] = 0;
        Deng3[ArraySize] = 0;
        Deng4[ArraySize] = 0;
        ArraySize = ArraySize - 1;
      }
      else {
        // erase individual at position i
        std::vector<int>::iterator itIndiv = Indiv.begin() + i;
        Indiv.erase( itIndiv );
        // And fix the resultant decrease in size of vector
        Indiv.push_back(0);

        std::vector<int>::iterator itDeng1 = Deng1.begin() + i;
        Deng1.erase( itDeng1 );
        Deng1.push_back(0);

        std::vector<int>::iterator itDeng2 = Deng2.begin() + i;
        Deng2.erase( itDeng2 );
        Deng2.push_back(0);

        std::vector<int>::iterator itDeng3 = Deng3.begin() + i;
        Deng3.erase( itDeng3 );
        Deng3.push_back(0);

        std::vector<int>::iterator itDeng4 = Deng4.begin() + i;
        Deng4.erase( itDeng4 );
        Deng4.push_back(0);

        // population decreased by one
        ArraySize = ArraySize - 1;
      }
    }
  }
}



void
dsport::SpoolToDisk( int SpRecNum )
{
  DiskSpooler DiskData;

  DiskData.Incubate1 = TotDlyIncub[1];
  DiskData.Incubate2 = TotDlyIncub[2];
  DiskData.Incubate3 = TotDlyIncub[3];
  DiskData.Incubate4 = TotDlyIncub[4];
      
  DiskData.Viremic1 = TotDlyInfective[1];
  DiskData.Viremic2 = TotDlyInfective[2];
  DiskData.Viremic3 = TotDlyInfective[3];
  DiskData.Viremic4 = TotDlyInfective[4];

  DiskData.MosqTotal = MosqTotal;
  for( int i = 1; i <= 4; ++i ) {
    DiskData.MosqInfvTotal[i] = MosqInfvTotal[i];
    DiskData.NewHumCases[i] = NewDlyInfective[i];
  }
  DiskData.InfvBites = NewDlyHumInoc;
  for( int i = 1; i <= 4; ++i ) {
    DiskData.EIPDevRate[i] = EIPDevRate[i];
  }
  DiskData.NumHumans = ArraySize;
  
  std::vector<float> Temp = std::vector<float>( 4+1, 0 );
  for( int i = 1; i <= 4; ++i ) {
    if( AgeDistr[1] == 0 ) {
      DiskData.SerPos[1][i] = 0;
      DiskData.SerPos[2][i] = 0;
    }
    else {
      DiskData.SerPos[1][i] = (float) MatAnti[i].MANA / AgeDistr[1] * 100;
      DiskData.SerPos[2][i] = (float) MatAnti[i].MAEA / AgeDistr[1] * 100;
    }
  }
  for( int i = 1; i <= 18; ++i ) {
    for( int j = 1; j <= 4; ++j ) {
      if( AgeDistr[i] == 0 ) {
        DiskData.SerPos[i + 2][j] = 0;
      }
      else {
        DiskData.SerPos[i + 2][j] = (float) SerDistr[i][j] / AgeDistr[i] * 100;
      }
      Temp[j] = Temp[j] + DiskData.SerPos[i + 2][j];
    }
  }
  DiskData.SerPos[21][1] = 0;
  DiskData.SerPos[21][2] = 0;
  DiskData.SerPos[21][3] = 0;
  DiskData.SerPos[21][4] = 0;
  for( int i = 5; i <= 10; ++i ) {
    for( int j = 1; j <= 4; ++j ) {
      if( AgeDistr[i] == 0 ) {
        DiskData.SerPos[21][j] = 0;
      }
      else {
        DiskData.SerPos[21][j] = DiskData.SerPos[21][j] + (SerDistr[i][j] / AgeDistr[i] * 100);
      }
    }
  }
  for( int i = 1; i <= 4; ++i ) {
    DiskData.SerPos[21][i] = DiskData.SerPos[21][i] / 6;
  }
  DiskData.SerPos[22][1] = 0;
  DiskData.SerPos[22][2] = 0;
  DiskData.SerPos[22][3] = 0;
  DiskData.SerPos[22][4] = 0;
  for( int i = 11; i <= 18; ++i ) {   // 46-80+
    for( int j = 1; j <= 4; ++j ) {
      if( AgeDistr[i] == 0 ) {
        DiskData.SerPos[22][j] = 0;
      }
      else {
        DiskData.SerPos[22][j] = DiskData.SerPos[22][j] + (SerDistr[i][j] / AgeDistr[i] * 100);
      }
    }
  }
  for( int i = 1; i <= 4; ++i ) {
    DiskData.SerPos[22][i] = DiskData.SerPos[22][i] / 8;
  }
  for( int i = 1; i <= 4; ++i ) {
    DiskData.SerPos[23][i] = Temp[i] / 18;
  }
  DiskData.SeqInfVals = DlySeqInfVals;

  LocationOutput_[SpRecNum] = DiskData;
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
  return result;
}




void
dsport::MenuPostSim()
{
}



DailyLocationOutput &
dsport::GetLocationOutputByIndex( int index )
{
  return LocationOutput_[index];
}

