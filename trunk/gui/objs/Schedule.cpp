#include "StdAfx.h"
#include "Schedule.h"

using namespace gui;



boost::gregorian::date
ToBoostDate( System::DateTime dt )
{
  // boost date_time library has different min/max points than .NET DateTime
  // map min year in .NET to min year in bost
  if( dt.Year < 1900 ) {
    return boost::gregorian::date( boost::gregorian::date::ymd_type(1900, dt.Month, dt.Day) );
  }
  return boost::gregorian::date( boost::gregorian::date::ymd_type( dt.Year, dt.Month, dt.Day ) );
}



System::String ^
Schedule::GetShortNameFromType( Schedule ^ s )
{
  // TODO - internationalization, but at least these aren't hardcoded completely into the gui
  System::Collections::Generic::Dictionary<System::Type^,System::String^> ^ typeToName = gcnew System::Collections::Generic::Dictionary<System::Type^,System::String^>();
  typeToName->Add( SingleSchedule::typeid, "Single" );
  typeToName->Add( WeeklySchedule::typeid , "Weekly" );
  typeToName->Add( MonthlySchedule::typeid, "Monthly" );
  typeToName->Add( YearlySchedule::typeid, "Yearly" );
  typeToName->Add( PeriodicSchedule::typeid, "Periodic" );

  return typeToName[s->GetType()];
}



System::Type ^
Schedule::GetTypeFromShortName( System::String ^ shortName )
{
  System::Collections::Generic::Dictionary<System::String^,System::Type^> ^ nameToType = gcnew System::Collections::Generic::Dictionary<System::String^,System::Type^>();
  nameToType->Add( "Single", SingleSchedule::typeid );
  nameToType->Add( "Weekly", WeeklySchedule::typeid );
  nameToType->Add( "Monthly", MonthlySchedule::typeid );
  nameToType->Add( "Yearly", YearlySchedule::typeid );
  nameToType->Add( "Periodic", PeriodicSchedule::typeid );

  return nameToType[shortName];
}


  
Schedule::Schedule(void)
: StartDate_(DateTime::MinValue),
  StopDate_(DateTime::MaxValue),
  UseStopDate_(false),
  MinDate_(DateTime::MinValue),
  MaxDate_(DateTime::MaxValue),
  ScheduledDates_(gcnew System::Collections::Generic::List<DateTime>())
{}



Schedule::Schedule( DateTime minDate, DateTime maxDate )
: StartDate_(minDate),
  StopDate_(maxDate),
  UseStopDate_(false),
  MinDate_(minDate),
  MaxDate_(maxDate),
  ScheduledDates_(gcnew System::Collections::Generic::List<DateTime>())
{}



Schedule::Schedule( const Schedule ^ s )
{
  this->StartDate_ = s->StartDate_;
  this->UseStopDate_ = s->UseStopDate_;
  this->StopDate_ = s->StopDate_;
  this->ScheduleType_ = s->ScheduleType_;
  this->MinDate_ = s->MinDate_;
  this->MaxDate_ = s->MaxDate_;
  this->ScheduledDates_ = s->ScheduledDates_;
}



SingleSchedule::SingleSchedule(void)
: Schedule()
{
  ScheduleType_ = ScheduleTypes::Single;
}



SingleSchedule::SingleSchedule( DateTime minDate, DateTime maxDate )
: Schedule(minDate, maxDate)
{}



SingleSchedule::SingleSchedule( const SingleSchedule ^ ss )
: Schedule(ss)
{}



SingleSchedule::~SingleSchedule(void)
{}



input::Schedule *
SingleSchedule::GetSimObject(void)
{
  input::SingleSchedule * ss = new input::SingleSchedule();

  ss->SetDate( ToBoostDate(this->StartDate_) );

  return ss;
}



void
SingleSchedule::InitializeSchedule(void)
{
  ScheduledDates_->Add( StartDate_ );
}



System::String ^
SingleSchedule::ToString(void)
{ 

  System::Text::StringBuilder ^ sb = gcnew System::Text::StringBuilder();
  sb->AppendLine( "Single Schedule:" );
  sb->AppendFormat( "  MinDate = {0}\n  MaxDate = {1}\n  StartDate = {2}\n  StopDate = {3}\n  UseStopDate = {4}",
                    MinDate_, MaxDate_, StartDate_, StopDate_, UseStopDate_ );
  sb->AppendLine();
  return sb->ToString();
}



WeeklySchedule::WeeklySchedule(void)
: Schedule(),
  WeekInterval_(1),
  Monday_(true)
{
  ScheduleType_ = ScheduleTypes::Weekly;
}



WeeklySchedule::WeeklySchedule( DateTime minDate, DateTime maxDate )
: Schedule(minDate, maxDate),
  WeekInterval_(1),
  Monday_(true)
{
  ScheduleType_ = ScheduleTypes::Weekly;
}



WeeklySchedule::WeeklySchedule( const WeeklySchedule ^ ws )
: Schedule( ws )
{
  this->WeekInterval_ = ws->WeekInterval_;
  this->Sunday_ = ws->Sunday_;
  this->Monday_ = ws->Monday_;
  this->Tuesday_ = ws->Tuesday_;
  this->Wednesday_ = ws->Wednesday_;
  this->Thursday_ = ws->Thursday_;
  this->Friday_ = ws->Friday_;
  this->Saturday_ = ws->Saturday_;
}



WeeklySchedule::~WeeklySchedule(void)
{}
  


input::Schedule *
WeeklySchedule::GetSimObject(void)
{
  input::WeeklySchedule * ws = new input::WeeklySchedule();

  ws->SetStartDate( ToBoostDate(this->StartDate_) );
  ws->UseStopDate( this->UseStopDate_ );
  ws->SetStopDate( ToBoostDate(this->StopDate_) );

  ws->SetWeekInterval( this->WeekInterval );

  if( Sunday_ ) {
    ws->EnableWeekday( boost::date_time::Sunday );
  }

  if( Monday_ ) {
    ws->EnableWeekday( boost::date_time::Monday );
  }

  if( Tuesday_ ) {
    ws->EnableWeekday( boost::date_time::Tuesday );
  }

  if( Wednesday_ ) {
    ws->EnableWeekday( boost::date_time::Wednesday );
  }

  if( Thursday_ ) {
    ws->EnableWeekday( boost::date_time::Thursday );
  }

  if( Friday_ ) {
    ws->EnableWeekday( boost::date_time::Friday );
  }

  if( Saturday_ ) {
    ws->EnableWeekday( boost::date_time::Saturday );
  }

  return ws;
}



void
WeeklySchedule::InitializeSchedule(void)
{
  //if( ScheduledWeekDays_.size() == 0 ) {
  //  // nothing to schedule
  //  return;
  //}

  //// if no stop date specified, schedule runs until end of simulation
  //if( UseStopDate_ != true )
  //  StopDate_ = MaxDate_;

  //// advance to closest scheduled weekday, since the specified
  //// StartDate_ could possibly fall on a non scheduled weekday
  //while( IsWeekdayScheduled( StartDate_.day_of_week() ) != true ) {
  //  // advance StartDate until a scheduled weekday is found
  //  StartDate_ = StartDate_ + date_duration(1);
  //}

  //// beginning with start date, move through each week, until end date
  //week_iterator itWeeks( StartDate_, WeekInterval_ );
  //for( ; itWeeks <= StopDate_; ++itWeeks ) {
  //  day_iterator itDays(*itWeeks);

  //  // iterate through a week of days
  //  for( ; itDays != *itWeeks + date_duration(7) && itDays <= StopDate_; ++itDays ) {

  //    // search scheduled weekdays for current weekday
  //    if( IsWeekdayScheduled(itDays->day_of_week()) ) {
  //      ScheduledDates_.push_back(*itDays);
  //    }
  //  }
  //}
}



System::String ^
WeeklySchedule::ToString(void)
{ 
  System::Text::StringBuilder ^ sb = gcnew System::Text::StringBuilder();
  sb->AppendLine( "WeeklySchedule" );
  sb->AppendFormat( "  MinDate = {0}\n  MaxDate = {1}\n  StartDate = {2}\n  StopDate = {3}\n  UseStopDate = {4}",
                    MinDate_, MaxDate_, StartDate_, StopDate_, UseStopDate_ );
  sb->AppendLine();
  sb->Append( "  On: ");
  if( Sunday_ ) sb->Append( "Sunday, " );
  if( Monday_ ) sb->Append( "Monday, " );
  if( Tuesday_ ) sb->Append( "Tuesday, " );
  if( Wednesday_ ) sb->Append( "Wednesday, " );
  if( Thursday_ ) sb->Append( "Thursday, " );
  if( Friday_ ) sb->Append( "Friday, " );
  if( Saturday_ ) sb->Append( "Saturday, " );

  sb->Remove( sb->Length - 2, 2 );
  sb->AppendLine();

  return sb->ToString();
}



MonthlySchedule::MonthlySchedule(void)
: Schedule(),
  MonthInterval_(1)
{
  ScheduleType_ = ScheduleTypes::Monthly;
}



MonthlySchedule::MonthlySchedule( DateTime minDate, DateTime maxDate )
: Schedule(minDate, maxDate),
  MonthInterval_(1)
{
  ScheduleType_ = ScheduleTypes::Monthly;
}



MonthlySchedule::MonthlySchedule( const MonthlySchedule ^ ms )
: Schedule(ms)
{
  this->MonthInterval_ = ms->MonthInterval_;
}



MonthlySchedule::~MonthlySchedule(void)
{}

  
  
input::Schedule *
MonthlySchedule::GetSimObject(void)
{
  input::MonthlySchedule * ms = new input::MonthlySchedule();

  ms->SetStartDate( ToBoostDate(this->StartDate_) );
  ms->UseStopDate( this->UseStopDate_ );
  ms->SetStopDate( ToBoostDate(this->StopDate_) );

  ms->SetMonthInterval( this->MonthInterval_ );
  ms->EnableMonth( boost::date_time::Jan );
  ms->EnableMonth( boost::date_time::Feb );
  ms->EnableMonth( boost::date_time::Mar );
  ms->EnableMonth( boost::date_time::Apr );
  ms->EnableMonth( boost::date_time::May );
  ms->EnableMonth( boost::date_time::Jun );
  ms->EnableMonth( boost::date_time::Jul );
  ms->EnableMonth( boost::date_time::Aug );
  ms->EnableMonth( boost::date_time::Sep );
  ms->EnableMonth( boost::date_time::Oct );
  ms->EnableMonth( boost::date_time::Nov );
  ms->EnableMonth( boost::date_time::Dec );

  return ms;
}



void
MonthlySchedule::InitializeSchedule(void)
{
  //// if not end date specified, schedule runs until end of simulation
  //if( UseStopDate_ != true )
  //  StopDate_ = MaxDate_;

  //// beginning with start date, move through each month, until end date
  //month_iterator itMonths( StartDate_, MonthInterval_ );
  //for( ; itMonths <= StopDate_; ++itMonths ) {
  //  // search scheduled months for current month
  //  if( IsMonthScheduled(itMonths->month()) ) {
  //    ScheduledDates_.push_back(*itMonths);
  //  }
  //}
}



System::String ^
MonthlySchedule::ToString(void)
{ 
  System::Text::StringBuilder ^ sb = gcnew System::Text::StringBuilder();
  sb->AppendLine( "Monthly Schedule" );
  sb->AppendFormat( "  MinDate = {0}\n  MaxDate = {1}\n  StartDate = {2}\n  StopDate = {3}\n  UseStopDate = {4}\n  MonthInterval= {5}",
                    MinDate_, MaxDate_, StartDate_, StopDate_, UseStopDate_, MonthInterval_ );
  sb->AppendLine();
  return sb->ToString();
}



YearlySchedule::YearlySchedule(void)
: Schedule(),
  YearInterval_(1)
{
  ScheduleType_ = ScheduleTypes::Yearly;
}



YearlySchedule::YearlySchedule( DateTime minDate, DateTime maxDate )
: Schedule(minDate, maxDate),
  YearInterval_(1)
{
  ScheduleType_ = ScheduleTypes::Yearly;
}



YearlySchedule::YearlySchedule( const YearlySchedule ^ ys )
: Schedule( ys )
{
  this->YearInterval_ = ys->YearInterval_;
}



YearlySchedule::~YearlySchedule(void) {}
  


input::Schedule *
YearlySchedule::GetSimObject(void)
{
  input::YearlySchedule * ys = new input::YearlySchedule();

  ys->SetStartDate( ToBoostDate(this->StartDate_) );
  ys->UseStopDate( this->UseStopDate_ );
  ys->SetStopDate( ToBoostDate(this->StopDate_) );

  ys->SetYearInterval( this->YearInterval_ );
  return ys;
}



void
YearlySchedule::InitializeSchedule(void)
{
  //// need day of year index
  //int dayOfYear = this->StartDate_.day_of_year();

  //// if no stop date specified, schedule runs until end of simulation
  //if( UseStopDate_ != true )
  //  StopDate_ = MaxDate_;

  //year_iterator itYear( StartDate_, YearInterval_ );
  //for( ; itYear <= StopDate_; ++itYear ) {
  //  // always use the day index to prevent hiccups with leap years
  //  date d = date(itYear->year(),1,1) + date_duration(dayOfYear - 1);
  //  ScheduledDates_.push_back(d);
  //}
}



System::String ^
YearlySchedule::ToString(void)
{ 
  System::Text::StringBuilder ^ sb = gcnew System::Text::StringBuilder();
  sb->AppendLine( "Yearly Schedule :" );
  sb->AppendFormat( "  MinDate = {0}\n  MaxDate = {1}\n  StartDate = {2}\n  StopDate = {3}\n  UseStopDate = {4}\n  YearInterval = {5}",
                    MinDate_, MaxDate_, StartDate_, StopDate_, UseStopDate_, YearInterval_ );
  sb->AppendLine();
  return sb->ToString();
}



PeriodicSchedule::PeriodicSchedule(void)
: TreatmentInterval_(1),
  NumberOfTreatments_(1)
{
  ScheduleType_ = ScheduleTypes::Periodic;
}



PeriodicSchedule::PeriodicSchedule( DateTime minDate, DateTime maxDate )
: Schedule(minDate, maxDate),
  TreatmentInterval_(1),
  NumberOfTreatments_(1)
{
  ScheduleType_ = ScheduleTypes::Periodic;
}



PeriodicSchedule::PeriodicSchedule( const PeriodicSchedule ^ ps )
: Schedule( ps )
{
  this->TreatmentInterval_ = ps->TreatmentInterval_;
  this->NumberOfTreatments_ = ps->NumberOfTreatments_;
}



PeriodicSchedule::~PeriodicSchedule(void) {}
  


input::Schedule *
PeriodicSchedule::GetSimObject(void)
{
  input::PeriodicSchedule * ps = new input::PeriodicSchedule();

  ps->SetStartDate( ToBoostDate(this->StartDate_) );
  ps->UseStopDate( this->UseStopDate_ );
  ps->SetStopDate( ToBoostDate(this->StopDate_) );

  ps->SetTreatmentInterval( this->TreatmentInterval_ );
  ps->SetNumberOfTreatments( this->NumberOfTreatments_ );

  return ps;
}



void
PeriodicSchedule::InitializeSchedule(void)
{
  //if( UseStopDate_ != true ) {
  //  // recall that StartDate will be date of the first treatment,
  //  // leaving (NumberOfTreatments - 1) treatments remaining
  //  StopDate_ = StartDate_ + date_duration( (NumberOfTreatments_ - 1) * TreatmentInterval_ );
  //}

  //day_iterator itDays( StartDate_, TreatmentInterval_ );
  //for( ; itDays <= StopDate_; ++itDays ) {
  //  ScheduledDates_.push_back(*itDays);
  //}
}



System::String ^
PeriodicSchedule::ToString(void)
{ 
  System::Text::StringBuilder ^ sb = gcnew System::Text::StringBuilder();
  sb->AppendLine( "Periodic Schedule");
  sb->AppendFormat( "  MinDate = {0}\n  MaxDate = {1}\n  StartDate = {2}\n  StopDate = {3}\n  UseStopDate = {4}\n  TreatmentInterval = {5}\n  NumberOfTreatments = {6}",
                    MinDate_, MaxDate_, StartDate_, StopDate_, UseStopDate_, TreatmentInterval_, NumberOfTreatments_ );
  sb->AppendLine();
  return sb->ToString();
}
