#pragma once

#include "NotifyValidateEditBase.h"
#include "AgeClasses.h"

#pragma managed( push, off )
#include "../../simulation/input/Demographics.h"
#pragma managed( pop )

using namespace System::Xml::Serialization;
using System::ComponentModel::BindingList;



namespace gui {

ref class DemographicParameters;

public ref class DemographicClass : public NotifyValidateEditBase
{
#pragma region Constructors
public:
  DemographicClass(void);
  DemographicClass( int rank );
  virtual ~DemographicClass(void);
  input::DemographicClass * GetSimObject(void);
#pragma endregion

#pragma region Properties
public:
  [XmlAttribute(AttributeName="birthRate")]
  [CompareDoubleRuleAttribute(0, CompareOperator::GreaterThanEqual, ErrorMessage="Birth rate cannot be negative." )]
  property double BirthRate {
    double get(void) {
      return BirthRate_;
    }
    void set(double d) {
      if( BirthRate_ != d ) {
        BirthRate_ = d;
        NotifyAndValidate( "BirthRate" );
      }
    }
  }

  [XmlAttribute(AttributeName="deathRate")]
  [CompareDoubleRuleAttribute(0, CompareOperator::GreaterThanEqual, ErrorMessage="Death rate cannot be negative." )]
  property double DeathRate {
    double get(void) {
      return DeathRate_;
    }
    void set(double d) {
      if( DeathRate_ != d ) {
        DeathRate_ = d;
        NotifyAndValidate( "DeathRate" );
      }
    }
  }

  [XmlAttribute(AttributeName="proportion")]
  [RangeDoubleRuleAttribute(0, 1, ErrorMessage="Age rank proportion must be between 0 and 1" )]
  property double Proportion {
    double get(void) {
      return Proportion_;
    }
    void set(double d) {
      if( Proportion_ != d ) {
        Proportion_ = d;
        NotifyAndValidate( "Proportion" );
      }
    }
  }

  [XmlAttribute(AttributeName="rank")]
  property int Rank {
    int get(void) {
      return Rank_;
    }
    void set(int i) {
      if( Rank_ != i ) {
        Rank_ = i;
        NotifyAndValidate( "Rank" );
      }
    }
  }

  [XmlIgnore]
  property System::String ^ AgeClass {
    System::String ^ get(void) {
      return AgeClasses::AgeRankToAgeClass( Rank_ );
    }
  }

  [XmlIgnore]
  property gui::DemographicParameters ^ DemographicParameters {
    gui::DemographicParameters ^ get(void) {
      return DemographicParameters_;
    }
    void set(gui::DemographicParameters ^ dp) {
      if( DemographicParameters_ != dp ) {
        DemographicParameters_ = dp;
      }
    }
  }

#pragma endregion

#pragma region Fields
private:
  int Rank_;
  double Proportion_;
  double DeathRate_;
  double BirthRate_;
  gui::DemographicParameters ^ DemographicParameters_;
#pragma endregion
};



public ref class DemographicParameters : public NotifyValidateEditBase
{
#pragma region Constructors
public:
  DemographicParameters(void);
  virtual ~DemographicParameters(void);
  input::Demographics * GetSimObject(void);
#pragma endregion

#pragma region Methods
public:
  void OnListChangedDemoClasses( Object ^ sender, System::ComponentModel::ListChangedEventArgs ^ e );

#pragma region Validation
private:
  static void CheckValidProportions( System::Object ^ sender, CustomValidationEventArgs ^ e );
#pragma endregion
#pragma endregion

#pragma region Properties
public:
  [XmlElement(ElementName="DemoClass",Order=0)]
  [CustomRuleAttribute( "gui.DemographicParameters,objs", "CheckValidProportions", "Validate proportions add to 1.0." )]
  property BindingList<DemographicClass^> ^ DemoClasses {
    BindingList<DemographicClass^> ^ get(void) {
      return DemoClasses_;
    }
    void set( BindingList<DemographicClass^> ^ bl ) {
      if( DemoClasses_ != bl ) {
        DemoClasses_ = bl;
        NotifyAndValidate( "DemoClasses" );
      }
    }
  }

  [XmlElement(ElementName="InitialPopulationSize",Order=1)]
  [ParameterDisplayAttribute( 0, true, ScientificNotationOptions::Never )]
  [CompareIntRuleAttribute( 0, CompareOperator::GreaterThan, ErrorMessage = "Initial population size must be greater than 0" )]
  [CompareIntRuleAttribute( 100000 , CompareOperator::LessThanEqual, ErrorMessage = "Initial population cannot be greater than 100,000" )]
  property int InitialPopulationSize {
    int get(void) {
      return InitialPopulationSize_;
    }
    void set(int i) {
      if( InitialPopulationSize_ != i ) {
        InitialPopulationSize_ = i;
        NotifyAndValidate( "InitialPopulationSize" );
      }
    }
  }

  [XmlElement(ElementName="HumanHostDensity",Order=2)]
  [ParameterDisplayAttribute(0,true,ScientificNotationOptions::Never)]
  [CompareDoubleRuleAttribute( 0, CompareOperator::GreaterThan, ErrorMessage = "Human host density must be greater than 0" )]
  property double HumanHostDensity {
    double get(void) {
      return HumanHostDensity_;
    }
    void set(double d) {
      if( HumanHostDensity != d ) {
        HumanHostDensity_ = d;
        NotifyAndValidate( "HumanHostDensity" );
      }
    }
  }
#pragma endregion

#pragma region Fields
private:
  BindingList<DemographicClass^> ^ DemoClasses_;
  int InitialPopulationSize_;
  double HumanHostDensity_;
#pragma endregion
};

};
