#include "stdafx.h"
#include "Log.h"

using namespace sim::output;



Log::Log(void)
{}



Log::Log( std::string title ) : _title(title)
{}



Log::Log( std::string title, Headers headers ) : _title(title), _headers(headers)
{}



Log::~Log(void) {}



Log&
Log::operator<<( double input )
{
  _tempRow.push_back( input );
  return *this;
}



Log&
Log::operator<<( LogManip logmanip )
{
  if( logmanip == eor ) {
    AddRow( _tempRow );
  }
  _tempRow.clear();
  return *this;
}



void
Log::AddRow( Row newRow )
{
  if( _data.empty() ) {
    _rowLength = newRow.size();
  }
  _data.push_back( newRow );
}



void
Log::WriteToDisk( void )
{
  std::string asciiFilename = _title + ".txt";
  std::ofstream asciiFile( asciiFilename.c_str() );
  asciiFile << GetAscii();
  asciiFile.close();

  std::string excelFilename = _title + ".xml";
  std::ofstream excelFile( excelFilename.c_str() );
  excelFile << GetExcelXml();
  excelFile.close();
}



void Log::ClearData(void)
{
  _data.clear();
}



std::string
Log::GetAscii(void)
{
  using namespace std;

  stringstream ss;

  for( vector<string>::iterator itHeader = _headers.begin(); itHeader != _headers.end(); ++itHeader ) {
    ss << *itHeader << ' ';
  }
  ss << endl;

  for( Data::iterator itRow = _data.begin(); itRow != _data.end(); itRow++ ) {
    if( _dropEmptyRows && IsRowEmpty(*itRow) )
      continue;

    Row curRec = *itRow;
    Row::iterator itValue;
    for( itValue = curRec.begin(); itValue != --curRec.end(); ++itValue ) {
      ss << DosFormat( *itValue ) << ' ';
    }
    ss << DosFormat( *itValue );
    ss << '\n';
  }

  return ss.str();
}



std::string
Log::GetExcelXml(void)
{
  std::stringstream xml;
  xml << std::setprecision( _precision ) << std::uppercase;

  // declaration and namespaces
  xml << "<?xml version=\"1.0\"?>" << std::endl;
  xml << "<?mso-application progid=\"Excel.Sheet\"?>" << std::endl;
  xml << "<Workbook xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\"" << std::endl;
  xml << " xmlns:o=\"urn:schemas-microsoft-com:office:office\"" << std::endl;
  xml << " xmlns:x=\"urn:schemas-microsoft-com:office:excel\"" << std::endl;
  xml << " xmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\"" << std::endl;
  xml << " xmlns:html=\"http://www.w3.org/TR/REC-html40\">" << std::endl;

  // doc props
  xml << "<DocumentProperties xmlns=\"urn:schemas-microsoft-com:office:office\">" << std::endl;
  xml << " <Author>\"CIMSiM 3.0\"</Author>" << std::endl;
  xml << "</DocumentProperties>" << std::endl;

  // default style
  xml << "<Styles>" << std::endl;
  xml << " <Style ss:ID=\"Default\">" << std::endl;
  xml << "  <Alignment ss:Horizontal=\"Center\"/>" << std::endl;
  xml << " </Style>" << std::endl;
  xml << "</Styles>" << std::endl;

  // worksheet and table
  xml << "<Worksheet ss:Name=\"" + _title + "\">" << std::endl;
  xml << "<Table ss:StyleID=\"Default\">" << std::endl;

  // auto fit columns
  xml << "<Column ss:Span=\"" << _rowLength + 1 << "\" ss:AutoFitWidth=\"1\"/>" << std::endl;

  // title
  xml << "<Row>" << std::endl;
  xml << " <Cell ss:MergeAcross=\"" << _rowLength + 1 << "\">" << std::endl;
  xml << "  <Data ss:Type=\"String\">" << _title << "</Data>" << std::endl;
  xml << " </Cell>" << std::endl;
  xml << "</Row>" << std::endl;

  // column headers
  xml << "<Row>" << std::endl;
  for( std::vector<std::string>::iterator itCol = _headers.begin(); itCol != _headers.end(); ++itCol ) {
    xml << " <Cell><Data ss:Type=\"String\">" << *itCol << "</Data></Cell>" << std::endl;
  }
  xml << "</Row>" << std::endl;

  // data rows
  for( Data::iterator itData = _data.begin(); itData!= _data.end(); ++itData ) {
    xml << "<Row>" << std::endl;
    Row curRec = *itData;
    Row::iterator itValue;
    for( itValue = curRec.begin(); itValue != curRec.end(); ++itValue ) {
      xml << "<Cell><Data ss:Type=\"Number\">" << DosFormat(*itValue) << "</Data></Cell>" << std::endl;
    }
    xml << "</Row>" << std::endl;
  }

  // close up
  xml << "</Table>" << std::endl;
  xml << "</Worksheet>" << std::endl;
  xml << "</Workbook>" << std::endl;

  return xml.str();
}



std::string
Log::DosFormat( double value )
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



bool
Log::IsRowEmpty( const Row & row )
{
  Row::const_iterator itRow = row.begin();
  for( int i = 0; i < _numberOfIndexColumns; ++i ) {
    ++itRow;
  }

  for( ; itRow != row.end(); ++itRow ) {
    double value = *itRow;
    if( value != 0 )
      return false;
  }
  return true;
}