#include "StdAfx.h"
#include "SimClasses.h"

using namespace sim::cs;



ExcludedDensity::ExcludedDensity(void)
: Density(0), RateOfRecovery(0), ApplyMonthlyLoss(false)
{}



ExcludedDensity::~ExcludedDensity(void)
{}



LarvicideTreatment::LarvicideTreatment(void)
{}



LarvicideTreatment::LarvicideTreatment( input::Larvicide * li, boost::gregorian::date startDate )
: LoseOnDry(li->IsEffectLostWhenDry()),
  InEffect(true)
{
  // determine length of treatment period
  int totalPeriod = li->GetLagPeriod() + li->GetMaxEffectPeriod() + li->GetDeclineEffectPeriod();

  // get mortality by period from larvicide description
  std::vector<double> & periodMortality = li->GetMortality();
  
  // now create map of mortality by date
  this->Mortality = std::map<boost::gregorian::date,double>();
  for( int i = 0; i < totalPeriod; ++i ) {
    this->Mortality[startDate + boost::gregorian::days(i)] = periodMortality[i];
  }
}



double
LarvicideTreatment::GetMortality( boost::gregorian::date d )
{
  return Mortality[d];
}



bool
LarvicideTreatment::IsDateInTreatmentPeriod( boost::gregorian::date d )
{
  std::map<boost::gregorian::date, double>::iterator itMort;

  itMort = Mortality.find( d );
  if( itMort != Mortality.end() ) {
    return true;
  }
  else {
    return false;
  }
}
