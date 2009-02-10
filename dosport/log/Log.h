#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>



namespace sim {
namespace output
{

  class Log
  {
  public:
    typedef std::vector<std::string> Headers;
    typedef std::vector<double> Row;
    typedef std::vector<Row> Data;

  public:
    enum LogManip { eor = 0 };

  public:
    Log(void);
    Log( std::string title );
    Log( std::string title, Headers headers );
    virtual ~Log(void);

  public:
    Log& operator<<( double input );
    Log& operator<<( LogManip logmanip );
    void AddRow( Row newRow );

    void WriteToDisk(void);
    void ClearData(void);

  private:
    std::string GetAscii(void);
    std::string GetExcelXml(void);
    std::string DosFormat( double value );
    bool IsRowEmpty( const Row & row );

  protected:
    std::string _title;
    std::vector<std::string> _headers;
    int _numberOfIndexColumns;

    Data _data;
    Row _tempRow;
    Row::size_type _rowLength;
    bool _dropEmptyRows;

    static const int _precision = 7;
  };

  class LocationLog : public Log
  {
  public:
    LocationLog(void)
    : Log()
    {
      Initialize();
    }

    LocationLog( std::string title )
    : Log( title )
    {
      Initialize();
    }

    void Initialize(void)
    {
      std::string headers[12] = {"Day","Total Females","New Females", "On Humans","On Other Hosts","On All Hosts","Fecundity",
                                 "Max Temp (C)","Min Temp (C)","Rainfall (cm)", "Rel Humidity (%)","Sat Def (mb)"};
      _headers = std::vector<std::string>( headers, headers + 12 );
    }
  };
  
  class AdultSurvivalLog : public Log
  {
  public:
    AdultSurvivalLog(void)
    : Log()
    {
      Initialize();
    }

    AdultSurvivalLog( std::string title )
    : Log( title )
    {
      Initialize();
    }

    void Initialize(void)
    {
      std::string headers[8] = {"Day","Surv Temp","Surv SD","Surv Density","Surv Overall","Tmp Max","Tmp Min","Sat Def"};
      _headers = std::vector<std::string>( headers, headers + 8 );
    }
  };

};
};

#endif
