#pragma once

#include "NotifyValidateEditBase.h"
#include "Util.h"

#pragma managed( push, off )
#include "../../simulation/input/Control.h"
#pragma managed( pop )

using namespace System::Xml::Serialization;
using namespace ValidationFramework;



namespace gui {

ref class SourceReductionTarget;
ref class OvipositionExclusionTarget;
ref class EggDestructionTarget;
ref class LarvicideTarget;

[XmlInclude(SourceReductionTarget::typeid)]
[XmlInclude(OvipositionExclusionTarget::typeid)]
[XmlInclude(EggDestructionTarget::typeid)]
[XmlInclude(LarvicideTarget::typeid)]
public ref class Target : public NotifyValidateEditBase
{
#pragma region Constructors
public:
  Target(void);
  Target( const Target ^ t );
  Target( System::String ^ name );
  ~Target(void);
#pragma endregion

#pragma region Properties
public:
  [XmlElement(Order=0)]
  property System::String ^ Name {
    System::String ^ get(void) {
      return Name_;
    }
    void set(System::String ^ s) {
      if( Name != s ) {
        Name_ = s;
        NotifyPropertyChanged( "Name" );
      }
    }
  }
#pragma endregion

#pragma region Fields
protected:
  System::String ^ Name_;
#pragma endregion
};



public ref class SourceReductionTarget : public Target
{
#pragma region Constructors
public:
  SourceReductionTarget(void);
  SourceReductionTarget( System::String ^ name );
  SourceReductionTarget( System::String ^ name, double rateOfReduction );
  SourceReductionTarget( const SourceReductionTarget ^ srt );
  ~SourceReductionTarget(void);
#pragma endregion

#pragma region Properties
  [XmlElement(Order=0)]
  [RangeDoubleRuleAttribute( 0, 1, ErrorMessage = "Rate of reduction must be between 0 and 1." )]
  property double RateOfReduction {
    double get(void) {
      return RateOfReduction_;
    }
    void set( double rr ) {
      if( RateOfReduction != rr ) {
        RateOfReduction_ = rr;
        NotifyAndValidate( "RateOfReduction" );
      }
    }
  }
#pragma endregion

#pragma region Fields
private:
  double RateOfReduction_;
#pragma endregion
};



public ref class OvipositionExclusionTarget : public Target
{
public:
  OvipositionExclusionTarget(void);
  OvipositionExclusionTarget( System::String ^ name );
  OvipositionExclusionTarget( System::String ^ name, double rateOfExclusion, double rateOfRecovery );
  OvipositionExclusionTarget( const OvipositionExclusionTarget ^ oet );
  ~OvipositionExclusionTarget(void);

public:
  [XmlElement(Order=0)]
  [RangeDoubleRuleAttribute( 0, 1, ErrorMessage = "Rate of exclusion must be between 0 and 1." )]
  property double RateOfExclusion {
    double get(void) {
      return RateOfExclusion_;
    }
    void set(double d) {
      if( RateOfExclusion_ != d ) {
        RateOfExclusion_ = d;
        NotifyAndValidate( "RateOfExclusion" );
      }
    }
  }

  [XmlElement(Order=1)]
  [RangeDoubleRuleAttribute( 0, 1, ErrorMessage = "Rate of recovery must be between 0 and 1." )]
  property double RateOfRecovery {
    double get(void) {
      return RateOfRecovery_;
    }
    void set(double d) {
      if( RateOfRecovery_ != d ) {
        RateOfRecovery_ = d;
        NotifyAndValidate( "RateOfRecovery" );
      }
    }
  }

private:
  double RateOfExclusion_;
  double RateOfRecovery_;
};



public ref class EggDestructionTarget : public Target
{
public:
  EggDestructionTarget(void);
  EggDestructionTarget( System::String ^ name );
  EggDestructionTarget( System::String ^ name, double rateOfDestruction );
  EggDestructionTarget( const EggDestructionTarget ^ edt );
  ~EggDestructionTarget(void);

public:
  [XmlElement(Order=0)]
  property double RateOfDestruction {
    double get(void) {
      return RateOfDestruction_;
    }
    void set(double d) {
      if( RateOfDestruction_ != d ) {
        RateOfDestruction_ = d;
        NotifyPropertyChanged( "RateOfDestruction" );
      }
    }
  }

private:
  double RateOfDestruction_;
};



public ref class LarvicideTarget : public Target
{
public:
  LarvicideTarget(void);
  LarvicideTarget( System::String ^ name );
  LarvicideTarget( System::String ^ name, double rateOfTreatment );
  LarvicideTarget( const LarvicideTarget ^ lt );
  ~LarvicideTarget(void);

public:
  [XmlElement(Order=0)]
  property double RateOfTreatment {
    double get(void) {
      return RateOfTreatment_;
    }
    void set(double d) {
      if( RateOfTreatment_ != d ) {
        RateOfTreatment_ = d;
        NotifyPropertyChanged( "RateOfTreatment" );
      }
    }
  }

private:
  double RateOfTreatment_;
};



};
