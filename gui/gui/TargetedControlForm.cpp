#include "StdAfx.h"
#include "TargetedControlForm.h"
#include "AddTargetContainerForm.h"
#include "SingleSchedulePanel.h"
#include "WeeklySchedulePanel.h"
#include "MonthlySchedulePanel.h"
#include "YearlySchedulePanel.h"
#include "PeriodicSchedulePanel.h"

using namespace gui;



generic<class T>
TargetedControlForm<T>::TargetedControlForm( TargetedControl<T> ^ targetedControl, BindingSource ^ locationBinding )
: LocationBinding(locationBinding),
  ActiveLocation((gui::Location^)locationBinding->DataSource),
  CurrentSchedulePanel(nullptr)
{
	InitializeComponent();

  Text = targetedControl->Name;

  // edit control
  _targetedControl = targetedControl;
  _targetedControl->BeginEdit();

  // populate and select correct schedule types
  cboxSchedule->Items->Add( "Single" );
  cboxSchedule->Items->Add( "Weekly" );
  cboxSchedule->Items->Add( "Monthly" );
  cboxSchedule->Items->Add( "Yearly" );
  cboxSchedule->Items->Add( "Periodic" );
  cboxSchedule->SelectedItem = Schedule::GetShortNameFromType( _targetedControl->Schedule );
}



generic<class T>
TargetedControlForm<T>::~TargetedControlForm()
{
	if( components ) {
		delete components;
	}
}



generic<class T>
System::Void
TargetedControlForm<T>::OnLoad(System::Object^  sender, System::EventArgs^  e)
{
  tboxName->DataBindings->Add( "Text", _targetedControl, "Name" );
  Text = _targetedControl->Name;

  // set datasouce, which generates columns, and then do appropriate hiding/arranging
  dgvTargets->DataSource = _targetedControl->Targets;

  dgvTargets->SuspendLayout();
  // TODO this is fucked, it relies on the framework binding to properties in the same order each time
  // evidence shoes this doesn't always happen.  This causes the wrong columns to be displayed.
  // In fact it seems one machine running Vista flip flops the order, that means the very columns we are
  // looking to display are hidden.

//  // look for column named IsValid (for now a workaround to implementing ICustomTypeDescriptor, etc.)
//  int isValidIndex = 0;
//  for( int i = 0; i < dgvTargets->Columns->Count; ++i ) {
//    if( dgvTargets->Columns[i]->Name == "IsValid" ) {
//      isValidIndex = i;
//      break;
//    }
//  }
//
//  // rearrange columns before IsValid column, and set Name as read only
//  for( int i = 0; i < isValidIndex; ++i ) {
//    dgvTargets->Columns[i]->DisplayIndex = (isValidIndex - 1) - i;
//    if( dgvTargets->Columns[i]->Name == "Name" ) {
//      dgvTargets->Columns[i]->ReadOnly = true;
//      dgvTargets->Columns[i]->DefaultCellStyle->BackColor = SystemColors::Control;
//    }
//  }
//
//  // hide IsValid columns and on
//  for( int i = isValidIndex; i < dgvTargets->Columns->Count; ++i ) {
//    dgvTargets->Columns[i]->Visible = false;
//  }
//  dgvTargets->ResumeLayout();

  // look for Name column and "Rate*" columns
  Collections::Generic::List<DataGridViewColumn^> ^ columnsToRemove = gcnew Collections::Generic::List<DataGridViewColumn^>();
  int displayIndex = 1;
  for each( DataGridViewColumn ^ dgvc in dgvTargets->Columns ) {
    if( dgvc->Name == "Name" ) {
      dgvc->DisplayIndex = 0;
      continue;
    }
    else if(  dgvc->Name->StartsWith( "Rate" ) ) {
      dgvc->DisplayIndex = displayIndex++;
      continue;
    }
    dgvc->Visible = false;
  }



  // select current schedule
  SetSchedulePanel();
}



generic<class T>
System::Void
TargetedControlForm<T>::OnScheduleChange( System::Object ^ sender, System::EventArgs ^ e )
{
  // create new schedule
  Type ^ newScheduleType = Schedule::GetTypeFromShortName( (String^)cboxSchedule->SelectedItem );
  Reflection::ConstructorInfo ^ sci = newScheduleType->GetConstructor( gcnew array<Type^>(2){DateTime::typeid, DateTime::typeid} );
  _targetedControl->Schedule = (Schedule^) sci->Invoke( gcnew array<Object^>(2){ActiveLocation->Weather->MinDate, ActiveLocation->Weather->MaxDate} );
  SetSchedulePanel();
}



generic<class T>
void
TargetedControlForm<T>::SetSchedulePanel(void)
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

  Type ^ newFormType = ScheduleTypeToFormType[_targetedControl->Schedule->GetType()];
  Reflection::ConstructorInfo ^ fci = newFormType->GetConstructor( gcnew array<Type^>(2){_targetedControl->Schedule->GetType(), BindingSource::typeid} );
  CurrentSchedulePanel = (UserControl^) fci->Invoke( gcnew array<Object^>(2){_targetedControl->Schedule, LocationBinding} );

  CurrentSchedulePanel->Location = Point( cboxSchedule->Location.X,
                                          cboxSchedule->Location.Y + cboxSchedule->Height + cboxSchedule->Margin.Bottom + CurrentSchedulePanel->Margin.Top );
  //CurrentSchedulePanel->TabIndex = cboxSchedule->TabIndex + 1;
  CurrentSchedulePanel->Size.Width = dgvTargets->Size.Width;

  gboxSchedule->Controls->Add( CurrentSchedulePanel );
}




generic<class T>
System::Void
TargetedControlForm<T>::OnOk( System::Object ^ sender, System::EventArgs ^ e )
{
  _targetedControl->EndEdit();
}



generic<class T>
System::Void
TargetedControlForm<T>::OnCancel( System::Object ^ sender, System::EventArgs ^ e )
{
  _targetedControl->CancelEdit();
}



generic<class T>
System::Void TargetedControlForm<T>::OnAddContainer(System::Object^  sender, System::EventArgs^  e)
{
  BindingList<String^>^ containerList = gcnew BindingList<String^>();

  for each( gui::Container ^ ctnr in ActiveLocation->Containers ) {
    // user can add any container currently in this location
    containerList->Add( ctnr->Name );
  }

  // provided it isn't already added
  for each( Target ^ t in _targetedControl->Targets ) {
    if( containerList->Contains(t->Name) ) {
      containerList->Remove( t->Name );
    }
  }

  AddTargetContainerForm ^ addTargetContainerForm = gcnew AddTargetContainerForm( containerList );
  if( addTargetContainerForm->ShowDialog(this) == ::DialogResult::Cancel ) {
    return;
  }

  // proceed with adding new target
  _targetedControl->AddTargets( addTargetContainerForm->GetContainers() );
}



generic<class T>
System::Void
TargetedControlForm<T>::OnRemoveContainer(System::Object^  sender, System::EventArgs^  e)
{
  if( dgvTargets->CurrentRow == nullptr ) {
    MessageBox::Show( "Please select container to remove." );
    return;
  }

  int nameIndex = dgvTargets->Columns["Name"]->Index;
  _targetedControl->RemoveTarget( dgvTargets->CurrentRow->Cells[nameIndex]->Value->ToString() );
}
