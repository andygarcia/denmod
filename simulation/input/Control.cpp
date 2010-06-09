#include "StdAfx.h"
#include "Control.h"
#include "Container.h"

using namespace boost::gregorian;
using namespace input;



std::string
Control::ControlTypeToString( ControlType ct )
{
  static std::string strings[] = { "Source Reduction", "Oviposition Exclusion", "Egg Destruction", "Sterile Male Release",
                                   "Space Spray", "Residual Spray", "Larvicide" };

  return strings[ct];
}



Control::Control( ControlType controlType, std::string name, bool enabled )
: ControlType_(controlType),
  Name_(name),
  Enabled_(enabled)
{}



Control::ControlType
Control::GetControlType(void)
{
  return this->ControlType_;
}



std::string
Control::GetControlTypeAsString(void)
{
  return ControlTypeToString( this->ControlType_ );
}



std::string Control::GetName(void)
{
  return Name_;
}



void Control::SetName( std::string name )
{
  Name_ = name;
}



bool Control::IsEnabled(void)
{
  return Enabled_;
}



void Control::SetEnable( bool b )
{
  Enabled_ = b;
}



ScheduledControl::ScheduledControl( ControlType controlType, std::string name, bool enabled, Schedule * schedule )
: Control( controlType, name, enabled ),
  Schedule_(schedule)
{}



ScheduledControl::~ScheduledControl(void)
{
  delete Schedule_;
}



bool
ScheduledControl::IsDateScheduled( date d )
{
  return Schedule_->IsDateScheduled(d);
}



void
ScheduledControl::CalculateSchedule( date minDate, date maxDate )
{
  this->Schedule_->CalculateSchedule( minDate, maxDate );
}



Schedule::ScheduleType
ScheduledControl::GetScheduleType(void)
{
  return Schedule_->GetScheduleType();
}



Schedule *
ScheduledControl::GetSchedule(void)
{
  return Schedule_;
}



void
ScheduledControl::SetSchedule( Schedule * schedule )
{
  Schedule_ = schedule;
}
  


SourceReduction::SourceReduction(void)
: ScheduledControl( Control::SourceReduction, "", false, NULL )
{}



SourceReduction::SourceReduction( std::string name, bool enabled, Schedule * schedule )
: ScheduledControl( Control::SourceReduction, name, enabled, schedule )
{}



SourceReduction::~SourceReduction(void)
{
  std::map<std::string, SourceReduction::Parameters*>::iterator itTrgt;
  for( itTrgt = Targets_.begin(); itTrgt != Targets_.end(); ++itTrgt ) {
    delete (*itTrgt).second;
  }
}



std::map<std::string, SourceReduction::Parameters*> &
SourceReduction::GetTargets(void)
{
  return Targets_;
}



void SourceReduction::AddTarget( std::string containerName, SourceReduction::Parameters * params )
{
  Targets_[containerName] = params;
}



bool SourceReduction::IsTarget( std::string containerName )
{
  std::map<std::string,SourceReduction::Parameters*>::iterator it = Targets_.find( containerName );

  if( it != Targets_.end() )
    return true;
  else
    return false;
}



SourceReduction::Parameters * SourceReduction::GetTargetParams( std::string containerName )
{
  return Targets_[containerName];
}



OvipositionExclusion::OvipositionExclusion(void)
: ScheduledControl( Control::OvipositionExclusion, "", false, NULL )
{}



OvipositionExclusion::OvipositionExclusion( std::string name, bool enabled, Schedule * schedule )
: ScheduledControl( Control::OvipositionExclusion, name, enabled, schedule ) {}



OvipositionExclusion::~OvipositionExclusion(void)
{}



std::map<std::string, OvipositionExclusion::Parameters*> & OvipositionExclusion::GetTargets(void)
{
  return Targets_;
}



void OvipositionExclusion::AddTarget( std::string containerName, OvipositionExclusion::Parameters * params )
{
  Targets_[containerName] = params;
}



bool OvipositionExclusion::IsTarget( std::string containerName )
{
  std::map<std::string,OvipositionExclusion::Parameters*>::iterator it = Targets_.find( containerName );

  if( it != Targets_.end() )
    return true;
  else
    return false;
}



OvipositionExclusion::Parameters * OvipositionExclusion::GetTargetParams( std::string containerName )
{
  return Targets_[containerName];
}



EggDestruction::EggDestruction(void)
: ScheduledControl( Control::EggDestruction, "", false, NULL )
{}



EggDestruction::EggDestruction( std::string name, bool enabled, Schedule * schedule )
: ScheduledControl( Control::EggDestruction, name, enabled, schedule )
{}



EggDestruction::~EggDestruction(void)
{}



std::map<std::string, EggDestruction::Parameters*> &
EggDestruction::GetTargets(void)
{
  return Targets_;
}



void
EggDestruction::AddTarget( std::string containerName, EggDestruction::Parameters * params )
{
  Targets_[containerName] = params;
}



bool
EggDestruction::IsTarget( std::string containerName )
{
  std::map<std::string,EggDestruction::Parameters*>::iterator it = Targets_.find( containerName );

  if( it != Targets_.end() )
    return true;
  else
    return false;
}



EggDestruction::Parameters *
EggDestruction::GetTargetParams( std::string containerName )
{
  return Targets_[containerName];
}



Larvicide::Larvicide(void)
: ScheduledControl( Control::Larvicide, "", false, NULL )
{}



Larvicide::Larvicide( std::string name, bool enabled, Schedule * schedule, int lagPeriod, double initMortality,
                      int maxEffectPeriod, int declineEffectPeriod, bool effectLostWhenDry )
: ScheduledControl( Control::Larvicide, name, enabled, schedule ),
  LagPeriod_(lagPeriod),
  InitialMortality_(initMortality),
  MaxEffectPeriod_(maxEffectPeriod),
  DeclineEffectPeriod_(declineEffectPeriod),
  EffectLostWhenDry_(effectLostWhenDry)
{}



Larvicide::~Larvicide(void)
{}


void
Larvicide::CalculateMortality(void)
{
  // Calculate mortality for each treatment period
  int totalEffectPeriod = LagPeriod_ + MaxEffectPeriod_ + DeclineEffectPeriod_;
  Mortality_ = std::vector<double>( totalEffectPeriod, 0.0 );

  for( int i = 0; i < LagPeriod_; ++i ) {
    // no effect yet
    Mortality_[i] = 0.0;
  }
  for( int i = LagPeriod_; i < LagPeriod_ + MaxEffectPeriod_; ++i ) {
    // maximum effect period with some initial mortality
    Mortality_[i] = InitialMortality_;
  }
  for( int i = LagPeriod_ + MaxEffectPeriod_; i < LagPeriod_ + MaxEffectPeriod_ + DeclineEffectPeriod_; ++i ) {
    double slope = InitialMortality_ / (0 - DeclineEffectPeriod_);
    Mortality_[i] = (slope * (i - (MaxEffectPeriod_+LagPeriod_))) + InitialMortality_;    
  }
}



bool
Larvicide::IsTarget( std::string containerName)
{
  std::map<std::string,Larvicide::Parameters*>::iterator it = Targets_.find( containerName );

  if( it != Targets_.end() )
    return true;
  else
    return false;
}



Larvicide::Parameters *
Larvicide::GetTargetParams( std::string containerName )
{
  return Targets_[containerName];
}



std::map<std::string, Larvicide::Parameters*> &
Larvicide::GetTargets(void)
{
  return Targets_;
}



void
Larvicide::AddTarget( std::string containerName, Larvicide::Parameters * params )
{
  Targets_[containerName] = params;
}



std::vector<double> & Larvicide::GetMortality(void)
{
  return Mortality_;
}



int Larvicide::GetLagPeriod(void)
{
  return LagPeriod_;
}



void Larvicide::SetLagPeriod( int lagPeriod )
{
  LagPeriod_ = lagPeriod;
}



double Larvicide::GetInitialMortality(void)
{
  return InitialMortality_;
}



void Larvicide::SetInitialMortality( double initialMortality )
{
  InitialMortality_ = initialMortality;
}



int Larvicide::GetMaxEffectPeriod(void)
{
  return MaxEffectPeriod_;
}



void Larvicide::SetMaxEffectPeriod( int maxEffectPeriod )
{
  MaxEffectPeriod_ = maxEffectPeriod;
}



int Larvicide::GetDeclineEffectPeriod(void)
{  return DeclineEffectPeriod_;
}



void Larvicide::SetDeclineEffectPeriod( int declineEffectPeriod )
{  DeclineEffectPeriod_ = declineEffectPeriod;
}



bool Larvicide::IsEffectLostWhenDry(void)
{
  return EffectLostWhenDry_;
}



void Larvicide::SetEffectLostWhenDry( bool effectLostWhenDry )
{  EffectLostWhenDry_ = effectLostWhenDry;
}



SterileMaleRelease::SterileMaleRelease(void)
: ScheduledControl( Control::SterileMaleRelease, "", false, NULL )
{}



SterileMaleRelease::SterileMaleRelease( std::string name, bool enabled, Schedule * schedule,
                                        double numberReleased, double sterilityRate,
                                        double competitiveness, double ratioMaleToFemaleSurvival )
: ScheduledControl( Control::SterileMaleRelease, name, enabled, schedule ),
  NumberReleased_(numberReleased),
  SterilityRate_(sterilityRate),
  Competitiveness_(competitiveness),
  RatioMaleToFemaleSurvival_(ratioMaleToFemaleSurvival)
{}



SterileMaleRelease::~SterileMaleRelease(void)
{}



double
SterileMaleRelease::GetNumberReleased(void)
{
  return NumberReleased_;
}


void
SterileMaleRelease::SetNumberReleased(double numberReleased)
{
  NumberReleased_ = numberReleased;
}



double
SterileMaleRelease::GetSterilityRate(void)
{
  return SterilityRate_;
}



void
SterileMaleRelease::SetSterilityRate(double sterilityRate)
{
  SterilityRate_ = sterilityRate;
}



double
SterileMaleRelease::GetCompetitiveness(void)
{
  return Competitiveness_;
}



void
SterileMaleRelease::SetCompetitiveness(double competitiveness)
{
  Competitiveness_ = competitiveness;
}



double
SterileMaleRelease::GetRatioMaleToFemaleSurvival(void)
{
  return RatioMaleToFemaleSurvival_;
}



void
SterileMaleRelease::SetRatioMaleToFemaleSurvival(double ratioMaleToFemaleSurvival)
{
  RatioMaleToFemaleSurvival_ = ratioMaleToFemaleSurvival;
}



SpaceSpray::SpaceSpray(void)
: ScheduledControl( Control::SpaceSpray, "", false, NULL )
{}



SpaceSpray::SpaceSpray( std::string name, bool enabled, Schedule * schedule, double outdoorMortality, double indoorMortality )
: ScheduledControl( Control::SpaceSpray, name, enabled, schedule),
  OutdoorMortality_(outdoorMortality),
  IndoorMortality_(indoorMortality)
{}



SpaceSpray::~SpaceSpray(void)
{
}



double SpaceSpray::GetOutdoorMortality(void)
{
  return OutdoorMortality_;
}



void SpaceSpray::SetOutdoorMortality( double outdoorMortality )
{
  OutdoorMortality_ = outdoorMortality;
}



double SpaceSpray::GetIndoorMortality(void)
{
  return IndoorMortality_;
}



void SpaceSpray::SetIndoorMortality( double indoorMortality )
{
  IndoorMortality_ = indoorMortality;
}



ResidualSpray::ResidualSpray(void)
: ScheduledControl( Control::ResidualSpray, "", false, NULL )
{}



ResidualSpray::ResidualSpray( std::string name, bool enabled, Schedule * schedule,
               double initialMortality, int maximumEffectPeriod, int residualEffectPeriod,
               double treatedInteriorProportion, double treatedHousesProportion )
: ScheduledControl( Control::ResidualSpray, name, enabled, schedule),
  InitialMortality_(initialMortality),
  MaximumEffectPeriod_(maximumEffectPeriod),
  ResidualEffectPeriod_(residualEffectPeriod),
  TreatedInteriorProportion_(treatedInteriorProportion),
  TreatedHousesProportion_(treatedHousesProportion)
{}


ResidualSpray::~ResidualSpray(void)
{}



double
ResidualSpray::GetInitialMortality(void)
{
  return InitialMortality_;
}



void
ResidualSpray::SetInitialMortality(double initialMortality)
{
  InitialMortality_ = initialMortality;
}


int
ResidualSpray::GetMaximumEffectPeriod(void)
{
  return MaximumEffectPeriod_;
}



void
ResidualSpray::SetMaximumEffectPeriod(int maximumEffectPeriod)
{
  MaximumEffectPeriod_ = maximumEffectPeriod;
}



int
ResidualSpray::GetResidualEffectPeriod(void)
{
  return ResidualEffectPeriod_;
}



void
ResidualSpray::SetResidualEffectPeriod(int residualEffectPeriod)
{
  ResidualEffectPeriod_ = residualEffectPeriod;
}



double
ResidualSpray::GetTreatedInteriorProportion(void)
{
  return TreatedInteriorProportion_;
}



void
ResidualSpray::SetTreatedInteriorProportion(double treatedInteriorProportion)
{
  TreatedInteriorProportion_ = treatedInteriorProportion;
}



double
ResidualSpray::GetTreatedHousesProportion(void)
{
  return TreatedHousesProportion_;
}



void
ResidualSpray::SetTreatedHousesProportion(double treatedHousesProportion)
{
  TreatedHousesProportion_ = treatedHousesProportion;
}



void
ResidualSpray::CalculateMortality(void)
{
  Schedule::ScheduledDates treatmentDates = Schedule_->GetScheduledDates();
  if( treatmentDates.size() == 0 ) {
    // no treatment dates scheduled, no mortality to calculate
    return;
  }

  date_period lagPeriod = date_period(date(),date());
  date_period maxPeriod = date_period(date(),date());
  date_period decPeriod = date_period(date(),date());

  // keep iterating past StopDate to allow for calculation of residual mortality
  int totalDays = MaximumEffectPeriod_ + ResidualEffectPeriod_;
  for( day_iterator itDate = day_iterator(Schedule_->GetStartDate()); itDate <= (Schedule_->GetStopDate() + days(totalDays)); ++itDate ) {

    if( Schedule_->IsDateScheduled(*itDate) ) {
      // begin a new treatment on this date
      date maxEffectEnds = *itDate + days(MaximumEffectPeriod_);
      date decEffectEnds = *itDate + days(MaximumEffectPeriod_) + days(ResidualEffectPeriod_);

      maxPeriod = date_period( *itDate, maxEffectEnds );
      decPeriod = date_period( maxEffectEnds, decEffectEnds );
    }

    // determine mortality based on which period contains current date
    if( lagPeriod.contains(*itDate) ) {
      Mortality_[*itDate] = 0.0;
    }
    else if( maxPeriod.contains(*itDate) ) {
      Mortality_[*itDate] = InitialMortality_;
    }
    else if( decPeriod.contains(*itDate) ) {
      // linear decline using point-slope form
      double slope = (0 - InitialMortality_) / ( decPeriod.length().days() );
      Mortality_[*itDate] = (slope * ((*itDate - decPeriod.begin()).days())) + InitialMortality_;
    }
  }
}



double
ResidualSpray::GetSurvival( boost::gregorian::date d )
{
  if( Mortality_.find(d) == Mortality_.end() ) {
    // no effect if not scheduled
    return 1.0;
  }
  else {
    double survival = 1.0 - Mortality_[d];
    return survival;
  }
}
