#include "StdAfx.h"
#include "CimsimPanel.h"
#include "ContainerForm.h"
#include "ParameterDisplayBinding.h"

using namespace gui;



ContainerForm::ContainerForm( gui::Container ^ container, System::String ^ title, gui::Location ^ activeLoc )
: ActiveLocation( activeLoc )
{
  InitializeComponent();

  Container_ = container;
  Container_->BeginEdit();

  this->Text = title;
}



ContainerForm::~ContainerForm()
{
	if( components ) {
		delete components;
	}
}



System::Void
ContainerForm::OnLoad( System::Object^ sender, System::EventArgs^ e)
{
  tboxName->DataBindings->Add( "Text", Container_, "Name" );
  snboxDensity->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "Density") );

  chkClone->DataBindings->Add( "Checked", Container_, "IsCloned", false, DataSourceUpdateMode::OnPropertyChanged );
  snboxNumberOfClones->DataBindings->Add( "Enabled", Container_, "IsCloned", false, DataSourceUpdateMode::Never );
  snboxNumberOfClones->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "NumberOfClones", DataSourceUpdateMode::OnPropertyChanged) );

  if( Container_->Shape == gui::Container::ShapeType::Circular  ) {
    radRect->Checked = false;
    radCirc->Checked = true;
  }
  else if( Container_->Shape == gui::Container::ShapeType::Rectangular ) {
    radRect->Checked = true;
    radCirc->Checked = false;
  }
  OnShapeChanged(nullptr, nullptr);

  snboxHeight->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "Height", DataSourceUpdateMode::OnPropertyChanged) );
  snboxLength->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "Length", DataSourceUpdateMode::OnPropertyChanged) );
  snboxDiameter->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "Diameter", DataSourceUpdateMode::OnPropertyChanged) );
  snboxWidth->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "Width", DataSourceUpdateMode::OnPropertyChanged) );

  snboxMonthlyTurnover->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "MonthlyTurnoverRate") );
  snboxInitEggs->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "InitEggs") );
  snboxSunExp->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "SunExposure", DataSourceUpdateMode::OnPropertyChanged) );
  snboxCooling->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "Cooling", DataSourceUpdateMode::OnPropertyChanged) );

  chkCover->DataBindings->Add( "Checked", Container_, "IsCovered", false, DataSourceUpdateMode::OnPropertyChanged );
  lblCoverReduction->DataBindings->Add( "Enabled", Container_, "IsCovered", false, DataSourceUpdateMode::Never );
  snboxCoverReduction->DataBindings->Add( "Enabled", Container_, "IsCovered", false, DataSourceUpdateMode::Never );
  snboxCoverReduction->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "CoverReduction", DataSourceUpdateMode::OnPropertyChanged) );

  typedef Collections::Generic::KeyValuePair<Enum^, String^> EnumValuePair;
  typedef Collections::Generic::List<EnumValuePair> EnumValuePairCollection;
  EnumValuePairCollection ^ fillEnumValues = gcnew Collections::Generic::List<EnumValuePair>();
  fillEnumValues->Add( EnumValuePair( gui::Container::Fill::ManualFill, "Manually Filled" ) );
  fillEnumValues->Add( EnumValuePair( gui::Container::Fill::RainFill, "Rain Filled" ) );

  cboxFillMethod->DisplayMember = "Value";
  cboxFillMethod->ValueMember = "Key";
  cboxFillMethod->DataSource = fillEnumValues;
  cboxFillMethod->DataBindings->Add( "SelectedValue", Container_, "FillMethod" );
  
  snboxWatershed->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "WatershedRatio", DataSourceUpdateMode::OnPropertyChanged) );

  Collections::Generic::List<EnumValuePair> ^ frequencyEnumValues;
  frequencyEnumValues = gcnew Collections::Generic::List<EnumValuePair>();
  frequencyEnumValues->Add( EnumValuePair( gui::Container::Frequency::Daily, "Daily" ) );
  frequencyEnumValues->Add( EnumValuePair( gui::Container::Frequency::Weekly, "Weekly" ) );
  frequencyEnumValues->Add( EnumValuePair( gui::Container::Frequency::Monthly, "Monthly" ) );

  cboxManualFillFrequency->DisplayMember = "Value";
  cboxManualFillFrequency->ValueMember= "Key";
  cboxManualFillFrequency->DataSource = frequencyEnumValues;
  cboxManualFillFrequency->DataBindings->Add( "SelectedValue", Container_, "ManualFillFrequency" );

  snboxDrawdownPercentage->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "DrawdownPercentage", DataSourceUpdateMode::OnPropertyChanged) );

  cboxDrawdownFrequency->DisplayMember = "Value";
  cboxDrawdownFrequency->ValueMember= "Key";
  cboxDrawdownFrequency->DataSource = gcnew EnumValuePairCollection( frequencyEnumValues );
  cboxDrawdownFrequency->DataBindings->Add( "SelectedValue", Container_, "DrawdownFrequency" );

  snboxInitFood->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "InitFood", DataSourceUpdateMode::OnPropertyChanged) );
  snboxDecayRate->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "FoodDecayRate", DataSourceUpdateMode::OnPropertyChanged) );

  snboxFoodJan->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "FoodGainJan", DataSourceUpdateMode::OnPropertyChanged) );
  snboxFoodFeb->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "FoodGainFeb", DataSourceUpdateMode::OnPropertyChanged) );
  snboxFoodMar->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "FoodGainMar", DataSourceUpdateMode::OnPropertyChanged) );
  snboxFoodApr->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "FoodGainApr", DataSourceUpdateMode::OnPropertyChanged) );
  snboxFoodMay->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "FoodGainMay", DataSourceUpdateMode::OnPropertyChanged) );
  snboxFoodJun->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "FoodGainJun", DataSourceUpdateMode::OnPropertyChanged) );
  snboxFoodJul->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "FoodGainJul", DataSourceUpdateMode::OnPropertyChanged) );
  snboxFoodAug->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "FoodGainAug", DataSourceUpdateMode::OnPropertyChanged) );
  snboxFoodSep->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "FoodGainSep", DataSourceUpdateMode::OnPropertyChanged) );
  snboxFoodOct->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "FoodGainOct", DataSourceUpdateMode::OnPropertyChanged) );
  snboxFoodNov->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "FoodGainNov", DataSourceUpdateMode::OnPropertyChanged) );
  snboxFoodDec->DataBindings->Add( gcnew ParameterDisplayBinding("Value", Container_, "FoodGainDec", DataSourceUpdateMode::OnPropertyChanged) );

  errproContainer->DataSource = Container_;
  Container_->PropertyValidationManager->ValidateAllProperties();
}



System::Void
ContainerForm::OnShapeChanged( System::Object ^ sender, System::EventArgs ^ e )
{
  if( radCirc->Checked == true ) {
    lblLength->Visible = false;
    snboxLength->Visible = false;
    lblWidth->Visible = false;
    snboxWidth->Visible = false;

    // move height up to width position (to stack below diameter)
    lblHeight->Location = Point( 140, 76 );
    lblHeight->Visible = true;
    snboxHeight->Location = Point( 210, 74 );
    snboxHeight->Visible = true;

    lblDiameter->Visible = true;
    snboxDiameter->Visible = true;
    Container_->Shape = gui::Container::ShapeType::Circular;
  }
  else if( radRect->Checked == true ) {
    lblLength->Visible = true;
    snboxLength->Visible = true;
    lblWidth->Visible = true;
    snboxWidth->Visible = true;

    // move height back down below width
    lblHeight->Location = Point( 140, 102 );
    lblHeight->Visible = true;
    snboxHeight->Location = Point( 210, 100 );
    snboxHeight->Visible = true;

    lblDiameter->Visible = false;
    snboxDiameter->Visible = false;
    Container_->Shape = gui::Container::ShapeType::Rectangular;
  }
}



System::Void
ContainerForm::OnFillMethodChanged( System::Object ^ sender, System::EventArgs ^ e )
{
  if( cboxFillMethod->SelectedValue == nullptr ) {
    return;
  }

  gui::Container::Fill newFillMethod = (gui::Container::Fill) cboxFillMethod->SelectedValue;
  if( newFillMethod == gui::Container::Fill::ManualFill ) {
    lblWatershed->Enabled = false;
    snboxWatershed->Enabled = false;
    cboxManualFillFrequency->Enabled = true;
    lblManualFillFrequency->Enabled = true;
  }
  else if( newFillMethod == gui::Container::Fill::RainFill ) {
    lblWatershed->Enabled = true;
    snboxWatershed->Enabled = true;
    cboxManualFillFrequency->Enabled = false;
    lblManualFillFrequency->Enabled = false;
  }
}



System::Void
ContainerForm::OnCopyFood( System::Object ^ sender, System::EventArgs ^ e )
{
  double newMonthlyFood = Double::Parse(snboxDailyFood->Value);

  Container_->FoodGainJan = newMonthlyFood;
  Container_->FoodGainFeb = newMonthlyFood;
  Container_->FoodGainMar = newMonthlyFood;
  Container_->FoodGainApr = newMonthlyFood;
  Container_->FoodGainMay = newMonthlyFood;
  Container_->FoodGainJun = newMonthlyFood;
  Container_->FoodGainJul = newMonthlyFood;
  Container_->FoodGainAug = newMonthlyFood;
  Container_->FoodGainSep = newMonthlyFood;
  Container_->FoodGainOct = newMonthlyFood;
  Container_->FoodGainNov = newMonthlyFood;
  Container_->FoodGainDec = newMonthlyFood;
}



System::Void
ContainerForm::OnOk( System::Object ^ sender, System::EventArgs ^ e )
{
  using namespace ValidationFramework;

  // validate entire object
  Container_->PropertyValidationManager->ValidateAllProperties();
  if( !Container_->IsValid ) {
    String ^ errorMessages = ValidationFramework::ResultFormatter::GetConcatenatedErrorMessages( "\n", Container_->PropertyValidationManager->ValidatorResultsInError );
    MessageBox::Show( this, errorMessages, "Errors in container description." );
    this->DialogResult = ::DialogResult::None;
    return;
  }

  if( ActiveLocation->ContainerNameCount(tboxName->Text) != 1 ) {
    // name of container already exists
    this->DialogResult = ::DialogResult::None;
    MessageBox::Show( "A container with this name already exists.  Please choose a unique name.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    tboxName->Focus();
    return;
  }
  else {
    // name is unique
    Container_->EndEdit();
  }
}



System::Void ContainerForm::OnCancel(System::Object^  sender, System::EventArgs^  e)
{
  Container_->CancelEdit();
}
