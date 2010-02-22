#pragma once

#include "NotifyValidateEditBase.h"
#include "AgeClasses.h"

#pragma managed( push, off )
#include "../../simulation/input/Serology.h"
#pragma managed( pop )

using namespace System::Xml::Serialization;
using System::ComponentModel::BindingList;



namespace gui {

public ref class SerologyClass : public NotifyValidateEditBase
{
public:
  SerologyClass(void);
  SerologyClass( int rank );
  virtual ~SerologyClass(void);
  input::SerologyClass * GetSimObject(void);

public:
  [XmlAttribute(AttributeName="dengue4")]
  [RangeDoubleRuleAttribute( 0, 1, ErrorMessage="Serotype proportions must be between 0 and 1." )]
  property double Dengue4 {
    double get(void) {
      return Dengue4_;
    }
    void set(double d) {
      Dengue4_ = d;
      NotifyAndValidate( "Dengue4" );
    }
  }

  [XmlAttribute(AttributeName="dengue3")]
  [RangeDoubleRuleAttribute( 0, 1, ErrorMessage="Serotype proportions must be between 0 and 1." )]
  property double Dengue3 {
    double get(void) {
      return Dengue3_;
    }
    void set(double d) {
      Dengue3_ = d;
      NotifyAndValidate( "Dengue3" );
    }
  }

  [XmlAttribute(AttributeName="dengue2")]
  [RangeDoubleRuleAttribute( 0, 1, ErrorMessage="Serotype proportions must be between 0 and 1." )]
  property double Dengue2 {
    double get(void) {
      return Dengue2_;
    }
    void set(double d) {
      Dengue2_ = d;
      NotifyAndValidate( "dengue2" );
    }
  }

  [XmlAttribute(AttributeName="dengue1")]
  [RangeDoubleRuleAttribute( 0, 1, ErrorMessage="Serotype proportions must be between 0 and 1." )]
  property double Dengue1 {
    double get(void) {
      return Dengue1_;
    }
    void set(double d) {
      Dengue1_ = d;
      NotifyAndValidate( "Dengue1" );
    }
  }

  [XmlAttribute(AttributeName="rank")]
  property int Rank {
    int get(void) {
      return Rank_;
    }
    void set(int i) {
      Rank_ = i;
      NotifyPropertyChanged( "Rank" );
    }
  }

  [XmlIgnore]
  property System::String ^ AgeClass {
    System::String ^ get(void) {
      return AgeClasses::AgeRankToAgeClass( Rank_ );
    }
  }

private:
  int Rank_;
  double Dengue1_;
  double Dengue2_;
  double Dengue3_;
  double Dengue4_;
};



public ref class SerologyParameters : public NotifyValidateEditBase
{
public:
  SerologyParameters(void);
  virtual ~SerologyParameters(void);
  void OnListChangedSeroClasses( Object ^ sender, System::ComponentModel::ListChangedEventArgs ^ e );

  input::Serology * GetSimObject(void);

  void AutoFillSerology( double proportion );

public:
  [XmlElement(ElementName="SeroClass",Order=0)]
  property BindingList<SerologyClass^> ^ SeroClasses {
    BindingList<SerologyClass^> ^ get(void) {
      return SeroClasses_;
    }
    void set( BindingList<SerologyClass^> ^ bl ) {
      SeroClasses_ = bl;
      NotifyPropertyChanged( "SeroClasses" );
    }
  }

  [XmlElement(ElementName="MANADuration",Order=1)]
  [CompareIntRule( 0, CompareOperator::GreaterThan, ErrorMessage = "Duration must be greater than 0 days." )]
  [ParameterDisplayAttribute(0,true,ScientificNotationOptions::Never)]
  property int MANADuration{
    int get(void) {
      return MANADuration_;
    }
    void set(int i) {
      MANADuration_ = i;
      NotifyAndValidate( "MANADuration" );
    }
  }

  [XmlElement(ElementName="MAEADuration",Order=2)]
  [CompareIntRule( 0, CompareOperator::GreaterThan, ErrorMessage = "Duration must be greater than 0 days." )]
  [ParameterDisplayAttribute(0,true,ScientificNotationOptions::Never)]
  property int MAEADuration{
    int get(void) {
      return MAEADuration_;
    }
    void set(int i) {
      MAEADuration_ = i;
      NotifyAndValidate( "MAEADuration" );
    }
  }

  [XmlElement(ElementName="HeterologousImmunityDuration",Order=3)]
  [CompareIntRule( 0, CompareOperator::GreaterThan, ErrorMessage = "Duration must be greater than 0 days." )]
  [ParameterDisplayAttribute(0,true,ScientificNotationOptions::Never)]
  property int HetDuration{
    int get(void) {
      return HetDuration_;
    }
    void set(int i) {
      HetDuration_ = i;
      NotifyAndValidate( "HetDuration" );
    }
  }

private:
  BindingList<SerologyClass^> ^ SeroClasses_;
  int MANADuration_;
  int MAEADuration_;
  int HetDuration_;
};

};
