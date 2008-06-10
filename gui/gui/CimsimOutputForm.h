#pragma once

#include "SimOutput.h"

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
    System::Void OnMore( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnSave( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnSaveAll( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnRunDensim(System::Object^  sender, System::EventArgs^  e);

  private:
    gui::Location ^ _location;

  private: System::Windows::Forms::Button^  btnExit;
  private: System::Windows::Forms::Button^  btnMore;
  private: System::Windows::Forms::Button^  btnSave;
  private: System::Windows::Forms::Button^  btnSaveAll;
  private: Dundas::Charting::WinControl::Chart^  chartOutput;
  private: System::Windows::Forms::Button^  btnRunDensim;
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
      Dundas::Charting::WinControl::ChartArea^  chartArea3 = (gcnew Dundas::Charting::WinControl::ChartArea());
      Dundas::Charting::WinControl::Legend^  legend3 = (gcnew Dundas::Charting::WinControl::Legend());
      this->btnExit = (gcnew System::Windows::Forms::Button());
      this->btnMore = (gcnew System::Windows::Forms::Button());
      this->btnSave = (gcnew System::Windows::Forms::Button());
      this->btnSaveAll = (gcnew System::Windows::Forms::Button());
      this->chartOutput = (gcnew Dundas::Charting::WinControl::Chart());
      this->btnRunDensim = (gcnew System::Windows::Forms::Button());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chartOutput))->BeginInit();
      this->SuspendLayout();
      // 
      // btnExit
      // 
      this->btnExit->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnExit->DialogResult = System::Windows::Forms::DialogResult::Cancel;
      this->btnExit->Location = System::Drawing::Point(929, 706);
      this->btnExit->Name = L"btnExit";
      this->btnExit->Size = System::Drawing::Size(75, 23);
      this->btnExit->TabIndex = 4;
      this->btnExit->Text = L"Close";
      this->btnExit->UseVisualStyleBackColor = true;
      // 
      // btnMore
      // 
      this->btnMore->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnMore->Location = System::Drawing::Point(848, 706);
      this->btnMore->Name = L"btnMore";
      this->btnMore->Size = System::Drawing::Size(75, 23);
      this->btnMore->TabIndex = 3;
      this->btnMore->Text = L"Graphs...";
      this->btnMore->UseVisualStyleBackColor = true;
      this->btnMore->Click += gcnew System::EventHandler(this, &CimsimOutputForm::OnMore);
      // 
      // btnSave
      // 
      this->btnSave->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
      this->btnSave->Location = System::Drawing::Point(12, 706);
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
      this->btnSaveAll->Location = System::Drawing::Point(93, 706);
      this->btnSaveAll->Name = L"btnSaveAll";
      this->btnSaveAll->Size = System::Drawing::Size(75, 23);
      this->btnSaveAll->TabIndex = 2;
      this->btnSaveAll->Text = L"Save All";
      this->btnSaveAll->UseVisualStyleBackColor = true;
      this->btnSaveAll->Click += gcnew System::EventHandler(this, &CimsimOutputForm::OnSaveAll);
      // 
      // chartOutput
      // 
      this->chartOutput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->chartOutput->BackColor = System::Drawing::Color::WhiteSmoke;
      this->chartOutput->BackGradientEndColor = System::Drawing::Color::White;
      this->chartOutput->BackGradientType = Dundas::Charting::WinControl::GradientType::DiagonalLeft;
      this->chartOutput->BorderLineColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(26)), 
        static_cast<System::Int32>(static_cast<System::Byte>(59)), static_cast<System::Int32>(static_cast<System::Byte>(105)));
      this->chartOutput->BorderLineStyle = Dundas::Charting::WinControl::ChartDashStyle::Solid;
      this->chartOutput->BorderSkin->FrameBackColor = System::Drawing::Color::CornflowerBlue;
      this->chartOutput->BorderSkin->FrameBackGradientEndColor = System::Drawing::Color::CornflowerBlue;
      this->chartOutput->BorderSkin->PageColor = System::Drawing::SystemColors::Control;
      this->chartOutput->BorderSkin->SkinStyle = Dundas::Charting::WinControl::BorderSkinStyle::Emboss;
      chartArea3->AxisX->LabelStyle->IntervalOffset = 0;
      chartArea3->AxisX->LabelStyle->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisX->LabelStyle->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisX->MajorGrid->Enabled = false;
      chartArea3->AxisX->MajorGrid->Interval = 0;
      chartArea3->AxisX->MajorGrid->IntervalOffset = 0;
      chartArea3->AxisX->MajorGrid->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisX->MajorGrid->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisX->MajorGrid->LineColor = System::Drawing::Color::Silver;
      chartArea3->AxisX->MajorTickMark->Interval = 0;
      chartArea3->AxisX->MajorTickMark->IntervalOffset = 0;
      chartArea3->AxisX->MajorTickMark->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisX->MajorTickMark->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisX->Margin = false;
      chartArea3->AxisX->MinorGrid->LineColor = System::Drawing::Color::Silver;
      chartArea3->AxisX->Title = L"Week";
      chartArea3->AxisX2->LabelStyle->Interval = 0;
      chartArea3->AxisX2->LabelStyle->IntervalOffset = 0;
      chartArea3->AxisX2->LabelStyle->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisX2->LabelStyle->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisX2->MajorGrid->Interval = 0;
      chartArea3->AxisX2->MajorGrid->IntervalOffset = 0;
      chartArea3->AxisX2->MajorGrid->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisX2->MajorGrid->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisX2->MajorGrid->LineColor = System::Drawing::Color::Silver;
      chartArea3->AxisX2->MajorTickMark->Interval = 0;
      chartArea3->AxisX2->MajorTickMark->IntervalOffset = 0;
      chartArea3->AxisX2->MajorTickMark->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisX2->MajorTickMark->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisX2->MinorGrid->LineColor = System::Drawing::Color::Silver;
      chartArea3->AxisY->LabelStyle->Interval = 0;
      chartArea3->AxisY->LabelStyle->IntervalOffset = 0;
      chartArea3->AxisY->LabelStyle->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisY->LabelStyle->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisY->MajorGrid->Interval = 0;
      chartArea3->AxisY->MajorGrid->IntervalOffset = 0;
      chartArea3->AxisY->MajorGrid->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisY->MajorGrid->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisY->MajorGrid->LineColor = System::Drawing::Color::Silver;
      chartArea3->AxisY->MajorTickMark->Interval = 0;
      chartArea3->AxisY->MajorTickMark->IntervalOffset = 0;
      chartArea3->AxisY->MajorTickMark->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisY->MajorTickMark->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisY->Margin = false;
      chartArea3->AxisY->MinorGrid->LineColor = System::Drawing::Color::Silver;
      chartArea3->AxisY->Title = L"# / ha";
      chartArea3->AxisY2->LabelStyle->Interval = 0;
      chartArea3->AxisY2->LabelStyle->IntervalOffset = 0;
      chartArea3->AxisY2->LabelStyle->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisY2->LabelStyle->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisY2->MajorGrid->Interval = 0;
      chartArea3->AxisY2->MajorGrid->IntervalOffset = 0;
      chartArea3->AxisY2->MajorGrid->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisY2->MajorGrid->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisY2->MajorGrid->LineColor = System::Drawing::Color::Silver;
      chartArea3->AxisY2->MajorTickMark->Interval = 0;
      chartArea3->AxisY2->MajorTickMark->IntervalOffset = 0;
      chartArea3->AxisY2->MajorTickMark->IntervalOffsetType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisY2->MajorTickMark->IntervalType = Dundas::Charting::WinControl::DateTimeIntervalType::Auto;
      chartArea3->AxisY2->MinorGrid->LineColor = System::Drawing::Color::Silver;
      chartArea3->BackColor = System::Drawing::Color::White;
      chartArea3->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(26)), static_cast<System::Int32>(static_cast<System::Byte>(59)), 
        static_cast<System::Int32>(static_cast<System::Byte>(105)));
      chartArea3->BorderStyle = Dundas::Charting::WinControl::ChartDashStyle::Solid;
      chartArea3->CursorX->UserEnabled = true;
      chartArea3->CursorX->UserSelection = true;
      chartArea3->CursorY->UserEnabled = true;
      chartArea3->CursorY->UserSelection = true;
      chartArea3->InnerPlotPosition->Auto = false;
      chartArea3->InnerPlotPosition->Height = 91.31669F;
      chartArea3->InnerPlotPosition->Width = 90.36408F;
      chartArea3->InnerPlotPosition->X = 5.64604F;
      chartArea3->InnerPlotPosition->Y = 1.98027F;
      chartArea3->Name = L"Default";
      chartArea3->Position->Auto = false;
      chartArea3->Position->Height = 79.53476F;
      chartArea3->Position->Width = 92.10797F;
      chartArea3->Position->X = 3.756811F;
      chartArea3->Position->Y = 15.82769F;
      chartArea3->ShadowOffset = 2;
      this->chartOutput->ChartAreas->Add(chartArea3);
      legend3->Alignment = System::Drawing::StringAlignment::Far;
      legend3->BackColor = System::Drawing::Color::White;
      legend3->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(26)), static_cast<System::Int32>(static_cast<System::Byte>(59)), 
        static_cast<System::Int32>(static_cast<System::Byte>(105)));
      legend3->Docking = Dundas::Charting::WinControl::LegendDocking::Top;
      legend3->Name = L"Default";
      legend3->ShadowOffset = 2;
      this->chartOutput->Legends->Add(legend3);
      this->chartOutput->Location = System::Drawing::Point(12, 12);
      this->chartOutput->Name = L"chartOutput";
      this->chartOutput->Palette = Dundas::Charting::WinControl::ChartColorPalette::Dundas;
      this->chartOutput->Size = System::Drawing::Size(992, 688);
      this->chartOutput->TabIndex = 0;
      this->chartOutput->Text = L"chartOutput";
      // 
      // btnRunDensim
      // 
      this->btnRunDensim->Location = System::Drawing::Point(741, 706);
      this->btnRunDensim->Name = L"btnRunDensim";
      this->btnRunDensim->Size = System::Drawing::Size(101, 23);
      this->btnRunDensim->TabIndex = 5;
      this->btnRunDensim->Text = L"Run DENSiM";
      this->btnRunDensim->UseVisualStyleBackColor = true;
      this->btnRunDensim->Click += gcnew System::EventHandler(this, &CimsimOutputForm::OnRunDensim);
      // 
      // CimsimOutputForm
      // 
      this->AcceptButton = this->btnMore;
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->CancelButton = this->btnExit;
      this->ClientSize = System::Drawing::Size(1016, 741);
      this->Controls->Add(this->btnRunDensim);
      this->Controls->Add(this->chartOutput);
      this->Controls->Add(this->btnSaveAll);
      this->Controls->Add(this->btnSave);
      this->Controls->Add(this->btnMore);
      this->Controls->Add(this->btnExit);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
      this->Name = L"CimsimOutputForm";
      this->ShowInTaskbar = false;
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
      this->Text = L"CIMSiM Output";
      this->Load += gcnew System::EventHandler(this, &CimsimOutputForm::OnLoad);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chartOutput))->EndInit();
      this->ResumeLayout(false);

    }
#pragma endregion
  };
}
