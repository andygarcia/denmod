#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace gui {

	public ref class FoodFitterForm : public System::Windows::Forms::Form
	{
	public:
    FoodFitterForm( gui::Location ^ location );
	protected:
		~FoodFitterForm();

  private:
    System::Void OnNextIteration(System::Object ^ sender, System::EventArgs^ e);
    System::Void OnLoad(System::Object ^ sender, System::EventArgs ^ e);
    System::Void OnSave(System::Object ^ sender, System::EventArgs ^ e);
    System::Void OnCancel(System::Object ^ sender, System::EventArgs ^ e);

  private:
    gui::Location ^ Location_;
    BindingSource ^ ContainerBinding_;

  private: System::Windows::Forms::Label^  lblRuns;
  private: System::Windows::Forms::NumericUpDown^  numRuns;

  private: System::Windows::Forms::Label^  lblSurveyStart;
  private: System::Windows::Forms::Label^  lblSurveyEnd;
  private: System::Windows::Forms::DateTimePicker^  dateTimeSurveyStart;
  private: System::Windows::Forms::DateTimePicker^  dateTimeSurveyStop;


  private: System::Windows::Forms::DataGridView^  dgvFit;

  private: System::Windows::Forms::Label^  lblTotalObserved;


  private: System::Windows::Forms::Label^  lblTotalPredicted;


  private: System::Windows::Forms::Label^  lblTotalDifference;


  private: System::Windows::Forms::Label^  lblTotalRatio;


  private: System::Windows::Forms::Button^  btnNext;
  private: System::Windows::Forms::Button^  btnCancel;
  private: System::Windows::Forms::Button^  btnSave;








  private: ctrl::ScientificNotationTextBox^  snboxTotalPredicted;
  private: ctrl::ScientificNotationTextBox^  snboxTotalObserved;
  private: ctrl::ScientificNotationTextBox^  snboxTotalDifference;
  private: ctrl::ScientificNotationTextBox^  snboxTotalRatio;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcContainer;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcDensity;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcObservedPupaeContainer;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcObservedHectare;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcDailyFood;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcPredictedPupaeContainer;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcPredictedPupaeHectare;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcDifferenceContainer;


























































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
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle5 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle6 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle7 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle8 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      this->numRuns = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblRuns = (gcnew System::Windows::Forms::Label());
      this->dgvFit = (gcnew System::Windows::Forms::DataGridView());
      this->lblSurveyStart = (gcnew System::Windows::Forms::Label());
      this->dateTimeSurveyStart = (gcnew System::Windows::Forms::DateTimePicker());
      this->dateTimeSurveyStop = (gcnew System::Windows::Forms::DateTimePicker());
      this->lblSurveyEnd = (gcnew System::Windows::Forms::Label());
      this->btnNext = (gcnew System::Windows::Forms::Button());
      this->btnCancel = (gcnew System::Windows::Forms::Button());
      this->btnSave = (gcnew System::Windows::Forms::Button());
      this->lblTotalObserved = (gcnew System::Windows::Forms::Label());
      this->lblTotalPredicted = (gcnew System::Windows::Forms::Label());
      this->lblTotalDifference = (gcnew System::Windows::Forms::Label());
      this->lblTotalRatio = (gcnew System::Windows::Forms::Label());
      this->snboxTotalPredicted = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxTotalObserved = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxTotalDifference = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxTotalRatio = (gcnew ctrl::ScientificNotationTextBox());
      this->dgvcContainer = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcDensity = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcObservedPupaeContainer = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcObservedHectare = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcDailyFood = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcPredictedPupaeContainer = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcPredictedPupaeHectare = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcDifferenceContainer = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numRuns))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvFit))->BeginInit();
      this->SuspendLayout();
      // 
      // numRuns
      // 
      this->numRuns->Location = System::Drawing::Point(111, 12);
      this->numRuns->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numRuns->Name = L"numRuns";
      this->numRuns->Size = System::Drawing::Size(81, 20);
      this->numRuns->TabIndex = 1;
      this->numRuns->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {5, 0, 0, 0});
      // 
      // lblRuns
      // 
      this->lblRuns->AutoSize = true;
      this->lblRuns->Location = System::Drawing::Point(12, 14);
      this->lblRuns->Name = L"lblRuns";
      this->lblRuns->Size = System::Drawing::Size(93, 13);
      this->lblRuns->TabIndex = 0;
      this->lblRuns->Text = L"Runs per iteration:";
      // 
      // dgvFit
      // 
      this->dgvFit->AllowUserToAddRows = false;
      this->dgvFit->AllowUserToDeleteRows = false;
      this->dgvFit->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->dgvFit->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
      this->dgvFit->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
      this->dgvFit->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(8) {this->dgvcContainer, 
        this->dgvcDensity, this->dgvcObservedPupaeContainer, this->dgvcObservedHectare, this->dgvcDailyFood, this->dgvcPredictedPupaeContainer, 
        this->dgvcPredictedPupaeHectare, this->dgvcDifferenceContainer});
      this->dgvFit->Location = System::Drawing::Point(12, 67);
      this->dgvFit->Name = L"dgvFit";
      this->dgvFit->RowHeadersVisible = false;
      this->dgvFit->Size = System::Drawing::Size(788, 273);
      this->dgvFit->TabIndex = 8;
      // 
      // lblSurveyStart
      // 
      this->lblSurveyStart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->lblSurveyStart->AutoSize = true;
      this->lblSurveyStart->Location = System::Drawing::Point(426, 16);
      this->lblSurveyStart->Name = L"lblSurveyStart";
      this->lblSurveyStart->Size = System::Drawing::Size(168, 13);
      this->lblSurveyStart->TabIndex = 4;
      this->lblSurveyStart->Text = L"Observed counts date range from:";
      // 
      // dateTimeSurveyStart
      // 
      this->dateTimeSurveyStart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->dateTimeSurveyStart->Location = System::Drawing::Point(600, 12);
      this->dateTimeSurveyStart->Name = L"dateTimeSurveyStart";
      this->dateTimeSurveyStart->Size = System::Drawing::Size(200, 20);
      this->dateTimeSurveyStart->TabIndex = 5;
      // 
      // dateTimeSurveyStop
      // 
      this->dateTimeSurveyStop->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->dateTimeSurveyStop->Location = System::Drawing::Point(600, 38);
      this->dateTimeSurveyStop->Name = L"dateTimeSurveyStop";
      this->dateTimeSurveyStop->Size = System::Drawing::Size(200, 20);
      this->dateTimeSurveyStop->TabIndex = 7;
      // 
      // lblSurveyEnd
      // 
      this->lblSurveyEnd->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->lblSurveyEnd->AutoSize = true;
      this->lblSurveyEnd->Location = System::Drawing::Point(575, 42);
      this->lblSurveyEnd->Name = L"lblSurveyEnd";
      this->lblSurveyEnd->Size = System::Drawing::Size(19, 13);
      this->lblSurveyEnd->TabIndex = 6;
      this->lblSurveyEnd->Text = L"to:";
      // 
      // btnNext
      // 
      this->btnNext->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
      this->btnNext->Location = System::Drawing::Point(12, 398);
      this->btnNext->Name = L"btnNext";
      this->btnNext->Size = System::Drawing::Size(93, 23);
      this->btnNext->TabIndex = 17;
      this->btnNext->Text = L"Next Iteration";
      this->btnNext->UseVisualStyleBackColor = true;
      this->btnNext->Click += gcnew System::EventHandler(this, &FoodFitterForm::OnNextIteration);
      // 
      // btnCancel
      // 
      this->btnCancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
      this->btnCancel->Location = System::Drawing::Point(725, 398);
      this->btnCancel->Name = L"btnCancel";
      this->btnCancel->Size = System::Drawing::Size(75, 23);
      this->btnCancel->TabIndex = 19;
      this->btnCancel->Text = L"Close";
      this->btnCancel->UseVisualStyleBackColor = true;
      this->btnCancel->Click += gcnew System::EventHandler(this, &FoodFitterForm::OnCancel);
      // 
      // btnSave
      // 
      this->btnSave->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnSave->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->btnSave->Location = System::Drawing::Point(644, 398);
      this->btnSave->Name = L"btnSave";
      this->btnSave->Size = System::Drawing::Size(75, 23);
      this->btnSave->TabIndex = 18;
      this->btnSave->Text = L"Save";
      this->btnSave->UseVisualStyleBackColor = true;
      this->btnSave->Click += gcnew System::EventHandler(this, &FoodFitterForm::OnSave);
      // 
      // lblTotalObserved
      // 
      this->lblTotalObserved->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->lblTotalObserved->AutoSize = true;
      this->lblTotalObserved->Location = System::Drawing::Point(316, 349);
      this->lblTotalObserved->Name = L"lblTotalObserved";
      this->lblTotalObserved->Size = System::Drawing::Size(147, 13);
      this->lblTotalObserved->TabIndex = 9;
      this->lblTotalObserved->Text = L"Total observed pupae per ha:";
      // 
      // lblTotalPredicted
      // 
      this->lblTotalPredicted->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->lblTotalPredicted->AutoSize = true;
      this->lblTotalPredicted->Location = System::Drawing::Point(316, 375);
      this->lblTotalPredicted->Name = L"lblTotalPredicted";
      this->lblTotalPredicted->Size = System::Drawing::Size(147, 13);
      this->lblTotalPredicted->TabIndex = 11;
      this->lblTotalPredicted->Text = L"Total predicted pupae per ha:";
      // 
      // lblTotalDifference
      // 
      this->lblTotalDifference->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->lblTotalDifference->AutoSize = true;
      this->lblTotalDifference->Location = System::Drawing::Point(596, 349);
      this->lblTotalDifference->Name = L"lblTotalDifference";
      this->lblTotalDifference->Size = System::Drawing::Size(98, 13);
      this->lblTotalDifference->TabIndex = 13;
      this->lblTotalDifference->Text = L"Difference in totals:";
      // 
      // lblTotalRatio
      // 
      this->lblTotalRatio->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->lblTotalRatio->AutoSize = true;
      this->lblTotalRatio->Location = System::Drawing::Point(619, 375);
      this->lblTotalRatio->Name = L"lblTotalRatio";
      this->lblTotalRatio->Size = System::Drawing::Size(75, 13);
      this->lblTotalRatio->TabIndex = 15;
      this->lblTotalRatio->Text = L"Ratio of totals:";
      // 
      // snboxTotalPredicted
      // 
      this->snboxTotalPredicted->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->snboxTotalPredicted->Location = System::Drawing::Point(469, 372);
      this->snboxTotalPredicted->Name = L"snboxTotalPredicted";
      this->snboxTotalPredicted->ReadOnly = true;
      this->snboxTotalPredicted->Size = System::Drawing::Size(100, 20);
      this->snboxTotalPredicted->TabIndex = 20;
      this->snboxTotalPredicted->Text = L"0";
      this->snboxTotalPredicted->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTotalPredicted->Value = L"0";
      // 
      // snboxTotalObserved
      // 
      this->snboxTotalObserved->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->snboxTotalObserved->Location = System::Drawing::Point(469, 346);
      this->snboxTotalObserved->Name = L"snboxTotalObserved";
      this->snboxTotalObserved->ReadOnly = true;
      this->snboxTotalObserved->Size = System::Drawing::Size(100, 20);
      this->snboxTotalObserved->TabIndex = 20;
      this->snboxTotalObserved->Text = L"0";
      this->snboxTotalObserved->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTotalObserved->Value = L"0";
      // 
      // snboxTotalDifference
      // 
      this->snboxTotalDifference->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->snboxTotalDifference->Location = System::Drawing::Point(700, 346);
      this->snboxTotalDifference->Name = L"snboxTotalDifference";
      this->snboxTotalDifference->ReadOnly = true;
      this->snboxTotalDifference->Size = System::Drawing::Size(100, 20);
      this->snboxTotalDifference->TabIndex = 20;
      this->snboxTotalDifference->Text = L"0";
      this->snboxTotalDifference->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTotalDifference->Value = L"0";
      // 
      // snboxTotalRatio
      // 
      this->snboxTotalRatio->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->snboxTotalRatio->Location = System::Drawing::Point(700, 372);
      this->snboxTotalRatio->Name = L"snboxTotalRatio";
      this->snboxTotalRatio->ReadOnly = true;
      this->snboxTotalRatio->Size = System::Drawing::Size(100, 20);
      this->snboxTotalRatio->TabIndex = 20;
      this->snboxTotalRatio->Text = L"0";
      this->snboxTotalRatio->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTotalRatio->Value = L"0";
      // 
      // dgvcContainer
      // 
      this->dgvcContainer->DataPropertyName = L"Name";
      dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
      this->dgvcContainer->DefaultCellStyle = dataGridViewCellStyle1;
      this->dgvcContainer->HeaderText = L"Container";
      this->dgvcContainer->Name = L"dgvcContainer";
      this->dgvcContainer->ReadOnly = true;
      // 
      // dgvcDensity
      // 
      this->dgvcDensity->DataPropertyName = L"Density";
      dataGridViewCellStyle2->BackColor = System::Drawing::SystemColors::Control;
      this->dgvcDensity->DefaultCellStyle = dataGridViewCellStyle2;
      this->dgvcDensity->HeaderText = L"Container Density (#/ha)";
      this->dgvcDensity->Name = L"dgvcDensity";
      this->dgvcDensity->ReadOnly = true;
      // 
      // dgvcObservedPupaeContainer
      // 
      this->dgvcObservedPupaeContainer->DataPropertyName = L"ObservedPerContainer";
      dataGridViewCellStyle3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->dgvcObservedPupaeContainer->DefaultCellStyle = dataGridViewCellStyle3;
      this->dgvcObservedPupaeContainer->FillWeight = 75;
      this->dgvcObservedPupaeContainer->HeaderText = L"Observed Pupae per Container";
      this->dgvcObservedPupaeContainer->Name = L"dgvcObservedPupaeContainer";
      // 
      // dgvcObservedHectare
      // 
      this->dgvcObservedHectare->DataPropertyName = L"ObservedPerHectare";
      dataGridViewCellStyle4->BackColor = System::Drawing::SystemColors::Control;
      this->dgvcObservedHectare->DefaultCellStyle = dataGridViewCellStyle4;
      this->dgvcObservedHectare->HeaderText = L"Observed Pupae per ha";
      this->dgvcObservedHectare->Name = L"dgvcObservedHectare";
      this->dgvcObservedHectare->ReadOnly = true;
      // 
      // dgvcDailyFood
      // 
      this->dgvcDailyFood->DataPropertyName = L"DailyFood";
      dataGridViewCellStyle5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->dgvcDailyFood->DefaultCellStyle = dataGridViewCellStyle5;
      this->dgvcDailyFood->FillWeight = 75;
      this->dgvcDailyFood->HeaderText = L"Daily Food";
      this->dgvcDailyFood->Name = L"dgvcDailyFood";
      // 
      // dgvcPredictedPupaeContainer
      // 
      this->dgvcPredictedPupaeContainer->DataPropertyName = L"PredictedPerContainer";
      dataGridViewCellStyle6->BackColor = System::Drawing::SystemColors::Control;
      dataGridViewCellStyle6->Format = L"N2";
      this->dgvcPredictedPupaeContainer->DefaultCellStyle = dataGridViewCellStyle6;
      this->dgvcPredictedPupaeContainer->HeaderText = L"Predicted Pupae per Container";
      this->dgvcPredictedPupaeContainer->Name = L"dgvcPredictedPupaeContainer";
      this->dgvcPredictedPupaeContainer->ReadOnly = true;
      // 
      // dgvcPredictedPupaeHectare
      // 
      this->dgvcPredictedPupaeHectare->DataPropertyName = L"PredictedPerHectare";
      dataGridViewCellStyle7->BackColor = System::Drawing::SystemColors::Control;
      dataGridViewCellStyle7->Format = L"N2";
      this->dgvcPredictedPupaeHectare->DefaultCellStyle = dataGridViewCellStyle7;
      this->dgvcPredictedPupaeHectare->HeaderText = L"Predicted Pupae per ha";
      this->dgvcPredictedPupaeHectare->Name = L"dgvcPredictedPupaeHectare";
      this->dgvcPredictedPupaeHectare->ReadOnly = true;
      // 
      // dgvcDifferenceContainer
      // 
      this->dgvcDifferenceContainer->DataPropertyName = L"DifferencePerHectare";
      dataGridViewCellStyle8->BackColor = System::Drawing::SystemColors::Control;
      dataGridViewCellStyle8->Format = L"N2";
      this->dgvcDifferenceContainer->DefaultCellStyle = dataGridViewCellStyle8;
      this->dgvcDifferenceContainer->HeaderText = L"ABS( Observed - Predicted )";
      this->dgvcDifferenceContainer->Name = L"dgvcDifferenceContainer";
      this->dgvcDifferenceContainer->ReadOnly = true;
      // 
      // FoodFitterForm
      // 
      this->AcceptButton = this->btnSave;
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->CancelButton = this->btnCancel;
      this->ClientSize = System::Drawing::Size(812, 433);
      this->Controls->Add(this->snboxTotalObserved);
      this->Controls->Add(this->snboxTotalRatio);
      this->Controls->Add(this->snboxTotalDifference);
      this->Controls->Add(this->snboxTotalPredicted);
      this->Controls->Add(this->lblTotalRatio);
      this->Controls->Add(this->lblTotalDifference);
      this->Controls->Add(this->lblTotalPredicted);
      this->Controls->Add(this->lblTotalObserved);
      this->Controls->Add(this->btnSave);
      this->Controls->Add(this->btnCancel);
      this->Controls->Add(this->btnNext);
      this->Controls->Add(this->dateTimeSurveyStop);
      this->Controls->Add(this->dateTimeSurveyStart);
      this->Controls->Add(this->lblSurveyEnd);
      this->Controls->Add(this->lblSurveyStart);
      this->Controls->Add(this->dgvFit);
      this->Controls->Add(this->lblRuns);
      this->Controls->Add(this->numRuns);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
      this->MinimumSize = System::Drawing::Size(600, 300);
      this->Name = L"FoodFitterForm";
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
      this->Text = L"Food Fitter";
      this->Load += gcnew System::EventHandler(this, &FoodFitterForm::OnLoad);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numRuns))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvFit))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  };
}
