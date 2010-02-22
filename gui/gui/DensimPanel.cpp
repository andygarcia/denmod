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

  errproDemographics->DataSource = _locationBinding;
  errproDemographics->DataMember = "Demographics";

  // serology
  dgvSerology->DataBindings->Add( "DataSource", _locationBinding, "Serology.SeroClasses" );

  snboxManaDuration->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Serology.MANADuration") );
  snboxMaeaDuration->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Serology.MAEADuration") );
  snboxHetDuration->DataBindings->Add( gcnew ParameterDisplayBinding("Value", _locationBinding, "Serology.HetDuration") );

  errproSerology->DataSource = _locationBinding;
  errproSerology->DataMember = "Serology";

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

  errproHumanToMosquitoInfection->DataSource = _locationBinding;
  errproHumanToMosquitoInfection->DataMember = "Virology.HumanToMosquitoInfection";

  errproTiterModification->DataSource = _locationBinding;
  errproTiterModification->DataMember = "Virology.EIP.TiterModification";

  // infection introduction
  _formInfectionIntroduction->DataBindings->Add( "Enabled", _locationBinding, "Weather.IsWeatherAvailable", false, DataSourceUpdateMode::OnPropertyChanged );

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



void
DensimPanel::AllWeatherRemoved(void)
{
  if( tabDensim->SelectedTab == tabInfections ) {
    MessageBox::Show( "All weather has been removed, scheduling of infection introduction not possible until weather is added.","DENSiM",
                      MessageBoxButtons::OK, MessageBoxIcon::Exclamation );
    tabDensim->SelectedTab = tabDemographics;
  }
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
        MessageBox::Show( "Weather data must be added before scheduling infection introduction." );
        e->Cancel = true;
        return;
      }
    }
  }
}



System::Void
DensimPanel::OnSerologyAutoFill( System::Object ^ sender, System::EventArgs ^ e )
{
  Form ^ f = gcnew Form();

  f->FormBorderStyle = Windows::Forms::FormBorderStyle::FixedToolWindow;
  f->ShowInTaskbar = false;
  f->Text = "Auto Fill Serology";
  f->Size = Drawing::Size( 290, 70 );

  TextBox ^ tb = gcnew TextBox();
  tb->TextAlign = HorizontalAlignment::Right;
  tb->Location = Drawing::Point( 12, 12 );
  f->Controls->Add( tb );

  Button ^ ok = gcnew Button();
  ok->Text = "OK";
  ok->Location = Drawing::Point( 118, 10 );
  ok->DialogResult = ::DialogResult::OK;
  f->Controls->Add( ok );

  Button ^ cancel = gcnew Button();
  cancel->Text = "Cancel";
  cancel->DialogResult = ::DialogResult::Cancel;
  cancel->Location = Drawing::Point( 199, 10 );
  f->Controls->Add( cancel );

  f->AcceptButton = ok;
  f->CancelButton = cancel;
  f->StartPosition = FormStartPosition::CenterParent;

  if( f->ShowDialog() == ::DialogResult::OK ) {
    // do something with the number
    String ^ input = tb->Text;
    double proportion = Convert::ToDouble( input );
    GetLocation()->Serology->AutoFillSerology( proportion );
  }
}



System::Void
DensimPanel::OnDemographicsRowValidating( System::Object ^ sender, System::Windows::Forms::DataGridViewCellCancelEventArgs ^ e )
{
  GetLocation()->Demographics->PropertyValidationManager->ValidateProperty( "DemoClasses" );
  // if not valid, calculate appropriate padding to impose error icon in proportion
}
