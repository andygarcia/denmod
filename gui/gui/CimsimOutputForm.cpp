#include "StdAfx.h"
#include "CimsimOutputForm.h"
#include "RunDensimForm.h"
#include "DensimOutputForm.h"
#include "ExcelOutput.h"
#include "../objs/Util.h"

using namespace gui;
using namespace boost::gregorian;
using namespace Dundas::Charting::WinControl;



CimsimOutputForm::CimsimOutputForm( gui::Location ^ location )
: _location(location)
{
	InitializeComponent();
  output::CimsimOutput ^ co = _location->CimsimOutput;
  UserSettings ^ userSettings = _location->UserSettings;
  
  // create chart depending on scale setting
  output::Chart ^ chart;
  if( userSettings->ScaleCimsimMainGraph ) {
    chart = co->CreateLocationChart( output::ChartIds::CimsimMainScaled );
  }
  else {
    chart = co->CreateLocationChart( output::ChartIds::CimsimMain );
  }

  output::Plot ^ mainPlot = chart->Plots[0];

  for each( output::DatedOutput ^ output in mainPlot->PrimaryOutputs ) {
    Series ^ s = gcnew Series( output->Name );
    s->ChartType = "Line";

    s->Points->DataBindXY( co->Weeks, output->GetWeeklyData( output::TimePeriodFunction::Average ) );

    _chart->Series->Add( s );
  }

  _chart->Title = "Total mosquitoes per hectare - weekly averages";

}



CimsimOutputForm::~CimsimOutputForm()
{
  if( components ) {
		delete components;
	}
}



System::Void
CimsimOutputForm::OnLoad(System::Object^  sender, System::EventArgs^  e)
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
CimsimOutputForm::OnView(System::Object^  sender, System::EventArgs^  e)
{
  if( tabGraphs->SelectedTab == tabPageLocation ) {
    OnViewLocationGraph( btnView, nullptr );
  }
  else if( tabGraphs->SelectedTab == tabPageContainers ) {
    OnViewContainerGraph( btnView, nullptr );
  }
  else {
  }
}




System::Void
CimsimOutputForm::OnViewLocationGraph(System::Object^  sender, System::EventArgs^  e)
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
  DisplayChart( chart, timePeriod, timePeriodFunction );
}



System::Void
CimsimOutputForm::OnViewContainerGraph(System::Object^  sender, System::EventArgs^  e)
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
  DisplayChart( chart, timePeriod, timePeriodFunction );
}



System::Void
CimsimOutputForm::OnSave(System::Object^  sender, System::EventArgs^  e)
{
  // save current chart to disk
  SaveFileDialog ^ sfd = gcnew SaveFileDialog();
  sfd->InitialDirectory = Environment::CurrentDirectory;
  sfd->FileName = "CIMSiM - Main Graph - " + _location->Name + ".xml";

  String ^ newFilename;
  if( sfd->ShowDialog(this) != Windows::Forms::DialogResult::OK) {
    return;
  }
  newFilename = sfd->FileName;

  // ensure correct extensions
  IO::FileInfo ^ fi = gcnew IO::FileInfo(newFilename);
  if( fi->Extension->Equals(".xml", StringComparison::CurrentCultureIgnoreCase) == false ) {
    newFilename = newFilename + ".xml";
  }

  try {
    System::IO::StreamWriter ^ sw = gcnew System::IO::StreamWriter( newFilename );
    sw->Write( ExcelOutput::GetXml(_chart) );
    sw->Close();
  }
  catch( System::IO::IOException ^ ioe ) {
    Diagnostics::Debug::WriteLine( ioe->ToString() );
    MessageBox::Show( "Unable to save files.  " + newFilename + "is currently open.  Please close output files and try again" );
  }
}



System::Void
CimsimOutputForm::OnSaveAll(System::Object^  sender, System::EventArgs^  e)
{
  // save all output to a directory
  FolderBrowserDialog ^ fbd = gcnew FolderBrowserDialog();
  fbd->SelectedPath = Environment::CurrentDirectory;
  if( fbd->ShowDialog() != ::DialogResult::OK ) {
    return;
  }
  IO::DirectoryInfo ^ di = gcnew IO::DirectoryInfo( fbd->SelectedPath );

  try {
    _location->CimsimOutput->SaveToDisk( di );
  }
  catch( System::IO::DirectoryNotFoundException ^ e ) {
    Console::WriteLine( "CimsimOutputForm::OnSaveAll() : " + e->ToString() + " : " + e->Message );
    MessageBox::Show( "Unable to save files. Directory not found." );
    return;
  }
  catch( System::IO::DriveNotFoundException ^ e ) {
    Console::WriteLine( "CimsimOutputForm::OnSaveAll() : " + e->ToString() + " : " + e->Message );
    MessageBox::Show( "Unable to save files. Drive not found." );
    return;
  }
  catch( System::IO::IOException ^ e ) {
    Console::WriteLine( "CimsimOutputForm::OnSaveAll() : " + e->ToString() + " : " + e->Message );
    MessageBox::Show( "Unable to save files. Make sure all output files are closed before saving." );
  }
}



System::Void
CimsimOutputForm::OnRunDensim(System::Object^  sender, System::EventArgs^  e)
{
  BindingSource ^ locBinding = gcnew BindingSource();
  locBinding->DataSource = _location;

  RunDensimForm ^ rdf = gcnew RunDensimForm( locBinding );
  if( rdf->ShowDialog(this) == ::DialogResult::OK ) {
    // run simulation
    gui::Location::RunDensimOptions ^ rdo = rdf->RunDensimOptions;
    _location->RunDensim( rdo->StartDate, rdo->StopDate );
    rdf->Close();

    // process output
    DensimOutputForm ^ dof = gcnew DensimOutputForm( _location );
    dof->ShowDialog(this);
    dof->Close();    
  }
}



void
CimsimOutputForm::DisplayChart( output::Chart ^ chartData, output::TimePeriod timePeriod, output::TimePeriodFunction timePeriodFunction )
{
  // first remove existing chart areas
  _chart->ChartAreas->Clear();
  _chart->Titles->Clear();
  _chart->Legends->Clear();
  _chart->Series->Clear();
  _chart->Update();

  // now display newly selected chart
  for each( output::Plot ^ plot in chartData->Plots ) {
    // create, add, and customize chart area
    ChartArea ^ chartArea = gcnew ChartArea();
    _chart->ChartAreas->Add( chartArea );
    chartArea->Name = plot->Title;

    // create chart area title from output::Plot::Title
    Title ^ title = gcnew Title( plot->Title, Docking::Top );
    _chart->Titles->Add( title );
    title->DockToChartArea = chartArea->Name;
    title->DockInsideChartArea = false;

    // position and size
    chartArea->Position->Auto = true;
    chartArea->InnerPlotPosition->Auto = true;

    // x axis
    chartArea->AxisX->LabelStyle->IntervalOffset = 0;
    chartArea->AxisX->LabelStyle->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
    chartArea->AxisX->LabelStyle->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
    chartArea->AxisX->MajorGrid->Enabled = false;
    chartArea->AxisX->MajorGrid->Interval = 0;
    chartArea->AxisX->MajorGrid->IntervalOffset = 0;
    chartArea->AxisX->MajorGrid->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
    chartArea->AxisX->MajorGrid->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
    chartArea->AxisX->MajorGrid->LineColor = System::Drawing::Color::Silver;
    chartArea->AxisX->MajorTickMark->Interval = 0;
    chartArea->AxisX->MajorTickMark->IntervalOffset = 0;
    chartArea->AxisX->MajorTickMark->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
    chartArea->AxisX->MajorTickMark->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
    chartArea->AxisX->Margin = false;
    chartArea->AxisX->MinorGrid->LineColor = System::Drawing::Color::Silver;
    chartArea->AxisX->Title = plot->AxisX;

    // y axis
    chartArea->AxisY->LabelStyle->Interval = 0;
    chartArea->AxisY->LabelStyle->IntervalOffset = 0;
    chartArea->AxisY->LabelStyle->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
    chartArea->AxisY->LabelStyle->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
    chartArea->AxisY->MajorGrid->Interval = 0;
    chartArea->AxisY->MajorGrid->IntervalOffset = 0;
    chartArea->AxisY->MajorGrid->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
    chartArea->AxisY->MajorGrid->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
    chartArea->AxisY->MajorGrid->LineColor = System::Drawing::Color::Silver;
    chartArea->AxisY->MajorTickMark->Interval = 0;
    chartArea->AxisY->MajorTickMark->IntervalOffset = 0;
    chartArea->AxisY->MajorTickMark->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
    chartArea->AxisY->MajorTickMark->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
    chartArea->AxisY->Margin = true;
    chartArea->AxisY->MinorGrid->LineColor = System::Drawing::Color::Silver;
    chartArea->AxisY->Title = plot->AxisY;

    // check for custom y bounds
    if( plot->CustomYAxis ) {
      chartArea->AxisY->Minimum = plot->MinYAxis;
      chartArea->AxisY->Maximum = plot->MaxYAxis;
    }

    // colors
    chartArea->BackColor = System::Drawing::Color::White;
    chartArea->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(26)),
                                                              static_cast<System::Int32>(static_cast<System::Byte>(59)), 
                                                              static_cast<System::Int32>(static_cast<System::Byte>(105)));
    chartArea->BorderStyle = Dundas::Charting::WinControl::ChartDashStyle::Solid;

    chartArea->ShadowOffset = 2;

    Legend ^ legend = gcnew Legend( plot->Title );
    legend->Enabled = true;
    legend->DockToChartArea = chartArea->Name;
    legend->BorderStyle = ChartDashStyle::Solid;
    legend->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(26)),
                                                           static_cast<System::Int32>(static_cast<System::Byte>(59)), 
                                                           static_cast<System::Int32>(static_cast<System::Byte>(105)));
    _chart->Legends->Add( legend );

    // create series and add to chart
    for each( output::IOutput ^ output in plot->PrimaryOutputs ) {
      Series ^ series = gcnew Series();
      series->Name = output->Name;
      series->ChartType = plot->PlotType;
      series->ChartArea = chartArea->Name;
      series->Legend = legend->Name;

      if( output->GetType() == output::DatedOutput::typeid ) {
        output::DatedOutput ^ datedOutput = (output::DatedOutput^) output;

        // get dates and data for axis
        Collections::IEnumerable ^ dates;
        Collections::IEnumerable ^ data;

        if( timePeriod == output::TimePeriod::Daily ) {
          dates = datedOutput->GetDates();
          data = datedOutput->Data;
        }
        else if( timePeriod == output::TimePeriod::Weekly ) {
          dates = datedOutput->GetWeeks();
          data = datedOutput->GetWeeklyData( timePeriodFunction );
        }
        else if( timePeriod == output::TimePeriod::Monthly ) {
          dates = datedOutput->GetMonths();
          data = datedOutput->GetMonthlyData( timePeriodFunction );
        }
        else {
          throw gcnew ArgumentException( "unrecognized time period", "timePeriod" );
        }

        series->Points->DataBindXY( dates, data );

      }
      else {
        series->Points->DataBindY( output->Data );
      }

      _chart->Series->Add( series );
    }

    // now that data is added for this plot, call method to update min/max vals for axes
    chartArea->ReCalc();

    // now enable selection/zooming with intervals based on data
    chartArea->CursorX->Interval = 1;
    chartArea->CursorX->UserEnabled = true;
    chartArea->CursorX->UserSelection = true;

    chartArea->CursorY->Interval = (chartArea->AxisY->Maximum - chartArea->AxisY->Minimum) / 100.0;
    chartArea->CursorY->UserEnabled = true;
    chartArea->CursorY->UserSelection = true;
  }
}