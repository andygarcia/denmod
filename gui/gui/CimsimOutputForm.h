#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace gui {


  public ref class CimsimOutputForm : public System::Windows::Forms::Form
	{
	public:
    CimsimOutputForm( gui::Location ^ Location );
	protected:
		~CimsimOutputForm();

  private:
    System::Void OnLoad(System::Object^  sender, System::EventArgs^  e);
    System::Void OnView(System::Object^  sender, System::EventArgs^  e);
    System::Void OnViewLocationGraph( System::Object^  sender, System::EventArgs^  e );
    System::Void OnViewContainerGraph( System::Object^  sender, System::EventArgs^  e );
    void DisplayChart( output::Chart ^ chartData, output::TimePeriod timePeriod, output::TimePeriodFunction timePeriodFunction );
    System::Void OnSave( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnSaveAll( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnRunDensim(System::Object^  sender, System::EventArgs^  e);

  private:
    gui::Location ^ _location;

  private: System::Windows::Forms::Button^  btnExit;
  private: System::Windows::Forms::Button^  btnSave;
  private: System::Windows::Forms::Button^  btnSaveAll;
  private: Dundas::Charting::WinControl::Chart^  _chart;

  private: System::Windows::Forms::Button^  btnRunDensim;
  private: System::Windows::Forms::ComboBox^  cboxContainers;
  private: System::Windows::Forms::ComboBox^  cboxTimePeriodFunction;
  private: System::Windows::Forms::ComboBox^  cboxTimePeriod;
  private: System::Windows::Forms::Label^  lblSummaryFunction;
  private: System::Windows::Forms::Label^  lblSummaryPeriod;
  private: System::Windows::Forms::ListBox^  lboxContainerGraphs;
  private: System::Windows::Forms::ListBox^  lboxLocationGraphs;
  private: System::Windows::Forms::TabPage^  tabPageContainers;
  private: System::Windows::Forms::TabPage^  tabPageLocation;
  private: System::Windows::Forms::TabControl^  tabGraphs;
  private: System::Windows::Forms::Button^  btnView;
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
      Dundas::Charting::WinControl::ChartArea^  chartArea1 = (gcnew Dundas::Charting::WinControl::ChartArea());
      Dundas::Charting::WinControl::Legend^  legend1 = (gcnew Dundas::Charting::WinControl::Legend());
      this->btnExit = (gcnew System::Windows::Forms::Button());
      this->btnSave = (gcnew System::Windows::Forms::Button());
      this->btnSaveAll = (gcnew System::Windows::Forms::Button());
      this->_chart = (gcnew Dundas::Charting::WinControl::Chart());
      this->btnRunDensim = (gcnew System::Windows::Forms::Button());
      this->cboxContainers = (gcnew System::Windows::Forms::ComboBox());
      this->cboxTimePeriodFunction = (gcnew System::Windows::Forms::ComboBox());
      this->cboxTimePeriod = (gcnew System::Windows::Forms::ComboBox());
      this->lboxContainerGraphs = (gcnew System::Windows::Forms::ListBox());
      this->lboxLocationGraphs = (gcnew System::Windows::Forms::ListBox());
      this->lblSummaryFunction = (gcnew System::Windows::Forms::Label());
      this->lblSummaryPeriod = (gcnew System::Windows::Forms::Label());
      this->tabPageContainers = (gcnew System::Windows::Forms::TabPage());
      this->tabPageLocation = (gcnew System::Windows::Forms::TabPage());
      this->tabGraphs = (gcnew System::Windows::Forms::TabControl());
      this->btnView = (gcnew System::Windows::Forms::Button());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->_chart))->BeginInit();
      this->tabPageContainers->SuspendLayout();
      this->tabPageLocation->SuspendLayout();
      this->tabGraphs->SuspendLayout();
      this->SuspendLayout();
      // 
      // btnExit
      // 
      this->btnExit->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnExit->DialogResult = System::Windows::Forms::DialogResult::Cancel;
      this->btnExit->Location = System::Drawing::Point(1097, 731);
      this->btnExit->Name = L"btnExit";
      this->btnExit->Size = System::Drawing::Size(75, 23);
      this->btnExit->TabIndex = 4;
      this->btnExit->Text = L"Close";
      this->btnExit->UseVisualStyleBackColor = true;
      // 
      // btnSave
      // 
      this->btnSave->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
      this->btnSave->Location = System::Drawing::Point(229, 731);
      this->btnSave->Name = L"btnSave";
      this->btnSave->Size = System::Drawing::Size(75, 23);
      this->btnSave->TabIndex = 1;
      this->btnSave->Text = L"Save";
      this->btnSave->UseVisualStyleBackColor = true;
      this->btnSave->Click += gcnew System::EventHandler(this, &CimsimOutputForm::OnSave);
      // 
      // btnSaveAll
      // 
      this->btnSaveAll->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
      this->btnSaveAll->Location = System::Drawing::Point(310, 731);
      this->btnSaveAll->Name = L"btnSaveAll";
      this->btnSaveAll->Size = System::Drawing::Size(75, 23);
      this->btnSaveAll->TabIndex = 2;
      this->btnSaveAll->Text = L"Save All";
      this->btnSaveAll->UseVisualStyleBackColor = true;
      this->btnSaveAll->Click += gcnew System::EventHandler(this, &CimsimOutputForm::OnSaveAll);
      // 
      // _chart
      // 
      this->_chart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->_chart->BackColor = System::Drawing::Color::WhiteSmoke;
      this->_chart->BackGradientEndColor = System::Drawing::Color::White;
      this->_chart->BackGradientType = Dundas::Charting::WinControl::GradientType::DiagonalLeft;
      this->_chart->BorderLineColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(26)), static_cast<System::Int32>(static_cast<System::Byte>(59)), 
        static_cast<System::Int32>(static_cast<System::Byte>(105)));
      this->_chart->BorderLineStyle = Dundas::Charting::WinControl::ChartDashStyle::Solid;
      this->_chart->BorderSkin->FrameBackColor = System::Drawing::Color::CornflowerBlue;
      this->_chart->BorderSkin->FrameBackGradientEndColor = System::Drawing::Color::CornflowerBlue;
      this->_chart->BorderSkin->PageColor = System::Drawing::SystemColors::Control;
      this->_chart->BorderSkin->SkinStyle = Dundas::Charting::WinControl::BorderSkinStyle::Emboss;
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
      chartArea1->AxisX->Margin = false;
      chartArea1->AxisX->MinorGrid->LineColor = System::Drawing::Color::Silver;
      chartArea1->AxisX->Title = L"Week";
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
      chartArea1->AxisY->Margin = false;
      chartArea1->AxisY->MinorGrid->LineColor = System::Drawing::Color::Silver;
      chartArea1->AxisY->Title = L"# / ha";
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
      chartArea1->CursorX->UserEnabled = true;
      chartArea1->CursorX->UserSelection = true;
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
      this->_chart->ChartAreas->Add(chartArea1);
      legend1->Alignment = System::Drawing::StringAlignment::Far;
      legend1->BackColor = System::Drawing::Color::White;
      legend1->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(26)), static_cast<System::Int32>(static_cast<System::Byte>(59)), 
        static_cast<System::Int32>(static_cast<System::Byte>(105)));
      legend1->Docking = Dundas::Charting::WinControl::LegendDocking::Top;
      legend1->Name = L"Default";
      legend1->ShadowOffset = 2;
      this->_chart->Legends->Add(legend1);
      this->_chart->Location = System::Drawing::Point(229, 12);
      this->_chart->Name = L"_chart";
      this->_chart->Palette = Dundas::Charting::WinControl::ChartColorPalette::Dundas;
      this->_chart->Size = System::Drawing::Size(943, 713);
      this->_chart->TabIndex = 0;
      this->_chart->Text = L"chartOutput";
      // 
      // btnRunDensim
      // 
      this->btnRunDensim->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnRunDensim->Location = System::Drawing::Point(990, 731);
      this->btnRunDensim->Name = L"btnRunDensim";
      this->btnRunDensim->Size = System::Drawing::Size(101, 23);
      this->btnRunDensim->TabIndex = 5;
      this->btnRunDensim->Text = L"Run DENSiM";
      this->btnRunDensim->UseVisualStyleBackColor = true;
      this->btnRunDensim->Click += gcnew System::EventHandler(this, &CimsimOutputForm::OnRunDensim);
      // 
      // cboxContainers
      // 
      this->cboxContainers->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->cboxContainers->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxContainers->FormattingEnabled = true;
      this->cboxContainers->Location = System::Drawing::Point(3, 6);
      this->cboxContainers->Name = L"cboxContainers";
      this->cboxContainers->Size = System::Drawing::Size(194, 21);
      this->cboxContainers->TabIndex = 7;
      // 
      // cboxTimePeriodFunction
      // 
      this->cboxTimePeriodFunction->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxTimePeriodFunction->FormattingEnabled = true;
      this->cboxTimePeriodFunction->Location = System::Drawing::Point(57, 438);
      this->cboxTimePeriodFunction->Name = L"cboxTimePeriodFunction";
      this->cboxTimePeriodFunction->Size = System::Drawing::Size(166, 21);
      this->cboxTimePeriodFunction->TabIndex = 15;
      // 
      // cboxTimePeriod
      // 
      this->cboxTimePeriod->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxTimePeriod->FormattingEnabled = true;
      this->cboxTimePeriod->Location = System::Drawing::Point(57, 411);
      this->cboxTimePeriod->Name = L"cboxTimePeriod";
      this->cboxTimePeriod->Size = System::Drawing::Size(166, 21);
      this->cboxTimePeriod->TabIndex = 14;
      // 
      // lboxContainerGraphs
      // 
      this->lboxContainerGraphs->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->lboxContainerGraphs->FormattingEnabled = true;
      this->lboxContainerGraphs->Location = System::Drawing::Point(3, 32);
      this->lboxContainerGraphs->Name = L"lboxContainerGraphs";
      this->lboxContainerGraphs->Size = System::Drawing::Size(194, 329);
      this->lboxContainerGraphs->TabIndex = 8;
      this->lboxContainerGraphs->DoubleClick += gcnew System::EventHandler(this, &CimsimOutputForm::OnView);
      // 
      // lboxLocationGraphs
      // 
      this->lboxLocationGraphs->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->lboxLocationGraphs->FormattingEnabled = true;
      this->lboxLocationGraphs->Location = System::Drawing::Point(3, 6);
      this->lboxLocationGraphs->Name = L"lboxLocationGraphs";
      this->lboxLocationGraphs->Size = System::Drawing::Size(194, 355);
      this->lboxLocationGraphs->TabIndex = 6;
      this->lboxLocationGraphs->DoubleClick += gcnew System::EventHandler(this, &CimsimOutputForm::OnView);
      // 
      // lblSummaryFunction
      // 
      this->lblSummaryFunction->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->lblSummaryFunction->AutoSize = true;
      this->lblSummaryFunction->Location = System::Drawing::Point(16, 441);
      this->lblSummaryFunction->Name = L"lblSummaryFunction";
      this->lblSummaryFunction->Size = System::Drawing::Size(35, 13);
      this->lblSummaryFunction->TabIndex = 19;
      this->lblSummaryFunction->Text = L"using:";
      // 
      // lblSummaryPeriod
      // 
      this->lblSummaryPeriod->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->lblSummaryPeriod->AutoSize = true;
      this->lblSummaryPeriod->Location = System::Drawing::Point(18, 414);
      this->lblSummaryPeriod->Name = L"lblSummaryPeriod";
      this->lblSummaryPeriod->Size = System::Drawing::Size(33, 13);
      this->lblSummaryPeriod->TabIndex = 17;
      this->lblSummaryPeriod->Text = L"View:";
      // 
      // tabPageContainers
      // 
      this->tabPageContainers->Controls->Add(this->lboxContainerGraphs);
      this->tabPageContainers->Controls->Add(this->cboxContainers);
      this->tabPageContainers->Location = System::Drawing::Point(4, 22);
      this->tabPageContainers->Name = L"tabPageContainers";
      this->tabPageContainers->Padding = System::Windows::Forms::Padding(3);
      this->tabPageContainers->Size = System::Drawing::Size(203, 367);
      this->tabPageContainers->TabIndex = 1;
      this->tabPageContainers->Text = L"Containers";
      this->tabPageContainers->UseVisualStyleBackColor = true;
      // 
      // tabPageLocation
      // 
      this->tabPageLocation->Controls->Add(this->lboxLocationGraphs);
      this->tabPageLocation->Location = System::Drawing::Point(4, 22);
      this->tabPageLocation->Name = L"tabPageLocation";
      this->tabPageLocation->Padding = System::Windows::Forms::Padding(3);
      this->tabPageLocation->Size = System::Drawing::Size(203, 367);
      this->tabPageLocation->TabIndex = 0;
      this->tabPageLocation->Text = L"Location";
      this->tabPageLocation->UseVisualStyleBackColor = true;
      // 
      // tabGraphs
      // 
      this->tabGraphs->Controls->Add(this->tabPageLocation);
      this->tabGraphs->Controls->Add(this->tabPageContainers);
      this->tabGraphs->Location = System::Drawing::Point(12, 12);
      this->tabGraphs->Name = L"tabGraphs";
      this->tabGraphs->SelectedIndex = 0;
      this->tabGraphs->Size = System::Drawing::Size(211, 393);
      this->tabGraphs->TabIndex = 10;
      // 
      // btnView
      // 
      this->btnView->Location = System::Drawing::Point(148, 465);
      this->btnView->Name = L"btnView";
      this->btnView->Size = System::Drawing::Size(75, 23);
      this->btnView->TabIndex = 13;
      this->btnView->Text = L"View";
      this->btnView->UseVisualStyleBackColor = true;
      this->btnView->Click += gcnew System::EventHandler(this, &CimsimOutputForm::OnView);
      // 
      // CimsimOutputForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->CancelButton = this->btnExit;
      this->ClientSize = System::Drawing::Size(1184, 766);
      this->Controls->Add(this->cboxTimePeriod);
      this->Controls->Add(this->lblSummaryFunction);
      this->Controls->Add(this->cboxTimePeriodFunction);
      this->Controls->Add(this->tabGraphs);
      this->Controls->Add(this->lblSummaryPeriod);
      this->Controls->Add(this->btnRunDensim);
      this->Controls->Add(this->_chart);
      this->Controls->Add(this->btnView);
      this->Controls->Add(this->btnSaveAll);
      this->Controls->Add(this->btnSave);
      this->Controls->Add(this->btnExit);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
      this->Name = L"CimsimOutputForm";
      this->ShowInTaskbar = false;
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
      this->Text = L"CIMSiM Output";
      this->Load += gcnew System::EventHandler(this, &CimsimOutputForm::OnLoad);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->_chart))->EndInit();
      this->tabPageContainers->ResumeLayout(false);
      this->tabPageLocation->ResumeLayout(false);
      this->tabGraphs->ResumeLayout(false);
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  };
}
