#pragma once

using namespace System;



namespace gui {
namespace output {

generic<typename T> where T : ref class T GetCustomAttribute( Reflection::FieldInfo ^ fi, bool mustExist );


public ref class EnumText
{
public:
  EnumText( String ^ displayName, System::Type ^ enumType, System::Object ^ value )
  : _displayName(displayName),
    _enumType(enumType),
    _value(value)

  {}

public:
  static Collections::Generic::List<EnumText^> ^ ConvertEnumForBinding( System::Enum ^ enumeration );

public:
  property String ^ DisplayName {
    String ^ get(void) {
      return _displayName;
    }
  }

  property Object ^ Value {
    Object ^ get(void) {
      return _value;
    }
  }
  
public:
  String ^ _displayName;
  Type ^ _enumType;
  Object ^ _value;
};



public enum class TimePeriod : int
{
  [ComponentModel::Description("Daily")]
  Daily = 0,

  [ComponentModel::Description("Weekly")]
  Weekly,

  [ComponentModel::Description("Monthly")]
  Monthly
};




public enum class TimePeriodFunction : int
{
  [ComponentModel::Description("Average")]
  Average = 0,

  [ComponentModel::Description("Sum")]
  Sum,
};



public enum class SeroClass : int
{
  [ComponentModel::Description("MANA Infants")]
  MANA = 1,

  [ComponentModel::Description("MAEA Infants")]
  MAEA,

  [ComponentModel::Description("< 1 year")]
  LessThanOne,

  [ComponentModel::Description("1-4 years")]
  OneToFour,

  [ComponentModel::Description("5-9 years")]
  FiveToNine,

  [ComponentModel::Description("10-14 years")]
  TenToFourteen,

  [ComponentModel::Description("15-19 years")]
  FifteenToNineteen,

  [ComponentModel::Description("20-24 years")]
  TwentyToTwentyFour,

  [ComponentModel::Description("25-29 years")]
  TwentyFiveToTwentyNine,

  [ComponentModel::Description("30-34 years")]
  ThirtyToThirtyFour,

  [ComponentModel::Description("35-39 years")]
  ThirtyFiveToThirtyNine,

  [ComponentModel::Description("40-44 years")]
  FortyToFortyFour,

  [ComponentModel::Description("45-49 years")]
  FortyFiveToFortyNine,

  [ComponentModel::Description("50-54 years")]
  FiftyToFiftyFour,

  [ComponentModel::Description("55-59 years")]
  FiftyFiveToFiftyNine,

  [ComponentModel::Description("60-64 years")]
  SixtyToSixtyFour,

  [ComponentModel::Description("65-69 years")]
  SixtyFiveToSixtyNine,

  [ComponentModel::Description("70-74 years")]
  SeventyToSeventyFour,

  [ComponentModel::Description("75-79 years")]
  SeventyFiveToSeventyNine,

  [ComponentModel::Description("80+ years")]
  EightyPlus,

  [ComponentModel::Description("15-44 years")]
  FifteenToFortyFour,

  [ComponentModel::Description("45+ years")]
  FortyFivePlus,

  [ComponentModel::Description("All ages")]
  AllAges,
};

};
};
