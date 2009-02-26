#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace gui {


  public ref class AdultBiologyPanel : public System::Windows::Forms::UserControl
	{
	public:
		AdultBiologyPanel( BindingSource ^ locationBinding );
	protected:
		~AdultBiologyPanel();

  private:
    System::Void OnLoad( System::Object ^ sender, System::EventArgs ^ e );

  private:
    BindingSource ^ LocationBinding;

  private: System::Windows::Forms::GroupBox^  gboxDev;
  private: System::Windows::Forms::Label^  lblTHALF;
  private: System::Windows::Forms::Label^  lblDHH;
  private: System::Windows::Forms::Label^  lblDHA;
  private: System::Windows::Forms::Label^  lblRO25;





  private: System::Windows::Forms::Label^  lblFecundityFactor;
  private: System::Windows::Forms::Label^  lblDryToWetWeightFactor;
  private: System::Windows::Forms::Label^  lblNominalSurvival;

  private: System::Windows::Forms::Label^  lblSecondDevelopmentThreshold;

  private: System::Windows::Forms::Label^  lblMinimumOvipositionTemperature;

  private: System::Windows::Forms::Label^  lblInterruptedFeedsPerMeal;










  private: System::Windows::Forms::GroupBox^  gboxTemp;
  private: System::Windows::Forms::Label^  lblTempHighLethalSurvival;
  private: System::Windows::Forms::Label^  lblTempLowLethalSurvival;
  private: System::Windows::Forms::Label^  lblTempHighThreshold;
  private: System::Windows::Forms::Label^  lblTempLowThreshold;
  private: System::Windows::Forms::Label^  lblTempHighLethalThreshold;
  private: System::Windows::Forms::Label^  lblTempLowLethalThreshold;







  private: System::Windows::Forms::GroupBox^  gboxSatDef;
  private: System::Windows::Forms::Label^  lblSatDefHighSurvival;
  private: System::Windows::Forms::Label^  lblSatDefLowSurvival;
  private: System::Windows::Forms::Label^  lblSatDefLowThreshold;
  private: System::Windows::Forms::Label^  lblSatDefHighThreshold;















  private: System::Windows::Forms::GroupBox^  gboxDBM;
  private: System::Windows::Forms::Label^  lblDoubleBloodMealHighWeightRatio;
  private: System::Windows::Forms::Label^  lblDoubleBloodMealLowWeightRatio;
  private: System::Windows::Forms::Label^  lblDoubleBloodMealLowWeightThreshold;
  private: System::Windows::Forms::Label^  lblDoubleBloodMealHighWeightThreshold;





  private: ctrl::ScientificNotationTextBox^  snboxSecondDevelopmentThreshold;
  private: ctrl::ScientificNotationTextBox^  snboxNominalSurvival;
  private: ctrl::ScientificNotationTextBox^  snboxDryToWetWeightFactor;
  private: ctrl::ScientificNotationTextBox^  snboxMinimumOvipositionTemperature;
  private: ctrl::ScientificNotationTextBox^  snboxFecundityFactor;
  private: ctrl::ScientificNotationTextBox^  snboxInterruptedFeedsPerMeal;
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
private: ctrl::ScientificNotationTextBox^  snboxSatDefHighSurvival;

private: ctrl::ScientificNotationTextBox^  snboxSatDefLowSurvival;
private: ctrl::ScientificNotationTextBox^  snboxSatDefHighThreshold;


private: ctrl::ScientificNotationTextBox^  snboxSatDefLowThreshold;




private: ctrl::ScientificNotationTextBox^  snboxDoubleBloodMealHighWeightRatio;

private: ctrl::ScientificNotationTextBox^  snboxDoubleBloodMealLowWeightRatio;
private: ctrl::ScientificNotationTextBox^  snboxDoubleBloodMealHighWeightLimit;


private: ctrl::ScientificNotationTextBox^  snboxDoubleBloodMealLowWeightLimit;
private: System::Windows::Forms::GroupBox^  gboxAgeSurvival;
private: ctrl::ScientificNotationTextBox^  snboxYoungSurvival;

private: System::Windows::Forms::Label^  label1;
private: ctrl::ScientificNotationTextBox^  snboxOldSurvival;

private: System::Windows::Forms::Label^  label2;
private: ctrl::ScientificNotationTextBox^  snboxCutoffAge;

private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::GroupBox^  groupBox1;


private: ctrl::ScientificNotationTextBox^  snboxFeedingProportionInterrupedDifferentHost;

private: ctrl::ScientificNotationTextBox^  snboxFeedingHumanProportion;



private: System::Windows::Forms::Label^  lblFeedingHumanProportion;
private: System::Windows::Forms::Label^  lblFeedingProportionInterrupedDifferentHost;















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
      this->lblFecundityFactor = (gcnew System::Windows::Forms::Label());
      this->lblDryToWetWeightFactor = (gcnew System::Windows::Forms::Label());
      this->lblNominalSurvival = (gcnew System::Windows::Forms::Label());
      this->lblSecondDevelopmentThreshold = (gcnew System::Windows::Forms::Label());
      this->lblMinimumOvipositionTemperature = (gcnew System::Windows::Forms::Label());
      this->lblInterruptedFeedsPerMeal = (gcnew System::Windows::Forms::Label());
      this->gboxSatDef = (gcnew System::Windows::Forms::GroupBox());
      this->snboxSatDefHighSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxSatDefLowSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->lblSatDefHighSurvival = (gcnew System::Windows::Forms::Label());
      this->snboxSatDefHighThreshold = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxSatDefLowThreshold = (gcnew ctrl::ScientificNotationTextBox());
      this->lblSatDefLowSurvival = (gcnew System::Windows::Forms::Label());
      this->lblSatDefLowThreshold = (gcnew System::Windows::Forms::Label());
      this->lblSatDefHighThreshold = (gcnew System::Windows::Forms::Label());
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
      this->gboxDBM = (gcnew System::Windows::Forms::GroupBox());
      this->snboxDoubleBloodMealHighWeightRatio = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxDoubleBloodMealLowWeightRatio = (gcnew ctrl::ScientificNotationTextBox());
      this->lblDoubleBloodMealHighWeightRatio = (gcnew System::Windows::Forms::Label());
      this->snboxDoubleBloodMealHighWeightLimit = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxDoubleBloodMealLowWeightLimit = (gcnew ctrl::ScientificNotationTextBox());
      this->lblDoubleBloodMealLowWeightRatio = (gcnew System::Windows::Forms::Label());
      this->lblDoubleBloodMealLowWeightThreshold = (gcnew System::Windows::Forms::Label());
      this->lblDoubleBloodMealHighWeightThreshold = (gcnew System::Windows::Forms::Label());
      this->snboxSecondDevelopmentThreshold = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxNominalSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxDryToWetWeightFactor = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxMinimumOvipositionTemperature = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxFecundityFactor = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxInterruptedFeedsPerMeal = (gcnew ctrl::ScientificNotationTextBox());
      this->gboxAgeSurvival = (gcnew System::Windows::Forms::GroupBox());
      this->snboxYoungSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->snboxOldSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->snboxCutoffAge = (gcnew ctrl::ScientificNotationTextBox());
      this->label3 = (gcnew System::Windows::Forms::Label());
      this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
      this->snboxFeedingProportionInterrupedDifferentHost = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxFeedingHumanProportion = (gcnew ctrl::ScientificNotationTextBox());
      this->lblFeedingHumanProportion = (gcnew System::Windows::Forms::Label());
      this->lblFeedingProportionInterrupedDifferentHost = (gcnew System::Windows::Forms::Label());
      this->gboxDev->SuspendLayout();
      this->gboxSatDef->SuspendLayout();
      this->gboxTemp->SuspendLayout();
      this->gboxDBM->SuspendLayout();
      this->gboxAgeSurvival->SuspendLayout();
      this->groupBox1->SuspendLayout();
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
      this->gboxDev->Location = System::Drawing::Point(0, 247);
      this->gboxDev->Name = L"gboxDev";
      this->gboxDev->Size = System::Drawing::Size(374, 123);
      this->gboxDev->TabIndex = 11;
      this->gboxDev->TabStop = false;
      this->gboxDev->Text = L"Daily Development";
      // 
      // snboxTHALF
      // 
      this->snboxTHALF->Location = System::Drawing::Point(277, 97);
      this->snboxTHALF->Name = L"snboxTHALF";
      this->snboxTHALF->Size = System::Drawing::Size(80, 20);
      this->snboxTHALF->TabIndex = 7;
      this->snboxTHALF->Text = L"0";
      this->snboxTHALF->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTHALF->Value = L"0";
      // 
      // snboxRO25
      // 
      this->snboxRO25->Location = System::Drawing::Point(277, 19);
      this->snboxRO25->Name = L"snboxRO25";
      this->snboxRO25->Size = System::Drawing::Size(80, 20);
      this->snboxRO25->TabIndex = 1;
      this->snboxRO25->Text = L"0";
      this->snboxRO25->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxRO25->Value = L"0";
      // 
      // snboxDHH
      // 
      this->snboxDHH->Location = System::Drawing::Point(277, 71);
      this->snboxDHH->Name = L"snboxDHH";
      this->snboxDHH->Size = System::Drawing::Size(80, 20);
      this->snboxDHH->TabIndex = 5;
      this->snboxDHH->Text = L"0";
      this->snboxDHH->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxDHH->Value = L"0";
      // 
      // snboxDHA
      // 
      this->snboxDHA->Location = System::Drawing::Point(277, 45);
      this->snboxDHA->Name = L"snboxDHA";
      this->snboxDHA->Size = System::Drawing::Size(80, 20);
      this->snboxDHA->TabIndex = 3;
      this->snboxDHA->Text = L"0";
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
      // lblFecundityFactor
      // 
      this->lblFecundityFactor->AutoSize = true;
      this->lblFecundityFactor->Location = System::Drawing::Point(9, 92);
      this->lblFecundityFactor->Name = L"lblFecundityFactor";
      this->lblFecundityFactor->Size = System::Drawing::Size(86, 13);
      this->lblFecundityFactor->TabIndex = 6;
      this->lblFecundityFactor->Text = L"Fecundity factor:";
      // 
      // lblDryToWetWeightFactor
      // 
      this->lblDryToWetWeightFactor->AutoSize = true;
      this->lblDryToWetWeightFactor->Location = System::Drawing::Point(9, 66);
      this->lblDryToWetWeightFactor->Name = L"lblDryToWetWeightFactor";
      this->lblDryToWetWeightFactor->Size = System::Drawing::Size(122, 13);
      this->lblDryToWetWeightFactor->TabIndex = 4;
      this->lblDryToWetWeightFactor->Text = L"Dry to wet weight factor:";
      // 
      // lblNominalSurvival
      // 
      this->lblNominalSurvival->AutoSize = true;
      this->lblNominalSurvival->Location = System::Drawing::Point(9, 40);
      this->lblNominalSurvival->Name = L"lblNominalSurvival";
      this->lblNominalSurvival->Size = System::Drawing::Size(87, 13);
      this->lblNominalSurvival->TabIndex = 2;
      this->lblNominalSurvival->Text = L"Nominal survival:";
      // 
      // lblSecondDevelopmentThreshold
      // 
      this->lblSecondDevelopmentThreshold->AutoSize = true;
      this->lblSecondDevelopmentThreshold->Location = System::Drawing::Point(9, 14);
      this->lblSecondDevelopmentThreshold->Name = L"lblSecondDevelopmentThreshold";
      this->lblSecondDevelopmentThreshold->Size = System::Drawing::Size(157, 13);
      this->lblSecondDevelopmentThreshold->TabIndex = 0;
      this->lblSecondDevelopmentThreshold->Text = L"Second development threshold:";
      // 
      // lblMinimumOvipositionTemperature
      // 
      this->lblMinimumOvipositionTemperature->AutoSize = true;
      this->lblMinimumOvipositionTemperature->Location = System::Drawing::Point(9, 118);
      this->lblMinimumOvipositionTemperature->Name = L"lblMinimumOvipositionTemperature";
      this->lblMinimumOvipositionTemperature->Size = System::Drawing::Size(163, 13);
      this->lblMinimumOvipositionTemperature->TabIndex = 8;
      this->lblMinimumOvipositionTemperature->Text = L"Minimum oviposition temperature:";
      // 
      // lblInterruptedFeedsPerMeal
      // 
      this->lblInterruptedFeedsPerMeal->AutoSize = true;
      this->lblInterruptedFeedsPerMeal->Location = System::Drawing::Point(6, 48);
      this->lblInterruptedFeedsPerMeal->Name = L"lblInterruptedFeedsPerMeal";
      this->lblInterruptedFeedsPerMeal->Size = System::Drawing::Size(130, 13);
      this->lblInterruptedFeedsPerMeal->TabIndex = 2;
      this->lblInterruptedFeedsPerMeal->Text = L"Interruped feeds per meal:";
      // 
      // gboxSatDef
      // 
      this->gboxSatDef->Controls->Add(this->snboxSatDefHighSurvival);
      this->gboxSatDef->Controls->Add(this->snboxSatDefLowSurvival);
      this->gboxSatDef->Controls->Add(this->lblSatDefHighSurvival);
      this->gboxSatDef->Controls->Add(this->snboxSatDefHighThreshold);
      this->gboxSatDef->Controls->Add(this->snboxSatDefLowThreshold);
      this->gboxSatDef->Controls->Add(this->lblSatDefLowSurvival);
      this->gboxSatDef->Controls->Add(this->lblSatDefLowThreshold);
      this->gboxSatDef->Controls->Add(this->lblSatDefHighThreshold);
      this->gboxSatDef->Location = System::Drawing::Point(0, 557);
      this->gboxSatDef->Name = L"gboxSatDef";
      this->gboxSatDef->Size = System::Drawing::Size(374, 123);
      this->gboxSatDef->TabIndex = 13;
      this->gboxSatDef->TabStop = false;
      this->gboxSatDef->Text = L"Survival vs. Saturation Deficit";
      // 
      // snboxSatDefHighSurvival
      // 
      this->snboxSatDefHighSurvival->Location = System::Drawing::Point(277, 97);
      this->snboxSatDefHighSurvival->Name = L"snboxSatDefHighSurvival";
      this->snboxSatDefHighSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxSatDefHighSurvival->TabIndex = 7;
      this->snboxSatDefHighSurvival->Text = L"0";
      this->snboxSatDefHighSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxSatDefHighSurvival->Value = L"0";
      // 
      // snboxSatDefLowSurvival
      // 
      this->snboxSatDefLowSurvival->Location = System::Drawing::Point(277, 45);
      this->snboxSatDefLowSurvival->Name = L"snboxSatDefLowSurvival";
      this->snboxSatDefLowSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxSatDefLowSurvival->TabIndex = 3;
      this->snboxSatDefLowSurvival->Text = L"0";
      this->snboxSatDefLowSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxSatDefLowSurvival->Value = L"0";
      // 
      // lblSatDefHighSurvival
      // 
      this->lblSatDefHighSurvival->AutoSize = true;
      this->lblSatDefHighSurvival->Location = System::Drawing::Point(6, 99);
      this->lblSatDefHighSurvival->Name = L"lblSatDefHighSurvival";
      this->lblSatDefHighSurvival->Size = System::Drawing::Size(254, 13);
      this->lblSatDefHighSurvival->TabIndex = 6;
      this->lblSatDefHighSurvival->Text = L"Survival at or above high saturation deficit threshold:";
      // 
      // snboxSatDefHighThreshold
      // 
      this->snboxSatDefHighThreshold->Location = System::Drawing::Point(277, 71);
      this->snboxSatDefHighThreshold->Name = L"snboxSatDefHighThreshold";
      this->snboxSatDefHighThreshold->Size = System::Drawing::Size(80, 20);
      this->snboxSatDefHighThreshold->TabIndex = 5;
      this->snboxSatDefHighThreshold->Text = L"0";
      this->snboxSatDefHighThreshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxSatDefHighThreshold->Value = L"0";
      // 
      // snboxSatDefLowThreshold
      // 
      this->snboxSatDefLowThreshold->Location = System::Drawing::Point(277, 19);
      this->snboxSatDefLowThreshold->Name = L"snboxSatDefLowThreshold";
      this->snboxSatDefLowThreshold->Size = System::Drawing::Size(80, 20);
      this->snboxSatDefLowThreshold->TabIndex = 1;
      this->snboxSatDefLowThreshold->Text = L"0";
      this->snboxSatDefLowThreshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxSatDefLowThreshold->Value = L"0";
      // 
      // lblSatDefLowSurvival
      // 
      this->lblSatDefLowSurvival->AutoSize = true;
      this->lblSatDefLowSurvival->Location = System::Drawing::Point(6, 47);
      this->lblSatDefLowSurvival->Name = L"lblSatDefLowSurvival";
      this->lblSatDefLowSurvival->Size = System::Drawing::Size(205, 13);
      this->lblSatDefLowSurvival->TabIndex = 2;
      this->lblSatDefLowSurvival->Text = L"Survival at low saturation deficit threshold:";
      // 
      // lblSatDefLowThreshold
      // 
      this->lblSatDefLowThreshold->AutoSize = true;
      this->lblSatDefLowThreshold->Location = System::Drawing::Point(6, 21);
      this->lblSatDefLowThreshold->Name = L"lblSatDefLowThreshold";
      this->lblSatDefLowThreshold->Size = System::Drawing::Size(156, 13);
      this->lblSatDefLowThreshold->TabIndex = 0;
      this->lblSatDefLowThreshold->Text = L"Low saturation deficit threshold:";
      // 
      // lblSatDefHighThreshold
      // 
      this->lblSatDefHighThreshold->AutoSize = true;
      this->lblSatDefHighThreshold->Location = System::Drawing::Point(6, 73);
      this->lblSatDefHighThreshold->Name = L"lblSatDefHighThreshold";
      this->lblSatDefHighThreshold->Size = System::Drawing::Size(158, 13);
      this->lblSatDefHighThreshold->TabIndex = 4;
      this->lblSatDefHighThreshold->Text = L"High saturation deficit threshold:";
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
      this->gboxTemp->Location = System::Drawing::Point(0, 376);
      this->gboxTemp->Name = L"gboxTemp";
      this->gboxTemp->Size = System::Drawing::Size(374, 175);
      this->gboxTemp->TabIndex = 12;
      this->gboxTemp->TabStop = false;
      this->gboxTemp->Text = L"Survival vs. Temperature";
      // 
      // snboxTempHighLethalSurvival
      // 
      this->snboxTempHighLethalSurvival->Location = System::Drawing::Point(277, 149);
      this->snboxTempHighLethalSurvival->Name = L"snboxTempHighLethalSurvival";
      this->snboxTempHighLethalSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxTempHighLethalSurvival->TabIndex = 11;
      this->snboxTempHighLethalSurvival->Text = L"0";
      this->snboxTempHighLethalSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTempHighLethalSurvival->Value = L"0";
      // 
      // snboxTempHighThreshold
      // 
      this->snboxTempHighThreshold->Location = System::Drawing::Point(277, 97);
      this->snboxTempHighThreshold->Name = L"snboxTempHighThreshold";
      this->snboxTempHighThreshold->Size = System::Drawing::Size(80, 20);
      this->snboxTempHighThreshold->TabIndex = 7;
      this->snboxTempHighThreshold->Text = L"0";
      this->snboxTempHighThreshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTempHighThreshold->Value = L"0";
      // 
      // snboxTempLowLethalSurvival
      // 
      this->snboxTempLowLethalSurvival->Location = System::Drawing::Point(277, 45);
      this->snboxTempLowLethalSurvival->Name = L"snboxTempLowLethalSurvival";
      this->snboxTempLowLethalSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxTempLowLethalSurvival->TabIndex = 3;
      this->snboxTempLowLethalSurvival->Text = L"0";
      this->snboxTempLowLethalSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTempLowLethalSurvival->Value = L"0";
      // 
      // snboxTempHighLethalThreshold
      // 
      this->snboxTempHighLethalThreshold->Location = System::Drawing::Point(277, 123);
      this->snboxTempHighLethalThreshold->Name = L"snboxTempHighLethalThreshold";
      this->snboxTempHighLethalThreshold->Size = System::Drawing::Size(80, 20);
      this->snboxTempHighLethalThreshold->TabIndex = 9;
      this->snboxTempHighLethalThreshold->Text = L"0";
      this->snboxTempHighLethalThreshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTempHighLethalThreshold->Value = L"0";
      // 
      // snboxTempLowThreshold
      // 
      this->snboxTempLowThreshold->Location = System::Drawing::Point(277, 71);
      this->snboxTempLowThreshold->Name = L"snboxTempLowThreshold";
      this->snboxTempLowThreshold->Size = System::Drawing::Size(80, 20);
      this->snboxTempLowThreshold->TabIndex = 5;
      this->snboxTempLowThreshold->Text = L"0";
      this->snboxTempLowThreshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxTempLowThreshold->Value = L"0";
      // 
      // snboxTempLowLethalThreshold
      // 
      this->snboxTempLowLethalThreshold->Location = System::Drawing::Point(277, 19);
      this->snboxTempLowLethalThreshold->Name = L"snboxTempLowLethalThreshold";
      this->snboxTempLowLethalThreshold->Size = System::Drawing::Size(80, 20);
      this->snboxTempLowLethalThreshold->TabIndex = 1;
      this->snboxTempLowLethalThreshold->Text = L"0";
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
      // gboxDBM
      // 
      this->gboxDBM->Controls->Add(this->snboxDoubleBloodMealHighWeightRatio);
      this->gboxDBM->Controls->Add(this->snboxDoubleBloodMealLowWeightRatio);
      this->gboxDBM->Controls->Add(this->lblDoubleBloodMealHighWeightRatio);
      this->gboxDBM->Controls->Add(this->snboxDoubleBloodMealHighWeightLimit);
      this->gboxDBM->Controls->Add(this->snboxDoubleBloodMealLowWeightLimit);
      this->gboxDBM->Controls->Add(this->lblDoubleBloodMealLowWeightRatio);
      this->gboxDBM->Controls->Add(this->lblDoubleBloodMealLowWeightThreshold);
      this->gboxDBM->Controls->Add(this->lblDoubleBloodMealHighWeightThreshold);
      this->gboxDBM->Location = System::Drawing::Point(0, 686);
      this->gboxDBM->Name = L"gboxDBM";
      this->gboxDBM->Size = System::Drawing::Size(374, 123);
      this->gboxDBM->TabIndex = 14;
      this->gboxDBM->TabStop = false;
      this->gboxDBM->Text = L"Double Blood Meals";
      // 
      // snboxDoubleBloodMealHighWeightRatio
      // 
      this->snboxDoubleBloodMealHighWeightRatio->Location = System::Drawing::Point(277, 97);
      this->snboxDoubleBloodMealHighWeightRatio->Name = L"snboxDoubleBloodMealHighWeightRatio";
      this->snboxDoubleBloodMealHighWeightRatio->Size = System::Drawing::Size(80, 20);
      this->snboxDoubleBloodMealHighWeightRatio->TabIndex = 7;
      this->snboxDoubleBloodMealHighWeightRatio->Text = L"0";
      this->snboxDoubleBloodMealHighWeightRatio->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxDoubleBloodMealHighWeightRatio->Value = L"0";
      // 
      // snboxDoubleBloodMealLowWeightRatio
      // 
      this->snboxDoubleBloodMealLowWeightRatio->Location = System::Drawing::Point(277, 45);
      this->snboxDoubleBloodMealLowWeightRatio->Name = L"snboxDoubleBloodMealLowWeightRatio";
      this->snboxDoubleBloodMealLowWeightRatio->Size = System::Drawing::Size(80, 20);
      this->snboxDoubleBloodMealLowWeightRatio->TabIndex = 3;
      this->snboxDoubleBloodMealLowWeightRatio->Text = L"0";
      this->snboxDoubleBloodMealLowWeightRatio->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxDoubleBloodMealLowWeightRatio->Value = L"0";
      // 
      // lblDoubleBloodMealHighWeightRatio
      // 
      this->lblDoubleBloodMealHighWeightRatio->AutoSize = true;
      this->lblDoubleBloodMealHighWeightRatio->Location = System::Drawing::Point(6, 99);
      this->lblDoubleBloodMealHighWeightRatio->Name = L"lblDoubleBloodMealHighWeightRatio";
      this->lblDoubleBloodMealHighWeightRatio->Size = System::Drawing::Size(172, 13);
      this->lblDoubleBloodMealHighWeightRatio->TabIndex = 6;
      this->lblDoubleBloodMealHighWeightRatio->Text = L"DBM ratio at high weight threshold:";
      // 
      // snboxDoubleBloodMealHighWeightLimit
      // 
      this->snboxDoubleBloodMealHighWeightLimit->Location = System::Drawing::Point(277, 71);
      this->snboxDoubleBloodMealHighWeightLimit->Name = L"snboxDoubleBloodMealHighWeightLimit";
      this->snboxDoubleBloodMealHighWeightLimit->Size = System::Drawing::Size(80, 20);
      this->snboxDoubleBloodMealHighWeightLimit->TabIndex = 5;
      this->snboxDoubleBloodMealHighWeightLimit->Text = L"0";
      this->snboxDoubleBloodMealHighWeightLimit->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxDoubleBloodMealHighWeightLimit->Value = L"0";
      // 
      // snboxDoubleBloodMealLowWeightLimit
      // 
      this->snboxDoubleBloodMealLowWeightLimit->Location = System::Drawing::Point(277, 19);
      this->snboxDoubleBloodMealLowWeightLimit->Name = L"snboxDoubleBloodMealLowWeightLimit";
      this->snboxDoubleBloodMealLowWeightLimit->Size = System::Drawing::Size(80, 20);
      this->snboxDoubleBloodMealLowWeightLimit->TabIndex = 1;
      this->snboxDoubleBloodMealLowWeightLimit->Text = L"0";
      this->snboxDoubleBloodMealLowWeightLimit->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxDoubleBloodMealLowWeightLimit->Value = L"0";
      // 
      // lblDoubleBloodMealLowWeightRatio
      // 
      this->lblDoubleBloodMealLowWeightRatio->AutoSize = true;
      this->lblDoubleBloodMealLowWeightRatio->Location = System::Drawing::Point(6, 47);
      this->lblDoubleBloodMealLowWeightRatio->Name = L"lblDoubleBloodMealLowWeightRatio";
      this->lblDoubleBloodMealLowWeightRatio->Size = System::Drawing::Size(168, 13);
      this->lblDoubleBloodMealLowWeightRatio->TabIndex = 2;
      this->lblDoubleBloodMealLowWeightRatio->Text = L"DBM ratio at low weight threshold:";
      // 
      // lblDoubleBloodMealLowWeightThreshold
      // 
      this->lblDoubleBloodMealLowWeightThreshold->AutoSize = true;
      this->lblDoubleBloodMealLowWeightThreshold->Location = System::Drawing::Point(6, 21);
      this->lblDoubleBloodMealLowWeightThreshold->Name = L"lblDoubleBloodMealLowWeightThreshold";
      this->lblDoubleBloodMealLowWeightThreshold->Size = System::Drawing::Size(110, 13);
      this->lblDoubleBloodMealLowWeightThreshold->TabIndex = 0;
      this->lblDoubleBloodMealLowWeightThreshold->Text = L"Low weight threshold:";
      // 
      // lblDoubleBloodMealHighWeightThreshold
      // 
      this->lblDoubleBloodMealHighWeightThreshold->AutoSize = true;
      this->lblDoubleBloodMealHighWeightThreshold->Location = System::Drawing::Point(6, 73);
      this->lblDoubleBloodMealHighWeightThreshold->Name = L"lblDoubleBloodMealHighWeightThreshold";
      this->lblDoubleBloodMealHighWeightThreshold->Size = System::Drawing::Size(112, 13);
      this->lblDoubleBloodMealHighWeightThreshold->TabIndex = 4;
      this->lblDoubleBloodMealHighWeightThreshold->Text = L"High weight threshold:";
      // 
      // snboxSecondDevelopmentThreshold
      // 
      this->snboxSecondDevelopmentThreshold->Location = System::Drawing::Point(280, 11);
      this->snboxSecondDevelopmentThreshold->Name = L"snboxSecondDevelopmentThreshold";
      this->snboxSecondDevelopmentThreshold->Size = System::Drawing::Size(80, 20);
      this->snboxSecondDevelopmentThreshold->TabIndex = 1;
      this->snboxSecondDevelopmentThreshold->Text = L"0";
      this->snboxSecondDevelopmentThreshold->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxSecondDevelopmentThreshold->Value = L"0";
      // 
      // snboxNominalSurvival
      // 
      this->snboxNominalSurvival->Location = System::Drawing::Point(280, 37);
      this->snboxNominalSurvival->Name = L"snboxNominalSurvival";
      this->snboxNominalSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxNominalSurvival->TabIndex = 3;
      this->snboxNominalSurvival->Text = L"0";
      this->snboxNominalSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxNominalSurvival->Value = L"0";
      // 
      // snboxDryToWetWeightFactor
      // 
      this->snboxDryToWetWeightFactor->Location = System::Drawing::Point(280, 63);
      this->snboxDryToWetWeightFactor->Name = L"snboxDryToWetWeightFactor";
      this->snboxDryToWetWeightFactor->Size = System::Drawing::Size(80, 20);
      this->snboxDryToWetWeightFactor->TabIndex = 5;
      this->snboxDryToWetWeightFactor->Text = L"0";
      this->snboxDryToWetWeightFactor->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxDryToWetWeightFactor->Value = L"0";
      // 
      // snboxMinimumOvipositionTemperature
      // 
      this->snboxMinimumOvipositionTemperature->Location = System::Drawing::Point(280, 115);
      this->snboxMinimumOvipositionTemperature->Name = L"snboxMinimumOvipositionTemperature";
      this->snboxMinimumOvipositionTemperature->Size = System::Drawing::Size(80, 20);
      this->snboxMinimumOvipositionTemperature->TabIndex = 9;
      this->snboxMinimumOvipositionTemperature->Text = L"0";
      this->snboxMinimumOvipositionTemperature->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxMinimumOvipositionTemperature->Value = L"0";
      // 
      // snboxFecundityFactor
      // 
      this->snboxFecundityFactor->Location = System::Drawing::Point(280, 89);
      this->snboxFecundityFactor->Name = L"snboxFecundityFactor";
      this->snboxFecundityFactor->Size = System::Drawing::Size(80, 20);
      this->snboxFecundityFactor->TabIndex = 7;
      this->snboxFecundityFactor->Text = L"0";
      this->snboxFecundityFactor->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxFecundityFactor->Value = L"0";
      // 
      // snboxInterruptedFeedsPerMeal
      // 
      this->snboxInterruptedFeedsPerMeal->Location = System::Drawing::Point(277, 45);
      this->snboxInterruptedFeedsPerMeal->Name = L"snboxInterruptedFeedsPerMeal";
      this->snboxInterruptedFeedsPerMeal->Size = System::Drawing::Size(80, 20);
      this->snboxInterruptedFeedsPerMeal->TabIndex = 3;
      this->snboxInterruptedFeedsPerMeal->Text = L"0";
      this->snboxInterruptedFeedsPerMeal->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxInterruptedFeedsPerMeal->Value = L"0";
      // 
      // gboxAgeSurvival
      // 
      this->gboxAgeSurvival->Controls->Add(this->snboxYoungSurvival);
      this->gboxAgeSurvival->Controls->Add(this->label1);
      this->gboxAgeSurvival->Controls->Add(this->snboxOldSurvival);
      this->gboxAgeSurvival->Controls->Add(this->label2);
      this->gboxAgeSurvival->Controls->Add(this->snboxCutoffAge);
      this->gboxAgeSurvival->Controls->Add(this->label3);
      this->gboxAgeSurvival->Location = System::Drawing::Point(0, 141);
      this->gboxAgeSurvival->Name = L"gboxAgeSurvival";
      this->gboxAgeSurvival->Size = System::Drawing::Size(373, 100);
      this->gboxAgeSurvival->TabIndex = 10;
      this->gboxAgeSurvival->TabStop = false;
      this->gboxAgeSurvival->Text = L"Age Dependent Survival";
      // 
      // snboxYoungSurvival
      // 
      this->snboxYoungSurvival->Location = System::Drawing::Point(280, 18);
      this->snboxYoungSurvival->Name = L"snboxYoungSurvival";
      this->snboxYoungSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxYoungSurvival->TabIndex = 1;
      this->snboxYoungSurvival->Text = L"0";
      this->snboxYoungSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxYoungSurvival->Value = L"0";
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Location = System::Drawing::Point(9, 21);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(125, 13);
      this->label1->TabIndex = 0;
      this->label1->Text = L"Young mosquito survival:";
      // 
      // snboxOldSurvival
      // 
      this->snboxOldSurvival->Location = System::Drawing::Point(280, 71);
      this->snboxOldSurvival->Name = L"snboxOldSurvival";
      this->snboxOldSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxOldSurvival->TabIndex = 5;
      this->snboxOldSurvival->Text = L"0";
      this->snboxOldSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxOldSurvival->Value = L"0";
      // 
      // label2
      // 
      this->label2->AutoSize = true;
      this->label2->Location = System::Drawing::Point(9, 74);
      this->label2->Name = L"label2";
      this->label2->Size = System::Drawing::Size(110, 13);
      this->label2->TabIndex = 2;
      this->label2->Text = L"Old mosquito survival:";
      // 
      // snboxCutoffAge
      // 
      this->snboxCutoffAge->Location = System::Drawing::Point(280, 45);
      this->snboxCutoffAge->Name = L"snboxCutoffAge";
      this->snboxCutoffAge->Size = System::Drawing::Size(80, 20);
      this->snboxCutoffAge->TabIndex = 3;
      this->snboxCutoffAge->Text = L"0";
      this->snboxCutoffAge->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxCutoffAge->Value = L"0";
      // 
      // label3
      // 
      this->label3->AutoSize = true;
      this->label3->Location = System::Drawing::Point(9, 48);
      this->label3->Name = L"label3";
      this->label3->Size = System::Drawing::Size(137, 13);
      this->label3->TabIndex = 4;
      this->label3->Text = L"Young mosquito cutoff age:";
      // 
      // groupBox1
      // 
      this->groupBox1->Controls->Add(this->snboxFeedingProportionInterrupedDifferentHost);
      this->groupBox1->Controls->Add(this->snboxInterruptedFeedsPerMeal);
      this->groupBox1->Controls->Add(this->snboxFeedingHumanProportion);
      this->groupBox1->Controls->Add(this->lblFeedingHumanProportion);
      this->groupBox1->Controls->Add(this->lblFeedingProportionInterrupedDifferentHost);
      this->groupBox1->Controls->Add(this->lblInterruptedFeedsPerMeal);
      this->groupBox1->Location = System::Drawing::Point(0, 815);
      this->groupBox1->Name = L"groupBox1";
      this->groupBox1->Size = System::Drawing::Size(374, 99);
      this->groupBox1->TabIndex = 15;
      this->groupBox1->TabStop = false;
      this->groupBox1->Text = L"Micellaneous Parameters";
      // 
      // snboxFeedingProportionInterrupedDifferentHost
      // 
      this->snboxFeedingProportionInterrupedDifferentHost->Location = System::Drawing::Point(277, 71);
      this->snboxFeedingProportionInterrupedDifferentHost->Name = L"snboxFeedingProportionInterrupedDifferentHost";
      this->snboxFeedingProportionInterrupedDifferentHost->Size = System::Drawing::Size(80, 20);
      this->snboxFeedingProportionInterrupedDifferentHost->TabIndex = 5;
      this->snboxFeedingProportionInterrupedDifferentHost->Text = L"0";
      this->snboxFeedingProportionInterrupedDifferentHost->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxFeedingProportionInterrupedDifferentHost->Value = L"0";
      // 
      // snboxFeedingHumanProportion
      // 
      this->snboxFeedingHumanProportion->Location = System::Drawing::Point(277, 19);
      this->snboxFeedingHumanProportion->Name = L"snboxFeedingHumanProportion";
      this->snboxFeedingHumanProportion->Size = System::Drawing::Size(80, 20);
      this->snboxFeedingHumanProportion->TabIndex = 1;
      this->snboxFeedingHumanProportion->Text = L"0";
      this->snboxFeedingHumanProportion->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxFeedingHumanProportion->Value = L"0";
      // 
      // lblFeedingHumanProportion
      // 
      this->lblFeedingHumanProportion->AutoSize = true;
      this->lblFeedingHumanProportion->Location = System::Drawing::Point(6, 21);
      this->lblFeedingHumanProportion->Name = L"lblFeedingHumanProportion";
      this->lblFeedingHumanProportion->Size = System::Drawing::Size(219, 13);
      this->lblFeedingHumanProportion->TabIndex = 0;
      this->lblFeedingHumanProportion->Text = L"Proportion of mosquitoes feeding on humans:";
      // 
      // lblFeedingProportionInterrupedDifferentHost
      // 
      this->lblFeedingProportionInterrupedDifferentHost->AutoSize = true;
      this->lblFeedingProportionInterrupedDifferentHost->Location = System::Drawing::Point(6, 73);
      this->lblFeedingProportionInterrupedDifferentHost->Name = L"lblFeedingProportionInterrupedDifferentHost";
      this->lblFeedingProportionInterrupedDifferentHost->Size = System::Drawing::Size(240, 13);
      this->lblFeedingProportionInterrupedDifferentHost->TabIndex = 4;
      this->lblFeedingProportionInterrupedDifferentHost->Text = L"Proportion of interrupted feeds on a different host:";
      // 
      // AdultBiologyPanel
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->Controls->Add(this->gboxAgeSurvival);
      this->Controls->Add(this->snboxDryToWetWeightFactor);
      this->Controls->Add(this->snboxFecundityFactor);
      this->Controls->Add(this->snboxMinimumOvipositionTemperature);
      this->Controls->Add(this->snboxSecondDevelopmentThreshold);
      this->Controls->Add(this->snboxNominalSurvival);
      this->Controls->Add(this->groupBox1);
      this->Controls->Add(this->gboxDBM);
      this->Controls->Add(this->gboxSatDef);
      this->Controls->Add(this->gboxTemp);
      this->Controls->Add(this->gboxDev);
      this->Controls->Add(this->lblFecundityFactor);
      this->Controls->Add(this->lblDryToWetWeightFactor);
      this->Controls->Add(this->lblMinimumOvipositionTemperature);
      this->Controls->Add(this->lblSecondDevelopmentThreshold);
      this->Controls->Add(this->lblNominalSurvival);
      this->Name = L"AdultBiologyPanel";
      this->Size = System::Drawing::Size(380, 917);
      this->Load += gcnew System::EventHandler(this, &AdultBiologyPanel::OnLoad);
      this->gboxDev->ResumeLayout(false);
      this->gboxDev->PerformLayout();
      this->gboxSatDef->ResumeLayout(false);
      this->gboxSatDef->PerformLayout();
      this->gboxTemp->ResumeLayout(false);
      this->gboxTemp->PerformLayout();
      this->gboxDBM->ResumeLayout(false);
      this->gboxDBM->PerformLayout();
      this->gboxAgeSurvival->ResumeLayout(false);
      this->gboxAgeSurvival->PerformLayout();
      this->groupBox1->ResumeLayout(false);
      this->groupBox1->PerformLayout();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  };
}
