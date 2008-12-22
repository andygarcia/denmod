#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace gui {

	public ref class ContainerForm : public System::Windows::Forms::Form
	{
  public:
    ContainerForm( gui::Container ^ container, System::String ^ title, gui::Location ^ activeLoc );
		~ContainerForm(void);

  private:
    System::Void OnLoad( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnShapeChanged( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnFillMethodChanged( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnCopyFood( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnOk( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnCancel( System::Object ^ sender, System::EventArgs ^ e );

  private:
    gui::Container ^ Container_;
    gui::Location ^ ActiveLocation;

  private:
    // Name and density
    System::Windows::Forms::Label^  lblName;
    System::Windows::Forms::TextBox^  tboxName;
    System::Windows::Forms::Label^  lblDensity;


    // Tab pages
    System::Windows::Forms::TabControl^  tabControl1;
    System::Windows::Forms::TabPage^  tabShapeSize;
    System::Windows::Forms::TabPage^  tabConditions;
    System::Windows::Forms::TabPage^  tabWater;
    System::Windows::Forms::TabPage^  tabFood;

    // Shape & Size Tab
    System::Windows::Forms::Label^  lblShape;
    System::Windows::Forms::RadioButton^  radRect;
    System::Windows::Forms::RadioButton^  radCirc;
    System::Windows::Forms::Label^  lblLength;

    System::Windows::Forms::Label^  lblWidth;

    System::Windows::Forms::Label^  lblHeight;

    System::Windows::Forms::Label^  lblDiameter;

    System::Windows::Forms::Label^  lblWatershed;



    // Conditions Tab
    System::Windows::Forms::Label^  lblMonthlyTurnover;

    System::Windows::Forms::Label^  lblInitEggs;


    System::Windows::Forms::Label^  lblSunExp;

    System::Windows::Forms::Label^  lblCooling;


    System::Windows::Forms::Label^  lblCoverReduction;


    // Water Tab
    System::Windows::Forms::Label^  lblFillMethod;
    System::Windows::Forms::ComboBox^  cboxFillMethod;
    System::Windows::Forms::Label^  lblManualFillFrequency;
    System::Windows::Forms::ComboBox^  cboxManualFillFrequency;

    System::Windows::Forms::Label^  lblDrawdown;

    System::Windows::Forms::Label^  lblDrawdownFrequency;
    System::Windows::Forms::ComboBox^  cboxDrawdownFrequency;

    System::Windows::Forms::CheckBox^  chkCover;


    // Food Tab
    System::Windows::Forms::Label^  lblInitFoot;

    System::Windows::Forms::Label^  lblFoodDecay;


    System::Windows::Forms::Label^  lblFoodAdd;
    System::Windows::Forms::Label^  lblFoodJan;

    System::Windows::Forms::Label^  lblFoodFeb;

    System::Windows::Forms::Label^  lblFoodMar;

    System::Windows::Forms::Label^  lblFoodApr;

    System::Windows::Forms::Label^  lblFoodMay;

    System::Windows::Forms::Label^  lblFoodJun;

    System::Windows::Forms::Label^  lblFoodJul;

    System::Windows::Forms::Label^  lblFoodAug;

    System::Windows::Forms::Label^  lblFoodSep;

    System::Windows::Forms::Label^  lblFoodOct;

    System::Windows::Forms::Label^  lblFoodNov;

    System::Windows::Forms::Label^  lblFoodDec;


    System::Windows::Forms::Label^  lblDailyFood;

    System::Windows::Forms::Button^  btnCopyFood;

    // Dialog buttons  
    System::Windows::Forms::Button^  btnCancel;
    System::Windows::Forms::Button^  btnOk;
private: ctrl::ScientificNotationTextBox^  snboxMonthlyTurnover;
private: ctrl::ScientificNotationTextBox^  snboxCoverReduction;

private: ctrl::ScientificNotationTextBox^  snboxCooling;

private: ctrl::ScientificNotationTextBox^  snboxSunExp;




private: ctrl::ScientificNotationTextBox^  snboxInitEggs;
private: System::Windows::Forms::ErrorProvider^  errproContainer;
private: ctrl::ScientificNotationTextBox^  snboxWatershed;
private: ctrl::ScientificNotationTextBox^  snboxHeight;
private: ctrl::ScientificNotationTextBox^  snboxWidth;
private: ctrl::ScientificNotationTextBox^  snboxLength;
private: ctrl::ScientificNotationTextBox^  snboxDiameter;
private: ctrl::ScientificNotationTextBox^  snboxDensity;
private: ctrl::ScientificNotationTextBox^  snboxDrawdown;

private: ctrl::ScientificNotationTextBox^  snboxDecayRate;
private: ctrl::ScientificNotationTextBox^  snboxInitFood;
private: ctrl::ScientificNotationTextBox^  snboxDailyFood;
private: ctrl::ScientificNotationTextBox^  snboxFoodDec;

private: ctrl::ScientificNotationTextBox^  snboxFoodJun;
private: ctrl::ScientificNotationTextBox^  snboxFoodNov;


private: ctrl::ScientificNotationTextBox^  snboxFoodMay;
private: ctrl::ScientificNotationTextBox^  snboxFoodOct;


private: ctrl::ScientificNotationTextBox^  snboxFoodApr;
private: ctrl::ScientificNotationTextBox^  snboxFoodSep;


private: ctrl::ScientificNotationTextBox^  snboxFoodMar;
private: ctrl::ScientificNotationTextBox^  snboxFoodAug;


private: ctrl::ScientificNotationTextBox^  snboxFoodFeb;
private: ctrl::ScientificNotationTextBox^  snboxFoodJul;

private: ctrl::ScientificNotationTextBox^  snboxFoodJan;
private: System::Windows::Forms::CheckBox^  chkClone;
private: ctrl::ScientificNotationTextBox^  snboxNumberOfClones;







private: System::ComponentModel::IContainer^  components;




#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->components = (gcnew System::ComponentModel::Container());
      this->lblName = (gcnew System::Windows::Forms::Label());
      this->tboxName = (gcnew System::Windows::Forms::TextBox());
      this->lblShape = (gcnew System::Windows::Forms::Label());
      this->radRect = (gcnew System::Windows::Forms::RadioButton());
      this->radCirc = (gcnew System::Windows::Forms::RadioButton());
      this->lblLength = (gcnew System::Windows::Forms::Label());
      this->lblWidth = (gcnew System::Windows::Forms::Label());
      this->lblHeight = (gcnew System::Windows::Forms::Label());
      this->lblDiameter = (gcnew System::Windows::Forms::Label());
      this->lblDensity = (gcnew System::Windows::Forms::Label());
      this->lblMonthlyTurnover = (gcnew System::Windows::Forms::Label());
      this->lblSunExp = (gcnew System::Windows::Forms::Label());
      this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
      this->tabShapeSize = (gcnew System::Windows::Forms::TabPage());
      this->snboxHeight = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxWidth = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxLength = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxDiameter = (gcnew ctrl::ScientificNotationTextBox());
      this->tabConditions = (gcnew System::Windows::Forms::TabPage());
      this->snboxCoverReduction = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxCooling = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxSunExp = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxInitEggs = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxMonthlyTurnover = (gcnew ctrl::ScientificNotationTextBox());
      this->lblCoverReduction = (gcnew System::Windows::Forms::Label());
      this->chkCover = (gcnew System::Windows::Forms::CheckBox());
      this->lblInitEggs = (gcnew System::Windows::Forms::Label());
      this->lblCooling = (gcnew System::Windows::Forms::Label());
      this->tabWater = (gcnew System::Windows::Forms::TabPage());
      this->snboxDrawdown = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxWatershed = (gcnew ctrl::ScientificNotationTextBox());
      this->lblDrawdownFrequency = (gcnew System::Windows::Forms::Label());
      this->lblManualFillFrequency = (gcnew System::Windows::Forms::Label());
      this->cboxDrawdownFrequency = (gcnew System::Windows::Forms::ComboBox());
      this->lblDrawdown = (gcnew System::Windows::Forms::Label());
      this->cboxManualFillFrequency = (gcnew System::Windows::Forms::ComboBox());
      this->lblWatershed = (gcnew System::Windows::Forms::Label());
      this->cboxFillMethod = (gcnew System::Windows::Forms::ComboBox());
      this->lblFillMethod = (gcnew System::Windows::Forms::Label());
      this->tabFood = (gcnew System::Windows::Forms::TabPage());
      this->snboxFoodDec = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxFoodJun = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxFoodNov = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxFoodMay = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxFoodOct = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxFoodApr = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxFoodSep = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxFoodMar = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxFoodAug = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxFoodFeb = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxFoodJul = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxFoodJan = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxDailyFood = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxDecayRate = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxInitFood = (gcnew ctrl::ScientificNotationTextBox());
      this->lblDailyFood = (gcnew System::Windows::Forms::Label());
      this->btnCopyFood = (gcnew System::Windows::Forms::Button());
      this->lblFoodAdd = (gcnew System::Windows::Forms::Label());
      this->lblFoodDec = (gcnew System::Windows::Forms::Label());
      this->lblFoodJun = (gcnew System::Windows::Forms::Label());
      this->lblFoodSep = (gcnew System::Windows::Forms::Label());
      this->lblFoodMar = (gcnew System::Windows::Forms::Label());
      this->lblFoodNov = (gcnew System::Windows::Forms::Label());
      this->lblFoodMay = (gcnew System::Windows::Forms::Label());
      this->lblFoodAug = (gcnew System::Windows::Forms::Label());
      this->lblFoodFeb = (gcnew System::Windows::Forms::Label());
      this->lblFoodOct = (gcnew System::Windows::Forms::Label());
      this->lblFoodApr = (gcnew System::Windows::Forms::Label());
      this->lblFoodJul = (gcnew System::Windows::Forms::Label());
      this->lblFoodJan = (gcnew System::Windows::Forms::Label());
      this->lblFoodDecay = (gcnew System::Windows::Forms::Label());
      this->lblInitFoot = (gcnew System::Windows::Forms::Label());
      this->btnCancel = (gcnew System::Windows::Forms::Button());
      this->btnOk = (gcnew System::Windows::Forms::Button());
      this->errproContainer = (gcnew System::Windows::Forms::ErrorProvider(this->components));
      this->snboxDensity = (gcnew ctrl::ScientificNotationTextBox());
      this->chkClone = (gcnew System::Windows::Forms::CheckBox());
      this->snboxNumberOfClones = (gcnew ctrl::ScientificNotationTextBox());
      this->tabControl1->SuspendLayout();
      this->tabShapeSize->SuspendLayout();
      this->tabConditions->SuspendLayout();
      this->tabWater->SuspendLayout();
      this->tabFood->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errproContainer))->BeginInit();
      this->SuspendLayout();
      // 
      // lblName
      // 
      this->lblName->AutoSize = true;
      this->lblName->Location = System::Drawing::Point(50, 15);
      this->lblName->Name = L"lblName";
      this->lblName->Size = System::Drawing::Size(38, 13);
      this->lblName->TabIndex = 0;
      this->lblName->Text = L"Name:";
      // 
      // tboxName
      // 
      this->tboxName->Location = System::Drawing::Point(96, 12);
      this->tboxName->Name = L"tboxName";
      this->tboxName->Size = System::Drawing::Size(410, 20);
      this->tboxName->TabIndex = 1;
      // 
      // lblShape
      // 
      this->lblShape->AutoSize = true;
      this->lblShape->Location = System::Drawing::Point(148, 27);
      this->lblShape->Name = L"lblShape";
      this->lblShape->Size = System::Drawing::Size(41, 13);
      this->lblShape->TabIndex = 0;
      this->lblShape->Text = L"Shape:";
      // 
      // radRect
      // 
      this->radRect->AutoSize = true;
      this->radRect->Checked = true;
      this->radRect->Location = System::Drawing::Point(195, 25);
      this->radRect->Name = L"radRect";
      this->radRect->Size = System::Drawing::Size(83, 17);
      this->radRect->TabIndex = 1;
      this->radRect->TabStop = true;
      this->radRect->Text = L"Rectangular";
      this->radRect->UseVisualStyleBackColor = true;
      this->radRect->CheckedChanged += gcnew System::EventHandler(this, &ContainerForm::OnShapeChanged);
      // 
      // radCirc
      // 
      this->radCirc->AutoSize = true;
      this->radCirc->Location = System::Drawing::Point(284, 25);
      this->radCirc->Name = L"radCirc";
      this->radCirc->Size = System::Drawing::Size(60, 17);
      this->radCirc->TabIndex = 2;
      this->radCirc->Text = L"Circular";
      this->radCirc->UseVisualStyleBackColor = true;
      this->radCirc->CheckedChanged += gcnew System::EventHandler(this, &ContainerForm::OnShapeChanged);
      // 
      // lblLength
      // 
      this->lblLength->AutoSize = true;
      this->lblLength->Location = System::Drawing::Point(138, 51);
      this->lblLength->Name = L"lblLength";
      this->lblLength->Size = System::Drawing::Size(66, 13);
      this->lblLength->TabIndex = 3;
      this->lblLength->Text = L"Length (cm):";
      // 
      // lblWidth
      // 
      this->lblWidth->AutoSize = true;
      this->lblWidth->Location = System::Drawing::Point(143, 77);
      this->lblWidth->Name = L"lblWidth";
      this->lblWidth->Size = System::Drawing::Size(61, 13);
      this->lblWidth->TabIndex = 7;
      this->lblWidth->Text = L"Width (cm):";
      // 
      // lblHeight
      // 
      this->lblHeight->AutoSize = true;
      this->lblHeight->Location = System::Drawing::Point(140, 103);
      this->lblHeight->Name = L"lblHeight";
      this->lblHeight->Size = System::Drawing::Size(64, 13);
      this->lblHeight->TabIndex = 9;
      this->lblHeight->Text = L"Height (cm):";
      // 
      // lblDiameter
      // 
      this->lblDiameter->AutoSize = true;
      this->lblDiameter->Location = System::Drawing::Point(129, 51);
      this->lblDiameter->Name = L"lblDiameter";
      this->lblDiameter->Size = System::Drawing::Size(75, 13);
      this->lblDiameter->TabIndex = 5;
      this->lblDiameter->Text = L"Diameter (cm):";
      // 
      // lblDensity
      // 
      this->lblDensity->AutoSize = true;
      this->lblDensity->Location = System::Drawing::Point(12, 41);
      this->lblDensity->Name = L"lblDensity";
      this->lblDensity->Size = System::Drawing::Size(78, 13);
      this->lblDensity->TabIndex = 2;
      this->lblDensity->Text = L"Density (#/ha):";
      // 
      // lblMonthlyTurnover
      // 
      this->lblMonthlyTurnover->AutoSize = true;
      this->lblMonthlyTurnover->Location = System::Drawing::Point(111, 24);
      this->lblMonthlyTurnover->Name = L"lblMonthlyTurnover";
      this->lblMonthlyTurnover->Size = System::Drawing::Size(93, 13);
      this->lblMonthlyTurnover->TabIndex = 0;
      this->lblMonthlyTurnover->Text = L"Monthly Turnover:";
      // 
      // lblSunExp
      // 
      this->lblSunExp->AutoSize = true;
      this->lblSunExp->Location = System::Drawing::Point(128, 86);
      this->lblSunExp->Name = L"lblSunExp";
      this->lblSunExp->Size = System::Drawing::Size(76, 13);
      this->lblSunExp->TabIndex = 4;
      this->lblSunExp->Text = L"Sun Exposure:";
      // 
      // tabControl1
      // 
      this->tabControl1->Controls->Add(this->tabShapeSize);
      this->tabControl1->Controls->Add(this->tabConditions);
      this->tabControl1->Controls->Add(this->tabWater);
      this->tabControl1->Controls->Add(this->tabFood);
      this->tabControl1->Location = System::Drawing::Point(12, 76);
      this->tabControl1->Name = L"tabControl1";
      this->tabControl1->SelectedIndex = 0;
      this->tabControl1->Size = System::Drawing::Size(498, 231);
      this->tabControl1->TabIndex = 6;
      // 
      // tabShapeSize
      // 
      this->tabShapeSize->Controls->Add(this->snboxHeight);
      this->tabShapeSize->Controls->Add(this->snboxWidth);
      this->tabShapeSize->Controls->Add(this->lblShape);
      this->tabShapeSize->Controls->Add(this->lblLength);
      this->tabShapeSize->Controls->Add(this->lblWidth);
      this->tabShapeSize->Controls->Add(this->lblHeight);
      this->tabShapeSize->Controls->Add(this->lblDiameter);
      this->tabShapeSize->Controls->Add(this->radRect);
      this->tabShapeSize->Controls->Add(this->radCirc);
      this->tabShapeSize->Controls->Add(this->snboxLength);
      this->tabShapeSize->Controls->Add(this->snboxDiameter);
      this->tabShapeSize->Location = System::Drawing::Point(4, 22);
      this->tabShapeSize->Name = L"tabShapeSize";
      this->tabShapeSize->Padding = System::Windows::Forms::Padding(3);
      this->tabShapeSize->Size = System::Drawing::Size(490, 205);
      this->tabShapeSize->TabIndex = 0;
      this->tabShapeSize->Text = L"Shape & Size";
      this->tabShapeSize->UseVisualStyleBackColor = true;
      // 
      // snboxHeight
      // 
      this->snboxHeight->Location = System::Drawing::Point(210, 100);
      this->snboxHeight->Name = L"snboxHeight";
      this->snboxHeight->Size = System::Drawing::Size(68, 20);
      this->snboxHeight->TabIndex = 10;
      this->snboxHeight->Text = L"0";
      this->snboxHeight->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxHeight->Value = L"0";
      // 
      // snboxWidth
      // 
      this->snboxWidth->Location = System::Drawing::Point(210, 74);
      this->snboxWidth->Name = L"snboxWidth";
      this->snboxWidth->Size = System::Drawing::Size(68, 20);
      this->snboxWidth->TabIndex = 8;
      this->snboxWidth->Text = L"0";
      this->snboxWidth->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxWidth->Value = L"0";
      // 
      // snboxLength
      // 
      this->snboxLength->Location = System::Drawing::Point(210, 48);
      this->snboxLength->Name = L"snboxLength";
      this->snboxLength->Size = System::Drawing::Size(68, 20);
      this->snboxLength->TabIndex = 4;
      this->snboxLength->Text = L"0";
      this->snboxLength->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxLength->Value = L"0";
      // 
      // snboxDiameter
      // 
      this->snboxDiameter->Location = System::Drawing::Point(210, 48);
      this->snboxDiameter->Name = L"snboxDiameter";
      this->snboxDiameter->Size = System::Drawing::Size(68, 20);
      this->snboxDiameter->TabIndex = 6;
      this->snboxDiameter->Text = L"0";
      this->snboxDiameter->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxDiameter->Value = L"0";
      // 
      // tabConditions
      // 
      this->tabConditions->Controls->Add(this->snboxCoverReduction);
      this->tabConditions->Controls->Add(this->snboxCooling);
      this->tabConditions->Controls->Add(this->snboxSunExp);
      this->tabConditions->Controls->Add(this->snboxInitEggs);
      this->tabConditions->Controls->Add(this->snboxMonthlyTurnover);
      this->tabConditions->Controls->Add(this->lblCoverReduction);
      this->tabConditions->Controls->Add(this->chkCover);
      this->tabConditions->Controls->Add(this->lblMonthlyTurnover);
      this->tabConditions->Controls->Add(this->lblInitEggs);
      this->tabConditions->Controls->Add(this->lblCooling);
      this->tabConditions->Controls->Add(this->lblSunExp);
      this->tabConditions->Location = System::Drawing::Point(4, 22);
      this->tabConditions->Name = L"tabConditions";
      this->tabConditions->Padding = System::Windows::Forms::Padding(3);
      this->tabConditions->Size = System::Drawing::Size(490, 205);
      this->tabConditions->TabIndex = 1;
      this->tabConditions->Text = L"Conditions";
      this->tabConditions->UseVisualStyleBackColor = true;
      // 
      // snboxCoverReduction
      // 
      this->snboxCoverReduction->Location = System::Drawing::Point(210, 171);
      this->snboxCoverReduction->Name = L"snboxCoverReduction";
      this->snboxCoverReduction->Size = System::Drawing::Size(68, 20);
      this->snboxCoverReduction->TabIndex = 10;
      this->snboxCoverReduction->Text = L"0";
      this->snboxCoverReduction->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxCoverReduction->Value = L"0";
      // 
      // snboxCooling
      // 
      this->snboxCooling->Location = System::Drawing::Point(210, 109);
      this->snboxCooling->Name = L"snboxCooling";
      this->snboxCooling->Size = System::Drawing::Size(68, 20);
      this->snboxCooling->TabIndex = 7;
      this->snboxCooling->Text = L"0";
      this->snboxCooling->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxCooling->Value = L"0";
      // 
      // snboxSunExp
      // 
      this->snboxSunExp->Location = System::Drawing::Point(210, 83);
      this->snboxSunExp->Name = L"snboxSunExp";
      this->snboxSunExp->Size = System::Drawing::Size(68, 20);
      this->snboxSunExp->TabIndex = 5;
      this->snboxSunExp->Text = L"0";
      this->snboxSunExp->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxSunExp->Value = L"0";
      // 
      // snboxInitEggs
      // 
      this->snboxInitEggs->Location = System::Drawing::Point(210, 47);
      this->snboxInitEggs->Name = L"snboxInitEggs";
      this->snboxInitEggs->Size = System::Drawing::Size(68, 20);
      this->snboxInitEggs->TabIndex = 3;
      this->snboxInitEggs->Text = L"0";
      this->snboxInitEggs->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxInitEggs->Value = L"0";
      // 
      // snboxMonthlyTurnover
      // 
      this->snboxMonthlyTurnover->Location = System::Drawing::Point(210, 21);
      this->snboxMonthlyTurnover->Name = L"snboxMonthlyTurnover";
      this->snboxMonthlyTurnover->Size = System::Drawing::Size(68, 20);
      this->snboxMonthlyTurnover->TabIndex = 1;
      this->snboxMonthlyTurnover->Text = L"0";
      this->snboxMonthlyTurnover->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxMonthlyTurnover->Value = L"0";
      // 
      // lblCoverReduction
      // 
      this->lblCoverReduction->AutoSize = true;
      this->lblCoverReduction->Location = System::Drawing::Point(22, 174);
      this->lblCoverReduction->Name = L"lblCoverReduction";
      this->lblCoverReduction->Size = System::Drawing::Size(182, 13);
      this->lblCoverReduction->TabIndex = 9;
      this->lblCoverReduction->Text = L"Reduction in evaporation from cover:";
      // 
      // chkCover
      // 
      this->chkCover->AutoSize = true;
      this->chkCover->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
      this->chkCover->Location = System::Drawing::Point(155, 148);
      this->chkCover->Name = L"chkCover";
      this->chkCover->Size = System::Drawing::Size(69, 17);
      this->chkCover->TabIndex = 8;
      this->chkCover->Text = L"Covered:";
      this->chkCover->UseVisualStyleBackColor = true;
      // 
      // lblInitEggs
      // 
      this->lblInitEggs->AutoSize = true;
      this->lblInitEggs->Location = System::Drawing::Point(143, 50);
      this->lblInitEggs->Name = L"lblInitEggs";
      this->lblInitEggs->Size = System::Drawing::Size(61, 13);
      this->lblInitEggs->TabIndex = 2;
      this->lblInitEggs->Text = L"Initial Eggs:";
      // 
      // lblCooling
      // 
      this->lblCooling->AutoSize = true;
      this->lblCooling->Location = System::Drawing::Point(58, 112);
      this->lblCooling->Name = L"lblCooling";
      this->lblCooling->Size = System::Drawing::Size(146, 13);
      this->lblCooling->TabIndex = 6;
      this->lblCooling->Text = L"Cooling effect of evaporation:";
      // 
      // tabWater
      // 
      this->tabWater->Controls->Add(this->snboxDrawdown);
      this->tabWater->Controls->Add(this->snboxWatershed);
      this->tabWater->Controls->Add(this->lblDrawdownFrequency);
      this->tabWater->Controls->Add(this->lblManualFillFrequency);
      this->tabWater->Controls->Add(this->cboxDrawdownFrequency);
      this->tabWater->Controls->Add(this->lblDrawdown);
      this->tabWater->Controls->Add(this->cboxManualFillFrequency);
      this->tabWater->Controls->Add(this->lblWatershed);
      this->tabWater->Controls->Add(this->cboxFillMethod);
      this->tabWater->Controls->Add(this->lblFillMethod);
      this->tabWater->Location = System::Drawing::Point(4, 22);
      this->tabWater->Name = L"tabWater";
      this->tabWater->Padding = System::Windows::Forms::Padding(3);
      this->tabWater->Size = System::Drawing::Size(490, 205);
      this->tabWater->TabIndex = 3;
      this->tabWater->Text = L"Water & Filling";
      this->tabWater->UseVisualStyleBackColor = true;
      // 
      // snboxDrawdown
      // 
      this->snboxDrawdown->Location = System::Drawing::Point(210, 119);
      this->snboxDrawdown->Name = L"snboxDrawdown";
      this->snboxDrawdown->Size = System::Drawing::Size(68, 20);
      this->snboxDrawdown->TabIndex = 7;
      this->snboxDrawdown->Text = L"0";
      this->snboxDrawdown->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxDrawdown->Value = L"0";
      // 
      // snboxWatershed
      // 
      this->snboxWatershed->Location = System::Drawing::Point(210, 49);
      this->snboxWatershed->Name = L"snboxWatershed";
      this->snboxWatershed->Size = System::Drawing::Size(68, 20);
      this->snboxWatershed->TabIndex = 3;
      this->snboxWatershed->Text = L"0";
      this->snboxWatershed->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxWatershed->Value = L"0";
      // 
      // lblDrawdownFrequency
      // 
      this->lblDrawdownFrequency->AutoSize = true;
      this->lblDrawdownFrequency->Location = System::Drawing::Point(90, 148);
      this->lblDrawdownFrequency->Name = L"lblDrawdownFrequency";
      this->lblDrawdownFrequency->Size = System::Drawing::Size(114, 13);
      this->lblDrawdownFrequency->TabIndex = 8;
      this->lblDrawdownFrequency->Text = L"Drawdown Frequency:";
      // 
      // lblManualFillFrequency
      // 
      this->lblManualFillFrequency->AutoSize = true;
      this->lblManualFillFrequency->Location = System::Drawing::Point(91, 78);
      this->lblManualFillFrequency->Name = L"lblManualFillFrequency";
      this->lblManualFillFrequency->Size = System::Drawing::Size(113, 13);
      this->lblManualFillFrequency->TabIndex = 4;
      this->lblManualFillFrequency->Text = L"Manual Fill Frequency:";
      // 
      // cboxDrawdownFrequency
      // 
      this->cboxDrawdownFrequency->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxDrawdownFrequency->FormattingEnabled = true;
      this->cboxDrawdownFrequency->Location = System::Drawing::Point(210, 145);
      this->cboxDrawdownFrequency->Name = L"cboxDrawdownFrequency";
      this->cboxDrawdownFrequency->Size = System::Drawing::Size(121, 21);
      this->cboxDrawdownFrequency->TabIndex = 9;
      // 
      // lblDrawdown
      // 
      this->lblDrawdown->AutoSize = true;
      this->lblDrawdown->Location = System::Drawing::Point(74, 122);
      this->lblDrawdown->Name = L"lblDrawdown";
      this->lblDrawdown->Size = System::Drawing::Size(130, 13);
      this->lblDrawdown->TabIndex = 6;
      this->lblDrawdown->Text = L"Drawdown Amount (liters):";
      // 
      // cboxManualFillFrequency
      // 
      this->cboxManualFillFrequency->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxManualFillFrequency->FormattingEnabled = true;
      this->cboxManualFillFrequency->Location = System::Drawing::Point(210, 75);
      this->cboxManualFillFrequency->Name = L"cboxManualFillFrequency";
      this->cboxManualFillFrequency->Size = System::Drawing::Size(121, 21);
      this->cboxManualFillFrequency->TabIndex = 5;
      // 
      // lblWatershed
      // 
      this->lblWatershed->AutoSize = true;
      this->lblWatershed->Location = System::Drawing::Point(114, 52);
      this->lblWatershed->Name = L"lblWatershed";
      this->lblWatershed->Size = System::Drawing::Size(90, 13);
      this->lblWatershed->TabIndex = 2;
      this->lblWatershed->Text = L"Watershed Ratio:";
      // 
      // cboxFillMethod
      // 
      this->cboxFillMethod->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxFillMethod->FormattingEnabled = true;
      this->cboxFillMethod->Location = System::Drawing::Point(210, 22);
      this->cboxFillMethod->Name = L"cboxFillMethod";
      this->cboxFillMethod->Size = System::Drawing::Size(121, 21);
      this->cboxFillMethod->TabIndex = 1;
      this->cboxFillMethod->SelectedValueChanged += gcnew System::EventHandler(this, &ContainerForm::OnFillMethodChanged);
      // 
      // lblFillMethod
      // 
      this->lblFillMethod->AutoSize = true;
      this->lblFillMethod->Location = System::Drawing::Point(143, 25);
      this->lblFillMethod->Name = L"lblFillMethod";
      this->lblFillMethod->Size = System::Drawing::Size(61, 13);
      this->lblFillMethod->TabIndex = 0;
      this->lblFillMethod->Text = L"Fill Method:";
      // 
      // tabFood
      // 
      this->tabFood->Controls->Add(this->snboxFoodDec);
      this->tabFood->Controls->Add(this->snboxFoodJun);
      this->tabFood->Controls->Add(this->snboxFoodNov);
      this->tabFood->Controls->Add(this->snboxFoodMay);
      this->tabFood->Controls->Add(this->snboxFoodOct);
      this->tabFood->Controls->Add(this->snboxFoodApr);
      this->tabFood->Controls->Add(this->snboxFoodSep);
      this->tabFood->Controls->Add(this->snboxFoodMar);
      this->tabFood->Controls->Add(this->snboxFoodAug);
      this->tabFood->Controls->Add(this->snboxFoodFeb);
      this->tabFood->Controls->Add(this->snboxFoodJul);
      this->tabFood->Controls->Add(this->snboxFoodJan);
      this->tabFood->Controls->Add(this->snboxDailyFood);
      this->tabFood->Controls->Add(this->snboxDecayRate);
      this->tabFood->Controls->Add(this->snboxInitFood);
      this->tabFood->Controls->Add(this->lblDailyFood);
      this->tabFood->Controls->Add(this->btnCopyFood);
      this->tabFood->Controls->Add(this->lblFoodAdd);
      this->tabFood->Controls->Add(this->lblFoodDec);
      this->tabFood->Controls->Add(this->lblFoodJun);
      this->tabFood->Controls->Add(this->lblFoodSep);
      this->tabFood->Controls->Add(this->lblFoodMar);
      this->tabFood->Controls->Add(this->lblFoodNov);
      this->tabFood->Controls->Add(this->lblFoodMay);
      this->tabFood->Controls->Add(this->lblFoodAug);
      this->tabFood->Controls->Add(this->lblFoodFeb);
      this->tabFood->Controls->Add(this->lblFoodOct);
      this->tabFood->Controls->Add(this->lblFoodApr);
      this->tabFood->Controls->Add(this->lblFoodJul);
      this->tabFood->Controls->Add(this->lblFoodJan);
      this->tabFood->Controls->Add(this->lblFoodDecay);
      this->tabFood->Controls->Add(this->lblInitFoot);
      this->tabFood->Location = System::Drawing::Point(4, 22);
      this->tabFood->Name = L"tabFood";
      this->tabFood->Size = System::Drawing::Size(490, 205);
      this->tabFood->TabIndex = 2;
      this->tabFood->Text = L"Food";
      this->tabFood->UseVisualStyleBackColor = true;
      // 
      // snboxFoodDec
      // 
      this->snboxFoodDec->Location = System::Drawing::Point(399, 167);
      this->snboxFoodDec->Name = L"snboxFoodDec";
      this->snboxFoodDec->Size = System::Drawing::Size(68, 20);
      this->snboxFoodDec->TabIndex = 31;
      this->snboxFoodDec->Text = L"0";
      this->snboxFoodDec->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxFoodDec->Value = L"0";
      // 
      // snboxFoodJun
      // 
      this->snboxFoodJun->Location = System::Drawing::Point(293, 167);
      this->snboxFoodJun->Name = L"snboxFoodJun";
      this->snboxFoodJun->Size = System::Drawing::Size(68, 20);
      this->snboxFoodJun->TabIndex = 19;
      this->snboxFoodJun->Text = L"0";
      this->snboxFoodJun->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxFoodJun->Value = L"0";
      // 
      // snboxFoodNov
      // 
      this->snboxFoodNov->Location = System::Drawing::Point(399, 141);
      this->snboxFoodNov->Name = L"snboxFoodNov";
      this->snboxFoodNov->Size = System::Drawing::Size(68, 20);
      this->snboxFoodNov->TabIndex = 29;
      this->snboxFoodNov->Text = L"0";
      this->snboxFoodNov->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxFoodNov->Value = L"0";
      // 
      // snboxFoodMay
      // 
      this->snboxFoodMay->Location = System::Drawing::Point(293, 141);
      this->snboxFoodMay->Name = L"snboxFoodMay";
      this->snboxFoodMay->Size = System::Drawing::Size(68, 20);
      this->snboxFoodMay->TabIndex = 17;
      this->snboxFoodMay->Text = L"0";
      this->snboxFoodMay->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxFoodMay->Value = L"0";
      // 
      // snboxFoodOct
      // 
      this->snboxFoodOct->Location = System::Drawing::Point(399, 115);
      this->snboxFoodOct->Name = L"snboxFoodOct";
      this->snboxFoodOct->Size = System::Drawing::Size(68, 20);
      this->snboxFoodOct->TabIndex = 27;
      this->snboxFoodOct->Text = L"0";
      this->snboxFoodOct->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxFoodOct->Value = L"0";
      // 
      // snboxFoodApr
      // 
      this->snboxFoodApr->Location = System::Drawing::Point(293, 115);
      this->snboxFoodApr->Name = L"snboxFoodApr";
      this->snboxFoodApr->Size = System::Drawing::Size(68, 20);
      this->snboxFoodApr->TabIndex = 15;
      this->snboxFoodApr->Text = L"0";
      this->snboxFoodApr->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxFoodApr->Value = L"0";
      // 
      // snboxFoodSep
      // 
      this->snboxFoodSep->Location = System::Drawing::Point(399, 89);
      this->snboxFoodSep->Name = L"snboxFoodSep";
      this->snboxFoodSep->Size = System::Drawing::Size(68, 20);
      this->snboxFoodSep->TabIndex = 25;
      this->snboxFoodSep->Text = L"0";
      this->snboxFoodSep->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxFoodSep->Value = L"0";
      // 
      // snboxFoodMar
      // 
      this->snboxFoodMar->Location = System::Drawing::Point(293, 89);
      this->snboxFoodMar->Name = L"snboxFoodMar";
      this->snboxFoodMar->Size = System::Drawing::Size(68, 20);
      this->snboxFoodMar->TabIndex = 13;
      this->snboxFoodMar->Text = L"0";
      this->snboxFoodMar->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxFoodMar->Value = L"0";
      // 
      // snboxFoodAug
      // 
      this->snboxFoodAug->Location = System::Drawing::Point(399, 63);
      this->snboxFoodAug->Name = L"snboxFoodAug";
      this->snboxFoodAug->Size = System::Drawing::Size(68, 20);
      this->snboxFoodAug->TabIndex = 23;
      this->snboxFoodAug->Text = L"0";
      this->snboxFoodAug->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxFoodAug->Value = L"0";
      // 
      // snboxFoodFeb
      // 
      this->snboxFoodFeb->Location = System::Drawing::Point(293, 63);
      this->snboxFoodFeb->Name = L"snboxFoodFeb";
      this->snboxFoodFeb->Size = System::Drawing::Size(68, 20);
      this->snboxFoodFeb->TabIndex = 11;
      this->snboxFoodFeb->Text = L"0";
      this->snboxFoodFeb->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxFoodFeb->Value = L"0";
      // 
      // snboxFoodJul
      // 
      this->snboxFoodJul->Location = System::Drawing::Point(399, 37);
      this->snboxFoodJul->Name = L"snboxFoodJul";
      this->snboxFoodJul->Size = System::Drawing::Size(68, 20);
      this->snboxFoodJul->TabIndex = 21;
      this->snboxFoodJul->Text = L"0";
      this->snboxFoodJul->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxFoodJul->Value = L"0";
      // 
      // snboxFoodJan
      // 
      this->snboxFoodJan->Location = System::Drawing::Point(293, 37);
      this->snboxFoodJan->Name = L"snboxFoodJan";
      this->snboxFoodJan->Size = System::Drawing::Size(68, 20);
      this->snboxFoodJan->TabIndex = 9;
      this->snboxFoodJan->Text = L"0";
      this->snboxFoodJan->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxFoodJan->Value = L"0";
      // 
      // snboxDailyFood
      // 
      this->snboxDailyFood->Location = System::Drawing::Point(109, 168);
      this->snboxDailyFood->Name = L"snboxDailyFood";
      this->snboxDailyFood->Size = System::Drawing::Size(68, 20);
      this->snboxDailyFood->TabIndex = 5;
      this->snboxDailyFood->Text = L"0";
      this->snboxDailyFood->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxDailyFood->Value = L"0";
      // 
      // snboxDecayRate
      // 
      this->snboxDecayRate->Location = System::Drawing::Point(109, 64);
      this->snboxDecayRate->Name = L"snboxDecayRate";
      this->snboxDecayRate->Size = System::Drawing::Size(68, 20);
      this->snboxDecayRate->TabIndex = 3;
      this->snboxDecayRate->Text = L"0";
      this->snboxDecayRate->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxDecayRate->Value = L"0";
      // 
      // snboxInitFood
      // 
      this->snboxInitFood->Location = System::Drawing::Point(109, 38);
      this->snboxInitFood->Name = L"snboxInitFood";
      this->snboxInitFood->Size = System::Drawing::Size(68, 20);
      this->snboxInitFood->TabIndex = 1;
      this->snboxInitFood->Text = L"0";
      this->snboxInitFood->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxInitFood->Value = L"0";
      // 
      // lblDailyFood
      // 
      this->lblDailyFood->AutoSize = true;
      this->lblDailyFood->Location = System::Drawing::Point(4, 171);
      this->lblDailyFood->Name = L"lblDailyFood";
      this->lblDailyFood->Size = System::Drawing::Size(99, 13);
      this->lblDailyFood->TabIndex = 4;
      this->lblDailyFood->Text = L"Set monthly values:";
      // 
      // btnCopyFood
      // 
      this->btnCopyFood->Location = System::Drawing::Point(197, 168);
      this->btnCopyFood->Name = L"btnCopyFood";
      this->btnCopyFood->Size = System::Drawing::Size(55, 20);
      this->btnCopyFood->TabIndex = 6;
      this->btnCopyFood->Text = L"copy >>";
      this->btnCopyFood->UseVisualStyleBackColor = true;
      this->btnCopyFood->Click += gcnew System::EventHandler(this, &ContainerForm::OnCopyFood);
      // 
      // lblFoodAdd
      // 
      this->lblFoodAdd->AutoSize = true;
      this->lblFoodAdd->Location = System::Drawing::Point(308, 12);
      this->lblFoodAdd->Name = L"lblFoodAdd";
      this->lblFoodAdd->Size = System::Drawing::Size(126, 13);
      this->lblFoodAdd->TabIndex = 7;
      this->lblFoodAdd->Text = L"Daily Additions by Month:";
      // 
      // lblFoodDec
      // 
      this->lblFoodDec->AutoSize = true;
      this->lblFoodDec->Location = System::Drawing::Point(363, 170);
      this->lblFoodDec->Name = L"lblFoodDec";
      this->lblFoodDec->Size = System::Drawing::Size(30, 13);
      this->lblFoodDec->TabIndex = 30;
      this->lblFoodDec->Text = L"Dec:";
      // 
      // lblFoodJun
      // 
      this->lblFoodJun->AutoSize = true;
      this->lblFoodJun->Location = System::Drawing::Point(260, 170);
      this->lblFoodJun->Name = L"lblFoodJun";
      this->lblFoodJun->Size = System::Drawing::Size(27, 13);
      this->lblFoodJun->TabIndex = 18;
      this->lblFoodJun->Text = L"Jun:";
      // 
      // lblFoodSep
      // 
      this->lblFoodSep->AutoSize = true;
      this->lblFoodSep->Location = System::Drawing::Point(364, 92);
      this->lblFoodSep->Name = L"lblFoodSep";
      this->lblFoodSep->Size = System::Drawing::Size(29, 13);
      this->lblFoodSep->TabIndex = 24;
      this->lblFoodSep->Text = L"Sep:";
      // 
      // lblFoodMar
      // 
      this->lblFoodMar->AutoSize = true;
      this->lblFoodMar->Location = System::Drawing::Point(259, 92);
      this->lblFoodMar->Name = L"lblFoodMar";
      this->lblFoodMar->Size = System::Drawing::Size(28, 13);
      this->lblFoodMar->TabIndex = 12;
      this->lblFoodMar->Text = L"Mar:";
      // 
      // lblFoodNov
      // 
      this->lblFoodNov->AutoSize = true;
      this->lblFoodNov->Location = System::Drawing::Point(363, 144);
      this->lblFoodNov->Name = L"lblFoodNov";
      this->lblFoodNov->Size = System::Drawing::Size(30, 13);
      this->lblFoodNov->TabIndex = 28;
      this->lblFoodNov->Text = L"Nov:";
      // 
      // lblFoodMay
      // 
      this->lblFoodMay->AutoSize = true;
      this->lblFoodMay->Location = System::Drawing::Point(257, 144);
      this->lblFoodMay->Name = L"lblFoodMay";
      this->lblFoodMay->Size = System::Drawing::Size(30, 13);
      this->lblFoodMay->TabIndex = 16;
      this->lblFoodMay->Text = L"May:";
      // 
      // lblFoodAug
      // 
      this->lblFoodAug->AutoSize = true;
      this->lblFoodAug->Location = System::Drawing::Point(364, 66);
      this->lblFoodAug->Name = L"lblFoodAug";
      this->lblFoodAug->Size = System::Drawing::Size(29, 13);
      this->lblFoodAug->TabIndex = 22;
      this->lblFoodAug->Text = L"Aug:";
      // 
      // lblFoodFeb
      // 
      this->lblFoodFeb->AutoSize = true;
      this->lblFoodFeb->Location = System::Drawing::Point(259, 66);
      this->lblFoodFeb->Name = L"lblFoodFeb";
      this->lblFoodFeb->Size = System::Drawing::Size(28, 13);
      this->lblFoodFeb->TabIndex = 10;
      this->lblFoodFeb->Text = L"Feb:";
      // 
      // lblFoodOct
      // 
      this->lblFoodOct->AutoSize = true;
      this->lblFoodOct->Location = System::Drawing::Point(366, 118);
      this->lblFoodOct->Name = L"lblFoodOct";
      this->lblFoodOct->Size = System::Drawing::Size(27, 13);
      this->lblFoodOct->TabIndex = 26;
      this->lblFoodOct->Text = L"Oct:";
      // 
      // lblFoodApr
      // 
      this->lblFoodApr->AutoSize = true;
      this->lblFoodApr->Location = System::Drawing::Point(261, 118);
      this->lblFoodApr->Name = L"lblFoodApr";
      this->lblFoodApr->Size = System::Drawing::Size(26, 13);
      this->lblFoodApr->TabIndex = 14;
      this->lblFoodApr->Text = L"Apr:";
      // 
      // lblFoodJul
      // 
      this->lblFoodJul->AutoSize = true;
      this->lblFoodJul->Location = System::Drawing::Point(370, 40);
      this->lblFoodJul->Name = L"lblFoodJul";
      this->lblFoodJul->Size = System::Drawing::Size(23, 13);
      this->lblFoodJul->TabIndex = 20;
      this->lblFoodJul->Text = L"Jul:";
      // 
      // lblFoodJan
      // 
      this->lblFoodJan->AutoSize = true;
      this->lblFoodJan->Location = System::Drawing::Point(260, 41);
      this->lblFoodJan->Name = L"lblFoodJan";
      this->lblFoodJan->Size = System::Drawing::Size(27, 13);
      this->lblFoodJan->TabIndex = 8;
      this->lblFoodJan->Text = L"Jan:";
      // 
      // lblFoodDecay
      // 
      this->lblFoodDecay->AutoSize = true;
      this->lblFoodDecay->Location = System::Drawing::Point(10, 66);
      this->lblFoodDecay->Name = L"lblFoodDecay";
      this->lblFoodDecay->Size = System::Drawing::Size(93, 13);
      this->lblFoodDecay->TabIndex = 2;
      this->lblFoodDecay->Text = L"Daily Decay Rate:";
      // 
      // lblInitFoot
      // 
      this->lblInitFoot->AutoSize = true;
      this->lblInitFoot->Location = System::Drawing::Point(42, 41);
      this->lblInitFoot->Name = L"lblInitFoot";
      this->lblInitFoot->Size = System::Drawing::Size(61, 13);
      this->lblInitFoot->TabIndex = 0;
      this->lblInitFoot->Text = L"Initial Food:";
      // 
      // btnCancel
      // 
      this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
      this->btnCancel->Location = System::Drawing::Point(435, 313);
      this->btnCancel->Name = L"btnCancel";
      this->btnCancel->Size = System::Drawing::Size(75, 23);
      this->btnCancel->TabIndex = 8;
      this->btnCancel->Text = L"Cancel";
      this->btnCancel->UseVisualStyleBackColor = true;
      this->btnCancel->Click += gcnew System::EventHandler(this, &ContainerForm::OnCancel);
      // 
      // btnOk
      // 
      this->btnOk->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->btnOk->Location = System::Drawing::Point(354, 313);
      this->btnOk->Name = L"btnOk";
      this->btnOk->Size = System::Drawing::Size(75, 23);
      this->btnOk->TabIndex = 7;
      this->btnOk->Text = L"OK";
      this->btnOk->UseVisualStyleBackColor = true;
      this->btnOk->Click += gcnew System::EventHandler(this, &ContainerForm::OnOk);
      // 
      // errproContainer
      // 
      this->errproContainer->BlinkRate = 100;
      this->errproContainer->ContainerControl = this;
      // 
      // snboxDensity
      // 
      this->snboxDensity->Location = System::Drawing::Point(96, 38);
      this->snboxDensity->Name = L"snboxDensity";
      this->snboxDensity->Size = System::Drawing::Size(68, 20);
      this->snboxDensity->TabIndex = 3;
      this->snboxDensity->Text = L"0";
      this->snboxDensity->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxDensity->Value = L"0";
      // 
      // chkClone
      // 
      this->chkClone->AutoSize = true;
      this->chkClone->Location = System::Drawing::Point(373, 40);
      this->chkClone->Name = L"chkClone";
      this->chkClone->Size = System::Drawing::Size(56, 17);
      this->chkClone->TabIndex = 4;
      this->chkClone->Text = L"Clone:";
      this->chkClone->UseVisualStyleBackColor = true;
      // 
      // snboxNumberOfClones
      // 
      this->snboxNumberOfClones->Location = System::Drawing::Point(435, 38);
      this->snboxNumberOfClones->Name = L"snboxNumberOfClones";
      this->snboxNumberOfClones->Size = System::Drawing::Size(68, 20);
      this->snboxNumberOfClones->TabIndex = 5;
      this->snboxNumberOfClones->Text = L"0";
      this->snboxNumberOfClones->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxNumberOfClones->Value = L"0";
      // 
      // ContainerForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(522, 346);
      this->Controls->Add(this->chkClone);
      this->Controls->Add(this->snboxDensity);
      this->Controls->Add(this->lblDensity);
      this->Controls->Add(this->btnOk);
      this->Controls->Add(this->snboxNumberOfClones);
      this->Controls->Add(this->btnCancel);
      this->Controls->Add(this->tabControl1);
      this->Controls->Add(this->tboxName);
      this->Controls->Add(this->lblName);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
      this->Name = L"ContainerForm";
      this->ShowInTaskbar = false;
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
      this->Text = L"ContainerForm";
      this->Load += gcnew System::EventHandler(this, &ContainerForm::OnLoad);
      this->tabControl1->ResumeLayout(false);
      this->tabShapeSize->ResumeLayout(false);
      this->tabShapeSize->PerformLayout();
      this->tabConditions->ResumeLayout(false);
      this->tabConditions->PerformLayout();
      this->tabWater->ResumeLayout(false);
      this->tabWater->PerformLayout();
      this->tabFood->ResumeLayout(false);
      this->tabFood->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errproContainer))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  };
}
