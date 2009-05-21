#ifndef UTIL_PARSEDOS_EXCELWORKBOOK_H
#define UTIL_PARSEDOS_EXCELWORKBOOK_H

#include "ExcelWorksheet.h"



ref class ExcelWorkbook
{
// Constructors
public:
  ExcelWorkbook( System::String ^ author );
  virtual ~ExcelWorkbook(void);

// Methods
public:
  void AddWorksheet( ExcelWorksheet ^ worksheet );
  void SaveToDisk( System::IO::DirectoryInfo ^ directoryInfo, System::String ^ filename );
  System::String ^ GetSpreadsheetMl( void );


// Members
private:
  System::String ^ _author;
  System::String ^ _lastAuthor;

  System::Collections::Generic::List<ExcelWorksheet^> ^ _worksheets;
};

#endif
