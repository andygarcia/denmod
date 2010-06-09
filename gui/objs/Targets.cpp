#include "StdAfx.h"
#include "Targets.h"

using namespace gui;
using namespace System;



Target::Target(void)
{}



Target::Target( const Target ^ t )
{
  this->Name_ = t->Name_;
}



Target::Target( System::String ^ name )
: Name_(name)
{}



Target::~Target(void)
{}



SourceReductionTarget::SourceReductionTarget(void)
{}



SourceReductionTarget::SourceReductionTarget( System::String ^ name )
: Target(name),
  RateOfReduction_(0.0)
{}



SourceReductionTarget::SourceReductionTarget( System::String ^ name, double rateOfReduction )
: Target(name),
  RateOfReduction_(rateOfReduction)
{}



SourceReductionTarget::SourceReductionTarget( const SourceReductionTarget^ srt )
{
  this->Name_ = srt->Name_;
  this->RateOfReduction = srt->RateOfReduction_;
}



SourceReductionTarget::~SourceReductionTarget(void)
{}



OvipositionExclusionTarget::OvipositionExclusionTarget(void)
{}



OvipositionExclusionTarget::OvipositionExclusionTarget( System::String ^ name )
: Target(name),
  RateOfExclusion_(0.0),
  RateOfRecovery_(0.0)
{}



OvipositionExclusionTarget::OvipositionExclusionTarget( System::String ^ name, double rateOfExclusion, double rateOfRecovery )
: Target(name),
  RateOfExclusion_(rateOfExclusion),
  RateOfRecovery_(rateOfRecovery)
{}



OvipositionExclusionTarget::OvipositionExclusionTarget( const OvipositionExclusionTarget ^ oet )
{
  this->Name_ = oet->Name_;
  this->RateOfExclusion_ = oet->RateOfExclusion_;
  this->RateOfRecovery_ = oet->RateOfRecovery_;
}



OvipositionExclusionTarget::~OvipositionExclusionTarget(void)
{}



EggDestructionTarget::EggDestructionTarget(void)
{}



EggDestructionTarget::EggDestructionTarget( System::String ^ name )
: Target(name),
  RateOfDestruction_(0.0)
{}



EggDestructionTarget::EggDestructionTarget( System::String ^ name, double rateOfDestruction )
: Target(name),
  RateOfDestruction_(rateOfDestruction)
{}



EggDestructionTarget::EggDestructionTarget( const EggDestructionTarget ^ edt )
{
  this->Name_ = edt->Name_;
  this->RateOfDestruction = edt->RateOfDestruction_;
}



EggDestructionTarget::~EggDestructionTarget(void)
{}



LarvicideTarget::LarvicideTarget(void)
{}



LarvicideTarget::LarvicideTarget( System::String ^ name )
: Target(name),
  RateOfTreatment_(0.0)
{}



LarvicideTarget::LarvicideTarget( System::String ^ name, double rateOfTreatment )
: Target(name),
  RateOfTreatment_(rateOfTreatment)
{}



LarvicideTarget::LarvicideTarget( const LarvicideTarget ^ lt )
{
  this->Name_ = lt->Name_;
  this->RateOfTreatment = lt->RateOfTreatment_;
}



LarvicideTarget::~LarvicideTarget(void)
{}
