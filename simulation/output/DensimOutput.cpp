#include "StdAfx.h"
#include "DensimOutput.h"

using namespace boost::gregorian;
using namespace sim::output;



DensimOutput::DensimOutput(void)
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
DensimOutput::SetInitialData( std::vector<int> & initialAgeDistribution, std::vector<std::vector<int>> & initialSeroprevalence )
{
  _initialAgeDistribution = initialAgeDistribution;
  _initialSeroprevalence = initialSeroprevalence;
}



void
DensimOutput::SetFinalData( std::vector<int> & finalAgeDistribution, std::vector<int> & births, std::vector<int> & deaths,
                           std::vector<std::vector<int>> & finalSeroprevalence )
{
  _finalAgeDistribution= finalAgeDistribution;
  _births = births;
  _deaths = deaths;
  _finalSeroprevalence = finalSeroprevalence;
}



std::vector<int>
DensimOutput::GetInitialAgeDsitribution(void)
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
DensimOutput::GetInitialSeroprevalence( int serotype )
{
  std::vector<int> values;

  for( int i = 0; i < 18; ++i ) {
    values.push_back( _initialSeroprevalence[i][serotype] );
  }

  return values;
}



std::vector<int>
DensimOutput::GetFinalSeroprevalence( int serotype )
{
  std::vector<int> values;

  for( int i = 0; i < 18; ++i ) {
    values.push_back( _finalSeroprevalence[i][serotype] );
  }

  return values;
}



std::vector<double>
DensimOutput::GetDetailedSeroprevalence( boost::gregorian::date startDate, boost::gregorian::date stopDate, int ageClass, int serotype )
{
  std::vector<double> values;

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= stopDate; ++itDate ) {
    values.push_back( _locationOutput[*itDate].SerPos[ageClass][serotype] );
  }  

  return values;
}



std::vector<double>
DensimOutput::GetPersonsWithVirus( date startDate, date stopDate, int serotype )
{
  std::vector<double> withVirus;
  SerotypeOutput & serotypeOutput = _serotypeOutputs[serotype];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= stopDate; ++itDate ) {
    withVirus.push_back( serotypeOutput[*itDate].Incubating + serotypeOutput[*itDate].Viremic );
  }

  return withVirus;
}



std::vector<double>
DensimOutput::GetPersonsIncubating( date startDate, date stopDate, int serotype )
{
  std::vector<double> incubating;
  SerotypeOutput & serotypeOutput = _serotypeOutputs[serotype];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= stopDate; ++itDate ) {
    incubating.push_back( serotypeOutput[*itDate].Incubating );
  }

  return incubating;
}



std::vector<double>
DensimOutput::GetPersonsViremic( date startDate, date stopDate, int serotype )
{
  std::vector<double> viremic;
  SerotypeOutput & serotypeOutput = _serotypeOutputs[serotype];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= stopDate; ++itDate ) {
    viremic.push_back( serotypeOutput[*itDate].Viremic );
  }

  return viremic;
}



std::vector<double>
DensimOutput::GetEipDevelopmentRate(  date startDate, date stopDate,int serotype )
{
  std::vector<double> eipDevRate;
  SerotypeOutput & serotypeOutput = _serotypeOutputs[serotype];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= stopDate; ++itDate ) {
    eipDevRate.push_back( serotypeOutput[*itDate].EipDevelopmentRate );
  }

  return eipDevRate;
}



std::vector<double>
DensimOutput::GetInfectiveMosquitoes(  date startDate, date stopDate,int serotype )
{
  std::vector<double> infvMosqs;
  SerotypeOutput & serotypeOutput = _serotypeOutputs[serotype];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= stopDate; ++itDate ) {
    infvMosqs.push_back( serotypeOutput[*itDate].InfectiveMosquitoes );
  }

  return infvMosqs;
}



std::vector<int>
DensimOutput::GetNumberOfHumans( boost::gregorian::date startDate, boost::gregorian::date stopDate )
{
  std::vector<int> humans;

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= stopDate; ++itDate ) {
    humans.push_back( _locationOutput[*itDate].NumHumans );
  }

  return humans;
}



std::vector<double>
DensimOutput::GetMosqTotal( boost::gregorian::date startDate, boost::gregorian::date stopDate )
{
  std::vector<double> mosqs;

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= stopDate; ++itDate ) {
    mosqs.push_back( _locationOutput[*itDate].MosqTotal );
  }

  return mosqs;
}



std::vector<int>
DensimOutput::GetPotentiallyInfectiveBites( boost::gregorian::date startDate, boost::gregorian::date stopDate )
{
  std::vector<int> bites;

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= stopDate; ++itDate ) {
    bites.push_back( _locationOutput[*itDate].InfvBites );
  }

  return bites;
}
