#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <vector>
#include "Control.h"



namespace input
{

class Container
{
public:
  enum ShapeType {
    Circle = 0,
    Rectangle
  };

  enum Fill {
    ManualFill = 0,
    RainFill
  };

  enum Frequency {
    Daily = 0,
    Weekly,
    Monthly
  };

public:
  std::string Name_;
  int Id_;
  ShapeType Shape_;
  double Length_;
  double Width_;
  double Height_;
  double Diameter_;
  double MonthlyTurnoverRate_;
  double Density_;
  bool IsCovered_;
  double CoverReduction_;
  double SunExposure_;
  double Cooling_;
  Fill FillMethod_;
  double Drawdown_;
  Frequency DrawdownFrequency_;
  Frequency ManualFillFrequency_;
  double WatershedRatio_;
  double InitFood_;
  double FoodGainJan_;
  double FoodGainFeb_;
  double FoodGainMar_;
  double FoodGainApr_;
  double FoodGainMay_;
  double FoodGainJun_;
  double FoodGainJul_;
  double FoodGainAug_;
  double FoodGainSep_;
  double FoodGainOct_;
  double FoodGainNov_;
  double FoodGainDec_;
  double FoodDecayRate_;
  double InitEggs_;
};

};

#endif
