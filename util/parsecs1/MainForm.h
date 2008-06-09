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
    System::Void OnBrowseInput(System::Object^  sender, System::EventArgs^  e);
    System::Void OnDragDropInput(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
    System::Void OnDragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);

  private: System::Windows::Forms::Label^  lblInput;
  private: System::Windows::Forms::TextBox^  tboxInput;
  private: System::Windows::Forms::Button^  btnInput;
  private: System::Windows::Forms::Button^  btnParse;

  private: System::Windows::Forms::CheckBox^  chkLocation;
  private: System::Windows::Forms::CheckBox^  chkContainer;
  private: System::Windows::Forms::CheckBox^  chkSurvivals;
  private: System::Windows::Forms::CheckBox^  chkLarvalData;

  private: System::Windows::Forms::GroupBox^  gboxUsage;
  private: System::Windows::Forms::RichTextBox^  rtbUsage1;
  private: System::Windows::Forms::RichTextBox^  rtbUsage3;
  private: System::Windows::Forms::RichTextBox^  rtbUsage2;

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
      System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
      this->lblInput = (gcnew System::Windows::Forms::Label());
      this->tboxInput = (gcnew System::Windows::Forms::TextBox());
      this->btnParse = (gcnew System::Windows::Forms::Button());
      this->btnInput = (gcnew System::Windows::Forms::Button());
      this->chkLocation = (gcnew System::Windows::Forms::CheckBox());
      this->chkContainer = (gcnew System::Windows::Forms::CheckBox());
      this->chkSurvivals = (gcnew System::Windows::Forms::CheckBox());
      this->chkLarvalData = (gcnew System::Windows::Forms::CheckBox());
      this->gboxUsage = (gcnew System::Windows::Forms::GroupBox());
      this->rtbUsage3 = (gcnew System::Windows::Forms::RichTextBox());
      this->rtbUsage2 = (gcnew System::Windows::Forms::RichTextBox());
      this->rtbUsage1 = (gcnew System::Windows::Forms::RichTextBox());
      this->gboxUsage->SuspendLayout();
      this->SuspendLayout();
      // 
      // lblInput
      // 
      this->lblInput->AutoSize = true;
      this->lblInput->Location = System::Drawing::Point(12, 16);
      this->lblInput->Name = L"lblInput";
      this->lblInput->Size = System::Drawing::Size(116, 13);
      this->lblInput->TabIndex = 0;
      this->lblInput->Text = L"Input/Output Directory:";
      // 
      // tboxInput
      // 
      this->tboxInput->AllowDrop = true;
      this->tboxInput->Location = System::Drawing::Point(134, 12);
      this->tboxInput->Name = L"tboxInput";
      this->tboxInput->Size = System::Drawing::Size(544, 20);
      this->tboxInput->TabIndex = 1;
      this->tboxInput->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::OnDragDropInput);
      this->tboxInput->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::OnDragEnter);
      // 
      // btnParse
      // 
      this->btnParse->Location = System::Drawing::Point(633, 38);
      this->btnParse->Name = L"btnParse";
      this->btnParse->Size = System::Drawing::Size(75, 23);
      this->btnParse->TabIndex = 6;
      this->btnParse->Text = L"Parse";
      this->btnParse->UseVisualStyleBackColor = true;
      this->btnParse->Click += gcnew System::EventHandler(this, &MainForm::OnParse);
      // 
      // btnInput
      // 
      this->btnInput->Location = System::Drawing::Point(684, 12);
      this->btnInput->Name = L"btnInput";
      this->btnInput->Size = System::Drawing::Size(24, 20);
      this->btnInput->TabIndex = 2;
      this->btnInput->Text = L"...";
      this->btnInput->UseVisualStyleBackColor = true;
      this->btnInput->Click += gcnew System::EventHandler(this, &MainForm::OnBrowseInput);
      // 
      // chkLocation
      // 
      this->chkLocation->AutoSize = true;
      this->chkLocation->Checked = true;
      this->chkLocation->CheckState = System::Windows::Forms::CheckState::Checked;
      this->chkLocation->Location = System::Drawing::Point(134, 42);
      this->chkLocation->Name = L"chkLocation";
      this->chkLocation->Size = System::Drawing::Size(67, 17);
      this->chkLocation->TabIndex = 7;
      this->chkLocation->Text = L"Location";
      this->chkLocation->UseVisualStyleBackColor = true;
      // 
      // chkContainer
      // 
      this->chkContainer->AutoSize = true;
      this->chkContainer->Checked = true;
      this->chkContainer->CheckState = System::Windows::Forms::CheckState::Checked;
      this->chkContainer->Location = System::Drawing::Point(207, 42);
      this->chkContainer->Name = L"chkContainer";
      this->chkContainer->Size = System::Drawing::Size(71, 17);
      this->chkContainer->TabIndex = 7;
      this->chkContainer->Text = L"Container";
      this->chkContainer->UseVisualStyleBackColor = true;
      // 
      // chkSurvivals
      // 
      this->chkSurvivals->AutoSize = true;
      this->chkSurvivals->Checked = true;
      this->chkSurvivals->CheckState = System::Windows::Forms::CheckState::Checked;
      this->chkSurvivals->Location = System::Drawing::Point(284, 42);
      this->chkSurvivals->Name = L"chkSurvivals";
      this->chkSurvivals->Size = System::Drawing::Size(69, 17);
      this->chkSurvivals->TabIndex = 7;
      this->chkSurvivals->Text = L"Survivals";
      this->chkSurvivals->UseVisualStyleBackColor = true;
      // 
      // chkLarvalData
      // 
      this->chkLarvalData->AutoSize = true;
      this->chkLarvalData->Location = System::Drawing::Point(359, 42);
      this->chkLarvalData->Name = L"chkLarvalData";
      this->chkLarvalData->Size = System::Drawing::Size(81, 17);
      this->chkLarvalData->TabIndex = 7;
      this->chkLarvalData->Text = L"Larval Data";
      this->chkLarvalData->UseVisualStyleBackColor = true;
      // 
      // gboxUsage
      // 
      this->gboxUsage->Controls->Add(this->rtbUsage3);
      this->gboxUsage->Controls->Add(this->rtbUsage2);
      this->gboxUsage->Controls->Add(this->rtbUsage1);
      this->gboxUsage->Location = System::Drawing::Point(12, 65);
      this->gboxUsage->Name = L"gboxUsage";
      this->gboxUsage->Size = System::Drawing::Size(696, 401);
      this->gboxUsage->TabIndex = 9;
      this->gboxUsage->TabStop = false;
      this->gboxUsage->Text = L"Usage";
      // 
      // rtbUsage3
      // 
      this->rtbUsage3->BackColor = System::Drawing::SystemColors::Control;
      this->rtbUsage3->BorderStyle = System::Windows::Forms::BorderStyle::None;
      this->rtbUsage3->Location = System::Drawing::Point(331, 156);
      this->rtbUsage3->Name = L"rtbUsage3";
      this->rtbUsage3->Size = System::Drawing::Size(359, 241);
      this->rtbUsage3->TabIndex = 1;
      this->rtbUsage3->Text = resources->GetString(L"rtbUsage3.Text");
      // 
      // rtbUsage2
      // 
      this->rtbUsage2->BackColor = System::Drawing::SystemColors::Control;
      this->rtbUsage2->BorderStyle = System::Windows::Forms::BorderStyle::None;
      this->rtbUsage2->Location = System::Drawing::Point(6, 156);
      this->rtbUsage2->Name = L"rtbUsage2";
      this->rtbUsage2->Size = System::Drawing::Size(319, 241);
      this->rtbUsage2->TabIndex = 1;
      this->rtbUsage2->Text = resources->GetString(L"rtbUsage2.Text");
      // 
      // rtbUsage1
      // 
      this->rtbUsage1->BackColor = System::Drawing::SystemColors::Control;
      this->rtbUsage1->BorderStyle = System::Windows::Forms::BorderStyle::None;
      this->rtbUsage1->Location = System::Drawing::Point(6, 19);
      this->rtbUsage1->Name = L"rtbUsage1";
      this->rtbUsage1->Size = System::Drawing::Size(684, 131);
      this->rtbUsage1->TabIndex = 0;
      this->rtbUsage1->Text = resources->GetString(L"rtbUsage1.Text");
      // 
      // MainForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(720, 477);
      this->Controls->Add(this->chkLocation);
      this->Controls->Add(this->chkLarvalData);
      this->Controls->Add(this->gboxUsage);
      this->Controls->Add(this->chkContainer);
      this->Controls->Add(this->btnInput);
      this->Controls->Add(this->btnParse);
      this->Controls->Add(this->chkSurvivals);
      this->Controls->Add(this->tboxInput);
      this->Controls->Add(this->lblInput);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
      this->Name = L"MainForm";
      this->Text = L"CIMSiM 1.0 Output Parser";
      this->gboxUsage->ResumeLayout(false);
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  };
}
