#include "stdafx.h"
#include "CimsimParser.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace util;



std::string toss( String ^ s )
{
  using Runtime::InteropServices::Marshal;
  const char* c_str = (const char*) (Marshal::StringToHGlobalAnsi(s)).ToPointer();
  std::string sstring = c_str;
  Marshal::FreeHGlobal(IntPtr((void*)c_str));
  return sstring;
}



static
CimsimParser::CimsimParser(void)
{
  _yearDays = gcnew System::Collections::Generic::List<int>();
  for( int i = 1; i <= 365; ++i ) {
    _yearDays->Add( i );
  }

  _locationFilenames = gcnew List<String^>();
  _locationFilenames->Add( "MAIN.PRN" );
  _locationFilenames->Add( "FEMSHA.PRN" );
  _locationFilenames->Add( "FEMSHOST.PRN" );
  _locationFilenames->Add( "FECUND.PRN" );
  _locationFilenames->Add( "WEATHER.PRN" );
  _locationFilenames->Add( "SUADLT.PRN" );

  _containerFilters = gcnew List<String^>();
  _containerFilters->Add( "DEPTH*.PRN" );
  _containerFilters->Add( "FOOD*.PRN" );
  _containerFilters->Add( "EGGS*.PRN" );
  _containerFilters->Add( "LARVAE*.PRN" );
  _containerFilters->Add( "PUPAE*.PRN" );
  _containerFilters->Add( "AVGPUWT*.PRN" );
  _containerFilters->Add( "NEWFEMS*.PRN" );
  _containerFilters->Add( "CUMFEMS*.PRN" );
  _containerFilters->Add( "DLYOVI*.PRN" );

  _survivalFilters = gcnew List<String^>();
  _survivalFilters->Add( "SUEGG*.PRN" );
  _survivalFilters->Add( "SULARV*.PRN" );
  _survivalFilters->Add( "SUPUP*.PRN" );

  _larvalDataFilename = "LARVD*.PRN";

}



CimsimParser::CimsimParser( DirectoryInfo ^ inputDirectory)
: _inputDirectory(inputDirectory),
  _parseCompleted(false),
  _locationFiles(gcnew List<LocationFile^>()),
  _containerNames(gcnew List<String^>()),
  _containerHeaders(gcnew List<String^>()),
  _containerData(gcnew Dictionary<String^,Dictionary<String^,List<String^>^>^>()),
  _containerSurvivals(gcnew Dictionary<String^,List<SurvivalFile^>^>()),
  _larvalDataFiles(gcnew List<LarvalDataFile^>())
{}



CimsimParser::~CimsimParser(void)
{}



void
CimsimParser::Parse(void)
{
  // parse each location file
  for each( String ^ s in _locationFilenames ) {
    String ^ filename = Path::Combine( _inputDirectory->FullName, s );
    _locationFiles->Add( gcnew LocationFile(filename) );
  }


  // parse container files
  for each( String ^ filter in _containerFilters ) {
    // find and open files for each filter, e.g. EGGS1.PRN, EGGS2.PRN, EGGS3.PRN
    array<FileInfo^> ^ fis = _inputDirectory->GetFiles( filter );
    if( fis->Length == 0 ) {
      throw gcnew FileNotFoundException( "Unable to find any files for container file type " + filter );
    }

    for each( FileInfo ^ fi in fis ) {
      ContainerFile ^ cf = gcnew ContainerFile( fi->FullName );

      // save header
      if( !_containerHeaders->Contains(cf->Header) ) {
        _containerHeaders->Add( cf->Header );
      }

      // save data by container
      for each( String ^ containerName in cf->ContainerNames ) {
        if( !_containerNames->Contains(containerName) ) {
          // first time encountering this container
          _containerNames->Add( containerName );
          _containerData[containerName] = gcnew Dictionary<String^,List<String^>^>();
          _containerSurvivals[containerName] = gcnew List<SurvivalFile^>();
        }

        // get container's header and columns
        _containerData[containerName][cf->Header] = cf->ContainerData[containerName];

      }
    } // for each
  }


  // search each filter for survival files
  for each( String ^ filter in _survivalFilters ) {
    array<FileInfo^> ^ fis = _inputDirectory->GetFiles( filter );
    if( fis->Length == 0 ) {
      throw gcnew FileNotFoundException( "Unable to find any files for survival file type " + filter );
    }
    for each( FileInfo ^ fi in fis ) {
      SurvivalFile ^ sf = gcnew SurvivalFile( fi->FullName );

      // save survival data to container data
      for each( String ^ header in sf->Headers ) {
        _containerData[sf->ContainerName][header] = sf->Data[header];

      }
    }
  }


  // parse larval data
  array<FileInfo^> ^ files = _inputDirectory->GetFiles( _larvalDataFilename );
  for( int i = 0; i < files->Length; i++ ) {
    _larvalDataFiles->Add( gcnew LarvalDataFile(files[i]->Name) );
  }

  _parseCompleted = true;
}



void
CimsimParser::SaveToDisk( OutputType outputType )
{
  if( _parseCompleted != true ) {
    throw gcnew InvalidOperationException( "SaveToDisk called before parsing completed." );
  }
  else {
    System::String ^ pwd = System::Environment::CurrentDirectory;
    System::Environment::CurrentDirectory = _inputDirectory->FullName;
    OutputLocation( outputType );
    OutputContainer( outputType );
    OutputSurvivals( outputType );
    OutputLarvalData( outputType );
    System::Environment::CurrentDirectory = pwd;
  }
}



void
CimsimParser::OutputLocation( OutputType ot )
{
  ExcelWorksheet ^ ews = gcnew ExcelWorksheet( "Location" );
  ews->AddColumn( "Day", Int32::typeid, _yearDays );

  for each( LocationFile ^ lf in _locationFiles ) {
    for each( String ^ s in lf->Headers) {
      ews->AddColumn( s, Double::typeid, lf->Data[s] );
    }
  }

  ExcelWorkbook ^ ewb = gcnew ExcelWorkbook( "CIMSiM 1.0" );
  ewb->AddWorksheet( ews );
  ewb->SaveToDisk( _inputDirectory, "CS 1.0 - Location.xml" );
}



void
CimsimParser::OutputContainer( OutputType ot )
{
  for each( KeyValuePair<String^,Dictionary<String^,List<String^>^>^> ^ kvp in _containerData ) {
    ExcelWorksheet ^ ews = gcnew ExcelWorksheet( kvp->Key );
    ews->AddColumn( "Day", Int32::typeid, _yearDays );

    for each( String ^ header in kvp->Value->Keys ) {
      ews->AddColumn( header, Double::typeid, kvp->Value[header] );
    }

    ExcelWorkbook ^ ewb = gcnew ExcelWorkbook( "CIMSiM 1.0" );
    ewb->AddWorksheet( ews );
    ewb->SaveToDisk( _inputDirectory, "CS 1.0 - " + kvp->Key + ".xml" );
  }
}



void
CimsimParser::OutputLarvalData( OutputType ot )
{
}
