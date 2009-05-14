#include "stdafx.h"
#include "PrnFiles.h"

using namespace System;
using namespace System::IO;
using namespace System::Text::RegularExpressions;
using namespace System::Windows::Forms;



PrnFile::PrnFile( String ^ filename )
{
  // open file
  Filename = filename;
  StreamReader ^ sr = gcnew StreamReader( filename );

  // local variables for parsing
  String ^ s;
  String ^ headerDelim = "-";
  String ^ dataDelim = " ,";
  array<String ^> ^ entries;


  // read first row of headers
  s = sr->ReadLine();
  entries = s->Split( headerDelim->ToCharArray() );
  FirstHeaderRow = gcnew List<String^>( entries->Length );
  for each( String ^ s in entries ) {
    FirstHeaderRow->Add( s->Trim() );
  }


  // read second row of headers
  s = sr->ReadLine();
  entries = s->Split( headerDelim->ToCharArray() );
  SecondHeaderRow = gcnew List<String^>( entries->Length );
  for each( String ^ s in entries ) {
    SecondHeaderRow->Add( s->Trim() );
  }


  // read data
  DataRows = gcnew List<List<String^>^>();
  for( int i = 0; i < 365; ++i ) {
    s = sr->ReadLine();
    List<String^> ^ row = gcnew List<String^>();
    entries = s->Split( dataDelim->ToCharArray(), StringSplitOptions::RemoveEmptyEntries );
    if( entries->Length != SecondHeaderRow->Count ) {
      // number of columns in this row does not match expected count from second header row
      throw gcnew InvalidDataException( "Number of entries for day " + (i+1) + " does not match number of headers in second row in " + Filename );
    }
    for each( String ^ s in entries ) {
      row->Add( s->Trim() );
    }
    DataRows->Add( row );
  }
}



PrnFile::~PrnFile(void)
{}


LocationFile::LocationFile( String ^ filename )
{
  _filename = filename;

  StreamReader ^ sr = gcnew StreamReader( filename );
  String ^ s;
  String ^ headerDelim = "-";
  String ^ dataDelim = " ,";

  // read container name
  s = sr->ReadLine();
  array<String ^> ^ strings = s->Split( headerDelim->ToCharArray() );
  if( strings[0]->Trim(' ') == "Day" ) {
    // female host density file, only one header line
    _title = "Density";
    _headers = gcnew array<String^>(strings->Length - 1);
    Array::Copy( strings, 1, _headers, 0, strings->Length - 1 );
  }
  else {
    _title = strings[0];
    
    // save headers
    s = sr->ReadLine();
    strings = s->Split(headerDelim->ToCharArray());
    _headers = gcnew array<String^>(strings->Length - 1);
    Array::Copy( strings, 1, _headers, 0, strings->Length - 1 );
  }

  _data = gcnew array<String ^,2>(365, _headers->Length);

  int i;
  for( i = 0; i < 365 && !sr->EndOfStream; i++ ) {
    s = sr->ReadLine();
    array<String ^> ^ columnEntries = s->Split( dataDelim->ToCharArray(), StringSplitOptions::RemoveEmptyEntries );

    if( columnEntries->Length - 1 > _headers->Length ) {
      // more column entries than headers (infective bites), only save what's needed for headers
      for( int j = 0; j < _headers->Length; j++ ) {
        _data[i,j] = columnEntries[j+1];
      }
    }
    else {
      for( int j = 0; j < columnEntries->Length-1; j++ ) {
        _data[i,j] = columnEntries[j+1];
      }
    }
  }
}



ContainerFile::ContainerFile( String ^ filename )
: PrnFile(filename)
{
  // first row's (only) header is the header for this container file
  Header = FirstHeaderRow[0];

  // except for first entry (day), the second row's header are all container names
  ContainerNames = gcnew List<String^>( SecondHeaderRow->Count - 1 );
  for( int i = 1; i < SecondHeaderRow->Count; ++i ) {
    ContainerNames->Add( SecondHeaderRow[i] );
  }

  // create dictionary for each container's column of data
  ContainerData = gcnew Dictionary<String^,List<String^>^>();
  for each( String ^ container in ContainerNames ) {
    ContainerData[container] = gcnew List<String^>();
  }

  // process data from rows into individual container columns, ignoring first column (day)
  for each( List<String^> ^ row in DataRows ) {
    // ignore first column (day index)
    for( int i = 1; i < row->Count; ++i ) {
      ContainerData[ContainerNames[i-1]]->Add( row[i] );
    }
  }
}



SerotypeFile::SerotypeFile( String ^ filename )
: PrnFile(filename),
  SerotypeData(gcnew Dictionary<int,List<String^>^>())
{
  // first row's (only) header is the header for this container file
  Header = FirstHeaderRow[0];

  // create columns for each serotype
  for( int i = 1; i <= 4; ++i ) {
    SerotypeData[i] = gcnew List<String^>();
  }

  // process data from rows into individual serotype columns, ignoring first column (day)
  for each( List<String^> ^ row in DataRows ) {
    // ignore first column (day index)
    for( int i = 1; i <= 4; ++i ) {
      SerotypeData[i]->Add( row[i] );
    }
  }
}



SurvivalFile::SurvivalFile( String ^ filename )
: PrnFile( filename )
{
  // first row has two headers, stage identifier followed by container
  String ^ stageHeader = FirstHeaderRow[0];
  ContainerName = FirstHeaderRow[1];

  // save column headers, ignoring first entry (day)
  Headers = gcnew List<String^>( SecondHeaderRow->Count - 1 );
  for( int i = 1; i < SecondHeaderRow->Count; ++i ) {
    Headers->Add( stageHeader + " - " + SecondHeaderRow[i] );
  }

  // create dictionary for each header's column of data
  Data = gcnew Dictionary<String^,List<String^>^>();
  for each( String ^ header in Headers ) {
    Data[header] = gcnew List<String^>();
  }

  // process data from rows into individual header columns, ignoring first column (day)
  for each( List<String^> ^ row in PrnFile::DataRows ) {
    // ignore first column (day index)
    for( int i = 1; i < row->Count; ++i ) {
      Data[Headers[i-1]]->Add( row[i] );
    }
  }
}



LarvalDataFile::LarvalDataFile( String ^ filename )
: PrnFile(filename)
{
}
