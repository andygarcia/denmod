#pragma once

#include "ScheduleControl.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace gui {


	public ref class InfectionIntroductionForm : public System::Windows::Forms::UserControl
	{
	public:
		InfectionIntroductionForm( BindingSource ^ locationBinding );
	protected:
		~InfectionIntroductionForm();

  private:
    System::Void OnLoad(System::Object^  sender, System::EventArgs^  e);

  private:
    BindingSource ^ LocationBinding;

  private: System::Windows::Forms::TabControl^  tabSerotypeInfections;

  private: System::Windows::Forms::TabPage^  tabDengue1;
  private: System::Windows::Forms::Label^  lblHumansD1;
  private: System::Windows::Forms::NumericUpDown^  numHumansD1;
  private: System::Windows::Forms::Label^  lblMosquitoesD1;
  private: System::Windows::Forms::NumericUpDown^  numMosquitoesD1;
  private: System::Windows::Forms::Label^  lblScheduleD1;
  private: ScheduleControl ^ ScheduleD1;

  private: System::Windows::Forms::TabPage^  tabDengue2;
  private: System::Windows::Forms::Label^  lblHumansD2;
  private: System::Windows::Forms::NumericUpDown^  numHumansD2;
  private: System::Windows::Forms::Label^  lblMosquitoesD2;
  private: System::Windows::Forms::NumericUpDown^  numMosquitoesD2;
  private: System::Windows::Forms::Label^  lblScheduleD2;
  private: ScheduleControl ^ ScheduleD2;

  private: System::Windows::Forms::TabPage^  tabDengue3;
  private: System::Windows::Forms::Label^  lblHumansD3;
  private: System::Windows::Forms::NumericUpDown^  numHumansD3;
  private: System::Windows::Forms::Label^  lblMosquitoesD3;
  private: System::Windows::Forms::NumericUpDown^  numMosquitoesD3;
  private: System::Windows::Forms::Label^  lblScheduleD3;
  private: ScheduleControl ^ ScheduleD3;

  private: System::Windows::Forms::TabPage^  tabDengue4;
  private: System::Windows::Forms::Label^  lblHumansD4;
  private: System::Windows::Forms::NumericUpDown^  numHumansD4;
  private: System::Windows::Forms::Label^  lblMosquitoesD4;
  private: System::Windows::Forms::NumericUpDown^  numMosquitoesD4;
  private: System::Windows::Forms::Label^  lblScheduleD4;
  private: ScheduleControl ^ ScheduleD4;

  private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->tabSerotypeInfections = (gcnew System::Windows::Forms::TabControl());
      this->tabDengue1 = (gcnew System::Windows::Forms::TabPage());
      this->numMosquitoesD1 = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblScheduleD1 = (gcnew System::Windows::Forms::Label());
      this->lblMosquitoesD1 = (gcnew System::Windows::Forms::Label());
      this->numHumansD1 = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblHumansD1 = (gcnew System::Windows::Forms::Label());
      this->tabDengue2 = (gcnew System::Windows::Forms::TabPage());
      this->lblScheduleD2 = (gcnew System::Windows::Forms::Label());
      this->numMosquitoesD2 = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblMosquitoesD2 = (gcnew System::Windows::Forms::Label());
      this->numHumansD2 = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblHumansD2 = (gcnew System::Windows::Forms::Label());
      this->tabDengue3 = (gcnew System::Windows::Forms::TabPage());
      this->lblScheduleD3 = (gcnew System::Windows::Forms::Label());
      this->numMosquitoesD3 = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblMosquitoesD3 = (gcnew System::Windows::Forms::Label());
      this->numHumansD3 = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblHumansD3 = (gcnew System::Windows::Forms::Label());
      this->tabDengue4 = (gcnew System::Windows::Forms::TabPage());
      this->lblScheduleD4 = (gcnew System::Windows::Forms::Label());
      this->numMosquitoesD4 = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblMosquitoesD4 = (gcnew System::Windows::Forms::Label());
      this->numHumansD4 = (gcnew System::Windows::Forms::NumericUpDown());
      this->lblHumansD4 = (gcnew System::Windows::Forms::Label());
      this->tabSerotypeInfections->SuspendLayout();
      this->tabDengue1->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMosquitoesD1))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numHumansD1))->BeginInit();
      this->tabDengue2->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMosquitoesD2))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numHumansD2))->BeginInit();
      this->tabDengue3->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMosquitoesD3))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numHumansD3))->BeginInit();
      this->tabDengue4->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMosquitoesD4))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numHumansD4))->BeginInit();
      this->SuspendLayout();
      // 
      // tabSerotypeInfections
      // 
      this->tabSerotypeInfections->Controls->Add(this->tabDengue1);
      this->tabSerotypeInfections->Controls->Add(this->tabDengue2);
      this->tabSerotypeInfections->Controls->Add(this->tabDengue3);
      this->tabSerotypeInfections->Controls->Add(this->tabDengue4);
      this->tabSerotypeInfections->Location = System::Drawing::Point(3, 3);
      this->tabSerotypeInfections->Multiline = true;
      this->tabSerotypeInfections->Name = L"tabSerotypeInfections";
      this->tabSerotypeInfections->SelectedIndex = 0;
      this->tabSerotypeInfections->Size = System::Drawing::Size(748, 266);
      this->tabSerotypeInfections->TabIndex = 0;
      // 
      // tabDengue1
      // 
      this->tabDengue1->Controls->Add(this->numMosquitoesD1);
      this->tabDengue1->Controls->Add(this->lblScheduleD1);
      this->tabDengue1->Controls->Add(this->lblMosquitoesD1);
      this->tabDengue1->Controls->Add(this->numHumansD1);
      this->tabDengue1->Controls->Add(this->lblHumansD1);
      this->tabDengue1->Location = System::Drawing::Point(4, 24);
      this->tabDengue1->Name = L"tabDengue1";
      this->tabDengue1->Size = System::Drawing::Size(740, 245);
      this->tabDengue1->TabIndex = 0;
      this->tabDengue1->Text = L"Dengue 1";
      this->tabDengue1->UseVisualStyleBackColor = true;
      // 
      // numMosquitoesD1
      // 
      this->numMosquitoesD1->Location = System::Drawing::Point(76, 41);
      this->numMosquitoesD1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000000, 0, 0, 0});
      this->numMosquitoesD1->Name = L"numMosquitoesD1";
      this->numMosquitoesD1->Size = System::Drawing::Size(73, 20);
      this->numMosquitoesD1->TabIndex = 3;
      // 
      // lblScheduleD1
      // 
      this->lblScheduleD1->AutoSize = true;
      this->lblScheduleD1->Location = System::Drawing::Point(169, 17);
      this->lblScheduleD1->Name = L"lblScheduleD1";
      this->lblScheduleD1->Size = System::Drawing::Size(55, 13);
      this->lblScheduleD1->TabIndex = 4;
      this->lblScheduleD1->Text = L"Schedule:";
      // 
      // lblMosquitoesD1
      // 
      this->lblMosquitoesD1->AutoSize = true;
      this->lblMosquitoesD1->Location = System::Drawing::Point(6, 43);
      this->lblMosquitoesD1->Name = L"lblMosquitoesD1";
      this->lblMosquitoesD1->Size = System::Drawing::Size(64, 13);
      this->lblMosquitoesD1->TabIndex = 2;
      this->lblMosquitoesD1->Text = L"Mosquitoes:";
      // 
      // numHumansD1
      // 
      this->numHumansD1->Location = System::Drawing::Point(76, 15);
      this->numHumansD1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000000, 0, 0, 0});
      this->numHumansD1->Name = L"numHumansD1";
      this->numHumansD1->Size = System::Drawing::Size(73, 20);
      this->numHumansD1->TabIndex = 1;
      // 
      // lblHumansD1
      // 
      this->lblHumansD1->AutoSize = true;
      this->lblHumansD1->Location = System::Drawing::Point(21, 17);
      this->lblHumansD1->Name = L"lblHumansD1";
      this->lblHumansD1->Size = System::Drawing::Size(49, 13);
      this->lblHumansD1->TabIndex = 0;
      this->lblHumansD1->Text = L"Humans:";
      // 
      // tabDengue2
      // 
      this->tabDengue2->Controls->Add(this->lblScheduleD2);
      this->tabDengue2->Controls->Add(this->numMosquitoesD2);
      this->tabDengue2->Controls->Add(this->lblMosquitoesD2);
      this->tabDengue2->Controls->Add(this->numHumansD2);
      this->tabDengue2->Controls->Add(this->lblHumansD2);
      this->tabDengue2->Location = System::Drawing::Point(4, 24);
      this->tabDengue2->Name = L"tabDengue2";
      this->tabDengue2->Size = System::Drawing::Size(740, 245);
      this->tabDengue2->TabIndex = 1;
      this->tabDengue2->Text = L"Dengue 2";
      this->tabDengue2->UseVisualStyleBackColor = true;
      // 
      // lblScheduleD2
      // 
      this->lblScheduleD2->AutoSize = true;
      this->lblScheduleD2->Location = System::Drawing::Point(169, 17);
      this->lblScheduleD2->Name = L"lblScheduleD2";
      this->lblScheduleD2->Size = System::Drawing::Size(55, 13);
      this->lblScheduleD2->TabIndex = 8;
      this->lblScheduleD2->Text = L"Schedule:";
      // 
      // numMosquitoesD2
      // 
      this->numMosquitoesD2->Location = System::Drawing::Point(76, 41);
      this->numMosquitoesD2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000000, 0, 0, 0});
      this->numMosquitoesD2->Name = L"numMosquitoesD2";
      this->numMosquitoesD2->Size = System::Drawing::Size(73, 20);
      this->numMosquitoesD2->TabIndex = 7;
      // 
      // lblMosquitoesD2
      // 
      this->lblMosquitoesD2->AutoSize = true;
      this->lblMosquitoesD2->Location = System::Drawing::Point(6, 43);
      this->lblMosquitoesD2->Name = L"lblMosquitoesD2";
      this->lblMosquitoesD2->Size = System::Drawing::Size(64, 13);
      this->lblMosquitoesD2->TabIndex = 6;
      this->lblMosquitoesD2->Text = L"Mosquitoes:";
      // 
      // numHumansD2
      // 
      this->numHumansD2->Location = System::Drawing::Point(76, 15);
      this->numHumansD2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000000, 0, 0, 0});
      this->numHumansD2->Name = L"numHumansD2";
      this->numHumansD2->Size = System::Drawing::Size(73, 20);
      this->numHumansD2->TabIndex = 5;
      // 
      // lblHumansD2
      // 
      this->lblHumansD2->AutoSize = true;
      this->lblHumansD2->Location = System::Drawing::Point(21, 17);
      this->lblHumansD2->Name = L"lblHumansD2";
      this->lblHumansD2->Size = System::Drawing::Size(49, 13);
      this->lblHumansD2->TabIndex = 4;
      this->lblHumansD2->Text = L"Humans:";
      // 
      // tabDengue3
      // 
      this->tabDengue3->Controls->Add(this->lblScheduleD3);
      this->tabDengue3->Controls->Add(this->numMosquitoesD3);
      this->tabDengue3->Controls->Add(this->lblMosquitoesD3);
      this->tabDengue3->Controls->Add(this->numHumansD3);
      this->tabDengue3->Controls->Add(this->lblHumansD3);
      this->tabDengue3->Location = System::Drawing::Point(4, 24);
      this->tabDengue3->Name = L"tabDengue3";
      this->tabDengue3->Size = System::Drawing::Size(740, 245);
      this->tabDengue3->TabIndex = 2;
      this->tabDengue3->Text = L"Dengue 3";
      this->tabDengue3->UseVisualStyleBackColor = true;
      // 
      // lblScheduleD3
      // 
      this->lblScheduleD3->AutoSize = true;
      this->lblScheduleD3->Location = System::Drawing::Point(169, 17);
      this->lblScheduleD3->Name = L"lblScheduleD3";
      this->lblScheduleD3->Size = System::Drawing::Size(55, 13);
      this->lblScheduleD3->TabIndex = 8;
      this->lblScheduleD3->Text = L"Schedule:";
      // 
      // numMosquitoesD3
      // 
      this->numMosquitoesD3->Location = System::Drawing::Point(76, 41);
      this->numMosquitoesD3->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000000, 0, 0, 0});
      this->numMosquitoesD3->Name = L"numMosquitoesD3";
      this->numMosquitoesD3->Size = System::Drawing::Size(73, 20);
      this->numMosquitoesD3->TabIndex = 7;
      // 
      // lblMosquitoesD3
      // 
      this->lblMosquitoesD3->AutoSize = true;
      this->lblMosquitoesD3->Location = System::Drawing::Point(6, 43);
      this->lblMosquitoesD3->Name = L"lblMosquitoesD3";
      this->lblMosquitoesD3->Size = System::Drawing::Size(64, 13);
      this->lblMosquitoesD3->TabIndex = 6;
      this->lblMosquitoesD3->Text = L"Mosquitoes:";
      // 
      // numHumansD3
      // 
      this->numHumansD3->Location = System::Drawing::Point(76, 15);
      this->numHumansD3->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000000, 0, 0, 0});
      this->numHumansD3->Name = L"numHumansD3";
      this->numHumansD3->Size = System::Drawing::Size(73, 20);
      this->numHumansD3->TabIndex = 5;
      // 
      // lblHumansD3
      // 
      this->lblHumansD3->AutoSize = true;
      this->lblHumansD3->Location = System::Drawing::Point(21, 17);
      this->lblHumansD3->Name = L"lblHumansD3";
      this->lblHumansD3->Size = System::Drawing::Size(49, 13);
      this->lblHumansD3->TabIndex = 4;
      this->lblHumansD3->Text = L"Humans:";
      // 
      // tabDengue4
      // 
      this->tabDengue4->Controls->Add(this->lblScheduleD4);
      this->tabDengue4->Controls->Add(this->numMosquitoesD4);
      this->tabDengue4->Controls->Add(this->lblMosquitoesD4);
      this->tabDengue4->Controls->Add(this->numHumansD4);
      this->tabDengue4->Controls->Add(this->lblHumansD4);
      this->tabDengue4->Location = System::Drawing::Point(4, 24);
      this->tabDengue4->Name = L"tabDengue4";
      this->tabDengue4->Size = System::Drawing::Size(740, 238);
      this->tabDengue4->TabIndex = 3;
      this->tabDengue4->Text = L"Dengue 4";
      this->tabDengue4->UseVisualStyleBackColor = true;
      // 
      // lblScheduleD4
      // 
      this->lblScheduleD4->AutoSize = true;
      this->lblScheduleD4->Location = System::Drawing::Point(169, 17);
      this->lblScheduleD4->Name = L"lblScheduleD4";
      this->lblScheduleD4->Size = System::Drawing::Size(55, 13);
      this->lblScheduleD4->TabIndex = 8;
      this->lblScheduleD4->Text = L"Schedule:";
      // 
      // numMosquitoesD4
      // 
      this->numMosquitoesD4->Location = System::Drawing::Point(76, 41);
      this->numMosquitoesD4->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000000, 0, 0, 0});
      this->numMosquitoesD4->Name = L"numMosquitoesD4";
      this->numMosquitoesD4->Size = System::Drawing::Size(73, 20);
      this->numMosquitoesD4->TabIndex = 7;
      // 
      // lblMosquitoesD4
      // 
      this->lblMosquitoesD4->AutoSize = true;
      this->lblMosquitoesD4->Location = System::Drawing::Point(6, 43);
      this->lblMosquitoesD4->Name = L"lblMosquitoesD4";
      this->lblMosquitoesD4->Size = System::Drawing::Size(64, 13);
      this->lblMosquitoesD4->TabIndex = 6;
      this->lblMosquitoesD4->Text = L"Mosquitoes:";
      // 
      // numHumansD4
      // 
      this->numHumansD4->Location = System::Drawing::Point(76, 15);
      this->numHumansD4->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000000, 0, 0, 0});
      this->numHumansD4->Name = L"numHumansD4";
      this->numHumansD4->Size = System::Drawing::Size(73, 20);
      this->numHumansD4->TabIndex = 5;
      // 
      // lblHumansD4
      // 
      this->lblHumansD4->AutoSize = true;
      this->lblHumansD4->Location = System::Drawing::Point(21, 17);
      this->lblHumansD4->Name = L"lblHumansD4";
      this->lblHumansD4->Size = System::Drawing::Size(49, 13);
      this->lblHumansD4->TabIndex = 4;
      this->lblHumansD4->Text = L"Humans:";
      // 
      // InfectionIntroductionForm
      // 
      this->BackColor = System::Drawing::Color::Transparent;
      this->Controls->Add(this->tabSerotypeInfections);
      this->Name = L"InfectionIntroductionForm";
      this->Size = System::Drawing::Size(754, 347);
      this->Load += gcnew System::EventHandler(this, &InfectionIntroductionForm::OnLoad);
      this->tabSerotypeInfections->ResumeLayout(false);
      this->tabDengue1->ResumeLayout(false);
      this->tabDengue1->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMosquitoesD1))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numHumansD1))->EndInit();
      this->tabDengue2->ResumeLayout(false);
      this->tabDengue2->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMosquitoesD2))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numHumansD2))->EndInit();
      this->tabDengue3->ResumeLayout(false);
      this->tabDengue3->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMosquitoesD3))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numHumansD3))->EndInit();
      this->tabDengue4->ResumeLayout(false);
      this->tabDengue4->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numMosquitoesD4))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numHumansD4))->EndInit();
      this->ResumeLayout(false);

    }
#pragma endregion
	};
}
