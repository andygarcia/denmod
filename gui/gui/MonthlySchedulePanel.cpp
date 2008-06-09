#include "StdAfx.h"
#include "MonthlySchedulePanel.h"

using namespace gui;



MonthlySchedulePanel::MonthlySchedulePanel( gui::MonthlySchedule ^ ms, BindingSource ^ locationBinding )
: LocationBinding(locationBinding),
  ActiveLocation((gui::Location^)locationBinding->DataSource)
{
  Schedule_ = ms;
	InitializeComponent();

  // add months and days to respective combo boxes
  for( int i = 1; i <= 28; ++i ) {
    cboxMonthlyDay->Items->Add( i );
  }
  cboxMonthlyStartMonth->DataSource = System::Enum::GetValues( gui::Months::typeid );
}



MonthlySchedulePanel::~MonthlySchedulePanel()
{
  if( components ) {
		delete components;
	}
}


System::Void
MonthlySchedulePanel::OnLoad( System::Object ^ sender, System::EventArgs ^ e)
{
  cboxMonthlyStartMonth->DataBindings->Add( "SelectedItem", Schedule_, "StartMonth" );

  cboxMonthlyStartYear->ValueMember = "Index";
  cboxMonthlyStartYear->DisplayMember = "Index";
  cboxMonthlyStartYear->DataBindings->Add( "DataSource", LocationBinding, "Weather.YearsBindingList" );

  cboxMonthlyStartYear->DataBindings->Add( "SelectedValue", Schedule_, "StartYear" );

  numMonthlyInterval->DataBindings->Add( "Text", Schedule_, "MonthInterval" );

  cboxMonthlyDay->DataBindings->Add( "SelectedItem", Schedule_, "DayOfMonth" );

  checkMonthlyEnd->DataBindings->Add( "Checked", Schedule_, "UseStopDate", false, DataSourceUpdateMode::OnPropertyChanged );
  dateTimeMonthlyEnd->DataBindings->Add( "MinDate", LocationBinding, "Weather.MinDate" );
  dateTimeMonthlyEnd->DataBindings->Add( "MaxDate", LocationBinding, "Weather.MaxDate" );
  dateTimeMonthlyEnd->DataBindings->Add( "Enabled", Schedule_, "UseStopDate" );
  dateTimeMonthlyEnd->DataBindings->Add( "Value", Schedule_, "StopDate" );
}
