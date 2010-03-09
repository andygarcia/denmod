#pragma once

#include "NotifyValidateEditBase.h"
#include "ObjectBindingList.h"
#include "Schedule.h"
#include "Targets.h"
#include "Util.h"

#pragma managed( push, off )
#include "../../simulation/input/Control.h"
#pragma managed( pop )

using namespace System::Xml::Serialization;
using namespace ValidationFramework;



namespace gui {



public ref class Control abstract : public NotifyValidateEditBase
{
public:
  Control(void);
  Control( DateTime minDate, DateTime maxDate );
  Control( const Control ^ c );
  virtual ~Control(void);

  virtual input::Control * GetSimObject(void) abstract;

public:
  [XmlElement(Order=0)]
  property System::String ^ Name {
    System::String ^ get(void) {
      return Name_;
    }
    void set(System::String ^ s) {
      if( Name_ != s ) {
        Name_ = s;
        NotifyPropertyChanged( "Name" );
      }
    }
  }

  [XmlElement(Order=1)]
  property bool Enabled {
    bool get(void) {
      return Enabled_;
    }
    void set(bool b) {
      if( Enabled_ != b ) {
        Enabled_ = b;
        NotifyPropertyChanged( "Enabled" );
      }
    }
  }

  [XmlElement(Order=2)]
  [XmlElement("SingleSchedule",SingleSchedule::typeid)]
  [XmlElement("WeeklySchedule",WeeklySchedule::typeid)]
  [XmlElement("MonthlySchedule",MonthlySchedule::typeid)]
  [XmlElement("YearlySchedule",YearlySchedule::typeid)]
  [XmlElement("PeriodicSchedule",PeriodicSchedule::typeid)]
  property gui::Schedule ^ Schedule {
    gui::Schedule ^ get(void) {
      return Schedule_;
    }
    void set( gui::Schedule ^ s ) {
      if( Schedule_ != s ) {
        Schedule_ = s;
        NotifyPropertyChanged( "Schedule" );
      }
    }
  }

  protected:
    System::String ^ Name_;
    bool Enabled_;
    gui::Schedule ^ Schedule_;
};


generic<class T> where T : Target, ref class
public ref class TargetedControl abstract : public Control
{
#pragma region Constructors
public:
  TargetedControl(void);
  TargetedControl( DateTime minDate, DateTime maxDate );
  TargetedControl( const TargetedControl ^ tc );
  ~TargetedControl(void);
#pragma endregion

#pragma region Methods
public:
  void AddTarget( System::String ^ containerName );
  void AddTargets( array<System::String^> ^ containerNames );
  void RemoveTarget( System::String ^ containerName );
  T FindTarget( System::String ^ containerName );
#pragma endregion

#pragma region Properties
public:
  [XmlElementAttribute(Order=0)]
  property ObjectBindingList<T> ^ Targets {
    ObjectBindingList<T>^ get(void) {
      return Targets_;
    }
    void set( ObjectBindingList<T>^ obl ) {
      if( Targets != obl ) {
        Targets_ = obl;
        NotifyAndValidate( "Targets" );
      }
    }
  }
#pragma endregion

#pragma region Fields
protected:
  [OnEditSaveCloneAttribute()]
  ObjectBindingList<T> ^ Targets_;
#pragma endregion
};



public ref class SourceReduction : public TargetedControl<SourceReductionTarget^>
{
#pragma region Constructors
public:
  SourceReduction(void);
  SourceReduction( DateTime minDate, DateTime maxDate );
  SourceReduction( const SourceReduction ^ sr );
  ~SourceReduction(void);
#pragma endregion

#pragma region Methods
public:
  virtual input::Control * GetSimObject(void) override;
  //virtual void AddTarget( System::String ^ containerName ) override;
#pragma endregion
};



public ref class OvipositionExclusion : public TargetedControl<OvipositionExclusionTarget^>
{
#pragma region Constructors
public:
  OvipositionExclusion(void);
  OvipositionExclusion( DateTime minDate, DateTime maxDate );
  OvipositionExclusion( const OvipositionExclusion ^ sr );
  ~OvipositionExclusion(void);
#pragma endregion

#pragma region Methods
public:
  virtual input::Control * GetSimObject(void) override;
#pragma endregion
};



public ref class EggDestruction : public TargetedControl<EggDestructionTarget^>
{
#pragma region Constructors
public:
  EggDestruction(void);
  EggDestruction( DateTime minDate, DateTime maxDate );
  EggDestruction( const EggDestruction ^ sr );
  ~EggDestruction(void);
#pragma endregion

#pragma region Methods
public:
  virtual input::Control * GetSimObject(void) override;
#pragma endregion
};




public ref class Larvicide : public TargetedControl<LarvicideTarget^>
{
#pragma region Constructors
public:
  Larvicide(void);
  Larvicide( DateTime minDate, DateTime maxDate );
  Larvicide( const Larvicide ^ sr );
  ~Larvicide(void);
#pragma endregion

#pragma region Methods
public:
  virtual input::Control * GetSimObject(void) override;
#pragma endregion

#pragma region Property
public:
  [XmlElement(ElementName="LagPeriod",Order=0)]
  property int LagPeriod {
    int get(void) {
      return LagPeriod_;
    }
    void set(int i) {
      if( LagPeriod_ != i ) {
        LagPeriod_ = i;
        NotifyPropertyChanged( "LagPeriod" );
      }
    }
  }

  [XmlElement(ElementName="InitialMortality",Order=1)]
  property double InitialMortality {
    double get(void) {
      return InitialMortality_;
    }
    void set(double d) {
      if( InitialMortality_ != d ) {
        InitialMortality_ = d;
        NotifyPropertyChanged( "InitialMortality" );
      }
    }
  }

  [XmlElement(ElementName="MaximumEffectPeriod",Order=2)]
  property int MaximumEffectPeriod {
    int get(void) {
      return MaximumEffectPeriod_;
    }
    void set(int i) {
      if( MaximumEffectPeriod_ != i ) {
        MaximumEffectPeriod_ = i;
        NotifyPropertyChanged( "MaximumEffectPeriod" );
      }
    }
  }

  [XmlElement(ElementName="DeclineEffectPeriod",Order=3)]
  property int DeclineEffectPeriod {
    int get(void) {
      return DeclineEffectPeriod_;
    }
    void set(int i) {
      if( DeclineEffectPeriod_ != i ) {
        DeclineEffectPeriod_ = i;
        NotifyPropertyChanged( "DeclineEffectPeriod" );
      }
    }
  }

  [XmlElement(ElementName="EffectLostWhenDry",Order=4)]
  property bool EffectLostWhenDry {
    bool get(void) {
      return EffectLostWhenDry_;
    }
    void set(bool b) {
      if( EffectLostWhenDry_ != b ) {
        EffectLostWhenDry_ = b;
        NotifyPropertyChanged( "EffectLostWhenDry" );
      }
    }
  }
#pragma endregion

#pragma region Fields
private:
  int LagPeriod_;
  double InitialMortality_;
  int MaximumEffectPeriod_;
  int DeclineEffectPeriod_;
  bool EffectLostWhenDry_;
#pragma endregion
};



public ref class SterileMaleRelease : public Control
{
public:
  SterileMaleRelease(void);
  SterileMaleRelease( DateTime minDate, DateTime maxDate );
  SterileMaleRelease( const SterileMaleRelease ^ sm );
  ~SterileMaleRelease(void);

  virtual input::Control * GetSimObject(void) override;

public:
  [XmlElement(ElementName="NumberReleased",Order=0)]
  property double NumberReleased {
    double get(void) {
      return NumberReleased_;
    }
    void set(double d) {
      if( NumberReleased_ != d ) {
        NumberReleased_ = d;
        NotifyPropertyChanged( "NumberReleased" );
      }
    }
  }

  [XmlElement(ElementName="SterilityRate",Order=1)]
  property double SterilityRate {
    double get(void) {
      return SterilityRate_;
    }
    void set(double d) {
      if( SterilityRate_ != d ) {
        SterilityRate_ = d;
        NotifyPropertyChanged( "SterilityRate" );
      }
    }
  }

  [XmlElement(ElementName="Competitiveness",Order=2)]
  property double Competitiveness {
    double get(void) {
      return Competitiveness_;
    }
    void set(double d) {
      if( Competitiveness_ != d ) {
        Competitiveness_ = d;
        NotifyPropertyChanged( "Competitiveness" );
      }
    }
  }

  [XmlElement(ElementName="RatioMaleToFemaleSurvival",Order=3)]
  property double RatioMaleToFemaleSurvival {
    double get(void) {
      return RatioMaleToFemaleSurvival_;
    }
    void set(double d) {
      if( RatioMaleToFemaleSurvival_ != d ) {
        RatioMaleToFemaleSurvival_ = d;
        NotifyPropertyChanged( "RatioMaleToFemaleSurvival" );
      }
    }
  }

private:
  double NumberReleased_;
  double SterilityRate_;
  double Competitiveness_;
  double RatioMaleToFemaleSurvival_;
};



public ref class SpaceSpray : public Control
{
public:
  SpaceSpray(void);
  SpaceSpray( DateTime minDate, DateTime maxDate );
  SpaceSpray( const SpaceSpray ^ sr );
  ~SpaceSpray(void);

  virtual input::Control * GetSimObject(void) override;

public:
  [XmlElement(Order=0)]
  property double OutdoorMortality {
    double get(void) {
      return OutdoorMortality_;
    }
    void set(double d) {
      if( OutdoorMortality_ != d ) {
        OutdoorMortality_ = d;
        NotifyPropertyChanged( "OutdoorMortality" );
      }
    }
  }

  [XmlElement(Order=1)]
  property double IndoorMortality {
    double get(void) {
      return IndoorMortality_;
    }
    void set(double d) {
      if( IndoorMortality_ != d ) {
        IndoorMortality_ = d;
        NotifyPropertyChanged( "IndoorMortality" );
      }
    }
  }
private:
  double OutdoorMortality_;
  double IndoorMortality_;
};



public ref class ResidualSpray : public Control
{
public:
  ResidualSpray(void);
  ResidualSpray( DateTime minDate, DateTime maxDate );
  ResidualSpray( const ResidualSpray ^ rs );
  ~ResidualSpray(void);

  virtual input::Control * GetSimObject(void) override;

public:
  [XmlElement(ElementName="InitialMortality",Order=0)]
  property double InitialMortality {
    double get(void) {
      return InitialMortality_;
    }
    void set(double d) {
      if( InitialMortality_ != d ) {
        InitialMortality_ = d;
        NotifyPropertyChanged( "InitialMortality" );
      }
    }
  }

  [XmlElement(ElementName="MaximumEffectPeriod",Order=1)]
  property int MaximumEffectPeriod {
    int get(void) {
      return MaximumEffectPeriod_;
    }
    void set(int i) {
      if( MaximumEffectPeriod_ != i ) {
        MaximumEffectPeriod_ = i;
        NotifyPropertyChanged( "MaximumEffectPeriod" );
      }
    }
  }

  [XmlElement(ElementName="ResidualEffectPeriod",Order=2)]
  property int ResidualEffectPeriod {
    int get(void) {
      return ResidualEffectPeriod_;
    }
    void set(int i) {
      if( ResidualEffectPeriod_ != i ) {
        ResidualEffectPeriod_ = i;
        NotifyPropertyChanged( "ResidualEffectPeriod" );
      }
    }
  }

  [XmlElement(ElementName="TreatedInteriorProportion",Order=3)]
  property double TreatedInteriorProportion {
    double get(void) {
      return TreatedInteriorProportion_;
    }
    void set(double d) {
      if( TreatedInteriorProportion_ != d ) {
        TreatedInteriorProportion_ = d;
        NotifyPropertyChanged( "TreatedInteriorProportion" );
      }
    }
  }

  [XmlElement(ElementName="TreatedHousesProportion",Order=4)]
  property double TreatedHousesProportion {
    double get(void) {
      return TreatedHousesProportion_;
    }
    void set(double d) {
      if( TreatedHousesProportion_ != d ) {
        TreatedHousesProportion_ = d;
        NotifyPropertyChanged( "TreatedHousesProportion" );
      }
    }
  }

private:
  double InitialMortality_;
  int MaximumEffectPeriod_;
  int ResidualEffectPeriod_;
  double TreatedInteriorProportion_;
  double TreatedHousesProportion_;
};

};
