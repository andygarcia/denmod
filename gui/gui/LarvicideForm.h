#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace gui {

	public ref class LarvicideForm : public System::Windows::Forms::Form
	{
	public:
    LarvicideForm( Larvicide ^ li, BindingSource ^ locationBinding );
		~LarvicideForm();

    void SetSchedulePanel(void);
  private: System::Windows::Forms::GroupBox^  gboxEffects;
  private: System::Windows::Forms::Panel^  panel1;
  public: 

  private:
    Larvicide ^ Larvicide_;

  private:
    System::Void OnLoad( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnAddContainer( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnRemoveContainer( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnOk( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnCancel( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnScheduleChange( System::Object ^ sender, System::EventArgs ^ e );

  private:
    BindingSource ^ LocationBinding;
    gui::Location ^ ActiveLocation;

    UserControl ^ CurrentSchedulePanel;

  private: System::Windows::Forms::Label^  lblName;
  private: System::Windows::Forms::TextBox^  tboxName;

  private: System::Windows::Forms::Label^  lblTargets;
  private: System::Windows::Forms::DataGridView^  dgvTargets;
  private: System::Windows::Forms::Button^  btnAddContainer;

  private: System::Windows::Forms::Label^  lblSchedule;

  private: System::Windows::Forms::Button^  btnOK;
  private: System::Windows::Forms::Button^  btnCancel;
  private: System::Windows::Forms::Button^  btnRemoveContainer;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcName;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcRateOfTreatment;
  private: System::Windows::Forms::Label^  lblLagPeriod;
  private: System::Windows::Forms::NumericUpDown^  numLagPeriod;
  private: System::Windows::Forms::Label^  lblMaxEffectPeriod;
  private: System::Windows::Forms::NumericUpDown^  numMaxEffectPeriod;
  private: System::Windows::Forms::Label^  lblDeclineEffectPeriod;
  private: System::Windows::Forms::NumericUpDown^  numDeclineEffectPeriod;
  private: System::Windows::Forms::Label^  lblInitMortality;
  private: System::Windows::Forms::NumericUpDown^  numInitMortality;
  private: System::Windows::Forms::CheckBox^  chkEffectLost;
  private: System::Windows::Forms::ComboBox^  cboxSchedule;












	private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->lblName = (gcnew System::Windows::Forms::Label());
      this->tboxName = (gcnew System::Windows::Forms::TextBox());
      this->lblTargets = (gcnew System::Windows::Forms::Label());
      this->dgvTargets = (gcnew System::Windows::Forms::DataGridView());
      this->dgvcName = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcRateOfTreatment = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->btnCancel = (gcnew System::Windows::Forms::Button());
      this->btnOK = (gcnew System::Windows::Forms::Button());
      this->btnAddContainer = (gcnew System::Windows::Forms::Button());
      this->lblSchedule = (gcnew System::Windows::Forms::Label());
      this->btnRemoveContainer = (gcnew System::Windows::Forms::Button());
      this->lblLagPeriod = (gcnew System::Windows::Forms::Label());
      this->numLagPeriod = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblMaxEffectPeriod = (gcnew System::Windows::Forms::Label());
      this->numMaxEffectPeriod = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblDeclineEffectPeriod = (gcnew System::Windows::Forms::Label());
      this->numDeclineEffectPeriod = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblInitMortality = (gcnew System::Windows::Forms::Label());
      this->numInitMortality = (gcnew System::Windows::Forms::NumericUpDown());
      this->chkEffectLost = (gcnew System::Windows::Forms::CheckBox());
      this->cboxSchedule = (gcnew System::Windows::Forms::ComboBox());
      this->gboxEffects = (gcnew System::Windows::Forms::GroupBox());
      this->panel1 = (gcnew System::Windows::Forms::Panel());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvTargets))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numLagPeriod))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMaxEffectPeriod))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numDeclineEffectPeriod))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numInitMortality))->BeginInit();
      this->gboxEffects->SuspendLayout();
      this->SuspendLayout();
      // 
      // lblName
      // 
      this->lblName->AutoSize = true;
      this->lblName->Location = System::Drawing::Point(29, 15);
      this->lblName->Name = L"lblName";
      this->lblName->Size = System::Drawing::Size(38, 13);
      this->lblName->TabIndex = 0;
      this->lblName->Text = L"Name:";
      // 
      // tboxName
      // 
      this->tboxName->Location = System::Drawing::Point(73, 12);
      this->tboxName->Name = L"tboxName";
      this->tboxName->ReadOnly = true;
      this->tboxName->Size = System::Drawing::Size(420, 20);
      this->tboxName->TabIndex = 1;
      // 
      // lblTargets
      // 
      this->lblTargets->AutoSize = true;
      this->lblTargets->Location = System::Drawing::Point(21, 39);
      this->lblTargets->Name = L"lblTargets";
      this->lblTargets->Size = System::Drawing::Size(46, 13);
      this->lblTargets->TabIndex = 2;
      this->lblTargets->Text = L"Targets:";
      // 
      // dgvTargets
      // 
      this->dgvTargets->AllowUserToAddRows = false;
      this->dgvTargets->AllowUserToDeleteRows = false;
      this->dgvTargets->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
      this->dgvTargets->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {this->dgvcName, 
        this->dgvcRateOfTreatment});
      this->dgvTargets->Location = System::Drawing::Point(73, 39);
      this->dgvTargets->Name = L"dgvTargets";
      this->dgvTargets->RowHeadersVisible = false;
      this->dgvTargets->Size = System::Drawing::Size(420, 194);
      this->dgvTargets->TabIndex = 3;
      // 
      // dgvcName
      // 
      this->dgvcName->DataPropertyName = L"Name";
      this->dgvcName->HeaderText = L"Name";
      this->dgvcName->Name = L"dgvcName";
      this->dgvcName->ReadOnly = true;
      // 
      // dgvcRateOfTreatment
      // 
      this->dgvcRateOfTreatment->DataPropertyName = L"RateOfTreatment";
      this->dgvcRateOfTreatment->HeaderText = L"Rate of Treatment";
      this->dgvcRateOfTreatment->Name = L"dgvcRateOfTreatment";
      // 
      // btnCancel
      // 
      this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
      this->btnCancel->Location = System::Drawing::Point(418, 608);
      this->btnCancel->Name = L"btnCancel";
      this->btnCancel->Size = System::Drawing::Size(75, 23);
      this->btnCancel->TabIndex = 17;
      this->btnCancel->Text = L"Cancel";
      this->btnCancel->UseVisualStyleBackColor = true;
      this->btnCancel->Click += gcnew System::EventHandler(this, &LarvicideForm::OnCancel);
      // 
      // btnOK
      // 
      this->btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->btnOK->Location = System::Drawing::Point(337, 608);
      this->btnOK->Name = L"btnOK";
      this->btnOK->Size = System::Drawing::Size(75, 23);
      this->btnOK->TabIndex = 16;
      this->btnOK->Text = L"OK";
      this->btnOK->UseVisualStyleBackColor = true;
      this->btnOK->Click += gcnew System::EventHandler(this, &LarvicideForm::OnOk);
      // 
      // btnAddContainer
      // 
      this->btnAddContainer->Location = System::Drawing::Point(73, 239);
      this->btnAddContainer->Name = L"btnAddContainer";
      this->btnAddContainer->Size = System::Drawing::Size(104, 23);
      this->btnAddContainer->TabIndex = 4;
      this->btnAddContainer->Text = L"Add Container";
      this->btnAddContainer->UseVisualStyleBackColor = true;
      this->btnAddContainer->Click += gcnew System::EventHandler(this, &LarvicideForm::OnAddContainer);
      // 
      // lblSchedule
      // 
      this->lblSchedule->AutoSize = true;
      this->lblSchedule->Location = System::Drawing::Point(12, 378);
      this->lblSchedule->Name = L"lblSchedule";
      this->lblSchedule->Size = System::Drawing::Size(55, 13);
      this->lblSchedule->TabIndex = 15;
      this->lblSchedule->Text = L"Schedule:";
      // 
      // btnRemoveContainer
      // 
      this->btnRemoveContainer->Location = System::Drawing::Point(183, 239);
      this->btnRemoveContainer->Name = L"btnRemoveContainer";
      this->btnRemoveContainer->Size = System::Drawing::Size(104, 23);
      this->btnRemoveContainer->TabIndex = 5;
      this->btnRemoveContainer->Text = L"Remove Container";
      this->btnRemoveContainer->UseVisualStyleBackColor = true;
      this->btnRemoveContainer->Click += gcnew System::EventHandler(this, &LarvicideForm::OnRemoveContainer);
      // 
      // lblLagPeriod
      // 
      this->lblLagPeriod->AutoSize = true;
      this->lblLagPeriod->Location = System::Drawing::Point(6, 21);
      this->lblLagPeriod->Name = L"lblLagPeriod";
      this->lblLagPeriod->Size = System::Drawing::Size(92, 13);
      this->lblLagPeriod->TabIndex = 6;
      this->lblLagPeriod->Text = L"Lag Period (days):";
      // 
      // numLagPeriod
      // 
      this->numLagPeriod->Location = System::Drawing::Point(161, 19);
      this->numLagPeriod->Name = L"numLagPeriod";
      this->numLagPeriod->Size = System::Drawing::Size(60, 20);
      this->numLagPeriod->TabIndex = 7;
      // 
      // lblMaxEffectPeriod
      // 
      this->lblMaxEffectPeriod->AutoSize = true;
      this->lblMaxEffectPeriod->Location = System::Drawing::Point(6, 47);
      this->lblMaxEffectPeriod->Name = L"lblMaxEffectPeriod";
      this->lblMaxEffectPeriod->Size = System::Drawing::Size(149, 13);
      this->lblMaxEffectPeriod->TabIndex = 8;
      this->lblMaxEffectPeriod->Text = L"Maximum Effect Period (days):";
      // 
      // numMaxEffectPeriod
      // 
      this->numMaxEffectPeriod->Location = System::Drawing::Point(161, 45);
      this->numMaxEffectPeriod->Name = L"numMaxEffectPeriod";
      this->numMaxEffectPeriod->Size = System::Drawing::Size(60, 20);
      this->numMaxEffectPeriod->TabIndex = 9;
      // 
      // lblDeclineEffectPeriod
      // 
      this->lblDeclineEffectPeriod->AutoSize = true;
      this->lblDeclineEffectPeriod->Location = System::Drawing::Point(6, 73);
      this->lblDeclineEffectPeriod->Name = L"lblDeclineEffectPeriod";
      this->lblDeclineEffectPeriod->Size = System::Drawing::Size(149, 13);
      this->lblDeclineEffectPeriod->TabIndex = 10;
      this->lblDeclineEffectPeriod->Text = L"Declining Effect Period (days):";
      // 
      // numDeclineEffectPeriod
      // 
      this->numDeclineEffectPeriod->Location = System::Drawing::Point(161, 71);
      this->numDeclineEffectPeriod->Name = L"numDeclineEffectPeriod";
      this->numDeclineEffectPeriod->Size = System::Drawing::Size(60, 20);
      this->numDeclineEffectPeriod->TabIndex = 11;
      // 
      // lblInitMortality
      // 
      this->lblInitMortality->AutoSize = true;
      this->lblInitMortality->Location = System::Drawing::Point(231, 21);
      this->lblInitMortality->Name = L"lblInitMortality";
      this->lblInitMortality->Size = System::Drawing::Size(76, 13);
      this->lblInitMortality->TabIndex = 12;
      this->lblInitMortality->Text = L"Initial Mortality:";
      // 
      // numInitMortality
      // 
      this->numInitMortality->DecimalPlaces = 2;
      this->numInitMortality->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 131072});
      this->numInitMortality->Location = System::Drawing::Point(354, 19);
      this->numInitMortality->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numInitMortality->Name = L"numInitMortality";
      this->numInitMortality->Size = System::Drawing::Size(60, 20);
      this->numInitMortality->TabIndex = 13;
      // 
      // chkEffectLost
      // 
      this->chkEffectLost->AutoSize = true;
      this->chkEffectLost->Location = System::Drawing::Point(234, 46);
      this->chkEffectLost->Name = L"chkEffectLost";
      this->chkEffectLost->Size = System::Drawing::Size(153, 17);
      this->chkEffectLost->TabIndex = 14;
      this->chkEffectLost->Text = L"Effect lost if container dries";
      this->chkEffectLost->UseVisualStyleBackColor = true;
      // 
      // cboxSchedule
      // 
      this->cboxSchedule->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxSchedule->FormattingEnabled = true;
      this->cboxSchedule->Location = System::Drawing::Point(73, 375);
      this->cboxSchedule->Name = L"cboxSchedule";
      this->cboxSchedule->Size = System::Drawing::Size(122, 21);
      this->cboxSchedule->TabIndex = 18;
      this->cboxSchedule->SelectionChangeCommitted += gcnew System::EventHandler(this, &LarvicideForm::OnScheduleChange);
      // 
      // gboxEffects
      // 
      this->gboxEffects->Controls->Add(this->numLagPeriod);
      this->gboxEffects->Controls->Add(this->numInitMortality);
      this->gboxEffects->Controls->Add(this->lblLagPeriod);
      this->gboxEffects->Controls->Add(this->numDeclineEffectPeriod);
      this->gboxEffects->Controls->Add(this->chkEffectLost);
      this->gboxEffects->Controls->Add(this->lblDeclineEffectPeriod);
      this->gboxEffects->Controls->Add(this->lblMaxEffectPeriod);
      this->gboxEffects->Controls->Add(this->lblInitMortality);
      this->gboxEffects->Controls->Add(this->numMaxEffectPeriod);
      this->gboxEffects->Location = System::Drawing::Point(73, 268);
      this->gboxEffects->Name = L"gboxEffects";
      this->gboxEffects->Size = System::Drawing::Size(420, 101);
      this->gboxEffects->TabIndex = 20;
      this->gboxEffects->TabStop = false;
      this->gboxEffects->Text = L"Larvicide Effects";
      // 
      // panel1
      // 
      this->panel1->Location = System::Drawing::Point(73, 402);
      this->panel1->Name = L"panel1";
      this->panel1->Size = System::Drawing::Size(420, 200);
      this->panel1->TabIndex = 21;
      this->panel1->Visible = false;
      // 
      // LarvicideForm
      // 
      this->AcceptButton = this->btnOK;
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->CancelButton = this->btnCancel;
      this->ClientSize = System::Drawing::Size(505, 643);
      this->Controls->Add(this->panel1);
      this->Controls->Add(this->gboxEffects);
      this->Controls->Add(this->cboxSchedule);
      this->Controls->Add(this->lblSchedule);
      this->Controls->Add(this->btnRemoveContainer);
      this->Controls->Add(this->btnAddContainer);
      this->Controls->Add(this->btnOK);
      this->Controls->Add(this->btnCancel);
      this->Controls->Add(this->dgvTargets);
      this->Controls->Add(this->lblTargets);
      this->Controls->Add(this->tboxName);
      this->Controls->Add(this->lblName);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
      this->Name = L"LarvicideForm";
      this->ShowInTaskbar = false;
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
      this->Text = L"Larvicide";
      this->Load += gcnew System::EventHandler(this, &LarvicideForm::OnLoad);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvTargets))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numLagPeriod))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMaxEffectPeriod))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numDeclineEffectPeriod))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numInitMortality))->EndInit();
      this->gboxEffects->ResumeLayout(false);
      this->gboxEffects->PerformLayout();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
};
}
