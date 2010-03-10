#pragma once
#include "SensitivityAnalysis.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace lhsmod {

	public ref class LhsForm : public System::Windows::Forms::Form
	{
	public:
		LhsForm(void);
	protected:
		~LhsForm(void);

  private:
    System::Void OnBrowseDml(System::Object^  sender, System::EventArgs^  e);
    System::Void OnBrowseLsp(System::Object^  sender, System::EventArgs^  e);
    System::Void OnBrowseOutput(System::Object^  sender, System::EventArgs^  e);
    System::Void OnRun(System::Object^  sender, System::EventArgs^  e);

    void StartStudy( Object ^ sender, DoWorkEventArgs ^ e );
    void StudyProgressChanged( Object ^ sender, ProgressChangedEventArgs ^ e );
    void StudyCompleted( Object ^ sender, RunWorkerCompletedEventArgs ^ e );

  private:
    SensitivityAnalysisStudy ^ _study;

    ref class StudyState
    {
    public:
      int NumberRuns;
      bool useDiscrete;
      bool doProcessOnly;
      int CurrentRun;
      TimeSpan RunTime;
    };

    BackgroundWorker ^ _fileReader;
    BackgroundWorker ^ _backgroundWorker;

  private: System::Windows::Forms::TextBox^  tboxLsp;
  private: System::Windows::Forms::TextBox^  tboxOutput;
  private: System::Windows::Forms::Label^  lblLsp;
  private: System::Windows::Forms::Label^  lblOutput;
  private: System::Windows::Forms::Button^  btnBrowseLsp;
  private: System::Windows::Forms::Button^  btnBrowseOutput;
  private: System::Windows::Forms::Button^  btnRun;
  private: System::Windows::Forms::TextBox^  tboxDml;
  private: System::Windows::Forms::Label^  lblDml;
  private: System::Windows::Forms::Button^  btnBrowseDml;
  private: System::Windows::Forms::ProgressBar^  pbarRuns;


  private: System::Windows::Forms::CheckBox^  chkDiscrete;
  private: System::Windows::Forms::CheckBox^  chkProcessOnly;
  private: System::Windows::Forms::RichTextBox^  rboxOutput;









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
      this->tboxLsp = (gcnew System::Windows::Forms::TextBox());
      this->tboxOutput = (gcnew System::Windows::Forms::TextBox());
      this->lblLsp = (gcnew System::Windows::Forms::Label());
      this->lblOutput = (gcnew System::Windows::Forms::Label());
      this->btnBrowseLsp = (gcnew System::Windows::Forms::Button());
      this->btnBrowseOutput = (gcnew System::Windows::Forms::Button());
      this->btnRun = (gcnew System::Windows::Forms::Button());
      this->tboxDml = (gcnew System::Windows::Forms::TextBox());
      this->lblDml = (gcnew System::Windows::Forms::Label());
      this->btnBrowseDml = (gcnew System::Windows::Forms::Button());
      this->pbarRuns = (gcnew System::Windows::Forms::ProgressBar());
      this->chkDiscrete = (gcnew System::Windows::Forms::CheckBox());
      this->chkProcessOnly = (gcnew System::Windows::Forms::CheckBox());
      this->rboxOutput = (gcnew System::Windows::Forms::RichTextBox());
      this->SuspendLayout();
      // 
      // tboxLsp
      // 
      this->tboxLsp->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->tboxLsp->Location = System::Drawing::Point(105, 43);
      this->tboxLsp->Name = L"tboxLsp";
      this->tboxLsp->Size = System::Drawing::Size(387, 20);
      this->tboxLsp->TabIndex = 0;
      // 
      // tboxOutput
      // 
      this->tboxOutput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->tboxOutput->Location = System::Drawing::Point(105, 72);
      this->tboxOutput->Name = L"tboxOutput";
      this->tboxOutput->Size = System::Drawing::Size(387, 20);
      this->tboxOutput->TabIndex = 1;
      // 
      // lblLsp
      // 
      this->lblLsp->AutoSize = true;
      this->lblLsp->Location = System::Drawing::Point(12, 46);
      this->lblLsp->Name = L"lblLsp";
      this->lblLsp->Size = System::Drawing::Size(52, 13);
      this->lblLsp->TabIndex = 2;
      this->lblLsp->Text = L".LSP File:";
      // 
      // lblOutput
      // 
      this->lblOutput->AutoSize = true;
      this->lblOutput->Location = System::Drawing::Point(12, 75);
      this->lblOutput->Name = L"lblOutput";
      this->lblOutput->Size = System::Drawing::Size(87, 13);
      this->lblOutput->TabIndex = 2;
      this->lblOutput->Text = L"Output Directory:";
      // 
      // btnBrowseLsp
      // 
      this->btnBrowseLsp->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->btnBrowseLsp->Location = System::Drawing::Point(498, 41);
      this->btnBrowseLsp->Name = L"btnBrowseLsp";
      this->btnBrowseLsp->Size = System::Drawing::Size(75, 23);
      this->btnBrowseLsp->TabIndex = 3;
      this->btnBrowseLsp->Text = L"Browse";
      this->btnBrowseLsp->UseVisualStyleBackColor = true;
      this->btnBrowseLsp->Click += gcnew System::EventHandler(this, &LhsForm::OnBrowseLsp);
      // 
      // btnBrowseOutput
      // 
      this->btnBrowseOutput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->btnBrowseOutput->Location = System::Drawing::Point(498, 70);
      this->btnBrowseOutput->Name = L"btnBrowseOutput";
      this->btnBrowseOutput->Size = System::Drawing::Size(75, 23);
      this->btnBrowseOutput->TabIndex = 3;
      this->btnBrowseOutput->Text = L"Browse";
      this->btnBrowseOutput->UseVisualStyleBackColor = true;
      this->btnBrowseOutput->Click += gcnew System::EventHandler(this, &LhsForm::OnBrowseOutput);
      // 
      // btnRun
      // 
      this->btnRun->Location = System::Drawing::Point(12, 143);
      this->btnRun->Name = L"btnRun";
      this->btnRun->Size = System::Drawing::Size(75, 23);
      this->btnRun->TabIndex = 4;
      this->btnRun->Text = L"Run";
      this->btnRun->UseVisualStyleBackColor = true;
      this->btnRun->Click += gcnew System::EventHandler(this, &LhsForm::OnRun);
      // 
      // tboxDml
      // 
      this->tboxDml->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->tboxDml->Location = System::Drawing::Point(105, 14);
      this->tboxDml->Name = L"tboxDml";
      this->tboxDml->Size = System::Drawing::Size(387, 20);
      this->tboxDml->TabIndex = 0;
      // 
      // lblDml
      // 
      this->lblDml->AutoSize = true;
      this->lblDml->Location = System::Drawing::Point(12, 17);
      this->lblDml->Name = L"lblDml";
      this->lblDml->Size = System::Drawing::Size(52, 13);
      this->lblDml->TabIndex = 2;
      this->lblDml->Text = L".DML File";
      // 
      // btnBrowseDml
      // 
      this->btnBrowseDml->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->btnBrowseDml->Location = System::Drawing::Point(498, 12);
      this->btnBrowseDml->Name = L"btnBrowseDml";
      this->btnBrowseDml->Size = System::Drawing::Size(75, 23);
      this->btnBrowseDml->TabIndex = 3;
      this->btnBrowseDml->Text = L"Browse";
      this->btnBrowseDml->UseVisualStyleBackColor = true;
      this->btnBrowseDml->Click += gcnew System::EventHandler(this, &LhsForm::OnBrowseDml);
      // 
      // pbarRuns
      // 
      this->pbarRuns->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->pbarRuns->Location = System::Drawing::Point(105, 144);
      this->pbarRuns->Name = L"pbarRuns";
      this->pbarRuns->Size = System::Drawing::Size(468, 23);
      this->pbarRuns->TabIndex = 5;
      // 
      // chkDiscrete
      // 
      this->chkDiscrete->AutoSize = true;
      this->chkDiscrete->Location = System::Drawing::Point(105, 98);
      this->chkDiscrete->Name = L"chkDiscrete";
      this->chkDiscrete->Size = System::Drawing::Size(133, 17);
      this->chkDiscrete->TabIndex = 8;
      this->chkDiscrete->Text = L"Discrete cohort counts";
      this->chkDiscrete->UseVisualStyleBackColor = true;
      // 
      // chkProcessOnly
      // 
      this->chkProcessOnly->AutoSize = true;
      this->chkProcessOnly->Location = System::Drawing::Point(105, 121);
      this->chkProcessOnly->Name = L"chkProcessOnly";
      this->chkProcessOnly->Size = System::Drawing::Size(251, 17);
      this->chkProcessOnly->TabIndex = 8;
      this->chkProcessOnly->Text = L"Disable simulation - process DML and LSP only.";
      this->chkProcessOnly->UseVisualStyleBackColor = true;
      // 
      // rboxOutput
      // 
      this->rboxOutput->Location = System::Drawing::Point(105, 173);
      this->rboxOutput->Name = L"rboxOutput";
      this->rboxOutput->Size = System::Drawing::Size(468, 248);
      this->rboxOutput->TabIndex = 9;
      this->rboxOutput->Text = L"";
      // 
      // LhsForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(585, 433);
      this->Controls->Add(this->rboxOutput);
      this->Controls->Add(this->chkProcessOnly);
      this->Controls->Add(this->chkDiscrete);
      this->Controls->Add(this->pbarRuns);
      this->Controls->Add(this->btnRun);
      this->Controls->Add(this->btnBrowseOutput);
      this->Controls->Add(this->btnBrowseDml);
      this->Controls->Add(this->btnBrowseLsp);
      this->Controls->Add(this->lblDml);
      this->Controls->Add(this->lblOutput);
      this->Controls->Add(this->lblLsp);
      this->Controls->Add(this->tboxDml);
      this->Controls->Add(this->tboxOutput);
      this->Controls->Add(this->tboxLsp);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
      this->MinimumSize = System::Drawing::Size(480, 220);
      this->Name = L"LhsForm";
      this->Text = L"LHSWIN -CIMSiM Sensitivity Analysis Study";
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  };
}
