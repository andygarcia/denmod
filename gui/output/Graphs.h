#pragma once

#include "Outputs.h"

using namespace System;



namespace gui {
namespace output {



ref class Graph;

public ref class GraphInfo
{
public:
  GraphInfo(void)
  : _primaryOutputs(gcnew OutputInfoCollection()),
    _secondaryOutputs(gcnew OutputInfoCollection())
  {};
  virtual ~GraphInfo(void)
  {}

public:
  Graph ^ CreateGraph( CimsimOutput ^ cimsimOutput, DensimOutput ^ densimOutput );

public:
  property String ^ Title {
    String ^ get(void) {
      return _title;
    }
    void set(String ^ s) {
      _title = s;
    }
  }

  property String ^ GraphType {
    String ^ get (void) {
      return _graphType;
    }
    void set(String ^ s) {
      _graphType = s;
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

  property OutputInfoCollection ^ PrimaryOutputs {
    OutputInfoCollection ^ get(void) {
      return _primaryOutputs;
    }
  }

  property OutputInfoCollection ^ SecondaryOutputs {
    OutputInfoCollection ^ get(void) {
      return _secondaryOutputs;
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
  String ^ _title;
  String ^ _graphType;
  String ^ _axisX;
  String ^ _axisY;
  String ^ _secondaryAxisY;
  OutputInfoCollection ^ _primaryOutputs;
  OutputInfoCollection ^ _secondaryOutputs;
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
  property output::GraphInfo ^ GraphInfo {
    output::GraphInfo ^ get(void) {
      return _graphInfo;
    }
  }

  property OutputCollection ^ PrimaryOutputs {
    OutputCollection ^ get(void) {
      return _primaryOutputs;
    }
  }

  property OutputCollection ^ SecondaryOutputs {
    OutputCollection ^ get(void) {
      return _secondaryOutputs;
    }
  }

  property Collections::IEnumerable ^ AxisXData {
    Collections::IEnumerable ^ get(void) {
      return _axisXData;
    }
  }

private:
  output::GraphInfo ^ _graphInfo;
  OutputCollection ^ _primaryOutputs;
  OutputCollection ^ _secondaryOutputs;
  Collections::IEnumerable ^ _axisXData;
};



public ref class GraphInfos abstract sealed
{
public:
  static ComponentModel::BindingList<GraphInfo^> ^ GetGraphInfoBindingList( Group graphGroup );

private:
  static GraphInfos(void);

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
    static CimsimLocation(void);
  public:
    static GraphInfo ^ Females;
    static GraphInfo ^ AverageFemaleWetWeight;
    static GraphInfo ^ Oviposition;
    static GraphInfo ^ Weather;
  };

  ref class CimsimContainer
  {
  public:
    static CimsimContainer(void);
  public:
    static GraphInfo ^ ContainerDensity;
    static GraphInfo ^ Depth;
    static GraphInfo ^ Food;
    static GraphInfo ^ WaterTemperature;
    static GraphInfo ^ Eggs;
    static GraphInfo ^ Larvae;
    static GraphInfo ^ Pupae;
    static GraphInfo ^ AveragePupalWeight;
    static GraphInfo ^ NewFemales;
    static GraphInfo ^ CumulativeFemales;
    static GraphInfo ^ Oviposition;
  };

  ref class DensimLocation
  {
  public:
    static DensimLocation(void);

  public:
    static GraphInfo ^ InitialAgeDistribution;
    static GraphInfo ^ FinalAgeDistribution;
    static GraphInfo ^ SimulationArea;
    static GraphInfo ^ PopulationSize;
    static GraphInfo ^ BirthsByClass;
    static GraphInfo ^ DeathsByClass;
    static GraphInfo ^ BirthPercentagesByClass;
    static GraphInfo ^ DeathPercentagesByClass;
    static GraphInfo ^ FemaleMosquitoesInSimulationArea;
    static GraphInfo ^ FemaleMosquitoesPerHectare;
    static GraphInfo ^ FemaleMosquitoesPerPerson;
    static GraphInfo ^ FemaleMosquitoSurvival;
    static GraphInfo ^ FemaleMosquitoWetWeight;

    //static GraphInfo ^ GeneralSeroprevalence,
    //static GraphInfo ^ DetailedSeroprevalence,
    //static GraphInfo ^ NewCases,
    //static GraphInfo ^ PredictedHFSS,
    //static GraphInfo ^ DeathsHFSS
  };

  ref class DensimSerotype
  {
  public:
    static DensimSerotype(void);

  public:
    static GraphInfo ^ EipDevelopmentRate;
    static GraphInfo ^ InfectiveMosquitoes;
    static GraphInfo ^ PersonsIncubating;
    static GraphInfo ^ PersonsViremic;
    static GraphInfo ^ PersonsWithVirus;
  };

};

};
};
