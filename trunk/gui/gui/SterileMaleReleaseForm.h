#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace gui {

	public ref class SterileMaleReleaseForm : public System::Windows::Forms::Form
	{
	public:
    SterileMaleReleaseForm( SterileMaleRelease ^ sm, BindingSource ^ locationBinding );
	protected:
		~SterileMaleReleaseForm(void);

  private:
    void SetSchedulePanel(void);
  private: System::Windows::Forms::ComboBox^  cboxSchedule;
  private: System::Windows::Forms::Panel^  panel1;
  private: System::Windows::Forms::GroupBox^  gboxSchedule;


  private:
    SterileMaleRelease ^ SterileMaleRelease_;

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
  private: System::Windows::Forms::Label^  lblNumberReleased;

  private: System::Windows::Forms::Label^  lblSterilityRate;
  private: System::Windows::Forms::NumericUpDown^  numNumberReleased;

  private: System::Windows::Forms::NumericUpDown^  numSterilityRate;

  private: System::Windows::Forms::Label^  lblMaleToFemaleSurvivalRatio;

  private: System::Windows::Forms::Button^  btnCancel;
  private: System::Windows::Forms::Button^  btnOk;
  private: System::Windows::Forms::Label^  lblCompetitiveness;
  private: System::Windows::Forms::NumericUpDown^  numCompetitiveness;





  private: System::Windows::Forms::NumericUpDown^  numMaleToFemaleSurvivalRatio;















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
      this->lblNumberReleased = (gcnew System::Windows::Forms::Label());
      this->lblSterilityRate = (gcnew System::Windows::Forms::Label());
      this->numNumberReleased = (gcnew System::Windows::Forms::NumericUpDown());
      this->numSterilityRate = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblMaleToFemaleSurvivalRatio = (gcnew System::Windows::Forms::Label());
      this->btnCancel = (gcnew System::Windows::Forms::Button());
      this->btnOk = (gcnew System::Windows::Forms::Button());
      this->lblCompetitiveness = (gcnew System::Windows::Forms::Label());
      this->numCompetitiveness = (gcnew System::Windows::Forms::NumericUpDown());
      this->numMaleToFemaleSurvivalRatio = (gcnew System::Windows::Forms::NumericUpDown());
      this->cboxSchedule = (gcnew System::Windows::Forms::ComboBox());
      this->panel1 = (gcnew System::Windows::Forms::Panel());
      this->gboxSchedule = (gcnew System::Windows::Forms::GroupBox());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numNumberReleased))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numSterilityRate))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numCompetitiveness))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMaleToFemaleSurvivalRatio))->BeginInit();
      this->gboxSchedule->SuspendLayout();
      this->SuspendLayout();
      // 
      // tboxName
      // 
      this->tboxName->Location = System::Drawing::Point(56, 6);
      this->tboxName->Name = L"tboxName";
      this->tboxName->ReadOnly = true;
      this->tboxName->Size = System::Drawing::Size(396, 20);
      this->tboxName->TabIndex = 1;
      // 
      // lblName
      // 
      this->lblName->AutoSize = true;
      this->lblName->Location = System::Drawing::Point(12, 9);
      this->lblName->Name = L"lblName";
      this->lblName->Size = System::Drawing::Size(38, 13);
      this->lblName->TabIndex = 0;
      this->lblName->Text = L"Name:";
      // 
      // lblNumberReleased
      // 
      this->lblNumberReleased->AutoSize = true;
      this->lblNumberReleased->Location = System::Drawing::Point(12, 40);
      this->lblNumberReleased->Name = L"lblNumberReleased";
      this->lblNumberReleased->Size = System::Drawing::Size(123, 13);
      this->lblNumberReleased->TabIndex = 2;
      this->lblNumberReleased->Text = L"Number released per ha:";
      // 
      // lblSterilityRate
      // 
      this->lblSterilityRate->AutoSize = true;
      this->lblSterilityRate->Location = System::Drawing::Point(12, 66);
      this->lblSterilityRate->Name = L"lblSterilityRate";
      this->lblSterilityRate->Size = System::Drawing::Size(64, 13);
      this->lblSterilityRate->TabIndex = 4;
      this->lblSterilityRate->Text = L"Sterility rate:";
      // 
      // numNumberReleased
      // 
      this->numNumberReleased->Location = System::Drawing::Point(171, 38);
      this->numNumberReleased->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100000, 0, 0, 0});
      this->numNumberReleased->Name = L"numNumberReleased";
      this->numNumberReleased->Size = System::Drawing::Size(72, 20);
      this->numNumberReleased->TabIndex = 3;
      // 
      // numSterilityRate
      // 
      this->numSterilityRate->DecimalPlaces = 2;
      this->numSterilityRate->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 65536});
      this->numSterilityRate->Location = System::Drawing::Point(171, 64);
      this->numSterilityRate->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numSterilityRate->Name = L"numSterilityRate";
      this->numSterilityRate->Size = System::Drawing::Size(72, 20);
      this->numSterilityRate->TabIndex = 5;
      // 
      // lblMaleToFemaleSurvivalRatio
      // 
      this->lblMaleToFemaleSurvivalRatio->AutoSize = true;
      this->lblMaleToFemaleSurvivalRatio->Location = System::Drawing::Point(12, 118);
      this->lblMaleToFemaleSurvivalRatio->Name = L"lblMaleToFemaleSurvivalRatio";
      this->lblMaleToFemaleSurvivalRatio->Size = System::Drawing::Size(141, 13);
      this->lblMaleToFemaleSurvivalRatio->TabIndex = 8;
      this->lblMaleToFemaleSurvivalRatio->Text = L"Male to female survival ratio:";
      // 
      // btnCancel
      // 
      this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
      this->btnCancel->Location = System::Drawing::Point(377, 407);
      this->btnCancel->Name = L"btnCancel";
      this->btnCancel->Size = System::Drawing::Size(75, 23);
      this->btnCancel->TabIndex = 14;
      this->btnCancel->Text = L"Cancel";
      this->btnCancel->UseVisualStyleBackColor = true;
      this->btnCancel->Click += gcnew System::EventHandler(this, &SterileMaleReleaseForm::OnCancel);
      // 
      // btnOk
      // 
      this->btnOk->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->btnOk->Location = System::Drawing::Point(296, 407);
      this->btnOk->Name = L"btnOk";
      this->btnOk->Size = System::Drawing::Size(75, 23);
      this->btnOk->TabIndex = 13;
      this->btnOk->Text = L"OK";
      this->btnOk->UseVisualStyleBackColor = true;
      this->btnOk->Click += gcnew System::EventHandler(this, &SterileMaleReleaseForm::OnOk);
      // 
      // lblCompetitiveness
      // 
      this->lblCompetitiveness->AutoSize = true;
      this->lblCompetitiveness->Location = System::Drawing::Point(12, 92);
      this->lblCompetitiveness->Name = L"lblCompetitiveness";
      this->lblCompetitiveness->Size = System::Drawing::Size(87, 13);
      this->lblCompetitiveness->TabIndex = 6;
      this->lblCompetitiveness->Text = L"Competitiveness:";
      // 
      // numCompetitiveness
      // 
      this->numCompetitiveness->DecimalPlaces = 2;
      this->numCompetitiveness->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 131072});
      this->numCompetitiveness->Location = System::Drawing::Point(171, 90);
      this->numCompetitiveness->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numCompetitiveness->Name = L"numCompetitiveness";
      this->numCompetitiveness->Size = System::Drawing::Size(72, 20);
      this->numCompetitiveness->TabIndex = 7;
      // 
      // numMaleToFemaleSurvivalRatio
      // 
      this->numMaleToFemaleSurvivalRatio->DecimalPlaces = 2;
      this->numMaleToFemaleSurvivalRatio->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 131072});
      this->numMaleToFemaleSurvivalRatio->Location = System::Drawing::Point(171, 116);
      this->numMaleToFemaleSurvivalRatio->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numMaleToFemaleSurvivalRatio->Name = L"numMaleToFemaleSurvivalRatio";
      this->numMaleToFemaleSurvivalRatio->Size = System::Drawing::Size(72, 20);
      this->numMaleToFemaleSurvivalRatio->TabIndex = 9;
      // 
      // cboxSchedule
      // 
      this->cboxSchedule->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxSchedule->FormattingEnabled = true;
      this->cboxSchedule->Location = System::Drawing::Point(10, 19);
      this->cboxSchedule->Name = L"cboxSchedule";
      this->cboxSchedule->Size = System::Drawing::Size(122, 21);
      this->cboxSchedule->TabIndex = 11;
      this->cboxSchedule->SelectionChangeCommitted += gcnew System::EventHandler(this, &SterileMaleReleaseForm::OnScheduleChange);
      // 
      // panel1
      // 
      this->panel1->Location = System::Drawing::Point(10, 46);
      this->panel1->Name = L"panel1";
      this->panel1->Size = System::Drawing::Size(420, 200);
      this->panel1->TabIndex = 12;
      this->panel1->Visible = false;
      // 
      // gboxSchedule
      // 
      this->gboxSchedule->Controls->Add(this->cboxSchedule);
      this->gboxSchedule->Controls->Add(this->panel1);
      this->gboxSchedule->Location = System::Drawing::Point(12, 142);
      this->gboxSchedule->Name = L"gboxSchedule";
      this->gboxSchedule->Size = System::Drawing::Size(440, 259);
      this->gboxSchedule->TabIndex = 15;
      this->gboxSchedule->TabStop = false;
      this->gboxSchedule->Text = L"Schedule";
      // 
      // SterileMaleReleaseForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(467, 441);
      this->Controls->Add(this->gboxSchedule);
      this->Controls->Add(this->btnOk);
      this->Controls->Add(this->btnCancel);
      this->Controls->Add(this->numSterilityRate);
      this->Controls->Add(this->numMaleToFemaleSurvivalRatio);
      this->Controls->Add(this->numCompetitiveness);
      this->Controls->Add(this->numNumberReleased);
      this->Controls->Add(this->lblCompetitiveness);
      this->Controls->Add(this->lblSterilityRate);
      this->Controls->Add(this->lblNumberReleased);
      this->Controls->Add(this->tboxName);
      this->Controls->Add(this->lblMaleToFemaleSurvivalRatio);
      this->Controls->Add(this->lblName);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
      this->Name = L"SterileMaleReleaseForm";
      this->ShowInTaskbar = false;
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
      this->Text = L"Sterile Male Release";
      this->Load += gcnew System::EventHandler(this, &SterileMaleReleaseForm::OnLoad);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numNumberReleased))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numSterilityRate))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numCompetitiveness))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMaleToFemaleSurvivalRatio))->EndInit();
      this->gboxSchedule->ResumeLayout(false);
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
};
}
