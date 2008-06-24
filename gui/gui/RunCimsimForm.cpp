#include "StdAfx.h"
#include "RunCimsimForm.h"

using namespace gui;



RunCimsimForm::RunCimsimForm(BindingSource ^ locationBinding)
: _locationBinding(locationBinding)
{
	InitializeComponent();

  // initialize combo boxes with year values
  gui::Location ^ location = (gui::Location^) _locationBinding->DataSource;
  int firstYear = location->Weather->MinDate.Year;
  int lastYear = location->Weather->MaxDate.Year;

  for( int i = firstYear; i <= lastYear; ++i ) {
    cboxStartYear->Items->Add( i );
    cboxStopYear->Items->Add( i );
  }

  // set intially to start and stop with all available years
  cboxStartYear->SelectedItem = firstYear;
  cboxStopYear->SelectedItem = lastYear;
}



RunCimsimForm::~RunCimsimForm()
{
  if( components ) {
		delete components;
	}
}



System::Void
RunCimsimForm::OnLoad(System::Object ^ sender, System::EventArgs ^ e)
{
}



System::Void
RunCimsimForm::OnAllYearsChecked(System::Object ^ sender, System::EventArgs ^ e)
{
  if( radUseAll->Checked ) {
    radUseRange->Checked = false;
    cboxStartYear->Enabled = false;
    cboxStopYear->Enabled = false;
  }
}



System::Void
RunCimsimForm::OnRangeYearsChecked(System::Object ^ sender, System::EventArgs ^ e)
{
  if( radUseRange->Checked ) {
    radUseAll->Checked = false;
    cboxStartYear->Enabled = true;
    cboxStopYear->Enabled = true;
  }
}



System::Void
RunCimsimForm::OnStartYearChanged(System::Object ^ sender, System::EventArgs ^ e)
{
  int startYear = (int) cboxStartYear->SelectedItem;
  int stopYear = (int) cboxStopYear->SelectedItem;

  if(  stopYear < startYear ) {
    // reset stop year to start year
    cboxStopYear->SelectedItem = startYear;
  }
}



System::Void
RunCimsimForm::OnStopYearChanged(System::Object ^ sender, System::EventArgs ^ e)
{
  int stopYear = (int) cboxStopYear->SelectedItem;
  int startYear = (int) cboxStartYear->SelectedItem;

  if(  stopYear < startYear ) {
    // reset stop year to start year
    cboxStopYear->SelectedItem = startYear;
  }
}



System::Void
RunCimsimForm::OnRun(System::Object ^ sender, System::EventArgs ^ e)
{
  gui::Location ^ location = (gui::Location^) _locationBinding->DataSource;

  bool usePop = chkUsePop->Checked;

  DateTime startDate;
  DateTime stopDate;
  if( radUseAll->Checked ) {
    // use all weather
    startDate = location->Weather->MinDate;
    stopDate = location->Weather->MaxDate;
  }
  else {
    // use selected years
    int startYear = (int) cboxStartYear->SelectedItem;
    int stopYear = (int) cboxStopYear->SelectedItem;

    startDate = DateTime( startYear, 1, 1 );
    stopDate = DateTime( stopYear, 12, 31 );
  }

  RunCimsimOptions = gcnew gui::Location::RunCimsimOptions();
  RunCimsimOptions->UsePop = usePop;
  RunCimsimOptions->StartDate = startDate;
  RunCimsimOptions->StopDate = stopDate;
}
