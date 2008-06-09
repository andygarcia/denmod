#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace gui {


  public ref class RunCimsimForm : public System::Windows::Forms::Form
	{


  // Constructors
	public:
		RunCimsimForm( BindingSource ^ locationBinding );
	protected:
		~RunCimsimForm();

  // Methods
  private:
    System::Void OnLoad(System::Object ^ sender, System::EventArgs ^ e);

    System::Void OnAllYearsChecked(System::Object ^ sender, System::EventArgs ^ e);
    System::Void OnRangeYearsChecked(System::Object ^ sender, System::EventArgs ^ e);

    System::Void OnStartYearChanged(System::Object ^ sender, System::EventArgs ^ e);
    System::Void OnStopYearChanged(System::Object ^ sender, System::EventArgs ^ e);

    System::Void OnRun(System::Object ^ sender, System::EventArgs ^ e);

  // Fields
  public:
    gui::Location::RunCimsimOptions ^ RunCimsimOptions;
  private:
    BindingSource ^ _locationBinding;


  private: System::Windows::Forms::CheckBox^  chkUsePop;
  private: System::Windows::Forms::GroupBox^  gboxYears;


  private: System::Windows::Forms::Label^  lblStopYear;
  private: System::Windows::Forms::Label^  lblStartYear;
  private: System::Windows::Forms::ComboBox^  cboxStopYear;
  private: System::Windows::Forms::ComboBox^  cboxStartYear;





  private: System::Windows::Forms::Button^  btnRun;
  private: System::Windows::Forms::Button^  btnCancel;
  private: System::Windows::Forms::RadioButton^  radUseRange;
  private: System::Windows::Forms::RadioButton^  radUseAll;








  protected: 

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
      this->chkUsePop = (gcnew System::Windows::Forms::CheckBox());
      this->gboxYears = (gcnew System::Windows::Forms::GroupBox());
      this->radUseRange = (gcnew System::Windows::Forms::RadioButton());
      this->radUseAll = (gcnew System::Windows::Forms::RadioButton());
      this->lblStopYear = (gcnew System::Windows::Forms::Label());
      this->lblStartYear = (gcnew System::Windows::Forms::Label());
      this->cboxStopYear = (gcnew System::Windows::Forms::ComboBox());
      this->cboxStartYear = (gcnew System::Windows::Forms::ComboBox());
      this->btnRun = (gcnew System::Windows::Forms::Button());
      this->btnCancel = (gcnew System::Windows::Forms::Button());
      this->gboxYears->SuspendLayout();
      this->SuspendLayout();
      // 
      // chkUsePop
      // 
      this->chkUsePop->AutoSize = true;
      this->chkUsePop->Checked = true;
      this->chkUsePop->CheckState = System::Windows::Forms::CheckState::Checked;
      this->chkUsePop->Location = System::Drawing::Point(12, 12);
      this->chkUsePop->Name = L"chkUsePop";
      this->chkUsePop->Size = System::Drawing::Size(153, 17);
      this->chkUsePop->TabIndex = 0;
      this->chkUsePop->Text = L"Use established population";
      this->chkUsePop->UseVisualStyleBackColor = true;
      // 
      // gboxYears
      // 
      this->gboxYears->Controls->Add(this->radUseRange);
      this->gboxYears->Controls->Add(this->radUseAll);
      this->gboxYears->Controls->Add(this->lblStopYear);
      this->gboxYears->Controls->Add(this->lblStartYear);
      this->gboxYears->Controls->Add(this->cboxStopYear);
      this->gboxYears->Controls->Add(this->cboxStartYear);
      this->gboxYears->Location = System::Drawing::Point(12, 35);
      this->gboxYears->Name = L"gboxYears";
      this->gboxYears->Size = System::Drawing::Size(222, 119);
      this->gboxYears->TabIndex = 1;
      this->gboxYears->TabStop = false;
      this->gboxYears->Text = L"Simulation Year Range (from weather)";
      // 
      // radUseRange
      // 
      this->radUseRange->AutoSize = true;
      this->radUseRange->Location = System::Drawing::Point(6, 42);
      this->radUseRange->Name = L"radUseRange";
      this->radUseRange->Size = System::Drawing::Size(179, 17);
      this->radUseRange->TabIndex = 1;
      this->radUseRange->Text = L"Use the following range of years:";
      this->radUseRange->UseVisualStyleBackColor = true;
      this->radUseRange->CheckedChanged += gcnew System::EventHandler(this, &RunCimsimForm::OnRangeYearsChecked);
      // 
      // radUseAll
      // 
      this->radUseAll->AutoSize = true;
      this->radUseAll->Checked = true;
      this->radUseAll->Location = System::Drawing::Point(6, 19);
      this->radUseAll->Name = L"radUseAll";
      this->radUseAll->Size = System::Drawing::Size(130, 17);
      this->radUseAll->TabIndex = 0;
      this->radUseAll->TabStop = true;
      this->radUseAll->Text = L"Use all available years";
      this->radUseAll->UseVisualStyleBackColor = true;
      this->radUseAll->CheckedChanged += gcnew System::EventHandler(this, &RunCimsimForm::OnAllYearsChecked);
      // 
      // lblStopYear
      // 
      this->lblStopYear->AutoSize = true;
      this->lblStopYear->Location = System::Drawing::Point(25, 95);
      this->lblStopYear->Name = L"lblStopYear";
      this->lblStopYear->Size = System::Drawing::Size(32, 13);
      this->lblStopYear->TabIndex = 4;
      this->lblStopYear->Text = L"Stop:";
      // 
      // lblStartYear
      // 
      this->lblStartYear->AutoSize = true;
      this->lblStartYear->Location = System::Drawing::Point(25, 68);
      this->lblStartYear->Name = L"lblStartYear";
      this->lblStartYear->Size = System::Drawing::Size(32, 13);
      this->lblStartYear->TabIndex = 2;
      this->lblStartYear->Text = L"Start:";
      // 
      // cboxStopYear
      // 
      this->cboxStopYear->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxStopYear->Enabled = false;
      this->cboxStopYear->FormattingEnabled = true;
      this->cboxStopYear->Location = System::Drawing::Point(63, 92);
      this->cboxStopYear->Name = L"cboxStopYear";
      this->cboxStopYear->Size = System::Drawing::Size(121, 21);
      this->cboxStopYear->TabIndex = 5;
      this->cboxStopYear->SelectionChangeCommitted += gcnew System::EventHandler(this, &RunCimsimForm::OnStopYearChanged);
      // 
      // cboxStartYear
      // 
      this->cboxStartYear->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxStartYear->Enabled = false;
      this->cboxStartYear->FormattingEnabled = true;
      this->cboxStartYear->Location = System::Drawing::Point(63, 65);
      this->cboxStartYear->Name = L"cboxStartYear";
      this->cboxStartYear->Size = System::Drawing::Size(121, 21);
      this->cboxStartYear->TabIndex = 3;
      this->cboxStartYear->SelectionChangeCommitted += gcnew System::EventHandler(this, &RunCimsimForm::OnStartYearChanged);
      // 
      // btnRun
      // 
      this->btnRun->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->btnRun->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->btnRun->Location = System::Drawing::Point(12, 160);
      this->btnRun->Name = L"btnRun";
      this->btnRun->Size = System::Drawing::Size(75, 23);
      this->btnRun->TabIndex = 2;
      this->btnRun->Text = L"Run";
      this->btnRun->UseVisualStyleBackColor = true;
      this->btnRun->Click += gcnew System::EventHandler(this, &RunCimsimForm::OnRun);
      // 
      // btnCancel
      // 
      this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
      this->btnCancel->Location = System::Drawing::Point(159, 160);
      this->btnCancel->Name = L"btnCancel";
      this->btnCancel->Size = System::Drawing::Size(75, 23);
      this->btnCancel->TabIndex = 3;
      this->btnCancel->Text = L"Cancel";
      this->btnCancel->UseVisualStyleBackColor = true;
      // 
      // RunCimsimForm
      // 
      this->AcceptButton = this->btnRun;
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->CancelButton = this->btnCancel;
      this->ClientSize = System::Drawing::Size(246, 195);
      this->Controls->Add(this->btnCancel);
      this->Controls->Add(this->btnRun);
      this->Controls->Add(this->chkUsePop);
      this->Controls->Add(this->gboxYears);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
      this->Name = L"RunCimsimForm";
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
      this->Text = L"Run CIMSiM";
      this->Load += gcnew System::EventHandler(this, &RunCimsimForm::OnLoad);
      this->gboxYears->ResumeLayout(false);
      this->gboxYears->PerformLayout();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  };
}
