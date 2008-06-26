#include"StdAfx.h"
#include "Enums.h"

using namespace gui::output;


generic<typename T> where T : ref class
T
gui::output::GetCustomAttribute( Reflection::FieldInfo ^ fi, bool mustExist )
{
  array<Object^> ^ attributes = fi->GetCustomAttributes( T::typeid, false );
  int numAttributes = attributes->Length;

  if( mustExist && numAttributes == 0 ) {
    throw gcnew Exception( "No custom attribute of type " + T::typeid + " was found on " + fi->Name );
  }
  else if( numAttributes == 1 ) {
    T t = (T) attributes[0];
    return t;
  }
  else if( mustExist ) {
    throw gcnew Exception( "More than one custom attribute of type " + T::typeid + " found on " + fi->Name );
  }
  else {
    return T();
  }
}



int CompareValues( EnumText ^ et1, EnumText ^ et2 )
{
  return (int) et1->Value - (int) et2->Value;
}



Collections::Generic::List<EnumText^> ^
EnumText::ConvertEnumForBinding( System::Enum ^ enumeration )
{
  using ComponentModel::DescriptionAttribute;

  Collections::Generic::List<EnumText^> ^ enumTexts = gcnew Collections::Generic::List<EnumText^>();
  System::Type ^ enumType = enumeration->GetType();

  array<Reflection::FieldInfo^> ^ fields = enumType->GetFields( Reflection::BindingFlags::Static | Reflection::BindingFlags::GetField | Reflection::BindingFlags::Public );
  for each( Reflection::FieldInfo ^ fi in fields ) {
    String ^ displayName = GetCustomAttribute<DescriptionAttribute^>( fi, true )->Description;
    Object ^ enumValue = fi->GetValue(nullptr);
    enumTexts->Add( gcnew EnumText(displayName, enumType, enumValue) );
  }

  enumTexts->Sort( gcnew Comparison<EnumText^>(CompareValues) );

  return enumTexts;
}
