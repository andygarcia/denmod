#include "StdAfx.h"
#include "Virology.h"

using namespace gui;



SerotypeParameters::SerotypeParameters(void)
{}



SerotypeParameters::SerotypeParameters( int serotype )
: Serotype_(serotype)
{}



SerotypeParameters::~SerotypeParameters(void)
{}



input::VirusSerotype *
SerotypeParameters::GetSimObject(void)
{
  input::VirusSerotype * vs = new input::VirusSerotype();

  vs->Serotype_ = this->Serotype_;
  vs->Viremia_ = this->Viremia_;
  vs->IncubationDuration_ = this->IncubationDuration_;
  vs->ViremicDuration_ = this->ViremicDuration_;

  return vs;
}



EnzymeKineticDevelopmentParameters::EnzymeKineticDevelopmentParameters(void)
{}



EnzymeKineticDevelopmentParameters::~EnzymeKineticDevelopmentParameters(void)
{}



input::VirusDevelopment * 
EnzymeKineticDevelopmentParameters::GetSimObject(void)
{
  input::VirusDevelopment * vd = new input::VirusDevelopment();

  vd->RO25 = this->RO25_;
  vd->DHA = this->DHA_;
  vd->DHH = this->DHH_;
  vd->THALF = this->THALF_;

  return vd;
}


HumanToMosquitoInfectionParameters::HumanToMosquitoInfectionParameters(void)
{}



HumanToMosquitoInfectionParameters::~HumanToMosquitoInfectionParameters(void)
{}



input::HumanToMosquitoInfection *
HumanToMosquitoInfectionParameters::GetSimObject(void)
{
  input::HumanToMosquitoInfection * htmi = new input::HumanToMosquitoInfection();

  htmi->LowTiterSetPoint_ = this->LowTiterSetPoint_;
  htmi->LowTiterInfection_ = this->LowTiterInfection_;
  htmi->HighTiterSetPoint_ = this->HighTiterSetPoint_;
  htmi->HighTiterInfection_ = this->HighTiterInfection_;

  return htmi;
}



EIPTiterModificationParameters::EIPTiterModificationParameters(void)
{}



EIPTiterModificationParameters::~EIPTiterModificationParameters(void)
{}



input::EipTiterModification *
EIPTiterModificationParameters::GetSimObject(void)
{
  input::EipTiterModification * etm = new input::EipTiterModification();

  etm->LowSetPoint_ = this->LowSetPoint_;
  etm->LowFactor_ = this->LowFactor_;
  etm->HighSetPoint_ = this->HighSetPoint_;
  etm->HighFactor_ = this->HighFactor_;

  return etm;
}



EIPParameters::EIPParameters(void)
: Development_(gcnew EnzymeKineticDevelopmentParameters()),
  TiterModification_(gcnew EIPTiterModificationParameters())
{}



EIPParameters::~EIPParameters(void)
{}



input::Eip *
EIPParameters::GetSimObject(void)
{
  input::Eip * e = new input::Eip();

  e->Development_ = *(this->Development_->GetSimObject());
  e->EipTiterModification_ = *(this->TiterModification_->GetSimObject());

  return e;
}



VirologyParameters::VirologyParameters(void)
: Dengue1_(gcnew SerotypeParameters(1)),
  Dengue2_(gcnew SerotypeParameters(2)),
  Dengue3_(gcnew SerotypeParameters(3)),
  Dengue4_(gcnew SerotypeParameters(4)),
  HumanToMosquitoInfection_(gcnew HumanToMosquitoInfectionParameters()),
  EIP_(gcnew EIPParameters())
{
}



VirologyParameters::~VirologyParameters(void)
{}



input::Virology * 
VirologyParameters::GetSimObject(void)
{
  input::Virology * v = new input::Virology();

  v->Dengue1_ = *(this->Dengue1_->GetSimObject());
  v->Dengue2_ = *(this->Dengue2_->GetSimObject());
  v->Dengue3_ = *(this->Dengue3_->GetSimObject());
  v->Dengue4_ = *(this->Dengue4_->GetSimObject());
  v->Eip_ = *(this->EIP_->GetSimObject());
  v->HumanToMosquitoInfection_ = *(this->HumanToMosquitoInfection_->GetSimObject());
  v->MosquitoToHumanNominalProbabilityOfInfection_ = this->MosquitoToHumanNominalProbabilityOfInfection_;
  v->MosquitoCountForStochasticity = this->MosquitoCountForStochasticity_;

  return v;
}
