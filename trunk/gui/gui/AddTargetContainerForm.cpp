#include "StdAfx.h"
#include "AddTargetContainerForm.h"

using namespace gui;


AddTargetContainerForm::AddTargetContainerForm( BindingList<String^> ^ containers )
{
	InitializeComponent();

  Containers_ = containers;
}



AddTargetContainerForm::~AddTargetContainerForm()
{
	if( components ) {
		delete components;
	}
}



array<String^> ^ 
AddTargetContainerForm::GetContainers(void)
{
  ListBox::SelectedObjectCollection ^ soc = lboxContainers->SelectedItems;

  array<String^> ^ containers = gcnew array<String^>(soc->Count);
  soc->CopyTo( containers, 0 );

  return containers;
}



System::Void
AddTargetContainerForm::OnLoad(System::Object^  sender, System::EventArgs^  e)
{
  this->lboxContainers->DataSource = Containers_;
}
