#include "StdAfx.h"
#include "Constants.h"
#include "Humans.h"
#include "Location.h"
#include <numeric>

using namespace sim::ds;



Human::Human( int age )
: Age(age)
{
  for( int i = 1; i <=4; ++i ) {
    Dengue[i] = 0;
  }
}



Human::~Human(void)
{}



int
Human::GetAge(void)
{
  return Age;
}



void 
Human::SetAge( int age )
{
  Age = age;
}



int
Human::GetSerotypeStatus( int serotype )
{
  return Dengue[serotype];
}



void
Human::SetSerotypeStatus( int serotype, int status )
{
  Dengue[serotype] = status;
}



HumanPopulation::HumanPopulation( const input::Location * location, boost::variate_generator<boost::mt19937, boost::uniform_01<>> & rng )
: _rng(rng),
  _ageClasses(std::map<int,AgeClass>()),
  _populationSize(0),
  _humans(HumansByClass(18+1,HumanCollection())),
  _ageDistribution(std::vector<int>(18+1,0)),
  _initialAgeDistribution(std::vector<int>(18+1,0)),
  _cumulativeDeaths(std::vector<double>(18+1, 0)),
  _cumulativeBirths(std::vector<double>(18+1, 0)),
  _totalDeaths(std::vector<int>(18+1, 0)),
  _totalBirths(std::vector<int>(18+1, 0)),
  _initialSeroprevalence(std::vector<std::vector<double>>(18+1,std::vector<double>(4+1))),
  _classSpecificSeroprevalence(ClassSpecificSeroprevalence()),
  _seroDistribution(std::vector<std::vector<int>>(18+1,std::vector<int>(4+1))),
  _initialSeroDistribution(std::vector<std::vector<int>>(18+1,std::vector<int>(4+1))),
  _incubating(std::vector<std::vector<int>>(18+1, std::vector<int>(4+1, 0))),
  _infective(std::vector<std::vector<int>>(18+1, std::vector<int>(4+1, 0))),
  _homologousImmunity(std::vector<std::vector<int>>(18+1, std::vector<int>(4+1, 0) )),
  _heterologousImmunity(std::vector<std::vector<int>>(18+1, std::vector<int>(4+1, 0))),
  _maternalAntibodies(std::vector<MaternalAntibodies>(4+1)),
  _totalIncubating(std::vector<int>(4+1, 0)),
  _newInfective(std::vector<int>(4+1, 0)),
  _totalInfective(std::vector<int>(4+1, 0)),
  _totalHomologousImmunity(std::vector<int>(4+1, 0)),
  _totalHeterologousImmunity(std::vector<int>(4+1, 0)),
  _cumulativeHfDeaths(std::vector<double>(15+1, 0))
{
  // demographics
  _demographics = location->Demographics_;

  // serology
  for( int i = 1; i <= 18; ++i ) {
    _initialSeroprevalence[i][1] = location->Serology_->SerologyData_[i-1].Dengue1_;
    _initialSeroprevalence[i][2] = location->Serology_->SerologyData_[i-1].Dengue2_;
    _initialSeroprevalence[i][3] = location->Serology_->SerologyData_[i-1].Dengue3_;
    _initialSeroprevalence[i][4] = location->Serology_->SerologyData_[i-1].Dengue4_;
  }
  _neutralizingDuration = location->Serology_->ManaDuration_;
  _enhancingDuration = location->Serology_->MaeaDuration_;
  _heterologousImmunityDuration = location->Serology_->HeterologousImmunityDuration_;

  // virology
  _virology = location->Virology_;

  // sequential infections
  _sequentialInfections = location->SequentialInfections_;


  // completed processing parameters, now do initialization
  Initialize();
}



HumanPopulation::~HumanPopulation(void)
{}



void
HumanPopulation::Initialize(void)
{
  // initialize age class data
  InitializeAgeClasses();
  InitializeDemographics();

  // find threshold age and class for purging maternal antibodies
  _thresholdAge = _neutralizingDuration + _enhancingDuration;
  _thresholdClass = GetAgeClassFromAge( _thresholdAge );
  if( _thresholdAge == _ageClasses[_thresholdClass].LastDay ) {
    _thresholdClass++;
  }

  // initialize population and seroprevalence
  InitializePopulation();
  InitializeSeroprevalence();
}


int
HumanPopulation::GetPopulationSize(void)
{
  unsigned int populationSize = 0;

  // sum number of individuals in each age class
  for( unsigned int i = 1; i <= 18; ++i ) {
    populationSize += static_cast<unsigned int>( _humans[i].size() );
  }

  return populationSize;
}



int
HumanPopulation::GetInitialPopulationSize(void)
{
  return _initialPopulationSize;
}



std::vector<int>
HumanPopulation::GetInitialAgeDistribution(void)
{
  return _initialAgeDistribution;
}



std::vector<double>
HumanPopulation::GetInitialAgeProportions(void)
{
  std::vector<double> initAgeProportions = std::vector<double>( 18+1, 0 );
  for( int i = 1; i <= 18; ++i ) {
    if( _initialAgeDistribution[i] != 0 ) {
      initAgeProportions[i] = _initialAgeDistribution[i] / static_cast<double>( _initialPopulationSize );
    }
    else {
      initAgeProportions[i] = 0;
    }
  }

  return initAgeProportions;
}



std::vector<int>
HumanPopulation::GetAgeDistribution(void)
{
  return _ageDistribution;
}



std::vector<double>
HumanPopulation::GetAgeProportions(void)
{
  std::vector<double> ageProportions = std::vector<double>( 18+1, 0 );
  for( int i = 1; i <= 18; ++i ) {
    if( _ageDistribution[i] != 0 ) {
      ageProportions[i] = _ageDistribution[i] / static_cast<double>( _populationSize );
    }
    else {
      ageProportions[i] = 0;
    }
  }

  return ageProportions;
}



std::vector<int>
HumanPopulation::GetBirthsByClass(void)
{
  return _totalBirths;
}



std::vector<double>
HumanPopulation::GetBirthPercentagesByClass(void)
{
  // first calculate total births
  int totalBirths = std::accumulate( ++_totalBirths.begin(), _totalBirths.end(), 0 );

  std::vector<double> birthPercentages = std::vector<double>( 18+1, 0 );
  for( int i = 1; i <= 18; ++i ) {
    if( _totalBirths[i] != 0 ) {
      birthPercentages[i] = static_cast<double>( _totalBirths[i] ) / static_cast<double>( totalBirths ) * 100;
    }
    else {
      birthPercentages[i] = 0;
    }
  }

  return birthPercentages;
}


  
std::vector<int>
HumanPopulation::GetDeathsByClass(void)
{
  return _totalDeaths;
}




std::vector<double>
HumanPopulation::GetDeathPercentagesByClass(void)
{
  // first calculate total deaths
  int totalDeaths = std::accumulate( ++_totalDeaths.begin(), _totalDeaths.end(), 0 );

  // calculate each class's proportion out of total deaths
  std::vector<double> deathPercentages = std::vector<double>( 18+1, 0 );
  for( int i = 1; i <= 18; ++i ) {
    if( _totalDeaths[i] != 0 ) {
      deathPercentages[i] = static_cast<double>( _totalDeaths[i] ) / static_cast<double>( totalDeaths ) * 100;
    }
    else {
      deathPercentages[i] = 0;
    }
  }

  return deathPercentages;
}



std::vector<std::vector<int>>
HumanPopulation::GetInitialSeroDistribution(void)
{
  return _initialSeroDistribution;
}



std::vector<std::vector<int>>
HumanPopulation::GetSeroDistribution(void)
{
  return _seroDistribution;
}



HumanPopulation::ClassSpecificSeroprevalence
HumanPopulation::GetClassSpecificSeroprevalence(void)
{
  // first tabulate class specific seroprevalence
  _classSpecificSeroprevalence.clear();

  for( int i = 1; i <= 23; ++i ) {
    _classSpecificSeroprevalence[i] = std::map<int, double>();
  }

  std::map<int,double> allAges;

  for( int i = 1; i <= 4; ++i ) {
    if( _ageDistribution[1] == 0 ) {
      _classSpecificSeroprevalence[1][i] = 0;
      _classSpecificSeroprevalence[2][i] = 0;
    }
    else {
      _classSpecificSeroprevalence[1][i] = (double) _maternalAntibodies[i].MANA / _ageDistribution[1] * 100;
      _classSpecificSeroprevalence[2][i] = (double) _maternalAntibodies[i].MAEA / _ageDistribution[1] * 100;
    }
  }
  for( int i = 1; i <= 18; ++i ) {
    for( int j = 1; j <= 4; ++j ) {
      if( _ageDistribution[i] == 0 ) {
        _classSpecificSeroprevalence[i + 2][j] = 0;
      }
      else {
        _classSpecificSeroprevalence[i + 2][j] = (double) _seroDistribution[i][j] / _ageDistribution[i] * 100;
      }
      allAges[j] = allAges[j] + _classSpecificSeroprevalence[i + 2][j];
    }
  }
  _classSpecificSeroprevalence[21][1] = 0;
  _classSpecificSeroprevalence[21][2] = 0;
  _classSpecificSeroprevalence[21][3] = 0;
  _classSpecificSeroprevalence[21][4] = 0;
  for( int i = 5; i <= 10; ++i ) {
    for( int j = 1; j <= 4; ++j ) {
      if( _ageDistribution[i] == 0 ) {
        _classSpecificSeroprevalence[21][j] = 0;
      }
      else {
        _classSpecificSeroprevalence[21][j] = _classSpecificSeroprevalence[21][j] + ((double) _seroDistribution[i][j] / _ageDistribution[i] * 100);
      }
    }
  }
  for( int i = 1; i <= 4; ++i ) {
    _classSpecificSeroprevalence[21][i] = _classSpecificSeroprevalence[21][i] / 6;
  }
  _classSpecificSeroprevalence[22][1] = 0;
  _classSpecificSeroprevalence[22][2] = 0;
  _classSpecificSeroprevalence[22][3] = 0;
  _classSpecificSeroprevalence[22][4] = 0;
  for( int i = 11; i <= 18; ++i ) {   // 46-80+
    for( int j = 1; j <= 4; ++j ) {
      if( _ageDistribution[i] == 0 ) {
        _classSpecificSeroprevalence[22][j] = 0;
      }
      else {
        _classSpecificSeroprevalence[22][j] = _classSpecificSeroprevalence[22][j] + ((double) _seroDistribution[i][j] / _ageDistribution[i] * 100);
      }
    }
  }
  for( int i = 1; i <= 4; ++i ) {
    _classSpecificSeroprevalence[22][i] = _classSpecificSeroprevalence[22][i] / 8;
  }
  for( int i = 1; i <= 4; ++i ) {
    _classSpecificSeroprevalence[23][i] = allAges[i] / 18;
  }

  return _classSpecificSeroprevalence;
}



void
HumanPopulation::DoDailyDeaths(void)
{
  for( int i = 18; i >= 1; --i ) {
    // calculate cumulative age class death rate
    double DRate = (_ageClasses[i].YearlyDeathRate / 1000) * (1 / (double) YrLen);

    // add deaths to previous fractional remainder
    _cumulativeDeaths[i] += (_ageDistribution[i] * DRate);

    if( _cumulativeDeaths[i] >= 1 && _ageDistribution[i] > 0 ) {
      for( int j = 1; j <= INT( _cumulativeDeaths[i] ); ++j ) {
        // pick radom individual within age class for death
        double rndNum = _rng();
        int index = INT( _ageDistribution[i]  * rndNum );

        // index iterator and delete death
        HumanCollection::iterator itDead = _humans[i].begin() + index;
        _humans[i].erase( itDead );

        // population decreased by one
        _populationSize--;
        _ageDistribution[i]--;

        _totalDeaths[i]++;
        if( _ageDistribution[i] <= 0 ) {
          break;
        }
      }
    }
    _cumulativeDeaths[i] = _cumulativeDeaths[i] - INT(_cumulativeDeaths[i]);
  }
}



void
HumanPopulation::DoDailyBirths(void)
{
  for( int i = 18; i >= 1; --i ) {
    // calculate cumulative age class birth rate
    double BRate = (_ageClasses[i].YearlyBirthRate / 1000) * (1 / (double) YrLen);

    // only females contribute to birth
    _cumulativeBirths[i] += ((_ageDistribution[i] / (double) 2) * BRate);

    if( _cumulativeBirths[i] >= 1 ) {
      for( int j = 1; j <= INT( _cumulativeBirths[i] ); ++j ) {
        // create newborn
        Human newborn(1);

        // select mother in this age class
        Human & mother = SelectHumanByAgeClass( i );

        // confer maternally acquired immunities, if previous or homologous immunity present in mother
        for( int k = 1; k <= 4; ++k ) {
          if( mother.Dengue[k] > 0 || mother.Dengue[k] == -2 ) {
            newborn.Dengue[k] = -1;
          }
        }

        // add individual to population, in first age class
        _humans[1].push_back( newborn );
        _populationSize++;

        // update age distribution and birth counts
        _ageDistribution[1]++;
        _totalBirths[i]++;
      }
      _cumulativeBirths[i] = _cumulativeBirths[i] - INT(_cumulativeBirths[i]);
    }
  }
}



void
HumanPopulation::AgePopulation(void)
{
  // age population
  for( int i = 1; i <= 18; ++i ) {
    int maxAge = _ageClasses[i].LastDay;

    for( HumanCollection::iterator itHum = _humans[i].begin(); itHum != _humans[i].end(); /**/ ) {
      // increment age
      itHum->Age++;

      // if neccesary, move to next age class
      if( itHum->Age > maxAge ) {
        if( i != 18 ) {
          // update age distribution
          _ageDistribution[i]--;
          _ageDistribution[i+1]++;

          // copy individual to next age class
          Human transfer = *itHum;
          _humans[i+1].push_back( transfer );

          // delete from this age class
          itHum = _humans[i].erase( itHum );
          continue;
        }
        else {
          // oldest age is capped
          itHum->Age = maxAge;
        }
      }
      // no transfer, advance to next human
      ++itHum;
    }
  }
}



int
HumanPopulation::GetAgeClassFromAge( int age )
{
  // find first age class in which specified age
  // is less than the class's last day
  for( int i = 1; i <= 18; ++i ) {
    if( age <= _ageClasses[i].LastDay ) {
      return i;
    }
  }
  throw;
}

  

void
HumanPopulation::PurgeMaternalAntibodies(void)
{
  // search threshold class for individual who have exceeded threshold age
  for( HumanCollection::iterator itHum = _humans[_thresholdClass].begin(); itHum != _humans[_thresholdClass].end(); ++itHum ) {
    if( itHum->Age >= _thresholdAge ) {
      // individual older than threshold age have exceeded nuetralizing + enhancing period
      // clear any existing maternally acquired immunities
      for( int i = 1; i <= 4; ++i ) {
        if( itHum->Dengue[i] == -1 ) {
          itHum->Dengue[i] = 0;
        }
      }
    }
  }
}



void
HumanPopulation::IntroduceInfectedHuman( unsigned int serotype )
{
  // increase current population size by one
  _populationSize++;

  // pull data for this serotype
  input::VirusSerotype & virus = _virology->GetSerotype( serotype );

  // randomly select age of new infected human and determine age class
  int age = INT( (_ageClasses[18].LastDay - (virus.IncubationDuration_ + 1) + 1) * _rng() + (virus.IncubationDuration_ + 1) );
  int ageClass = GetAgeClassFromAge( age );

  // create human and mark as infected
  Human newInfected = Human(age);
  newInfected.Dengue[serotype] = age - virus.IncubationDuration_;

  // insert into age class
  _humans[ageClass].push_back( newInfected );
  _ageDistribution[ageClass]++;
}



void
HumanPopulation::InoculateRandomHuman( unsigned int serotype )
{
  // randomly select individual for new innoculation
  Human & human = SelectHuman();

  // if maternally acquired antibodies exist
  if( human.Dengue[serotype] == -1 ) {
    if( human.Age > _neutralizingDuration ) {
      // nuetralizing period exceeded, normal or enhanced infection depending on age
      human.Dengue[serotype] = human.Age;
    }
  }


  // if no previous exposure
  else if( human.Dengue[serotype] == 0 ) {

    // check for heterologous immunity, initialized immunity (-2) does not confer heterlogous immunity
    bool iHetImmunity = false;
    for( int i = 1; i <= 4; ++i ) {
      if( i == serotype ) {
        continue;
      }
      if( human.Dengue[i] > 0 && (human.Age - human.Dengue[i] < _heterologousImmunityDuration ) ) {
        iHetImmunity = true;
      }
    }
    
    // if no heterologous immunity then assign infection date
    if( iHetImmunity == false ) {
      // todo 1.0 bug? why first day of 18th age class
      int oldestAge = _ageClasses[18].FirstDay;
      if( human.Age > oldestAge ) {
        human.Age = oldestAge;
      }
      human.Dengue[serotype] = human.Age;
    }
  }


  // if homologous immunity exists
  else if( human.Dengue[serotype] == -2 ) {
    // innoculation has no effect
  }


  // if previous infection
  else if( human.Dengue[serotype] > 0 ) {
    // innoculation has no effect
  }
}



void
HumanPopulation::RankPopulation(void)
{
  _ageDistribution = std::vector<int>( 18+1, 0 );                                             // clear last tally
  _seroDistribution = std::vector<std::vector<int>>( 18+1, std::vector<int>(4+1, 0) );         // clear last tally
  _incubating = std::vector<std::vector<int>>( 18+1, std::vector<int>(4+1, 0) );            // clear last tally
  _infective = std::vector<std::vector<int>>( 18+1, std::vector<int>(4+1, 0) );        // clear last tally
  _homologousImmunity = std::vector<std::vector<int>>( 18+1, std::vector<int>(4+1, 0) );           // clear last tally
  _heterologousImmunity = std::vector<std::vector<int>>( 18+1, std::vector<int>(4+1, 0) );           // clear last tally
  _maternalAntibodies = std::vector<MaternalAntibodies>( 4+1 );                                 // clear last tally
  _totalIncubating = std::vector<int>( 4+1, 0 );
  _newInfective = std::vector<int>( 4+1, 0 );
  _totalInfective = std::vector<int>( 4+1, 0 );
  _totalHomologousImmunity = std::vector<int>( 4+1, 0 );
  _totalHeterologousImmunity = std::vector<int>( 4+1, 0 );

  std::map<int,double> seqInf;
  seqInf[D1] = 0;
  seqInf[D2] = 0;
  seqInf[D3] = 0;
  seqInf[D4] = 0;
  seqInf[Maternal] = 0;

  _dailySequentialInfections.clear();
  _dailySequentialInfections[D1] = seqInf;
  _dailySequentialInfections[D2] = seqInf;
  _dailySequentialInfections[D3] = seqInf;
  _dailySequentialInfections[D4] = seqInf;
  _dailySequentialInfections[Maternal] = seqInf;

  int iRank = 18;                                   // assume oldest age class first

  for( int i = 1; i <= 18; ++i ) {
    for( HumanCollection::iterator itHum = _humans[i].begin(); itHum != _humans[i].end(); ++itHum ) {
      _ageDistribution[i]++;
      RankSerology( itHum, i );
    }
  }
}



void
HumanPopulation::RankSerology( HumanCollection::iterator itHum, int ageClass )
{
  // Rank can be -2 for initialized homologous immmunity
  //             -1 for maternally acquired immunity
  //              0 for no previous exposure
  //             >0 inoculation day

  for( int i = 1; i <= 4; ++i ) {
    // pull data for this serotype
    input::VirusSerotype & virus = _virology->GetSerotype( i );

    if( itHum->Dengue[i] != 0 ) {
      // show seropositive status
      _seroDistribution[ageClass][i]++;

      // initialized immunity counts as homologous immunity
      if( itHum->Dengue[i] == -2 ) {
        _homologousImmunity[ageClass][i]++;
        _totalHomologousImmunity[i]++;
      }

      // maternally acquired immunity
      else if( itHum->Dengue[i] == -1 ) {
        // check for neutralizing or enhancing antibody
        if( itHum->Age < _neutralizingDuration ) {
          // MANA individual
          _maternalAntibodies[i].MANA++;
          _homologousImmunity[ageClass][i]++;
          _totalHomologousImmunity[i]++;
        }
        else if( itHum->Age < _enhancingDuration + _neutralizingDuration ) {
          _maternalAntibodies[i].MAEA++;
        }
      }

      // previous or ongoing infection
      else {
        int daysSinceInfection = itHum->Age - itHum->Dengue[i];

        // incubation phase
        if( daysSinceInfection < virus.IncubationDuration_ ) {
          _incubating[ageClass][i]++;
          _totalIncubating[i]++;
        }

        // viremic phase (infective)
        else if( daysSinceInfection < virus.ViremicDuration_ + virus.IncubationDuration_ ) {
          _infective[ageClass][i]++;
          _totalInfective[i]++;
          
          // newly infective
          if( daysSinceInfection == virus.IncubationDuration_ ) {
            _newInfective[i]++;
          }

          // latter half of viremic phase, check for HF/SS
          if( daysSinceInfection > virus.IncubationDuration_ + (virus.ViremicDuration_ / 2) ) {
            CheckSequentialInfection( i, itHum );
          }
        }

        // past viremic phase
        else {
          // heterologous immunity
          if( daysSinceInfection < _heterologousImmunityDuration + virus.ViremicDuration_ + virus.IncubationDuration_ ) {
            _heterologousImmunity[ageClass][i]++;
            _totalHeterologousImmunity[i]++;
          }

          // homologous immunity
          _homologousImmunity[ageClass][i]++;
          _totalHomologousImmunity[i]++;
        }
      }
    }
  }
}



void
HumanPopulation::CheckSequentialInfection( int serotype, HumanCollection::iterator itHum )
{
  // calculates daily sequential infection and MAEA statistics
  // applies death to those with hf/ss - assigns age of -999 for later analysis.

  bool previousSerotypeInoculation = false;
  for( int i = 1; i <= 4; ++i ) {

    // todo - this is cock eyed logic from ds 1.0, needs checking
    // basically because of if/else logic used in original code,
    // if the serotype for which a infection is at risk for hf/ss
    // but there has been a previous innoculation
    // the MAEA check is skipped
    // this means that a child with enhancing isn't at risk for the second secondary infection

    if( i != serotype ) {
      if( itHum->Dengue[i] > 0 ) {
        previousSerotypeInoculation = true;

        // possible sequential infection first = i, second = serotype
        input::SequentialInfection * si = _sequentialInfections->GetSequentialInfection( i, serotype );

        if( itHum->Age < (si->AtRiskCutoffAge_ * 365) + 365 ) {
          int elapsedDays = itHum->Dengue[serotype] - itHum->Dengue[i];
          if( elapsedDays > (si->MinMonths_ * 30) && elapsedDays < (si->MaxMonths_ * 30) ) {
            // sequential infection falls before cutoff and within window
            _dailySequentialInfections[serotype][i] += (1 * si->Probability_);
            
            // possible death
            if( si->Probability_ * si->Mortality_ > _rng() ) {
              TabulateHfDeath( itHum->Age );
              itHum->Age = -999;
              return;
            }
          }
        }
      }
    }
  }


  // todo, kludge from above to match ds 1.0 logic
  if( previousSerotypeInoculation ) {
    return;
  }

  if( itHum->Age < _neutralizingDuration + _enhancingDuration ) {
    // possible sequential infection from maternally acquired enhancing antibodies
    input::SequentialInfection * msi = _sequentialInfections->GetMaeaSequentialInfection( serotype );

    // human is viremic and enhancing
    _dailySequentialInfections[Maternal][serotype] += (1 * msi->Probability_);
    if( msi->Probability_ * msi->Mortality_ > _rng() ) {
      // individual dies
      TabulateHfDeath( itHum->Age );
      itHum->Age = -999;
      return;
    }
  }

}



void
HumanPopulation::TabulateHfDeath( int age )
{
  if( 0 <= age && age <= 365 ) {
    _cumulativeHfDeaths[0]++;
  }
  else if( 366 <= age && age <= 730 ) {
    _cumulativeHfDeaths[1]++;
  }
  else if( 731 <= age && age <= 1095 ) {
    _cumulativeHfDeaths[2]++;
  }
  else if( 1096 <= age && age <= 1460 ) {
    _cumulativeHfDeaths[3]++;
  }
  else if( 1461 <= age && age <= 1825 ) {
    _cumulativeHfDeaths[4]++;
  }
  else if( 1826 <= age && age <= 2190 ) {
    _cumulativeHfDeaths[5]++;
  }
  else if( 2191 <= age && age <= 2555 ) {
    _cumulativeHfDeaths[6]++;
  }
  else if( 2556 <= age && age <= 2920 ) {
    _cumulativeHfDeaths[7]++;
  }
  else if( 2921 <= age && age <= 3285 ) {
    _cumulativeHfDeaths[8]++;
  }
  else if( 3286 <= age && age <= 3650 ) {
    _cumulativeHfDeaths[9]++;
  }
  else if( 3651 <= age && age <= 4015 ) {
    _cumulativeHfDeaths[10]++;
  }
  else if( 4016 <= age && age <= 4380 ) {
    _cumulativeHfDeaths[11]++;
  }
  else if( 4381 <= age && age <= 4745 ) {
    _cumulativeHfDeaths[12]++;
  }
  else if( 4746 <= age && age <= 5110 ) {
    _cumulativeHfDeaths[13]++;
  }
  else if( 5111 <= age && age <= 5475 ) {
    _cumulativeHfDeaths[14]++;
  }
  else if( 5476 <= age && age <= 5840 ) {
    _cumulativeHfDeaths[15]++;
  }
}



void
HumanPopulation::PurgeHfDeaths(void)
{
  // hf deaths do not occur over age 5840, which lies in age class 5
  for( int i = 1; i <= 5; ++i ) {
    for( HumanCollection::iterator itHum = _humans[i].begin(); itHum != _humans[i].end(); /**/ ) {
      // look for dead individuals, marked with age -999
      if( itHum->Age == -999 ) {
        // remove individual from this age class
        itHum = _humans[i].erase( itHum );
        _populationSize--;
      }
      else {
        // advance to next individual in age class
        ++itHum;
      }
    }
  }
}



void
HumanPopulation::InitializeAgeClasses(void)
{
  _ageClasses[1] = AgeClass( 1, 364 );
  _ageClasses[2] = AgeClass( 365, 1824 );
  _ageClasses[3] = AgeClass( 1825, 3649 );
  _ageClasses[4] = AgeClass( 3650, 5474 );
  _ageClasses[5] = AgeClass( 5475, 7299 );
  _ageClasses[6] = AgeClass( 7300, 9124 );
  _ageClasses[7] = AgeClass( 9125, 10949 );
  _ageClasses[8] = AgeClass( 10950, 12774 );
  _ageClasses[9] = AgeClass( 12775, 14599 );
  _ageClasses[10] = AgeClass( 14600, 16424 );
  _ageClasses[11] = AgeClass( 16425, 18249 );
  _ageClasses[12] = AgeClass( 18250, 20074 );
  _ageClasses[13] = AgeClass( 20075, 21899 );
  _ageClasses[14] = AgeClass( 21900, 23724 );
  _ageClasses[15] = AgeClass( 23725, 25549 );
  _ageClasses[16] = AgeClass( 25550, 27374 );
  _ageClasses[17] = AgeClass( 27375, 29199 );
  _ageClasses[18] = AgeClass( 29200, 30000 );
}



void
HumanPopulation::InitializeDemographics(void)
{
  for( int i = 1; i <= 18; ++i ) {
    _ageClasses[i].Proportion = _demographics->DemographicData[i-1].Proportion;
    _ageClasses[i].YearlyBirthRate = _demographics->DemographicData[i-1].BirthRate;
    _ageClasses[i].YearlyDeathRate = _demographics->DemographicData[i-1].DeathRate;
  }
}



void
HumanPopulation::InitializePopulation(void)
{
  _initialPopulationSize = _demographics->InitialPopulationSize;
  _populationSize = 0;

  for( int i = 18; i >= 1; --i ) {
    // determine number of individuals in this age class, along with min and max age possible
    int ageClassCount = CINT( _ageClasses[i].Proportion * _initialPopulationSize );
    int minAge = _ageClasses[i].FirstDay;
    int maxAge = _ageClasses[i].LastDay;

    // set initial capacity to twice the initial class size
    _humans[i].reserve( ageClassCount * 2 );

    // for all individual in this age class
    for( int j = 1; j <= ageClassCount; ++j ) {
      // ... select a random age in [minAge, maxAge]
      int age = INT( (maxAge - minAge + 1) * _rng() + minAge);

      // create individual and insert into population
      Human human(age);
      _humans[i].push_back( human );

      // update age distributions
      _ageDistribution[i]++;
      _initialAgeDistribution[i]++;
      _populationSize++;
    }
  }
}



void
HumanPopulation::InitializeSeroprevalence(void)
{
  // iterate through each age class and serotype
  for( int i = 18; i >= 1; --i ) {
    for( int j = 1; j <= 4; ++j ) {

      // calculate the number of individuals with homologuos immunity to this serotype in this age class
      int numInfected = CINT( _initialSeroprevalence[i][j] * _ageDistribution[i]);

      while( numInfected > 0 ) {
        Human & human = SelectHumanByAgeClass( i );

        // check if no previous immunity
        if( human.Dengue[j] == 0 ) {
          numInfected--;
          human.Dengue[j] = -2;

          _initialSeroDistribution[i][j]++;
          _seroDistribution[i][j]++;
        }
      }
    }
  }
}



Human &
HumanPopulation::SelectHuman(void)
{
  // select human out of entire population
  int index = INT( (_populationSize - 1) * _rng() );

  // find age class where index maps into
  for( int i = 1; i <= 18; ++i ) {
    if( index < _ageDistribution[i]  ) {
      // if index lies within bounds of this age class
      // then return individual at specified index
      return _humans[i][index];
    }
    else {
      index = index - _ageDistribution[i];
    }
  }
  throw;
}



Human &
HumanPopulation::SelectHumanByAgeClass( int ageClass )
{
  // number of humans available for selection in this age class
  int numHumans = _ageDistribution[ageClass];

  double rndNum = _rng();

  // indices in vector run from 0 to numHumans - 1
  // to select a number between [min,max], we multiply [0,1] by
  // (max - min + 1) = ((numHumans - 1) - (0) + 1) = numHumans
  int index = INT( numHumans * rndNum );

  // return individual in specified age class and index
  return _humans[ageClass][index];
}



int
HumanPopulation::GetIncubatingBySerotype( int serotype )
{
  return _totalIncubating[serotype];
}



int
HumanPopulation::GetNewInfectiveBySerotype( int serotype )
{
  return _newInfective[serotype];
}



int
HumanPopulation::GetInfectiveBySerotype( int serotype )
{
  return _totalInfective[serotype];
}



HumanPopulation::DailySequentialInfections
HumanPopulation::GetDailySequentialInfections(void)
{
  return _dailySequentialInfections;
}
