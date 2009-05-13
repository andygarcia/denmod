#include <string>
#include <vector>

// ================================================== //
// ExcelOutput                                        //
// Handles outputting CIMSiM results for verification //
// use in an excel spreadsheet format                 //
// ================================================== //

using namespace std;

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

  string GetOutput( OutputType output, int numDigitsPrecision );
  string GetXML( int numDigitsPrecision );
  string GetASCII( int numDigitsPrecision );

// Members
private:
  string Title;
  vector<string> Headers;
  unsigned int NumDataColumns;
  unsigned int NumDataRows;
  vector<vector<string>> Data;
};

