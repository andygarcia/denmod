#pragma once

#include "Outputs.h"

using namespace System;



namespace gui {
namespace output {



public ref class Graph
{
public:
  Graph(void);
protected:
  virtual ~Graph(void);

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
  String ^ _title;
  String ^ _graphType;
  String ^ _axisX;
  String ^ _axisY;
  String ^ _secondaryAxisY;
  OutputCollection ^ _primaryOutputs;
  OutputCollection ^ _secondaryOutputs;
  Collections::IEnumerable ^ _axisXData;
};
typedef Collections::Generic::List<Graph^> GraphCollection;

};
};
