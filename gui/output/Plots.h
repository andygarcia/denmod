#pragma once

#include "Outputs.h"

using namespace System;



namespace gui {
namespace output {



public ref class Plot
{
public:
  Plot(void)
  : _primaryOutputs(gcnew OutputCollection()),
    _secondaryOutputs(gcnew OutputCollection()),
    _customYAxis(false)
  {}
protected:
  virtual ~Plot(void)
  {}

public:
  property String ^ Title {
    String ^ get(void) {
      return _title;
    }
    void set(String ^ s) {
      _title = s;
    }
  }

  property String ^ PlotType {
    String ^ get (void) {
      return _plotType;
    }
    void set(String ^ s) {
      _plotType = s;
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

  property bool CustomYAxis {
    bool get(void) {
      return _customYAxis;
    }
  }

  property double MinYAxis {
    double get(void) {
      return _minYAxis;
    }
    void set(double d) {
      _customYAxis = true;
      _minYAxis = d;
    }
  }

  property double MaxYAxis {
    double get(void) {
      return _maxYAxis;
    }
    void set(double d) {
      _customYAxis = true;
      _maxYAxis = d;
    }
  }

private:
  String ^ _title;
  String ^ _plotType;
  String ^ _axisX;
  String ^ _axisY;
  String ^ _secondaryAxisY;
  OutputCollection ^ _primaryOutputs;
  OutputCollection ^ _secondaryOutputs;
  Collections::IEnumerable ^ _axisXData;

  bool _customYAxis;
  double _minYAxis;
  double _maxYAxis;
};
typedef Collections::Generic::List<Plot^> PlotCollection;

};
};
