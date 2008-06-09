#include "StdAfx.h"
#include "SpaceSprayForm.h"
#include "SingleSchedulePanel.h"
#include "WeeklySchedulePanel.h"
#include "MonthlySchedulePanel.h"
#include "YearlySchedulePanel.h"
#include "PeriodicSchedulePanel.h"

using namespace gui;



SpaceSprayForm::SpaceSprayForm( SpaceSpray ^ ss, BindingSource ^ locationBinding )
: LocationBinding(locationBinding),
  ActiveLocation((gui::Location^)locationBinding->DataSource),
  CurrentSchedulePanel(nullptr)
{
	InitializeComponent();

  SpaceSpray_ = ss;
  SpaceSpray_->BeginEdit();

  // populate and select correct schedule types
  cboxSchedule->Items->Add( "Single" );
  cboxSchedule->Items->Add( "Weekly" );
  cboxSchedule->Items->Add( "Monthly" );
  cboxSchedule->Items->Add( "Yearly" );
  cboxSchedule->Items->Add( "Periodic" );
  cboxSchedule->SelectedItem = Schedule::GetShortNameFromType( SpaceSpray_->Schedule );
}


SpaceSprayForm::~SpaceSprayForm()
{
  if( components ) {
    delete components;
  }
}



System::Void
SpaceSprayForm::OnLoad(System::Object^  sender, System::EventArgs^  e)
{
  this->tboxName->DataBindings->Add( "Text", SpaceSpray_, "Name" );
  this->Text = SpaceSpray_->Name;

  this->numOutdoorMortality->DataBindings->Add( "Text", SpaceSpray_, "OutdoorMortality" );
  this->numIndoorMortality->DataBindings->Add( "Text", SpaceSpray_, "IndoorMortality" );
  this->numOutdoorProportion->DataBindings->Add( "Text", LocationBinding, "Biology.Adult.ProportionOfAdultsRestingOutdoors" );
  // select current schedule
  SetSchedulePanel();
}



System::Void
SpaceSprayForm::OnScheduleChange( System::Object ^ sender, System::EventArgs ^ e )
{
  // create new schedule
  Type ^ newScheduleType = Schedule::GetTypeFromShortName( (String^)cboxSchedule->SelectedItem );
  Reflection::ConstructorInfo ^ sci = newScheduleType->GetConstructor( gcnew array<Type^>(2){DateTime::typeid, DateTime::typeid} );
  SpaceSpray_->Schedule = (Schedule^) sci->Invoke( gcnew array<Object^>(2){ActiveLocation->Weather->MinDate, ActiveLocation->Weather->MaxDate} );
  SetSchedulePanel();
}



void
SpaceSprayForm::SetSchedulePanel(void)
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

  Type ^ newFormType = ScheduleTypeToFormType[SpaceSpray_->Schedule->GetType()];
  Reflection::ConstructorInfo ^ fci = newFormType->GetConstructor( gcnew array<Type^>(2){SpaceSpray_->Schedule->GetType(), BindingSource::typeid} );
  CurrentSchedulePanel = (UserControl^) fci->Invoke( gcnew array<Object^>(2){SpaceSpray_->Schedule, LocationBinding} );

  CurrentSchedulePanel->Location = Point( cboxSchedule->Location.X,
                                          cboxSchedule->Location.Y + cboxSchedule->Height + cboxSchedule->Margin.Bottom + CurrentSchedulePanel->Margin.Top );
  //CurrentSchedulePanel->TabIndex = cboxSchedule->TabIndex + 1;
  CurrentSchedulePanel->Size.Width = tboxName->Size.Width;

  this->Controls->Add( CurrentSchedulePanel );
}



System::Void
SpaceSprayForm::OnOk( System::Object ^ sender, System::EventArgs ^ e )
{
  SpaceSpray_->EndEdit();
}



System::Void
SpaceSprayForm::OnCancel( System::Object ^ sender, System::EventArgs ^ e )
{
  SpaceSpray_->CancelEdit();
}
