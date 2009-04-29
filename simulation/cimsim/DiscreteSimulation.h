#ifndef CS_SIM_DISCRETE_SIMULATION_H
#define CS_SIM_DISCRETE_SIMULATION_H

#include "../input/Location.h"
#include "DiscreteSimLocation.h"



namespace sim {
namespace cs  {


class DiscreteSimulation
{
public:
  DiscreteSimulation( input::Location * location, boost::gregorian::date startDate, boost::gregorian::date stopDate, bool usePop = false );
public:
  virtual ~DiscreteSimulation(void);

  void Start(void);
  void DoFoodFitIteration( int numberOfRuns, boost::gregorian::date surveyStartDate, boost::gregorian::date surveyEndDate );

  sim::output::CimsimOutput * GetSimOutput(void);

private:
  boost::gregorian::date _startDate;
  boost::gregorian::date _stopDate;
  bool _usePop;
  output::PopData * _popData;

  DiscreteSimLocation * SimLocation_;
};



class FoodFitDiscreteSimulation
{
public:
  std::vector<double> ObservedPupae;

public:
  FoodFitDiscreteSimulation( input::Location * location, boost::gregorian::date surveyStartDate, boost::gregorian::date surveyStopDate );
  ~FoodFitDiscreteSimulation(void);

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
