#include "StdAfx.h"
#include "Control.h"

using namespace gui;
using namespace System;



#pragma region Control
Control::Control(void)
: Enabled_(true),
  Schedule_(gcnew SingleSchedule())
{}



Control::Control( DateTime minDate, DateTime maxDate )
: Enabled_(true),
  Schedule_(gcnew SingleSchedule(minDate, maxDate))
{}



Control::Control( const Control ^ c )
{
  this->Name_ = c->Name_;
  this->Enabled_ = c->Enabled_;
  this->Schedule_ = c->Schedule_;
}



Control::~Control(void)
{}
#pragma endregion



#pragma region TargetedControl
generic<class T>
TargetedControl<T>::TargetedControl(void)
:  Targets_(gcnew ObjectBindingList<T>())
{}



generic<class T>
TargetedControl<T>::TargetedControl( DateTime minDate, DateTime maxDate )
: Control(minDate, maxDate),
  Targets_(gcnew ObjectBindingList<T>())
{}



generic<class T>
TargetedControl<T>::TargetedControl( const TargetedControl<T> ^ tc )
: Control(tc)
{
  this->Targets_ = gcnew ObjectBindingList<T>(tc->Targets_);
}



generic<class T>
TargetedControl<T>::~TargetedControl(void)
{}



generic<class T>
T
TargetedControl<T>::FindTarget( String ^ containerName )
{
  for each( T t in Targets_ ) {
    if( t->Name == containerName )
      return t;
  }
  return T();
}



generic<class T>
void
TargetedControl<T>::AddTarget( System::String ^ containerName )
{
  T t = safe_cast<T>( System::Activator::CreateInstance(T::typeid, gcnew array<Object^>(1){containerName}) );
  t->Name = containerName;
  Targets_->Add( t );
}



generic<class T>
void
TargetedControl<T>::AddTargets( array<String^> ^ containerNames )
{
  for each( String ^ s in containerNames ) {
    AddTarget( s );
  }
}



generic<class T>
void
TargetedControl<T>::RemoveTarget( String ^ containerName )
{
  T t = FindTarget( containerName );
  Targets_->Remove( t );
}
#pragma endregion



#pragma region SourceReduction
SourceReduction::SourceReduction(void)
{}



SourceReduction::SourceReduction( DateTime minDate, DateTime maxDate )
: TargetedControl(minDate, maxDate)
{}



SourceReduction::SourceReduction( const SourceReduction ^ sr )
: TargetedControl( sr )
{}



SourceReduction::~SourceReduction(void)
{}



input::Control *
SourceReduction::GetSimObject(void)
{
  input::SourceReduction * sr = new input::SourceReduction();

  sr->SetName( toss(this->Name) );
  sr->SetEnable( this->Enabled );
  sr->SetSchedule( Schedule->GetSimObject() );
  for each( SourceReductionTarget ^ srt in Targets ) {
    sr->AddTarget( toss(srt->Name), new input::SourceReduction::Parameters(srt->RateOfReduction) );
  }
  return sr;
}
#pragma endregion



#pragma region OvipositionExclusion
OvipositionExclusion::OvipositionExclusion(void)
{}



OvipositionExclusion::OvipositionExclusion( DateTime minDate, DateTime maxDate )
: TargetedControl(minDate, maxDate)
{}



OvipositionExclusion::OvipositionExclusion( const OvipositionExclusion ^ oe )
: TargetedControl(oe)
{}



OvipositionExclusion::~OvipositionExclusion(void)
{}



input::Control *
OvipositionExclusion::GetSimObject(void)
{
  input::OvipositionExclusion * oe = new input::OvipositionExclusion();

  oe->SetName( toss(this->Name) );
  oe->SetEnable( this->Enabled );
  oe->SetSchedule( Schedule->GetSimObject() );
  for each( OvipositionExclusionTarget ^ oet in Targets ) {
    oe->AddTarget( toss(oet->Name), new input::OvipositionExclusion::Parameters(oet->RateOfExclusion,oet->RateOfRecovery) );
  }
  return oe;
}
#pragma endregion



#pragma region EggDestruction
EggDestruction::EggDestruction(void)
{}



EggDestruction::EggDestruction( DateTime minDate, DateTime maxDate )
: TargetedControl(minDate, maxDate)
{}



EggDestruction::EggDestruction( const EggDestruction ^ ed )
: TargetedControl(ed)
{}



EggDestruction::~EggDestruction(void)
{}



input::Control *
EggDestruction::GetSimObject(void)
{
  input::EggDestruction * sr = new input::EggDestruction();

  sr->SetName( toss(this->Name) );
  sr->SetEnable( this->Enabled );
  sr->SetSchedule( Schedule->GetSimObject() );
  for each( EggDestructionTarget ^ edt in Targets ) {
    sr->AddTarget( toss(edt->Name), new input::EggDestruction::Parameters(edt->RateOfDestruction) );
  }
  return sr;
}
#pragma endregion



#pragma region Larvicide
Larvicide::Larvicide(void)
{}



Larvicide::Larvicide( DateTime minDate, DateTime maxDate )
: TargetedControl(minDate, maxDate)
{}



Larvicide::Larvicide( const Larvicide ^ li )
: TargetedControl(li)
{
  this->LagPeriod_ = li->LagPeriod_;
  this->InitialMortality_ = li->InitialMortality_;
  this->MaximumEffectPeriod_ = li->MaximumEffectPeriod_;
  this->DeclineEffectPeriod_ = li->DeclineEffectPeriod_;
  this->EffectLostWhenDry_ = li->EffectLostWhenDry_;
}



Larvicide::~Larvicide(void)
{}



input::Control *
Larvicide::GetSimObject(void)
{
  input::Larvicide * l = new input::Larvicide();

  l->SetName( toss(this->Name) );
  l->SetEnable( this->Enabled );
  l->SetSchedule( Schedule->GetSimObject() );
  for each( LarvicideTarget ^ lt in Targets ) {
    l->AddTarget( toss(lt->Name), new input::Larvicide::Parameters(lt->RateOfTreatment) );
  }
  l->SetLagPeriod( LagPeriod_ );
  l->SetInitialMortality( InitialMortality_ );
  l->SetMaxEffectPeriod( MaximumEffectPeriod_);
  l->SetDeclineEffectPeriod( DeclineEffectPeriod_ );
  l->SetEffectLostWhenDry( EffectLostWhenDry_ );

  return l;
}
#pragma endregion



#pragma region SterilMaleRelease
SterileMaleRelease::SterileMaleRelease(void)
{}



SterileMaleRelease::SterileMaleRelease( DateTime minDate, DateTime maxDate )
: Control(minDate, maxDate)
{}



SterileMaleRelease::SterileMaleRelease( const SterileMaleRelease ^ sm )
{
  this->Name_ = sm->Name_;
  this->Enabled_ = sm->Enabled_;
  this->Schedule_ = sm->Schedule_;
  this->NumberReleased_ = sm->NumberReleased_;
  this->SterilityRate_ = sm->SterilityRate_;
  this->Competitiveness_ = sm->Competitiveness_;
  this->RatioMaleToFemaleSurvival_ = sm->RatioMaleToFemaleSurvival_;
}



SterileMaleRelease::~SterileMaleRelease(void) {}



input::Control *
SterileMaleRelease::GetSimObject(void)
{
  input::SterileMaleRelease * sm = new input::SterileMaleRelease( toss(Name_), Enabled_, Schedule_->GetSimObject(),
                                                                  NumberReleased_,  SterilityRate_,
                                                                  Competitiveness_, RatioMaleToFemaleSurvival_ );
  return sm;
}
#pragma endregion



#pragma region SpaceSpray
SpaceSpray::SpaceSpray(void)
{}



SpaceSpray::SpaceSpray( DateTime minDate, DateTime maxDate )
: Control(minDate, maxDate)
{}



SpaceSpray::SpaceSpray( const SpaceSpray ^ sr )
{
  this->Name_ = sr->Name_;
  this->Enabled_ = sr->Enabled_;
  this->Schedule_ = sr->Schedule_;
  this->OutdoorMortality_ = sr->OutdoorMortality_;
  this->IndoorMortality_ = sr->IndoorMortality_;
}



SpaceSpray::~SpaceSpray(void)
{}



input::Control *
SpaceSpray::GetSimObject(void)
{
  input::SpaceSpray * ss = new input::SpaceSpray( toss(Name_), Enabled_, Schedule_->GetSimObject(), OutdoorMortality_, IndoorMortality_ );
  return ss;
}
#pragma endregion



#pragma region ResidualSpray
ResidualSpray::ResidualSpray(void)
{}



ResidualSpray::ResidualSpray( DateTime minDate, DateTime maxDate )
: Control(minDate, maxDate)
{}



ResidualSpray::ResidualSpray( const ResidualSpray ^ rs )
{
  this->Name_ = rs->Name_;
  this->Enabled_ = rs->Enabled_;
  this->Schedule_ = rs->Schedule_;
  this->InitialMortality_ = rs->InitialMortality_;
  this->MaximumEffectPeriod_ = rs->MaximumEffectPeriod_;
  this->ResidualEffectPeriod_ = rs->ResidualEffectPeriod_;
  this->TreatedInteriorProportion_ = rs->TreatedInteriorProportion_;
  this->TreatedHousesProportion_ = rs->TreatedHousesProportion_;
}



ResidualSpray::~ResidualSpray(void)
{}



input::Control *
ResidualSpray::GetSimObject(void)
{
  input::ResidualSpray * rs = new input::ResidualSpray( toss(Name_), Enabled_, Schedule_->GetSimObject(),
                                                        InitialMortality_, MaximumEffectPeriod_, ResidualEffectPeriod_,
                                                        TreatedInteriorProportion_, TreatedHousesProportion_ );
  return rs;
}
#pragma endregion
