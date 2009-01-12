#include "StdAfx.h"
#include "LhsForm.h"

using namespace lhsmod;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Text;
using namespace System::Text::RegularExpressions;



System::Void
LhsForm::OnBrowseDml(System::Object^  sender, System::EventArgs^  e)
{
  OpenFileDialog ^ ofd = gcnew OpenFileDialog();
  ofd->Filter = "Dengue Model Locations (*.dml)|*.dml";
  if( ofd->ShowDialog() == ::DialogResult::OK ) {
    tboxDml->Text = ofd->FileName;
  }
}



System::Void
LhsForm::OnBrowseLsp(System::Object^  sender, System::EventArgs^  e)
{
  OpenFileDialog ^ ofd = gcnew OpenFileDialog();
  ofd->Filter = "LHSWIN Output File (*.lsp)|*.lsp";
  if( ofd->ShowDialog() == ::DialogResult::OK ) {
    tboxLsp->Text = ofd->FileName;
  }
}



System::Void
LhsForm::OnBrowseOutput(System::Object^  sender, System::EventArgs^  e)
{
  FolderBrowserDialog ^ fbd = gcnew FolderBrowserDialog();
  fbd->SelectedPath = Environment::CurrentDirectory;
  if( fbd->ShowDialog() == ::DialogResult::OK ) {
    tboxOutput->Text = fbd->SelectedPath;
  }
}



System::Void
LhsForm::OnRun(System::Object^  sender, System::EventArgs^  e)
{
  System::IO::StreamReader ^ sr = gcnew System::IO::StreamReader( tboxLsp->Text );
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

  s = sr->ReadLine();
  m = r->Match( s );
  int numRuns = Convert::ToInt32( m->Value );

  s = sr->ReadLine();
  m = r->Match( s );
  int numParams = Convert::ToInt32( m->Value );


  // parameter names in ordered parsed
  typedef Generic::List<String^> ParameterNames;
  ParameterNames ^ paramNames = gcnew ParameterNames();

  for( int i = 1; i <= numParams; ++i ) {
    s = sr->ReadLine();
    s->Trim( gcnew array<wchar_t>{' ',':'} );
    paramNames->Add( s );
  }


  // advance to SAMPLEDATA block
  while( true ) {
    String ^ s = sr->ReadLine();
    if( s == "@SAMPLEDATA" ) {
      break;
    }
  }


  // collection of sampled parameter values in order encountered
  typedef Generic::List<double> SampledParameterValues;
  typedef Generic::List<SampledParameterValues^> SampledParameterValuesByRun;
  SampledParameterValuesByRun ^ allRuns = gcnew SampledParameterValuesByRun();

  // parse each run
  for( int i = 1; i <= numRuns; ++i ) {

    // read numParams + 2 values (run index and param count exists in each run's data)
    Generic::List<double> ^ values = gcnew Generic::List<double>();
    while( true ) {
      // parse line into separate values
      s = sr->ReadLine();
      Regex ^ rr = gcnew Regex( "\\-?\\d+(\\.\\d+)?([E|D]\\-?\\d+)?" );
      MatchCollection ^ mc = rr->Matches( s );
      for each( Match ^ m in mc ) {
        values->Add( Convert::ToDouble(m->Value) );
      }

      // once we have read all parameter values as well as index and param count, stop
      if( values->Count >= numParams + 2 ) {
        break;
      }
    }

    // save values: after discarding run index and parameter count,
    // data in the values array begins at index 2
    SampledParameterValues ^ thisRun = gcnew SampledParameterValues();
    for( int i = 2; i <= numParams + 2; ++i ) {
      thisRun->Add( values[i+1] );
    }
    allRuns->Add( thisRun );
  }

  // at this point allRuns has sampled values for all parameters in
  // parameter order and run order


  // now need to map from SA parameters to DML parameters
  Generic::Dictionary<String^,String^> SaNamesToDmlNames = gcnew Generic::Dictionary<String^,String^>();
"E.min.htch.temp"             "Biology.Egg.MinimumHatchTemperature"
"E.flod.htch.ratio"           "Biology.Egg.FloodHatchRatio"
"E.spon.htch.ratio"           "Biology.Egg.SpontaneousHatchRatio"
"E.nom.surv"                  "Biology.Egg.NominalSurvival"
"E.temp.LL.surv"              "Biology.Egg.Temperature.LowLethalSurvival"
"E.temp.LL.thresh"            "Biology.Egg.Temperature.LowLethalThreshold"
"E.temp.L.thresh"             "Biology.Egg.Temperature.LowThreshold"
"E.temp.H.thresh"             "Biology.Egg.Temperature.HighThreshold"
"E.temp.HL.thresh"            "Biology.Egg.Temperature.HighLethalThreshold"
"E.temp.HL.surv"              "Biology.Egg.Temperature.HighLethalSurvival"
"E.sat.sun.thresh"            "Biology.Egg.SaturationDeficit.HighSunExposureThreshold"
"E.sat.sunex.surv"            "Biology.Egg.SaturationDeficit.HighSunExposureSurvival"
"E.sat.L.thresh"              "Biology.Egg.SaturationDeficit.LowThreshold"
"E.sat.H.thresh"              "Biology.Egg.SaturationDeficit.HighThreshold"
"E.sat.L.surv"                "Biology.Egg.SaturationDeficit.LowSurvival"
"E.sat.H.surv"                "Biology.Egg.SaturationDeficit.HighSurvival"
"E.pred.L.thresh"             "Biology.Egg.Predation.LowThreshold"
"E.pred.H.thresh"             "Biology.Egg.Predation.HighThreshold"
"E.pred.H.surv"               "Biology.Egg.Predation.HighSurvival"
"L.wt.at.hatch"               "Biology.Larvae.WeightAtHatch"
"L.nom.surv"                  "Biology.Larvae.NominalSurvival"
"L.pup.surv"                  "Biology.Larvae.PupationSurvival"
"L.dry.cont.surv"             "Biology.Larvae.DryContainerSurvival"
"L.min.wt.surv"               "Biology.Larvae.MinimumWeightForSurvival"
"L.cad.fd.ratio"              "Biology.Larvae.CadaverFoodRatio"
"L.temp.LL.surv"              "Biology.Larvae.Temperature.LowLethalSurvival"
"L.temp.LL.thresh"            "Biology.Larvae.Temperature.LowLethalThreshold"
"L.temp.L.thresh"             "Biology.Larvae.Temperature.LowThreshold"
"L.temp.H.thresh"             "Biology.Larvae.Temperature.HighThreshold"
"L.temp.HL.thresh"            "Biology.Larvae.Temperature.HighLethalThreshold"
"L.temp.HL.surv"              "Biology.Larvae.Temperature.HighLethalSurvival"
"L.pup.minwt.pupn"            "Biology.Larvae.PupationWeight.MinimumWeightForPupation"
"L.fd.assim.rate"             "Biology.Larvae.Food.AssimilationRate"
"L.fd.explt.rate"             "Biology.Larvae.Food.ExploitationRate"
"L.fd.exprt.indep"            "Biology.Larvae.Food.ExploitationRateIndepedence"
"L.fd.mt.wtlos.rt"            "Biology.Larvae.Food.MetabolicWeightLossRate"
"L.fd.wtlos.expnt"            "Biology.Larvae.Food.MetabolicWeightLossRateExponent"
"L.fst.lip.rsvsur"            "Biology.Larvae.Fasting.LipidReserveSurvival"
"L.fst.nolip.surv"            "Biology.Larvae.Fasting.NoLipidReserveSurvival"
"L.fst.nondep.rsv"            "Biology.Larvae.Fasting.NonDepletableLipidReserve"
"P.nom.surv"                  "Biology.Pupae.NominalSurvival"
"P.emerg.surv"                "Biology.Pupae.EmergenceSurvival"
"P.fem.emerg"                 "Biology.Pupae.FemaleEmergence"
"P.temp.LL.surv"              "Biology.Pupae.Temperature.LowLethalSurvival"
"P.temp.LL.thresh"            "Biology.Pupae.Temperature.LowLethalThreshold"
"P.temp.L.thresh"             "Biology.Pupae.Temperature.LowThreshold"
"P.temp.H.thresh"             "Biology.Pupae.Temperature.HighThreshold"
"P.temp.HL.thresh"            "Biology.Pupae.Temperature.HighLethalThreshold"
"P.temp.HL.surv"              "Biology.Pupae.Temperature.HighLethalSurvival"
"A.sec.dev.thresh"            "Biology.Adult.SecondDevelopmentThreshold"
"A.dry.wet.wt.fac"            "Biology.Adult.DryToWetWeightFactor"
"A.fecund.fac"                "Biology.Adult.FecundityFactor"
"A.min.ovip.temp"             "Biology.Adult.MinimumOvipositionTemperature"
"A.prop.feed.hum"             "Biology.Adult.ProportionOfFeedsOnHumans"
"A.intruptd.feed"             "Biology.Adult.InterruptedFeedsPerMeal"
"A.prp.intfd.host"            "Biology.Adult.ProportionOfInterruptedFeedsOnDifferentHost"
"A.age.youngsurv"             "Biology.Adult.AgeDependentSurvival.YoungSurvival"
"A.age.cutoffage"             "Biology.Adult.AgeDependentSurvival.CutoffAge"
"A.age.oldsurv"               "Biology.Adult.AgeDependentSurvival.OldSurvival"
"A.temp.LL.surv"              "Biology.Adult.Temperature.LowLethalSurvival"
"A.temp.LL.thresh"            "Biology.Adult.Temperature.LowLethalThreshold"
"A.temp.L.thresh"             "Biology.Adult.Temperature.LowThreshold"
"A.temp.H.thresh"             "Biology.Adult.Temperature.HighThreshold"
"A.temp.HL.thresh"            "Biology.Adult.Temperature.HighLethalThreshold"
"A.temp.HL.surv"              "Biology.Adult.Temperature.HighLethalSurvival"
"A.satdef.L.thrsh"            "Biology.Adult.SaturationDeficit.LowThreshold"
"A.satdef.H.surv"             "Biology.Adult.SaturationDeficit.HighSurvival"
"A.satdef.H.thrsh"            "Biology.Adult.SaturationDeficit.HighThreshold"
"A.bld.L.wt.ratio"            "Biology.Adult.DoubleBloodMeal.LowWeightRatio"
"A.bld.L.wt.limit"            "Biology.Adult.DoubleBloodMeal.LowWeightLimit"
"A.bld.H.wt.ratio"            "Biology.Adult.DoubleBloodMeal.HighWeightRatio"
"A.bld.H.wt.limit"            "Biology.Adult.DoubleBloodMeal.HighWeightLimit"



}
