#include "StdAfx.h"
#include "NotifyValidateEditBase.h"

using namespace gui;
using namespace System;
using namespace System::Reflection;



NotifyValidateEditBase::NotifyValidateEditBase(void)
: ValidationFramework::NotifyValidatableBase( false, nullptr, nullptr, true )
{}



NotifyValidateEditBase::~NotifyValidateEditBase(void)
{}



array<System::Reflection::FieldInfo^> ^
NotifyValidateEditBase::ReflectFields(System::Type ^ type)
{
  return type->GetFields( System::Reflection::BindingFlags::NonPublic | System::Reflection::BindingFlags::Instance | System::Reflection::BindingFlags::Public );
}



System::String ^
NotifyValidateEditBase::CreateUniqueKey(System::Reflection::FieldInfo ^ field)
{
  return field->DeclaringType->FullName + "." + field->Name;
}



void
NotifyValidateEditBase::Cleanup(void)
{
  if( this->_state == nullptr ) {
    return;
  }

	this->_state->Clear();
	this->_state = nullptr;
}



void
NotifyValidateEditBase::BeginEdit(void)
{
  if( _inEdit ) {
    return;
  }

  this->OnBeforeBeginEdit();
	this->CopyState();
	this->OnAfterBeginEdit();

  _inEdit = true;
}



void
NotifyValidateEditBase::CopyState(void)
{
  System::Type ^ inspectedType = this->GetType();
  this->_state = gcnew System::Collections::Hashtable();

  // moving down object heirarchy, save fields
	do {
    for each( System::Reflection::FieldInfo ^ field in this->ReflectFields(inspectedType)) {
			if( field->DeclaringType == inspectedType) {
				this->CopyField(field);
			}
		}
    
    // move down heirarchy
		inspectedType = inspectedType->BaseType;
  } while( inspectedType != NotifyValidateEditBase::typeid);
}



void
NotifyValidateEditBase::CopyField(System::Reflection::FieldInfo ^ field)
{
  // don't copy fields which are flagged to be ignored on edit
  if( System::Attribute::IsDefined(field, OnEditIgnoreAttribute::typeid) ) {
    return;
  }

  System::Object ^ fieldValue = field->GetValue(this);
  System::Object ^ savedValue;

  // save field's value, either by cloning or assignment
  if( System::Attribute::IsDefined(field, OnEditSaveCloneAttribute::typeid) ) {
    // save by cloning, not assignment
    System::Type ^ fieldValueType = fieldValue->GetType();
    ConstructorInfo ^ ci = fieldValueType->GetConstructor( gcnew array<Type^>(1){fieldValueType} );
    if( ci == nullptr ) {
      throw gcnew InvalidOperationException( "OnEditSaveCopyAttribute specified on a type without a copy constructor" );
    }
    savedValue = ci->Invoke( gcnew array<Object^>(1){fieldValue} );
  }
  else {
    // save by assignment
    savedValue = fieldValue;
  }

  // determine if this field itself should be edited
  if( dynamic_cast<System::ComponentModel::IEditableObject^>(fieldValue) != nullptr ) {
    ((System::ComponentModel::IEditableObject ^) fieldValue)->BeginEdit();
  }

	this->_state->Add( this->CreateUniqueKey(field), savedValue );
}



void
NotifyValidateEditBase::OnBeforeBeginEdit(void)
{}



void
NotifyValidateEditBase::OnAfterBeginEdit(void)
{}



void
NotifyValidateEditBase::CancelEdit(void)
{
  if( !this->_inEdit ) {
    return;
  }

	this->OnBeforeCancelEdit();
	this->RollbackChanges();
	this->OnAfterCancelEdit();

  this->_inEdit = false;
}



void
NotifyValidateEditBase::RollbackChanges(void)
{
  System::Type ^ inspectedType = this->GetType();

  // working down heirarchy, restore field values
	do {
    for each( System::Reflection::FieldInfo ^ field in this->ReflectFields(inspectedType) ) {
      if( field->DeclaringType == inspectedType ) {
				this->SetField(field);
			}
		}

		inspectedType = inspectedType->BaseType;
  } while( inspectedType != NotifyValidateEditBase::typeid );

	this->Cleanup();
}



void
NotifyValidateEditBase::SetField(System::Reflection::FieldInfo ^ field)
{
  System::Object ^ value = this->_state[this->CreateUniqueKey(field)];

  if( dynamic_cast<System::ComponentModel::IEditableObject^>(value) != nullptr ) {
    ((System::ComponentModel::IEditableObject^) value)->CancelEdit();
  }

	field->SetValue(this, value);
}



void
NotifyValidateEditBase::OnBeforeCancelEdit()
{}



void
NotifyValidateEditBase::OnAfterCancelEdit()
{}



void
NotifyValidateEditBase::EndEdit(void)
{
  if( !_inEdit ) {
    return;
  }

	this->OnBeforeEndEdit();
	this->CommitChanges();
	this->OnAfterEndEdit();
	
  _inEdit = false;
}



void
NotifyValidateEditBase::OnBeforeEndEdit(void)
{}



void
NotifyValidateEditBase::OnAfterEndEdit(void)
{}



void
NotifyValidateEditBase::CommitChanges(void)
{
  System::Type ^ currentType = this->GetType();

	do {
    for each( System::Reflection::FieldInfo ^ field in this->ReflectFields(currentType) ) {
      System::ComponentModel::IEditableObject ^ value = dynamic_cast<System::ComponentModel::IEditableObject^>(this->_state[this->CreateUniqueKey(field)]);
      if( value != nullptr ) {
        value->EndEdit();
      }
		}

		currentType = currentType->BaseType;
  } while( currentType != NotifyValidateEditBase::typeid );

	this->Cleanup();
}
