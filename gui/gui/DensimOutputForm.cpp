#include "StdAfx.h"
#include "DensimOutputForm.h"
#include "DensimExtOutputForm.h"
#include "ExcelOutput.h"
#include "../objs/Util.h"

using namespace gui;
using namespace boost::gregorian;
using namespace Dundas::Charting::WinControl;

typedef System::Collections::Generic::Dictionary<System::String^,Dundas::Charting::WinControl::Series^> OutputSeries;
typedef System::Collections::Generic::Dictionary<System::String^,OutputSeries^> ContainerOutputSeries;
typedef System::Collections::Generic::Dictionary<int,OutputSeries^> SerotypeOutputSeries;



DensimOutputForm::DensimOutputForm( gui::Location ^ location )
: Location_(location),
  SimOutput_(location->DensimData)
{
	InitializeComponent();

  date_period outputDates = SimOutput_->GetDateRange();
  this->BeginDate_ = new date( outputDates.begin() );
  this->EndDate_ = new date( outputDates.end() );
  this->CurDate_ = new date( *BeginDate_ );

  chartMainPlot->ChartAreas["Default"]->AxisX->Minimum = ToDateTime(*BeginDate_).ToOADate();
  chartMainPlot->ChartAreas["Default"]->AxisX->Maximum = ToDateTime(*EndDate_).ToOADate();
  chartMainPlot->ChartAreas["Default"]->AxisY->Minimum = 0;
  chartMainPlot->ChartAreas["Default"]->AxisY->Maximum= 1;

  Series ^ initialAgeDistr = gcnew Series( "Initial Age Distribution" );
  initialAgeDistr->Type = SeriesChartType::Column;
  this->Location_->DensimSeries_[initialAgeDistr->Name] = initialAgeDistr;

  Series ^ finalAgeDistr = gcnew Series( "Final Age Distribution" );
  finalAgeDistr->Type = SeriesChartType::Column;
  this->Location_->DensimSeries_[finalAgeDistr->Name] = finalAgeDistr;

  Series ^ popSize= gcnew Series( "Population Size" );
  popSize->Type = SeriesChartType::Line;
  this->Location_->DensimSeries_[popSize->Name] = popSize;

  Series ^ births = gcnew Series( "Births By Class" );
  births->Type = SeriesChartType::Column;
  this->Location_->DensimSeries_[births->Name] = births;

  Series ^ deaths = gcnew Series( "Deaths By Class" );
  deaths->Type = SeriesChartType::Column;
  this->Location_->DensimSeries_[deaths->Name] = deaths;

  Series ^ birthPercentages = gcnew Series( "Birth Percentages By Class" );
  birthPercentages->Type = SeriesChartType::Column;
  this->Location_->DensimSeries_[birthPercentages->Name] = birthPercentages;

  Series ^ deathPercentages = gcnew Series( "Death Percentages By Class" );
  deathPercentages->Type = SeriesChartType::Column;
  this->Location_->DensimSeries_[deathPercentages->Name] = deathPercentages;

  Series ^ simArea = gcnew Series( "Simulation Area" );
  simArea->Type = SeriesChartType::Line;
  this->Location_->DensimSeries_[simArea->Name] = simArea;

  Series ^ femalesSimArea = gcnew Series( "Female Mosquitoes In Simulation Area" );
  femalesSimArea->Type = SeriesChartType::Line;
  this->Location_->DensimSeries_[femalesSimArea->Name] = femalesSimArea;

  Series ^ femalesHectare = gcnew Series( "Female Mosquitoes Per Hectare" );
  femalesHectare->Type = SeriesChartType::Line;
  this->Location_->DensimSeries_[femalesHectare->Name] = femalesHectare;

  Series ^ femaleSurvival = gcnew Series( "Female Mosquito Survival" );
  femaleSurvival->Type = SeriesChartType::Line;
  this->Location_->DensimSeries_[femaleSurvival->Name] = femaleSurvival;

  Series ^ femaleWetWeight = gcnew Series( "Female Mosquito Wet Weight" );
  femaleWetWeight->Type = SeriesChartType::Line;
  this->Location_->DensimSeries_[femaleWetWeight->Name] = femaleWetWeight;

  Series ^ femalesPerPerson = gcnew Series( "Female Mosquitoes Per Person" );
  femalesPerPerson->Type = SeriesChartType::Line;
  this->Location_->DensimSeries_[femalesPerPerson->Name] = femalesPerPerson;

  Series ^ potentiallyInfvBites = gcnew Series( "Potentially Infective Bites" );
  potentiallyInfvBites->Type = SeriesChartType::Line;
  this->Location_->DensimSeries_[potentiallyInfvBites->Name] = potentiallyInfvBites;

  for( int serotype = 1; serotype <= 4; ++serotype ) {
    Location_->SerotypeSeries_->Add( serotype, gcnew OutputSeries() );

    this->Location_->SerotypeSeries_[serotype]["Incubating"] = gcnew Series( "Incubating - Dengue " + serotype );
    this->Location_->SerotypeSeries_[serotype]["Incubating"]->Type = SeriesChartType::Line;
    
    this->Location_->SerotypeSeries_[serotype]["Viremic"] = gcnew Series( "Viremic - Dengue " + serotype );
    this->Location_->SerotypeSeries_[serotype]["Viremic"]->Type = SeriesChartType::Line;

    this->Location_->SerotypeSeries_[serotype]["Infective Mosquitoes"] = gcnew Series( "Infective Mosquitoes - Dengue" + serotype );
    this->Location_->SerotypeSeries_[serotype]["Infective Mosquitoes"]->Type = SeriesChartType::Line;

    this->Location_->SerotypeSeries_[serotype]["EIP Development Rate"] = gcnew Series( "EIP Development Rate - Dengue " + serotype );
    this->Location_->SerotypeSeries_[serotype]["EIP Development Rate"]->Type = SeriesChartType::Line;
  }
}



DensimOutputForm::~DensimOutputForm()
{
  if( components ) {
		delete components;
	}
}



void
DensimOutputForm::AddData( Object ^ sender, EventArgs ^ e)
{
  // starting from current date, plot (at most) the specified number of days up to end date of simulation
  date firstDate = *CurDate_;
  date lastDate = ((*CurDate_) + days(NUM_DAYS_TO_PLOT-1)) > *EndDate_ ? *EndDate_ : (*CurDate_) + days(NUM_DAYS_TO_PLOT-1);

  day_iterator itDate = day_iterator( firstDate );
  for( ; itDate <= lastDate; ++itDate ) {
    DateTime dt = ToDateTime( *itDate );
    int numHumans = SimOutput_->GetNumberOfHumans(*itDate);
    double numHectares = numHumans / Location_->Demographics->HumanHostDensity;
    double numFemales = SimOutput_->GetMosqTotal(*itDate);
    sim::output::DailyMosData & dmd = Location_->MosData->GetMosData( *itDate );

    // graph series
    chartMainPlot->Series["Virus - Dengue 1"]->Points->AddXY( dt, SimOutput_->GetDengue1Virus(*itDate) / numHumans );
    chartMainPlot->Series["Virus - Dengue 2"]->Points->AddXY( dt, SimOutput_->GetDengue2Virus(*itDate) / numHumans );
    chartMainPlot->Series["Virus - Dengue 3"]->Points->AddXY( dt, SimOutput_->GetDengue3Virus(*itDate) / numHumans );
    chartMainPlot->Series["Virus - Dengue 4"]->Points->AddXY( dt, SimOutput_->GetDengue4Virus(*itDate) / numHumans );

    Location_->DensimSeries_["Population Size"]->Points->AddXY( dt, numHumans );
    Location_->DensimSeries_["Simulation Area"]->Points->AddXY( dt, numHectares);

    Location_->SerotypeSeries_[1]["Incubating"]->Points->AddXY( dt, SimOutput_->GetDengue1Incubating(*itDate) / numHumans );
    Location_->SerotypeSeries_[2]["Incubating"]->Points->AddXY( dt, SimOutput_->GetDengue2Incubating(*itDate) / numHumans );
    Location_->SerotypeSeries_[3]["Incubating"]->Points->AddXY( dt, SimOutput_->GetDengue3Incubating(*itDate) / numHumans );
    Location_->SerotypeSeries_[4]["Incubating"]->Points->AddXY( dt, SimOutput_->GetDengue4Incubating(*itDate) / numHumans );

    Location_->SerotypeSeries_[1]["Viremic"]->Points->AddXY( dt, SimOutput_->GetDengue1Viremic(*itDate) / numHumans );
    Location_->SerotypeSeries_[2]["Viremic"]->Points->AddXY( dt, SimOutput_->GetDengue2Viremic(*itDate) / numHumans );
    Location_->SerotypeSeries_[3]["Viremic"]->Points->AddXY( dt, SimOutput_->GetDengue3Viremic(*itDate) / numHumans );
    Location_->SerotypeSeries_[4]["Viremic"]->Points->AddXY( dt, SimOutput_->GetDengue4Viremic(*itDate) / numHumans );

    Location_->SerotypeSeries_[1]["Infective Mosquitoes"]->Points->AddXY( dt, SimOutput_->GetDengue1InfectiveMosquitoes(*itDate) );
    Location_->SerotypeSeries_[2]["Infective Mosquitoes"]->Points->AddXY( dt, SimOutput_->GetDengue2InfectiveMosquitoes(*itDate) );
    Location_->SerotypeSeries_[3]["Infective Mosquitoes"]->Points->AddXY( dt, SimOutput_->GetDengue3InfectiveMosquitoes(*itDate) );
    Location_->SerotypeSeries_[4]["Infective Mosquitoes"]->Points->AddXY( dt, SimOutput_->GetDengue4InfectiveMosquitoes(*itDate) );

    Location_->SerotypeSeries_[1]["EIP Development Rate"]->Points->AddXY( dt, SimOutput_->GetDengue1EipDevelopmentRate(*itDate) );
    Location_->SerotypeSeries_[2]["EIP Development Rate"]->Points->AddXY( dt, SimOutput_->GetDengue2EipDevelopmentRate(*itDate) );
    Location_->SerotypeSeries_[3]["EIP Development Rate"]->Points->AddXY( dt, SimOutput_->GetDengue3EipDevelopmentRate(*itDate) );
    Location_->SerotypeSeries_[4]["EIP Development Rate"]->Points->AddXY( dt, SimOutput_->GetDengue4EipDevelopmentRate(*itDate) );

    Location_->DensimSeries_["Female Mosquitoes In Simulation Area"]->Points->AddXY( dt, numFemales );
    Location_->DensimSeries_["Female Mosquitoes Per Hectare"]->Points->AddXY( dt, numFemales / numHectares );
    Location_->DensimSeries_["Female Mosquito Survival"]->Points->AddXY( dt, dmd.OverallSurvival );
    Location_->DensimSeries_["Female Mosquito Wet Weight"]->Points->AddXY( dt, dmd.AverageWeight );
    Location_->DensimSeries_["Female Mosquitoes Per Person"]->Points->AddXY( dt, numFemales / numHumans );

    Location_->DensimSeries_["Potentially Infective Bites"]->Points->AddXY( dt, SimOutput_->GetPotentiallyInfectiveBites(*itDate) );
  }

  // update for next timer call and force chart redraw
  *CurDate_ = *itDate;
  chartMainPlot->Invalidate();

  // if done, disable this timer, save series, and allow user interaction
  if( lastDate == *EndDate_ ) {
    this->timerAddData->Enabled = false;

    // save graph series
    this->Location_->SerotypeSeries_[1]["Virus"] = chartMainPlot->Series["Virus - Dengue 1"];
    this->Location_->SerotypeSeries_[2]["Virus"] = chartMainPlot->Series["Virus - Dengue 2"];
    this->Location_->SerotypeSeries_[3]["Virus"] = chartMainPlot->Series["Virus - Dengue 3"];
    this->Location_->SerotypeSeries_[4]["Virus"] = chartMainPlot->Series["Virus - Dengue 4"];


    std::vector<int> & initAgeDistr = SimOutput_->GetInitialAgeDsitribution();
    std::vector<int> & finalAgeDistr = SimOutput_->GetFinalAgeDsitribution();
    std::vector<int> & birthsByClass = SimOutput_->GetBirths();
    std::vector<int> & deathsByClass = SimOutput_->GetDeaths();

    int totalBirths = 0;
    int totalDeaths = 0;

    for( int i = 1; i <= 18; ++i ) {
      totalBirths += birthsByClass[i];
      totalDeaths += deathsByClass[i];
    }

    // calculate percentage by class
    for( int i = 1; i <= 18; ++i ) {
      this->Location_->DensimSeries_["Initial Age Distribution"]->Points->AddXY( i, initAgeDistr[i] );
      this->Location_->DensimSeries_["Final Age Distribution"]->Points->AddXY( i, finalAgeDistr[i] );
      this->Location_->DensimSeries_["Births By Class"]->Points->AddXY( i, birthsByClass[i] );
      this->Location_->DensimSeries_["Deaths By Class"]->Points->AddXY( i, deathsByClass[i] );
      this->Location_->DensimSeries_["Birth Percentages By Class"]->Points->AddXY( i, (double) birthsByClass[i] / (double) totalBirths );
      this->Location_->DensimSeries_["Death Percentages By Class"]->Points->AddXY( i, (double) deathsByClass[i] / (double) totalDeaths );
    }

    this->btnMore->Enabled = true;
    this->btnExit->Enabled = true;
    this->btnSave->Enabled = true;
    this->btnSaveAll->Enabled = true;

    // all unmanaged data now in managed data
    delete SimOutput_;
  }
}



System::Void
DensimOutputForm::OnMore( System::Object ^ sender, System::EventArgs ^ e )
{
  DensimExtOutputForm ^ deof = gcnew DensimExtOutputForm( Location_, ToDateTime(*BeginDate_), ToDateTime(*EndDate_) );
  deof->ShowDialog(this);
  deof->Close();
}



System::Void
DensimOutputForm::OnSave(System::Object^  sender, System::EventArgs^  e)
{
  // save current chart to disk
  SaveFileDialog ^ sfd = gcnew SaveFileDialog();
  sfd->InitialDirectory = Environment::CurrentDirectory;
  sfd->FileName = "DENSiM - Main Graph - " + Location_->Name + ".xml";

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
    Diagnostics::Debug::WriteLine( ioe->ToString() );
    MessageBox::Show( "Unable to save files.  " + newFilename + " is open.  Please close output files and try again" );
  }
}



System::Void
DensimOutputForm::OnSaveAll(System::Object^  sender, System::EventArgs^  e)
{
  // save all output to a directory
  FolderBrowserDialog ^ fbd = gcnew FolderBrowserDialog();
  if( fbd->ShowDialog() != ::DialogResult::OK ) {
    return;
  }
  String ^ directory = fbd->SelectedPath;

  // just need to create chart objects with specified series and save them all
  Dundas::Charting::WinControl::Chart ^ locationChart = gcnew Dundas::Charting::WinControl::Chart();
  locationChart->Series->Add( Location_->DensimSeries_["Population Size"] );
  locationChart->Series->Add( Location_->SerotypeSeries_[1]["Virus"] );
  locationChart->Series->Add( Location_->SerotypeSeries_[2]["Virus"] );
  locationChart->Series->Add( Location_->SerotypeSeries_[3]["Virus"] );
  locationChart->Series->Add( Location_->SerotypeSeries_[4]["Virus"] );
  locationChart->Series->Add( Location_->DensimSeries_["Female Mosquitoes Per Hectare"] );
  locationChart->Series->Add( Location_->DensimSeries_["Female Mosquito Survival"] );
  locationChart->Series->Add( Location_->DensimSeries_["Female Mosquito Wet Weight"] );
  locationChart->Series->Add( Location_->DensimSeries_["Female Mosquitoes Per Person"] );
  locationChart->Series->Add( Location_->DensimSeries_["Potentially Infective Bites"] );

  String ^ locationFile = directory + "\\DENSiM - Location Totals - " + Location_->Name + ".xml";
  try {
    System::IO::StreamWriter ^ sw = gcnew System::IO::StreamWriter( locationFile );
    sw->Write( ExcelOutput::GetXml(locationChart) );
    sw->Close();
  }
  catch( System::IO::IOException ^ ioe ) {
    Diagnostics::Debug::WriteLine( ioe->ToString() );
    MessageBox::Show( "Unable to save files.  " + locationFile + " is open.  Please close output files and try again" );
    return;
  }

  // four serotypes
  for( int i = 1; i <= 4; ++i ) {
    Dundas::Charting::WinControl::Chart ^ serotypeChart = gcnew Dundas::Charting::WinControl::Chart();
    serotypeChart->Series->Add( Location_->SerotypeSeries_[i]["Incubating"] );
    serotypeChart->Series->Add( Location_->SerotypeSeries_[i]["Viremic"] );
    serotypeChart->Series->Add( Location_->SerotypeSeries_[i]["Virus"] );
    serotypeChart->Series->Add( Location_->SerotypeSeries_[i]["Infective Mosquitoes"] );
    serotypeChart->Series->Add( Location_->SerotypeSeries_[i]["EIP Development Rate"] );

    String ^ containerFile = directory + "\\DENSiM - Dengue " + i.ToString() + ".xml";
    try {
      System::IO::StreamWriter ^ sw = gcnew System::IO::StreamWriter( containerFile );
      sw->Write( ExcelOutput::GetXml(serotypeChart) );
      sw->Close();
    }
    catch( System::IO::IOException ^ ioe ) {
      Diagnostics::Debug::WriteLine( ioe->ToString() );
      MessageBox::Show( "Unable to save files.  " + containerFile + " is open.  Please close output files and try again" );
      return;
    }
  }

  // population and age distributions
  Dundas::Charting::WinControl::Chart ^ ageDistrChart = gcnew Dundas::Charting::WinControl::Chart();
  ageDistrChart->Series->Add( Location_->DensimSeries_["Initial Age Distribution"] );
  ageDistrChart->Series->Add( Location_->DensimSeries_["Final Age Distribution"] );
  ageDistrChart->Series->Add( Location_->DensimSeries_["Births By Class"] );
  ageDistrChart->Series->Add( Location_->DensimSeries_["Deaths By Class"] );
  ageDistrChart->Series->Add( Location_->DensimSeries_["Birth Percentages By Class"] );
  ageDistrChart->Series->Add( Location_->DensimSeries_["Death Percentages By Class"] );

  String ^ ageDistrFile = directory + "\\DENSiM - Population Structure.xml";
  try {
    System::IO::StreamWriter ^ sw = gcnew System::IO::StreamWriter( ageDistrFile );
    sw->Write( ExcelOutput::GetXml(ageDistrChart) );
    sw->Close();
  }
  catch( System::IO::IOException ^ ioe ) {
    Diagnostics::Debug::WriteLine( ioe->ToString() );
    MessageBox::Show( "Unable to save files.  " + ageDistrFile + " is open.  Please close output files and try again" );
    return;
  }
}
