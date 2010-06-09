#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace gui {

	public ref class EggBiologyPanel : public System::Windows::Forms::UserControl
	{
	public:
		EggBiologyPanel( BindingSource ^ locationBinding );
	protected:
		~EggBiologyPanel();

  private:
    BindingSource ^ _locationBinding;

  private:
    System::Void OnLoad( System::Object ^ sender, System::EventArgs ^ e );

  private: System::Windows::Forms::ErrorProvider^  errproTemperature;
  private: System::Windows::Forms::ErrorProvider^  errproSaturationDeficit;
  private: System::Windows::Forms::ErrorProvider^  errproPredation;
  private: ctrl::ScientificNotationTextBox^  snboxNominalSurvival;
  private: ctrl::ScientificNotationTextBox^  snboxTHALF;
  private: ctrl::ScientificNotationTextBox^  snboxDHA;
  private: ctrl::ScientificNotationTextBox^  snboxDHH;
  private: ctrl::ScientificNotationTextBox^  snboxRO25;
  private: ctrl::ScientificNotationTextBox^  snboxMinimumHatchTemperature;
  private: ctrl::ScientificNotationTextBox^  snboxSpontaneousHatchRatio;
  private: ctrl::ScientificNotationTextBox^  snboxFloodHatchRatio;
  private: ctrl::ScientificNotationTextBox^  snboxTempLowLethalThreshold;
  private: ctrl::ScientificNotationTextBox^  snboxTempLowLethalSurvival;
  private: ctrl::ScientificNotationTextBox^  snboxTempLowThreshold;
  private: ctrl::ScientificNotationTextBox^  snboxTempHighThreshold;
  private: ctrl::ScientificNotationTextBox^  snboxTempHighLethalThreshold;
  private: ctrl::ScientificNotationTextBox^  snboxTempHighLethalSurvival;
  private: ctrl::ScientificNotationTextBox^  snboxSatDefHighSurvival;
  private: ctrl::ScientificNotationTextBox^  snboxSatDefHighThreshold;
  private: ctrl::ScientificNotationTextBox^  snboxSatDefLowSurvival;
  private: ctrl::ScientificNotationTextBox^  snboxSatDefLowThreshold;
  private: ctrl::ScientificNotationTextBox^  snboxHighSunExposureSurvival;
  private: ctrl::ScientificNotationTextBox^  snboxHighSunExposureThrehsold;
  private: ctrl::ScientificNotationTextBox^  snboxPredHighSurvival;
  private: ctrl::ScientificNotationTextBox^  snboxPredHighThreshold;
  private: ctrl::ScientificNotationTextBox^  snboxPredLowSurvival;
  private: ctrl::ScientificNotationTextBox^  snboxPredLowThreshold;
  private: System::Windows::Forms::ErrorProvider^  errproEgg;
  private: System::Windows::Forms::Label^  lblNominalSurvival;
  private: System::Windows::Forms::GroupBox^  gboxDev;
  private: System::Windows::Forms::Label^  lblRO25;
  private: System::Windows::Forms::Label^  lblDHA;
  private: System::Windows::Forms::Label^  lblDHH;
  private: System::Windows::Forms::Label^  lblTHALF;
  private: System::Windows::Forms::GroupBox^  gboxHatch;
  private: System::Windows::Forms::Label^  lblMinimumHatchTemperature;
  private: System::Windows::Forms::Label^  lblFloodHatchRatio;
  private: System::Windows::Forms::Label^  lblSpontaneousHatchRatio;
  private: System::Windows::Forms::GroupBox^  gboxTemp;
  private: System::Windows::Forms::Label^  lblTempLowLethalThreshold;
  private: System::Windows::Forms::Label^  lblTempLowLethalSurvival;
  private: System::Windows::Forms::Label^  lblTempLowThreshold;
  private: System::Windows::Forms::Label^  lblTempHighThreshold;
  private: System::Windows::Forms::Label^  lblTempHighLethalThreshold;
  private: System::Windows::Forms::Label^  lblTempHighLethalSurvival;
  private: System::Windows::Forms::GroupBox^  gboxSatDef;
  private: System::Windows::Forms::Label^  lblHighSunExposureThrehsold;
  private: System::Windows::Forms::Label^  lblHighSunExposureSurvival;
  private: System::Windows::Forms::Label^  lblSatDefLowThreshold;
  private: System::Windows::Forms::Label^  lblSatDefLowSurvival;
  private: System::Windows::Forms::Label^  lblSatDefHighThreshold;
  private: System::Windows::Forms::Label^  lblSatDefHighSurvival;
  private: System::Windows::Forms::GroupBox^  gboxPredation;
  private: System::Windows::Forms::Label^  lblPredLowThreshold;
  private: System::Windows::Forms::Label^  lblPredLowSurvival;
  private: System::Windows::Forms::Label^  lblPredHighThreshold;
  private: System::Windows::Forms::Label^  lblPredHighSurvival;

  private: System::ComponentModel::IContainer^  components;
  private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->components = (gcnew System::ComponentModel::Container());
      this->gboxHatch = (gcnew System::Windows::Forms::GroupBox());
      this->snboxSpontaneousHatchRatio = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxFloodHatchRatio = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxMinimumHatchTemperature = (gcnew ctrl::ScientificNotationTextBox());
      this->lblSpontaneousHatchRatio = (gcnew System::Windows::Forms::Label());
      this->lblFloodHatchRatio = (gcnew System::Windows::Forms::Label());
      this->lblMinimumHatchTemperature = (gcnew System::Windows::Forms::Label());
      this->lblNominalSurvival = (gcnew System::Windows::Forms::Label());
      this->lblRO25 = (gcnew System::Windows::Forms::Label());
      this->lblDHA = (gcnew System::Windows::Forms::Label());
      this->lblDHH = (gcnew System::Windows::Forms::Label());
      this->lblTHALF = (gcnew System::Windows::Forms::Label());
      this->gboxDev = (gcnew System::Windows::Forms::GroupBox());
      this->snboxTHALF = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxDHA = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxDHH = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxRO25 = (gcnew ctrl::ScientificNotationTextBox());
      this->gboxTemp = (gcnew System::Windows::Forms::GroupBox());
      this->snboxTempHighLethalSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxTempHighLethalThreshold = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxTempHighThreshold = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxTempLowThreshold = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxTempLowLethalSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxTempLowLethalThreshold = (gcnew ctrl::ScientificNotationTextBox());
      this->lblTempHighLethalSurvival = (gcnew System::Windows::Forms::Label());
      this->lblTempLowLethalSurvival = (gcnew System::Windows::Forms::Label());
      this->lblTempHighThreshold = (gcnew System::Windows::Forms::Label());
      this->lblTempLowThreshold = (gcnew System::Windows::Forms::Label());
      this->lblTempHighLethalThreshold = (gcnew System::Windows::Forms::Label());
      this->lblTempLowLethalThreshold = (gcnew System::Windows::Forms::Label());
      this->gboxSatDef = (gcnew System::Windows::Forms::GroupBox());
      this->snboxSatDefHighSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxSatDefHighThreshold = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxSatDefLowSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->lblSatDefHighSurvival = (gcnew System::Windows::Forms::Label());
      this->snboxSatDefLowThreshold = (gcnew ctrl::ScientificNotationTextBox());
      this->lblHighSunExposureSurvival = (gcnew System::Windows::Forms::Label());
      this->snboxHighSunExposureSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxHighSunExposureThrehsold = (gcnew ctrl::ScientificNotationTextBox());
      this->lblSatDefLowSurvival = (gcnew System::Windows::Forms::Label());
      this->lblSatDefLowThreshold = (gcnew System::Windows::Forms::Label());
      this->lblSatDefHighThreshold = (gcnew System::Windows::Forms::Label());
      this->lblHighSunExposureThrehsold = (gcnew System::Windows::Forms::Label());
      this->gboxPredation = (gcnew System::Windows::Forms::GroupBox());
      this->lblPredHighSurvival = (gcnew System::Windows::Forms::Label());
      this->lblPredHighThreshold = (gcnew System::Windows::Forms::Label());
      this->snboxPredHighSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->lblPredLowSurvival = (gcnew System::Windows::Forms::Label());
      this->lblPredLowThreshold = (gcnew System::Windows::Forms::Label());
      this->snboxPredHighThreshold = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxPredLowSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxPredLowThreshold = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxNominalSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->errproEgg = (gcnew System::Windows::Forms::ErrorProvider(this->components));
      this->errproTemperature = (gcnew System::Windows::Forms::ErrorProvider(this->components));
      this->errproSaturationDeficit = (gcnew System::Windows::Forms::ErrorProvider(this->components));
      this->errproPredation = (gcnew System::Windows::Forms::ErrorProvider(this->components));
      this->gboxHatch->SuspendLayout();
      this->gboxDev->SuspendLayout();
      this->gboxTemp->SuspendLayout();
      this->gboxSatDef->SuspendLayout();
      this->gboxPredation->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errproEgg))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errproTemperature))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errproSaturationDeficit))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errproPredation))->BeginInit();
      this->SuspendLayout();
      // 
      // gboxHatch
      // 
      this->gboxHatch->Controls->Add(this->snboxSpontaneousHatchRatio);
      this->gboxHatch->Controls->Add(this->snboxFloodHatchRatio);
      this->gboxHatch->Controls->Add(this->snboxMinimumHatchTemperature);
      this->gboxHatch->Controls->Add(this->lblSpontaneousHatchRatio);
      this->gboxHatch->Controls->Add(this->lblFloodHatchRatio);
      this->gboxHatch->Controls->Add(this->lblMinimumHatchTemperature);
      this->gboxHatch->Location = System::Drawing::Point(3, 166);
      this->gboxHatch->Name = L"gboxHatch";
      this->gboxHatch->Size = System::Drawing::Size(374, 97);
      this->gboxHatch->TabIndex = 5;
      this->gboxHatch->TabStop = false;
      this->gboxHatch->Text = L"Hatch";
      // 
      // snboxSpontaneousHatchRatio
      // 
      this->snboxSpontaneousHatchRatio->Location = System::Drawing::Point(277, 71);
      this->snboxSpontaneousHatchRatio->Name = L"snboxSpontaneousHatchRatio";
      this->snboxSpontaneousHatchRatio->Size = System::Drawing::Size(80, 20);
      this->snboxSpontaneousHatchRatio->TabIndex = 5;
      this->snboxSpontaneousHatchRatio->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxSpontaneousHatchRatio->Value = L"";
      // 
      // snboxFloodHatchRatio
      // 
      this->snboxFloodHatchRatio->Location = System::Drawing::Point(277, 45);
      this->snboxFloodHatchRatio->Name = L"snboxFloodHatchRatio";
      this->snboxFloodHatchRatio->Size = System::Drawing::Size(80, 20);
      this->snboxFloodHatchRatio->TabIndex = 3;
      this->snboxFloodHatchRatio->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxFloodHatchRatio->Value = L"";
      // 
      // snboxMinimumHatchTemperature
      // 
      this->snboxMinimumHatchTemperature->Location = System::Drawing::Point(277, 19);
      this->snboxMinimumHatchTemperature->Name = L"snboxMinimumHatchTemperature";
      this->snboxMinimumHatchTemperature->Size = System::Drawing::Size(80, 20);
      this->snboxMinimumHatchTemperature->TabIndex = 1;
      this->snboxMinimumHatchTemperature->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxMinimumHatchTemperature->Value = L"";
      // 
      // lblSpontaneousHatchRatio
      // 
      this->lblSpontaneousHatchRatio->AutoSize = true;
      this->lblSpontaneousHatchRatio->Location = System::Drawing::Point(6, 73);
      this->lblSpontaneousHatchRatio->Name = L"lblSpontaneousHatchRatio";
      this->lblSpontaneousHatchRatio->Size = System::Drawing::Size(126, 13);
      this->lblSpontaneousHatchRatio->TabIndex = 4;
      this->lblSpontaneousHatchRatio->Text = L"Spontaneous hatch ratio:";
      // 
      // lblFloodHatchRatio
      // 
      this->lblFloodHatchRatio->AutoSize = true;
      this->lblFloodHatchRatio->Location = System::Drawing::Point(6, 47);
      this->lblFloodHatchRatio->Name = L"lblFloodHatchRatio";
      this->lblFloodHatchRatio->Size = System::Drawing::Size(89, 13);
      this->lblFloodHatchRatio->TabIndex = 2;
      this->lblFloodHatchRatio->Text = L"Flood hatch ratio:";
      // 
      // lblMinimumHatchTemperature
      // 
      this->lblMinimumHatchTemperature->AutoSize = true;
      this->lblMinimumHatchTemperature->Location = System::Drawing::Point(6, 21);
      this->lblMinimumHatchTemperature->Name = L"lblMinimumHatchTemperature";
      this->lblMinimumHatchTemperature->Size = System::Drawing::Size(140, 13);
      this->lblMinimumHatchTemperature->TabIndex = 0;
      this->lblMinimumHatchTemperature->Text = L"Minimum hatch temperature:";
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
      // lblRO25
      // 
      this->lblRO25->AutoSize = true;
      this->lblRO25->Location = System::Drawing::Point(6, 21);
      this->lblRO25->Name = L"lblRO25";
      this->lblRO25->Size = System::Drawing::Size(94, 13);
      this->lblRO25->TabIndex = 0;
      this->lblRO25->Text = L"Development rate:";
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
      // lblDHH
      // 
      this->lblDHH->AutoSize = true;
      this->lblDHH->Location = System::Drawing::Point(6, 73);
      this->lblDHH->Name = L"lblDHH";
      this->lblDHH->Size = System::Drawing::Size(120, 13);
      this->lblDHH->TabIndex = 4;
      this->lblDHH->Text = L"Enthalpy of inactivation:";
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
      // gboxDev
      // 
      this->gboxDev->Controls->Add(this->snboxTHALF);
      this->gboxDev->Controls->Add(this->snboxDHA);
      this->gboxDev->Controls->Add(this->snboxDHH);
      this->gboxDev->Controls->Add(this->snboxRO25);
      this->gboxDev->Controls->Add(this->lblTHALF);
      this->gboxDev->Controls->Add(this->lblDHH);
      this->gboxDev->Controls->Add(this->lblDHA);
      this->gboxDev->Controls->Add(this->lblRO25);
      this->gboxDev->Location = System::Drawing::Point(3, 37);
      this->gboxDev->Name = L"gboxDev";
      this->gboxDev->Size = System::Drawing::Size(374, 123);
      this->gboxDev->TabIndex = 4;
      this->gboxDev->TabStop = false;
      this->gboxDev->Text = L"Daily Development";
      // 
      // snboxTHALF
      // 
      this->snboxTHALF->Location = System::Drawing::Point(277, 96);
      this->snboxTHALF->Name = L"snboxTHALF";
      this->snboxTHALF->Size = System::Drawing::Size(80, 20);
      this->snboxTHALF->TabIndex = 7;
      this->snboxTHALF->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTHALF->Value = L"";
      // 
      // snboxDHA
      // 
      this->snboxDHA->Location = System::Drawing::Point(277, 44);
      this->snboxDHA->Name = L"snboxDHA";
      this->snboxDHA->Size = System::Drawing::Size(80, 20);
      this->snboxDHA->TabIndex = 3;
      this->snboxDHA->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxDHA->Value = L"";
      // 
      // snboxDHH
      // 
      this->snboxDHH->Location = System::Drawing::Point(277, 70);
      this->snboxDHH->Name = L"snboxDHH";
      this->snboxDHH->Size = System::Drawing::Size(80, 20);
      this->snboxDHH->TabIndex = 5;
      this->snboxDHH->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxDHH->Value = L"";
      // 
      // snboxRO25
      // 
      this->snboxRO25->Location = System::Drawing::Point(277, 18);
      this->snboxRO25->Name = L"snboxRO25";
      this->snboxRO25->Size = System::Drawing::Size(80, 20);
      this->snboxRO25->TabIndex = 1;
      this->snboxRO25->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxRO25->Value = L"";
      // 
      // gboxTemp
      // 
      this->gboxTemp->Controls->Add(this->snboxTempHighLethalSurvival);
      this->gboxTemp->Controls->Add(this->snboxTempHighLethalThreshold);
      this->gboxTemp->Controls->Add(this->snboxTempHighThreshold);
      this->gboxTemp->Controls->Add(this->snboxTempLowThreshold);
      this->gboxTemp->Controls->Add(this->snboxTempLowLethalSurvival);
      this->gboxTemp->Controls->Add(this->snboxTempLowLethalThreshold);
      this->gboxTemp->Controls->Add(this->lblTempHighLethalSurvival);
      this->gboxTemp->Controls->Add(this->lblTempLowLethalSurvival);
      this->gboxTemp->Controls->Add(this->lblTempHighThreshold);
      this->gboxTemp->Controls->Add(this->lblTempLowThreshold);
      this->gboxTemp->Controls->Add(this->lblTempHighLethalThreshold);
      this->gboxTemp->Controls->Add(this->lblTempLowLethalThreshold);
      this->gboxTemp->Location = System::Drawing::Point(3, 269);
      this->gboxTemp->Name = L"gboxTemp";
      this->gboxTemp->Size = System::Drawing::Size(374, 175);
      this->gboxTemp->TabIndex = 6;
      this->gboxTemp->TabStop = false;
      this->gboxTemp->Text = L"Survival vs. Temperature";
      // 
      // snboxTempHighLethalSurvival
      // 
      this->snboxTempHighLethalSurvival->Location = System::Drawing::Point(277, 149);
      this->snboxTempHighLethalSurvival->Name = L"snboxTempHighLethalSurvival";
      this->snboxTempHighLethalSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxTempHighLethalSurvival->TabIndex = 11;
      this->snboxTempHighLethalSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTempHighLethalSurvival->Value = L"";
      // 
      // snboxTempHighLethalThreshold
      // 
      this->snboxTempHighLethalThreshold->Location = System::Drawing::Point(277, 123);
      this->snboxTempHighLethalThreshold->Name = L"snboxTempHighLethalThreshold";
      this->snboxTempHighLethalThreshold->Size = System::Drawing::Size(80, 20);
      this->snboxTempHighLethalThreshold->TabIndex = 9;
      this->snboxTempHighLethalThreshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTempHighLethalThreshold->Value = L"";
      // 
      // snboxTempHighThreshold
      // 
      this->snboxTempHighThreshold->Location = System::Drawing::Point(277, 97);
      this->snboxTempHighThreshold->Name = L"snboxTempHighThreshold";
      this->snboxTempHighThreshold->Size = System::Drawing::Size(80, 20);
      this->snboxTempHighThreshold->TabIndex = 7;
      this->snboxTempHighThreshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTempHighThreshold->Value = L"";
      // 
      // snboxTempLowThreshold
      // 
      this->snboxTempLowThreshold->Location = System::Drawing::Point(277, 71);
      this->snboxTempLowThreshold->Name = L"snboxTempLowThreshold";
      this->snboxTempLowThreshold->Size = System::Drawing::Size(80, 20);
      this->snboxTempLowThreshold->TabIndex = 5;
      this->snboxTempLowThreshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTempLowThreshold->Value = L"";
      // 
      // snboxTempLowLethalSurvival
      // 
      this->snboxTempLowLethalSurvival->Location = System::Drawing::Point(277, 45);
      this->snboxTempLowLethalSurvival->Name = L"snboxTempLowLethalSurvival";
      this->snboxTempLowLethalSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxTempLowLethalSurvival->TabIndex = 3;
      this->snboxTempLowLethalSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTempLowLethalSurvival->Value = L"";
      // 
      // snboxTempLowLethalThreshold
      // 
      this->snboxTempLowLethalThreshold->Location = System::Drawing::Point(277, 19);
      this->snboxTempLowLethalThreshold->Name = L"snboxTempLowLethalThreshold";
      this->snboxTempLowLethalThreshold->Size = System::Drawing::Size(80, 20);
      this->snboxTempLowLethalThreshold->TabIndex = 1;
      this->snboxTempLowLethalThreshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTempLowLethalThreshold->Value = L"";
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
      // gboxSatDef
      // 
      this->gboxSatDef->Controls->Add(this->snboxSatDefHighSurvival);
      this->gboxSatDef->Controls->Add(this->snboxSatDefHighThreshold);
      this->gboxSatDef->Controls->Add(this->snboxSatDefLowSurvival);
      this->gboxSatDef->Controls->Add(this->lblSatDefHighSurvival);
      this->gboxSatDef->Controls->Add(this->snboxSatDefLowThreshold);
      this->gboxSatDef->Controls->Add(this->lblHighSunExposureSurvival);
      this->gboxSatDef->Controls->Add(this->snboxHighSunExposureSurvival);
      this->gboxSatDef->Controls->Add(this->snboxHighSunExposureThrehsold);
      this->gboxSatDef->Controls->Add(this->lblSatDefLowSurvival);
      this->gboxSatDef->Controls->Add(this->lblSatDefLowThreshold);
      this->gboxSatDef->Controls->Add(this->lblSatDefHighThreshold);
      this->gboxSatDef->Controls->Add(this->lblHighSunExposureThrehsold);
      this->gboxSatDef->Location = System::Drawing::Point(3, 450);
      this->gboxSatDef->Name = L"gboxSatDef";
      this->gboxSatDef->Size = System::Drawing::Size(374, 175);
      this->gboxSatDef->TabIndex = 7;
      this->gboxSatDef->TabStop = false;
      this->gboxSatDef->Text = L"Survival vs. Saturation Deficit";
      // 
      // snboxSatDefHighSurvival
      // 
      this->snboxSatDefHighSurvival->Location = System::Drawing::Point(277, 144);
      this->snboxSatDefHighSurvival->Name = L"snboxSatDefHighSurvival";
      this->snboxSatDefHighSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxSatDefHighSurvival->TabIndex = 11;
      this->snboxSatDefHighSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxSatDefHighSurvival->Value = L"";
      // 
      // snboxSatDefHighThreshold
      // 
      this->snboxSatDefHighThreshold->Location = System::Drawing::Point(277, 118);
      this->snboxSatDefHighThreshold->Name = L"snboxSatDefHighThreshold";
      this->snboxSatDefHighThreshold->Size = System::Drawing::Size(80, 20);
      this->snboxSatDefHighThreshold->TabIndex = 9;
      this->snboxSatDefHighThreshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxSatDefHighThreshold->Value = L"";
      // 
      // snboxSatDefLowSurvival
      // 
      this->snboxSatDefLowSurvival->Location = System::Drawing::Point(277, 92);
      this->snboxSatDefLowSurvival->Name = L"snboxSatDefLowSurvival";
      this->snboxSatDefLowSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxSatDefLowSurvival->TabIndex = 7;
      this->snboxSatDefLowSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxSatDefLowSurvival->Value = L"";
      // 
      // lblSatDefHighSurvival
      // 
      this->lblSatDefHighSurvival->AutoSize = true;
      this->lblSatDefHighSurvival->Location = System::Drawing::Point(6, 151);
      this->lblSatDefHighSurvival->Name = L"lblSatDefHighSurvival";
      this->lblSatDefHighSurvival->Size = System::Drawing::Size(254, 13);
      this->lblSatDefHighSurvival->TabIndex = 10;
      this->lblSatDefHighSurvival->Text = L"Survival at or above high saturation deficit threshold:";
      // 
      // snboxSatDefLowThreshold
      // 
      this->snboxSatDefLowThreshold->Location = System::Drawing::Point(277, 66);
      this->snboxSatDefLowThreshold->Name = L"snboxSatDefLowThreshold";
      this->snboxSatDefLowThreshold->Size = System::Drawing::Size(80, 20);
      this->snboxSatDefLowThreshold->TabIndex = 5;
      this->snboxSatDefLowThreshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxSatDefLowThreshold->Value = L"";
      // 
      // lblHighSunExposureSurvival
      // 
      this->lblHighSunExposureSurvival->AutoSize = true;
      this->lblHighSunExposureSurvival->Location = System::Drawing::Point(6, 47);
      this->lblHighSunExposureSurvival->Name = L"lblHighSunExposureSurvival";
      this->lblHighSunExposureSurvival->Size = System::Drawing::Size(240, 13);
      this->lblHighSunExposureSurvival->TabIndex = 2;
      this->lblHighSunExposureSurvival->Text = L"Survival at or above high sun exposure threshold:";
      // 
      // snboxHighSunExposureSurvival
      // 
      this->snboxHighSunExposureSurvival->Location = System::Drawing::Point(277, 40);
      this->snboxHighSunExposureSurvival->Name = L"snboxHighSunExposureSurvival";
      this->snboxHighSunExposureSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxHighSunExposureSurvival->TabIndex = 3;
      this->snboxHighSunExposureSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxHighSunExposureSurvival->Value = L"";
      // 
      // snboxHighSunExposureThrehsold
      // 
      this->snboxHighSunExposureThrehsold->Location = System::Drawing::Point(277, 14);
      this->snboxHighSunExposureThrehsold->Name = L"snboxHighSunExposureThrehsold";
      this->snboxHighSunExposureThrehsold->Size = System::Drawing::Size(80, 20);
      this->snboxHighSunExposureThrehsold->TabIndex = 1;
      this->snboxHighSunExposureThrehsold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxHighSunExposureThrehsold->Value = L"";
      // 
      // lblSatDefLowSurvival
      // 
      this->lblSatDefLowSurvival->AutoSize = true;
      this->lblSatDefLowSurvival->Location = System::Drawing::Point(6, 99);
      this->lblSatDefLowSurvival->Name = L"lblSatDefLowSurvival";
      this->lblSatDefLowSurvival->Size = System::Drawing::Size(205, 13);
      this->lblSatDefLowSurvival->TabIndex = 6;
      this->lblSatDefLowSurvival->Text = L"Survival at low saturation deficit threshold:";
      // 
      // lblSatDefLowThreshold
      // 
      this->lblSatDefLowThreshold->AutoSize = true;
      this->lblSatDefLowThreshold->Location = System::Drawing::Point(6, 73);
      this->lblSatDefLowThreshold->Name = L"lblSatDefLowThreshold";
      this->lblSatDefLowThreshold->Size = System::Drawing::Size(156, 13);
      this->lblSatDefLowThreshold->TabIndex = 4;
      this->lblSatDefLowThreshold->Text = L"Low saturation deficit threshold:";
      // 
      // lblSatDefHighThreshold
      // 
      this->lblSatDefHighThreshold->AutoSize = true;
      this->lblSatDefHighThreshold->Location = System::Drawing::Point(6, 125);
      this->lblSatDefHighThreshold->Name = L"lblSatDefHighThreshold";
      this->lblSatDefHighThreshold->Size = System::Drawing::Size(158, 13);
      this->lblSatDefHighThreshold->TabIndex = 8;
      this->lblSatDefHighThreshold->Text = L"High saturation deficit threshold:";
      // 
      // lblHighSunExposureThrehsold
      // 
      this->lblHighSunExposureThrehsold->AutoSize = true;
      this->lblHighSunExposureThrehsold->Location = System::Drawing::Point(6, 21);
      this->lblHighSunExposureThrehsold->Name = L"lblHighSunExposureThrehsold";
      this->lblHighSunExposureThrehsold->Size = System::Drawing::Size(144, 13);
      this->lblHighSunExposureThrehsold->TabIndex = 0;
      this->lblHighSunExposureThrehsold->Text = L"High sun exposure threshold:";
      // 
      // gboxPredation
      // 
      this->gboxPredation->Controls->Add(this->lblPredHighSurvival);
      this->gboxPredation->Controls->Add(this->lblPredHighThreshold);
      this->gboxPredation->Controls->Add(this->snboxPredHighSurvival);
      this->gboxPredation->Controls->Add(this->lblPredLowSurvival);
      this->gboxPredation->Controls->Add(this->lblPredLowThreshold);
      this->gboxPredation->Controls->Add(this->snboxPredHighThreshold);
      this->gboxPredation->Controls->Add(this->snboxPredLowSurvival);
      this->gboxPredation->Controls->Add(this->snboxPredLowThreshold);
      this->gboxPredation->Location = System::Drawing::Point(3, 631);
      this->gboxPredation->Name = L"gboxPredation";
      this->gboxPredation->Size = System::Drawing::Size(374, 123);
      this->gboxPredation->TabIndex = 8;
      this->gboxPredation->TabStop = false;
      this->gboxPredation->Text = L"Survival vs. Predation";
      // 
      // lblPredHighSurvival
      // 
      this->lblPredHighSurvival->AutoSize = true;
      this->lblPredHighSurvival->Location = System::Drawing::Point(6, 99);
      this->lblPredHighSurvival->Name = L"lblPredHighSurvival";
      this->lblPredHighSurvival->Size = System::Drawing::Size(188, 13);
      this->lblPredHighSurvival->TabIndex = 6;
      this->lblPredHighSurvival->Text = L"Survival at high temperature threshold:";
      // 
      // lblPredHighThreshold
      // 
      this->lblPredHighThreshold->AutoSize = true;
      this->lblPredHighThreshold->Location = System::Drawing::Point(6, 73);
      this->lblPredHighThreshold->Name = L"lblPredHighThreshold";
      this->lblPredHighThreshold->Size = System::Drawing::Size(137, 13);
      this->lblPredHighThreshold->TabIndex = 4;
      this->lblPredHighThreshold->Text = L"High temperature threshold:";
      // 
      // snboxPredHighSurvival
      // 
      this->snboxPredHighSurvival->Location = System::Drawing::Point(274, 97);
      this->snboxPredHighSurvival->Name = L"snboxPredHighSurvival";
      this->snboxPredHighSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxPredHighSurvival->TabIndex = 7;
      this->snboxPredHighSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxPredHighSurvival->Value = L"";
      // 
      // lblPredLowSurvival
      // 
      this->lblPredLowSurvival->AutoSize = true;
      this->lblPredLowSurvival->Location = System::Drawing::Point(6, 47);
      this->lblPredLowSurvival->Name = L"lblPredLowSurvival";
      this->lblPredLowSurvival->Size = System::Drawing::Size(184, 13);
      this->lblPredLowSurvival->TabIndex = 2;
      this->lblPredLowSurvival->Text = L"Survival at low temperature threshold:";
      // 
      // lblPredLowThreshold
      // 
      this->lblPredLowThreshold->AutoSize = true;
      this->lblPredLowThreshold->Location = System::Drawing::Point(6, 21);
      this->lblPredLowThreshold->Name = L"lblPredLowThreshold";
      this->lblPredLowThreshold->Size = System::Drawing::Size(135, 13);
      this->lblPredLowThreshold->TabIndex = 0;
      this->lblPredLowThreshold->Text = L"Low temperature threshold:";
      // 
      // snboxPredHighThreshold
      // 
      this->snboxPredHighThreshold->Location = System::Drawing::Point(274, 71);
      this->snboxPredHighThreshold->Name = L"snboxPredHighThreshold";
      this->snboxPredHighThreshold->Size = System::Drawing::Size(80, 20);
      this->snboxPredHighThreshold->TabIndex = 5;
      this->snboxPredHighThreshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxPredHighThreshold->Value = L"";
      // 
      // snboxPredLowSurvival
      // 
      this->snboxPredLowSurvival->Location = System::Drawing::Point(274, 45);
      this->snboxPredLowSurvival->Name = L"snboxPredLowSurvival";
      this->snboxPredLowSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxPredLowSurvival->TabIndex = 3;
      this->snboxPredLowSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxPredLowSurvival->Value = L"";
      // 
      // snboxPredLowThreshold
      // 
      this->snboxPredLowThreshold->Location = System::Drawing::Point(274, 19);
      this->snboxPredLowThreshold->Name = L"snboxPredLowThreshold";
      this->snboxPredLowThreshold->Size = System::Drawing::Size(80, 20);
      this->snboxPredLowThreshold->TabIndex = 1;
      this->snboxPredLowThreshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxPredLowThreshold->Value = L"";
      // 
      // snboxNominalSurvival
      // 
      this->snboxNominalSurvival->Location = System::Drawing::Point(280, 11);
      this->snboxNominalSurvival->Name = L"snboxNominalSurvival";
      this->snboxNominalSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxNominalSurvival->TabIndex = 3;
      this->snboxNominalSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxNominalSurvival->Value = L"";
      // 
      // errproEgg
      // 
      this->errproEgg->BlinkRate = 100;
      this->errproEgg->ContainerControl = this;
      // 
      // errproTemperature
      // 
      this->errproTemperature->ContainerControl = this;
      // 
      // errproSaturationDeficit
      // 
      this->errproSaturationDeficit->ContainerControl = this;
      // 
      // errproPredation
      // 
      this->errproPredation->ContainerControl = this;
      // 
      // EggBiologyPanel
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->AutoScroll = true;
      this->Controls->Add(this->snboxNominalSurvival);
      this->Controls->Add(this->gboxSatDef);
      this->Controls->Add(this->gboxTemp);
      this->Controls->Add(this->gboxHatch);
      this->Controls->Add(this->gboxPredation);
      this->Controls->Add(this->gboxDev);
      this->Controls->Add(this->lblNominalSurvival);
      this->Name = L"EggBiologyPanel";
      this->Size = System::Drawing::Size(380, 758);
      this->Load += gcnew System::EventHandler(this, &EggBiologyPanel::OnLoad);
      this->gboxHatch->ResumeLayout(false);
      this->gboxHatch->PerformLayout();
      this->gboxDev->ResumeLayout(false);
      this->gboxDev->PerformLayout();
      this->gboxTemp->ResumeLayout(false);
      this->gboxTemp->PerformLayout();
      this->gboxSatDef->ResumeLayout(false);
      this->gboxSatDef->PerformLayout();
      this->gboxPredation->ResumeLayout(false);
      this->gboxPredation->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errproEgg))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errproTemperature))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errproSaturationDeficit))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errproPredation))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  };
}
