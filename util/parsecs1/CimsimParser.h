#ifndef PROCESSPRN_H
#define PROCESSPRN_H

#include <string>
#include <vector>
#include "PrnFiles.h"

using namespace System::Collections::Generic;

ref class CimsimParser
{
// Methods
public:
  CimsimParser(void);
  virtual ~CimsimParser(void);
  
  bool ParseLocation(void);
  bool ParseContainer(void);
  bool ParseSurvivals(void);
  bool ParseLarvalData(void);

  enum class OutputType { ASCII, XML };

  void OutputLocation( OutputType ot );
  void OutputContainer( OutputType ot );
  void OutputSurvivals( OutputType ot );
  void OutputLarvalData( OutputType ot );


// Members
private:
  array<LocationFile^> ^ _locationFiles;

  // maps container name and filter to data list
  List<String^> ^ _containerOutputHeaders;
  Dictionary<String^,Dictionary<String^,List<String^>^>^> ^ _containerDataByNameAndHeader;

  List<SurvivalFile^> ^ _survivalFiles;
  array<LarvalDataFile^> ^ _larvalDataFiles;

  // hardcoded filenames used by parser
  static array<String^> ^ _locationFilenames = gcnew array<String^>(5){ "FEMSHA.PRN", "FEMSHOST.PRN", "FECUND.PRN", "WEATHER.PRN", "SUADLT.PRN" };
  static array<String^> ^ _containerFilters = gcnew array<String^>(9){ "DEPTH*.PRN", "FOOD*.PRN", "EGGS*.PRN", "LARVAE*.PRN", "PUPAE*.PRN",
                                                                       "AVGPUWT*.PRN", "NEWFEMS*.PRN", "CUMFEMS*.PRN", "DLYOVI*.PRN" };
  static array<String^> ^ _survivalFilters = gcnew array<String^>(3){ "SUEGG*.PRN", "SULARV*.PRN", "SUPUP*.PRN" };
  static String ^ _larvalDataFilename = gcnew String( "LARVD*.PRN" );
};

#endif
