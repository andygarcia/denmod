#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace gui {

	public ref class ResidualSprayForm : public System::Windows::Forms::Form
	{
	public:
    ResidualSprayForm( ResidualSpray ^ sr, BindingSource ^ locationBinding );
	protected:
		~ResidualSprayForm(void);

  private:
    void SetSchedulePanel(void);
  private: System::Windows::Forms::Panel^  panel1;

  private:
    ResidualSpray ^ ResidualSpray_;

  private:
    System::Void OnLoad( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnOk( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnCancel( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnScheduleChange( System::Object ^ sender, System::EventArgs ^ e );

  private:
    BindingSource ^ LocationBinding;
    gui::Location ^ ActiveLocation;

    UserControl ^ CurrentSchedulePanel;

  private: System::Windows::Forms::TextBox^  tboxName;
  private: System::Windows::Forms::Label^  lblName;
  private: System::Windows::Forms::Label^  lblInitialMortality;
  private: System::Windows::Forms::Label^  lblMaximumEffectPeriod;



  private: System::Windows::Forms::NumericUpDown^  numInitialMortality;
  private: System::Windows::Forms::NumericUpDown^  numMaximumEffectPeriod;


  private: System::Windows::Forms::Label^  lblSchedule;

  private: System::Windows::Forms::Button^  btnCancel;
  private: System::Windows::Forms::Button^  btnOk;
  private: System::Windows::Forms::Label^  lblResidualEffectPeriod;
  private: System::Windows::Forms::Label^  lblTreatedInteriorProportion;


  private: System::Windows::Forms::NumericUpDown^  numResidualEffectPeriod;
  private: System::Windows::Forms::NumericUpDown^  numTreatedInteriorProportion;
  private: System::Windows::Forms::Label^  lblTreatedHousesProportion;
  private: System::Windows::Forms::NumericUpDown^  numTreatedHousesProportion;
  private: System::Windows::Forms::NumericUpDown^  numOutdoorProportion;
  private: System::Windows::Forms::Label^  lblOutdoorProportion;
  private: System::Windows::Forms::ComboBox^  cboxSchedule;








	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->tboxName = (gcnew System::Windows::Forms::TextBox());
      this->lblName = (gcnew System::Windows::Forms::Label());
      this->lblInitialMortality = (gcnew System::Windows::Forms::Label());
      this->lblMaximumEffectPeriod = (gcnew System::Windows::Forms::Label());
      this->numInitialMortality = (gcnew System::Windows::Forms::NumericUpDown());
      this->numMaximumEffectPeriod = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblSchedule = (gcnew System::Windows::Forms::Label());
      this->btnCancel = (gcnew System::Windows::Forms::Button());
      this->btnOk = (gcnew System::Windows::Forms::Button());
      this->lblResidualEffectPeriod = (gcnew System::Windows::Forms::Label());
      this->lblTreatedInteriorProportion = (gcnew System::Windows::Forms::Label());
      this->numResidualEffectPeriod = (gcnew System::Windows::Forms::NumericUpDown());
      this->numTreatedInteriorProportion = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblTreatedHousesProportion = (gcnew System::Windows::Forms::Label());
      this->numTreatedHousesProportion = (gcnew System::Windows::Forms::NumericUpDown());
      this->numOutdoorProportion = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblOutdoorProportion = (gcnew System::Windows::Forms::Label());
      this->cboxSchedule = (gcnew System::Windows::Forms::ComboBox());
      this->panel1 = (gcnew System::Windows::Forms::Panel());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numInitialMortality))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMaximumEffectPeriod))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numResidualEffectPeriod))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numTreatedInteriorProportion))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numTreatedHousesProportion))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numOutdoorProportion))->BeginInit();
      this->SuspendLayout();
      // 
      // tboxName
      // 
      this->tboxName->Location = System::Drawing::Point(136, 12);
      this->tboxName->Name = L"tboxName";
      this->tboxName->ReadOnly = true;
      this->tboxName->Size = System::Drawing::Size(420, 20);
      this->tboxName->TabIndex = 1;
      // 
      // lblName
      // 
      this->lblName->AutoSize = true;
      this->lblName->Location = System::Drawing::Point(92, 15);
      this->lblName->Name = L"lblName";
      this->lblName->Size = System::Drawing::Size(38, 13);
      this->lblName->TabIndex = 0;
      this->lblName->Text = L"Name:";
      // 
      // lblInitialMortality
      // 
      this->lblInitialMortality->AutoSize = true;
      this->lblInitialMortality->Location = System::Drawing::Point(54, 40);
      this->lblInitialMortality->Name = L"lblInitialMortality";
      this->lblInitialMortality->Size = System::Drawing::Size(76, 13);
      this->lblInitialMortality->TabIndex = 2;
      this->lblInitialMortality->Text = L"Initial Mortality:";
      // 
      // lblMaximumEffectPeriod
      // 
      this->lblMaximumEffectPeriod->AutoSize = true;
      this->lblMaximumEffectPeriod->Location = System::Drawing::Point(12, 66);
      this->lblMaximumEffectPeriod->Name = L"lblMaximumEffectPeriod";
      this->lblMaximumEffectPeriod->Size = System::Drawing::Size(118, 13);
      this->lblMaximumEffectPeriod->TabIndex = 4;
      this->lblMaximumEffectPeriod->Text = L"Maximum Effect Period:";
      // 
      // numInitialMortality
      // 
      this->numInitialMortality->DecimalPlaces = 2;
      this->numInitialMortality->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 131072});
      this->numInitialMortality->Location = System::Drawing::Point(136, 38);
      this->numInitialMortality->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numInitialMortality->Name = L"numInitialMortality";
      this->numInitialMortality->Size = System::Drawing::Size(72, 20);
      this->numInitialMortality->TabIndex = 3;
      // 
      // numMaximumEffectPeriod
      // 
      this->numMaximumEffectPeriod->Location = System::Drawing::Point(136, 64);
      this->numMaximumEffectPeriod->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {365, 0, 0, 0});
      this->numMaximumEffectPeriod->Name = L"numMaximumEffectPeriod";
      this->numMaximumEffectPeriod->Size = System::Drawing::Size(72, 20);
      this->numMaximumEffectPeriod->TabIndex = 5;
      // 
      // lblSchedule
      // 
      this->lblSchedule->AutoSize = true;
      this->lblSchedule->Location = System::Drawing::Point(75, 119);
      this->lblSchedule->Name = L"lblSchedule";
      this->lblSchedule->Size = System::Drawing::Size(55, 13);
      this->lblSchedule->TabIndex = 14;
      this->lblSchedule->Text = L"Schedule:";
      // 
      // btnCancel
      // 
      this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
      this->btnCancel->Location = System::Drawing::Point(481, 349);
      this->btnCancel->Name = L"btnCancel";
      this->btnCancel->Size = System::Drawing::Size(75, 23);
      this->btnCancel->TabIndex = 18;
      this->btnCancel->Text = L"Cancel";
      this->btnCancel->UseVisualStyleBackColor = true;
      this->btnCancel->Click += gcnew System::EventHandler(this, &ResidualSprayForm::OnCancel);
      // 
      // btnOk
      // 
      this->btnOk->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->btnOk->Location = System::Drawing::Point(400, 349);
      this->btnOk->Name = L"btnOk";
      this->btnOk->Size = System::Drawing::Size(75, 23);
      this->btnOk->TabIndex = 17;
      this->btnOk->Text = L"OK";
      this->btnOk->UseVisualStyleBackColor = true;
      this->btnOk->Click += gcnew System::EventHandler(this, &ResidualSprayForm::OnOk);
      // 
      // lblResidualEffectPeriod
      // 
      this->lblResidualEffectPeriod->AutoSize = true;
      this->lblResidualEffectPeriod->Location = System::Drawing::Point(15, 92);
      this->lblResidualEffectPeriod->Name = L"lblResidualEffectPeriod";
      this->lblResidualEffectPeriod->Size = System::Drawing::Size(115, 13);
      this->lblResidualEffectPeriod->TabIndex = 6;
      this->lblResidualEffectPeriod->Text = L"Residual Effect Period:";
      // 
      // lblTreatedInteriorProportion
      // 
      this->lblTreatedInteriorProportion->AutoSize = true;
      this->lblTreatedInteriorProportion->Location = System::Drawing::Point(295, 40);
      this->lblTreatedInteriorProportion->Name = L"lblTreatedInteriorProportion";
      this->lblTreatedInteriorProportion->Size = System::Drawing::Size(183, 13);
      this->lblTreatedInteriorProportion->TabIndex = 8;
      this->lblTreatedInteriorProportion->Text = L"Proportion of interior surfaces treated:";
      // 
      // numResidualEffectPeriod
      // 
      this->numResidualEffectPeriod->Location = System::Drawing::Point(136, 90);
      this->numResidualEffectPeriod->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {365, 0, 0, 0});
      this->numResidualEffectPeriod->Name = L"numResidualEffectPeriod";
      this->numResidualEffectPeriod->Size = System::Drawing::Size(72, 20);
      this->numResidualEffectPeriod->TabIndex = 7;
      // 
      // numTreatedInteriorProportion
      // 
      this->numTreatedInteriorProportion->DecimalPlaces = 2;
      this->numTreatedInteriorProportion->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 131072});
      this->numTreatedInteriorProportion->Location = System::Drawing::Point(484, 38);
      this->numTreatedInteriorProportion->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numTreatedInteriorProportion->Name = L"numTreatedInteriorProportion";
      this->numTreatedInteriorProportion->Size = System::Drawing::Size(72, 20);
      this->numTreatedInteriorProportion->TabIndex = 9;
      // 
      // lblTreatedHousesProportion
      // 
      this->lblTreatedHousesProportion->AutoSize = true;
      this->lblTreatedHousesProportion->Location = System::Drawing::Point(335, 66);
      this->lblTreatedHousesProportion->Name = L"lblTreatedHousesProportion";
      this->lblTreatedHousesProportion->Size = System::Drawing::Size(143, 13);
      this->lblTreatedHousesProportion->TabIndex = 10;
      this->lblTreatedHousesProportion->Text = L"Proportion of houses treated:";
      // 
      // numTreatedHousesProportion
      // 
      this->numTreatedHousesProportion->DecimalPlaces = 2;
      this->numTreatedHousesProportion->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 131072});
      this->numTreatedHousesProportion->Location = System::Drawing::Point(484, 64);
      this->numTreatedHousesProportion->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numTreatedHousesProportion->Name = L"numTreatedHousesProportion";
      this->numTreatedHousesProportion->Size = System::Drawing::Size(72, 20);
      this->numTreatedHousesProportion->TabIndex = 11;
      // 
      // numOutdoorProportion
      // 
      this->numOutdoorProportion->DecimalPlaces = 3;
      this->numOutdoorProportion->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 131072});
      this->numOutdoorProportion->Location = System::Drawing::Point(484, 90);
      this->numOutdoorProportion->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numOutdoorProportion->Name = L"numOutdoorProportion";
      this->numOutdoorProportion->Size = System::Drawing::Size(72, 20);
      this->numOutdoorProportion->TabIndex = 13;
      // 
      // lblOutdoorProportion
      // 
      this->lblOutdoorProportion->AutoSize = true;
      this->lblOutdoorProportion->Location = System::Drawing::Point(299, 92);
      this->lblOutdoorProportion->Name = L"lblOutdoorProportion";
      this->lblOutdoorProportion->Size = System::Drawing::Size(179, 13);
      this->lblOutdoorProportion->TabIndex = 12;
      this->lblOutdoorProportion->Text = L"Proportion of adults resting outdoors:";
      // 
      // cboxSchedule
      // 
      this->cboxSchedule->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxSchedule->FormattingEnabled = true;
      this->cboxSchedule->Location = System::Drawing::Point(136, 116);
      this->cboxSchedule->Name = L"cboxSchedule";
      this->cboxSchedule->Size = System::Drawing::Size(122, 21);
      this->cboxSchedule->TabIndex = 15;
      this->cboxSchedule->SelectionChangeCommitted += gcnew System::EventHandler(this, &ResidualSprayForm::OnScheduleChange);
      // 
      // panel1
      // 
      this->panel1->Location = System::Drawing::Point(136, 143);
      this->panel1->Name = L"panel1";
      this->panel1->Size = System::Drawing::Size(420, 200);
      this->panel1->TabIndex = 16;
      this->panel1->Visible = false;
      // 
      // ResidualSprayForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(568, 384);
      this->Controls->Add(this->panel1);
      this->Controls->Add(this->cboxSchedule);
      this->Controls->Add(this->numOutdoorProportion);
      this->Controls->Add(this->lblOutdoorProportion);
      this->Controls->Add(this->btnOk);
      this->Controls->Add(this->btnCancel);
      this->Controls->Add(this->numTreatedHousesProportion);
      this->Controls->Add(this->numTreatedInteriorProportion);
      this->Controls->Add(this->numMaximumEffectPeriod);
      this->Controls->Add(this->lblTreatedHousesProportion);
      this->Controls->Add(this->numResidualEffectPeriod);
      this->Controls->Add(this->lblTreatedInteriorProportion);
      this->Controls->Add(this->numInitialMortality);
      this->Controls->Add(this->lblResidualEffectPeriod);
      this->Controls->Add(this->lblMaximumEffectPeriod);
      this->Controls->Add(this->lblInitialMortality);
      this->Controls->Add(this->tboxName);
      this->Controls->Add(this->lblSchedule);
      this->Controls->Add(this->lblName);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
      this->Name = L"ResidualSprayForm";
      this->ShowInTaskbar = false;
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
      this->Text = L"Residual Spray";
      this->Load += gcnew System::EventHandler(this, &ResidualSprayForm::OnLoad);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numInitialMortality))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMaximumEffectPeriod))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numResidualEffectPeriod))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numTreatedInteriorProportion))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numTreatedHousesProportion))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numOutdoorProportion))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
};
}
