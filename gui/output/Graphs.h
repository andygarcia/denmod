#pragma once

#include "Outputs.h"

using namespace System;



namespace gui {
namespace output {



typedef array<OutputInfo^> GraphType;


public ref class GraphAttribute : public Attribute
{
public:
  GraphAttribute(void)
    : _title(""),
      _chartType("Line"),
      _axisX(""),
      _axisY(""),
      _secondaryAxisY("")
  {}
protected:
  virtual ~GraphAttribute(void)
  {}

public:
  property String ^ Title {
    String ^ get (void) {
      return _title;
    }
    void set(String ^ s) {
      _title = s;
    }
  }

  property String ^ ChartType {
    String ^ get (void) {
      return _chartType;
    }
    void set(String ^ s) {
      _chartType = s;
    }
  }

  property String ^ AxisX {
    String ^ get (void) {
      return _axisX;
    }
    void set(String ^ s) {
      _axisX = s;
    }
  }

  property String ^ AxisY {
    String ^ get (void) {
      return _axisY;
    }
    void set(String ^ s) {
      _axisY = s;
    }
  }

  property String ^ SecondaryAxisY {
    String ^ get(void) {
      return _secondaryAxisY;
    }
    void set(String ^ s) {
      _secondaryAxisY = s;
    }
  }

private:
  String ^ _title;
  String ^ _chartType;
  String ^ _axisX;
  String ^ _axisY;
  String ^ _secondaryAxisY;
};


ref class Graph;

public ref class GraphInfo
{
public:
  GraphInfo( GraphType ^ graphType, output::GraphAttribute ^ GraphAttribute )
  : _graphType(graphType),
    _graphAttribute(GraphAttribute)
  {}

public:
  Graph ^ CreateGraph( CimsimOutput ^ cimsimOutput, DensimOutput ^ densimOutput );

public:
  property String ^ Title {
    String ^ get(void) {
      return _graphAttribute->Title;
    }
  }

  property output::GraphType ^ GraphType {
    output::GraphType ^ get(void) {
      return _graphType;
    }
  }


  property output::GraphAttribute ^ GraphAttribute {
    output::GraphAttribute ^ get(void) {
      return _graphAttribute;
    }
  }

  property int ContainerId {
    int get(void) {
      return _containerId;
    }
    void set(int i) {
      _containerId = i;
    }
  }

  property int SerotypeId {
    int get(void) {
      return _serotypeId;
    }
    void set(int i) {
      _serotypeId = i;
    }
  }

private:
  output::GraphType ^ _graphType;
  output::GraphAttribute ^ _graphAttribute;
  int _containerId;
  int _serotypeId;
};
typedef Collections::Generic::List<GraphInfo^> GraphInfoCollection;



public ref class Graph
{
public:
  Graph( GraphInfo ^ gi )
  : _graphInfo(gi),
    _primaryOutputs(gcnew Collections::Generic::List<Output^>()),
    _secondaryOutputs(gcnew Collections::Generic::List<Output^>())
  {}

public:

protected:
  virtual ~Graph(void)
  {}

public:
  property String ^ Title {
    String ^ get(void) {
      return _graphInfo->GraphAttribute->Title;
    }
  }

  property String ^ ChartType {
    String ^ get(void) {
      return _graphInfo->GraphAttribute->ChartType;
    }
  }

  property String ^ AxisX {
    String ^ get(void) {
      return _graphInfo->GraphAttribute->AxisX;
    }
  }

  property String ^ AxisY {
    String ^ get(void) {
      return _graphInfo->GraphAttribute->AxisY;
    }
  }

  property Collections::Generic::List<Output^> ^ PrimaryOutputs {
    Collections::Generic::List<Output^> ^ get(void) {
      return _primaryOutputs;
    }
  }

  property Collections::Generic::List<Output^> ^ SecondaryOutputs {
    Collections::Generic::List<Output^> ^ get(void) {
      return _secondaryOutputs;
    }
  }

private:
  GraphInfo ^ _graphInfo;
  Collections::Generic::List<Output^> ^ _primaryOutputs;
  Collections::Generic::List<Output^> ^ _secondaryOutputs;
};



public ref class GraphInfos abstract sealed
{
public:
  static ComponentModel::BindingList<GraphInfo^> ^ GetGraphInfoBindingList( Group graphGroup );

private:
  static GraphInfos(void);
  static GraphInfoCollection ^ GetGraphInfoCollection( System::Type ^ type );

private:
  static Collections::Generic::Dictionary<Group,GraphInfoCollection^> ^ _groupToCollection;
  static GraphInfoCollection ^ _cimsimLocation;
  static GraphInfoCollection ^ _cimsimContainer;
  static GraphInfoCollection ^ _densimLocation;
  static GraphInfoCollection ^ _densimSerotype;

public:
  ref class CimsimLocation
  {
  public:
    [GraphAttribute(Title="Females per Hectare", AxisX="Date", AxisY="# of females per ha", ChartType="Line")]
    static GraphInfo ^ Females;

    //[GraphAttribute(Title="Average Female Wet Weight", AxisX="Date", AxisY="Wet Weight (mg)", ChartType="Line")]
    //static GraphInfo ^ AverageFemaleWetWeight = gcnew GraphInfo { OutputInfos::CimsimLocation::AverageFemaleWeight };

    //[GraphAttribute(Title="Oviposition", AxisX="Date", AxisY="# of eggs", ChartType="Line")]
    //static GraphInfo ^ Oviposition = gcnew GraphInfo { OutputInfos::CimsimLocation::Oviposition };

    //[GraphAttribute(Title="Weather", AxisX="Date", AxisY="°C / mm / mbars", ChartType="Line")]
    //static GraphInfo ^ Weather = gcnew GraphInfo { OutputInfos::CimsimLocation::MinimumTemperature,
    //                                               OutputInfos::CimsimLocation::AverageTemperature,
    //                                               OutputInfos::CimsimLocation::MaximumTemperature,
    //                                               OutputInfos::CimsimLocation::Rainfall,
    //                                               OutputInfos::CimsimLocation::RelativeHumidity,
    //                                               OutputInfos::CimsimLocation::SaturationDeficit };
  };



  ref class CimsimContainer
  {
  public:
    //[GraphAttribute(Title="Container Densities", AxisX="Date", AxisY="# of containers per ha", ChartType="Line")]
    //static GraphInfo ^ ContainerDensity = gcnew GraphInfo { OutputInfos::CimsimContainer::UntreatedDensity,
    //                                                        OutputInfos::CimsimContainer::TreatedDensity,
    //                                                        OutputInfos::CimsimContainer::ExcludedDensity };

    //[GraphAttribute(Title="Water Depth", AxisX="Date", AxisY="cm", ChartType="Line")]
    //static GraphInfo ^ Depth = gcnew GraphInfo { OutputInfos::CimsimContainer::Depth };

    //[GraphAttribute(Title="Food", AxisX="Date", AxisY="mg", ChartType="Line")]
    //static GraphInfo ^ Food = gcnew GraphInfo { OutputInfos::CimsimContainer::Food };

    //[GraphAttribute(Title="Water Temperature", AxisX="Date", AxisY="°C", ChartType="Line")]
    //static GraphInfo ^ WaterTemperature = gcnew GraphInfo { OutputInfos::CimsimContainer::MaximumTemperature,
    //                                                        OutputInfos::CimsimContainer::MinimumTemperature };

    //[GraphAttribute(Title="Eggs", AxisX="Date", AxisY="# of eggs", ChartType="Line")]
    //static GraphInfo ^ Eggs = gcnew GraphInfo { OutputInfos::CimsimContainer::Eggs };

    //[GraphAttribute(Title="Larvae", AxisX="Date", AxisY="# of larvae", ChartType="Line")]
    //static GraphInfo ^ Larvae = gcnew GraphInfo { OutputInfos::CimsimContainer::Larvae };

    //[GraphAttribute(Title="Pupae", AxisX="Date", AxisY="# of pupae", ChartType="Line")]
    //static GraphInfo ^ Pupae = gcnew GraphInfo { OutputInfos::CimsimContainer::Pupae };

    //[GraphAttribute(Title="Average Pupal Weight", AxisX="Date", AxisY="mg", ChartType="Line")]
    //static GraphInfo ^ AveragePupalWeight = gcnew GraphInfo { OutputInfos::CimsimContainer::AveragePupalWeight };
    //
    //[GraphAttribute(Title="New Females", AxisX="Date", AxisY="# of new females", ChartType="Line")]
    //static GraphInfo ^ NewFemales = gcnew GraphInfo { OutputInfos::CimsimContainer::NewFemales };
    //
    //[GraphAttribute(Title="Cumulative Females", AxisX="Date", AxisY="# of cumulative females", ChartType="Line")]
    //static GraphInfo ^ CumulativeFemales = gcnew GraphInfo { OutputInfos::CimsimContainer::CumulativeFemales };
    //
    //[GraphAttribute(Title="Oviposition", AxisX="Date", AxisY="# of eggs", ChartType="Line")]
    //static GraphInfo ^ Oviposition = gcnew GraphInfo { OutputInfos::CimsimContainer::Oviposition };
  };

  ref class DensimLocation
  {
  public:
  };

  ref class DensimSerotype
  {
  public:
  };

};

};
};
