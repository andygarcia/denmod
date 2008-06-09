#pragma once

using namespace System;



namespace gui {
namespace output {

public ref class EnumText
{
public:
  EnumText( String ^ displayName, System::Type ^ enumType, System::Object ^ value )
  : _displayName(displayName),
    _enumType(enumType),
    _value(value)

  {}

public:
  static Collections::Generic::List<EnumText^> ^ ConvertEnumForBinding( System::Enum ^ enumeration )
  {
    using ComponentModel::DescriptionAttribute;

    Collections::Generic::List<EnumText^> ^ enumTexts = gcnew Collections::Generic::List<EnumText^>();
    System::Type ^ enumType = enumeration->GetType();

    array<Reflection::FieldInfo^> ^ fields = enumType->GetFields( Reflection::BindingFlags::Static | Reflection::BindingFlags::GetField | Reflection::BindingFlags::Public );
    for each( Reflection::FieldInfo ^ fi in fields ) {
      array<Object^> ^ das = fi->GetCustomAttributes( DescriptionAttribute::typeid, false );
      if( das->Length == 0 ) {
        throw gcnew Exception( enumType->Name + "." + fi->Name + " is missing a DescriptionAttribute." );
      }
      else if( das->Length > 1 ) {
        throw gcnew Exception( enumType->Name + "." + fi->Name + " has more than one DescriptionAttribute." );
      }
      else {
        String ^ displayName = ((DescriptionAttribute^) das[0])->Description;
        Object ^ enumValue = fi->GetValue(nullptr);
        enumTexts->Add( gcnew EnumText(displayName, enumType, enumValue) );
      }
    }

    enumTexts->Sort( gcnew Comparison<EnumText^>(CompareValues) );

    return enumTexts;
  }

private:
  static int CompareValues( EnumText ^ et1, EnumText ^ et2 )
  {
    return (int) et1->Value - (int) et2->Value;
  }

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
