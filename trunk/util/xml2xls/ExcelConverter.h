#ifndef UTIL_XML2XLS_EXCELCONVERT_H
#define UTIL_XML2XLS_EXCELCONVERT_H

namespace xml2xls {

ref class ExcelConverter
{
public:
  ExcelConverter(void);
  virtual ~ExcelConverter(void);

public:
  void Convert( System::String ^ sourceFilename,
                Microsoft::Office::Interop::Excel::XlFileFormat sourceFormat,
                System::String ^ targetFilename,
                Microsoft::Office::Interop::Excel::XlFileFormat targetFormat,
                bool deleteSource );

private:
  Microsoft::Office::Interop::Excel::Application ^ _excelApplication;
};

};

#endif
