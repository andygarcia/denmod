#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace gui {


  public ref class PupaeBiologyPanel : public System::Windows::Forms::UserControl
	{
	public:
		PupaeBiologyPanel( BindingSource ^ locationBinding );
	protected:
		~PupaeBiologyPanel();

  private:
    System::Void OnLoad( System::Object ^ sender, System::EventArgs ^ e );

  private:
    BindingSource  ^ LocationBinding;


  private: System::Windows::Forms::Label^  lblNominalSurvival;
  private: System::Windows::Forms::Label^  lblEmergenceSurvival;
  private: System::Windows::Forms::Label^  lblFemaleEmergence;





  private: System::Windows::Forms::GroupBox^  gboxDev;
  private: System::Windows::Forms::Label^  lblTHALF;
  private: System::Windows::Forms::Label^  lblDHH;
  private: System::Windows::Forms::Label^  lblDHA;
  private: System::Windows::Forms::Label^  lblRO25;





  private: System::Windows::Forms::GroupBox^  gboxTemp;
  private: System::Windows::Forms::Label^  lblTempHighLethalSurvival;
  private: System::Windows::Forms::Label^  lblTempLowLethalSurvival;
  private: System::Windows::Forms::Label^  lblTempHighThreshold;
  private: System::Windows::Forms::Label^  lblTempLowThreshold;
  private: System::Windows::Forms::Label^  lblTempHighLethalThreshold;
  private: System::Windows::Forms::Label^  lblTempLowLethalThreshold;







  private: ctrl::ScientificNotationTextBox^  snboxNominalSurvival;
  private: ctrl::ScientificNotationTextBox^  snboxEmergenceSurvival;
  private: ctrl::ScientificNotationTextBox^  snboxFemaleEmergence;
  private: ctrl::ScientificNotationTextBox^  snboxTHALF;
  private: ctrl::ScientificNotationTextBox^  snboxRO25;
  private: ctrl::ScientificNotationTextBox^  snboxDHH;
  private: ctrl::ScientificNotationTextBox^  snboxDHA;
  private: ctrl::ScientificNotationTextBox^  snboxTempHighLethalSurvival;
  private: ctrl::ScientificNotationTextBox^  snboxTempHighThreshold;
  private: ctrl::ScientificNotationTextBox^  snboxTempLowLethalSurvival;
  private: ctrl::ScientificNotationTextBox^  snboxTempHighLethalThreshold;
  private: ctrl::ScientificNotationTextBox^  snboxTempLowThreshold;
  private: ctrl::ScientificNotationTextBox^  snboxTempLowLethalThreshold;


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
      this->gboxDev = (gcnew System::Windows::Forms::GroupBox());
      this->snboxTHALF = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxRO25 = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxDHH = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxDHA = (gcnew ctrl::ScientificNotationTextBox());
      this->lblTHALF = (gcnew System::Windows::Forms::Label());
      this->lblDHH = (gcnew System::Windows::Forms::Label());
      this->lblDHA = (gcnew System::Windows::Forms::Label());
      this->lblRO25 = (gcnew System::Windows::Forms::Label());
      this->lblNominalSurvival = (gcnew System::Windows::Forms::Label());
      this->lblEmergenceSurvival = (gcnew System::Windows::Forms::Label());
      this->lblFemaleEmergence = (gcnew System::Windows::Forms::Label());
      this->gboxTemp = (gcnew System::Windows::Forms::GroupBox());
      this->snboxTempHighLethalSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxTempHighThreshold = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxTempLowLethalSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxTempHighLethalThreshold = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxTempLowThreshold = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxTempLowLethalThreshold = (gcnew ctrl::ScientificNotationTextBox());
      this->lblTempHighLethalSurvival = (gcnew System::Windows::Forms::Label());
      this->lblTempLowLethalSurvival = (gcnew System::Windows::Forms::Label());
      this->lblTempHighThreshold = (gcnew System::Windows::Forms::Label());
      this->lblTempLowThreshold = (gcnew System::Windows::Forms::Label());
      this->lblTempHighLethalThreshold = (gcnew System::Windows::Forms::Label());
      this->lblTempLowLethalThreshold = (gcnew System::Windows::Forms::Label());
      this->snboxNominalSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxEmergenceSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxFemaleEmergence = (gcnew ctrl::ScientificNotationTextBox());
      this->gboxDev->SuspendLayout();
      this->gboxTemp->SuspendLayout();
      this->SuspendLayout();
      // 
      // gboxDev
      // 
      this->gboxDev->Controls->Add(this->snboxTHALF);
      this->gboxDev->Controls->Add(this->snboxRO25);
      this->gboxDev->Controls->Add(this->snboxDHH);
      this->gboxDev->Controls->Add(this->snboxDHA);
      this->gboxDev->Controls->Add(this->lblTHALF);
      this->gboxDev->Controls->Add(this->lblDHH);
      this->gboxDev->Controls->Add(this->lblDHA);
      this->gboxDev->Controls->Add(this->lblRO25);
      this->gboxDev->Location = System::Drawing::Point(3, 89);
      this->gboxDev->Name = L"gboxDev";
      this->gboxDev->Size = System::Drawing::Size(374, 123);
      this->gboxDev->TabIndex = 8;
      this->gboxDev->TabStop = false;
      this->gboxDev->Text = L"Daily Development";
      // 
      // snboxTHALF
      // 
      this->snboxTHALF->Location = System::Drawing::Point(277, 97);
      this->snboxTHALF->Name = L"snboxTHALF";
      this->snboxTHALF->Size = System::Drawing::Size(80, 20);
      this->snboxTHALF->TabIndex = 7;
      this->snboxTHALF->Text = L"0.00000";
      this->snboxTHALF->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTHALF->Value = L"0";
      // 
      // snboxRO25
      // 
      this->snboxRO25->Location = System::Drawing::Point(277, 19);
      this->snboxRO25->Name = L"snboxRO25";
      this->snboxRO25->Size = System::Drawing::Size(80, 20);
      this->snboxRO25->TabIndex = 1;
      this->snboxRO25->Text = L"0.00000";
      this->snboxRO25->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxRO25->Value = L"0";
      // 
      // snboxDHH
      // 
      this->snboxDHH->Location = System::Drawing::Point(277, 71);
      this->snboxDHH->Name = L"snboxDHH";
      this->snboxDHH->Size = System::Drawing::Size(80, 20);
      this->snboxDHH->TabIndex = 5;
      this->snboxDHH->Text = L"0.00000";
      this->snboxDHH->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxDHH->Value = L"0";
      // 
      // snboxDHA
      // 
      this->snboxDHA->Location = System::Drawing::Point(277, 45);
      this->snboxDHA->Name = L"snboxDHA";
      this->snboxDHA->Size = System::Drawing::Size(80, 20);
      this->snboxDHA->TabIndex = 3;
      this->snboxDHA->Text = L"0.00000";
      this->snboxDHA->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxDHA->Value = L"0";
      // 
      // lblTHALF
      // 
      this->lblTHALF->AutoSize = true;
      this->lblTHALF->Location = System::Drawing::Point(6, 99);
      this->lblTHALF->Name = L"lblTHALF";
      this->lblTHALF->Size = System::Drawing::Size(139, 13);
      this->lblTHALF->TabIndex = 6;
      this->lblTHALF->Text = L"Temperature of inactivation:";
      // 
      // lblDHH
      // 
      this->lblDHH->AutoSize = true;
      this->lblDHH->Location = System::Drawing::Point(6, 73);
      this->lblDHH->Name = L"lblDHH";
      this->lblDHH->Size = System::Drawing::Size(120, 13);
      this->lblDHH->TabIndex = 4;
      this->lblDHH->Text = L"Enthalpy of inactivation:";
      // 
      // lblDHA
      // 
      this->lblDHA->AutoSize = true;
      this->lblDHA->Location = System::Drawing::Point(6, 47);
      this->lblDHA->Name = L"lblDHA";
      this->lblDHA->Size = System::Drawing::Size(112, 13);
      this->lblDHA->TabIndex = 2;
      this->lblDHA->Text = L"Enthalpy of activation:";
      // 
      // lblRO25
      // 
      this->lblRO25->AutoSize = true;
      this->lblRO25->Location = System::Drawing::Point(6, 21);
      this->lblRO25->Name = L"lblRO25";
      this->lblRO25->Size = System::Drawing::Size(94, 13);
      this->lblRO25->TabIndex = 0;
      this->lblRO25->Text = L"Development rate:";
      // 
      // lblNominalSurvival
      // 
      this->lblNominalSurvival->AutoSize = true;
      this->lblNominalSurvival->Location = System::Drawing::Point(9, 14);
      this->lblNominalSurvival->Name = L"lblNominalSurvival";
      this->lblNominalSurvival->Size = System::Drawing::Size(87, 13);
      this->lblNominalSurvival->TabIndex = 2;
      this->lblNominalSurvival->Text = L"Nominal survival:";
      // 
      // lblEmergenceSurvival
      // 
      this->lblEmergenceSurvival->AutoSize = true;
      this->lblEmergenceSurvival->Location = System::Drawing::Point(9, 40);
      this->lblEmergenceSurvival->Name = L"lblEmergenceSurvival";
      this->lblEmergenceSurvival->Size = System::Drawing::Size(103, 13);
      this->lblEmergenceSurvival->TabIndex = 4;
      this->lblEmergenceSurvival->Text = L"Emergence survival:";
      // 
      // lblFemaleEmergence
      // 
      this->lblFemaleEmergence->AutoSize = true;
      this->lblFemaleEmergence->Location = System::Drawing::Point(9, 66);
      this->lblFemaleEmergence->Name = L"lblFemaleEmergence";
      this->lblFemaleEmergence->Size = System::Drawing::Size(123, 13);
      this->lblFemaleEmergence->TabIndex = 6;
      this->lblFemaleEmergence->Text = L"Female emergence ratio:";
      // 
      // gboxTemp
      // 
      this->gboxTemp->Controls->Add(this->snboxTempHighLethalSurvival);
      this->gboxTemp->Controls->Add(this->snboxTempHighThreshold);
      this->gboxTemp->Controls->Add(this->snboxTempLowLethalSurvival);
      this->gboxTemp->Controls->Add(this->snboxTempHighLethalThreshold);
      this->gboxTemp->Controls->Add(this->snboxTempLowThreshold);
      this->gboxTemp->Controls->Add(this->snboxTempLowLethalThreshold);
      this->gboxTemp->Controls->Add(this->lblTempHighLethalSurvival);
      this->gboxTemp->Controls->Add(this->lblTempLowLethalSurvival);
      this->gboxTemp->Controls->Add(this->lblTempHighThreshold);
      this->gboxTemp->Controls->Add(this->lblTempLowThreshold);
      this->gboxTemp->Controls->Add(this->lblTempHighLethalThreshold);
      this->gboxTemp->Controls->Add(this->lblTempLowLethalThreshold);
      this->gboxTemp->Location = System::Drawing::Point(3, 218);
      this->gboxTemp->Name = L"gboxTemp";
      this->gboxTemp->Size = System::Drawing::Size(374, 175);
      this->gboxTemp->TabIndex = 9;
      this->gboxTemp->TabStop = false;
      this->gboxTemp->Text = L"Survival vs. Temperature";
      // 
      // snboxTempHighLethalSurvival
      // 
      this->snboxTempHighLethalSurvival->Location = System::Drawing::Point(277, 149);
      this->snboxTempHighLethalSurvival->Name = L"snboxTempHighLethalSurvival";
      this->snboxTempHighLethalSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxTempHighLethalSurvival->TabIndex = 11;
      this->snboxTempHighLethalSurvival->Text = L"0.00";
      this->snboxTempHighLethalSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTempHighLethalSurvival->Value = L"0";
      // 
      // snboxTempHighThreshold
      // 
      this->snboxTempHighThreshold->Location = System::Drawing::Point(277, 97);
      this->snboxTempHighThreshold->Name = L"snboxTempHighThreshold";
      this->snboxTempHighThreshold->Size = System::Drawing::Size(80, 20);
      this->snboxTempHighThreshold->TabIndex = 7;
      this->snboxTempHighThreshold->Text = L"0.00";
      this->snboxTempHighThreshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTempHighThreshold->Value = L"0";
      // 
      // snboxTempLowLethalSurvival
      // 
      this->snboxTempLowLethalSurvival->Location = System::Drawing::Point(277, 45);
      this->snboxTempLowLethalSurvival->Name = L"snboxTempLowLethalSurvival";
      this->snboxTempLowLethalSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxTempLowLethalSurvival->TabIndex = 3;
      this->snboxTempLowLethalSurvival->Text = L"0.00";
      this->snboxTempLowLethalSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTempLowLethalSurvival->Value = L"0";
      // 
      // snboxTempHighLethalThreshold
      // 
      this->snboxTempHighLethalThreshold->Location = System::Drawing::Point(277, 123);
      this->snboxTempHighLethalThreshold->Name = L"snboxTempHighLethalThreshold";
      this->snboxTempHighLethalThreshold->Size = System::Drawing::Size(80, 20);
      this->snboxTempHighLethalThreshold->TabIndex = 9;
      this->snboxTempHighLethalThreshold->Text = L"0.00";
      this->snboxTempHighLethalThreshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTempHighLethalThreshold->Value = L"0";
      // 
      // snboxTempLowThreshold
      // 
      this->snboxTempLowThreshold->Location = System::Drawing::Point(277, 71);
      this->snboxTempLowThreshold->Name = L"snboxTempLowThreshold";
      this->snboxTempLowThreshold->Size = System::Drawing::Size(80, 20);
      this->snboxTempLowThreshold->TabIndex = 5;
      this->snboxTempLowThreshold->Text = L"0.00";
      this->snboxTempLowThreshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTempLowThreshold->Value = L"0";
      // 
      // snboxTempLowLethalThreshold
      // 
      this->snboxTempLowLethalThreshold->Location = System::Drawing::Point(277, 19);
      this->snboxTempLowLethalThreshold->Name = L"snboxTempLowLethalThreshold";
      this->snboxTempLowLethalThreshold->Size = System::Drawing::Size(80, 20);
      this->snboxTempLowLethalThreshold->TabIndex = 1;
      this->snboxTempLowLethalThreshold->Text = L"0.00";
      this->snboxTempLowLethalThreshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTempLowLethalThreshold->Value = L"0";
      // 
      // lblTempHighLethalSurvival
      // 
      this->lblTempHighLethalSurvival->AutoSize = true;
      this->lblTempHighLethalSurvival->Location = System::Drawing::Point(6, 151);
      this->lblTempHighLethalSurvival->Name = L"lblTempHighLethalSurvival";
      this->lblTempHighLethalSurvival->Size = System::Drawing::Size(261, 13);
      this->lblTempHighLethalSurvival->TabIndex = 10;
      this->lblTempHighLethalSurvival->Text = L"Survival at or above high lethal temperature threshold:";
      // 
      // lblTempLowLethalSurvival
      // 
      this->lblTempLowLethalSurvival->AutoSize = true;
      this->lblTempLowLethalSurvival->Location = System::Drawing::Point(6, 47);
      this->lblTempLowLethalSurvival->Name = L"lblTempLowLethalSurvival";
      this->lblTempLowLethalSurvival->Size = System::Drawing::Size(255, 13);
      this->lblTempLowLethalSurvival->TabIndex = 2;
      this->lblTempLowLethalSurvival->Text = L"Survival at or below low lethal temperature threshold:";
      // 
      // lblTempHighThreshold
      // 
      this->lblTempHighThreshold->AutoSize = true;
      this->lblTempHighThreshold->Location = System::Drawing::Point(6, 99);
      this->lblTempHighThreshold->Name = L"lblTempHighThreshold";
      this->lblTempHighThreshold->Size = System::Drawing::Size(134, 13);
      this->lblTempHighThreshold->TabIndex = 6;
      this->lblTempHighThreshold->Text = L"High temperature threshold";
      // 
      // lblTempLowThreshold
      // 
      this->lblTempLowThreshold->AutoSize = true;
      this->lblTempLowThreshold->Location = System::Drawing::Point(6, 73);
      this->lblTempLowThreshold->Name = L"lblTempLowThreshold";
      this->lblTempLowThreshold->Size = System::Drawing::Size(135, 13);
      this->lblTempLowThreshold->TabIndex = 4;
      this->lblTempLowThreshold->Text = L"Low temperature threshold:";
      // 
      // lblTempHighLethalThreshold
      // 
      this->lblTempHighLethalThreshold->AutoSize = true;
      this->lblTempHighLethalThreshold->Location = System::Drawing::Point(6, 125);
      this->lblTempHighLethalThreshold->Name = L"lblTempHighLethalThreshold";
      this->lblTempHighLethalThreshold->Size = System::Drawing::Size(165, 13);
      this->lblTempHighLethalThreshold->TabIndex = 8;
      this->lblTempHighLethalThreshold->Text = L"High lethal temperature threshold:";
      // 
      // lblTempLowLethalThreshold
      // 
      this->lblTempLowLethalThreshold->AutoSize = true;
      this->lblTempLowLethalThreshold->Location = System::Drawing::Point(6, 21);
      this->lblTempLowLethalThreshold->Name = L"lblTempLowLethalThreshold";
      this->lblTempLowLethalThreshold->Size = System::Drawing::Size(163, 13);
      this->lblTempLowLethalThreshold->TabIndex = 0;
      this->lblTempLowLethalThreshold->Text = L"Low lethal temperature threshold:";
      // 
      // snboxNominalSurvival
      // 
      this->snboxNominalSurvival->Location = System::Drawing::Point(280, 11);
      this->snboxNominalSurvival->Name = L"snboxNominalSurvival";
      this->snboxNominalSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxNominalSurvival->TabIndex = 3;
      this->snboxNominalSurvival->Text = L"0.00";
      this->snboxNominalSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxNominalSurvival->Value = L"0";
      // 
      // snboxEmergenceSurvival
      // 
      this->snboxEmergenceSurvival->Location = System::Drawing::Point(280, 37);
      this->snboxEmergenceSurvival->Name = L"snboxEmergenceSurvival";
      this->snboxEmergenceSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxEmergenceSurvival->TabIndex = 5;
      this->snboxEmergenceSurvival->Text = L"0.00";
      this->snboxEmergenceSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxEmergenceSurvival->Value = L"0";
      // 
      // snboxFemaleEmergence
      // 
      this->snboxFemaleEmergence->Location = System::Drawing::Point(280, 63);
      this->snboxFemaleEmergence->Name = L"snboxFemaleEmergence";
      this->snboxFemaleEmergence->Size = System::Drawing::Size(80, 20);
      this->snboxFemaleEmergence->TabIndex = 7;
      this->snboxFemaleEmergence->Text = L"0.00";
      this->snboxFemaleEmergence->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxFemaleEmergence->Value = L"0";
      // 
      // PupaeBiologyPanel
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->Controls->Add(this->snboxFemaleEmergence);
      this->Controls->Add(this->snboxNominalSurvival);
      this->Controls->Add(this->snboxEmergenceSurvival);
      this->Controls->Add(this->gboxTemp);
      this->Controls->Add(this->gboxDev);
      this->Controls->Add(this->lblFemaleEmergence);
      this->Controls->Add(this->lblEmergenceSurvival);
      this->Controls->Add(this->lblNominalSurvival);
      this->Name = L"PupaeBiologyPanel";
      this->Size = System::Drawing::Size(380, 396);
      this->Load += gcnew System::EventHandler(this, &PupaeBiologyPanel::OnLoad);
      this->gboxDev->ResumeLayout(false);
      this->gboxDev->PerformLayout();
      this->gboxTemp->ResumeLayout(false);
      this->gboxTemp->PerformLayout();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  };
}
