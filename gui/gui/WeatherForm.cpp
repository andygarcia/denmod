#include "StdAfx.h"
#include "WeatherForm.h"

using namespace gui;



WeatherForm::WeatherForm( BindingSource ^ locationBinding, WeatherYear ^ weatherYear )
: LocationBinding_(locationBinding),
  WeatherYear_(weatherYear)
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
  errPro->DataSource = WeatherYear_;

  tboxYear->DataBindings->Add( "Text", WeatherYear_, "Index" );
  tboxCity->DataBindings->Add( "Text", WeatherYear_, "City" );
  tboxProvince->DataBindings->Add( "Text", WeatherYear_, "Province" );
  tboxCountry->DataBindings->Add( "Text", WeatherYear_, "Country" );
  tboxLatitude->DataBindings->Add( "Text", WeatherYear_, "Latitude" );
  tboxLongitude->DataBindings->Add( "Text", WeatherYear_, "Longitude" );
  tboxElevation->DataBindings->Add( "Text", WeatherYear_, "Elevation" );
  tboxSource->DataBindings->Add( "Text", WeatherYear_, "Source" );

  dgvWeather->AutoGenerateColumns = false;
  dgvWeather->DataSource = WeatherYear_->Days;

  // if just imported from excel, neccesary to tag year
  if( WeatherYear_->ImportSource == WeatherYear::ImportSourceEnum::Excel ) {
    WeatherYear_->Index = DateTime::Now.Year;
    tboxYear->SelectAll();
  }
}



System::Void
WeatherForm::OnOk( System::Object ^ sender, System::EventArgs ^ e )
{
  // check all values valid
  using namespace ValidationFramework;

  // validate entire object
  WeatherYear_->PropertyValidationManager->ValidateAllProperties();
  if( !WeatherYear_->IsValid ) {
    String ^ errorMessages = ValidationFramework::ResultFormatter::GetConcatenatedErrorMessages( "\n", WeatherYear_->PropertyValidationManager->ValidatorResultsInError );
    MessageBox::Show( this, errorMessages, "Errors in container description." );
    this->DialogResult = ::DialogResult::None;
    return;
  }

  // if excel sourced and leap year, check for extra day
  if( DateTime::IsLeapYear( WeatherYear_->Index ) ) {
    if( WeatherYear_->Days->Count != 366 ) {
      MessageBox::Show( "Attempting to add leap year, but only 365 days of weather present in Excel data. Spreadsheet must have 366 days of data.",
                        "Error adding weather",
                        MessageBoxButtons::OK, MessageBoxIcon::Error );
      DialogResult = ::DialogResult::None;
    }
  }


  // check if replacing
  WeatherData ^ weather = ((gui::Location^)LocationBinding_->DataSource)->Weather;
  if( weather->IsWeatherYearAvailable( WeatherYear_->Index ) ) {
    ::DialogResult dr = MessageBox::Show( String::Format("Weather for {0} is already available. Replace with this file?", WeatherYear_->Index),
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
