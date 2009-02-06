#pragma once

#include "CimsimParser.h"


namespace parsecs1 {

	using namespace System;
  using namespace System::Xml;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;
  using namespace System::IO;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void);
	protected:
		~MainForm();

  private:
    System::Void OnParse(System::Object^  sender, System::EventArgs^  e);
    System::Void OnHelp( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnBrowseInput(System::Object^  sender, System::EventArgs^  e);
    System::Void OnDragDropInput(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
    System::Void OnDragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);


  private: System::Windows::Forms::TextBox^  tboxInput;
  private: System::Windows::Forms::Button^  btnInput;
  private: System::Windows::Forms::Button^  btnParse;





  private: System::Windows::Forms::Button^  btnHelp;
  private: System::Windows::Forms::CheckBox^  cboxXml;
  private: System::Windows::Forms::CheckBox^  cboxTxt;


  private: System::Windows::Forms::GroupBox^  gboxOutput;
  private: System::Windows::Forms::GroupBox^  gboxInput;






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
      this->tboxInput = (gcnew System::Windows::Forms::TextBox());
      this->btnParse = (gcnew System::Windows::Forms::Button());
      this->btnInput = (gcnew System::Windows::Forms::Button());
      this->btnHelp = (gcnew System::Windows::Forms::Button());
      this->cboxXml = (gcnew System::Windows::Forms::CheckBox());
      this->cboxTxt = (gcnew System::Windows::Forms::CheckBox());
      this->gboxOutput = (gcnew System::Windows::Forms::GroupBox());
      this->gboxInput = (gcnew System::Windows::Forms::GroupBox());
      this->gboxOutput->SuspendLayout();
      this->gboxInput->SuspendLayout();
      this->SuspendLayout();
      // 
      // tboxInput
      // 
      this->tboxInput->AllowDrop = true;
      this->tboxInput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->tboxInput->Location = System::Drawing::Point(6, 19);
      this->tboxInput->Name = L"tboxInput";
      this->tboxInput->Size = System::Drawing::Size(410, 20);
      this->tboxInput->TabIndex = 1;
      this->tboxInput->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::OnDragDropInput);
      this->tboxInput->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::OnDragEnter);
      // 
      // btnParse
      // 
      this->btnParse->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnParse->Location = System::Drawing::Point(389, 145);
      this->btnParse->Name = L"btnParse";
      this->btnParse->Size = System::Drawing::Size(75, 23);
      this->btnParse->TabIndex = 6;
      this->btnParse->Text = L"Parse";
      this->btnParse->UseVisualStyleBackColor = true;
      this->btnParse->Click += gcnew System::EventHandler(this, &MainForm::OnParse);
      // 
      // btnInput
      // 
      this->btnInput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->btnInput->Location = System::Drawing::Point(422, 19);
      this->btnInput->Name = L"btnInput";
      this->btnInput->Size = System::Drawing::Size(24, 20);
      this->btnInput->TabIndex = 2;
      this->btnInput->Text = L"...";
      this->btnInput->UseVisualStyleBackColor = true;
      this->btnInput->Click += gcnew System::EventHandler(this, &MainForm::OnBrowseInput);
      // 
      // btnHelp
      // 
      this->btnHelp->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnHelp->Location = System::Drawing::Point(12, 145);
      this->btnHelp->Name = L"btnHelp";
      this->btnHelp->Size = System::Drawing::Size(75, 23);
      this->btnHelp->TabIndex = 6;
      this->btnHelp->Text = L"Help";
      this->btnHelp->UseVisualStyleBackColor = true;
      this->btnHelp->Click += gcnew System::EventHandler(this, &MainForm::OnHelp);
      // 
      // cboxXml
      // 
      this->cboxXml->AutoSize = true;
      this->cboxXml->Location = System::Drawing::Point(6, 19);
      this->cboxXml->Name = L"cboxXml";
      this->cboxXml->Size = System::Drawing::Size(139, 17);
      this->cboxXml->TabIndex = 7;
      this->cboxXml->Text = L"Excel Spreadsheet (xml)";
      this->cboxXml->UseVisualStyleBackColor = true;
      // 
      // cboxTxt
      // 
      this->cboxTxt->AutoSize = true;
      this->cboxTxt->Location = System::Drawing::Point(6, 42);
      this->cboxTxt->Name = L"cboxTxt";
      this->cboxTxt->Size = System::Drawing::Size(96, 17);
      this->cboxTxt->TabIndex = 7;
      this->cboxTxt->Text = L"Plain Text (.txt)";
      this->cboxTxt->UseVisualStyleBackColor = true;
      // 
      // gboxOutput
      // 
      this->gboxOutput->Controls->Add(this->cboxXml);
      this->gboxOutput->Controls->Add(this->cboxTxt);
      this->gboxOutput->Location = System::Drawing::Point(12, 68);
      this->gboxOutput->Name = L"gboxOutput";
      this->gboxOutput->Size = System::Drawing::Size(452, 68);
      this->gboxOutput->TabIndex = 8;
      this->gboxOutput->TabStop = false;
      this->gboxOutput->Text = L"Output Formats:";
      // 
      // gboxInput
      // 
      this->gboxInput->Controls->Add(this->tboxInput);
      this->gboxInput->Controls->Add(this->btnInput);
      this->gboxInput->Location = System::Drawing::Point(12, 12);
      this->gboxInput->Name = L"gboxInput";
      this->gboxInput->Size = System::Drawing::Size(452, 50);
      this->gboxInput->TabIndex = 8;
      this->gboxInput->TabStop = false;
      this->gboxInput->Text = L"Input Directory";
      // 
      // MainForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(476, 178);
      this->Controls->Add(this->gboxInput);
      this->Controls->Add(this->gboxOutput);
      this->Controls->Add(this->btnHelp);
      this->Controls->Add(this->btnParse);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
      this->Name = L"MainForm";
      this->Text = L"CIMSiM 1.0 Output Parser";
      this->gboxOutput->ResumeLayout(false);
      this->gboxOutput->PerformLayout();
      this->gboxInput->ResumeLayout(false);
      this->gboxInput->PerformLayout();
      this->ResumeLayout(false);

    }
#pragma endregion
  };
}
