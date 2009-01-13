#include "StdAfx.h"
#include "SensitivityAnalysis.h"



static
SensitivityAnalysis::SensitivityAnalysis(void)
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



SensitivityAnalysis::SensitivityAnalysis(void)
{
}



SensitivityAnalysis::~SensitivityAnalysis(void)
{
}



void
SensitivityAnalysis::ModifyLocation( gui::Location ^ location, Generic::List<String^> ^ paramNames, Generic::List<double> ^ paramValues )
{
  // for location, modify specified parameters to have specified values
  int numParams = paramNames->Count;

  for( int i = 0; i < numParams; ++i ) {
    // find dml name and value
    String ^ dmlName = GetDmlNameFromSa( paramNames[i] );
    double value = paramValues[i];

    SetDmlParameter( location, dmlName, value );
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
SensitivityAnalysis::SetDmlParameter( gui::Location ^ location, String ^ dmlName, Object ^ value )
{
  Object ^ parentObj = location;
  String ^ propName = dmlName;

  if( dmlName->Contains(".") ) {
    // nested property, find parent property
    int lastPeriod = dmlName->LastIndexOf(".");
    String ^ parentName = dmlName->Substring( 0, lastPeriod );
    parentObj = FindNestedProperty( location, parentName );
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
SensitivityAnalysis::GetDmlNameFromSa( String ^ saName )
{
  return _saNamesToDmlNames[saName];
}
