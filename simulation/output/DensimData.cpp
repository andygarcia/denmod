#include "StdAfx.h"
#include "DensimData.h"

using namespace boost::gregorian;
using namespace sim::output;



DensimData::DensimData(void)
{}



DensimData::~DensimData(void)
{}



boost::gregorian::date_period
DensimData::GetDateRange(void)
{
  date firstDate = LocationOutput_.begin()->first;
  date lastDate = LocationOutput_.rbegin()->first;
  return date_period( firstDate, lastDate );
}



void
DensimData::AddDailyLocationOutput( DailyLocationOutput dlo, date d )
{
  LocationOutput_[d] = dlo;

  DailySerotypeOutput dso1;
  dso1.Incubating = dlo.Incubate1;
  dso1.Viremic = dlo.Viremic1;
  dso1.InfectiveMosquitoes = dlo.MosqInfvTotal[1];
  dso1.EipDevelopmentRate = dlo.EIPDevRate[1];
  dso1.NewCases = dlo.NewHumCases[1];
  Dengue1Output_[d] = dso1;

  DailySerotypeOutput dso2;
  dso2.Incubating = dlo.Incubate2;
  dso2.Viremic = dlo.Viremic2;
  dso2.InfectiveMosquitoes = dlo.MosqInfvTotal[2];
  dso2.EipDevelopmentRate = dlo.EIPDevRate[2];
  dso2.NewCases = dlo.NewHumCases[2];
  Dengue2Output_[d] = dso2;

  DailySerotypeOutput dso3;
  dso3.Incubating = dlo.Incubate3;
  dso3.Viremic = dlo.Viremic3;
  dso3.InfectiveMosquitoes = dlo.MosqInfvTotal[3];
  dso3.EipDevelopmentRate = dlo.EIPDevRate[3];
  dso3.NewCases = dlo.NewHumCases[3];
  Dengue3Output_[d] = dso3;

  DailySerotypeOutput dso4;
  dso4.Incubating = dlo.Incubate4;
  dso4.Viremic = dlo.Viremic4;
  dso4.InfectiveMosquitoes = dlo.MosqInfvTotal[4];
  dso4.EipDevelopmentRate = dlo.EIPDevRate[4];
  dso4.NewCases = dlo.NewHumCases[4];
  Dengue4Output_[d] = dso4;
}



void
DensimData::SetInitialData( std::vector<int>& initialAgeDistribution )
{
  InitialAgeDistribution_ = initialAgeDistribution;
}



void
DensimData::SetFinalData( std::vector<int>& finalAgeDistribution, std::vector<int>& births, std::vector<int>& deaths )
{
  FinalAgeDistribution_= finalAgeDistribution;
  Births_ = births;
  Deaths_ = deaths;
}



std::vector<int>
DensimData::GetInitialAgeDsitribution(void)
{
  return InitialAgeDistribution_;
}



std::vector<int>
DensimData::GetFinalAgeDsitribution(void)
{
  return FinalAgeDistribution_;
}



std::vector<int>
DensimData::GetBirths(void)
{
  return Births_;
}



std::vector<int>
DensimData::GetDeaths(void)
{
  return Deaths_;
}


  
double
DensimData::GetDengue1Virus( boost::gregorian::date d )
{
  return Dengue1Output_[d].Incubating + Dengue1Output_[d].Viremic;
}



double
DensimData::GetDengue2Virus( boost::gregorian::date d )
{
  return Dengue2Output_[d].Incubating + Dengue2Output_[d].Viremic;
}



double
DensimData::GetDengue3Virus( boost::gregorian::date d )
{
  return Dengue3Output_[d].Incubating + Dengue3Output_[d].Viremic;
}



double
DensimData::GetDengue4Virus( boost::gregorian::date d )
{
  return Dengue4Output_[d].Incubating + Dengue4Output_[d].Viremic;
}



double
DensimData::GetDengue1Incubating( boost::gregorian::date d )
{
  return Dengue1Output_[d].Incubating;
}



double
DensimData::GetDengue2Incubating( boost::gregorian::date d )
{
  return Dengue2Output_[d].Incubating;
}



double
DensimData::GetDengue3Incubating( boost::gregorian::date d )
{
  return Dengue3Output_[d].Incubating;
}



double
DensimData::GetDengue4Incubating( boost::gregorian::date d )
{
  return Dengue4Output_[d].Incubating;
}



double
DensimData::GetDengue1Viremic( boost::gregorian::date d )
{
  return Dengue1Output_[d].Viremic;
}



double
DensimData::GetDengue2Viremic( boost::gregorian::date d )
{
  return Dengue2Output_[d].Viremic;
}



double
DensimData::GetDengue3Viremic( boost::gregorian::date d )
{
  return Dengue3Output_[d].Viremic;
}



double
DensimData::GetDengue4Viremic( boost::gregorian::date d )
{
  return Dengue4Output_[d].Viremic;
}



double
DensimData::GetDengue1InfectiveMosquitoes( boost::gregorian::date d )
{
  return Dengue1Output_[d].InfectiveMosquitoes;
}



double
DensimData::GetDengue2InfectiveMosquitoes( boost::gregorian::date d )
{
  return Dengue2Output_[d].InfectiveMosquitoes;
}



double
DensimData::GetDengue3InfectiveMosquitoes( boost::gregorian::date d )
{
  return Dengue3Output_[d].InfectiveMosquitoes;
}



double
DensimData::GetDengue4InfectiveMosquitoes( boost::gregorian::date d )
{
  return Dengue4Output_[d].InfectiveMosquitoes;
}



double
DensimData::GetDengue1EipDevelopmentRate( boost::gregorian::date d )
{
  return Dengue1Output_[d].EipDevelopmentRate;
}



double
DensimData::GetDengue2EipDevelopmentRate( boost::gregorian::date d )
{
  return Dengue2Output_[d].EipDevelopmentRate;
}



double
DensimData::GetDengue3EipDevelopmentRate( boost::gregorian::date d )
{
  return Dengue3Output_[d].EipDevelopmentRate;
}



double
DensimData::GetDengue4EipDevelopmentRate( boost::gregorian::date d )
{
  return Dengue4Output_[d].EipDevelopmentRate;
}



int
DensimData::GetNumberOfHumans( date d )
{
  return LocationOutput_[d].NumHumans;
}



double
DensimData::GetMosqTotal( boost::gregorian::date d )
{
  return LocationOutput_[d].MosqTotal;
}



double
DensimData::GetPotentiallyInfectiveBites( boost::gregorian::date d )
{
  return LocationOutput_[d].InfvBites;
}