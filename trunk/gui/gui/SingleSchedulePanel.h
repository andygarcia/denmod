#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace gui {

  public ref class SingleSchedulePanel : public System::Windows::Forms::UserControl
	{
	public:
    SingleSchedulePanel( gui::SingleSchedule ^ ss, BindingSource ^ locationBinding );
	protected:
		~SingleSchedulePanel();

  private:
    System::Void OnLoad( System::Object ^ sender, System::EventArgs ^ e);

  protected:
    BindingSource ^ LocationBinding;
    gui::Location ^ ActiveLocation;
    gui::Schedule ^ Schedule_;

  private: System::Windows::Forms::Label^  lblSingleStart;
  private: System::Windows::Forms::DateTimePicker^  dateTimeSingleStart;

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
      this->dateTimeSingleStart = (gcnew System::Windows::Forms::DateTimePicker());
      this->lblSingleStart = (gcnew System::Windows::Forms::Label());
      this->SuspendLayout();
      // 
      // dateTimeSingleStart
      // 
      this->dateTimeSingleStart->Location = System::Drawing::Point(100, 20);
      this->dateTimeSingleStart->Name = L"dateTimeSingleStart";
      this->dateTimeSingleStart->Size = System::Drawing::Size(200, 20);
      this->dateTimeSingleStart->TabIndex = 3;
      this->dateTimeSingleStart->Validated += gcnew System::EventHandler(this, &SingleSchedulePanel::OnValidated);
      this->dateTimeSingleStart->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &SingleSchedulePanel::OnValidating);
      // 
      // lblSingleStart
      // 
      this->lblSingleStart->AutoSize = true;
      this->lblSingleStart->Location = System::Drawing::Point(24, 24);
      this->lblSingleStart->Name = L"lblSingleStart";
      this->lblSingleStart->Size = System::Drawing::Size(70, 13);
      this->lblSingleStart->TabIndex = 2;
      this->lblSingleStart->Text = L"Schedule on:";
      // 
      // SingleSchedulePanel
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->BackColor = System::Drawing::SystemColors::Window;
      this->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->Controls->Add(this->dateTimeSingleStart);
      this->Controls->Add(this->lblSingleStart);
      this->Name = L"SingleSchedulePanel";
      this->Size = System::Drawing::Size(420, 200);
      this->Load += gcnew System::EventHandler(this, &SingleSchedulePanel::OnLoad);
      this->Validated += gcnew System::EventHandler(this, &SingleSchedulePanel::OnValidated);
      this->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &SingleSchedulePanel::OnValidating);
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  private: System::Void OnValidating(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
           }
  private: System::Void OnValidated(System::Object^  sender, System::EventArgs^  e) {
           }
  };
}
