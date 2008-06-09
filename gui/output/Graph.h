#pragma once

#include "OutputTypes.h"

using namespace System;



namespace gui {
namespace output {

[System::AttributeUsageAttribute(AttributeTargets::Field)]
public ref class GraphPrimaryOutputAttribute : public Attribute
{
public:
  GraphPrimaryOutputAttribute( int outputId )
  {
    // TODO this won't compile if rewritten into the initialization list
    _outputIds = gcnew array<int>{ outputId };
  }
  GraphPrimaryOutputAttribute( array<int> ^ outputIds )
  : _outputIds( gcnew array<int>(outputIds->Length) )
  {
    outputIds->CopyTo( _outputIds, 0 );
  }

protected:
  virtual ~GraphPrimaryOutputAttribute(void)
  {}

public:
  property array<int> ^ OutputIds {
    array<int> ^ get(void) {
      return _outputIds;
    }
  }

private:
  array<int> ^ _outputIds;
};



[System::AttributeUsageAttribute(AttributeTargets::Field)]
public ref class GraphSecondaryOutputAttribute : public Attribute
{
public:
  GraphSecondaryOutputAttribute( int outputId )
  {
    // TODO this won't compile if rewritten into the initialization list
    _outputIds = gcnew array<int>{ outputId };
  }
  GraphSecondaryOutputAttribute( array<int> ^ outputIds )
  : _outputIds( gcnew array<int>(outputIds->Length) )
  {
    outputIds->CopyTo( _outputIds, 0 );
  }

protected:
  virtual ~GraphSecondaryOutputAttribute(void)
  {}

public:
  property array<int> ^ OutputIds {
    array<int> ^ get(void) {
      return _outputIds;
    }
  }

private:
  array<int> ^ _outputIds;
};



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



public ref class GraphTypes abstract sealed
{
public:
  ref class Cimsim abstract sealed
  {
  public:
    enum class Location : int
    {
      [GraphPrimaryOutputAttribute( gcnew array<int> {(int)OutputTypes::Cimsim::Location::NewFemales,
                                                      (int)OutputTypes::Cimsim::Location::TotalFemales} )]
      [GraphTitlesAttribute(Title="Females per Hectare", AxisX="Date", AxisY="# of females per ha", ChartType="Line")]
      Females = 0,

      [GraphPrimaryOutputAttribute((int)OutputTypes::Cimsim::Location::AverageFemaleWeight)]
      [GraphTitlesAttribute(Title="Average Female Wet Weight", AxisX="Date", AxisY="Wet Weight (mg)", ChartType="Line")]
      AverageFemaleWetWeight,

      [GraphPrimaryOutputAttribute((int)OutputTypes::Cimsim::Location::Oviposition)]
      [GraphTitlesAttribute(Title="Oviposition", AxisX="Date", AxisY="# of eggs", ChartType="Line")]
      Oviposition,
    };
    enum class Container : int
    {
      [GraphPrimaryOutputAttribute( gcnew array<int> {(int)OutputTypes::Cimsim::Container::UntreatedDensity,
                                                      (int)OutputTypes::Cimsim::Container::TreatedDensity,
                                                      (int)OutputTypes::Cimsim::Container::ExcludedDensity} )]
      [GraphTitlesAttribute(Title="Container Densities", AxisX="Date", AxisY="# of containers per ha", ChartType="Line")]
      ContainerDensity = Location::Oviposition + 1,

      [GraphPrimaryOutputAttribute((int)OutputTypes::Cimsim::Container::Depth)]
      [GraphTitlesAttribute(Title="Water Depth", AxisX="Date", AxisY="cm", ChartType="Line")]
      Depth,

      [GraphPrimaryOutputAttribute((int)OutputTypes::Cimsim::Container::Food)]
      [GraphTitlesAttribute(Title="Food", AxisX="Date", AxisY="mg", ChartType="Line")]
      Food,

      [GraphPrimaryOutputAttribute( gcnew array<int> {(int)OutputTypes::Cimsim::Container::MaximumTemperature,
                                                      (int)OutputTypes::Cimsim::Container::MinimumTemperature} )]
      [GraphTitlesAttribute(Title="Water Temperature", AxisX="Date", AxisY="°C", ChartType="Line")]
      WaterTemperature,

      [GraphPrimaryOutputAttribute((int)OutputTypes::Cimsim::Container::Eggs)]
      [GraphTitlesAttribute(Title="Eggs", AxisX="Date", AxisY="# of eggs", ChartType="Line")]
      Eggs,

      [GraphPrimaryOutputAttribute((int)OutputTypes::Cimsim::Container::Larvae)]
      [GraphTitlesAttribute(Title="Larvae", AxisX="Date", AxisY="# of larvae", ChartType="Line")]
      Larvae,

      [GraphPrimaryOutputAttribute((int)OutputTypes::Cimsim::Container::Pupae)]
      [GraphTitlesAttribute(Title="Pupae", AxisX="Date", AxisY="# of pupae", ChartType="Line")]
      Pupae,

      [GraphPrimaryOutputAttribute((int)OutputTypes::Cimsim::Container::AveragePupalWeight)]
      [GraphTitlesAttribute(Title="Average Pupal Weight", AxisX="Date", AxisY="mg", ChartType="Line")]
      AveragePupalWeight,
      
      [GraphPrimaryOutputAttribute((int)OutputTypes::Cimsim::Container::NewFemales)]
      [GraphTitlesAttribute(Title="New Females", AxisX="Date", AxisY="# of new females", ChartType="Line")]
      NewFemales,
      
      [GraphPrimaryOutputAttribute((int)OutputTypes::Cimsim::Container::CumulativeFemales)]
      [GraphTitlesAttribute(Title="Cumulative Females", AxisX="Date", AxisY="# of cumulative females", ChartType="Line")]
      CumulativeFemales,
      
      [GraphPrimaryOutputAttribute((int)OutputTypes::Cimsim::Container::Oviposition)]
      [GraphTitlesAttribute(Title="Oviposition", AxisX="Date", AxisY="# of eggs", ChartType="Line")]
      Oviposition
    };
  };

  ref class Densim abstract sealed
  {
  public:
    enum class Location : int
    {
    };
    enum class Serotype : int
    {
    };
  };
};



public ref class GraphInfo
{
public:
  GraphInfo( int id, output::GraphPrimaryOutputAttribute ^ graphPrimaryOutputAttribute, output::GraphSecondaryOutputAttribute ^ graphSecondaryOutputAttribute, output::GraphTitlesAttribute ^ graphTitlesAttribute )
  : _id(id),
    _graphPrimaryOutputAttribute(graphPrimaryOutputAttribute),
    _graphSecondaryOutputAttribute(graphSecondaryOutputAttribute),
    _graphTitlesAttribute(graphTitlesAttribute)
  {}

public:
  property String ^ Title {
    String ^ get(void) {
      return _graphTitlesAttribute->Title;
    }
  }

  property int Id {
    int get(void) {
      return _id;
    }
  }

  property output::GraphPrimaryOutputAttribute ^ GraphPrimaryOutputAttribute {
    output::GraphPrimaryOutputAttribute ^ get(void) {
      return _graphPrimaryOutputAttribute;
    }
  }

  property output::GraphSecondaryOutputAttribute ^ GraphSecondaryOutputAttribute {
    output::GraphSecondaryOutputAttribute ^ get(void) {
      return _graphSecondaryOutputAttribute;
    }
  }

  property output::GraphTitlesAttribute ^ GraphTitlesAttribute {
    output::GraphTitlesAttribute ^ get(void) {
      return _graphTitlesAttribute;
    }
  }

private:
  int _id;
  output::GraphPrimaryOutputAttribute ^ _graphPrimaryOutputAttribute;
  output::GraphSecondaryOutputAttribute ^ _graphSecondaryOutputAttribute;
  output::GraphTitlesAttribute ^ _graphTitlesAttribute;
};
typedef Collections::Generic::Dictionary<int,GraphInfo^> GraphInfoCollection;



public ref class Graph
{
public:
  Graph( GraphInfo ^ gi )
  : _graphInfo(gi),
    _primaryOutputs(gcnew Collections::Generic::List<Output^>()),
    _secondaryOutputs(gcnew Collections::Generic::List<Output^>())
  {}

  static Graph ^ CreateGraph( GraphTypes::Cimsim::Location graphType, CimsimOutput ^ cimsimOutput );
  static Graph ^ CreateGraph( GraphTypes::Cimsim::Container graphType, CimsimOutput ^ cimsimOutput, int containerId );
  //static Graph ^ CreateGraph( GraphTypes::Densim::Location graphType, DensimOutput ^ densimOutput );
  //static Graph ^ CreateGraph( GraphTypes::Densim::Serotype graphType, DensimOutput ^ densimOutput );

protected:
  virtual ~Graph(void)
  {}

public:
  property int Id {
    int get(void) {
      return _graphInfo->Id;
    }
  }

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



public ref class GraphCollections abstract sealed
{
public:
  static ComponentModel::BindingList<GraphInfo^> ^ GetGraphInfoBindingList( System::Type ^ type );

  static GraphInfo ^ GetGraphInfo( GraphTypes::Cimsim::Location graphType );
  static GraphInfo ^ GetGraphInfo( GraphTypes::Cimsim::Container graphType );
  static GraphInfo ^ GetGraphInfo( GraphTypes::Densim::Location graphType );
  static GraphInfo ^ GetGraphInfo( GraphTypes::Densim::Serotype graphType );

private:
  static GraphCollections(void);
  static GraphInfoCollection ^ GetGraphInfoCollection( System::Type ^ type );
  generic<typename T> static T GetCustomAttribute( Reflection::FieldInfo ^ fi, bool mustExist );

private:
  static GraphInfoCollection ^ _cimsimLocation;
  static GraphInfoCollection ^ _cimsimContainer;
  static GraphInfoCollection ^ _densimLocation;
  static GraphInfoCollection ^ _densimSerotype;
};

};
};
