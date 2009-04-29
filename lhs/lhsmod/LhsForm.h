#pragma once

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
    void InitializeBackgroundWorker(void);
    void DoRuns( Object ^ sender, DoWorkEventArgs ^ e );
    void RunProgressChanged( Object ^ sender, ProgressChangedEventArgs ^ e );
    void FinishedRuns( Object ^ sender, RunWorkerCompletedEventArgs ^ e );

  private:

    ref class StudyState
    {
    public:
      int NumberRuns;
      bool useDiscrete;
      int CurrentRun;
      TimeSpan RunTime;
    };

    BackgroundWorker ^ _backgroundWorkerCimsim;
    Generic::Dictionary<String^,String^> ^ _saToDmlMap;

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
  private: System::Windows::Forms::Label^  lblCompletedRuns;
  private: System::Windows::Forms::Label^  lblEstimatedTime;
  private: System::Windows::Forms::CheckBox^  chkDiscrete;









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
      this->lblCompletedRuns = (gcnew System::Windows::Forms::Label());
      this->lblEstimatedTime = (gcnew System::Windows::Forms::Label());
      this->chkDiscrete = (gcnew System::Windows::Forms::CheckBox());
      this->SuspendLayout();
      // 
      // tboxLsp
      // 
      this->tboxLsp->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->tboxLsp->Location = System::Drawing::Point(105, 43);
      this->tboxLsp->Name = L"tboxLsp";
      this->tboxLsp->Size = System::Drawing::Size(274, 20);
      this->tboxLsp->TabIndex = 0;
      // 
      // tboxOutput
      // 
      this->tboxOutput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->tboxOutput->Location = System::Drawing::Point(105, 72);
      this->tboxOutput->Name = L"tboxOutput";
      this->tboxOutput->Size = System::Drawing::Size(274, 20);
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
      this->btnBrowseLsp->Location = System::Drawing::Point(385, 41);
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
      this->btnBrowseOutput->Location = System::Drawing::Point(385, 70);
      this->btnBrowseOutput->Name = L"btnBrowseOutput";
      this->btnBrowseOutput->Size = System::Drawing::Size(75, 23);
      this->btnBrowseOutput->TabIndex = 3;
      this->btnBrowseOutput->Text = L"Browse";
      this->btnBrowseOutput->UseVisualStyleBackColor = true;
      this->btnBrowseOutput->Click += gcnew System::EventHandler(this, &LhsForm::OnBrowseOutput);
      // 
      // btnRun
      // 
      this->btnRun->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnRun->Location = System::Drawing::Point(385, 201);
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
      this->tboxDml->Size = System::Drawing::Size(274, 20);
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
      this->btnBrowseDml->Location = System::Drawing::Point(385, 12);
      this->btnBrowseDml->Name = L"btnBrowseDml";
      this->btnBrowseDml->Size = System::Drawing::Size(75, 23);
      this->btnBrowseDml->TabIndex = 3;
      this->btnBrowseDml->Text = L"Browse";
      this->btnBrowseDml->UseVisualStyleBackColor = true;
      this->btnBrowseDml->Click += gcnew System::EventHandler(this, &LhsForm::OnBrowseDml);
      // 
      // pbarRuns
      // 
      this->pbarRuns->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->pbarRuns->Location = System::Drawing::Point(105, 201);
      this->pbarRuns->Name = L"pbarRuns";
      this->pbarRuns->Size = System::Drawing::Size(274, 23);
      this->pbarRuns->TabIndex = 5;
      // 
      // lblCompletedRuns
      // 
      this->lblCompletedRuns->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->lblCompletedRuns->AutoSize = true;
      this->lblCompletedRuns->Location = System::Drawing::Point(102, 164);
      this->lblCompletedRuns->Name = L"lblCompletedRuns";
      this->lblCompletedRuns->Size = System::Drawing::Size(108, 13);
      this->lblCompletedRuns->TabIndex = 6;
      this->lblCompletedRuns->Text = L"Runs Completed: 0/0";
      // 
      // lblEstimatedTime
      // 
      this->lblEstimatedTime->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->lblEstimatedTime->AutoSize = true;
      this->lblEstimatedTime->Location = System::Drawing::Point(102, 181);
      this->lblEstimatedTime->Name = L"lblEstimatedTime";
      this->lblEstimatedTime->Size = System::Drawing::Size(146, 13);
      this->lblEstimatedTime->TabIndex = 7;
      this->lblEstimatedTime->Text = L"Estimated Time Left: 0:00 min";
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
      // LhsForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(472, 236);
      this->Controls->Add(this->chkDiscrete);
      this->Controls->Add(this->lblEstimatedTime);
      this->Controls->Add(this->lblCompletedRuns);
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
