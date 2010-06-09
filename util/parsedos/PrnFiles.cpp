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


  SecondHeaderRow = gcnew List<String^>( entries->Length );
  if( FirstHeaderRow[0] == "Day" ) {
    // no more header rows
  }
  else {
    // second row of header exists (beginning with Day)
    s = sr->ReadLine();
    entries = s->Split( headerDelim->ToCharArray() );
    for each( String ^ s in entries ) {
      SecondHeaderRow->Add( s->Trim() );
    }
  }


  // determine number of columns
  int numColumns;
  if( SecondHeaderRow->Count == 0  ) {
    numColumns = FirstHeaderRow->Count;
  }
  else {
    numColumns = SecondHeaderRow->Count;
  }


  // read data
  DataRows = gcnew List<List<String^>^>();
  while( s = sr->ReadLine() ) {
    List<String^> ^ row = gcnew List<String^>();
    entries = s->Split( dataDelim->ToCharArray(), StringSplitOptions::RemoveEmptyEntries );

    // add each trimmed value
    for each( String ^ s in entries ) {
      row->Add( s->Trim() );
    }

    // save row
    DataRows->Add( row );
  }
}



PrnFile::~PrnFile(void)
{}



LocationFile::LocationFile( String ^ filename )
: PrnFile(filename)
{
  List<String^> ^ headers;
  if( SecondHeaderRow->Count == 0 ) {
    // use filename minus extension as title
    this->Title = filename;
    
    // and first row contains data headers
    headers = FirstHeaderRow;
  }
  else {
    // title is first row
    this->Title = FirstHeaderRow[0];

    // and second row contains data headers
    headers = SecondHeaderRow;
  }

  // except for first entry (day), the second row's entries are all headers
  this->Headers = gcnew List<String^>( headers->Count - 1 );
  for( int i = 1; i < headers->Count; ++i ) {
    Headers->Add( headers[i] );
  }

  // create header for each headers's column of data
  Data = gcnew Dictionary<String^,List<String^>^>();
  for each( String ^ s in Headers ) {
    Data[s] = gcnew List<String^>();
  }

  // process data from rows into individual container columns, ignoring first column (day)
  for each( List<String^> ^ row in DataRows ) {
    // ignore first column (day index)
    for( int i = 1; i <= Headers->Count; ++i ) {
      Data[Headers[i-1]]->Add( row[i] );
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
