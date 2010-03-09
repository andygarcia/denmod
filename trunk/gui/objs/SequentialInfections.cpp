#include "StdAfx.h"
#include "SequentialInfections.h"
#include "Util.h"

using namespace gui;



SequentialInfection::SequentialInfection(void)
{}



SequentialInfection::SequentialInfection( System::String ^ sequence )
: SequenceOfInfection_(sequence)
{}



SequentialInfection::~SequentialInfection(void)
{}



input::SequentialInfection *
SequentialInfection::GetSimObject(void)
{
  array<System::String^> ^ toks;
  toks = SequenceOfInfection_->Split('-');
  System::String ^ firstInfectionType = toks[0];
  System::String ^ secondInfectionType = toks[1];

  input::SequentialInfection * si = new input::SequentialInfection( toss(firstInfectionType), toss(secondInfectionType) );

  si->MinMonths_ = this->MinMonths_;
  si->MaxMonths_ = this->MaxMonths_;
  si->Probability_ = this->Probability_;
  si->AtRiskCutoffAge_ = this->AtRiskCutoffAge_;
  si->Mortality_ = this->Mortality_;

  return si;
}



SequentialInfectionParameters::SequentialInfectionParameters(void)
: SequentialInfections_(gcnew BindingList<SequentialInfection^>())
{
  SequentialInfections_->ListChanged += gcnew System::ComponentModel::ListChangedEventHandler(this, &SequentialInfectionParameters::OnListChangedSequentialInfections);

  SequentialInfections_->Add( gcnew SequentialInfection( "2-1" ) );
  SequentialInfections_->Add( gcnew SequentialInfection( "3-1" ) );
  SequentialInfections_->Add( gcnew SequentialInfection( "4-1" ) );

  SequentialInfections_->Add( gcnew SequentialInfection( "1-2" ) );
  SequentialInfections_->Add( gcnew SequentialInfection( "3-2" ) );
  SequentialInfections_->Add( gcnew SequentialInfection( "4-2" ) );

  SequentialInfections_->Add( gcnew SequentialInfection( "1-3" ) );
  SequentialInfections_->Add( gcnew SequentialInfection( "2-3" ) );
  SequentialInfections_->Add( gcnew SequentialInfection( "4-3" ) );

  SequentialInfections_->Add( gcnew SequentialInfection( "1-4" ) );
  SequentialInfections_->Add( gcnew SequentialInfection( "2-4" ) );
  SequentialInfections_->Add( gcnew SequentialInfection( "3-4" ) );

  SequentialInfections_->Add( gcnew SequentialInfection( "MAEA-1" ) );
  SequentialInfections_->Add( gcnew SequentialInfection( "MAEA-2" ) );
  SequentialInfections_->Add( gcnew SequentialInfection( "MAEA-3" ) );
  SequentialInfections_->Add( gcnew SequentialInfection( "MAEA-4" ) );
}



SequentialInfectionParameters::~SequentialInfectionParameters(void)
{}



void
SequentialInfectionParameters::OnListChangedSequentialInfections( Object ^ sender, System::ComponentModel::ListChangedEventArgs ^ e )
{
  BindingList<SequentialInfection^>^ bl = (BindingList<SequentialInfection^>^) sender;
  if( e->ListChangedType == System::ComponentModel::ListChangedType::ItemAdded ) {
    if( bl->Count == 17 ) {
      SequentialInfection ^ si = bl[16];
      bl->Clear();
      bl->Add( si );
    }
  }
}



input::SequentialInfections *
SequentialInfectionParameters::GetSimObject(void)
{
  input::SequentialInfections::SequentialInfectionCollection sic;

  for each( SequentialInfection ^ si in SequentialInfections_ ) {
    sic.push_back( si->GetSimObject() );
  }

  input::SequentialInfections * si = new input::SequentialInfections( sic );

  return si;
}