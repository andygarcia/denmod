#include "StdAfx.h"
#include "LarvicideForm.h"
#include "AddTargetContainerForm.h"
#include "SingleSchedulePanel.h"
#include "WeeklySchedulePanel.h"
#include "MonthlySchedulePanel.h"
#include "YearlySchedulePanel.h"
#include "PeriodicSchedulePanel.h"

using namespace gui;



LarvicideForm::LarvicideForm( Larvicide ^ li, BindingSource ^ locationBinding )
: LocationBinding(locationBinding),
  ActiveLocation((gui::Location^)locationBinding->DataSource),
  CurrentSchedulePanel(nullptr)
{
	InitializeComponent();

  Larvicide_ = li;
  Larvicide_->BeginEdit();

  // populate and select correct schedule types
  cboxSchedule->Items->Add( "Single" );
  cboxSchedule->Items->Add( "Weekly" );
  cboxSchedule->Items->Add( "Monthly" );
  cboxSchedule->Items->Add( "Yearly" );
  cboxSchedule->Items->Add( "Periodic" );
  cboxSchedule->SelectedItem = Schedule::GetShortNameFromType( Larvicide_->Schedule );
}



LarvicideForm::~LarvicideForm()
{
	if( components ) {
		delete components;
	}
}



System::Void
LarvicideForm::OnLoad(System::Object^  sender, System::EventArgs^  e)
{
  this->tboxName->DataBindings->Add( "Text", Larvicide_, "Name" );
  this->Text = Larvicide_->Name;

  this->numLagPeriod->DataBindings->Add( "Text", Larvicide_, "LagPeriod" );
  this->numMaxEffectPeriod->DataBindings->Add( "Text", Larvicide_, "MaximumEffectPeriod" );
  this->numDeclineEffectPeriod->DataBindings->Add( "Text", Larvicide_, "DeclineEffectPeriod" );
  this->numInitMortality->DataBindings->Add( "Text", Larvicide_, "InitialMortality" );
  this->chkEffectLost->DataBindings->Add( "Checked", Larvicide_, "EffectLostWhenDry", false, DataSourceUpdateMode::OnPropertyChanged );

  this->dgvTargets->AutoGenerateColumns = false;
  this->dgvTargets->DataSource = Larvicide_->Targets;
  this->dgvTargets->Columns[0]->ReadOnly = true;

  // select current schedule
  SetSchedulePanel();
}



System::Void
LarvicideForm::OnScheduleChange( System::Object ^ sender, System::EventArgs ^ e )
{
  // create new schedule
  Type ^ newScheduleType = Schedule::GetTypeFromShortName( (String^)cboxSchedule->SelectedItem );
  Reflection::ConstructorInfo ^ sci = newScheduleType->GetConstructor( gcnew array<Type^>(2){DateTime::typeid, DateTime::typeid} );
  Larvicide_->Schedule = (Schedule^) sci->Invoke( gcnew array<Object^>(2){ActiveLocation->Weather->MinDate, ActiveLocation->Weather->MaxDate} );
  SetSchedulePanel();
}



void
LarvicideForm::SetSchedulePanel(void)
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

  Type ^ newFormType = ScheduleTypeToFormType[Larvicide_->Schedule->GetType()];
  Reflection::ConstructorInfo ^ fci = newFormType->GetConstructor( gcnew array<Type^>(2){Larvicide_->Schedule->GetType(), BindingSource::typeid} );
  CurrentSchedulePanel = (UserControl^) fci->Invoke( gcnew array<Object^>(2){Larvicide_->Schedule, LocationBinding} );

  CurrentSchedulePanel->Location = Point( cboxSchedule->Location.X,
                                          cboxSchedule->Location.Y + cboxSchedule->Height + cboxSchedule->Margin.Bottom + CurrentSchedulePanel->Margin.Top );
  //CurrentSchedulePanel->TabIndex = cboxSchedule->TabIndex + 1;
  CurrentSchedulePanel->Size.Width = dgvTargets->Size.Width;

  this->Controls->Add( CurrentSchedulePanel );
}



System::Void
LarvicideForm::OnOk( System::Object ^ sender, System::EventArgs ^ e )
{
  Larvicide_->EndEdit();
}



System::Void
LarvicideForm::OnCancel( System::Object ^ sender, System::EventArgs ^ e )
{
  Larvicide_->CancelEdit();
}



System::Void LarvicideForm::OnAddContainer(System::Object^  sender, System::EventArgs^  e)
{
  BindingList<String^>^ containerList = gcnew BindingList<String^>();

  for each( gui::Container ^ ctnr in ActiveLocation->Containers ) {
    // user can add any container currently in this location
    containerList->Add( ctnr->Name );
  }

  for each( gui::LarvicideTarget ^ lt in Larvicide_->Targets ) {
    // provided it isn't already added
    if( containerList->Contains(lt->Name) ) {
      containerList->Remove( lt->Name );
    }
  }

  AddTargetContainerForm ^ addTargetContainerForm = gcnew AddTargetContainerForm( containerList );
  if( addTargetContainerForm->ShowDialog(this) == ::DialogResult::Cancel ) {
    return;
  }

  // proceed with adding new target
  Larvicide_->AddTargets( addTargetContainerForm->GetContainers() );
}



System::Void
LarvicideForm::OnRemoveContainer(System::Object^  sender, System::EventArgs^  e)
{
  if( dgvTargets->CurrentRow == nullptr ) {
    MessageBox::Show( "Please select container to remove." );
    return;
  }

  Larvicide_->RemoveTarget( (String^)dgvTargets->CurrentRow->Cells[0]->Value->ToString() );
}
