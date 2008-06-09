#ifndef CS_SIM_SIMULATION_H
#define CS_SIM_SIMULATION_H

#include "../input/Location.h"
#include "SimLocation.h"



namespace sim {
namespace cs  {


class Simulation
{
public:
  Simulation( const input::Location * location, boost::gregorian::date startDate, boost::gregorian::date stopDate, bool usePop = false );
public:
  virtual ~Simulation(void);

  void Start(void);
  void DoFoodFitIteration( int numberOfRuns, boost::gregorian::date surveyStartDate, boost::gregorian::date surveyEndDate );

  sim::output::CimsimOutput * GetSimOutput(void);

private:
  boost::gregorian::date _startDate;
  boost::gregorian::date _stopDate;
  bool _usePop;
  output::PopData * _popData;

  SimLocation * SimLocation_;
};



class FoodFitSimulation
{
public:
  std::vector<double> ObservedPupae;

public:
  FoodFitSimulation( const input::Location * location, boost::gregorian::date surveyStartDate, boost::gregorian::date surveyStopDate );
  ~FoodFitSimulation(void);

  std::map<std::string,double> DoIteration( int numberOfRuns );

private:
  const input::Location * _location;

  boost::gregorian::date _startDate;
  boost::gregorian::date _stopDate;

  boost::gregorian::date _surveyStartDate;
  boost::gregorian::date _surveyStopDate;
  int _numberDaysSurveyed;

  output::PopData * _popData;
};

};
};

#endif
