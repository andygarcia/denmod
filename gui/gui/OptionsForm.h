#pragma once
#include "Settings.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace gui {

	public ref class OptionsForm : public System::Windows::Forms::Form
	{
	public:
		OptionsForm( Settings ^ userSettings );
	protected:
		~OptionsForm();

  private:
    System::Void OnLoad(System::Object^  sender, System::EventArgs^  e);
    System::Void OnOk(System::Object^  sender, System::EventArgs^  e);
    System::Void OnCancel(System::Object^  sender, System::EventArgs^  e);

  private:
    Settings ^ _settings;

  private: System::Windows::Forms::CheckBox^  chkDoSimulationDiskOutput;
  private: System::Windows::Forms::GroupBox^  gboxCimsim;
  private: System::Windows::Forms::CheckBox^  chkScaleCimsimMainGraph;
  private: System::Windows::Forms::CheckBox^  chkStochasticAdvancement;
  private: System::Windows::Forms::CheckBox^  chkEstablishedPopulationDefault;
  private: System::Windows::Forms::Button^  btnOk;
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
      this->btnOk = (gcnew System::Windows::Forms::Button());
      this->btnCancel = (gcnew System::Windows::Forms::Button());
      this->chkScaleCimsimMainGraph = (gcnew System::Windows::Forms::CheckBox());
      this->chkStochasticAdvancement = (gcnew System::Windows::Forms::CheckBox());
      this->gboxCimsim = (gcnew System::Windows::Forms::GroupBox());
      this->chkEstablishedPopulationDefault = (gcnew System::Windows::Forms::CheckBox());
      this->chkDoSimulationDiskOutput = (gcnew System::Windows::Forms::CheckBox());
      this->gboxCimsim->SuspendLayout();
      this->SuspendLayout();
      // 
      // btnOk
      // 
      this->btnOk->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnOk->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->btnOk->Location = System::Drawing::Point(158, 132);
      this->btnOk->Name = L"btnOk";
      this->btnOk->Size = System::Drawing::Size(75, 23);
      this->btnOk->TabIndex = 0;
      this->btnOk->Text = L"OK";
      this->btnOk->UseVisualStyleBackColor = true;
      this->btnOk->Click += gcnew System::EventHandler(this, &OptionsForm::OnOk);
      // 
      // btnCancel
      // 
      this->btnCancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
      this->btnCancel->Location = System::Drawing::Point(239, 132);
      this->btnCancel->Name = L"btnCancel";
      this->btnCancel->Size = System::Drawing::Size(75, 23);
      this->btnCancel->TabIndex = 0;
      this->btnCancel->Text = L"Cancel";
      this->btnCancel->UseVisualStyleBackColor = true;
      this->btnCancel->Click += gcnew System::EventHandler(this, &OptionsForm::OnCancel);
      // 
      // chkScaleCimsimMainGraph
      // 
      this->chkScaleCimsimMainGraph->AutoSize = true;
      this->chkScaleCimsimMainGraph->Location = System::Drawing::Point(6, 68);
      this->chkScaleCimsimMainGraph->Name = L"chkScaleCimsimMainGraph";
      this->chkScaleCimsimMainGraph->Size = System::Drawing::Size(268, 17);
      this->chkScaleCimsimMainGraph->TabIndex = 1;
      this->chkScaleCimsimMainGraph->Text = L"Scale immatures on CIMSiM\'s main output by 100\'s.";
      this->chkScaleCimsimMainGraph->UseVisualStyleBackColor = true;
      // 
      // chkStochasticAdvancement
      // 
      this->chkStochasticAdvancement->AutoSize = true;
      this->chkStochasticAdvancement->Location = System::Drawing::Point(6, 45);
      this->chkStochasticAdvancement->Name = L"chkStochasticAdvancement";
      this->chkStochasticAdvancement->Size = System::Drawing::Size(240, 17);
      this->chkStochasticAdvancement->TabIndex = 2;
      this->chkStochasticAdvancement->Text = L"Use stochasticity for discrete cohort numbers.";
      this->chkStochasticAdvancement->UseVisualStyleBackColor = true;
      // 
      // gboxCimsim
      // 
      this->gboxCimsim->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->gboxCimsim->Controls->Add(this->chkEstablishedPopulationDefault);
      this->gboxCimsim->Controls->Add(this->chkStochasticAdvancement);
      this->gboxCimsim->Controls->Add(this->chkScaleCimsimMainGraph);
      this->gboxCimsim->Location = System::Drawing::Point(12, 35);
      this->gboxCimsim->Name = L"gboxCimsim";
      this->gboxCimsim->Size = System::Drawing::Size(302, 91);
      this->gboxCimsim->TabIndex = 3;
      this->gboxCimsim->TabStop = false;
      this->gboxCimsim->Text = L"CIMSiM";
      // 
      // chkEstablishedPopulationDefault
      // 
      this->chkEstablishedPopulationDefault->AutoSize = true;
      this->chkEstablishedPopulationDefault->Location = System::Drawing::Point(6, 22);
      this->chkEstablishedPopulationDefault->Name = L"chkEstablishedPopulationDefault";
      this->chkEstablishedPopulationDefault->Size = System::Drawing::Size(203, 17);
      this->chkEstablishedPopulationDefault->TabIndex = 2;
      this->chkEstablishedPopulationDefault->Text = L"Run established population by default";
      this->chkEstablishedPopulationDefault->UseVisualStyleBackColor = true;
      // 
      // chkDoSimulationDiskOutput
      // 
      this->chkDoSimulationDiskOutput->AutoSize = true;
      this->chkDoSimulationDiskOutput->Location = System::Drawing::Point(18, 12);
      this->chkDoSimulationDiskOutput->Name = L"chkDoSimulationDiskOutput";
      this->chkDoSimulationDiskOutput->Size = System::Drawing::Size(290, 17);
      this->chkDoSimulationDiskOutput->TabIndex = 4;
      this->chkDoSimulationDiskOutput->Text = L"Write extended output to disk from within simulation runs";
      this->chkDoSimulationDiskOutput->UseVisualStyleBackColor = true;
      // 
      // OptionsForm
      // 
      this->AcceptButton = this->btnOk;
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->CancelButton = this->btnCancel;
      this->ClientSize = System::Drawing::Size(326, 167);
      this->ControlBox = false;
      this->Controls->Add(this->chkDoSimulationDiskOutput);
      this->Controls->Add(this->gboxCimsim);
      this->Controls->Add(this->btnCancel);
      this->Controls->Add(this->btnOk);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
      this->Name = L"OptionsForm";
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
      this->Text = L"Options";
      this->Load += gcnew System::EventHandler(this, &OptionsForm::OnLoad);
      this->gboxCimsim->ResumeLayout(false);
      this->gboxCimsim->PerformLayout();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  };
}
