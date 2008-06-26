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

};
};
