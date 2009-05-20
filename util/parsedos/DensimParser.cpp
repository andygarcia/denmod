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



DensimParser::DensimParser( DirectoryInfo ^ inputDirectory)
: _inputDirectory(inputDirectory),
  _parseCompleted(false),
  _demographics(gcnew Demographics()),
  _initialSerology(gcnew Serology()),
  _finalSerology(gcnew Serology()),
  _location(gcnew Location()),
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
  for( int i = 1; i < 4; ++i ) {
    for each( String ^ s in sf->SerotypeData[i] ) {
      _serotypes[i]->EIP->Add( s );
    }
  }

  // Infective Mosquitoes
  sf = gcnew SerotypeFile( Path::Combine(_inputDirectory->FullName, "INFVMOSQ.PRN") );
  for( int i = 1; i < 4; ++i ) {
    for each( String ^ s in sf->SerotypeData[i] ) {
      _serotypes[i]->InfectiveMosquitoes->Add( s );
    }
  }

  // Persons Incubating
  sf = gcnew SerotypeFile( Path::Combine(_inputDirectory->FullName, "INCUBAT.PRN") );
  for( int i = 1; i < 4; ++i ) {
    for each( String ^ s in sf->SerotypeData[i] ) {
      _serotypes[i]->PersonsIncubating->Add( s );
    }
  }


  // Persons Viremic
  sf = gcnew SerotypeFile( Path::Combine(_inputDirectory->FullName, "VIREMIC.PRN") );
  for( int i = 1; i < 4; ++i ) {
    for each( String ^ s in sf->SerotypeData[i] ) {
      _serotypes[i]->PersonsViremic->Add( s );
    }
  }

  // Persons With Virus
  sf = gcnew SerotypeFile( Path::Combine(_inputDirectory->FullName, "WITHVIRS.PRN") );
  for( int i = 1; i < 4; ++i ) {
    for each( String ^ s in sf->SerotypeData[i] ) {
      _serotypes[i]->PersonsWithVirus->Add( s );
    }
  }


  // parse detailed serologies by serotype
  for( int i = 1; i <= 4; ++i ) {
    // parse each set (1-3)
    for( int j = 1; j <= 3; ++j ) {
      String ^ filter = "DET" + Convert::ToString(j) + "Y*D" + Convert::ToString(i) + ".PRN";
      array<FileInfo^> ^ fis = _inputDirectory->GetFiles( filter );

      for each( FileInfo ^ fi in fis ) {
        // open file, parse year index from file name, and insert year
        PrnFile ^ pf = gcnew PrnFile( fi->FullName );
        int year = Convert::ToInt32( fi->Name->Substring(5,1) );
        Serotype ^ serotype = _serotypes[i];
        serotype->YearlyDetailedSerologies[year] = gcnew Serotype::DetailedSerologies();
        for( int k = 1; k <= 23; ++k ) {
          serotype->YearlyDetailedSerologies[year]->Add( gcnew Serotype::DetailedSerology() );
        }

        // column offset based on which set of details
        int columnOffset;
        if( j == 1 ) {
          columnOffset = 0;
        }
        else if( j == 2 ) {
          columnOffset = 8;
        }
        else if ( j == 3 ) {
          columnOffset = 16;
        }

        // process into serology
        for each( List<String^> ^ row in pf->DataRows ) {
          for( int k = 1; k < row->Count; ++k ) {
            serotype->YearlyDetailedSerologies[year][k+columnOffset-1]->Add( row[k] );
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
  System::String ^ pwd = System::Environment::CurrentDirectory;
  System::Environment::CurrentDirectory = _inputDirectory->FullName;

  // save outputs
  OutputDemographics( outputType );
  OutputSerology( outputType );
  OutputLocation( outputType );
  OutputSerotypes( outputType );

  // restore working directory
  System::Environment::CurrentDirectory = pwd;
}



void
DensimParser::OutputDemographics( OutputType ot )
{
  // collate all header names
  std::vector<std::string> headers;
  headers.push_back( "Initial age distribution" );
  headers.push_back( "Initial percentage" );
  headers.push_back( "Births" );
  headers.push_back( "Birth percentages" );
  headers.push_back( "Deaths" );
  headers.push_back( "Death percentages" );
  headers.push_back( "Final age distribution" );
  headers.push_back( "Final percentage" );

  String ^ title = "Demographics";
  ExcelOutput * eo = new ExcelOutput( toss(title), headers, 18 );

  for( int i = 0; i < 18; ++i ) {
    std::vector<std::string> newRow;

    newRow.push_back( toss(_demographics->InitialDistribution[i]) );
    newRow.push_back( toss(_demographics->InitialDistributionPercentages[i]) );
    newRow.push_back( toss(_demographics->Births[i]) );
    newRow.push_back( toss(_demographics->BirthPercentages[i]) );
    newRow.push_back( toss(_demographics->Deaths[i]) );
    newRow.push_back( toss(_demographics->DeathPercentages[i]) );
    newRow.push_back( toss(_demographics->FinalDistribution[i]) );
    newRow.push_back( toss(_demographics->FinalDistributionPercentages[i]) );

    eo->AddRow( newRow );
  }

  String ^ filename = "DS 1.0 - Demographics";
  if( ot == OutputType::XML ) {
    filename += ".xml";
    std::ofstream containerXML(toss(filename).c_str());
    containerXML << eo->GetOutput( ExcelOutput::XML, 7 );
    containerXML.close();
  }

  if( ot == OutputType::ASCII ) {
    filename += ".txt";
    std:: ofstream containerTXT(toss(filename).c_str());
    containerTXT << eo->GetOutput( ExcelOutput::ASCII, 7 );
    containerTXT.close();
  }

  delete eo;
}



void
DensimParser::OutputSerology( OutputType ot )
{
  // collate all header names
  std::vector<std::string> headers;
  headers.push_back( "Dengue 1 Initial Distribution" );
  headers.push_back( "Dengue 1 Initial Distribution Percentage" );
  headers.push_back( "Dengue 2 Initial Distribution" );
  headers.push_back( "Dengue 2 Initial Distribution Percentage" );
  headers.push_back( "Dengue 3 Initial Distribution" );
  headers.push_back( "Dengue 3 Initial Distribution Percentage" );
  headers.push_back( "Dengue 4 Initial Distribution" );
  headers.push_back( "Dengue 4 Initial Distribution Percentage" );

  headers.push_back( "Dengue 1 Final Distribution" );
  headers.push_back( "Dengue 1 Final Distribution Percentage" );
  headers.push_back( "Dengue 2 Final Distribution" );
  headers.push_back( "Dengue 2 Final Distribution Percentage" );
  headers.push_back( "Dengue 3 Final Distribution" );
  headers.push_back( "Dengue 3 Final Distribution Percentage" );
  headers.push_back( "Dengue 4 Final Distribution" );
  headers.push_back( "Dengue 4 Final Distribution Percentage" );

  String ^ title = "Serology";
  ExcelOutput * eo = new ExcelOutput( toss(title), headers, 18 );

  for( int i = 0; i < 18; ++i ) {
    std::vector<std::string> newRow;

    newRow.push_back( toss(_initialSerology->D1Number[i]) );
    newRow.push_back( toss(_initialSerology->D1Percent[i]) );
    newRow.push_back( toss(_initialSerology->D2Number[i]) );
    newRow.push_back( toss(_initialSerology->D2Percent[i]) );
    newRow.push_back( toss(_initialSerology->D3Number[i]) );
    newRow.push_back( toss(_initialSerology->D3Percent[i]) );
    newRow.push_back( toss(_initialSerology->D4Number[i]) );
    newRow.push_back( toss(_initialSerology->D4Percent[i]) );

    newRow.push_back( toss(_finalSerology->D1Number[i]) );
    newRow.push_back( toss(_finalSerology->D1Percent[i]) );
    newRow.push_back( toss(_finalSerology->D2Number[i]) );
    newRow.push_back( toss(_finalSerology->D2Percent[i]) );
    newRow.push_back( toss(_finalSerology->D3Number[i]) );
    newRow.push_back( toss(_finalSerology->D3Percent[i]) );
    newRow.push_back( toss(_finalSerology->D4Number[i]) );
    newRow.push_back( toss(_finalSerology->D4Percent[i]) );

    eo->AddRow( newRow );
  }

  String ^ filename = "DS 1.0 - Serology";
  if( ot == OutputType::XML ) {
    filename += ".xml";
    std::ofstream containerXML(toss(filename).c_str());
    containerXML << eo->GetOutput( ExcelOutput::XML, 7 );
    containerXML.close();
  }

  if( ot == OutputType::ASCII ) {
    filename += ".txt";
    std:: ofstream containerTXT(toss(filename).c_str());
    containerTXT << eo->GetOutput( ExcelOutput::ASCII, 7 );
    containerTXT.close();
  }

  delete eo;
}



void
DensimParser::OutputLocation( OutputType ot )
{
  // collate all header names
  std::vector<std::string> headers;
  headers.push_back( "Simulation Area" );
  headers.push_back( "Mosquitoes In Area" );
  headers.push_back( "Mosquitoes Per Hectare" );
  headers.push_back( "Mosquitoes Per Person" );
  headers.push_back( "Mosquito Wet Weight" );
  headers.push_back( "Mosquito Survival" );
  headers.push_back( "Infective Bites" );

  String ^ title = "Location";
  ExcelOutput * eo = new ExcelOutput( toss(title), headers, 365 );

  for( int i = 0; i < 365; ++i ) {
    std::vector<std::string> newRow;

    newRow.push_back( toss(_location->SimulationArea[i]) );
    newRow.push_back( toss(_location->MosquitoesInArea[i]) );
    newRow.push_back( toss(_location->MosquitoesPerHectare[i]) );
    newRow.push_back( toss(_location->MosquitoesPerPerson[i]) );
    newRow.push_back( toss(_location->MosquitoWetWeight[i]) );
    newRow.push_back( toss(_location->MosquitoSurvival[i]) );
    newRow.push_back( toss(_location->InfectiveBites[i]) );

    eo->AddRow( newRow );
  }

  String ^ filename = "DS 1.0 - Location";
  if( ot == OutputType::XML ) {
    filename += ".xml";
    std::ofstream containerXML(toss(filename).c_str());
    containerXML << eo->GetOutput( ExcelOutput::XML, 7 );
    containerXML.close();
  }

  if( ot == OutputType::ASCII ) {
    filename += ".txt";
    std:: ofstream containerTXT(toss(filename).c_str());
    containerTXT << eo->GetOutput( ExcelOutput::ASCII, 7 );
    containerTXT.close();
  }

  delete eo;
}



void 
DensimParser::OutputSerotypes( OutputType ot )
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
  YearlyDetailedSerologies(gcnew Dictionary<int,DetailedSerologies^>())
{
}



DensimParser::Serotype::~Serotype(void)
{}
