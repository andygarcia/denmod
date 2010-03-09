#ifndef CONTROL_H
#define CONTROL_H

#include <vector>
#include "Schedule.h"



namespace input
{

class Container;

class Control
{
public:
  enum ControlType { SourceReduction = 0, OvipositionExclusion, EggDestruction, SterileMaleRelease, SpaceSpray, ResidualSpray, Larvicide };
  static std::string ControlTypeToString( ControlType ct );

public:
  Control( ControlType controlType, std::string name, bool enabled );
  virtual ~Control(void) {};

  virtual ControlType GetControlType(void);
  virtual std::string GetControlTypeAsString(void);

  std::string GetName(void);
  void SetName(std::string name);

  bool IsEnabled(void);
  void SetEnable( bool b );

protected:

  ControlType ControlType_;
  std::string Name_;
  bool Enabled_;
};

typedef std::vector<Control*> ControlCollection;



class ScheduledControl : public Control
{
public:
  ScheduledControl( ControlType controlType, std::string name, bool enabled, Schedule * schedule );
  virtual ~ScheduledControl(void);

  bool IsDateScheduled( boost::gregorian::date d );
  void CalculateSchedule( boost::gregorian::date minDate, boost::gregorian::date maxDate );

  Schedule::ScheduleType GetScheduleType(void);
  Schedule * GetSchedule(void);
  void SetSchedule( Schedule * schedule );

protected:
  Schedule * Schedule_;
};



class SourceReduction : public ScheduledControl
{
public:
  class Parameters
  {
  public:
    Parameters(void) : RateOfReduction(0) {}
    Parameters( double rateOfReduction ) : RateOfReduction( rateOfReduction ) {}
    double RateOfReduction;
  };

public:
  SourceReduction(void);
  SourceReduction( std::string name, bool enabled, Schedule * schedule );
  ~SourceReduction(void);
  
  bool IsTarget( std::string containerName);
  SourceReduction::Parameters * GetTargetParams( std::string containerName );

  std::map<std::string, SourceReduction::Parameters*> & GetTargets(void);
  void AddTarget( std::string containerName, SourceReduction::Parameters * params );

private:
  std::map<std::string, SourceReduction::Parameters*> Targets_;
};



class OvipositionExclusion : public ScheduledControl
{
public:
  class Parameters
  {
  public:
    Parameters(void) : RateOfExclusion(0), RateOfRecovery(0) {}
    Parameters( double rateOfExclusion, double rateOfRecovery ) : RateOfExclusion(rateOfExclusion), RateOfRecovery(rateOfRecovery) {}
    double RateOfExclusion;
    double RateOfRecovery;
  };

public:
  OvipositionExclusion(void);
  OvipositionExclusion( std::string name, bool enabled, Schedule * schedule );
  ~OvipositionExclusion(void);

  bool IsTarget( std::string containerName);
  OvipositionExclusion::Parameters * GetTargetParams( std::string containerName );

  std::map<std::string, OvipositionExclusion::Parameters*> & GetTargets(void);
  void AddTarget( std::string containerName, OvipositionExclusion::Parameters * params );

private:
  std::map<std::string, OvipositionExclusion::Parameters*> Targets_;
};



class EggDestruction : public ScheduledControl
{
public:
  class Parameters
  {
  public:
    Parameters(void) : RateOfDestruction(0) {}
    Parameters( double rateOfDestruction) : RateOfDestruction(rateOfDestruction) {}
    double RateOfDestruction;
  };

public:
  EggDestruction(void);
  EggDestruction( std::string name, bool enabled, Schedule * schedule );
  ~EggDestruction(void);

  bool IsTarget( std::string containerName);
  EggDestruction::Parameters * GetTargetParams( std::string containerName );

  std::map<std::string, EggDestruction::Parameters*> & GetTargets(void);
  void AddTarget( std::string containerName, EggDestruction::Parameters * params );

private:
  std::map<std::string, EggDestruction::Parameters*> Targets_;
};



class Larvicide : public ScheduledControl
{
public:
  class Parameters
  {
  public:
    Parameters(void) : RateOfTreatment(0) {}
    Parameters( double rateOfTreatment ) : RateOfTreatment(rateOfTreatment) {}
    double RateOfTreatment;
  };

public:
  Larvicide(void);
  Larvicide( std::string name, bool enabled, Schedule * schedule, int lagPeriod, double initMortality, int maxEffectPeriod, int declineEffectPeriod, bool effectLostOnDry );
  ~Larvicide(void);

  void CalculateMortality(void);

  bool IsTarget( std::string containerName);
  Larvicide::Parameters * GetTargetParams( std::string containerName );

  std::map<std::string, Larvicide::Parameters*> & GetTargets(void);
  void AddTarget( std::string containerName, Larvicide::Parameters * params );

  std::vector<double> & GetMortality(void);

  int GetLagPeriod(void);
  void SetLagPeriod( int lagPeriod );

  double GetInitialMortality(void);
  void SetInitialMortality( double initialMortality );

  int GetMaxEffectPeriod(void);
  void SetMaxEffectPeriod( int maxEffectPeriod );

  int GetDeclineEffectPeriod(void);
  void SetDeclineEffectPeriod( int declineEffectPeriod );

  bool IsEffectLostWhenDry(void);
  void SetEffectLostWhenDry( bool effectLostWhenDry );

private:
  std::map<std::string, Larvicide::Parameters*> Targets_;
  std::vector<double> Mortality_;
  int LagPeriod_;
  double InitialMortality_;
  int MaxEffectPeriod_;
  int DeclineEffectPeriod_;
  bool EffectLostWhenDry_;
};



class SterileMaleRelease : public ScheduledControl
{
public:
  SterileMaleRelease(void);
  SterileMaleRelease( std::string name, bool enabled, Schedule * schedule,
                      double numberReleased, double sterilityRate, double competitiveness, double ratioMaleToFemaleSurvival );
  ~SterileMaleRelease(void);

  double GetNumberReleased(void);
  void SetNumberReleased( double numberReleased );

  double GetSterilityRate(void);
  void SetSterilityRate( double sterilityRate );

  double GetCompetitiveness(void);
  void SetCompetitiveness( double competitiveness );

  double GetRatioMaleToFemaleSurvival(void);
  void SetRatioMaleToFemaleSurvival( double ratioMaleToFemaleSurvival );

private:
  double NumberReleased_;
  double SterilityRate_;
  double Competitiveness_;
  double RatioMaleToFemaleSurvival_;
};



class SpaceSpray : public ScheduledControl
{
public:
  SpaceSpray(void);
  SpaceSpray( std::string name, bool enabled, Schedule * schedule, double outdoorMortality, double indoorMortality );
  ~SpaceSpray(void);

  double GetOutdoorMortality(void);
  void SetOutdoorMortality( double outdoorMortality );

  double GetIndoorMortality(void);
  void SetIndoorMortality( double indoorMortality );

private:
  double OutdoorMortality_;
  double IndoorMortality_;
};



class ResidualSpray : public ScheduledControl
{
public:
  ResidualSpray(void);
  ResidualSpray( std::string name, bool enabled, Schedule * schedule,
                 double initialMortality, int maximumEffectPeriod, int residualEffectPeriod,
                 double treatedInteriorProportion, double treatedHousesProportion );
  ~ResidualSpray(void);

  void CalculateMortality(void);
  std::map<boost::gregorian::date, double> & GetMortality(void);
  double GetSurvival( boost::gregorian::date d );

  double GetInitialMortality(void);
  void SetInitialMortality(double initialMortality);

  int GetMaximumEffectPeriod(void);
  void SetMaximumEffectPeriod(int maximumEffectPeriod);

  int GetResidualEffectPeriod(void);
  void SetResidualEffectPeriod(int residualEffectPeriod);

  double GetTreatedInteriorProportion(void);
  void SetTreatedInteriorProportion(double treatedInteriorProportion);

  double GetTreatedHousesProportion(void);
  void SetTreatedHousesProportion(double treatedHousesProportion);

private:
  double InitialMortality_;
  std::map<boost::gregorian::date, double> Mortality_;
  int MaximumEffectPeriod_;
  int ResidualEffectPeriod_;
  double TreatedInteriorProportion_;
  double TreatedHousesProportion_;
};

};

#endif
