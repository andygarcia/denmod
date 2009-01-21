#include "StdAfx.h"
#include "DensimExtOutputForm.h"
#include "ChartForm.h"
#include "DensimPanel.h"

using namespace gui;



DensimExtOutputForm::DensimExtOutputForm( gui::Location ^ location )
: _location( location )
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
  lboxLocationGraphs->DataSource = output::ChartInfos::DensimCharts;

  lboxVirusGraphs->DisplayMember = "Name";
  lboxVirusGraphs->DataSource = output::ChartInfos::DensimVirusCharts;

  lboxSeroprevalence->DisplayMember = "DisplayName";
  lboxSeroprevalence->ValueMember = "Value";
  lboxSeroprevalence->DataSource = output::EnumText::ConvertEnumForBinding( output::SeroClass() );

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
  else if( tabGraphType->SelectedTab == tabPageSeroprevalence ) {
    OnViewDetailedSeroprevalenceGraph( btnView, nullptr );
  }
  else {
    throw gcnew InvalidOperationException( "count not find selected tab" );
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
  else if( tabGraphType->SelectedTab == tabPageSeroprevalence ) {
    // all detailed seroprevalence can be summarized
    cboxTimePeriod->Enabled = true;
    cboxTimePeriodFunction->Enabled = true;
    return;
  }
  else {
    throw gcnew InvalidOperationException( "cound not locate tab page" );
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
  Chart ^ chart = _location->DensimOutput->CreateChart( chartInfo );
  TimePeriod timePeriod = TimePeriod( cboxTimePeriod->SelectedValue );
  TimePeriodFunction timePeriodFunction = TimePeriodFunction( cboxTimePeriodFunction->SelectedValue );

  ChartForm ^ gf = gcnew ChartForm( _location, chart, timePeriod, timePeriodFunction );
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
  Chart ^ chart = _location->DensimOutput->CreateChart( chartInfo );
  TimePeriod timePeriod = TimePeriod( cboxTimePeriod->SelectedValue );
  TimePeriodFunction timePeriodFunction = TimePeriodFunction( cboxTimePeriodFunction->SelectedValue );

  ChartForm ^ gf = gcnew ChartForm( _location, chart, timePeriod, timePeriodFunction );
  gf->ShowDialog(this);
  gf->Close();
}



System::Void
DensimExtOutputForm::OnViewDetailedSeroprevalenceGraph( System::Object ^ sender, System::EventArgs ^ e )
{
  if( lboxVirusGraphs->SelectedItem == nullptr ) {
    MessageBox::Show( this, "Please select a graph to view." );
    return;
  }

  using namespace output;

  int seroClass = safe_cast<int>( SeroClass(lboxSeroprevalence->SelectedValue) );
  Chart ^ chart = _location->DensimOutput->CreateDetailedSeroprevalenceChart( seroClass );
  TimePeriod timePeriod = TimePeriod( cboxTimePeriod->SelectedValue );
  TimePeriodFunction timePeriodFunction = TimePeriodFunction( cboxTimePeriodFunction->SelectedValue );

  ChartForm ^ gf = gcnew ChartForm( _location, chart, timePeriod, timePeriodFunction );
  gf->ShowDialog(this);
  gf->Close();
}
