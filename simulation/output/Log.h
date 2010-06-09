#ifndef DENMOD_SIMULATION_OUTPUT_LOG_H
#define DENMOD_SIMULATION_OUTPUT_LOG_H

#include <string>
#include <vector>



namespace sim {
namespace output {

class Log
{
// Constructors
public:
  Log( std::string filename, std::vector<std::string> headers );
  virtual ~Log(void);

// Methods
public:
  void AddData( const int i );
  void AddData( const double d );
  void AddData( const std::string s );

  void Write( void );

// Members
private:
  std::string _filename;
  std::vector<std::string> _headers;
  size_t _headerCount;
  std::vector<std::vector<std::string>> _data;
};

};
};

#endif
