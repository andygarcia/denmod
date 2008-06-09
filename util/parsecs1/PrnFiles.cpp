#include "stdafx.h"
#include "PrnFiles.h"

using namespace System;
using namespace System::IO;
using namespace System::Text::RegularExpressions;
using namespace System::Windows::Forms;


LocationFile::LocationFile(void) {}
LocationFile::~LocationFile(void) {}


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
    for( int j = 0; j < columnEntries->Length-1; j++ ) {
      _data[i,j] = columnEntries[j+1];
    }
  }
}



ContainerFile::ContainerFile(void) {}
ContainerFile::~ContainerFile(void) {}
ContainerFile::ContainerFile( String ^ filename )
: _filename(filename)
{
  String ^ s;
  String ^ headerDelim = "-";
  String ^ dataDelim = " ,";
  StreamReader ^ sr = gcnew StreamReader( filename );


  // read graph title
  s = sr->ReadLine();
  _title= s->Trim();


  // read headers, consisting of day header and container name(s)
  s = sr->ReadLine();
  array<String ^> ^ entries = s->Split( headerDelim->ToCharArray() );
  _numContainers = entries->Length - 1;
  // copy headers, and remove first one (day)
  _containerNames = gcnew List<String^>();
  for each( String ^ s in entries ) {
    _containerNames->Add( s->Trim() );
  }
  _containerNames->RemoveAt(0);


  // save data for individual containers
  _containerData = gcnew Dictionary<String^,List<String^>^>();
  for each( String ^ containerName in _containerNames ) {
    _containerData[containerName] = gcnew List<String^>(365);
  }

  int i = 0;
  while( !sr->EndOfStream ) {
    s = sr->ReadLine();
    array<String ^> ^ columnEntries = s->Split( dataDelim->ToCharArray(), StringSplitOptions::RemoveEmptyEntries );
    // not interested in the Day column, start reading at column index 1
    for( int j = 0; j < _numContainers; ++j ) {
      _containerData[_containerNames[j]]->Add( columnEntries[j+1] );
    }
    i++;
  }
}



bool 
ContainerFile::HasContainer( String ^ containerName )
{
  if( _containerNames->Contains(containerName) ) {
    return true;
  }
  else {
    return false;
  }
}



List<String^> ^
ContainerFile::GetContainerData( String ^ containerName )
{
  return _containerData[containerName];
}



SurvivalFile::SurvivalFile(void) {}
SurvivalFile::~SurvivalFile(void) {}
SurvivalFile::SurvivalFile( String ^ filename )
: _filename(filename)
{
  StreamReader ^ sr = gcnew StreamReader( filename );
  String ^ s;
  String ^ headerDelim = "-";
  String ^ dataDelim = " ,";

  // read container name
  s = sr->ReadLine();
  array<String ^> ^ strings = s->Split( headerDelim->ToCharArray() );
  _title = strings[0]->Trim();
  if( strings->Length > 1 ) {
    _containerName = strings[1]->Trim();
  }

  // save headers
  s = sr->ReadLine();
  strings = s->Split(headerDelim->ToCharArray());
  // copy headers, and remove first one (day)
  _headers= gcnew List<String^>();
  for each( String ^ s in strings ) {
    _headers->Add( s->Trim() );
  }
  _headers->RemoveAt(0);

  _data = gcnew Dictionary<String^, List<String^>^>;
  for each( String ^ header in _headers) {
    _data[header] = gcnew List<String^>(365);
  }

  for( int i = 0; i < 365 && !sr->EndOfStream; i++ ) {
    s = sr->ReadLine();
    array<String ^> ^ columnEntries = s->Split( dataDelim->ToCharArray(), StringSplitOptions::RemoveEmptyEntries );
    for( int j = 0; j < columnEntries->Length-1; j++ ) {
      _data[_headers[j]]->Add( columnEntries[j+1] );
    }
  }
}



LarvalDataFile::LarvalDataFile(void) {}
LarvalDataFile::~LarvalDataFile(void) {}
LarvalDataFile::LarvalDataFile( String ^ filename )
{
  _filename = filename;
  StreamReader ^ sr = gcnew StreamReader( _filename );

  // read day and container name
  array<wchar_t> ^ delimiters = { '-', '=', ',' };
  String ^ input = sr->ReadLine();
  array<String ^> ^ tokens = input->Split( delimiters );
  _day = tokens[1]->Trim( ' ' );
  _containerName = tokens[2]->Trim( ' ' );
  _title = "Larval Data - Day - " + _day;

  // read headers
  array<wchar_t> ^ headerDelim = { '-' };
  input = sr->ReadLine();
  tokens = input ->Split( headerDelim );
  _headers = gcnew array<String^>(tokens->Length - 1);
  Array::Copy( tokens, 1, _headers , 0, tokens->Length - 1 );

  // read data
  _data = gcnew array<String ^,2>(365, _headers->Length);
  array<wchar_t> ^ dataDelim = { ',' };
  for( int i = 0; i < 365 && !sr->EndOfStream; i++ ) {
    input = sr->ReadLine();
    array<String ^> ^ columnEntries = input->Split( dataDelim, StringSplitOptions::RemoveEmptyEntries );
    for( int j = 0; j < columnEntries->Length-1; j++ ) {
      _data[i,j] = columnEntries[j+1]->Trim( ' ' );
    }
  }
}
