#pragma once

#include "NotifyValidateEditBase.h"

#pragma managed( push, off )
#include "../../simulation/input/SequentialInfections.h"
#pragma managed( pop )

using namespace System::Xml;
using namespace System::Xml::Serialization;
using System::ComponentModel::BindingList;



namespace gui {


public ref class SequentialInfection : public NotifyValidateEditBase
{
public:
  SequentialInfection(void);
  SequentialInfection::SequentialInfection( System::String ^ sequence );
  virtual ~SequentialInfection(void);

  input::SequentialInfection * GetSimObject(void);

public:
  [XmlAttribute(AttributeName="mortality")]
  property double Mortality {
    double get(void) {
      return Mortality_;
    }
    void set(double d) {
      Mortality_ = d;
      NotifyPropertyChanged( "Mortality" );
    }
  }

  [XmlAttribute(AttributeName="atRiskCutoffAge")]
  property int AtRiskCutoffAge {
    int get(void) {
      return AtRiskCutoffAge_;
    }
    void set(int i) {
      AtRiskCutoffAge_ = i;
      NotifyPropertyChanged( "AtRiskCutoffAge" );
    }
  }

  [XmlAttribute(AttributeName="probability")]
  property double Probability {
    double get(void) {
      return Probability_;
    }
    void set(double d) {
      Probability_ = d;
      NotifyPropertyChanged( "Probability" );
    }
  }

  [XmlAttribute(AttributeName="maxMonths")]
  property int MaxMonths {
    int get(void) {
      return MaxMonths_;
    }
    void set(int i) {
      MaxMonths_ = i;
      NotifyPropertyChanged( "MaxMonths" );
    }
  }

  [XmlAttribute(AttributeName="minMonths")]
  property int MinMonths {
    int get(void) {
      return MinMonths_;
    }
    void set(int i) {
      MinMonths_ = i;
      NotifyPropertyChanged( "MinMonths" );
    }
  }

  [XmlAttribute(AttributeName="sequence")]
  property System::String ^ Sequence{
    System::String ^ get(void) {
      return SequenceOfInfection_;
    }
    void set(System::String ^ s) {
      SequenceOfInfection_ = s;
      NotifyPropertyChanged( "Sequence" );
    }
  }

private:
  System::String ^ SequenceOfInfection_;
  int MinMonths_;
  int MaxMonths_;
  double Probability_;
  int AtRiskCutoffAge_;
  double Mortality_;
};



public ref class SequentialInfectionParameters : public NotifyValidateEditBase
{
public:
  SequentialInfectionParameters(void);
  virtual ~SequentialInfectionParameters(void);
  void OnListChangedSequentialInfections( Object ^ sender, System::ComponentModel::ListChangedEventArgs ^ e );

  input::SequentialInfections * GetSimObject(void);

public:
  [XmlElement("SequentialInfection")]
  property BindingList<SequentialInfection^> ^ SequentialInfections {
    BindingList<SequentialInfection^>^ get(void) {
      return SequentialInfections_;
    }
    void set( BindingList<SequentialInfection^>^ bl ) {
      SequentialInfections_ = bl;
      NotifyPropertyChanged( "SequentialInfections" );
    }
  }

private:
  BindingList<SequentialInfection^> ^ SequentialInfections_;
};

};
