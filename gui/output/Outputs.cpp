#include "stdafx.h"
#include "Enums.h"
#include "Outputs.h"
#include <cmath>

using namespace gui::output;



List<DateTime> ^
DatedOutput::GetDates(void)
{
  List<DateTime> ^ dates = gcnew List<DateTime>();

  // create list of Dates
  DateTime date = _startDate;
  while( date <= _stopDate ) {
    dates->Add( date );
    date = date.AddDays(1);
  }

  return dates;
}



List<DateTime> ^
DatedOutput::GetWeeks(void)
{
  List<DateTime> ^ weeks = gcnew List<DateTime>();

  DateTime dt = DateTime( _startDate.Ticks );
  while( dt <= _stopDate ) {
    weeks->Add( dt );
    dt = dt.AddDays( 7 );
  }

  return weeks;
}



List<DateTime> ^
DatedOutput::GetMonths(void)
{
  List<DateTime> ^ months = gcnew List<DateTime>();

  DateTime dt = DateTime( _startDate.Year, _startDate.Month, 1 );
  while( dt <= _stopDate ) {
    months->Add( dt );
    dt = dt.AddMonths( 1 );
  }

  return months;
}



Collections::Generic::List<double> ^ 
DatedOutput::GetWeeklyData( TimePeriodFunction function )
{
  Collections::Generic::List<double> ^ weeklyData = gcnew Collections::Generic::List<double>();

  int numDays = _data->Count;
  int intervalSize = 7;

  // go from current date for period of 7 days (include current day)
  for( int i = 0; i < numDays; i += intervalSize ) {

    // get data for current week
    int count = numDays - i >= intervalSize ? intervalSize : numDays - i;
    Collections::Generic::List<double> ^ week = _data->GetRange( i, count );

    // sum and average current week
    double sum = 0.0;
    for each( double d in week ) {
      sum += d;
    }

    if( function == TimePeriodFunction::Sum ) {
      weeklyData->Add( sum );
    }
    else if( function == TimePeriodFunction::Average ) {
      double average = sum / week->Count;
      weeklyData->Add( average );
    }
    else {
      throw gcnew ArgumentException( "function not found" );
    }
  }

  return weeklyData;
}



Collections::Generic::List<double> ^ 
DatedOutput::GetMonthlyData( TimePeriodFunction function )
{
  Collections::Generic::List<double> ^ monthlyData = gcnew Collections::Generic::List<double>();

  // end of the month is one day before the start of the next month
  DateTime endOfMonth = DateTime( _startDate.Year, _startDate.Month, 1 ).AddMonths( 1 ).AddDays( -1 );
  int i = 0;
  for( DateTime dt = _startDate; dt <= _stopDate; ) {

    // interval for the last month can end at some specified
    // stopDate and not neccesarily the end of the month
    if( endOfMonth > _stopDate ) {
      endOfMonth = _stopDate;
    }

    int count = (endOfMonth - dt).Days + 1;

    // get data for current month
    Collections::Generic::List<double> ^ month = _data->GetRange( i, count );

    // sum and average current month
    double sum = 0.0;
    for each( double d in month ) {
      sum += d;
    }
    if( function == TimePeriodFunction::Sum ) {
      monthlyData->Add( sum );
    }
    else if ( function == TimePeriodFunction::Average ) {
      double average = sum / month->Count;
      monthlyData->Add( average );
    }
    else {
      throw gcnew ArgumentException( "function not found" );
    }

    // next interval begins on the day after end of the current month
    i = i + count;
    dt = endOfMonth.AddDays( 1 );
    // and goes to the end of the next month
    endOfMonth = dt.AddMonths( 1 ).AddDays( -1 );
  }

  return monthlyData;
}



SimOutput::SimOutput( String ^ name, DateTime startDate, DateTime stopDate )
: _name(name),
  _startDate(startDate),
  _stopDate(stopDate),
  _numberOfDays((stopDate - startDate).Days + 1),
  _dates(gcnew Collections::Generic::List<DateTime>()),
  _typeToStyle(gcnew Dictionary<Type^,String^>()),
  _typeToCellType(gcnew Dictionary<Type^,String^>())
{

  // create list of Dates
  DateTime date = _startDate;
  while( date <= _stopDate ) {
    _dates->Add( date );
    date = date.AddDays(1);
  }

  _typeToStyle->Add( DateTime::typeid, "sDate" );
  _typeToStyle->Add( Int32::typeid, "sClass" );
  _typeToStyle->Add( Double::typeid, "sData" );

  _typeToCellType->Add( DateTime::typeid, "DateTime" );
  _typeToCellType->Add( Int32::typeid, "Number" );
  _typeToCellType->Add( Double::typeid, "Number" );
}



SimOutput::~SimOutput(void)
{}



void
SimOutput::GenerateWeeks(void)
{
  _weeks = gcnew Collections::Generic::List<DateTime>();

  DateTime dt = DateTime( _startDate.Ticks );
  while( dt <= _stopDate ) {
    _weeks->Add( dt );
    dt = dt.AddDays( 7 );
  }
}



void
SimOutput::GenerateMonths(void)
{
  _months = gcnew Collections::Generic::List<DateTime>();

  DateTime dt = DateTime( _startDate.Year, _startDate.Month, 1 );
  while( dt <= _stopDate ) {
    _months->Add( dt );
    dt = dt.AddMonths( 1 );
  }
}



String ^
SimOutput::GenerateExcelDateXml( List<String^> ^ headers, List<DateTime> ^ dates, List<array<double>^> ^ columns )
{
  // add date column
  int columnCount = columns->Count + 1;

  if( headers->Count != columnCount ) {
    // add one to account for data column
    throw gcnew InvalidOperationException( "header count exceeds date and column total" );
  }

  // build xml
  System::Text::StringBuilder ^ sb = gcnew System::Text::StringBuilder();

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
  // default style
  sb->AppendLine( "  <Style ss:ID=\"Default\" ss:Name=\"Normal\">" );
  sb->AppendLine( "   <Alignment ss:Vertical=\"Center\"/>" );
  sb->AppendLine( "  </Style>" );
  // date style
  sb->AppendLine( "  <Style ss:ID=\"sDate\" ss:Name=\"Date Column\">" );
  sb->AppendLine( "   <Alignment ss:Vertical=\"Center\" ss:Horizontal=\"Center\"/>" );
  sb->AppendLine( "   <NumberFormat ss:Format=\"yyyy\\-mm\\-dd\"/>" );
  sb->AppendLine( "  </Style>" );
  // number style
  sb->AppendLine( "  <Style ss:ID=\"sData\" ss:Name=\"Data Columns\">" );
  sb->AppendLine( "   <Alignment ss:Vertical=\"Center\" ss:Horizontal=\"Center\"/>" );
  sb->AppendLine( "   <NumberFormat ss:Format=\"Fixed\"/>" );
  sb->AppendLine( "  </Style>" );

  sb->AppendLine( " </Styles>" );

  sb->AppendLine( " <Worksheet ss:Name=\"Sheet1\">" );
  sb->AppendLine( "  <Table ss:ExpandedColumnCount=\"" + columnCount + "\" ss:ExpandedRowCount=\"" + (dates->Count + 1) + "\">");
  sb->AppendLine( "   <Column ss:StyleID=\"sDate\"/>" );
  sb->AppendLine( "   <Column ss:StyleID=\"sData\" ss:Span=\"" + (columnCount - 2) + "\"/>" );

  // if any data to save exists...
  if( columns->Count > 0 && dates->Count > 0 ) {

    // header row
    sb->AppendLine( "   <Row>" );
    for( int i = 0; i < headers->Count; ++i ) {
      int columnIndex = i + 2;
      String ^ cellString = String::Format( "    <Cell><Data ss:Type=\"String\">{1}</Data></Cell>", Convert::ToString( columnIndex ), headers[i] );
      sb->AppendLine( cellString );
    }
    sb->AppendLine( "   </Row>" );


    // data rows
    for( int i = 0; i < dates->Count; ++i ) {
      sb->AppendLine( "   <Row>" );

      // date cell
      String ^ cellString = String::Format( "    <Cell><Data ss:Type=\"DateTime\">{1}</Data></Cell>", Convert::ToString(0), dates[i].ToString("yyyy-MM-dd") );
      //dates[i].ToString("yyyy-MM-dd")
      sb->AppendLine( cellString );
      
      // data cells
      for( int j = 0; j < columns->Count; ++j ) {
        cellString = String::Format( "    <Cell><Data ss:Type=\"Number\">{1}</Data></Cell>",
                                     Convert::ToString( j + 2 ),
                                     Convert::ToDouble( columns[j][i] ));
        sb->AppendLine( cellString );
      }
      sb->AppendLine( "   </Row>" );
    }
  }

  // close all XML tags
  sb->Append("  </Table>" + Environment::NewLine);
  sb->Append(" </Worksheet>" + Environment::NewLine);
  sb->Append("</Workbook>" + Environment::NewLine);

  return sb->ToString();
}



String ^
SimOutput::GenerateExcelClassXml( List<String^> ^ headers, List<String^> ^ indices, List<array<double>^> ^ columns )
{
  // headers should equal number of columns plus one more for class column
  int columnCount = columns->Count + 1;
  if( headers->Count != columnCount ) {
    // add one to account for data column
    throw gcnew InvalidOperationException( "header count exceeds index and column total" );
  }

  // build xml
  System::Text::StringBuilder ^ sb = gcnew System::Text::StringBuilder();

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

  sb->AppendLine( " <Worksheet ss:Name=\"Sheet1\">" );
  sb->AppendLine( "  <Table ss:ExpandedColumnCount=\"" + columnCount + "\" ss:ExpandedRowCount=\"" + (indices->Count + 1) + "\">");
  sb->AppendLine( "   <Column ss:StyleID=\"sIndex\"/>" );
  sb->AppendLine( "   <Column ss:StyleID=\"sData\" ss:Span=\"" + (columnCount - 2) + "\"/>" );


  // header row
  sb->AppendLine( "   <Row>" );
  for( int i = 0; i < headers->Count; ++i ) {
    int columnIndex = i + 2;
    sb->AppendLine( "    <Cell><Data ss:Type=\"String\">" + headers[i] + "</Data></Cell>" );
  }
  sb->AppendLine( "   </Row>" );


  // data rows
  for( int i = 0; i < indices->Count; ++i ) {
    sb->AppendLine( "   <Row>" );

    // index cell
    sb->AppendLine( "    <Cell><Data ss:Type=\"Number\">" + indices[i] + "</Data></Cell>" );
    
    // data cells
    for( int j = 0; j < columns->Count; ++j ) {
      String ^ dataString = String::Format( "    <Cell><Data ss:Type=\"Number\">{0}</Data></Cell>", columns[j][i] );
      sb->AppendLine( dataString );
    }
    sb->AppendLine( "   </Row>" );
  }

  // close all XML tags
  sb->Append("  </Table>" + Environment::NewLine);
  sb->Append(" </Worksheet>" + Environment::NewLine);
  sb->Append("</Workbook>" + Environment::NewLine);

  return sb->ToString();

}



String ^
SimOutput::GenerateWorkbook( List<String^> ^ worksheetXmls )
{
   // build xml
  System::Text::StringBuilder ^ sb = gcnew System::Text::StringBuilder();

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

  for each( String ^ worksheetXml in worksheetXmls ) {
    sb->AppendLine( worksheetXml );
  }

  sb->Append("</Workbook>" + Environment::NewLine);

  return sb->ToString(); 
}



String ^
SimOutput::GenerateWorksheet( String ^ worksheetName, List<Type^> ^ columnTypes, List<String^> ^ headers, List<List<String^>^> ^ columns )
{
  // all three List arguments should have identical count
  if( (columnTypes->Count != headers->Count) || (headers->Count != columns->Count) ) {
    throw gcnew ArgumentException( "column types, headers, and columns are not the same size" );
  }

  // worksheet name in excel is limited in length to 31 characters
  if( worksheetName->Length >= 31 ) {
    worksheetName = worksheetName->Substring(0, 31);
  }

  // generate style and types for each column
  List<String^> ^ columnStyles = gcnew List<String^>();
  List<String^> ^ columnCellTypes = gcnew List<String^>();

  for each( Type ^ t in columnTypes ) {
    if( !_typeToStyle->ContainsKey(t) || !_typeToCellType->ContainsKey(t) ) {
      throw gcnew ArgumentException( "column types contains non alloweable types" );
    }
    else {
      columnStyles->Add( _typeToStyle[t] );
      columnCellTypes->Add( _typeToCellType[t] );
    }
  }

  // get number of rows
  int numDataRows = columns[0]->Count;


  // build xml
  System::Text::StringBuilder ^ sb = gcnew System::Text::StringBuilder();

  // worksheet and table info
  sb->AppendLine( " <Worksheet ss:Name=\"" + worksheetName + "\">" );
  sb->AppendLine( "  <Table ss:ExpandedColumnCount=\"" + columns->Count + "\" ss:ExpandedRowCount=\"" + (numDataRows + 1) + "\">");
  for each( String ^ s in columnStyles ) {
    sb->AppendLine( "   <Column ss:StyleID=\"" + s + "\"/>" );
  }

  // header row
  sb->AppendLine( "   <Row>" );
  for( int i = 0; i < headers->Count; ++i ) {
    int columnIndex = i + 2;
    sb->AppendLine( "    <Cell><Data ss:Type=\"String\">" + headers[i] + "</Data></Cell>" );
  }
  sb->AppendLine( "   </Row>" );


  // data rows
  for( int i = 0; i < numDataRows; ++i ) {
    sb->AppendLine( "   <Row>" );

    // cells for each column
    for( int j = 0; j < columns->Count; ++j ) {
      String ^ dataString = String::Format( "    <Cell><Data ss:Type=\"" + columnCellTypes[j] + "\">{0}</Data></Cell>", columns[j][i] );
      sb->AppendLine( dataString );
    }
    sb->AppendLine( "   </Row>" );
  }

  // close all XML tags
  sb->Append("  </Table>" + Environment::NewLine);
  sb->Append(" </Worksheet>" + Environment::NewLine);

  return sb->ToString();

}
