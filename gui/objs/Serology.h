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
      NotifyPropertyChanged( "Dengue4" );
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
      NotifyPropertyChanged( "Dengue3" );
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
      NotifyPropertyChanged( "dengue2" );
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
      NotifyPropertyChanged( "Dengue1" );
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
  [ParameterDisplayAttribute(0,true,ScientificNotationOptions::Never)]
  property int MANADuration{
    int get(void) {
      return MANADuration_;
    }
    void set(int i) {
      MANADuration_ = i;
      NotifyPropertyChanged( "MANADuration" );
    }
  }

  [XmlElement(ElementName="MAEADuration",Order=2)]
  [ParameterDisplayAttribute(0,true,ScientificNotationOptions::Never)]
  property int MAEADuration{
    int get(void) {
      return MAEADuration_;
    }
    void set(int i) {
      MAEADuration_ = i;
      NotifyPropertyChanged( "MAEADuration" );
    }
  }

  [XmlElement(ElementName="HeterologousImmunityDuration",Order=3)]
  [ParameterDisplayAttribute(0,true,ScientificNotationOptions::Never)]
  property int HetDuration{
    int get(void) {
      return HetDuration_;
    }
    void set(int i) {
      HetDuration_ = i;
      NotifyPropertyChanged( "HetDuration" );
    }
  }

private:
  BindingList<SerologyClass^> ^ SeroClasses_;
  int MANADuration_;
  int MAEADuration_;
  int HetDuration_;
};

};
