#pragma once

#include "Plots.h"

using namespace System;



namespace gui {
namespace output {

public enum class ChartIds : int
{
  CimsimMain = 0,
  CimsimFemales,
  CimsimAverageFemaleWetWeight,
  CimsimOviposition,
  CimsimWeather,

  ContainerDensity,
  ContainerDepth,
  ContainerFood,
  ContainerWaterTemperature,
  ContainerImmatures,
  ContainerEggs,
  ContainerLarvae,
  ContainerPupae,
  ContainerAveragePupalWeight,
  ContainerNewFemales,
  ContainerCumulativeFemales,
  ContainerOviposition,
  ContainerDevelopmentRates,

  DensimMain,
  DensimAgeDistributions,
  DensimSimulationArea,
  DensimPopulationSize,
  DensimBirthsAndDeaths,
  DensimFemaleMosquitoesInArea,
  DensimFemaleMosquitoesPerPerson,
  DensimFemaleMosquitoSurvival,
  DensimFemaleMosquitoWetWeight,
  DensimEipDevelopmentRate,
  DensimInfectiveMosquitoes,
  DensimPersonsIncubating,
  DensimPersonsViremic,
  DensimPersonsWithVirus,
  DensimGeneralSeroDistribution,
  DensimDetailedSeroDistribution
};



public ref class ChartInfo
{
public:
  ChartInfo( output::ChartIds chartId, String ^ name, bool periodic )
  : _chartId(chartId),
    _name(name),
    _periodic(periodic)
  {}
  ~ChartInfo(void) {}

public:
  property output::ChartIds ChartId {
    output::ChartIds get(void) {
      return _chartId;
    }
  }

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
  output::ChartIds _chartId;
  String ^ _name;
  bool _periodic;
};



public ref class ChartInfos
{

private:
  static ChartInfos(void)
  {
    _cimsimLocationCharts = gcnew ComponentModel::BindingList<ChartInfo^>();
    _cimsimLocationCharts->Add( gcnew ChartInfo(ChartIds::CimsimFemales, "Females", true) );
    _cimsimLocationCharts->Add( gcnew ChartInfo(ChartIds::CimsimAverageFemaleWetWeight, "Average female wet weight", true) );
    _cimsimLocationCharts->Add( gcnew ChartInfo(ChartIds::CimsimOviposition, "Oviposition", true) );
    _cimsimLocationCharts->Add( gcnew ChartInfo(ChartIds::CimsimWeather, "Weather", true) );

    _cimsimContainerCharts = gcnew ComponentModel::BindingList<ChartInfo^>();
    _cimsimContainerCharts->Add( gcnew ChartInfo(ChartIds::ContainerDensity, "Container densities", true) );
    _cimsimContainerCharts->Add( gcnew ChartInfo(ChartIds::ContainerDepth, "Water depth", true) );
    _cimsimContainerCharts->Add( gcnew ChartInfo(ChartIds::ContainerFood, "Food", true) );
    _cimsimContainerCharts->Add( gcnew ChartInfo(ChartIds::ContainerWaterTemperature, "Water temperature", true) );
    _cimsimContainerCharts->Add( gcnew ChartInfo(ChartIds::ContainerImmatures, "Immature stages", true) );
    _cimsimContainerCharts->Add( gcnew ChartInfo(ChartIds::ContainerEggs, "Eggs", true) );
    _cimsimContainerCharts->Add( gcnew ChartInfo(ChartIds::ContainerLarvae, "Larvae", true) );
    _cimsimContainerCharts->Add( gcnew ChartInfo(ChartIds::ContainerPupae, "Pupae", true) );
    _cimsimContainerCharts->Add( gcnew ChartInfo(ChartIds::ContainerAveragePupalWeight, "Average pupal weight", true) );
    _cimsimContainerCharts->Add( gcnew ChartInfo(ChartIds::ContainerNewFemales, "New females", true) );
    _cimsimContainerCharts->Add( gcnew ChartInfo(ChartIds::ContainerCumulativeFemales, "Cumulative females", true) );
    _cimsimContainerCharts->Add( gcnew ChartInfo(ChartIds::ContainerOviposition, "Oviposition", true) );
    _cimsimContainerCharts->Add( gcnew ChartInfo(ChartIds::ContainerDevelopmentRates, "Development rates", true) );

    _densimCharts = gcnew ComponentModel::BindingList<ChartInfo^>();
    _densimCharts->Add( gcnew ChartInfo(ChartIds::DensimAgeDistributions, "Age distributions", false) );
    _densimCharts->Add( gcnew ChartInfo(ChartIds::DensimSimulationArea, "Simulation area", true) );
    _densimCharts->Add( gcnew ChartInfo(ChartIds::DensimPopulationSize, "Population", true) );
    _densimCharts->Add( gcnew ChartInfo(ChartIds::DensimBirthsAndDeaths, "Births and deaths", false) );
    _densimCharts->Add( gcnew ChartInfo(ChartIds::DensimFemaleMosquitoesInArea, "Female mosquitoes in area", true) );
    _densimCharts->Add( gcnew ChartInfo(ChartIds::DensimFemaleMosquitoesPerPerson, "Female mosquitoes per person", true) );

    _densimVirusCharts = gcnew ComponentModel::BindingList<ChartInfo^>();
    _densimVirusCharts->Add( gcnew ChartInfo(ChartIds::DensimEipDevelopmentRate, "EIP development rate", true) );
    _densimVirusCharts->Add( gcnew ChartInfo(ChartIds::DensimInfectiveMosquitoes, "Infective mosquitoes", true) );
    _densimVirusCharts->Add( gcnew ChartInfo(ChartIds::DensimPersonsIncubating, "Individuals with incubating infection", true) );
    _densimVirusCharts->Add( gcnew ChartInfo(ChartIds::DensimPersonsViremic, "Individual with viremic infection", true) );
    _densimVirusCharts->Add( gcnew ChartInfo(ChartIds::DensimPersonsWithVirus, "All individuals infected", true) );
    _densimVirusCharts->Add( gcnew ChartInfo(ChartIds::DensimGeneralSeroDistribution, "Serology distribution", false) );
  }

public:
  static property ComponentModel::BindingList<ChartInfo^> ^ CimsimLocationCharts {
    ComponentModel::BindingList<ChartInfo^> ^ get(void) {
      return _cimsimLocationCharts;
    }
  }

  static property ComponentModel::BindingList<ChartInfo^> ^ CimsimContainerCharts {
    ComponentModel::BindingList<ChartInfo^> ^ get(void) {
      return _cimsimContainerCharts;
    }
  }

  static property ComponentModel::BindingList<ChartInfo^> ^ DensimCharts {
    ComponentModel::BindingList<ChartInfo^> ^ get(void) {
      return _densimCharts;
    }
  }

  static property ComponentModel::BindingList<ChartInfo^> ^ DensimVirusCharts {
    ComponentModel::BindingList<ChartInfo^> ^ get(void) {
      return _densimVirusCharts;
    }
  }

private:
  static ComponentModel::BindingList<ChartInfo^> ^ _cimsimLocationCharts;
  static ComponentModel::BindingList<ChartInfo^> ^ _cimsimContainerCharts;
  static ComponentModel::BindingList<ChartInfo^> ^ _densimCharts;
  static ComponentModel::BindingList<ChartInfo^> ^ _densimVirusCharts;
};



public ref class Chart
{
public:
  Chart( String ^ name, bool periodic )
  : _name(name),
    _periodic(periodic),
    _plots(gcnew PlotCollection())
  {}

  virtual ~Chart(void)
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

  property PlotCollection ^ Plots {
    PlotCollection ^ get(void) {
      return _plots;
    }
  }

private:
  String ^ _name;
  bool _periodic;
  PlotCollection ^ _plots;
};



};
};
