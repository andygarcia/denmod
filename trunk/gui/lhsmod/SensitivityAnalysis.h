#pragma once

#include "SimulationStack.h"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::ComponentModel;
using namespace System::Threading;
using namespace Microsoft::Office::Interop;



public ref class SensitivityAnalysisParser
{
public:
// Constructors
private:
  static SensitivityAnalysisParser(void);
public:
  SensitivityAnalysisParser( String ^ dmlFile, String ^ lspFile, String ^ outputDir );
  virtual ~SensitivityAnalysisParser(void);

// Methods
public:
  SimulationStack ^ ParseStudy( BackgroundWorker ^ bw );

private:
  void ModifyBaseLocation( Generic::List<String^> ^ paramNames, Generic::List<double> ^ paramValues );
  void SetDmlParameter( String ^ dmlName, Object ^ value );
  static String ^ GetDmlNameFromSa( String ^ saName );

// Fields
private:
  gui::Location ^ _baseLocation;

  String ^ _dmlFilename;
  String ^ _lspFilename;
  String ^ _outputDirectory;

  int _numberOfSimulations;
  SimulationStack ^ _simulationStack;

  static Dictionary<String^,String^> ^ _saNamesToDmlNames;
};



public ref class StudyProgress
{
public:
  StudyProgress(void)
  : Messages(gcnew List<String^>())
  {}

public:
  int NumberOfRunsCompleted;
  int NumberOfRunsDiscarded;
  List<String^> ^ Messages;
};



public ref class FileReadProgress
{
public:
  FileReadProgress(void)
  : Messages(gcnew List<String^>())
  {}

public:
  int TotalFileCount;
  int CurrentFileCount;
  List<String^> ^ Messages;
};
