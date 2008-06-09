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
  lboxLocationGraphs->DisplayMember = "Title";
  lboxLocationGraphs->ValueMember = "Id";
  lboxLocationGraphs->DataSource = gui::output::GraphCollections::GetGraphInfoBindingList( gui::output::GraphTypes::Cimsim::Location::typeid );

  // container graphs
  lboxContainerGraphs->DisplayMember = "Title";
  lboxContainerGraphs->ValueMember = "Id";
  lboxContainerGraphs->DataSource = gui::output::GraphCollections::GetGraphInfoBindingList( gui::output::GraphTypes::Cimsim::Container::typeid );

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
CimsimExtOutputForm::OnViewLocationGraph(System::Object^  sender, System::EventArgs^  e)
{
  if( lboxLocationGraphs->SelectedItem == nullptr ) {
    MessageBox::Show( this, "Please select a graph to view." );
    return;
  }

  output::GraphTypes::Cimsim::Location graphType = output::GraphTypes::Cimsim::Location( lboxLocationGraphs->SelectedValue );
  output::Graph ^ graph = output::Graph::CreateGraph( graphType, Location_->CimsimOutput);
  output::TimePeriod timePeriod = output::TimePeriod( cboxTimePeriod->SelectedValue );

  GraphForm ^ gf = gcnew GraphForm( Location_, graph, timePeriod, output::TimePeriodFunction::Average );
  gf->ShowDialog(this);
  gf->Close();
}



System::Void
CimsimExtOutputForm::OnViewContainerGraph(System::Object^  sender, System::EventArgs^  e)
{
  if( cboxContainers->SelectedItem == nullptr || lboxContainerGraphs->SelectedItem == nullptr ) {
    MessageBox::Show( "Please select a container and graph to view." );
  }

  output::GraphTypes::Cimsim::Container graphType = output::GraphTypes::Cimsim::Container( lboxContainerGraphs->SelectedValue );
  int containerId = Convert::ToInt32( cboxContainers->SelectedValue );
  output::Graph ^ graph = output::Graph::CreateGraph( graphType, Location_->CimsimOutput, containerId );
  output::TimePeriod timePeriod = output::TimePeriod( cboxTimePeriod->SelectedValue );

  GraphForm ^ gf = gcnew GraphForm( Location_, graph, timePeriod, output::TimePeriodFunction::Average );
  gf->ShowDialog(this);
  gf->Close();
}
