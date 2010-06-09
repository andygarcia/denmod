#include "StdAfx.h"
#include "ScientificNotationTextBox.h"

using namespace ctrl;
using namespace System::Reflection;



ScientificNotationTextBox::ScientificNotationTextBox(void)
{
  InitializeComponent();
  this->Value_ = Text;
}



ScientificNotationTextBox::~ScientificNotationTextBox(void)
{
}



void
ScientificNotationTextBox::OnKeyPress( System::Windows::Forms::KeyPressEventArgs ^ e )
{
  // disallow all input unless valid scientific notation
  e->Handled = true;

  // TODO - need to handle text selection as an "overwrite", right now
  // this only handle the case where all text is highlighted, which
  // occurs when tabbing into the control, now what about the case
  // when part of the text is highlighted?  Needs testing.
  System::String ^ searchText = Text;
  if( SelectedText == Text ) {
    searchText = "";
  }

  // since e->Handled is set to true by default (above), allowed input is followed up by
  // setting e->Handled to false in anticipation of calling parent handler
  //
  // only allow the following as input:

  // numeric digits, but not in front of a minus sign
  if( System::Char::IsDigit(e->KeyChar)  ) {
    int minusIndex = searchText->IndexOf( "-" );
    if( minusIndex == -1 ) {
      e->Handled = false;
    }
    else {                    
      int currentIndex = SelectionStart;
      if( currentIndex > minusIndex ) {
        e->Handled = false;
      }
    }
  }

  // backspaces
  if( e->KeyChar == System::Char(8) ) {
    // allow backspace
    e->Handled = false;
  }

  // one and only one decimal point, and only in the significand
  if( e->KeyChar == '.' && searchText->IndexOf('.') == -1 ) {
    // find possible exponent
    int exponentIndex = searchText->IndexOf( "E", StringComparison::OrdinalIgnoreCase );

    if( exponentIndex == -1 ) {                   // no exponent yet, allow regardless
      e->Handled = false;
    }
    else {                                        // exponent, only allow in significand
      int currentIndex = SelectionStart;
      int sigStartIndex = searchText->IndexOfAny(gcnew array<wchar_t>(10){ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' });

      // check if caret is in significand (between starting index and exponent index)
      if( currentIndex >= sigStartIndex && currentIndex <= exponentIndex ) {
        e->Handled = false;
      }
    }
  }

  // on and only one exponent symbol, regardless of case, but only after at least one digit has been entered
  if( e->KeyChar == 'E' || e->KeyChar == 'e' ) {
    if( searchText->IndexOfAny(gcnew array<wchar_t>(10){ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' }) != -1 ) {
      String ^ symbol = e->KeyChar.ToString();
      if( searchText->IndexOf( symbol, StringComparison::OrdinalIgnoreCase) == -1 ) {
        e->Handled = false;
      }
    }
  }

  // a negative symbol at the beginning of number as well as immediately after exponent symbol
  if( e->KeyChar == '-' ) {
    if( this->SelectionStart == 0 ) {
      e->Handled = false;
    }
    if( searchText->EndsWith("E", System::StringComparison::OrdinalIgnoreCase) ) {
      e->Handled = false;
    }
  }

  // a positive symbol immediately after exponent symbol
  if( e->KeyChar == '+' ) {
    if( searchText->EndsWith("E", System::StringComparison::OrdinalIgnoreCase) ) {
      // allow negative exponent immediately following exponent symbol
      e->Handled = false;
    }
  }

  System::Windows::Forms::TextBox::OnKeyPress(e);
}



void
ScientificNotationTextBox::OnGotFocus( System::EventArgs ^ e )
{
  SelectAll();
}



void
ScientificNotationTextBox::OnLeave( System::EventArgs ^ e )
{
  // check if new text translates to appropriate double value
  try {
    double value = Convert::ToDouble( Text );
    Value = Text;
  }
  catch ( Exception ^ x ) {
    System::Console::WriteLine( x->ToString() );
    return;
  }
}



System::String ^
ScientificNotationTextBox::Value::get(void)
{
  return Value_;
}



void
ScientificNotationTextBox::Value::set(System::String ^ s)
{
  Value_ = s;
  Text = s;
  OnValueChanged();
}
