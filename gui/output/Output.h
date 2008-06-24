#pragma once

#include "Enums.h"
#include "OutputTypes.h"

using namespace System;



namespace gui {
namespace output {

ref class Output;
ref class CimsimOutput;
ref class DensimOutput;



public ref class OutputInfo
{
public:
  enum class Type : int {
    CimsimLocation = 0,
    CimsimContainer,
    DensimLocation,
    DensimSerotype
  };

public:
  OutputInfo( OutputInfoAttribute ^ outputInfoAttribute );
  OutputInfo( String ^ name, String ^ units );
  virtual ~OutputInfo(void);

public:
  Output ^ CreateOutput(void);

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
typedef Collections::Generic::List<OutputInfo^> OutputInfoCollection;


public ref class Output
{
public:
  Output( OutputInfo ^ oi )
  : _outputInfo(oi),
    _data(gcnew Collections::Generic::List<double>())
  {}

public:
  property String ^ Name {
    String ^ get(void) {
      return _outputInfo->Name;
    }
  }
  property String ^ Units {
    String ^ get(void) {
      return _outputInfo->Units;
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
typedef Collections::Generic::Dictionary<OutputInfo^,Output^> OutputMap;



public ref class DatedOutput : public Output
{
public:
  DatedOutput( gui::output::OutputInfo ^ outputInfo );
public:
  Collections::Generic::List<double> ^ GetWeeklyData( TimePeriodFunction function );
  Collections::Generic::List<double> ^ GetMonthlyData( DateTime startDate, DateTime stopDate, TimePeriodFunction function );
};


public ref class ClassOutput : public Output
{
  ClassOutput( gui::output::OutputInfo ^ outputInfo );
};



public ref class OutputInfos abstract sealed
{
public:
  static OutputMap ^ CreateNewOutputMap( gui::output::Group outputGroup );

private:
  static OutputInfos(void);
  static OutputInfoCollection ^ GetOutputInfoCollection( Type ^ type );
  static OutputInfoAttribute ^ GetOutputInfoAttribute( Reflection::FieldInfo ^ fi );

private:
  static Collections::Generic::Dictionary<Group,OutputInfoCollection^> ^ _groupToCollection;
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
  property OutputMap ^ Location {
    OutputMap ^ get(void) {
      return _location;
    }
  }

  property Collections::Generic::Dictionary<int,OutputMap^> ^ Containers {
    Collections::Generic::Dictionary<int,OutputMap^> ^ get(void) {
      return _containers;
    }
  }

private:
  OutputMap ^ _location;
  Collections::Generic::Dictionary<int,OutputMap^> ^ _containers;
};



public ref class DensimOutput : public SimOutput
{
public:
  DensimOutput( DateTime startDate, DateTime stopDate );
  virtual ~DensimOutput(void);

public:
  property OutputMap ^ OutputMapLocation {
    OutputMap ^ get(void) {
      return _location;
    }
  }

  property Collections::Generic::Dictionary<int,OutputMap^> ^ Serotypes {
    Collections::Generic::Dictionary<int,OutputMap^> ^ get(void) {
      return _serotypes;
    }
  }

private:
  OutputMap ^_location;
  Collections::Generic::Dictionary<int,OutputMap^> ^ _serotypes;
};

};
};
