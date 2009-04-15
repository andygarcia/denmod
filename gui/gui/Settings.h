#pragma once


namespace gui {

public ref class Settings : gui::NotifyValidateEditBase
{
public:
  Settings(void);

public:
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

private:
  bool _scaleCimsimMainGraph;
  bool _stochasticAdvancement;
};

};
