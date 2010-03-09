#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace gui {

	public ref class SpaceSprayForm : public System::Windows::Forms::Form
	{
	public:
    SpaceSprayForm( SpaceSpray ^ sr, BindingSource ^ locationBinding );
	protected:
		~SpaceSprayForm(void);

  private:
    void SetSchedulePanel(void);
  private: System::Windows::Forms::Panel^  panel1;

  private:
    SpaceSpray ^ SpaceSpray_;

  private:
    System::Void OnLoad( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnOk( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnCancel( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnScheduleChange( System::Object ^ sender, System::EventArgs ^ e );

  private:
    BindingSource ^ LocationBinding;
    gui::Location ^ ActiveLocation;

    UserControl ^ CurrentSchedulePanel;

  private: System::Windows::Forms::TextBox^  tboxName;
  private: System::Windows::Forms::Label^  lblName;
  private: System::Windows::Forms::Label^  lblOutdoorMortality;
  private: System::Windows::Forms::Label^  lblIndoorMortality;
  private: System::Windows::Forms::NumericUpDown^  numOutdoorMortality;
  private: System::Windows::Forms::NumericUpDown^  numIndoorMortality;
  private: System::Windows::Forms::Label^  lblSchedule;
  private: System::Windows::Forms::ComboBox^  cboxSchedule;
  private: System::Windows::Forms::Button^  btnCancel;
  private: System::Windows::Forms::Button^  btnOk;
  private: System::Windows::Forms::Label^  lblOutdoorProportion;

  private: System::Windows::Forms::NumericUpDown^  numOutdoorProportion;






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
      this->lblOutdoorMortality = (gcnew System::Windows::Forms::Label());
      this->lblIndoorMortality = (gcnew System::Windows::Forms::Label());
      this->numOutdoorMortality = (gcnew System::Windows::Forms::NumericUpDown());
      this->numIndoorMortality = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblSchedule = (gcnew System::Windows::Forms::Label());
      this->btnCancel = (gcnew System::Windows::Forms::Button());
      this->btnOk = (gcnew System::Windows::Forms::Button());
      this->lblOutdoorProportion = (gcnew System::Windows::Forms::Label());
      this->numOutdoorProportion = (gcnew System::Windows::Forms::NumericUpDown());
      this->cboxSchedule = (gcnew System::Windows::Forms::ComboBox());
      this->panel1 = (gcnew System::Windows::Forms::Panel());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numOutdoorMortality))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numIndoorMortality))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numOutdoorProportion))->BeginInit();
      this->SuspendLayout();
      // 
      // tboxName
      // 
      this->tboxName->Location = System::Drawing::Point(108, 12);
      this->tboxName->Name = L"tboxName";
      this->tboxName->ReadOnly = true;
      this->tboxName->Size = System::Drawing::Size(420, 20);
      this->tboxName->TabIndex = 1;
      // 
      // lblName
      // 
      this->lblName->AutoSize = true;
      this->lblName->Location = System::Drawing::Point(64, 15);
      this->lblName->Name = L"lblName";
      this->lblName->Size = System::Drawing::Size(38, 13);
      this->lblName->TabIndex = 0;
      this->lblName->Text = L"Name:";
      // 
      // lblOutdoorMortality
      // 
      this->lblOutdoorMortality->AutoSize = true;
      this->lblOutdoorMortality->Location = System::Drawing::Point(12, 40);
      this->lblOutdoorMortality->Name = L"lblOutdoorMortality";
      this->lblOutdoorMortality->Size = System::Drawing::Size(90, 13);
      this->lblOutdoorMortality->TabIndex = 2;
      this->lblOutdoorMortality->Text = L"Outdoor Mortality:";
      // 
      // lblIndoorMortality
      // 
      this->lblIndoorMortality->AutoSize = true;
      this->lblIndoorMortality->Location = System::Drawing::Point(20, 66);
      this->lblIndoorMortality->Name = L"lblIndoorMortality";
      this->lblIndoorMortality->Size = System::Drawing::Size(82, 13);
      this->lblIndoorMortality->TabIndex = 4;
      this->lblIndoorMortality->Text = L"Indoor Mortality:";
      // 
      // numOutdoorMortality
      // 
      this->numOutdoorMortality->DecimalPlaces = 3;
      this->numOutdoorMortality->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 131072});
      this->numOutdoorMortality->Location = System::Drawing::Point(108, 38);
      this->numOutdoorMortality->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numOutdoorMortality->Name = L"numOutdoorMortality";
      this->numOutdoorMortality->Size = System::Drawing::Size(72, 20);
      this->numOutdoorMortality->TabIndex = 3;
      // 
      // numIndoorMortality
      // 
      this->numIndoorMortality->DecimalPlaces = 3;
      this->numIndoorMortality->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 131072});
      this->numIndoorMortality->Location = System::Drawing::Point(108, 64);
      this->numIndoorMortality->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numIndoorMortality->Name = L"numIndoorMortality";
      this->numIndoorMortality->Size = System::Drawing::Size(72, 20);
      this->numIndoorMortality->TabIndex = 5;
      // 
      // lblSchedule
      // 
      this->lblSchedule->AutoSize = true;
      this->lblSchedule->Location = System::Drawing::Point(47, 93);
      this->lblSchedule->Name = L"lblSchedule";
      this->lblSchedule->Size = System::Drawing::Size(55, 13);
      this->lblSchedule->TabIndex = 8;
      this->lblSchedule->Text = L"Schedule:";
      // 
      // btnCancel
      // 
      this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
      this->btnCancel->Location = System::Drawing::Point(453, 323);
      this->btnCancel->Name = L"btnCancel";
      this->btnCancel->Size = System::Drawing::Size(75, 23);
      this->btnCancel->TabIndex = 12;
      this->btnCancel->Text = L"Cancel";
      this->btnCancel->UseVisualStyleBackColor = true;
      this->btnCancel->Click += gcnew System::EventHandler(this, &SpaceSprayForm::OnCancel);
      // 
      // btnOk
      // 
      this->btnOk->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->btnOk->Location = System::Drawing::Point(372, 323);
      this->btnOk->Name = L"btnOk";
      this->btnOk->Size = System::Drawing::Size(75, 23);
      this->btnOk->TabIndex = 11;
      this->btnOk->Text = L"OK";
      this->btnOk->UseVisualStyleBackColor = true;
      this->btnOk->Click += gcnew System::EventHandler(this, &SpaceSprayForm::OnOk);
      // 
      // lblOutdoorProportion
      // 
      this->lblOutdoorProportion->AutoSize = true;
      this->lblOutdoorProportion->Location = System::Drawing::Point(271, 40);
      this->lblOutdoorProportion->Name = L"lblOutdoorProportion";
      this->lblOutdoorProportion->Size = System::Drawing::Size(179, 13);
      this->lblOutdoorProportion->TabIndex = 6;
      this->lblOutdoorProportion->Text = L"Proportion of adults resting outdoors:";
      // 
      // numOutdoorProportion
      // 
      this->numOutdoorProportion->DecimalPlaces = 3;
      this->numOutdoorProportion->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 131072});
      this->numOutdoorProportion->Location = System::Drawing::Point(456, 38);
      this->numOutdoorProportion->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numOutdoorProportion->Name = L"numOutdoorProportion";
      this->numOutdoorProportion->Size = System::Drawing::Size(72, 20);
      this->numOutdoorProportion->TabIndex = 7;
      // 
      // cboxSchedule
      // 
      this->cboxSchedule->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxSchedule->FormattingEnabled = true;
      this->cboxSchedule->Location = System::Drawing::Point(108, 90);
      this->cboxSchedule->Name = L"cboxSchedule";
      this->cboxSchedule->Size = System::Drawing::Size(122, 21);
      this->cboxSchedule->TabIndex = 9;
      this->cboxSchedule->SelectionChangeCommitted += gcnew System::EventHandler(this, &SpaceSprayForm::OnScheduleChange);
      // 
      // panel1
      // 
      this->panel1->Location = System::Drawing::Point(108, 117);
      this->panel1->Name = L"panel1";
      this->panel1->Size = System::Drawing::Size(420, 200);
      this->panel1->TabIndex = 10;
      this->panel1->Visible = false;
      // 
      // SpaceSprayForm
      // 
      this->AcceptButton = this->btnOk;
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->CancelButton = this->btnCancel;
      this->ClientSize = System::Drawing::Size(540, 358);
      this->Controls->Add(this->panel1);
      this->Controls->Add(this->cboxSchedule);
      this->Controls->Add(this->btnOk);
      this->Controls->Add(this->btnCancel);
      this->Controls->Add(this->numIndoorMortality);
      this->Controls->Add(this->numOutdoorProportion);
      this->Controls->Add(this->numOutdoorMortality);
      this->Controls->Add(this->lblOutdoorProportion);
      this->Controls->Add(this->lblIndoorMortality);
      this->Controls->Add(this->lblOutdoorMortality);
      this->Controls->Add(this->tboxName);
      this->Controls->Add(this->lblSchedule);
      this->Controls->Add(this->lblName);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
      this->Name = L"SpaceSprayForm";
      this->ShowInTaskbar = false;
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
      this->Text = L"Space Spray";
      this->Load += gcnew System::EventHandler(this, &SpaceSprayForm::OnLoad);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numOutdoorMortality))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numIndoorMortality))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numOutdoorProportion))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
};
}
