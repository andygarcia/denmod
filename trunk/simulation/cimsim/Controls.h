#ifndef SIM_CS_CONTROLS_H
#define SIM_CS_CONTROLS_H

#include "../input/Control.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <map>



namespace sim {
namespace cs {

class ExcludedDensity
{
// Constructors
public:
  ExcludedDensity(void);
  ~ExcludedDensity(void);

// Fields
public:
  double Density;
  double RateOfRecovery;
  bool ApplyMonthlyLoss;
};



class LarvicideTreatment
{
// Constructors
public:
  LarvicideTreatment(void);
  LarvicideTreatment(input::Larvicide * li, boost::gregorian::date startDate);

// Methods
public:
  double GetMortality( boost::gregorian::date d );
  bool IsDateInTreatmentPeriod( boost::gregorian::date d );

// Fields
public:
  bool InEffect;
  std::map<boost::gregorian::date, double> Mortality;
  bool LoseOnDry;
};

};
};

#endif
