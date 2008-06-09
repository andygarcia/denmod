#include "StdAfx.h"
#include "ExcelOutput.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;


ExcelOutput::ExcelOutput(void) {}



ExcelOutput::~ExcelOutput(void) {}



ExcelOutput::ExcelOutput( std::string title, int numCols, int numDataRows, std::vector<std::vector<Header>> headers )
{
  this->Title_ = title;
  this->NumColumns_ = numCols;

  //for( unsigned int i = 0; i < NumColumns_; i++ ) {
  //  string temp = headers[i];
  //  this->Headers.push_back(temp);
  //}
  this->NumHeaderRows_ = headers.size();
  Headers_ = headers;


  this->NumDataRows_ = numDataRows;
  this->Data_ = vector<vector<string>>();
}



bool ExcelOutput::AddRow( vector<string> newRow )
{
  if( newRow.size() != NumColumns_ ) {
    // new row does not have valid number of entries
    return false;
  }

  Data_.push_back( newRow );
  return true;
}



string ExcelOutput::GetXML( int numDigitsPrecision )
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
  xmlOutput << "<Author>CIMSiM 3.0</Author>" << endl;
  xmlOutput << "<LastAuthor>CIMSiM 3.0</LastAuthor>" << endl;
  xmlOutput << "<Created>2006-05-23T14:47:19Z</Created>" << endl;
  xmlOutput << "<Version>11.8036</Version>" << endl;
  xmlOutput << "</DocumentProperties>" << endl;

  // header styles
  xmlOutput << "<Styles>" << endl;
  xmlOutput << "<Style ss:ID=\"styHeader1\">" << endl;
  xmlOutput << "<Alignment ss:Horizontal=\"Center\" ss:Vertical=\"Center\"/>" << endl;
  xmlOutput << "<Borders>" << "<Border ss:Position=\"Bottom\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/>"
            << "<Border ss:Position=\"Left\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/>"
            << "<Border ss:Position=\"Right\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/>"
            << "<Border ss:Position=\"Top\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/>"
            << "</Borders>" << endl;
  xmlOutput << "<Interior ss:Color=\"#99CCFF\" ss:Pattern=\"Solid\"/>" << endl;     // blue
  xmlOutput << "<Font ss:Size=\"14\"/>" << endl;
  xmlOutput << "</Style>" << endl;

  xmlOutput << "<Style ss:ID=\"styHeader2\">" << endl;
  xmlOutput << "<Alignment ss:Horizontal=\"Center\" ss:Vertical=\"Center\"/>" << endl;
  xmlOutput << "<Borders>" << "<Border ss:Position=\"Bottom\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/>"
            << "<Border ss:Position=\"Left\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/>"
            << "<Border ss:Position=\"Right\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/>"
            << "<Border ss:Position=\"Top\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/>"
            << "</Borders>" << endl;
  xmlOutput << "<Interior ss:Color=\"#CCFFCC\" ss:Pattern=\"Solid\"/>" << endl;   // green
  xmlOutput << "</Style>" << endl;

  xmlOutput << "<Style ss:ID=\"styHeader3\">" << endl;
  xmlOutput << "<Alignment ss:Horizontal=\"Center\" ss:Vertical=\"Center\"/>" << endl;
  xmlOutput << "<Borders>" << "<Border ss:Position=\"Bottom\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/>"
            << "<Border ss:Position=\"Left\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/>"
            << "<Border ss:Position=\"Right\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/>"
            << "<Border ss:Position=\"Top\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/>"
            << "</Borders>" << endl;
  xmlOutput << "<Interior ss:Color=\"#CC99FF\" ss:Pattern=\"Solid\"/>" << endl;   // purple
  xmlOutput << "</Style>" << endl;

  // table index style
  xmlOutput << "<Style ss:ID=\"styIndex\">" << endl;
  xmlOutput << "<Alignment ss:Horizontal=\"Center\" ss:Vertical=\"Bottom\"/>" << endl;
  xmlOutput << "<NumberFormat ss:Format=\"0\"/>" << endl << "</Style>" << endl;

  // table data style
  xmlOutput << "<Style ss:ID=\"styData\">" << endl;
  xmlOutput << "<Alignment ss:Horizontal=\"Center\" ss:Vertical=\"Bottom\"/>" << endl;
  xmlOutput << "<NumberFormat ss:Format=\"0.00000000\"/>" << endl << "</Style>" << endl;
  xmlOutput << "</Styles>" << endl;

  // worksheet
  xmlOutput << "<Worksheet ss:Name=\"" + Title_ + "\">" << endl;

  // table
  xmlOutput << "<Table"
            //<< " ss:ExpandedColumnCount=\"" << NumColumns_ /*11*/ /*_columnHeaders.size()*/ << "\""
            //<< " ss:ExpandedRowCount=\"" << (NumHeaderRows_ + NumDataRows_) << "\""
            //<< " ss:FullColumns=\"" << 1 << "\""
            << ">";

  // set column style and size (autofit)
  xmlOutput << "<Column ss:Index=\"1\" ss:StyleID=\"styIndex\" ss:AutoFitWidth=\"1\"/>" << endl;
  xmlOutput << "<Column ss:Index=\"2\" ss:StyleID=\"styData\" ss:Span=\"" << (NumColumns_ - 1) << "\" ss:AutoFitWidth=\"1\"/>" << endl;

  // header rows
  std::vector<Header> firstHeaderRow = Headers_.at(0);
  xmlOutput << "<Row ss:AutoFitHeight=\"0\" ss:Height=\"40.5\">" << endl;
  for( std::vector<Header>::iterator itHeader = firstHeaderRow.begin(); itHeader != firstHeaderRow.end(); ++itHeader ) {
    xmlOutput << "<Cell ss:Index=\"" << itHeader->GetColumnIndex() << "\""
              << " ss:MergeAcross=\"" << (itHeader->GetWidth() - 1) << "\""
              << " ss:MergeDown=\"" << (itHeader->GetHeight() - 1) << "\""
              << " ss:StyleID=\"styHeader1\">"
              << "<Data ss:Type=\"String\">" << Title_ << "</Data></Cell>" << endl; 
  }
  xmlOutput << "</Row>" << endl;

  std::vector<Header> secondHeaderRow = Headers_.at(1);
  xmlOutput << "<Row>" << endl;
  for( std::vector<Header>::iterator itHeader = secondHeaderRow.begin(); itHeader != secondHeaderRow.end(); ++itHeader ) {
    xmlOutput << "<Cell ss:Index=\"" << itHeader->GetColumnIndex() << "\""
              << " ss:MergeAcross=\"" << (itHeader->GetWidth() - 1) << "\""
              << " ss:MergeDown=\"" << (itHeader->GetHeight() - 1) << "\""
              << " ss:StyleID=\"" << ((Headers_.size() == 3) ? "styHeader3" : "styHeader2") << "\">"
              << "<Data ss:Type=\"String\">" << itHeader->GetText() << "</Data></Cell>" << endl;    
  }
  xmlOutput << "</Row>" << endl;

  if( Headers_.size() > 2 ) {
    std::vector<Header> thirdHeaderRow = Headers_.at(2);
    xmlOutput << "<Row>" << endl;
    for( std::vector<Header>::iterator itHeader = thirdHeaderRow.begin(); itHeader != thirdHeaderRow.end(); ++itHeader ) {
      xmlOutput << "<Cell ss:Index=\"" << itHeader->GetColumnIndex() << "\""
                << " ss:MergeAcross=\"" << (itHeader->GetWidth() - 1) << "\""
                << " ss:MergeDown=\"" << (itHeader->GetHeight() - 1) << "\""
                << " ss:StyleID=\"" << ((Headers_.size() == 2) ? "styHeader3" : "styHeader2") << "\">"
                << "<Data ss:Type=\"String\">" << itHeader->GetText() << "</Data></Cell>" << endl;    
    }
    xmlOutput << "</Row>" << endl;
  }

  // data rows
  for( vector<vector<string>>::iterator itRow = Data_.begin(); itRow != Data_.end(); ++itRow ) {
    xmlOutput << "<Row>" << endl;
    vector<string> curRow = *itRow;
    vector<string>::iterator itCol = itRow->begin();
    xmlOutput << "<Cell ss:StyleID=\"styIndex\"><Data ss:Type=\"Number\">" << curRow.at(0) << "</Data></Cell>" << endl;


    for( ++itCol; itCol != (*itRow).end(); ++itCol ) {
      xmlOutput << "<Cell ss:StyleID=\"styData\"><Data ss:Type=\"Number\">" << *itCol << "</Data></Cell>" << endl;
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

  for( vector<vector<string>>::iterator itRow = Data_.begin(); itRow != Data_.end(); itRow++ ) {
    vector<string> curRow = *itRow;
    vector<string>::iterator itCol = itRow->begin();
    osOutput << *itCol;
    for( ++itCol; itCol != (*itRow).end(); ++itCol ) {
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



Header::Header( int columnIndex, int width, int height, std::string text )
{
  this->ColumnIndex_ = columnIndex;
  this->Width_ = width;
  this->Height_ = height;
  this->Text_ = text;
}
