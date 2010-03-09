#pragma once


namespace gui {

public ref class UserSettings : gui::NotifyValidateEditBase
{
public:
  UserSettings(void)
  : _doSimulationDiskOutput(false),
    _scaleCimsimMainGraph(false),
    _stochasticAdvancement(false),
    _establishedPopulationDefault(true)
  {}

public:
  property bool DoSimulationDiskOutput {
    bool get(void) {
      return _doSimulationDiskOutput;
    }
    void set(bool b) {
      if( b != _doSimulationDiskOutput ) {
        _doSimulationDiskOutput = b;
        NotifyPropertyChanged( "DoSimulationDiskOutput" );
      }
    }
  }


  property bool ScaleCimsimMainGraph {
    bool get(void) {
      return _scaleCimsimMainGraph;
    }
    void set(bool b) {
      if( b != _scaleCimsimMainGraph ) {
        _scaleCimsimMainGraph = b;
        NotifyPropertyChanged( "ScaleCimsimMainGraph" );
      }
    }
  }

  property bool StochasticAdvancement {
    bool get(void) {
      return _stochasticAdvancement;
    }
    void set(bool b) {
      if( b != _stochasticAdvancement ) {
        _stochasticAdvancement = b;
        NotifyPropertyChanged( "StochasticAdvancement" );
      }
    }
  }

  property bool EstablishedPopulationDefault {
    bool get(void) {
      return _establishedPopulationDefault;
    }
    void set(bool b) {
      if( b != _establishedPopulationDefault) {
        _establishedPopulationDefault= b;
        NotifyPropertyChanged( "EstablishedPopulationDefault" );
      }
    }
  }

private:
  bool _doSimulationDiskOutput;
  bool _scaleCimsimMainGraph;
  bool _stochasticAdvancement;
  bool _establishedPopulationDefault;
};

};
