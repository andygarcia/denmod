#pragma once

#include "Output.h"

using namespace System;



namespace gui {
namespace output {

public ref class GraphTitlesAttribute : public Attribute
{
public:
  GraphTitlesAttribute(void)
    : _title(""),
      _chartType("Line"),
      _axisX(""),
      _axisY(""),
      _secondaryAxisY("")
  {}
protected:
  virtual ~GraphTitlesAttribute(void)
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
  GraphInfo( output::GraphTitlesAttribute ^ graphTitlesAttribute )
  : _graphTitlesAttribute(graphTitlesAttribute)
  {}

public:
  Graph ^ CreateGraph( CimsimOutput ^ cimsimOutput );
  Graph ^ CreateGraph( CimsimOutput ^ cimsimOutput, int containerId );
  Graph ^ CreateGraph( DensimOutput ^ densimOutput );
  Graph ^ CreateGraph( DensimOutput ^ densimOutput, int seroType );

public:
  property String ^ Title {
    String ^ get(void) {
      return _graphTitlesAttribute->Title;
    }
  }

  property output::GraphTitlesAttribute ^ GraphTitlesAttribute {
    output::GraphTitlesAttribute ^ get(void) {
      return _graphTitlesAttribute;
    }
  }

private:
  output::GraphTitlesAttribute ^ _graphTitlesAttribute;
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
      return _graphInfo->GraphTitlesAttribute->Title;
    }
  }

  property String ^ ChartType {
    String ^ get(void) {
      return _graphInfo->GraphTitlesAttribute->ChartType;
    }
  }

  property String ^ AxisX {
    String ^ get(void) {
      return _graphInfo->GraphTitlesAttribute->AxisX;
    }
  }

  property String ^ AxisY {
    String ^ get(void) {
      return _graphInfo->GraphTitlesAttribute->AxisY;
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



typedef array<OutputInfo^> GraphType;
public ref class GraphInfos abstract sealed
{
public:
  static ComponentModel::BindingList<GraphInfo^> ^ GetGraphInfoBindingList( Group graphGroup );

private:
  static GraphInfos(void);
  static GraphInfoCollection ^ GetGraphInfoCollection( System::Type ^ type );
  generic<typename T> static T GetCustomAttribute( Reflection::FieldInfo ^ fi, bool mustExist );

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
    [GraphTitlesAttribute(Title="Females per Hectare", AxisX="Date", AxisY="# of females per ha", ChartType="Line")]
    static GraphType ^ Females = gcnew GraphType { OutputInfos::CimsimLocation::TotalFemales };

    [GraphTitlesAttribute(Title="Average Female Wet Weight", AxisX="Date", AxisY="Wet Weight (mg)", ChartType="Line")]
    static GraphType ^ AverageFemaleWetWeight = gcnew GraphType { OutputInfos::CimsimLocation::AverageFemaleWeight };

    [GraphTitlesAttribute(Title="Oviposition", AxisX="Date", AxisY="# of eggs", ChartType="Line")]
    static GraphType ^ Oviposition = gcnew GraphType { OutputInfos::CimsimLocation::Oviposition };


    [GraphTitlesAttribute(Title="Weather", AxisX="Date", AxisY="°C / mm / mbars", ChartType="Line")]
    static GraphType ^ Weather = gcnew GraphType{ OutputInfos::CimsimLocation::MinimumTemperature,
                                                  OutputInfos::CimsimLocation::AverageTemperature,
                                                  OutputInfos::CimsimLocation::MaximumTemperature,
                                                  OutputInfos::CimsimLocation::Rainfall,
                                                  OutputInfos::CimsimLocation::RelativeHumidity,
                                                  OutputInfos::CimsimLocation::SaturationDeficit };
  };



  ref class CimsimContainer
  {
  public:
    //[GraphPrimaryOutputAttribute( gcnew array<int> {(int)OutputTypes::Cimsim::Container::UntreatedDensity,
    //                                                (int)OutputTypes::Cimsim::Container::TreatedDensity,
    //                                                (int)OutputTypes::Cimsim::Container::ExcludedDensity} )]
    //[GraphTitlesAttribute(Title="Container Densities", AxisX="Date", AxisY="# of containers per ha", ChartType="Line")]
    //ContainerDensity = Location::Oviposition + 1,

    //[GraphPrimaryOutputAttribute((int)OutputTypes::Cimsim::Container::Depth)]
    //[GraphTitlesAttribute(Title="Water Depth", AxisX="Date", AxisY="cm", ChartType="Line")]
    //Depth,

    //[GraphPrimaryOutputAttribute((int)OutputTypes::Cimsim::Container::Food)]
    //[GraphTitlesAttribute(Title="Food", AxisX="Date", AxisY="mg", ChartType="Line")]
    //Food,

    //[GraphPrimaryOutputAttribute( gcnew array<int> {(int)OutputTypes::Cimsim::Container::MaximumTemperature,
    //                                                (int)OutputTypes::Cimsim::Container::MinimumTemperature} )]
    //[GraphTitlesAttribute(Title="Water Temperature", AxisX="Date", AxisY="°C", ChartType="Line")]
    //WaterTemperature,

    //[GraphPrimaryOutputAttribute((int)OutputTypes::Cimsim::Container::Eggs)]
    //[GraphTitlesAttribute(Title="Eggs", AxisX="Date", AxisY="# of eggs", ChartType="Line")]
    //Eggs,

    //[GraphPrimaryOutputAttribute((int)OutputTypes::Cimsim::Container::Larvae)]
    //[GraphTitlesAttribute(Title="Larvae", AxisX="Date", AxisY="# of larvae", ChartType="Line")]
    //Larvae,

    //[GraphPrimaryOutputAttribute((int)OutputTypes::Cimsim::Container::Pupae)]
    //[GraphTitlesAttribute(Title="Pupae", AxisX="Date", AxisY="# of pupae", ChartType="Line")]
    //Pupae,

    //[GraphPrimaryOutputAttribute((int)OutputTypes::Cimsim::Container::AveragePupalWeight)]
    //[GraphTitlesAttribute(Title="Average Pupal Weight", AxisX="Date", AxisY="mg", ChartType="Line")]
    //AveragePupalWeight,
    //
    //[GraphPrimaryOutputAttribute((int)OutputTypes::Cimsim::Container::NewFemales)]
    //[GraphTitlesAttribute(Title="New Females", AxisX="Date", AxisY="# of new females", ChartType="Line")]
    //NewFemales,
    //
    //[GraphPrimaryOutputAttribute((int)OutputTypes::Cimsim::Container::CumulativeFemales)]
    //[GraphTitlesAttribute(Title="Cumulative Females", AxisX="Date", AxisY="# of cumulative females", ChartType="Line")]
    //CumulativeFemales,
    //
    //[GraphPrimaryOutputAttribute((int)OutputTypes::Cimsim::Container::Oviposition)]
    //[GraphTitlesAttribute(Title="Oviposition", AxisX="Date", AxisY="# of eggs", ChartType="Line")]
    //Oviposition
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
