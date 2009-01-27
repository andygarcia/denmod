#include "StdAfx.h"
#include "Container.h"
#include "Util.h"

using namespace gui;



gui::Container::Container(void)
: NotifyValidateEditBase(),
  Name_(""),
  Id_( _nextId++ ),
  Shape_(ShapeType::Circular),
  Length_(1),
  Width_(1),
  Height_(1),
  Diameter_(1),
  MonthlyTurnoverRate_(0.0),
  Density_(1),
  IsCovered_(false),
  CoverReduction_(0.0),
  SunExposure_(0.0),
  Cooling_(0.0),
  FillMethod_(Fill::ManualFill),
  Drawdown_(0.0),
  DrawdownFrequency_(Frequency::Daily),
  ManualFillFrequency_(Frequency::Daily),
  WatershedRatio_(1.0),
  InitFood_(0.0),
  FoodGainJan_(0.0),
  FoodGainFeb_(0.0),
  FoodGainMar_(0.0),
  FoodGainApr_(0.0),
  FoodGainMay_(0.0),
  FoodGainJun_(0.0),
  FoodGainJul_(0.0),
  FoodGainAug_(0.0),
  FoodGainSep_(0.0),
  FoodGainOct_(0.0),
  FoodGainNov_(0.0),
  FoodGainDec_(0.0),
  FoodDecayRate_(0.0),
  InitEggs_(100),
  DoingFoodFit_(false),
  ObservedPerContainer_(0.0),
  PreFitFood_(0.0),
  PredictedPerContainer_(0.0),
  IsCloned_(false),
  NumberOfClones_(1)
{}



gui::Container::Container( const Container ^ c )
{
  this->Name_ = gcnew System::String( c->Name_ );
  this->Id_ = _nextId++;
  this->Shape_ = c->Shape_;
  this->Length_ = c->Length_;
  this->Width_ = c->Width_;
  this->Height_ = c->Height_;
  this->Diameter_ = c->Diameter_;
  this->MonthlyTurnoverRate_ = c->MonthlyTurnoverRate_;
  this->Density_ = c->Density_;
  this->IsCovered_ = c->IsCovered_;
  this->CoverReduction_ = c->CoverReduction_;
  this->SunExposure_ = c->SunExposure_;
  this->Cooling_ = c->Cooling_;
  this->FillMethod_ = c->FillMethod_;
  this->Drawdown_ = c->Drawdown_;
  this->DrawdownFrequency_ = c->DrawdownFrequency_;
  this->ManualFillFrequency_ = c->ManualFillFrequency_;
  this->WatershedRatio_ = c->WatershedRatio_;
  this->InitFood_ = c->InitFood_;
  this->FoodGainJan_ = c->FoodGainJan_;
  this->FoodGainFeb_ = c->FoodGainFeb_;
  this->FoodGainMar_ = c->FoodGainMar_;
  this->FoodGainApr_ = c->FoodGainApr_;
  this->FoodGainMay_ = c->FoodGainMay_;
  this->FoodGainJun_ = c->FoodGainJun_;
  this->FoodGainJul_ = c->FoodGainJul_;
  this->FoodGainAug_ = c->FoodGainAug_;
  this->FoodGainSep_ = c->FoodGainSep_;
  this->FoodGainOct_ = c->FoodGainOct_;
  this->FoodGainNov_ = c->FoodGainNov_;
  this->FoodGainDec_ = c->FoodGainDec_;
  this->FoodDecayRate_ = c->FoodDecayRate_;
  this->InitEggs_ = c->InitEggs_;
  this->ObservedPerContainer_ = c->ObservedPerContainer_;
  this->PreFitFood_ = c->PreFitFood_;
  this->PredictedPerContainer_ = c->PredictedPerContainer_;
  this->IsCloned_ = c->IsCloned_;
  this->NumberOfClones_ = c->NumberOfClones_;
}



gui::Container::~Container(void)
{
}



input::Container *
gui::Container::GetSimObject(void)
{
  input::Container * container = new input::Container();

  container->Name_ = toss(this->Name);
  container->Id_ = this->Id_;

  if( Shape_ == ShapeType::Circular ) {
    container->Shape_ = input::Container::Circle;
  }
  else if( Shape_ == ShapeType::Rectangular ) {
    container->Shape_ = input::Container::Rectangle;
  }

  container->Length_ = this->Length;
  container->Width_ = this->Width;
  container->Height_ = this->Height;
  container->Diameter_ = this->Diameter;
  container->WatershedRatio_ = this->WatershedRatio;

  container->Density_ = this->Density;
  container->MonthlyTurnoverRate_ = this->MonthlyTurnoverRate;

  container->SunExposure_ = this->SunExposure;
  container->Cooling_ = this->Cooling;

  container->IsCovered_ = this->IsCovered;
  container->CoverReduction_ = this->CoverReduction;

  if( FillMethod_ == Fill::ManualFill ) {
    container->FillMethod_ = input::Container::ManualFill;
  }
  else if( FillMethod_ == Fill::RainFill ) {
    container->FillMethod_ = input::Container::RainFill;
  }

  container->Drawdown_ = this->Drawdown;

  if( DrawdownFrequency_ == Frequency::Daily ) {
    container->DrawdownFrequency_ = input::Container::Daily;
  }
  else if( DrawdownFrequency_ == Frequency::Weekly ) {
    container->DrawdownFrequency_ = input::Container::Weekly;
  }
  else if( DrawdownFrequency_ == Frequency::Monthly ) {
    container->DrawdownFrequency_ = input::Container::Monthly;
  }

  if( ManualFillFrequency_ == Frequency::Daily ) {
    container->ManualFillFrequency_ = input::Container::Daily;
  }
  else if( ManualFillFrequency_ == Frequency::Weekly ) {
    container->ManualFillFrequency_ = input::Container::Weekly;
  }
  else if( ManualFillFrequency_ == Frequency::Monthly ) {
    container->ManualFillFrequency_ = input::Container::Monthly;
  }

  container->InitFood_ = this->InitFood;
  container->FoodGainJan_ = this->FoodGainJan;
  container->FoodGainFeb_ = this->FoodGainFeb;
  container->FoodGainMar_ = this->FoodGainMar;
  container->FoodGainApr_ = this->FoodGainApr;
  container->FoodGainMay_ = this->FoodGainMay;
  container->FoodGainJun_ = this->FoodGainJun;
  container->FoodGainJul_ = this->FoodGainJul;
  container->FoodGainAug_ = this->FoodGainAug;
  container->FoodGainSep_ = this->FoodGainSep;
  container->FoodGainOct_ = this->FoodGainOct;
  container->FoodGainNov_ = this->FoodGainNov;
  container->FoodGainDec_ = this->FoodGainDec;
  container->FoodDecayRate_ = this->FoodDecayRate;
  container->InitEggs_ = this->InitEggs;

  container->IsCloned_ = this->IsCloned_;
  container->NumberOfClones_ = this->NumberOfClones_;

  return container;
}



System::String ^
Container::ToString(void)
{
  System::Text::StringBuilder ^ sb = gcnew System::Text::StringBuilder();

  // name and shape
  sb->AppendLine( Name_ + " : " + System::Enum::GetName(ShapeType::typeid, Shape_) + " Shape" );

  // dimension with units and watershed ratio
  if( Shape_ == ShapeType::Circular ) {
    sb->Append( "d x h = " + Diameter_ + " (cm) x " + Height_ + " (cm), " );
  }
  else if( Shape_ == ShapeType::Rectangular ) {
    sb->Append( "l x w x h = " + Length_ + " (cm) x " + Width_  + " (cm) x " + Height_ + "(cm), " );
  }

  // density with possible turnover rate
  sb->Append( "Density = " + Density_ );
  if( MonthlyTurnoverRate_ == 0 ) {
    sb->AppendLine( " with no monthly turnover" );
  }
  else {
    sb->AppendLine( " with " + MonthlyTurnoverRate_ + " monthly turnover.");
  }

  // sun exposure with cover status and possible cover reductions
  sb->Append( "Sun exposure = " + SunExposure_ + ", " );
  if( IsCovered_ ) {
    sb->Append( "Covered" );
    if( CoverReduction == 0 ) {
      sb->AppendLine( " with no reduction in evaporation" );
    }
    else {
      sb->AppendLine( " with " + CoverReduction_ + " reduction in evaporation" );
    }
  }
  else {
    sb->AppendLine( "Not covered" );
  }

  // cooling status
  if( this->Cooling == 0 ) {
    sb->AppendLine( "No reduction in temperature from evaporation" );
  }
  else {
    sb->AppendLine( "" + Cooling_ + " reduction in temperature from evaporation" );
  }


  // fill method, with possible frequency
  if( FillMethod_ == Fill::ManualFill ) {
    sb->AppendLine( "Manually filled " + System::Enum::GetName(gui::Container::Frequency::typeid, ManualFillFrequency_)->ToLower() );
  }
  else if( FillMethod_ == Fill::RainFill ) {
    sb->AppendLine( "Rain filled with " + WatershedRatio_ + " watershed ratio." );
  }


  // possible drawdown with frequency, unless manually filled daily (considered full)
  if( FillMethod_ == Fill::ManualFill && ManualFillFrequency_ == Frequency::Daily ) {
    sb->AppendLine( "No drawdown" );
  }
  else if( Drawdown == 0 ) {
    sb->AppendLine( "No drawdown" );
  }
  else {
    System::String ^ sLiters = System::Double( Drawdown_ ).ToString( "F2" );
    System::String ^ sPercentage = System::Double( DrawdownPercentage ).ToString( "F2" );
    sb->AppendLine( "" + sPercentage + " % drawdown (" + sLiters  + " liters) " + System::Enum::GetName(gui::Container::Frequency::typeid, DrawdownFrequency_)->ToLower() );
  }


  // initial food and decay rates
  sb->AppendLine( "Initial food = " + InitFood_ + ", Food decay rate = " + FoodDecayRate_ );

  // daily food additions by month
  sb->AppendLine( "Daily food additions by month = " + this->FoodGainJan + ", " + FoodGainFeb + ", " + FoodGainMar + ", " + FoodGainApr + ", " + FoodGainMay + ", " +
                  FoodGainJun + ", " + FoodGainJul + ", " + FoodGainAug + ", " + FoodGainSep + ", " + FoodGainOct + ", " + FoodGainNov + ", " + FoodGainDec );

  // initial eggs
  sb->AppendLine( "Initial eggs = " + InitEggs_ );


  return sb->ToString();
}



void
Container::BeginFoodFit(void)
{
  DoingFoodFit_ = true;
  PreFitFood_ = DailyFood;
  PreFitInitFood_ = InitFood_;
}



void Container::UpdateInitialFood(void)
{
  InitFood = DailyFood * 10.0;
}



void
Container::EndFoodFit( bool save )
{
  if( !save ) {
    DailyFood = PreFitFood_;
    InitFood = PreFitInitFood_;
  }
  else {
    UpdateInitialFood();
  }
  DoingFoodFit_ = false;
}



void
Container::CheckValidLength( System::Object ^ sender, CustomValidationEventArgs ^ e )
{
  Container ^ c = (Container^) e->TargetObjectValue;
  double length = System::Convert::ToDouble( e->TargetMemberValue );

  if( c->Shape_ == ShapeType::Rectangular && length <= 0 ) {
    e->IsValid = false;
    e->ErrorMessage = "Length must be greater than 0";
  }
  else {
    e->IsValid = true;
  }
}



void
Container::CheckValidWidth( System::Object ^ sender, CustomValidationEventArgs ^ e )
{
  Container ^ c = (Container^) e->TargetObjectValue;
  double width = System::Convert::ToDouble( e->TargetMemberValue );

  if( c->Shape_ == ShapeType::Rectangular && width <= 0 ) {
    e->IsValid = false;
    e->ErrorMessage = "Width must be greater than 0";
  }
  else {
    e->IsValid = true;
  }
}



void
Container::CheckValidHeight( System::Object ^ sender, CustomValidationEventArgs ^ e )
{
  Container ^ c = (Container^) e->TargetObjectValue;
  double height= System::Convert::ToDouble( e->TargetMemberValue );

  if( height <= 0 ) {
    e->IsValid = false;
    e->ErrorMessage = "Height must be greater than 0.";
  }
  else {
    e->IsValid = true;
  }
}



void
Container::CheckValidDiameter( System::Object ^ sender, CustomValidationEventArgs ^ e )
{
  Container ^ c = (Container^) e->TargetObjectValue;
  double diameter = System::Convert::ToDouble( e->TargetMemberValue );

  if( c->Shape_ == ShapeType::Circular && diameter <= 0 ) {
    e->IsValid = false;
    e->ErrorMessage = "Diameter must be greater than 0.";
  }
  else {
    e->IsValid = true;
  }
}


  
void
Container::CheckValidCoverReduction( System::Object ^ sender, CustomValidationEventArgs ^ e )
{
  Container ^ c = (Container^) e->TargetObjectValue;
  double coverReduction = System::Convert::ToDouble( e->TargetMemberValue );

  // cover reduction must be between 0 and 1 if container is covered
  if( c->IsCovered == true && (coverReduction < 0 || coverReduction > 1) ) {
    e->IsValid = false;
    e->ErrorMessage = "Reduction in evaporation from cover must be between 0 and 1.";
  }
  else {
    e->IsValid = true;
  }
}



void
Container::CheckValidWatershedRatio( System::Object ^ sender, CustomValidationEventArgs ^ e )
{
  Container ^ c = (Container^) e->TargetObjectValue;
  double watershed = System::Convert::ToDouble( e->TargetMemberValue );

  // watershed must be greater than 0 if container is rain filled
  if( c->FillMethod_ == Fill::RainFill && watershed <= 0 ) {
    e->IsValid = false;
    e->ErrorMessage = "Watershed ratio must be greater than 0.";
  }
  else {
    e->IsValid = true;
  }
}


void
Container::CheckValidDrawdown( System::Object ^ sender, CustomValidationEventArgs ^ e )
{
  Container ^ c = (Container^) e->TargetObjectValue;
  double drawdown = System::Convert::ToDouble( e->TargetMemberValue );

  // drawdown must not be negative
  if( drawdown < 0 ) {
    e->IsValid = false;
    e->ErrorMessage = "Drawdow must be greater than 0.";
  }
  // or greater than container's actual capacity
  else if( drawdown > c->CapacityInLiters ) {
    e->IsValid = false;
    e->ErrorMessage = "Drawdown cannot be greater than container's capacity.";
  }
  else {
    e->IsValid = true;
  }
}

