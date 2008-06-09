#include "StdAfx.h"
#include "CimsimOutput.h"

using namespace boost::gregorian;
using namespace sim::output;



CimsimOutput::CimsimOutput(void)
: AreContainersTotaled_(false),
  PopData_(NULL),
  IsPopDataReleased_(false)
{}



CimsimOutput::~CimsimOutput(void)
{
  if( IsPopDataReleased_ == false ) {
    // this still owns PopData
    delete PopData_;
  }
}



boost::gregorian::date_period
CimsimOutput::GetDateRange(void)
{
  date firstDate = LocationOutput_.begin()->first;
  date lastDate = LocationOutput_.rbegin()->first;
  return date_period( firstDate, lastDate );
}



void
CimsimOutput::AddDailyLocationOutput( DailyLocationOutput dlo, date d )
{
  LocationOutput_[d] = dlo;
}



void
CimsimOutput::AddDailyContainerOutput( DailyContainerOutput dco, date d, int containerID )
{
  ContainerOutputs_[containerID][d] = dco;
}



MosData *
CimsimOutput::GetMosData(void)
{
  MosData * mosData = new MosData();

  date_period dp = GetDateRange();
  date beginDate = dp.begin();
  date endDate = dp.end();

  year_iterator itYr(beginDate);
  for( ; itYr <= endDate; ++itYr ) {
    YearlyMosData ymd;
    
    day_iterator itDate(*itYr);
    date endOfYear = date( itYr->year(), 12, 31 );
    for( ; itDate <= endOfYear; ++itDate ) {
      DailyLocationOutput & dlo = LocationOutput_[*itDate];
      DailyMosData dmd = dlo.GetDailyMosData();

      ymd.AddDailyMosData( *itDate, dmd );
    }

    mosData->AddYearlyMosData( itYr->year(), ymd );
  }

  mosData->PreOviAdultCohorts = this->InitialPreOviAdultCohorts;
  mosData->OviAdultCohorts = this->InitialOviAdultCohorts;

  return mosData;
}



void
CimsimOutput::SetPopData( PopData * popData )
{
  PopData_ = popData;
}



PopData *
CimsimOutput::GetPopData(void)
{
  IsPopDataReleased_ = true;
  return PopData_;
}



std::vector<DailyDensimOutput>
CimsimOutput::GetDensimOutput( date startDate, date endDate )
{
  std::vector<DailyDensimOutput> densimOutput;

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    DailyDensimOutput ddso;
    ddso.NewFemales = LocationOutput_[*itDate].NewFemales;
    ddso.AverageWeight = LocationOutput_[*itDate].AverageWeight;
    ddso.OverallSurvival = LocationOutput_[*itDate].OverallSurvival;
    ddso.AdultDevelopment = LocationOutput_[*itDate].AdultDevelopment;
    densimOutput.push_back( ddso );
  }

  return densimOutput;
}



std::vector<DailyContainerOutput>
CimsimOutput::GetContainerOutput( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID )
{
  std::vector<DailyContainerOutput> containerOutput;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    DailyContainerOutput dco;
    dco.DayOfYear = co[*itDate].DayOfYear;
    dco.Depth = co[*itDate].Depth;
    dco.Food = co[*itDate].Food;
    dco.MaxTemp = co[*itDate].MaxTemp;
    dco.MinTemp = co[*itDate].MinTemp;
    dco.Eggs = co[*itDate].Eggs;
    dco.Larvae = co[*itDate].Larvae;
    dco.Pupae = co[*itDate].Pupae;
    dco.AvgDryPupWt = co[*itDate].AvgDryPupWt;
    dco.NewFemales = co[*itDate].NewFemales;
    dco.CumulativeFemales = co[*itDate].CumulativeFemales;
    dco.Oviposition = co[*itDate].Oviposition;
    containerOutput.push_back( dco);
  }
  return containerOutput;
}


  
std::vector<double>
CimsimOutput::GetFemales( date startDate, date endDate )
{
  std::vector<double> females;

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    females.push_back( LocationOutput_[*itDate].Females );
  }

  return females;
}



double
CimsimOutput::GetFemales( date d )
{
  return LocationOutput_[d].Females;  
  
}



std::vector<double>
CimsimOutput::GetNewFemales( date startDate, date endDate )
{
  std::vector<double> newFemales;

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    newFemales.push_back( LocationOutput_[*itDate].NewFemales );
  }

  return newFemales;
}



double
CimsimOutput::GetNewFemales( date d )
{
  return LocationOutput_[d].NewFemales;  
}



std::vector<double>
CimsimOutput::GetAverageFemaleWeight( boost::gregorian::date startDate, boost::gregorian::date endDate )
{
  std::vector<double> avgWeights;

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    avgWeights.push_back( LocationOutput_[*itDate].AverageWeight);
  }

  return avgWeights;
}



double
CimsimOutput::GetAverageFemaleWeight( boost::gregorian::date d )
{
  return LocationOutput_[d].AverageWeight;
}
  


std::vector<double>
CimsimOutput::GetOviposition( date startDate, date endDate )
{
  std::vector<double> oviposition;

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    oviposition.push_back( LocationOutput_[*itDate].Oviposition );
  }

  return oviposition;
}



double
CimsimOutput::GetOviposition( date d )
{
  return LocationOutput_[d].Oviposition;
}



std::vector<double> CimsimOutput::GetTotalPupae( boost::gregorian::date startDate, boost::gregorian::date endDate )
{
  if( !AreContainersTotaled_ ) {
    CalculateContainerTotals();
  }

  std::vector<double> totalPupae;

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    totalPupae.push_back( ContainerTotals_[*itDate].Pupae );
  }

  return totalPupae;
}



double
CimsimOutput::GetTotalPupae( date d )
{
  if( !AreContainersTotaled_ ) {
    CalculateContainerTotals();
  }

  return ContainerTotals_[d].Pupae;
}



std::vector<double> CimsimOutput::GetTotalLarvae( boost::gregorian::date startDate, boost::gregorian::date endDate )
{
  if( !AreContainersTotaled_ ) {
    CalculateContainerTotals();
  }

  std::vector<double> totalLarvae;

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    totalLarvae.push_back( ContainerTotals_[*itDate].Larvae );
  }

  return totalLarvae;
}



double
CimsimOutput::GetTotalLarvae( date d )
{
  if( !AreContainersTotaled_ ) {
    CalculateContainerTotals();
  }

  return ContainerTotals_[d].Larvae;
}



std::vector<double>
CimsimOutput::GetTotalEggs( date startDate, date endDate )
{
  if( !AreContainersTotaled_ ) {
    CalculateContainerTotals();
  }

  std::vector<double> totalEggs;

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    totalEggs.push_back( ContainerTotals_[*itDate].Eggs );
  }

  return totalEggs;
}



double
CimsimOutput::GetTotalEggs( date d )
{
  if( !AreContainersTotaled_ ) {
    CalculateContainerTotals();
  }

  return ContainerTotals_[d].Eggs;
}



std::vector<double>
CimsimOutput::GetDepth( date startDate, date endDate, int containerID )
{
  std::vector<double> depth;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    depth.push_back( co[*itDate].Depth );
  }

  return depth;
}



double
CimsimOutput::GetDepth( date d, int containerID )
{
  return ContainerOutputs_[containerID][d].Depth;
}



std::vector<double>
CimsimOutput::GetFood( date startDate, date endDate, int containerID )
{
  std::vector<double> food;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    food.push_back( co[*itDate].Food );
  }

  return food;
}



double
CimsimOutput::GetFood( date d, int containerID )
{
  return ContainerOutputs_[containerID][d].Food;
}



std::vector<double>
CimsimOutput::GetMaxTemp( date startDate, date endDate, int containerID )
{
  std::vector<double> maxTemp;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    maxTemp.push_back( co[*itDate].MaxTemp );
  }

  return maxTemp;
}



double
CimsimOutput::GetMaxTemp( date d, int containerID )
{
  return ContainerOutputs_[containerID][d].MaxTemp;
}



std::vector<double>
CimsimOutput::GetMinTemp( date startDate, date endDate, int containerID )
{
  std::vector<double> minTemp;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    minTemp.push_back( co[*itDate].MinTemp );
  }

  return minTemp;
}



double
CimsimOutput::GetMinTemp( date d, int containerID )
{
  return ContainerOutputs_[containerID][d].MinTemp;
}



std::vector<double>
CimsimOutput::GetEggs( date startDate, date endDate, int containerID )
{
  std::vector<double> eggs;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    eggs.push_back( co[*itDate].Eggs );
  }

  return eggs;
}



double
CimsimOutput::GetEggs( boost::gregorian::date d, int containerID )
{
  return ContainerOutputs_[containerID][d].Eggs;
}



std::vector<double>
CimsimOutput::GetLarvae( date startDate, date endDate, int containerID )
{
  std::vector<double> larvae;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    larvae.push_back( co[*itDate].Larvae );
  }

  return larvae;
}



double
CimsimOutput::GetLarvae( date d, int containerID )
{
  return ContainerOutputs_[containerID][d].Larvae;
}



std::vector<double>
CimsimOutput::GetPupae( date startDate, date endDate, int containerID )
{
  std::vector<double> pupae;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    pupae.push_back( co[*itDate].Pupae );
  }

  return pupae;
}



double
CimsimOutput::GetPupae( date d, int containerID )
{
  return ContainerOutputs_[containerID][d].Pupae;
}
 
std::vector<double>
CimsimOutput::GetAvgDryPupWt( date startDate, date endDate, int containerID )
{
  std::vector<double> avgDryPupWt;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    avgDryPupWt.push_back( co[*itDate].AvgDryPupWt );
  }

  return avgDryPupWt;
}



double
CimsimOutput::GetAvgDryPupWt( date d, int containerID )
{
  return ContainerOutputs_[containerID][d].AvgDryPupWt;
}

std::vector<double>
CimsimOutput::GetNewFemales( date startDate, date endDate, int containerID )
{
  std::vector<double> newFemales;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    newFemales.push_back( co[*itDate].NewFemales );
  }

  return newFemales;
}



double
CimsimOutput::GetNewFemales( date d, int containerID )
{
  return ContainerOutputs_[containerID][d].NewFemales;
}

std::vector<double>
CimsimOutput::GetCumulativeFemales( date startDate, date endDate, int containerID )
{
  std::vector<double> cumFemales;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    cumFemales.push_back( co[*itDate].CumulativeFemales );
  }

  return cumFemales;
}



double
CimsimOutput::GetCumulativeFemales( date d, int containerID )
{
  return ContainerOutputs_[containerID][d].CumulativeFemales;
}



std::vector<double>
CimsimOutput::GetOviposition( date startDate, date endDate, int containerID )
{
  std::vector<double> oviposition;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    oviposition.push_back( co[*itDate].Oviposition );
  }

  return oviposition;
}



double
CimsimOutput::GetOviposition( date d, int containerID )
{
  return ContainerOutputs_[containerID][d].Oviposition;
}



std::vector<double>
CimsimOutput::GetTotalDensity( date startDate, date endDate, int containerID )
{
  std::vector<double> totalDensity;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    totalDensity.push_back( co[*itDate].TotalDensity );
  }

  return totalDensity;
}



double
CimsimOutput::GetTotalDensity( date d, int containerID )
{
  return ContainerOutputs_[containerID][d].TotalDensity;
}

std::vector<double>
CimsimOutput::GetUntreatedDensity( date startDate, date endDate, int containerID )
{
  std::vector<double> untreatedDensity;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    untreatedDensity.push_back( co[*itDate].UntreatedDensity );
  }

  return untreatedDensity;
}



double
CimsimOutput::GetUntreatedDensity( date d, int containerID )
{
  return ContainerOutputs_[containerID][d].UntreatedDensity;
}

std::vector<double>
CimsimOutput::GetTreatedDensity( date startDate, date endDate, int containerID )
{
  std::vector<double> treatedDensity;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    treatedDensity.push_back( co[*itDate].TreatedDensity );
  }

  return treatedDensity;
}



double
CimsimOutput::GetTreatedDensity( date d, int containerID )
{
  return ContainerOutputs_[containerID][d].TreatedDensity;
}

std::vector<double>
CimsimOutput::GetExcludedDensity( date startDate, date endDate, int containerID )
{
  std::vector<double> excludedDensity;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    excludedDensity.push_back( co[*itDate].ExcludedDensity );
  }

  return excludedDensity;
}



double
CimsimOutput::GetExcludedDensity( date d, int containerID )
{
  return ContainerOutputs_[containerID][d].ExcludedDensity;
}



void
CimsimOutput::CalculateContainerTotals(void)
{
  date startDate = LocationOutput_.begin()->first;
  date endDate = LocationOutput_.rbegin()->first;

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    DailyContainerOutput dco;

    ContainerOutputs::iterator itCos;
    for( itCos = ContainerOutputs_.begin(); itCos != ContainerOutputs_.end(); ++itCos ) {
      ContainerOutput & co = itCos->second;
      double densityScale = co[*itDate].UntreatedDensity + co[*itDate].TreatedDensity;
      dco.Eggs += co[*itDate].Eggs * densityScale;
      dco.Larvae += co[*itDate].Larvae * densityScale;
      dco.Pupae += co[*itDate].Pupae * densityScale;
      dco.NewFemales += co[*itDate].NewFemales * densityScale;
      dco.CumulativeFemales += co[*itDate].CumulativeFemales * densityScale;
      dco.Oviposition += co[*itDate].Oviposition * densityScale;
    }

    ContainerTotals_[*itDate] = dco;
  }
  AreContainersTotaled_ = true;
}



DailyMosData
DailyLocationOutput::GetDailyMosData(void)
{
  DailyMosData dmd;

  dmd.NewFemales = this->NewFemales;
  dmd.AverageWeight = this->AverageWeight;
  dmd.OverallSurvival = this->OverallSurvival;
  dmd.AdultDevelopment = this->AdultDevelopment;

  return dmd;
}