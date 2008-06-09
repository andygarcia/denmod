#ifndef CONTAINERFILE_H
#define CONTAINERFILE_H

using namespace System;
using namespace System::Collections::Generic;

ref class LocationFile
{
public:
  LocationFile(void);
  LocationFile( String ^ fileName );
  virtual ~LocationFile(void);

public:
  String ^ _filename;
  String ^ _title;
  array<String ^> ^ _headers;
  array<String ^,2> ^ _data;
};


ref class ContainerFile
{
public:
  ContainerFile(void);
  ContainerFile( String ^ fileName );
  virtual ~ContainerFile(void);

  bool HasContainer( String ^ containerName );
  List<String^> ^ GetContainerData( String ^ containerName );

public:
  String ^ _filename;
  String ^ _title;

  int _numContainers;
  List<String ^> ^ _containerNames;
  Dictionary<String^,List<String^>^> ^ _containerData;
};


ref class SurvivalFile
{
public:
  SurvivalFile(void);
  SurvivalFile( String ^ fileName );
  virtual ~SurvivalFile(void);

public:
  String ^ _filename;
  String ^ _title;
  String ^ _containerName;
  List<String ^> ^ _headers;
  Dictionary<String^, List<String^>^> ^ _data;
};


ref class LarvalDataFile
{
public:
  LarvalDataFile(void);
  LarvalDataFile( String ^ fileName );
  virtual ~LarvalDataFile(void);

public:
  String ^ _filename;
  String ^ _title;
  String ^ _containerName;
  String ^ _day;
  array<String ^> ^ _headers;
  array<String ^,2> ^ _data;
};


#endif
