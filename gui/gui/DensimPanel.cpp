#include "StdAfx.h"
#include "DensimPanel.h"
#include "RunDensimForm.h"
#include "DensimOutputForm.h"
#include "ParameterDisplayBinding.h"

using namespace gui;



DensimPanel::DensimPanel( BindingSource ^ locationBinding )
: _locationBinding(locationBinding)
{
	InitializeComponent();

  _formInfectionIntroduction = gcnew InfectionIntroductionForm(_locationBinding);
  tabInfections->Controls->Add(_formInfectionIntroduction);
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
  return (gui::Location^) _locationBinding->DataSource;
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
  dgvDemographics->DataBindings->Add( "DataSource", _locationBinding, "Demographics.DemoClasses" );

  snboxInitialPopulationSize->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Demographics.InitialPopulationSize") );
  snboxHumHostDensity->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Demographics.HumanHostDensity") );

  errProDemographics->DataSource = _locationBinding;
  errProDemographics->DataMember = "Demographics";

  // serology
  dgvSerology->DataBindings->Add( "DataSource", _locationBinding, "Serology.SeroClasses" );

  snboxManaDuration->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Serology.MANADuration") );
  snboxMaeaDuration->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Serology.MAEADuration") );
  snboxHetDuration->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Serology.HetDuration") );

  errProSerology->DataSource = _locationBinding;
  errProSerology->DataMember = "Serology";

  // virology
  dgvVirology->DataBindings->Add( "DataSource", _locationBinding, "Virology.Serotypes" );
  snboxVirLowTiterSetPoint->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Virology.HumanToMosquitoInfection.LowTiterSetPoint") );
  snboxVirLowTiterInfection->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Virology.HumanToMosquitoInfection.LowTiterInfection") );
  snboxVirHighTiterSetPoint->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Virology.HumanToMosquitoInfection.HighTiterSetPoint") );
  snboxVirHighTiterInfection->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Virology.HumanToMosquitoInfection.HighTiterInfection") );
  snboxNomProbInfection->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Virology.MosquitoToHumanNominalProbabilityOfInfection") );
  snboxMosqCountStochastic->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Virology.MosquitoCountForStochasticity") );

  snboxEipRo25->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Virology.EIP.Development.RO25") );
  snboxEipEnthAct->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Virology.EIP.Development.DHA") );
  snboxEipEnthInact->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Virology.EIP.Development.DHH") );
  snboxEipTempInact->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Virology.EIP.Development.THALF") );

  snboxLowTiterSetPoint->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Virology.EIP.TiterModification.LowSetPoint") );
  snboxLowTiterFactor->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Virology.EIP.TiterModification.LowFactor") );
  snboxHighTiterSetPoint->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Virology.EIP.TiterModification.HighSetPoint") );
  snboxHighTiterFactor->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Virology.EIP.TiterModification.HighFactor") );

  errProHumanToMosquitoInfection->DataSource = _locationBinding;
  errProHumanToMosquitoInfection->DataMember = "Virology.HumanToMosquitoInfection";

  errProTiterModification->DataSource = _locationBinding;
  errProTiterModification->DataMember = "Virology.EIP.TiterModification";

  // sequentials
  dgvSequentials->DataBindings->Add( "DataSource", _locationBinding, "SequentialInfections.SequentialInfections" );
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
  RunDensimForm ^ rdf = gcnew RunDensimForm(_locationBinding);
  if( rdf->ShowDialog(this) == ::DialogResult::OK ) {
    // run simulation
    gui::Location::RunDensimOptions ^ rdo = rdf->RunDensimOptions;
    GetLocation()->RunDensim( rdo->StartDate, rdo->StopDate );
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
  gui::Location ^ location = GetLocation();

  if( e->Action == TabControlAction::Selecting ) {
    if( e->TabPageIndex == 3 ) {
      if( !location->Weather->IsWeatherAvailable ) {
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
