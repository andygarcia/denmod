#include "StdAfx.h"
#include "DensimOutput.h"

using namespace boost::gregorian;
using namespace sim::output;



DensimOutput::DensimOutput( date startDate, date stopDate )
: _startDate(startDate),
  _stopDate(stopDate)
{}



DensimOutput::~DensimOutput(void)
{}



boost::gregorian::date_period
DensimOutput::GetDateRange(void)
{
  date firstDate = _locationOutput.begin()->first;
  date lastDate = _locationOutput.rbegin()->first;
  return date_period( firstDate, lastDate );
}



void
DensimOutput::AddDailyLocationOutput( DailyLocationOutput dlo, date d )
{
  _locationOutput[d] = dlo;

  DailySerotypeOutput dso1;
  dso1.Incubating = dlo.Incubate1;
  dso1.Viremic = dlo.Viremic1;
  dso1.InfectiveMosquitoes = dlo.MosqInfvTotal[1];
  dso1.EipDevelopmentRate = dlo.EIPDevRate[1];
  dso1.NewCases = dlo.NewHumCases[1];
  _serotypeOutputs[1][d] = dso1;

  DailySerotypeOutput dso2;
  dso2.Incubating = dlo.Incubate2;
  dso2.Viremic = dlo.Viremic2;
  dso2.InfectiveMosquitoes = dlo.MosqInfvTotal[2];
  dso2.EipDevelopmentRate = dlo.EIPDevRate[2];
  dso2.NewCases = dlo.NewHumCases[2];
  _serotypeOutputs[2][d] = dso2;

  DailySerotypeOutput dso3;
  dso3.Incubating = dlo.Incubate3;
  dso3.Viremic = dlo.Viremic3;
  dso3.InfectiveMosquitoes = dlo.MosqInfvTotal[3];
  dso3.EipDevelopmentRate = dlo.EIPDevRate[3];
  dso3.NewCases = dlo.NewHumCases[3];
  _serotypeOutputs[3][d] = dso3;

  DailySerotypeOutput dso4;
  dso4.Incubating = dlo.Incubate4;
  dso4.Viremic = dlo.Viremic4;
  dso4.InfectiveMosquitoes = dlo.MosqInfvTotal[4];
  dso4.EipDevelopmentRate = dlo.EIPDevRate[4];
  dso4.NewCases = dlo.NewHumCases[4];
  _serotypeOutputs[4][d] = dso4;
}



void
DensimOutput::SetInitialData( std::vector<int> & initialAgeDistribution, std::vector<std::vector<int>> & initialSeroDistribution )
{
  _initialAgeDistribution = initialAgeDistribution;
  _initialSeroDistribution = initialSeroDistribution;
}



void
DensimOutput::SetFinalData( std::vector<int> & finalAgeDistribution, std::vector<int> & births, std::vector<int> & deaths,
                           std::vector<std::vector<int>> & finalSeroDistribution )
{
  _finalAgeDistribution= finalAgeDistribution;
  _births = births;
  _deaths = deaths;
  _finalSeroDistribution = finalSeroDistribution;
}



std::vector<int>
DensimOutput::GetInitialAgeDistribution(void)
{
  return _initialAgeDistribution;
}



std::vector<int>
DensimOutput::GetFinalAgeDistribution(void)
{
  return _finalAgeDistribution;
}



std::vector<int>
DensimOutput::GetBirths(void)
{
  return _births;
}



std::vector<int>
DensimOutput::GetDeaths(void)
{
  return _deaths;
}


  
std::vector<int>
DensimOutput::GetInitialSeroDistribution( int serotype )
{
  std::vector<int> values;

  for( int i = 0; i < 18; ++i ) {
    values.push_back( _initialSeroDistribution[i][serotype] );
  }

  return values;
}



std::vector<int>
DensimOutput::GetFinalSeroDistribution( int serotype )
{
  std::vector<int> values;

  for( int i = 0; i < 18; ++i ) {
    values.push_back( _finalSeroDistribution[i][serotype] );
  }

  return values;
}



std::vector<double>
DensimOutput::GetDetailedSeroprevalence( int seroClass, int serotype )
{
  // sero classes:
  // 1 - MANA
  // 2 - MAEA
  // 3 - 0-1 years
  // 4 - 1-4 years
  // 5 - 5-9
  // 6 - 10-14
  // 7 - 15-19
  // 8 - 20-24
  // 9 - 25-29
  // 10 - 30-34
  // 11 - 35-39
  // 12 - 40-44
  // 13 - 45-49
  // 14 - 50-54
  // 15 - 55-59
  // 16 - 60-64
  // 17 - 65-69
  // 18 - 70-74
  // 19 - 75-79
  // 20 - 80+
  // 21 - 15-44
  // 22 - 45-80+
  // 23 - 0-80+  

  std::vector<double> values;

  day_iterator itDate = day_iterator(_startDate);
  for( ; *itDate <= _stopDate; ++itDate ) {
    values.push_back( _locationOutput[*itDate].SerPos[seroClass][serotype] );
  }

  return values;
}



std::vector<double>
DensimOutput::GetPersonsWithVirus( int serotype )
{
  std::vector<double> withVirus;
  SerotypeOutput & serotypeOutput = _serotypeOutputs[serotype];

  day_iterator itDate = day_iterator(_startDate);
  for( ; *itDate <= _stopDate; ++itDate ) {
    withVirus.push_back( serotypeOutput[*itDate].Incubating + serotypeOutput[*itDate].Viremic );
  }

  return withVirus;
}



std::vector<double>
DensimOutput::GetPersonsIncubating( int serotype )
{
  std::vector<double> incubating;
  SerotypeOutput & serotypeOutput = _serotypeOutputs[serotype];

  day_iterator itDate = day_iterator(_startDate);
  for( ; *itDate <= _stopDate; ++itDate ) {
    incubating.push_back( serotypeOutput[*itDate].Incubating );
  }

  return incubating;
}



std::vector<double>
DensimOutput::GetPersonsViremic( int serotype )
{
  std::vector<double> viremic;
  SerotypeOutput & serotypeOutput = _serotypeOutputs[serotype];

  day_iterator itDate = day_iterator(_startDate);
  for( ; *itDate <= _stopDate; ++itDate ) {
    viremic.push_back( serotypeOutput[*itDate].Viremic );
  }

  return viremic;
}



std::vector<double>
DensimOutput::GetEipDevelopmentRate( int serotype )
{
  std::vector<double> eipDevRate;
  SerotypeOutput & serotypeOutput = _serotypeOutputs[serotype];

  day_iterator itDate = day_iterator(_startDate);
  for( ; *itDate <= _stopDate; ++itDate ) {
    eipDevRate.push_back( serotypeOutput[*itDate].EipDevelopmentRate );
  }

  return eipDevRate;
}



std::vector<double>
DensimOutput::GetInfectiveMosquitoes( int serotype )
{
  std::vector<double> infvMosqs;
  SerotypeOutput & serotypeOutput = _serotypeOutputs[serotype];

  day_iterator itDate = day_iterator(_startDate);
  for( ; *itDate <= _stopDate; ++itDate ) {
    infvMosqs.push_back( serotypeOutput[*itDate].InfectiveMosquitoes );
  }

  return infvMosqs;
}



std::vector<int>
DensimOutput::GetPopulation(void)
{
  std::vector<int> humans;

  day_iterator itDate = day_iterator(_startDate);
  for( ; *itDate <= _stopDate; ++itDate ) {
    humans.push_back( _locationOutput[*itDate].NumHumans );
  }

  return humans;
}



std::vector<double>
DensimOutput::GetMosqTotal(void)
{
  std::vector<double> mosqs;

  day_iterator itDate = day_iterator(_startDate);
  for( ; *itDate <= _stopDate; ++itDate ) {
    mosqs.push_back( _locationOutput[*itDate].MosqTotal );
  }

  return mosqs;
}



std::vector<int>
DensimOutput::GetPotentiallyInfectiveBites(void)
{
  std::vector<int> bites;

  day_iterator itDate = day_iterator(_startDate);
  for( ; *itDate <= _stopDate; ++itDate ) {
    bites.push_back( _locationOutput[*itDate].InfvBites );
  }

  return bites;
}
