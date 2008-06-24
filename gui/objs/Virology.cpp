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
{
  input::VirusDevelopment defVals;

  this->RO25_ = defVals.RO25;
  this->DHA_ = defVals.DHA;
  this->DHH_ = defVals.DHH;
  this->THALF_ = defVals.THALF;
}



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
{
  input::HumanToMosquitoInfection defVals;
  this->LowTiterSetPoint_ = defVals.LowTiterSetPoint_;
  this->LowTiterInfection_ = defVals.LowTiterInfection_;
  this->HighTiterSetPoint_ = defVals.HighTiterSetPoint_;
  this->HighTiterInfection_ = defVals.HighTiterInfection_;
}



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
{
  input::EipTiterModification defVals;

  this->LowSetPoint_ = defVals.LowSetPoint_;
  this->LowFactor_ = defVals.LowFactor_;
  this->HighSetPoint_ = defVals.HighSetPoint_;
  this->HighFactor_ = defVals.HighFactor_;
}



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
  input::Virology defVals;

  Dengue1_->Viremia = defVals.Dengue1_.Viremia_;
  Dengue1_->IncubationDuration = defVals.Dengue1_.IncubationDuration_;
  Dengue1_->ViremicDuration = defVals.Dengue1_.ViremicDuration_;

  Dengue2_->Viremia = defVals.Dengue2_.Viremia_;
  Dengue2_->IncubationDuration = defVals.Dengue2_.IncubationDuration_;
  Dengue2_->ViremicDuration = defVals.Dengue2_.ViremicDuration_;

  Dengue3_->Viremia = defVals.Dengue3_.Viremia_;
  Dengue3_->IncubationDuration = defVals.Dengue3_.IncubationDuration_;
  Dengue3_->ViremicDuration = defVals.Dengue3_.ViremicDuration_;

  Dengue4_->Viremia = defVals.Dengue4_.Viremia_;
  Dengue4_->IncubationDuration = defVals.Dengue4_.IncubationDuration_;
  Dengue4_->ViremicDuration = defVals.Dengue4_.ViremicDuration_;

  this->MosquitoToHumanNominalProbabilityOfInfection_ = defVals.MosquitoToHumanNominalProbabilityOfInfection_;
  this->MosquitoCountForStochasticity_ = defVals.MosquitoCountForStochasticity;
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
