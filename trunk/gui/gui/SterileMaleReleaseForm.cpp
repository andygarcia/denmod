#include "StdAfx.h"
#include "SterileMaleReleaseForm.h"
#include "SingleSchedulePanel.h"
#include "WeeklySchedulePanel.h"
#include "MonthlySchedulePanel.h"
#include "YearlySchedulePanel.h"
#include "PeriodicSchedulePanel.h"

using namespace gui;



SterileMaleReleaseForm::SterileMaleReleaseForm( SterileMaleRelease ^ sm, BindingSource ^ locationBinding )
: LocationBinding(locationBinding),
  ActiveLocation((gui::Location^)locationBinding->DataSource),
  CurrentSchedulePanel(nullptr)
{
	InitializeComponent();

  SterileMaleRelease_ = sm;
  SterileMaleRelease_->BeginEdit();

  // populate and select correct schedule types
  cboxSchedule->Items->Add( "Single" );
  cboxSchedule->Items->Add( "Weekly" );
  cboxSchedule->Items->Add( "Monthly" );
  cboxSchedule->Items->Add( "Yearly" );
  cboxSchedule->Items->Add( "Periodic" );
  cboxSchedule->SelectedItem = Schedule::GetShortNameFromType( SterileMaleRelease_->Schedule );
}



SterileMaleReleaseForm::~SterileMaleReleaseForm()
{
  if( components ) {
    delete components;
  }
}


System::Void
SterileMaleReleaseForm::OnLoad(System::Object^  sender, System::EventArgs^  e)
{
  this->tboxName->DataBindings->Add( "Text", SterileMaleRelease_, "Name" );
  this->Text = SterileMaleRelease_->Name;

  this->numNumberReleased->DataBindings->Add( "Text", SterileMaleRelease_, "NumberReleased" );
  this->numSterilityRate->DataBindings->Add( "Text", SterileMaleRelease_, "SterilityRate" );
  this->numMaleToFemaleSurvivalRatio->DataBindings->Add( "Text", SterileMaleRelease_, "RatioMaleToFemaleSurvival" );

  // select current schedule
  SetSchedulePanel();
}



System::Void
SterileMaleReleaseForm::OnScheduleChange( System::Object ^ sender, System::EventArgs ^ e )
{
  // create new schedule
  Type ^ newScheduleType = Schedule::GetTypeFromShortName( (String^)cboxSchedule->SelectedItem );
  Reflection::ConstructorInfo ^ sci = newScheduleType->GetConstructor( gcnew array<Type^>(2){DateTime::typeid, DateTime::typeid} );
  SterileMaleRelease_->Schedule = (Schedule^) sci->Invoke( gcnew array<Object^>(2){ActiveLocation->Weather->MinDate, ActiveLocation->Weather->MaxDate} );
  SetSchedulePanel();
}



void
SterileMaleReleaseForm::SetSchedulePanel(void)
{
  if( CurrentSchedulePanel != nullptr ) {
    this->Controls->Remove( CurrentSchedulePanel );
    delete CurrentSchedulePanel;
    CurrentSchedulePanel = nullptr;
  }

  Collections::Generic::Dictionary<Type^,Type^> ^ ScheduleTypeToFormType = gcnew Collections::Generic::Dictionary<Type^,Type^>();
  ScheduleTypeToFormType->Add( SingleSchedule::typeid, SingleSchedulePanel::typeid );
  ScheduleTypeToFormType->Add( WeeklySchedule::typeid, WeeklySchedulePanel::typeid );
  ScheduleTypeToFormType->Add( MonthlySchedule::typeid, MonthlySchedulePanel::typeid );
  ScheduleTypeToFormType->Add( YearlySchedule::typeid, YearlySchedulePanel::typeid );
  ScheduleTypeToFormType->Add( PeriodicSchedule::typeid, PeriodicSchedulePanel::typeid );

  Type ^ newFormType = ScheduleTypeToFormType[SterileMaleRelease_->Schedule->GetType()];
  Reflection::ConstructorInfo ^ fci = newFormType->GetConstructor( gcnew array<Type^>(2){SterileMaleRelease_->Schedule->GetType(), BindingSource::typeid} );
  CurrentSchedulePanel = (UserControl^) fci->Invoke( gcnew array<Object^>(2){SterileMaleRelease_->Schedule, LocationBinding} );

  CurrentSchedulePanel->Location = Point( cboxSchedule->Location.X,
                                          cboxSchedule->Location.Y + cboxSchedule->Height + cboxSchedule->Margin.Bottom + CurrentSchedulePanel->Margin.Top );
  CurrentSchedulePanel->Size.Width = tboxName->Size.Width;

  gboxSchedule->Controls->Add( CurrentSchedulePanel );
}



System::Void
SterileMaleReleaseForm::OnOk( System::Object ^ sender, System::EventArgs ^ e )
{
  SterileMaleRelease_->EndEdit();
}



System::Void
SterileMaleReleaseForm::OnCancel( System::Object ^ sender, System::EventArgs ^ e )
{
  SterileMaleRelease_->CancelEdit();
}
