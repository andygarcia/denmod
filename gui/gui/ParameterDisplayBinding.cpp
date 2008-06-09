#include "StdAfx.h"
#include "ParameterDisplayBinding.h"

using namespace gui;
using namespace System;
using namespace System::Windows;
using namespace System::Windows::Forms;
using namespace System::Reflection;



ParameterDisplayBinding::ParameterDisplayBinding( String ^ propertyName, Object ^ dataSource, String ^ dataMember )
: Binding( propertyName, dataSource, dataMember ),
  _parameterDisplayAttribute(nullptr)
{}



ParameterDisplayBinding::ParameterDisplayBinding( String ^ propertyName, Object ^ dataSource, String ^ dataMember, Forms::DataSourceUpdateMode dataSourceUpdateMode )
: Binding( propertyName, dataSource, dataMember, false, dataSourceUpdateMode ),
  _parameterDisplayAttribute(nullptr)
{}



ParameterDisplayBinding::~ParameterDisplayBinding(void)
{
}



void
ParameterDisplayBinding::OnFormat( System::Windows::Forms::ConvertEventArgs ^ cea )
{
  if( cea->DesiredType != System::String::typeid ) {
    return;
  }

  if( _parameterDisplayAttribute == nullptr ) {
    System::Windows::Forms::BindingManagerBase ^ bmb = this->BindingManagerBase;
    System::Type ^ currentType = bmb->Current->GetType();
    PropertyInfo ^ pi = currentType->GetProperty( this->BindingMemberInfo.BindingField );
    if( pi->IsDefined( gui::ParameterDisplayAttribute::typeid, true ) ) {
      // target property has InputParameter attribute
      array<System::Object^> ^ attribs = pi->GetCustomAttributes( gui::ParameterDisplayAttribute::typeid, true );
      _parameterDisplayAttribute = safe_cast<gui::ParameterDisplayAttribute^>( attribs[0] );

      ctrl::ScientificNotationTextBox ^ sntb = safe_cast<ctrl::ScientificNotationTextBox^>(Control);
    }
  }
  cea->Value = FormatDouble( Convert::ToDouble(cea->Value) );
}



System::String ^
ParameterDisplayBinding::FormatDouble(double d)
{
  // display options
  int precision = _parameterDisplayAttribute->Precision;
  bool showLeadingZero = _parameterDisplayAttribute->ShowLeadingZero;
  gui::ScientificNotationOptions scientificNotationOptions = _parameterDisplayAttribute->ScientificNotationOptions;
  int triggerExponent = _parameterDisplayAttribute->TriggerExponent;

  // first determine format strings
  System::String ^ format;

  // based on use of scientific notation
  if( scientificNotationOptions == gui::ScientificNotationOptions::Always ) {
    // output to scientific notation format

    if( precision != 0 ) {
      format = "0." + gcnew String( '0', precision ) + "E+0";
    }
    else {
      format = "0E+0";
    }
    System::String ^ formattedOutput = Double(d).ToString( format );
    return formattedOutput;
  }
  else if( scientificNotationOptions == gui::ScientificNotationOptions::Never ) {
    // convert using only precision
    format = "#,0." + gcnew String( '0', precision );
  }
  else if( scientificNotationOptions == gui::ScientificNotationOptions::UseTriggerExponent ) {
    // first convert to scientific notation to determine magnitude of exponent
    String ^ sn = Double(d).ToString( "0E+0" );

    // search for exponent sign
    String ^ exponentSigns = "+-";
    int exponentSignIndex = sn->LastIndexOfAny(exponentSigns->ToCharArray());

    // take substring from after sign as exponent
    int valueExponent = Convert::ToInt32(sn->Substring(exponentSignIndex + 1));

    // if larger than trigger, use scientific notation
    if( valueExponent >= triggerExponent ) {
      format = "0." + gcnew String( '0', precision ) + "E+0";
    }
    else {
      format = "#,0." + gcnew System::String( '0', precision );
    }
  }


  System::String ^ formattedOutput = Double(d).ToString( format );

  if( showLeadingZero ) {
    // one weakness with using .NET formatting no options for handle a leading zero
    try {
      // positive numbers
      if( formattedOutput[0] == '.' ) {
        // positive
        formattedOutput = "0" + formattedOutput;
      }
      // negative numbers
      else if( formattedOutput[0] == '-' && formattedOutput[1] == '.' ) {
        formattedOutput = formattedOutput->Insert( 1, "0" );
      }
    }
    catch( Exception ^ ) {
      // number wasn't long enough
    }
  }

  return formattedOutput;
}
