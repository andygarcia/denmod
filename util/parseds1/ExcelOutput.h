#include <string>
#include <vector>

// ================================================== //
// ExcelOutput                                        //
// Handles outputting CIMSiM results for verification //
// use in an excel spreadsheet format                 //
// ================================================== //


class Header;
typedef std::vector<Header*> HeaderRow;

class ExcelOutput
{
// Methods
public:
  ExcelOutput(void);
  ExcelOutput( std::string title, int numCols, int numDataRows, std::vector<std::vector<Header>> headers );
  virtual ~ExcelOutput(void);

  bool AddHeader( Header header );
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
  std::string Filename_;
  std::string Title_;
  unsigned int NumColumns_;

  unsigned int NumHeaderRows_;
  std::vector<std::vector<Header>> Headers_;

  unsigned int NumDataRows_;
  std::vector<std::vector<std::string>> Data_;
};


class Header
{
public:
  Header( int columnIndex, int width, int height, std::string text );

  int GetColumnIndex(void) { return this->ColumnIndex_; }
  int GetWidth(void) { return this->Width_; }
  int GetHeight(void) { return this->Height_; }
  std::string GetText(void) { return this->Text_; }

private:
  int ColumnIndex_;
  int Width_;
  int Height_;
  std::string Text_;
};
