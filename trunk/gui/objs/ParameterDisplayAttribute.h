#pragma once



namespace gui {



public enum class ScientificNotationOptions : int
{
  UseTriggerExponent = 0,
  Never,
  Always
};



public ref class ParameterDisplayAttribute : public System::Attribute
{
#pragma region Constructors
public:
  ParameterDisplayAttribute( int precision, bool showLeadingZero, ScientificNotationOptions scientificNotationOptions )
  : _precision(precision),
    _showLeadingZero(showLeadingZero),
    _scientificNotationOptions(scientificNotationOptions),
    _triggerExponent(8)
  {}

  ParameterDisplayAttribute( int precision, bool showLeadingZero, ScientificNotationOptions scientificNotationOptions, int triggerExponent )
  : _precision(precision),
   _showLeadingZero(showLeadingZero),
   _scientificNotationOptions(scientificNotationOptions),
   _triggerExponent(triggerExponent)
  {}

  virtual ~ParameterDisplayAttribute(void)
  {}
#pragma endregion

#pragma region Properties
public:
  property int Precision {
    int get(void) {
      return _precision;
    }
    void set(int i) {
      if( _precision != i ) {
        _precision = i;
      }
    }
  }

  property bool ShowLeadingZero {
    bool get(void) {
      return _showLeadingZero;
    }
    void set(bool b) {
      if( _showLeadingZero != b ) {
        _showLeadingZero = b;
      }
    }
  }

  property ScientificNotationOptions ScientificNotationOptions {
    gui::ScientificNotationOptions get(void) {
      return _scientificNotationOptions;
    }
    void set(gui::ScientificNotationOptions usno ) {
      if( _scientificNotationOptions != usno ) {
        _scientificNotationOptions = usno;
      }
    }
  }

  property int TriggerExponent {
    int get(void) {
      return _triggerExponent;
    }
    void set(int i ) {
      if( _triggerExponent != i ) {
        _triggerExponent = i;
      }
    }
  }

#pragma endregion

#pragma region Fields
private:
  int _precision;
  bool _showLeadingZero;
  gui::ScientificNotationOptions _scientificNotationOptions;
  int _triggerExponent;
#pragma endregion
};

};
