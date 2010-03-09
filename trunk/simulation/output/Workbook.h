#ifndef OUTPUT_WORKBOOK_H
#define OUTPUT_WORKBOOK_H

#include <string>
#include <vector>
#include "Worksheet.h"



class Workbook
{
// Constructors
public:
  Workbook( std::string author );
  virtual ~Workbook(void);

// Methods
public:
  void AddWorksheet( Worksheet * worksheet );
  void SaveToDisk( std::string filename );

private:
  std::string GetSpreadsheetMl( void );

// Members
private:
  std::string _author;
  std::vector<Worksheet*> _worksheets;
};

#endif
