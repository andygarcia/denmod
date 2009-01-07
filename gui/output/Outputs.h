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
  : _name(oi->Name),
    _units(oi->Units),
    _data(gcnew Collections::Generic::List<double>())
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
  }

  property Collections::Generic::List<double> ^ Data {
    Collections::Generic::List<double> ^ get(void) {
      return _data;
    }
  }

private:
  String ^ _name;
  String ^ _units;
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
    static DatedOutputInfo ^ TotalEggs = gcnew DatedOutputInfo( Group::CimsimLocation, "Total Eggs", "#/ha" );
    static DatedOutputInfo ^ TotalLarvae = gcnew DatedOutputInfo( Group::CimsimLocation, "Total Larvae", "#/ha" );
    static DatedOutputInfo ^ TotalPupae = gcnew DatedOutputInfo( Group::CimsimLocation, "Total Pupae", "#/ha" );
    static DatedOutputInfo ^ TotalFemales = gcnew DatedOutputInfo( Group::CimsimLocation, "Total Females", "#/ha" );
    static DatedOutputInfo ^ NewFemales = gcnew DatedOutputInfo( Group::CimsimLocation, "New Females", "#/ha" );
    static DatedOutputInfo ^ AverageFemaleWeight = gcnew DatedOutputInfo( Group::CimsimLocation, "Average Female Weight", "mg" );
    static DatedOutputInfo ^ Oviposition = gcnew DatedOutputInfo( Group::CimsimLocation, "Oviposition", "#" );
    static DatedOutputInfo ^ MaximumTemperature = gcnew DatedOutputInfo( Group::CimsimLocation, "Maximum Temperature", "C" );
    static DatedOutputInfo ^ AverageTemperature = gcnew DatedOutputInfo( Group::CimsimLocation, "Average Temperature", "C" );
    static DatedOutputInfo ^ MinimumTemperature = gcnew DatedOutputInfo( Group::CimsimLocation, "Minimum Temperature", "C" );
    static DatedOutputInfo ^ Rainfall = gcnew DatedOutputInfo( Group::CimsimLocation, "Rainfall", "mm" );
    static DatedOutputInfo ^ RelativeHumidity = gcnew DatedOutputInfo( Group::CimsimLocation, "Relative Humidity", "%" );
    static DatedOutputInfo ^ SaturationDeficit = gcnew DatedOutputInfo( Group::CimsimLocation, "Saturation Deficit", "mbars" );
  };

  ref class CimsimContainer
  {
  public:
    static DatedOutputInfo ^ Depth = gcnew DatedOutputInfo( Group::CimsimContainer, "Depth", "cm" );
    static DatedOutputInfo ^ Food = gcnew DatedOutputInfo( Group::CimsimContainer, "Food", "mg" );
    static DatedOutputInfo ^ MaximumTemperature = gcnew DatedOutputInfo( Group::CimsimContainer, "Maximum Temperature", "C" );
    static DatedOutputInfo ^ MinimumTemperature = gcnew DatedOutputInfo( Group::CimsimContainer, "Minimum Temperature", "C" );
    static DatedOutputInfo ^ Eggs = gcnew DatedOutputInfo( Group::CimsimContainer, "Eggs", "#" );
    static DatedOutputInfo ^ Larvae = gcnew DatedOutputInfo( Group::CimsimContainer, "Larvae", "#" );
    static DatedOutputInfo ^ Pupae = gcnew DatedOutputInfo( Group::CimsimContainer, "Pupae", "#" );
    static DatedOutputInfo ^ AveragePupalWeight = gcnew DatedOutputInfo( Group::CimsimContainer, "Average Pupal Weight", "mg" );
    static DatedOutputInfo ^ NewFemales = gcnew DatedOutputInfo( Group::CimsimContainer, "New Females", "#" );
    static DatedOutputInfo ^ CumulativeFemales = gcnew DatedOutputInfo( Group::CimsimContainer, "Cumulative Females", "#" );
    static DatedOutputInfo ^ Oviposition = gcnew DatedOutputInfo( Group::CimsimContainer, "Oviposition", "#" );
    static DatedOutputInfo ^ UntreatedDensity = gcnew DatedOutputInfo( Group::CimsimContainer, "Untreated Density", "#/ha" );
    static DatedOutputInfo ^ TreatedDensity = gcnew DatedOutputInfo( Group::CimsimContainer, "Treated Density", "#/ha" );
    static DatedOutputInfo ^ ExcludedDensity = gcnew DatedOutputInfo( Group::CimsimContainer, "Excluded Density", "#/ha" );

    static DatedOutputInfo ^ EggSurvival = gcnew DatedOutputInfo( Group::CimsimContainer, "Egg Survival", "#" );
    static DatedOutputInfo ^ EggTemperatureSurvival = gcnew DatedOutputInfo( Group::CimsimContainer, "Egg Survival vs. Temperature", "#" );
    static DatedOutputInfo ^ EggSatDefSurvival = gcnew DatedOutputInfo( Group::CimsimContainer, "Egg Survival vs. Saturation Deficit", "#" );
    static DatedOutputInfo ^ EggPredationSurvival = gcnew DatedOutputInfo( Group::CimsimContainer, "Egg Survival vs. Predation", "#" );

  };

  ref class DensimLocation
  {
  public:
    static ClassOutputInfo ^ InitialAgeDistribution = gcnew ClassOutputInfo( Group::DensimLocation, "Initial Age Distribution", "# of individuals" );
    static ClassOutputInfo ^ FinalAgeDistribution = gcnew ClassOutputInfo( Group::DensimLocation, "Final Age Distribution", "# of individuals" );
    static ClassOutputInfo ^ BirthsByClass = gcnew ClassOutputInfo( Group::DensimLocation, "Births by Class", "# births" );
    static ClassOutputInfo ^ DeathsByClass = gcnew ClassOutputInfo( Group::DensimLocation, "Deaths by Class", "# of individuals" );
    static ClassOutputInfo ^ BirthPercentagesByClass = gcnew ClassOutputInfo( Group::DensimLocation, "Birth Percentages by Class", "# of individuals" );
    static ClassOutputInfo ^ DeathPercentagesByClass = gcnew ClassOutputInfo( Group::DensimLocation, "Death Percentages by Class", "# of individuals" );

    static DatedOutputInfo ^ SimulationArea = gcnew DatedOutputInfo( Group::DensimLocation, "Simulation Area", "ha" );
    static DatedOutputInfo ^ PopulationSize = gcnew DatedOutputInfo( Group::DensimLocation, "Population Size", "# of individuals" );
    static DatedOutputInfo ^ FemaleMosquitoesInSimulationArea = gcnew DatedOutputInfo( Group::DensimLocation, "Female Mosquitoes in Area", "# in area" );
    static DatedOutputInfo ^ FemaleMosquitoesPerPerson = gcnew DatedOutputInfo( Group::DensimLocation, "Female Mosquitoes per Person", "# / person" );
    static DatedOutputInfo ^ PotentiallyInfectiveBites = gcnew DatedOutputInfo( Group::DensimLocation, "Potentially Infective Bites", "# of bites" );
    static DatedOutputInfo ^ FemaleMosquitoSurvival = gcnew DatedOutputInfo( Group::DensimLocation, "Female Mosquito Survival", "" );
    static DatedOutputInfo ^ FemaleMosquitoWetWeight = gcnew DatedOutputInfo( Group::DensimLocation, "Female Mosquito Wet Weight", "mg" );

    //NewCases,
    //PredictedHFSS,
    //DeathsHFSS
  };

  ref class DensimSerotype
  {
  public:
    static DatedOutputInfo ^ EipDevelopmentRate = gcnew DatedOutputInfo( Group::DensimSerotype, "Eip Development Rate", L"day ⁻¹" ); 
    static DatedOutputInfo ^ InfectiveMosquitoes = gcnew DatedOutputInfo( Group::DensimSerotype, "Infective Mosquitoes", "# of infective mosquitoes" );
    static DatedOutputInfo ^ PersonsIncubating = gcnew DatedOutputInfo( Group::DensimSerotype, "Persons Incubating", "# of persons incubating" );
    static DatedOutputInfo ^ PersonsViremic = gcnew DatedOutputInfo( Group::DensimSerotype, "Persons Viremic", "# of persons viremic" );
    static DatedOutputInfo ^ PersonsWithVirus = gcnew DatedOutputInfo( Group::DensimSerotype, "Persons With Virus", "# of persons incubating or viremic" );
    static ClassOutputInfo ^ InitialSeroprevalence = gcnew ClassOutputInfo( Group::DensimSerotype, "Initial Seroprevalence", "# of individuals seropositive" );
    static ClassOutputInfo ^ FinalSeroprevalence = gcnew ClassOutputInfo( Group::DensimSerotype, "Final Seroprevalence", "# of individuals seropositive" );
  };

  ref class DensimDetailedSeroprevalence
  {
  public:



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
