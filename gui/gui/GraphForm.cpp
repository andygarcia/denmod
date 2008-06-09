#include "StdAfx.h"
#include "GraphForm.h"
#include "ExcelOutput.h"

using namespace gui;
using namespace boost::gregorian;
using namespace Dundas::Charting::WinControl;



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
    s->ChartType = graph->ChartType;

    // use appropriate time scale for data
    Collections::IEnumerable ^ data;
    if( timePeriod == output::TimePeriod::Daily ) {
      data = output->Data;
    }
    else if( timePeriod == output::TimePeriod::Weekly ) {
      data = output->GetWeeklyData( timePeriodFunction );
    }
    else if( timePeriod == output::TimePeriod::Monthly ) {
      data = output->GetMonthlyData( co->StartDate, co->StopDate, timePeriodFunction );
    }
  
    s->Points->DataBindXY(  dates, data );

    chartMainPlot->Series->Add( s );
  }

  if( graph->SecondaryOutputs->Count > 0 ) {
    for each( output::Output ^ output in graph->SecondaryOutputs ) {
      Series ^ s = gcnew Series( output->Name );
      s->ChartType = graph->ChartType;
      s->YAxisType = AxisType::Secondary;
     
      Collections::IEnumerable ^ data;
      if( timePeriod == output::TimePeriod::Daily ) {
        data = output->Data;
      }
      else if( timePeriod == output::TimePeriod::Weekly ) {
        data = output->GetWeeklyData( timePeriodFunction );
      }
      else if( timePeriod == output::TimePeriod::Monthly ) {
        data = output->GetMonthlyData( co->StartDate, co->StopDate, timePeriodFunction );
      }
      
      s->Points->DataBindXY(  co->Dates, output->Data );

      chartMainPlot->Series->Add( s );
    }
  }

  // all graphs of this type are time series
  chartMainPlot->Title = graph->Title;
  if( timePeriod == output::TimePeriod::Daily ) {
    chartMainPlot->ChartAreas["Default"]->AxisX->Title = "Date";
  }
  else if( timePeriod == output::TimePeriod::Weekly ) {
    chartMainPlot->ChartAreas["Default"]->AxisX->Title = "Week";
  }
  else if( timePeriod == output::TimePeriod::Monthly ) {
    chartMainPlot->ChartAreas["Default"]->AxisX->Title = "Month";
  }

  chartMainPlot->ChartAreas["Default"]->AxisY->Title = graph->AxisY;
}



GraphForm::GraphForm( gui::Location ^ location, DensimGraphType graphType )
: Location_(location),
  Container_(nullptr)
{
	InitializeComponent();

  gui::output::CimsimOutput ^ co = location->CimsimOutput;

  // setup axis
  chartMainPlot->ChartAreas["Default"]->AxisX->Minimum = co->StartDate.ToOADate();
  chartMainPlot->ChartAreas["Default"]->AxisX->Maximum = co->StopDate.ToOADate();

  if( graphType == DensimGraphType::InitialAgeDistribution ) {
    chartMainPlot->ChartAreas["Default"]->AxisX->Minimum = 1;
    chartMainPlot->ChartAreas["Default"]->AxisX->Maximum = 18;
    chartMainPlot->ChartAreas["Default"]->AxisX->Interval = 1;
    chartMainPlot->ChartAreas["Default"]->AxisX->IntervalType = DateTimeIntervalType::Auto;
    chartMainPlot->ChartAreas["Default"]->AxisX->LabelStyle->Format = "";
    chartMainPlot->ChartAreas["Default"]->AxisX->LabelStyle->IntervalType = DateTimeIntervalType::Auto;
    Series ^ initAgeDistr = Location_->DensimSeries_["Initial Age Distribution"];
    chartMainPlot->Series->Add( initAgeDistr );
  }

  else if( graphType == DensimGraphType::FinalAgeDistribution ) {
    chartMainPlot->ChartAreas["Default"]->AxisX->Minimum = 1;
    chartMainPlot->ChartAreas["Default"]->AxisX->Maximum = 18;
    chartMainPlot->ChartAreas["Default"]->AxisX->Interval = 1;
    chartMainPlot->ChartAreas["Default"]->AxisX->IntervalType = DateTimeIntervalType::Auto;
    chartMainPlot->ChartAreas["Default"]->AxisX->LabelStyle->Format = "";
    chartMainPlot->ChartAreas["Default"]->AxisX->LabelStyle->IntervalType = DateTimeIntervalType::Auto;
    Series ^ finalAgeDistr = Location_->DensimSeries_["Final Age Distribution"];
    chartMainPlot->Series->Add( finalAgeDistr );
  }

  else if( graphType == DensimGraphType::BirthsByClass ) {
    chartMainPlot->ChartAreas["Default"]->AxisX->Minimum = 1;
    chartMainPlot->ChartAreas["Default"]->AxisX->Maximum = 18;
    chartMainPlot->ChartAreas["Default"]->AxisX->Interval = 1;
    chartMainPlot->ChartAreas["Default"]->AxisX->IntervalType = DateTimeIntervalType::Auto;
    chartMainPlot->ChartAreas["Default"]->AxisX->LabelStyle->Format = "";
    chartMainPlot->ChartAreas["Default"]->AxisX->LabelStyle->IntervalType = DateTimeIntervalType::Auto;
    Series ^ births = Location_->DensimSeries_["Births By Class"];
    chartMainPlot->Series->Add( births );
  }

  else if( graphType == DensimGraphType::DeathsByClass) {
    chartMainPlot->ChartAreas["Default"]->AxisX->Minimum = 1;
    chartMainPlot->ChartAreas["Default"]->AxisX->Maximum = 18;
    chartMainPlot->ChartAreas["Default"]->AxisX->Interval = 1;
    chartMainPlot->ChartAreas["Default"]->AxisX->IntervalType = DateTimeIntervalType::Auto;
    chartMainPlot->ChartAreas["Default"]->AxisX->LabelStyle->Format = "";
    chartMainPlot->ChartAreas["Default"]->AxisX->LabelStyle->IntervalType = DateTimeIntervalType::Auto;
    Series ^ deaths = Location_->DensimSeries_["Deaths By Class"];
    chartMainPlot->Series->Add( deaths);
  }

  else if( graphType == DensimGraphType::BirthPercentagesByClass ) {
    chartMainPlot->ChartAreas["Default"]->AxisX->Minimum = 1;
    chartMainPlot->ChartAreas["Default"]->AxisX->Maximum = 18;
    chartMainPlot->ChartAreas["Default"]->AxisX->Interval = 1;
    chartMainPlot->ChartAreas["Default"]->AxisX->IntervalType = DateTimeIntervalType::Auto;
    chartMainPlot->ChartAreas["Default"]->AxisX->LabelStyle->Format = "";
    chartMainPlot->ChartAreas["Default"]->AxisX->LabelStyle->IntervalType = DateTimeIntervalType::Auto;
    Series ^ births = Location_->DensimSeries_["Birth Percentages By Class"];
    chartMainPlot->Series->Add( births );
  }

  else if( graphType == DensimGraphType::DeathPercentagesByClass ) {
    chartMainPlot->ChartAreas["Default"]->AxisX->Minimum = 1;
    chartMainPlot->ChartAreas["Default"]->AxisX->Maximum = 18;
    chartMainPlot->ChartAreas["Default"]->AxisX->Interval = 1;
    chartMainPlot->ChartAreas["Default"]->AxisX->IntervalType = DateTimeIntervalType::Auto;
    chartMainPlot->ChartAreas["Default"]->AxisX->LabelStyle->Format = "";
    chartMainPlot->ChartAreas["Default"]->AxisX->LabelStyle->IntervalType = DateTimeIntervalType::Auto;
    Series ^ deaths = Location_->DensimSeries_["Death Percentages By Class"];
    chartMainPlot->Series->Add( deaths);
  }

  if( graphType == DensimGraphType::PopulationSize ) {
    Series ^ popSize = Location_->DensimSeries_["Population Size"];
    chartMainPlot->Series->Add( popSize );
  }

  else if( graphType == DensimGraphType::SimulationArea ) {
    Series ^ simArea = Location_->DensimSeries_["Simulation Area"];
    chartMainPlot->Series->Add( simArea );
  }

  else if( graphType == DensimGraphType::PersonsIncubating ) {
    Series ^ d1 = Location_->SerotypeSeries_[1]["Incubating"];
    Series ^ d2 = Location_->SerotypeSeries_[2]["Incubating"];
    Series ^ d3 = Location_->SerotypeSeries_[3]["Incubating"];
    Series ^ d4 = Location_->SerotypeSeries_[4]["Incubating"];

    chartMainPlot->Series->Add( d1 );
    chartMainPlot->Series->Add( d2 );
    chartMainPlot->Series->Add( d3 );
    chartMainPlot->Series->Add( d4 );
  }

  else if( graphType == DensimGraphType::PersonsViremic ) {
    Series ^ d1 = Location_->SerotypeSeries_[1]["Viremic"];
    Series ^ d2 = Location_->SerotypeSeries_[2]["Viremic"];
    Series ^ d3 = Location_->SerotypeSeries_[3]["Viremic"];
    Series ^ d4 = Location_->SerotypeSeries_[4]["Viremic"];

    chartMainPlot->Series->Add( d1 );
    chartMainPlot->Series->Add( d2 );
    chartMainPlot->Series->Add( d3 );
    chartMainPlot->Series->Add( d4 );
  }

  else if( graphType == DensimGraphType::PersonsWithVirus ) {
    Series ^ d1 = Location_->SerotypeSeries_[1]["Virus"];
    Series ^ d2 = Location_->SerotypeSeries_[2]["Virus"];
    Series ^ d3 = Location_->SerotypeSeries_[3]["Virus"];
    Series ^ d4 = Location_->SerotypeSeries_[4]["Virus"];

    chartMainPlot->Series->Add( d1 );
    chartMainPlot->Series->Add( d2 );
    chartMainPlot->Series->Add( d3 );
    chartMainPlot->Series->Add( d4 );
  }

  else if( graphType == DensimGraphType::FemaleMosquitoesInSimulationArea ) {
    Series ^ s = Location_->DensimSeries_["Female Mosquitoes In Simulation Area"];
    chartMainPlot->Series->Add(s);
  }

  else if( graphType == DensimGraphType::FemaleMosquitoesPerHectare ) {
    Series ^ s = Location_->DensimSeries_["Female Mosquitoes Per Hectare"];
    chartMainPlot->Series->Add(s);
  }

  else if( graphType == DensimGraphType::FemaleMosquitoSurvival ) {
    Series ^ s = Location_->DensimSeries_["Female Mosquito Survival"];
    chartMainPlot->Series->Add(s);
  }

  else if( graphType == DensimGraphType::FemaleMosquitoWetWeight ) {
    Series ^ s = Location_->DensimSeries_["Female Mosquito Wet Weight"];
    chartMainPlot->Series->Add(s);
  }

  else if( graphType == DensimGraphType::FemaleMosquitoesPerPerson ) {
    Series ^ s = Location_->DensimSeries_["Female Mosquitoes Per Person"];
    chartMainPlot->Series->Add(s);
  }

  else if( graphType == DensimGraphType::PotentiallyInfectiveBites ) {
    Series ^ s = Location_->DensimSeries_["Potentially Infective Bites"];
    chartMainPlot->Series->Add(s);
  }

  else if( graphType == DensimGraphType::InfectiveMosquitoes ) {
    Series ^ d1 = Location_->SerotypeSeries_[1]["Infective Mosquitoes"];
    Series ^ d2 = Location_->SerotypeSeries_[2]["Infective Mosquitoes"];
    Series ^ d3 = Location_->SerotypeSeries_[3]["Infective Mosquitoes"];
    Series ^ d4 = Location_->SerotypeSeries_[4]["Infective Mosquitoes"];
 
    chartMainPlot->Series->Add( d1 );
    chartMainPlot->Series->Add( d2 );
    chartMainPlot->Series->Add( d3 );
    chartMainPlot->Series->Add( d4 );
  }

  else if( graphType == DensimGraphType::EipDevelopmentRate ) {
    Series ^ d1 = Location_->SerotypeSeries_[1]["EIP Development Rate"];
    Series ^ d2 = Location_->SerotypeSeries_[2]["EIP Development Rate"];
    Series ^ d3 = Location_->SerotypeSeries_[3]["EIP Development Rate"];
    Series ^ d4 = Location_->SerotypeSeries_[4]["EIP Development Rate"];
 
    chartMainPlot->Series->Add( d1 );
    chartMainPlot->Series->Add( d2 );
    chartMainPlot->Series->Add( d3 );
    chartMainPlot->Series->Add( d4 );
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
  sfd->FileName = chartMainPlot->Tag + ".xml";
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
    sw->Write( ExcelOutput::GetXml(chartMainPlot) );
    sw->Close();
  }
  catch( System::IO::IOException ^ ioe ) {
    System::Console::WriteLine( ioe->ToString() );
    MessageBox::Show( "Unable to save file.  " + newFilename + " is open.  Please close file and try again" );
  }
}
