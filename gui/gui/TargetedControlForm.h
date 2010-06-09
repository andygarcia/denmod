#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace gui {

  generic<class T> where T: gui::Target, ref class
	public ref class TargetedControlForm : public System::Windows::Forms::Form
	{
	public:
		TargetedControlForm( TargetedControl<T> ^ targetedControl, BindingSource ^ locationBinding );
	protected:
		~TargetedControlForm(void);

  protected:
    void SetSchedulePanel(void);
  private: System::Windows::Forms::Panel^  panel1;
  private: System::Windows::Forms::GroupBox^  gboxSchedule;

  private: System::Windows::Forms::GroupBox^  gboxTargets;
  protected: 

  protected:
    TargetedControl<T> ^ _targetedControl;

  protected:
    System::Void OnLoad( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnAddContainer( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnRemoveContainer( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnOk( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnCancel( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnScheduleChange( System::Object ^ sender, System::EventArgs ^ e );

  protected:
    UserControl ^ CurrentSchedulePanel;
    BindingSource ^ LocationBinding;
    gui::Location ^ ActiveLocation;


  private: System::Windows::Forms::TextBox^  tboxName;
  private: System::Windows::Forms::Label^  lblName;
  private: System::Windows::Forms::DataGridView^  dgvTargets;

  private: System::Windows::Forms::Button^  btnRemoveContainer;
  private: System::Windows::Forms::Button^  btnAddContainer;
  private: System::Windows::Forms::ComboBox^  cboxSchedule;

  private: System::Windows::Forms::Button^  btnOK;
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
      this->tboxName = (gcnew System::Windows::Forms::TextBox());
      this->lblName = (gcnew System::Windows::Forms::Label());
      this->dgvTargets = (gcnew System::Windows::Forms::DataGridView());
      this->btnRemoveContainer = (gcnew System::Windows::Forms::Button());
      this->btnAddContainer = (gcnew System::Windows::Forms::Button());
      this->cboxSchedule = (gcnew System::Windows::Forms::ComboBox());
      this->btnOK = (gcnew System::Windows::Forms::Button());
      this->btnCancel = (gcnew System::Windows::Forms::Button());
      this->panel1 = (gcnew System::Windows::Forms::Panel());
      this->gboxSchedule = (gcnew System::Windows::Forms::GroupBox());
      this->gboxTargets = (gcnew System::Windows::Forms::GroupBox());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvTargets))->BeginInit();
      this->gboxSchedule->SuspendLayout();
      this->gboxTargets->SuspendLayout();
      this->SuspendLayout();
      // 
      // tboxName
      // 
      this->tboxName->Location = System::Drawing::Point(53, 9);
      this->tboxName->Name = L"tboxName";
      this->tboxName->ReadOnly = true;
      this->tboxName->Size = System::Drawing::Size(391, 20);
      this->tboxName->TabIndex = 1;
      // 
      // lblName
      // 
      this->lblName->AutoSize = true;
      this->lblName->Location = System::Drawing::Point(9, 12);
      this->lblName->Name = L"lblName";
      this->lblName->Size = System::Drawing::Size(38, 13);
      this->lblName->TabIndex = 0;
      this->lblName->Text = L"Name:";
      // 
      // dgvTargets
      // 
      this->dgvTargets->AllowUserToAddRows = false;
      this->dgvTargets->AllowUserToDeleteRows = false;
      this->dgvTargets->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
      this->dgvTargets->Location = System::Drawing::Point(6, 48);
      this->dgvTargets->Name = L"dgvTargets";
      this->dgvTargets->RowHeadersVisible = false;
      this->dgvTargets->Size = System::Drawing::Size(420, 157);
      this->dgvTargets->TabIndex = 0;
      // 
      // btnRemoveContainer
      // 
      this->btnRemoveContainer->Location = System::Drawing::Point(116, 19);
      this->btnRemoveContainer->Name = L"btnRemoveContainer";
      this->btnRemoveContainer->Size = System::Drawing::Size(104, 23);
      this->btnRemoveContainer->TabIndex = 2;
      this->btnRemoveContainer->Text = L"Remove Container";
      this->btnRemoveContainer->UseVisualStyleBackColor = true;
      this->btnRemoveContainer->Click += gcnew System::EventHandler(this, &TargetedControlForm::OnRemoveContainer);
      // 
      // btnAddContainer
      // 
      this->btnAddContainer->Location = System::Drawing::Point(6, 19);
      this->btnAddContainer->Name = L"btnAddContainer";
      this->btnAddContainer->Size = System::Drawing::Size(104, 23);
      this->btnAddContainer->TabIndex = 1;
      this->btnAddContainer->Text = L"Add Container";
      this->btnAddContainer->UseVisualStyleBackColor = true;
      this->btnAddContainer->Click += gcnew System::EventHandler(this, &TargetedControlForm::OnAddContainer);
      // 
      // cboxSchedule
      // 
      this->cboxSchedule->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxSchedule->FormattingEnabled = true;
      this->cboxSchedule->Location = System::Drawing::Point(6, 19);
      this->cboxSchedule->Name = L"cboxSchedule";
      this->cboxSchedule->Size = System::Drawing::Size(122, 21);
      this->cboxSchedule->TabIndex = 0;
      this->cboxSchedule->SelectionChangeCommitted += gcnew System::EventHandler(this, &TargetedControlForm::OnScheduleChange);
      // 
      // btnOK
      // 
      this->btnOK->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->btnOK->Location = System::Drawing::Point(288, 513);
      this->btnOK->Name = L"btnOK";
      this->btnOK->Size = System::Drawing::Size(75, 23);
      this->btnOK->TabIndex = 4;
      this->btnOK->Text = L"OK";
      this->btnOK->UseVisualStyleBackColor = true;
      this->btnOK->Click += gcnew System::EventHandler(this, &TargetedControlForm::OnOk);
      // 
      // btnCancel
      // 
      this->btnCancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
      this->btnCancel->Location = System::Drawing::Point(369, 513);
      this->btnCancel->Name = L"btnCancel";
      this->btnCancel->Size = System::Drawing::Size(75, 23);
      this->btnCancel->TabIndex = 5;
      this->btnCancel->Text = L"Cancel";
      this->btnCancel->UseVisualStyleBackColor = true;
      this->btnCancel->Click += gcnew System::EventHandler(this, &TargetedControlForm::OnCancel);
      // 
      // panel1
      // 
      this->panel1->Location = System::Drawing::Point(6, 46);
      this->panel1->Name = L"panel1";
      this->panel1->Size = System::Drawing::Size(420, 200);
      this->panel1->TabIndex = 1;
      this->panel1->Visible = false;
      // 
      // gboxSchedule
      // 
      this->gboxSchedule->Controls->Add(this->panel1);
      this->gboxSchedule->Controls->Add(this->cboxSchedule);
      this->gboxSchedule->Location = System::Drawing::Point(12, 255);
      this->gboxSchedule->Name = L"gboxSchedule";
      this->gboxSchedule->Size = System::Drawing::Size(432, 252);
      this->gboxSchedule->TabIndex = 3;
      this->gboxSchedule->TabStop = false;
      this->gboxSchedule->Text = L"Scheduling";
      // 
      // gboxTargets
      // 
      this->gboxTargets->Controls->Add(this->btnAddContainer);
      this->gboxTargets->Controls->Add(this->dgvTargets);
      this->gboxTargets->Controls->Add(this->btnRemoveContainer);
      this->gboxTargets->Location = System::Drawing::Point(12, 38);
      this->gboxTargets->Name = L"gboxTargets";
      this->gboxTargets->Size = System::Drawing::Size(432, 211);
      this->gboxTargets->TabIndex = 2;
      this->gboxTargets->TabStop = false;
      this->gboxTargets->Text = L"Target Containers:";
      // 
      // TargetedControlForm
      // 
      this->AcceptButton = this->btnOK;
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->CancelButton = this->btnCancel;
      this->ClientSize = System::Drawing::Size(456, 548);
      this->Controls->Add(this->gboxTargets);
      this->Controls->Add(this->gboxSchedule);
      this->Controls->Add(this->btnOK);
      this->Controls->Add(this->btnCancel);
      this->Controls->Add(this->tboxName);
      this->Controls->Add(this->lblName);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
      this->Name = L"TargetedControlForm";
      this->ShowInTaskbar = false;
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
      this->Text = L"TargetedControlForm";
      this->Load += gcnew System::EventHandler(this, &TargetedControlForm::OnLoad);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvTargets))->EndInit();
      this->gboxSchedule->ResumeLayout(false);
      this->gboxTargets->ResumeLayout(false);
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
	};
}
