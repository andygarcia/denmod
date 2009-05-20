#include "StdAfx.h"
#include "ExcelOutput.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;



ExcelOutput::ExcelOutput(void)
{
}



ExcelOutput::ExcelOutput( string title, vector<string> headers, int numDataRows )
{
  this->Title = title;
  this->NumDataColumns = static_cast<unsigned int>(headers.size());

  for( unsigned int i = 0; i < NumDataColumns; i++ ) {
    string temp = headers[i];
    this->Headers.push_back(temp);
  }

  this->NumDataRows = numDataRows;
  this->Data = vector<vector<string>>();
}



ExcelOutput::~ExcelOutput(void)
{
}



bool ExcelOutput::AddRow( vector<string> newRow )
{
  if( newRow.size() != NumDataColumns ) {
    // new row does not have valid number of entries
    return false;
  }

  Data.push_back( newRow );

  return true;
}



string
ExcelOutput::GetXML( int numDigitsPrecision )
{
  stringstream xmlOutput;

  xmlOutput << setprecision( numDigitsPrecision ) << uppercase;

  // save current format
  //ios_base::fmtflags originalFormat = xmlOutput.flags();

  // declaration and namespaces
  xmlOutput << "<?xml version=\"1.0\"?>" << endl;
  xmlOutput << "<?mso-application progid=\"Excel.Sheet\"?>" << endl;
  xmlOutput << "<Workbook xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\"" << endl;
  xmlOutput << " xmlns:o=\"urn:schemas-microsoft-com:office:office\"" << endl;
  xmlOutput << " xmlns:x=\"urn:schemas-microsoft-com:office:excel\"" << endl;
  xmlOutput << " xmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\"" << endl;
  xmlOutput << " xmlns:html=\"http://www.w3.org/TR/REC-html40\">" << endl;
  
  // doc props
  xmlOutput << "<DocumentProperties xmlns=\"urn:schemas-microsoft-com:office:office\">" << endl;
  xmlOutput << " <Author>parsedos</Author>" << endl;
  xmlOutput << "</DocumentProperties>" << endl;

  // default style
  xmlOutput << " <Styles>" << endl;
  xmlOutput << "  <Style ss:ID=\"Default\">" << endl;
  xmlOutput << "   <Alignment ss:Horizontal=\"Center\"/>" << endl;
  xmlOutput << "  </Style>" << endl;
  xmlOutput << " </Styles>" << endl;

  // worksheet and table
  xmlOutput << "<Worksheet ss:Name=\"" + this->Title + "\">" << endl;
  xmlOutput << "<Table ss:StyleID=\"Default\">" << endl;

  // autofit all columns
  xmlOutput << "<Column ss:Span=\"" << this->NumDataColumns + 1 << "\" ss:AutoFitWidth=\"1\"/>" << endl;

  // title
  xmlOutput << "<Row>" << endl;
  xmlOutput << " <Cell ss:MergeAcross=\"" << this->NumDataColumns + 1 << "\">"
            << "  <Data ss:Type=\"String\">" << Title << "</Data>"
            << " </Cell>"  << endl
            << "</Row>" << endl;

  // day column header
  xmlOutput << "<Row>" << endl
            << " <Cell><Data ss:Type=\"String\">" << "Day" << "</Data></Cell>" << endl;

  // data column headers
  for( vector<string>::iterator itCol = Headers.begin(); itCol != Headers.end(); ++itCol ) {
    xmlOutput << " <Cell>"
              << "  <Data ss:Type=\"String\">" << *itCol << "</Data>"
              << " </Cell>" << endl;
  }
  xmlOutput << "</Row>" << endl;

  // data rows
  int iDay = 1;
  for( vector<vector<string>>::iterator itRow = Data.begin(); itRow != Data.end(); ++itRow, ++iDay ) {
    xmlOutput << "<Row>" << endl;
    xmlOutput << "<Cell><Data ss:Type=\"Number\">" << iDay << "</Data></Cell>" << endl;
    vector<string> curRow = *itRow;
    vector<string>::iterator itCol;
    for( itCol = (*itRow).begin(); itCol != (*itRow).end(); itCol++ ) {
      xmlOutput << "<Cell><Data ss:Type=\"Number\">" << *itCol << "</Data></Cell>" << endl;
    }
    xmlOutput << "</Row>" << endl;
  }

  // close up
  xmlOutput << "</Table>" << endl;
  xmlOutput << "</Worksheet>" << endl;
  xmlOutput << "</Workbook>" << endl;

  return xmlOutput.str();
}


string ExcelOutput::GetASCII( int numDigitsPrecision )
{
  using namespace std;
  
  stringstream osOutput;

  osOutput << setprecision( numDigitsPrecision );

  int iDay = 1;
  for( vector<vector<string>>::iterator itRow = Data.begin(); itRow != Data.end(); itRow++, iDay++ ) {
    osOutput << iDay;
    vector<string> curRow = *itRow;
    vector<string>::iterator itCol;
    for( itCol = (*itRow).begin(); itCol != (*itRow).end(); itCol++ ) {
      osOutput << ' ' << *itCol;
    }
    osOutput << endl;
  }

  return osOutput.str();
}


string ExcelOutput::GetOutput( OutputType output, int numDigitsPrecision )
{
  if( output == XML )
    return GetXML( numDigitsPrecision );
  if( output == ASCII )
    return GetASCII( numDigitsPrecision );

  return "Invalid output type, please specify XML or ASCII";
}
