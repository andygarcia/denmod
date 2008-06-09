#include "StdAfx.h"
#include "DensimOutput.h"

using namespace boost::gregorian;
using namespace sim::output;



DensimOutput::DensimOutput( boost::gregorian::date startDate, boost::gregorian::date stopDate )
: _locationOutput( startDate, stopDate)
{
  _serotypeOutputs[1] = SerotypeOutput( startDate, stopDate );
  _serotypeOutputs[2] = SerotypeOutput( startDate, stopDate );
  _serotypeOutputs[3] = SerotypeOutput( startDate, stopDate );
  _serotypeOutputs[4] = SerotypeOutput( startDate, stopDate );
}



DensimOutput::~DensimOutput(void)
{}



void
DensimOutput::AddDailyLocationOutput( DailyLocationOutput dlo, date d )
{
  _locationOutput.TotalFemales.PushData( dlo.MosqTotal );
  _locationOutput.InfvBites.PushData( dlo.InfvBites );
  _locationOutput.Humans.PushData( dlo.NumHumans );

  _serotypeOutputs[1].Incubating.PushData( dlo.Incubate1 );
  _serotypeOutputs[1].Viremic.PushData( dlo.Viremic1 );
  _serotypeOutputs[1].InfectiveMosquitoes.PushData( dlo.MosqInfvTotal[1] );
  _serotypeOutputs[1].EipDevelopmentRate.PushData( dlo.EIPDevRate[1] );
  _serotypeOutputs[1].NewCases.PushData( dlo.NewHumCases[1] );

  _serotypeOutputs[2].Incubating.PushData( dlo.Incubate2 );
  _serotypeOutputs[2].Viremic.PushData( dlo.Viremic2 );
  _serotypeOutputs[2].InfectiveMosquitoes.PushData( dlo.MosqInfvTotal[2] );
  _serotypeOutputs[2].EipDevelopmentRate.PushData( dlo.EIPDevRate[2] );
  _serotypeOutputs[2].NewCases.PushData( dlo.NewHumCases[2] );

  _serotypeOutputs[3].Incubating.PushData( dlo.Incubate3 );
  _serotypeOutputs[3].Viremic.PushData( dlo.Viremic3 );
  _serotypeOutputs[3].InfectiveMosquitoes.PushData( dlo.MosqInfvTotal[3] );
  _serotypeOutputs[3].EipDevelopmentRate.PushData( dlo.EIPDevRate[3] );
  _serotypeOutputs[3].NewCases.PushData( dlo.NewHumCases[3] );

  _serotypeOutputs[4].Incubating.PushData( dlo.Incubate4 );
  _serotypeOutputs[4].Viremic.PushData( dlo.Viremic4 );
  _serotypeOutputs[4].InfectiveMosquitoes.PushData( dlo.MosqInfvTotal[4] );
  _serotypeOutputs[4].EipDevelopmentRate.PushData( dlo.EIPDevRate[4] );
  _serotypeOutputs[4].NewCases.PushData( dlo.NewHumCases[4] );
}



void
DensimOutput::SetInitialData( ClassData& initialAgeDistribution )
{
  _initialAgeDistribution = initialAgeDistribution;
}



void
DensimOutput::SetFinalData( ClassData& finalAgeDistribution, ClassData& births, ClassData& deaths )
{
  _finalAgeDistribution= finalAgeDistribution;
  _births = births;
  _deaths = deaths;
}



DensimOutput::ClassData
DensimOutput::GetInitialAgeDsitribution(void)
{
  return _initialAgeDistribution;
}



DensimOutput::ClassData
DensimOutput::GetFinalAgeDsitribution(void)
{
  return _finalAgeDistribution;
}



DensimOutput::ClassData
DensimOutput::GetBirths(void)
{
  return _births;
}



DensimOutput::ClassData
DensimOutput::GetDeaths(void)
{
  return _deaths;
}



std::vector<double>
DensimOutput::GetPersonsWithVirus( int serotype )
{
  SerotypeOutput & so = _serotypeOutputs[serotype];

  std::vector<double> & incubating = so.Incubating.GetAllDates();
  std::vector<double> & viremic = so.Viremic.GetAllDates();

  std::vector<double> withVirus = std::vector<double>( incubating.size() );

  for( unsigned int i = 0; i < incubating.size(); ++i ) {
    withVirus[i] = incubating[i] + viremic[i];
  }

  return withVirus;
}
  


std::vector<double> &
DensimOutput::GetPersonsIncubating( int serotype )
{
  SerotypeOutput & so = _serotypeOutputs[serotype];
  return so.Incubating.GetAllDates();
}



std::vector<double> &
DensimOutput::GetPersonsViremic( int serotype )
{
  SerotypeOutput & so = _serotypeOutputs[serotype];
  return so.Viremic.GetAllDates();
}



std::vector<double> &
DensimOutput::GetInfectiveMosquitoes( int serotype )
{
  SerotypeOutput & so = _serotypeOutputs[serotype];
  return so.InfectiveMosquitoes.GetAllDates();
}



std::vector<double> &
DensimOutput::GetEipDevelopmentRate( int serotype )
{
  SerotypeOutput & so = _serotypeOutputs[serotype];
  return so.EipDevelopmentRate.GetAllDates();
}



std::vector<int> &
DensimOutput::GetNumberOfHumans(void)
{
  return _locationOutput.Humans.GetAllDates();
}



std::vector<double>
DensimOutput::GetSimulationArea( double humanHostDensity )
{
  std::vector<int> humans = GetNumberOfHumans();
  std::vector<double> simArea = std::vector<double>( humans.size() );

  for( unsigned int i = 0; i < humans.size(); ++i ) {
    simArea[i] = humans[i] / humanHostDensity;
  }

  return simArea;
}



std::vector<double> &
DensimOutput::GetFemales(void)
{
  return _locationOutput.TotalFemales.GetAllDates();
}



std::vector<double>
DensimOutput::GetFemalesPerPerson(void)
{
  std::vector<double> & females = GetFemales();
  std::vector<int> & humans = GetNumberOfHumans();

  std::vector<double> femalesPerPerson = std::vector<double>( females.size() );

  for( unsigned int i = 0; i < females.size(); ++i ) {
    femalesPerPerson[i] = females[i] / humans[i];
  }

  return femalesPerPerson;
}



std::vector<int> &
DensimOutput::GetPotentiallyInfectiveBites(void)
{
  return _locationOutput.InfvBites.GetAllDates();
}
