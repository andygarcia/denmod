#pragma once

#include "Graphs.h"

using namespace System;



namespace gui {
namespace output {



public ref class ChartInfoAttribute
{
public:
  ChartInfoAttribute(void);
  virtual ~ChartInfoAttribute(void);

public:


};


public ref class ChartInfo
{
public:
  ChartInfo( String ^ name, array<GraphInfo^> ^ array<GraphInfo^> );
  virtual ~ChartInfo(void);

public:
  property String ^ Name {
    String ^ get(void) {
      return _name;
    }
  }

  property GraphInfoCollection ^ GraphInfos {
    GraphInfoCollection ^ get(void) {
      return _graphInfos;
    }
  }

private:
  String ^ _name;
  GraphInfoCollection ^ _graphInfos;
};
typedef ComponentModel::BindingList<ChartInfo^> ChartInfoCollection;


public ref class ChartInfos
{
public:
  static ChartInfos(void);

public:
  ChartInfoCollection ^ GetChartInfoCollection( Group outputGroup );

private:
  ChartInfoCollection ^ _cimsimLocation;
  ChartInfoCollection ^ _cimsimContainer;
  ChartInfoCollection ^ _densimLocation;
  ChartInfoCollection ^ _densimSerotype;

public:
  ref class CimsimLocation
  {
  public:
    [ComponentModel::Description("Females")]
    static array<GraphInfo^> ^ Females = gcnew array<GraphInfo^> { GraphInfos::CimsimLocation::Females };

    [ComponentModel::Description("Average Female Wet Weight")]
    static array<GraphInfo^> ^ AverageFemaleWetWeight = gcnew array<GraphInfo^> { GraphInfos::CimsimLocation::AverageFemaleWeight };

    [ComponentModel::Description("Oviposition")]
    static array<GraphInfo^> ^ Oviposition = gcnew array<GraphInfo^> { GraphInfos::CimsimLocation::Oviposition };

    [ComponentModel::Description("Weather")]
    static array<GraphInfo^> ^ Weather = gcnew array<GraphInfo^> { GraphInfos::CimsimLocation::Weather };
  };

  ref class CimsimContainer
  {
  public:
    [ComponentModel::Description("Container Density")]
    static array<GraphInfo^> ^ ContainerDensity = gcnew array<GraphInfo^> { GraphInfos::CimsimContainer::ContainerDensity };

    [ComponentModel::Description("Water Depth")]
    static array<GraphInfo^> ^ Depth = gcnew array<GraphInfo^> { GraphInfos::CimsimContainer::Depth };

    [ComponentModel::Description("Food")]
    static array<GraphInfo^> ^ Food = gcnew array<GraphInfo^> { GraphInfos::CimsimContainer::Food };

    [ComponentModel::Description("Water Temperature")]
    static array<GraphInfo^> ^ WaterTemperature = gcnew array<GraphInfo^> { GraphInfos::CimsimContainer::MaximumTemperature };

    [ComponentModel::Description("All Immatures")]
    static array<GraphInfo^> ^ Immatures = gcnew array<GraphInfo^> { GraphInfos::CimsimContainer::Eggs,
                                                                     GraphInfos::CimsimContainer::Larvae,
                                                                     GraphInfos::CimsimContainer::Pupae };

    [ComponentModel::Description("Eggs")]
    static array<GraphInfo^> ^ Eggs = gcnew array<GraphInfo^> { GraphInfos::CimsimContainer::Eggs };

    [ComponentModel::Description("Larvae")]
    static array<GraphInfo^> ^ Larvae = gcnew array<GraphInfo^> { GraphInfos::CimsimContainer::Larvae };

    [ComponentModel::Description("Pupae")]
    static array<GraphInfo^> ^ Pupae = gcnew array<GraphInfo^> { GraphInfos::CimsimContainer::Pupae };

    [ComponentModel::Description("Average Pupal Weight")]
    static array<GraphInfo^> ^ AveragePupalWeight = gcnew array<GraphInfo^> { GraphInfos::CimsimContainer::AveragePupalWeight };

    [ComponentModel::Description("New Females")]
    static array<GraphInfo^> ^ NewFemales = gcnew array<GraphInfo^> { GraphInfos::CimsimContainer::NewFemales };

    [ComponentModel::Description("Cumulative Females")]
    static array<GraphInfo^> ^ CumulativeFemales = gcnew array<GraphInfo^> { GraphInfos::CimsimContainer::CumulativeFemales };

    [ComponentModel::Description("Oviposition")]
    static array<GraphInfo^> ^ Oviposition = gcnew array<GraphInfo^> { GraphInfos::CimsimContainer::Oviposition };
  };
};

};
};
