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
  if( !dco.IsCloned ) {
    // simple case for non cloned containers, this dco is the only dco for the container type
    ContainerOutputs_[containerID][d] = dco;
  }
  else {
    // for cloned container we require the aggregation of output

    // start by pulling the existing output for this container type
    DailyContainerOutput & currentDco = ContainerOutputs_[containerID][d];

    // if no data has been added yet...
    if( currentDco.CloneDataCount == 0 ) {
      // just push ours in (flagged cloned) and set the count
      currentDco = dco;
      currentDco.CloneDataCount = 1;
    }
    else {
      // this require some math to average/accumulate outputs

      // average the water environment
      currentDco.Depth = (currentDco.Depth + dco.Depth ) / 2;
      currentDco.MaxTemp = (currentDco.MaxTemp + dco.MaxTemp ) / 2;
      currentDco.MinTemp = (currentDco.MinTemp + dco.MinTemp ) / 2;

      // accumulate container densities
      currentDco.TotalDensity += dco.TotalDensity;
      currentDco.UntreatedDensity += dco.UntreatedDensity;
      currentDco.TreatedDensity += dco.TreatedDensity;
      currentDco.ExcludedDensity += dco.ExcludedDensity;

      // average development rates
      currentDco.EggDevelopment = dco.EggDevelopment;
      currentDco.LarvaeDevelopment = dco.LarvaeDevelopment;
      currentDco.PupaeDevelopment = dco.PupaeDevelopment;

      // accumulate stage related outputs
      currentDco.Eggs += dco.Eggs;
      currentDco.Larvae += dco.Larvae;
      currentDco.LarvaeFasting += dco.LarvaeFasting;
      currentDco.LarvaeDeathFromFasting += dco.LarvaeDeathFromFasting;
      currentDco.NewFemales += dco.NewFemales;
      currentDco.CumulativeFemales += dco.CumulativeFemales;
      currentDco.Oviposition += dco.Oviposition;

      // average food related output
      currentDco.Food = (currentDco.Food + dco.Food) / 2.0;
      currentDco.FoodAddition = (currentDco.FoodAddition + dco.FoodAddition) / 2.0;
      currentDco.FoodConsumption = (currentDco.FoodConsumption + dco.FoodConsumption) / 2.0;
      currentDco.CadaverFoodContribution = (currentDco.CadaverFoodContribution + dco.CadaverFoodContribution) / 2.0;

      // accumulate pupae and average their weight (using true population average, not container averages)
      double existingWeight = currentDco.Pupae * currentDco.AvgDryPupWt;
      double newWeight = dco.Pupae * dco.AvgDryPupWt;
      double totalWeight = existingWeight + newWeight;

      currentDco.Pupae += dco.Pupae;
      if( currentDco.Pupae != 0 ) {
        currentDco.AvgDryPupWt = totalWeight / currentDco.Pupae;
      }
      else {
        currentDco.AvgDryPupWt = 0;
      }
    }
  }
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



std::vector<double>
CimsimOutput::GetAdultDevelopment( date startDate, date endDate )
{
  std::vector<double> values;

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    values.push_back( LocationOutput_[*itDate].AdultDevelopment );
  }

  return values;
}



std::vector<double>
CimsimOutput::GetFemales( date startDate, date endDate )
{
  std::vector<double> values;

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    values.push_back( LocationOutput_[*itDate].Females );
  }

  return values;
}



std::vector<double>
CimsimOutput::GetHostSeekingFemales( date startDate, date endDate )
{
  std::vector<double> values;

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    values.push_back( LocationOutput_[*itDate].HostSeekingFemales );
  }

  return values;
}



std::vector<double>
CimsimOutput::GetOvipositingFemales( date startDate, date endDate )
{
  std::vector<double> values;

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    values.push_back( LocationOutput_[*itDate].OvipositingFemales );
  }

  return values;
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



std::vector<double>
CimsimOutput::GetNewFemaleWeight( date startDate, date endDate )
{
  std::vector<double> newFemaleWeight;

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    newFemaleWeight.push_back( LocationOutput_[*itDate].NewFemaleWeight );
  }

  return newFemaleWeight;
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



std::vector<double>
CimsimOutput::GetTotalPupae( boost::gregorian::date startDate, boost::gregorian::date endDate )
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



std::vector<double>
CimsimOutput::GetTotalLarvae( boost::gregorian::date startDate, boost::gregorian::date endDate )
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



std::vector<double>
CimsimOutput::GetFoodAddition( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID )
{
  std::vector<double> values;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    values.push_back( co[*itDate].FoodAddition );
  }

  return values;
}



std::vector<double>
CimsimOutput::GetFoodConsumption( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID )
{
  std::vector<double> values;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    values.push_back( co[*itDate].FoodConsumption );
  }

  return values;
}



std::vector<double>
CimsimOutput::GetCadaverFoodContribution( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID )
{
  std::vector<double> values;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    values.push_back( co[*itDate].CadaverFoodContribution);
  }

  return values;
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



std::vector<double>
CimsimOutput::GetLarvae( date startDate, date endDate, int containerID )
{
  std::vector<double> values;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    values.push_back( co[*itDate].Larvae );
  }

  return values;
}



std::vector<double>
CimsimOutput::GetLarvaeFasting( date startDate, date endDate, int containerID )
{
  std::vector<double> values;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    values.push_back( co[*itDate].LarvaeFasting );
  }

  return values;
}



std::vector<double>
CimsimOutput::GetLarvaeDeathFromFasting( date startDate, date endDate, int containerID )
{
  std::vector<double> values;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    values.push_back( co[*itDate].LarvaeDeathFromFasting );
  }

  return values;
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



std::vector<double>
CimsimOutput::GetEggDevelopment( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID )
{
  std::vector<double> values;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    values.push_back( co[*itDate].EggDevelopment );
  }

  return values;
}



std::vector<double>
CimsimOutput::GetLarvaeDevelopment( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID )
{
  std::vector<double> values;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    values.push_back( co[*itDate].LarvaeDevelopment );
  }

  return values;
}



std::vector<double>
CimsimOutput::GetPupaeDevelopment( boost::gregorian::date startDate, boost::gregorian::date endDate, int containerID )
{
  std::vector<double> values;
  ContainerOutput & co = ContainerOutputs_[containerID];

  day_iterator itDate = day_iterator(startDate);
  for( ; *itDate <= endDate; ++itDate ) {
    values.push_back( co[*itDate].PupaeDevelopment );
  }

  return values;
}




DailyMosData
DailyLocationOutput::GetDailyMosData(void)
{
  DailyMosData dmd;

  dmd.NewFemales = this->NewFemales;
  dmd.NewFemaleWeight = this->NewFemaleWeight;
  dmd.AverageWeight = this->AverageWeight;
  dmd.OverallSurvival = this->OverallSurvival;
  dmd.AgeIndependentSurvival = this->AgeIndependentSurvival;
  dmd.AdultDevelopment = this->AdultDevelopment;

  return dmd;
}