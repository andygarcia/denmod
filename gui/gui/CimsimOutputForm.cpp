#include "StdAfx.h"
#include "CimsimOutputForm.h"
#include "CimsimExtOutputForm.h"
#include "ExcelOutput.h"
#include "../objs/Util.h"

using namespace gui;
using namespace boost::gregorian;
using namespace Dundas::Charting::WinControl;

typedef System::Collections::Generic::Dictionary<System::String^,Dundas::Charting::WinControl::Series^> OutputSeries;
typedef System::Collections::Generic::Dictionary<System::String^,OutputSeries^> ContainerOutputSeries;
typedef System::Collections::Generic::Dictionary<int,OutputSeries^> SerotypeOutputSeries;



CimsimOutputForm::CimsimOutputForm( gui::Location ^ location )
: _location(location)
{
	InitializeComponent();
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
  gui::output::CimsimOutput ^ co = _location->CimsimOutput;

  chartMainPlot->Series["Eggs"]->Points->DataBindXY( co->Weeks, co->Location[(int)gui::output::OutputTypes::Cimsim::Location::TotalEggs]->GetWeeklyData( output::TimePeriodFunction::Average ) );
  chartMainPlot->Series["Larvae"]->Points->DataBindXY( co->Weeks, co->Location[(int)gui::output::OutputTypes::Cimsim::Location::TotalLarvae]->GetWeeklyData( output::TimePeriodFunction::Average ));
  chartMainPlot->Series["Pupae"]->Points->DataBindXY( co->Weeks, co->Location[(int)gui::output::OutputTypes::Cimsim::Location::TotalPupae]->GetWeeklyData( output::TimePeriodFunction::Average ));
  chartMainPlot->Series["Females"]->Points->DataBindXY( co->Weeks, co->Location[(int)gui::output::OutputTypes::Cimsim::Location::TotalFemales]->GetWeeklyData( output::TimePeriodFunction::Average ));
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
    sw->Write( ExcelOutput::GetXml(chartMainPlot) );
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
  //// save all output to a directory
  //FolderBrowserDialog ^ fbd = gcnew FolderBrowserDialog();
  //if( fbd->ShowDialog() != ::DialogResult::OK ) {
  //  return;
  //}
  //String ^ directory = fbd->SelectedPath;

  //// just need to create chart objects with specified series and save them all
  //Dundas::Charting::WinControl::Chart ^ locationChart = gcnew Dundas::Charting::WinControl::Chart();
  //locationChart->Series->Add( _location->CimsimSeries_["Eggs"] );
  //locationChart->Series->Add( _location->CimsimSeries_["Larvae"] );
  //locationChart->Series->Add( _location->CimsimSeries_["Pupae"] );
  //locationChart->Series->Add( _location->CimsimSeries_["Total Females"] );
  //locationChart->Series->Add( _location->CimsimSeries_["New Females"] );
  //locationChart->Series->Add( _location->CimsimSeries_["Average Female Weight"] );
  //locationChart->Series->Add( _location->CimsimSeries_["Oviposition"] );

  //String ^ locationFile = directory + "\\CIMSiM - Location Totals - " + _location->Name + ".xml";
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

  //for each( gui::Container ^ c in _location->Containers ) {
  //  Dundas::Charting::WinControl::Chart ^ containerChart = gcnew Dundas::Charting::WinControl::Chart();
  //  containerChart->Series->Add( _location->ContainerSeries_[c->Name]["Depth"] );
  //  containerChart->Series->Add( _location->ContainerSeries_[c->Name]["Food"] );
  //  containerChart->Series->Add( _location->ContainerSeries_[c->Name]["Maximum Temperature"] );
  //  containerChart->Series->Add( _location->ContainerSeries_[c->Name]["Minimum Temperature"] );
  //  containerChart->Series->Add( _location->ContainerSeries_[c->Name]["Eggs"] );
  //  containerChart->Series->Add( _location->ContainerSeries_[c->Name]["Larvae"] );
  //  containerChart->Series->Add( _location->ContainerSeries_[c->Name]["Pupae"] );
  //  containerChart->Series->Add( _location->ContainerSeries_[c->Name]["Average Pupal Weight"] );
  //  containerChart->Series->Add( _location->ContainerSeries_[c->Name]["New Females"] );
  //  containerChart->Series->Add( _location->ContainerSeries_[c->Name]["Cumulative Females"] );
  //  containerChart->Series->Add( _location->ContainerSeries_[c->Name]["Oviposition"] );
  //  containerChart->Series->Add( _location->ContainerSeries_[c->Name]["Untreated Density"] );
  //  containerChart->Series->Add( _location->ContainerSeries_[c->Name]["Treated Density"] );
  //  containerChart->Series->Add( _location->ContainerSeries_[c->Name]["Excluded Density"] );

  //  String ^ containerFile = directory + "\\CIMSiM - " + c->Name + ".xml";
  //  try {
  //    System::IO::StreamWriter ^ sw = gcnew System::IO::StreamWriter( containerFile );
  //    sw->Write( ExcelOutput::GetXml(containerChart) );
  //    sw->Close();
  //  }
  //  catch( System::IO::IOException ^ ioe ) {
  //    Diagnostics::Debug::WriteLine( ioe->ToString() );
  //    MessageBox::Show( "Unable to save files.  " + containerFile + "is currently open.  Please close output files and try again" );
  //    return;
  //  }
  //}
}
