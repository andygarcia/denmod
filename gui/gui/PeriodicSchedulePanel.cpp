#include "StdAfx.h"
#include "PeriodicSchedulePanel.h"

using namespace gui;



PeriodicSchedulePanel::PeriodicSchedulePanel( gui::PeriodicSchedule ^ ps, BindingSource ^ locationBinding )
: LocationBinding(locationBinding),
  ActiveLocation((gui::Location^)locationBinding->DataSource)
{
  Schedule_ = ps;
	InitializeComponent();
}



PeriodicSchedulePanel::~PeriodicSchedulePanel()
{
  if( components ) {
		delete components;
	}
}


System::Void
PeriodicSchedulePanel::OnLoad( System::Object ^ sender, System::EventArgs ^ e)
{
  dateTimePeriodicStart->DataBindings->Add( "MinDate", LocationBinding, "Weather.MinDate" );
  dateTimePeriodicStart->DataBindings->Add( "MaxDate", LocationBinding, "Weather.MaxDate" );
  dateTimePeriodicStart->DataBindings->Add( "Value", Schedule_, "StartDate" );

  DateTime minDate = ActiveLocation->Weather->MinDate;
  DateTime maxDate = ActiveLocation->Weather->MaxDate;
  numPeriodicInterval->Maximum = (maxDate - minDate).Days;
  numPeriodicInterval->DataBindings->Add( "Text", Schedule_, "TreatmentInterval" );

  checkPeriodicTreatments->DataBindings->Add( "Checked", Schedule_, "UseTreatments", false, DataSourceUpdateMode::OnPropertyChanged );

  numPeriodicTreatments->DataBindings->Add( "Enabled", Schedule_, "UseTreatments" );
  numPeriodicTreatments->DataBindings->Add( "Text", Schedule_, "NumberOfTreatments" );

  checkPeriodicStop->DataBindings->Add( "Checked", Schedule_, "UseStopDate", false, DataSourceUpdateMode::OnPropertyChanged );

  dateTimePeriodicStop->DataBindings->Add( "MinDate", LocationBinding, "Weather.MinDate", false, DataSourceUpdateMode::Never );
  dateTimePeriodicStop->DataBindings->Add( "MaxDate", LocationBinding, "Weather.MaxDate", false, DataSourceUpdateMode::Never );
  dateTimePeriodicStop->DataBindings->Add( "Enabled", Schedule_, "UseStopDate" );
  dateTimePeriodicStop->DataBindings->Add( "Value", Schedule_, "StopDate" );
}
