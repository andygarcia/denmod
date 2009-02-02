#include "StdAfx.h"
#include "ChartForm.h"
#include "ExcelOutput.h"

using namespace gui;
using namespace boost::gregorian;
using namespace Dundas::Charting::WinControl;



ChartForm::ChartForm( gui::Location ^ location, output::Chart ^ chartData, output::TimePeriod timePeriod, output::TimePeriodFunction timePeriodFunction )
: _location(location)
{
  InitializeComponent();

  // set window title from output::Chart::Name
  this->Text = chartData->Name;

  for each( output::Plot ^ plot in chartData->Plots ) {
    // create, add, and customize chart area
    ChartArea ^ chartArea = gcnew ChartArea();
    chart->ChartAreas->Add( chartArea );
    chartArea->Name = plot->Title;

    // create chart area title from output::Plot::Title
    Title ^ title = gcnew Title( plot->Title, Docking::Top );
    chart->Titles->Add( title );
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

    chartArea->CursorX->Interval = 1;
    chartArea->CursorX->UserEnabled = true;
    chartArea->CursorX->UserSelection = true;
    // use 1% of range of Y axis
    chartArea->CursorY->Interval = (chartArea->AxisY->Maximum - chartArea->AxisY->Minimum) / 100.0;
    chartArea->CursorY->UserEnabled = true;
    chartArea->CursorY->UserSelection = true;


    Legend ^ legend = gcnew Legend( plot->Title );
    legend->Enabled = true;
    legend->DockToChartArea = chartArea->Name;
    legend->BorderStyle = ChartDashStyle::Solid;
    legend->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(26)),
                                                           static_cast<System::Int32>(static_cast<System::Byte>(59)), 
                                                           static_cast<System::Int32>(static_cast<System::Byte>(105)));
    chart->Legends->Add( legend );

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

      chart->Series->Add( series );
    }
  }
}



ChartForm::~ChartForm()
{
  if( components ) {
		delete components;
	}
}



System::Void ChartForm::OnSave(System::Object^  sender, System::EventArgs^  e)
{
  // save current chart to disk
  SaveFileDialog ^ sfd = gcnew SaveFileDialog();
  sfd->InitialDirectory = Environment::CurrentDirectory;
  sfd->FileName = chart->Text + ".xml";

  if( sfd->ShowDialog(this) != Windows::Forms::DialogResult::OK) {
    return;
  }
  String ^ newFilename = sfd->FileName;

  // ensure correct extensions
  IO::FileInfo ^ fi = gcnew IO::FileInfo(newFilename);
  if( fi->Extension->Equals(".xml", StringComparison::CurrentCultureIgnoreCase) == false ) {
    newFilename = newFilename + ".xml";
  }

  try {
    System::IO::StreamWriter ^ sw = gcnew System::IO::StreamWriter( newFilename );
    sw->Write( ExcelOutput::GetXml(chart) );
    sw->Close();
  }
  catch( System::IO::IOException ^ ioe ) {
    System::Console::WriteLine( ioe->ToString() );
    MessageBox::Show( "Unable to save file.  " + newFilename + " is open.  Please close file and try again" );
  }
}
