#include "StdAfx.h"
#include "ResidualSprayForm.h"
#include "SingleSchedulePanel.h"
#include "WeeklySchedulePanel.h"
#include "MonthlySchedulePanel.h"
#include "YearlySchedulePanel.h"
#include "PeriodicSchedulePanel.h"

using namespace gui;



ResidualSprayForm::ResidualSprayForm( ResidualSpray ^ rs, BindingSource ^ locationBinding )
: LocationBinding(locationBinding),
  ActiveLocation((gui::Location^)locationBinding->DataSource),
  CurrentSchedulePanel(nullptr)
{
	InitializeComponent();

  ResidualSpray_ = rs;
  ResidualSpray_->BeginEdit();

  // populate and select correct schedule types
  cboxSchedule->Items->Add( "Single" );
  cboxSchedule->Items->Add( "Weekly" );
  cboxSchedule->Items->Add( "Monthly" );
  cboxSchedule->Items->Add( "Yearly" );
  cboxSchedule->Items->Add( "Periodic" );
  cboxSchedule->SelectedItem = Schedule::GetShortNameFromType( ResidualSpray_->Schedule );
}



ResidualSprayForm::~ResidualSprayForm()
{
  if( components ) {
    delete components;
  }
}



System::Void
ResidualSprayForm::OnLoad(System::Object^  sender, System::EventArgs^  e)
{
  this->tboxName->DataBindings->Add( "Text", ResidualSpray_, "Name" );
  this->Text = ResidualSpray_->Name;

  this->numInitialMortality->DataBindings->Add( "Text", ResidualSpray_, "InitialMortality" );
  this->numMaximumEffectPeriod->DataBindings->Add( "Text", ResidualSpray_, "MaximumEffectPeriod" );
  this->numResidualEffectPeriod->DataBindings->Add( "Text", ResidualSpray_, "ResidualEffectPeriod" );
  this->numTreatedInteriorProportion->DataBindings->Add( "Text", ResidualSpray_, "TreatedInteriorProportion" );
  this->numTreatedHousesProportion->DataBindings->Add( "Text", ResidualSpray_, "TreatedHousesProportion" );
  this->numOutdoorProportion->DataBindings->Add( "Text", LocationBinding, "Biology.Adult.ProportionOfAdultsRestingOutdoors" );

  // select current schedule
  SetSchedulePanel();
}



System::Void
ResidualSprayForm::OnScheduleChange( System::Object ^ sender, System::EventArgs ^ e )
{
  // create new schedule
  Type ^ newScheduleType = Schedule::GetTypeFromShortName( (String^)cboxSchedule->SelectedItem );
  Reflection::ConstructorInfo ^ sci = newScheduleType->GetConstructor( gcnew array<Type^>(2){DateTime::typeid, DateTime::typeid} );
  ResidualSpray_->Schedule = (Schedule^) sci->Invoke( gcnew array<Object^>(2){ActiveLocation->Weather->MinDate, ActiveLocation->Weather->MaxDate} );
  SetSchedulePanel();
}



void
ResidualSprayForm::SetSchedulePanel(void)
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

  Type ^ newFormType = ScheduleTypeToFormType[ResidualSpray_->Schedule->GetType()];
  Reflection::ConstructorInfo ^ fci = newFormType->GetConstructor( gcnew array<Type^>(2){ResidualSpray_->Schedule->GetType(), BindingSource::typeid} );
  CurrentSchedulePanel = (UserControl^) fci->Invoke( gcnew array<Object^>(2){ResidualSpray_->Schedule, LocationBinding} );

  CurrentSchedulePanel->Location = Point( cboxSchedule->Location.X,
                                          cboxSchedule->Location.Y + cboxSchedule->Height + cboxSchedule->Margin.Bottom + CurrentSchedulePanel->Margin.Top );
  //CurrentSchedulePanel->TabIndex = cboxSchedule->TabIndex + 1;
  CurrentSchedulePanel->Size.Width = tboxName->Size.Width;

  this->Controls->Add( CurrentSchedulePanel );
}



System::Void
ResidualSprayForm::OnOk( System::Object ^ sender, System::EventArgs ^ e )
{
  ResidualSpray_->EndEdit();
}



System::Void
ResidualSprayForm::OnCancel( System::Object ^ sender, System::EventArgs ^ e )
{
  ResidualSpray_->CancelEdit();
}

