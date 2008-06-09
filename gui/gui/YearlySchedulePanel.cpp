#include "StdAfx.h"
#include "YearlySchedulePanel.h"

using namespace gui;



YearlySchedulePanel::YearlySchedulePanel( gui::YearlySchedule ^ ys, BindingSource ^ locationBinding )
: LocationBinding(locationBinding),
  ActiveLocation((gui::Location^)locationBinding->DataSource)
{
  Schedule_ = ys;
	InitializeComponent();
}



YearlySchedulePanel::~YearlySchedulePanel()
{
	if (components)
	{
		delete components;
	}
}



System::Void
YearlySchedulePanel::OnLoad( System::Object ^ sender, System::EventArgs ^ e)
{
  // yearly schedule bindings
  cboxYearlyStart->ValueMember = "Index";
  cboxYearlyStart->DisplayMember = "Index";
  cboxYearlyStart->DataBindings->Add( "DataSource", LocationBinding, "Weather.YearsBindingList" );
  cboxYearlyStart->DataBindings->Add( "SelectedValue", Schedule_, "StartYear" );

  numYearlyInterval->DataBindings->Add( "Text", Schedule_, "YearInterval" );

  numYearlyDay->DataBindings->Add( "Text", Schedule_, "DayOfYear" );
}
