#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace gui {

	public ref class WeeklySchedulePanel : public System::Windows::Forms::UserControl
	{
	public:
		WeeklySchedulePanel( gui::WeeklySchedule ^ ws, BindingSource ^ locationBinding );
	protected:
		~WeeklySchedulePanel();

  private:
    BindingSource ^ LocationBinding;
    gui::Location ^ ActiveLocation;
    gui::Schedule ^ Schedule_;

  private:
    System::Void OnLoad( System::Object ^ sender, System::EventArgs ^ e);

  private: System::Windows::Forms::CheckBox^  checkWeeklyEnd;
  private: System::Windows::Forms::Label^  lblWeeklyDays;
  private: System::Windows::Forms::DateTimePicker^  dateTimeWeeklyEnd;
  private: System::Windows::Forms::DateTimePicker^  dateTimeWeeklyStart;
  private: System::Windows::Forms::Label^  lblWeeklyStart;
  private: System::Windows::Forms::CheckBox^  checkSaturday;
  private: System::Windows::Forms::CheckBox^  checkFriday;
  private: System::Windows::Forms::CheckBox^  checkThursday;
  private: System::Windows::Forms::CheckBox^  checkWednesday;
  private: System::Windows::Forms::CheckBox^  checkTuesday;
  private: System::Windows::Forms::CheckBox^  checkSunday;
  private: System::Windows::Forms::CheckBox^  checkMonday;
  private: System::Windows::Forms::Label^  lblWeeklyInterval2;
  private: System::Windows::Forms::NumericUpDown^  numWeeklyInterval;
  private: System::Windows::Forms::Label^  lblWeeklyInterval1;

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
      this->checkWeeklyEnd = (gcnew System::Windows::Forms::CheckBox());
      this->lblWeeklyDays = (gcnew System::Windows::Forms::Label());
      this->dateTimeWeeklyEnd = (gcnew System::Windows::Forms::DateTimePicker());
      this->dateTimeWeeklyStart = (gcnew System::Windows::Forms::DateTimePicker());
      this->lblWeeklyStart = (gcnew System::Windows::Forms::Label());
      this->checkSaturday = (gcnew System::Windows::Forms::CheckBox());
      this->checkFriday = (gcnew System::Windows::Forms::CheckBox());
      this->checkThursday = (gcnew System::Windows::Forms::CheckBox());
      this->checkWednesday = (gcnew System::Windows::Forms::CheckBox());
      this->checkTuesday = (gcnew System::Windows::Forms::CheckBox());
      this->checkSunday = (gcnew System::Windows::Forms::CheckBox());
      this->checkMonday = (gcnew System::Windows::Forms::CheckBox());
      this->lblWeeklyInterval2 = (gcnew System::Windows::Forms::Label());
      this->numWeeklyInterval = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblWeeklyInterval1 = (gcnew System::Windows::Forms::Label());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numWeeklyInterval))->BeginInit();
      this->SuspendLayout();
      // 
      // checkWeeklyEnd
      // 
      this->checkWeeklyEnd->AutoSize = true;
      this->checkWeeklyEnd->Location = System::Drawing::Point(28, 144);
      this->checkWeeklyEnd->Name = L"checkWeeklyEnd";
      this->checkWeeklyEnd->Size = System::Drawing::Size(66, 17);
      this->checkWeeklyEnd->TabIndex = 28;
      this->checkWeeklyEnd->Text = L"Stop on:";
      this->checkWeeklyEnd->UseVisualStyleBackColor = true;
      // 
      // lblWeeklyDays
      // 
      this->lblWeeklyDays->AutoSize = true;
      this->lblWeeklyDays->Location = System::Drawing::Point(54, 73);
      this->lblWeeklyDays->Name = L"lblWeeklyDays";
      this->lblWeeklyDays->Size = System::Drawing::Size(40, 13);
      this->lblWeeklyDays->TabIndex = 20;
      this->lblWeeklyDays->Text = L"Day(s):";
      // 
      // dateTimeWeeklyEnd
      // 
      this->dateTimeWeeklyEnd->Location = System::Drawing::Point(100, 141);
      this->dateTimeWeeklyEnd->Name = L"dateTimeWeeklyEnd";
      this->dateTimeWeeklyEnd->Size = System::Drawing::Size(200, 20);
      this->dateTimeWeeklyEnd->TabIndex = 29;
      // 
      // dateTimeWeeklyStart
      // 
      this->dateTimeWeeklyStart->Location = System::Drawing::Point(100, 20);
      this->dateTimeWeeklyStart->Name = L"dateTimeWeeklyStart";
      this->dateTimeWeeklyStart->Size = System::Drawing::Size(200, 20);
      this->dateTimeWeeklyStart->TabIndex = 16;
      // 
      // lblWeeklyStart
      // 
      this->lblWeeklyStart->AutoSize = true;
      this->lblWeeklyStart->Location = System::Drawing::Point(47, 24);
      this->lblWeeklyStart->Name = L"lblWeeklyStart";
      this->lblWeeklyStart->Size = System::Drawing::Size(47, 13);
      this->lblWeeklyStart->TabIndex = 15;
      this->lblWeeklyStart->Text = L"Start on:";
      // 
      // checkSaturday
      // 
      this->checkSaturday->AutoSize = true;
      this->checkSaturday->Location = System::Drawing::Point(282, 72);
      this->checkSaturday->Name = L"checkSaturday";
      this->checkSaturday->Size = System::Drawing::Size(68, 17);
      this->checkSaturday->TabIndex = 27;
      this->checkSaturday->Text = L"Saturday";
      this->checkSaturday->UseVisualStyleBackColor = true;
      // 
      // checkFriday
      // 
      this->checkFriday->AutoSize = true;
      this->checkFriday->Location = System::Drawing::Point(184, 118);
      this->checkFriday->Name = L"checkFriday";
      this->checkFriday->Size = System::Drawing::Size(54, 17);
      this->checkFriday->TabIndex = 26;
      this->checkFriday->Text = L"Friday";
      this->checkFriday->UseVisualStyleBackColor = true;
      // 
      // checkThursday
      // 
      this->checkThursday->AutoSize = true;
      this->checkThursday->Location = System::Drawing::Point(184, 95);
      this->checkThursday->Name = L"checkThursday";
      this->checkThursday->Size = System::Drawing::Size(70, 17);
      this->checkThursday->TabIndex = 25;
      this->checkThursday->Text = L"Thursday";
      this->checkThursday->UseVisualStyleBackColor = true;
      // 
      // checkWednesday
      // 
      this->checkWednesday->AutoSize = true;
      this->checkWednesday->Location = System::Drawing::Point(184, 72);
      this->checkWednesday->Name = L"checkWednesday";
      this->checkWednesday->Size = System::Drawing::Size(83, 17);
      this->checkWednesday->TabIndex = 24;
      this->checkWednesday->Text = L"Wednesday";
      this->checkWednesday->UseVisualStyleBackColor = true;
      // 
      // checkTuesday
      // 
      this->checkTuesday->AutoSize = true;
      this->checkTuesday->Location = System::Drawing::Point(100, 118);
      this->checkTuesday->Name = L"checkTuesday";
      this->checkTuesday->Size = System::Drawing::Size(67, 17);
      this->checkTuesday->TabIndex = 23;
      this->checkTuesday->Text = L"Tuesday";
      this->checkTuesday->UseVisualStyleBackColor = true;
      // 
      // checkSunday
      // 
      this->checkSunday->AutoSize = true;
      this->checkSunday->Location = System::Drawing::Point(100, 72);
      this->checkSunday->Name = L"checkSunday";
      this->checkSunday->Size = System::Drawing::Size(62, 17);
      this->checkSunday->TabIndex = 21;
      this->checkSunday->Text = L"Sunday";
      this->checkSunday->UseVisualStyleBackColor = true;
      // 
      // checkMonday
      // 
      this->checkMonday->AutoSize = true;
      this->checkMonday->Location = System::Drawing::Point(100, 95);
      this->checkMonday->Name = L"checkMonday";
      this->checkMonday->Size = System::Drawing::Size(64, 17);
      this->checkMonday->TabIndex = 22;
      this->checkMonday->Text = L"Monday";
      this->checkMonday->UseVisualStyleBackColor = true;
      // 
      // lblWeeklyInterval2
      // 
      this->lblWeeklyInterval2->AutoSize = true;
      this->lblWeeklyInterval2->Location = System::Drawing::Point(159, 48);
      this->lblWeeklyInterval2->Name = L"lblWeeklyInterval2";
      this->lblWeeklyInterval2->Size = System::Drawing::Size(44, 13);
      this->lblWeeklyInterval2->TabIndex = 19;
      this->lblWeeklyInterval2->Text = L"week(s)";
      // 
      // numWeeklyInterval
      // 
      this->numWeeklyInterval->Location = System::Drawing::Point(100, 46);
      this->numWeeklyInterval->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numWeeklyInterval->Name = L"numWeeklyInterval";
      this->numWeeklyInterval->Size = System::Drawing::Size(43, 20);
      this->numWeeklyInterval->TabIndex = 18;
      this->numWeeklyInterval->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      // 
      // lblWeeklyInterval1
      // 
      this->lblWeeklyInterval1->AutoSize = true;
      this->lblWeeklyInterval1->Location = System::Drawing::Point(57, 48);
      this->lblWeeklyInterval1->Name = L"lblWeeklyInterval1";
      this->lblWeeklyInterval1->Size = System::Drawing::Size(37, 13);
      this->lblWeeklyInterval1->TabIndex = 17;
      this->lblWeeklyInterval1->Text = L"Every:";
      // 
      // WeeklySchedulePanel
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->BackColor = System::Drawing::SystemColors::Window;
      this->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->Controls->Add(this->checkWeeklyEnd);
      this->Controls->Add(this->lblWeeklyDays);
      this->Controls->Add(this->dateTimeWeeklyEnd);
      this->Controls->Add(this->dateTimeWeeklyStart);
      this->Controls->Add(this->lblWeeklyStart);
      this->Controls->Add(this->checkSaturday);
      this->Controls->Add(this->checkFriday);
      this->Controls->Add(this->checkThursday);
      this->Controls->Add(this->checkWednesday);
      this->Controls->Add(this->checkTuesday);
      this->Controls->Add(this->checkSunday);
      this->Controls->Add(this->checkMonday);
      this->Controls->Add(this->lblWeeklyInterval2);
      this->Controls->Add(this->numWeeklyInterval);
      this->Controls->Add(this->lblWeeklyInterval1);
      this->Name = L"WeeklySchedulePanel";
      this->Size = System::Drawing::Size(420, 200);
      this->Load += gcnew System::EventHandler(this, &WeeklySchedulePanel::OnLoad);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numWeeklyInterval))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
	};
}
