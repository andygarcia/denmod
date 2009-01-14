#ifndef OUTPUT_MOSDATA_H
#define OUTPUT_MOSDATA_H

#include <map>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "../cimsim/Cohorts.h"


// TODO - an std::vector would be more effecient for this, constant time to access and append to end
// let any more complicated mappings occur by member methods


namespace sim {
namespace output {

class DailyMosData
{
public:
  DailyMosData(void) {}
  virtual ~DailyMosData(void) {}

public:
  double NewFemales;
  double AverageWeight;
  double OverallSurvival;
  double AdultDevelopment;
};



class YearlyMosData
{
public:
  YearlyMosData(void);
  virtual ~YearlyMosData(void);

public:
  DailyMosData & GetDailyMosData( boost::gregorian::date d );
  void AddDailyMosData( boost::gregorian::date d, DailyMosData dailyMosData );


public:
  // TODO reimplement this using a static array:
  // mosdata is generated from SimOutput post simulation
  // so array bounds would be known
  std::map<boost::gregorian::date, DailyMosData> YearlyMosData_;
};



class MosData
{
// Typedef
  typedef std::map<int, YearlyMosData> YearlyMosDataCollection;

// Constructor
public:
  MosData(void);
  virtual ~MosData(void);

// Methods
public:
  boost::gregorian::date_period GetMosDataPeriod(void);
  DailyMosData & GetMosData( boost::gregorian::date d );
  YearlyMosData & GetYearlyMosData( int year );
  void AddYearlyMosData( int year, YearlyMosData yearlyMosData );

// Fields
public:
  // initial starting population of CIMSiM
  sim::cs::PreOviAdultCohortCollection PreOviAdultCohorts;
  sim::cs::OviAdultCohortCollection OviAdultCohorts;
private:
  YearlyMosDataCollection YearlyMosDataCollection_;
};

};
};

#endif
