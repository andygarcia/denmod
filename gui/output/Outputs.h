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



public ref class OutputInfoAttribute : public Attribute
{
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

  //property gui::output::AxisType AxisType {
  //  gui::output::AxisType get(void) {
  //    return _axisType;
  //  }
  //  void set(gui::output::AxisType at) {
  //    _axisType = at;
  //  }
  //}

private:
  String ^ _name;
  String ^ _units;
  //gui::output::AxisType _axisType;
};



public ref class OutputInfo
{
public:
  OutputInfo( OutputInfoAttribute ^ outputInfoAttribute, Group outputGroup );
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

  property Group OutputGroup {
    Group get(void) {
      return _outputGroup;
    }
  }

private:
  String ^ _name;
  String ^ _units;
  Group _outputGroup;
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
  Collections::Generic::List<double> ^ GetWeeklyData( TimePeriodFunction function );
  Collections::Generic::List<double> ^ GetMonthlyData( DateTime startDate, DateTime stopDate, TimePeriodFunction function );

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



public ref class OutputInfos abstract sealed
{
public:
  static OutputMap ^ CreateNewOutputMap( gui::output::Group outputGroup );

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
    [OutputInfoAttribute(Name="Total Eggs",Units="#/ha")]
    static OutputInfo ^ TotalEggs;

    [OutputInfoAttribute(Name="Total Larvae",Units="#/ha")]
    static OutputInfo ^ TotalLarvae;

    [OutputInfoAttribute(Name="Total Pupae",Units="#/ha")]
    static OutputInfo ^ TotalPupae;

    [OutputInfoAttribute(Name="Total Females",Units="#/ha")]
    static OutputInfo ^ TotalFemales;

    [OutputInfoAttribute(Name="New Females",Units="#/ha")]
    static OutputInfo ^ NewFemales;

    [OutputInfoAttribute(Name="Average Female Weight",Units="mg")]
    static OutputInfo ^ AverageFemaleWeight;

    [OutputInfoAttribute(Name="Oviposition",Units="#")]
    static OutputInfo ^ Oviposition;

    [OutputInfoAttribute(Name="Maximum Temperature",Units="C")]
    static OutputInfo ^ MaximumTemperature;

    [OutputInfoAttribute(Name="Average Temperature",Units="C")]
    static OutputInfo ^ AverageTemperature;

    [OutputInfoAttribute(Name="Minimum Temperature",Units="C")]
    static OutputInfo ^ MinimumTemperature;

    [OutputInfoAttribute(Name="Rainfall",Units="mm")]
    static OutputInfo ^ Rainfall;

    [OutputInfoAttribute(Name="Relative Humidity",Units="%")]
    static OutputInfo ^ RelativeHumidity;

    [OutputInfoAttribute(Name="Saturation Deficit",Units="mbars")]
    static OutputInfo ^ SaturationDeficit;
  };

  ref class CimsimContainer
  {
  public:
    [OutputInfoAttribute(Name="Depth",Units="cm")]
    static OutputInfo ^ Depth;

    [OutputInfoAttribute(Name="Food",Units="mg")]
    static OutputInfo ^ Food;

    [OutputInfoAttribute(Name="Maximum Water Temperature",Units="C")]
    static OutputInfo ^ MaximumTemperature;

    [OutputInfoAttribute(Name="Minimum Water Temperature",Units="C")]
    static OutputInfo ^ MinimumTemperature;

    [OutputInfoAttribute(Name="Eggs",Units="#")]
    static OutputInfo ^ Eggs;

    [OutputInfoAttribute(Name="Larvae",Units="#")]
    static OutputInfo ^ Larvae;

    [OutputInfoAttribute(Name="Pupae",Units="#")]
    static OutputInfo ^ Pupae;

    [OutputInfoAttribute(Name="Average Pupal Weight",Units="mg")]
    static OutputInfo ^ AveragePupalWeight;

    [OutputInfoAttribute(Name="New Females",Units="#")]
    static OutputInfo ^ NewFemales;

    [OutputInfoAttribute(Name="Cumulative Females",Units="#")]
    static OutputInfo ^ CumulativeFemales;

    [OutputInfoAttribute(Name="Oviposition",Units="#")]
    static OutputInfo ^ Oviposition;

    [OutputInfoAttribute(Name="Untreated Density",Units="#/ha")]
    static OutputInfo ^ UntreatedDensity;

    [OutputInfoAttribute(Name="Treated Density",Units="#/ha")]
    static OutputInfo ^ TreatedDensity;

    [OutputInfoAttribute(Name="Excluded Density",Units="#/ha")]
    static OutputInfo ^ ExcludedDensity;
  };

  ref class DensimLocation
  {
  public:
    [OutputInfoAttribute(Name="Initial Age Distribution",Units="# of individuals")]
    static OutputInfo ^ InitialAgeDistribution;

    [OutputInfoAttribute(Name="Final Age Distribution",Units="# of individuals")]
    static OutputInfo ^ FinalAgeDistribution;

    [OutputInfoAttribute(Name="Simulation Area",Units="ha")]
    static OutputInfo ^ SimulationArea;

    [OutputInfoAttribute(Name="Population Size",Units="# of individuals")]
    static OutputInfo ^ PopulationSize;

    [OutputInfoAttribute(Name="Births by Class",Units="# births")]
    static OutputInfo ^ BirthsByClass;

    [OutputInfoAttribute(Name="Deaths by Class",Units="# of individuals")]
    static OutputInfo ^ DeathsByClass;
    
    [OutputInfoAttribute(Name="Birth Percentages by Class",Units="# of individuals")]
    static OutputInfo ^ BirthPercentagesByClass;
    
    [OutputInfoAttribute(Name="Death Percentages by Class",Units="# of individuals")]
    static OutputInfo ^ DeathPercentagesByClass;

    [OutputInfoAttribute(Name="Female Mosquitoes in Area",Units="# in area")]
    static OutputInfo ^ FemaleMosquitoesInSimulationArea;

    [OutputInfoAttribute(Name="Female Mosquitoes per Hectare",Units="# / ha")]
    static OutputInfo ^ FemaleMosquitoesPerHectare;

    [OutputInfoAttribute(Name="Female Mosquitoes per Person",Units="# / person")]
    static OutputInfo ^ FemaleMosquitoesPerPerson;

    [OutputInfoAttribute(Name="Female Survival",Units="")]
    static OutputInfo ^ FemaleMosquitoSurvival;

    [OutputInfoAttribute(Name="Female Mosquitoes Wet Weight",Units="mg")]
    static OutputInfo ^ FemaleMosquitoWetWeight;

    //GeneralSeroprevalence,
    //DetailedSeroprevalence,

    //NewCases,
    //PredictedHFSS,
    //DeathsHFSS
  };

  ref class DensimSerotype
  {
  public:
    [OutputInfoAttribute(Name="EIP Development Rate",Units="1/day")]
    static OutputInfo ^ EipDevelopmentRate;

    [OutputInfoAttribute(Name="Infective Mosquitoes",Units="# of infective mosquitoes")]
    static OutputInfo ^ InfectiveMosquitoes;

    [OutputInfoAttribute(Name="Potentially Infective Bites",Units="# of bites")]
    static OutputInfo ^ PotentiallyInfectiveBites;

    [OutputInfoAttribute(Name="Persons Incubating",Units="# of persons incubating")]
    static OutputInfo ^ PersonsIncubating;

    [OutputInfoAttribute(Name="Persons Viremic",Units="# of persons viremic")]
    static OutputInfo ^ PersonsViremic;

    [OutputInfoAttribute(Name="Persons with Virus",Units="# of persons incubating or viremic")]
    static OutputInfo ^ PersonsWithVirus;
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
