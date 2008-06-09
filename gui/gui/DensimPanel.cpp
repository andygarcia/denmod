#include "StdAfx.h"
#include "DensimPanel.h"
#include "RunDensimForm.h"
#include "DensimOutputForm.h"
#include "ParameterDisplayBinding.h"

using namespace gui;



DensimPanel::DensimPanel( BindingSource ^ locationBinding )
: LocationBinding(locationBinding)
{
	InitializeComponent();
  formInfectionIntroduction = gcnew InfectionIntroductionForm(LocationBinding);
  tabInfections->Controls->Add(formInfectionIntroduction);
}



DensimPanel::~DensimPanel()
{
	if( components ) {
		delete components;
	}
}



gui::Location ^
DensimPanel::GetLocation(void)
{
  return (gui::Location^) LocationBinding->DataSource;
}



System::Void
DensimPanel::OnLoad(System::Object^  sender, System::EventArgs^  e)
{
  // some bugs with auto generated columns, oddly this property is not listed in the designer
  dgvDemographics->AutoGenerateColumns = false;
  dgvSerology->AutoGenerateColumns = false;
  dgvVirology->AutoGenerateColumns = false;
  dgvSequentials->AutoGenerateColumns = false;

  // demographics
  dgvDemographics->DataBindings->Add( "DataSource", LocationBinding, "Demographics.DemoClasses" );

  snboxInitialPopulationSize->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Demographics.InitialPopulationSize") );
  snboxHumHostDensity->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Demographics.HumanHostDensity") );

  errProDemographics->DataSource = LocationBinding;
  errProDemographics->DataMember = "Demographics";

  // serology
  dgvSerology->DataBindings->Add( "DataSource", LocationBinding, "Serology.SeroClasses" );

  snboxManaDuration->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Serology.MANADuration") );
  snboxMaeaDuration->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Serology.MAEADuration") );
  snboxHetDuration->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Serology.HetDuration") );

  // virology
  dgvVirology->DataBindings->Add( "DataSource", LocationBinding, "Virology.Serotypes" );
  snboxVirLowTiterSetPoint->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Virology.HumanToMosquitoInfection.LowTiterSetPoint") );
  snboxVirLowTiterInfection->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Virology.HumanToMosquitoInfection.LowTiterInfection") );
  snboxVirHighTiterSetPoint->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Virology.HumanToMosquitoInfection.HighTiterSetPoint") );
  snboxVirHighTiterInfection->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Virology.HumanToMosquitoInfection.HighTiterInfection") );
  snboxNomProbInfection->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Virology.MosquitoToHumanNominalProbabilityOfInfection") );
  snboxMosqCountStochastic->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Virology.MosquitoCountForStochasticity") );

  snboxEipRo25->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Virology.EIP.Development.RO25") );
  snboxEipEnthAct->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Virology.EIP.Development.DHA") );
  snboxEipEnthInact->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Virology.EIP.Development.DHH") );
  snboxEipTempInact->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Virology.EIP.Development.THALF") );

  snboxLowTiterSetPoint->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Virology.EIP.TiterModification.LowSetPoint") );
  snboxLowTiterFactor->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Virology.EIP.TiterModification.LowFactor") );
  snboxHighTiterSetPoint->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Virology.EIP.TiterModification.HighSetPoint") );
  snboxHighTiterFactor->DataBindings->Add( gcnew ParameterDisplayBinding("Value", LocationBinding, "Virology.EIP.TiterModification.HighFactor") );

  // sequentials
  dgvSequentials->DataBindings->Add( "DataSource", LocationBinding, "SequentialInfections.SequentialInfections" );
}



System::Void
DensimPanel::OnRunDensim( System::Object ^ sender, System::EventArgs ^ e )
{
  gui::Location ^ location = GetLocation();

  if( !location->IsCimsimCompleted ) {
    MessageBox::Show( "Before running DENSiM, please run CIMSiM to generate necessary entomological inputs.", "DENSiM",
                      MessageBoxButtons::OK, MessageBoxIcon::Exclamation );
    return;
  }

  // TODO - this should check that all years in available mos data have weather associated
  if( !location->Weather->IsWeatherDataContiguous() ) {
    MessageBox::Show( "Weather data is not contiguous, missing years detected.", "DENSiM",
                      MessageBoxButtons::OK, MessageBoxIcon::Exclamation );
    return;
  }

  RunDensim();
}



System::Void
DensimPanel::RunDensim(System::Void)
{
  RunDensimForm ^ rdf = gcnew RunDensimForm(LocationBinding);
  if( rdf->ShowDialog(this) == ::DialogResult::OK ) {
    // run simulation
    gui::Location::RunDensimOptions ^ rdo = rdf->RunDensimOptions;
    GetLocation()->RunDensim( rdo->StartDate.Year, rdo->StopDate.Year );
    rdf->Close();

    // process output
    DensimOutputForm ^ dof = gcnew DensimOutputForm( GetLocation() );
    dof->ShowDialog(this);
    dof->Close();    
  }
}



System::Void
DensimPanel::OnTabPageSelecting( System::Object ^ sender, System::Windows::Forms::TabControlCancelEventArgs ^ e )
{
  if( e->Action == TabControlAction::Selecting ) {
    if( e->TabPageIndex == 3 ) {
      if( !IsWeatherAvailable ) {
        MessageBox::Show( "Weather data must be added before scheduling infection introductions." );
        e->Cancel = true;
      }
    }
  }
}



System::Void
DensimPanel::OnDemographicsRowValidating( System::Object ^ sender, System::Windows::Forms::DataGridViewCellCancelEventArgs ^ e )
{
  GetLocation()->Demographics->PropertyValidationManager->ValidateProperty( "DemoClasses" );
  // if not valid, calculate appropriate padding to impose error icon in proportion
}
