#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace gui {

	public ref class MonthlySchedulePanel : public System::Windows::Forms::UserControl
	{
	public:
		MonthlySchedulePanel( gui::MonthlySchedule ^ ms, BindingSource ^ locationBinding );
	protected:
		~MonthlySchedulePanel();

  private:
    BindingSource ^ LocationBinding;
    gui::Location ^ ActiveLocation;
    gui::Schedule ^ Schedule_;

  private:
    System::Void OnLoad( System::Object ^ sender, System::EventArgs ^ e);

  private: System::Windows::Forms::CheckBox^  checkMonthlyEnd;
  private: System::Windows::Forms::DateTimePicker^  dateTimeMonthlyEnd;
  private: System::Windows::Forms::ComboBox^  cboxMonthlyDay;
  private: System::Windows::Forms::ComboBox^  cboxMonthlyStartYear;
  private: System::Windows::Forms::ComboBox^  cboxMonthlyStartMonth;
  private: System::Windows::Forms::Label^  lblMonthlyStart;
  private: System::Windows::Forms::Label^  lblMonthlyInterval2;
  private: System::Windows::Forms::NumericUpDown^  numMonthlyInterval;
  private: System::Windows::Forms::Label^  lblMonthlyDay;
  private: System::Windows::Forms::Label^  lblMonthlyInterval1;

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
      this->checkMonthlyEnd = (gcnew System::Windows::Forms::CheckBox());
      this->dateTimeMonthlyEnd = (gcnew System::Windows::Forms::DateTimePicker());
      this->cboxMonthlyDay = (gcnew System::Windows::Forms::ComboBox());
      this->cboxMonthlyStartYear = (gcnew System::Windows::Forms::ComboBox());
      this->cboxMonthlyStartMonth = (gcnew System::Windows::Forms::ComboBox());
      this->lblMonthlyStart = (gcnew System::Windows::Forms::Label());
      this->lblMonthlyInterval2 = (gcnew System::Windows::Forms::Label());
      this->numMonthlyInterval = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblMonthlyDay = (gcnew System::Windows::Forms::Label());
      this->lblMonthlyInterval1 = (gcnew System::Windows::Forms::Label());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMonthlyInterval))->BeginInit();
      this->SuspendLayout();
      // 
      // checkMonthlyEnd
      // 
      this->checkMonthlyEnd->AutoSize = true;
      this->checkMonthlyEnd->Location = System::Drawing::Point(24, 103);
      this->checkMonthlyEnd->Name = L"checkMonthlyEnd";
      this->checkMonthlyEnd->Size = System::Drawing::Size(66, 17);
      this->checkMonthlyEnd->TabIndex = 18;
      this->checkMonthlyEnd->Text = L"Stop on:";
      this->checkMonthlyEnd->UseVisualStyleBackColor = true;
      // 
      // dateTimeMonthlyEnd
      // 
      this->dateTimeMonthlyEnd->Location = System::Drawing::Point(100, 100);
      this->dateTimeMonthlyEnd->Name = L"dateTimeMonthlyEnd";
      this->dateTimeMonthlyEnd->Size = System::Drawing::Size(200, 20);
      this->dateTimeMonthlyEnd->TabIndex = 19;
      // 
      // cboxMonthlyDay
      // 
      this->cboxMonthlyDay->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxMonthlyDay->FormattingEnabled = true;
      this->cboxMonthlyDay->Location = System::Drawing::Point(100, 73);
      this->cboxMonthlyDay->MaxDropDownItems = 28;
      this->cboxMonthlyDay->Name = L"cboxMonthlyDay";
      this->cboxMonthlyDay->Size = System::Drawing::Size(43, 21);
      this->cboxMonthlyDay->TabIndex = 17;
      // 
      // cboxMonthlyStartYear
      // 
      this->cboxMonthlyStartYear->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxMonthlyStartYear->FormattingEnabled = true;
      this->cboxMonthlyStartYear->Location = System::Drawing::Point(227, 20);
      this->cboxMonthlyStartYear->Name = L"cboxMonthlyStartYear";
      this->cboxMonthlyStartYear->Size = System::Drawing::Size(121, 21);
      this->cboxMonthlyStartYear->TabIndex = 12;
      // 
      // cboxMonthlyStartMonth
      // 
      this->cboxMonthlyStartMonth->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxMonthlyStartMonth->FormattingEnabled = true;
      this->cboxMonthlyStartMonth->Location = System::Drawing::Point(100, 20);
      this->cboxMonthlyStartMonth->MaxDropDownItems = 12;
      this->cboxMonthlyStartMonth->Name = L"cboxMonthlyStartMonth";
      this->cboxMonthlyStartMonth->Size = System::Drawing::Size(121, 21);
      this->cboxMonthlyStartMonth->TabIndex = 11;
      // 
      // lblMonthlyStart
      // 
      this->lblMonthlyStart->AutoSize = true;
      this->lblMonthlyStart->Location = System::Drawing::Point(47, 23);
      this->lblMonthlyStart->Name = L"lblMonthlyStart";
      this->lblMonthlyStart->Size = System::Drawing::Size(47, 13);
      this->lblMonthlyStart->TabIndex = 10;
      this->lblMonthlyStart->Text = L"Start on:";
      // 
      // lblMonthlyInterval2
      // 
      this->lblMonthlyInterval2->AutoSize = true;
      this->lblMonthlyInterval2->Location = System::Drawing::Point(149, 49);
      this->lblMonthlyInterval2->Name = L"lblMonthlyInterval2";
      this->lblMonthlyInterval2->Size = System::Drawing::Size(47, 13);
      this->lblMonthlyInterval2->TabIndex = 15;
      this->lblMonthlyInterval2->Text = L"month(s)";
      // 
      // numMonthlyInterval
      // 
      this->numMonthlyInterval->Location = System::Drawing::Point(100, 47);
      this->numMonthlyInterval->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numMonthlyInterval->Name = L"numMonthlyInterval";
      this->numMonthlyInterval->Size = System::Drawing::Size(43, 20);
      this->numMonthlyInterval->TabIndex = 14;
      this->numMonthlyInterval->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      // 
      // lblMonthlyDay
      // 
      this->lblMonthlyDay->AutoSize = true;
      this->lblMonthlyDay->Location = System::Drawing::Point(21, 76);
      this->lblMonthlyDay->Name = L"lblMonthlyDay";
      this->lblMonthlyDay->Size = System::Drawing::Size(73, 13);
      this->lblMonthlyDay->TabIndex = 16;
      this->lblMonthlyDay->Text = L"Day of month:";
      // 
      // lblMonthlyInterval1
      // 
      this->lblMonthlyInterval1->AutoSize = true;
      this->lblMonthlyInterval1->Location = System::Drawing::Point(57, 49);
      this->lblMonthlyInterval1->Name = L"lblMonthlyInterval1";
      this->lblMonthlyInterval1->Size = System::Drawing::Size(37, 13);
      this->lblMonthlyInterval1->TabIndex = 13;
      this->lblMonthlyInterval1->Text = L"Every:";
      // 
      // MonthlySchedulePanel
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->BackColor = System::Drawing::SystemColors::Window;
      this->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->Controls->Add(this->checkMonthlyEnd);
      this->Controls->Add(this->dateTimeMonthlyEnd);
      this->Controls->Add(this->cboxMonthlyDay);
      this->Controls->Add(this->cboxMonthlyStartYear);
      this->Controls->Add(this->cboxMonthlyStartMonth);
      this->Controls->Add(this->lblMonthlyStart);
      this->Controls->Add(this->lblMonthlyInterval2);
      this->Controls->Add(this->numMonthlyInterval);
      this->Controls->Add(this->lblMonthlyDay);
      this->Controls->Add(this->lblMonthlyInterval1);
      this->Name = L"MonthlySchedulePanel";
      this->Size = System::Drawing::Size(420, 200);
      this->Load += gcnew System::EventHandler(this, &MonthlySchedulePanel::OnLoad);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMonthlyInterval))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
	};
}
