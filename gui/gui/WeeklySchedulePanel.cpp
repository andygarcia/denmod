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
  dateTimeWeeklyStart->DataBindings->Add( "MinDate", LocationBinding, "Weather.MinDate", false, DataSourceUpdateMode::Never );
  dateTimeWeeklyStart->DataBindings->Add( "MaxDate", LocationBinding, "Weather.MaxDate", false, DataSourceUpdateMode::Never );
  dateTimeWeeklyStart->DataBindings->Add( "Value", Schedule_, "StartDate", false, DataSourceUpdateMode::OnPropertyChanged );

  numWeeklyInterval->DataBindings->Add( "Text", Schedule_, "WeekInterval", false, DataSourceUpdateMode::OnPropertyChanged );

  checkSunday->DataBindings->Add( "Checked", Schedule_, "Sunday", false, DataSourceUpdateMode::OnPropertyChanged );
  checkMonday->DataBindings->Add( "Checked", Schedule_, "Monday", false, DataSourceUpdateMode::OnPropertyChanged );
  checkTuesday->DataBindings->Add( "Checked", Schedule_, "Tuesday", false, DataSourceUpdateMode::OnPropertyChanged );
  checkWednesday->DataBindings->Add( "Checked", Schedule_, "Wednesday", false, DataSourceUpdateMode::OnPropertyChanged );
  checkThursday->DataBindings->Add( "Checked", Schedule_, "Thursday", false, DataSourceUpdateMode::OnPropertyChanged );
  checkFriday->DataBindings->Add( "Checked", Schedule_, "Friday", false, DataSourceUpdateMode::OnPropertyChanged );
  checkSaturday->DataBindings->Add( "Checked", Schedule_, "Saturday", false, DataSourceUpdateMode::OnPropertyChanged );

  checkWeeklyEnd->DataBindings->Add( "Checked", Schedule_, "UseStopDate", false, DataSourceUpdateMode::OnPropertyChanged );

  dateTimeWeeklyEnd->DataBindings->Add( "MinDate", LocationBinding, "Weather.MinDate", false, DataSourceUpdateMode::Never );
  dateTimeWeeklyEnd->DataBindings->Add( "MaxDate", LocationBinding, "Weather.MaxDate", false, DataSourceUpdateMode::Never );
  dateTimeWeeklyEnd->DataBindings->Add( "Enabled", Schedule_, "UseStopDate", false, DataSourceUpdateMode::OnPropertyChanged );
  dateTimeWeeklyEnd->DataBindings->Add( "Value", Schedule_, "StopDate", false, DataSourceUpdateMode::OnPropertyChanged );
}
