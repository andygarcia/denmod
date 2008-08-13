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
  //ArrayList ^ tags = gcnew ArrayList();
  //lboxLocationGraphs->Tag = tags;

  // place all graphs in one list box
  lboxLocationGraphs->DisplayMember = "Name";
  lboxLocationGraphs->DataSource = output::ChartInfos::GetChartInfoCollection(output::Group::DensimLocation);

  // todo
  //output::ChartInfo ^ detailedSero = gcnew output::ChartInfo( "Detailed Seroprevalence", false);
  //tags->Add( gcnew output::CreateChartInfoDelegate( this, &gui::DensimExtOutputForm::DetailedSeroprevalence ) );
  //lboxLocationGraphs->Items->Add( detailedSero );

  lboxVirusGraphs->DisplayMember = "Name";
  lboxVirusGraphs->DataSource = output::ChartInfos::GetChartInfoCollection(output::Group::DensimSerotype);
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
DensimExtOutputForm::OnViewLocationGraph(System::Object^  sender, System::EventArgs^  e)
{
  if( lboxLocationGraphs->SelectedItem == nullptr ) {
    MessageBox::Show( this, "Please select a graph to view." );
    return;
  }

  using namespace output;

  //ChartInfo ^ chartInfo;
  //ArrayList ^ tags = (ArrayList^) lboxLocationGraphs->Tag;
  //if( tags[lboxLocationGraphs->SelectedIndex] != nullptr ) {
  //  // use delegate to create chart
  //  output::CreateChartInfoDelegate ^ ccid = (output::CreateChartInfoDelegate^) tags[lboxLocationGraphs->SelectedIndex];
  //  chartInfo = ccid->Invoke();
  //}
  //else {
  //  // non data bound list, SelectedValue always null, use SelectedItem
  //  chartInfo = (ChartInfo^) lboxLocationGraphs->SelectedItem;
  //}


  ChartInfo ^ chartInfo = (ChartInfo^) lboxLocationGraphs->SelectedValue;
  //TimePeriod timePeriod = TimePeriod( cboxTimePeriod->SelectedValue );
  TimePeriod timePeriod = TimePeriod::Daily;
  //TimePeriodFunction timePeriodFunction = TimePeriodFunction( cboxTimePeriodFunction->SelectedValue );
  TimePeriodFunction timePeriodFunction = TimePeriodFunction::Average;

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
  //TimePeriod timePeriod = TimePeriod( cboxTimePeriod->SelectedValue );
  TimePeriod timePeriod = TimePeriod::Daily;
  //TimePeriodFunction timePeriodFunction = TimePeriodFunction( cboxTimePeriodFunction->SelectedValue );
  TimePeriodFunction timePeriodFunction = TimePeriodFunction::Average;

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



output::ChartInfo ^
DensimExtOutputForm::DetailedSeroprevalence(void)
{
  // pop up dialog that allows selection of age class for seroprevalence summary
  output::ChartInfo ^ chartInfo = gcnew output::ChartInfo( "Detailed Seroprevalence", false );

  // prompt user for age classes


  // use densim output to create output


  // create relevant outputs
  return chartInfo;
}
