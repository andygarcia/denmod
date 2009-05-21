#include "StdAfx.h"
#include "ExcelWorkbook.h"

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace util;



ExcelWorkbook::ExcelWorkbook( String ^ author )
: _author(author),
  _lastAuthor(author),
  _worksheets(gcnew List<ExcelWorksheet^>())
{}



ExcelWorkbook::~ExcelWorkbook(void)
{}



void
ExcelWorkbook::AddWorksheet( ExcelWorksheet ^ worksheet )
{
  _worksheets->Add( worksheet );
}



void
ExcelWorkbook::SaveToDisk( System::IO::DirectoryInfo ^ directoryInfo, System::String ^ filename )
{
  // check if directory exists
  if( !directoryInfo->Exists ) {
    throw gcnew DirectoryNotFoundException( directoryInfo->FullName );
  }

  String ^ filepath = Path::Combine(directoryInfo->FullName, filename);
  StreamWriter ^ sw = gcnew StreamWriter( filepath );
  sw->Write( GetSpreadsheetMl() );
  sw->Close();
}



String ^
ExcelWorkbook::GetSpreadsheetMl(void)
{
   // build xml
  System::Text::StringBuilder ^ sb = gcnew System::Text::StringBuilder();

  sb->AppendLine( "<?xml version=\"1.0\"?>" );
  sb->AppendLine( "<?mso-application progid=\"Excel.Sheet\"?>" );
  sb->AppendLine( "<Workbook xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\"" );
  sb->AppendLine( " xmlns:o=\"urn:schemas-microsoft-com:office:office\"" );
  sb->AppendLine( " xmlns:x=\"urn:schemas-microsoft-com:office:excel\"" );
  sb->AppendLine( " xmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\"" );
  sb->AppendLine( " xmlns:html=\"http://www.w3.org/TR/REC-html40\">" );

  sb->AppendLine(" <DocumentProperties xmlns=\"urn:schemas-microsoft-com:office:office\">");
  sb->AppendLine("  <Author>" + _author + "</Author>" + Environment::NewLine );
  sb->AppendLine("  <LastAuthor>" + _lastAuthor + "</LastAuthor>");
  sb->AppendLine("  <Created>" + DateTime::Now.ToString("s") + "</Created>");
  sb->AppendLine("  <Version>12.00</Version>");
  sb->AppendLine(" </DocumentProperties>");

  sb->AppendLine( " <Styles>");

  // default style
  sb->AppendLine( "  <Style ss:ID=\"Default\" ss:Name=\"Normal\">" );
  sb->AppendLine( "   <Alignment ss:Vertical=\"Center\"/>" );
  sb->AppendLine( "  </Style>" );

  // date style
  sb->AppendLine( "  <Style ss:ID=\"sDate\" ss:Name=\"Date Column\">" );
  sb->AppendLine( "   <Alignment ss:Vertical=\"Center\" ss:Horizontal=\"Center\"/>" );
  sb->AppendLine( "   <NumberFormat ss:Format=\"yyyy\\-mm\\-dd\"/>" );
  sb->AppendLine( "  </Style>" );

  // class style
  sb->AppendLine( "  <Style ss:ID=\"sClass\" ss:Name=\"Class Column\">" );
  sb->AppendLine( "   <Alignment ss:Vertical=\"Center\" ss:Horizontal=\"Center\"/>" );
  sb->AppendLine( "  </Style>" );

  // number style
  sb->AppendLine( "  <Style ss:ID=\"sData\" ss:Name=\"Data Columns\">" );
  sb->AppendLine( "   <Alignment ss:Vertical=\"Center\" ss:Horizontal=\"Center\"/>" );
  sb->AppendLine( "   <NumberFormat ss:Format=\"Fixed\"/>" );
  sb->AppendLine( "  </Style>" );

  sb->AppendLine( " </Styles>" );

  for each( ExcelWorksheet ^ worksheet in _worksheets ) {
    sb->AppendLine( worksheet->GetSpreadsheetMl() );
  }

  sb->Append("</Workbook>" + Environment::NewLine);

  return sb->ToString(); 
}
