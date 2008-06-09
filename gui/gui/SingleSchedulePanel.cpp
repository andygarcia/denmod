#include "StdAfx.h"
#include "SingleSchedulePanel.h"

using namespace gui;



SingleSchedulePanel::SingleSchedulePanel( gui::SingleSchedule ^ ss, BindingSource ^ locationBinding )
: LocationBinding(locationBinding),
  ActiveLocation((gui::Location^)locationBinding->DataSource)
{
  Schedule_ = ss;
	InitializeComponent();
}



SingleSchedulePanel::~SingleSchedulePanel()
{
  if( components ) {
		delete components;
	}
}



System::Void
SingleSchedulePanel::OnLoad( System::Object ^ sender, System::EventArgs ^ e)
{
  dateTimeSingleStart->DataBindings->Add( "MinDate", LocationBinding, "Weather.MinDate", false, DataSourceUpdateMode::Never );
  dateTimeSingleStart->DataBindings->Add( "MaxDate", LocationBinding, "Weather.MaxDate", false, DataSourceUpdateMode::Never );
  dateTimeSingleStart->DataBindings->Add( "Value", Schedule_, "Date" );
}
