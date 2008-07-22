#include "StdAfx.h"
#include "SimLocation.h"
#include <cmath>

using namespace boost::gregorian;
using namespace sim::ds;



date BoostDateFromYearAndDayOfYear( int year, int day )
{
  return date(year, 1, 1 ) + date_duration( day - 1 );
}



SimLocation::SimLocation( const input::Location * location, sim::output::MosData * mosData )
: Location_(location),
  MosData_(mosData),
  Output_(new output::DensimOutput()),
  GasCoef(1.987f),
  CumulativeDeaths(std::vector<double>( 18+1, 0 )),
  CumulativeBirths(std::vector<double>( 18+1, 0 )),
  TotalDeaths(std::vector<int>( 18+1, 0 )),
  TotalBirths(std::vector<int>( 18+1, 0 )),
  AgeDistribution(std::vector<int>( 18+1, 0 )),
  InitialAgeDistribution(std::vector<int>( 18+1, 0 )),
  PopProp(std::vector<input::DemographicClass>( 18+1 )),
  SerProp(std::vector<std::vector<double>>( 18+1, std::vector<double>(4+1) )),
  SerDistr(std::vector<std::vector<int>>( 18+1, std::vector<int>(4+1, 0) )),
  InitSerDistr(std::vector<std::vector<int>>( 18+1, std::vector<int>(4+1, 0) )),
  Incub(std::vector<std::vector<int>>( 18+1, std::vector<int>( 4+1, 0 ) )),
  Infective(std::vector<std::vector<int>>( 18+1, std::vector<int>( 4+1, 0 ) )),
  HomImm(std::vector<std::vector<int>>( 18+1, std::vector<int>( 4+1, 0 ) )),
  HetImm(std::vector<std::vector<int>>( 18+1, std::vector<int>( 4+1, 0 ) )),
  MatAnti(std::vector<MaternalTransmission>( 4+1 )),
  CumHFDeaths(std::vector<double>( 15+1, 0 )),
  TotDlyIncub(std::vector<int>( 4+1, 0 )),
  TotDlyInfective(std::vector<int>( 4+1, 0 )),
  TotDlyHomImm(std::vector<int>( 4+1, 0 )),
  TotDlyHetImm(std::vector<int>( 4+1, 0 )),
  NewDlyInfective(std::vector<int>( 4+1, 0 )),
  Virus(std::vector<input::VirusSerotype>( 4+1 )),
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
  EIPFactor(std::vector<double>( 4+1, 0 )),
  MosqInfvTotal(std::vector<double>( 4+1, 0 ))
{
#ifdef _DEBUG
  // Unlike CIMSiM, where the option of random food delivery is the only stochastic process,
  // many processes in DENSiM are stochastic and cannot be done deterministically. In debug
  // mode we accomodate repeatability and comparability of output by setting the see constant
  srand(1);
#endif

  // define age classes
  AgeClasses[1].Rank = 1;
  AgeClasses[1].FDay = 1;
  AgeClasses[1].LDay = 364;

  AgeClasses[2].Rank = 2;
  AgeClasses[2].FDay = 365;
  AgeClasses[2].LDay = 1824;

  AgeClasses[3].Rank = 3;
  AgeClasses[3].FDay = 1825;
  AgeClasses[3].LDay = 3649;

  AgeClasses[4].Rank = 4;
  AgeClasses[4].FDay = 3650;
  AgeClasses[4].LDay = 5474;

  AgeClasses[5].Rank = 5;
  AgeClasses[5].FDay = 5475;
  AgeClasses[5].LDay = 7299;

  AgeClasses[6].Rank = 6;
  AgeClasses[6].FDay = 7300;
  AgeClasses[6].LDay = 9124;

  AgeClasses[7].Rank = 7;
  AgeClasses[7].FDay = 9125;
  AgeClasses[7].LDay = 10949;

  AgeClasses[8].Rank = 8;
  AgeClasses[8].FDay = 10950;
  AgeClasses[8].LDay = 12774;

  AgeClasses[9].Rank = 9;
  AgeClasses[9].FDay = 12775;
  AgeClasses[9].LDay = 14599;

  AgeClasses[10].Rank = 10;
  AgeClasses[10].FDay = 14600;
  AgeClasses[10].LDay = 16424;

  AgeClasses[11].Rank = 11;
  AgeClasses[11].FDay = 16425;
  AgeClasses[11].LDay = 18249;

  AgeClasses[12].Rank = 12;
  AgeClasses[12].FDay = 18250;
  AgeClasses[12].LDay = 20074;

  AgeClasses[13].Rank = 13;
  AgeClasses[13].FDay = 20075;
  AgeClasses[13].LDay = 21899;

  AgeClasses[14].Rank = 14;
  AgeClasses[14].FDay = 21900;
  AgeClasses[14].LDay = 23724;

  AgeClasses[15].Rank = 15;
  AgeClasses[15].FDay = 23725;
  AgeClasses[15].LDay = 25549;

  AgeClasses[16].Rank = 16;
  AgeClasses[16].FDay = 25550;
  AgeClasses[16].LDay = 27374;

  AgeClasses[17].Rank = 17;
  AgeClasses[17].FDay = 27375;
  AgeClasses[17].LDay = 29199;

  AgeClasses[18].Rank = 18;
  AgeClasses[18].FDay = 29200;
  AgeClasses[18].LDay = 30000;

  // demographics
  for( int i = 0; i < 18; i++ ) {
    PopProp[i+1] = Location_->Demographics_->DemographicData[i]; 
  }
  this->InitialPopSize = Location_->Demographics_->InitialPopulationSize;
  this->HumHostDensity = Location_->Demographics_->HumanHostDensity;

  // size population vectors based on InitialPopSize

  // virology
  Virus[1] = Location_->Virology_->Dengue1_;
  Virus[2] = Location_->Virology_->Dengue2_;
  Virus[3] = Location_->Virology_->Dengue3_;
  Virus[4] = Location_->Virology_->Dengue4_;

  this->MosqToHumProb = Location_->Virology_->MosquitoToHumanNominalProbabilityOfInfection_;
  this->StochTransNum = Location_->Virology_->MosquitoCountForStochasticity;

  this->HumToMosLTiter = Location_->Virology_->HumanToMosquitoInfection_.LowTiterSetPoint_;
  this->HumToMosLInf = Location_->Virology_->HumanToMosquitoInfection_.LowTiterInfection_;
  this->HumToMosHTiter = Location_->Virology_->HumanToMosquitoInfection_.HighTiterSetPoint_;
  this->HumToMosHInf = Location_->Virology_->HumanToMosquitoInfection_.HighTiterInfection_;

  this->EipLTiter = Location_->Virology_->Eip_.EipTiterModification_.LowSetPoint_;
  this->EipLFactor = Location_->Virology_->Eip_.EipTiterModification_.LowFactor_;
  this->EipHTiter = Location_->Virology_->Eip_.EipTiterModification_.HighSetPoint_;
  this->EipHFactor = Location_->Virology_->Eip_.EipTiterModification_.HighFactor_;

  this->EnzKinDR = Location_->Virology_->Eip_.Development_.RO25;
  this->EnzKinEA = Location_->Virology_->Eip_.Development_.DHA;
  this->EnzKinEI = Location_->Virology_->Eip_.Development_.DHH;
  this->EnzKinTI = Location_->Virology_->Eip_.Development_.THALF;


  // serology
  for( int i = 0; i < 18; ++i ) {
    this->SerProp[i+1][1] = Location_->Serology_->SerologyData_[i].Dengue1_;
    this->SerProp[i+1][2] = Location_->Serology_->SerologyData_[i].Dengue2_;
    this->SerProp[i+1][3] = Location_->Serology_->SerologyData_[i].Dengue3_;
    this->SerProp[i+1][4] = Location_->Serology_->SerologyData_[i].Dengue4_;
  }
  this->MANADurat = Location_->Serology_->ManaDuration_;
  this->MAEADurat = Location_->Serology_->MaeaDuration_;
  this->HetImmunDurat = Location_->Serology_->HetDuration_;


  // initialize infection schedules for available weather period
  date_period wxAvailable = Location_->Weather_->GetWeatherPeriod();
  date wxMinDate = wxAvailable.begin();
  date wxMaxDate = wxAvailable.end();

  Location_->InfectionIntroduction_->Dengue1_->Schedule_->CalculateSchedule( wxMinDate, wxMaxDate );
  Location_->InfectionIntroduction_->Dengue2_->Schedule_->CalculateSchedule( wxMinDate, wxMaxDate );
  Location_->InfectionIntroduction_->Dengue3_->Schedule_->CalculateSchedule( wxMinDate, wxMaxDate );
  Location_->InfectionIntroduction_->Dengue4_->Schedule_->CalculateSchedule( wxMinDate, wxMaxDate );

  // biology
  this->PropOnHum = Location_->Biology_->Adult->ProportionOfFeedsOnHumans;
  this->FdAttempts = Location_->Biology_->Adult->InterruptedFeedsPerMeal;
  this->PropDifHost = Location_->Biology_->Adult->ProportionOfInterruptedFeedsOnDifferentHost;
  this->PropOutdoor = Location_->Biology_->Adult->ProportionOfAdultsRestingOutdoors;
  this->DBloodLWt = Location_->Biology_->Adult->DoubleBloodMeal->LowWeightLimit;
  this->DBloodUWt = Location_->Biology_->Adult->DoubleBloodMeal->HighWeightLimit;
  this->DBloodUProp = Location_->Biology_->Adult->DoubleBloodMeal->HighWeightRatio;
  this->DBloodLProp = Location_->Biology_->Adult->DoubleBloodMeal->LowWeightRatio;


  // use same initial adult population as CIMSiM
  // the population from CIMSiM is on the spatial scale of a hectare
  // so we must scale by the current simulation size
  double initialArea = InitialPopSize / HumHostDensity;
  for( sim::cs::PreOviAdultCohortCollection::iterator itAdult = MosData_->PreOviAdultCohorts.begin();
       itAdult != MosData_->PreOviAdultCohorts.end(); ++itAdult ) {
    NewMosqSusc[itAdult->Age] = itAdult->Number * initialArea;
    NewMosqSuscCD[itAdult->Age] = itAdult->Development;
  }
  for( sim::cs::OviAdultCohortCollection::iterator itAdult = MosData_->OviAdultCohorts.begin();
       itAdult != MosData_->OviAdultCohorts.end(); ++itAdult ) {
    OldMosqSusc[itAdult->Age] = itAdult->Number * initialArea;
    OldMosqSuscCD[itAdult->Age] = itAdult->Development;
  }
}



SimLocation::~SimLocation(void)
{
}



void
SimLocation::Start(void)
{
  // no specified start/stop dates, use available weather
  date_period wxAvailable = Location_->Weather_->GetWeatherPeriod();
  BeginDate_ = wxAvailable.begin();
  EndDate_ = wxAvailable.end();

  denmain();
}



void
SimLocation::Start( boost::gregorian::date startDate, boost::gregorian::date stopDate )
{
  BeginDate_ = startDate;
  EndDate_ = stopDate;

  denmain();
}


  
sim::output::DensimOutput *
SimLocation::GetSimOutput(void)
{
  return Output_;
}


void
SimLocation::denmain(void)
{
  // initialize variables
  Year = 1;
  Day = 1;
  SimYear = 1;
  PopulationSize = 0;
  OldPopulationSize = 0;
  EIPTempAdjust = 0;
  // TODO fix this initialization?
  EndYear = EndDate_.year();

  InitializePopulation();
  InitializeSeroprevalence();
  CalculateEipTiterAdjustment();

  for( Year = BeginDate_.year(); Year <= EndDate_.year(); ++Year ) {
    int numDays = gregorian_calendar::is_leap_year( Year ) ? 366 : 365;

    BitesPerPerson = std::vector<double>( numDays+1, 0 );

    ReadWeather( Year );
    ReadMos( Year );

    for( Day = 1; Day <= numDays; ++Day ) {
      CalculateDeaths();
      CalculateBirths();
      AgePopulation();

      IntroduceInfection();
      PurgeMaternal();
      CalculateEip();

      AdvanceMosquitoes();
      HumanToMosquitoTransmission();
      MosquitoToHumanTransmission();

      RankPop();
      PurgeHFDeaths();

      SpoolToDisk();
    }

    SimYear = SimYear + 1;

    if( Year < EndYear ) {
      ReadWeather( Year );
      ReadMos( Year );
    }
  }

  // Update end of simulation data output
  Output_->SetFinalData( AgeDistribution, TotalBirths, TotalDeaths );

  return;
}



void
SimLocation::InitializePopulation(void)
{
  PopulationSize = 0;

  AgeDistribution = std::vector<int>( 18+1, 0 );
  InitialAgeDistribution = std::vector<int>( 18+1, 0 );

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
    int classSize = CINT( PopProp[iClass].Proportion * InitialPopSize );
    for( int iIndiv = 1; iIndiv <= classSize; ++iIndiv ) {
      int age = INT( (AgeClasses[iClass].LDay - AgeClasses[iClass].FDay + 1) * RND() + AgeClasses[iClass].FDay);
      PopulationSize = PopulationSize + 1;
      Indiv[PopulationSize] = age;
      AgeDistribution[iClass] = AgeDistribution[iClass] + 1;
      InitialAgeDistribution[iClass] = InitialAgeDistribution[iClass] + 1;
      if( age < AgeClasses[iClass].FDay || age > AgeClasses[iClass].LDay ) {
        // STOP  'debugging code
        throw;
      }

      Individuals.push_back( Individual(age) );
    }
  }

  // DS 1.0 doesn't specify it, but oldest individuals are first, this means the
  // Indiv vector is reverse sorted, we decrement the reverse end iterator so
  // sort doesn't access position 0, which is not used in our 1's indexed vectors
  std::sort( Indiv.rbegin(), --(Indiv.rend()) );
  OldPopulationSize = PopulationSize;
  InitPopulationSize = PopulationSize;
  std::sort( Individuals.begin(), Individuals.end(), DescendingAgeSort() );
  ComparePopulation();

  // save initial age distribution to output
  Output_->SetInitialData( InitialAgeDistribution );
}



void
SimLocation::InitializeSeroprevalence(void)
{
  // Initialize the seroprevalence data
  // This data confers previous homologous immunity (designated by -2)
  // Oldest individuals have the smallest subscripts.
  
  Deng1 = std::vector<int>( MaxPopSize+1, 0 );
  Deng2 = std::vector<int>( MaxPopSize+1, 0 );
  Deng3 = std::vector<int>( MaxPopSize+1, 0 );
  Deng4 = std::vector<int>( MaxPopSize+1, 0 );
  InitSerDistr = std::vector<std::vector<int>>( 18+1, std::vector<int>(4+1, 0) );

  int iPos = 0;                       // base for indexing into individuals, by adding iElement, this is the position right before the start of a class
  for( int i = 18; i >= 1; --i ) {    // each age class
    for( int j = 1; j <= 4; ++j ) {   // each serotype

      // calculate the number of individuals with homologuos immunity to this serotype in this age class
      int iNewInfect = CINT(SerProp[i][j] * AgeDistribution[i]);
      if( iNewInfect > 0 ) {
        // assign infections to individuals
        for( int k = 1; k <= iNewInfect; ++k ) {
          bool iSuscept = false;
          do {
            // find an individual in this age class to mark with homologuos immunity
            int iElement = INT( (AgeDistribution[i] - 1 + 1) * RND() + 1 );
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
            Population::iterator itIndiv = Individuals.begin() + iPos + iElement - 1;
            itIndiv->InitializeImmunity(j);
          } while ( iSuscept != true );
        }
      }
    }
    iPos = iPos + AgeDistribution[i];
  }
  ComparePopulationAndSerotypes();
}



void
SimLocation::CalculateEipTiterAdjustment(void)
{
  // calculate EIP by titer
  for( int i = 1; i <= 4; ++i ) {
    if( Virus[i].Viremia_ < EipLTiter ) {
      EIPFactor[i] = EipLFactor;
    }
    else if( Virus[i].Viremia_ > EipHTiter ) {
      EIPFactor[i] = EipHFactor;
    }
    else {
      double slope = (EipLFactor - EipHFactor) / (EipHTiter - EipLTiter);
      EIPFactor[i] = EipLFactor - (Virus[i].Viremia_ - EipLTiter) * slope;
    }
  }
}



void
SimLocation::CalculateDeaths(void)
{
  int iPos = 0;     // start with array position 1, or the oldest individual

  for( int i = 18; i >= 1; --i ) {

    // calculate cumulative age class death rate
    double DRate = (PopProp[i].DeathRate / 1000) * (1 / (double) YrLen);
    // add deaths to previous fractional remainder
    CumulativeDeaths[i] = CumulativeDeaths[i] + (AgeDistribution[i] * DRate);

    // subtract deaths from Indiv() array
    if( CumulativeDeaths[i] >= 1 && AgeDistribution[i] > 0 ) {
      for( int j = 1; j <= INT(CumulativeDeaths[i]); ++j ) {
        // pick a random individual - taken from the number of individuals
        // in an age class - and remove.  Compress the array.
        int iElement = INT((AgeDistribution[i] - 1 + 1) * RND() + 1);
        int iNumElsLeft = PopulationSize - (iPos + iElement);

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
        PopulationSize = PopulationSize - 1;
        AgeDistribution[i] = AgeDistribution[i] - 1;
        TotalDeaths[i] = TotalDeaths[i] + 1;
        if( AgeDistribution[i] <= 0 ) {
          break;
        }

        Individuals.erase( Individuals.begin() + iPos + iElement - 1 );
        ComparePopulationAndSerotypes();
      }
    }
    iPos = iPos + AgeDistribution[i];
    CumulativeDeaths[i] = CumulativeDeaths[i] - INT(CumulativeDeaths[i]);
  }
}



void
SimLocation::CalculateBirths(void)
{
  int iPos = 0;           // start with array pos. 1, or the oldest individuals

  for( int i = 18; i >= 1; --i ) {

    // calculate cumulative age class birth rate
    double BRate = (PopProp[i].BirthRate / 1000) * (1 / (double) YrLen);
    // only females contribute to birth
    CumulativeBirths[i] = CumulativeBirths[i] + ((AgeDistribution[i] / (double) 2) * BRate);

    // add Births to Indiv() array
    if( CumulativeBirths[i] >= 1 ) {
      for( int j =1; j <= INT( CumulativeBirths[i] ); ++j ) {
        PopulationSize = PopulationSize + 1;            // add an element, i.e. an individual, to the array

        // TODO - figure out memory limitations

        Indiv[PopulationSize] = 1;        // one day old

        // record maternally acquired seroprev. type by randomly selecting individual
        // in this age class as the mother
        // -1 denotes maternally acquired
        // -2 denotes homologous immunity for seroprevalence intitialization
        int iElement = INT((AgeDistribution[i] - 1 + 1) * RND() + 1);
        if( Deng1[iPos + iElement] > 0 || Deng1[iPos + iElement] == -2 ) {
          // if positive for homologuos immunity, confer maternally acquired immunity on birth
          Deng1[PopulationSize] = -1;
        }
        if( Deng2[iPos + iElement] > 0 || Deng2[iPos + iElement] == -2 ) {
          Deng2[PopulationSize] = -1;
        }
        if( Deng3[iPos + iElement] > 0 || Deng3[iPos + iElement] == -2 ) {
          Deng3[PopulationSize] = -1;
        }
        if( Deng4[iPos + iElement] > 0 || Deng4[iPos + iElement] == -2 ) {
          Deng4[PopulationSize] = -1;
        }

        AgeDistribution[1] = AgeDistribution[1] + 1;        // update age distribution data
        TotalBirths[i] = TotalBirths[i] + 1;      // simulation tally

        Individual newBirth = Individual(1);
        Individual & mother = *(Individuals.begin() + iPos + iElement - 1);
        for( int serotype = 1; serotype <= 4; ++serotype ) {
          if( mother.HasHomologousImmunity(serotype) ) {
            newBirth.InitializeMaternallyAcquiredImmunity(serotype);
          }
        }
        Individuals.push_back( newBirth );
        ComparePopulationAndSerotypes();
      }
      CumulativeBirths[i] = CumulativeBirths[i] - INT(CumulativeBirths[i]);
    }
    iPos = iPos + AgeDistribution[i];
  }
}



void
SimLocation::AgePopulation(void)
{
  // age population
  for( int k = 1; k <= PopulationSize; ++k ) {
    Indiv[k] = Indiv[k] + 1;
    if( Indiv[k] > AgeClasses[18].LDay ) {
      Indiv[k] = AgeClasses[18].LDay;           // don't age individuals older than limits of oldest class
    }
  }

  for( Population::iterator itIndiv = Individuals.begin(); itIndiv != Individuals.end(); ++itIndiv ) {
    itIndiv->Age++;
    if( itIndiv->Age > AgeClasses[18].LDay ) {
      itIndiv->Age = AgeClasses[18].LDay;           // don't age individuals older than limits of oldest class
    }
  }

  ComparePopulationAndSerotypes();
}



void
SimLocation::IntroduceInfection(void)
{
  // add infective humans/mosquitoes
  date curDay = BoostDateFromYearAndDayOfYear( Year, Day );

  // initialize infective mosquitoes for the 4 serotypes
  for( int seroType = 1; seroType <= 4; ++seroType ) {

    // get serotype introduction object for this serotype
    input::SerotypeIntroduction * serotypeIntro = Location_->InfectionIntroduction_->GetSerotype(seroType);

    //if( AddedInfections[seroType][Day] && VirusIntro[seroType].Mosq > 0 ) {
    if( serotypeIntro->Schedule_->IsDateScheduled( curDay ) && serotypeIntro->Mosquitoes_ > 0 ) {
      // look for empty position in the old infected array and add.  This way the
      // new infectives will drop to position 1 in the infective array and
      // become new blood feeders on this day.
      // If no free space is found, then add to last position in the array.
      bool ifound = false;
      for( int i = 1; i <= MaxAgeMosq; ++i ) {
        if( OldMosqInfd[i][seroType] == 0 ) {
          //OldMosqInfd[i][seroType] = VirusIntro[seroType].Mosq;
          OldMosqInfd[i][seroType] = serotypeIntro->Mosquitoes_;
          OldMosqInfdCD[i][seroType] = 1.1f;
          OldMosqInfdEIP[i][seroType] = 1.1f;
          ifound = true;
          break;
        }
      }
      if( ifound != true ) {
        // no open position found, accumulate into the oldest cohort of old infecteds
        OldMosqInfd[MaxAgeMosq][seroType] = OldMosqInfd[MaxAgeMosq][seroType] + serotypeIntro->Mosquitoes_;
        OldMosqInfdCD[MaxAgeMosq][seroType] = 1.1f;
        OldMosqInfdEIP[MaxAgeMosq][seroType] = 1.1f;
      }
    }
  }

  // initialize infective humans
  for( int seroType = 1; seroType <= 4; ++seroType ) {
    // get serotype introduction object for this serotype
    input::SerotypeIntroduction * serotypeIntro = Location_->InfectionIntroduction_->GetSerotype(seroType);

    //if( AddedInfections[seroType][Day] && VirusIntro[seroType].Hums > 0 ) {
    if( serotypeIntro->Schedule_->IsDateScheduled( curDay ) && serotypeIntro->Humans_ > 0 ) {
      for( int i = 1; i <= serotypeIntro->Humans_; ++i ) {
        // Increase current population size
        PopulationSize = PopulationSize + 1;
        int IAge = 0;
        int iPos = 0;
        switch (seroType) {
          case 1:
            IAge = INT((AgeClasses[18].LDay - (Virus[1].IncubationDuration_ + 1) + 1) * RND() + (Virus[1].IncubationDuration_ + 1));
            iPos = DeterminePosition( IAge );
            Indiv[iPos] = IAge;
            Deng1[iPos] = IAge - Virus[1].IncubationDuration_;
            if( IAge - Virus[1].IncubationDuration_ <= 0) {
              // STOP  'debugging code
            }
            break;
          case 2:
            IAge = INT((AgeClasses[18].LDay - (Virus[2].IncubationDuration_ + 1) + 1) * RND() + (Virus[2].IncubationDuration_ + 1));
            iPos = DeterminePosition( IAge );
            Indiv[iPos] = IAge;
            Deng2[iPos] = IAge - Virus[2].IncubationDuration_;
            if( IAge - Virus[2].IncubationDuration_ <= 0) {
              // STOP  'debugging code
            }
            break;
          case 3:
            IAge = INT((AgeClasses[18].LDay - (Virus[3].IncubationDuration_ + 1) + 1) * RND() + (Virus[3].IncubationDuration_ + 1));
            iPos = DeterminePosition( IAge );
            Indiv[iPos] = IAge;
            Deng3[iPos] = IAge - Virus[3].IncubationDuration_;
            if( IAge - Virus[3].IncubationDuration_ <= 0) {
              // STOP  'debugging code
            }
            break;
          case 4:
            IAge = INT((AgeClasses[18].LDay - (Virus[4].IncubationDuration_ + 1) + 1) * RND() + (Virus[4].IncubationDuration_ + 1));
            iPos = DeterminePosition( IAge );
            Indiv[iPos] = IAge;
            Deng4[iPos] = IAge - Virus[4].IncubationDuration_;
            if( IAge - Virus[4].IncubationDuration_ <= 0) {
              // STOP  'debugging code
            }
            break;
        }
        //// by incrementing PopulationSize, DS 1.0 effectively added a new individual with age 0
        //Individuals.push_back( Individual(0) );
        //Population::iterator itIndiv = Individuals.begin() + iPos - 1;
        //itIndiv->Age = IAge;
        //// DS effectively overwrites any existing status to specified serotype
        //itIndiv->SetNewInfection( seroType, IAge - Virus[seroType].IncubationDuration_ );

        // insert before existing individual
        Population::iterator itIndiv = Individuals.begin() + iPos - 1;

        // artifact of DS arrays is new individual has previous individuals immunities
        Individual introducedIndividual = Individual( *itIndiv );
        introducedIndividual.Age = IAge;
        introducedIndividual.Infect( seroType, IAge - Virus[seroType].IncubationDuration_ );

        Individuals.insert( Individuals.begin() + iPos - 1, introducedIndividual );
        ComparePopulationAndSerotypes();
      }
    }
  }
}



int
SimLocation::DeterminePosition( int IAge )
{
  int iPos;
  // check for extremes
  if( IAge >= Indiv[1] ) {
    // they become the oldest individual
    for( int k = PopulationSize; k >= 2; --k ) {
      Indiv[k] = Indiv[k - 1];
      Deng1[k] = Deng1[k - 1];
      Deng2[k] = Deng2[k - 1];
      Deng3[k] = Deng3[k - 1];
      Deng4[k] = Deng4[k - 1];
    }
    iPos = 1;
    return iPos;
  }
  if( IAge <= Indiv[PopulationSize - 1] ) {
    // they become the youngest individual
    iPos = PopulationSize;
    return iPos;
  }
  // somewhere in the middle
  for( iPos = 2; iPos <= (PopulationSize - 1); ++iPos ) {       // last position is new
    if( IAge <= Indiv[iPos - 1] && IAge >= Indiv[iPos] ) {
      // position found
      for( int k = PopulationSize; k >= iPos + 1; --k ) {
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
SimLocation::PurgeMaternal(void)
{
  int purgePeriod = MANADurat + MAEADurat;

  for( int i = PopulationSize; i >= 1; --i ) {
    if( Indiv[i] > purgePeriod + 20 ) {
      break;                            // buffer region - ages sequential so no need for further searches
    }
    if( Indiv[i] >= purgePeriod ) {
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

  Population::reverse_iterator itIndiv;
  for( itIndiv = Individuals.rbegin(); itIndiv != Individuals.rend(); ++itIndiv ) {
    if( itIndiv->Age > purgePeriod + 20 ) {
      break;
    }
    if( itIndiv->Age >= purgePeriod ) {
      itIndiv->PurgeMaternalImmunity();
    }
  }

  ComparePopulationAndSerotypes();
}



void
SimLocation::CalculateEip(void)
{
  for( int k = 1; k <=4; ++k ) {
    if( EIPFactor[k] == 0 ) {
      // STOP
    }
    EIPDevRate[k] = EIPEnzKin(TemperatureAvg[Day] + EIPTempAdjust + 273.15f) / EIPFactor[k];
  }
}



void
SimLocation::AdvanceMosquitoes(void)
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

  std::vector<double> BitersInfd( 4+1, 0 );        // infected biters
  std::vector<double> EIPTranNew( 4+1, 0 );        // Infective class from infected new
  std::vector<double> EIPTranOld( 4+1, 0 );        // Infective class from infected old
  std::vector<double> EggersInfv( 4+1, 0 );        // Infective egg transfers
  BitersInfv = std::vector<double>( 4+1, 0 );      // total infective biters
  
  if( SimYear == 1 && Day == 1 ) {
    // initialize static variables
    BitersInfdNewDB = std::vector<double>( 4+1, 0 );
    BitersInfdOldDB = std::vector<double>( 4+1, 0 );
  }

  date curDate = BoostDateFromYearAndDayOfYear( Year, Day );
  output::DailyMosData dailyMosData = YearlyMosData_.GetDailyMosData(curDate);

  // calculate proportion taking a double blood meal
  double DMealProp = 0;
  if( dailyMosData.AverageWeight <= DBloodLWt ) {
    DMealProp = DBloodUProp;
  }
  else if( dailyMosData.AverageWeight >= DBloodUWt ) {
    DMealProp = DBloodLProp;
  }
  else {
    if( (DBloodUWt - DBloodLWt) == 0 ) {
      throw;  // STOP
    }
    double Slope = (DBloodUProp - DBloodLProp) / (DBloodUWt - DBloodLWt);
    DMealProp = DBloodUProp - ((dailyMosData.AverageWeight - DBloodLWt) * Slope);
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
        NewMosqSusc[i + 1] = NewMosqSusc[i] * dailyMosData.OverallSurvival;
        NewMosqSuscCD[i + 1] = NewMosqSuscCD[i] + dailyMosData.AdultDevelopment;
      }
      else {
        EggersNew = EggersNew + (NewMosqSusc[i] * dailyMosData.OverallSurvival);
      }
      NewMosqSusc[i] = 0;
      NewMosqSuscCD[i] = 0;
    }
  }

  // adjust cimsim mosq pop(per ha) for current population size
  if( HumHostDensity == 0 ) {
    throw; // STOP 
  }
  NewMosqSusc[1] = dailyMosData.NewFemales * (PopulationSize / HumHostDensity);
  NewMosqSuscCD[1] = dailyMosData.AdultDevelopment;
  BitersNew = NewMosqSusc[2] + (NewMosqSusc[3] * DMealProp);


  // advance susceptibles - successive gonotrophic cycles
  // last position in the array does not accumulate
  BitersOld = 0;
  double EggersOld = 0;
  for( int i = MaxAgeMosq; i >= 1; --i ) {
    if( OldMosqSusc[i] <= 0 ) {
      continue;
    }
    else {
      if( OldMosqSuscCD[i] <= .58 ) {
        OldMosqSusc[i + 1] = OldMosqSusc[i] * dailyMosData.OverallSurvival;
        OldMosqSuscCD[i + 1] = OldMosqSuscCD[i] + dailyMosData.AdultDevelopment;
      }
      else {
        EggersOld = EggersOld + (OldMosqSusc[i] * dailyMosData.OverallSurvival);
      }
      OldMosqSusc[i] = 0;
      OldMosqSuscCD[i] = 0;
    }
  }
  OldMosqSusc[1] = EggersNew + EggersOld;
  OldMosqSuscCD[1] = dailyMosData.AdultDevelopment;
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
        double OldAdultDev;
        if( Day == 1 ) {
          // find last day of current year
          //OldAdultDev = CimsimOutput[365].AdultDev;
          date lastDayOfCurYear = date( Year, 12, 31 );
          OldAdultDev = YearlyMosData_.GetDailyMosData(lastDayOfCurYear).AdultDevelopment;
        }
        else {
          date today = BoostDateFromYearAndDayOfYear(Year,Day);
          date yesterday = today - date_duration(1);
          OldAdultDev = YearlyMosData_.GetDailyMosData(yesterday).AdultDevelopment;
        }

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
          EIPTranNew[j] = EIPTranNew[j] + (NewMosqInfd[i][j] * dailyMosData.OverallSurvival);
        }
        else {
          NewMosqInfd[i + 1][j] = NewMosqInfd[i][j] * dailyMosData.OverallSurvival;
          NewMosqInfdCD[i + 1][j] = NewMosqInfdCD[i][j] + dailyMosData.AdultDevelopment;
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
          EIPTranOld[j] = EIPTranOld[j] + (OldMosqInfd[i][j] * dailyMosData.OverallSurvival);
        }
        else {
          OldMosqInfd[i+1][j] = OldMosqInfd[i][j] * dailyMosData.OverallSurvival;
          if( OldMosqInfdCD[i][j] > .58 ) {
            BitersInfd[j] = BitersInfd[j] + OldMosqInfd[i+1][j];
            BitersInfdOldDB[j] = BitersInfdOldDB[j] + (OldMosqInfd[i+1][j] * DMealProp);
            OldMosqInfdCD[i+1][j] = dailyMosData.AdultDevelopment;
          }
          else {
            OldMosqInfdCD[i+1][j] = OldMosqInfdCD[i][j] + dailyMosData.AdultDevelopment;
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
          MosqInfv[i+1][j] = MosqInfv[i][j] * dailyMosData.OverallSurvival;
          MosqInfvCD[i+1][j] = MosqInfvCD[i][j] + dailyMosData.AdultDevelopment;
        }
        else {
          EggersInfv[j] = EggersInfv[j] + (MosqInfv[i][j] * dailyMosData.OverallSurvival);
        }
        MosqInfv[i][j] = 0;
        MosqInfvCD[i][j] = 0;
      }
    }
    MosqInfv[1][j] = EggersInfv[j] + EIPTranNew[j] + EIPTranOld[j];
    MosqInfvCD[1][j] = dailyMosData.AdultDevelopment;
    BitersInfv[j] = MosqInfv[1][j] + (MosqInfv[2][j] * DMealProp);
  }

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
SimLocation::HumanToMosquitoTransmission(void)
{
  // Number of susceptible probes per individual
  BitesPerPerson[Day] = (BitersNew + BitersOld) * PropOnHum;
  BitesPerPerson[Day] = BitesPerPerson[Day] + (BitesPerPerson[Day] * (FdAttempts - 1) * PropDifHost);
  if( PopulationSize == 0 ) {
    throw; // STOP
  }
  BitesPerPerson[Day] = BitesPerPerson[Day] / PopulationSize;


  // randomly calculate new mosquito infections for four serotypes
  std::vector<int> seroTypesCompleted;
  // loop until all four sero types are processed
  while(true) {
    int i = INT( (4 - 1 + 1) * RND() + 1 );
    std::vector<int>::iterator findResult;
    findResult = std::find( seroTypesCompleted.begin(), seroTypesCompleted.end(), i );
    if( findResult == seroTypesCompleted.end() ) {
      // serotype "i" has not been processed yet
      InnoculateMosquitoes(i);
      seroTypesCompleted.push_back(i);
    }
    if( seroTypesCompleted.size() == 4 ) {
      // all 4 serotypes completed
      break;
    }
  }
}



void
SimLocation::InnoculateMosquitoes( int iType )
{
  int r;                    // for poisson distribution
  double InocEstimate;       // Number of mosq to be infected
  int NewDlyMosqInoc;       // actual number of new infected mosq. (differs due to/if stochastic routines enabled)
  int OldInfd;              // new infected from old susceptible
  int NewInfd;              // new infected from new susceptible

  // calculate probability of infection and  estimate newly inoculated mosquitoes
  // Viremia is in scientific notation and Titers are in logs
  double ProbInf = 0;
  if( log(Virus[iType].Viremia_) / log(10.0) <= HumToMosLTiter ) {
    ProbInf = HumToMosLInf;
  }
  else if( log(Virus[iType].Viremia_) / log(10.0) >= HumToMosHTiter ) {
    ProbInf = HumToMosHInf;
  }
  else {
    if( (HumToMosHTiter - HumToMosLTiter) == 0 ) {
      throw; // STOP
    }
    double Slope = (HumToMosHInf - HumToMosLInf) / (HumToMosHTiter - HumToMosLTiter);
    ProbInf = HumToMosHInf - ((HumToMosHTiter - (log(Virus[iType].Viremia_) / log(10.0f))) * Slope);
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
    double num = RND();
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
    
    date curDate = BoostDateFromYearAndDayOfYear( Year, Day );
    output::DailyMosData dailyMosData = YearlyMosData_.GetDailyMosData(curDate);

    // adjust infected mosquito arrays
    OldMosqInfd[1][iType] = OldInfd;
    NewMosqInfd[1][iType] = NewInfd;
    OldMosqInfdCD[1][iType] = dailyMosData.AdultDevelopment;
    NewMosqInfdCD[1][iType] = dailyMosData.AdultDevelopment;
    OldMosqInfdEIP[1][iType] = EIPDevRate[iType];
    NewMosqInfdEIP[1][iType] = EIPDevRate[iType];
  }
}



void
SimLocation::MosquitoToHumanTransmission()
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
      InnoculateHumans( iType );
      seroTypesCompleted.push_back( iType );
    }
    if( seroTypesCompleted.size() == 4 ) {
      // all 4 serotypes completed
      break;
    }
  }
}




void
SimLocation::InnoculateHumans( int iType )
{
  int iOldAge = AgeClasses[18].FDay;    // reset age for oldest age class individuals who become infected
  int r;                                // for poisson distribution
  double InocEstimate;                  // number of infv bites to humans

  InocEstimate = ((BitersInfv[iType] * PropOnHum) + ((BitersInfv[iType] * PropOnHum) * (FdAttempts - 1) * PropDifHost)) * MosqToHumProb;

  if( InocEstimate > StochTransNum ) {
    // discrete
    NewDlyHumInoc = CINT( InocEstimate );
  }

  else if( InocEstimate > 0 ) {
    // stochastic
    double num = RND();
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

    // randomly select individual for new innoculation
    int iElement = INT( (PopulationSize - 1 + 1) * RND() + 1);

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

    Population::iterator itIndiv = Individuals.begin() + iElement - 1;

    if( itIndiv->IsSeropositive(iType) ){
      if( itIndiv->HasMaternallyAcquiredImmunity( iType ) ) {
        if( itIndiv->Age > MANADurat ) {
          // neutralizing period expired, now enhancing, infection occurs
          itIndiv->Infect( iType, itIndiv->Age );
        }
      }
      else {
        // homologous immunity, either initialized or from previous infection
      }
    }
    else {
      if( !itIndiv->HasHeterologousImmunity( iType, HetImmunDurat ) ) {
        // no heterologous immunity, normal infection
        if( itIndiv->Age > iOldAge ) {
          itIndiv->Age = iOldAge;
        }
        itIndiv->Infect( iType, itIndiv->Age );
      }
    }

    ComparePopulationAndSerotypes();
  }
}



void
SimLocation::RankPop(void)
{
  AgeDistribution = std::vector<int>( 18+1, 0 );                                      // clear last tally
  SerDistr = std::vector<std::vector<int>>( 18+1, std::vector<int>(4+1, 0) );         // clear last tally
  Incub = std::vector<std::vector<int>>( 18+1, std::vector<int>(4+1, 0) );            // clear last tally
  Infective = std::vector<std::vector<int>>( 18+1, std::vector<int>(4+1, 0) );        // clear last tally
  HomImm = std::vector<std::vector<int>>( 18+1, std::vector<int>(4+1, 0) );           // clear last tally
  HetImm = std::vector<std::vector<int>>( 18+1, std::vector<int>(4+1, 0) );           // clear last tally
  MatAnti = std::vector<MaternalTransmission>( 4+1 );                                 // clear last tally
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
  for( int i = 1; i <= PopulationSize; ++i ) {
    if( Indiv[i] >= AgeClasses[iRank].FDay ) {
      AgeDistribution[iRank] = AgeDistribution[iRank] + 1;
      SeroRank(i, iRank);
    }
    else {
      int j;
      for( j = iRank - 1; j >= 1; --j ) {           // find next ranking
        if( Indiv[i] >= AgeClasses[j].FDay ) {
          // found individuals new rank
          break;
        }
      }
      iRank = j;
      if( iRank < 1 ) {
        throw; // STOP
      }
      AgeDistribution[iRank] = AgeDistribution[iRank] + 1;
      SeroRank(i, iRank);
    }
  }
}



void
SimLocation::SeroRank( int iElement, int iRank )
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
      if( iTemp < Virus[1].IncubationDuration_ ) {
        Incub[iRank][1] = Incub[iRank][1] + 1;
        TotDlyIncub[1] = TotDlyIncub[1] + 1;
      }
      else if( iTemp < Virus[1].ViremicDuration_ + Virus[1].IncubationDuration_ ) {
        // check for infectious virus
        Infective[iRank][1] = Infective[iRank][1] + 1;
        TotDlyInfective[1] = TotDlyInfective[1] + 1;
        if( iTemp == Virus[1].IncubationDuration_ ) {
          // New infectives for the day
          NewDlyInfective[1] = NewDlyInfective[1] + 1;
        }
        if( iTemp > Virus[1].IncubationDuration_ + (Virus[1].ViremicDuration_ / 2) ) {
          // latter half of viremic phase, check for HF/SS
          CalcSeqInfs(1, Indiv[i], Deng1[i], Deng2[i], Deng3[i], Deng4[i]);
        }
      }
      else {
        // check for heterologous immunity
        if( iTemp < HetImmunDurat + Virus[1].ViremicDuration_ + Virus[1].IncubationDuration_ ) {
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
      if( iTemp < Virus[2].IncubationDuration_ ) {
        Incub[iRank][2] = Incub[iRank][2] + 1;
        TotDlyIncub[2] = TotDlyIncub[2] + 1;
      }
      else if( iTemp < Virus[2].ViremicDuration_ + Virus[2].IncubationDuration_ ) {
        // check for infectious virus
        Infective[iRank][2] = Infective[iRank][2] + 1;
        TotDlyInfective[2] = TotDlyInfective[2] + 1;
        if( iTemp == Virus[2].IncubationDuration_ ) {
          // New infectives for the day
          NewDlyInfective[2] = NewDlyInfective[2] + 1;
        }
        if( iTemp > Virus[2].IncubationDuration_ + (Virus[2].ViremicDuration_ / 2) ) {
          // latter half of viremic phase, check for HF/SS
          CalcSeqInfs(2, Indiv[i], Deng1[i], Deng2[i], Deng3[i], Deng4[i]);
        }
      }
      else {
        // check for heterologous immunity
        if( iTemp < HetImmunDurat + Virus[2].ViremicDuration_ + Virus[2].IncubationDuration_ ) {
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
      if( iTemp < Virus[3].IncubationDuration_ ) {
        Incub[iRank][3] = Incub[iRank][3] + 1;
        TotDlyIncub[3] = TotDlyIncub[3] + 1;
      }
      else if( iTemp < Virus[3].ViremicDuration_ + Virus[3].IncubationDuration_ ) {
        // check for infectious virus
        Infective[iRank][3] = Infective[iRank][3] + 1;
        TotDlyInfective[3] = TotDlyInfective[3] + 1;
        if( iTemp == Virus[3].IncubationDuration_ ) {
          // New infectives for the day
          NewDlyInfective[3] = NewDlyInfective[3] + 1;
        }
        if( iTemp > Virus[3].IncubationDuration_ + (Virus[3].ViremicDuration_ / 2) ) {
          // latter half of viremic phase, check for HF/SS
          CalcSeqInfs(3, Indiv[i], Deng1[i], Deng2[i], Deng3[i], Deng4[i]);
        }
      }
      else {
        // check for heterologous immunity
        if( iTemp < HetImmunDurat + Virus[3].ViremicDuration_ + Virus[3].IncubationDuration_ ) {
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
      if( iTemp < Virus[4].IncubationDuration_ ) {
        Incub[iRank][4] = Incub[iRank][4] + 1;
        TotDlyIncub[4] = TotDlyIncub[4] + 1;
      }
      else if( iTemp < Virus[4].ViremicDuration_ + Virus[4].IncubationDuration_ ) {
        // check for infectious virus
        Infective[iRank][4] = Infective[iRank][4] + 1;
        TotDlyInfective[4] = TotDlyInfective[4] + 1;
        if( iTemp == Virus[4].IncubationDuration_ ) {
          // New infectives for the day
          NewDlyInfective[4] = NewDlyInfective[4] + 1;
        }
        if( iTemp > Virus[4].IncubationDuration_ + (Virus[4].ViremicDuration_ / 2) ) {
          // latter half of viremic phase, check for HF/SS
          CalcSeqInfs(4, Indiv[i], Deng1[i], Deng2[i], Deng3[i], Deng4[i]);
        }
      }
      else {
        // check for heterologous immunity
        if( iTemp < HetImmunDurat + Virus[4].ViremicDuration_ + Virus[4].IncubationDuration_ ) {
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
SimLocation::CalcSeqInfs( int iVirType, int iPerAge, int iD1Inoc, int iD2Inoc, int iD3Inoc, int iD4Inoc )
{
  // calculates daily sequential infection and MAEA statistics
  // applies death to those with hf/ss - assigns Indiv(i) age of -999 for later analysis.

  // sequential infection parameters
  input::SequentialInfection * seqInf;
  input::SequentialInfection * MAEASeqInf;

  switch( iVirType ) {                                        // what is indiv. viremic for - secondary infection

    case 1: {                                                 // dengue 1 viremia

      if( iD2Inoc > 0 || iD3Inoc > 0 || iD4Inoc > 0 ) {       // with some sort of sequential infection present

        seqInf = Location_->SequentialInfections_->GetSequentialInfection("2","1");
        // look for 2-1
        if( iD2Inoc > 0 && iPerAge < (seqInf->AtRiskCutoffAge_ * 365) + 365 ) {
          // 2-1 sequence found - indiv is proper age
          int ElapsedTime = iD1Inoc - iD2Inoc;
          if(  ElapsedTime > (seqInf->MinMonths_ * 30) && ElapsedTime < (seqInf->MaxMonths_ * 30)  ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F2T1 = DlySeqInfVals.F2T1 + (1 * seqInf->Probability_);
            if( seqInf->Probability_ * seqInf->Mortality_ > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }

        seqInf = Location_->SequentialInfections_->GetSequentialInfection("3","1");
        // look for 3-1
        if( iD3Inoc > 0 && iPerAge < (seqInf->AtRiskCutoffAge_ * 365) + 365 ) {
          // 3-1 sequence found - indiv is proper age
          int ElapsedTime = iD1Inoc - iD3Inoc;
          if( ElapsedTime > (seqInf->MinMonths_ * 30) && ElapsedTime < (seqInf->MaxMonths_ * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F3T1 = DlySeqInfVals.F3T1 + (1 * seqInf->Probability_);
            if( seqInf->Probability_ * seqInf->Mortality_ > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }

        seqInf = Location_->SequentialInfections_->GetSequentialInfection("4","1");
        // look for 4-1
        if( iD4Inoc > 0 && iPerAge < (seqInf->AtRiskCutoffAge_ * 365) + 365 ) {
          // 4-1 sequence found - indiv is proper age
          int ElapsedTime = iD1Inoc - iD4Inoc;
          if( ElapsedTime > (seqInf->MinMonths_ * 30) && ElapsedTime < (seqInf->MaxMonths_ * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F4T1 = DlySeqInfVals.F4T1 + (1 * seqInf->Probability_);
            if( seqInf->Probability_ * seqInf->Mortality_ > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }
      }
      else {  // no subtype sequential infection - check for MAEA to subtype sequential
        MAEASeqInf = Location_->SequentialInfections_->GetSequentialInfection("MAEA","1");
        // look for MAEA-1
        if( iPerAge < MANADurat + MAEADurat ) {
          // indiv is viremic and enhancing
          DlySeqInfVals.FMT1 = DlySeqInfVals.FMT1 + (1 * MAEASeqInf->Probability_);
          if( MAEASeqInf->Probability_ * MAEASeqInf->Mortality_ > RND() ) {
            // individual dies
            AgeAtDeath( iPerAge );
            iPerAge = -999;
            return;
          }
        }
      }
      break;
    }

    case 2: {                                                   // dengue 2 viremia

      if( iD1Inoc > 0 || iD3Inoc > 0 || iD4Inoc > 0 ) {         // with some sort of sequential infection is present

        seqInf = Location_->SequentialInfections_->GetSequentialInfection("1","2");
        // look for 1-2
        if( iD1Inoc > 0 && iPerAge < (seqInf->AtRiskCutoffAge_ * 365) + 365 ) {
          // 1-2 sequence found - indiv is proper age
          int ElapsedTime =iD2Inoc - iD1Inoc;
          if( ElapsedTime > (seqInf->MinMonths_ * 30) && ElapsedTime < (seqInf->MaxMonths_ * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F1T2 = DlySeqInfVals.F1T2 + (1 * seqInf->Probability_);
            if( seqInf->Probability_ * seqInf->Mortality_ > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }

        seqInf = Location_->SequentialInfections_->GetSequentialInfection("3","2");
        // look for 3-2
        if( iD3Inoc > 0 && iPerAge < (seqInf->AtRiskCutoffAge_ * 365) + 365 ) {
          // 3-2 sequence found - indiv is proper age
          int ElapsedTime =iD2Inoc - iD3Inoc;
          if( ElapsedTime > (seqInf->MinMonths_ * 30) && ElapsedTime < (seqInf->MaxMonths_ * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F3T2 = DlySeqInfVals.F3T2 + (1 * seqInf->Probability_);
            if( seqInf->Probability_ * seqInf->Mortality_ > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }

        seqInf = Location_->SequentialInfections_->GetSequentialInfection("4","2");
        // look for 4-2
        if( iD4Inoc > 0 && iPerAge < (seqInf->AtRiskCutoffAge_ * 365) + 365 ) {
          // 4-2 sequence found - indiv is proper age
          int ElapsedTime =iD2Inoc - iD4Inoc;
          if( ElapsedTime > (seqInf->MinMonths_ * 30) && ElapsedTime < (seqInf->MaxMonths_ * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F4T2 = DlySeqInfVals.F4T2 + (1 * seqInf->Probability_);
            if( seqInf->Probability_ * seqInf->Mortality_ > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }
      }
      else {
        MAEASeqInf = Location_->SequentialInfections_->GetSequentialInfection("MAEA","2");
        // look for MAEA-2
        if( iPerAge < MANADurat + MAEADurat ) {
          // indiv is viremic and enhancing
          DlySeqInfVals.FMT2 = DlySeqInfVals.FMT2 + (1 * MAEASeqInf->Probability_);
          if( MAEASeqInf->Probability_ * MAEASeqInf->Mortality_ > RND() ) {
            // individual dies
            AgeAtDeath( iPerAge );
            iPerAge = -999;
            return;
          }
        }
      }
      break;
    }
    
    case 3: {                                                        // dengue 3 viremia

      if( iD1Inoc > 0 || iD2Inoc > 0 || iD4Inoc > 0 ) {
        // some sort of sequential infection is present

        seqInf = Location_->SequentialInfections_->GetSequentialInfection("1","3");
        // look for 1-3
        if( iD1Inoc > 0 && iPerAge < (seqInf->AtRiskCutoffAge_ * 365) + 365 ) {
          // 1-3 sequence found - indiv is proper age
          int ElapsedTime =iD3Inoc - iD1Inoc;
          if( ElapsedTime > (seqInf->MinMonths_ * 30) && ElapsedTime < (seqInf->MaxMonths_ * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F1T3 = DlySeqInfVals.F1T3 + (1 * seqInf->Probability_);
            if( seqInf->Probability_ * seqInf->Mortality_ > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }

        seqInf = Location_->SequentialInfections_->GetSequentialInfection("2","3");
        // look for 2-3
        if( iD2Inoc > 0 && iPerAge < (seqInf->AtRiskCutoffAge_ * 365) + 365 ) {
          // 2-3 sequence found - indiv is proper age
          int ElapsedTime =iD3Inoc - iD2Inoc;
          if( ElapsedTime > (seqInf->MinMonths_ * 30) && ElapsedTime < (seqInf->MaxMonths_ * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F2T3 = DlySeqInfVals.F2T3 + (1 * seqInf->Probability_);
            if( seqInf->Probability_ * seqInf->Mortality_ > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }

        seqInf = Location_->SequentialInfections_->GetSequentialInfection("4","3");
        // look for 4-3
        if( iD4Inoc > 0 && iPerAge < (seqInf->AtRiskCutoffAge_ * 365) + 365 ) {
          // 4-3 sequence found - indiv is proper age
          int ElapsedTime =iD3Inoc - iD4Inoc;
          if( ElapsedTime > (seqInf->MinMonths_ * 30) && ElapsedTime < (seqInf->MaxMonths_ * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F4T3 = DlySeqInfVals.F4T3 + (1 * seqInf->Probability_);
            if( seqInf->Probability_ * seqInf->Mortality_ > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }
      }
      else {
        MAEASeqInf = Location_->SequentialInfections_->GetSequentialInfection("MAEA","3");
        // look for MAEA-3
        if( iPerAge < MANADurat + MAEADurat ) {
          // indiv is viremic and enhancing
          DlySeqInfVals.FMT3 = DlySeqInfVals.FMT3 + (1 * MAEASeqInf->Probability_);
          if( MAEASeqInf->Probability_ * MAEASeqInf->Mortality_ > RND() ) {
            // individual dies
            AgeAtDeath( iPerAge );
            iPerAge = -999;
            return;
          }
        }
      }
      break;
    }

    case 4: {                                                   // dengue 4 viremia
    
      if( iD1Inoc > 0 || iD2Inoc > 0 || iD3Inoc > 0 ) {         // some sort of sequential infection
        
        seqInf = Location_->SequentialInfections_->GetSequentialInfection("1","4");
        // look for 1-4
        if( iD1Inoc > 0 && iPerAge < (seqInf->AtRiskCutoffAge_ * 365) + 365 ) {
          // 1-4 sequence found - indiv is proper age
          int ElapsedTime =iD4Inoc - iD1Inoc;
          if( ElapsedTime > (seqInf->MinMonths_ * 30) && ElapsedTime < (seqInf->MaxMonths_ * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F1T4 = DlySeqInfVals.F1T4 + (1 * seqInf->Probability_);
            if( seqInf->Probability_ * seqInf->Mortality_ > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }

        seqInf = Location_->SequentialInfections_->GetSequentialInfection("2","4");
        // look for 2-4
        if( iD2Inoc > 0 && iPerAge < (seqInf->AtRiskCutoffAge_ * 365) + 365 ) {
          // 2-4 sequence found - indiv is proper age
          int ElapsedTime =iD4Inoc - iD2Inoc;
          if( ElapsedTime > (seqInf->MinMonths_ * 30) && ElapsedTime < (seqInf->MaxMonths_ * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F2T4 = DlySeqInfVals.F2T4 + (1 * seqInf->Probability_);
            if( seqInf->Probability_ * seqInf->Mortality_ > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }

        seqInf = Location_->SequentialInfections_->GetSequentialInfection("3","4");
        // look for 3-4
        if( iD3Inoc > 0 && iPerAge < (seqInf->AtRiskCutoffAge_ * 365) + 365 ) {
          // 3-4 sequence found - indiv is proper age
          int ElapsedTime =iD4Inoc - iD3Inoc;
          if( ElapsedTime > (seqInf->MinMonths_ * 30) && ElapsedTime < (seqInf->MaxMonths_ * 30) ) {
            // Proper sequential exposure window - This is it!
            DlySeqInfVals.F3T4 = DlySeqInfVals.F3T4 + (1 * seqInf->Probability_);
            if( seqInf->Probability_ * seqInf->Mortality_ > RND() ) {
              // individual dies
              AgeAtDeath( iPerAge );
              iPerAge = -999;
              return;
            }
          }
        }
      }
      else {
        MAEASeqInf = Location_->SequentialInfections_->GetSequentialInfection("MAEA","4");
        // look for MAEA-4
        if( iPerAge < MANADurat + MAEADurat ) {
          // indiv is viremic and enhancing
          DlySeqInfVals.FMT4 = DlySeqInfVals.FMT4 + (1 * MAEASeqInf->Probability_);
          if( MAEASeqInf->Probability_ * MAEASeqInf->Mortality_ > RND() ) {
            // individual dies
            AgeAtDeath( iPerAge );
            iPerAge = -999;
            return;
          }
        }
      }
      break;
    }
  }
}



void
SimLocation::AgeAtDeath( int iPerAge )
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
SimLocation::PurgeHFDeaths(void)
{
  int iStart = PopulationSize;                 // start with youngest individual

  for( int i = iStart; i >= 1; --i ) {

    if( Indiv[i] > 5840 ) { 
      return;     // following individuals are older than 15
    }

    // look for dead indviduals - value of -999
    if( Indiv[i] == -999 ) {
      if( i == iStart ) {
        // last position, simply zero to remove
        Indiv[PopulationSize] = 0;
        Deng1[PopulationSize] = 0;
        Deng2[PopulationSize] = 0;
        Deng3[PopulationSize] = 0;
        Deng4[PopulationSize] = 0;
        PopulationSize = PopulationSize - 1;
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
        PopulationSize = PopulationSize - 1;
      }

      Individuals.erase( Individuals.begin() + i -1 );
    }
  }
}



void
SimLocation::SpoolToDisk(void)
{
  output::DensimOutput::DailyLocationOutput dlo;

  dlo.Incubate1 = TotDlyIncub[1];
  dlo.Incubate2 = TotDlyIncub[2];
  dlo.Incubate3 = TotDlyIncub[3];
  dlo.Incubate4 = TotDlyIncub[4];

  dlo.Viremic1 = TotDlyInfective[1];
  dlo.Viremic2 = TotDlyInfective[2];
  dlo.Viremic3 = TotDlyInfective[3];
  dlo.Viremic4 = TotDlyInfective[4];

  dlo.MosqTotal = MosqTotal;
  for( int i = 1; i <= 4; ++i ) {
    dlo.MosqInfvTotal[i] = MosqInfvTotal[i];
    dlo.NewHumCases[i] = NewDlyInfective[i];
  }
  dlo.InfvBites = NewDlyHumInoc;
  for( int i = 1; i <= 4; ++i ) {
    dlo.EIPDevRate[i] = EIPDevRate[i];
  }
  dlo.NumHumans = PopulationSize;

  // 1  - MANA
  // 2 - MAEA
  std::vector<double> Temp = std::vector<double>( 4+1, 0 );
  for( int i = 1; i <= 4; ++i ) {
    if( AgeDistribution[1] == 0 ) {
      dlo.SerPos[1][i] = 0;
      dlo.SerPos[2][i] = 0;
    }
    else {
      dlo.SerPos[1][i] = (double) MatAnti[i].MANA / AgeDistribution[1] * 100;
      dlo.SerPos[2][i] = (double) MatAnti[i].MAEA / AgeDistribution[1] * 100;
    }
  }
  // 3 - 20 - the 18 age classes
  for( int i = 1; i <= 18; ++i ) {
    for( int j = 1; j <= 4; ++j ) {
      if( AgeDistribution[i] == 0 ) {
        dlo.SerPos[i + 2][j] = 0;
      }
      else {
        dlo.SerPos[i + 2][j] = (double) SerDistr[i][j] / AgeDistribution[i] * 100;
      }
      Temp[j] = Temp[j] + dlo.SerPos[i + 2][j];
    }
  }
  // 21 - age classes 5-10
  dlo.SerPos[21][1] = 0;
  dlo.SerPos[21][2] = 0;
  dlo.SerPos[21][3] = 0;
  dlo.SerPos[21][4] = 0;
  for( int i = 5; i <= 10; ++i ) {
    for( int j = 1; j <= 4; ++j ) {
      if( AgeDistribution[i] == 0 ) {
        dlo.SerPos[21][j] = 0;
      }
      else {
        dlo.SerPos[21][j] = dlo.SerPos[21][j] + (SerDistr[i][j] / AgeDistribution[i] * 100);
      }
    }
  }
  for( int i = 1; i <= 4; ++i ) {
    dlo.SerPos[21][i] = dlo.SerPos[21][i] / 6;
  }

  // 22 - age classes 11 through 18
  dlo.SerPos[22][1] = 0;
  dlo.SerPos[22][2] = 0;
  dlo.SerPos[22][3] = 0;
  dlo.SerPos[22][4] = 0;
  for( int i = 11; i <= 18; ++i ) {   // 46-80+
    for( int j = 1; j <= 4; ++j ) {
      if( AgeDistribution[i] == 0 ) {
        dlo.SerPos[22][j] = 0;
      }
      else {
        dlo.SerPos[22][j] = dlo.SerPos[22][j] + (SerDistr[i][j] / AgeDistribution[i] * 100);
      }
    }
  }
  for( int i = 1; i <= 4; ++i ) {
    dlo.SerPos[22][i] = dlo.SerPos[22][i] / 8;
  }
  for( int i = 1; i <= 4; ++i ) {
    dlo.SerPos[23][i] = Temp[i] / 18;
  }
  dlo.SeqInfVals = DlySeqInfVals;

  Output_->AddDailyLocationOutput( dlo, BoostDateFromYearAndDayOfYear(Year, Day) );
}



void
SimLocation::ReadWeather( int year )
{
  // read specified year's worth of weather
  input::WeatherYear * wy = Location_->Weather_->GetWeatherForYear(year);

  // adjust vector length for leap years
  int numDays = gregorian_calendar::is_leap_year( year ) ? 366 : 365;
  TemperatureMax = std::vector<double>( numDays+1, 0.0f );
  TemperatureMin = std::vector<double>( numDays+1, 0.0f );
  TemperatureAvg = std::vector<double>( numDays+1, 0.0f );
  Rain = std::vector<double>( numDays+1, 0.0f );
  RelHumid = std::vector<double>( numDays+1, 0.0f );
  SD = std::vector<double>( numDays+1, 0.0f );

  for( int i = 1; i <= numDays; i++ ) {
    input::WeatherDay * wd = wy->GetDay(i);
    TemperatureMax[i] = wd->MaxTemp_;
    TemperatureMin[i] = wd->MinTemp_;
    TemperatureAvg[i] = wd->AvgTemp_;
    SD[i] = wd->SatDef_;
    Rain[i] = wd->Precip_;
    RelHumid[i] = wd->RelHum_;
  }
}



void
SimLocation::ReadMos( int year )
{
  this->YearlyMosData_ = MosData_->GetYearlyMosData(year);
}



void
SimLocation::ComparePopulation(void)
{
  // helper method in transitioning to better population data structures
  // ensures that the population are equivalent

  if( !(SimYear == 1 && Day == 1) ) {
    return;
  }

  // PopulationSize is current size of population
  Population::iterator itIndiv = Individuals.begin();
  for( int i = 1; i <= PopulationSize; ++i ) {
    if( Indiv[i] != itIndiv->Age ) {
      std::cout << "Error in age comparison, old index = " << i << std::endl;
      throw;
    }
    ++itIndiv;
  }
}



void
SimLocation::ComparePopulationAndSerotypes(void)
{
  // helper method in transitioning to better population data structures
  // ensures that the population and serotype statuses are equivalent

  if( !(SimYear == 1 && Day < 3) ) {
    return;
  }

  Population::iterator itIndiv = Individuals.begin();
  for( int i = 1; i <= PopulationSize; ++i ) {
    if( Indiv[i] != itIndiv->Age ) {
      std::cout << "Error in age comparison, old index = " << i << std::endl;
      throw;
    }
    if( Deng1[i] != itIndiv->Dengue[1] ) {
      std::cout << "Error in dengue 1 comparison, old index = " << i << std::endl;
      throw;
    }
    if( Deng2[i] != itIndiv->Dengue[2] ) {
      std::cout << "Error in dengue 2 comparison, old index = " << i << std::endl;
      throw;
    }
    if( Deng3[i] != itIndiv->Dengue[3] ) {
      std::cout << "Error in dengue 3 comparison, old index = " << i << std::endl;
      throw;
    }
    if( Deng4[i] != itIndiv->Dengue[4] ) {
      std::cout << "Error in dengue 4 comparison, old index = " << i << std::endl;
      throw;
    }
    ++itIndiv;
  }
}

// emulate DS 1.0 CINT() which does banker's rounding
int
SimLocation::CINT( double value )
{
  double integer;
  double fraction;
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
SimLocation::INT( double value )
{
  return (int)floor(value);
}



// emulate PDS 7.1 RND
// PDS 7.1 RND returns single precision values in the range of [0,1)
// the only problem with our emulation is the exclusion of
// ( RAND_MAX/(RAND_MAX+1), 1 ) from the range of generation
double
SimLocation::RND(void)
{
  return rand() / (double) (RAND_MAX + 1); 
}
double
SimLocation::Factorial( int n )
{
  int result = 1;
  for( int i = n; i > 0; --i ) {
    result = result * i;
  }
  return result;
}



double
SimLocation::EIPEnzKin( double temp )
{
  double TempExpr1 = (EnzKinEA / GasCoef) * ((1 / (double) 298) - (1 / temp));
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
