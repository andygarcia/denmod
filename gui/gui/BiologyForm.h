#pragma once

#include "EggBiologyPanel.h"
#include "LarvaeBiologyPanel.h"
#include "PupaeBiologyPanel.h"
#include "AdultBiologyPanel.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace gui {


  public ref class BiologyForm : public System::Windows::Forms::Form
	{
	public:
		BiologyForm( BindingSource ^ locationBinding );
	protected:
		~BiologyForm(void);

  private:
    System::Void OnDefault( System::Object ^ sender, System::EventArgs ^ e );

  private:
    BindingSource ^ LocationBinding;

    EggBiologyPanel ^ EggBiologyPanel_;
    LarvaeBiologyPanel ^ LarvaeBiologyPanel_ ;
    PupaeBiologyPanel ^ PupaeBiologyPanel_;
    AdultBiologyPanel ^ AdultBiologyPanel_;

  private: System::Windows::Forms::TabControl^  tabControl1;
  private: System::Windows::Forms::TabPage^  tabPageEgg;
  private: System::Windows::Forms::TabPage^  tabPageLarvae;
  private: System::Windows::Forms::TabPage^  tabPagePupae;
  private: System::Windows::Forms::TabPage^  tabPageAdult;
  private: System::Windows::Forms::Button^  btnOk;
  private: System::Windows::Forms::Button^  btnDefault;
  private: System::Windows::Forms::Button^  btnCancel;


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
      this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
      this->tabPageEgg = (gcnew System::Windows::Forms::TabPage());
      this->tabPageLarvae = (gcnew System::Windows::Forms::TabPage());
      this->tabPagePupae = (gcnew System::Windows::Forms::TabPage());
      this->tabPageAdult = (gcnew System::Windows::Forms::TabPage());
      this->btnOk = (gcnew System::Windows::Forms::Button());
      this->btnDefault = (gcnew System::Windows::Forms::Button());
      this->btnCancel = (gcnew System::Windows::Forms::Button());
      this->tabControl1->SuspendLayout();
      this->SuspendLayout();
      // 
      // tabControl1
      // 
      this->tabControl1->Controls->Add(this->tabPageEgg);
      this->tabControl1->Controls->Add(this->tabPageLarvae);
      this->tabControl1->Controls->Add(this->tabPagePupae);
      this->tabControl1->Controls->Add(this->tabPageAdult);
      this->tabControl1->Location = System::Drawing::Point(12, 12);
      this->tabControl1->Name = L"tabControl1";
      this->tabControl1->SelectedIndex = 0;
      this->tabControl1->Size = System::Drawing::Size(406, 445);
      this->tabControl1->TabIndex = 0;
      // 
      // tabPageEgg
      // 
      this->tabPageEgg->AutoScroll = true;
      this->tabPageEgg->Location = System::Drawing::Point(4, 24);
      this->tabPageEgg->Name = L"tabPageEgg";
      this->tabPageEgg->Padding = System::Windows::Forms::Padding(3);
      this->tabPageEgg->Size = System::Drawing::Size(398, 417);
      this->tabPageEgg->TabIndex = 0;
      this->tabPageEgg->Text = L"Eggs";
      this->tabPageEgg->UseVisualStyleBackColor = true;
      // 
      // tabPageLarvae
      // 
      this->tabPageLarvae->AutoScroll = true;
      this->tabPageLarvae->Location = System::Drawing::Point(4, 24);
      this->tabPageLarvae->Name = L"tabPageLarvae";
      this->tabPageLarvae->Padding = System::Windows::Forms::Padding(3);
      this->tabPageLarvae->Size = System::Drawing::Size(398, 417);
      this->tabPageLarvae->TabIndex = 1;
      this->tabPageLarvae->Text = L"Larvae";
      this->tabPageLarvae->UseVisualStyleBackColor = true;
      // 
      // tabPagePupae
      // 
      this->tabPagePupae->AutoScroll = true;
      this->tabPagePupae->Location = System::Drawing::Point(4, 24);
      this->tabPagePupae->Name = L"tabPagePupae";
      this->tabPagePupae->Size = System::Drawing::Size(398, 417);
      this->tabPagePupae->TabIndex = 2;
      this->tabPagePupae->Text = L"Pupae";
      this->tabPagePupae->UseVisualStyleBackColor = true;
      // 
      // tabPageAdult
      // 
      this->tabPageAdult->AutoScroll = true;
      this->tabPageAdult->Location = System::Drawing::Point(4, 24);
      this->tabPageAdult->Name = L"tabPageAdult";
      this->tabPageAdult->Size = System::Drawing::Size(398, 417);
      this->tabPageAdult->TabIndex = 3;
      this->tabPageAdult->Text = L"Adults";
      this->tabPageAdult->UseVisualStyleBackColor = true;
      // 
      // btnOk
      // 
      this->btnOk->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->btnOk->Location = System::Drawing::Point(262, 463);
      this->btnOk->Name = L"btnOk";
      this->btnOk->Size = System::Drawing::Size(75, 23);
      this->btnOk->TabIndex = 1;
      this->btnOk->Text = L"OK";
      this->btnOk->UseVisualStyleBackColor = true;
      // 
      // btnDefault
      // 
      this->btnDefault->Location = System::Drawing::Point(12, 463);
      this->btnDefault->Name = L"btnDefault";
      this->btnDefault->Size = System::Drawing::Size(100, 23);
      this->btnDefault->TabIndex = 1;
      this->btnDefault->Text = L"Load Defaults";
      this->btnDefault->UseVisualStyleBackColor = true;
      this->btnDefault->Click += gcnew System::EventHandler(this, &BiologyForm::OnDefault);
      // 
      // btnCancel
      // 
      this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
      this->btnCancel->Location = System::Drawing::Point(343, 463);
      this->btnCancel->Name = L"btnCancel";
      this->btnCancel->Size = System::Drawing::Size(75, 23);
      this->btnCancel->TabIndex = 2;
      this->btnCancel->Text = L"Cancel";
      this->btnCancel->UseVisualStyleBackColor = true;
      // 
      // BiologyForm
      // 
      this->AcceptButton = this->btnOk;
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->CancelButton = this->btnCancel;
      this->ClientSize = System::Drawing::Size(430, 498);
      this->Controls->Add(this->btnCancel);
      this->Controls->Add(this->btnDefault);
      this->Controls->Add(this->btnOk);
      this->Controls->Add(this->tabControl1);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
      this->Name = L"BiologyForm";
      this->ShowInTaskbar = false;
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
      this->Text = L"BiologyForm";
      this->tabControl1->ResumeLayout(false);
      this->ResumeLayout(false);

    }
#pragma endregion
  };
}
