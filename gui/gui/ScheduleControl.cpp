#include "StdAfx.h"
#include "ScheduleControl.h"
#include "ResidualSprayForm.h"
#include "SingleSchedulePanel.h"
#include "WeeklySchedulePanel.h"
#include "MonthlySchedulePanel.h"
#include "YearlySchedulePanel.h"
#include "PeriodicSchedulePanel.h"

using namespace gui;


ScheduleControl::ScheduleControl( BindingSource ^ locationBinding, String ^ scheduleBindingSite )
: LocationBinding_(locationBinding),
  ScheduleBindingSite_(scheduleBindingSite)
{
	InitializeComponent();

  // populate and select correct schedule types
  cboxSchedule->Items->Add( "Single" );
  cboxSchedule->Items->Add( "Weekly" );
  cboxSchedule->Items->Add( "Monthly" );
  cboxSchedule->Items->Add( "Yearly" );
  cboxSchedule->Items->Add( "Periodic" );
}



ScheduleControl::~ScheduleControl()
{
  if( components ) {
		delete components;
	}
}



System::Void
ScheduleControl::OnLoad( System::Object ^ sender, System::EventArgs ^ e )
{
  DataBindings->Add( "CurrentSchedule", LocationBinding_, ScheduleBindingSite_, false, DataSourceUpdateMode::OnPropertyChanged );  
}



System::Void
ScheduleControl::OnScheduleChange( System::Object ^ sender, System::EventArgs ^ e )
{
  // create new schedule
  Type ^ newScheduleType = Schedule::GetTypeFromShortName( (String^)cboxSchedule->SelectedItem );
  Reflection::ConstructorInfo ^ sci = newScheduleType->GetConstructor( gcnew array<Type^>(2){DateTime::typeid, DateTime::typeid} );
  gui::Location ^ location = (gui::Location^) LocationBinding_->DataSource;
  CurrentSchedule = (Schedule^) sci->Invoke( gcnew array<Object^>(2){location->Weather->MinDate, location->Weather->MaxDate} );
}



void
ScheduleControl::SetSchedulePanel(void)
{
  // remove previous panel
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

  // create new panel
  Type ^ newFormType = ScheduleTypeToFormType[CurrentSchedule->GetType()];
  Reflection::ConstructorInfo ^ fci = newFormType->GetConstructor( gcnew array<Type^>(2){CurrentSchedule->GetType(), BindingSource::typeid} );
  CurrentSchedulePanel = (UserControl^) fci->Invoke( gcnew array<Object^>(2){CurrentSchedule, LocationBinding_} );

  CurrentSchedulePanel->Location = Point( cboxSchedule->Location.X,
                                          cboxSchedule->Location.Y + cboxSchedule->Height + cboxSchedule->Margin.Bottom + CurrentSchedulePanel->Margin.Top );
  this->Controls->Add( CurrentSchedulePanel );

  // update drop down
  cboxSchedule->SelectedItem = Schedule::GetShortNameFromType( CurrentSchedule );
}



Schedule ^
ScheduleControl::CurrentSchedule::get(void)
{
  return CurrentSchedule_;
}



void
ScheduleControl::CurrentSchedule::set( Schedule ^ schedule )
{
  if( schedule != CurrentSchedule_ ) {
    CurrentSchedule_ = schedule;
    SetSchedulePanel();
    NotifyPropertyChanged("CurrentSchedule");
  }
}
