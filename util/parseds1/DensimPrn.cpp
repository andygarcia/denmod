#include "StdAfx.h"
#include "DensimPrn.h"
#include "ExcelOutput.h"
#include <fstream>
#include <list>
#include <sstream>


using namespace System;
using namespace System::IO;
using namespace System::Text::RegularExpressions;



std::string toss( String ^ s )
{
  using Runtime::InteropServices::Marshal;
  const char* c_str = (const char*) (Marshal::StringToHGlobalAnsi(s)).ToPointer();
  std::string sstring = c_str;
  Marshal::FreeHGlobal(IntPtr((void*)c_str));
  return sstring;
}


DensimPrn::DensimPrn( String ^ directory )
{
  this->Dir_ = directory;
  Graphs_ = new std::map<int, gcroot<PrnFile^>>();
}



DensimPrn::~DensimPrn(void)
{
  delete Graphs_;
}


void DensimPrn::Parse(void)
{
  array<String^>^ dFiles = Directory::GetFiles( Dir_, "DG*" );
  array<String^>^ rFiles = Directory::GetFiles( Dir_, "RG*" );
  if( dFiles->Length > 0 && rFiles->Length > 0 ) {
    Windows::Forms::MessageBox::Show( "Both DS 1.0 and RC 1.0 output files exists.  Check directory contents." );
    return;
  }
  else if ( dFiles->Length > 0 ) {
    ParseDailyData("D");
    ParseClassData("D");
  }
  else if ( rFiles->Length > 0 ) {
    ParseDailyData("R");
    ParseClassData("R");
  }
}



void DensimPrn::Output(void)
{
  OutputMainGraph();
  OutputDemographics();
  OutputFemales();
  OutputSeroprevalence();
  OutputCaseData();
  OutputEIP();
}



void DensimPrn::ParseDailyData( String ^ prefix )
{
  array<String^>^ files = Directory::GetFiles( Dir_, prefix + "G*.PRN" );
  for each( String ^ s in files ) {
    int lastPathSep = s->LastIndexOf('\\');
    s = s->Substring( lastPathSep + 1 );

    DailyDataPrnFile ^ ddpf = gcnew DailyDataPrnFile(s);
    ddpf->Parse();

    // create graph object and add to collection
    std::pair<int , gcroot<PrnFile^>> newGraph;
    newGraph.first = ddpf->GetGraphNumber();
    newGraph.second = ddpf;
    Graphs_->insert( newGraph );
  }
}



void DensimPrn::ParseClassData( String ^ prefix )
{
  // parse .DEM, .PPL, and .SER files
  array<String^>^ demFiles = Directory::GetFiles( Dir_, prefix + "G1.DEM" );
  array<String^>^ pplFiles = Directory::GetFiles( Dir_, prefix + "G2.PPL" );
  array<String^>^ serFiles = Directory::GetFiles( Dir_, prefix + "G11.SER" );

  array<String^>^ files = gcnew array<String^>( demFiles->Length + pplFiles->Length + serFiles->Length );
  demFiles->CopyTo( files, 0 );
  pplFiles->CopyTo( files, demFiles->Length );
  serFiles->CopyTo( files, demFiles->Length + pplFiles->Length );

  for each( String ^ s in files ) {
    int lastPathSep = s->LastIndexOf('\\');
    s = s->Substring( lastPathSep + 1 );

    ClassDataPrnFile ^ cdpf = gcnew ClassDataPrnFile(s);
    cdpf->Parse();

    std::pair<int , gcroot<PrnFile^>> newGraph;
    newGraph.first = cdpf->GetGraphNumber();
    newGraph.second = cdpf;
    Graphs_->insert( newGraph );
  }
}



void DensimPrn::OutputMainGraph(void)
{
  // create headers
  std::vector<std::vector<Header>> headers(2);
  headers.at(0).push_back( Header(1, 5, 1, "Percent of population with virus") );

  headers.at(1).push_back( Header(1, 1, 1, "Day") );
  headers.at(1).push_back( Header(2, 1, 1, "Dengue 1") );
  headers.at(1).push_back( Header(3, 1, 1, "Dengue 2") );
  headers.at(1).push_back( Header(4, 1, 1, "Dengue 3") );
  headers.at(1).push_back( Header(5, 1, 1, "Dengue 4") );

  ExcelOutput * eo = new ExcelOutput( "Main Graph", 5, 365, headers );

  // demographic data is drawn from DG0
  PrnFile ^ pf = Graphs_->find(0)->second;
  DailyDataPrnFile ^ dg0 = safe_cast<DailyDataPrnFile^>(pf);
  PrnData ^ dg0Data = dg0->GetData();

  int numRows = dg0Data->GetNumRows();
  for( int i = 0; i < numRows; ++i ) {
    std::vector<std::string> newRow;
    array<String ^> ^ row = dg0Data->GetRow(i);
    for each( String ^ s in row ) {
      newRow.push_back( toss(s) );
    }
    eo->AddRow( newRow );
  }

  String ^ pfFilename = pf->GetFilename();
  String ^ mgFilename;
  if( pfFilename->StartsWith("D") )
    mgFilename = "DS 1.0 - Main Graph";
  else if ( pfFilename->StartsWith("R") )
    mgFilename = "RC 1.0 - Main Graph";

  std::ofstream mgXml(toss(mgFilename+".xml").c_str());
  mgXml<< eo->GetOutput( ExcelOutput::XML, 7 );
  mgXml.close();

  std:: ofstream mgTxt(toss(mgFilename+".txt").c_str());
  mgTxt << eo->GetOutput( ExcelOutput::ASCII, 7 );
  mgTxt.close();
  delete eo;
}



void DensimPrn::OutputDemographics(void)
{
  std::vector<std::vector<Header>> headers(3);
  headers.at(0).push_back( Header(1, 9, 1, "Demographics") );

  headers.at(1).push_back( Header(1, 1, 2, "Class") );
  headers.at(1).push_back( Header(2, 2, 1, "Initial Population") );
  headers.at(1).push_back( Header(4, 2, 1, "Total Births") );
  headers.at(1).push_back( Header(6, 2, 1, "Total Deaths") );
  headers.at(1).push_back( Header(8, 2, 1, "Final Population") );

  headers.at(2).push_back( Header(2, 1, 1, "Number") );
  headers.at(2).push_back( Header(3, 1, 1, "Percent") );
  headers.at(2).push_back( Header(4, 1, 1, "Number") );
  headers.at(2).push_back( Header(5, 1, 1, "Percent") );
  headers.at(2).push_back( Header(6, 1, 1, "Number") );
  headers.at(2).push_back( Header(7, 1, 1, "Percent") );
  headers.at(2).push_back( Header(8, 1, 1, "Number") );
  headers.at(2).push_back( Header(9, 1, 1, "Percent") );

  // output demographics spreadsheet for each year
  ExcelOutput * eo = new ExcelOutput( "Demographics", 9, 18, headers );

  // demographic data is drawn from DG1 and DG2
  PrnFile ^ pf = Graphs_->find(1)->second;
  ClassDataPrnFile ^ dg1 = safe_cast<ClassDataPrnFile^>(pf);
  pf = Graphs_->find(2)->second;
  ClassDataPrnFile ^ dg2 = safe_cast<ClassDataPrnFile^>(pf);

  for( int i = 0; i < 18; ++i ) {
    std::vector<std::string> newRow;
    newRow.push_back( toss(dg1->InitialData_[i,0]) );
    newRow.push_back( toss(dg1->InitialData_[i,1] ) );
    newRow.push_back( toss(dg1->InitialData_[i,2] ) );
    newRow.push_back( toss(dg2->InitialData_[i,1] ) );
    newRow.push_back( toss(dg2->InitialData_[i,2] ) );
    newRow.push_back( toss(dg2->FinalData_[i,1] ) );
    newRow.push_back( toss(dg2->FinalData_[i,2] ) );
    newRow.push_back( toss(dg1->FinalData_[i,1] ) );
    newRow.push_back( toss(dg1->FinalData_[i,2] ) );
    eo->AddRow( newRow );
  }

  String ^ pfFilename = pf->GetFilename();
  String ^ demFilename;
  if( pfFilename->StartsWith("D") )
    demFilename = "DS 1.0 - Demographics";
  else if( pfFilename->StartsWith("R") )
    demFilename = "RC 1.0 - Demographics";

  std::ofstream demXml(toss(demFilename + ".xml").c_str());
  demXml<< eo->GetOutput( ExcelOutput::XML, 7 );
  demXml.close();

  std:: ofstream demTxt(toss(demFilename + ".txt").c_str());
  demTxt << eo->GetOutput( ExcelOutput::ASCII, 7 );
  demTxt.close();
  delete eo;
}



void DensimPrn::OutputFemales(void)
{
  std::vector<std::vector<Header>> headers(3);
  headers.at(0).push_back( Header(1, 13, 1, "Female Adults") );

  headers.at(1).push_back( Header(1, 1, 2, "Day") );
  headers.at(1).push_back( Header(2, 1, 2, "Area (ha)") );
  headers.at(1).push_back( Header(3, 1, 2, "Fem./Area") );
  headers.at(1).push_back( Header(4, 1, 2, "Fem./ha") );
  headers.at(1).push_back( Header(5, 1, 2, "Survival") );
  headers.at(1).push_back( Header(6, 1, 2, "Development") );
  headers.at(1).push_back( Header(7, 1, 2, "Weight") );
  headers.at(1).push_back( Header(8, 1, 2, "Fem/Humans") );
  headers.at(1).push_back( Header(9, 1, 2, "Inf. Bites") );
  headers.at(1).push_back( Header(10, 4, 1, "Infective Mosquitoes (adjusted)") );

  headers.at(2).push_back( Header(10, 1, 1, "Dengue 1") );
  headers.at(2).push_back( Header(11, 1, 1, "Dengue 2") );
  headers.at(2).push_back( Header(12, 1, 1, "Dengue 3") );
  headers.at(2).push_back( Header(13, 1, 1, "Dengue 4") );

  ExcelOutput * eo = new ExcelOutput( "Female Data", 13, 365, headers );

  // mosquito data is draw from DG3, DG4, DG5, DG6, DG8, DG9, and DG13
  PrnFile ^ pf = Graphs_->find(3)->second;
  DailyDataPrnFile ^ dg3 = safe_cast<DailyDataPrnFile^>(pf);
  PrnData ^ dg3Data = dg3->GetData();
  pf = Graphs_->find(4)->second;
  DailyDataPrnFile ^ dg4 = safe_cast<DailyDataPrnFile^>(pf);
  PrnData ^ dg4Data = dg4->GetData();
  pf = Graphs_->find(5)->second;
  DailyDataPrnFile ^ dg5 = safe_cast<DailyDataPrnFile^>(pf);
  PrnData ^ dg5Data = dg5->GetData();
  pf = Graphs_->find(6)->second;
  DailyDataPrnFile ^ dg6 = safe_cast<DailyDataPrnFile^>(pf);
  PrnData ^ dg6Data = dg6->GetData();
  pf = Graphs_->find(8)->second;
  DailyDataPrnFile ^ dg8 = safe_cast<DailyDataPrnFile^>(pf);
  PrnData ^ dg8Data = dg8->GetData();
  pf = Graphs_->find(9)->second;
  DailyDataPrnFile ^ dg9 = safe_cast<DailyDataPrnFile^>(pf);
  PrnData ^ dg9Data = dg9->GetData();
  pf = Graphs_->find(13)->second;
  DailyDataPrnFile ^ dg13 = safe_cast<DailyDataPrnFile^>(pf);
  PrnData ^ dg13Data = dg13->GetData();

  int numRows = dg3Data->GetNumRows();
  for( int i = 0; i < numRows; ++i ) {
    std::vector<std::string> newRow;

    std::string day = toss( dg3Data->GetRow(i)[0] );
    std::string area = toss( dg3Data->GetRow(i)[1] );
    std::string femPerArea = toss( dg4Data->GetRow(i)[1] );
    std::string femPerHa = toss( dg4Data->GetRow(i)[2] );
    std::string femSurv = toss( dg5Data->GetRow(i)[1] );
    std::string femDev = toss( dg5Data->GetRow(i)[2] );
    std::string femWt = toss( dg8Data->GetRow(i)[1] );
    std::string femPerHum = toss( dg9Data->GetRow(i)[1] );
    std::string infBites = toss( dg13Data->GetRow(i)[1] );
    std::string den1 = toss( dg6Data->GetRow(i)[1] );
    std::string den2 = toss( dg6Data->GetRow(i)[2] );
    std::string den3 = toss( dg6Data->GetRow(i)[3] );
    std::string den4 = toss( dg6Data->GetRow(i)[4] );

    newRow.push_back( day );
    newRow.push_back( area );
    newRow.push_back( femPerArea );
    newRow.push_back( femPerHa );
    newRow.push_back( femSurv );
    newRow.push_back( femDev );
    newRow.push_back( femWt );
    newRow.push_back( femPerHum );
    newRow.push_back( infBites );
    newRow.push_back( den1 );
    newRow.push_back( den2 );
    newRow.push_back( den3 );
    newRow.push_back( den4 );

    eo->AddRow( newRow );
  }

  String ^ pfFilename = pf->GetFilename();
  String ^ femFilename;
  if( pfFilename->StartsWith("D") )
    femFilename = "DS 1.0 - Females";
  else if( pfFilename->StartsWith("R") )
    femFilename = "RC 1.0 - Females";

  std::ofstream femXml(toss(femFilename+".xml").c_str());
  femXml<< eo->GetOutput( ExcelOutput::XML, 7 );
  femXml.close();

  std:: ofstream femTxt(toss(femFilename+".txt").c_str());
  femTxt << eo->GetOutput( ExcelOutput::ASCII, 7 );
  femTxt.close();
  delete eo;
}



void DensimPrn::OutputSeroprevalence(void)
{
  std::vector<std::vector<Header>> headers(3);
  headers.at(0).push_back( Header(1, 10, 1, "Final Seroprevalence") );

  headers.at(1).push_back( Header(1, 1, 2, "Class") );
  headers.at(1).push_back( Header(2, 2, 1, "Dengue 1") );
  headers.at(1).push_back( Header(4, 2, 1, "Dengue 2") );
  headers.at(1).push_back( Header(6, 2, 1, "Dengue 3") );
  headers.at(1).push_back( Header(8, 2, 1, "Dengue 4") );
  headers.at(1).push_back( Header(10, 1, 2, "Total in Class") );

  headers.at(2).push_back( Header(2, 1, 1, "Number") );
  headers.at(2).push_back( Header(3, 1, 1, "Percent") );
  headers.at(2).push_back( Header(4, 1, 1, "Number") );
  headers.at(2).push_back( Header(5, 1, 1, "Percent") );
  headers.at(2).push_back( Header(6, 1, 1, "Number") );
  headers.at(2).push_back( Header(7, 1, 1, "Percent") );
  headers.at(2).push_back( Header(8, 1, 1, "Number") );
  headers.at(2).push_back( Header(9, 1, 1, "Percent") );

  ExcelOutput * eo = new ExcelOutput( "Final Seroprevalence", 10, 365, headers );

  // final seroprevalence is drawon from DG11
  PrnFile ^ pf = Graphs_->find(11)->second;
  ClassDataPrnFile ^ dg11 = safe_cast<ClassDataPrnFile^>(pf);

  for( int i = 0; i < 18; ++i ) {
    std::vector<std::string> newRow;
    newRow.push_back( toss(dg11->FinalData_[i,0]) );
    newRow.push_back( toss(dg11->FinalData_[i,1]) );
    newRow.push_back( toss(dg11->FinalData_[i,2]) );
    newRow.push_back( toss(dg11->FinalData_[i,3]) );
    newRow.push_back( toss(dg11->FinalData_[i,4]) );
    newRow.push_back( toss(dg11->FinalData_[i,5]) );
    newRow.push_back( toss(dg11->FinalData_[i,6]) );
    newRow.push_back( toss(dg11->FinalData_[i,7]) );
    newRow.push_back( toss(dg11->FinalData_[i,8]) );
    newRow.push_back( toss(dg11->FinalData_[i,9]) );
    eo->AddRow( newRow );
  }

  String ^ pfFilename = pf->GetFilename();
  String ^ serFilename;
  if( pfFilename->StartsWith("D") )
    serFilename = "DS 1.0 - Final Seroprevalence";
  else if( pfFilename->StartsWith("R") )
    serFilename = "RC 1.0 - Final Seroprevalence";

  std::ofstream serXml(toss(serFilename+".xml").c_str());
  serXml<< eo->GetOutput( ExcelOutput::XML, 7 );
  serXml.close();

  std:: ofstream serTxt(toss(serFilename+".txt").c_str());
  serTxt << eo->GetOutput( ExcelOutput::ASCII, 7 );
  serTxt.close();
  delete eo;
}



void DensimPrn::OutputCaseData(void)
{
  std::vector<std::vector<Header>> headers(3);
  headers.at(0).push_back( Header(1, 17, 1, "Case Data") );

  headers.at(1).push_back( Header(1, 1, 2, "Day") );
  headers.at(1).push_back( Header(2, 4, 1, "Dengue 1") );
  headers.at(1).push_back( Header(6, 4, 1, "Dengue 2") );
  headers.at(1).push_back( Header(10, 4, 1, "Dengue 3") );
  headers.at(1).push_back( Header(14, 4, 1, "Dengue 4") );

  headers.at(2).push_back( Header(2, 1, 1, "New Cases") );
  headers.at(2).push_back( Header(3, 1, 1, "Incubating") );
  headers.at(2).push_back( Header(4, 1, 1, "Viremic") );
  headers.at(2).push_back( Header(5, 1, 1, "Both") );

  headers.at(2).push_back( Header(6, 1, 1, "New Cases") );
  headers.at(2).push_back( Header(7, 1, 1, "Incubating") );
  headers.at(2).push_back( Header(8, 1, 1, "Viremic") );
  headers.at(2).push_back( Header(9, 1, 1, "Both") );

  headers.at(2).push_back( Header(10, 1, 1, "New Cases") );
  headers.at(2).push_back( Header(11, 1, 1, "Incubating") );
  headers.at(2).push_back( Header(12, 1, 1, "Viremic") );
  headers.at(2).push_back( Header(13, 1, 1, "Both") );

  headers.at(2).push_back( Header(14, 1, 1, "New Cases") );
  headers.at(2).push_back( Header(15, 1, 1, "Incubating") );
  headers.at(2).push_back( Header(16, 1, 1, "Viremic") );
  headers.at(2).push_back( Header(17, 1, 1, "Both") );

  ExcelOutput * eo = new ExcelOutput( "Case Data", 17, 365, headers );

  // case data is drawn from DG10, DG14, DG15, DG16
  PrnFile ^ pf = Graphs_->find(10)->second;
  PrnData ^ dg10Data = safe_cast<DailyDataPrnFile^>(pf)->GetData();
  pf = Graphs_->find(14)->second;
  PrnData ^ dg14Data = safe_cast<DailyDataPrnFile^>(pf)->GetData();
  pf = Graphs_->find(15)->second;
  PrnData ^ dg15Data = safe_cast<DailyDataPrnFile^>(pf)->GetData();
  pf = Graphs_->find(16)->second;
  PrnData ^ dg16Data = safe_cast<DailyDataPrnFile^>(pf)->GetData();

  int numRows = dg10Data->GetNumRows();
  for( int i = 0; i < numRows; ++i ) {
    std::vector<std::string> newRow;

    std::string day =  toss( dg16Data->GetRow(i)[0]);
    std::string den1New =  toss(dg16Data->GetRow(i)[1]);
    std::string den1Inc =  toss(dg14Data->GetRow(i)[1]);
    std::string den1Vir =  toss(dg10Data->GetRow(i)[1]);
    std::string den1Both =  toss(dg15Data->GetRow(i)[1]);
    std::string den2New =  toss(dg16Data->GetRow(i)[2]);
    std::string den2Inc =  toss(dg14Data->GetRow(i)[2]);
    std::string den2Vir =  toss(dg10Data->GetRow(i)[2]);
    std::string den2Both =  toss(dg15Data->GetRow(i)[2]);
    std::string den3New =  toss(dg16Data->GetRow(i)[3]);
    std::string den3Inc =  toss(dg14Data->GetRow(i)[3]);
    std::string den3Vir =  toss(dg10Data->GetRow(i)[3]);
    std::string den3Both =  toss(dg15Data->GetRow(i)[3]);
    std::string den4New =  toss(dg16Data->GetRow(i)[4]);
    std::string den4Inc =  toss(dg14Data->GetRow(i)[4]);
    std::string den4Vir =  toss(dg10Data->GetRow(i)[4]);
    std::string den4Both =  toss(dg15Data->GetRow(i)[4]);

    newRow.push_back( day );
    newRow.push_back( den1New );
    newRow.push_back( den1Inc );
    newRow.push_back( den1Vir );
    newRow.push_back( den1Both );
    newRow.push_back( den2New );
    newRow.push_back( den2Inc );
    newRow.push_back( den2Vir );
    newRow.push_back( den2Both );
    newRow.push_back( den3New );
    newRow.push_back( den3Inc );
    newRow.push_back( den3Vir );
    newRow.push_back( den3Both );
    newRow.push_back( den4New );
    newRow.push_back( den4Inc );
    newRow.push_back( den4Vir );
    newRow.push_back( den4Both );

    eo->AddRow( newRow );
  }

  String ^ pfFilename = pf->GetFilename();
  String ^ caseFilename;
  if( pfFilename->StartsWith("D") )
    caseFilename = "DS 1.0 - Case Data";
  else if( pfFilename->StartsWith("R") )
    caseFilename = "RC 1.0 - Case Data";

  std::ofstream caseXml(toss(caseFilename+".xml").c_str());
  caseXml<< eo->GetOutput( ExcelOutput::XML, 7 );
  caseXml.close();

  std:: ofstream caseTxt(toss(caseFilename+".txt").c_str());
  caseTxt << eo->GetOutput( ExcelOutput::ASCII, 7 );
  caseTxt.close();
  delete eo;
}



void DensimPrn::OutputEIP(void)
{
  std::vector<std::vector<Header>> headers(2);
  headers.at(0).push_back( Header(1, 5, 1, "EIP") );

  headers.at(1).push_back( Header(1, 1, 1, "Day") );
  headers.at(1).push_back( Header(2, 1, 1, "Dengue 1") );
  headers.at(1).push_back( Header(3, 1, 1, "Dengue 2") );
  headers.at(1).push_back( Header(4, 1, 1, "Dengue 3") );
  headers.at(1).push_back( Header(5, 1, 1, "Dengue 4") );

  ExcelOutput * eo = new ExcelOutput( "Case Data", 5, 365, headers );

  // EIP data is drawn from DG7
  PrnFile ^ pf = Graphs_->find(7)->second;
  PrnData ^ dg7Data = safe_cast<DailyDataPrnFile^>(pf)->GetData();

  int numRows = dg7Data->GetNumRows();
  for( int i = 0; i < numRows; ++i ) {
    std::vector<std::string> newRow;
    array<String ^> ^ row = dg7Data->GetRow(i);
    for each( String ^ s in row ) {
      newRow.push_back( toss(s) );
    }
    eo->AddRow( newRow );
  }

  String ^ pfFilename = pf->GetFilename();
  String ^ eipFilename;
  if( pfFilename->StartsWith("D") )
    eipFilename = "DS 1.0 - Case Data";
  else if( pfFilename->StartsWith("R") )
    eipFilename = "RC 1.0 - Case Data";

  std::ofstream eipXml(toss(eipFilename+".xml").c_str());
  eipXml<< eo->GetOutput( ExcelOutput::XML, 7 );
  eipXml.close();

  std:: ofstream eipTxt(toss(eipFilename+".txt").c_str());
  eipTxt << eo->GetOutput( ExcelOutput::ASCII, 7 );
  eipTxt.close();
  delete eo;
}



PrnFile::PrnFile( String ^ filename )
{
  this->Filename_ = filename;
  this->GraphNumber_ = -1;
  
  // parse graph number from filename
  Regex ^ r = gcnew Regex("G([0-9]+)");
  GraphNumber_ = Convert::ToInt32( r->Match(filename)->ToString()->Substring(1) );
}



DailyDataPrnFile::DailyDataPrnFile( String ^ filename ) : PrnFile( filename )
{
}



void DailyDataPrnFile::Parse(void)
{
  StreamReader ^ sr = gcnew StreamReader( Filename_ );
  String ^ s;
  array<String^> ^ headerDelim = {" - "};
  String ^ dataDelim = " ,";

  // read title
  Title_ = sr->ReadLine();

  // read headers
  s = sr->ReadLine();
  array<String ^> ^ strings = s->Split( headerDelim, StringSplitOptions::RemoveEmptyEntries );
  Headers_ = gcnew array<String^>(strings->Length);
  Array::Copy( strings, Headers_, strings->Length);

  // read data
  int numColumns = Headers_->Length;
  Data_ = gcnew PrnData(Headers_->Length);

  for( int i = 0; !sr->EndOfStream; i++ ) {
    s = sr->ReadLine();
    array<String ^> ^ colVals = s->Split( dataDelim->ToCharArray(), StringSplitOptions::RemoveEmptyEntries );
    for( int j = 0; j < numColumns; j++ ) {
      Data_->Add( colVals[j] );
    }
  }

  sr->Close();
}



PrnData ^ DailyDataPrnFile::GetData(void)
{
  return Data_;
}



void ClassDataPrnFile::Parse(void)
{
  StreamReader ^ sr = gcnew StreamReader( Filename_ );
  String ^ s;
  String ^ headerDelim = "--/";
  String ^ dataDelim = " ,";

  // read title and parse year
  Title_ = sr->ReadLine();
  sr->ReadLine();
  sr->ReadLine();

  // read headers
  s = sr->ReadLine();
  array<String ^> ^ strings = s->Split( headerDelim->ToCharArray(), StringSplitOptions::RemoveEmptyEntries );
  Headers_ = gcnew array<String^>(strings->Length);
  Array::Copy( strings, Headers_, strings->Length);

  // read initial data
  InitialData_ = gcnew array<String ^,2>(18,Headers_->Length);
  for( int i = 0; i < 18 && !sr->EndOfStream; i++ ) {
    s = sr->ReadLine();
    array<String ^> ^ colVals = s->Split( dataDelim->ToCharArray(), StringSplitOptions::RemoveEmptyEntries );
    for( int j = 0; j < colVals->Length; j++ ) {
      InitialData_[i,j] = colVals[j];
    }
  }

  // read final data
  sr->ReadLine();
  sr->ReadLine();
  FinalData_ = gcnew array<String ^,2>(18,Headers_->Length);
  for( int i = 0; i < 18 && !sr->EndOfStream; i++ ) {
    s = sr->ReadLine();
    array<String ^> ^ colVals = s->Split( dataDelim->ToCharArray(), StringSplitOptions::RemoveEmptyEntries );
    for( int j = 0; j < colVals->Length; j++ ) {
      FinalData_[i,j] = colVals[j];
    }
  }

  sr->Close();
}



PrnData::PrnData( int rowLength )
{
  this->RowLength_ = rowLength;
  this->Data_ = gcnew Collections::ArrayList( RowLength_ * 365 );
}



void PrnData::Add( System::String ^ s )
{
  this->Data_->Add(s);
}
  
int PrnData::GetNumRows(void)
{
  return this->Data_->Count / RowLength_;
}
  
array<String^> ^  PrnData::GetRow( int iRow )
{
  array<String^> ^ row = gcnew array<String^>(RowLength_);

  for( int i = 0; i < RowLength_; ++i ) {
    row[i] = Data_[iRow*RowLength_ + i]->ToString();
  }

  return row;
}