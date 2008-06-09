#include "StdAfx.h"
#include "InfectionIntroductionForm.h"

using namespace gui;



InfectionIntroductionForm::InfectionIntroductionForm( BindingSource ^ locationBinding )
: LocationBinding(locationBinding)
{
  InitializeComponent();

  ScheduleD1 = gcnew ScheduleControl( LocationBinding, "InfectionIntroduction.Dengue1.Schedule" );
  ScheduleD1->Location = Point( lblScheduleD1->Location.X + lblScheduleD1->Size.Width + lblScheduleD1->Margin.Right, numHumansD1->Location.Y );
  tabDengue1->Controls->Add( ScheduleD1 );

  ScheduleD2 = gcnew ScheduleControl( LocationBinding, "InfectionIntroduction.Dengue2.Schedule" );
  ScheduleD2->Location = Point( lblScheduleD2->Location.X + lblScheduleD2->Size.Width + lblScheduleD2->Margin.Right, numHumansD2->Location.Y );
  tabDengue2->Controls->Add( ScheduleD2 );

  ScheduleD3 = gcnew ScheduleControl( LocationBinding, "InfectionIntroduction.Dengue3.Schedule" );
  ScheduleD3->Location = Point( lblScheduleD3->Location.X + lblScheduleD3->Size.Width + lblScheduleD3->Margin.Right, numHumansD3->Location.Y );
  tabDengue3->Controls->Add( ScheduleD3 );

  ScheduleD4 = gcnew ScheduleControl( LocationBinding, "InfectionIntroduction.Dengue4.Schedule" );
  ScheduleD4->Location = Point( lblScheduleD4->Location.X + lblScheduleD4->Size.Width + lblScheduleD4->Margin.Right, numHumansD4->Location.Y );
  tabDengue4->Controls->Add( ScheduleD4 );

  this->Enabled = false;
}



InfectionIntroductionForm::~InfectionIntroductionForm(void)
{
  if( components ) {
		delete components;
	}
}



System::Void
InfectionIntroductionForm::OnLoad( System::Object ^ sender, System::EventArgs ^ e )
{
  numHumansD1->DataBindings->Add( "Text", LocationBinding, "InfectionIntroduction.Dengue1.Humans" );
  numMosquitoesD1->DataBindings->Add( "Text", LocationBinding, "InfectionIntroduction.Dengue1.Mosquitoes" );

  numHumansD2->DataBindings->Add( "Text", LocationBinding, "InfectionIntroduction.Dengue2.Humans" );
  numMosquitoesD2->DataBindings->Add( "Text", LocationBinding, "InfectionIntroduction.Dengue2.Mosquitoes" );

  numHumansD3->DataBindings->Add( "Text", LocationBinding, "InfectionIntroduction.Dengue3.Humans" );
  numMosquitoesD3->DataBindings->Add( "Text", LocationBinding, "InfectionIntroduction.Dengue3.Mosquitoes" );

  numHumansD4->DataBindings->Add( "Text", LocationBinding, "InfectionIntroduction.Dengue4.Humans" );
  numMosquitoesD4->DataBindings->Add( "Text", LocationBinding, "InfectionIntroduction.Dengue4.Mosquitoes" );
}
