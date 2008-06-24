#include "StdAfx.h"
#include "Demographics.h"

using namespace gui;



DemographicClass::DemographicClass(void)
{}



DemographicClass::DemographicClass( int rank )
: Rank_(rank)
{}



input::DemographicClass *
DemographicClass::GetSimObject(void)
{
  input::DemographicClass * dc = new input::DemographicClass();

  dc->Rank = this->Rank_;
  dc->Proportion = this->Proportion_;
  dc->BirthRate = this->BirthRate_;
  dc->DeathRate = this->DeathRate_;

  return dc;
}



DemographicClass::~DemographicClass(void)
{}



DemographicParameters::DemographicParameters(void)
: DemoClasses_(gcnew BindingList<DemographicClass^>())
{
  DemoClasses_->ListChanged += gcnew System::ComponentModel::ListChangedEventHandler(this, &DemographicParameters::OnListChangedDemoClasses);
  if( DemoClasses_->Count == 0 ) {
    // no xml serialization yet, create the default list
    for( int i = 1; i <= 18; ++i ) {
      DemographicClass ^ dc = gcnew DemographicClass(i);
      DemoClasses_->Add( dc );
    }
  }

  input::Demographics defVals;

  this->InitialPopulationSize_ = defVals.InitialPopulationSize;
  this->HumanHostDensity = defVals.HumanHostDensity;
}



DemographicParameters::~DemographicParameters(void)
{}



input::Demographics *
DemographicParameters::GetSimObject(void)
{
  input::Demographics * d = new input::Demographics();

  for each( DemographicClass ^ dc in DemoClasses_ ) {
    d->DemographicData.push_back( *(dc->GetSimObject()) );
  }
  d->InitialPopulationSize = this->InitialPopulationSize_;
  d->HumanHostDensity = this->HumanHostDensity_;

  return d;
}



void
DemographicParameters::OnListChangedDemoClasses( Object ^ sender, System::ComponentModel::ListChangedEventArgs ^ e )
{
  BindingList<DemographicClass^>^ bl = (BindingList<DemographicClass^>^) sender;
  if( e->ListChangedType == System::ComponentModel::ListChangedType::ItemAdded ) {
    DemographicClass ^ dc = bl[e->NewIndex];
    dc->DemographicParameters = this;
    if( bl->Count == 19 ) {
      DemographicClass ^ dc = bl[18];
      bl->Clear();
      bl->Add( dc );
    }
  }
}



void
DemographicParameters::CheckValidProportions( System::Object ^ sender, CustomValidationEventArgs ^ e )
{
  DemographicParameters ^ dp = safe_cast<DemographicParameters^>( e->TargetObjectValue );
  BindingList<DemographicClass^> ^ demoClasses = safe_cast<BindingList<DemographicClass^>^>( e->TargetMemberValue );

  // sum proportions
  double sumProportion = 0.0;
  for each( DemographicClass ^ dc in demoClasses ) {
    sumProportion += dc->Proportion;
  }

  // check if equal to 1.0
  if( sumProportion != 1.0 ) {
    e->IsValid = false;
    e->ErrorMessage = "Demographic rank proportion must add to 1.0";
  }
  else {
    e->IsValid = true;
  }
}
