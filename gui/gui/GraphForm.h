#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace gui {


    enum class DensimGraphType : int {
      InitialAgeDistribution,
      FinalAgeDistribution,

      SimulationArea,
      PopulationSize,

      BirthsByClass,
      DeathsByClass,
      BirthPercentagesByClass,
      DeathPercentagesByClass,

      FemaleMosquitoesInSimulationArea,
      FemaleMosquitoesPerHectare,
      FemaleMosquitoesPerPerson,
      FemaleMosquitoSurvival,
      FemaleMosquitoWetWeight,

      EipDevelopmentRate,
      InfectiveMosquitoes,
      PotentiallyInfectiveBites,
      PersonsIncubating,
      PersonsViremic,
      PersonsWithVirus,

      //GeneralSeroprevalence,
      //DetailedSeroprevalence,

      //NewCases,
      //PredictedHFSS,
      //DeathsHFSS
    };

  public ref class GraphForm : public System::Windows::Forms::Form
	{
	public:
    GraphForm( gui::Location ^ location, output::Graph ^ graph, output::TimePeriod timePeriod, output::TimePeriodFunction timePeriodFunction );
    GraphForm( gui::Location ^ location, DensimGraphType graphType );
	protected:
		~GraphForm();

  private:
    System::Void OnSave(System::Object^  sender, System::EventArgs^  e);
    
  private:
    gui::Location ^ Location_;
    gui::Container ^ Container_;

  private: Dundas::Charting::WinControl::Chart^  chartMainPlot;
  private: System::Windows::Forms::Button^  btnExit;
  private: System::Windows::Forms::Button^  btnSave;
  protected: 

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
      Dundas::Charting::WinControl::ChartArea^  chartArea1 = (gcnew Dundas::Charting::WinControl::ChartArea());
      Dundas::Charting::WinControl::Legend^  legend1 = (gcnew Dundas::Charting::WinControl::Legend());
      this->chartMainPlot = (gcnew Dundas::Charting::WinControl::Chart());
      this->btnExit = (gcnew System::Windows::Forms::Button());
      this->btnSave = (gcnew System::Windows::Forms::Button());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chartMainPlot))->BeginInit();
      this->SuspendLayout();
      // 
      // chartMainPlot
      // 
      this->chartMainPlot->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->chartMainPlot->BackColor = System::Drawing::Color::WhiteSmoke;
      this->chartMainPlot->BackGradientEndColor = System::Drawing::Color::White;
      this->chartMainPlot->BackGradientType = Dundas::Charting::WinControl::GradientType::DiagonalLeft;
      this->chartMainPlot->BorderLineColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(26)), 
        static_cast<System::Int32>(static_cast<System::Byte>(59)), static_cast<System::Int32>(static_cast<System::Byte>(105)));
      this->chartMainPlot->BorderLineStyle = Dundas::Charting::WinControl::ChartDashStyle::Solid;
      this->chartMainPlot->BorderSkin->FrameBackColor = System::Drawing::Color::CornflowerBlue;
      this->chartMainPlot->BorderSkin->FrameBackGradientEndColor = System::Drawing::Color::CornflowerBlue;
      this->chartMainPlot->BorderSkin->PageColor = System::Drawing::SystemColors::Control;
      this->chartMainPlot->BorderSkin->SkinStyle = Dundas::Charting::WinControl::BorderSkinStyle::Emboss;
      chartArea1->AxisX->LabelStyle->IntervalOffset = 0;
      chartArea1->AxisX->LabelStyle->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisX->LabelStyle->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisX->MajorGrid->Enabled = false;
      chartArea1->AxisX->MajorGrid->Interval = 0;
      chartArea1->AxisX->MajorGrid->IntervalOffset = 0;
      chartArea1->AxisX->MajorGrid->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisX->MajorGrid->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisX->MajorGrid->LineColor = System::Drawing::Color::Silver;
      chartArea1->AxisX->MajorTickMark->Interval = 0;
      chartArea1->AxisX->MajorTickMark->IntervalOffset = 0;
      chartArea1->AxisX->MajorTickMark->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisX->MajorTickMark->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisX->MinorGrid->LineColor = System::Drawing::Color::Silver;
      chartArea1->AxisX2->LabelStyle->Interval = 0;
      chartArea1->AxisX2->LabelStyle->IntervalOffset = 0;
      chartArea1->AxisX2->LabelStyle->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisX2->LabelStyle->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisX2->MajorGrid->Interval = 0;
      chartArea1->AxisX2->MajorGrid->IntervalOffset = 0;
      chartArea1->AxisX2->MajorGrid->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisX2->MajorGrid->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisX2->MajorGrid->LineColor = System::Drawing::Color::Silver;
      chartArea1->AxisX2->MajorTickMark->Interval = 0;
      chartArea1->AxisX2->MajorTickMark->IntervalOffset = 0;
      chartArea1->AxisX2->MajorTickMark->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisX2->MajorTickMark->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisX2->MinorGrid->LineColor = System::Drawing::Color::Silver;
      chartArea1->AxisY->LabelStyle->Interval = 0;
      chartArea1->AxisY->LabelStyle->IntervalOffset = 0;
      chartArea1->AxisY->LabelStyle->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisY->LabelStyle->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisY->MajorGrid->Interval = 0;
      chartArea1->AxisY->MajorGrid->IntervalOffset = 0;
      chartArea1->AxisY->MajorGrid->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisY->MajorGrid->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisY->MajorGrid->LineColor = System::Drawing::Color::Silver;
      chartArea1->AxisY->MajorTickMark->Interval = 0;
      chartArea1->AxisY->MajorTickMark->IntervalOffset = 0;
      chartArea1->AxisY->MajorTickMark->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisY->MajorTickMark->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisY->MinorGrid->LineColor = System::Drawing::Color::Silver;
      chartArea1->AxisY2->LabelStyle->Interval = 0;
      chartArea1->AxisY2->LabelStyle->IntervalOffset = 0;
      chartArea1->AxisY2->LabelStyle->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisY2->LabelStyle->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisY2->MajorGrid->Interval = 0;
      chartArea1->AxisY2->MajorGrid->IntervalOffset = 0;
      chartArea1->AxisY2->MajorGrid->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisY2->MajorGrid->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisY2->MajorGrid->LineColor = System::Drawing::Color::Silver;
      chartArea1->AxisY2->MajorTickMark->Interval = 0;
      chartArea1->AxisY2->MajorTickMark->IntervalOffset = 0;
      chartArea1->AxisY2->MajorTickMark->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisY2->MajorTickMark->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea1->AxisY2->MinorGrid->LineColor = System::Drawing::Color::Silver;
      chartArea1->BackColor = System::Drawing::Color::White;
      chartArea1->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(26)), static_cast<System::Int32>(static_cast<System::Byte>(59)), 
        static_cast<System::Int32>(static_cast<System::Byte>(105)));
      chartArea1->BorderStyle = Dundas::Charting::WinControl::ChartDashStyle::Solid;
      chartArea1->CursorX->Interval = 0;
      chartArea1->CursorX->UserEnabled = true;
      chartArea1->CursorX->UserSelection = true;
      chartArea1->CursorY->Interval = 0;
      chartArea1->CursorY->UserEnabled = true;
      chartArea1->CursorY->UserSelection = true;
      chartArea1->InnerPlotPosition->Auto = false;
      chartArea1->InnerPlotPosition->Height = 91.31669F;
      chartArea1->InnerPlotPosition->Width = 90.36408F;
      chartArea1->InnerPlotPosition->X = 5.64604F;
      chartArea1->InnerPlotPosition->Y = 1.98027F;
      chartArea1->Name = L"Default";
      chartArea1->Position->Auto = false;
      chartArea1->Position->Height = 79.53476F;
      chartArea1->Position->Width = 92.10797F;
      chartArea1->Position->X = 3.756811F;
      chartArea1->Position->Y = 15.82769F;
      chartArea1->ShadowOffset = 2;
      this->chartMainPlot->ChartAreas->Add(chartArea1);
      legend1->Alignment = System::Drawing::StringAlignment::Far;
      legend1->BackColor = System::Drawing::Color::White;
      legend1->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(26)), static_cast<System::Int32>(static_cast<System::Byte>(59)), 
        static_cast<System::Int32>(static_cast<System::Byte>(105)));
      legend1->Docking = Dundas::Charting::WinControl::LegendDocking::Top;
      legend1->Name = L"Default";
      legend1->ShadowOffset = 2;
      this->chartMainPlot->Legends->Add(legend1);
      this->chartMainPlot->Location = System::Drawing::Point(12, 12);
      this->chartMainPlot->Name = L"chartMainPlot";
      this->chartMainPlot->Palette = Dundas::Charting::WinControl::ChartColorPalette::Dundas;
      this->chartMainPlot->Size = System::Drawing::Size(992, 688);
      this->chartMainPlot->TabIndex = 2;
      this->chartMainPlot->Text = L"chart1";
      // 
      // btnExit
      // 
      this->btnExit->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnExit->DialogResult = System::Windows::Forms::DialogResult::Cancel;
      this->btnExit->Location = System::Drawing::Point(929, 706);
      this->btnExit->Name = L"btnExit";
      this->btnExit->Size = System::Drawing::Size(75, 23);
      this->btnExit->TabIndex = 3;
      this->btnExit->Text = L"Exit";
      this->btnExit->UseVisualStyleBackColor = true;
      // 
      // btnSave
      // 
      this->btnSave->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
      this->btnSave->Location = System::Drawing::Point(12, 706);
      this->btnSave->Name = L"btnSave";
      this->btnSave->Size = System::Drawing::Size(120, 23);
      this->btnSave->TabIndex = 4;
      this->btnSave->Text = L"Save to Spreadsheet";
      this->btnSave->UseVisualStyleBackColor = true;
      this->btnSave->Click += gcnew System::EventHandler(this, &GraphForm::OnSave);
      // 
      // GraphForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->CancelButton = this->btnExit;
      this->ClientSize = System::Drawing::Size(1016, 741);
      this->Controls->Add(this->btnSave);
      this->Controls->Add(this->btnExit);
      this->Controls->Add(this->chartMainPlot);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
      this->Name = L"GraphForm";
      this->ShowInTaskbar = false;
      this->Text = L"GraphForm";
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chartMainPlot))->EndInit();
      this->ResumeLayout(false);

    }
#pragma endregion
};
}
