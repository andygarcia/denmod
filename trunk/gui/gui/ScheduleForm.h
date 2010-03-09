#pragma once

#include "Schedule.h"



namespace gui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class ScheduleForm : public System::Windows::Forms::Form
	{
	public:
    ScheduleForm( DateTime minDate, DateTime maxDate, Schedule ^ schedule );
		~ScheduleForm(void);

    Schedule ^ GetSchedule(void);

  private:
    System::Void OnLoad(System::Object^  sender, System::EventArgs^  e);
    System::Void OnChangeSchedule(System::Object^  sender, System::Windows::Forms::TabControlEventArgs^  e);

  public:
    DateTime MinDate_;
    DateTime MaxDate_;

    Schedule ^ OriginalSchedule_;
    SingleSchedule ^ SingleSchedule_;
    WeeklySchedule ^ WeeklySchedule_;
    MonthlySchedule ^ MonthlySchedule_;
    YearlySchedule ^ YearlySchedule_;
    PeriodicSchedule ^ PeriodicSchedule_;
    Schedule ^ CurrentSchedule_;

	protected:

  private: System::Windows::Forms::TabControl^  tabSchedule;

  private: System::Windows::Forms::TabPage^  tabPageSingle;
  private: System::Windows::Forms::Label^  lblSingleStart;
  private: System::Windows::Forms::DateTimePicker^  dateTimeSingleStart;

  private: System::Windows::Forms::TabPage^  tabPageWeekly;
  private: System::Windows::Forms::Label^  lblWeeklyStart;
  private: System::Windows::Forms::DateTimePicker^  dateTimeWeeklyStart;
  private: System::Windows::Forms::Label^  lblWeeklyDays;
  private: System::Windows::Forms::Label^  lblWeeklyInterval1;
  private: System::Windows::Forms::Label^  lblWeeklyInterval2;
  private: System::Windows::Forms::NumericUpDown^  numWeeklyInterval;
  private: System::Windows::Forms::CheckBox^  checkSunday;
  private: System::Windows::Forms::CheckBox^  checkMonday;
  private: System::Windows::Forms::CheckBox^  checkTuesday;
  private: System::Windows::Forms::CheckBox^  checkWednesday;
  private: System::Windows::Forms::CheckBox^  checkThursday;
  private: System::Windows::Forms::CheckBox^  checkFriday;
  private: System::Windows::Forms::CheckBox^  checkSaturday;
  private: System::Windows::Forms::CheckBox^  checkWeeklyEnd;
  private: System::Windows::Forms::DateTimePicker^  dateTimeWeeklyEnd;

  private: System::Windows::Forms::TabPage^  tabPageMonthly;
  private: System::Windows::Forms::Label^  lblMonthlyStart;
  private: System::Windows::Forms::ComboBox^  cboxMonthlyStartMonth;
  private: System::Windows::Forms::ComboBox^  cboxMonthlyStartYear;

  private: System::Windows::Forms::Label^  lblMonthlyInterval1;
  private: System::Windows::Forms::NumericUpDown^  numMonthlyInterval;
  private: System::Windows::Forms::Label^  lblMonthlyInterval2;
  private: System::Windows::Forms::Label^  lblMonthlyDay;
  private: System::Windows::Forms::ComboBox^  cboxMonthlyDay;
  private: System::Windows::Forms::CheckBox^  checkMonthlyEnd;
  private: System::Windows::Forms::DateTimePicker^  dateTimeMonthlyEnd;

  private: System::Windows::Forms::TabPage^  tabPageYearly;
  private: System::Windows::Forms::Label^  lblYearlyStart;
  private: System::Windows::Forms::ComboBox^  cboxYearlyStart;
  private: System::Windows::Forms::Label^  lblYearlyDay1;
  private: System::Windows::Forms::NumericUpDown^  numYearlyDay;
  private: System::Windows::Forms::Label^  lblYearlyDay2;
  private: System::Windows::Forms::Label^  lblYearlyInterval1;
  private: System::Windows::Forms::NumericUpDown^  numYearlyInterval;
  private: System::Windows::Forms::Label^  lblYearlyInterval2;

  private: System::Windows::Forms::TabPage^  tabPagePeriodic;
  private: System::Windows::Forms::Label^  lblPeriodicStart;
  private: System::Windows::Forms::DateTimePicker^  dateTimePeriodicStart;
  private: System::Windows::Forms::Label^  lblPeriodicInterval1;
  private: System::Windows::Forms::NumericUpDown^  numPeriodicTreatments;
  private: System::Windows::Forms::Label^  lblPeriodicInterval2;
  private: System::Windows::Forms::CheckBox^  checkPeriodicTreatments;
  private: System::Windows::Forms::NumericUpDown^  numPeriodicInterval;
  private: System::Windows::Forms::CheckBox^  checkPeriodicStop;
  private: System::Windows::Forms::DateTimePicker^  dateTimePeriodicStop;


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
      this->tabSchedule = (gcnew System::Windows::Forms::TabControl());
      this->tabPageSingle = (gcnew System::Windows::Forms::TabPage());
      this->dateTimeSingleStart = (gcnew System::Windows::Forms::DateTimePicker());
      this->lblSingleStart = (gcnew System::Windows::Forms::Label());
      this->tabPageWeekly = (gcnew System::Windows::Forms::TabPage());
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
      this->tabPageMonthly = (gcnew System::Windows::Forms::TabPage());
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
      this->tabPageYearly = (gcnew System::Windows::Forms::TabPage());
      this->cboxYearlyStart = (gcnew System::Windows::Forms::ComboBox());
      this->lblYearlyStart = (gcnew System::Windows::Forms::Label());
      this->lblYearlyDay2 = (gcnew System::Windows::Forms::Label());
      this->lblYearlyInterval1 = (gcnew System::Windows::Forms::Label());
      this->lblYearlyInterval2 = (gcnew System::Windows::Forms::Label());
      this->numYearlyInterval = (gcnew System::Windows::Forms::NumericUpDown());
      this->numYearlyDay = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblYearlyDay1 = (gcnew System::Windows::Forms::Label());
      this->tabPagePeriodic = (gcnew System::Windows::Forms::TabPage());
      this->checkPeriodicTreatments = (gcnew System::Windows::Forms::CheckBox());
      this->checkPeriodicStop = (gcnew System::Windows::Forms::CheckBox());
      this->dateTimePeriodicStop = (gcnew System::Windows::Forms::DateTimePicker());
      this->dateTimePeriodicStart = (gcnew System::Windows::Forms::DateTimePicker());
      this->lblPeriodicStart = (gcnew System::Windows::Forms::Label());
      this->lblPeriodicInterval2 = (gcnew System::Windows::Forms::Label());
      this->numPeriodicTreatments = (gcnew System::Windows::Forms::NumericUpDown());
      this->numPeriodicInterval = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblPeriodicInterval1 = (gcnew System::Windows::Forms::Label());
      this->tabSchedule->SuspendLayout();
      this->tabPageSingle->SuspendLayout();
      this->tabPageWeekly->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numWeeklyInterval))->BeginInit();
      this->tabPageMonthly->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMonthlyInterval))->BeginInit();
      this->tabPageYearly->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numYearlyInterval))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numYearlyDay))->BeginInit();
      this->tabPagePeriodic->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numPeriodicTreatments))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numPeriodicInterval))->BeginInit();
      this->SuspendLayout();
      // 
      // tabSchedule
      // 
      this->tabSchedule->Controls->Add(this->tabPageSingle);
      this->tabSchedule->Controls->Add(this->tabPageWeekly);
      this->tabSchedule->Controls->Add(this->tabPageMonthly);
      this->tabSchedule->Controls->Add(this->tabPageYearly);
      this->tabSchedule->Controls->Add(this->tabPagePeriodic);
      this->tabSchedule->Location = System::Drawing::Point(12, 12);
      this->tabSchedule->Name = L"tabSchedule";
      this->tabSchedule->SelectedIndex = 0;
      this->tabSchedule->Size = System::Drawing::Size(500, 267);
      this->tabSchedule->TabIndex = 0;
      this->tabSchedule->Selected += gcnew System::Windows::Forms::TabControlEventHandler(this, &ScheduleForm::OnChangeSchedule);
      // 
      // tabPageSingle
      // 
      this->tabPageSingle->Controls->Add(this->dateTimeSingleStart);
      this->tabPageSingle->Controls->Add(this->lblSingleStart);
      this->tabPageSingle->Location = System::Drawing::Point(4, 24);
      this->tabPageSingle->Name = L"tabPageSingle";
      this->tabPageSingle->Padding = System::Windows::Forms::Padding(3);
      this->tabPageSingle->Size = System::Drawing::Size(492, 239);
      this->tabPageSingle->TabIndex = 0;
      this->tabPageSingle->Text = L"Single";
      this->tabPageSingle->UseVisualStyleBackColor = true;
      // 
      // dateTimeSingleStart
      // 
      this->dateTimeSingleStart->Location = System::Drawing::Point(160, 30);
      this->dateTimeSingleStart->Name = L"dateTimeSingleStart";
      this->dateTimeSingleStart->Size = System::Drawing::Size(200, 20);
      this->dateTimeSingleStart->TabIndex = 1;
      // 
      // lblSingleStart
      // 
      this->lblSingleStart->AutoSize = true;
      this->lblSingleStart->Location = System::Drawing::Point(84, 34);
      this->lblSingleStart->Name = L"lblSingleStart";
      this->lblSingleStart->Size = System::Drawing::Size(70, 13);
      this->lblSingleStart->TabIndex = 0;
      this->lblSingleStart->Text = L"Schedule on:";
      // 
      // tabPageWeekly
      // 
      this->tabPageWeekly->Controls->Add(this->checkWeeklyEnd);
      this->tabPageWeekly->Controls->Add(this->lblWeeklyDays);
      this->tabPageWeekly->Controls->Add(this->dateTimeWeeklyEnd);
      this->tabPageWeekly->Controls->Add(this->dateTimeWeeklyStart);
      this->tabPageWeekly->Controls->Add(this->lblWeeklyStart);
      this->tabPageWeekly->Controls->Add(this->checkSaturday);
      this->tabPageWeekly->Controls->Add(this->checkFriday);
      this->tabPageWeekly->Controls->Add(this->checkThursday);
      this->tabPageWeekly->Controls->Add(this->checkWednesday);
      this->tabPageWeekly->Controls->Add(this->checkTuesday);
      this->tabPageWeekly->Controls->Add(this->checkSunday);
      this->tabPageWeekly->Controls->Add(this->checkMonday);
      this->tabPageWeekly->Controls->Add(this->lblWeeklyInterval2);
      this->tabPageWeekly->Controls->Add(this->numWeeklyInterval);
      this->tabPageWeekly->Controls->Add(this->lblWeeklyInterval1);
      this->tabPageWeekly->Location = System::Drawing::Point(4, 24);
      this->tabPageWeekly->Name = L"tabPageWeekly";
      this->tabPageWeekly->Padding = System::Windows::Forms::Padding(3);
      this->tabPageWeekly->Size = System::Drawing::Size(492, 239);
      this->tabPageWeekly->TabIndex = 1;
      this->tabPageWeekly->Text = L"Weekly";
      this->tabPageWeekly->UseVisualStyleBackColor = true;
      // 
      // checkWeeklyEnd
      // 
      this->checkWeeklyEnd->AutoSize = true;
      this->checkWeeklyEnd->Location = System::Drawing::Point(88, 154);
      this->checkWeeklyEnd->Name = L"checkWeeklyEnd";
      this->checkWeeklyEnd->Size = System::Drawing::Size(66, 17);
      this->checkWeeklyEnd->TabIndex = 13;
      this->checkWeeklyEnd->Text = L"Stop on:";
      this->checkWeeklyEnd->UseVisualStyleBackColor = true;
      // 
      // lblWeeklyDays
      // 
      this->lblWeeklyDays->AutoSize = true;
      this->lblWeeklyDays->Location = System::Drawing::Point(114, 83);
      this->lblWeeklyDays->Name = L"lblWeeklyDays";
      this->lblWeeklyDays->Size = System::Drawing::Size(40, 13);
      this->lblWeeklyDays->TabIndex = 5;
      this->lblWeeklyDays->Text = L"Day(s):";
      // 
      // dateTimeWeeklyEnd
      // 
      this->dateTimeWeeklyEnd->Location = System::Drawing::Point(160, 151);
      this->dateTimeWeeklyEnd->Name = L"dateTimeWeeklyEnd";
      this->dateTimeWeeklyEnd->Size = System::Drawing::Size(200, 20);
      this->dateTimeWeeklyEnd->TabIndex = 14;
      // 
      // dateTimeWeeklyStart
      // 
      this->dateTimeWeeklyStart->Location = System::Drawing::Point(160, 30);
      this->dateTimeWeeklyStart->Name = L"dateTimeWeeklyStart";
      this->dateTimeWeeklyStart->Size = System::Drawing::Size(200, 20);
      this->dateTimeWeeklyStart->TabIndex = 1;
      // 
      // lblWeeklyStart
      // 
      this->lblWeeklyStart->AutoSize = true;
      this->lblWeeklyStart->Location = System::Drawing::Point(107, 34);
      this->lblWeeklyStart->Name = L"lblWeeklyStart";
      this->lblWeeklyStart->Size = System::Drawing::Size(47, 13);
      this->lblWeeklyStart->TabIndex = 0;
      this->lblWeeklyStart->Text = L"Start on:";
      // 
      // checkSaturday
      // 
      this->checkSaturday->AutoSize = true;
      this->checkSaturday->Location = System::Drawing::Point(342, 82);
      this->checkSaturday->Name = L"checkSaturday";
      this->checkSaturday->Size = System::Drawing::Size(68, 17);
      this->checkSaturday->TabIndex = 12;
      this->checkSaturday->Text = L"Saturday";
      this->checkSaturday->UseVisualStyleBackColor = true;
      // 
      // checkFriday
      // 
      this->checkFriday->AutoSize = true;
      this->checkFriday->Location = System::Drawing::Point(244, 128);
      this->checkFriday->Name = L"checkFriday";
      this->checkFriday->Size = System::Drawing::Size(54, 17);
      this->checkFriday->TabIndex = 11;
      this->checkFriday->Text = L"Friday";
      this->checkFriday->UseVisualStyleBackColor = true;
      // 
      // checkThursday
      // 
      this->checkThursday->AutoSize = true;
      this->checkThursday->Location = System::Drawing::Point(244, 105);
      this->checkThursday->Name = L"checkThursday";
      this->checkThursday->Size = System::Drawing::Size(70, 17);
      this->checkThursday->TabIndex = 10;
      this->checkThursday->Text = L"Thursday";
      this->checkThursday->UseVisualStyleBackColor = true;
      // 
      // checkWednesday
      // 
      this->checkWednesday->AutoSize = true;
      this->checkWednesday->Location = System::Drawing::Point(244, 82);
      this->checkWednesday->Name = L"checkWednesday";
      this->checkWednesday->Size = System::Drawing::Size(83, 17);
      this->checkWednesday->TabIndex = 9;
      this->checkWednesday->Text = L"Wednesday";
      this->checkWednesday->UseVisualStyleBackColor = true;
      // 
      // checkTuesday
      // 
      this->checkTuesday->AutoSize = true;
      this->checkTuesday->Location = System::Drawing::Point(160, 128);
      this->checkTuesday->Name = L"checkTuesday";
      this->checkTuesday->Size = System::Drawing::Size(67, 17);
      this->checkTuesday->TabIndex = 8;
      this->checkTuesday->Text = L"Tuesday";
      this->checkTuesday->UseVisualStyleBackColor = true;
      // 
      // checkSunday
      // 
      this->checkSunday->AutoSize = true;
      this->checkSunday->Location = System::Drawing::Point(160, 82);
      this->checkSunday->Name = L"checkSunday";
      this->checkSunday->Size = System::Drawing::Size(62, 17);
      this->checkSunday->TabIndex = 6;
      this->checkSunday->Text = L"Sunday";
      this->checkSunday->UseVisualStyleBackColor = true;
      // 
      // checkMonday
      // 
      this->checkMonday->AutoSize = true;
      this->checkMonday->Location = System::Drawing::Point(160, 105);
      this->checkMonday->Name = L"checkMonday";
      this->checkMonday->Size = System::Drawing::Size(64, 17);
      this->checkMonday->TabIndex = 7;
      this->checkMonday->Text = L"Monday";
      this->checkMonday->UseVisualStyleBackColor = true;
      // 
      // lblWeeklyInterval2
      // 
      this->lblWeeklyInterval2->AutoSize = true;
      this->lblWeeklyInterval2->Location = System::Drawing::Point(219, 58);
      this->lblWeeklyInterval2->Name = L"lblWeeklyInterval2";
      this->lblWeeklyInterval2->Size = System::Drawing::Size(44, 13);
      this->lblWeeklyInterval2->TabIndex = 4;
      this->lblWeeklyInterval2->Text = L"week(s)";
      // 
      // numWeeklyInterval
      // 
      this->numWeeklyInterval->Location = System::Drawing::Point(160, 56);
      this->numWeeklyInterval->Name = L"numWeeklyInterval";
      this->numWeeklyInterval->Size = System::Drawing::Size(43, 20);
      this->numWeeklyInterval->TabIndex = 3;
      // 
      // lblWeeklyInterval1
      // 
      this->lblWeeklyInterval1->AutoSize = true;
      this->lblWeeklyInterval1->Location = System::Drawing::Point(117, 58);
      this->lblWeeklyInterval1->Name = L"lblWeeklyInterval1";
      this->lblWeeklyInterval1->Size = System::Drawing::Size(37, 13);
      this->lblWeeklyInterval1->TabIndex = 2;
      this->lblWeeklyInterval1->Text = L"Every:";
      // 
      // tabPageMonthly
      // 
      this->tabPageMonthly->Controls->Add(this->checkMonthlyEnd);
      this->tabPageMonthly->Controls->Add(this->dateTimeMonthlyEnd);
      this->tabPageMonthly->Controls->Add(this->cboxMonthlyDay);
      this->tabPageMonthly->Controls->Add(this->cboxMonthlyStartYear);
      this->tabPageMonthly->Controls->Add(this->cboxMonthlyStartMonth);
      this->tabPageMonthly->Controls->Add(this->lblMonthlyStart);
      this->tabPageMonthly->Controls->Add(this->lblMonthlyInterval2);
      this->tabPageMonthly->Controls->Add(this->numMonthlyInterval);
      this->tabPageMonthly->Controls->Add(this->lblMonthlyDay);
      this->tabPageMonthly->Controls->Add(this->lblMonthlyInterval1);
      this->tabPageMonthly->Location = System::Drawing::Point(4, 24);
      this->tabPageMonthly->Name = L"tabPageMonthly";
      this->tabPageMonthly->Size = System::Drawing::Size(492, 239);
      this->tabPageMonthly->TabIndex = 2;
      this->tabPageMonthly->Text = L"Monthly";
      this->tabPageMonthly->UseVisualStyleBackColor = true;
      // 
      // checkMonthlyEnd
      // 
      this->checkMonthlyEnd->AutoSize = true;
      this->checkMonthlyEnd->Location = System::Drawing::Point(84, 113);
      this->checkMonthlyEnd->Name = L"checkMonthlyEnd";
      this->checkMonthlyEnd->Size = System::Drawing::Size(66, 17);
      this->checkMonthlyEnd->TabIndex = 8;
      this->checkMonthlyEnd->Text = L"Stop on:";
      this->checkMonthlyEnd->UseVisualStyleBackColor = true;
      // 
      // dateTimeMonthlyEnd
      // 
      this->dateTimeMonthlyEnd->Location = System::Drawing::Point(160, 110);
      this->dateTimeMonthlyEnd->Name = L"dateTimeMonthlyEnd";
      this->dateTimeMonthlyEnd->Size = System::Drawing::Size(200, 20);
      this->dateTimeMonthlyEnd->TabIndex = 9;
      // 
      // cboxMonthlyDay
      // 
      this->cboxMonthlyDay->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxMonthlyDay->FormattingEnabled = true;
      this->cboxMonthlyDay->Items->AddRange(gcnew cli::array< System::Object^  >(28) {L"1", L"2", L"3", L"4", L"5", L"6", L"7", 
        L"8", L"9", L"10", L"11", L"12", L"13", L"14", L"15", L"16", L"17", L"18", L"19", L"20", L"21", L"22", L"23", L"24", L"25", L"26", 
        L"27", L"28"});
      this->cboxMonthlyDay->Location = System::Drawing::Point(160, 83);
      this->cboxMonthlyDay->MaxDropDownItems = 28;
      this->cboxMonthlyDay->Name = L"cboxMonthlyDay";
      this->cboxMonthlyDay->Size = System::Drawing::Size(43, 21);
      this->cboxMonthlyDay->TabIndex = 7;
      // 
      // cboxMonthlyStartYear
      // 
      this->cboxMonthlyStartYear->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxMonthlyStartYear->FormattingEnabled = true;
      this->cboxMonthlyStartYear->Location = System::Drawing::Point(287, 30);
      this->cboxMonthlyStartYear->Name = L"cboxMonthlyStartYear";
      this->cboxMonthlyStartYear->Size = System::Drawing::Size(121, 21);
      this->cboxMonthlyStartYear->TabIndex = 2;
      // 
      // cboxMonthlyStartMonth
      // 
      this->cboxMonthlyStartMonth->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxMonthlyStartMonth->FormattingEnabled = true;
      this->cboxMonthlyStartMonth->Location = System::Drawing::Point(160, 30);
      this->cboxMonthlyStartMonth->MaxDropDownItems = 12;
      this->cboxMonthlyStartMonth->Name = L"cboxMonthlyStartMonth";
      this->cboxMonthlyStartMonth->Size = System::Drawing::Size(121, 21);
      this->cboxMonthlyStartMonth->TabIndex = 1;
      // 
      // lblMonthlyStart
      // 
      this->lblMonthlyStart->AutoSize = true;
      this->lblMonthlyStart->Location = System::Drawing::Point(107, 33);
      this->lblMonthlyStart->Name = L"lblMonthlyStart";
      this->lblMonthlyStart->Size = System::Drawing::Size(47, 13);
      this->lblMonthlyStart->TabIndex = 0;
      this->lblMonthlyStart->Text = L"Start on:";
      // 
      // lblMonthlyInterval2
      // 
      this->lblMonthlyInterval2->AutoSize = true;
      this->lblMonthlyInterval2->Location = System::Drawing::Point(209, 59);
      this->lblMonthlyInterval2->Name = L"lblMonthlyInterval2";
      this->lblMonthlyInterval2->Size = System::Drawing::Size(47, 13);
      this->lblMonthlyInterval2->TabIndex = 5;
      this->lblMonthlyInterval2->Text = L"month(s)";
      // 
      // numMonthlyInterval
      // 
      this->numMonthlyInterval->Location = System::Drawing::Point(160, 57);
      this->numMonthlyInterval->Name = L"numMonthlyInterval";
      this->numMonthlyInterval->Size = System::Drawing::Size(43, 20);
      this->numMonthlyInterval->TabIndex = 4;
      // 
      // lblMonthlyDay
      // 
      this->lblMonthlyDay->AutoSize = true;
      this->lblMonthlyDay->Location = System::Drawing::Point(81, 86);
      this->lblMonthlyDay->Name = L"lblMonthlyDay";
      this->lblMonthlyDay->Size = System::Drawing::Size(73, 13);
      this->lblMonthlyDay->TabIndex = 6;
      this->lblMonthlyDay->Text = L"Day of month:";
      // 
      // lblMonthlyInterval1
      // 
      this->lblMonthlyInterval1->AutoSize = true;
      this->lblMonthlyInterval1->Location = System::Drawing::Point(117, 59);
      this->lblMonthlyInterval1->Name = L"lblMonthlyInterval1";
      this->lblMonthlyInterval1->Size = System::Drawing::Size(37, 13);
      this->lblMonthlyInterval1->TabIndex = 3;
      this->lblMonthlyInterval1->Text = L"Every:";
      // 
      // tabPageYearly
      // 
      this->tabPageYearly->Controls->Add(this->cboxYearlyStart);
      this->tabPageYearly->Controls->Add(this->lblYearlyStart);
      this->tabPageYearly->Controls->Add(this->lblYearlyDay2);
      this->tabPageYearly->Controls->Add(this->lblYearlyInterval1);
      this->tabPageYearly->Controls->Add(this->lblYearlyInterval2);
      this->tabPageYearly->Controls->Add(this->numYearlyInterval);
      this->tabPageYearly->Controls->Add(this->numYearlyDay);
      this->tabPageYearly->Controls->Add(this->lblYearlyDay1);
      this->tabPageYearly->Location = System::Drawing::Point(4, 24);
      this->tabPageYearly->Name = L"tabPageYearly";
      this->tabPageYearly->Size = System::Drawing::Size(492, 239);
      this->tabPageYearly->TabIndex = 3;
      this->tabPageYearly->Text = L"Yearly";
      this->tabPageYearly->UseVisualStyleBackColor = true;
      // 
      // cboxYearlyStart
      // 
      this->cboxYearlyStart->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxYearlyStart->FormattingEnabled = true;
      this->cboxYearlyStart->Location = System::Drawing::Point(160, 29);
      this->cboxYearlyStart->Name = L"cboxYearlyStart";
      this->cboxYearlyStart->Size = System::Drawing::Size(121, 21);
      this->cboxYearlyStart->TabIndex = 1;
      // 
      // lblYearlyStart
      // 
      this->lblYearlyStart->AutoSize = true;
      this->lblYearlyStart->Location = System::Drawing::Point(111, 32);
      this->lblYearlyStart->Name = L"lblYearlyStart";
      this->lblYearlyStart->Size = System::Drawing::Size(43, 13);
      this->lblYearlyStart->TabIndex = 0;
      this->lblYearlyStart->Text = L"Start in:";
      // 
      // lblYearlyDay2
      // 
      this->lblYearlyDay2->AutoSize = true;
      this->lblYearlyDay2->Location = System::Drawing::Point(209, 84);
      this->lblYearlyDay2->Name = L"lblYearlyDay2";
      this->lblYearlyDay2->Size = System::Drawing::Size(77, 13);
      this->lblYearlyDay2->TabIndex = 7;
      this->lblYearlyDay2->Text = L"day of the year";
      // 
      // lblYearlyInterval1
      // 
      this->lblYearlyInterval1->AutoSize = true;
      this->lblYearlyInterval1->Location = System::Drawing::Point(117, 58);
      this->lblYearlyInterval1->Name = L"lblYearlyInterval1";
      this->lblYearlyInterval1->Size = System::Drawing::Size(37, 13);
      this->lblYearlyInterval1->TabIndex = 2;
      this->lblYearlyInterval1->Text = L"Every:";
      // 
      // lblYearlyInterval2
      // 
      this->lblYearlyInterval2->AutoSize = true;
      this->lblYearlyInterval2->Location = System::Drawing::Point(209, 58);
      this->lblYearlyInterval2->Name = L"lblYearlyInterval2";
      this->lblYearlyInterval2->Size = System::Drawing::Size(38, 13);
      this->lblYearlyInterval2->TabIndex = 4;
      this->lblYearlyInterval2->Text = L"year(s)";
      // 
      // numYearlyInterval
      // 
      this->numYearlyInterval->Location = System::Drawing::Point(160, 56);
      this->numYearlyInterval->Name = L"numYearlyInterval";
      this->numYearlyInterval->Size = System::Drawing::Size(43, 20);
      this->numYearlyInterval->TabIndex = 3;
      // 
      // numYearlyDay
      // 
      this->numYearlyDay->Location = System::Drawing::Point(160, 82);
      this->numYearlyDay->Name = L"numYearlyDay";
      this->numYearlyDay->Size = System::Drawing::Size(43, 20);
      this->numYearlyDay->TabIndex = 6;
      // 
      // lblYearlyDay1
      // 
      this->lblYearlyDay1->AutoSize = true;
      this->lblYearlyDay1->Location = System::Drawing::Point(112, 84);
      this->lblYearlyDay1->Name = L"lblYearlyDay1";
      this->lblYearlyDay1->Size = System::Drawing::Size(42, 13);
      this->lblYearlyDay1->TabIndex = 5;
      this->lblYearlyDay1->Text = L"On the:";
      // 
      // tabPagePeriodic
      // 
      this->tabPagePeriodic->Controls->Add(this->checkPeriodicTreatments);
      this->tabPagePeriodic->Controls->Add(this->checkPeriodicStop);
      this->tabPagePeriodic->Controls->Add(this->dateTimePeriodicStop);
      this->tabPagePeriodic->Controls->Add(this->dateTimePeriodicStart);
      this->tabPagePeriodic->Controls->Add(this->lblPeriodicStart);
      this->tabPagePeriodic->Controls->Add(this->lblPeriodicInterval2);
      this->tabPagePeriodic->Controls->Add(this->numPeriodicTreatments);
      this->tabPagePeriodic->Controls->Add(this->numPeriodicInterval);
      this->tabPagePeriodic->Controls->Add(this->lblPeriodicInterval1);
      this->tabPagePeriodic->Location = System::Drawing::Point(4, 24);
      this->tabPagePeriodic->Name = L"tabPagePeriodic";
      this->tabPagePeriodic->Size = System::Drawing::Size(492, 239);
      this->tabPagePeriodic->TabIndex = 4;
      this->tabPagePeriodic->Text = L"Periodic";
      this->tabPagePeriodic->UseVisualStyleBackColor = true;
      // 
      // checkPeriodicTreatments
      // 
      this->checkPeriodicTreatments->AutoSize = true;
      this->checkPeriodicTreatments->Location = System::Drawing::Point(72, 83);
      this->checkPeriodicTreatments->Name = L"checkPeriodicTreatments";
      this->checkPeriodicTreatments->Size = System::Drawing::Size(82, 17);
      this->checkPeriodicTreatments->TabIndex = 5;
      this->checkPeriodicTreatments->Text = L"Treatments:";
      this->checkPeriodicTreatments->UseVisualStyleBackColor = true;
      // 
      // checkPeriodicStop
      // 
      this->checkPeriodicStop->AutoSize = true;
      this->checkPeriodicStop->Location = System::Drawing::Point(88, 111);
      this->checkPeriodicStop->Name = L"checkPeriodicStop";
      this->checkPeriodicStop->Size = System::Drawing::Size(66, 17);
      this->checkPeriodicStop->TabIndex = 7;
      this->checkPeriodicStop->Text = L"Stop on:";
      this->checkPeriodicStop->UseVisualStyleBackColor = true;
      // 
      // dateTimePeriodicStop
      // 
      this->dateTimePeriodicStop->Location = System::Drawing::Point(160, 108);
      this->dateTimePeriodicStop->Name = L"dateTimePeriodicStop";
      this->dateTimePeriodicStop->Size = System::Drawing::Size(200, 20);
      this->dateTimePeriodicStop->TabIndex = 8;
      // 
      // dateTimePeriodicStart
      // 
      this->dateTimePeriodicStart->Location = System::Drawing::Point(160, 30);
      this->dateTimePeriodicStart->Name = L"dateTimePeriodicStart";
      this->dateTimePeriodicStart->Size = System::Drawing::Size(200, 20);
      this->dateTimePeriodicStart->TabIndex = 1;
      // 
      // lblPeriodicStart
      // 
      this->lblPeriodicStart->AutoSize = true;
      this->lblPeriodicStart->Location = System::Drawing::Point(107, 34);
      this->lblPeriodicStart->Name = L"lblPeriodicStart";
      this->lblPeriodicStart->Size = System::Drawing::Size(47, 13);
      this->lblPeriodicStart->TabIndex = 0;
      this->lblPeriodicStart->Text = L"Start on:";
      // 
      // lblPeriodicInterval2
      // 
      this->lblPeriodicInterval2->AutoSize = true;
      this->lblPeriodicInterval2->Location = System::Drawing::Point(209, 58);
      this->lblPeriodicInterval2->Name = L"lblPeriodicInterval2";
      this->lblPeriodicInterval2->Size = System::Drawing::Size(35, 13);
      this->lblPeriodicInterval2->TabIndex = 4;
      this->lblPeriodicInterval2->Text = L"day(s)";
      // 
      // numPeriodicTreatments
      // 
      this->numPeriodicTreatments->Location = System::Drawing::Point(160, 82);
      this->numPeriodicTreatments->Name = L"numPeriodicTreatments";
      this->numPeriodicTreatments->Size = System::Drawing::Size(43, 20);
      this->numPeriodicTreatments->TabIndex = 6;
      // 
      // numPeriodicInterval
      // 
      this->numPeriodicInterval->Location = System::Drawing::Point(160, 56);
      this->numPeriodicInterval->Name = L"numPeriodicInterval";
      this->numPeriodicInterval->Size = System::Drawing::Size(43, 20);
      this->numPeriodicInterval->TabIndex = 3;
      // 
      // lblPeriodicInterval1
      // 
      this->lblPeriodicInterval1->AutoSize = true;
      this->lblPeriodicInterval1->Location = System::Drawing::Point(117, 58);
      this->lblPeriodicInterval1->Name = L"lblPeriodicInterval1";
      this->lblPeriodicInterval1->Size = System::Drawing::Size(37, 13);
      this->lblPeriodicInterval1->TabIndex = 2;
      this->lblPeriodicInterval1->Text = L"Every:";
      // 
      // ScheduleForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(529, 294);
      this->Controls->Add(this->tabSchedule);
      this->Name = L"ScheduleForm";
      this->Text = L"ScheduleForm";
      this->Load += gcnew System::EventHandler(this, &ScheduleForm::OnLoad);
      this->tabSchedule->ResumeLayout(false);
      this->tabPageSingle->ResumeLayout(false);
      this->tabPageSingle->PerformLayout();
      this->tabPageWeekly->ResumeLayout(false);
      this->tabPageWeekly->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numWeeklyInterval))->EndInit();
      this->tabPageMonthly->ResumeLayout(false);
      this->tabPageMonthly->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMonthlyInterval))->EndInit();
      this->tabPageYearly->ResumeLayout(false);
      this->tabPageYearly->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numYearlyInterval))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numYearlyDay))->EndInit();
      this->tabPagePeriodic->ResumeLayout(false);
      this->tabPagePeriodic->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numPeriodicTreatments))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numPeriodicInterval))->EndInit();
      this->ResumeLayout(false);

    }
#pragma endregion
  };
}
