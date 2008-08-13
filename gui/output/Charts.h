#pragma once

#include "Graphs.h"

using namespace System;



namespace gui {
namespace output {



public ref class ChartInfo
{
public:
  ChartInfo( String ^ name, bool periodic)
  : _graphs(gcnew GraphCollection()),
    _name(name),
    _periodic(periodic)
  {}
  virtual ~ChartInfo(void)
  {}

public:
  property String ^ Name {
    String ^ get(void) {
      return _name;
    }
  }

  property bool Periodic {
    bool get(void) {
      return _periodic;
    }
  }

private:
  String ^ _name;
  bool _periodic;
  GraphCollection ^ _graphs;
};
typedef ComponentModel::BindingList<ChartInfo^> ChartInfoCollection;

public delegate output::ChartInfo ^ CreateChartInfoDelegate(void);



public ref class ChartInfos
{
private:
  static ChartInfos(void);

public:
  static ChartInfoCollection ^ GetChartInfoCollection( Group outputGroup );

private:
  static Collections::Generic::Dictionary<Group,ChartInfoCollection^> ^ _groupToCollection;
  static ChartInfoCollection ^ _cimsimLocation;
  static ChartInfoCollection ^ _cimsimContainer;
  static ChartInfoCollection ^ _densimLocation;
  static ChartInfoCollection ^ _densimSerotype;

public:
  ref class CimsimLocation
  {
  public:
    static ChartInfo ^ Females = gcnew ChartInfo( "Females", true );
    static ChartInfo ^ AverageFemaleWetWeight = gcnew ChartInfo( "Average Female Wet Weight", true );
    static ChartInfo ^ Oviposition = gcnew ChartInfo( "Oviposition", true );
    static ChartInfo ^ Weather = gcnew ChartInfo( "Weather", true );
  };

  ref class CimsimContainer
  {
  public:
    static ChartInfo ^ ContainerDensity = gcnew ChartInfo( "Container Density", true );
    static ChartInfo ^ Depth = gcnew ChartInfo( "Water Depth", true );
    static ChartInfo ^ Food = gcnew ChartInfo( "Food", true );
    static ChartInfo ^ WaterTemperature = gcnew ChartInfo( "Water Temperature", true );
    static ChartInfo ^ Immatures = gcnew ChartInfo( "All immature stages", true );
    static ChartInfo ^ Eggs = gcnew ChartInfo( "Eggs", true );
    static ChartInfo ^ Larvae = gcnew ChartInfo( "Larvae", true );
    static ChartInfo ^ Pupae = gcnew ChartInfo( "Pupae", true );
    static ChartInfo ^ AveragePupalWeight = gcnew ChartInfo( "Average Pupal Weight", true );
    static ChartInfo ^ NewFemales = gcnew ChartInfo( "New Females", true );
    static ChartInfo ^ CumulativeFemales = gcnew ChartInfo( "Cumulative Females", true );
    static ChartInfo ^ Oviposition = gcnew ChartInfo( "Oviposition", true );
  };

  ref class DensimLocation
  {
  public:
    static ChartInfo ^ AgeDistribution = gcnew ChartInfo( "Age Distributions", false );
    static ChartInfo ^ SimulationArea = gcnew ChartInfo( "Simulation Area", true );
    static ChartInfo ^ PopulationSize = gcnew ChartInfo( "Population Size", true );
    static ChartInfo ^ BirthsAndDeaths = gcnew ChartInfo( "Births and Deaths", false );
    static ChartInfo ^ FemaleMosquitoesInArea = gcnew ChartInfo( "Female Mosquitoes In Area", true );
    static ChartInfo ^ FemaleMosquitoesPerPerson = gcnew ChartInfo( "Female Mosquitoes Per Person", true );
    static ChartInfo ^ FemaleMosquitoSurvival = gcnew ChartInfo( "Female Mosquito Survival", true);
    static ChartInfo ^ FemaleMosquitoWetWeight = gcnew ChartInfo( "Female Mosquito Wet Weight", true );
  };

  ref class DensimSerotype
  {
  public:
    static ChartInfo ^ EipDevelopmentRate = gcnew ChartInfo( "EIP Development Rate", true );
    static ChartInfo ^ InfectiveMosquitoes = gcnew ChartInfo( "Infective Mosquitoes", true );
    static ChartInfo ^ PersonsIncubating = gcnew ChartInfo( "Persons Incubating", true );
    static ChartInfo ^ PersonsViremic = gcnew ChartInfo( "Persons Viremic", true );
    static ChartInfo ^ PersonsWithVirus = gcnew ChartInfo( "Persons with Virus", true );
  };
};



public ref class Chart
{
public:
  static Chart ^ Create( ChartInfo ^ chartInfo, CimsimOutput ^ cimsimOutput, DensimOutput ^ densimOutput, Collections::Generic::List<int> ^ indices );

public:
  Chart(void)
  : _graphs(gcnew GraphCollection())
  {}

  virtual ~Chart(void)
  {}

public:
  property String ^ Name {
    String ^ get(void) {
      return _chartInfo->Name;
    }
  }

  property bool Periodic {
    bool get(void) {
      return _chartInfo->Periodic;
    }
  }

  property GraphCollection ^ Graphs {
    GraphCollection ^ get(void) {
      return _graphs;
    }
  }

private:
  ChartInfo ^ _chartInfo;
  GraphCollection ^ _graphs;
};



};
};
