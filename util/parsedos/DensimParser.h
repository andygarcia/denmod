#ifndef PARSEDOS_DENSIMPARSER_H
#define PARSEDOS_DENSIMPARSER_H

#include <string>
#include <vector>
#include "PrnFiles.h"

using namespace System::Collections::Generic;



ref class DensimParser
{
// Enums
public:
  enum class OutputType { ASCII, XML };

// Constructors
private:
  static DensimParser(void);
public:
  DensimParser( System::IO::DirectoryInfo ^ inputDirectory );
  virtual ~DensimParser(void);

// Methods
public:
  void Parse(void);
  void ParseDemographics(void);
  void ParseSerology(void);
  void ParseLocation(void);
  void ParseSerotypes(void);

  void SaveToDisk( OutputType outputType );

private:
  //void OutputLocation( OutputType ot );
  //void OutputContainer( OutputType ot );
  //void OutputSurvivals( OutputType ot );
  //void OutputLarvalData( OutputType ot );

// Members
private:
  bool _parseCompleted;
  System::IO::DirectoryInfo ^ _inputDirectory;
  
  static List<String^> ^ _locationFilenames;
  List<LocationFile^> ^ _locationFiles;

  ref class Demographics;
  Demographics ^ _demographics;

  ref class Serology;
  Serology ^ _initialSerology;
  Serology ^ _finalSerology;

  ref class Serotype;
  Dictionary<int,Serotype^> ^ _serotypes;


private:
  ref class Demographics
  {
  public:
    Demographics(void);
    ~Demographics(void);

  public:
    List<String^> ^ ClassIndicies;
    List<String^> ^ InitialDistribution;
    List<String^> ^ InitialDistributionPercentages;
    List<String^> ^ Births;
    List<String^> ^ BirthPercentages;
    List<String^> ^ Deaths;
    List<String^> ^ DeathPercentages;
    List<String^> ^ FinalDistribution;
    List<String^> ^ FinalDistributionPercentages;
  };

  ref class Serology
  {
  public:
    Serology(void);
    ~Serology(void);

  public:
    List<String^> ^ ClassIndicies;
    List<String^> ^ D1Number;
    List<String^> ^ D1Percent;
    List<String^> ^ D2Number;
    List<String^> ^ D2Percent;
    List<String^> ^ D3Number;
    List<String^> ^ D3Percent;
    List<String^> ^ D4Number;
    List<String^> ^ D4Percent;
    List<String^> ^ TotalInClass;
  };

  ref class Serotype
  {
  public:
    Serotype(void);
    ~Serotype(void);

  public:
    List<String^> ^ EIP;
    List<String^> ^ InfectiveMosquitoes;
    List<String^> ^ PersonsIncubating;
    List<String^> ^ PersonsViremic;
    List<String^> ^ PersonsWithVirus;

    List<String^> ^ DetailedSerologyHeaders;
    List<List<String^>^> ^ DetailedSerologyValues;
  };
};

#endif
