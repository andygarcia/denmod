#include "stdafx.h"
#include "ExcelWorksheet.h"

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;



static ExcelWorksheet::ExcelWorksheet(void)
{
  _typeToStyle = gcnew Dictionary<Type^,String^>();
  _typeToStyle->Add( DateTime::typeid, "sDate" );
  _typeToStyle->Add( Int32::typeid, "sClass" );
  _typeToStyle->Add( Double::typeid, "sData" );

  _typeToCellType = gcnew Dictionary<Type^,String^>();
  _typeToCellType->Add( DateTime::typeid, "DateTime" );
  _typeToCellType->Add( Int32::typeid, "Number" );
  _typeToCellType->Add( Double::typeid, "Number" );
}



ExcelWorksheet::ExcelWorksheet( System::String ^ worksheetName )
: _worksheetName(worksheetName),
  _columnHeaders(gcnew List<String^>()),
  _columnTypes(gcnew List<Type^>()),
  _columns(gcnew List<Column^>())
{}



ExcelWorksheet::~ExcelWorksheet(void)
{}



void
ExcelWorksheet::AddColumn( String ^ header, Type ^ type, Column ^ column )
{
  _columnHeaders->Add( header );
  _columnTypes->Add( type );
  _columns->Add( column );

  if( column->Count > _numberOfRows ) {
    _numberOfRows = column->Count;
  }
}



String ^
ExcelWorksheet::GetSpreadsheetMl()
{
  // column type count must match column count
  int numTypes = _columnTypes->Count;
  int numColumns = _columns->Count;
  if( numTypes != numColumns ) {
    throw gcnew InvalidDataException( "columns types and columns must have the same number of entries" );
  }

  // worksheet name in excel is limited in length to 31 characters
  String ^ worksheetName = _worksheetName;
  if( _worksheetName->Length >= 31 ) {
    worksheetName = _worksheetName->Substring(0, 31);
  }

  // generate style and types for each column
  List<String^> ^ columnStyles = gcnew List<String^>();
  List<String^> ^ columnCellTypes = gcnew List<String^>();

  for each( Type ^ t in _columnTypes ) {
    if( !_typeToStyle->ContainsKey(t) || !_typeToCellType->ContainsKey(t) ) {
      throw gcnew ArgumentException( "column types contains non alloweable types" );
    }
    else {
      columnStyles->Add( _typeToStyle[t] );
      columnCellTypes->Add( _typeToCellType[t] );
    }
  }

  // build xml
  System::Text::StringBuilder ^ sb = gcnew System::Text::StringBuilder();

  // worksheet and table info
  sb->AppendLine( " <Worksheet ss:Name=\"" + worksheetName + "\">" );
  sb->AppendLine( "  <Table ss:ExpandedColumnCount=\"" + _columns->Count + "\" ss:ExpandedRowCount=\"" + (_numberOfRows + 1) + "\">");
  for each( String ^ s in columnStyles ) {
    sb->AppendLine( "   <Column ss:StyleID=\"" + s + "\"/>" );
  }

  // header row
  sb->AppendLine( "   <Row>" );
  for( int i = 0; i < _columnHeaders->Count; ++i ) {
    int columnIndex = i + 2;
    sb->AppendLine( "    <Cell><Data ss:Type=\"String\">" + _columnHeaders[i] + "</Data></Cell>" );
  }
  sb->AppendLine( "   </Row>" );


  // data rows
  for( int i = 0; i < _numberOfRows; ++i ) {
    sb->AppendLine( "   <Row>" );

    // cells for each column
    for( int j = 0; j < _columns->Count; ++j ) {
      String ^ dataString = String::Format( "    <Cell><Data ss:Type=\"" + columnCellTypes[j] + "\">{0}</Data></Cell>", _columns[j][i] );
      sb->AppendLine( dataString );
    }
    sb->AppendLine( "   </Row>" );
  }

  // close all XML tags
  sb->Append("  </Table>" + Environment::NewLine);
  sb->Append(" </Worksheet>" + Environment::NewLine);

  return sb->ToString();
}
