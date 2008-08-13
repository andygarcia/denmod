#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace gui {


  public ref class ChartForm : public System::Windows::Forms::Form
	{
	public:
    ChartForm( gui::Location ^ location, output::Chart ^ chartData, output::TimePeriod timePeriod, output::TimePeriodFunction timePeriodFunction );
	protected:
		~ChartForm();

  private:
    System::Void OnSave(System::Object^  sender, System::EventArgs^  e);
    
  private:
    gui::Location ^ Location_;
    gui::Container ^ Container_;

  private: Dundas::Charting::WinControl::Chart^  chart;
  private: System::Windows::Forms::Button^  btnExit;
  private: System::Windows::Forms::Button^  btnSave;

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
      Dundas::Charting::WinControl::Legend^  legend1 = (gcnew Dundas::Charting::WinControl::Legend());
      this->chart = (gcnew Dundas::Charting::WinControl::Chart());
      this->btnExit = (gcnew System::Windows::Forms::Button());
      this->btnSave = (gcnew System::Windows::Forms::Button());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart))->BeginInit();
      this->SuspendLayout();
      // 
      // chart
      // 
      this->chart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->chart->BackColor = System::Drawing::Color::WhiteSmoke;
      this->chart->BackGradientEndColor = System::Drawing::Color::White;
      this->chart->BackGradientType = Dundas::Charting::WinControl::GradientType::DiagonalLeft;
      this->chart->BorderLineColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(26)), static_cast<System::Int32>(static_cast<System::Byte>(59)), 
        static_cast<System::Int32>(static_cast<System::Byte>(105)));
      this->chart->BorderLineStyle = Dundas::Charting::WinControl::ChartDashStyle::Solid;
      this->chart->BorderSkin->FrameBackColor = System::Drawing::Color::CornflowerBlue;
      this->chart->BorderSkin->FrameBackGradientEndColor = System::Drawing::Color::CornflowerBlue;
      this->chart->BorderSkin->PageColor = System::Drawing::SystemColors::Control;
      this->chart->BorderSkin->SkinStyle = Dundas::Charting::WinControl::BorderSkinStyle::Emboss;
      legend1->Alignment = System::Drawing::StringAlignment::Far;
      legend1->BackColor = System::Drawing::Color::White;
      legend1->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(26)), static_cast<System::Int32>(static_cast<System::Byte>(59)), 
        static_cast<System::Int32>(static_cast<System::Byte>(105)));
      legend1->Docking = Dundas::Charting::WinControl::LegendDocking::Top;
      legend1->Enabled = false;
      legend1->Name = L"Default";
      legend1->ShadowOffset = 2;
      this->chart->Legends->Add(legend1);
      this->chart->Location = System::Drawing::Point(12, 12);
      this->chart->Name = L"chart";
      this->chart->Palette = Dundas::Charting::WinControl::ChartColorPalette::Dundas;
      this->chart->Size = System::Drawing::Size(992, 688);
      this->chart->TabIndex = 2;
      this->chart->Text = L"chart1";
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
      this->btnSave->Click += gcnew System::EventHandler(this, &ChartForm::OnSave);
      // 
      // ChartForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->CancelButton = this->btnExit;
      this->ClientSize = System::Drawing::Size(1016, 741);
      this->Controls->Add(this->btnSave);
      this->Controls->Add(this->btnExit);
      this->Controls->Add(this->chart);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
      this->Name = L"ChartForm";
      this->ShowInTaskbar = false;
      this->Text = L"ChartForm";
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart))->EndInit();
      this->ResumeLayout(false);

    }
#pragma endregion
};
}
