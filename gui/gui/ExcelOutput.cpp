#include "StdAfx.h"
#include "ExcelOutput.h"

using namespace System;



ExcelOutput::ExcelOutput(void)
{
}



ExcelOutput::~ExcelOutput(void)
{
}



System::String ^
ExcelOutput::GetXml( Dundas::Charting::WinControl::Chart ^ chart )
{
  System::Text::StringBuilder ^ sb = gcnew System::Text::StringBuilder();

  // write XML file header
  sb->Append("<?xml version=\"1.0\"?>" + Environment::NewLine);
  sb->Append("<?mso-application progid=\"Excel.Sheet\"?>" + Environment::NewLine);
  sb->Append("<Workbook xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\"" + Environment::NewLine);
  sb->Append(" xmlns:o=\"urn:schemas-microsoft-com:office:office\"" + Environment::NewLine);
  sb->Append(" xmlns:x=\"urn:schemas-microsoft-com:office:excel\"" + Environment::NewLine);
  sb->Append(" xmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\"" + Environment::NewLine);
  sb->Append(" xmlns:html=\"http://www.w3.org/TR/REC-html40\">" + Environment::NewLine);

  sb->Append(" <DocumentProperties xmlns=\"urn:schemas-microsoft-com:office:office\">" + Environment::NewLine);
  sb->Append("  <Author>Dengue Models</Author>" + Environment::NewLine );
  sb->Append("  <LastAuthor>Dengue Models</LastAuthor>" + Environment::NewLine);
  sb->Append("  <Created>" + DateTime::Now.ToString("s") + "</Created>" + Environment::NewLine);
  sb->Append("  <Version>12.00</Version>" + Environment::NewLine);
  sb->Append(" </DocumentProperties>" + Environment::NewLine);

  sb->AppendLine( " <Styles>");
  sb->AppendLine( "  <Style ss:ID=\"Default\" ss:Name=\"Normal\">" );
  sb->AppendLine( "   <Alignment ss:Vertical=\"Center\"/>" );
  sb->AppendLine( "  </Style>" );
  sb->AppendLine( " </Styles>" );
  sb->AppendLine( " <Worksheet ss:Name=\"Sheet1\">" );
  sb->AppendLine( "  <Table>");

  // if any data to save exists...
  if( chart->Series->Count > 0 && chart->Series[0]->Points->Count > 0 ) {

    // date header
    sb->AppendLine( "   <Row>" );
    String ^ cellString = String::Format( "    <Cell><Data ss:Type=\"String\">Date</Data></Cell>" );
    sb->AppendLine( cellString );

    // series headers
    int index = 2;
    for( int seriesIndex = 0; seriesIndex < chart->Series->Count; ++seriesIndex )
    {
      String ^ cellString = String::Format( "    <Cell><Data ss:Type=\"String\">{1}</Data></Cell>",
                                            Convert::ToString( index ),
                                            chart->Series[seriesIndex]->Name);
      sb->Append(cellString);
      sb->Append(Environment::NewLine);
      ++index;
    }
    sb->Append("   </Row>" + Environment::NewLine);


    for( int pointIndex = 0; pointIndex < chart->Series[0]->Points->Count; ++pointIndex ) {
      sb->Append("   <Row>" + Environment::NewLine);

      // date cell
      String ^ cellString = String::Format( "    <Cell><Data ss:Type=\"String\">{1}</Data></Cell>",
                                            Convert::ToString(0),
                                            DateTime::FromOADate(chart->Series[0]->Points[pointIndex]->XValue).ToString("yyyy-MM-dd") );
      sb->Append(cellString + Environment::NewLine );
      
        
      // series cells
      for( int seriesIndex = 0; seriesIndex < chart->Series->Count; ++seriesIndex ) {

        // and then all series data for that date
        if( !chart->Series[seriesIndex]->Points[pointIndex]->Empty ) {
          cellString = String::Format( "    <Cell><Data ss:Type=\"Number\">{1}</Data></Cell>",
                                       Convert::ToString(seriesIndex + 2),
                                       Convert::ToDouble(chart->Series[seriesIndex]->Points[pointIndex]->YValues[0]) );
          sb->Append(cellString + Environment::NewLine);
        }
      }

      sb->Append("   </Row>" + Environment::NewLine);
    }
  }

  // close all XML tags
  sb->Append("  </Table>" + Environment::NewLine);
  sb->Append(" </Worksheet>" + Environment::NewLine);
  sb->Append("</Workbook>" + Environment::NewLine);

  return sb->ToString();
}
