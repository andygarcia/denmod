#include "StdAfx.h"
#include "Workbook.h"

#include <fstream>
#include <iomanip>
#include <sstream>



Workbook::Workbook( std::string author)
: _author(author)
{}



Workbook::~Workbook(void)
{
  for( std::vector<Worksheet*>::iterator itWs = _worksheets.begin(); itWs != _worksheets.end(); ++itWs ) {
    delete *itWs;
  }
}



void
Workbook::AddWorksheet( Worksheet * worksheet )
{
  _worksheets.push_back( worksheet );
}



void
Workbook::SaveToDisk( std::string filename )
{
  std::ofstream ofs( filename.c_str() );
  ofs << GetSpreadsheetMl();
  ofs.close();  
}



std::string
Workbook::GetSpreadsheetMl(void)
{
  std::stringstream ss;
  ss << std::setprecision( Worksheet::_precision ) << std::uppercase;

  // declaration and namespaces
  ss << "<?xml version=\"1.0\"?>" << std::endl;
  ss << "<?mso-application progid=\"Excel.Sheet\"?>" << std::endl;
  ss << "<Workbook xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\"" << std::endl;
  ss << " xmlns:o=\"urn:schemas-microsoft-com:office:office\"" << std::endl;
  ss << " xmlns:x=\"urn:schemas-microsoft-com:office:excel\"" << std::endl;
  ss << " xmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\"" << std::endl;
  ss << " xmlns:html=\"http://www.w3.org/TR/REC-html40\">" << std::endl;

  // doc props
  ss << " <DocumentProperties xmlns=\"urn:schemas-microsoft-com:office:office\">" << std::endl;
  ss << "  <Author>\"" << _author << "\"</Author>" << std::endl;
  ss << "  <LastAuthor>\"" << _author << "\"</LastAuthor>" << std::endl;
  ss << "  <Created>" << Worksheet::GetIsoDateTime() << "</Created>" << std::endl;
  ss << "  <Version>11.8036</Version>" << std::endl;
  ss << " </DocumentProperties>" << std::endl;

  ss << " <Styles>" << std::endl;

  // header style
  ss << "  <Style ss:ID=\"styHeader\">" << std::endl;
  ss << "   <Alignment ss:Horizontal=\"Center\"/>" << std::endl;
  ss << " </Style>" << std::endl;

  // day style
  ss << " <Style ss:ID=\"styDay\">" << std::endl;
  ss << "  <Alignment ss:Horizontal=\"Center\" ss:Vertical=\"Bottom\"/>" << std::endl;
  ss << " <NumberFormat ss:Format=\"0\"/>" << std::endl << "</Style>" << std::endl;

  // data style
  ss << " <Style ss:ID=\"styData\">" << std::endl;
  ss << "  <Alignment ss:Horizontal=\"Center\" ss:Vertical=\"Bottom\"/>" << std::endl;
  ss << "  <NumberFormat ss:Format=\"0.00000000\"/>" << std::endl << "</Style>" << std::endl;
  ss << " </Styles>" << std::endl;

  // worksheets
  for( std::vector<Worksheet*>::iterator itWs = _worksheets.begin(); itWs != _worksheets.end(); ++itWs ) {
    ss << (*itWs)->GetSpreadsheetMl();
  }

  // close up
  ss << "</Workbook>" << std::endl;

  return ss.str();
}
