#include "StdAfx.h"
#include "CimsimPanel.h"
#include "RunCimsimForm.h"
#include "CimsimOutputForm.h"
#include "ContainerForm.h"
#include "AddControlForm.h"
#include "TargetedControlForm.h"
#include "LarvicideForm.h"
#include "SterileMaleReleaseForm.h"
#include "SpaceSprayForm.h"
#include "ResidualSprayForm.h"
#include "BiologyForm.h"
#include "FoodFitterForm.h"

using namespace gui;



CimsimPanel::CimsimPanel( BindingSource ^ locationBinding )
: LocationBinding(locationBinding),
  ControlFormMapping(gcnew Collections::Generic::Dictionary<System::Type^, System::Type^>())
{
	InitializeComponent();

  ControlFormMapping->Add( SourceReduction::typeid, TargetedControlForm<SourceReductionTarget^>::typeid );
  ControlFormMapping->Add( OvipositionExclusion::typeid, TargetedControlForm<OvipositionExclusionTarget^>::typeid );
  ControlFormMapping->Add( EggDestruction::typeid, TargetedControlForm<EggDestructionTarget^>::typeid );
  ControlFormMapping->Add( Larvicide::typeid, LarvicideForm::typeid );
  ControlFormMapping->Add( SterileMaleRelease::typeid, SterileMaleReleaseForm::typeid );
  ControlFormMapping->Add( SpaceSpray::typeid, SpaceSprayForm::typeid );
  ControlFormMapping->Add( ResidualSpray::typeid, ResidualSprayForm::typeid );

  PreviousContainerHoverIndex = -2;
  dtContainerLastShown = DateTime::Now.Subtract( TimeSpan(0,0,0,0,ttContainers->ReshowDelay) );
}



CimsimPanel::~CimsimPanel()
{
  if( components ) {
		delete components;
	}
}



gui::Location ^
CimsimPanel::GetLocation(void)
{
  return (gui::Location^) LocationBinding->DataSource;
}



System::Void
CimsimPanel::OnLoad(System::Object^  sender, System::EventArgs^  e)
{
  this->lboxContainers->DataBindings->Add( "DataSource", LocationBinding, "Containers" );
  this->lboxContainers->DisplayMember = "Name";

  this->lboxControls->DataBindings->Add( "DataSource", LocationBinding, "Controls" );
  this->lboxControls->DisplayMember = "Name";
}



System::Void
CimsimPanel::OnRunCimsim(System::Object^  sender, System::EventArgs^  e)
{
  gui::Location ^ location = GetLocation();

  if( location->Containers->Count == 0 ) {
    MessageBox::Show( "Unable to run CIMSiM until containers are added." );
    return;
  }

  if( location->Weather->NumberOfYears == 0 ) {
    MessageBox::Show( "Unable to run CIMSiM until weather data is added." );
    return;
  }

  if( location->Weather->IsWeatherDataContiguous() == false ) {
    MessageBox::Show( "Weather data is not contiguous, missing years detected." );
    return;
  }

  RunCimsim();
}



void
CimsimPanel::RunCimsim(void)
{
  RunCimsimForm ^ rcf = gcnew RunCimsimForm( LocationBinding, _userSettings->EstablishedPopulationDefault );
  if( rcf->ShowDialog(this) == ::DialogResult::OK ) {
    // run simulation
    gui::Location::RunCimsimOptions ^ rco = rcf->RunCimsimOptions;
    GetLocation()->RunCimsim( rco->UsePop, _userSettings->StochasticAdvancement, rco->StartDate, rco->StopDate );
    rcf->Close();

    // process output
    CimsimOutputForm ^ cof = gcnew CimsimOutputForm( GetLocation() );
    cof->ShowDialog(this);
    cof->Close();    
  }
}



System::Void
CimsimPanel::OnAddContainer( System::Object ^  sender, System::EventArgs ^  e )
{
  gui::Container ^ newContainer = GetLocation()->Containers->AddNew();
  newContainer->Name = "[new container name]";
  ContainerForm ^ addForm = gcnew ContainerForm( newContainer, "Add Container" , GetLocation() );

  if( addForm->ShowDialog(this) == ::DialogResult::OK ) {
    GetLocation()->Containers->EndNew( GetLocation()->Containers->IndexOf(newContainer) );
  }
  else {
    GetLocation()->Containers->CancelNew( GetLocation()->Containers->IndexOf(newContainer) );
  }
  addForm->Close();
}



System::Void
CimsimPanel::OnEditContainer( System::Object ^ sender, System::EventArgs ^ e )
{
  if( lboxContainers->SelectedItem == nullptr ) {
    return;
  }

  gui::Container ^ selectedContainer = (gui::Container^) lboxContainers->SelectedItem;
  String ^ oldName = selectedContainer->Name;
  ContainerForm ^ cf = gcnew ContainerForm( selectedContainer, "Editing Container: " + selectedContainer->Name, GetLocation() );
  cf->ShowDialog(this);
  cf->Close();

  if( oldName != selectedContainer->Name ) {
    GetLocation()->RenameContainer( selectedContainer, oldName );
  }
}



System::Void
CimsimPanel::OnRemoveContainer( System::Object ^ sender, System::EventArgs ^ e )
{
  if( lboxContainers->SelectedItem == nullptr ) {
    // no container selected
    return;
  }

  gui::Container ^ selectedContainer = (gui::Container^) lboxContainers->SelectedItem;
  GetLocation()->RemoveContainer( selectedContainer );
}



System::Void
CimsimPanel::OnCopyContainer( System::Object ^ sender, System::EventArgs ^ e )
{
  if( lboxContainers->SelectedItem == nullptr ) {
    // no container selected
    return;
  }

  gui::Container ^ selectedContainer = (gui::Container^) lboxContainers->SelectedItem;
  gui::Container ^ clonedContainer = gcnew gui::Container( selectedContainer );

  for( int i = 1; i < System::Int32::MaxValue; ++i  ) {
    String ^ newName = selectedContainer->Name + " Copy #" + i;
    if( GetLocation()->ContainerNameCount(newName) == 0 ) {
      // find the next iteration of "Container - Clone #i" that doesn't exist
      clonedContainer->Name = newName;
      break;
    }
  }

  GetLocation()->Containers->Add( gcnew gui::Container(clonedContainer) );
}



System::Void
CimsimPanel::OnMouseMoveContainers( System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e )
{
  if( sender == lboxContainers ) {
    int hoverIndex = lboxContainers->IndexFromPoint( Point(e->X, e->Y) );
    if( 0 <= hoverIndex && hoverIndex < lboxContainers->Items->Count  && hoverIndex != PreviousContainerHoverIndex ) {
      if( DateTime::Now > dtContainerLastShown.AddMilliseconds(ttContainers->ReshowDelay) ) {
        ttContainers->SetToolTip( lboxContainers, lboxContainers->Items[hoverIndex]->ToString() );
        PreviousContainerHoverIndex = hoverIndex;
      }
    }
  }
}



System::Void
CimsimPanel::OnMouseLeaveContainers( System::Object ^ sender, System::EventArgs ^ e )
{
  PreviousContainerHoverIndex = -2;
  ttContainers->RemoveAll();
}



System::Void
CimsimPanel::OnAddControl( System::Object ^ sender, System::EventArgs ^ e )
{
  if( !GetLocation()->Weather->IsWeatherAvailable ) {
    MessageBox::Show( "Unable to add control interventions s until weather data is available.  Please add weather data.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error );
    return;
  }

  // user selects new control
  AddControlForm ^ acf = gcnew AddControlForm();
  if( acf->ShowDialog(this) != ::DialogResult::OK ) {
    return;
  }
  System::Type ^ controlType = acf->GetNewControlType();
  acf->Close();


  // do not allow  more than one larvicide, sterile male release, or residual spray
  if( controlType == Larvicide::typeid ) {
    if( GetLocation()->GetNumberOfControls( Larvicide::typeid ) > 0 ) {
      MessageBox::Show( "CIMSiM does not currently support multiple larvicides." );
      return;
    }
  }
  if( controlType == SterileMaleRelease::typeid ) {
    if( GetLocation()->GetNumberOfControls( SterileMaleRelease::typeid ) > 0 ) {
      MessageBox::Show( "CIMSiM does not currently support multiple sterile male releases." );
      return;
    }
  }
  if( controlType == ResidualSpray::typeid ) {
    if( GetLocation()->GetNumberOfControls( ResidualSpray::typeid ) > 0 ) {
      MessageBox::Show( "CIMSiM does not currently support multiple residual sprays." );
      return;
    }
  }

  // new control schedule limited by available weather
  DateTime minDate = GetLocation()->Weather->MinDate;
  DateTime maxDate = GetLocation()->Weather->MaxDate;

  // create new control
  Reflection::ConstructorInfo ^ cci = controlType->GetConstructor( gcnew array< System::Type^>(2){DateTime::typeid,DateTime::typeid} );
  gui::Control ^ newControl = (gui::Control^) cci->Invoke( gcnew array<Object^>(2){ minDate, maxDate } );
  newControl->Name = newControl->GetType()->Name + " #" + (GetLocation()->GetNumberOfControls(controlType) + 1);

  // show add form
  System::Type ^ formType = ControlFormMapping[controlType];
  Form ^ f = (Form^) Activator::CreateInstance( formType, gcnew array<Object^>(2){newControl, LocationBinding} );
  if( f->ShowDialog(this) == ::DialogResult::OK ) {
    GetLocation()->AddControl( newControl );
  }
  f->Close();
}



System::Void
CimsimPanel::OnEditControl( System::Object ^ sender, System::EventArgs ^ e)
{
  if( lboxControls->SelectedItem == nullptr ) {
    return;
  }
  gui::Control ^ selectedControl = (gui::Control^) lboxControls->SelectedItem;

  // find min and max weather dates for schedule constraints
  if( !GetLocation()->Weather->IsWeatherAvailable ) {
    MessageBox::Show( "Unabled to edit control intervention until weather data is available.  Please add weather data.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error );
    return;
  }

  // show edit form
  System::Type ^ controlType = selectedControl->GetType();
  System::Type ^ formType = ControlFormMapping[controlType];
  Form ^ f = (Form^) Activator::CreateInstance( formType, gcnew array<Object^>(2){selectedControl, LocationBinding} );
  f->ShowDialog(this);
  f->Close();
}



System::Void
CimsimPanel::OnRemoveControl( System::Object ^ sender, System::EventArgs ^ e )
{
  if( lboxContainers->SelectedItem == nullptr ) {
    // no container selected
    return;
  }
  gui::Control ^ selectedControl = (gui::Control^) lboxControls->SelectedItem;
  GetLocation()->RemoveControl( selectedControl );
}



System::Void
CimsimPanel::OnClickBiology( System::Object ^ sender, System::EventArgs ^ e )
{
  BiologyForm ^ bf = gcnew BiologyForm(LocationBinding);
  GetLocation()->Biology->BeginEdit();
  if( bf->ShowDialog(this) == ::DialogResult::OK ) {
    GetLocation()->Biology->EndEdit();
  }
  else {
    GetLocation()->Biology->CancelEdit();
  }
  bf->Close();
}



System::Void
CimsimPanel::OnRunFoodFitter( System::Object ^ sender, System::EventArgs ^  e )
{
  if( GetLocation()->Containers->Count == 0 ) {
    MessageBox::Show( "Container types must be added before running food fitter" );
    return;
  }
  FoodFitterForm ^ fff = gcnew FoodFitterForm(GetLocation());
  fff->ShowDialog(this);
  fff->Close();
}
