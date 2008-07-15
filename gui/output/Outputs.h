#pragma once

#include "Enums.h"

using namespace System;



namespace gui {
namespace output {

ref class Output;



public enum class Group : int
{
  CimsimLocation = 0,
  CimsimContainer,
  DensimLocation,
  DensimSerotype
};



public ref class OutputInfo abstract
{
public:
  OutputInfo( Group outputGroup, String ^ name, String ^ units );
  virtual ~OutputInfo(void);

public:
  property Group OutputGroup {
    Group get(void) {
      return _outputGroup;
    }
  }

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
  Group _outputGroup;
  String ^ _name;
  String ^ _units;
};
typedef Collections::Generic::List<OutputInfo^> OutputInfoCollection;



public ref class DatedOutputInfo : public OutputInfo
{
public:
  DatedOutputInfo( Group outputGroup, String ^ name, String ^ units )
  : OutputInfo(outputGroup, name, units)
  {}
};



public ref class ClassOutputInfo : public OutputInfo
{
public:
  ClassOutputInfo( Group outputGroup, String ^ name, String ^ units )
  : OutputInfo(outputGroup, name, units)
  {}
};


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
typedef Collections::Generic::List<Output^> OutputCollection;
typedef Collections::Generic::Dictionary<OutputInfo^,Output^> OutputMap;



public ref class DatedOutput : public Output
{
public:
  DatedOutput( output::OutputInfo ^ oi, DateTime startDate, DateTime stopDate )
  : Output(oi),
    _startDate(startDate),
    _stopDate(stopDate)
    
  {}

public:
  Collections::Generic::List<double> ^ GetWeeklyData( TimePeriodFunction function );
  Collections::Generic::List<double> ^ GetMonthlyData( DateTime startDate, DateTime stopDate, TimePeriodFunction function );

private:
  DateTime _startDate;
  DateTime _stopDate;
};



public ref class OutputInfos abstract sealed
{
public:
  static OutputMap ^ CreateNewOutputMap( gui::output::Group outputGroup, DateTime startDate, DateTime stopDate );

private:
  static OutputInfos(void);
  static OutputInfoCollection ^ GetOutputInfoCollection( Group outputGroup );

private:
  static Collections::Generic::Dictionary<Group,Type^> ^ _groupToType;
  static Collections::Generic::Dictionary<Group,OutputInfoCollection^> ^ _groupToCollection;

  static OutputInfoCollection ^ _cimsimLocation;
  static OutputInfoCollection ^ _cimsimContainer;
  static OutputInfoCollection ^ _densimLocation;
  static OutputInfoCollection ^ _densimSerotype;

public:
  ref class CimsimLocation
  {
  public:
    static CimsimLocation(void);

  public:
    static DatedOutputInfo ^ TotalEggs;
    static DatedOutputInfo ^ TotalLarvae;
    static DatedOutputInfo ^ TotalPupae;
    static DatedOutputInfo ^ TotalFemales;
    static DatedOutputInfo ^ NewFemales;
    static DatedOutputInfo ^ AverageFemaleWeight;
    static DatedOutputInfo ^ Oviposition;
    static DatedOutputInfo ^ MaximumTemperature;
    static DatedOutputInfo ^ AverageTemperature;
    static DatedOutputInfo ^ MinimumTemperature;
    static DatedOutputInfo ^ Rainfall;
    static DatedOutputInfo ^ RelativeHumidity;
    static DatedOutputInfo ^ SaturationDeficit;
  };

  ref class CimsimContainer
  {
  public:
    static CimsimContainer(void);

  public:
    static DatedOutputInfo ^ Depth;
    static DatedOutputInfo ^ Food;
    static DatedOutputInfo ^ MaximumTemperature;
    static DatedOutputInfo ^ MinimumTemperature;
    static DatedOutputInfo ^ Eggs;
    static DatedOutputInfo ^ Larvae;
    static DatedOutputInfo ^ Pupae;
    static DatedOutputInfo ^ AveragePupalWeight;
    static DatedOutputInfo ^ NewFemales;
    static DatedOutputInfo ^ CumulativeFemales;
    static DatedOutputInfo ^ Oviposition;
    static DatedOutputInfo ^ UntreatedDensity;
    static DatedOutputInfo ^ TreatedDensity;
    static DatedOutputInfo ^ ExcludedDensity;
  };

  ref class DensimLocation
  {
  public:
    static DensimLocation(void);

  public:
    static ClassOutputInfo ^ InitialAgeDistribution;
    static ClassOutputInfo ^ FinalAgeDistribution;
    static DatedOutputInfo ^ SimulationArea;
    static DatedOutputInfo ^ PopulationSize;
    static ClassOutputInfo ^ BirthsByClass;
    static ClassOutputInfo ^ DeathsByClass;
    static ClassOutputInfo ^ BirthPercentagesByClass;
    static ClassOutputInfo ^ DeathPercentagesByClass;
    static DatedOutputInfo ^ FemaleMosquitoesInSimulationArea;
    static DatedOutputInfo ^ FemaleMosquitoesPerHectare;
    static DatedOutputInfo ^ FemaleMosquitoesPerPerson;
    static DatedOutputInfo ^ PotentiallyInfectiveBites;
    static DatedOutputInfo ^ FemaleMosquitoSurvival;
    static DatedOutputInfo ^ FemaleMosquitoWetWeight;

    //GeneralSeroprevalence,
    //DetailedSeroprevalence,

    //NewCases,
    //PredictedHFSS,
    //DeathsHFSS
  };

  ref class DensimSerotype
  {
  public:
    static DensimSerotype(void);

  public:
    static DatedOutputInfo ^ EipDevelopmentRate;
    static DatedOutputInfo ^ InfectiveMosquitoes;
    static DatedOutputInfo ^ PersonsIncubating;
    static DatedOutputInfo ^ PersonsViremic;
    static DatedOutputInfo ^ PersonsWithVirus;
  };
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

protected:
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
  property OutputMap ^ Location {
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
