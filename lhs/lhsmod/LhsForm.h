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

  private:
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
      this->SuspendLayout();
      // 
      // tboxLsp
      // 
      this->tboxLsp->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->tboxLsp->Location = System::Drawing::Point(105, 43);
      this->tboxLsp->Name = L"tboxLsp";
      this->tboxLsp->Size = System::Drawing::Size(225, 20);
      this->tboxLsp->TabIndex = 0;
      // 
      // tboxOutput
      // 
      this->tboxOutput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->tboxOutput->Location = System::Drawing::Point(105, 72);
      this->tboxOutput->Name = L"tboxOutput";
      this->tboxOutput->Size = System::Drawing::Size(225, 20);
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
      this->btnBrowseLsp->Location = System::Drawing::Point(336, 41);
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
      this->btnBrowseOutput->Location = System::Drawing::Point(336, 70);
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
      this->btnRun->Location = System::Drawing::Point(336, 99);
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
      this->tboxDml->Size = System::Drawing::Size(225, 20);
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
      this->btnBrowseDml->Location = System::Drawing::Point(336, 12);
      this->btnBrowseDml->Name = L"btnBrowseDml";
      this->btnBrowseDml->Size = System::Drawing::Size(75, 23);
      this->btnBrowseDml->TabIndex = 3;
      this->btnBrowseDml->Text = L"Browse";
      this->btnBrowseDml->UseVisualStyleBackColor = true;
      this->btnBrowseDml->Click += gcnew System::EventHandler(this, &LhsForm::OnBrowseDml);
      // 
      // LhsForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(423, 134);
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
      this->MinimumSize = System::Drawing::Size(431, 131);
      this->Name = L"LhsForm";
      this->Text = L"LhsForm";
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  };
}
