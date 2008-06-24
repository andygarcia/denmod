#pragma once

#include "NotifyValidateEditBase.h"
#include "Biology.h"

#pragma managed( push, off )
#include "../../simulation/input/Virology.h"
#pragma managed( pop )

using namespace System::Xml::Serialization;
using namespace System::ComponentModel;



namespace gui {

public ref class EnzymeKineticDevelopmentParameters : public gui::DevelopmentParameters
{
public:
  EnzymeKineticDevelopmentParameters(void);
  virtual ~EnzymeKineticDevelopmentParameters(void);

  input::VirusDevelopment * GetSimObject(void);

public:
  [ParameterDisplayAttribute(6,true,ScientificNotationOptions::Always)]
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

  [ParameterDisplayAttribute(6,true,ScientificNotationOptions::Always)]
  property double DHH {
    virtual double get(void) {
      return DevelopmentParameters::DHH;
    }
    virtual void set(double d) {
      DevelopmentParameters::DHH = d;
    }
  }

  [ParameterDisplayAttribute(5,true,ScientificNotationOptions::Always)]
  property double THALF {
    virtual double get(void) {
      return DevelopmentParameters::THALF;
    }
    virtual void set(double d) {
      DevelopmentParameters::THALF = d;
    }
  }
};



public ref class SerotypeParameters : public NotifyValidateEditBase
{
public:
  SerotypeParameters(void);
  SerotypeParameters( int serotype );
  virtual ~SerotypeParameters(void);

  input::VirusSerotype * GetSimObject(void);

public:
  [XmlAttribute(AttributeName="viremicDuration")]
  property int ViremicDuration {
    int get(void) {
      return ViremicDuration_;
    }
    void set(int i) {
      ViremicDuration_ = i;
      NotifyPropertyChanged( "ViremicDuration" );
    }
  }

  [XmlAttribute(AttributeName="incubationDuration")]
  property int IncubationDuration {
    int get(void) {
      return IncubationDuration_;
    }
    void set(int i) {
      IncubationDuration_ = i;
      NotifyPropertyChanged( "IncubationDuration" );
    }
  }

  [XmlAttribute(AttributeName="viremia")]
  property double Viremia {
    double get(void) {
      return Viremia_;
    }
    void set(double d) {
      Viremia_ = d;
      NotifyPropertyChanged( "Viremia" );
    }
  }

  [XmlIgnore]
  property int Serotype {
    int get(void) {
      return Serotype_;
    }
    void set(int i) {
      Serotype_ = i;
    }
  }

  [XmlIgnore]
  property System::String ^ SerotypeString {
    System::String ^ get(void) {
      return "Dengue " + Serotype_;
    }
  }

private:
  int Serotype_;
  double Viremia_;
  int IncubationDuration_;
  int ViremicDuration_;
};



public ref class HumanToMosquitoInfectionParameters : public NotifyValidateEditBase
{
public:
  HumanToMosquitoInfectionParameters(void);
  virtual ~HumanToMosquitoInfectionParameters(void);

  input::HumanToMosquitoInfection * GetSimObject(void);

public:
  [XmlElement(ElementName="LowTiterSetPoint",Order=0)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  property double LowTiterSetPoint {
    double get(void) {
      return LowTiterSetPoint_;
    }
    void set(double d) {
      LowTiterSetPoint_ = d;
      NotifyPropertyChanged( "LowTiterSetPoint" );
    }
  }

  [XmlElement(ElementName="LowTiterInfection",Order=1)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  property double LowTiterInfection {
    double get(void) {
      return LowTiterInfection_;
    }
    void set(double d) {
      LowTiterInfection_ = d;
      NotifyPropertyChanged( "LowTiterInfection" );
    }
  }

  [XmlElement(ElementName="HighTiterSetPoint",Order=2)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  property double HighTiterSetPoint {
    double get(void) {
      return HighTiterSetPoint_;
    }
    void set(double d) {
      HighTiterSetPoint_ = d;
      NotifyPropertyChanged( "HighTiterSetPoint" );
    }
  }

  [XmlElement(ElementName="HighTiterInfection",Order=3)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  property double HighTiterInfection {
    double get(void) {
      return HighTiterInfection_;
    }
    void set(double d) {
      HighTiterInfection_ = d;
      NotifyPropertyChanged( "HighTiterInfection" );
    }
  }

private:
  double LowTiterSetPoint_;
  double LowTiterInfection_;
  double HighTiterSetPoint_;
  double HighTiterInfection_;
};



public ref class EIPTiterModificationParameters : public NotifyValidateEditBase
{
public:
  EIPTiterModificationParameters(void);
  virtual ~EIPTiterModificationParameters(void);

  input::EipTiterModification * GetSimObject(void);

public:
  [XmlElement(ElementName="LowSetPoint",Order=0)]
  [ParameterDisplayAttribute(0,true,ScientificNotationOptions::Always)]
  property double LowSetPoint {
    double get(void) {
      return LowSetPoint_;
    }
    void set(double d) {
      LowSetPoint_ = d;
      NotifyPropertyChanged( "LowSetPoint" );
    }
  }

  [XmlElement(ElementName="LowFactor",Order=1)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  property double LowFactor {
    double get(void) {
      return LowFactor_;
    }
    void set(double d) {
      LowFactor_ = d;
      NotifyPropertyChanged( "LowFactor" );
    }
  }

  [XmlElement(ElementName="HighSetPoint",Order=2)]
  [ParameterDisplayAttribute(0,true,ScientificNotationOptions::Always)]
  property double HighSetPoint {
    double get(void) {
      return HighSetPoint_;
    }
    void set(double d) {
      HighSetPoint_ = d;
      NotifyPropertyChanged( "HighSetPoint" );
    }
  }

  [XmlElement(ElementName="HighFactor",Order=3)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  property double HighFactor {
    double get(void) {
      return HighFactor_;
    }
    void set(double d) {
      HighFactor_ = d;
      NotifyPropertyChanged( "HighFactor" );
    }
  }

private:
  double LowSetPoint_;
  double LowFactor_;
  double HighSetPoint_;
  double HighFactor_;
};



public ref class EIPParameters : public NotifyValidateEditBase
{
public:
  EIPParameters(void);
  virtual ~EIPParameters(void);

  input::Eip * GetSimObject(void);

public:
  [XmlElement(ElementName="Development",Order=0)]
  property EnzymeKineticDevelopmentParameters ^ Development {
    EnzymeKineticDevelopmentParameters ^ get(void) {
      return Development_;
    }
    void set( EnzymeKineticDevelopmentParameters^ ekdp ) {
      Development_ = ekdp;
      NotifyPropertyChanged( "Development" );
    }  
  }

  [XmlElement(ElementName="TiterModification",Order=1)]
  property EIPTiterModificationParameters ^ TiterModification {
    EIPTiterModificationParameters ^ get(void) {
      return TiterModification_;
    }
    void set( EIPTiterModificationParameters ^ etmp ) {
      TiterModification_ = etmp;
      NotifyPropertyChanged( "TiterModification" );
    }  
  }

private:
  EnzymeKineticDevelopmentParameters ^ Development_;
  EIPTiterModificationParameters ^ TiterModification_;
};



public ref class VirologyParameters : public NotifyValidateEditBase
{
public:
  VirologyParameters(void);
  virtual ~VirologyParameters(void);

  input::Virology * GetSimObject(void);

public:
  [XmlIgnore]
  property BindingList<SerotypeParameters^> ^ Serotypes {
    BindingList<SerotypeParameters^> ^ get(void) {
      BindingList<SerotypeParameters^> ^ serotypes = gcnew BindingList<SerotypeParameters^>();
      serotypes->Add( Dengue1 );
      serotypes->Add( Dengue2 );
      serotypes->Add( Dengue3 );
      serotypes->Add( Dengue4 );
      return serotypes;
    }
  }

  [XmlElement(ElementName="Dengue1",Order=0)]
  property SerotypeParameters ^ Dengue1 {
    SerotypeParameters ^ get(void) {
      return Dengue1_;
    }
    void set(SerotypeParameters ^ vc) {
      Dengue1_ = vc;
      Dengue1_->Serotype = 1;
      NotifyPropertyChanged( "Dengue1" );
    }  
  }

  [XmlElement(ElementName="Dengue2",Order=1)]
  property SerotypeParameters ^ Dengue2 {
    SerotypeParameters ^ get(void) {
      return Dengue2_;
    }
    void set(SerotypeParameters ^ vc) {
      Dengue2_ = vc;
      Dengue2_->Serotype = 2;
      NotifyPropertyChanged( "Dengue2" );
    }  
  }

  [XmlElement(ElementName="Dengue3",Order=2)]
  property SerotypeParameters ^ Dengue3 {
    SerotypeParameters ^ get(void) {
      return Dengue3_;
    }
    void set(SerotypeParameters ^ vc) {
      Dengue3_ = vc;
      Dengue3_->Serotype = 3;
      NotifyPropertyChanged( "Dengue3" );
    }  
  }

  [XmlElement(ElementName="Dengue4",Order=3)]
  property SerotypeParameters ^ Dengue4 {
    SerotypeParameters ^ get(void) {
      return Dengue4_;
    }
    void set(SerotypeParameters ^ vc) {
      Dengue4_ = vc;
      Dengue4_->Serotype = 4;
      NotifyPropertyChanged( "Dengue4" );
    }  
  }

  [XmlElement(ElementName="HumanToMosquitoInfection",Order=4)]
  property HumanToMosquitoInfectionParameters ^ HumanToMosquitoInfection {
    HumanToMosquitoInfectionParameters ^ get(void) {
      return HumanToMosquitoInfection_;
    }
    void set( HumanToMosquitoInfectionParameters ^ htmip ) {
      HumanToMosquitoInfection_ = htmip;
      NotifyPropertyChanged( "HumanToMosquitoInfection" );
    }  
  }

  [XmlElement(ElementName="MosquitoToHumanNominalProbabilityOfInfection",Order=5)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  property double MosquitoToHumanNominalProbabilityOfInfection {
    double get(void) {
      return MosquitoToHumanNominalProbabilityOfInfection_;
    }
    void set( double d ) {
      MosquitoToHumanNominalProbabilityOfInfection_ = d;
      NotifyPropertyChanged( "MosquitoToHumanNominalProbabilityOfInfection" );
    }
  }

  [XmlElement(ElementName="MosquitoCountForStochasticity",Order=6)]
  [ParameterDisplayAttribute(0,true,ScientificNotationOptions::Never)]
  property double MosquitoCountForStochasticity {
    double get(void) {
      return MosquitoCountForStochasticity_;
    }
    void set( double d ) {
      MosquitoCountForStochasticity_ = d;
      NotifyPropertyChanged( "MosquitoCountForStochasticity" );
    }
  }

  [XmlElement(ElementName="EIP",Order=7)]
  property EIPParameters ^ EIP {
    EIPParameters ^ get(void) {
      return EIP_;
    }
    void set( EIPParameters ^ ep ) {
      EIP_ = ep;
      NotifyPropertyChanged( "EIP" );
    }  
  }

private:
  SerotypeParameters ^ Dengue1_;
  SerotypeParameters ^ Dengue2_;
  SerotypeParameters ^ Dengue3_;
  SerotypeParameters ^ Dengue4_;

  HumanToMosquitoInfectionParameters ^ HumanToMosquitoInfection_;
  double MosquitoToHumanNominalProbabilityOfInfection_;
  double MosquitoCountForStochasticity_;
  EIPParameters ^ EIP_;
};

};
