#pragma once

#include "NotifyValidateEditBase.h"

#pragma managed( push, off )
#include "../../simulation/input/Biology.h"
#pragma managed( pop )

using namespace System::Xml::Serialization;



namespace gui {

public ref class DevelopmentParameters : public NotifyValidateEditBase
{
public:
  DevelopmentParameters(void) {}
  DevelopmentParameters( const DevelopmentParameters ^ dp );
  virtual ~DevelopmentParameters(void) {}

public:
  [XmlElement(Order=0)]
  property double RO25 {
    double get(void) {
      return RO25_;
    }
    void set(double d) {
      if( RO25_ != d ) {
        RO25_ = d;
        NotifyAndValidate("RO25");
      }
    }
  }

  [XmlElement(Order=1)]
  property double DHA {
    double get(void) {
      return DHA_;
    }
    void set(double d) {
      if( DHA_ != d ) {
        DHA_ = d;
        NotifyAndValidate("DHA");
      }
    }
  }

  [XmlElement(Order=2)]
  property double DHH {
    double get(void) {
      return DHH_;
    }
    void set(double d) {
      if( DHH_ != d ) {
        DHH_ = d;
        NotifyAndValidate("DHH");
      }
    }
  }

  [XmlElement(Order=3)]
  property double THALF {
    double get(void) {
      return THALF_;
    }
    void set(double d) {
      if( THALF_ != d ) {
        THALF_ = d;
        NotifyAndValidate("THALF");
      }
    }
  }

protected:
  double RO25_;
  double DHA_;
  double DHH_;
  double THALF_;
};



public ref class TemperatureParameters : public NotifyValidateEditBase
{
public:
  TemperatureParameters(void) {}
  TemperatureParameters( const TemperatureParameters ^ tp );
  virtual ~TemperatureParameters(void) {}

private:
  static void CheckValidLowLethalThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e );
  static void CheckValidLowThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e );
  static void CheckValidHighThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e );
  static void CheckValidHighLethalThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e );

public:
  [XmlElement(Order=0)]
  [ParameterDisplayAttribute(3, true, ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Survival must be between 0 and 1.")]
  property double LowLethalSurvival {
    double get(void) {
      return LowLethalSurvival_;
    }
    void set(double d) {
      if( LowLethalSurvival_ != d )  {
        LowLethalSurvival_ = d;
        NotifyAndValidate("LowLethalSurvival");
      }
    }
  }

  [XmlElement(Order=1)]
  [CustomRuleAttribute( "gui.TemperatureParameters,denmod.ui.objs", "CheckValidLowLethalThreshold", "Low lethal threshold must be less than low threshold." )]
  [ParameterDisplayAttribute(2, true, ScientificNotationOptions::Never)]
  property double LowLethalThreshold {
    double get(void) {
      return LowLethalThreshold_;
    }
    void set(double d) {
      if( LowLethalThreshold_ != d ) {
        LowLethalThreshold_ = d;
        NotifyAndValidate("LowLethalThreshold");
        ValidateProperty("LowThreshold");
      }
    }
  }

  [XmlElement(Order=2)]
  [CustomRuleAttribute( "gui.TemperatureParameters,denmod.ui.objs", "CheckValidLowThreshold", "Low threshold must be greater than low lethal threshold and less than high threshold." )]
  [ParameterDisplayAttribute(2, true, ScientificNotationOptions::Never)]
  property double LowThreshold {
    double get(void) {
      return LowThreshold_;
    }
    void set(double d) {
      if( LowThreshold_ != d ) {
        LowThreshold_ = d;
        NotifyAndValidate("LowThreshold");
        ValidateProperty("LowLethalThreshold");
        ValidateProperty("HighThreshold");
      }
    }
  }

  [XmlElement(Order=3)]
  [CustomRuleAttribute( "gui.TemperatureParameters,denmod.ui.objs", "CheckValidHighThreshold", "High threshold must be greater than low threshold and less than high lethal threshold." )]
  [ParameterDisplayAttribute(2, true, ScientificNotationOptions::Never)]
  property double HighThreshold {
    double get(void) {
      return HighThreshold_;
    }
    void set(double d) {
      if( HighThreshold_ != d ) {
        HighThreshold_ = d;
        NotifyAndValidate("HighThreshold");
        ValidateProperty("LowThreshold");
        ValidateProperty("HighLethalThreshold");
      }
    }
  }

  [XmlElement(Order=4)]
  [ParameterDisplayAttribute(2, true, ScientificNotationOptions::Never)]
  [CustomRuleAttribute( "gui.TemperatureParameters,denmod.ui.objs", "CheckValidHighLethalThreshold", "High lethal threshold must be greater than high threshold." )]
  property double HighLethalThreshold {
    double get(void) {
      return HighLethalThreshold_;
    }
    void set(double d) {
      if( HighLethalThreshold_ != d ) {
        HighLethalThreshold_ = d;
        NotifyAndValidate("HighLethalThreshold");
        ValidateProperty("HighThreshold");
      }
    }
  }

  [XmlElement(Order=5)]
  [ParameterDisplayAttribute(3, true, ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Survival must be between 0 and 1.")]
  property double HighLethalSurvival {
    double get(void) {
      return HighLethalSurvival_;
    }
    void set(double d) {
      if( HighLethalSurvival_ != d ) {
        HighLethalSurvival_ = d;
        NotifyAndValidate("HighLethalSurvival");
      }
    }
  }

protected:
  double LowLethalSurvival_;
  double LowLethalThreshold_;
  double LowThreshold_;
  double HighThreshold_;
  double HighLethalThreshold_;
  double HighLethalSurvival_;
};



public ref class EggDevelopment : public DevelopmentParameters
{
public:
  EggDevelopment(void);
  EggDevelopment( const EggDevelopment ^ ed );
  ~EggDevelopment(void) {}
  input::Biology::EggParameters::DevelopmentParameters * GetSimObject(void);

public:
  [ParameterDisplayAttribute(5,true,ScientificNotationOptions::Never)]
  property double RO25 {
    double get(void) {
      return DevelopmentParameters::RO25;
    }
    void set(double d) {
      DevelopmentParameters::RO25 = d;
    }
  }

  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  property double DHA {
    virtual double get(void) {
      return DevelopmentParameters::DHA;
    }
    virtual void set(double d) {
      DevelopmentParameters::DHA = d;
    }
  }

  [ParameterDisplayAttribute(0,true,ScientificNotationOptions::Never)]
  property double DHH {
    virtual double get(void) {
      return DevelopmentParameters::DHH;
    }
    virtual void set(double d) {
      DevelopmentParameters::DHH = d;
    }
  }

  [ParameterDisplayAttribute(1,true,ScientificNotationOptions::Never)]
  property double THALF {
    virtual double get(void) {
      return DevelopmentParameters::THALF;
    }
    virtual void set(double d) {
      DevelopmentParameters::THALF = d;
    }
  }
};



public ref class EggTemperature : public TemperatureParameters
{
public:
  EggTemperature(void);
  EggTemperature( const EggTemperature ^ et );
  ~EggTemperature(void) {}
  input::Biology::EggParameters::TemperatureParameters * GetSimObject(void);
};



public ref class EggSaturationDeficit : public NotifyValidateEditBase
{
public:
  EggSaturationDeficit(void);
  EggSaturationDeficit( const EggSaturationDeficit ^ esd );
  ~EggSaturationDeficit(void) {}

public:
  input::Biology::EggParameters::SaturationDeficitParameters * GetSimObject(void);

private:
  static void CheckValidHighThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e );
  static void CheckValidLowThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e );

public:
  [XmlElement(Order=0)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Survival must be between 0 and 1.")]
  property double WetSurvival {
    double get(void) {
      return WetSurvival_;
    }
    void set(double d) {
      if( WetSurvival_ != d ) {
        WetSurvival_ = d;
        NotifyAndValidate("WetSurvival");
      }
    }
  }

  [XmlElement(Order=1)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Sun exposure must be between 0 and 1.")]
  property double HighSunExposureThreshold {
    double get(void) {
      return HighSunExposureThreshold_;
    }
    void set(double d) {
      if( HighSunExposureThreshold_ != d ) {
        HighSunExposureThreshold_ = d;
        NotifyAndValidate("HighSunExposureThreshold");
      }
    }
  }

  [XmlElement(Order=2)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Survival must be between 0 and 1.")]
  property double HighSunExposureSurvival {
    double get(void) {
      return HighSunExposureSurvival_;
    }
    void set(double d) {
      if( HighSunExposureSurvival_ != d ) {
        HighSunExposureSurvival_ = d;
        NotifyAndValidate("HighSunExposureSurvival");
      }
    }
  }

  [XmlElement(Order=3)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CustomRuleAttribute( "gui.EggSaturationDeficit,denmod.ui.objs", "CheckValidLowThreshold", "Low threshold must be less than high threshold." )]
  property double LowThreshold {
    double get(void) {
      return LowThreshold_;
    }
    void set(double d) {
      if( LowThreshold_ != d ) {
        LowThreshold_ = d;
        NotifyAndValidate("LowThreshold");
        ValidateProperty("HighThreshold");
      }
    }
  }

  [XmlElement(Order=4)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CustomRuleAttribute( "gui.EggSaturationDeficit,denmod.ui.objs", "CheckValidHighThreshold", "High threshold must be greater than low threshold." )]
  property double HighThreshold {
    double get(void) {
      return HighThreshold_;
    }
    void set(double d) {
      if( HighThreshold_ != d ) {
        HighThreshold_ = d;
        NotifyAndValidate("HighThreshold");
        ValidateProperty("LowThreshold");
      }
    }
  }

  [XmlElement(Order=5)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Survival must be between 0 and 1.")]
  property double LowSurvival {
    double get(void) {
      return LowSurvival_;
    }
    void set(double d) {
      if( LowSurvival_ != d ) {
        LowSurvival_ = d;
        NotifyAndValidate("LowSurvival");
      }
    }
  }

  [XmlElement(Order=6)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Survival must be between 0 and 1.")]
  property double HighSurvival {
    double get(void) {
      return HighSurvival_;
    }
    void set(double d) {
      if( HighSurvival_ != d ) {
        HighSurvival_ = d;
        NotifyAndValidate("HighSurvival");
      }
    }
  }

private:
  double WetSurvival_;
  double HighSunExposureThreshold_;
  double HighSunExposureSurvival_;
  double LowThreshold_;
  double HighThreshold_;
  double LowSurvival_;
  double HighSurvival_;
};



public ref class EggPredation : public NotifyValidateEditBase
{
public:
  EggPredation(void);
  EggPredation( const EggPredation ^ ep );
  ~EggPredation(void) {}

public:
  input::Biology::EggParameters::PredationParameters * GetSimObject(void);

private:
  static void CheckValidHighThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e );
  static void CheckValidLowThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e );

public:
  [XmlElement(Order=0)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Survival must be between 0 and 1.")]
  property double LowSurvival {
    double get(void) {
      return LowSurvival_;
    }
    void set(double d) {
      if( LowSurvival != d ) {
        LowSurvival_ = d;
        NotifyAndValidate("LowSurvival");
      }
    }
  }

  [XmlElement(Order=1)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CustomRuleAttribute( "gui.EggPredation,denmod.ui.objs", "CheckValidLowThreshold", "Low threshold must be less than high threshold." )]
  property double LowThreshold {
    double get(void) {
      return LowThreshold_;
    }
    void set(double d) {
      if( LowThreshold_ != d ) {
        LowThreshold_ = d;
        NotifyAndValidate("LowThreshold");
        ValidateProperty("HighThreshold");
      }
    }
  }

  [XmlElement(Order=2)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CustomRuleAttribute( "gui.EggPredation,denmod.ui.objs", "CheckValidHighThreshold", "High threshold must be greater than high threshold." )]
  property double HighThreshold {
    double get(void) {
      return HighThreshold_;
    }
    void set(double d) {
      if( HighThreshold_ != d ) {
        HighThreshold_ = d;
        NotifyAndValidate("HighThreshold");
        ValidateProperty("LowThreshold");
      }
    }
  }

  [XmlElement(Order=3)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Survival must be between 0 and 1.")]
  property double HighSurvival {
    double get(void) {
      return HighSurvival_;
    }
    void set(double d) {
      if( HighSurvival_ != d ) {
        HighSurvival_ = d;
        NotifyAndValidate("HighSurvival");
      }
    }
  }

private:
  double LowSurvival_;
  double LowThreshold_;
  double HighThreshold_;
  double HighSurvival_;
};



public ref class EggBiology : public NotifyValidateEditBase
{
public:
  EggBiology(void);
  EggBiology( const EggBiology ^ eb );
  ~EggBiology(void) {}

public:
  input::Biology::EggParameters * GetSimObject(void);

public:
  [XmlElement(Order=0)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  property double MinimumHatchTemperature {
    double get(void) {
      return MinimumHatchTemperature_;
    }
    void set(double d) {
      if( MinimumHatchTemperature_ != d ) {
        MinimumHatchTemperature_ = d;
        NotifyAndValidate("MinimumHatchTemperature");
      }
    }
  }

  [XmlElement(Order=1)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute( 0, 1, ErrorMessage = "Flood hatch ratio must be between 0 and 1." )]
  property double FloodHatchRatio {
    double get(void) {
      return FloodHatchRatio_;
    }
    void set(double d) {
      if( FloodHatchRatio_ != d ) {
        FloodHatchRatio_ = d;
        NotifyAndValidate("FloodHatchRatio");
      }
    }
  }

  [XmlElement(Order=2)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute( 0, 1, ErrorMessage = "Spontaneous hatch ratio must be between 0 and 1." )]
  property double SpontaneousHatchRatio {
    double get(void) {
      return SpontaneousHatchRatio_;
    }
    void set(double d) {
      if( SpontaneousHatchRatio_ != d ) {
        SpontaneousHatchRatio_ = d;
        NotifyAndValidate("SpontaneousHatchRatio");
      }
    }
  }

  [XmlElement(Order=3)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute( 0, 1, ErrorMessage = "Nominal survival must be between 0 and 1." )]
  property double NominalSurvival {
    double get(void) {
      return NominalSurvival_;
    }
    void set(double ns) {
      if( NominalSurvival_ != ns ) {
        NominalSurvival_ = ns;
        NotifyAndValidate("NominalSurvival");
      }
    }
  }


  [XmlElement(Order=4)]
  [ValidatableRuleAttribute(UseMemberErrorMessages=false,ErrorMessage="Errors exists in egg development parameters.")]
  property EggDevelopment ^ Development {
    EggDevelopment ^ get(void) {
      return Development_;
    }
    void set(EggDevelopment ^ ed) {
      if( Development_ != ed ) {
        Development_ = ed;
        NotifyAndValidate("Development");
      }
    }
  }

  [XmlElement(Order=5)]
  [ValidatableRuleAttribute(UseMemberErrorMessages=false,ErrorMessage="Errors exists in egg temperature parameters.")]
  property EggTemperature ^ Temperature {
    EggTemperature ^ get(void) {
      return Temperature_;
    }
    void set(EggTemperature ^ et) {
      if( Temperature_ != et ) {
        Temperature_ = et;
        NotifyAndValidate("Temperature");
      }
    }
  }

  [XmlElement(Order=6)]
  [ValidatableRuleAttribute(UseMemberErrorMessages=false,ErrorMessage="Errors exists in egg saturation deficit parameters.")]
  property EggSaturationDeficit ^ SaturationDeficit {
    EggSaturationDeficit ^ get(void) {
      return SaturationDeficit_;
    }
    void set(EggSaturationDeficit ^ esd) {
      if( SaturationDeficit_ != esd ) {
        SaturationDeficit_ = esd;
        NotifyAndValidate("SaturationDeficit");
      }
    }
  }

  [XmlElement(Order=7)]
  [ValidatableRuleAttribute(UseMemberErrorMessages=false,ErrorMessage="Errors exists in egg predation parameters.")]
  property EggPredation ^ Predation {
    EggPredation ^ get(void) {
      return Predation_;
    }
    void set(EggPredation ^ ep) {
      if( Predation_ != ep ) {
        Predation_ = ep;
        NotifyAndValidate("Predation");
      }
    }
  }

private:
  double DevelopmentThreshold_;
  double MinimumHatchTemperature_;
  double FloodHatchRatio_;
  double SpontaneousHatchRatio_;
  double NominalSurvival_;
  EggDevelopment ^ Development_;
  EggTemperature ^ Temperature_;
  EggSaturationDeficit ^ SaturationDeficit_;
  EggPredation ^ Predation_;
};



public ref class LarvaeDevelopment : public DevelopmentParameters
{
public:
  LarvaeDevelopment(void);
  LarvaeDevelopment( const LarvaeDevelopment ^ ld );
  ~LarvaeDevelopment(void) {}

public:
  input::Biology::LarvaeParameters::DevelopmentParameters * GetSimObject(void);

public:
  [ParameterDisplayAttribute(5,true,ScientificNotationOptions::Never)]
  property double RO25 {
    double get(void) {
      return DevelopmentParameters::RO25;
    }
    void set(double d) {
      DevelopmentParameters::RO25 = d;
    }
  }

  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  property double DHA {
    virtual double get(void) {
      return DevelopmentParameters::DHA;
    }
    virtual void set(double d) {
      DevelopmentParameters::DHA = d;
    }
  }

  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  property double DHH {
    virtual double get(void) {
      return DevelopmentParameters::DHH;
    }
    virtual void set(double d) {
      DevelopmentParameters::DHH = d;
    }
  }

  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  property double THALF {
    virtual double get(void) {
      return DevelopmentParameters::THALF;
    }
    virtual void set(double d) {
      DevelopmentParameters::THALF = d;
    }
  }
};



public ref class LarvaePupationWeight : public NotifyValidateEditBase
{
public:
  LarvaePupationWeight(void);
  LarvaePupationWeight( const LarvaePupationWeight ^ lpw );
  ~LarvaePupationWeight(void) {}
  input::Biology::LarvaeParameters::PupationWeightParameters * GetSimObject(void);

public:
  [XmlElement(Order=0)]
  [ParameterDisplayAttribute(4,true,ScientificNotationOptions::Never)]
  property double Slope {
    double get(void) {
      return Slope_;
    }
    void set(double d) {
      if( Slope_ != d ) {
        Slope_ = d;
        NotifyAndValidate("Slope");
      }
    }
  }

  [XmlElement(Order=1)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  property double Intercept {
    double get(void) {
      return Intercept_;
    }
    void set(double d) {
      if( Intercept_ != d ) {
        Intercept_ = d;
        NotifyAndValidate("Intercept");
      }
    }
  }

  [XmlElement(Order=2)]
  [ParameterDisplayAttribute(4,true,ScientificNotationOptions::Never)]
  [CompareDoubleRule(0,CompareOperator::GreaterThan,ErrorMessage="Weight must be greater than 0.")]
  property double MinimumWeightForPupation {
    double get(void) {
      return MinimumWeightForPupation_;
    }
    void set(double d) {
      if( MinimumWeightForPupation_ != d ) {
        MinimumWeightForPupation_ = d;
        NotifyAndValidate("MinimumWeightForPupation");
      }
    }
  }

  [XmlElement(Order=3)]
  [ParameterDisplayAttribute(1,true,ScientificNotationOptions::Never)]
  [CompareDoubleRule(0,CompareOperator::GreaterThan,ErrorMessage="Development must be greater than 0.")]
  property double MaximumDevelopment {
    double get(void) {
      return MaximumDevelopment_;
    }
    void set(double d) {
      if( MaximumDevelopment_ != d ) {
        MaximumDevelopment_ = d;
        NotifyAndValidate("MaximumDevelopment");
      }
    }
  }

private:
  double Slope_;
  double Intercept_;
  double MinimumWeightForPupation_;
  double MaximumDevelopment_;
};



public ref class LarvaeTemperature : public TemperatureParameters
{
public:
  LarvaeTemperature(void);
  LarvaeTemperature( const LarvaeTemperature ^ lt );
  ~LarvaeTemperature(void) {}
  input::Biology::LarvaeParameters::TemperatureParameters * GetSimObject(void);
};



public ref class LarvaeFood : public NotifyValidateEditBase
{
public:
  LarvaeFood(void);
  LarvaeFood( const LarvaeFood ^ lf );
  ~LarvaeFood(void) {}
  input::Biology::LarvaeParameters::FoodParameters * GetSimObject(void);

public:
  [XmlElement(Order=0)]
  property bool UseRandomFood {
    bool get(void) {
      return UseRandomFood_;
    }
    void set(bool b) {
      if( UseRandomFood_ != b ) {
        UseRandomFood_ = b;
        NotifyAndValidate("UseRandomFood");
      }
    }
  }

  [XmlElement(Order=1)]
  [ParameterDisplayAttribute(1,true,ScientificNotationOptions::Never)]
  property double AssimilationRate {
    double get(void) {
      return AssimilationRate_;
    }
    void set(double d) {
      if( AssimilationRate_ != d ) {
        AssimilationRate_ = d;
        NotifyAndValidate("AssimilationRate");
      }
    }
  }

  [XmlElement(Order=2)]
  [ParameterDisplayAttribute(1,true,ScientificNotationOptions::Never)]
  property double ExploitationRate {
    double get(void) {
      return ExploitationRate_;
    }
    void set(double d) {
      if( ExploitationRate_ != d ) {
        ExploitationRate_ = d;
        NotifyAndValidate("ExploitationRate");
      }
    }
  }

  [XmlElement(Order=3)]
  [ParameterDisplayAttribute(1,true,ScientificNotationOptions::Never)]
  property double ExploitationRateIndependence {
    double get(void) {
      return ExploitationRateIndependence_;
    }
    void set(double d) {
      if( ExploitationRateIndependence_ != d ) {
        ExploitationRateIndependence_ = d;
        NotifyAndValidate("ExploitationRateIndependence");
      }
    }
  }

  [XmlElement(Order=4)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  property double MetabolicWeightLossRate {
    double get(void) {
      return MetabolicWeightLossRate_;
    }
    void set(double d) {
      if( MetabolicWeightLossRate_ != d ) {
        MetabolicWeightLossRate_ = d;
        NotifyAndValidate("MetabolicWeightLossRate");
      }
    }
  }

  [XmlElement(Order=5)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  property double MetabolicWeightLossExponent {
    double get(void) {
      return MetabolicWeightLossExponent_;
    }
    void set(double d) {
      if( MetabolicWeightLossExponent_ != d ) {
        MetabolicWeightLossExponent_ = d;
        NotifyAndValidate("MetabolicWeightLossExponent");
      }
    }
  }

private:
  bool UseRandomFood_;
  double AssimilationRate_;
  double ExploitationRate_;
  double ExploitationRateIndependence_;
  double MetabolicWeightLossRate_;
  double MetabolicWeightLossExponent_;
};



public ref class LarvaeFasting : public NotifyValidateEditBase
{
public:
  LarvaeFasting(void);
  LarvaeFasting( const LarvaeFasting ^ lf );
  ~LarvaeFasting(void) {}
  input::Biology::LarvaeParameters::FastingParameters * GetSimObject(void);

public:
  [XmlElement(Order=0)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Survival must be between 0 and 1.")]
  property double NoFastingSurvival {
    double get(void) {
      return NoFastingSurvival_;
    }
    void set(double d) {
      if( NoFastingSurvival_ != d ) {
        NoFastingSurvival_ = d;
        NotifyAndValidate("NoFastingSurvival");
      }
    }
  }

  [XmlElement(Order=1)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Survival must be between 0 and 1.")]
  property double LipidReserveSurvival {
    double get(void) {
      return LipidReserveSurvival_;
    }
    void set(double d) {
      if( LipidReserveSurvival_ != d ) {
        LipidReserveSurvival_ = d;
        NotifyAndValidate("LipidReserveSurvival");
      }
    }
  }

  [XmlElement(Order=2)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Survival must be between 0 and 1.")]
  property double NoLipidReserveSurvival {
    double get(void) {
      return NoLipidReserveSurvival_;
    }
    void set(double d) {
      if( NoLipidReserveSurvival_ != d ) {
        NoLipidReserveSurvival_ = d;
        NotifyAndValidate("NoLipidReserveSurvival");
      }
    }
  }

  [XmlElement(Order=3)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  property double NonDepletableLipidReserve {
    double get(void) {
      return NonDepletableLipidReserve_;
    }
    void set(double d) {
      if( NonDepletableLipidReserve_ != d ) {
        NonDepletableLipidReserve_ = d;
        NotifyAndValidate("NonDepletableLipidReserve");
      }
    }
  }

  [XmlElement(Order=4)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  property double WeightToLipidSlope {
    double get(void) {
      return WeightToLipidSlope_;
    }
    void set(double d) {
      if( WeightToLipidSlope_ != d ) {
        WeightToLipidSlope_ = d;
        NotifyAndValidate("WeightToLipidSlope");
      }
    }
  }

  [XmlElement(Order=5)]
  [ParameterDisplayAttribute(1,true,ScientificNotationOptions::Never)]
  property double WeightToLipidConstant {
    double get(void) {
      return WeightToLipidConstant_;
    }
    void set(double d) {
      if( WeightToLipidConstant_ != d ) {
        WeightToLipidConstant_ = d;
        NotifyAndValidate("WeightToLipidConstant");
      }
    }
  }

private:
  double NoFastingSurvival_;
  double LipidReserveSurvival_;
  double NoLipidReserveSurvival_;
  double NonDepletableLipidReserve_;
  double WeightToLipidSlope_;
  double WeightToLipidConstant_;
};



public ref class LarvaeBiology : public NotifyValidateEditBase
{
public:
  LarvaeBiology(void);
  LarvaeBiology( const LarvaeBiology ^ lb );
  ~LarvaeBiology(void) {}
  input::Biology::LarvaeParameters * GetSimObject(void);

public:
  [XmlElement(Order=0)]
  [ParameterDisplayAttribute(4,true,ScientificNotationOptions::Never)]
  [CompareDoubleRule(0,CompareOperator::GreaterThan,ErrorMessage="Weight must be greater than 0.")]
  property double WeightAtHatch {
    double get(void) {
      return WeightAtHatch_;
    }
    void set(double d) {
      if( WeightAtHatch_ != d ) {
        WeightAtHatch_ = d;
        NotifyAndValidate("WeightAtHatch");
      }
    }
  }

  [XmlElement(Order=1)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  property double ChronologicalBasisAt26C {
    double get(void) {
      return ChronologicalBasisAt26C_;
    }
    void set(double d) {
      if( ChronologicalBasisAt26C_ != d ) {
        ChronologicalBasisAt26C_ = d;
        NotifyAndValidate("ChronologicalBasisAt26C");
      }
    }
  }

  [XmlElement(Order=2)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Survival must be between 0 and 1.")]
  property double NominalSurvival {
    double get(void) {
      return NominalSurvival_;
    }
    void set(double d) {
      if( NominalSurvival_ != d ) {
        NominalSurvival_ = d;
        NotifyAndValidate("NominalSurvival");
      }
    }
  }

  [XmlElement(Order=3)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Survival must be between 0 and 1.")]
  property double PupationSurvival {
    double get(void) {
      return PupationSurvival_;
    }
    void set(double d) {
      if( PupationSurvival_ != d ) {
        PupationSurvival_ = d;
        NotifyAndValidate("PupationSurvival");
      }
    }
  }

  [XmlElement(Order=4)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Survival must be between 0 and 1.")]
  property double DryContainerSurvival {
    double get(void) {
      return DryContainerSurvival_;
    }
    void set(double d) {
      if( DryContainerSurvival_ != d ) {
        DryContainerSurvival_ = d;
        NotifyAndValidate("DryContainerSurvival");
      }
    }
  }

  [XmlElement(Order=5)]
  [ParameterDisplayAttribute(4,true,ScientificNotationOptions::Never)]
  [CompareDoubleRule(0,CompareOperator::GreaterThan,ErrorMessage="Weight must be greater than 0.")]
  property double MinimumWeightForSurvival {
    double get(void) {
      return MinimumWeightForSurvival_;
    }
    void set(double d) {
      if( MinimumWeightForSurvival_ != d ) {
        MinimumWeightForSurvival_ = d;
        NotifyAndValidate("MinimumWeightForSurvival");
      }
    }
  }

  [XmlElement(Order=6)]
  [ParameterDisplayAttribute(0,true,ScientificNotationOptions::Never)]
  [CompareIntRule(0,CompareOperator::GreaterThan,ErrorMessage="Number of steps must be greater than 0.")]
  property int NumberEulerSteps {
    int get(void) {
      return NumberEulerSteps_;
    }
    void set(int i) {
      if( NumberEulerSteps_ != i ) {
        NumberEulerSteps_ = i;
        NotifyAndValidate("NumberEulerSteps");
      }
    }
  }

  [XmlElement(Order=7)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Ratio must be between 0 and 1.")]
  property double CadaverFoodRatio {
    double get(void) {
      return CadaverFoodRatio_;
    }
    void set(double d) {
      if( CadaverFoodRatio_ != d ) {
        CadaverFoodRatio_ = d;
        NotifyAndValidate("CadaverFoodRatio");
      }
    }
  }

  [XmlElement(Order=8)]
  [ValidatableRuleAttribute(UseMemberErrorMessages=false,ErrorMessage="Errors exists in larvae development parameters.")]
  property LarvaeDevelopment ^ Development {
    LarvaeDevelopment ^ get(void) {
      return Development_;
    }
    void set(LarvaeDevelopment ^ ld) {
      if( Development_ != ld ) {
        Development_ = ld;
        NotifyAndValidate("Development");
      }
    }
  }

  [XmlElement(Order=9)]
  [ValidatableRuleAttribute(UseMemberErrorMessages=false,ErrorMessage="Errors exists in larvae pupation weight parameters.")]
  property LarvaePupationWeight ^ PupationWeight {
    LarvaePupationWeight ^ get(void) {
      return PupationWeight_;
    }
    void set(LarvaePupationWeight ^ lpw) {
      if( PupationWeight_ != lpw ) {
        PupationWeight_ = lpw;
        NotifyAndValidate("PupationWeight");
      }
    }
  }

  [XmlElement(Order=10)]
  [ValidatableRuleAttribute(UseMemberErrorMessages=false,ErrorMessage="Errors exists in larvae temperature parameters.")]
  property LarvaeTemperature ^ Temperature {
    LarvaeTemperature ^ get(void) {
      return Temperature_;
    }
    void set(LarvaeTemperature ^ lt) {
      if( Temperature_ != lt ) {
        Temperature_ = lt;
        NotifyAndValidate("Temperature");
      }
    }
  }

  [XmlElement(Order=11)]
  [ValidatableRuleAttribute(UseMemberErrorMessages=false,ErrorMessage="Errors exists in larvae food parameters.")]
  property LarvaeFood ^ Food {
    LarvaeFood ^ get(void) {
      return Food_;
    }
    void set(LarvaeFood ^ lf) {
      if( Food_ != lf ) {
        Food_ = lf;
        NotifyAndValidate("Food");
      }
    }
  }

  [XmlElement(Order=12)]
  [ValidatableRuleAttribute(UseMemberErrorMessages=false,ErrorMessage="Errors exists in larvae fasting parameters.")]
  property LarvaeFasting ^ Fasting {
    LarvaeFasting ^ get(void) {
      return Fasting_;
    }
    void set(LarvaeFasting ^ lf) {
      if( Fasting_ != lf ) {
        Fasting_ = lf;
        NotifyAndValidate("Fasting");
      }
    }
  }

private:
  double WeightAtHatch_;
  double ChronologicalBasisAt26C_;
  double NominalSurvival_;
  double PupationSurvival_;
  double DryContainerSurvival_;
  double MinimumWeightForSurvival_;
  int NumberEulerSteps_;
  double CadaverFoodRatio_;
  LarvaeDevelopment ^ Development_;
  LarvaePupationWeight ^ PupationWeight_;
  LarvaeTemperature ^ Temperature_;
  LarvaeFood ^ Food_;
  LarvaeFasting ^ Fasting_;
};



public ref class PupaeDevelopment : public DevelopmentParameters
{
public:
  PupaeDevelopment(void);
  PupaeDevelopment( const PupaeDevelopment ^ pd );
  ~PupaeDevelopment(void) {}
  input::Biology::PupaeParameters::DevelopmentParameters * GetSimObject(void);

public:
  [ParameterDisplayAttribute(4,true,ScientificNotationOptions::Never)]
  property double RO25 {
    double get(void) {
      return DevelopmentParameters::RO25;
    }
    void set(double d) {
      DevelopmentParameters::RO25 = d;
    }
  }

  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  property double DHA {
    virtual double get(void) {
      return DevelopmentParameters::DHA;
    }
    virtual void set(double d) {
      DevelopmentParameters::DHA = d;
    }
  }

  [ParameterDisplayAttribute(0,true,ScientificNotationOptions::Never)]
  property double DHH {
    virtual double get(void) {
      return DevelopmentParameters::DHH;
    }
    virtual void set(double d) {
      DevelopmentParameters::DHH = d;
    }
  }

  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  property double THALF {
    virtual double get(void) {
      return DevelopmentParameters::THALF;
    }
    virtual void set(double d) {
      DevelopmentParameters::THALF = d;
    }
  }
};



public ref class PupaeTemperature : public TemperatureParameters
{
public:
  PupaeTemperature(void);
  PupaeTemperature( const PupaeTemperature ^ pt );
  ~PupaeTemperature(void) {}
  input::Biology::PupaeParameters::TemperatureParameters * GetSimObject(void);
};



public ref class PupaeBiology : public NotifyValidateEditBase
{
public:
  PupaeBiology(void);
  PupaeBiology( const PupaeBiology ^ pb );
  ~PupaeBiology(void) {}

public:
  input::Biology::PupaeParameters * GetSimObject(void);

public:
  [XmlElement(Order=0)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Survival must be between 0 and 1.")]
  property double NominalSurvival {
    double get(void) {
      return NominalSurvival_;
    }
    void set(double d) {
      if( NominalSurvival_ != d ) {
        NominalSurvival_ = d;
        NotifyAndValidate("NominalSurvival");
      }
    }
  }

  [XmlElement(Order=1)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Survival must be between 0 and 1.")]
  property double EmergenceSurvival {
    double get(void) {
      return EmergenceSurvival_;
    }
    void set(double d) {
      if( EmergenceSurvival_ != d ) {
        EmergenceSurvival_ = d;
        NotifyAndValidate("EmergenceSurvival");
      }
    }
  }

  [XmlElement(Order=2)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Emergence must be between 0 and 1.")]
  property double FemaleEmergence {
    double get(void) {
      return FemaleEmergence_;
    }
    void set(double d) {
      if( FemaleEmergence_ != d ) {
        FemaleEmergence_ = d;
        NotifyAndValidate("FemaleEmergence");
      }
    }
  }

  [XmlElement(Order=3)]
  [ValidatableRuleAttribute(UseMemberErrorMessages=false,ErrorMessage="Errors exists in pupae development parameters.")]
  property PupaeDevelopment ^ Development {
   PupaeDevelopment ^ get(void) {
      return Development_;
    }
    void set(PupaeDevelopment ^ pd) {
      if( Development_ != pd ) {
        Development_ = pd;
        NotifyAndValidate("Development");
      }
    }
  }

  [XmlElement(Order=4)]
  [ValidatableRuleAttribute(UseMemberErrorMessages=false,ErrorMessage="Errors exists in pupae temperature parameters.")]
  property PupaeTemperature ^ Temperature {
   PupaeTemperature ^ get(void) {
      return Temperature_;
    }
    void set(PupaeTemperature ^ pt) {
      if( Temperature_ != pt ) {
        Temperature_ = pt;
        NotifyAndValidate("Temperature");
      }
    }
  }

private:
  double NominalSurvival_;
  double EmergenceSurvival_;
  double FemaleEmergence_;
  PupaeDevelopment ^ Development_;
  PupaeTemperature ^ Temperature_;
};



public ref class AdultAgeDependentSurvival: public NotifyValidateEditBase
{
public:
  AdultAgeDependentSurvival(void);
  AdultAgeDependentSurvival( const AdultAgeDependentSurvival ^ aads );
  ~AdultAgeDependentSurvival(void) {}
  input::Biology::AdultParameters::AgeDependentSurvivalParameters * GetSimObject(void);

public:
  [XmlElement(Order=0)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Survival must be between 0 and 1.")]
  property double YoungSurvival{
    double get(void) {
      return YoungSurvival_;
    }
    void set(double d) {
      if( YoungSurvival_ != d ) {
        YoungSurvival_ = d;
        NotifyAndValidate("YoungSurvival");
      }
    }
  }

  [XmlElement(Order=1)]
  [ParameterDisplayAttribute(0,true,ScientificNotationOptions::Never)]
  [CompareIntRule(1,CompareOperator::GreaterThanEqual,ErrorMessage="Cutoff age must be 1 or greater.")]
  property int CutoffAge {
    int get(void) {
      return CutoffAge_;
    }
    void set(int i) {
      if( CutoffAge_ != i ) {
        CutoffAge_ = i;
        NotifyAndValidate("CutoffAge");
      }
    }
  }

  [XmlElement(Order=2)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Survival must be between 0 and 1.")]
  property double OldSurvival {
    double get(void) {
      return OldSurvival_;
    }
    void set(double d) {
      if( OldSurvival != d ) {
        OldSurvival_ = d;
        NotifyAndValidate("OldSurvival");
      }
    }
  }

private:
  double YoungSurvival_;
  int CutoffAge_;
  double OldSurvival_;
};



public ref class AdultDevelopment : public DevelopmentParameters
{
public:
  AdultDevelopment(void);
  AdultDevelopment( const AdultDevelopment ^ ad );
  ~AdultDevelopment(void) {}
  input::Biology::AdultParameters::DevelopmentParameters * GetSimObject(void);

public:
  [ParameterDisplayAttribute(5,true,ScientificNotationOptions::Never)]
  property double RO25 {
    double get(void) {
      return DevelopmentParameters::RO25;
    }
    void set(double d) {
      DevelopmentParameters::RO25 = d;
    }
  }

  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  property double DHA {
    virtual double get(void) {
      return DevelopmentParameters::DHA;
    }
    virtual void set(double d) {
      DevelopmentParameters::DHA = d;
    }
  }

  [ParameterDisplayAttribute(0,true,ScientificNotationOptions::Never)]
  property double DHH {
    virtual double get(void) {
      return DevelopmentParameters::DHH;
    }
    virtual void set(double d) {
      DevelopmentParameters::DHH = d;
    }
  }

  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  property double THALF {
    virtual double get(void) {
      return DevelopmentParameters::THALF;
    }
    virtual void set(double d) {
      DevelopmentParameters::THALF = d;
    }
  }
};



public ref class AdultTemperature : public TemperatureParameters
{
public:
  AdultTemperature(void);
  AdultTemperature( const AdultTemperature ^ at );
  ~AdultTemperature(void) {}
  input::Biology::AdultParameters::TemperatureParameters * GetSimObject(void);
};



public ref class AdultSaturationDeficit : public NotifyValidateEditBase
{
public:
  AdultSaturationDeficit(void);
  AdultSaturationDeficit( const AdultSaturationDeficit ^ asd );
  ~AdultSaturationDeficit(void) {}

public:
  input::Biology::AdultParameters::SaturationDeficitParameters * GetSimObject(void);

private:
  static void CheckValidHighThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e );
  static void CheckValidLowThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e );

public:
  [XmlElement(Order=0)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Survival must be between 0 and 1.")]
  property double LowSurvival {
    double get(void) {
      return LowSurvival_;
    }
    void set(double d) {
      if( LowSurvival_ != d ) {
        LowSurvival_ = d;
        NotifyAndValidate("LowSurvival");
      }
    }
  }

  [XmlElement(Order=1)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CustomRuleAttribute( "gui.AdultSaturationDeficit,denmod.ui.objs", "CheckValidLowThreshold", "Low threshold must be less than high threshold." )]
  property double LowThreshold {
    double get(void) {
      return LowThreshold_;
    }
    void set(double d) {
      if( LowThreshold_ != d ) {
        LowThreshold_ = d;
        NotifyAndValidate("LowThreshold");
        ValidateProperty("HighThreshold");
      }
    }
  }

  [XmlElement(Order=2)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [CustomRuleAttribute( "gui.AdultSaturationDeficit,denmod.ui.objs", "CheckValidHighThreshold", "High threshold must be greater than high threshold." )]
  property double HighThreshold {
    double get(void) {
      return HighThreshold_;
    }
    void set(double d) {
      if( HighThreshold_ != d ) {
        HighThreshold_ = d;
        NotifyAndValidate("HighThreshold");
        ValidateProperty("LowThreshold");
      }
    }
  }

  [XmlElement(Order=3)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Survival must be between 0 and 1.")]
  property double HighSurvival {
    double get(void) {
      return HighSurvival_;
    }
    void set(double d) {
      if( HighSurvival_ != d ) {
        HighSurvival_ = d;
        NotifyAndValidate("HighSurvival");
      }
    }
  }

private:
  double LowThreshold_;
  double HighThreshold_;
  double LowSurvival_;
  double HighSurvival_;
};



public ref class AdultDoubleBloodMeal : public NotifyValidateEditBase
{
public:
  AdultDoubleBloodMeal(void);
  AdultDoubleBloodMeal( const AdultDoubleBloodMeal ^ adbm );
  ~AdultDoubleBloodMeal(void) {}

public:
  input::Biology::AdultParameters::DoubleBloodMealParameters * GetSimObject(void);

private:
  static void CheckValidHighThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e );
  static void CheckValidLowThreshold( System::Object ^ sender, CustomValidationEventArgs ^ e );

public:
  [XmlElement(Order=0)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Ratio must be between 0 and 1.")]
  property double LowWeightRatio {
    double get(void) {
      return LowWeightRatio_;
    }
    void set(double d) {
      if( LowWeightRatio_ != d ) {
        LowWeightRatio_ = d;
        NotifyAndValidate("LowWeightRatio");
      }
    }
  }

  [XmlElement(Order=1)]
  [ParameterDisplayAttribute(4,true,ScientificNotationOptions::Never)]
  [CustomRuleAttribute( "gui.AdultDoubleBloodMeal,denmod.ui.objs", "CheckValidLowThreshold", "Low threshold must be less than high threshold." )]
  property double LowWeightLimit {
    double get(void) {
      return LowWeightLimit_;
    }
    void set(double d) {
      if( LowWeightLimit_ != d ) {
        LowWeightLimit_ = d;
        NotifyAndValidate("LowWeightLimit");
        ValidateProperty("HighWeightLimit");
      }
    }
  }

  [XmlElement(Order=2)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [CustomRuleAttribute( "gui.AdultDoubleBloodMeal,denmod.ui.objs", "CheckValidHighThreshold", "High threshold must be greater than low threshold." )]
  property double HighWeightLimit {
    double get(void) {
      return HighWeightLimit_;
    }
    void set(double d) {
      if( HighWeightLimit_ != d ) {
        HighWeightLimit_ = d;
        NotifyAndValidate("HighWeightLimit");
        ValidateProperty("LowWeightLimit");
      }
    }
  }

  [XmlElement(Order=3)]
  [ParameterDisplayAttribute(4,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Ratio must be between 0 and 1.")]
  property double HighWeightRatio {
    double get(void) {
      return HighWeightRatio_;
    }
    void set(double d) {
      if( HighWeightRatio_ != d ) {
        HighWeightRatio_ = d;
        NotifyAndValidate("HighWeightRatio");
      }
    }
  }

private:
  double LowWeightRatio_;
  double LowWeightLimit_;
  double HighWeightLimit_;
  double HighWeightRatio_;
};



public ref class AdultBiology : public NotifyValidateEditBase
{
public:
  AdultBiology(void);
  AdultBiology( const AdultBiology ^ ab );
  ~AdultBiology(void) {}
  input::Biology::AdultParameters * GetSimObject(void);

public:
  [XmlElement(Order=0)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [CompareDoubleRule(0,CompareOperator::GreaterThan,ErrorMessage="Development threshold must be greater than 0.")]
  property double SecondDevelopmentThreshold {
    double get(void) {
      return SecondDevelopmentThreshold_;
    }
    void set(double d) {
      if( SecondDevelopmentThreshold_ != d ) {
        SecondDevelopmentThreshold_ = d;
        NotifyAndValidate("SecondDevelopmentThreshold");
      }
    }
  }

  [XmlElement(Order=1)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Survival must be between 0 and 1.")]
  property double NominalSurvival {
    double get(void) {
      return NominalSurvival_;
    }
    void set(double d) {
      if( NominalSurvival_ != d ) {
        NominalSurvival_ = d;
        NotifyAndValidate("NominalSurvival");
      }
    }
  }

  [XmlElement(Order=2)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  property double DryToWetWeightFactor {
    double get(void) {
      return DryToWetWeightFactor_;
    }
    void set(double d) {
      if( DryToWetWeightFactor_ != d ) {
        DryToWetWeightFactor_ = d;
        NotifyAndValidate("DryToWetWeightFactor");
      }
    }
  }

  [XmlElement(Order=3)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  property double FecundityFactor {
    double get(void) {
      return FecundityFactor_;
    }
    void set(double d) {
      if( FecundityFactor_ != d ) {
        FecundityFactor_ = d;
        NotifyAndValidate("FecundityFactor");
      }
    }
  }

  [XmlElement(Order=4)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  property double MinimumOvipositionTemperature {
    double get(void) {
      return MinimumOvipositionTemperature_;
    }
    void set(double d) {
      if( MinimumOvipositionTemperature_ != d ) {
        MinimumOvipositionTemperature_ = d;
        NotifyAndValidate("MinimumOvipositionTemperature");
      }
    }
  }

  [XmlElement(Order=5)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Proportion must be between 0 and 1.")]
  property double ProportionOfFeedsOnHumans {
    double get(void) {
      return ProportionOfFeedsOnHumans_;
    }
    void set(double d) {
      if( ProportionOfFeedsOnHumans_ != d ) {
        ProportionOfFeedsOnHumans_ = d;
        NotifyAndValidate("ProportionOfFeedsOnHumans");
      }
    }
  }

  [XmlElement(Order=6)]
  [ParameterDisplayAttribute(0,true,ScientificNotationOptions::Never)]
  [CompareIntRuleAttribute(0,CompareOperator::GreaterThanEqual,ErrorMessage="Interrupted feeds per meal must be 0 or greater.")]
  property int InterruptedFeedsPerMeal {
    int get(void) {
      return InterruptedFeedsPerMeal_;
    }
    void set(int i) {
      if( InterruptedFeedsPerMeal_ != i ) {
        InterruptedFeedsPerMeal_ = i;
        NotifyAndValidate("InterruptedFeedsPerMeal");
      }
    }
  }

  [XmlElement(Order=7)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Proportion must be between 0 and 1.")]
  property double ProportionOfInterruptedFeedsOnDifferentHost {
    double get(void) {
      return ProportionOfInterruptedFeedsOnDifferentHost_;
    }
    void set(double d) {
      if( ProportionOfInterruptedFeedsOnDifferentHost_ != d ) {
        ProportionOfInterruptedFeedsOnDifferentHost_ = d;
        NotifyAndValidate("ProportionOfInterruptedFeedsOnDifferentHost");
      }
    }
  }

  [XmlElement(Order=8)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute(0,1,ErrorMessage="Proportion must be between 0 and 1.")]
  property double ProportionOfAdultsRestingOutdoors {
    double get(void) {
      return ProportionOfAdultsRestingOutdoors_;
    }
    void set(double d) {
      if( ProportionOfAdultsRestingOutdoors_ != d ) {
        ProportionOfAdultsRestingOutdoors_ = d;
        NotifyAndValidate("ProportionOfAdultsRestingOutdoors");
      }
    }
  }

  [XmlElement(Order=9)]
  [ValidatableRuleAttribute(UseMemberErrorMessages=false,ErrorMessage="Errors exists in adult age dependence parameters.")]
  property AdultAgeDependentSurvival ^ AgeDependentSurvival {
    AdultAgeDependentSurvival ^ get(void) {
      return AgeDependentSurvival_;
    }
    void set(AdultAgeDependentSurvival ^ aads) {
      if( AgeDependentSurvival_ != aads ) {
        AgeDependentSurvival_ = aads;
        NotifyAndValidate("AgeDependentSurvival");
      }
    }
  }

  [XmlElement(Order=10)]
  [ValidatableRuleAttribute(UseMemberErrorMessages=false,ErrorMessage="Errors exists in adult development parameters.")]
  property AdultDevelopment ^ Development {
    AdultDevelopment ^ get(void) {
      return Development_;
    }
    void set(AdultDevelopment ^ ad) {
      if( Development_ != ad ) {
        Development_ = ad;
        NotifyAndValidate("Development");
      }
    }
  }

  [XmlElement(Order=11)]
  [ValidatableRuleAttribute(UseMemberErrorMessages=false,ErrorMessage="Errors exists in adult temperature parameters.")]
  property AdultTemperature ^ Temperature {
    AdultTemperature ^ get(void) {
      return Temperature_;
    }
    void set(AdultTemperature ^ at) {
      if( Temperature_ != at ) {
        Temperature_ = at;
        NotifyAndValidate("Temperature");
      }
    }
  }

  [XmlElement(Order=12)]
  [ValidatableRuleAttribute(UseMemberErrorMessages=false,ErrorMessage="Errors exists in adult saturation deficit parameters.")]
  property AdultSaturationDeficit ^ SaturationDeficit {
    AdultSaturationDeficit ^ get(void) {
      return SaturationDeficit_;
    }
    void set(AdultSaturationDeficit ^ asd) {
      if( SaturationDeficit_ != asd ) {
        SaturationDeficit_ = asd;
        NotifyAndValidate("SaturationDeficit");
      }
    }
  }

  [XmlElement(Order=13)]
  [ValidatableRuleAttribute(UseMemberErrorMessages=false,ErrorMessage="Errors exists in adult double blood meal parameters.")]
  property AdultDoubleBloodMeal ^ DoubleBloodMeal {
   AdultDoubleBloodMeal ^ get(void) {
      return DoubleBloodMeal_;
    }
    void set(AdultDoubleBloodMeal ^ adbm) {
      if( DoubleBloodMeal_ != adbm ) {
        DoubleBloodMeal_ = adbm;
        NotifyAndValidate("DoubleBloodMeal");
      }
    }
  }

private:
  double FirstDevelopmentThreshold_;
  double SecondDevelopmentThreshold_;
  double NominalSurvival_;
  double DryToWetWeightFactor_;
  double FecundityFactor_;
  double MinimumOvipositionTemperature_;
  double ProportionOfFeedsOnHumans_;
  int InterruptedFeedsPerMeal_;
  double ProportionOfInterruptedFeedsOnDifferentHost_;
  double ProportionOfAdultsRestingOutdoors_;
  AdultAgeDependentSurvival ^ AgeDependentSurvival_;
  AdultDevelopment ^ Development_;
  AdultTemperature ^ Temperature_;
  AdultSaturationDeficit ^ SaturationDeficit_;
  AdultDoubleBloodMeal ^ DoubleBloodMeal_;
};



public ref class BiologyParameters : public NotifyValidateEditBase
{
public:
  BiologyParameters(void);
  BiologyParameters( const BiologyParameters ^ bp );
  ~BiologyParameters(void) {}
  input::Biology * GetSimObject(void);

public:
  void LoadDefaultValues(void);

public:
  [XmlElement(Order=0)]
  [ValidatableRuleAttribute(UseMemberErrorMessages=false,ErrorMessage="Errors exists in egg parameters.")]
  property EggBiology ^ Egg {
    EggBiology ^ get(void) {
      return Egg_;
    }
    void set(EggBiology ^ eb) {
      if( Egg_ != eb ) {
        Egg_ = eb;
        NotifyAndValidate("Egg");
      }
    }
  }

  [XmlElement(Order=1)]
  [ValidatableRuleAttribute(UseMemberErrorMessages=false,ErrorMessage="Errors exists in larvae parameters.")]
  property LarvaeBiology ^ Larvae {
    LarvaeBiology ^ get(void) {
      return Larvae_;
    }
    void set(LarvaeBiology ^ lb) {
      if( Larvae_ != lb ) {
        Larvae_ = lb;
        NotifyAndValidate("Larvae");
      }
    }
  }

  [XmlElement(Order=2)]
  [ValidatableRuleAttribute(UseMemberErrorMessages=false,ErrorMessage="Errors exists in pupae parameters.")]
  property PupaeBiology ^ Pupae {
    PupaeBiology ^ get(void) {
      return Pupae_;
    }
    void set(PupaeBiology ^ pb) {
      if( Pupae_ != pb ) {
        Pupae_ = pb;
        NotifyAndValidate("Pupae");
      }
    }
  }

  [XmlElement(ElementName="Adult",Order=3)]
  [ValidatableRuleAttribute(UseMemberErrorMessages=false,ErrorMessage="Errors exists in adult parameters.")]
  property AdultBiology ^ Adult {
    gui::AdultBiology ^ get(void) {
      return Adult_;
    }
    void set(gui::AdultBiology ^ ab) {
      if( Adult_ != ab ) {
        Adult_ = ab;
        NotifyAndValidate("Adult");
      }
    }      
  }

private:
  EggBiology ^ Egg_;
  LarvaeBiology ^ Larvae_;
  PupaeBiology ^ Pupae_;
  AdultBiology ^ Adult_;
};

};
