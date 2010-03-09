#include "StdAfx.h"
#include "SensitivityAnalysis.h"

using namespace System::IO;
using namespace System::Collections;
using namespace System::Text;
using namespace System::Text::RegularExpressions;



static
SensitivityAnalysisStudy::SensitivityAnalysisStudy(void)
{
  _saNamesToDmlNames = gcnew Generic::Dictionary<String^,String^>(StringComparer::InvariantCultureIgnoreCase);
  _saNamesToDmlNames->Add( "E.min.htch.temp", "Biology.Egg.MinimumHatchTemperature" );
  _saNamesToDmlNames->Add( "E.flod.htch.rati", "Biology.Egg.FloodHatchRatio" );
  _saNamesToDmlNames->Add( "E.spon.htch.ratio", "Biology.Egg.SpontaneousHatchRatio" );
  _saNamesToDmlNames->Add( "E.nom.surv", "Biology.Egg.NominalSurvival" );
  _saNamesToDmlNames->Add( "E.temp.LL.surv", "Biology.Egg.Temperature.LowLethalSurvival" );
  _saNamesToDmlNames->Add( "E.temp.LL.thresh", "Biology.Egg.Temperature.LowLethalThreshold" );
  _saNamesToDmlNames->Add( "E.temp.L.thresh", "Biology.Egg.Temperature.LowThreshold" );
  _saNamesToDmlNames->Add( "E.temp.H.thresh", "Biology.Egg.Temperature.HighThreshold" );
  _saNamesToDmlNames->Add( "E.temp.HL.thresh", "Biology.Egg.Temperature.HighLethalThreshold" );
  _saNamesToDmlNames->Add( "E.temp.HL.surv", "Biology.Egg.Temperature.HighLethalSurvival" );
  _saNamesToDmlNames->Add( "E.sat.sun.thresh", "Biology.Egg.SaturationDeficit.HighSunExposureThreshold" );
  _saNamesToDmlNames->Add( "E.sat.sunex.surv", "Biology.Egg.SaturationDeficit.HighSunExposureSurvival" );
  _saNamesToDmlNames->Add( "E.sat.L.thresh", "Biology.Egg.SaturationDeficit.LowThreshold" );
  _saNamesToDmlNames->Add( "E.sat.H.thresh", "Biology.Egg.SaturationDeficit.HighThreshold" );
  _saNamesToDmlNames->Add( "E.sat.L.surv", "Biology.Egg.SaturationDeficit.LowSurvival" );
  _saNamesToDmlNames->Add( "E.sat.H.surv", "Biology.Egg.SaturationDeficit.HighSurvival" );
  _saNamesToDmlNames->Add( "E.pred.L.thresh", "Biology.Egg.Predation.LowThreshold" );
  _saNamesToDmlNames->Add( "E.pred.H.thresh", "Biology.Egg.Predation.HighThreshold" );
  _saNamesToDmlNames->Add( "E.pred.H.surv", "Biology.Egg.Predation.HighSurvival" );
  _saNamesToDmlNames->Add( "L.wt.at.hatch", "Biology.Larvae.WeightAtHatch" );
  _saNamesToDmlNames->Add( "L.nom.surv", "Biology.Larvae.NominalSurvival" );
  _saNamesToDmlNames->Add( "L.pup.surv", "Biology.Larvae.PupationSurvival" );
  _saNamesToDmlNames->Add( "L.dry.cont.surv", "Biology.Larvae.DryContainerSurvival" );
  _saNamesToDmlNames->Add( "L.min.wt.surv", "Biology.Larvae.MinimumWeightForSurvival" );
  _saNamesToDmlNames->Add( "L.cad.fd.ratio", "Biology.Larvae.CadaverFoodRatio" );
  _saNamesToDmlNames->Add( "L.temp.LL.surv", "Biology.Larvae.Temperature.LowLethalSurvival" );
  _saNamesToDmlNames->Add( "L.temp.LL.thresh", "Biology.Larvae.Temperature.LowLethalThreshold" );
  _saNamesToDmlNames->Add( "L.temp.L.thresh", "Biology.Larvae.Temperature.LowThreshold" );
  _saNamesToDmlNames->Add( "L.temp.H.thresh", "Biology.Larvae.Temperature.HighThreshold" );
  _saNamesToDmlNames->Add( "L.temp.HL.thresh", "Biology.Larvae.Temperature.HighLethalThreshold" );
  _saNamesToDmlNames->Add( "L.temp.HL.surv", "Biology.Larvae.Temperature.HighLethalSurvival" );
  _saNamesToDmlNames->Add( "L.pup.minwt.pupn", "Biology.Larvae.PupationWeight.MinimumWeightForPupation" );
  _saNamesToDmlNames->Add( "L.fd.assim.rate", "Biology.Larvae.Food.AssimilationRate" );
  _saNamesToDmlNames->Add( "L.fd.explt.rate", "Biology.Larvae.Food.ExploitationRate" );
  _saNamesToDmlNames->Add( "L.fd.exprt.indep", "Biology.Larvae.Food.ExploitationRateIndependence" );
  _saNamesToDmlNames->Add( "L.fd.mt.wtlos.rt", "Biology.Larvae.Food.MetabolicWeightLossRate" );
  _saNamesToDmlNames->Add( "L.fd.wtlos.expnt", "Biology.Larvae.Food.MetabolicWeightLossExponent" );
  _saNamesToDmlNames->Add( "L.fst.lip.rsvsur", "Biology.Larvae.Fasting.LipidReserveSurvival" );
  _saNamesToDmlNames->Add( "L.fst.nolip.surv", "Biology.Larvae.Fasting.NoLipidReserveSurvival" );
  _saNamesToDmlNames->Add( "L.fst.nondep.rsv", "Biology.Larvae.Fasting.NonDepletableLipidReserve" );
  _saNamesToDmlNames->Add( "P.nom.surv", "Biology.Pupae.NominalSurvival" );
  _saNamesToDmlNames->Add( "P.emerg.surv", "Biology.Pupae.EmergenceSurvival" );
  _saNamesToDmlNames->Add( "P.fem.emerg", "Biology.Pupae.FemaleEmergence" );
  _saNamesToDmlNames->Add( "P.temp.LL.surv", "Biology.Pupae.Temperature.LowLethalSurvival" );
  _saNamesToDmlNames->Add( "P.temp.LL.thresh", "Biology.Pupae.Temperature.LowLethalThreshold" );
  _saNamesToDmlNames->Add( "P.temp.L.thresh", "Biology.Pupae.Temperature.LowThreshold" );
  _saNamesToDmlNames->Add( "P.temp.H.thresh", "Biology.Pupae.Temperature.HighThreshold" );
  _saNamesToDmlNames->Add( "P.temp.HL.thresh", "Biology.Pupae.Temperature.HighLethalThreshold" );
  _saNamesToDmlNames->Add( "P.temp.HL.surv", "Biology.Pupae.Temperature.HighLethalSurvival" );
  _saNamesToDmlNames->Add( "A.sec.dev.thresh", "Biology.Adult.SecondDevelopmentThreshold" );
  _saNamesToDmlNames->Add( "A.dry.wet.wt.fac", "Biology.Adult.DryToWetWeightFactor" );
  _saNamesToDmlNames->Add( "A.fecund.fac", "Biology.Adult.FecundityFactor" );
  _saNamesToDmlNames->Add( "A.min.ovip.temp", "Biology.Adult.MinimumOvipositionTemperature" );
  _saNamesToDmlNames->Add( "A.prop.feed.hum", "Biology.Adult.ProportionOfFeedsOnHumans" );
  _saNamesToDmlNames->Add( "A.intruptd.feed", "Biology.Adult.InterruptedFeedsPerMeal" );
  _saNamesToDmlNames->Add( "A.prp.intfd.host", "Biology.Adult.ProportionOfInterruptedFeedsOnDifferentHost" );
  _saNamesToDmlNames->Add( "A.age.youngsurv", "Biology.Adult.AgeDependentSurvival.YoungSurvival" );
  _saNamesToDmlNames->Add( "A.age.cutoffage", "Biology.Adult.AgeDependentSurvival.CutoffAge" );
  _saNamesToDmlNames->Add( "A.age.oldsurv", "Biology.Adult.AgeDependentSurvival.OldSurvival" );
  _saNamesToDmlNames->Add( "A.temp.LL.surv", "Biology.Adult.Temperature.LowLethalSurvival" );
  _saNamesToDmlNames->Add( "A.temp.LL.thresh", "Biology.Adult.Temperature.LowLethalThreshold" );
  _saNamesToDmlNames->Add( "A.temp.L.thresh", "Biology.Adult.Temperature.LowThreshold" );
  _saNamesToDmlNames->Add( "A.temp.H.thresh", "Biology.Adult.Temperature.HighThreshold" );
  _saNamesToDmlNames->Add( "A.temp.HL.thresh", "Biology.Adult.Temperature.HighLethalThreshold" );
  _saNamesToDmlNames->Add( "A.temp.HL.surv", "Biology.Adult.Temperature.HighLethalSurvival" );
  _saNamesToDmlNames->Add( "A.satdef.L.thrsh", "Biology.Adult.SaturationDeficit.LowThreshold" );
  _saNamesToDmlNames->Add( "A.satdef.H.surv", "Biology.Adult.SaturationDeficit.HighSurvival" );
  _saNamesToDmlNames->Add( "A.satdef.H.thrsh", "Biology.Adult.SaturationDeficit.HighThreshold" );
  _saNamesToDmlNames->Add( "A.bld.L.wt.ratio", "Biology.Adult.DoubleBloodMeal.LowWeightRatio" );
  _saNamesToDmlNames->Add( "A.bld.L.wt.limit", "Biology.Adult.DoubleBloodMeal.LowWeightLimit" );
  _saNamesToDmlNames->Add( "A.bld.H.wt.ratio", "Biology.Adult.DoubleBloodMeal.HighWeightRatio" );
  _saNamesToDmlNames->Add( "A.bld.H.wt.limit", "Biology.Adult.DoubleBloodMeal.HighWeightLimit" );

  // truncuate all keys to 16 characters (LHSWIN love)
  Generic::Dictionary<String^,String^> ^ d = gcnew Generic::Dictionary<String^,String^>(StringComparer::InvariantCultureIgnoreCase);
  for each( Generic::KeyValuePair<String^,String^> ^ kvp in _saNamesToDmlNames ) {
    String ^ newKey;
    int keyLength = kvp->Key->Length;
    if( keyLength > 16 ) {
      newKey = kvp->Key->Substring( 0, 16 );
    }
    else {
      newKey = kvp->Key;
    }

    d->Add( newKey, kvp->Value );
  }

  _saNamesToDmlNames = d;
}



SensitivityAnalysisStudy::SensitivityAnalysisStudy( BackgroundWorker ^ backgroundWorker, String ^ dmlFilename, String ^ lspFilename, String ^ outputDir, bool processOnly, bool useDiscrete )
: _dmlFilename(dmlFilename),
  _lspFilename(lspFilename),
  _outputDirectory(outputDir),
  _processOnly(processOnly),
  _useDiscrete(useDiscrete),
  _numberOfRuns(0),
  _numberOfCompletedRuns(0),
  _newResults(gcnew List<String^>()),
  _runResults(gcnew Dictionary<int,String^>())
{
  ParseStudy();
}



SensitivityAnalysisStudy::~SensitivityAnalysisStudy(void)
{}



void
SensitivityAnalysisStudy::ParseStudy(void)
{
  // read dml file for base location object
  gui::DmlFile ^ dmlFile = gcnew gui::DmlFile( _dmlFilename );
  _baseLocation = dmlFile->Location;

  // read lsp file
  System::IO::StreamReader ^ sr = gcnew System::IO::StreamReader( _lspFilename );
  String ^ s;

  // advance to UNCERTAINTY block
  while( true ) {
    String ^ s = sr->ReadLine();
    if( s == "@UNCERTAINTY" ) {
      break;
    }
  }

  // read number of params and runs for this file
  Regex ^ r = gcnew Regex( "\\d+" );
  Match ^ m;

  // read number of runs
  s = sr->ReadLine();
  m = r->Match( s );
  _numberOfRuns = Convert::ToInt32( m->Value );

  // read number of parameters
  s = sr->ReadLine();
  m = r->Match( s );
  int numParams = Convert::ToInt32( m->Value );

  // parameter names in ordered parsed
  Generic::List<String^> ^ sampledParameterNamesInOrder = gcnew Generic::List<String^>();

  for( int i = 1; i <= numParams; ++i ) {
    s = sr->ReadLine();
    s = s->Trim( gcnew array<wchar_t>{' ',':'} );
    sampledParameterNamesInOrder->Add( s );
  }

  // advance to SAMPLEDATA block
  while( true ) {
    String ^ s = sr->ReadLine();
    if( s == "@SAMPLEDATA" ) {
      break;
    }
  }


  // create list of files for each thread
  int procCount = Environment::ProcessorCount;
  _filesByThread = gcnew List<Dictionary<int,String^>^>(procCount);
  for( int i = 0; i < procCount; ++i ) {
    _filesByThread->Add( gcnew Dictionary<int,String^>() );
  }


  // read parameters for each run
  for( int i = 0; i < _numberOfRuns; ++i ) {

    // sampled parameters for current run
    Generic::List<double> ^ thisRun = gcnew Generic::List<double>();

    while( true ) {
      // parse line into separate values
      s = sr->ReadLine();
      Regex ^ rr = gcnew Regex( "\\-?\\d+(\\.\\d+)?([E|D]\\-?\\d+)?" );
      MatchCollection ^ mc = rr->Matches( s );
      for each( Match ^ m in mc ) {
        thisRun->Add( Convert::ToDouble(m->Value) );
      }

      // check if all params have been read and then cleanup
      if( thisRun->Count >= numParams + 2 ) {
        // remove first two values (index and param count)
        thisRun->RemoveAt(0);
        thisRun->RemoveAt(0);
        break;
      }
    }

    // create directory for this run
    DirectoryInfo ^ baseDir = gcnew DirectoryInfo( _outputDirectory );
    DirectoryInfo ^ runDir = gcnew DirectoryInfo( baseDir->FullName + "\\run " + (i+1) );
    if( !runDir->Exists ) {
      runDir->Create();
    }

    // modify base location with this run's parameters values
    ModifyBaseLocation( sampledParameterNamesInOrder, thisRun );

    // create file for this run
    String ^ runFilename = String::Format( runDir + "\\run{0}.dml", i+1 );
    gui::DmlFile ^ runFile = gcnew gui::DmlFile( runFilename, _baseLocation );
    runFile->Save();

    // allocate file to a thread
    int threadId = i % procCount;
    _filesByThread[threadId]->Add( i, runFile->Filename );
  }
}



void
SensitivityAnalysisStudy::StartStudy( BackgroundWorker ^ bw )
{
  _backgroundWorker = bw;

  // start each separate thread
  int numThreads = _filesByThread->Count;
  _simulationThreads = gcnew List<Thread^>(numThreads);
  for( int i = 0; i < numThreads; ++i ) {
    // create and start thread
    StudyThread ^ st = gcnew StudyThread( this, _filesByThread[i], _processOnly, _useDiscrete );
    ThreadStart ^ ts = gcnew ThreadStart( st, &StudyThread::Start );
    Thread ^ t = gcnew Thread( ts );
    t->Name = Convert::ToString( i );
    _simulationThreads->Add( t );
    t->Start();
  }

  while( true ) {
    // ensure no simulation threads are updating results
    Monitor::Enter( _runResults );

    // check for new results
    try {
      if( _newResults->Count > 0 ) {
        // create update object
        StudyState ^ ss = gcnew StudyState();
        ss->NumberOfRuns = _numberOfRuns;
        ss->PercentCompleted = static_cast<double>(_runResults->Count) / static_cast<double>(_numberOfRuns);
        ss->Messages = gcnew List<String^>();
        for each( String ^ s in _newResults ) {
          ss->Messages->Add( s );
        }

        // clear results
        _newResults->Clear();

        // report progress to ui
        _backgroundWorker->ReportProgress( static_cast<int>(ss->PercentCompleted), ss );

        if( _runResults->Count == _numberOfRuns ) {
          break;
        }
      }
    }
    finally {
      Monitor::Exit( _runResults );
    }
  }
}



void
SensitivityAnalysisStudy::ReportRunResult( int runId, bool runDiscarded )
{
  // ensure only one simulation thread at a time is reporting results
  Monitor::Enter( _runResults );

  // todo fix run indexing kludge
  try {
    // create message
    String ^ message;
    if( runDiscarded) {
      message = String::Format( "Thread #{0} discarded run #{1}. See errors.txt.", Thread::CurrentThread->Name, runId+1 );
    }
    else {
      message = String::Format( "Thread #{0} completed run #{1}.", Thread::CurrentThread->Name, runId+1 );
    }

    // save temporary and final results
    _newResults->Add( message );
    _runResults[runId] = message;
  }
  finally {
    Monitor::Exit( _runResults );
  }
    
}


void
SensitivityAnalysisStudy::SuspendStudy(void)
{
  for each( Thread ^ t in _simulationThreads ) {
    t->Suspend();
  }
}



void
SensitivityAnalysisStudy::ResumeStudy(void)
{
  for each( Thread ^ t in _simulationThreads ) {
    t->Resume();
  }
}



void
SensitivityAnalysisStudy::StopStudy(void)
{
  for each( Thread ^ t in _simulationThreads ) {
    t->Abort();
  }  
}



void
SensitivityAnalysisStudy::ModifyBaseLocation( Generic::List<String^> ^ paramNames, Generic::List<double> ^ paramValues )
{
  // for location, modify specified parameters to have specified values
  int numParams = paramNames->Count;

  for( int i = 0; i < numParams; ++i ) {
    // find dml name and value
    String ^ dmlName = GetDmlNameFromSa( paramNames[i] );
    double value = paramValues[i];

    SetDmlParameter( dmlName, value );
  }
}



Reflection::PropertyInfo ^
FindProperty( Object ^ object, String ^ propName )
{
  if( propName->Contains(".") ) {
    // still nested, chop
    int lastPeriod = propName->LastIndexOf(".");
    String ^ nextSearch = propName->Substring(0, lastPeriod);
    return FindProperty( object, nextSearch );
  }
  else {
    return object->GetType()->GetProperty( propName );
  }

}



System::Object ^ 
FindNestedProperty( Object ^ rootObject, String ^ propName )
{
  // return propName's value in rootObject's (possibly nested)
  if( propName->Contains(".") ) {
    int firstPeriod = propName->IndexOf(".");
    String ^ childName = propName->Substring( 0, firstPeriod );
    String ^ childPropName = propName->Substring( firstPeriod+1 );

    Object ^ child = rootObject->GetType()->GetProperty( childName )->GetValue( rootObject, nullptr );
    return FindNestedProperty( child, childPropName );
  }
  else {
    return rootObject->GetType()->GetProperty( propName )->GetValue( rootObject, nullptr );
  }
}



void
SensitivityAnalysisStudy::SetDmlParameter( String ^ dmlName, Object ^ value )
{
  Object ^ parentObj = _baseLocation;
  String ^ propName = dmlName;

  if( dmlName->Contains(".") ) {
    // nested property, find parent property
    int lastPeriod = dmlName->LastIndexOf(".");
    String ^ parentName = dmlName->Substring( 0, lastPeriod );
    parentObj = FindNestedProperty( _baseLocation, parentName );
    propName = dmlName->Substring( lastPeriod + 1 );
  }

  Reflection::PropertyInfo ^ dmlProp = parentObj->GetType()->GetProperty( propName );
  Type ^ propType = dmlProp->PropertyType;
  bool test = propType->IsAssignableFrom( value->GetType() );
  Object ^ propValue = value;
  if( propType == Int32::typeid ) {
    propValue = Convert::ToInt32( value );
  }

  dmlProp->SetValue( parentObj, propValue, nullptr );
}



String ^
SensitivityAnalysisStudy::GetDmlNameFromSa( String ^ saName )
{
  return _saNamesToDmlNames[saName];
}



StudyThread::StudyThread( SensitivityAnalysisStudy ^ study, Dictionary<int,String^> ^ filenames, bool processOnly, bool useDiscrete )
: _study(study),
  _dmlFilenames(filenames),
  _processOnly(processOnly),
  _useDiscrete(useDiscrete),
  _excelApplication(gcnew Excel::Application())
{
  // disable error/warning dialogs in Excel for clean automation
  _excelApplication->DisplayAlerts = false;
}



StudyThread::~StudyThread( void )
{
  delete _excelApplication;
}



void
StudyThread::Start(void)
{
  for each( KeyValuePair<int,String^> ^ kvp in _dmlFilenames ) {
    // pull kvp
    String ^ filename = kvp->Value;
    int runId = kvp->Key;

    // open this file and location
    gui::DmlFile ^ dmlFile = gcnew gui::DmlFile( filename );
    gui::Location ^ location = dmlFile->Location;
    DirectoryInfo ^ runDir = gcnew DirectoryInfo( Path::GetDirectoryName(filename) );
    
    // check for errors in location's parameters
    location->Biology->PropertyValidationManager->ValidateAllProperties();
    if( !location->Biology->IsValid ) {
      // delete error log if already present
      String ^ logFilename = Path::Combine( runDir->FullName, "errors.txt" );
      if( File::Exists( logFilename ) ) {
        File::Delete( logFilename );
      }

      // create log file with error message
      StreamWriter ^ sw = gcnew StreamWriter( Path::Combine(runDir->FullName, "errorLog.txt") );
      sw->Write( ValidationFramework::ResultFormatter::GetConcatenatedErrorMessages("\n", location->Biology->PropertyValidationManager->ValidatorResultsInError) );
      sw->Close();

      // abort this run (errors), continue with next run
      _study->ReportRunResult( runId, true );
      continue;
    }

    // if processing files only, skip simulation and continue to next file
    if( _processOnly ) {
      _study->ReportRunResult( runId, false );
      continue;
    }

    // do simulation and save output
    location->RunCimsim( true, _useDiscrete );
    //location->CimsimOutput->SaveToDisk( runDir );

    // dummy code to chew cycles for testing, thread will consume cpu for 2 seconds
    //int taskTime = 2000;
    //int startTime = Environment::TickCount;
    //while( Environment::TickCount - startTime < taskTime ) {}


    // first time generate list of filenames that will be converted post simulation for each subsequent run
    if( _outputFilenames == nullptr ) {
      // first look for all excel .xml files in current run directory
      array<FileInfo^> ^ xmlFiles = runDir->GetFiles( "*.xml", SearchOption::TopDirectoryOnly );
      
      // we only want the filename, not path (changes each time)
      _outputFilenames = gcnew array<String^>(xmlFiles->Length);
      for( int i = 0; i < xmlFiles->Length; ++i ) {
        _outputFilenames[i] = xmlFiles[i]->Name;
      }
    }

    // convert output files from Excel's xml format to binary format
    for each( String ^ filename in _outputFilenames ) {
      // open from this directory
      String ^ xmlFilename = Path::Combine( runDir->FullName, filename );

      // open and disable compatability check
      Excel::Workbook ^ xmlFile = _excelApplication->Workbooks->Open(xmlFilename, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing );
      xmlFile->CheckCompatibility = false;

      // save as excel 97-2003 format, changing extension, close and delete old workbook
      xmlFile->SaveAs( Path::ChangeExtension( xmlFilename, ".xls" ), Excel::XlFileFormat::xlExcel8, Type::Missing, Type::Missing, Type::Missing, false, Excel::XlSaveAsAccessMode::xlNoChange, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing );
      _excelApplication->Workbooks->Close();
      File::Delete( xmlFilename );
    }

    // completed run and saved output
    _study->ReportRunResult( runId, false );
  }
}
