#include "StdAfx.h"
#include "WeatherForm.h"

using namespace gui;



WeatherForm::WeatherForm( WeatherFormMode mode, BindingSource ^ locationBinding, WeatherYear ^ weatherYear )
: _mode(mode),
  _locationBinding(locationBinding),
  _weatherYear(weatherYear)
{
	InitializeComponent();
}



WeatherForm::~WeatherForm()
{
	if( components ) {
		delete components;
	}
}



System::Void
WeatherForm::OnLoad( System::Object ^ sender, System::EventArgs ^ e )
{
  errpro->DataSource = _weatherYear;

  tboxYear->DataBindings->Add( "Text", _weatherYear, "Index" );
  tboxCity->DataBindings->Add( "Text", _weatherYear, "City" );
  tboxProvince->DataBindings->Add( "Text", _weatherYear, "Province" );
  tboxCountry->DataBindings->Add( "Text", _weatherYear, "Country" );
  tboxLatitude->DataBindings->Add( "Text", _weatherYear, "Latitude" );
  tboxLongitude->DataBindings->Add( "Text", _weatherYear, "Longitude" );
  tboxElevation->DataBindings->Add( "Text", _weatherYear, "Elevation" );
  tboxSource->DataBindings->Add( "Text", _weatherYear, "Source" );

  dgvWeather->AutoGenerateColumns = false;
  dgvWeather->DataSource = _weatherYear->Days;

  // if just imported from excel, neccesary to tag year
  if( _mode == WeatherFormMode::Import && _weatherYear->ImportSource == WeatherYear::ImportSourceEnum::Excel ) {
    _weatherYear->Index = DateTime::Now.Year;
    tboxYear->SelectAll();
  }

  if( _mode == WeatherFormMode::Edit ) {
    // do not allow changing of year
    tboxYear->Enabled = false;
  }
}



System::Void
WeatherForm::OnOk( System::Object ^ sender, System::EventArgs ^ e )
{
  // check all values valid
  using namespace ValidationFramework;

  // validate entire object
  _weatherYear->PropertyValidationManager->ValidateAllProperties();
  if( !_weatherYear->IsValid ) {
    String ^ errorMessages = ValidationFramework::ResultFormatter::GetConcatenatedErrorMessages( "\n", _weatherYear->PropertyValidationManager->ValidatorResultsInError );
    MessageBox::Show( this, errorMessages, "Errors in weather metadata." );
    this->DialogResult = ::DialogResult::None;
    return;
  }

  if( _mode == WeatherFormMode::Import ) {
    // if excel sourced and leap year, check for extra day
    if( DateTime::IsLeapYear( _weatherYear->Index ) ) {
      if( _weatherYear->Days->Count != 366 ) {
        MessageBox::Show( "Attempting to add leap year, but only 365 days of weather present in Excel data. Spreadsheet must have 366 days of data.",
                          "Error adding weather",
                          MessageBoxButtons::OK, MessageBoxIcon::Error );
        DialogResult = ::DialogResult::None;
      }
    }


    // check if replacing
    WeatherData ^ weather = ((gui::Location^)_locationBinding->DataSource)->Weather;
    if( weather->IsWeatherYearAvailable( _weatherYear->Index ) ) {
      ::DialogResult dr = MessageBox::Show( String::Format("Weather for {0} is already available. Replace with this file?", _weatherYear->Index),
                                            "Weather already exists",
                                            MessageBoxButtons::OKCancel,
                                            MessageBoxIcon::Question,
                                            MessageBoxDefaultButton::Button2 );
      if( dr != ::DialogResult::OK ) {
        DialogResult = ::DialogResult::None;
        return;
      }
    }
  }
}
