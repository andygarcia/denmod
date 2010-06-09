#ifndef OUTPUT_WORKSHEET_H
#define OUTPUT_WORKSHEET_H

#include <string>
#include <vector>



class Worksheet
{
// Typedefs
public:
  typedef std::vector<double> Column;
  typedef std::vector<Column>::iterator ColumnIterator;
  typedef std::vector<double> Row;

// Constructors
public:
  Worksheet( std::string title, std::vector<std::string> headers );
  virtual ~Worksheet(void);

// Methods
public:
  Worksheet& operator<<( double value );
  std::string GetSpreadsheetMl(void);
  void SaveAsText( std::string filename);
  static std::string GetIsoDateTime(void);

private:
  std::string GetAscii(void);
  std::string GetXml(void);
  std::string FormatToCs1( double value );

// Members
private:
  std::string _title;
  std::string _author;
  std::vector<std::string> _headers;
  std::vector<Column> _columns;
  int _currentColumn;

  unsigned int _numberOfRows;
  unsigned int _numberOfColumns;

public:
  // mimic DOS model precision
  static const int _precision = 7;
};

#endif
