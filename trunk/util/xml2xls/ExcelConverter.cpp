#include "StdAfx.h"
#include "ExcelConverter.h"

using namespace xml2xls;
using namespace System;
using namespace Microsoft::Office::Interop;



ExcelConverter::ExcelConverter(void)
: _excelApplication(gcnew Excel::Application())
{
  _excelApplication->DisplayAlerts = false;
}



ExcelConverter::~ExcelConverter(void)
{}



void
ExcelConverter::Convert( String ^ sourceFilename, Excel::XlFileFormat sourceFormat,
                         String ^ targetFilename, Excel::XlFileFormat targetFormat, bool deleteSource )
{
  // open and disable compatability check
  Excel::Workbook ^ sourceFile = _excelApplication->Workbooks->Open( sourceFilename, Type::Missing, Type::Missing,
                                                                     Type::Missing, Type::Missing, Type::Missing,
                                                                     Type::Missing, Type::Missing, Type::Missing,
                                                                     Type::Missing, Type::Missing, Type::Missing,
                                                                     Type::Missing, Type::Missing, Type::Missing );
  sourceFile->CheckCompatibility = false;

  // save in desired format and close
  sourceFile->SaveAs( targetFilename, targetFormat, Type::Missing, Type::Missing, Type::Missing, false, Excel::XlSaveAsAccessMode::xlNoChange, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing );
  _excelApplication->Workbooks->Close();

  // optionaly delete
  if( deleteSource ) {
    IO::File::Delete( sourceFilename );
  }
}
