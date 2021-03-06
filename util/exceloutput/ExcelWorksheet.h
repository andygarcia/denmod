#ifndef UTIL_EXCELOUTPUT_EXCELWORKSHEET_H
#define UTIL_EXCELOUTPUT_EXCELWORKSHEET_H



namespace util {

public ref class ExcelWorksheet
{
// Typedefs
public:
  typedef System::Collections::IList Column;

// Constructors
private:
  static ExcelWorksheet(void);
public:
  ExcelWorksheet( System::String ^ worksheetName );
  virtual ~ExcelWorksheet(void);

// Methods
public:
  void AddColumn( System::String ^ header, System::Type ^ type, Column ^ column );
  System::String ^ GetSpreadsheetMl( void );


// Members
private:
  static System::Collections::Generic::Dictionary<System::Type^,System::String^> ^ _typeToStyle;
  static System::Collections::Generic::Dictionary<System::Type^,System::String^> ^ _typeToCellType;
  
  System::String ^ _worksheetName;
  int _numberOfRows;
  System::Collections::Generic::List<System::String^> ^ _columnHeaders;
  System::Collections::Generic::List<System::Type^> ^ _columnTypes;
  System::Collections::Generic::List<Column^> ^ _columns;
};

};

#endif
