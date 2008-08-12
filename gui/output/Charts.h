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
    static CimsimLocation(void);

  public:
    static ChartInfo ^ Females;
    static ChartInfo ^ AverageFemaleWetWeight;
    static ChartInfo ^ Oviposition;
    static ChartInfo ^ Weather;
  };

  ref class CimsimContainer
  {
  public:
    static CimsimContainer(void);

  public:
    static ChartInfo ^ ContainerDensity;
    static ChartInfo ^ Depth;
    static ChartInfo ^ Food;
    static ChartInfo ^ WaterTemperature;
    static ChartInfo ^ Immatures;
    static ChartInfo ^ Eggs;
    static ChartInfo ^ Larvae;
    static ChartInfo ^ Pupae;
    static ChartInfo ^ AveragePupalWeight;
    static ChartInfo ^ NewFemales;
    static ChartInfo ^ CumulativeFemales;
    static ChartInfo ^ Oviposition;
  };

  ref class DensimLocation
  {
  public:
    static DensimLocation(void);
  public:
    static ChartInfo ^ AgeDistribution;
    static ChartInfo ^ SimulationArea;
    static ChartInfo ^ PopulationSize;
    static ChartInfo ^ BirthsAndDeaths;
    static ChartInfo ^ FemaleMosquitoesInArea;
    static ChartInfo ^ FemaleMosquitoesPerPerson;
    static ChartInfo ^ FemaleMosquitoSurvival;
    static ChartInfo ^ FemaleMosquitoWetWeight;
  };

  ref class DensimSerotype
  {
  public:
    static DensimSerotype(void);
  public:
    static ChartInfo ^ EipDevelopmentRate;
    static ChartInfo ^ InfectiveMosquitoes;
    static ChartInfo ^ PersonsIncubating;
    static ChartInfo ^ PersonsViremic;
    static ChartInfo ^ PersonsWithVirus;
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
