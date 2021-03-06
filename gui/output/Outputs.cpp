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



void
SimOutput::WriteDailyWorksheet( IO::StreamWriter ^ sw, String ^ worksheetName, List<String^> ^ headers, List<DateTime> ^ dates, List<array<double>^> ^ columns )
{
  // add date column
  int columnCount = columns->Count + 1;

  if( headers->Count != columnCount ) {
    // add one to account for data column
    throw gcnew InvalidOperationException( "header count exceeds date and column total" );
  }

  // write worksheet xml
  sw->WriteLine( " <Worksheet ss:Name=\"" + worksheetName + "\">" );
  sw->WriteLine( "  <Table ss:ExpandedColumnCount=\"" + columnCount + "\" ss:ExpandedRowCount=\"" + (dates->Count + 1) + "\">");
  sw->WriteLine( "   <Column ss:StyleID=\"sDate\"/>" );
  sw->WriteLine( "   <Column ss:StyleID=\"sData\" ss:Span=\"" + (columnCount - 2) + "\"/>" );

  // if any data to save exists...
  if( columns->Count > 0 && dates->Count > 0 ) {

    // header row
    sw->WriteLine( "   <Row>" );
    for( int i = 0; i < headers->Count; ++i ) {
      int columnIndex = i + 2;
      String ^ cellString = String::Format( "    <Cell><Data ss:Type=\"String\">{1}</Data></Cell>", Convert::ToString( columnIndex ), headers[i] );
      sw->WriteLine( cellString );
    }
    sw->WriteLine( "   </Row>" );


    // data rows
    for( int i = 0; i < dates->Count; ++i ) {
      sw->WriteLine( "   <Row>" );

      // date cell
      String ^ cellString = String::Format( "    <Cell><Data ss:Type=\"DateTime\">{1}</Data></Cell>", Convert::ToString(0), dates[i].ToString("yyyy-MM-dd") );
      //dates[i].ToString("yyyy-MM-dd")
      sw->WriteLine( cellString );
      
      // data cells
      for( int j = 0; j < columns->Count; ++j ) {
        cellString = String::Format( "    <Cell><Data ss:Type=\"Number\">{1}</Data></Cell>",
                                     Convert::ToString( j + 2 ),
                                     Convert::ToDouble( columns[j][i] ));
        sw->WriteLine( cellString );
      }
      sw->WriteLine( "   </Row>" );
    }
  }

  // close all XML tags
  sw->WriteLine( "  </Table>" );
  sw->WriteLine( " </Worksheet>" );
}



void
SimOutput::WriteClassWorksheet( IO::StreamWriter ^ sw, String ^ worksheetName, List<String^> ^ headers, List<String^> ^ indices, List<array<double>^> ^ columns )
{
  // headers should equal number of columns plus one more for class column
  int columnCount = columns->Count + 1;
  if( headers->Count != columnCount ) {
    // add one to account for data column
    throw gcnew InvalidOperationException( "header count exceeds index and column total" );
  }

  sw->WriteLine( " <Worksheet ss:Name=\"" + worksheetName + "\">" );
  sw->WriteLine( "  <Table ss:ExpandedColumnCount=\"" + columnCount + "\" ss:ExpandedRowCount=\"" + (indices->Count + 1) + "\">");
  sw->WriteLine( "   <Column ss:StyleID=\"sClass\"/>" );
  sw->WriteLine( "   <Column ss:StyleID=\"sData\" ss:Span=\"" + (columnCount - 2) + "\"/>" );


  // header row
  sw->WriteLine( "   <Row>" );
  for( int i = 0; i < headers->Count; ++i ) {
    int columnIndex = i + 2;
    sw->WriteLine( "    <Cell><Data ss:Type=\"String\">" + headers[i] + "</Data></Cell>" );
  }
  sw->WriteLine( "   </Row>" );


  // data rows
  for( int i = 0; i < indices->Count; ++i ) {
    sw->WriteLine( "   <Row>" );

    // index cell
    sw->WriteLine( "    <Cell><Data ss:Type=\"Number\">" + indices[i] + "</Data></Cell>" );
    
    // data cells
    for( int j = 0; j < columns->Count; ++j ) {
      String ^ dataString = String::Format( "    <Cell><Data ss:Type=\"Number\">{0}</Data></Cell>", columns[j][i] );
      sw->WriteLine( dataString );
    }
    sw->WriteLine( "   </Row>" );
  }

  // close all XML tags
  sw->WriteLine( "  </Table>" );
  sw->WriteLine( " </Worksheet>" );
}



void
SimOutput::WriteWorkbookOpen( IO::StreamWriter ^ sw )
{
  sw->WriteLine( "<?xml version=\"1.0\"?>" );
  sw->WriteLine( "<?mso-application progid=\"Excel.Sheet\"?>" );
  sw->WriteLine( "<Workbook xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\"" );
  sw->WriteLine( " xmlns:o=\"urn:schemas-microsoft-com:office:office\"" );
  sw->WriteLine( " xmlns:x=\"urn:schemas-microsoft-com:office:excel\"" );
  sw->WriteLine( " xmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\"" );
  sw->WriteLine( " xmlns:html=\"http://www.w3.org/TR/REC-html40\">" );

  sw->WriteLine( " <DocumentProperties xmlns=\"urn:schemas-microsoft-com:office:office\">" );
  sw->WriteLine( "  <Author>Dengue Models</Author>" );
  sw->WriteLine( "  <LastAuthor>Dengue Models</LastAuthor>" );
  sw->WriteLine( "  <Created>" + DateTime::Now.ToString("s") + "</Created>" );
  sw->WriteLine( "  <Version>12.00</Version>" );
  sw->WriteLine( " </DocumentProperties>" );
}



void
SimOutput::WriteWorkbookClose( IO::StreamWriter ^ sw )
{
  sw->WriteLine( "</Workbook>" );
}




void
SimOutput::WriteWorkbookStyles( IO::StreamWriter ^ sw )
{
  // open
  sw->WriteLine( " <Styles>" );

  // default style
  sw->WriteLine( "  <Style ss:ID=\"Default\" ss:Name=\"Normal\">" );
  sw->WriteLine( "   <Alignment ss:Vertical=\"Center\"/>" );
  sw->WriteLine( "  </Style>" );

  // date style
  sw->WriteLine( "  <Style ss:ID=\"sDate\" ss:Name=\"Date Column\">" );
  sw->WriteLine( "   <Alignment ss:Vertical=\"Center\" ss:Horizontal=\"Center\"/>" );
  sw->WriteLine( "   <NumberFormat ss:Format=\"yyyy\\-mm\\-dd\"/>" );
  sw->WriteLine( "  </Style>" );

  // class style
  sw->WriteLine( "  <Style ss:ID=\"sClass\" ss:Name=\"Class Column\">" );
  sw->WriteLine( "   <Alignment ss:Vertical=\"Center\" ss:Horizontal=\"Center\"/>" );
  sw->WriteLine( "  </Style>" );

  // number style
  sw->WriteLine( "  <Style ss:ID=\"sData\" ss:Name=\"Data Columns\">" );
  sw->WriteLine( "   <Alignment ss:Vertical=\"Center\" ss:Horizontal=\"Center\"/>" );
  sw->WriteLine( "   <NumberFormat ss:Format=\"Fixed\"/>" );
  sw->WriteLine( "  </Style>" );

  // close
  sw->WriteLine( " </Styles>" );
}