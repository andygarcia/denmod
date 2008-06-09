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



CimsimParser::CimsimParser(void)
{
}



CimsimParser::~CimsimParser(void)
{
}



bool
CimsimParser::ParseLocation(void)
{
  _locationFiles = gcnew array<LocationFile^>(_locationFilenames->Length);

  // open each location file
  for( int i = 0; i < _locationFilenames->Length; i++ ) {
    try {
      _locationFiles[i] = gcnew LocationFile( _locationFilenames[i] );
    }
    catch ( FileNotFoundException ^ e ) {
      System::Console::WriteLine( e->Message );
      MessageBox::Show( "Unable to open " + _locationFilenames[i] + " to create location output." );
      return false;
    }
  }

  return true;
}



bool
CimsimParser::ParseContainer(void)
{
  // collate title from each file into headers for combined output
  _containerOutputHeaders = gcnew List<String^>();

  // organize data by container name and filter for later use
  _containerDataByNameAndHeader = gcnew Dictionary<String^,Dictionary<String^,List<String^>^>^>();
    
  // search each filter
  DirectoryInfo ^ di = gcnew DirectoryInfo (System::Environment::CurrentDirectory );
  for each( String ^ filter in _containerFilters ) {
    // find file(s) for this filter , e.g. EGGS1.PRN, EGGS2.PRN, EGGS3.PRN
    array<FileInfo^> ^ fis = di->GetFiles( filter );

    // the number will vary between different simulation, but cannot be zero
    if( fis->Length == 0 ) {
      MessageBox::Show( "Unable to find any files for " + filter );
      return false;
    }

    // open each file
    for each( FileInfo ^ fi in fis ) {
      try {
        ContainerFile ^ cf = gcnew ContainerFile( fi->Name );

        // save title for output headers
        if( !_containerOutputHeaders->Contains( cf->_title ) ) {
          _containerOutputHeaders->Add( cf->_title );
        }

        // save each container's column of data from this file
        for each( String ^ containerName in cf->_containerNames ) {
          if( !_containerDataByNameAndHeader->ContainsKey( containerName ) ) {
            // first time container found, create its dictionary of output header to output data
            _containerDataByNameAndHeader[containerName] = gcnew Dictionary<String^,List<String^>^>();
          }
          _containerDataByNameAndHeader[containerName][cf->_title]= cf->_containerData[containerName];
        }
      }
      catch ( FileNotFoundException ^ e ) {
        System::Console::WriteLine( e->Message );
        MessageBox::Show( "Unable to open " + fi + " to create container output." );
        return false;
      }
    }
  }

  return true;
}



bool
CimsimParser::ParseSurvivals(void)
{
  _survivalFiles = gcnew List<SurvivalFile^>();

  // search each filter for survival files
  DirectoryInfo ^ di = gcnew DirectoryInfo (System::Environment::CurrentDirectory );
  for each( String ^ filter in _survivalFilters ) {
    // find file(s) for this filter , e.g. SUEGG1.PRN, SUEGG2.PRN, etc.
    array<FileInfo^> ^ fis = di->GetFiles( filter );

    // the number will vary between different simulation, but cannot be zero
    if( fis->Length == 0 ) {
      MessageBox::Show( "Unable to find any files for " + filter );
      return false;
    }

    // open each file
    for each( FileInfo ^ fi in fis ) {
      try {
        SurvivalFile ^ sf = gcnew SurvivalFile( fi->Name );
        _survivalFiles->Add( sf );
      }
      catch ( FileNotFoundException ^ e ) {
        System::Console::WriteLine( e->Message );
        MessageBox::Show( "Unable to open " + fi + " to create container output." );
        return false;
      }
    }
  }

  return true;
}



bool
CimsimParser::ParseLarvalData(void)
{

  DirectoryInfo ^ di = gcnew DirectoryInfo( System::Environment::CurrentDirectory );
  array<FileInfo^> ^ files = di->GetFiles( _larvalDataFilename );
  if( files->Length == 0 ) {
    MessageBox::Show( "No larval data files were found.  Unable to create larval data output." );
    return false;
  }
  _larvalDataFiles = gcnew array<LarvalDataFile^>(files->Length);
  
  for( int i = 0; i < files->Length; i++ ) {
    try {
      _larvalDataFiles[i] = gcnew LarvalDataFile( files[i]->Name );
    }
    catch ( FileNotFoundException ^ e ) {
      System::Console::WriteLine( e->Message );
      MessageBox::Show( "Unable to open " + files[i] + "." );
      return false;
    }
  }

  return true;
}



void CimsimParser::OutputLocation( OutputType ot )
{
  // collate all header names
  vector<string> headers;
  for each( LocationFile ^ lf in _locationFiles ) {
    for each( String ^ s in lf->_headers) {
      headers.push_back(toss(s));
    }
  }
  String ^ title = "Location Output";

  ExcelOutput * eo = new ExcelOutput( toss(title), headers, 365 );
  for( int iRow = 0; iRow < 365; ++iRow ) {
    vector<string> newRow;
    for each( LocationFile ^ lf in _locationFiles ) {
      for( int iCol = 0; iCol <= lf->_data->GetUpperBound(1); iCol++ ) {
        newRow.push_back(toss(lf->_data[iRow,iCol]));
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



void CimsimParser::OutputContainer( OutputType ot )
{
  vector<string> headers;
  for each( String ^ header in _containerOutputHeaders ) {
    headers.push_back( toss(header) );
  }

  for each( KeyValuePair<String^,Dictionary<String^,List<String^>^>^> ^ kvp in _containerDataByNameAndHeader ) {
    String ^ containerName = kvp->Key;
    String ^ title = "Container Output - " + containerName;
    ExcelOutput * eo = new ExcelOutput( toss(title), headers, 365 );

    for( int i = 0; i < 365; ++i ) {
      vector<string> newRow;
      for each( String ^ header in _containerOutputHeaders ) {
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



void CimsimParser::OutputSurvivals( OutputType ot )
{
  for each( SurvivalFile ^ sf in _survivalFiles ) {
    // collate all header names
    vector<string> headers;
    for each( String ^ s in sf->_headers ) {
      headers.push_back(toss(s));
    }

    String ^ title = sf->_containerName + " - " + sf->_title;

    ExcelOutput * eo = new ExcelOutput( toss(title), headers, 365 );

    for( int i = 0; i < 365; ++i ) {
      vector<string> newRow;
      for each( String ^ header in sf->_headers ) {
        newRow.push_back( toss(sf->_data[header][i]) );
      }
      eo->AddRow( newRow );
    }

    if( ot == OutputType::XML ) {

      String ^ filename = "CS 1.0 - " + title + ".xml";
      std::ofstream containerXML(toss(filename).c_str());
      containerXML << eo->GetOutput( ExcelOutput::XML, 7 );
      containerXML.close();
    }

    if( ot == OutputType::ASCII ) {
      String ^ filename = "CS 1.0 - " + title + ".txt";
      std:: ofstream containerTXT(toss(filename).c_str());
      containerTXT << eo->GetOutput( ExcelOutput::ASCII, 7 );
      containerTXT.close();
    }

    delete eo;
  }
}



void CimsimParser::OutputLarvalData( OutputType ot )
{
  for each( LarvalDataFile ^ ldf in _larvalDataFiles ) {
    vector<string> headers;
    for each( String ^ s in ldf->_headers ) {
      headers.push_back(toss(s));
    }

    ExcelOutput * eo = new ExcelOutput( toss(ldf->_title), headers, 365 );
    for( int iRow = 0; iRow < 100; ++iRow ) {
      vector<string> newRow;
      for( int iCol = 0; iCol <= ldf->_data->GetUpperBound(1); iCol++ ) {
        newRow.push_back(toss(ldf->_data[iRow,iCol]));
      }
      eo->AddRow( newRow );
    }

    if( ot == OutputType::XML ) {
      String ^ filename = "CS 1.0 - Larval Data - Day " + ldf->_day + ".xml";
      std::ofstream containerXML(toss(filename).c_str());
      containerXML << eo->GetOutput( ExcelOutput::XML, 7 );
      containerXML.close();
    }

    if( ot == OutputType::ASCII ) {
      String ^ filename = "CS 1.0 - Larval Data - Day " + ldf->_day + ".txt";
      std:: ofstream containerTXT(toss(filename).c_str());
      containerTXT << eo->GetOutput( ExcelOutput::ASCII, 7 );
      containerTXT.close();
    }

    delete eo;
  }
}
