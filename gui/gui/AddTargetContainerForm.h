#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace gui {

	public ref class AddTargetContainerForm : public System::Windows::Forms::Form
	{
	public:
		AddTargetContainerForm( BindingList<String^> ^ containers );
  protected:
		virtual ~AddTargetContainerForm(void);

  public:
    array<String^> ^ GetContainers(void);

  private:
    System::Void OnLoad(System::Object^  sender, System::EventArgs^  e);

  private:
    BindingList<String^> ^ Containers_;
  private: System::Windows::Forms::Button^  btnOK;
  private: System::Windows::Forms::Button^  btnCancel;
  private: System::Windows::Forms::ListBox^  lboxContainers;

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
      this->btnOK = (gcnew System::Windows::Forms::Button());
      this->btnCancel = (gcnew System::Windows::Forms::Button());
      this->lboxContainers = (gcnew System::Windows::Forms::ListBox());
      this->SuspendLayout();
      // 
      // btnOK
      // 
      this->btnOK->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->btnOK->Location = System::Drawing::Point(12, 178);
      this->btnOK->Name = L"btnOK";
      this->btnOK->Size = System::Drawing::Size(75, 23);
      this->btnOK->TabIndex = 1;
      this->btnOK->Text = L"OK";
      this->btnOK->UseVisualStyleBackColor = true;
      // 
      // btnCancel
      // 
      this->btnCancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
      this->btnCancel->Location = System::Drawing::Point(93, 178);
      this->btnCancel->Name = L"btnCancel";
      this->btnCancel->Size = System::Drawing::Size(75, 23);
      this->btnCancel->TabIndex = 2;
      this->btnCancel->Text = L"Cancel";
      this->btnCancel->UseVisualStyleBackColor = true;
      // 
      // lboxContainers
      // 
      this->lboxContainers->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->lboxContainers->FormattingEnabled = true;
      this->lboxContainers->Location = System::Drawing::Point(12, 12);
      this->lboxContainers->Name = L"lboxContainers";
      this->lboxContainers->SelectionMode = System::Windows::Forms::SelectionMode::MultiExtended;
      this->lboxContainers->Size = System::Drawing::Size(156, 160);
      this->lboxContainers->TabIndex = 0;
      // 
      // AddTargetContainerForm
      // 
      this->AcceptButton = this->btnOK;
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->CancelButton = this->btnCancel;
      this->ClientSize = System::Drawing::Size(180, 213);
      this->Controls->Add(this->lboxContainers);
      this->Controls->Add(this->btnCancel);
      this->Controls->Add(this->btnOK);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
      this->MinimumSize = System::Drawing::Size(186, 238);
      this->Name = L"AddTargetContainerForm";
      this->ShowInTaskbar = false;
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
      this->Text = L"Select Container";
      this->Load += gcnew System::EventHandler(this, &AddTargetContainerForm::OnLoad);
      this->ResumeLayout(false);

    }
#pragma endregion
  };
}
