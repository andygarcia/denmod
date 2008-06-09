#ifndef CS_SIM_CLASSES_H
#define CS_SIM_CLASSES_H

#include <string>
#include <map>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "../input/Control.h"



namespace sim {
namespace cs {

static const int YrLen = 365;
static const int MaxAgeEggs = 25;
static const int MaxAgeLarv = 100;
static const int MaxAgePupae = 25;
static const int MaxNumCt = 9;
static const int MaxAgePreOviAdults = 50;
static const int MaxAgeOviAdults = 50;



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
