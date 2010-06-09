#include "StdAfx.h"
#include "CimsimExtOutputForm.h"
#include "ChartForm.h"
#include "CimsimPanel.h"
#include "ExcelOutput.h"

using namespace gui;



CimsimExtOutputForm::CimsimExtOutputForm( gui::Location ^ location )
: _location(location)
{
	InitializeComponent();
}



CimsimExtOutputForm::~CimsimExtOutputForm()
{
	if( components ) {
		delete components;
	}
}



System::Void
CimsimExtOutputForm::OnLoad(System::Object^  sender, System::EventArgs^  e)
{
  // location graphs
  lboxLocationGraphs->DisplayMember = "Name";
  lboxLocationGraphs->DataSource = output::ChartInfos::CimsimLocationCharts;

  // container graphs
  lboxContainerGraphs->DisplayMember = "Name";
  lboxContainerGraphs->DataSource = output::ChartInfos::CimsimContainerCharts;

  // container names
  cboxContainers->DisplayMember = "Name";
  cboxContainers->ValueMember = "Id";
  cboxContainers->DataSource = _location->Containers;

  // initially select first container
  cboxContainers->SelectedIndex = 0;

  // time periods
  cboxTimePeriod->DisplayMember = "DisplayName";
  cboxTimePeriod->ValueMember = "Value";
  cboxTimePeriod->DataSource = output::EnumText::ConvertEnumForBinding( gcnew output::TimePeriod() );

  // time periods
  cboxTimePeriodFunction->DisplayMember = "DisplayName";
  cboxTimePeriodFunction->ValueMember = "Value";
  cboxTimePeriodFunction->DataSource = output::EnumText::ConvertEnumForBinding( gcnew output::TimePeriodFunction() );
}



System::Void
CimsimExtOutputForm::OnView(System::Object^  sender, System::EventArgs^  e)
{
  if( tabGraphType->SelectedTab == tabPageLocation ) {
    OnViewLocationGraph( btnView, nullptr );
  }
  else if( tabGraphType->SelectedTab == tabPageContainer ) {
    OnViewContainerGraph( btnView, nullptr );
  }
  else {
  }
}



System::Void
CimsimExtOutputForm::OnViewLocationGraph(System::Object^  sender, System::EventArgs^  e)
{
  if( lboxLocationGraphs->SelectedItem == nullptr ) {
    MessageBox::Show( this, "Please select a graph to view." );
    return;
  }

  using namespace output;

  // create selected chart
  ChartInfo ^ chartInfo = (ChartInfo^) lboxLocationGraphs->SelectedValue;
  Chart ^ chart = _location->CimsimOutput->CreateLocationChart( chartInfo->ChartId );

  // display chart with options
  TimePeriod timePeriod = TimePeriod( cboxTimePeriod->SelectedValue );
  TimePeriodFunction timePeriodFunction = TimePeriodFunction( cboxTimePeriodFunction->SelectedValue );
  ChartForm ^ gf = gcnew ChartForm( _location, chart, timePeriod, timePeriodFunction );
  gf->ShowDialog(this);
  gf->Close();
}



System::Void
CimsimExtOutputForm::OnViewContainerGraph(System::Object^  sender, System::EventArgs^  e)
{
  if( cboxContainers->SelectedItem == nullptr || lboxContainerGraphs->SelectedItem == nullptr ) {
    MessageBox::Show( "Please select a container and graph to view." );
  }

  using namespace output;

  // create selected chart
  ChartInfo ^ chartInfo= (ChartInfo^) lboxContainerGraphs->SelectedValue;
  int containerId = Convert::ToInt32( cboxContainers->SelectedValue );
  Chart ^ chart = _location->CimsimOutput->CreateContainerChart( chartInfo->ChartId, containerId );

  // display chart with options
  TimePeriod timePeriod = TimePeriod( cboxTimePeriod->SelectedValue );
  TimePeriodFunction timePeriodFunction = TimePeriodFunction( cboxTimePeriodFunction->SelectedValue );
  ChartForm ^ gf = gcnew ChartForm( _location, chart, timePeriod, timePeriodFunction );
  gf->ShowDialog(this);
  gf->Close();
}



System::Void
CimsimExtOutputForm::OnSelectedIndexChanged( System::Object ^ sender, System::EventArgs ^ e )
{

}
