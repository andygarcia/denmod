#include "stdafx.h"
#include "Worksheet.h"
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>

#define _CRT_SECURE_NO_WARNINGS



Worksheet::Worksheet( std::string title, std::vector<std::string> headers)
: _title(title),
  _headers(headers),
  _numberOfRows(0),
  _numberOfColumns( static_cast<unsigned int>(headers.size()) )
{
  // create columns
  _columns = std::vector<Column>( _numberOfColumns );

  // start with first column for input via << operator
  _currentColumn = 0;
}



Worksheet::~Worksheet(void)
{}



Worksheet&
Worksheet::operator<<( double value )
{
  // add value to current column and advance to next
  Column & column = _columns.at( _currentColumn );
  column.push_back( value );
  ++_currentColumn;

  if( _currentColumn == _numberOfColumns ) {
    _currentColumn = 0;
    _numberOfRows++;
  }
  return *this;
}



void
Worksheet::SaveAsText( std::string filename )
{
  std::ofstream asciiFile( filename.c_str() );
  asciiFile << GetAscii();
  asciiFile.close();
}



std::string
Worksheet::GetAscii(void)
{
  using namespace std;

  stringstream ss;

  for( vector<string>::iterator itHeader = _headers.begin(); itHeader != _headers.end(); ++itHeader ) {
    ss << *itHeader << ' ';
  }
  ss << endl;

  for( unsigned int i = 0; i < _numberOfRows; ++i ) {
    ColumnIterator itCol;
    // output all columns except last along with space delimiter
    for( itCol = _columns.begin(); itCol != --(_columns.end()); ++itCol ) {
      double value = (*itCol).at(i);
      ss << FormatToCs1( value ) << ' ';
    }

    // last column has no space delimiter
    double lastColumnValue = (*itCol).at(i);
    ss << FormatToCs1( lastColumnValue );
    ss << '\n';
  }

  return ss.str();
}



std::string
Worksheet::GetSpreadsheetMl(void)
{
  std::stringstream xml;
  xml << std::setprecision( _precision ) << std::uppercase;

  // worksheet
  xml << " <Worksheet ss:Name=\"" << _title << "\">" << std::endl;

  // table
  xml << "  <Table ss:ExpandedColumnCount=\"" << _numberOfColumns + 1 << "\" ss:ExpandedRowCount=\"" << _numberOfRows + 1 << "\">";

  // column headers
  xml << "   <Row>" << std::endl;
  for( std::vector<std::string>::iterator itCol = _headers.begin(); itCol != _headers.end(); ++itCol ) {
    xml << "    <Cell ss:StyleID=\"styHeader\"><Data ss:Type=\"String\">" << *itCol << "</Data></Cell>" << std::endl;
  }
  xml << "   </Row>" << std::endl;

  // data rows
  for( unsigned int i = 0; i < _numberOfRows; ++i ) {
    xml << "   <Row>" << std::endl;
    ColumnIterator itCol;
    // output all columns except last along with space delimiter
    for( itCol = _columns.begin(); itCol != _columns.end(); ++itCol ) {
      double value = (*itCol).at(i);
      xml << "    <Cell ss:StyleID=\"styData\"><Data ss:Type=\"Number\">" << FormatToCs1(value) << "</Data></Cell>" << std::endl;
    }
    xml << "   </Row>" << std::endl;
  }

  // close up
  xml << "  </Table>" << std::endl;
  xml << " </Worksheet>" << std::endl;

  return xml.str();
}



std::string
Worksheet::FormatToCs1( double value )
{
  using namespace std;
  
  stringstream ss;
  ss << setprecision(_precision) << uppercase;

  if( value == 0 ) { 
    ss << value;
  }

  else if( (0 < value && value < 0.1) || (0 > value && value > -0.1) ) {
    ss << scientific;
    ss.precision( _precision - 1 );
    ss << value;
    string s = ss.str();

    string::size_type exponentIndex = s.find("E-0");
    if( exponentIndex != string::npos ) {
      s= s.substr(0, exponentIndex + 2) + s.substr(exponentIndex + 3);
    }
    return s;
  }

  else if( (0.1 <= value && value < 1.0) || (-0.1 >= value && value > -1.0) ) {
    ss << value;
    string s = ss.str();

    if( s.at(0) = '0' && s.at(1) == '.' ) {
      s = s.substr(1);
    }
    return s;
  }

  else if( (1.0 <= value) || (-1.0 >= value) ) {
    ss << value;
  }

  return ss.str();
}



std::string
Worksheet::GetIsoDateTime(void)
{
  time_t rawtime;
  time( &rawtime );


  struct tm * lt = localtime( &rawtime );

  std::stringstream ss;
  ss << (1900 + lt->tm_year) << "-";
  ss.fill('0');
  ss.width(2);
  ss << (1 + lt->tm_mon) << "-";
  ss.fill('0');
  ss.width(2);
  ss << lt->tm_mday << "T";
  ss.fill('0');
  ss.width(2);
  ss << lt->tm_hour << ":";
  ss.fill('0');
  ss.width(2);
  ss << lt->tm_min << ":";
  ss.fill('0');
  ss.width(2);
  ss << lt->tm_sec;
  ss.fill('0');
  ss.width(2);
  return ss.str();
}

#undef _CRT_SECURE_NO_WARNINGS
