#pragma once

#include "ParameterDisplayAttribute.h"

using namespace ValidationFramework;



namespace gui {

[System::AttributeUsage(System::AttributeTargets::Field)]
[System::Serializable()]
public ref class OnEditSaveCloneAttribute : System::Attribute
{};



[System::AttributeUsage(System::AttributeTargets::Field)]
[System::Serializable()]
public ref class OnEditIgnoreAttribute : System::Attribute
{};



public ref class NotifyValidateEditBase : public ValidationFramework::NotifyValidatableBase,
                                          public System::ComponentModel::IEditableObject
{
#pragma region Constructors
public:
  NotifyValidateEditBase(void);
  virtual ~NotifyValidateEditBase(void);
#pragma endregion

#pragma region Helper Methods
private:
  array<System::Reflection::FieldInfo^> ^ ReflectFields(System::Type ^ type);
  System::String ^ CreateUniqueKey(System::Reflection::FieldInfo ^ field);
  void Cleanup(void);
#pragma endregion

#pragma region BeginEdit
public:
	virtual void BeginEdit(void);
protected:
  virtual void OnBeforeBeginEdit(void);
  virtual void OnAfterBeginEdit(void);
private:
	void CopyState(void);
  void CopyField(System::Reflection::FieldInfo ^ field);
#pragma endregion

#pragma region CancelEdit
public:
  virtual void CancelEdit(void);
protected:
  virtual void OnBeforeCancelEdit(void);
  virtual void OnAfterCancelEdit(void);
private:
  void RollbackChanges(void);
  void SetField(System::Reflection::FieldInfo ^ field);
#pragma endregion

#pragma region EndEdit
public:
  virtual void EndEdit(void);
protected:
	virtual void OnBeforeEndEdit(void);
	virtual void OnAfterEndEdit(void);
private:
	void CommitChanges(void);
#pragma endregion

#pragma region Fields
private:
  bool _inEdit;
  System::Collections::Hashtable ^ _state;
#pragma endregion
};

};
