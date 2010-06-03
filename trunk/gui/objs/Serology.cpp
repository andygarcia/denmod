#include "StdAfx.h"
#include "Serology.h"

using namespace gui;



SerologyClass::SerologyClass(void)
{}



SerologyClass::SerologyClass( int rank )
: Rank_(rank)
{}


SerologyClass::~SerologyClass(void)
{}



input::SerologyClass *
SerologyClass::GetSimObject(void)
{
  input::SerologyClass * sc = new input::SerologyClass();

  sc->Rank_ = this->Rank_;
  sc->Dengue1_ = this->Dengue1_;
  sc->Dengue2_ = this->Dengue2_;
  sc->Dengue3_ = this->Dengue3_;
  sc->Dengue4_ = this->Dengue4_;

  return sc;
}
  
  
SerologyParameters::SerologyParameters(void)
: SeroClasses_(gcnew BindingList<SerologyClass^>())
{
  SeroClasses_->ListChanged += gcnew System::ComponentModel::ListChangedEventHandler(this, &SerologyParameters::OnListChangedSeroClasses);
  if( SeroClasses_->Count == 0 ) {
    // no xml serialization yet, create the default list
    for( int i = 1; i <= 18; ++i ) {
      SerologyClass ^ dc = gcnew SerologyClass(i);
      SeroClasses_->Add( dc );
    }
  }

  // get default values for duration periods
  input::Serology defVals;
  this->MANADuration = defVals.ManaDuration_;
  this->MAEADuration = defVals.MaeaDuration_;
  this->HeterologousImmunityDuration = defVals.HeterologousImmunityDuration_;
}



SerologyParameters::~SerologyParameters(void)
{}



void
SerologyParameters::OnListChangedSeroClasses( Object ^ sender, System::ComponentModel::ListChangedEventArgs ^ e )
{
  BindingList<SerologyClass^>^ bl = (BindingList<SerologyClass^>^) sender;
  if( e->ListChangedType == System::ComponentModel::ListChangedType::ItemAdded ) {
    if( bl->Count == 19 ) {
      SerologyClass ^ dc = bl[18];
      bl->Clear();
      bl->Add( dc );
    }
  }
}


input::Serology *
SerologyParameters::GetSimObject(void)
{
  input::Serology * s = new input::Serology();

  for each( SerologyClass ^ sc in SeroClasses_ ) {
    s->SerologyData_.push_back( *(sc->GetSimObject()) );
  }
  s->ManaDuration_ = this->MANADuration_;
  s->MaeaDuration_ = this->MAEADuration_;
  s->HeterologousImmunityDuration_ = this->HeterologousImmunityDuration_;

  return s;
}



void
SerologyParameters::AutoFillSerology( double proportion )
{
  for each( SerologyClass ^ sc in SeroClasses_ ) {
    sc->Dengue1 = proportion;
    sc->Dengue2 = proportion;
    sc->Dengue3 = proportion;
    sc->Dengue4 = proportion;
  }
}
