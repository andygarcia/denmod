#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace gui {

	public ref class YearlySchedulePanel : public System::Windows::Forms::UserControl
	{
	public:
		YearlySchedulePanel( gui::YearlySchedule ^ ys, BindingSource ^ locationBinding );
	protected:
		~YearlySchedulePanel();

  private:
    BindingSource ^ LocationBinding;
    gui::Location ^ ActiveLocation;
    gui::Schedule ^ Schedule_;

  private:
    System::Void OnLoad( System::Object ^ sender, System::EventArgs ^ e);

  private: System::Windows::Forms::ComboBox^  cboxYearlyStart;
  private: System::Windows::Forms::Label^  lblYearlyStart;
  private: System::Windows::Forms::Label^  lblYearlyDay2;
  private: System::Windows::Forms::Label^  lblYearlyInterval1;
  private: System::Windows::Forms::Label^  lblYearlyInterval2;
  private: System::Windows::Forms::NumericUpDown^  numYearlyInterval;
  private: System::Windows::Forms::NumericUpDown^  numYearlyDay;
  private: System::Windows::Forms::Label^  lblYearlyDay1;

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
      this->cboxYearlyStart = (gcnew System::Windows::Forms::ComboBox());
      this->lblYearlyStart = (gcnew System::Windows::Forms::Label());
      this->lblYearlyDay2 = (gcnew System::Windows::Forms::Label());
      this->lblYearlyInterval1 = (gcnew System::Windows::Forms::Label());
      this->lblYearlyInterval2 = (gcnew System::Windows::Forms::Label());
      this->numYearlyInterval = (gcnew System::Windows::Forms::NumericUpDown());
      this->numYearlyDay = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblYearlyDay1 = (gcnew System::Windows::Forms::Label());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numYearlyInterval))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numYearlyDay))->BeginInit();
      this->SuspendLayout();
      // 
      // cboxYearlyStart
      // 
      this->cboxYearlyStart->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxYearlyStart->FormattingEnabled = true;
      this->cboxYearlyStart->Location = System::Drawing::Point(100, 20);
      this->cboxYearlyStart->Name = L"cboxYearlyStart";
      this->cboxYearlyStart->Size = System::Drawing::Size(121, 21);
      this->cboxYearlyStart->TabIndex = 9;
      // 
      // lblYearlyStart
      // 
      this->lblYearlyStart->AutoSize = true;
      this->lblYearlyStart->Location = System::Drawing::Point(51, 23);
      this->lblYearlyStart->Name = L"lblYearlyStart";
      this->lblYearlyStart->Size = System::Drawing::Size(43, 13);
      this->lblYearlyStart->TabIndex = 8;
      this->lblYearlyStart->Text = L"Start in:";
      // 
      // lblYearlyDay2
      // 
      this->lblYearlyDay2->AutoSize = true;
      this->lblYearlyDay2->Location = System::Drawing::Point(149, 75);
      this->lblYearlyDay2->Name = L"lblYearlyDay2";
      this->lblYearlyDay2->Size = System::Drawing::Size(77, 13);
      this->lblYearlyDay2->TabIndex = 15;
      this->lblYearlyDay2->Text = L"day of the year";
      // 
      // lblYearlyInterval1
      // 
      this->lblYearlyInterval1->AutoSize = true;
      this->lblYearlyInterval1->Location = System::Drawing::Point(57, 49);
      this->lblYearlyInterval1->Name = L"lblYearlyInterval1";
      this->lblYearlyInterval1->Size = System::Drawing::Size(37, 13);
      this->lblYearlyInterval1->TabIndex = 10;
      this->lblYearlyInterval1->Text = L"Every:";
      // 
      // lblYearlyInterval2
      // 
      this->lblYearlyInterval2->AutoSize = true;
      this->lblYearlyInterval2->Location = System::Drawing::Point(149, 49);
      this->lblYearlyInterval2->Name = L"lblYearlyInterval2";
      this->lblYearlyInterval2->Size = System::Drawing::Size(38, 13);
      this->lblYearlyInterval2->TabIndex = 12;
      this->lblYearlyInterval2->Text = L"year(s)";
      // 
      // numYearlyInterval
      // 
      this->numYearlyInterval->Location = System::Drawing::Point(100, 47);
      this->numYearlyInterval->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numYearlyInterval->Name = L"numYearlyInterval";
      this->numYearlyInterval->Size = System::Drawing::Size(43, 20);
      this->numYearlyInterval->TabIndex = 11;
      this->numYearlyInterval->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      // 
      // numYearlyDay
      // 
      this->numYearlyDay->Location = System::Drawing::Point(100, 73);
      this->numYearlyDay->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {365, 0, 0, 0});
      this->numYearlyDay->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numYearlyDay->Name = L"numYearlyDay";
      this->numYearlyDay->Size = System::Drawing::Size(43, 20);
      this->numYearlyDay->TabIndex = 14;
      this->numYearlyDay->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      // 
      // lblYearlyDay1
      // 
      this->lblYearlyDay1->AutoSize = true;
      this->lblYearlyDay1->Location = System::Drawing::Point(52, 75);
      this->lblYearlyDay1->Name = L"lblYearlyDay1";
      this->lblYearlyDay1->Size = System::Drawing::Size(42, 13);
      this->lblYearlyDay1->TabIndex = 13;
      this->lblYearlyDay1->Text = L"On the:";
      // 
      // YearlySchedulePanel
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->BackColor = System::Drawing::SystemColors::Window;
      this->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->Controls->Add(this->cboxYearlyStart);
      this->Controls->Add(this->lblYearlyStart);
      this->Controls->Add(this->lblYearlyDay2);
      this->Controls->Add(this->lblYearlyInterval1);
      this->Controls->Add(this->lblYearlyInterval2);
      this->Controls->Add(this->numYearlyInterval);
      this->Controls->Add(this->numYearlyDay);
      this->Controls->Add(this->lblYearlyDay1);
      this->Name = L"YearlySchedulePanel";
      this->Size = System::Drawing::Size(420, 200);
      this->Load += gcnew System::EventHandler(this, &YearlySchedulePanel::OnLoad);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numYearlyInterval))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numYearlyDay))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
	};
}
