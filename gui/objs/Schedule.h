#pragma once

#include "NotifyValidateEditBase.h"

#pragma managed( push, off )
#include "../../simulation/input/Schedule.h"
#pragma managed( pop )


using namespace System::Xml::Serialization;
using namespace System::ComponentModel;
using System::DateTime;
using System::TimeSpan;



namespace gui {


public enum class Months : int {
  January = 1,
  Februrary,
  March,
  April,
  May,
  June,
  July,
  August,
  September,
  October,
  November,
  December
};


ref class SingleSchedule;
ref class WeeklySchedule;
ref class MonthlySchedule;
ref class YearlySchedule;
ref class PeriodicSchedule;


[XmlInclude(SingleSchedule::typeid)]
[XmlInclude(WeeklySchedule::typeid)]
[XmlInclude(MonthlySchedule::typeid)]
[XmlInclude(YearlySchedule::typeid)]
[XmlInclude(PeriodicSchedule::typeid)]
public ref class Schedule abstract : public NotifyValidateEditBase {
public:
  enum class ScheduleTypes { Single = 0, Weekly, Monthly, Yearly, Periodic };

public:
  static System::String ^ GetShortNameFromType( Schedule ^ s );
  static System::Type ^ GetTypeFromShortName( System::String ^ shortName );

public:
  Schedule(void);
  Schedule( DateTime minDate, DateTime maxDate );
  Schedule( const Schedule ^ s );
  virtual ~Schedule(void) {}

  virtual input::Schedule * GetSimObject(void) abstract;
  virtual void InitializeSchedule(void) abstract;

public:
  [XmlElement(Order=0)]
  property DateTime StartDate {
    DateTime get(void) {
      return StartDate_;
    }
    void set( DateTime dt ) {
      if( StartDate_ != dt ) {
        StartDate_ = dt;
        NotifyPropertyChanged( "StartDate" );
      }
    }
  }

  [XmlElement(Order=1)]
  property bool UseStopDate {
    bool get(void) {
      return UseStopDate_;
    }
    void set( bool b ) {
      if( UseStopDate_ != b ) {
        UseStopDate_ = b;
        NotifyPropertyChanged( "UseStopDate" );
      }
    }
  }

  [XmlElement(Order=2)]
  property DateTime StopDate {
    DateTime get(void) {
      return StopDate_;
    }
    void set( DateTime dt ) {
      if( StopDate_ != dt ) {
        StopDate_ = dt;
        NotifyPropertyChanged( "StopDate" );
      }
    }
  }

  [XmlIgnore]
  property Schedule::ScheduleTypes ScheduleType {
    ScheduleTypes get(void) {
      return ScheduleType_;
    }
  }

  [XmlIgnore]
  property int ScheduleTypeIndex {
    int get(void) {
      return (int) ScheduleType_;
    }
  }

  [XmlIgnore]
  property DateTime MinDate {
    DateTime get(void) {
      return MinDate_;
    }
    void set( DateTime dt ) {
      MinDate_ = dt;
      if( StartDate < MinDate_ ) {
        StartDate = MinDate_;
      }
      if( StopDate < MinDate_ ) {
        StopDate = MinDate_;
      }
      NotifyPropertyChanged( "MinDate" );
    }
  }

  [XmlIgnore]
  property DateTime MaxDate {
    DateTime get(void) {
      return MaxDate_;
    }
    void set( DateTime dt ) {
      MaxDate_ = dt;
      if( StartDate > MaxDate_ ) {
        StartDate = MaxDate_;
      }
      if( StopDate > MaxDate_ ) {
        StopDate = MaxDate_;
      }
      NotifyPropertyChanged( "MaxDate" );
    }
  }

protected:
  DateTime StartDate_;
  bool UseStopDate_;
  DateTime StopDate_;
  ScheduleTypes ScheduleType_;

  DateTime MinDate_;
  DateTime MaxDate_;

  Schedule ^ Backup;

  System::Collections::Generic::List<DateTime> ^ ScheduledDates_;
};



public ref class SingleSchedule : Schedule
{
public:
  SingleSchedule(void);
  SingleSchedule( DateTime minDate, DateTime maxDate );
  SingleSchedule( const SingleSchedule ^ ss );
  virtual ~SingleSchedule(void);

  virtual input::Schedule * GetSimObject(void) override;
  virtual void InitializeSchedule(void) override;
  virtual System::String ^ ToString(void) override;

public:
  [XmlIgnore]
  property DateTime Date {
    DateTime get(void) {
      return StartDate_;
    }
    void set( DateTime dt ) {
      if( StartDate_ != dt ) {
        StartDate_ = dt;
        StopDate_ = dt;
        NotifyPropertyChanged( "Date" );
      }
    }
  }
};



public ref class WeeklySchedule : Schedule
{
public:
  WeeklySchedule(void);
  WeeklySchedule( DateTime minDate, DateTime maxDate );
  WeeklySchedule( const WeeklySchedule ^ ws );
  virtual ~WeeklySchedule(void);

  virtual input::Schedule * GetSimObject(void) override;
  virtual void InitializeSchedule(void) override;
  virtual System::String ^ ToString(void) override;

public:
  [XmlElement(Order=0)]
  property int WeekInterval {
    int get(void) {
      return WeekInterval_;
    }
    void set(int i) {
      if( WeekInterval_ != i ) {
        WeekInterval_ = i;
        NotifyPropertyChanged( "WeekInterval" );
      }
    }
  }

  [XmlElement(Order=1)]
  property bool Sunday {
    bool get(void) {
      return Sunday_;
    }
    void set(bool b) {
      if( Sunday_ != b ) {
        Sunday_ = b;
        NotifyPropertyChanged( "Sunday" );
      }
    }
  }

  [XmlElement(Order=2)]
  property bool Monday {
    bool get(void) {
      return Monday_;
    }
    void set(bool b) {
      if( Monday_ != b ) {
        Monday_ = b;
        NotifyPropertyChanged( "Monday" );
      }
    }
  }

  [XmlElement(Order=3)]
  property bool Tuesday {
    bool get(void) {
      return Tuesday_;
    }
    void set(bool b) {
      if( Tuesday_ != b ) {
        Tuesday_ = b;
        NotifyPropertyChanged( "Tuesday" );
      }
    }
  }

  [XmlElement(Order=4)]
  property bool Wednesday {
    bool get(void) {
      return Wednesday_;
    }
    void set(bool b) {
      if( Wednesday_ != b ) {
        Wednesday_ = b;
        NotifyPropertyChanged( "Wednesday" );
      }
    }
  }

  [XmlElement(Order=5)]
  property bool Thursday {
    bool get(void) {
      return Thursday_;
    }
    void set(bool b) {
      if( Thursday_ != b ) {
        Thursday_ = b;
        NotifyPropertyChanged( "Thursday" );
      }
    }
  }

  [XmlElement(Order=6)]
  property bool Friday {
    bool get(void) {
      return Friday_;
    }
    void set(bool b) {
      if( Friday_ != b ) {
        Friday_ = b;
        NotifyPropertyChanged( "Friday" );
      }
    }
  }

  [XmlElement(Order=7)]
  property bool Saturday {
    bool get(void) {
      return Saturday_;
    }
    void set(bool b) {
      if( Saturday_ != b ) {
        Saturday_ = b;
        NotifyPropertyChanged( "Saturday" );
      }
    }
  }

private:
  int WeekInterval_;
  bool Sunday_;
  bool Monday_;
  bool Tuesday_;
  bool Wednesday_;
  bool Thursday_;
  bool Friday_;
  bool Saturday_;
};



public ref class MonthlySchedule: Schedule
{
public:
  MonthlySchedule(void);
  MonthlySchedule( DateTime minDate, DateTime maxDate );
  MonthlySchedule( const MonthlySchedule ^ ms );
  virtual ~MonthlySchedule(void);

  virtual input::Schedule * GetSimObject(void) override;
  virtual void InitializeSchedule(void) override;
  virtual System::String^ ToString(void) override;

public:
  [XmlElement(Order=0)]
  property int StartMonth {
    int get(void) {
      return StartDate_.Month;
    }
    void set( int i ) {
      StartDate_ = DateTime( StartDate_.Year, i, StartDate_.Day );
      NotifyPropertyChanged( "StartMonth" );
    }
  }

  [XmlElement(Order=1)]
  property int StartYear {
    int get(void) {
      return StartDate_.Year;
    }
    void set( int i ) {
      StartDate_ = DateTime( i, StartDate_.Month, StartDate_.Day );
      NotifyPropertyChanged( "StartYear" );
    }
  }

  [XmlElement(Order=2)]
  property int MonthInterval {
    int get(void) {
      return MonthInterval_;
    }
    void set( int i ) {
      MonthInterval_ = i;
      NotifyPropertyChanged( "Month Interval" );
    }
  }
  
  [XmlElement(Order=3)]
  property int DayOfMonth {
    int get(void) {
      return StartDate_.Day;
    }
    void set( int i ) {
      StartDate_ = DateTime( StartDate_.Year, StartDate_.Month, i );
      NotifyPropertyChanged( "DayOfMonth" );
    }
  }

private:
  int MonthInterval_;
};



public ref class YearlySchedule: Schedule
{
public:
  YearlySchedule(void);
  YearlySchedule( DateTime minDate, DateTime maxDate );
  YearlySchedule( const YearlySchedule ^ ys );
  virtual ~YearlySchedule(void);

  virtual input::Schedule * GetSimObject(void) override;
  virtual void InitializeSchedule(void) override;
  virtual System::String^ ToString(void) override;

public:
  [XmlElement(Order=0)]
  property int YearInterval {
    int get(void) {
      return YearInterval_;
    }
    void set(int i) {
      if( YearInterval_ != i ) {
        YearInterval_ = i;
        NotifyPropertyChanged( "YearInterval" );
      }
    }
  }

  [XmlIgnore]
  property int StartYear {
    int get(void) {
      return StartDate_.Year;
    }
    void set( int i ) {
      StartDate_ = DateTime( i, StartDate_.Month, StartDate_.Day );
      NotifyPropertyChanged( "StartYear" );
      NotifyPropertyChanged( "StartDate" );
    }
  }

  [XmlIgnore]
  property int DayOfYear {
    int get(void) {
      return StartDate_.DayOfYear;
    }
    void set( int i ) {
      DateTime newStartDate = DateTime( StartDate_.Year, 1, 1 );
      StartDate_ = newStartDate.AddDays( i-1 );
      NotifyPropertyChanged( "DayOfYear" );
      NotifyPropertyChanged( "StartDate" );
    }
  }

private:
  int YearInterval_;
};



public ref class PeriodicSchedule: Schedule
{
public:
  PeriodicSchedule(void);
  PeriodicSchedule( DateTime minDate, DateTime maxDate );
  PeriodicSchedule( const PeriodicSchedule ^ ps );
  virtual ~PeriodicSchedule(void);

  virtual input::Schedule * GetSimObject(void) override;
  virtual void InitializeSchedule(void) override;
  virtual System::String^ ToString(void) override;

public:
  [XmlElement(Order=0)]
  property int TreatmentInterval {
    int get(void) {
      return TreatmentInterval_;
    }
    void set(int i) {
      if( TreatmentInterval_ != i ) {
        TreatmentInterval_ = i;
        NotifyPropertyChanged( "TreatmentInterval" );
      }
    }
  }

  [XmlElement(Order=1)]
  property int NumberOfTreatments {
    int get(void) {
      return NumberOfTreatments_;
    }
    void set(int i) {
      if( NumberOfTreatments_ != i ) {
        NumberOfTreatments_ = i;
        NotifyPropertyChanged( "NumberOfTreatments" );
      }
    }
  }

  [XmlIgnore]
  property bool UseTreatments {
    bool get(void) {
      return !UseStopDate_;
    }
    void set( bool b ) {
      UseStopDate = !b;
      NotifyPropertyChanged( "UseTreatments" );
    }
  }


private:
  int TreatmentInterval_;
  int NumberOfTreatments_;
};

};
