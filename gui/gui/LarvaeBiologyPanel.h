#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace gui {


  public ref class LarvaeBiologyPanel : public System::Windows::Forms::UserControl
	{
	public:
		LarvaeBiologyPanel( BindingSource ^ locationBinding );
	protected:
		~LarvaeBiologyPanel();

  private:
    System::Void OnLoad( System::Object ^ sender, System::EventArgs ^ e );

  private:
    BindingSource ^ LocationBinding;



  private: System::Windows::Forms::Label^  lblNominalSurvival;
  private: System::Windows::Forms::Label^  lblPupationSurvival;
  private: System::Windows::Forms::Label^  lblDryContainerSurvival;
  private: System::Windows::Forms::Label^  lblWeightAtHatch;
  private: System::Windows::Forms::Label^  lblMinimumWeightForSurvival;








  private: System::Windows::Forms::GroupBox^  gboxDev;
  private: System::Windows::Forms::Label^  lblTHALF;
  private: System::Windows::Forms::Label^  lblDHH;
  private: System::Windows::Forms::Label^  lblDHA;
  private: System::Windows::Forms::Label^  lblRO25;






  private: System::Windows::Forms::GroupBox^  gboxPupWt;
  private: System::Windows::Forms::Label^  lblPupWtSlope;
  private: System::Windows::Forms::Label^  lblPupWtIntercept;
  private: System::Windows::Forms::Label^  lblPupWtMinimumWeight;
  private: System::Windows::Forms::Label^  lblPupWtMinimumAge;





  private: System::Windows::Forms::GroupBox^  gboxTemp;


  private: System::Windows::Forms::Label^  lblTempHighLethalSurvival;
  private: System::Windows::Forms::Label^  lblTempLowLethalSurvival;


  private: System::Windows::Forms::Label^  lblTempHighThreshold;
  private: System::Windows::Forms::Label^  lblTempLowThreshold;

  private: System::Windows::Forms::Label^  lblTempHighLethalThreshold;

  private: System::Windows::Forms::Label^  lblTempLowLethalThreshold;

  private: System::Windows::Forms::GroupBox^  gboxFood;
  private: System::Windows::Forms::Label^  lblNumberEulerSteps;
  private: System::Windows::Forms::Label^  lblCadaverFoodRatio;
  private: System::Windows::Forms::Label^  lblAssimilationRate;
  private: System::Windows::Forms::Label^  lblExploitationRate;
  private: System::Windows::Forms::Label^  lblExploitationRateIndependence;
  private: System::Windows::Forms::Label^  lblMetabolicWeightLossRate;
  private: System::Windows::Forms::Label^  lblMetabolicWeightLossExponent;








  private: System::Windows::Forms::GroupBox^  gboxFasting;
  private: System::Windows::Forms::Label^  lblLipidReserveSurvival;
  private: System::Windows::Forms::Label^  lblNoLipidReserveSurvival;
  private: System::Windows::Forms::Label^  lblNonDepletableLipidReserve;
  private: System::Windows::Forms::Label^  lblWeightToLipidSlope;
  private: System::Windows::Forms::Label^  lblWeightToLipidConstant;





  private: System::Windows::Forms::CheckBox^  chkUseRandomFood;


  private: ctrl::ScientificNotationTextBox^  snboxNominalSurvival;
  private: ctrl::ScientificNotationTextBox^  snboxPupationSurvival;
  private: ctrl::ScientificNotationTextBox^  snboxDryContainerSurvival;
  private: ctrl::ScientificNotationTextBox^  snboxWeightAtHatch;
  private: ctrl::ScientificNotationTextBox^  snboxMinimumWeightForSurvival;
  private: ctrl::ScientificNotationTextBox^  snboxTHALF;

  private: ctrl::ScientificNotationTextBox^  snboxRO25;
  private: ctrl::ScientificNotationTextBox^  snboxDHH;


private: ctrl::ScientificNotationTextBox^  snboxDHA;
private: ctrl::ScientificNotationTextBox^  snboxPupWtMaximumDevelopment;

private: ctrl::ScientificNotationTextBox^  snboxPupWtSlope;
private: ctrl::ScientificNotationTextBox^  snboxPupWtMinimumWeight;
private: ctrl::ScientificNotationTextBox^  snboxPupWtIntercept;
private: ctrl::ScientificNotationTextBox^  snboxTempHighLethalSurvival;
private: ctrl::ScientificNotationTextBox^  snboxTempHighThreshold;
private: ctrl::ScientificNotationTextBox^  snboxTempLowLethalSurvival;
private: ctrl::ScientificNotationTextBox^  snboxTempHighLethalThreshold;
private: ctrl::ScientificNotationTextBox^  snboxTempLowThreshold;
private: ctrl::ScientificNotationTextBox^  snboxTempLowLethalThreshold;













private: ctrl::ScientificNotationTextBox^  snboxMetabolicWeightLossExponent;

private: ctrl::ScientificNotationTextBox^  snboxMetabolicWeightLossRate;

private: ctrl::ScientificNotationTextBox^  snboxExploitationRate;

private: ctrl::ScientificNotationTextBox^  snboxCadaverFoodRatio;
private: ctrl::ScientificNotationTextBox^  snboxExploitationRateIndependence;


private: ctrl::ScientificNotationTextBox^  snboxAssimilationRate;

private: ctrl::ScientificNotationTextBox^  snboxNumberEulerSteps;
private: ctrl::ScientificNotationTextBox^  snboxWeightToLipidConstant;

private: ctrl::ScientificNotationTextBox^  snboxWeightToLipidSlope;

private: ctrl::ScientificNotationTextBox^  snboxNoLipidReserveSurvival;
private: ctrl::ScientificNotationTextBox^  snboxNonDepletableLipidReserve;
private: ctrl::ScientificNotationTextBox^  snboxLipidReserveSurvival;
private: System::Windows::Forms::ErrorProvider^  errproLarvae;
private: System::Windows::Forms::ErrorProvider^  errproTemperature;
private: System::Windows::Forms::ErrorProvider^  errproPupationWeight;
private: System::Windows::Forms::ErrorProvider^  errproFood;
private: System::Windows::Forms::ErrorProvider^  errproFasting;
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
      this->gboxDev = (gcnew System::Windows::Forms::GroupBox());
      this->snboxTHALF = (gcnew ctrl::ScientificNotationTextBox());
      this->lblTHALF = (gcnew System::Windows::Forms::Label());
      this->snboxRO25 = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxDHH = (gcnew ctrl::ScientificNotationTextBox());
      this->lblDHH = (gcnew System::Windows::Forms::Label());
      this->lblDHA = (gcnew System::Windows::Forms::Label());
      this->snboxDHA = (gcnew ctrl::ScientificNotationTextBox());
      this->lblRO25 = (gcnew System::Windows::Forms::Label());
      this->lblNominalSurvival = (gcnew System::Windows::Forms::Label());
      this->lblPupationSurvival = (gcnew System::Windows::Forms::Label());
      this->lblDryContainerSurvival = (gcnew System::Windows::Forms::Label());
      this->lblMinimumWeightForSurvival = (gcnew System::Windows::Forms::Label());
      this->gboxPupWt = (gcnew System::Windows::Forms::GroupBox());
      this->snboxPupWtMaximumDevelopment = (gcnew ctrl::ScientificNotationTextBox());
      this->lblPupWtMinimumAge = (gcnew System::Windows::Forms::Label());
      this->lblPupWtMinimumWeight = (gcnew System::Windows::Forms::Label());
      this->snboxPupWtSlope = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxPupWtMinimumWeight = (gcnew ctrl::ScientificNotationTextBox());
      this->lblPupWtIntercept = (gcnew System::Windows::Forms::Label());
      this->lblPupWtSlope = (gcnew System::Windows::Forms::Label());
      this->snboxPupWtIntercept = (gcnew ctrl::ScientificNotationTextBox());
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
      this->gboxFood = (gcnew System::Windows::Forms::GroupBox());
      this->snboxMetabolicWeightLossExponent = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxMetabolicWeightLossRate = (gcnew ctrl::ScientificNotationTextBox());
      this->chkUseRandomFood = (gcnew System::Windows::Forms::CheckBox());
      this->snboxExploitationRate = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxCadaverFoodRatio = (gcnew ctrl::ScientificNotationTextBox());
      this->lblExploitationRate = (gcnew System::Windows::Forms::Label());
      this->snboxExploitationRateIndependence = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxAssimilationRate = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxNumberEulerSteps = (gcnew ctrl::ScientificNotationTextBox());
      this->lblMetabolicWeightLossRate = (gcnew System::Windows::Forms::Label());
      this->lblExploitationRateIndependence = (gcnew System::Windows::Forms::Label());
      this->lblMetabolicWeightLossExponent = (gcnew System::Windows::Forms::Label());
      this->lblNumberEulerSteps = (gcnew System::Windows::Forms::Label());
      this->lblCadaverFoodRatio = (gcnew System::Windows::Forms::Label());
      this->lblAssimilationRate = (gcnew System::Windows::Forms::Label());
      this->gboxFasting = (gcnew System::Windows::Forms::GroupBox());
      this->snboxWeightToLipidConstant = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxWeightToLipidSlope = (gcnew ctrl::ScientificNotationTextBox());
      this->lblNoLipidReserveSurvival = (gcnew System::Windows::Forms::Label());
      this->snboxNoLipidReserveSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->lblWeightToLipidSlope = (gcnew System::Windows::Forms::Label());
      this->lblNonDepletableLipidReserve = (gcnew System::Windows::Forms::Label());
      this->snboxNonDepletableLipidReserve = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxLipidReserveSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->lblWeightToLipidConstant = (gcnew System::Windows::Forms::Label());
      this->lblLipidReserveSurvival = (gcnew System::Windows::Forms::Label());
      this->lblWeightAtHatch = (gcnew System::Windows::Forms::Label());
      this->snboxNominalSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxPupationSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxDryContainerSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxWeightAtHatch = (gcnew ctrl::ScientificNotationTextBox());
      this->snboxMinimumWeightForSurvival = (gcnew ctrl::ScientificNotationTextBox());
      this->errproLarvae = (gcnew System::Windows::Forms::ErrorProvider(this->components));
      this->errproTemperature = (gcnew System::Windows::Forms::ErrorProvider(this->components));
      this->errproPupationWeight = (gcnew System::Windows::Forms::ErrorProvider(this->components));
      this->errproFood = (gcnew System::Windows::Forms::ErrorProvider(this->components));
      this->errproFasting = (gcnew System::Windows::Forms::ErrorProvider(this->components));
      this->gboxDev->SuspendLayout();
      this->gboxPupWt->SuspendLayout();
      this->gboxTemp->SuspendLayout();
      this->gboxFood->SuspendLayout();
      this->gboxFasting->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errproLarvae))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errproTemperature))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errproPupationWeight))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errproFood))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errproFasting))->BeginInit();
      this->SuspendLayout();
      // 
      // gboxDev
      // 
      this->gboxDev->Controls->Add(this->snboxTHALF);
      this->gboxDev->Controls->Add(this->lblTHALF);
      this->gboxDev->Controls->Add(this->snboxRO25);
      this->gboxDev->Controls->Add(this->snboxDHH);
      this->gboxDev->Controls->Add(this->lblDHH);
      this->gboxDev->Controls->Add(this->lblDHA);
      this->gboxDev->Controls->Add(this->snboxDHA);
      this->gboxDev->Controls->Add(this->lblRO25);
      this->gboxDev->Location = System::Drawing::Point(3, 141);
      this->gboxDev->Name = L"gboxDev";
      this->gboxDev->Size = System::Drawing::Size(374, 123);
      this->gboxDev->TabIndex = 14;
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
      // lblTHALF
      // 
      this->lblTHALF->AutoSize = true;
      this->lblTHALF->Location = System::Drawing::Point(6, 99);
      this->lblTHALF->Name = L"lblTHALF";
      this->lblTHALF->Size = System::Drawing::Size(139, 13);
      this->lblTHALF->TabIndex = 6;
      this->lblTHALF->Text = L"Temperature of inactivation:";
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
      this->lblNominalSurvival->TabIndex = 4;
      this->lblNominalSurvival->Text = L"Nominal survival:";
      // 
      // lblPupationSurvival
      // 
      this->lblPupationSurvival->AutoSize = true;
      this->lblPupationSurvival->Location = System::Drawing::Point(9, 40);
      this->lblPupationSurvival->Name = L"lblPupationSurvival";
      this->lblPupationSurvival->Size = System::Drawing::Size(91, 13);
      this->lblPupationSurvival->TabIndex = 6;
      this->lblPupationSurvival->Text = L"Pupation survival:";
      // 
      // lblDryContainerSurvival
      // 
      this->lblDryContainerSurvival->AutoSize = true;
      this->lblDryContainerSurvival->Location = System::Drawing::Point(9, 66);
      this->lblDryContainerSurvival->Name = L"lblDryContainerSurvival";
      this->lblDryContainerSurvival->Size = System::Drawing::Size(112, 13);
      this->lblDryContainerSurvival->TabIndex = 8;
      this->lblDryContainerSurvival->Text = L"Dry container survival:";
      // 
      // lblMinimumWeightForSurvival
      // 
      this->lblMinimumWeightForSurvival->AutoSize = true;
      this->lblMinimumWeightForSurvival->Location = System::Drawing::Point(9, 118);
      this->lblMinimumWeightForSurvival->Name = L"lblMinimumWeightForSurvival";
      this->lblMinimumWeightForSurvival->Size = System::Drawing::Size(139, 13);
      this->lblMinimumWeightForSurvival->TabIndex = 12;
      this->lblMinimumWeightForSurvival->Text = L"Minimum weight for survival:";
      // 
      // gboxPupWt
      // 
      this->gboxPupWt->Controls->Add(this->snboxPupWtMaximumDevelopment);
      this->gboxPupWt->Controls->Add(this->lblPupWtMinimumAge);
      this->gboxPupWt->Controls->Add(this->lblPupWtMinimumWeight);
      this->gboxPupWt->Controls->Add(this->snboxPupWtSlope);
      this->gboxPupWt->Controls->Add(this->snboxPupWtMinimumWeight);
      this->gboxPupWt->Controls->Add(this->lblPupWtIntercept);
      this->gboxPupWt->Controls->Add(this->lblPupWtSlope);
      this->gboxPupWt->Controls->Add(this->snboxPupWtIntercept);
      this->gboxPupWt->Location = System::Drawing::Point(3, 270);
      this->gboxPupWt->Name = L"gboxPupWt";
      this->gboxPupWt->Size = System::Drawing::Size(374, 123);
      this->gboxPupWt->TabIndex = 15;
      this->gboxPupWt->TabStop = false;
      this->gboxPupWt->Text = L"Pupation Weight";
      // 
      // snboxPupWtMaximumDevelopment
      // 
      this->snboxPupWtMaximumDevelopment->Location = System::Drawing::Point(277, 97);
      this->snboxPupWtMaximumDevelopment->Name = L"snboxPupWtMaximumDevelopment";
      this->snboxPupWtMaximumDevelopment->Size = System::Drawing::Size(80, 20);
      this->snboxPupWtMaximumDevelopment->TabIndex = 7;
      this->snboxPupWtMaximumDevelopment->Text = L"0";
      this->snboxPupWtMaximumDevelopment->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxPupWtMaximumDevelopment->Value = L"0";
      // 
      // lblPupWtMinimumAge
      // 
      this->lblPupWtMinimumAge->AutoSize = true;
      this->lblPupWtMinimumAge->Location = System::Drawing::Point(6, 99);
      this->lblPupWtMinimumAge->Name = L"lblPupWtMinimumAge";
      this->lblPupWtMinimumAge->Size = System::Drawing::Size(118, 13);
      this->lblPupWtMinimumAge->TabIndex = 6;
      this->lblPupWtMinimumAge->Text = L"Maximum development:";
      // 
      // lblPupWtMinimumWeight
      // 
      this->lblPupWtMinimumWeight->AutoSize = true;
      this->lblPupWtMinimumWeight->Location = System::Drawing::Point(6, 73);
      this->lblPupWtMinimumWeight->Name = L"lblPupWtMinimumWeight";
      this->lblPupWtMinimumWeight->Size = System::Drawing::Size(144, 13);
      this->lblPupWtMinimumWeight->TabIndex = 4;
      this->lblPupWtMinimumWeight->Text = L"Minimum weight for pupation:";
      // 
      // snboxPupWtSlope
      // 
      this->snboxPupWtSlope->Location = System::Drawing::Point(277, 19);
      this->snboxPupWtSlope->Name = L"snboxPupWtSlope";
      this->snboxPupWtSlope->Size = System::Drawing::Size(80, 20);
      this->snboxPupWtSlope->TabIndex = 1;
      this->snboxPupWtSlope->Text = L"0";
      this->snboxPupWtSlope->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxPupWtSlope->Value = L"0";
      // 
      // snboxPupWtMinimumWeight
      // 
      this->snboxPupWtMinimumWeight->Location = System::Drawing::Point(277, 71);
      this->snboxPupWtMinimumWeight->Name = L"snboxPupWtMinimumWeight";
      this->snboxPupWtMinimumWeight->Size = System::Drawing::Size(80, 20);
      this->snboxPupWtMinimumWeight->TabIndex = 5;
      this->snboxPupWtMinimumWeight->Text = L"0";
      this->snboxPupWtMinimumWeight->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxPupWtMinimumWeight->Value = L"0";
      // 
      // lblPupWtIntercept
      // 
      this->lblPupWtIntercept->AutoSize = true;
      this->lblPupWtIntercept->Location = System::Drawing::Point(6, 47);
      this->lblPupWtIntercept->Name = L"lblPupWtIntercept";
      this->lblPupWtIntercept->Size = System::Drawing::Size(52, 13);
      this->lblPupWtIntercept->TabIndex = 2;
      this->lblPupWtIntercept->Text = L"Intercept:";
      // 
      // lblPupWtSlope
      // 
      this->lblPupWtSlope->AutoSize = true;
      this->lblPupWtSlope->Location = System::Drawing::Point(6, 21);
      this->lblPupWtSlope->Name = L"lblPupWtSlope";
      this->lblPupWtSlope->Size = System::Drawing::Size(37, 13);
      this->lblPupWtSlope->TabIndex = 0;
      this->lblPupWtSlope->Text = L"Slope:";
      // 
      // snboxPupWtIntercept
      // 
      this->snboxPupWtIntercept->Location = System::Drawing::Point(277, 45);
      this->snboxPupWtIntercept->Name = L"snboxPupWtIntercept";
      this->snboxPupWtIntercept->Size = System::Drawing::Size(80, 20);
      this->snboxPupWtIntercept->TabIndex = 3;
      this->snboxPupWtIntercept->Text = L"0";
      this->snboxPupWtIntercept->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxPupWtIntercept->Value = L"0";
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
      this->gboxTemp->Location = System::Drawing::Point(3, 399);
      this->gboxTemp->Name = L"gboxTemp";
      this->gboxTemp->Size = System::Drawing::Size(374, 175);
      this->gboxTemp->TabIndex = 16;
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
      // gboxFood
      // 
      this->gboxFood->Controls->Add(this->snboxMetabolicWeightLossExponent);
      this->gboxFood->Controls->Add(this->snboxMetabolicWeightLossRate);
      this->gboxFood->Controls->Add(this->chkUseRandomFood);
      this->gboxFood->Controls->Add(this->snboxExploitationRate);
      this->gboxFood->Controls->Add(this->snboxCadaverFoodRatio);
      this->gboxFood->Controls->Add(this->lblExploitationRate);
      this->gboxFood->Controls->Add(this->snboxExploitationRateIndependence);
      this->gboxFood->Controls->Add(this->snboxAssimilationRate);
      this->gboxFood->Controls->Add(this->snboxNumberEulerSteps);
      this->gboxFood->Controls->Add(this->lblMetabolicWeightLossRate);
      this->gboxFood->Controls->Add(this->lblExploitationRateIndependence);
      this->gboxFood->Controls->Add(this->lblMetabolicWeightLossExponent);
      this->gboxFood->Controls->Add(this->lblNumberEulerSteps);
      this->gboxFood->Controls->Add(this->lblCadaverFoodRatio);
      this->gboxFood->Controls->Add(this->lblAssimilationRate);
      this->gboxFood->Location = System::Drawing::Point(3, 580);
      this->gboxFood->Name = L"gboxFood";
      this->gboxFood->Size = System::Drawing::Size(374, 228);
      this->gboxFood->TabIndex = 18;
      this->gboxFood->TabStop = false;
      this->gboxFood->Text = L"Food";
      // 
      // snboxMetabolicWeightLossExponent
      // 
      this->snboxMetabolicWeightLossExponent->Location = System::Drawing::Point(277, 201);
      this->snboxMetabolicWeightLossExponent->Name = L"snboxMetabolicWeightLossExponent";
      this->snboxMetabolicWeightLossExponent->Size = System::Drawing::Size(80, 20);
      this->snboxMetabolicWeightLossExponent->TabIndex = 14;
      this->snboxMetabolicWeightLossExponent->Text = L"0";
      this->snboxMetabolicWeightLossExponent->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxMetabolicWeightLossExponent->Value = L"0";
      // 
      // snboxMetabolicWeightLossRate
      // 
      this->snboxMetabolicWeightLossRate->Location = System::Drawing::Point(277, 175);
      this->snboxMetabolicWeightLossRate->Name = L"snboxMetabolicWeightLossRate";
      this->snboxMetabolicWeightLossRate->Size = System::Drawing::Size(80, 20);
      this->snboxMetabolicWeightLossRate->TabIndex = 12;
      this->snboxMetabolicWeightLossRate->Text = L"0";
      this->snboxMetabolicWeightLossRate->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxMetabolicWeightLossRate->Value = L"0";
      // 
      // chkUseRandomFood
      // 
      this->chkUseRandomFood->AutoSize = true;
      this->chkUseRandomFood->Location = System::Drawing::Point(9, 19);
      this->chkUseRandomFood->Name = L"chkUseRandomFood";
      this->chkUseRandomFood->Size = System::Drawing::Size(129, 17);
      this->chkUseRandomFood->TabIndex = 0;
      this->chkUseRandomFood->Text = L"Random food delivery";
      this->chkUseRandomFood->UseVisualStyleBackColor = true;
      // 
      // snboxExploitationRate
      // 
      this->snboxExploitationRate->Location = System::Drawing::Point(277, 123);
      this->snboxExploitationRate->Name = L"snboxExploitationRate";
      this->snboxExploitationRate->Size = System::Drawing::Size(80, 20);
      this->snboxExploitationRate->TabIndex = 8;
      this->snboxExploitationRate->Text = L"0";
      this->snboxExploitationRate->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxExploitationRate->Value = L"0";
      // 
      // snboxCadaverFoodRatio
      // 
      this->snboxCadaverFoodRatio->Location = System::Drawing::Point(277, 71);
      this->snboxCadaverFoodRatio->Name = L"snboxCadaverFoodRatio";
      this->snboxCadaverFoodRatio->Size = System::Drawing::Size(80, 20);
      this->snboxCadaverFoodRatio->TabIndex = 4;
      this->snboxCadaverFoodRatio->Text = L"0";
      this->snboxCadaverFoodRatio->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxCadaverFoodRatio->Value = L"0";
      // 
      // lblExploitationRate
      // 
      this->lblExploitationRate->AutoSize = true;
      this->lblExploitationRate->Location = System::Drawing::Point(6, 123);
      this->lblExploitationRate->Name = L"lblExploitationRate";
      this->lblExploitationRate->Size = System::Drawing::Size(85, 13);
      this->lblExploitationRate->TabIndex = 7;
      this->lblExploitationRate->Text = L"Exploitation rate:";
      // 
      // snboxExploitationRateIndependence
      // 
      this->snboxExploitationRateIndependence->Location = System::Drawing::Point(277, 149);
      this->snboxExploitationRateIndependence->Name = L"snboxExploitationRateIndependence";
      this->snboxExploitationRateIndependence->Size = System::Drawing::Size(80, 20);
      this->snboxExploitationRateIndependence->TabIndex = 10;
      this->snboxExploitationRateIndependence->Text = L"0";
      this->snboxExploitationRateIndependence->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxExploitationRateIndependence->Value = L"0";
      // 
      // snboxAssimilationRate
      // 
      this->snboxAssimilationRate->Location = System::Drawing::Point(277, 97);
      this->snboxAssimilationRate->Name = L"snboxAssimilationRate";
      this->snboxAssimilationRate->Size = System::Drawing::Size(80, 20);
      this->snboxAssimilationRate->TabIndex = 6;
      this->snboxAssimilationRate->Text = L"0";
      this->snboxAssimilationRate->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxAssimilationRate->Value = L"0";
      // 
      // snboxNumberEulerSteps
      // 
      this->snboxNumberEulerSteps->Location = System::Drawing::Point(277, 45);
      this->snboxNumberEulerSteps->Name = L"snboxNumberEulerSteps";
      this->snboxNumberEulerSteps->Size = System::Drawing::Size(80, 20);
      this->snboxNumberEulerSteps->TabIndex = 2;
      this->snboxNumberEulerSteps->Text = L"0";
      this->snboxNumberEulerSteps->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxNumberEulerSteps->Value = L"0";
      // 
      // lblMetabolicWeightLossRate
      // 
      this->lblMetabolicWeightLossRate->AutoSize = true;
      this->lblMetabolicWeightLossRate->Location = System::Drawing::Point(6, 175);
      this->lblMetabolicWeightLossRate->Name = L"lblMetabolicWeightLossRate";
      this->lblMetabolicWeightLossRate->Size = System::Drawing::Size(132, 13);
      this->lblMetabolicWeightLossRate->TabIndex = 11;
      this->lblMetabolicWeightLossRate->Text = L"Metabolic weight loss rate:";
      // 
      // lblExploitationRateIndependence
      // 
      this->lblExploitationRateIndependence->AutoSize = true;
      this->lblExploitationRateIndependence->Location = System::Drawing::Point(6, 149);
      this->lblExploitationRateIndependence->Name = L"lblExploitationRateIndependence";
      this->lblExploitationRateIndependence->Size = System::Drawing::Size(156, 13);
      this->lblExploitationRateIndependence->TabIndex = 9;
      this->lblExploitationRateIndependence->Text = L"Exploitation rate independence:";
      // 
      // lblMetabolicWeightLossExponent
      // 
      this->lblMetabolicWeightLossExponent->AutoSize = true;
      this->lblMetabolicWeightLossExponent->Location = System::Drawing::Point(6, 201);
      this->lblMetabolicWeightLossExponent->Name = L"lblMetabolicWeightLossExponent";
      this->lblMetabolicWeightLossExponent->Size = System::Drawing::Size(158, 13);
      this->lblMetabolicWeightLossExponent->TabIndex = 13;
      this->lblMetabolicWeightLossExponent->Text = L"Metabolic weight loss exponent:";
      // 
      // lblNumberEulerSteps
      // 
      this->lblNumberEulerSteps->AutoSize = true;
      this->lblNumberEulerSteps->Location = System::Drawing::Point(6, 45);
      this->lblNumberEulerSteps->Name = L"lblNumberEulerSteps";
      this->lblNumberEulerSteps->Size = System::Drawing::Size(184, 13);
      this->lblNumberEulerSteps->TabIndex = 1;
      this->lblNumberEulerSteps->Text = L"Number of steps in Euler calculations:";
      // 
      // lblCadaverFoodRatio
      // 
      this->lblCadaverFoodRatio->AutoSize = true;
      this->lblCadaverFoodRatio->Location = System::Drawing::Point(6, 71);
      this->lblCadaverFoodRatio->Name = L"lblCadaverFoodRatio";
      this->lblCadaverFoodRatio->Size = System::Drawing::Size(143, 13);
      this->lblCadaverFoodRatio->TabIndex = 3;
      this->lblCadaverFoodRatio->Text = L"Cadaver weight to food ratio:";
      // 
      // lblAssimilationRate
      // 
      this->lblAssimilationRate->AutoSize = true;
      this->lblAssimilationRate->Location = System::Drawing::Point(6, 97);
      this->lblAssimilationRate->Name = L"lblAssimilationRate";
      this->lblAssimilationRate->Size = System::Drawing::Size(85, 13);
      this->lblAssimilationRate->TabIndex = 5;
      this->lblAssimilationRate->Text = L"Assimilation rate:";
      // 
      // gboxFasting
      // 
      this->gboxFasting->Controls->Add(this->snboxWeightToLipidConstant);
      this->gboxFasting->Controls->Add(this->snboxWeightToLipidSlope);
      this->gboxFasting->Controls->Add(this->lblNoLipidReserveSurvival);
      this->gboxFasting->Controls->Add(this->snboxNoLipidReserveSurvival);
      this->gboxFasting->Controls->Add(this->lblWeightToLipidSlope);
      this->gboxFasting->Controls->Add(this->lblNonDepletableLipidReserve);
      this->gboxFasting->Controls->Add(this->snboxNonDepletableLipidReserve);
      this->gboxFasting->Controls->Add(this->snboxLipidReserveSurvival);
      this->gboxFasting->Controls->Add(this->lblWeightToLipidConstant);
      this->gboxFasting->Controls->Add(this->lblLipidReserveSurvival);
      this->gboxFasting->Location = System::Drawing::Point(3, 814);
      this->gboxFasting->Name = L"gboxFasting";
      this->gboxFasting->Size = System::Drawing::Size(374, 149);
      this->gboxFasting->TabIndex = 19;
      this->gboxFasting->TabStop = false;
      this->gboxFasting->Text = L"Fasting";
      // 
      // snboxWeightToLipidConstant
      // 
      this->snboxWeightToLipidConstant->Location = System::Drawing::Point(277, 123);
      this->snboxWeightToLipidConstant->Name = L"snboxWeightToLipidConstant";
      this->snboxWeightToLipidConstant->Size = System::Drawing::Size(80, 20);
      this->snboxWeightToLipidConstant->TabIndex = 9;
      this->snboxWeightToLipidConstant->Text = L"0";
      this->snboxWeightToLipidConstant->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxWeightToLipidConstant->Value = L"0";
      // 
      // snboxWeightToLipidSlope
      // 
      this->snboxWeightToLipidSlope->Location = System::Drawing::Point(277, 97);
      this->snboxWeightToLipidSlope->Name = L"snboxWeightToLipidSlope";
      this->snboxWeightToLipidSlope->Size = System::Drawing::Size(80, 20);
      this->snboxWeightToLipidSlope->TabIndex = 7;
      this->snboxWeightToLipidSlope->Text = L"0";
      this->snboxWeightToLipidSlope->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxWeightToLipidSlope->Value = L"0";
      // 
      // lblNoLipidReserveSurvival
      // 
      this->lblNoLipidReserveSurvival->AutoSize = true;
      this->lblNoLipidReserveSurvival->Location = System::Drawing::Point(6, 47);
      this->lblNoLipidReserveSurvival->Name = L"lblNoLipidReserveSurvival";
      this->lblNoLipidReserveSurvival->Size = System::Drawing::Size(179, 13);
      this->lblNoLipidReserveSurvival->TabIndex = 2;
      this->lblNoLipidReserveSurvival->Text = L"Fasting survival with no lipid reserve:";
      // 
      // snboxNoLipidReserveSurvival
      // 
      this->snboxNoLipidReserveSurvival->Location = System::Drawing::Point(277, 45);
      this->snboxNoLipidReserveSurvival->Name = L"snboxNoLipidReserveSurvival";
      this->snboxNoLipidReserveSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxNoLipidReserveSurvival->TabIndex = 3;
      this->snboxNoLipidReserveSurvival->Text = L"0";
      this->snboxNoLipidReserveSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxNoLipidReserveSurvival->Value = L"0";
      // 
      // lblWeightToLipidSlope
      // 
      this->lblWeightToLipidSlope->AutoSize = true;
      this->lblWeightToLipidSlope->Location = System::Drawing::Point(6, 99);
      this->lblWeightToLipidSlope->Name = L"lblWeightToLipidSlope";
      this->lblWeightToLipidSlope->Size = System::Drawing::Size(105, 13);
      this->lblWeightToLipidSlope->TabIndex = 6;
      this->lblWeightToLipidSlope->Text = L"Weight to lipid slope:";
      // 
      // lblNonDepletableLipidReserve
      // 
      this->lblNonDepletableLipidReserve->AutoSize = true;
      this->lblNonDepletableLipidReserve->Location = System::Drawing::Point(6, 73);
      this->lblNonDepletableLipidReserve->Name = L"lblNonDepletableLipidReserve";
      this->lblNonDepletableLipidReserve->Size = System::Drawing::Size(146, 13);
      this->lblNonDepletableLipidReserve->TabIndex = 4;
      this->lblNonDepletableLipidReserve->Text = L"Non depletable lipid reserves:";
      // 
      // snboxNonDepletableLipidReserve
      // 
      this->snboxNonDepletableLipidReserve->Location = System::Drawing::Point(277, 71);
      this->snboxNonDepletableLipidReserve->Name = L"snboxNonDepletableLipidReserve";
      this->snboxNonDepletableLipidReserve->Size = System::Drawing::Size(80, 20);
      this->snboxNonDepletableLipidReserve->TabIndex = 5;
      this->snboxNonDepletableLipidReserve->Text = L"0";
      this->snboxNonDepletableLipidReserve->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxNonDepletableLipidReserve->Value = L"0";
      // 
      // snboxLipidReserveSurvival
      // 
      this->snboxLipidReserveSurvival->Location = System::Drawing::Point(277, 19);
      this->snboxLipidReserveSurvival->Name = L"snboxLipidReserveSurvival";
      this->snboxLipidReserveSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxLipidReserveSurvival->TabIndex = 1;
      this->snboxLipidReserveSurvival->Text = L"0";
      this->snboxLipidReserveSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxLipidReserveSurvival->Value = L"0";
      // 
      // lblWeightToLipidConstant
      // 
      this->lblWeightToLipidConstant->AutoSize = true;
      this->lblWeightToLipidConstant->Location = System::Drawing::Point(6, 125);
      this->lblWeightToLipidConstant->Name = L"lblWeightToLipidConstant";
      this->lblWeightToLipidConstant->Size = System::Drawing::Size(121, 13);
      this->lblWeightToLipidConstant->TabIndex = 8;
      this->lblWeightToLipidConstant->Text = L"Weight to lipid constant:";
      // 
      // lblLipidReserveSurvival
      // 
      this->lblLipidReserveSurvival->AutoSize = true;
      this->lblLipidReserveSurvival->Location = System::Drawing::Point(6, 21);
      this->lblLipidReserveSurvival->Name = L"lblLipidReserveSurvival";
      this->lblLipidReserveSurvival->Size = System::Drawing::Size(164, 13);
      this->lblLipidReserveSurvival->TabIndex = 0;
      this->lblLipidReserveSurvival->Text = L"Fasting survival with lipid reserve:";
      // 
      // lblWeightAtHatch
      // 
      this->lblWeightAtHatch->AutoSize = true;
      this->lblWeightAtHatch->Location = System::Drawing::Point(9, 92);
      this->lblWeightAtHatch->Name = L"lblWeightAtHatch";
      this->lblWeightAtHatch->Size = System::Drawing::Size(86, 13);
      this->lblWeightAtHatch->TabIndex = 10;
      this->lblWeightAtHatch->Text = L"Weight at hatch:";
      // 
      // snboxNominalSurvival
      // 
      this->snboxNominalSurvival->Location = System::Drawing::Point(280, 11);
      this->snboxNominalSurvival->Name = L"snboxNominalSurvival";
      this->snboxNominalSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxNominalSurvival->TabIndex = 5;
      this->snboxNominalSurvival->Text = L"0";
      this->snboxNominalSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxNominalSurvival->Value = L"0";
      // 
      // snboxPupationSurvival
      // 
      this->snboxPupationSurvival->Location = System::Drawing::Point(280, 37);
      this->snboxPupationSurvival->Name = L"snboxPupationSurvival";
      this->snboxPupationSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxPupationSurvival->TabIndex = 7;
      this->snboxPupationSurvival->Text = L"0";
      this->snboxPupationSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxPupationSurvival->Value = L"0";
      // 
      // snboxDryContainerSurvival
      // 
      this->snboxDryContainerSurvival->Location = System::Drawing::Point(280, 63);
      this->snboxDryContainerSurvival->Name = L"snboxDryContainerSurvival";
      this->snboxDryContainerSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxDryContainerSurvival->TabIndex = 9;
      this->snboxDryContainerSurvival->Text = L"0";
      this->snboxDryContainerSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxDryContainerSurvival->Value = L"0";
      // 
      // snboxWeightAtHatch
      // 
      this->snboxWeightAtHatch->Location = System::Drawing::Point(280, 89);
      this->snboxWeightAtHatch->Name = L"snboxWeightAtHatch";
      this->snboxWeightAtHatch->Size = System::Drawing::Size(80, 20);
      this->snboxWeightAtHatch->TabIndex = 11;
      this->snboxWeightAtHatch->Text = L"0";
      this->snboxWeightAtHatch->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxWeightAtHatch->Value = L"0";
      // 
      // snboxMinimumWeightForSurvival
      // 
      this->snboxMinimumWeightForSurvival->Location = System::Drawing::Point(280, 115);
      this->snboxMinimumWeightForSurvival->Name = L"snboxMinimumWeightForSurvival";
      this->snboxMinimumWeightForSurvival->Size = System::Drawing::Size(80, 20);
      this->snboxMinimumWeightForSurvival->TabIndex = 13;
      this->snboxMinimumWeightForSurvival->Text = L"0";
      this->snboxMinimumWeightForSurvival->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->snboxMinimumWeightForSurvival->Value = L"0";
      // 
      // errproLarvae
      // 
      this->errproLarvae->ContainerControl = this;
      // 
      // errproTemperature
      // 
      this->errproTemperature->ContainerControl = this;
      // 
      // errproPupationWeight
      // 
      this->errproPupationWeight->ContainerControl = this;
      // 
      // errproFood
      // 
      this->errproFood->ContainerControl = this;
      // 
      // errproFasting
      // 
      this->errproFasting->ContainerControl = this;
      // 
      // LarvaeBiologyPanel
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->Controls->Add(this->snboxMinimumWeightForSurvival);
      this->Controls->Add(this->snboxPupationSurvival);
      this->Controls->Add(this->snboxWeightAtHatch);
      this->Controls->Add(this->snboxNominalSurvival);
      this->Controls->Add(this->snboxDryContainerSurvival);
      this->Controls->Add(this->gboxFood);
      this->Controls->Add(this->gboxFasting);
      this->Controls->Add(this->gboxTemp);
      this->Controls->Add(this->gboxPupWt);
      this->Controls->Add(this->gboxDev);
      this->Controls->Add(this->lblWeightAtHatch);
      this->Controls->Add(this->lblMinimumWeightForSurvival);
      this->Controls->Add(this->lblDryContainerSurvival);
      this->Controls->Add(this->lblPupationSurvival);
      this->Controls->Add(this->lblNominalSurvival);
      this->Name = L"LarvaeBiologyPanel";
      this->Size = System::Drawing::Size(380, 967);
      this->Load += gcnew System::EventHandler(this, &LarvaeBiologyPanel::OnLoad);
      this->gboxDev->ResumeLayout(false);
      this->gboxDev->PerformLayout();
      this->gboxPupWt->ResumeLayout(false);
      this->gboxPupWt->PerformLayout();
      this->gboxTemp->ResumeLayout(false);
      this->gboxTemp->PerformLayout();
      this->gboxFood->ResumeLayout(false);
      this->gboxFood->PerformLayout();
      this->gboxFasting->ResumeLayout(false);
      this->gboxFasting->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errproLarvae))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errproTemperature))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errproPupationWeight))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errproFood))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errproFasting))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  };
}
