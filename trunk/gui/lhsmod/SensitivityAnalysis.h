#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::ComponentModel;
using namespace System::Threading;
using namespace Microsoft::Office::Interop;

ref class SensitivityAnalysisStudy;



public ref class SensitivityAnalysisSimulation
{
public:
  SensitivityAnalysisSimulation( SensitivityAnalysisStudy ^ study, String ^ filename, int runId, ManualResetEvent ^ manualResetEvent );
protected:
  virtual ~SensitivityAnalysisSimulation(void);

public:
  void ThreadPoolCallback( Object ^ stateInfo );

private:
  SensitivityAnalysisStudy ^ _study;
  String ^ filename;
  int _runId;
  ManualResetEvent ^ _manualResetEvent;

  Excel::Application ^ _excelApplication;
  array<String^> ^ _outputFilenames;
};



public ref class SensitivityAnalysisStudy
{
public:
  ref class StudyState {
  public:
    int NumberOfRuns;
    double PercentCompleted;
    List<String^> ^ Messages;
  };

// Constructors
private:
  static SensitivityAnalysisStudy(void);
public:
  SensitivityAnalysisStudy( BackgroundWorker ^ backgroundWorker, String ^ dmlFile, String ^ lspFile, String ^ outputDir, bool useDiscrete, bool processOnly );
  virtual ~SensitivityAnalysisStudy(void);

// Properties
public:
  property int NumberOfRuns {
    int get(void) {
      return _numberOfRuns;
    }
  }

// Methods
public:
  void StartStudy( BackgroundWorker ^ bw );
  void ReportRunResult( int runId, bool runDiscarded );

private:
  void ParseStudy(void);
  void ModifyBaseLocation( Generic::List<String^> ^ paramNames, Generic::List<double> ^ paramValues );
  void SetDmlParameter( String ^ dmlName, Object ^ value );
  static String ^ GetDmlNameFromSa( String ^ saName );

// Fields
private:
  BackgroundWorker ^ _backgroundWorker;

  gui::Location ^ _baseLocation;

  String ^ _dmlFilename;
  String ^ _lspFilename;
  String ^ _outputDirectory;
  bool _useDiscrete;
  bool _processOnly;

  int _numberOfRuns;
  int _numberOfCompletedRuns;
  List<String^> ^ _newResults;
  Dictionary<int,String^> ^ _runResults;

  List<SensitivityAnalysisSimulation^> ^ _simulations;

  List<Dictionary<int,String^>^> ^ _filesByThread;

  static Dictionary<String^,String^> ^ _saNamesToDmlNames;
};
