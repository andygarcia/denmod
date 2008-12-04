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
  cboxMonthlyStartMonth->DataBindings->Add( "SelectedItem", Schedule_, "StartMonth", false, DataSourceUpdateMode::OnPropertyChanged );

  cboxMonthlyStartYear->ValueMember = "Index";
  cboxMonthlyStartYear->DisplayMember = "Index";
  cboxMonthlyStartYear->DataBindings->Add( "DataSource", LocationBinding, "Weather.YearsBindingList", false, DataSourceUpdateMode::OnPropertyChanged );

  cboxMonthlyStartYear->DataBindings->Add( "SelectedValue", Schedule_, "StartYear", false, DataSourceUpdateMode::OnPropertyChanged );

  numMonthlyInterval->DataBindings->Add( "Text", Schedule_, "MonthInterval", false, DataSourceUpdateMode::OnPropertyChanged );

  cboxMonthlyDay->DataBindings->Add( "SelectedItem", Schedule_, "DayOfMonth", false, DataSourceUpdateMode::OnPropertyChanged );

  checkMonthlyEnd->DataBindings->Add( "Checked", Schedule_, "UseStopDate", false, DataSourceUpdateMode::OnPropertyChanged );
  dateTimeMonthlyEnd->DataBindings->Add( "MinDate", LocationBinding, "Weather.MinDate", false, DataSourceUpdateMode::Never );
  dateTimeMonthlyEnd->DataBindings->Add( "MaxDate", LocationBinding, "Weather.MaxDate", false, DataSourceUpdateMode::Never );
  dateTimeMonthlyEnd->DataBindings->Add( "Enabled", Schedule_, "UseStopDate", false, DataSourceUpdateMode::OnPropertyChanged );
  dateTimeMonthlyEnd->DataBindings->Add( "Value", Schedule_, "StopDate", false, DataSourceUpdateMode::OnPropertyChanged );
}
