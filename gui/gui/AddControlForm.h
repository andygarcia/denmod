#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace gui {

	public ref class AddControlForm : public System::Windows::Forms::Form
	{
	public:
		AddControlForm(void);
	protected:
		~AddControlForm();

  private:
    System::Collections::Generic::Dictionary<System::String^,System::Type^> ^ ControlMap;

  public:
    System::Type ^ GetNewControlType(void);

  private:
    System::Void OnAdd( System::Object ^ sender, System::EventArgs ^ e );

  private: System::Windows::Forms::ListBox^  lboxControlTypes;
  private: System::Windows::Forms::Button^  btnCancel;
  private: System::Windows::Forms::Button^  btnAdd;

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
      this->lboxControlTypes = (gcnew System::Windows::Forms::ListBox());
      this->btnCancel = (gcnew System::Windows::Forms::Button());
      this->btnAdd = (gcnew System::Windows::Forms::Button());
      this->SuspendLayout();
      // 
      // lboxControlTypes
      // 
      this->lboxControlTypes->FormattingEnabled = true;
      this->lboxControlTypes->Location = System::Drawing::Point(12, 12);
      this->lboxControlTypes->Name = L"lboxControlTypes";
      this->lboxControlTypes->Size = System::Drawing::Size(156, 173);
      this->lboxControlTypes->TabIndex = 0;
      this->lboxControlTypes->DoubleClick += gcnew System::EventHandler(this, &AddControlForm::OnAdd);
      // 
      // btnCancel
      // 
      this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
      this->btnCancel->Location = System::Drawing::Point(93, 191);
      this->btnCancel->Name = L"btnCancel";
      this->btnCancel->Size = System::Drawing::Size(75, 23);
      this->btnCancel->TabIndex = 2;
      this->btnCancel->Text = L"Cancel";
      this->btnCancel->UseVisualStyleBackColor = true;
      // 
      // btnAdd
      // 
      this->btnAdd->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->btnAdd->Location = System::Drawing::Point(12, 191);
      this->btnAdd->Name = L"btnAdd";
      this->btnAdd->Size = System::Drawing::Size(75, 23);
      this->btnAdd->TabIndex = 1;
      this->btnAdd->Text = L"Add";
      this->btnAdd->UseVisualStyleBackColor = true;
      this->btnAdd->Click += gcnew System::EventHandler(this, &AddControlForm::OnAdd);
      // 
      // AddControlForm
      // 
      this->AcceptButton = this->btnAdd;
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->CancelButton = this->btnCancel;
      this->ClientSize = System::Drawing::Size(180, 226);
      this->Controls->Add(this->btnAdd);
      this->Controls->Add(this->btnCancel);
      this->Controls->Add(this->lboxControlTypes);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
      this->Name = L"AddControlForm";
      this->ShowInTaskbar = false;
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
      this->Text = L"Add Control";
      this->ResumeLayout(false);

    }
#pragma endregion
  };
}
