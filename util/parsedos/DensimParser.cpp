#include "stdafx.h"
#include "DensimParser.h"
#include "ExcelOutput.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;

std::string toss( String ^ s );



static
DensimParser::DensimParser(void)
{
  _locationFilenames = gcnew List<String^>();
  _locationFilenames->Add( "SIMAREA.PRN" );
  _locationFilenames->Add( "MOSQ.PRN" );
  _locationFilenames->Add( "MOSQPERS.PRN" );
  _locationFilenames->Add( "MOSQWT.PRN" );
  _locationFilenames->Add( "MOSQSURV.PRN" );
  _locationFilenames->Add( "INFVBITE.PRN" );
}



DensimParser::DensimParser( DirectoryInfo ^ inputDirectory)
: _inputDirectory(inputDirectory),
  _parseCompleted(false),
  _locationFiles(gcnew List<LocationFile^>()),
  _demographics(gcnew Demographics()),
  _initialSerology(gcnew Serology()),
  _finalSerology(gcnew Serology()),
  _serotypes(gcnew Dictionary<int,Serotype^>(4))
{
  for( int i = 1; i <= 4; ++i ) {
    _serotypes[i] = gcnew Serotype();
  }
}



DensimParser::~DensimParser(void)
{}



void
DensimParser::Parse(void)
{
  ParseDemographics();
  ParseSerology();
  ParseLocation();
  ParseSerotypes();
}



void
DensimParser::ParseDemographics(void)
{
  // first parse age.dem
  StreamReader ^ sr = gcnew StreamReader( Path::Combine(_inputDirectory->FullName, "AGE.DEM") );

  // local variables for parsing
  String ^ s;
  String ^ headerDelim = "-";
  String ^ dataDelim = " ,";
  array<String ^> ^ entries;


  // read and discard four rows of headers
  sr->ReadLine();
  sr->ReadLine();
  sr->ReadLine();
  sr->ReadLine();


  // read 18 rows of initial data
  for( int i = 0; i < 18; ++i ) {
    s = sr->ReadLine();
    List<String^> ^ row = gcnew List<String^>();
    entries = s->Split( dataDelim->ToCharArray(), StringSplitOptions::RemoveEmptyEntries );
    String ^ number = entries[1];
    String ^ percent = entries[2];
    _demographics->InitialDistribution->Add( number );
    _demographics->InitialDistributionPercentages->Add( percent );
  }
  
  // discard two more rows of headers
  sr->ReadLine();
  sr->ReadLine();

  // read 18 rows of final data
  for( int i = 0; i < 18; ++i ) {
    s = sr->ReadLine();
    List<String^> ^ row = gcnew List<String^>();
    entries = s->Split( dataDelim->ToCharArray(), StringSplitOptions::RemoveEmptyEntries );
    String ^ number = entries[1];
    String ^ percent = entries[2];
    _demographics->FinalDistribution->Add( number );
    _demographics->FinalDistributionPercentages->Add( percent );
  }

  sr->Close();


  // now read POPULATN.PRN
  sr = gcnew StreamReader( Path::Combine(_inputDirectory->FullName, "POPULATN.PRN") );

  // read and discard four rows of headers
  sr->ReadLine();
  sr->ReadLine();
  sr->ReadLine();
  sr->ReadLine();


  // read 18 rows of initial data
  for( int i = 0; i < 18; ++i ) {
    s = sr->ReadLine();
    List<String^> ^ row = gcnew List<String^>();
    entries = s->Split( dataDelim->ToCharArray(), StringSplitOptions::RemoveEmptyEntries );
    String ^ number = entries[1];
    String ^ percent = entries[2];
    _demographics->Births->Add( number );
    _demographics->BirthPercentages->Add( percent );
  }

  // discard two more rows of headers
  sr->ReadLine();
  sr->ReadLine();

  // read 18 rows of final data
  for( int i = 0; i < 18; ++i ) {
    s = sr->ReadLine();
    List<String^> ^ row = gcnew List<String^>();
    entries = s->Split( dataDelim->ToCharArray(), StringSplitOptions::RemoveEmptyEntries );
    String ^ number = entries[1];
    String ^ percent = entries[2];
    _demographics->Deaths->Add( number );
    _demographics->DeathPercentages->Add( percent );
  }

  sr->Close();
}



void
DensimParser::ParseSerology(void)
{
  StreamReader ^ sr = gcnew StreamReader( Path::Combine(_inputDirectory->FullName, "GENERAL.SER") );

  // local variables for parsing
  String ^ s;
  String ^ headerDelim = "-";
  String ^ dataDelim = " ,";
  array<String ^> ^ entries;


  // read and discard four rows of headers
  sr->ReadLine();
  sr->ReadLine();
  sr->ReadLine();
  sr->ReadLine();


  // read 18 rows of initial serology
  for( int i = 0; i < 18; ++i ) {
    s = sr->ReadLine();
    List<String^> ^ row = gcnew List<String^>();
    entries = s->Split( dataDelim->ToCharArray(), StringSplitOptions::RemoveEmptyEntries );
    _initialSerology->D1Number->Add( entries[1] );
    _initialSerology->D1Percent->Add( entries[2] );
    _initialSerology->D2Number->Add( entries[3] );
    _initialSerology->D2Percent->Add( entries[4] );
    _initialSerology->D3Number->Add( entries[5] );
    _initialSerology->D3Percent->Add( entries[6] );
    _initialSerology->D4Number->Add( entries[7] );
    _initialSerology->D4Percent->Add( entries[8] );
    _initialSerology->TotalInClass->Add( entries[9] );
  }
  
  // discard two more rows of headers
  sr->ReadLine();
  sr->ReadLine();

  // read 18 rows of final data
  for( int i = 0; i < 18; ++i ) {
    s = sr->ReadLine();
    List<String^> ^ row = gcnew List<String^>();
    entries = s->Split( dataDelim->ToCharArray(), StringSplitOptions::RemoveEmptyEntries );
    String ^ number = entries[1];
    String ^ percent = entries[2];
    _finalSerology->D1Number->Add( entries[1] );
    _finalSerology->D1Percent->Add( entries[2] );
    _finalSerology->D2Number->Add( entries[3] );
    _finalSerology->D2Percent->Add( entries[4] );
    _finalSerology->D3Number->Add( entries[5] );
    _finalSerology->D3Percent->Add( entries[6] );
    _finalSerology->D4Number->Add( entries[7] );
    _finalSerology->D4Percent->Add( entries[8] );
    _finalSerology->TotalInClass->Add( entries[9] );
  }

  sr->Close();
}



void
DensimParser::ParseLocation(void)
{
  // parse each location file
  for each( String ^ s in _locationFilenames ) {
    String ^ filename = Path::Combine( _inputDirectory->FullName, s );
    _locationFiles->Add( gcnew LocationFile(filename) );
  }    
}



void
DensimParser::ParseSerotypes(void)
{
  SerotypeFile ^ sf;

  // EIP
  sf = gcnew SerotypeFile( Path::Combine(_inputDirectory->FullName, "EIP.PRN") );
  for( int i = 1; i < 4; ++i ) {
    for each( String ^ s in sf->SerotypeData[i] ) {
      _serotypes[1]->EIP->Add( s );
    }
  }

  // Infective Mosquitoes
  sf = gcnew SerotypeFile( Path::Combine(_inputDirectory->FullName, "NFVMOSQ.PRN") );
  for( int i = 1; i < 4; ++i ) {
    for each( String ^ s in sf->SerotypeData[i] ) {
      _serotypes[1]->InfectiveMosquitoes->Add( s );
    }
  }

  // Persons Incubating
  sf = gcnew SerotypeFile( Path::Combine(_inputDirectory->FullName, "INCUBAT.PRN") );
  for( int i = 1; i < 4; ++i ) {
    for each( String ^ s in sf->SerotypeData[i] ) {
      _serotypes[1]->PersonsIncubating->Add( s );
    }
  }


  // Persons Viremic
  sf = gcnew SerotypeFile( Path::Combine(_inputDirectory->FullName, "VIREMIC.PRN") );
  for( int i = 1; i < 4; ++i ) {
    for each( String ^ s in sf->SerotypeData[i] ) {
      _serotypes[1]->PersonsViremic->Add( s );
    }
  }

  // Persons With Virus
  sf = gcnew SerotypeFile( Path::Combine(_inputDirectory->FullName, "WITHVIRS.PRN") );
  for( int i = 1; i < 4; ++i ) {
    for each( String ^ s in sf->SerotypeData[i] ) {
      _serotypes[1]->PersonsWithVirus->Add( s );
    }
  }

  // parse detailed serologies
  for( int i = 1; i <= 4; ++i ) {
    String ^ fileFilter = "DET" + Convert::ToString(i) + "Y#D#";
  }

}



void
DensimParser::SaveToDisk( OutputType outputType )
{

}



DensimParser::Demographics::Demographics(void)
: InitialDistribution(gcnew List<String^>()),
  InitialDistributionPercentages(gcnew List<String^>()),
  Births(gcnew List<String^>()),
  BirthPercentages(gcnew List<String^>()),
  Deaths(gcnew List<String^>()),
  DeathPercentages(gcnew List<String^>()),
  FinalDistribution(gcnew List<String^>()),
  FinalDistributionPercentages(gcnew List<String^>())
{}



DensimParser::Demographics::~Demographics(void)
{}



DensimParser::Serology::Serology(void)
: D1Number(gcnew List<String^>()),
  D1Percent(gcnew List<String^>()),
  D2Number(gcnew List<String^>()),
  D2Percent(gcnew List<String^>()),
  D3Number(gcnew List<String^>()),
  D3Percent(gcnew List<String^>()),
  D4Number(gcnew List<String^>()),
  D4Percent(gcnew List<String^>()),
  TotalInClass(gcnew List<String^>())
{}



DensimParser::Serology::~Serology(void)
{}



DensimParser::Serotype::Serotype(void)
: EIP(gcnew List<String^>()),
  InfectiveMosquitoes(gcnew List<String^>()),
  PersonsIncubating(gcnew List<String^>()),
  PersonsViremic(gcnew List<String^>()),
  PersonsWithVirus(gcnew List<String^>()),
  DetailedSerologyHeaders(gcnew List<String^>()),
  DetailedSerologyValues(gcnew List<List<String^>^>())
{}



DensimParser::Serotype::~Serotype(void)
{}
