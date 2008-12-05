#pragma once

#include "NotifyValidateEditBase.h"
#include "Container.h"
#include "Control.h"
#include "Weather.h"
#include "Biology.h"
#include "Demographics.h"
#include "Serology.h"
#include "Virology.h"
#include "InfectionIntroduction.h"
#include "SequentialInfections.h"
#include "Util.h"

#pragma managed(push, off)
#include "../../simulation/input/Location.h"
#include "../../simulation/cimsim/Simulation.h"
#include "../../simulation/csport/csport.h"
#include "../../simulation/densim/Simulation.h"
#include "../../simulation/output/CimsimOutput.h"
#include "../../simulation/output/DensimOutput.h"
#include "../../simulation/output/MosData.h"
#pragma managed(pop)

using namespace System::Xml::Serialization;
using System::Collections::ArrayList;
using System::ComponentModel::BindingList;



namespace gui {

public ref class Location  : public NotifyValidateEditBase
{
// Classes
public:
  ref class RunCimsimOptions
  {
  public:
    bool UsePop;
    DateTime StartDate;
    DateTime StopDate;
  };

  ref class RunDensimOptions
  {
  public:
    DateTime StartDate;
    DateTime StopDate;
  };

// Typedefs
public:
  typedef System::Collections::Generic::Dictionary<System::String^,Dundas::Charting::WinControl::Series^> OutputSeries;
  typedef System::Collections::Generic::Dictionary<System::String^,OutputSeries^> ContainerOutputSeries;
  typedef System::Collections::Generic::Dictionary<int,OutputSeries^> SerotypeOutputSeries;

// Constructors
public:
  Location(void);
  virtual ~Location(void);


// Methods
public:
  input::Location * GetSimObject(void);

  int ContainerNameCount( System::String ^ name );
  void RenameContainer( gui::Container ^ container, System::String ^ previousName );
  bool RemoveContainer( gui::Container ^ container );

  void AddControl( gui::Control ^ control );
  bool RemoveControl( gui::Control ^ control );
  int GetNumberOfControls( System::Type ^ controlType );

  void ResetBiology(void);

  void RunCimsim( bool usePop, DateTime startDate, DateTime stopDate );
  gui::output::CimsimOutput ^ ProcessCimsimOutput( sim::output::CimsimOutput * co, DateTime startDate, DateTime stopDate );
  void TestingRunCimsim(void);

  void BeginFoodFit(void);
  void RunFoodFitIteration( int numberOfRuns, DateTime surveyStart, DateTime surveyEnd );
  FoodFitTotals ^ GetFoodFitTotals(void);
  void EndFoodFit(bool saveFitData);

  void RunDensim( DateTime startDate, DateTime stopDate );
  output::DensimOutput ^ ProcessDensimOutput( sim::output::DensimOutput * udo, DateTime startDate, DateTime stopDate );

// Properties
public:
  // <Name>
  [XmlElement(Order=0)]
  property System::String ^ Name {
    System::String ^ get(void) {
      return Name_;
    }
    void set(System::String ^ s) {
      Name_ = s;
      NotifyPropertyChanged( "Name" );
    }
  }

  // <Notes>
  [XmlElement(Order=1)]
  property System::String ^ Notes {
    System::String ^ get(void) {
      return Notes_;
    }
    void set(System::String ^ s) {
      Notes_ = s;
      NotifyPropertyChanged( "Notes" );
    }
  }

  // <SurveyStartDate>
  [XmlElement(Order=2)]
  property DateTime SurveyStartDate {
    DateTime get(void) {
      return SurveyStartDate_;
    }
    void set( DateTime dt ) {
      if( SurveyStartDate_ != dt ) {
        SurveyStartDate_ = dt;
        NotifyPropertyChanged( "SurveyStartDate" );
      }
    }
  }

  // <SurveyStartDate>
  [XmlElement(Order=3)]
  property DateTime SurveyStopDate {
    DateTime get(void) {
      return SurveyStopDate_;
    }
    void set( DateTime dt ) {
      if( SurveyStopDate_ != dt ) {
        SurveyStopDate_ = dt;
        NotifyPropertyChanged( "SurveyStopDate" );
      }
    }
  }

  // <Containers>
  [XmlArray(ElementName="Containers",Order=4)]
  [XmlArrayItem(ElementName="Container",Type=gui::Container::typeid)]
  property BindingList<Container^>^ Containers {
    BindingList<Container^>^ get(void) {
      return Containers_;
    }
    void set( BindingList<gui::Container^>^ containers ) {
      Containers_ = containers;
      NotifyPropertyChanged( "Containers" );
    }
  }

  // <Controls>
  [XmlArray(ElementName="Controls",Order=5)]
  [XmlArrayItem(ElementName="SourceReduction",Type=gui::SourceReduction::typeid)]
  [XmlArrayItem(ElementName="OvipositionExclusion",Type=gui::OvipositionExclusion::typeid)]
  [XmlArrayItem(ElementName="EggDestruction",Type=gui::EggDestruction::typeid)]
  [XmlArrayItem(ElementName="Larvicide",Type=gui::Larvicide::typeid)]
  [XmlArrayItem(ElementName="SterileMaleRelease",Type=gui::SterileMaleRelease::typeid)]
  [XmlArrayItem(ElementName="SpaceSpray",Type=gui::SpaceSpray::typeid)]
  [XmlArrayItem(ElementName="ResidualSpray",Type=gui::ResidualSpray::typeid)]
  property BindingList<Control^>^ Controls {
    BindingList<Control^>^ get(void) {
      return Controls_;
    }
    void set( BindingList<gui::Control^>^ controls ) {
      Controls_ = controls;
      NotifyPropertyChanged( "Controls" );
    }
  }

  // <Weather>
  [XmlElement(ElementName="Weather",Order=6)]
  property gui::WeatherData ^ Weather {
    WeatherData ^ get(void) {
      return Weather_;
    }
    void set(WeatherData ^ wd) {
      Weather_ = wd;
      NotifyPropertyChanged( "Weather" );
    }
  }

  // <Biology>
  [XmlElement(ElementName="Biology",Order=7)]
  property gui::BiologyParameters ^ Biology {
    BiologyParameters ^ get(void) {
      return Biology_;
    }
    void set( BiologyParameters ^ b ) {
      Biology_ = b;
      NotifyPropertyChanged( "Biology" );
    }
  }

  // <Demographics>
  [XmlElement(ElementName="Demographics",Order=8)]
  property gui::DemographicParameters ^ Demographics {
    DemographicParameters ^ get(void) {
      return Demographics_;
    }
    void set( DemographicParameters ^ d ) {
      Demographics_ = d;
      NotifyPropertyChanged( "Demographics" );
    }
  }

  // <Serology>
  [XmlElement(ElementName="Serology",Order=9)]
  property gui::SerologyParameters ^ Serology{
    SerologyParameters ^ get(void) {
      return Serology_;
    }
    void set( SerologyParameters ^ s ) {
      Serology_ = s;
      NotifyPropertyChanged( "Serology" );
    }
  }

  // <Virology>
  [XmlElement(ElementName="Virology",Order=10)]
  property gui::VirologyParameters ^ Virology {
    VirologyParameters ^ get(void) {
      return Virology_;
    }
    void set( VirologyParameters ^ v ) {
      Virology_ = v;
      NotifyPropertyChanged( "Virology" );
    }
  }

  // <InfectionIntroduction>
  [XmlElement(ElementName="InfectionIntroduction",Order=11)]
  property gui::InfectionIntroductionParameters ^ InfectionIntroduction {
    InfectionIntroductionParameters ^ get(void) {
      return InfectionIntroduction_;
    }
    void set( InfectionIntroductionParameters ^ iip ) {
      InfectionIntroduction_ = iip;
      NotifyPropertyChanged( "InfectionIntroduction" );
    }
  }

  // <Sequentials>
  [XmlElement(ElementName="SequentialInfections",Order=12)]
  property gui::SequentialInfectionParameters ^ SequentialInfections {
    SequentialInfectionParameters ^ get(void) {
      return SequentialInfections_;
    }
    void set( SequentialInfectionParameters ^ s ) {
      SequentialInfections_ = s;
      NotifyPropertyChanged( "SequentialInfections" );
    }
  }

  [XmlIgnore]
  property bool IsCimsimCompleted {
    bool get(void) {
      return _isCimsimCompleted;
    }
  }

  [XmlIgnore]
  property gui::output::CimsimOutput ^ CimsimOutput {
    gui::output::CimsimOutput ^ get(void) {
      return CimsimOutput_;
    }
  }

  [XmlIgnore]
  property sim::output::MosData * MosData {
    sim::output::MosData * get(void) {
      return MosData_;
    }
  }

  [XmlIgnore]
  property bool IsDensimCompleted {
    bool get(void) {
      return _isDensimCompleted;
    }
  }

  [XmlIgnore]
  property gui::output::DensimOutput ^ DensimOutput {
    gui::output::DensimOutput ^ get(void) {
      return DensimOutput_;
    }
  }

  [XmlIgnore]
  OutputSeries ^ DensimSeries_;

  [XmlIgnore]
  SerotypeOutputSeries ^ SerotypeSeries_;

// Fields
private:
  // Parameters
  System::String ^ Name_;
  System::String ^ Notes_;
  DateTime SurveyStartDate_;
  DateTime SurveyStopDate_;
  BindingList<Container^>^ Containers_;
  BindingList<Control^>^ Controls_;
  WeatherData ^ Weather_;
  BiologyParameters ^ Biology_;
  DemographicParameters ^ Demographics_;
  SerologyParameters ^ Serology_;
  VirologyParameters ^ Virology_;
  InfectionIntroductionParameters ^ InfectionIntroduction_;
  SequentialInfectionParameters ^ SequentialInfections_;

  // Output status and data
  bool _isCimsimCompleted;
  bool _isDensimCompleted;
  gui::output::CimsimOutput ^ CimsimOutput_;
  sim::output::MosData * MosData_;
  gui::output::DensimOutput ^ DensimOutput_;
};

};
