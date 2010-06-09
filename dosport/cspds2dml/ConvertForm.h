#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace cspds2dml {

	/// <summary>
	/// Summary for ConvertForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class ConvertForm : public System::Windows::Forms::Form
	{
	public:
		ConvertForm(void);
	protected:
		~ConvertForm();

  private:
    System::Void OnConvert(System::Object^  sender, System::EventArgs^  e);
    System::Void OnBrowse(System::Object^  sender, System::EventArgs^  e);
    System::Void OnDragDropInput(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
    System::Void OnDragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);

  private: System::Windows::Forms::Label^  lblInput;
  private: System::Windows::Forms::TextBox^  tboxInput;
  private: System::Windows::Forms::Button^  btnInput;
  private: System::Windows::Forms::Button^  btnConvert;

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
      this->btnInput = (gcnew System::Windows::Forms::Button());
      this->btnConvert = (gcnew System::Windows::Forms::Button());
      this->tboxInput = (gcnew System::Windows::Forms::TextBox());
      this->lblInput = (gcnew System::Windows::Forms::Label());
      this->SuspendLayout();
      // 
      // lblInput
      // 
      this->lblInput->AutoSize = true;
      this->lblInput->Location = System::Drawing::Point(12, 15);
      this->lblInput->Name = L"lblInput";
      this->lblInput->Size = System::Drawing::Size(51, 13);
      this->lblInput->TabIndex = 7;
      this->lblInput->Text = L"PDS File:";
      // 
      // tboxInput
      // 
      this->tboxInput->AllowDrop = true;
      this->tboxInput->Location = System::Drawing::Point(69, 12);
      this->tboxInput->Name = L"tboxInput";
      this->tboxInput->Size = System::Drawing::Size(529, 20);
      this->tboxInput->TabIndex = 8;
      this->tboxInput->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &ConvertForm::OnDragDropInput);
      this->tboxInput->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &ConvertForm::OnDragEnter);
      // 
      // btnInput
      // 
      this->btnInput->Location = System::Drawing::Point(604, 12);
      this->btnInput->Name = L"btnInput";
      this->btnInput->Size = System::Drawing::Size(24, 20);
      this->btnInput->TabIndex = 9;
      this->btnInput->Text = L"...";
      this->btnInput->UseVisualStyleBackColor = true;
      this->btnInput->Click += gcnew System::EventHandler(this, &ConvertForm::OnBrowse);
      // 
      // btnConvert
      // 
      this->btnConvert->Location = System::Drawing::Point(553, 38);
      this->btnConvert->Name = L"btnConvert";
      this->btnConvert->Size = System::Drawing::Size(75, 23);
      this->btnConvert->TabIndex = 10;
      this->btnConvert->Text = L"Convert";
      this->btnConvert->UseVisualStyleBackColor = true;
      this->btnConvert->Click += gcnew System::EventHandler(this, &ConvertForm::OnConvert);
      // 
      // ConvertForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(640, 73);
      this->Controls->Add(this->lblInput);
      this->Controls->Add(this->tboxInput);
      this->Controls->Add(this->btnInput);
      this->Controls->Add(this->btnConvert);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
      this->Name = L"ConvertForm";
      this->Text = L"Convert .pds (CIMSIM) to .dml";
      this->ResumeLayout(false);
      this->PerformLayout();
    }
#pragma endregion
  };
}
