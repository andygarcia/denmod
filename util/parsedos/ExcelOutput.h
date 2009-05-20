#ifndef UTIL_PARSEDOS_EXCELOUTPUT_H
#define UTIL_PARSEDOS_EXCELOUTPUT_H

#include <string>
#include <vector>



class ExcelOutput
{
// Methods
public:
  ExcelOutput(void);
  ExcelOutput( std::string title, std::vector<std::string> headers, int numDataRows );
  virtual ~ExcelOutput(void);

  bool AddRow( std::vector<std::string> newRow );

  enum OutputType {
    ASCII = 0,
    XML = 1
  };

  std::string GetOutput( OutputType output, int numDigitsPrecision );
  std::string GetXML( int numDigitsPrecision );
  std::string GetASCII( int numDigitsPrecision );

// Members
private:
  std::string Title;
  std::vector<std::string> Headers;
  unsigned int NumDataColumns;
  unsigned int NumDataRows;
  std::vector<std::vector<std::string>> Data;
};

#endif
