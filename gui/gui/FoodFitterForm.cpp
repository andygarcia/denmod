#include "StdAfx.h"
#include "FoodFitterForm.h"

using namespace gui;



FoodFitterForm::FoodFitterForm( gui::Location ^ location )
: Location_(location),
  ContainerBinding_(gcnew BindingSource())
{
	InitializeComponent();

  Location_->BeginFoodFit();
  ContainerBinding_->DataSource = Location_->Containers;
}



FoodFitterForm::~FoodFitterForm()
{
	if( components )	{
		delete components;
	}
}



System::Void
FoodFitterForm::OnLoad( System::Object^ sender, System::EventArgs^ e )
{
  dgvFit->AutoGenerateColumns = false;
  dgvFit->DataSource = ContainerBinding_;
  dgvFit->CurrentCell = dgvFit->Rows[0]->Cells[2];

  DateTime wxMinDate = Location_->Weather->MinDate;
  DateTime wxMaxDate = Location_->Weather->MaxDate;

  dateTimeSurveyStart->MinDate = wxMinDate;
  dateTimeSurveyStart->MaxDate = wxMaxDate;
  try {
    dateTimeSurveyStart->DataBindings->Add( "Value", Location_, "SurveyStartDate" );
  }
  catch( ArgumentOutOfRangeException ^ e ) {
    // probably first time food fitter run at this location, data binding is pulled the default value from location
    // reset DateTimePicker to minimum
    delete e;
    dateTimeSurveyStart->Value = dateTimeSurveyStart->MinDate;
  }
  
  dateTimeSurveyStop->MinDate = wxMinDate;
  dateTimeSurveyStop->MaxDate = wxMaxDate;
  try {
    dateTimeSurveyStop->DataBindings->Add( "Value", Location_, "SurveyStopDate" );
  }
  catch( ArgumentOutOfRangeException ^ e ) {
    // ditto
    delete e;
    dateTimeSurveyStop->Value = dateTimeSurveyStop->MaxDate;
  }
}



System::Void
FoodFitterForm::OnNextIteration( System::Object^ sender, System::EventArgs^ e )
{
  // check if weather for survey range exists
  DateTime surveyStart = dateTimeSurveyStart->Value;
  DateTime surveyEnd = dateTimeSurveyStop->Value;

  // food fitter requires weather for survey range
  if( (Location_->Weather->IsWeatherYearAvailable(surveyStart.Year) == false)
      || (Location_->Weather->IsWeatherYearAvailable(surveyEnd.Year) == false) ) {
    MessageBox::Show( "Weather for survey range must be available before running food fitter" );
  }

  // run food fit iterations with some number of runs
  this->Cursor->Current = Cursors::WaitCursor;
  Location_->RunFoodFitIteration( Convert::ToInt32(numRuns->Value), surveyStart, surveyEnd );
  this->Cursor->Current = Cursors::Default;

  // tabulate totals
  FoodFitTotals ^ fft = Location_->GetFoodFitTotals();

  snboxTotalObserved->Value = fft->TotalObservedPupaePerHa.ToString();
  snboxTotalPredicted->Value = fft->TotalPredictedPupaePerHa.ToString();
  snboxTotalDifference->Value = fft->Difference.ToString();
  snboxTotalRatio->Value = fft->Ratio.ToString();
}


System::Void
FoodFitterForm::OnSave(System::Object ^ sender, System::EventArgs ^ e)
{
  Location_->EndFoodFit( true );
}



System::Void
FoodFitterForm::OnCancel(System::Object ^ sender, System::EventArgs ^ e)
{
  Location_->EndFoodFit( false );
}
