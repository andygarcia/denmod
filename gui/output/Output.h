#pragma once

#include "Enums.h"

using namespace System;



namespace gui {
namespace output {

ref class Output;

public ref class OutputInfoAttribute : public Attribute
{
public:
  OutputInfoAttribute(void)
  {}
  virtual ~OutputInfoAttribute(void)
  {}

public:
  property String ^ Name {
    String ^ get(void) {
      return _name;
    }
    void set(String ^ s) {
      _name = s;
    }
  }

  property String ^ Units {
    String ^ get(void) {
      return _units;
    }
    void set( String ^ s ) {
      _units = s;
    }
  }

private:
  String ^ _name;
  String ^ _units;
};



public ref class OutputInfo
{
private:
public:
  OutputInfo( int id, OutputInfoAttribute ^ OutputInfoAttribute );
  virtual ~OutputInfo(void);

public:
  Output ^ CreateNewOutput(void);

public:
  property int Id {
    int get(void) {
      return _id;
    }
  }

  property gui::output::OutputInfoAttribute ^ OutputInfoAttribute {
    gui::output::OutputInfoAttribute ^ get(void) {
      return _outputInfoAttribute;
    }
  }

private:
  int _id;
  gui::output::OutputInfoAttribute ^ _outputInfoAttribute;
};
typedef Collections::Generic::Dictionary<int,OutputInfo^> OutputInfoCollection;



public ref class Output
{
public:
  Output( OutputInfo ^ oi )
  : _outputInfo(oi),
    _data(gcnew Collections::Generic::List<double>())
  {}
  virtual ~Output(void)
  {}

public:
  Collections::Generic::List<double> ^ GetWeeklyData( TimePeriodFunction function );
  Collections::Generic::List<double> ^ GetMonthlyData( DateTime startDate, DateTime stopDate, TimePeriodFunction function );

public:
  property int Id {
    int get(void) {
      return _outputInfo->Id;
    }
  }

  property String ^ Name {
    String ^ get(void) {
      return _outputInfo->OutputInfoAttribute->Name;
    }
  }
  property String ^ Units {
    String ^ get(void) {
      return _outputInfo->OutputInfoAttribute->Units;
    }
  }

  property gui::output::OutputInfo ^ OutputInfo {
    gui::output::OutputInfo ^ get(void) {
      return _outputInfo;
    }
  }

  property Collections::Generic::List<double> ^ Data {
    Collections::Generic::List<double> ^ get(void) {
      return _data;
    }
  }

private:
  gui::output::OutputInfo ^ _outputInfo;
  Collections::Generic::List<double> ^ _data;
};
typedef Collections::Generic::Dictionary<int,Output^> IndexedOutputCollection;




public ref class OutputCollections abstract sealed
{
public:
  static IndexedOutputCollection ^ CreateNewOutputCollection( System::Type ^ outputType );

private:
  static OutputCollections(void);
  static OutputInfoCollection ^ GetOutputInfoCollection( System::Type ^ type );
  static OutputInfoAttribute ^ GetOutputInfoAttribute( Reflection::FieldInfo ^ fi );

private:
  static OutputInfoCollection ^ _cimsimLocation;
  static OutputInfoCollection ^ _cimsimContainer;
  static OutputInfoCollection ^ _densimLocation;
  static OutputInfoCollection ^ _densimSerotype;
};


public ref class SimOutput
{
public:
  SimOutput( DateTime startDate, DateTime stopDate );
  virtual ~SimOutput(void);

public:
  static String ^ GenerateExcelXml( Collections::Generic::List<DateTime> ^ dates, Collections::Generic::List<Output^> ^ columns );

private:
  void GenerateWeeks(void);
  void GenerateMonths(void);

public:
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

  property Collections::Generic::List<DateTime> ^ Dates {
    Collections::Generic::List<DateTime> ^ get(void) {
      return _dates;
    }
  }

  property Collections::Generic::List<int> ^ Weeks {
    Collections::Generic::List<int> ^ get(void) {
      if( _weeks == nullptr ) {
        GenerateWeeks();
      }
      return _weeks;
    }
  }

  property Collections::Generic::List<DateTime> ^ Months {
    Collections::Generic::List<DateTime> ^ get(void) {
      if( _months == nullptr ) {
        GenerateMonths();
      }
      return _months;
    }
  }

private:
  DateTime _startDate;
  DateTime _stopDate;
  Collections::Generic::List<DateTime> ^ _dates;
  Collections::Generic::List<int> ^ _weeks;
  Collections::Generic::List<DateTime> ^ _months;
};



public ref class CimsimOutput : public SimOutput
{
public:
  CimsimOutput( DateTime startDate, DateTime stopDate );
  virtual ~CimsimOutput(void);

public:
  void AddContainerType( int containerId );

  String ^ GetLocationExcelXml(void);
  String ^ GetContainerExcelXml( int containerId );

public:
  property IndexedOutputCollection ^ Location {
    IndexedOutputCollection ^ get(void) {
      return _location;
    }
  }

  property Collections::Generic::Dictionary<int,IndexedOutputCollection^> ^ Containers {
    Collections::Generic::Dictionary<int,IndexedOutputCollection^> ^ get(void) {
      return _containers;
    }
  }

private:
  IndexedOutputCollection ^ _location;
  Collections::Generic::Dictionary<int,IndexedOutputCollection^> ^ _containers;
};


public ref class DensimOutput : public SimOutput
{
public:
  DensimOutput( DateTime startDate, DateTime stopDate );
  virtual ~DensimOutput(void);

public:
  property IndexedOutputCollection ^ Location {
    IndexedOutputCollection ^ get(void) {
      return _location;
    }
  }

  property Collections::Generic::Dictionary<int,IndexedOutputCollection^> ^ Serotypes {
    Collections::Generic::Dictionary<int,IndexedOutputCollection^> ^ get(void) {
      return _serotypes;
    }
  }

private:
  IndexedOutputCollection ^ _location;
  Collections::Generic::Dictionary<int,IndexedOutputCollection^> ^ _serotypes;
};

};
};
