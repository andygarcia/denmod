#include "StdAfx.h"
#include "InfectionIntroduction.h"

using namespace gui;



SerotypeIntroduction::SerotypeIntroduction(void)
: Humans_(0),
  Mosquitoes_(0),
  Schedule_(gcnew SingleSchedule())
{}



SerotypeIntroduction::~SerotypeIntroduction(void)
{}



input::SerotypeIntroduction *
SerotypeIntroduction::GetSimObject(void)
{
  input::SerotypeIntroduction * si = new input::SerotypeIntroduction();

  si->Humans_ = this->Humans_;
  si->Mosquitoes_ = this->Mosquitoes_;
  si->Schedule_ = this->Schedule_->GetSimObject();

  return si;
}


System::String^
SerotypeIntroduction::ToString(void)
{
  System::Text::StringBuilder ^ sb = gcnew System::Text::StringBuilder();
  sb->Append( System::Enum::GetName(Serotypes::typeid, this->Serotype_) );
  sb->AppendFormat( "Humans = {0}, Mosquitoes = {1}, Schedule = {2}", Humans_, Mosquitoes_, Schedule_ );
  sb->AppendLine();
  return sb->ToString();
}


InfectionIntroductionParameters::InfectionIntroductionParameters(void)
: Dengue1_(gcnew SerotypeIntroduction()),
  Dengue2_(gcnew SerotypeIntroduction()),
  Dengue3_(gcnew SerotypeIntroduction()),
  Dengue4_(gcnew SerotypeIntroduction())
{}



InfectionIntroductionParameters::~InfectionIntroductionParameters(void)
{}



input::InfectionIntroduction *
InfectionIntroductionParameters::GetSimObject(void)
{
  input::InfectionIntroduction * ii = new input::InfectionIntroduction();

  ii->Dengue1_ = this->Dengue1_->GetSimObject();
  ii->Dengue2_ = this->Dengue2_->GetSimObject();
  ii->Dengue3_ = this->Dengue3_->GetSimObject();
  ii->Dengue4_ = this->Dengue4_->GetSimObject();

  return ii;
}



System::String^
InfectionIntroductionParameters::ToString(void)
{
  System::Text::StringBuilder ^ sb = gcnew System::Text::StringBuilder();
  sb->Append( Dengue1_->ToString() );
  sb->Append( Dengue2_->ToString() );
  sb->Append( Dengue3_->ToString() );
  sb->Append( Dengue4_->ToString() );
  return sb->ToString();
}
