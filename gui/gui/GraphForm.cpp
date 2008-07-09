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
    output::Graph ^ graph = graphInfo->CreateGraph( location->CimsimOutput, nullptr );

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
    chartArea->AxisY->Margin = false;
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
    chart->Legends->Add( legend );

    // create series, add random data, customize, and add to chart
    for each( output::Output ^ output in graph->PrimaryOutputs ) {
      Series ^ series = gcnew Series();
      series->Name = output->Name;
      series->ChartType = graphInfo->GraphType;
      series->ChartArea = chartArea->Name;
      series->Legend = legend->Name;


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



GraphForm::GraphForm( gui::Location ^ location, output::Graph ^ graph, output::TimePeriod timePeriod, output::TimePeriodFunction timePeriodFunction )
: Location_(location),
  Container_(nullptr)
{
	InitializeComponent();

  gui::output::CimsimOutput ^ co = location->CimsimOutput;
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

  for each( output::Output ^ output in graph->PrimaryOutputs ) {
    Series ^ s = gcnew Series( output->Name );
    s->ChartType = graph->GraphInfo->GraphType;


    Collections::IEnumerable ^ data;
    if( output->GetType() == output::DatedOutput::typeid ) {
      output::DatedOutput ^ datedOutput = (output::DatedOutput^) output;
      // dated output, apply time period
      if( timePeriod == output::TimePeriod::Daily ) {
        data = datedOutput->Data;
      }
      else if( timePeriod == output::TimePeriod::Weekly ) {
        data = datedOutput->GetWeeklyData( timePeriodFunction );
      }
      else if( timePeriod == output::TimePeriod::Monthly ) {
        data = datedOutput->GetMonthlyData( co->StartDate, co->StopDate, timePeriodFunction );
      }
    }
    else {
      data = output->Data;
    }

    s->Points->DataBindXY(  dates, data );

    chart->Series->Add( s );
  }

  if( graph->SecondaryOutputs->Count > 0 ) {
    for each( output::Output ^ output in graph->SecondaryOutputs ) {
      Series ^ s = gcnew Series( output->Name );
      s->ChartType = graph->GraphInfo->GraphType;
      s->YAxisType = AxisType::Secondary;
     
      Collections::IEnumerable ^ data;
      if( output->GetType() == output::DatedOutput::typeid ) {
        output::DatedOutput ^ datedOutput = (output::DatedOutput^) output;
        // dated output, apply time period
        if( timePeriod == output::TimePeriod::Daily ) {
          data = datedOutput->Data;
        }
        else if( timePeriod == output::TimePeriod::Weekly ) {
          data = datedOutput->GetWeeklyData( timePeriodFunction );
        }
        else if( timePeriod == output::TimePeriod::Monthly ) {
          data = datedOutput->GetMonthlyData( co->StartDate, co->StopDate, timePeriodFunction );
        }
      }
      else {
        data = output->Data;
      }
      
      s->Points->DataBindXY(  co->Dates, output->Data );

      chart->Series->Add( s );
    }
  }

  // set title and x axis based on time period of summary
  chart->Title = graph->GraphInfo->Title;
  if( timePeriod == output::TimePeriod::Daily ) {
    chart->ChartAreas["Default"]->AxisX->Title = "Date";
  }
  else if( timePeriod == output::TimePeriod::Weekly ) {
    chart->Title += " - weekly averages";
    chart->ChartAreas["Default"]->AxisX->Title = "Week";
  }
  else if( timePeriod == output::TimePeriod::Monthly ) {
    chart->Title += " - monthly averages";
    chart->ChartAreas["Default"]->AxisX->Title = "Month";
  }

  chart->ChartAreas["Default"]->AxisY->Title = graph->GraphInfo->AxisY;

  // set zoom intervals
  chart->ChartAreas["Default"]->CursorX->Interval = 0;
}



GraphForm::GraphForm( gui::Location ^ location, DensimGraphType graphType )
: Location_(location),
  Container_(nullptr)
{
	InitializeComponent();

  gui::output::CimsimOutput ^ co = location->CimsimOutput;

  // setup axis
  chart->ChartAreas["Default"]->AxisX->Minimum = co->StartDate.ToOADate();
  chart->ChartAreas["Default"]->AxisX->Maximum = co->StopDate.ToOADate();

  if( graphType == DensimGraphType::InitialAgeDistribution ) {
    chart->ChartAreas["Default"]->AxisX->Minimum = 1;
    chart->ChartAreas["Default"]->AxisX->Maximum = 18;
    chart->ChartAreas["Default"]->AxisX->Interval = 1;
    chart->ChartAreas["Default"]->AxisX->IntervalType = DateTimeIntervalType::Auto;
    chart->ChartAreas["Default"]->AxisX->LabelStyle->Format = "";
    chart->ChartAreas["Default"]->AxisX->LabelStyle->IntervalType = DateTimeIntervalType::Auto;
    Series ^ initAgeDistr = Location_->DensimSeries_["Initial Age Distribution"];
    chart->Series->Add( initAgeDistr );
  }

  else if( graphType == DensimGraphType::FinalAgeDistribution ) {
    chart->ChartAreas["Default"]->AxisX->Minimum = 1;
    chart->ChartAreas["Default"]->AxisX->Maximum = 18;
    chart->ChartAreas["Default"]->AxisX->Interval = 1;
    chart->ChartAreas["Default"]->AxisX->IntervalType = DateTimeIntervalType::Auto;
    chart->ChartAreas["Default"]->AxisX->LabelStyle->Format = "";
    chart->ChartAreas["Default"]->AxisX->LabelStyle->IntervalType = DateTimeIntervalType::Auto;
    Series ^ finalAgeDistr = Location_->DensimSeries_["Final Age Distribution"];
    chart->Series->Add( finalAgeDistr );
  }

  else if( graphType == DensimGraphType::BirthsByClass ) {
    chart->ChartAreas["Default"]->AxisX->Minimum = 1;
    chart->ChartAreas["Default"]->AxisX->Maximum = 18;
    chart->ChartAreas["Default"]->AxisX->Interval = 1;
    chart->ChartAreas["Default"]->AxisX->IntervalType = DateTimeIntervalType::Auto;
    chart->ChartAreas["Default"]->AxisX->LabelStyle->Format = "";
    chart->ChartAreas["Default"]->AxisX->LabelStyle->IntervalType = DateTimeIntervalType::Auto;
    Series ^ births = Location_->DensimSeries_["Births By Class"];
    chart->Series->Add( births );
  }

  else if( graphType == DensimGraphType::DeathsByClass) {
    chart->ChartAreas["Default"]->AxisX->Minimum = 1;
    chart->ChartAreas["Default"]->AxisX->Maximum = 18;
    chart->ChartAreas["Default"]->AxisX->Interval = 1;
    chart->ChartAreas["Default"]->AxisX->IntervalType = DateTimeIntervalType::Auto;
    chart->ChartAreas["Default"]->AxisX->LabelStyle->Format = "";
    chart->ChartAreas["Default"]->AxisX->LabelStyle->IntervalType = DateTimeIntervalType::Auto;
    Series ^ deaths = Location_->DensimSeries_["Deaths By Class"];
    chart->Series->Add( deaths);
  }

  else if( graphType == DensimGraphType::BirthPercentagesByClass ) {
    chart->ChartAreas["Default"]->AxisX->Minimum = 1;
    chart->ChartAreas["Default"]->AxisX->Maximum = 18;
    chart->ChartAreas["Default"]->AxisX->Interval = 1;
    chart->ChartAreas["Default"]->AxisX->IntervalType = DateTimeIntervalType::Auto;
    chart->ChartAreas["Default"]->AxisX->LabelStyle->Format = "";
    chart->ChartAreas["Default"]->AxisX->LabelStyle->IntervalType = DateTimeIntervalType::Auto;
    Series ^ births = Location_->DensimSeries_["Birth Percentages By Class"];
    chart->Series->Add( births );
  }

  else if( graphType == DensimGraphType::DeathPercentagesByClass ) {
    chart->ChartAreas["Default"]->AxisX->Minimum = 1;
    chart->ChartAreas["Default"]->AxisX->Maximum = 18;
    chart->ChartAreas["Default"]->AxisX->Interval = 1;
    chart->ChartAreas["Default"]->AxisX->IntervalType = DateTimeIntervalType::Auto;
    chart->ChartAreas["Default"]->AxisX->LabelStyle->Format = "";
    chart->ChartAreas["Default"]->AxisX->LabelStyle->IntervalType = DateTimeIntervalType::Auto;
    Series ^ deaths = Location_->DensimSeries_["Death Percentages By Class"];
    chart->Series->Add( deaths);
  }

  if( graphType == DensimGraphType::PopulationSize ) {
    Series ^ popSize = Location_->DensimSeries_["Population Size"];
    chart->Series->Add( popSize );
  }

  else if( graphType == DensimGraphType::SimulationArea ) {
    Series ^ simArea = Location_->DensimSeries_["Simulation Area"];
    chart->Series->Add( simArea );
  }

  else if( graphType == DensimGraphType::PersonsIncubating ) {
    chart->ChartAreas["Default"]->AxisY->Minimum = 0;
    chart->ChartAreas["Default"]->AxisY->Maximum= 1;

    Series ^ d1 = Location_->SerotypeSeries_[1]["Incubating"];
    Series ^ d2 = Location_->SerotypeSeries_[2]["Incubating"];
    Series ^ d3 = Location_->SerotypeSeries_[3]["Incubating"];
    Series ^ d4 = Location_->SerotypeSeries_[4]["Incubating"];

    chart->Series->Add( d1 );
    chart->Series->Add( d2 );
    chart->Series->Add( d3 );
    chart->Series->Add( d4 );
  }

  else if( graphType == DensimGraphType::PersonsViremic ) {
    chart->ChartAreas["Default"]->AxisY->Minimum = 0;
    chart->ChartAreas["Default"]->AxisY->Maximum= 1;

    Series ^ d1 = Location_->SerotypeSeries_[1]["Viremic"];
    Series ^ d2 = Location_->SerotypeSeries_[2]["Viremic"];
    Series ^ d3 = Location_->SerotypeSeries_[3]["Viremic"];
    Series ^ d4 = Location_->SerotypeSeries_[4]["Viremic"];

    chart->Series->Add( d1 );
    chart->Series->Add( d2 );
    chart->Series->Add( d3 );
    chart->Series->Add( d4 );
  }

  else if( graphType == DensimGraphType::PersonsWithVirus ) {
    chart->ChartAreas["Default"]->AxisY->Minimum = 0;
    chart->ChartAreas["Default"]->AxisY->Maximum= 1;

    Series ^ d1 = Location_->SerotypeSeries_[1]["Virus"];
    Series ^ d2 = Location_->SerotypeSeries_[2]["Virus"];
    Series ^ d3 = Location_->SerotypeSeries_[3]["Virus"];
    Series ^ d4 = Location_->SerotypeSeries_[4]["Virus"];

    chart->Series->Add( d1 );
    chart->Series->Add( d2 );
    chart->Series->Add( d3 );
    chart->Series->Add( d4 );
  }

  else if( graphType == DensimGraphType::FemaleMosquitoesInSimulationArea ) {
    Series ^ s = Location_->DensimSeries_["Female Mosquitoes In Simulation Area"];
    chart->Series->Add(s);
  }

  else if( graphType == DensimGraphType::FemaleMosquitoesPerHectare ) {
    Series ^ s = Location_->DensimSeries_["Female Mosquitoes Per Hectare"];
    chart->Series->Add(s);
  }

  else if( graphType == DensimGraphType::FemaleMosquitoSurvival ) {
    Series ^ s = Location_->DensimSeries_["Female Mosquito Survival"];
    chart->Series->Add(s);
  }

  else if( graphType == DensimGraphType::FemaleMosquitoWetWeight ) {
    Series ^ s = Location_->DensimSeries_["Female Mosquito Wet Weight"];
    chart->Series->Add(s);
  }

  else if( graphType == DensimGraphType::FemaleMosquitoesPerPerson ) {
    Series ^ s = Location_->DensimSeries_["Female Mosquitoes Per Person"];
    chart->Series->Add(s);
  }

  else if( graphType == DensimGraphType::PotentiallyInfectiveBites ) {
    Series ^ s = Location_->DensimSeries_["Potentially Infective Bites"];
    chart->Series->Add(s);
  }

  else if( graphType == DensimGraphType::InfectiveMosquitoes ) {
    Series ^ d1 = Location_->SerotypeSeries_[1]["Infective Mosquitoes"];
    Series ^ d2 = Location_->SerotypeSeries_[2]["Infective Mosquitoes"];
    Series ^ d3 = Location_->SerotypeSeries_[3]["Infective Mosquitoes"];
    Series ^ d4 = Location_->SerotypeSeries_[4]["Infective Mosquitoes"];
 
    chart->Series->Add( d1 );
    chart->Series->Add( d2 );
    chart->Series->Add( d3 );
    chart->Series->Add( d4 );
  }

  else if( graphType == DensimGraphType::EipDevelopmentRate ) {
    Series ^ d1 = Location_->SerotypeSeries_[1]["EIP Development Rate"];
    Series ^ d2 = Location_->SerotypeSeries_[2]["EIP Development Rate"];
    Series ^ d3 = Location_->SerotypeSeries_[3]["EIP Development Rate"];
    Series ^ d4 = Location_->SerotypeSeries_[4]["EIP Development Rate"];
 
    chart->Series->Add( d1 );
    chart->Series->Add( d2 );
    chart->Series->Add( d3 );
    chart->Series->Add( d4 );
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
