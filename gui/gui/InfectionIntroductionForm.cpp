#include "StdAfx.h"
#include "InfectionIntroductionForm.h"

using namespace gui;



InfectionIntroductionForm::InfectionIntroductionForm( BindingSource ^ locationBinding )
: LocationBinding(locationBinding)
{
  InitializeComponent();

  // create scheduling controls for each serotype
  ScheduleD1 = gcnew ScheduleControl( LocationBinding, "InfectionIntroduction.Dengue1.Schedule" );
  ScheduleD1->Location = Point( numHumansD1->Location.X + numHumansD1->Size.Width + numHumansD1->Margin.Right, 3 );
  tabDengue1->Controls->Add( ScheduleD1 );

  ScheduleD2 = gcnew ScheduleControl( LocationBinding, "InfectionIntroduction.Dengue2.Schedule" );
  ScheduleD2->Location = Point( numHumansD2->Location.X + numHumansD2->Size.Width + numHumansD2->Margin.Right, 3 );
  tabDengue2->Controls->Add( ScheduleD2 );

  ScheduleD3 = gcnew ScheduleControl( LocationBinding, "InfectionIntroduction.Dengue3.Schedule" );
  ScheduleD3->Location = Point( numHumansD3->Location.X + numHumansD3->Size.Width + numHumansD3->Margin.Right, 3 );
  tabDengue3->Controls->Add( ScheduleD3 );

  ScheduleD4 = gcnew ScheduleControl( LocationBinding, "InfectionIntroduction.Dengue4.Schedule" );
  ScheduleD4->Location = Point( numHumansD4->Location.X + numHumansD4->Size.Width + numHumansD4->Margin.Right, 3 );
  tabDengue4->Controls->Add( ScheduleD4 );
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
  // only enable infection introduction form when weather is available
  //this->DataBindings->Add( "Enabled", LocationBinding, "Weather.IsWeatherAvailable", false, DataSourceUpdateMode::OnPropertyChanged );

  numHumansD1->DataBindings->Add( "Text", LocationBinding, "InfectionIntroduction.Dengue1.Humans", false, DataSourceUpdateMode::OnPropertyChanged );
  numMosquitoesD1->DataBindings->Add( "Text", LocationBinding, "InfectionIntroduction.Dengue1.Mosquitoes", false, DataSourceUpdateMode::OnPropertyChanged );

  numHumansD2->DataBindings->Add( "Text", LocationBinding, "InfectionIntroduction.Dengue2.Humans", false, DataSourceUpdateMode::OnPropertyChanged );
  numMosquitoesD2->DataBindings->Add( "Text", LocationBinding, "InfectionIntroduction.Dengue2.Mosquitoes", false, DataSourceUpdateMode::OnPropertyChanged );

  numHumansD3->DataBindings->Add( "Text", LocationBinding, "InfectionIntroduction.Dengue3.Humans", false, DataSourceUpdateMode::OnPropertyChanged );
  numMosquitoesD3->DataBindings->Add( "Text", LocationBinding, "InfectionIntroduction.Dengue3.Mosquitoes", false, DataSourceUpdateMode::OnPropertyChanged );

  numHumansD4->DataBindings->Add( "Text", LocationBinding, "InfectionIntroduction.Dengue4.Humans", false, DataSourceUpdateMode::OnPropertyChanged );
  numMosquitoesD4->DataBindings->Add( "Text", LocationBinding, "InfectionIntroduction.Dengue4.Mosquitoes", false, DataSourceUpdateMode::OnPropertyChanged );
}
