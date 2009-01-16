#pragma once

#include "NotifyValidateEditBase.h"

#pragma managed( push, off )
#include "../../simulation/input/Container.h"
#pragma managed( pop )

using namespace System::Xml::Serialization;
using namespace ValidationFramework;



namespace gui {



public ref class Container : public NotifyValidateEditBase
{
// TODO
private:
  static int _nextId;
  static Container()
  {
    _nextId = 1;
  }

#pragma region Enums
public:
  enum class ShapeType {
    Circular = 0,
    Rectangular
  };

  enum class Fill {
    ManualFill = 0,
    RainFill,
  };

  enum class Frequency {
    Daily = 0,
    Weekly,
    Monthly
  };
#pragma endregion

#pragma region Constructors
public:
  Container(void);
  Container( const Container ^ c );
  ~Container(void);
#pragma endregion

#pragma region Methods
public:
  input::Container * GetSimObject(void);
  virtual System::String ^ ToString(void) override;

  void BeginFoodFit(void);
  void UpdateInitialFood(void);
  void EndFoodFit( bool save );
#pragma region Validation
private:
  static void CheckValidLength( System::Object ^ sender, CustomValidationEventArgs ^ e );
  static void CheckValidWidth( System::Object ^ sender, CustomValidationEventArgs ^ e );
  static void CheckValidHeight( System::Object ^ sender, CustomValidationEventArgs ^ e );
  static void CheckValidDiameter( System::Object ^ sender, CustomValidationEventArgs ^ e );
  static void CheckValidCoverReduction( System::Object ^ sender, CustomValidationEventArgs ^ e );
  static void CheckValidWatershedRatio( System::Object ^ sender, CustomValidationEventArgs ^ e );
  static void CheckValidDrawdown( System::Object ^ sender, CustomValidationEventArgs ^ e );
#pragma endregion
#pragma endregion

#pragma region Properties
public:
  [XmlElementAttribute(Order=0)]
  [RequiredStringRuleAttribute( ErrorMessage = "Container name must be specified." )]
  property System::String ^ Name {
    System::String ^ get(void) {
      return Name_;
    }
    void set(System::String ^ s) {
      if( s != Name_ ) {
        Name_ = s;
        NotifyAndValidate( "Name" );
      }
    }
  }

  [XmlIgnore]
  property int Id {
    int get(void) {
      return Id_;
    }
  }

  [XmlElementAttribute(Order=1)]
  property ShapeType Shape {
    ShapeType get(void) {
      return Shape_;
    }
    void set(ShapeType st) {
      if( st != Shape_ ) {
        Shape_ = st;
        NotifyAndValidate( "Shape" );
        NotifyAndValidate( "Length" );
        NotifyAndValidate( "Width" );
        NotifyAndValidate( "Height" );
        NotifyAndValidate( "Diameter" );
      }
    }
  }

  [XmlIgnore]
  property double CapacityInLiters {
    double get(void) {
      if( Shape == ShapeType::Circular ) {
        return System::Math::PI * System::Math::Pow( (Diameter_/2), 2) * Height_;
      }
      else if( Shape == ShapeType::Rectangular ) {
        return Length_ * Width_ * Height_;
      }
      else {
        throw gcnew System::InvalidOperationException( "CapacityInLiters(): invalid shape type." );
      }
    }
  }

  [XmlElementAttribute(Order=2)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CustomRuleAttribute( "gui.Container,objs", "CheckValidLength", "Validate container dimensions." )]
  property double Length {
    double get(void) {
      return Length_;
    }
    void set(double d) {
      if( d != Length_ ) {
        Length_ = d;
        NotifyAndValidate( "Length" );
      }
    }
  }

  [XmlElementAttribute(Order=3)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CustomRuleAttribute( "gui.Container,objs", "CheckValidWidth", "Validate container dimensions." )]
  property double Width {
    double get(void) {
      return Width_;
    }
    void set(double d) {
      if( d != Width_ ) {
        Width_ = d;
        NotifyAndValidate( "Width" );
      }
    }
  }

  [XmlElementAttribute(Order=4)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CustomRuleAttribute( "gui.Container,objs", "CheckValidHeight", "Validate container dimensions." )]
  property double Height {
    double get(void) {
      return Height_;
    }
    void set(double d) {
      if( d != Height_ ) {
        Height_ = d;
        NotifyAndValidate( "Height" );
      }
    }
  }

  [XmlElementAttribute(Order=5)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CustomRuleAttribute( "gui.Container,objs", "CheckValidDiameter", "Validate container dimensions." )]
  property double Diameter {
    double get(void) {
      return Diameter_;
    }
    void set(double d) {
      if( d != Diameter_ ) {
        Diameter_ = d;
        NotifyAndValidate( "Diameter" );
      }
    }
  }

  [XmlElement(Order=6)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute( 0, 1, ErrorMessage = "Monthly turnover rate must be between 0 and 1." )]
  property double MonthlyTurnoverRate {
    double get(void) {
      return MonthlyTurnoverRate_;
    }
    void set(double d) {
      if( d != MonthlyTurnoverRate_ ) {
        MonthlyTurnoverRate_ = d;
        NotifyAndValidate( "MonthlyTurnoverRate" );
      }
    }
  }

  [XmlElementAttribute(Order=7)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CompareDoubleRule( 0, CompareOperator::GreaterThan, ErrorMessage = "Density must be greater than 0" )]
  property double Density {
    double get(void) {
      return Density_;
    }
    void set(double d) {
      if( d != Density_ ) {
        Density_ = d;
        NotifyAndValidate( "Density" );
      }
    }
  }

  [XmlElementAttribute(Order=8)]
  property bool IsCovered {
    bool get(void) {
      return IsCovered_;
    }
    void set(bool b) {
      if( b != IsCovered_ ) {
        IsCovered_ = b;
        NotifyAndValidate( "IsCovered" );
        ValidateProperty( "CoverReduction" );
      }
    }
  }

  [XmlElementAttribute(Order=9)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [CustomRuleAttribute( "gui.Container,objs", "CheckValidCoverReduction", "Validate based on cover status")]
  property double CoverReduction {
    double get(void) {
      return CoverReduction_;
    }
    void set(double d) {
      if( d != CoverReduction ) {
        CoverReduction_ = d;
        NotifyAndValidate( "CoverReduction" );
      }
    }
  }

  [XmlElementAttribute(Order=10)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute( 0, 1, ErrorMessage = "Sun exposure ratio must be between 0 and 1." )]
  property double SunExposure {
    double get(void) {
      return SunExposure_;
    }
    void set(double d) {
      if( d != SunExposure ) {
        SunExposure_ = d;
        NotifyAndValidate( "SunExposure" );
      }
    }
  }

  [XmlElementAttribute(Order=11)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRuleAttribute( 0, 1, ErrorMessage = "Cooling effect of evaporation must be between 0 and 1." )]
  property double Cooling {
    double get(void) {
      return Cooling_;
    }
    void set(double d) {
      if( d != Cooling_ ) {
        Cooling_ = d;
        NotifyAndValidate( "Cooling" );
      }
    }
  }

  [XmlElementAttribute(Order=12)]
  property Fill FillMethod {
    Fill get(void) {
      return FillMethod_;
    }
    void set(Fill f) {
      if( f != FillMethod_ ) {
        FillMethod_ = f;
        NotifyAndValidate( "FillMethod" );
        ValidateProperty( "WatershedRatio" );
      }
    }
  }

  [XmlElementAttribute(Order=13)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CustomRuleAttribute( "gui.Container,objs", "CheckValidDrawdown", "Validate container's drawdown." )]
  property double Drawdown {
    double get(void) {
      return Drawdown_;
    }
    void set(double d) {
      if( Drawdown_ != d ) {
        Drawdown_ = d;
        NotifyAndValidate( "Drawdown" );
      }
    }
  }

  [XmlElementAttribute(Order=14)]
  property Frequency DrawdownFrequency {
    Frequency get(void) {
      return DrawdownFrequency_;
    }
    void set(Frequency f) {
      if( f != DrawdownFrequency_ ) {
        DrawdownFrequency_ = f;
        NotifyAndValidate( "DrawdownFrequency" );
      }
    }
  }

  [XmlElementAttribute(Order=15)]
  property Frequency ManualFillFrequency {
    Frequency get(void) {
      return ManualFillFrequency_;
    }
    void set(Frequency f) {
      if( f != ManualFillFrequency_ ){
        ManualFillFrequency_ = f;
        NotifyAndValidate( "ManualFillFrequency" );
      }
    }
  }

  [XmlElementAttribute(Order=16)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [CustomRuleAttribute( "gui.Container,objs", "CheckValidWatershedRatio", "Validate container's watershed ratio." )]
  property double WatershedRatio {
    double get(void) {
      return WatershedRatio_;
    }
    void set(double d) {
      if( d != WatershedRatio_ ) {
        WatershedRatio_ = d;
        NotifyAndValidate( "WatershedRatio" );
      }
    }
  }

  [XmlElementAttribute(Order=17)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CompareDoubleRule( 0, CompareOperator::GreaterThanEqual, ErrorMessage = "Initial food cannot be negative." )]
  property double InitFood {
    double get(void) {
      return InitFood_;
    }
    void set(double d) {
      if( d != InitFood_ ) {
        InitFood_ = d;
        NotifyAndValidate( "InitFood" );
      }
    }
  }

  [XmlElementAttribute(Order=18)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CompareDoubleRule( 0, CompareOperator::GreaterThanEqual, ErrorMessage = "Daily food additions cannot be negative." )]
  property double FoodGainJan {
    double get(void) {
      return FoodGainJan_;
    }
    void set(double d) {
      if( d != FoodGainJan ) {
        FoodGainJan_ = d;
        NotifyAndValidate( "FoodGainJan" );
        NotifyAndValidate( "DailyFood" );
      }
    }
  }

  [XmlElementAttribute(Order=19)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CompareDoubleRule( 0, CompareOperator::GreaterThanEqual, ErrorMessage = "Daily food additions cannot be negative." )]
  property double FoodGainFeb {
    double get(void) {
      return FoodGainFeb_;
    }
    void set(double d) {
      if( d != FoodGainFeb_ ) {
        FoodGainFeb_ = d;
        NotifyAndValidate( "FoodGainFeb" );
      }
    }
  }

  [XmlElementAttribute(Order=20)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CompareDoubleRule( 0, CompareOperator::GreaterThanEqual, ErrorMessage = "Daily food additions cannot be negative." )]
  property double FoodGainMar {
    double get(void) {
      return FoodGainMar_;
    }
    void set(double d) {
      if( d != FoodGainMar_ ) {
        FoodGainMar_ = d;
        NotifyAndValidate( "FoodGainMar" );
      }
    }
  }

  [XmlElementAttribute(Order=21)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CompareDoubleRule( 0, CompareOperator::GreaterThanEqual, ErrorMessage = "Daily food additions cannot be negative." )]
  property double FoodGainApr {
    double get(void) {
      return FoodGainApr_;
    }
    void set(double d) {
      if( d != FoodGainApr_ ) {
        FoodGainApr_ = d;
        NotifyAndValidate( "FoodGainApr" );
      }
    }
  }

  [XmlElementAttribute(Order=22)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CompareDoubleRule( 0, CompareOperator::GreaterThanEqual, ErrorMessage = "Daily food additions cannot be negative." )]
  property double FoodGainMay {
    double get(void) {
      return FoodGainMay_;
    }
    void set(double d) {
      if( d != FoodGainMay_ ) {
        FoodGainMay_ = d;
        NotifyAndValidate( "FoodGainMay" );
      }
    }
  }

  [XmlElementAttribute(Order=23)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CompareDoubleRule( 0, CompareOperator::GreaterThanEqual, ErrorMessage = "Daily food additions cannot be negative." )]
  property double FoodGainJun {
    double get(void) {
      return FoodGainJun_;
    }
    void set(double d) {
      if( d != FoodGainJun_ ) {
        FoodGainJun_ = d;
        NotifyAndValidate( "FoodGainJun" );
      }
    }
  }

  [XmlElementAttribute(Order=24)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CompareDoubleRule( 0, CompareOperator::GreaterThanEqual, ErrorMessage = "Daily food additions cannot be negative." )]
  property double FoodGainJul {
    double get(void) {
      return FoodGainJul_;
    }
    void set(double d) {
      if( d != FoodGainJul_ ) {
        FoodGainJul_ = d;
        NotifyAndValidate( "FoodGainJul" );
      }
    }
  }

  [XmlElementAttribute(Order=25)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CompareDoubleRule( 0, CompareOperator::GreaterThanEqual, ErrorMessage = "Daily food additions cannot be negative." )]
  property double FoodGainAug {
    double get(void) {
      return FoodGainAug_;
    }
    void set(double d) {
      if( d != FoodGainAug_ ) {
        FoodGainAug_ = d;
        NotifyAndValidate( "FoodGainAug" );
      }
    }
  }

  [XmlElementAttribute(Order=26)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CompareDoubleRule( 0, CompareOperator::GreaterThanEqual, ErrorMessage = "Daily food additions cannot be negative." )]
  property double FoodGainSep {
    double get(void) {
      return FoodGainSep_;
    }
    void set(double d) {
      if( d != FoodGainSep_ ) {
        FoodGainSep_ = d;
        NotifyAndValidate( "FoodGainSep" );
      }
    }
  }

  [XmlElementAttribute(Order=27)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CompareDoubleRule( 0, CompareOperator::GreaterThanEqual, ErrorMessage = "Daily food additions cannot be negative." )]
  property double FoodGainOct {
    double get(void) {
      return FoodGainOct_;
    }
    void set(double d) {
      if( d != FoodGainOct_ ) {
        FoodGainOct_ = d;
        NotifyAndValidate( "FoodGainOct" );
      }
    }
  }

  [XmlElementAttribute(Order=28)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CompareDoubleRule( 0, CompareOperator::GreaterThanEqual, ErrorMessage = "Daily food additions cannot be negative." )]
  property double FoodGainNov {
    double get(void) {
      return FoodGainNov_;
    }
    void set(double d) {
      if( d != FoodGainNov_ ) {
        FoodGainNov_ = d;
        NotifyAndValidate( "FoodGainNov" );
      }
    }
  }

  [XmlElementAttribute(Order=29)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CompareDoubleRule( 0, CompareOperator::GreaterThanEqual, ErrorMessage = "Daily food additions cannot be negative." )]
  property double FoodGainDec {
    double get(void) {
      return FoodGainDec_;
    }
    void set(double d) {
      if( d != FoodGainDec_ ) {
        FoodGainDec_ = d;
        NotifyAndValidate( "FoodGainDec" );
      }
    }
  }

  [XmlElementAttribute(Order=30)]
  [ParameterDisplayAttribute(3,true,ScientificNotationOptions::Never)]
  [RangeDoubleRule( 0, 1, ErrorMessage = "Food daily decay rate must be between 0 and 1." )]
  property double FoodDecayRate {
    double get(void) {
      return FoodDecayRate_;
    }
    void set(double d) {
      if( d != FoodDecayRate_ ) {
        FoodDecayRate_ = d;
        NotifyAndValidate( "FoodDecayRate" );
      }
    }
  }

  [XmlElementAttribute(Order=31)]
  [ParameterDisplayAttribute(0,true,ScientificNotationOptions::Never)]
  [CompareDoubleRule( 0, CompareOperator::GreaterThanEqual, ErrorMessage = "Initial egg count cannot be negative." )]
  property double InitEggs {
    double get(void) {
      return InitEggs_;
    }
    void set(double d) {
      if( d != InitEggs_ ) {
        InitEggs_ = d;
        NotifyAndValidate( "InitEggs" );
      }
    }
  }

  [XmlElementAttribute(Order=32)]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  [CompareDoubleRule( 0, CompareOperator::GreaterThanEqual, ErrorMessage = "Observed pupae counts cannot be negative." )]
  property double ObservedPerContainer {
    double get(void) {
      return ObservedPerContainer_;
    }
    void set(double d) {
      if( d != ObservedPerContainer_ ) {
        ObservedPerContainer_ = d;
        NotifyAndValidate( "ObservedPerContainer" );
        NotifyAndValidate( "ObservedPerHectare" );
        NotifyAndValidate( "DifferencePerHectare" );
      }
    }
  }


  [XmlIgnore]
  [ParameterDisplayAttribute(2,true,ScientificNotationOptions::Never)]
  property double DailyFood {
    double get(void) {
      return FoodGainJan_;
    }
    void set(double d) {
        if( d != FoodGainJan_ ) {
        FoodGainJan_ = d;
        FoodGainFeb_ = d;
        FoodGainMar_ = d;
        FoodGainApr_ = d;
        FoodGainMay_ = d;
        FoodGainJun_ = d;
        FoodGainJul_ = d;
        FoodGainAug_ = d;
        FoodGainSep_ = d;
        FoodGainOct_ = d;
        FoodGainNov_ = d;
        FoodGainDec_ = d;

        // TODO - hard code to 10.0 or react based on daily decay?
        if( DoingFoodFit_ ) {
          UpdateInitialFood();
        }

        NotifyAndValidate( "DailyFood" );
      }
    }
  }

  [XmlIgnore]
  property double ObservedPerHectare {
    double get(void) {
      return ObservedPerContainer_ * Density_;
    }  
  }

  [XmlIgnore]
  property double PredictedPerContainer {
    double get(void) {
      return PredictedPerContainer_;
    }
    void set(double d) {
      if( d != PredictedPerContainer_ ) {
        PredictedPerContainer_ = d;
        NotifyAndValidate( "PredictedPerContainer" );
        NotifyAndValidate( "PredictedPerHectare" );
        NotifyAndValidate( "DifferencePerHectare" );
      }
    }
  }

  [XmlIgnore]
  property double PredictedPerHectare {
    double get(void) {
      return PredictedPerContainer_ * Density_;
    }
  }

  [XmlIgnore]
  property double DifferencePerHectare {
    double get(void) {
      return System::Math::Abs(PredictedPerContainer_ - ObservedPerContainer_) * Density_;
    }
  }

  [XmlElementAttribute(Order=33)]
  property bool IsCloned {
    bool get(void) {
      return IsCloned_;
    }
    void set(bool b) {
      if( b != IsCloned_ ) {
        IsCloned_ = b;
        NotifyAndValidate( "IsCloned" );
      }
    }
  }

  [XmlElementAttribute(Order=34)]
  [ParameterDisplayAttribute(0,true,ScientificNotationOptions::Never)]
  [CompareIntRule( 1, CompareOperator::GreaterThanEqual, ErrorMessage = "Number of clones must be 1 or greater." )]
  property int NumberOfClones {
    int get(void) {
      return NumberOfClones_;
    }
    void set(int i) {
      if( i != NumberOfClones_) {
        NumberOfClones_ = i;
        NotifyAndValidate( "NumberOfClones" );
      }
    }
  }
#pragma endregion

#pragma region Fields
private:
  System::String ^ Name_;
  int Id_;
  ShapeType Shape_;
  double Length_;
  double Width_;
  double Height_;
  double Diameter_;
  double MonthlyTurnoverRate_;
  double Density_;
  bool IsCovered_;
  double CoverReduction_;
  double SunExposure_;
  double Cooling_;
  Fill FillMethod_;
  double Drawdown_;
  Frequency DrawdownFrequency_;
  Frequency ManualFillFrequency_;
  double WatershedRatio_;
  double InitFood_;
  double FoodGainJan_;
  double FoodGainFeb_;
  double FoodGainMar_;
  double FoodGainApr_;
  double FoodGainMay_;
  double FoodGainJun_;
  double FoodGainJul_;
  double FoodGainAug_;
  double FoodGainSep_;
  double FoodGainOct_;
  double FoodGainNov_;
  double FoodGainDec_;
  double FoodDecayRate_;
  double InitEggs_;

  bool DoingFoodFit_;
  double ObservedPerContainer_;
  double PreFitFood_;
  double PreFitInitFood_;
  double PredictedPerContainer_;

  bool IsCloned_;
  int NumberOfClones_;
#pragma endregion
};



public ref class FoodFitTotals
{
#pragma region Constructors
public:
  FoodFitTotals(void) {}
  ~FoodFitTotals(void) {}
#pragma endregion

#pragma region Fields
public:
  double TotalObservedPupaePerHa;
  double TotalPredictedPupaePerHa;
  double Difference;
  double Ratio;
#pragma endregion
};

};
