#include "StdAfx.h"
#include "CimsimOutputForm.h"
#include "CimsimExtOutputForm.h"
#include "RunDensimForm.h"
#include "DensimOutputForm.h"
#include "ExcelOutput.h"
#include "../objs/Util.h"

using namespace gui;
using namespace boost::gregorian;
using namespace Dundas::Charting::WinControl;



CimsimOutputForm::CimsimOutputForm( gui::Location ^ location, Settings ^ _userSettings )
: _location(location)
{
	InitializeComponent();
  gui::output::CimsimOutput ^ co = _location->CimsimOutput;

  // create chart depending on scale setting
  output::Chart ^ chart;
  if( _userSettings->ScaleCimsimMainGraph ) {
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

    chartOutput->Series->Add( s );
  }

  chartOutput->Title = "Total per hectare - weekly averages";

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
}



System::Void
CimsimOutputForm::OnMore( System::Object ^ sender, System::EventArgs ^ e )
{
  CimsimExtOutputForm ^ ceof = gcnew CimsimExtOutputForm( _location );
  ceof->ShowDialog(this);
  ceof->Close();
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
    sw->Write( ExcelOutput::GetXml(chartOutput) );
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
