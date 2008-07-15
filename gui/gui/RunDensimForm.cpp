#include "StdAfx.h"
#include "RunDensimForm.h"

using namespace gui;



RunDensimForm::RunDensimForm(BindingSource ^ locationBinding)
: _locationBinding(locationBinding)
{
	InitializeComponent();

  // load years into combo boxes based on what years of MosData are available
  gui::Location ^ location = (gui::Location^) _locationBinding->DataSource;
  _mosDataStartYear = location->CimsimOutput->StartDate.Year;
  _mosDataStopYear = location->CimsimOutput->StopDate.Year;

  for( int i = _mosDataStartYear; i <= _mosDataStopYear; ++i ) {
    cboxStartYear->Items->Add( i );
    cboxStopYear->Items->Add( i );
  }

  // set intially to start and stop with all available years
  cboxStartYear->SelectedIndex = 0;
  cboxStopYear->SelectedIndex = cboxStopYear->Items->Count - 1;
}



RunDensimForm::~RunDensimForm()
{
  if( components ) {
		delete components;
	}
}



System::Void
RunDensimForm::OnLoad(System::Object ^ sender, System::EventArgs ^ e)
{
}



System::Void
RunDensimForm::OnAllYearsChecked(System::Object ^ sender, System::EventArgs ^ e)
{
  if( radUseAll->Checked ) {
    radUseRange->Checked = false;
    cboxStartYear->Enabled = false;
    cboxStopYear->Enabled = false;
  }
}



System::Void
RunDensimForm::OnRangeYearsChecked(System::Object ^ sender, System::EventArgs ^ e)
{
  if( radUseRange->Checked ) {
    radUseAll->Checked = false;
    cboxStartYear->Enabled = true;
    cboxStopYear->Enabled = true;
  }
}



System::Void
RunDensimForm::OnStartYearChanged(System::Object ^ sender, System::EventArgs ^ e)
{
  int startYear = (int) cboxStartYear->SelectedItem;
  int stopYear = (int) cboxStopYear->SelectedItem;

  if(  stopYear < startYear ) {
    // reset stop year to start year
    cboxStopYear->SelectedItem = startYear;
  }
}



System::Void
RunDensimForm::OnStopYearChanged(System::Object ^ sender, System::EventArgs ^ e)
{
  int stopYear = (int) cboxStopYear->SelectedItem;
  int startYear = (int) cboxStartYear->SelectedItem;

  if(  stopYear < startYear ) {
    // reset stop year to start year
    cboxStopYear->SelectedItem = startYear;
  }
}



System::Void
RunDensimForm::OnRun(System::Object ^ sender, System::EventArgs ^ e)
{
  gui::Location ^ location = (gui::Location^) _locationBinding->DataSource;

  DateTime startDate;
  DateTime stopDate;

  if( radUseAll->Checked ) {
    // use all years mos data is available for
    startDate = DateTime( _mosDataStartYear, 1, 1 );
    stopDate = DateTime( _mosDataStopYear, 12, 31 );
  }
  else {
    // use selected years
    int startYear = (int) cboxStartYear->SelectedItem;
    int stopYear = (int) cboxStopYear->SelectedItem;

    startDate = DateTime( startYear, 1, 1 );
    stopDate = DateTime( stopYear, 12, 31 );
  }

  RunDensimOptions = gcnew gui::Location::RunDensimOptions();
  RunDensimOptions->StartDate = startDate;
  RunDensimOptions->StopDate = stopDate;
}
