#include "StdAfx.h"
#include "DensimExtOutputForm.h"
#include "GraphForm.h"
#include "DensimPanel.h"

using namespace gui;



DensimExtOutputForm::DensimExtOutputForm( gui::Location ^ location, DateTime beginDate, DateTime endDate )
: Location_( location ),
  BeginDate_(beginDate),
  EndDate_(endDate),
  SimOutput_(location->DensimData)
{
	InitializeComponent();
}



DensimExtOutputForm::~DensimExtOutputForm()
{
	if( components ) {
		delete components;
	}
}



System::Void
DensimExtOutputForm::OnLoad(System::Object^  sender, System::EventArgs^  e)
{
  lboxLocationGraphs->DataSource = System::Enum::GetValues( DensimGraphType::typeid );
}



System::Void
DensimExtOutputForm::OnViewLocationGraph(System::Object^  sender, System::EventArgs^  e)
{
  if( lboxLocationGraphs->SelectedItem == nullptr ) {
    MessageBox::Show( this, "Please select a graph to view." );
    return;
  }

  GraphForm ^ gf = gcnew GraphForm( Location_, (DensimGraphType) lboxLocationGraphs->SelectedIndex );
  gf->ShowDialog(this);
  gf->Close();
}
