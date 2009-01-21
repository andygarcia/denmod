#pragma once

#include "Enums.h"

using namespace System;
using namespace System::Collections::Generic;



namespace gui {
namespace output {


public interface class IOutput
{
public:
  property String ^ Name;
  property Collections::IList ^ Data;

};


generic<class T>
public ref class Output : public IOutput
{
public:
  Output( String ^ name, array<T> ^ data )
  : _name(name),
    _data(gcnew List<T>())
  {
    for each( T t in data ) {
      _data->Add( t );
    }
  }

public:
  property String ^ Name {
    virtual String ^ get(void) {
      return _name;
    }
    virtual void set(String ^ s) {
      _name = s;
    }
  }

  property Collections::IList ^ Data {
    virtual Collections::IList ^ get(void) {
      return _data;
    }
    virtual void set(Collections::IList ^ il) {
      throw gcnew InvalidOperationException( "not implemented" );
    }
  }

protected:
  String ^ _name;
  List<T> ^ _data;
};
typedef Collections::Generic::List<IOutput^> OutputCollection;



public ref class DatedOutput : public Output<double>
{
public:
  DatedOutput( String ^ name, DateTime startDate, DateTime stopDate, array<double> ^ data )
  : Output(name,data),
    _startDate(startDate),
    _stopDate(stopDate)
  {}

public:
  List<double> ^ GetWeeklyData( TimePeriodFunction function );
  List<double> ^ GetMonthlyData( DateTime startDate, DateTime stopDate, TimePeriodFunction function );

private:
  DateTime _startDate;
  DateTime _stopDate;
};



generic<class T>
public ref class ClassOutput : public Output<T>
{
public:
  ClassOutput( String ^ name, array<T> ^ data )
  : Output( name, data )
  {}
  virtual ~ClassOutput(void) {}
};



ref class CimsimOutput;
ref class DensimOutput;

public ref class SimOutput abstract
{
public:
  SimOutput( String ^ name, DateTime startDate, DateTime stopDate );
  virtual ~SimOutput(void);

public:
  virtual void SaveToDisk( IO::DirectoryInfo ^ di ) abstract;
  static String ^ GenerateExcelDateXml( List<String^> ^ headers, List<DateTime> ^ dates, List<array<double>^> ^ columns );

  generic<class T>
  static String ^ GenerateExcelClassXml( List<String^> ^ headers, List<String^> ^ indices, List<array<T>^> ^ columns );

private:
  void GenerateWeeks(void);
  void GenerateMonths(void);

public:
  property String ^ Name {
    String ^ get(void) {
      return _name;
    }
  }

  property DateTime StartDate {
    DateTime get(void) {
      return _startDate;
    }
  }

  property DateTime StopDate {
    DateTime get(void) {
      return _stopDate;
    }
  }

  property List<DateTime> ^ Dates {
    List<DateTime> ^ get(void) {
      return _dates;
    }
  }

  property List<DateTime> ^ Weeks {
    List<DateTime> ^ get(void) {
      if( _weeks == nullptr ) {
        GenerateWeeks();
      }
      return _weeks;
    }
  }

  property List<DateTime> ^ Months {
    List<DateTime> ^ get(void) {
      if( _months == nullptr ) {
        GenerateMonths();
      }
      return _months;
    }
  }

protected:
  String ^ _name;
  DateTime _startDate;
  DateTime _stopDate;
  List<DateTime> ^ _dates;
  List<DateTime> ^ _weeks;
  List<DateTime> ^ _months;
};

};
};
