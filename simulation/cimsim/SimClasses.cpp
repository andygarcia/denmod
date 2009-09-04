#include "StdAfx.h"
#include "SimClasses.h"
#include <boost/random.hpp>
#include <boost/math/distributions/binomial.hpp>

// standard macros that collide in std namespace, must be undefined
#undef min
#undef max

using namespace sim::cs;



int StochasticAdvancement( int number, double advancementFactor )
{
  // rng related variables are static to persist between calls
  static bool initialize = true;
  static boost::mt19937 rng = boost::mt19937();
  static double rngMin = rng.min();
  static double rngMax = rng.max();

  if( initialize ) {
    // seed rng
    rng.seed( static_cast<boost::uint32_t>(time(NULL)) );

    // find limits of rng to standardize generates
    rngMin = rng.min();
    rngMax = rng.max();

    // done with initialization
    initialize = false;
  }

  // trivial special case, all advance
  if( advancementFactor == 1.0 ) {
    return number;
  }

  // create binomial distribution
  boost::math::binomial bindist( number, advancementFactor );

  // generate a probability between 0 and 1
  double p = (rng() - rngMin) / rngMax;
  
  // calculated the variate representing the number of survivors that coincides with the above probability
  int advancement = static_cast<int>( boost::math::quantile( bindist, p ) );

  return advancement;
}



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
