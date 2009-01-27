#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace xml2xls {

	public ref class InputForm : public System::Windows::Forms::Form
	{
	public:
		InputForm(void);
	protected:
		virtual ~InputForm(void);

  private:
    System::Void OnBrowse(System::Object^  sender, System::EventArgs^  e);
    System::Void OnClear(System::Object^  sender, System::EventArgs^  e);
    System::Void OnConvert(System::Object^  sender, System::EventArgs^  e);
    System::Void OnDragDropInput(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
    System::Void OnDragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);

  private: System::Windows::Forms::RichTextBox^  richTextBox1;
  private: System::Windows::Forms::Button^  btnBrowse;
  private: System::Windows::Forms::Button^  btnConvert;
  private: System::Windows::Forms::ListView^  lvFiles;

  private: System::Windows::Forms::ColumnHeader^  columnHeader1;
  private: System::Windows::Forms::ColumnHeader^  columnHeader2;
  private: System::Windows::Forms::Button^  btnClear;
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
      System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(InputForm::typeid));
      this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
      this->btnBrowse = (gcnew System::Windows::Forms::Button());
      this->btnConvert = (gcnew System::Windows::Forms::Button());
      this->lvFiles = (gcnew System::Windows::Forms::ListView());
      this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
      this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
      this->btnClear = (gcnew System::Windows::Forms::Button());
      this->SuspendLayout();
      // 
      // richTextBox1
      // 
      this->richTextBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->richTextBox1->Location = System::Drawing::Point(12, 12);
      this->richTextBox1->Name = L"richTextBox1";
      this->richTextBox1->ReadOnly = true;
      this->richTextBox1->Size = System::Drawing::Size(368, 52);
      this->richTextBox1->TabIndex = 0;
      this->richTextBox1->Text = resources->GetString(L"richTextBox1.Text");
      // 
      // btnBrowse
      // 
      this->btnBrowse->Location = System::Drawing::Point(12, 70);
      this->btnBrowse->Name = L"btnBrowse";
      this->btnBrowse->Size = System::Drawing::Size(75, 23);
      this->btnBrowse->TabIndex = 1;
      this->btnBrowse->Text = L"Browse";
      this->btnBrowse->UseVisualStyleBackColor = true;
      this->btnBrowse->Click += gcnew System::EventHandler(this, &InputForm::OnBrowse);
      // 
      // btnConvert
      // 
      this->btnConvert->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
      this->btnConvert->Location = System::Drawing::Point(12, 346);
      this->btnConvert->Name = L"btnConvert";
      this->btnConvert->Size = System::Drawing::Size(75, 23);
      this->btnConvert->TabIndex = 1;
      this->btnConvert->Text = L"Convert";
      this->btnConvert->UseVisualStyleBackColor = true;
      this->btnConvert->Click += gcnew System::EventHandler(this, &InputForm::OnConvert);
      // 
      // lvFiles
      // 
      this->lvFiles->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->lvFiles->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->columnHeader1, this->columnHeader2});
      this->lvFiles->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
      this->lvFiles->Location = System::Drawing::Point(12, 99);
      this->lvFiles->Name = L"lvFiles";
      this->lvFiles->Size = System::Drawing::Size(368, 241);
      this->lvFiles->TabIndex = 2;
      this->lvFiles->UseCompatibleStateImageBehavior = false;
      this->lvFiles->View = System::Windows::Forms::View::Details;
      // 
      // columnHeader1
      // 
      this->columnHeader1->Text = L"Filename";
      this->columnHeader1->Width = 274;
      // 
      // columnHeader2
      // 
      this->columnHeader2->Text = L"Result";
      this->columnHeader2->Width = 80;
      // 
      // btnClear
      // 
      this->btnClear->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->btnClear->Location = System::Drawing::Point(305, 70);
      this->btnClear->Name = L"btnClear";
      this->btnClear->Size = System::Drawing::Size(75, 23);
      this->btnClear->TabIndex = 1;
      this->btnClear->Text = L"Clear";
      this->btnClear->UseVisualStyleBackColor = true;
      this->btnClear->Click += gcnew System::EventHandler(this, &InputForm::OnClear);
      // 
      // InputForm
      // 
      this->AllowDrop = true;
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(392, 381);
      this->Controls->Add(this->lvFiles);
      this->Controls->Add(this->btnConvert);
      this->Controls->Add(this->btnClear);
      this->Controls->Add(this->btnBrowse);
      this->Controls->Add(this->richTextBox1);
      this->MinimumSize = System::Drawing::Size(400, 240);
      this->Name = L"InputForm";
      this->Text = L"xml2xls 0.1";
      this->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &InputForm::OnDragDropInput);
      this->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &InputForm::OnDragEnter);
      this->ResumeLayout(false);

    }
#pragma endregion
  };
}
