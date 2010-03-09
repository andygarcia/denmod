#include "StdAfx.h"
#include "Log.h"

#include <fstream>
#include <sstream>

using namespace sim::output;



Log::Log( std::string filename, std::vector<std::string> headers )
: _filename(filename),
  _headers(headers),
  _headerCount(headers.size()),
  _data(std::vector<std::vector<std::string>>())
{
  // add first empty row of data
  _data.push_back( std::vector<std::string>() );
}



Log::~Log(void)
{}



void
Log::AddData( const int i )
{
  std::ostringstream o;
  o << i;

  AddData( o.str() );
}



void
Log::AddData( const double d )
{
  std::ostringstream o;
  o << d;

  AddData( o.str() );
}



void
Log::AddData( const std::string s )
{
  // if current row is full, add new row
  if( _data.back().size() == _headers.size() ) {
    _data.push_back( std::vector<std::string>() );
  }

  // push data to current row
  _data.back().push_back( s );
}




void
Log::Write(void)
{
  std::ofstream ofs = std::ofstream( _filename.c_str() );

  // write headers
  for( std::vector<std::string>::iterator itHeader = _headers.begin(); itHeader != _headers.end(); ++itHeader ) {
    ofs << *itHeader << ",";
  }
  ofs << std::endl;

  // write data
  for( std::vector<std::vector<std::string>>::iterator itRow = _data.begin(); itRow != _data.end(); ++itRow ) {
    std::vector<std::string> & row = *itRow;
    for( std::vector<std::string>::iterator itColumn = row.begin(); itColumn != row.end(); ++itColumn ) {
      ofs << *itColumn << ",";
    }
    ofs << std::endl;
  }

  ofs.close();
}
