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



CimsimOutputForm::CimsimOutputForm( gui::Location ^ location )
: _location(location)
{
	InitializeComponent();
  gui::output::CimsimOutput ^ co = _location->CimsimOutput;

  Collections::Generic::List<output::Output^> ^ outputs = gcnew Collections::Generic::List<output::Output^>();
  outputs->Add( co->Location[output::OutputInfos::CimsimLocation::TotalEggs] );
  outputs->Add( co->Location[output::OutputInfos::CimsimLocation::TotalLarvae] );
  outputs->Add( co->Location[output::OutputInfos::CimsimLocation::TotalPupae] );
  outputs->Add( co->Location[output::OutputInfos::CimsimLocation::TotalFemales] );

  for each( output::DatedOutput ^ output in outputs ) {
    Series ^ s = gcnew Series( output->Name );
    s->ChartType = "Line";
    s->YAxisType = AxisType::Primary;

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
  String ^ directory = fbd->SelectedPath;

  String ^ locationFile = directory + "\\CIMSiM - Location Totals - " + _location->Name + ".xml";
  try {
    System::IO::StreamWriter ^ sw = gcnew System::IO::StreamWriter( locationFile );
    sw->Write( _location->CimsimOutput->GetLocationExcelXml() );
    sw->Close();
  }
  catch( System::IO::IOException ^ ioe ) {
    Diagnostics::Debug::WriteLine( ioe->ToString() );
    MessageBox::Show( "Unable to save files.  " + locationFile + " is open.  Please close output files and try again" );
    return;
  }

  for each( gui::Container ^ c in _location->Containers ) {
    String ^ containerFile = directory + "\\CIMSiM - " + c->Name + ".xml";
    try {
      System::IO::StreamWriter ^ sw = gcnew System::IO::StreamWriter( containerFile );
      sw->Write( _location->CimsimOutput->GetContainerExcelXml(c->Id) );
      sw->Close();
    }
    catch( System::IO::IOException ^ ioe ) {
      Diagnostics::Debug::WriteLine( ioe->ToString() );
      MessageBox::Show( "Unable to save files.  " + containerFile + "is currently open.  Please close output files and try again" );
      return;
    }
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
