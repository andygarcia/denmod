#ifndef PROCESSPRN_H
#define PROCESSPRN_H

#include <string>
#include <vector>
#include "PrnFiles.h"

using namespace System::Collections::Generic;

ref class CimsimParser
{
// Enums
public:
  enum class OutputType { ASCII, XML };

// Constructors
private:
  static CimsimParser(void);
public:
  CimsimParser( System::IO::DirectoryInfo ^ inputDirectory );
  virtual ~CimsimParser(void);

// Methods
public:
  void Parse(void);
  void SaveToDisk( OutputType outputType );

private:
  void OutputLocation( OutputType ot );
  void OutputContainer( OutputType ot );
  void OutputSurvivals( OutputType ot );
  void OutputLarvalData( OutputType ot );

// Members
private:
  bool _parseCompleted;
  System::IO::DirectoryInfo ^ _inputDirectory;
  
  List<LocationFile^> ^ _locationFiles;

  List<String^> ^ _containerNames;
  List<String^> ^ _containerHeaders;
  Dictionary<String^,Dictionary<String^,List<String^>^>^> ^ _containerData;
  Dictionary<String^,List<SurvivalFile^>^> _containerSurvivals;

  List<LarvalDataFile^> ^ _larvalDataFiles;

  static List<String^> ^ _locationFilenames;
  static List<String^> ^ _containerFilters;
  static List<String^> ^ _survivalFilters;
  static String ^ _larvalDataFilename;
};

#endif
