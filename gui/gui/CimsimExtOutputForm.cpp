#include "StdAfx.h"
#include "CimsimExtOutputForm.h"
#include "GraphForm.h"
#include "CimsimPanel.h"
#include "ExcelOutput.h"

using namespace gui;



CimsimExtOutputForm::CimsimExtOutputForm( gui::Location ^ location )
: Location_(location)
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
  lboxLocationGraphs->DataSource = output::ChartInfos::GetChartInfoCollection( output::Group::CimsimLocation );

  // container graphs
  lboxContainerGraphs->DisplayMember = "Name";
  lboxContainerGraphs->DataSource = output::ChartInfos::GetChartInfoCollection( output::Group::CimsimContainer );

  // container names
  cboxContainers->DisplayMember = "Name";
  cboxContainers->ValueMember = "Id";
  cboxContainers->DataSource = Location_->Containers;

  // time periods
  cboxTimePeriod->DisplayMember = "DisplayName";
  cboxTimePeriod->ValueMember = "Value";
  cboxTimePeriod->DataSource = output::EnumText::ConvertEnumForBinding( gcnew output::TimePeriod() );

  // show a container initially
  cboxContainers->SelectedIndex = 0;
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
    // TODO ?
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

  ChartInfo ^ chartInfo = (ChartInfo^) lboxLocationGraphs->SelectedValue;
  TimePeriod timePeriod = TimePeriod( cboxTimePeriod->SelectedValue );

  GraphForm ^ gf = gcnew GraphForm( Location_, chartInfo, timePeriod, output::TimePeriodFunction::Average );
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

  ChartInfo ^ chartInfo= (ChartInfo^) lboxContainerGraphs->SelectedValue;
  for each( GraphInfo ^ graphInfo in chartInfo->GraphInfos ) {
    graphInfo->ContainerId = Convert::ToInt32( cboxContainers->SelectedValue );
  }

  TimePeriod timePeriod = TimePeriod( cboxTimePeriod->SelectedValue );

  GraphForm ^ gf = gcnew GraphForm( Location_, chartInfo, timePeriod, output::TimePeriodFunction::Average );
  gf->ShowDialog(this);
  gf->Close();
}
