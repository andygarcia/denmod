#include "StdAfx.h"
#include "SensitivityAnalysis.h"

using namespace System::IO;
using namespace System::Collections;
using namespace System::Text;
using namespace System::Text::RegularExpressions;



static
SensitivityAnalysisParser::SensitivityAnalysisParser(void)
{
  _saNamesToDmlNames = gcnew Generic::Dictionary<String^,String^>(StringComparer::InvariantCultureIgnoreCase);
  _saNamesToDmlNames->Add( "mana.dur", "Serology.MANADuration" );
  _saNamesToDmlNames->Add( "maea.dur", "Serology.MAEADuration" );
  _saNamesToDmlNames->Add( "hetero.im.dur", "Serology.HeterologousImmunityDuration" );
  _saNamesToDmlNames->Add( "den1.viermia", "Virology.Dengue1.Viremia" );
  _saNamesToDmlNames->Add( "den1.inc.dur", "Virology.Dengue1.IncubationDuration" );
  _saNamesToDmlNames->Add( "den1.vir.dur", "Virology.Dengue1.ViremicDuration" );
  _saNamesToDmlNames->Add( "den2.viermia", "Virology.Dengue2.Viremia" );
  _saNamesToDmlNames->Add( "den2.inc.dur", "Virology.Dengue2.IncubationDuration" );
  _saNamesToDmlNames->Add( "den2.vir.dur", "Virology.Dengue2.ViremicDuration" );
  _saNamesToDmlNames->Add( "den3.viermia", "Virology.Dengue3.Viremia" );
  _saNamesToDmlNames->Add( "den3.inc.dur", "Virology.Dengue3.IncubationDuration" );
  _saNamesToDmlNames->Add( "den3.vir.dur", "Virology.Dengue3.ViremicDuration" );
  _saNamesToDmlNames->Add( "den4.viermia", "Virology.Dengue4.Viremia" );
  _saNamesToDmlNames->Add( "den4.inc.dur", "Virology.Dengue4.IncubationDuration" );
  _saNamesToDmlNames->Add( "den4.vir.dur", "Virology.Dengue4.ViremicDuration" );
  _saNamesToDmlNames->Add( "h.m.low.titer", "Virology.HumanToMosquitoInfection.LowTiterSetPoint" );
  _saNamesToDmlNames->Add( "h.m.hi.titer", "Virology.HumanToMosquitoInfection.HighTiterSetPoint" );
  _saNamesToDmlNames->Add( "m.h.nom.prob", "Virology.MosquitoToHumanNominalProbabilityOfInfection" );
  _saNamesToDmlNames->Add( "eiptiterlofac", "Virology.EIP.TiterModification.LowSetPoint" );
  _saNamesToDmlNames->Add( "eiptiterhifac", "Virology.EIP.TiterModification.HighSetPoint" );
  _saNamesToDmlNames->Add( "bm.lo.wt.ratio", "Biology.Adult.DoubleBloodMeal.LowWeightRatio" );
  _saNamesToDmlNames->Add( "bm.lo.wt.lim", "Biology.Adult.DoubleBloodMeal.LowWeightLimit" );
  _saNamesToDmlNames->Add( "bm.hi.wt.ratio", "Biology.Adult.DoubleBloodMeal.HighWeightRatio" );
  _saNamesToDmlNames->Add( "bm.hi.wt.lim", "Biology.Adult.DoubleBloodMeal.HighWeightLimit" );
  _saNamesToDmlNames->Add( "prop.fd.hum", "Biology.Adult.ProportionOfFeedsOnHumans" );
  _saNamesToDmlNames->Add( "fd.per.meal", "Biology.Adult.InterruptedFeedsPerMeal" );
  _saNamesToDmlNames->Add( "interrupt.host", "Biology.Adult.ProportionOfInterruptedFeedsOnDifferentHost" );
  _saNamesToDmlNames->Add( "young.survive", "Biology.Adult.AgeDependentSurvival.YoungSurvival" );
  _saNamesToDmlNames->Add( "cutoff", "Biology.Adult.AgeDependentSurvival.CutoffAge" );
  _saNamesToDmlNames->Add( "old.survive", "Biology.Adult.AgeDependentSurvival.OldSurvival" );



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



SensitivityAnalysisParser::SensitivityAnalysisParser( String ^ dmlFilename, String ^ lspFilename, String ^ outputDir )
: _dmlFilename(dmlFilename),
  _lspFilename(lspFilename),
  _outputDirectory(outputDir),
  _simulationStack(gcnew SimulationStack()),
  _numberOfSimulations(0)
{}



SensitivityAnalysisParser::~SensitivityAnalysisParser(void)
{}



SimulationStack ^
SensitivityAnalysisParser::ParseStudy( BackgroundWorker ^ bw, DoWorkEventArgs ^ e )
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
  _numberOfSimulations = Convert::ToInt32( m->Value );

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

  // read parameters for each run and write file
  for( int i = 0; i < _numberOfSimulations; ++i ) {
    // check for cancel
    if( bw->CancellationPending ) {
      e->Cancel = true;
      return nullptr;
    }

    // sampled parameters for current run
    Generic::List<double> ^ thisRun = gcnew Generic::List<double>();

    while( true ) {
      // parse line into separate values
      s = sr->ReadLine();
      //Regex ^ rr = gcnew Regex( "\\-?\\d+(\\.\\d+)?([E|D]\\-?\\d+)?" );
      Regex ^ rr = gcnew Regex( "\\-?\\d+(\\.\\d+)?([E|D]\\-?\\+?\\d+)?" );

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

    _simulationStack->Push( runFilename );

    FileReadProgress ^ frp = gcnew FileReadProgress();
    frp->TotalFileCount = _numberOfSimulations;
    frp->CurrentFileCount = i+1;
    frp->Messages->Add( "Created " + runFilename );

    bw->ReportProgress( 0, frp );
  }

  return _simulationStack;
}



void
SensitivityAnalysisParser::ModifyBaseLocation( Generic::List<String^> ^ paramNames, Generic::List<double> ^ paramValues )
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
SensitivityAnalysisParser::SetDmlParameter( String ^ dmlName, Object ^ value )
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
SensitivityAnalysisParser::GetDmlNameFromSa( String ^ saName )
{
  return _saNamesToDmlNames[saName];
}
