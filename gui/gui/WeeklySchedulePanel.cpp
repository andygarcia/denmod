#include "StdAfx.h"
#include "WeeklySchedulePanel.h"

using namespace gui;



WeeklySchedulePanel::WeeklySchedulePanel( gui::WeeklySchedule ^ ws, BindingSource ^ locationBinding )
: LocationBinding(locationBinding),
  ActiveLocation((gui::Location^)locationBinding->DataSource)
{
  Schedule_ = ws;
	InitializeComponent();
}



WeeklySchedulePanel::~WeeklySchedulePanel()
{
  if( components ) {
		delete components;
	}
}


System::Void
WeeklySchedulePanel::OnLoad( System::Object ^ sender, System::EventArgs ^ e)
{
  dateTimeWeeklyStart->DataBindings->Add( "MinDate", LocationBinding, "Weather.MinDate" );
  dateTimeWeeklyStart->DataBindings->Add( "MaxDate", LocationBinding, "Weather.MaxDate" );
  dateTimeWeeklyStart->DataBindings->Add( "Value", Schedule_, "StartDate" );

  numWeeklyInterval->DataBindings->Add( "Text", Schedule_, "WeekInterval" );

  checkSunday->DataBindings->Add( "Checked", Schedule_, "Sunday" );
  checkMonday->DataBindings->Add( "Checked", Schedule_, "Monday" );
  checkTuesday->DataBindings->Add( "Checked", Schedule_, "Tuesday" );
  checkWednesday->DataBindings->Add( "Checked", Schedule_, "Wednesday" );
  checkThursday->DataBindings->Add( "Checked", Schedule_, "Thursday" );
  checkFriday->DataBindings->Add( "Checked", Schedule_, "Friday" );
  checkSaturday->DataBindings->Add( "Checked", Schedule_, "Saturday" );

  checkWeeklyEnd->DataBindings->Add( "Checked", Schedule_, "UseStopDate", false, DataSourceUpdateMode::OnPropertyChanged );

  dateTimeWeeklyEnd->DataBindings->Add( "MinDate", LocationBinding, "Weather.MinDate" );
  dateTimeWeeklyEnd->DataBindings->Add( "MaxDate", LocationBinding, "Weather.MaxDate" );
  dateTimeWeeklyEnd->DataBindings->Add( "Enabled", Schedule_, "UseStopDate" );
  dateTimeWeeklyEnd->DataBindings->Add( "Value", Schedule_, "StopDate" );
}
