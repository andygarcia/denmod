#include "StdAfx.h"
#include "GraphForm.h"
#include "ExcelOutput.h"

using namespace gui;
using namespace boost::gregorian;
using namespace Dundas::Charting::WinControl;



GraphForm::GraphForm( gui::Location ^ location, output::ChartInfo ^ chartInfo, output::TimePeriod timePeriod, output::TimePeriodFunction timePeriodFunction )
: Location_(location)
{
  InitializeComponent();

  for each( output::GraphInfo ^ graphInfo in chartInfo->GraphInfos ) {
    // create graph object
    output::Graph ^ graph = graphInfo->CreateGraph( location->CimsimOutput, location->DensimOutput );

    // creat, add, and customize chart area
    ChartArea ^ chartArea = gcnew ChartArea();
    chart->ChartAreas->Add( chartArea );
    chartArea->Name = graph->GraphInfo->Title;

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
    chartArea->AxisX->Title = graphInfo->AxisX;

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
    chartArea->AxisY->Title = graphInfo->AxisY;

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
    //chartArea->CursorY->Interval = 0.0001;
    chartArea->CursorY->UserEnabled = true;
    chartArea->CursorY->UserSelection = true;

    Legend ^ legend = gcnew Legend( graphInfo->Title );
    legend->Enabled = true;
    legend->DockToChartArea = chartArea->Name;
    legend->BorderStyle = ChartDashStyle::Solid;
    legend->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(26)),
                                                           static_cast<System::Int32>(static_cast<System::Byte>(59)), 
                                                           static_cast<System::Int32>(static_cast<System::Byte>(105)));
    chart->Legends->Add( legend );

    // create series, add random data, customize, and add to chart
    for each( output::Output ^ output in graph->PrimaryOutputs ) {
      Series ^ series = gcnew Series();
      series->Name = output->Name;
      series->ChartType = graphInfo->GraphType;
      series->ChartArea = chartArea->Name;
      series->Legend = legend->Name;

      output->OutputInfo->OutputGroup;

      if( output->GetType() == output::DatedOutput::typeid ) {
        output::DatedOutput ^ datedOutput = (output::DatedOutput^) output;

        output::CimsimOutput ^ co = location->CimsimOutput;

        // get dates for axis
        Collections::IEnumerable ^ dates;
        if( timePeriod == output::TimePeriod::Daily ) {
          dates = co->Dates;
        }
        else if( timePeriod == output::TimePeriod::Weekly ) {
          dates = co->Weeks;
        }
        else if( timePeriod == output::TimePeriod::Monthly ) {
          dates = co->Months;
        }

        // get period data
        Collections::IEnumerable ^ data;
        if( timePeriod == output::TimePeriod::Daily ) {
          data = datedOutput->Data;
        }
        else if( timePeriod == output::TimePeriod::Weekly ) {
          data = datedOutput->GetWeeklyData( timePeriodFunction );
        }
        else if( timePeriod == output::TimePeriod::Monthly ) {
          data = datedOutput->GetMonthlyData( co->StartDate, co->StopDate, timePeriodFunction );
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



GraphForm::~GraphForm()
{
  if( components ) {
		delete components;
	}
}



System::Void GraphForm::OnSave(System::Object^  sender, System::EventArgs^  e)
{
  // save current chart to disk
  SaveFileDialog ^ sfd = gcnew SaveFileDialog();
  sfd->InitialDirectory = Environment::CurrentDirectory;
  sfd->FileName = chart->Tag + ".xml";
  if( Container_ != nullptr ) {
    sfd->FileName = Container_->Name + " - " + sfd->FileName;
  }

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
    sw->Write( ExcelOutput::GetXml(chart) );
    sw->Close();
  }
  catch( System::IO::IOException ^ ioe ) {
    System::Console::WriteLine( ioe->ToString() );
    MessageBox::Show( "Unable to save file.  " + newFilename + " is open.  Please close file and try again" );
  }
}
