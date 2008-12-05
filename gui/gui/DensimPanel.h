#pragma once

#include "InfectionIntroductionForm.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace gui {


  public ref class DensimPanel : public System::Windows::Forms::UserControl
	{
	public:
    DensimPanel( BindingSource ^ locationBinding );
	protected:
		~DensimPanel();

  private:
    gui::Location ^ GetLocation(void);
    System::Void RunDensim(System::Void);

    System::Void OnLoad( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnRunDensim( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnTabPageSelecting( System::Object ^ sender, System::Windows::Forms::TabControlCancelEventArgs ^ e);

    System::Void OnDemographicsRowValidating( System::Object ^ sender, System::Windows::Forms::DataGridViewCellCancelEventArgs ^ e );

  private:
    BindingSource ^ LocationBinding;
    bool IsWeatherAvailable_;

  private: System::Windows::Forms::Button^  btnRunSim;
  private: System::Windows::Forms::TabControl^  tabDensim;

  private: System::Windows::Forms::TabPage^  tabDemographics;
  private: System::Windows::Forms::DataGridView^  dgvDemographics;

  private: System::Windows::Forms::Label^  lblHumHostDensity;



  private: System::Windows::Forms::TabPage^  tabSerology;
  private: System::Windows::Forms::DataGridView^  dgvSerology;
  private: System::Windows::Forms::Label^  lblManaDuration;
  private: System::Windows::Forms::Label^  lblMaeaDuration;
  private: System::Windows::Forms::Label^  lblHetDuration;




  private: System::Windows::Forms::TabPage^  tabVirology;
  private: System::Windows::Forms::TabControl^  tabInfectionEip;

  private: System::Windows::Forms::TabPage^  tabHumToMosInfection;
  private: System::Windows::Forms::TabPage^  tabEip;


  private: System::Windows::Forms::Label^  lblVirLowTiterSetPoint;

  private: System::Windows::Forms::Label^  lblVirLowInfection;

  private: System::Windows::Forms::Label^  lblVirHighTiterSetPoint;

  private: System::Windows::Forms::Label^  lblVirHighInfection;

  private: System::Windows::Forms::Label^  lblNomProbInfection;

  private: System::Windows::Forms::Label^  lbMosqCountStochastic;


  private: System::Windows::Forms::DataGridView^  dgvVirology;




  private: System::Windows::Forms::Label^  lblEipRo25;
  private: System::Windows::Forms::Label^  lblEipEnthInact;
  private: System::Windows::Forms::Label^  lblEipEnthAct;
  private: System::Windows::Forms::Label^  lblEipTempInact;













  private: System::Windows::Forms::TabPage^  tabInfections;
  private: gui::InfectionIntroductionForm ^ formInfectionIntroduction;

  private: System::Windows::Forms::TabPage^  tabDhsDss;
  private: System::Windows::Forms::DataGridView^  dgvSequentials;




























private: System::Windows::Forms::Label^  lblInitialPopulationSize;
private: ctrl::ScientificNotationTextBox^  snboxEipTempInact;
private: ctrl::ScientificNotationTextBox^  snboxEipEnthInact;
private: ctrl::ScientificNotationTextBox^  snboxEipEnthAct;
private: ctrl::ScientificNotationTextBox^  snboxEipRo25;

private: ctrl::ScientificNotationTextBox^  snboxHumHostDensity;
private: ctrl::ScientificNotationTextBox^  snboxInitialPopulationSize;

private: ctrl::ScientificNotationTextBox^  snboxHetDuration;

private: ctrl::ScientificNotationTextBox^  snboxVirHighTiterInfection;
private: ctrl::ScientificNotationTextBox^  snboxVirLowTiterInfection;
private: ctrl::ScientificNotationTextBox^  snboxVirHighTiterSetPoint;
private: ctrl::ScientificNotationTextBox^  snboxVirLowTiterSetPoint;
private: ctrl::ScientificNotationTextBox^  snboxMosqCountStochastic;
private: ctrl::ScientificNotationTextBox^  snboxNomProbInfection;




private: System::Windows::Forms::GroupBox^  gboxEipDevelopment;
private: System::Windows::Forms::GroupBox^  groupBox1;
private: ctrl::ScientificNotationTextBox^  snboxLowTiterSetPoint;
private: System::Windows::Forms::Label^  lblHighTiterFactor;
private: ctrl::ScientificNotationTextBox^  snboxLowTiterFactor;
private: System::Windows::Forms::Label^  lblHighTiterSetPoint;
private: ctrl::ScientificNotationTextBox^  snboxHighTiterFactor;
private: System::Windows::Forms::Label^  lblLowTiterFactor;
private: ctrl::ScientificNotationTextBox^  snboxHighTiterSetPoint;
private: System::Windows::Forms::Label^  lblLowTiterSetPoint;
private: System::Windows::Forms::GroupBox^  groupBox2;

















private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcDemoAgeClass;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcDemoProp;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcDemoDeath;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcDemoBirth;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcSeroClass;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcSeroDen1;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcSeroDen2;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcSeroDen3;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcSeroDen4;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcSequence;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcSecondaryMinimum;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgcSecondaryMaximum;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcProbDhfDss;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcAtRiskCutoff;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcMortality;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcSeroType;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcViremia;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcIncubationPeriod;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcViremicPeriod;
private: ctrl::ScientificNotationTextBox^  snboxMaeaDuration;
private: ctrl::ScientificNotationTextBox^  snboxManaDuration;
private: System::Windows::Forms::ErrorProvider^  errProDemographics;
private: System::ComponentModel::IContainer^  components;

























































	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->components = (gcnew System::ComponentModel::Container());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle5 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle7 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle8 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle6 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle9 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle12 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle13 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle10 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle11 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle14 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      this->btnRunSim = (gcnew System::Windows::Forms::Button());
      this->tabDensim = (gcnew System::Windows::Forms::TabControl());
      this->tabDemographics = (gcnew System::Windows::Forms::TabPage());
      this->snboxHumHostDensity = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxInitialPopulationSize = (gcnew ctrl::ScientificNotationTextBox());
      this->lblInitialPopulationSize = (gcnew System::Windows::Forms::Label());
      this->lblHumHostDensity = (gcnew System::Windows::Forms::Label());
      this->dgvDemographics = (gcnew System::Windows::Forms::DataGridView());
      this->dgvcDemoAgeClass = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcDemoProp = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcDemoDeath = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcDemoBirth = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->tabSerology = (gcnew System::Windows::Forms::TabPage());
      this->snboxMaeaDuration = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxManaDuration = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxHetDuration = (gcnew ctrl::ScientificNotationTextBox());
      this->dgvSerology = (gcnew System::Windows::Forms::DataGridView());
      this->dgvcSeroClass = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcSeroDen1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcSeroDen2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcSeroDen3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcSeroDen4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->lblManaDuration = (gcnew System::Windows::Forms::Label());
      this->lblHetDuration = (gcnew System::Windows::Forms::Label());
      this->lblMaeaDuration = (gcnew System::Windows::Forms::Label());
      this->tabVirology = (gcnew System::Windows::Forms::TabPage());
      this->dgvVirology = (gcnew System::Windows::Forms::DataGridView());
      this->dgvcSeroType = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcViremia = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcIncubationPeriod = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcViremicPeriod = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->tabInfectionEip = (gcnew System::Windows::Forms::TabControl());
      this->tabHumToMosInfection = (gcnew System::Windows::Forms::TabPage());
      this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
      this->snboxVirLowTiterSetPoint = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxVirHighTiterInfection = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxVirHighTiterSetPoint = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxVirLowTiterInfection = (gcnew ctrl::ScientificNotationTextBox());
      this->lblVirLowTiterSetPoint = (gcnew System::Windows::Forms::Label());
      this->lblVirHighInfection = (gcnew System::Windows::Forms::Label());
      this->lblVirLowInfection = (gcnew System::Windows::Forms::Label());
      this->lblVirHighTiterSetPoint = (gcnew System::Windows::Forms::Label());
      this->snboxMosqCountStochastic = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxNomProbInfection = (gcnew ctrl::ScientificNotationTextBox());
      this->lbMosqCountStochastic = (gcnew System::Windows::Forms::Label());
      this->lblNomProbInfection = (gcnew System::Windows::Forms::Label());
      this->tabEip = (gcnew System::Windows::Forms::TabPage());
      this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
      this->snboxLowTiterSetPoint = (gcnew ctrl::ScientificNotationTextBox());
      this->lblHighTiterFactor = (gcnew System::Windows::Forms::Label());
      this->snboxLowTiterFactor = (gcnew ctrl::ScientificNotationTextBox());
      this->lblHighTiterSetPoint = (gcnew System::Windows::Forms::Label());
      this->snboxHighTiterFactor = (gcnew ctrl::ScientificNotationTextBox());
      this->lblLowTiterFactor = (gcnew System::Windows::Forms::Label());
      this->snboxHighTiterSetPoint = (gcnew ctrl::ScientificNotationTextBox());
      this->lblLowTiterSetPoint = (gcnew System::Windows::Forms::Label());
      this->gboxEipDevelopment = (gcnew System::Windows::Forms::GroupBox());
      this->snboxEipRo25 = (gcnew ctrl::ScientificNotationTextBox());
      this->lblEipTempInact = (gcnew System::Windows::Forms::Label());
      this->snboxEipEnthAct = (gcnew ctrl::ScientificNotationTextBox());
      this->lblEipEnthInact = (gcnew System::Windows::Forms::Label());
      this->snboxEipTempInact = (gcnew ctrl::ScientificNotationTextBox());
      this->lblEipEnthAct = (gcnew System::Windows::Forms::Label());
      this->snboxEipEnthInact = (gcnew ctrl::ScientificNotationTextBox());
      this->lblEipRo25 = (gcnew System::Windows::Forms::Label());
      this->tabInfections = (gcnew System::Windows::Forms::TabPage());
      this->tabDhsDss = (gcnew System::Windows::Forms::TabPage());
      this->dgvSequentials = (gcnew System::Windows::Forms::DataGridView());
      this->dgvcSequence = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcSecondaryMinimum = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgcSecondaryMaximum = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcProbDhfDss = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcAtRiskCutoff = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcMortality = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->errProDemographics = (gcnew System::Windows::Forms::ErrorProvider(this->components));
      this->tabDensim->SuspendLayout();
      this->tabDemographics->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvDemographics))->BeginInit();
      this->tabSerology->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvSerology))->BeginInit();
      this->tabVirology->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvVirology))->BeginInit();
      this->tabInfectionEip->SuspendLayout();
      this->tabHumToMosInfection->SuspendLayout();
      this->groupBox2->SuspendLayout();
      this->tabEip->SuspendLayout();
      this->groupBox1->SuspendLayout();
      this->gboxEipDevelopment->SuspendLayout();
      this->tabDhsDss->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvSequentials))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errProDemographics))->BeginInit();
      this->SuspendLayout();
      // 
      // btnRunSim
      // 
      this->btnRunSim->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnRunSim->Location = System::Drawing::Point(679, 312);
      this->btnRunSim->Name = L"btnRunSim";
      this->btnRunSim->Size = System::Drawing::Size(101, 23);
      this->btnRunSim->TabIndex = 1;
      this->btnRunSim->Text = L"Run DENSiM...";
      this->btnRunSim->UseVisualStyleBackColor = true;
      this->btnRunSim->Click += gcnew System::EventHandler(this, &DensimPanel::OnRunDensim);
      // 
      // tabDensim
      // 
      this->tabDensim->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->tabDensim->Controls->Add(this->tabDemographics);
      this->tabDensim->Controls->Add(this->tabSerology);
      this->tabDensim->Controls->Add(this->tabVirology);
      this->tabDensim->Controls->Add(this->tabInfections);
      this->tabDensim->Controls->Add(this->tabDhsDss);
      this->tabDensim->Location = System::Drawing::Point(6, 6);
      this->tabDensim->MinimumSize = System::Drawing::Size(774, 300);
      this->tabDensim->Name = L"tabDensim";
      this->tabDensim->SelectedIndex = 0;
      this->tabDensim->Size = System::Drawing::Size(774, 300);
      this->tabDensim->TabIndex = 0;
      this->tabDensim->Selecting += gcnew System::Windows::Forms::TabControlCancelEventHandler(this, &DensimPanel::OnTabPageSelecting);
      // 
      // tabDemographics
      // 
      this->tabDemographics->Controls->Add(this->snboxHumHostDensity);
      this->tabDemographics->Controls->Add(this->snboxInitialPopulationSize);
      this->tabDemographics->Controls->Add(this->lblInitialPopulationSize);
      this->tabDemographics->Controls->Add(this->lblHumHostDensity);
      this->tabDemographics->Controls->Add(this->dgvDemographics);
      this->tabDemographics->Location = System::Drawing::Point(4, 24);
      this->tabDemographics->Name = L"tabDemographics";
      this->tabDemographics->Padding = System::Windows::Forms::Padding(3);
      this->tabDemographics->Size = System::Drawing::Size(766, 272);
      this->tabDemographics->TabIndex = 0;
      this->tabDemographics->Text = L"Demographics";
      this->tabDemographics->UseVisualStyleBackColor = true;
      // 
      // snboxHumHostDensity
      // 
      this->snboxHumHostDensity->Location = System::Drawing::Point(122, 32);
      this->snboxHumHostDensity->Name = L"snboxHumHostDensity";
      this->snboxHumHostDensity->Size = System::Drawing::Size(80, 20);
      this->snboxHumHostDensity->TabIndex = 3;
      this->snboxHumHostDensity->Text = L"0";
      this->snboxHumHostDensity->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxHumHostDensity->Value = L"0";
      // 
      // snboxInitialPopulationSize
      // 
      this->snboxInitialPopulationSize->Location = System::Drawing::Point(122, 6);
      this->snboxInitialPopulationSize->Name = L"snboxInitialPopulationSize";
      this->snboxInitialPopulationSize->Size = System::Drawing::Size(80, 20);
      this->snboxInitialPopulationSize->TabIndex = 1;
      this->snboxInitialPopulationSize->Text = L"0";
      this->snboxInitialPopulationSize->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxInitialPopulationSize->Value = L"0";
      // 
      // lblInitialPopulationSize
      // 
      this->lblInitialPopulationSize->AutoSize = true;
      this->lblInitialPopulationSize->Location = System::Drawing::Point(6, 9);
      this->lblInitialPopulationSize->Name = L"lblInitialPopulationSize";
      this->lblInitialPopulationSize->Size = System::Drawing::Size(110, 13);
      this->lblInitialPopulationSize->TabIndex = 0;
      this->lblInitialPopulationSize->Text = L"Initial Population Size:";
      // 
      // lblHumHostDensity
      // 
      this->lblHumHostDensity->AutoSize = true;
      this->lblHumHostDensity->Location = System::Drawing::Point(6, 35);
      this->lblHumHostDensity->Name = L"lblHumHostDensity";
      this->lblHumHostDensity->Size = System::Drawing::Size(107, 13);
      this->lblHumHostDensity->TabIndex = 2;
      this->lblHumHostDensity->Text = L"Human Host Density:";
      // 
      // dgvDemographics
      // 
      this->dgvDemographics->AllowUserToAddRows = false;
      this->dgvDemographics->AllowUserToDeleteRows = false;
      this->dgvDemographics->AllowUserToResizeRows = false;
      this->dgvDemographics->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->dgvDemographics->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
      dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
      dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
      dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
      dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
      dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
      dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
      this->dgvDemographics->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
      this->dgvDemographics->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
      this->dgvDemographics->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {this->dgvcDemoAgeClass, 
        this->dgvcDemoProp, this->dgvcDemoDeath, this->dgvcDemoBirth});
      dataGridViewCellStyle3->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
      dataGridViewCellStyle3->BackColor = System::Drawing::SystemColors::Window;
      dataGridViewCellStyle3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      dataGridViewCellStyle3->ForeColor = System::Drawing::SystemColors::ControlText;
      dataGridViewCellStyle3->SelectionBackColor = System::Drawing::SystemColors::Highlight;
      dataGridViewCellStyle3->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
      dataGridViewCellStyle3->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
      this->dgvDemographics->DefaultCellStyle = dataGridViewCellStyle3;
      this->errProDemographics->SetIconAlignment(this->dgvDemographics, System::Windows::Forms::ErrorIconAlignment::TopLeft);
      this->errProDemographics->SetIconPadding(this->dgvDemographics, -16);
      this->dgvDemographics->Location = System::Drawing::Point(6, 58);
      this->dgvDemographics->Name = L"dgvDemographics";
      dataGridViewCellStyle4->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
      dataGridViewCellStyle4->BackColor = System::Drawing::SystemColors::Control;
      dataGridViewCellStyle4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      dataGridViewCellStyle4->ForeColor = System::Drawing::SystemColors::WindowText;
      dataGridViewCellStyle4->SelectionBackColor = System::Drawing::SystemColors::Highlight;
      dataGridViewCellStyle4->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
      dataGridViewCellStyle4->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
      this->dgvDemographics->RowHeadersDefaultCellStyle = dataGridViewCellStyle4;
      this->dgvDemographics->RowHeadersVisible = false;
      this->dgvDemographics->Size = System::Drawing::Size(754, 208);
      this->dgvDemographics->TabIndex = 6;
      this->dgvDemographics->RowValidating += gcnew System::Windows::Forms::DataGridViewCellCancelEventHandler(this, &DensimPanel::OnDemographicsRowValidating);
      // 
      // dgvcDemoAgeClass
      // 
      this->dgvcDemoAgeClass->DataPropertyName = L"AgeClass";
      dataGridViewCellStyle2->BackColor = System::Drawing::SystemColors::Control;
      this->dgvcDemoAgeClass->DefaultCellStyle = dataGridViewCellStyle2;
      this->dgvcDemoAgeClass->HeaderText = L"Age Class";
      this->dgvcDemoAgeClass->Name = L"dgvcDemoAgeClass";
      this->dgvcDemoAgeClass->ReadOnly = true;
      // 
      // dgvcDemoProp
      // 
      this->dgvcDemoProp->DataPropertyName = L"Proportion";
      this->dgvcDemoProp->HeaderText = L"Proportion in Class";
      this->dgvcDemoProp->Name = L"dgvcDemoProp";
      // 
      // dgvcDemoDeath
      // 
      this->dgvcDemoDeath->DataPropertyName = L"DeathRate";
      this->dgvcDemoDeath->HeaderText = L"Death Rate per 1000";
      this->dgvcDemoDeath->Name = L"dgvcDemoDeath";
      // 
      // dgvcDemoBirth
      // 
      this->dgvcDemoBirth->DataPropertyName = L"BirthRate";
      this->dgvcDemoBirth->HeaderText = L"Birth Rate per 1000";
      this->dgvcDemoBirth->Name = L"dgvcDemoBirth";
      // 
      // tabSerology
      // 
      this->tabSerology->Controls->Add(this->snboxMaeaDuration);
      this->tabSerology->Controls->Add(this->snboxManaDuration);
      this->tabSerology->Controls->Add(this->snboxHetDuration);
      this->tabSerology->Controls->Add(this->dgvSerology);
      this->tabSerology->Controls->Add(this->lblManaDuration);
      this->tabSerology->Controls->Add(this->lblHetDuration);
      this->tabSerology->Controls->Add(this->lblMaeaDuration);
      this->tabSerology->Location = System::Drawing::Point(4, 24);
      this->tabSerology->Name = L"tabSerology";
      this->tabSerology->Padding = System::Windows::Forms::Padding(3);
      this->tabSerology->Size = System::Drawing::Size(766, 272);
      this->tabSerology->TabIndex = 1;
      this->tabSerology->Text = L"Serology";
      this->tabSerology->UseVisualStyleBackColor = true;
      // 
      // snboxMaeaDuration
      // 
      this->snboxMaeaDuration->Location = System::Drawing::Point(332, 32);
      this->snboxMaeaDuration->Name = L"snboxMaeaDuration";
      this->snboxMaeaDuration->Size = System::Drawing::Size(80, 20);
      this->snboxMaeaDuration->TabIndex = 3;
      this->snboxMaeaDuration->Text = L"0";
      this->snboxMaeaDuration->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxMaeaDuration->Value = L"0";
      // 
      // snboxManaDuration
      // 
      this->snboxManaDuration->Location = System::Drawing::Point(332, 6);
      this->snboxManaDuration->Name = L"snboxManaDuration";
      this->snboxManaDuration->Size = System::Drawing::Size(80, 20);
      this->snboxManaDuration->TabIndex = 1;
      this->snboxManaDuration->Text = L"0.00000";
      this->snboxManaDuration->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxManaDuration->Value = L"0.00000";
      // 
      // snboxHetDuration
      // 
      this->snboxHetDuration->Location = System::Drawing::Point(332, 58);
      this->snboxHetDuration->Name = L"snboxHetDuration";
      this->snboxHetDuration->Size = System::Drawing::Size(80, 20);
      this->snboxHetDuration->TabIndex = 5;
      this->snboxHetDuration->Text = L"0";
      this->snboxHetDuration->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxHetDuration->Value = L"0";
      // 
      // dgvSerology
      // 
      this->dgvSerology->AllowUserToAddRows = false;
      this->dgvSerology->AllowUserToDeleteRows = false;
      this->dgvSerology->AllowUserToResizeRows = false;
      this->dgvSerology->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->dgvSerology->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
      dataGridViewCellStyle5->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
      dataGridViewCellStyle5->BackColor = System::Drawing::SystemColors::Control;
      dataGridViewCellStyle5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      dataGridViewCellStyle5->ForeColor = System::Drawing::SystemColors::WindowText;
      dataGridViewCellStyle5->SelectionBackColor = System::Drawing::SystemColors::Highlight;
      dataGridViewCellStyle5->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
      dataGridViewCellStyle5->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
      this->dgvSerology->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle5;
      this->dgvSerology->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
      this->dgvSerology->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {this->dgvcSeroClass, 
        this->dgvcSeroDen1, this->dgvcSeroDen2, this->dgvcSeroDen3, this->dgvcSeroDen4});
      dataGridViewCellStyle7->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
      dataGridViewCellStyle7->BackColor = System::Drawing::SystemColors::Window;
      dataGridViewCellStyle7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      dataGridViewCellStyle7->ForeColor = System::Drawing::SystemColors::ControlText;
      dataGridViewCellStyle7->SelectionBackColor = System::Drawing::SystemColors::Highlight;
      dataGridViewCellStyle7->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
      dataGridViewCellStyle7->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
      this->dgvSerology->DefaultCellStyle = dataGridViewCellStyle7;
      this->dgvSerology->Location = System::Drawing::Point(6, 84);
      this->dgvSerology->Name = L"dgvSerology";
      dataGridViewCellStyle8->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
      dataGridViewCellStyle8->BackColor = System::Drawing::SystemColors::Control;
      dataGridViewCellStyle8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      dataGridViewCellStyle8->ForeColor = System::Drawing::SystemColors::WindowText;
      dataGridViewCellStyle8->SelectionBackColor = System::Drawing::SystemColors::Highlight;
      dataGridViewCellStyle8->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
      dataGridViewCellStyle8->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
      this->dgvSerology->RowHeadersDefaultCellStyle = dataGridViewCellStyle8;
      this->dgvSerology->RowHeadersVisible = false;
      this->dgvSerology->Size = System::Drawing::Size(754, 182);
      this->dgvSerology->TabIndex = 6;
      // 
      // dgvcSeroClass
      // 
      this->dgvcSeroClass->DataPropertyName = L"AgeClass";
      dataGridViewCellStyle6->BackColor = System::Drawing::SystemColors::Control;
      this->dgvcSeroClass->DefaultCellStyle = dataGridViewCellStyle6;
      this->dgvcSeroClass->HeaderText = L"Age Class";
      this->dgvcSeroClass->Name = L"dgvcSeroClass";
      this->dgvcSeroClass->ReadOnly = true;
      // 
      // dgvcSeroDen1
      // 
      this->dgvcSeroDen1->DataPropertyName = L"Dengue1";
      this->dgvcSeroDen1->HeaderText = L"Dengue 1";
      this->dgvcSeroDen1->Name = L"dgvcSeroDen1";
      // 
      // dgvcSeroDen2
      // 
      this->dgvcSeroDen2->DataPropertyName = L"Dengue2";
      this->dgvcSeroDen2->HeaderText = L"Dengue 2";
      this->dgvcSeroDen2->Name = L"dgvcSeroDen2";
      // 
      // dgvcSeroDen3
      // 
      this->dgvcSeroDen3->DataPropertyName = L"Dengue3";
      this->dgvcSeroDen3->HeaderText = L"Dengue 3";
      this->dgvcSeroDen3->Name = L"dgvcSeroDen3";
      // 
      // dgvcSeroDen4
      // 
      this->dgvcSeroDen4->DataPropertyName = L"Dengue4";
      this->dgvcSeroDen4->HeaderText = L"Dengue 4";
      this->dgvcSeroDen4->Name = L"dgvcSeroDen4";
      // 
      // lblManaDuration
      // 
      this->lblManaDuration->AutoSize = true;
      this->lblManaDuration->Location = System::Drawing::Point(6, 9);
      this->lblManaDuration->Name = L"lblManaDuration";
      this->lblManaDuration->Size = System::Drawing::Size(323, 13);
      this->lblManaDuration->TabIndex = 0;
      this->lblManaDuration->Text = L"Duration of maternally-acquired neutralizing titers of antibody (days):";
      // 
      // lblHetDuration
      // 
      this->lblHetDuration->AutoSize = true;
      this->lblHetDuration->Location = System::Drawing::Point(6, 61);
      this->lblHetDuration->Name = L"lblHetDuration";
      this->lblHetDuration->Size = System::Drawing::Size(194, 13);
      this->lblHetDuration->TabIndex = 4;
      this->lblHetDuration->Text = L"Duration of heterolgous immunity (days):";
      // 
      // lblMaeaDuration
      // 
      this->lblMaeaDuration->AutoSize = true;
      this->lblMaeaDuration->Location = System::Drawing::Point(6, 35);
      this->lblMaeaDuration->Name = L"lblMaeaDuration";
      this->lblMaeaDuration->Size = System::Drawing::Size(320, 13);
      this->lblMaeaDuration->TabIndex = 2;
      this->lblMaeaDuration->Text = L"Duration of maternally-acquired enhancing titers of antibody (days):";
      // 
      // tabVirology
      // 
      this->tabVirology->Controls->Add(this->dgvVirology);
      this->tabVirology->Controls->Add(this->tabInfectionEip);
      this->tabVirology->Location = System::Drawing::Point(4, 24);
      this->tabVirology->Name = L"tabVirology";
      this->tabVirology->Size = System::Drawing::Size(766, 272);
      this->tabVirology->TabIndex = 2;
      this->tabVirology->Text = L"Virology";
      this->tabVirology->UseVisualStyleBackColor = true;
      // 
      // dgvVirology
      // 
      this->dgvVirology->AllowUserToAddRows = false;
      this->dgvVirology->AllowUserToDeleteRows = false;
      this->dgvVirology->AllowUserToResizeRows = false;
      this->dgvVirology->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->dgvVirology->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
      this->dgvVirology->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::DisplayedCells;
      dataGridViewCellStyle9->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
      dataGridViewCellStyle9->BackColor = System::Drawing::SystemColors::Control;
      dataGridViewCellStyle9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      dataGridViewCellStyle9->ForeColor = System::Drawing::SystemColors::WindowText;
      dataGridViewCellStyle9->SelectionBackColor = System::Drawing::SystemColors::Highlight;
      dataGridViewCellStyle9->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
      dataGridViewCellStyle9->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
      this->dgvVirology->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle9;
      this->dgvVirology->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
      this->dgvVirology->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {this->dgvcSeroType, 
        this->dgvcViremia, this->dgvcIncubationPeriod, this->dgvcViremicPeriod});
      dataGridViewCellStyle12->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
      dataGridViewCellStyle12->BackColor = System::Drawing::SystemColors::Window;
      dataGridViewCellStyle12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      dataGridViewCellStyle12->ForeColor = System::Drawing::SystemColors::ControlText;
      dataGridViewCellStyle12->SelectionBackColor = System::Drawing::SystemColors::Highlight;
      dataGridViewCellStyle12->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
      dataGridViewCellStyle12->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
      this->dgvVirology->DefaultCellStyle = dataGridViewCellStyle12;
      this->dgvVirology->Location = System::Drawing::Point(3, 3);
      this->dgvVirology->Name = L"dgvVirology";
      dataGridViewCellStyle13->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
      dataGridViewCellStyle13->BackColor = System::Drawing::SystemColors::Control;
      dataGridViewCellStyle13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      dataGridViewCellStyle13->ForeColor = System::Drawing::SystemColors::WindowText;
      dataGridViewCellStyle13->SelectionBackColor = System::Drawing::SystemColors::Highlight;
      dataGridViewCellStyle13->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
      dataGridViewCellStyle13->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
      this->dgvVirology->RowHeadersDefaultCellStyle = dataGridViewCellStyle13;
      this->dgvVirology->RowHeadersVisible = false;
      this->dgvVirology->Size = System::Drawing::Size(760, 107);
      this->dgvVirology->TabIndex = 0;
      // 
      // dgvcSeroType
      // 
      this->dgvcSeroType->DataPropertyName = L"SeroTypeString";
      dataGridViewCellStyle10->BackColor = System::Drawing::SystemColors::Control;
      this->dgvcSeroType->DefaultCellStyle = dataGridViewCellStyle10;
      this->dgvcSeroType->HeaderText = L"Serotype";
      this->dgvcSeroType->Name = L"dgvcSeroType";
      this->dgvcSeroType->ReadOnly = true;
      // 
      // dgvcViremia
      // 
      this->dgvcViremia->DataPropertyName = L"Viremia";
      dataGridViewCellStyle11->Format = L"N0";
      dataGridViewCellStyle11->NullValue = nullptr;
      this->dgvcViremia->DefaultCellStyle = dataGridViewCellStyle11;
      this->dgvcViremia->HeaderText = L"Viremia (MID-50)";
      this->dgvcViremia->Name = L"dgvcViremia";
      // 
      // dgvcIncubationPeriod
      // 
      this->dgvcIncubationPeriod->DataPropertyName = L"IncubationDuration";
      this->dgvcIncubationPeriod->HeaderText = L"Incubation Duration (days)";
      this->dgvcIncubationPeriod->Name = L"dgvcIncubationPeriod";
      // 
      // dgvcViremicPeriod
      // 
      this->dgvcViremicPeriod->DataPropertyName = L"ViremicDuration";
      this->dgvcViremicPeriod->HeaderText = L"Viremic Duration (days)";
      this->dgvcViremicPeriod->Name = L"dgvcViremicPeriod";
      // 
      // tabInfectionEip
      // 
      this->tabInfectionEip->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->tabInfectionEip->Controls->Add(this->tabHumToMosInfection);
      this->tabInfectionEip->Controls->Add(this->tabEip);
      this->tabInfectionEip->Location = System::Drawing::Point(6, 116);
      this->tabInfectionEip->Name = L"tabInfectionEip";
      this->tabInfectionEip->SelectedIndex = 0;
      this->tabInfectionEip->Size = System::Drawing::Size(760, 152);
      this->tabInfectionEip->TabIndex = 1;
      // 
      // tabHumToMosInfection
      // 
      this->tabHumToMosInfection->Controls->Add(this->groupBox2);
      this->tabHumToMosInfection->Controls->Add(this->snboxMosqCountStochastic);
      this->tabHumToMosInfection->Controls->Add(this->snboxNomProbInfection);
      this->tabHumToMosInfection->Controls->Add(this->lbMosqCountStochastic);
      this->tabHumToMosInfection->Controls->Add(this->lblNomProbInfection);
      this->tabHumToMosInfection->Location = System::Drawing::Point(4, 24);
      this->tabHumToMosInfection->Name = L"tabHumToMosInfection";
      this->tabHumToMosInfection->Padding = System::Windows::Forms::Padding(3);
      this->tabHumToMosInfection->Size = System::Drawing::Size(752, 124);
      this->tabHumToMosInfection->TabIndex = 0;
      this->tabHumToMosInfection->Text = L"Infection Parameters";
      this->tabHumToMosInfection->UseVisualStyleBackColor = true;
      // 
      // groupBox2
      // 
      this->groupBox2->Controls->Add(this->snboxVirLowTiterSetPoint);
      this->groupBox2->Controls->Add(this->snboxVirHighTiterInfection);
      this->groupBox2->Controls->Add(this->snboxVirHighTiterSetPoint);
      this->groupBox2->Controls->Add(this->snboxVirLowTiterInfection);
      this->groupBox2->Controls->Add(this->lblVirLowTiterSetPoint);
      this->groupBox2->Controls->Add(this->lblVirHighInfection);
      this->groupBox2->Controls->Add(this->lblVirLowInfection);
      this->groupBox2->Controls->Add(this->lblVirHighTiterSetPoint);
      this->groupBox2->Location = System::Drawing::Point(6, 3);
      this->groupBox2->Name = L"groupBox2";
      this->groupBox2->Size = System::Drawing::Size(367, 115);
      this->groupBox2->TabIndex = 0;
      this->groupBox2->TabStop = false;
      this->groupBox2->Text = L"Probability of human to mosquito infection as function of titer";
      // 
      // snboxVirLowTiterSetPoint
      // 
      this->snboxVirLowTiterSetPoint->Location = System::Drawing::Point(281, 13);
      this->snboxVirLowTiterSetPoint->Name = L"snboxVirLowTiterSetPoint";
      this->snboxVirLowTiterSetPoint->Size = System::Drawing::Size(80, 20);
      this->snboxVirLowTiterSetPoint->TabIndex = 1;
      this->snboxVirLowTiterSetPoint->Text = L"0";
      this->snboxVirLowTiterSetPoint->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxVirLowTiterSetPoint->Value = L"0";
      // 
      // snboxVirHighTiterInfection
      // 
      this->snboxVirHighTiterInfection->Location = System::Drawing::Point(281, 91);
      this->snboxVirHighTiterInfection->Name = L"snboxVirHighTiterInfection";
      this->snboxVirHighTiterInfection->Size = System::Drawing::Size(80, 20);
      this->snboxVirHighTiterInfection->TabIndex = 7;
      this->snboxVirHighTiterInfection->Text = L"0";
      this->snboxVirHighTiterInfection->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxVirHighTiterInfection->Value = L"0";
      // 
      // snboxVirHighTiterSetPoint
      // 
      this->snboxVirHighTiterSetPoint->Location = System::Drawing::Point(281, 65);
      this->snboxVirHighTiterSetPoint->Name = L"snboxVirHighTiterSetPoint";
      this->snboxVirHighTiterSetPoint->Size = System::Drawing::Size(80, 20);
      this->snboxVirHighTiterSetPoint->TabIndex = 5;
      this->snboxVirHighTiterSetPoint->Text = L"0";
      this->snboxVirHighTiterSetPoint->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxVirHighTiterSetPoint->Value = L"0";
      // 
      // snboxVirLowTiterInfection
      // 
      this->snboxVirLowTiterInfection->Location = System::Drawing::Point(281, 39);
      this->snboxVirLowTiterInfection->Name = L"snboxVirLowTiterInfection";
      this->snboxVirLowTiterInfection->Size = System::Drawing::Size(80, 20);
      this->snboxVirLowTiterInfection->TabIndex = 3;
      this->snboxVirLowTiterInfection->Text = L"0";
      this->snboxVirLowTiterInfection->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxVirLowTiterInfection->Value = L"0";
      // 
      // lblVirLowTiterSetPoint
      // 
      this->lblVirLowTiterSetPoint->AutoSize = true;
      this->lblVirLowTiterSetPoint->Location = System::Drawing::Point(6, 16);
      this->lblVirLowTiterSetPoint->Name = L"lblVirLowTiterSetPoint";
      this->lblVirLowTiterSetPoint->Size = System::Drawing::Size(166, 13);
      this->lblVirLowTiterSetPoint->TabIndex = 0;
      this->lblVirLowTiterSetPoint->Text = L"Log of low titer set point (MID-50):";
      // 
      // lblVirHighInfection
      // 
      this->lblVirHighInfection->AutoSize = true;
      this->lblVirHighInfection->Location = System::Drawing::Point(6, 94);
      this->lblVirHighInfection->Name = L"lblVirHighInfection";
      this->lblVirHighInfection->Size = System::Drawing::Size(275, 13);
      this->lblVirHighInfection->TabIndex = 6;
      this->lblVirHighInfection->Text = L"Probability of infection in biters at or above high set point:";
      // 
      // lblVirLowInfection
      // 
      this->lblVirLowInfection->AutoSize = true;
      this->lblVirLowInfection->Location = System::Drawing::Point(6, 42);
      this->lblVirLowInfection->Name = L"lblVirLowInfection";
      this->lblVirLowInfection->Size = System::Drawing::Size(269, 13);
      this->lblVirLowInfection->TabIndex = 2;
      this->lblVirLowInfection->Text = L"Probability of infection in biters at or below low set point:";
      // 
      // lblVirHighTiterSetPoint
      // 
      this->lblVirHighTiterSetPoint->AutoSize = true;
      this->lblVirHighTiterSetPoint->Location = System::Drawing::Point(6, 68);
      this->lblVirHighTiterSetPoint->Name = L"lblVirHighTiterSetPoint";
      this->lblVirHighTiterSetPoint->Size = System::Drawing::Size(170, 13);
      this->lblVirHighTiterSetPoint->TabIndex = 4;
      this->lblVirHighTiterSetPoint->Text = L"Log of high titer set point (MID-50):";
      // 
      // snboxMosqCountStochastic
      // 
      this->snboxMosqCountStochastic->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->snboxMosqCountStochastic->Location = System::Drawing::Point(666, 38);
      this->snboxMosqCountStochastic->Name = L"snboxMosqCountStochastic";
      this->snboxMosqCountStochastic->Size = System::Drawing::Size(80, 20);
      this->snboxMosqCountStochastic->TabIndex = 4;
      this->snboxMosqCountStochastic->Text = L"0";
      this->snboxMosqCountStochastic->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxMosqCountStochastic->Value = L"0";
      // 
      // snboxNomProbInfection
      // 
      this->snboxNomProbInfection->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->snboxNomProbInfection->Location = System::Drawing::Point(666, 12);
      this->snboxNomProbInfection->Name = L"snboxNomProbInfection";
      this->snboxNomProbInfection->Size = System::Drawing::Size(80, 20);
      this->snboxNomProbInfection->TabIndex = 2;
      this->snboxNomProbInfection->Text = L"0";
      this->snboxNomProbInfection->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxNomProbInfection->Value = L"0";
      // 
      // lbMosqCountStochastic
      // 
      this->lbMosqCountStochastic->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->lbMosqCountStochastic->AutoSize = true;
      this->lbMosqCountStochastic->Location = System::Drawing::Point(466, 41);
      this->lbMosqCountStochastic->Name = L"lbMosqCountStochastic";
      this->lbMosqCountStochastic->Size = System::Drawing::Size(194, 13);
      this->lbMosqCountStochastic->TabIndex = 3;
      this->lbMosqCountStochastic->Text = L"Mosquito counts for stochastic routines:";
      // 
      // lblNomProbInfection
      // 
      this->lblNomProbInfection->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->lblNomProbInfection->AutoSize = true;
      this->lblNomProbInfection->Location = System::Drawing::Point(415, 15);
      this->lblNomProbInfection->Name = L"lblNomProbInfection";
      this->lblNomProbInfection->Size = System::Drawing::Size(245, 13);
      this->lblNomProbInfection->TabIndex = 1;
      this->lblNomProbInfection->Text = L"Nominal probability of mosquito to human infection:";
      // 
      // tabEip
      // 
      this->tabEip->Controls->Add(this->groupBox1);
      this->tabEip->Controls->Add(this->gboxEipDevelopment);
      this->tabEip->Location = System::Drawing::Point(4, 24);
      this->tabEip->Name = L"tabEip";
      this->tabEip->Padding = System::Windows::Forms::Padding(3);
      this->tabEip->Size = System::Drawing::Size(752, 124);
      this->tabEip->TabIndex = 1;
      this->tabEip->Text = L"Virus EIP";
      this->tabEip->UseVisualStyleBackColor = true;
      // 
      // groupBox1
      // 
      this->groupBox1->Controls->Add(this->snboxLowTiterSetPoint);
      this->groupBox1->Controls->Add(this->lblHighTiterFactor);
      this->groupBox1->Controls->Add(this->snboxLowTiterFactor);
      this->groupBox1->Controls->Add(this->lblHighTiterSetPoint);
      this->groupBox1->Controls->Add(this->snboxHighTiterFactor);
      this->groupBox1->Controls->Add(this->lblLowTiterFactor);
      this->groupBox1->Controls->Add(this->snboxHighTiterSetPoint);
      this->groupBox1->Controls->Add(this->lblLowTiterSetPoint);
      this->groupBox1->Location = System::Drawing::Point(379, 6);
      this->groupBox1->Name = L"groupBox1";
      this->groupBox1->Size = System::Drawing::Size(367, 115);
      this->groupBox1->TabIndex = 1;
      this->groupBox1->TabStop = false;
      this->groupBox1->Text = L"EIP Adjustment by Virus Titer";
      // 
      // snboxLowTiterSetPoint
      // 
      this->snboxLowTiterSetPoint->Location = System::Drawing::Point(281, 13);
      this->snboxLowTiterSetPoint->Name = L"snboxLowTiterSetPoint";
      this->snboxLowTiterSetPoint->Size = System::Drawing::Size(80, 20);
      this->snboxLowTiterSetPoint->TabIndex = 1;
      this->snboxLowTiterSetPoint->Text = L"0";
      this->snboxLowTiterSetPoint->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxLowTiterSetPoint->Value = L"0";
      // 
      // lblHighTiterFactor
      // 
      this->lblHighTiterFactor->AutoSize = true;
      this->lblHighTiterFactor->Location = System::Drawing::Point(6, 94);
      this->lblHighTiterFactor->Name = L"lblHighTiterFactor";
      this->lblHighTiterFactor->Size = System::Drawing::Size(180, 13);
      this->lblHighTiterFactor->TabIndex = 6;
      this->lblHighTiterFactor->Text = L"EIP factor at or above high set point:";
      // 
      // snboxLowTiterFactor
      // 
      this->snboxLowTiterFactor->Location = System::Drawing::Point(281, 39);
      this->snboxLowTiterFactor->Name = L"snboxLowTiterFactor";
      this->snboxLowTiterFactor->Size = System::Drawing::Size(80, 20);
      this->snboxLowTiterFactor->TabIndex = 3;
      this->snboxLowTiterFactor->Text = L"0";
      this->snboxLowTiterFactor->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxLowTiterFactor->Value = L"0";
      // 
      // lblHighTiterSetPoint
      // 
      this->lblHighTiterSetPoint->AutoSize = true;
      this->lblHighTiterSetPoint->Location = System::Drawing::Point(6, 68);
      this->lblHighTiterSetPoint->Name = L"lblHighTiterSetPoint";
      this->lblHighTiterSetPoint->Size = System::Drawing::Size(95, 13);
      this->lblHighTiterSetPoint->TabIndex = 4;
      this->lblHighTiterSetPoint->Text = L"High titer set point:";
      // 
      // snboxHighTiterFactor
      // 
      this->snboxHighTiterFactor->Location = System::Drawing::Point(281, 91);
      this->snboxHighTiterFactor->Name = L"snboxHighTiterFactor";
      this->snboxHighTiterFactor->Size = System::Drawing::Size(80, 20);
      this->snboxHighTiterFactor->TabIndex = 7;
      this->snboxHighTiterFactor->Text = L"0";
      this->snboxHighTiterFactor->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxHighTiterFactor->Value = L"0";
      // 
      // lblLowTiterFactor
      // 
      this->lblLowTiterFactor->AutoSize = true;
      this->lblLowTiterFactor->Location = System::Drawing::Point(6, 42);
      this->lblLowTiterFactor->Name = L"lblLowTiterFactor";
      this->lblLowTiterFactor->Size = System::Drawing::Size(174, 13);
      this->lblLowTiterFactor->TabIndex = 2;
      this->lblLowTiterFactor->Text = L"EIP factor at or below low set point:";
      // 
      // snboxHighTiterSetPoint
      // 
      this->snboxHighTiterSetPoint->Location = System::Drawing::Point(281, 65);
      this->snboxHighTiterSetPoint->Name = L"snboxHighTiterSetPoint";
      this->snboxHighTiterSetPoint->Size = System::Drawing::Size(80, 20);
      this->snboxHighTiterSetPoint->TabIndex = 5;
      this->snboxHighTiterSetPoint->Text = L"0";
      this->snboxHighTiterSetPoint->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxHighTiterSetPoint->Value = L"0";
      // 
      // lblLowTiterSetPoint
      // 
      this->lblLowTiterSetPoint->AutoSize = true;
      this->lblLowTiterSetPoint->Location = System::Drawing::Point(6, 16);
      this->lblLowTiterSetPoint->Name = L"lblLowTiterSetPoint";
      this->lblLowTiterSetPoint->Size = System::Drawing::Size(93, 13);
      this->lblLowTiterSetPoint->TabIndex = 0;
      this->lblLowTiterSetPoint->Text = L"Low titer set point:";
      // 
      // gboxEipDevelopment
      // 
      this->gboxEipDevelopment->Controls->Add(this->snboxEipRo25);
      this->gboxEipDevelopment->Controls->Add(this->lblEipTempInact);
      this->gboxEipDevelopment->Controls->Add(this->snboxEipEnthAct);
      this->gboxEipDevelopment->Controls->Add(this->lblEipEnthInact);
      this->gboxEipDevelopment->Controls->Add(this->snboxEipTempInact);
      this->gboxEipDevelopment->Controls->Add(this->lblEipEnthAct);
      this->gboxEipDevelopment->Controls->Add(this->snboxEipEnthInact);
      this->gboxEipDevelopment->Controls->Add(this->lblEipRo25);
      this->gboxEipDevelopment->Location = System::Drawing::Point(6, 6);
      this->gboxEipDevelopment->Name = L"gboxEipDevelopment";
      this->gboxEipDevelopment->Size = System::Drawing::Size(367, 115);
      this->gboxEipDevelopment->TabIndex = 0;
      this->gboxEipDevelopment->TabStop = false;
      this->gboxEipDevelopment->Text = L"EIP Development Rate";
      // 
      // snboxEipRo25
      // 
      this->snboxEipRo25->Enabled = false;
      this->snboxEipRo25->Location = System::Drawing::Point(261, 13);
      this->snboxEipRo25->Name = L"snboxEipRo25";
      this->snboxEipRo25->Size = System::Drawing::Size(100, 20);
      this->snboxEipRo25->TabIndex = 1;
      this->snboxEipRo25->Text = L"0";
      this->snboxEipRo25->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxEipRo25->Value = L"0";
      // 
      // lblEipTempInact
      // 
      this->lblEipTempInact->AutoSize = true;
      this->lblEipTempInact->Location = System::Drawing::Point(6, 94);
      this->lblEipTempInact->Name = L"lblEipTempInact";
      this->lblEipTempInact->Size = System::Drawing::Size(139, 13);
      this->lblEipTempInact->TabIndex = 6;
      this->lblEipTempInact->Text = L"Temperature of inactivation:";
      // 
      // snboxEipEnthAct
      // 
      this->snboxEipEnthAct->Enabled = false;
      this->snboxEipEnthAct->Location = System::Drawing::Point(261, 39);
      this->snboxEipEnthAct->Name = L"snboxEipEnthAct";
      this->snboxEipEnthAct->Size = System::Drawing::Size(100, 20);
      this->snboxEipEnthAct->TabIndex = 3;
      this->snboxEipEnthAct->Text = L"0";
      this->snboxEipEnthAct->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxEipEnthAct->Value = L"0";
      // 
      // lblEipEnthInact
      // 
      this->lblEipEnthInact->AutoSize = true;
      this->lblEipEnthInact->Location = System::Drawing::Point(6, 68);
      this->lblEipEnthInact->Name = L"lblEipEnthInact";
      this->lblEipEnthInact->Size = System::Drawing::Size(120, 13);
      this->lblEipEnthInact->TabIndex = 4;
      this->lblEipEnthInact->Text = L"Enthalpy of inactivation:";
      // 
      // snboxEipTempInact
      // 
      this->snboxEipTempInact->Enabled = false;
      this->snboxEipTempInact->Location = System::Drawing::Point(261, 91);
      this->snboxEipTempInact->Name = L"snboxEipTempInact";
      this->snboxEipTempInact->Size = System::Drawing::Size(100, 20);
      this->snboxEipTempInact->TabIndex = 7;
      this->snboxEipTempInact->Text = L"0";
      this->snboxEipTempInact->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxEipTempInact->Value = L"0";
      // 
      // lblEipEnthAct
      // 
      this->lblEipEnthAct->AutoSize = true;
      this->lblEipEnthAct->Location = System::Drawing::Point(6, 42);
      this->lblEipEnthAct->Name = L"lblEipEnthAct";
      this->lblEipEnthAct->Size = System::Drawing::Size(114, 13);
      this->lblEipEnthAct->TabIndex = 2;
      this->lblEipEnthAct->Text = L"Enthalpy of activiation:";
      // 
      // snboxEipEnthInact
      // 
      this->snboxEipEnthInact->Enabled = false;
      this->snboxEipEnthInact->Location = System::Drawing::Point(261, 65);
      this->snboxEipEnthInact->Name = L"snboxEipEnthInact";
      this->snboxEipEnthInact->Size = System::Drawing::Size(100, 20);
      this->snboxEipEnthInact->TabIndex = 5;
      this->snboxEipEnthInact->Text = L"0";
      this->snboxEipEnthInact->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxEipEnthInact->Value = L"0";
      // 
      // lblEipRo25
      // 
      this->lblEipRo25->AutoSize = true;
      this->lblEipRo25->Location = System::Drawing::Point(6, 16);
      this->lblEipRo25->Name = L"lblEipRo25";
      this->lblEipRo25->Size = System::Drawing::Size(94, 13);
      this->lblEipRo25->TabIndex = 0;
      this->lblEipRo25->Text = L"Development rate:";
      // 
      // tabInfections
      // 
      this->tabInfections->Location = System::Drawing::Point(4, 24);
      this->tabInfections->Name = L"tabInfections";
      this->tabInfections->Padding = System::Windows::Forms::Padding(3);
      this->tabInfections->Size = System::Drawing::Size(766, 272);
      this->tabInfections->TabIndex = 3;
      this->tabInfections->Text = L"Infection Introduction";
      this->tabInfections->UseVisualStyleBackColor = true;
      // 
      // tabDhsDss
      // 
      this->tabDhsDss->Controls->Add(this->dgvSequentials);
      this->tabDhsDss->Location = System::Drawing::Point(4, 24);
      this->tabDhsDss->Name = L"tabDhsDss";
      this->tabDhsDss->Padding = System::Windows::Forms::Padding(3);
      this->tabDhsDss->Size = System::Drawing::Size(766, 272);
      this->tabDhsDss->TabIndex = 4;
      this->tabDhsDss->Text = L"DHF/DSS";
      this->tabDhsDss->UseVisualStyleBackColor = true;
      // 
      // dgvSequentials
      // 
      this->dgvSequentials->AllowUserToAddRows = false;
      this->dgvSequentials->AllowUserToDeleteRows = false;
      this->dgvSequentials->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->dgvSequentials->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
      this->dgvSequentials->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
      this->dgvSequentials->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(6) {this->dgvcSequence, 
        this->dgvcSecondaryMinimum, this->dgcSecondaryMaximum, this->dgvcProbDhfDss, this->dgvcAtRiskCutoff, this->dgvcMortality});
      this->dgvSequentials->Location = System::Drawing::Point(6, 6);
      this->dgvSequentials->Name = L"dgvSequentials";
      this->dgvSequentials->RowHeadersVisible = false;
      this->dgvSequentials->Size = System::Drawing::Size(754, 260);
      this->dgvSequentials->TabIndex = 0;
      // 
      // dgvcSequence
      // 
      this->dgvcSequence->DataPropertyName = L"Sequence";
      dataGridViewCellStyle14->BackColor = System::Drawing::SystemColors::Control;
      this->dgvcSequence->DefaultCellStyle = dataGridViewCellStyle14;
      this->dgvcSequence->HeaderText = L"Sequence of Infection";
      this->dgvcSequence->Name = L"dgvcSequence";
      this->dgvcSequence->ReadOnly = true;
      // 
      // dgvcSecondaryMinimum
      // 
      this->dgvcSecondaryMinimum->DataPropertyName = L"MinMonths";
      this->dgvcSecondaryMinimum->HeaderText = L"Minimum (months)";
      this->dgvcSecondaryMinimum->Name = L"dgvcSecondaryMinimum";
      // 
      // dgcSecondaryMaximum
      // 
      this->dgcSecondaryMaximum->DataPropertyName = L"MaxMonths";
      this->dgcSecondaryMaximum->HeaderText = L"Maximum (months)";
      this->dgcSecondaryMaximum->Name = L"dgcSecondaryMaximum";
      // 
      // dgvcProbDhfDss
      // 
      this->dgvcProbDhfDss->DataPropertyName = L"Probability";
      this->dgvcProbDhfDss->HeaderText = L"Probability of DHF/DSS";
      this->dgvcProbDhfDss->Name = L"dgvcProbDhfDss";
      // 
      // dgvcAtRiskCutoff
      // 
      this->dgvcAtRiskCutoff->DataPropertyName = L"AtRiskCutoffAge";
      this->dgvcAtRiskCutoff->HeaderText = L"At-Risk Cutoff Age (years)";
      this->dgvcAtRiskCutoff->Name = L"dgvcAtRiskCutoff";
      // 
      // dgvcMortality
      // 
      this->dgvcMortality->DataPropertyName = L"Mortality";
      this->dgvcMortality->HeaderText = L"Mortality";
      this->dgvcMortality->Name = L"dgvcMortality";
      // 
      // errProDemographics
      // 
      this->errProDemographics->ContainerControl = this;
      // 
      // DensimPanel
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->BackColor = System::Drawing::Color::Transparent;
      this->Controls->Add(this->tabDensim);
      this->Controls->Add(this->btnRunSim);
      this->MinimumSize = System::Drawing::Size(786, 341);
      this->Name = L"DensimPanel";
      this->Padding = System::Windows::Forms::Padding(3);
      this->Size = System::Drawing::Size(786, 341);
      this->Load += gcnew System::EventHandler(this, &DensimPanel::OnLoad);
      this->tabDensim->ResumeLayout(false);
      this->tabDemographics->ResumeLayout(false);
      this->tabDemographics->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvDemographics))->EndInit();
      this->tabSerology->ResumeLayout(false);
      this->tabSerology->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvSerology))->EndInit();
      this->tabVirology->ResumeLayout(false);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvVirology))->EndInit();
      this->tabInfectionEip->ResumeLayout(false);
      this->tabHumToMosInfection->ResumeLayout(false);
      this->tabHumToMosInfection->PerformLayout();
      this->groupBox2->ResumeLayout(false);
      this->groupBox2->PerformLayout();
      this->tabEip->ResumeLayout(false);
      this->groupBox1->ResumeLayout(false);
      this->groupBox1->PerformLayout();
      this->gboxEipDevelopment->ResumeLayout(false);
      this->gboxEipDevelopment->PerformLayout();
      this->tabDhsDss->ResumeLayout(false);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvSequentials))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errProDemographics))->EndInit();
      this->ResumeLayout(false);

    }
#pragma endregion
  };
}
