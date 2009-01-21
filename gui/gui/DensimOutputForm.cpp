#include "StdAfx.h"
#include "DensimOutputForm.h"
#include "DensimExtOutputForm.h"
#include "ExcelOutput.h"
#include "../objs/Util.h"

using namespace gui;
using namespace boost::gregorian;
using namespace Dundas::Charting::WinControl;



DensimOutputForm::DensimOutputForm( gui::Location ^ location )
: _location(location)
{
	InitializeComponent();
  gui::output::DensimOutput ^ dso = _location->DensimOutput;

  output::Chart ^ chart = dso->CreateChart( gcnew output::ChartInfo(output::ChartIds::DensimMain, "Proportion infected", true) );
  output::Plot ^ mainPlot = chart->Plots[0];

  for each( output::DatedOutput ^ output in mainPlot->PrimaryOutputs ) {
    Series ^ s = gcnew Series( output->Name );
    s->ChartType = "Line";
    s->YAxisType = AxisType::Primary;

    s->Points->DataBindXY( dso->Dates, output->Data );

    chartOutput->Series->Add( s );
  }

  chartOutput->ChartAreas[0]->AxisY->Minimum = 0.0;
  chartOutput->ChartAreas[0]->AxisY->Maximum = 1.0;

  chartOutput->Title = "Proportion of population with virus";
}



DensimOutputForm::~DensimOutputForm()
{
  if( components ) {
		delete components;
	}
}



System::Void
DensimOutputForm::OnLoad(System::Object^  sender, System::EventArgs^  e)
{
}



System::Void
DensimOutputForm::OnMore( System::Object ^ sender, System::EventArgs ^ e )
{
  DensimExtOutputForm ^ deof = gcnew DensimExtOutputForm( _location );
  deof->ShowDialog(this);
  deof->Close();
}



System::Void
DensimOutputForm::OnSave(System::Object^  sender, System::EventArgs^  e)
{
  // save current chart to disk
  SaveFileDialog ^ sfd = gcnew SaveFileDialog();
  sfd->InitialDirectory = Environment::CurrentDirectory;
  sfd->FileName = "DENSiM - Main Graph - " + _location->Name + ".xml";

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
    sw->Write( ExcelOutput::GetXml(chartOutput) );
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

  throw gcnew InvalidOperationException( "Not implemented." );
  //// save all output to a directory
  //FolderBrowserDialog ^ fbd = gcnew FolderBrowserDialog();
  //if( fbd->ShowDialog() != ::DialogResult::OK ) {
  //  return;
  //}
  //String ^ directory = fbd->SelectedPath;

  //// just need to create chart objects with specified series and save them all
  //Dundas::Charting::WinControl::Chart ^ locationChart = gcnew Dundas::Charting::WinControl::Chart();
  //locationChart->Series->Add( _location->DensimSeries_["Population Size"] );
  //locationChart->Series->Add( _location->SerotypeSeries_[1]["Virus"] );
  //locationChart->Series->Add( _location->SerotypeSeries_[2]["Virus"] );
  //locationChart->Series->Add( _location->SerotypeSeries_[3]["Virus"] );
  //locationChart->Series->Add( _location->SerotypeSeries_[4]["Virus"] );
  //locationChart->Series->Add( _location->DensimSeries_["Female Mosquitoes Per Hectare"] );
  //locationChart->Series->Add( _location->DensimSeries_["Female Mosquito Survival"] );
  //locationChart->Series->Add( _location->DensimSeries_["Female Mosquito Wet Weight"] );
  //locationChart->Series->Add( _location->DensimSeries_["Female Mosquitoes Per Person"] );
  //locationChart->Series->Add( _location->DensimSeries_["Potentially Infective Bites"] );

  //String ^ locationFile = directory + "\\DENSiM - Location Totals - " + _location->Name + ".xml";
  //try {
  //  System::IO::StreamWriter ^ sw = gcnew System::IO::StreamWriter( locationFile );
  //  sw->Write( ExcelOutput::GetXml(locationChart) );
  //  sw->Close();
  //}
  //catch( System::IO::IOException ^ ioe ) {
  //  Diagnostics::Debug::WriteLine( ioe->ToString() );
  //  MessageBox::Show( "Unable to save files.  " + locationFile + " is open.  Please close output files and try again" );
  //  return;
  //}

  //// four serotypes
  //for( int i = 1; i <= 4; ++i ) {
  //  Dundas::Charting::WinControl::Chart ^ serotypeChart = gcnew Dundas::Charting::WinControl::Chart();
  //  serotypeChart->Series->Add( _location->SerotypeSeries_[i]["Incubating"] );
  //  serotypeChart->Series->Add( _location->SerotypeSeries_[i]["Viremic"] );
  //  serotypeChart->Series->Add( _location->SerotypeSeries_[i]["Virus"] );
  //  serotypeChart->Series->Add( _location->SerotypeSeries_[i]["Infective Mosquitoes"] );
  //  serotypeChart->Series->Add( _location->SerotypeSeries_[i]["EIP Development Rate"] );

  //  String ^ containerFile = directory + "\\DENSiM - Dengue " + i.ToString() + ".xml";
  //  try {
  //    System::IO::StreamWriter ^ sw = gcnew System::IO::StreamWriter( containerFile );
  //    sw->Write( ExcelOutput::GetXml(serotypeChart) );
  //    sw->Close();
  //  }
  //  catch( System::IO::IOException ^ ioe ) {
  //    Diagnostics::Debug::WriteLine( ioe->ToString() );
  //    MessageBox::Show( "Unable to save files.  " + containerFile + " is open.  Please close output files and try again" );
  //    return;
  //  }
  //}

  //// population and age distributions
  //Dundas::Charting::WinControl::Chart ^ ageDistrChart = gcnew Dundas::Charting::WinControl::Chart();
  //ageDistrChart->Series->Add( _location->DensimSeries_["Initial Age Distribution"] );
  //ageDistrChart->Series->Add( _location->DensimSeries_["Final Age Distribution"] );
  //ageDistrChart->Series->Add( _location->DensimSeries_["Births By Class"] );
  //ageDistrChart->Series->Add( _location->DensimSeries_["Deaths By Class"] );
  //ageDistrChart->Series->Add( _location->DensimSeries_["Birth Percentages By Class"] );
  //ageDistrChart->Series->Add( _location->DensimSeries_["Death Percentages By Class"] );

  //String ^ ageDistrFile = directory + "\\DENSiM - Population Structure.xml";
  //try {
  //  System::IO::StreamWriter ^ sw = gcnew System::IO::StreamWriter( ageDistrFile );
  //  sw->Write( ExcelOutput::GetXml(ageDistrChart) );
  //  sw->Close();
  //}
  //catch( System::IO::IOException ^ ioe ) {
  //  Diagnostics::Debug::WriteLine( ioe->ToString() );
  //  MessageBox::Show( "Unable to save files.  " + ageDistrFile + " is open.  Please close output files and try again" );
  //  return;
  //}
}
