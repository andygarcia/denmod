#include "StdAfx.h"
#include "DensimExtOutputForm.h"
#include "ChartForm.h"
#include "DensimPanel.h"

using namespace gui;



DensimExtOutputForm::DensimExtOutputForm( gui::Location ^ location )
: Location_( location )
{
	InitializeComponent();
}



DensimExtOutputForm::~DensimExtOutputForm()
{
	if( components ) {
		delete components;
	}
}



System::Void
DensimExtOutputForm::OnLoad(System::Object^  sender, System::EventArgs^  e)
{
  lboxLocationGraphs->DisplayMember = "Name";
  lboxLocationGraphs->DataSource = output::ChartInfos::GetChartInfoCollection(output::Group::DensimLocation);

  lboxVirusGraphs->DisplayMember = "Name";
  lboxVirusGraphs->DataSource = output::ChartInfos::GetChartInfoCollection(output::Group::DensimSerotype);

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
DensimExtOutputForm::OnGraphTabChanged(System::Object^  sender, System::EventArgs^  e)
{
  OnGraphSelectionChanged( sender, e );
}



System::Void
DensimExtOutputForm::OnView(System::Object^  sender, System::EventArgs^  e)
{
  if( tabGraphType->SelectedTab == tabPageLocation ) {
    OnViewLocationGraph( btnView, nullptr );
  }
  else if( tabGraphType->SelectedTab == tabPageVirus ) {
    OnViewVirusGraph( btnView, nullptr );
  }
  else {
  }
}



System::Void
DensimExtOutputForm::OnGraphSelectionChanged(System::Object^  sender, System::EventArgs^  e)
{
  // selection has changed, disable/enable summary combo boxes based on selected chart
  output::ChartInfo ^ chartInfo;
  if( tabGraphType->SelectedTab == tabPageLocation ) {
    chartInfo = (output::ChartInfo^) lboxLocationGraphs->SelectedValue;
  }
  else if( tabGraphType->SelectedTab == tabPageVirus ) {
    chartInfo = (output::ChartInfo^) lboxVirusGraphs->SelectedValue;
  }

  if( chartInfo->Periodic ) {
    cboxTimePeriod->Enabled = true;
    cboxTimePeriodFunction->Enabled = true;
  }
  else{
    // chart is non periodic data, disable period summary ui elements
    cboxTimePeriod->Enabled = false;
    cboxTimePeriodFunction->Enabled = false;
  }
}



System::Void
DensimExtOutputForm::OnViewLocationGraph(System::Object^  sender, System::EventArgs^  e)
{
  if( lboxLocationGraphs->SelectedItem == nullptr ) {
    MessageBox::Show( this, "Please select a graph to view." );
    return;
  }

  using namespace output;

  ChartInfo ^ chartInfo = (ChartInfo^) lboxLocationGraphs->SelectedValue;
  TimePeriod timePeriod = TimePeriod( cboxTimePeriod->SelectedValue );
  TimePeriodFunction timePeriodFunction = TimePeriodFunction( cboxTimePeriodFunction->SelectedValue );

  Chart ^ chart = Chart::Create( chartInfo, Location_->CimsimOutput, Location_->DensimOutput, nullptr );

  ChartForm ^ gf = gcnew ChartForm( Location_, chart, timePeriod, timePeriodFunction );
  gf->ShowDialog(this);
  gf->Close();
}



System::Void
DensimExtOutputForm::OnViewVirusGraph( System::Object ^ sender, System::EventArgs ^ e )
{
  if( lboxVirusGraphs->SelectedItem == nullptr ) {
    MessageBox::Show( this, "Please select a graph to view." );
    return;
  }

  using namespace output;

  ChartInfo ^ chartInfo = (ChartInfo^) lboxVirusGraphs->SelectedValue;
  TimePeriod timePeriod = TimePeriod( cboxTimePeriod->SelectedValue );
  TimePeriodFunction timePeriodFunction = TimePeriodFunction( cboxTimePeriodFunction->SelectedValue );

  Collections::Generic::List<int> ^ serotypes = gcnew Collections::Generic::List<int>();
  serotypes->Add(1);
  serotypes->Add(2);
  serotypes->Add(3);
  serotypes->Add(4);

  Chart ^ chart = Chart::Create( chartInfo, Location_->CimsimOutput, Location_->DensimOutput, serotypes );

  ChartForm ^ gf = gcnew ChartForm( Location_, chart, timePeriod, timePeriodFunction );
  gf->ShowDialog(this);
  gf->Close();
}
