#include "stdafx.h"
#include "DensimParser.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace util;



static
DensimParser::DensimParser(void)
{
  _classIndices = gcnew List<int>();
  for( int i = 1; i <= 18; ++i ) {
    _classIndices->Add( i );
  }
}



DensimParser::DensimParser( DirectoryInfo ^ inputDirectory)
: _inputDirectory(inputDirectory),
  _parseCompleted(false),
  _demographics(gcnew Demographics()),
  _initialSerology(gcnew Serology()),
  _finalSerology(gcnew Serology()),
  _location(gcnew Location()),
  _serotypes(gcnew Dictionary<int,Serotype^>(4)),
  _days(gcnew List<int>(365))
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
  LocationFile ^ lf;

  // simulation area
  lf = gcnew LocationFile( Path::Combine(_inputDirectory->FullName, "SIMAREA.PRN") );
  for each( String ^ s in lf->Data[lf->Headers[0]] ) {
    _location->SimulationArea->Add( s );
  }

  // female mosquitoes
  lf = gcnew LocationFile( Path::Combine(_inputDirectory->FullName, "MOSQ.PRN") );
  for each( String ^ s in lf->Data[lf->Headers[0]] ) {
    _location->MosquitoesInArea->Add( s );
  }
  for each( String ^ s in lf->Data[lf->Headers[1]] ) {
    _location->MosquitoesPerHectare->Add( s );
  }

  // mosquitoes per person
  lf = gcnew LocationFile( Path::Combine(_inputDirectory->FullName, "MOSQPERS.PRN") );
  for each( String ^ s in lf->Data[lf->Headers[0]] ) {
    _location->MosquitoesPerPerson->Add( s );
  }

  // mosquito weight
  lf = gcnew LocationFile( Path::Combine(_inputDirectory->FullName, "MOSQWT.PRN") );
  for each( String ^ s in lf->Data[lf->Headers[0]] ) {
    _location->MosquitoWetWeight->Add( s );
  }

  // mosquito survival
  lf = gcnew LocationFile( Path::Combine(_inputDirectory->FullName, "MOSQSURV.PRN") );
  for each( String ^ s in lf->Data[lf->Headers[0]] ) {
    _location->MosquitoSurvival->Add( s );
  }

  // infective bites
  lf = gcnew LocationFile( Path::Combine(_inputDirectory->FullName, "INFVBITE.PRN") );
  for each( String ^ s in lf->Data[lf->Headers[0]] ) {
    _location->InfectiveBites->Add( s );
  }
}



void
DensimParser::ParseSerotypes(void)
{
  SerotypeFile ^ sf;

  // EIP
  sf = gcnew SerotypeFile( Path::Combine(_inputDirectory->FullName, "EIP.PRN") );
  for( int i = 1; i <= 4; ++i ) {
    for each( String ^ s in sf->SerotypeData[i] ) {
      _serotypes[i]->EIP->Add( s );
    }
  }

  // Infective Mosquitoes
  sf = gcnew SerotypeFile( Path::Combine(_inputDirectory->FullName, "INFVMOSQ.PRN") );
  for( int i = 1; i <= 4; ++i ) {
    for each( String ^ s in sf->SerotypeData[i] ) {
      _serotypes[i]->InfectiveMosquitoes->Add( s );
    }
  }

  // Persons Incubating
  sf = gcnew SerotypeFile( Path::Combine(_inputDirectory->FullName, "INCUBAT.PRN") );
  for( int i = 1; i <= 4; ++i ) {
    for each( String ^ s in sf->SerotypeData[i] ) {
      _serotypes[i]->PersonsIncubating->Add( s );
    }
  }


  // Persons Viremic
  sf = gcnew SerotypeFile( Path::Combine(_inputDirectory->FullName, "VIREMIC.PRN") );
  for( int i = 1; i <= 4; ++i ) {
    for each( String ^ s in sf->SerotypeData[i] ) {
      _serotypes[i]->PersonsViremic->Add( s );
    }
  }

  // Persons With Virus
  sf = gcnew SerotypeFile( Path::Combine(_inputDirectory->FullName, "WITHVIRS.PRN") );
  for( int i = 1; i <= 4; ++i ) {
    for each( String ^ s in sf->SerotypeData[i] ) {
      _serotypes[i]->PersonsWithVirus->Add( s );
    }
  }


  // parse detailed serologies by serotype
  for( int i = 1; i <= 4; ++i ) {
    Serotype ^ serotype = _serotypes[i];

    // parse each set (1-3), using a column offset to place in correct order
    int columnOffset = 0;
    for( int j = 1; j <= 3; ++j, columnOffset +=8 ) {
      // find number of years
      String ^ filter = "DET" + j + "Y*D" + i + ".PRN";
      array<FileInfo^> ^ fis = _inputDirectory->GetFiles( filter );
      int numYears = fis->Length;

      // parse each year
      for( int k = 1; k <= numYears; ++k ) {
        String ^ yearFilename = "DET" + j + "Y" + k + "D" + i + ".PRN";
        PrnFile ^ pf = gcnew PrnFile( Path::Combine(_inputDirectory->FullName, yearFilename) );

        for each( List<String^> ^ row in pf->DataRows ) {
          for( int l = 1; l < row->Count; ++l ) {
            serotype->DetailedSerologies[l+columnOffset-1]->Add( row[l] );
          }
        }
      }
    }
  }
}



void
DensimParser::SaveToDisk( OutputType outputType )
{
  // save current working directory and change
  String ^ pwd = Environment::CurrentDirectory;
  Environment::CurrentDirectory = _inputDirectory->FullName;

  // save outputs
  OutputDemographics( outputType );
  OutputSerology( outputType );
  OutputLocation( outputType );

  // restore working directory
  Environment::CurrentDirectory = pwd;
}



void
DensimParser::OutputDemographics( OutputType ot )
{
  ExcelWorksheet ^ ews = gcnew ExcelWorksheet( "Demographics" );
  ews->AddColumn( "Class", Int32::typeid, _classIndices );
  ews->AddColumn( "Initial age distribution", Int32::typeid, _demographics->InitialDistribution );
  ews->AddColumn( "Initial percentages", Double::typeid, _demographics->InitialDistributionPercentages );
  ews->AddColumn( "Births", Int32::typeid, _demographics->Births );
  ews->AddColumn( "Birth percentages", Double::typeid, _demographics->BirthPercentages );
  ews->AddColumn( "Deaths", Int32::typeid, _demographics->Deaths );
  ews->AddColumn( "Death percentages", Double::typeid, _demographics->DeathPercentages );
  ews->AddColumn( "Final age distribution", Int32::typeid, _demographics->FinalDistribution );
  ews->AddColumn( "Final percentages", Double::typeid, _demographics->FinalDistributionPercentages );

  util::ExcelWorkbook ^ ewb = gcnew ExcelWorkbook( "DENSIM 1.0" );
  ewb->AddWorksheet( ews );
  ewb->SaveToDisk( _inputDirectory, "DS 1.0 - Demographics.xml" );

  return;
}



void
DensimParser::OutputSerology( OutputType ot )
{
  ExcelWorksheet ^ ews = gcnew ExcelWorksheet( "Serology" );
  ews->AddColumn( "Class", Int32::typeid, _classIndices );

  ews->AddColumn( "Dengue 1 Initial Distribution", Int32::typeid, _initialSerology->D1Number );
  ews->AddColumn( "Dengue 1 Initial Distribution Percentage", Double::typeid, _initialSerology->D1Percent );
  ews->AddColumn( "Dengue 2 Initial Distribution", Int32::typeid, _initialSerology->D2Number );
  ews->AddColumn( "Dengue 2 Initial Distribution Percentage", Double::typeid, _initialSerology->D2Percent );
  ews->AddColumn( "Dengue 3 Initial Distribution", Int32::typeid, _initialSerology->D3Number );
  ews->AddColumn( "Dengue 3 Initial Distribution Percentage", Double::typeid, _initialSerology->D3Percent );
  ews->AddColumn( "Dengue 4 Initial Distribution", Int32::typeid, _initialSerology->D4Number );
  ews->AddColumn( "Dengue 4 Initial Distribution Percentage", Double::typeid, _initialSerology->D4Percent );

  ews->AddColumn( "Dengue 1 Final Distribution", Int32::typeid, _finalSerology->D1Number );
  ews->AddColumn( "Dengue 1 Final Distribution Percentage", Double::typeid, _finalSerology->D1Percent );
  ews->AddColumn( "Dengue 2 Final Distribution", Int32::typeid, _finalSerology->D2Number );
  ews->AddColumn( "Dengue 2 Final Distribution Percentage", Double::typeid, _finalSerology->D2Percent );
  ews->AddColumn( "Dengue 3 Final Distribution", Int32::typeid, _finalSerology->D3Number );
  ews->AddColumn( "Dengue 3 Final Distribution Percentage", Double::typeid, _finalSerology->D3Percent );
  ews->AddColumn( "Dengue 4 Final Distribution", Int32::typeid, _finalSerology->D4Number );
  ews->AddColumn( "Dengue 4 Final Distribution Percentage", Double::typeid, _finalSerology->D4Percent );

  ExcelWorkbook ^ ewb = gcnew ExcelWorkbook( "DENSIM 1.0" );
  ewb->AddWorksheet( ews );
  ewb->SaveToDisk( _inputDirectory, "DS 1.0 - Serology.xml" );

  return;
}



void
DensimParser::OutputLocation( OutputType ot )
{
  // first create date index, similar to DS 1.0 this is a 1's index of the day and does not reset at yearly boundaries
  // this is easy to reproduce using the length of any of the lists in location data
  int numDays = _location->SimulationArea->Count;
  for( int i = 1; i <= numDays; ++i ) {
    _days->Add( i );
  }
  
  // now use days as first column in output
  ExcelWorksheet ^ ews = gcnew ExcelWorksheet( "Location" );
  ews->AddColumn( "Day", Int32::typeid, _days );
  ews->AddColumn( "Simulation Area", Double::typeid, _location->SimulationArea );
  ews->AddColumn( "Mosquitoes In Area", Double::typeid, _location->MosquitoesInArea );
  ews->AddColumn( "Mosquitoes Per Hectare", Double::typeid, _location->MosquitoesPerHectare );
  ews->AddColumn( "Mosquitoes Per Person", Double::typeid, _location->MosquitoesPerPerson );
  ews->AddColumn( "Mosquito Wet Weight", Double::typeid, _location->MosquitoWetWeight );
  ews->AddColumn( "Mosquito Survival", Double::typeid, _location->MosquitoSurvival );
  ews->AddColumn( "Infective Bites", Double::typeid, _location->InfectiveBites );

  ExcelWorkbook ^ ewb = gcnew ExcelWorkbook( "DENSIM 1.0" );
  ewb->AddWorksheet( ews );

  for( int i = 1; i <= 4; ++i ) {
    Serotype ^ serotype = _serotypes[i];

    ExcelWorksheet ^ ews = gcnew ExcelWorksheet( "Dengue " + i );
    ews->AddColumn( "Day", Int32::typeid, _days );
    ews->AddColumn( "EIP Development Rate", Double::typeid, serotype->EIP );
    ews->AddColumn( "Infective Mosquitoes", Double::typeid, serotype->InfectiveMosquitoes );
    ews->AddColumn( "Persons Incubating", Double::typeid, serotype->PersonsIncubating );
    ews->AddColumn( "Persons Viremic", Double::typeid, serotype->PersonsViremic );
    ews->AddColumn( "Persons With Virus", Double::typeid, serotype->PersonsWithVirus );
    ews->AddColumn( "MANA Infants", Double::typeid, serotype->DetailedSerologies[0] );
    ews->AddColumn( "MAEA Infants", Double::typeid, serotype->DetailedSerologies[1] );
    ews->AddColumn( "< 1 year", Double::typeid, serotype->DetailedSerologies[2] );
    ews->AddColumn( "1-4 years", Double::typeid, serotype->DetailedSerologies[3] );
    ews->AddColumn( "5-9 years", Double::typeid, serotype->DetailedSerologies[4] );
    ews->AddColumn( "10-14 years", Double::typeid, serotype->DetailedSerologies[5] );
    ews->AddColumn( "15-19 years", Double::typeid, serotype->DetailedSerologies[6] );
    ews->AddColumn( "20-24 years", Double::typeid, serotype->DetailedSerologies[7] );
    ews->AddColumn( "25-29 years", Double::typeid, serotype->DetailedSerologies[8] );
    ews->AddColumn( "30-34 years", Double::typeid, serotype->DetailedSerologies[9] );
    ews->AddColumn( "35-39 years", Double::typeid, serotype->DetailedSerologies[10] );
    ews->AddColumn( "40-44 years", Double::typeid, serotype->DetailedSerologies[11] );
    ews->AddColumn( "45-49 years", Double::typeid, serotype->DetailedSerologies[12] );
    ews->AddColumn( "50-54 years", Double::typeid, serotype->DetailedSerologies[13] );
    ews->AddColumn( "55-59 years", Double::typeid, serotype->DetailedSerologies[14] );
    ews->AddColumn( "60-64 years", Double::typeid, serotype->DetailedSerologies[15] );
    ews->AddColumn( "65-69 years", Double::typeid, serotype->DetailedSerologies[16] );
    ews->AddColumn( "70-74 years", Double::typeid, serotype->DetailedSerologies[17] );
    ews->AddColumn( "75-79 years", Double::typeid, serotype->DetailedSerologies[18] );
    ews->AddColumn( "80+ years", Double::typeid, serotype->DetailedSerologies[19] );
    ews->AddColumn( "15-44 years", Double::typeid, serotype->DetailedSerologies[20] );
    ews->AddColumn( "45+ years", Double::typeid, serotype->DetailedSerologies[21] );
    ews->AddColumn( "All ages", Double::typeid, serotype->DetailedSerologies[22] );

    ewb->AddWorksheet( ews );
  }

  ewb->SaveToDisk( _inputDirectory, "DS 1.0 - Location and Serotypes.xml" );
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



DensimParser::Location::Location(void)
: SimulationArea(gcnew List<String^>()),
  MosquitoesInArea(gcnew List<String^>()),
  MosquitoesPerHectare(gcnew List<String^>()),
  MosquitoesPerPerson(gcnew List<String^>()),
  MosquitoWetWeight(gcnew List<String^>()),
  MosquitoSurvival(gcnew List<String^>()),
  InfectiveBites(gcnew List<String^>())
{}



DensimParser::Location::~Location(void)
{}



DensimParser::Serotype::Serotype(void)
: EIP(gcnew List<String^>()),
  InfectiveMosquitoes(gcnew List<String^>()),
  PersonsIncubating(gcnew List<String^>()),
  PersonsViremic(gcnew List<String^>()),
  PersonsWithVirus(gcnew List<String^>()),
  DetailedSerologies(gcnew List<DetailedSerology^>())
{
  for( int i = 1; i <=23; ++i ) {
    // 23 classes for detailed serologies
    DetailedSerologies->Add( gcnew DetailedSerology() );
  }
}



DensimParser::Serotype::~Serotype(void)
{}
