#ifndef CONTAINERFILE_H
#define CONTAINERFILE_H

using namespace System;
using namespace System::Collections::Generic;



ref class PrnFile
{
public:
  PrnFile( String ^ filename );
  virtual ~PrnFile(void);

public:
  String ^ Filename;
  List<String^> ^ FirstHeaderRow;
  List<String^> ^ SecondHeaderRow;
  List<List<String^>^> ^ DataRows;
};



ref class LocationFile : PrnFile
{
public:
  LocationFile( String ^ fileName );

public:
  String ^ Title;
  List<String ^> ^ Headers;
  Dictionary<String^,List<String^>^> ^ Data;
};



ref class ContainerFile : public PrnFile
{
public:
  ContainerFile( String ^ fileName );

public:
  String ^ Header;
  List<String^> ^ ContainerNames;
  Dictionary<String^,List<String^>^> ^ ContainerData;
};



ref class SerotypeFile: public PrnFile
{
public:
  SerotypeFile( String ^ filename );

public:
  String ^ Header;
  Dictionary<int,List<String^>^> ^ SerotypeData;
};


ref class SurvivalFile : public PrnFile
{
public:
  SurvivalFile( String ^ fileName );

public:
  String ^ ContainerName;
  List<String^> ^ Headers;
  Dictionary<String^,List<String^>^> ^ Data;
};



ref class LarvalDataFile : public PrnFile
{
public:
  LarvalDataFile( String ^ fileName );

public:
  String ^ Day;
  String ^ ContainerName;
  List<String^> ^ Headers;
};


#endif
