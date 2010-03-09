#include "StdAfx.h"
#include "Schedule.h"

using namespace boost::gregorian;
using namespace input;



Schedule::Schedule( ScheduleType scheduleType )
: ScheduleType_(scheduleType),
  StartDate_(date()),
  StopDate_(date()),
  UseStopDate_(false)
{}



Schedule::Schedule( ScheduleType scheduleType, date startDate )
: ScheduleType_(scheduleType),
  StartDate_(startDate),
  StopDate_(date()),
  UseStopDate_(false)
{}



Schedule::Schedule( ScheduleType scheduleType, date startDate, date stopDate )
: ScheduleType_(scheduleType),
  StartDate_(startDate),
  StopDate_(stopDate),
  UseStopDate_(true)
{}



Schedule::ScheduleType
Schedule::GetScheduleType(void)
{
  return ScheduleType_;
}



std::string
Schedule::GetScheduleTypeAsString(void)
{
  static std::string strings[] = { "Single", "Weekly", "Monthly", "Yearly", "Periodic" };
  return strings[ScheduleType_];
}



date
Schedule::GetStartDate(void)
{
  return StartDate_;
}



void
Schedule::SetStartDate( boost::gregorian::date d )
{
  StartDate_ = d;
}



boost::gregorian::date Schedule::GetStopDate(void)
{
  return StopDate_;
}



void Schedule::SetStopDate( boost::gregorian::date d )
{
  StopDate_ = d;
}



bool
Schedule::UsingStopDate(void)
{
  return UseStopDate_;
}



void
Schedule::UseStopDate( bool useStopDate )
{
  UseStopDate_ = useStopDate;
}



std::vector<date> &
Schedule::GetScheduledDates(void)
{
  return ScheduledDates_;
}



bool
Schedule::IsDateScheduled( boost::gregorian::date d )
{
  if( std::find(ScheduledDates_.begin(), ScheduledDates_.end(), d) == ScheduledDates_.end() ) {
    // date not found, not scheduled
    return false;
  }
  else {
    return true;
  }
}



void
Schedule::CalculateSchedule( date minDate, date maxDate )
{
  this->MinDate_ = minDate;
  this->MaxDate_ = maxDate;

  // allow individual schedule types to calculate their own scheduled dates
  this->InitializeSchedule();
}



SingleSchedule::SingleSchedule(void)
: Schedule(Single)
{}



SingleSchedule::SingleSchedule( date date )
: Schedule(Single)
{
  StartDate_ = date;
  StopDate_ = date;
}



date
SingleSchedule::GetDate(void)
{
  return StartDate_;
}



void
SingleSchedule::SetDate( date d )
{
  StartDate_ = d;
  StopDate_ = d;
}



void
SingleSchedule::InitializeSchedule(void)
{
  ScheduledDates_.push_back( StartDate_ );
}



WeeklySchedule::WeeklySchedule(void)
: Schedule(Weekly)
{}



WeeklySchedule::WeeklySchedule( int weekInterval, ScheduledWeekdays days, date startDate )
: Schedule( Weekly, startDate ),
  WeekInterval_(weekInterval),
  ScheduledWeekDays_(days)
{
}



WeeklySchedule::WeeklySchedule( int weekInterval, ScheduledWeekdays days, date startDate, date stopDate )
: Schedule( Weekly, startDate, stopDate ),
  WeekInterval_(weekInterval),
  ScheduledWeekDays_(days)
{}



int WeeklySchedule::GetWeekInterval(void)
{
  return WeekInterval_;
}



void WeeklySchedule::SetWeekInterval( int weekInterval )
{
  WeekInterval_ = weekInterval;
}



bool WeeklySchedule::IsWeekdayScheduled( boost::gregorian::greg_weekday wd )
{
  if( std::find(ScheduledWeekDays_.begin(), ScheduledWeekDays_.end(), wd) == ScheduledWeekDays_.end() ) {
    // not found - not scheduled
    return false;
  }
  else {
    return true;
  }
}


void WeeklySchedule::EnableWeekday( boost::gregorian::greg_weekday wd )
{
  ScheduledWeekDays_.push_back( wd );
}



void WeeklySchedule::InitializeSchedule(void)
{
  if( ScheduledWeekDays_.size() == 0 ) {
    // nothing to schedule
    return;
  }

  // if no stop date specified, schedule runs until end of simulation
  if( UseStopDate_ != true )
    StopDate_ = MaxDate_;

  // advance to closest scheduled weekday, since the specified
  // StartDate_ could possibly fall on a non scheduled weekday
  while( IsWeekdayScheduled( StartDate_.day_of_week() ) != true ) {
    // advance StartDate until a scheduled weekday is found
    StartDate_ = StartDate_ + date_duration(1);
  }

  // beginning with start date, move through each week, until end date
  week_iterator itWeeks( StartDate_, WeekInterval_ );
  for( ; itWeeks <= StopDate_; ++itWeeks ) {
    day_iterator itDays(*itWeeks);

    // iterate through a week of days
    for( ; itDays != *itWeeks + date_duration(7) && itDays <= StopDate_; ++itDays ) {

      // search scheduled weekdays for current weekday
      if( IsWeekdayScheduled(itDays->day_of_week()) ) {
        ScheduledDates_.push_back(*itDays);
      }
    }
  }
}



MonthlySchedule::MonthlySchedule(void)
: Schedule(Monthly)
{}


MonthlySchedule::MonthlySchedule( int monthInterval, ScheduledMonths months, date startDate )
: Schedule( Monthly, startDate ),
  MonthInterval_(monthInterval),
  ScheduledMonths_(months)
{}



MonthlySchedule::MonthlySchedule( int monthInterval, ScheduledMonths months, date startDate, date stopDate )
: Schedule( Monthly, startDate, stopDate ),
  MonthInterval_(monthInterval),
  ScheduledMonths_(months)
{}



int MonthlySchedule::GetMonthInterval(void)
{
  return MonthInterval_;
}



void MonthlySchedule::SetMonthInterval( int monthInterval )
{
  MonthInterval_ = monthInterval;
}


  
bool MonthlySchedule::IsMonthScheduled( boost::gregorian::greg_month m )
{
  if( std::find(ScheduledMonths_.begin(), ScheduledMonths_.end(), m) == ScheduledMonths_.end() ) {
    // not found - not scheduled
    return false;
  }
  else {
    return true;
  }
}



void MonthlySchedule::EnableMonth( boost::gregorian::greg_month month )
{
  ScheduledMonths_.push_back( month );
}



void MonthlySchedule::InitializeSchedule(void)
{
  // if not end date specified, schedule runs until end of simulation
  if( UseStopDate_ != true )
    StopDate_ = MaxDate_;

  // beginning with start date, move through each month, until end date
  month_iterator itMonths( StartDate_, MonthInterval_ );
  for( ; itMonths <= StopDate_; ++itMonths ) {
    // search scheduled months for current month
    if( IsMonthScheduled(itMonths->month()) ) {
      ScheduledDates_.push_back(*itMonths);
    }
  }
}



YearlySchedule::YearlySchedule(void)
: Schedule( Yearly)
{}



YearlySchedule::YearlySchedule( int yearInterval )
: Schedule(Yearly),
  YearInterval_(yearInterval)
{}




int YearlySchedule::GetYearInterval(void)
{
  return YearInterval_;
}



void YearlySchedule::SetYearInterval( int yearInterval )
{
  YearInterval_ = yearInterval;
}



void YearlySchedule::InitializeSchedule(void)
{
  // need day of year index
  int dayOfYear = this->StartDate_.day_of_year();

  // if no stop date specified, schedule runs until end of simulation
  if( UseStopDate_ != true )
    StopDate_ = MaxDate_;

  year_iterator itYear( StartDate_, YearInterval_ );
  for( ; itYear <= StopDate_; ++itYear ) {
    // always use the day index to prevent hiccups with leap years
    date d = date(itYear->year(),1,1) + date_duration(dayOfYear - 1);
    ScheduledDates_.push_back(d);
  }
}



PeriodicSchedule::PeriodicSchedule(void)
: Schedule(Periodic)
{}



PeriodicSchedule::PeriodicSchedule( date startDate, int numberOfTreatments, int treatmentInterval )
: Schedule( Periodic, startDate ),
  NumberOfTreatments_(numberOfTreatments),
  TreatmentInterval_(treatmentInterval)
{}



PeriodicSchedule::PeriodicSchedule( date startDate, int treatmentInterval, date stopDate )
: Schedule( Periodic, startDate, stopDate),
  NumberOfTreatments_(0),
  TreatmentInterval_(treatmentInterval)
{}



int PeriodicSchedule::GetTreatmentInterval(void)
{
  return TreatmentInterval_;
}



void PeriodicSchedule::SetTreatmentInterval( int treatmentInterval )
{
  TreatmentInterval_ = treatmentInterval;
}



int PeriodicSchedule::GetNumberOfTreatments(void)
{
  return NumberOfTreatments_;
}



void PeriodicSchedule::SetNumberOfTreatments( int numTreatments )
{
  NumberOfTreatments_ = numTreatments;
}



void PeriodicSchedule::InitializeSchedule(void)
{
  if( UseStopDate_ != true ) {
    // recall that StartDate will be date of the first treatment,
    // leaving (NumberOfTreatments - 1) treatments remaining
    StopDate_ = StartDate_ + date_duration( (NumberOfTreatments_ - 1) * TreatmentInterval_ );
  }

  day_iterator itDays( StartDate_, TreatmentInterval_ );
  for( ; itDays <= StopDate_; ++itDays ) {
    ScheduledDates_.push_back(*itDays);
  }
}
