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

  ChartArea ^ ca = chartOutput->ChartAreas[0];
  //ca->AxisY->Minimum = 0.0;
  //ca->AxisY->Maximum = 1.0;
  ca->CursorY->Interval = (ca->AxisY->Maximum - ca->AxisY->Minimum) / 100.0;

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
  // save all output to a directory
  FolderBrowserDialog ^ fbd = gcnew FolderBrowserDialog();
  fbd->SelectedPath = Environment::CurrentDirectory;
  if( fbd->ShowDialog() != ::DialogResult::OK ) {
    return;
  }
  IO::DirectoryInfo ^ di = gcnew IO::DirectoryInfo( fbd->SelectedPath );

  try {
    _location->DensimOutput->SaveToDisk( di );
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
