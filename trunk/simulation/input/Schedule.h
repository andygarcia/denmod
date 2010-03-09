#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include <map>

#pragma managed( push, off )
#include <boost/date_time/gregorian/gregorian.hpp>
#pragma managed( pop )



namespace input
{

class Schedule
{
public:
  enum ScheduleType { Single = 0, Weekly, Monthly, Yearly, Periodic };
  typedef std::vector<boost::gregorian::date> ScheduledDates;
  typedef std::vector<boost::gregorian::greg_weekday> ScheduledWeekdays;
  typedef std::vector<boost::gregorian::greg_month> ScheduledMonths;

public:
  Schedule( ScheduleType scheduleType );
  Schedule( ScheduleType scheduleType, boost::gregorian::date startDate );
  Schedule( ScheduleType scheduleType, boost::gregorian::date startDate, boost::gregorian::date stopDate );
  virtual ~Schedule(void) {}

  ScheduleType GetScheduleType(void);
  std::string GetScheduleTypeAsString(void);

  boost::gregorian::date GetStartDate(void);
  void SetStartDate( boost::gregorian::date d );

  boost::gregorian::date GetStopDate(void);
  void SetStopDate( boost::gregorian::date d );

  bool UsingStopDate(void);
  void UseStopDate( bool useStopDate );

  std::vector<boost::gregorian::date> & GetScheduledDates(void);
  bool IsDateScheduled( boost::gregorian::date d );

  void CalculateSchedule( boost::gregorian::date minDate, boost::gregorian::date maxDate );

protected:
  virtual void InitializeSchedule(void) = 0;

protected:
  ScheduleType ScheduleType_;

  boost::gregorian::date StartDate_;
  boost::gregorian::date StopDate_;
  bool UseStopDate_;

  boost::gregorian::date MinDate_;
  boost::gregorian::date MaxDate_;

  ScheduledDates ScheduledDates_;


};



class SingleSchedule : public Schedule
{
public:
  SingleSchedule();
  SingleSchedule( boost::gregorian::date date );

  boost::gregorian::date GetDate();
  void SetDate( boost::gregorian::date d );

private:
  virtual void InitializeSchedule(void);
};



class WeeklySchedule : public Schedule
{
public:
  WeeklySchedule();
  WeeklySchedule( int weekInterval, ScheduledWeekdays days, boost::gregorian::date startDate );
  WeeklySchedule( int weekInterval, ScheduledWeekdays days, boost::gregorian::date startDate, boost::gregorian::date stopDate );

  int GetWeekInterval(void);
  void SetWeekInterval( int weekInterval );

  bool IsWeekdayScheduled( boost::gregorian::greg_weekday wd );
  void EnableWeekday( boost::gregorian::greg_weekday wd );

private:
  virtual void InitializeSchedule(void);

private:
  int WeekInterval_;
  ScheduledWeekdays ScheduledWeekDays_;
};



class MonthlySchedule : public Schedule
{
public:
  MonthlySchedule();
  MonthlySchedule( int monthInterval, ScheduledMonths months, boost::gregorian::date startDate );
  MonthlySchedule( int monthInterval, ScheduledMonths months, boost::gregorian::date startDate, boost::gregorian::date stopDate );

  int GetMonthInterval(void);
  void SetMonthInterval( int monthInterval );

  bool IsMonthScheduled( boost::gregorian::greg_month month );
  void EnableMonth( boost::gregorian::greg_month month );

private:
  virtual void InitializeSchedule(void);

private:
  int MonthInterval_;
  ScheduledMonths ScheduledMonths_;
};



class YearlySchedule : public Schedule
{
public:
  YearlySchedule();
  YearlySchedule( int yearInterval );

  int GetYearInterval(void);
  void SetYearInterval( int yearInterval );

private:
  virtual void InitializeSchedule(void);

private:
  int YearInterval_;
};



class PeriodicSchedule : public Schedule
{
public:
  PeriodicSchedule();
  PeriodicSchedule( boost::gregorian::date startDate, int numberOfTreatments, int treatmentInterval );
  PeriodicSchedule( boost::gregorian::date startDate, int treatmentInterval, boost::gregorian::date stopDate );

  int GetTreatmentInterval(void);
  void SetTreatmentInterval( int treatmentInterval );

  int GetNumberOfTreatments(void);
  void SetNumberOfTreatments( int numTreatments );

private:
  virtual void InitializeSchedule(void);

  int TreatmentInterval_;
  int NumberOfTreatments_;
};

};

#endif
