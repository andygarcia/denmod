#include "stdafx.h"
#include "CimsimParser.h"
#include "ExcelOutput.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;



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
  // collate all header names
  vector<string> headers;
  for each( LocationFile ^ lf in _locationFiles ) {
    for each( String ^ s in lf->Headers) {
      headers.push_back(toss(s));
    }
  }

  String ^ title = "Location Output";
  ExcelOutput * eo = new ExcelOutput( toss(title), headers, 365 );

  for( int i = 0; i < 365; ++i ) {
    vector<string> newRow;
    for each( LocationFile ^ lf in _locationFiles ) {
      for each( String ^ s in lf->Headers ) {
        newRow.push_back( toss(lf->Data[s][i]) );
      }
    }
    eo->AddRow( newRow );
  }

  if( ot == OutputType::XML ) {
    String ^ filename = "CS 1.0 - Location.xml";
    std::ofstream containerXML(toss(filename).c_str());
    containerXML << eo->GetOutput( ExcelOutput::XML, 7 );
    containerXML.close();
  }

  if( ot == OutputType::ASCII ) {
    String ^ filename = "CS 1.0 - Location.txt";
    std:: ofstream containerTXT(toss(filename).c_str());
    containerTXT << eo->GetOutput( ExcelOutput::ASCII, 7 );
    containerTXT.close();
  }

  delete eo;
}



void
CimsimParser::OutputContainer( OutputType ot )
{
  for each( KeyValuePair<String^,Dictionary<String^,List<String^>^>^> ^ kvp in _containerData ) {
    String ^ containerName = kvp->Key;
    String ^ title = "Container Output - " + containerName;

    vector<string> headers;
    for each( String ^ header in kvp->Value->Keys ) {
      headers.push_back( toss(header) );
    }

    ExcelOutput * eo = new ExcelOutput( toss(title), headers, 365 );

    for( int i = 0; i < 365; ++i ) {
      vector<string> newRow;
      for each( String ^ header in kvp->Value->Keys ) {
        newRow.push_back( toss(kvp->Value[header][i]) );
      }
      eo->AddRow( newRow );
    }


    if( ot == OutputType::XML ) {
      String ^ filename = "CS 1.0 - " + containerName + ".xml";
      std::ofstream containerXML(toss(filename).c_str());
      containerXML << eo->GetOutput( ExcelOutput::XML, 7 );
      containerXML.close();
    }

    if( ot == OutputType::ASCII ) {
      String ^ filename = "CS 1.0 - " + containerName + ".txt";
      std:: ofstream containerTXT(toss(filename).c_str());
      containerTXT << eo->GetOutput( ExcelOutput::ASCII, 7 );
      containerTXT.close();
    }
  }
}



void
CimsimParser::OutputSurvivals( OutputType ot )
{

}



void
CimsimParser::OutputLarvalData( OutputType ot )
{
  //for each( LarvalDataFile ^ ldf in _larvalDataFiles ) {
  //  vector<string> headers;
  //  for each( String ^ s in ldf->Headers ) {
  //    headers.push_back(toss(s));
  //  }

  //  ExcelOutput * eo = new ExcelOutput( toss(ldf->_title), headers, 365 );
  //  for( int iRow = 0; iRow < 100; ++iRow ) {
  //    vector<string> newRow;
  //    for( int iCol = 0; iCol <= ldf->_data->GetUpperBound(1); iCol++ ) {
  //      newRow.push_back(toss(ldf->_data[iRow,iCol]));
  //    }
  //    eo->AddRow( newRow );
  //  }

  //  if( ot == OutputType::XML ) {
  //    String ^ filename = "CS 1.0 - Larval Data - Day " + ldf->_day + ".xml";
  //    std::ofstream containerXML(toss(filename).c_str());
  //    containerXML << eo->GetOutput( ExcelOutput::XML, 7 );
  //    containerXML.close();
  //  }

  //  if( ot == OutputType::ASCII ) {
  //    String ^ filename = "CS 1.0 - Larval Data - Day " + ldf->_day + ".txt";
  //    std:: ofstream containerTXT(toss(filename).c_str());
  //    containerTXT << eo->GetOutput( ExcelOutput::ASCII, 7 );
  //    containerTXT.close();
  //  }

  //  delete eo;
  //}
}
