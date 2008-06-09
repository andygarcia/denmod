#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace gui {

	public ref class PeriodicSchedulePanel : public System::Windows::Forms::UserControl
	{
	public:
		PeriodicSchedulePanel( gui::PeriodicSchedule ^ ps, BindingSource ^ locationBinding );
	protected:
		~PeriodicSchedulePanel();

  private:
    System::Void OnLoad( System::Object ^ sender, System::EventArgs ^ e );

  private:
    BindingSource ^ LocationBinding;
    gui::Location ^ ActiveLocation;
    gui::Schedule ^ Schedule_;

  private: System::Windows::Forms::CheckBox^  checkPeriodicTreatments;
  private: System::Windows::Forms::CheckBox^  checkPeriodicStop;
  private: System::Windows::Forms::DateTimePicker^  dateTimePeriodicStop;
  private: System::Windows::Forms::DateTimePicker^  dateTimePeriodicStart;
  private: System::Windows::Forms::Label^  lblPeriodicStart;
  private: System::Windows::Forms::Label^  lblPeriodicInterval2;
  private: System::Windows::Forms::NumericUpDown^  numPeriodicTreatments;
  private: System::Windows::Forms::NumericUpDown^  numPeriodicInterval;
  private: System::Windows::Forms::Label^  lblPeriodicInterval1;

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
      this->checkPeriodicTreatments = (gcnew System::Windows::Forms::CheckBox());
      this->checkPeriodicStop = (gcnew System::Windows::Forms::CheckBox());
      this->dateTimePeriodicStop = (gcnew System::Windows::Forms::DateTimePicker());
      this->dateTimePeriodicStart = (gcnew System::Windows::Forms::DateTimePicker());
      this->lblPeriodicStart = (gcnew System::Windows::Forms::Label());
      this->lblPeriodicInterval2 = (gcnew System::Windows::Forms::Label());
      this->numPeriodicTreatments = (gcnew System::Windows::Forms::NumericUpDown());
      this->numPeriodicInterval = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblPeriodicInterval1 = (gcnew System::Windows::Forms::Label());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numPeriodicTreatments))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numPeriodicInterval))->BeginInit();
      this->SuspendLayout();
      // 
      // checkPeriodicTreatments
      // 
      this->checkPeriodicTreatments->AutoSize = true;
      this->checkPeriodicTreatments->Location = System::Drawing::Point(12, 73);
      this->checkPeriodicTreatments->Name = L"checkPeriodicTreatments";
      this->checkPeriodicTreatments->Size = System::Drawing::Size(82, 17);
      this->checkPeriodicTreatments->TabIndex = 14;
      this->checkPeriodicTreatments->Text = L"Treatments:";
      this->checkPeriodicTreatments->UseVisualStyleBackColor = true;
      // 
      // checkPeriodicStop
      // 
      this->checkPeriodicStop->AutoSize = true;
      this->checkPeriodicStop->Location = System::Drawing::Point(28, 101);
      this->checkPeriodicStop->Name = L"checkPeriodicStop";
      this->checkPeriodicStop->Size = System::Drawing::Size(66, 17);
      this->checkPeriodicStop->TabIndex = 16;
      this->checkPeriodicStop->Text = L"Stop on:";
      this->checkPeriodicStop->UseVisualStyleBackColor = true;
      // 
      // dateTimePeriodicStop
      // 
      this->dateTimePeriodicStop->Location = System::Drawing::Point(100, 98);
      this->dateTimePeriodicStop->Name = L"dateTimePeriodicStop";
      this->dateTimePeriodicStop->Size = System::Drawing::Size(200, 20);
      this->dateTimePeriodicStop->TabIndex = 17;
      // 
      // dateTimePeriodicStart
      // 
      this->dateTimePeriodicStart->Location = System::Drawing::Point(100, 20);
      this->dateTimePeriodicStart->Name = L"dateTimePeriodicStart";
      this->dateTimePeriodicStart->Size = System::Drawing::Size(200, 20);
      this->dateTimePeriodicStart->TabIndex = 10;
      // 
      // lblPeriodicStart
      // 
      this->lblPeriodicStart->AutoSize = true;
      this->lblPeriodicStart->Location = System::Drawing::Point(47, 24);
      this->lblPeriodicStart->Name = L"lblPeriodicStart";
      this->lblPeriodicStart->Size = System::Drawing::Size(47, 13);
      this->lblPeriodicStart->TabIndex = 9;
      this->lblPeriodicStart->Text = L"Start on:";
      // 
      // lblPeriodicInterval2
      // 
      this->lblPeriodicInterval2->AutoSize = true;
      this->lblPeriodicInterval2->Location = System::Drawing::Point(149, 48);
      this->lblPeriodicInterval2->Name = L"lblPeriodicInterval2";
      this->lblPeriodicInterval2->Size = System::Drawing::Size(35, 13);
      this->lblPeriodicInterval2->TabIndex = 13;
      this->lblPeriodicInterval2->Text = L"day(s)";
      // 
      // numPeriodicTreatments
      // 
      this->numPeriodicTreatments->Location = System::Drawing::Point(100, 72);
      this->numPeriodicTreatments->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numPeriodicTreatments->Name = L"numPeriodicTreatments";
      this->numPeriodicTreatments->Size = System::Drawing::Size(43, 20);
      this->numPeriodicTreatments->TabIndex = 15;
      this->numPeriodicTreatments->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      // 
      // numPeriodicInterval
      // 
      this->numPeriodicInterval->Location = System::Drawing::Point(100, 46);
      this->numPeriodicInterval->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numPeriodicInterval->Name = L"numPeriodicInterval";
      this->numPeriodicInterval->Size = System::Drawing::Size(43, 20);
      this->numPeriodicInterval->TabIndex = 12;
      this->numPeriodicInterval->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      // 
      // lblPeriodicInterval1
      // 
      this->lblPeriodicInterval1->AutoSize = true;
      this->lblPeriodicInterval1->Location = System::Drawing::Point(57, 48);
      this->lblPeriodicInterval1->Name = L"lblPeriodicInterval1";
      this->lblPeriodicInterval1->Size = System::Drawing::Size(37, 13);
      this->lblPeriodicInterval1->TabIndex = 11;
      this->lblPeriodicInterval1->Text = L"Every:";
      // 
      // PeriodicSchedulePanel
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->BackColor = System::Drawing::SystemColors::Window;
      this->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->Controls->Add(this->checkPeriodicTreatments);
      this->Controls->Add(this->checkPeriodicStop);
      this->Controls->Add(this->dateTimePeriodicStop);
      this->Controls->Add(this->dateTimePeriodicStart);
      this->Controls->Add(this->lblPeriodicStart);
      this->Controls->Add(this->lblPeriodicInterval2);
      this->Controls->Add(this->numPeriodicTreatments);
      this->Controls->Add(this->numPeriodicInterval);
      this->Controls->Add(this->lblPeriodicInterval1);
      this->Name = L"PeriodicSchedulePanel";
      this->Size = System::Drawing::Size(420, 200);
      this->Load += gcnew System::EventHandler(this, &PeriodicSchedulePanel::OnLoad);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numPeriodicTreatments))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numPeriodicInterval))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  private: System::Void StopDateChanged(System::Object^  sender, System::EventArgs^  e) {
           }
private: System::Void OnBindingContextChanged(System::Object^  sender, System::EventArgs^  e) {
         }
};
}
