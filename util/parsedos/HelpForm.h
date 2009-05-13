#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace parsedos {

	public ref class HelpForm : public System::Windows::Forms::Form
	{
	public:
		HelpForm(void);
	protected:
		~HelpForm();

  private: System::Windows::Forms::GroupBox^  gboxUsage;
  private: System::Windows::Forms::RichTextBox^  rtbUsage3;
  private: System::Windows::Forms::RichTextBox^  rtbUsage2;
  private: System::Windows::Forms::RichTextBox^  rtbUsage1;
  private: System::Windows::Forms::Button^  btnClose;
  private: System::Windows::Forms::TabControl^  tabControl1;
  private: System::Windows::Forms::TabPage^  tabPageCimsim;
  private: System::Windows::Forms::TabPage^  tabPageDensim;
  private: System::Windows::Forms::RichTextBox^  rtbUsage4;


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
      System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(HelpForm::typeid));
      this->gboxUsage = (gcnew System::Windows::Forms::GroupBox());
      this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
      this->tabPageCimsim = (gcnew System::Windows::Forms::TabPage());
      this->rtbUsage3 = (gcnew System::Windows::Forms::RichTextBox());
      this->rtbUsage2 = (gcnew System::Windows::Forms::RichTextBox());
      this->tabPageDensim = (gcnew System::Windows::Forms::TabPage());
      this->rtbUsage4 = (gcnew System::Windows::Forms::RichTextBox());
      this->rtbUsage1 = (gcnew System::Windows::Forms::RichTextBox());
      this->btnClose = (gcnew System::Windows::Forms::Button());
      this->gboxUsage->SuspendLayout();
      this->tabControl1->SuspendLayout();
      this->tabPageCimsim->SuspendLayout();
      this->tabPageDensim->SuspendLayout();
      this->SuspendLayout();
      // 
      // gboxUsage
      // 
      this->gboxUsage->Controls->Add(this->tabControl1);
      this->gboxUsage->Controls->Add(this->rtbUsage1);
      this->gboxUsage->Location = System::Drawing::Point(12, 12);
      this->gboxUsage->Name = L"gboxUsage";
      this->gboxUsage->Size = System::Drawing::Size(712, 449);
      this->gboxUsage->TabIndex = 10;
      this->gboxUsage->TabStop = false;
      this->gboxUsage->Text = L"Usage";
      // 
      // tabControl1
      // 
      this->tabControl1->Controls->Add(this->tabPageCimsim);
      this->tabControl1->Controls->Add(this->tabPageDensim);
      this->tabControl1->Location = System::Drawing::Point(6, 144);
      this->tabControl1->Name = L"tabControl1";
      this->tabControl1->SelectedIndex = 0;
      this->tabControl1->Size = System::Drawing::Size(700, 299);
      this->tabControl1->TabIndex = 1;
      // 
      // tabPageCimsim
      // 
      this->tabPageCimsim->BackColor = System::Drawing::Color::Transparent;
      this->tabPageCimsim->Controls->Add(this->rtbUsage3);
      this->tabPageCimsim->Controls->Add(this->rtbUsage2);
      this->tabPageCimsim->Location = System::Drawing::Point(4, 22);
      this->tabPageCimsim->Name = L"tabPageCimsim";
      this->tabPageCimsim->Padding = System::Windows::Forms::Padding(3);
      this->tabPageCimsim->Size = System::Drawing::Size(692, 273);
      this->tabPageCimsim->TabIndex = 0;
      this->tabPageCimsim->Text = L"CS 1.0";
      this->tabPageCimsim->UseVisualStyleBackColor = true;
      // 
      // rtbUsage3
      // 
      this->rtbUsage3->BackColor = System::Drawing::SystemColors::Control;
      this->rtbUsage3->BorderStyle = System::Windows::Forms::BorderStyle::None;
      this->rtbUsage3->Location = System::Drawing::Point(331, 6);
      this->rtbUsage3->Name = L"rtbUsage3";
      this->rtbUsage3->Size = System::Drawing::Size(355, 258);
      this->rtbUsage3->TabIndex = 1;
      this->rtbUsage3->Text = resources->GetString(L"rtbUsage3.Text");
      // 
      // rtbUsage2
      // 
      this->rtbUsage2->BackColor = System::Drawing::SystemColors::Control;
      this->rtbUsage2->BorderStyle = System::Windows::Forms::BorderStyle::None;
      this->rtbUsage2->Location = System::Drawing::Point(6, 6);
      this->rtbUsage2->Name = L"rtbUsage2";
      this->rtbUsage2->Size = System::Drawing::Size(319, 258);
      this->rtbUsage2->TabIndex = 1;
      this->rtbUsage2->Text = resources->GetString(L"rtbUsage2.Text");
      // 
      // tabPageDensim
      // 
      this->tabPageDensim->BackColor = System::Drawing::Color::Transparent;
      this->tabPageDensim->Controls->Add(this->rtbUsage4);
      this->tabPageDensim->Location = System::Drawing::Point(4, 22);
      this->tabPageDensim->Name = L"tabPageDensim";
      this->tabPageDensim->Padding = System::Windows::Forms::Padding(3);
      this->tabPageDensim->Size = System::Drawing::Size(692, 273);
      this->tabPageDensim->TabIndex = 1;
      this->tabPageDensim->Text = L"DS 1.0";
      this->tabPageDensim->UseVisualStyleBackColor = true;
      // 
      // rtbUsage4
      // 
      this->rtbUsage4->BackColor = System::Drawing::SystemColors::Control;
      this->rtbUsage4->BorderStyle = System::Windows::Forms::BorderStyle::None;
      this->rtbUsage4->Location = System::Drawing::Point(6, 6);
      this->rtbUsage4->Name = L"rtbUsage4";
      this->rtbUsage4->Size = System::Drawing::Size(680, 258);
      this->rtbUsage4->TabIndex = 2;
      this->rtbUsage4->Text = resources->GetString(L"rtbUsage4.Text");
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
      // btnClose
      // 
      this->btnClose->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->btnClose->Location = System::Drawing::Point(649, 467);
      this->btnClose->Name = L"btnClose";
      this->btnClose->Size = System::Drawing::Size(75, 23);
      this->btnClose->TabIndex = 11;
      this->btnClose->Text = L"Close";
      this->btnClose->UseVisualStyleBackColor = true;
      // 
      // HelpForm
      // 
      this->AcceptButton = this->btnClose;
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->CancelButton = this->btnClose;
      this->ClientSize = System::Drawing::Size(736, 502);
      this->Controls->Add(this->btnClose);
      this->Controls->Add(this->gboxUsage);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
      this->MaximizeBox = false;
      this->MinimizeBox = false;
      this->Name = L"HelpForm";
      this->ShowIcon = false;
      this->ShowInTaskbar = false;
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
      this->Text = L"HelpForm";
      this->gboxUsage->ResumeLayout(false);
      this->tabControl1->ResumeLayout(false);
      this->tabPageCimsim->ResumeLayout(false);
      this->tabPageDensim->ResumeLayout(false);
      this->ResumeLayout(false);

    }
#pragma endregion
	};
}
