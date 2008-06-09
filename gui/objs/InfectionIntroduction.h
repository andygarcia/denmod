#pragma once

#include "NotifyValidateEditBase.h"
#include "Schedule.h"
#include "AgeClasses.h"

#pragma managed( push, off )
#include "../../simulation/input/InfectionIntroduction.h"
#pragma managed( pop )

using namespace System::Xml;
using namespace System::Xml::Serialization;
using System::ComponentModel::BindingList;



namespace gui {


enum class Serotypes {
  Dengue1,
  Dengue2,
  Dengue3,
  Dengue4
};



public ref class SerotypeIntroduction : public NotifyValidateEditBase
{
public:
  SerotypeIntroduction(void);
  ~SerotypeIntroduction(void);

  input::SerotypeIntroduction * GetSimObject(void);
  virtual System::String^ ToString(void) override;

public:
  [XmlElement(Order=0)]
  property int Humans {
    int get(void) {
      return Humans_;
    }
    void set(int i) {
      Humans_ = i;
      NotifyPropertyChanged( "Humans" );
    }
  }

  [XmlElement(Order=1)]
  property int Mosquitoes {
    int get(void) {
      return Mosquitoes_;
    }
    void set(int i) {
      Mosquitoes_ = i;
      NotifyPropertyChanged( "Mosquitoes" );
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
      Schedule_ = s;
      NotifyPropertyChanged( "Schedule" );
    }
  }

  [XmlIgnore]
  property Serotypes Serotype {
    Serotypes get(void) {
      return Serotype_;
    }
    void set(Serotypes s) {
      Serotype_ = s;
    }
  }

private:
  Serotypes Serotype_;
  int Humans_;
  int Mosquitoes_;
  gui::Schedule ^ Schedule_;
};



public ref class InfectionIntroductionParameters : public NotifyValidateEditBase
{
public:
  InfectionIntroductionParameters(void);
  virtual ~InfectionIntroductionParameters(void);

  input::InfectionIntroduction * GetSimObject(void);
  virtual System::String^ ToString(void) override;

public:
  [XmlElement(ElementName="Dengue1",Order=0)]
  property gui::SerotypeIntroduction ^ Dengue1 {
    gui::SerotypeIntroduction ^ get(void) {
      return Dengue1_;
    }
    void set( gui::SerotypeIntroduction ^ si ) {
      Dengue1_ = si;
      Dengue1_->Serotype = Serotypes::Dengue1;
      NotifyPropertyChanged( "Dengue1" );
    }
  }

  [XmlElement(ElementName="Dengue2",Order=1)]
  property gui::SerotypeIntroduction ^ Dengue2 {
    gui::SerotypeIntroduction ^ get(void) {
      return Dengue2_;
    }
    void set( gui::SerotypeIntroduction ^ si ) {
      Dengue2_ = si;
      Dengue2_->Serotype = Serotypes::Dengue2;
      NotifyPropertyChanged( "Dengue2" );
    }
  }

  [XmlElement(ElementName="Dengue3",Order=2)]
  property gui::SerotypeIntroduction ^ Dengue3 {
    gui::SerotypeIntroduction ^ get(void) {
      return Dengue3_;
    }
    void set( gui::SerotypeIntroduction ^ si ) {
      Dengue3_ = si;
      Dengue3_->Serotype = Serotypes::Dengue3;
      NotifyPropertyChanged( "Dengue3" );
    }
  }

  [XmlElement(ElementName="Dengue4",Order=3)]
  property gui::SerotypeIntroduction ^ Dengue4 {
    gui::SerotypeIntroduction ^ get(void) {
      return Dengue4_;
    }
    void set( gui::SerotypeIntroduction ^ si ) {
      Dengue4_ = si;
      Dengue4_->Serotype = Serotypes::Dengue4;
      NotifyPropertyChanged( "Dengue4" );
    }
  }

private:
  SerotypeIntroduction ^ Dengue1_;
  SerotypeIntroduction ^ Dengue2_;
  SerotypeIntroduction ^ Dengue3_;
  SerotypeIntroduction ^ Dengue4_;
};

};

