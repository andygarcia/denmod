#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace parsecs1 {

	/// <summary>
	/// Summary for HelpForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class HelpForm : public System::Windows::Forms::Form
	{
	public:
		HelpForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~HelpForm()
		{
			if (components)
			{
				delete components;
			}
		}
  private: System::Windows::Forms::GroupBox^  gboxUsage;
  protected: 
  private: System::Windows::Forms::RichTextBox^  rtbUsage3;
  private: System::Windows::Forms::RichTextBox^  rtbUsage2;
  private: System::Windows::Forms::RichTextBox^  rtbUsage1;
  private: System::Windows::Forms::Button^  btnClose;


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
      this->rtbUsage3 = (gcnew System::Windows::Forms::RichTextBox());
      this->rtbUsage2 = (gcnew System::Windows::Forms::RichTextBox());
      this->rtbUsage1 = (gcnew System::Windows::Forms::RichTextBox());
      this->btnClose = (gcnew System::Windows::Forms::Button());
      this->gboxUsage->SuspendLayout();
      this->SuspendLayout();
      // 
      // gboxUsage
      // 
      this->gboxUsage->Controls->Add(this->rtbUsage3);
      this->gboxUsage->Controls->Add(this->rtbUsage2);
      this->gboxUsage->Controls->Add(this->rtbUsage1);
      this->gboxUsage->Location = System::Drawing::Point(12, 12);
      this->gboxUsage->Name = L"gboxUsage";
      this->gboxUsage->Size = System::Drawing::Size(712, 420);
      this->gboxUsage->TabIndex = 10;
      this->gboxUsage->TabStop = false;
      this->gboxUsage->Text = L"Usage";
      // 
      // rtbUsage3
      // 
      this->rtbUsage3->BackColor = System::Drawing::SystemColors::Control;
      this->rtbUsage3->BorderStyle = System::Windows::Forms::BorderStyle::None;
      this->rtbUsage3->Location = System::Drawing::Point(331, 156);
      this->rtbUsage3->Name = L"rtbUsage3";
      this->rtbUsage3->Size = System::Drawing::Size(359, 258);
      this->rtbUsage3->TabIndex = 1;
      this->rtbUsage3->Text = resources->GetString(L"rtbUsage3.Text");
      // 
      // rtbUsage2
      // 
      this->rtbUsage2->BackColor = System::Drawing::SystemColors::Control;
      this->rtbUsage2->BorderStyle = System::Windows::Forms::BorderStyle::None;
      this->rtbUsage2->Location = System::Drawing::Point(6, 156);
      this->rtbUsage2->Name = L"rtbUsage2";
      this->rtbUsage2->Size = System::Drawing::Size(319, 258);
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
      // btnClose
      // 
      this->btnClose->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->btnClose->Location = System::Drawing::Point(644, 438);
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
      this->ClientSize = System::Drawing::Size(731, 473);
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
      this->ResumeLayout(false);

    }
#pragma endregion
	};
}
