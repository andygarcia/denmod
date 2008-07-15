#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace gui {

	public ref class DensimExtOutputForm : public System::Windows::Forms::Form
	{
	public:
    DensimExtOutputForm( gui::Location ^ location );
	protected:
		~DensimExtOutputForm();

  private:
    gui::Location ^ Location_;

  private:
    System::Void OnLoad(System::Object^  sender, System::EventArgs^  e);
    System::Void OnViewLocationGraph(System::Object^  sender, System::EventArgs^  e);
    System::Void OnViewVirusGraph( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnView(System::Object^  sender, System::EventArgs^  e);
    output::ChartInfo ^ DetailedSeroprevalence(void);

  private: System::Windows::Forms::TabControl^  tabGraphType;
  private: System::Windows::Forms::TabPage^  tabPageLocation;
  private: System::Windows::Forms::TabPage^  tabPageVirus;
  private: System::Windows::Forms::ListBox^  lboxVirusGraphs;
  private: System::Windows::Forms::ListBox^  lboxLocationGraphs;
  private: System::Windows::Forms::Button^  btnView;

  private: System::Windows::Forms::Button^  btnExitLocation;

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
      this->tabGraphType = (gcnew System::Windows::Forms::TabControl());
      this->tabPageLocation = (gcnew System::Windows::Forms::TabPage());
      this->lboxLocationGraphs = (gcnew System::Windows::Forms::ListBox());
      this->tabPageVirus = (gcnew System::Windows::Forms::TabPage());
      this->lboxVirusGraphs = (gcnew System::Windows::Forms::ListBox());
      this->btnExitLocation = (gcnew System::Windows::Forms::Button());
      this->btnView = (gcnew System::Windows::Forms::Button());
      this->tabGraphType->SuspendLayout();
      this->tabPageLocation->SuspendLayout();
      this->tabPageVirus->SuspendLayout();
      this->SuspendLayout();
      // 
      // tabGraphType
      // 
      this->tabGraphType->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->tabGraphType->Controls->Add(this->tabPageLocation);
      this->tabGraphType->Controls->Add(this->tabPageVirus);
      this->tabGraphType->Location = System::Drawing::Point(12, 12);
      this->tabGraphType->Name = L"tabGraphType";
      this->tabGraphType->SelectedIndex = 0;
      this->tabGraphType->Size = System::Drawing::Size(220, 304);
      this->tabGraphType->TabIndex = 0;
      // 
      // tabPageLocation
      // 
      this->tabPageLocation->Controls->Add(this->lboxLocationGraphs);
      this->tabPageLocation->Location = System::Drawing::Point(4, 24);
      this->tabPageLocation->Name = L"tabPageLocation";
      this->tabPageLocation->Padding = System::Windows::Forms::Padding(3);
      this->tabPageLocation->Size = System::Drawing::Size(212, 276);
      this->tabPageLocation->TabIndex = 0;
      this->tabPageLocation->Text = L"Humans & Mosquitoes";
      this->tabPageLocation->UseVisualStyleBackColor = true;
      // 
      // lboxLocationGraphs
      // 
      this->lboxLocationGraphs->FormattingEnabled = true;
      this->lboxLocationGraphs->Location = System::Drawing::Point(6, 6);
      this->lboxLocationGraphs->Name = L"lboxLocationGraphs";
      this->lboxLocationGraphs->Size = System::Drawing::Size(200, 264);
      this->lboxLocationGraphs->TabIndex = 1;
      this->lboxLocationGraphs->DoubleClick += gcnew System::EventHandler(this, &DensimExtOutputForm::OnViewLocationGraph);
      // 
      // tabPageVirus
      // 
      this->tabPageVirus->Controls->Add(this->lboxVirusGraphs);
      this->tabPageVirus->Location = System::Drawing::Point(4, 24);
      this->tabPageVirus->Name = L"tabPageVirus";
      this->tabPageVirus->Size = System::Drawing::Size(212, 276);
      this->tabPageVirus->TabIndex = 1;
      this->tabPageVirus->Text = L"Virus";
      this->tabPageVirus->UseVisualStyleBackColor = true;
      // 
      // lboxVirusGraphs
      // 
      this->lboxVirusGraphs->FormattingEnabled = true;
      this->lboxVirusGraphs->Location = System::Drawing::Point(3, 3);
      this->lboxVirusGraphs->Name = L"lboxVirusGraphs";
      this->lboxVirusGraphs->Size = System::Drawing::Size(206, 264);
      this->lboxVirusGraphs->TabIndex = 2;
      this->lboxVirusGraphs->DoubleClick += gcnew System::EventHandler(this, &DensimExtOutputForm::OnViewVirusGraph);
      // 
      // btnExitLocation
      // 
      this->btnExitLocation->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnExitLocation->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->btnExitLocation->Location = System::Drawing::Point(157, 322);
      this->btnExitLocation->Name = L"btnExitLocation";
      this->btnExitLocation->Size = System::Drawing::Size(75, 23);
      this->btnExitLocation->TabIndex = 3;
      this->btnExitLocation->Text = L"Exit";
      this->btnExitLocation->UseVisualStyleBackColor = true;
      // 
      // btnView
      // 
      this->btnView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnView->Location = System::Drawing::Point(76, 322);
      this->btnView->Name = L"btnView";
      this->btnView->Size = System::Drawing::Size(75, 23);
      this->btnView->TabIndex = 2;
      this->btnView->Text = L"View";
      this->btnView->UseVisualStyleBackColor = true;
      this->btnView->Click += gcnew System::EventHandler(this, &DensimExtOutputForm::OnView);
      // 
      // DensimExtOutputForm
      // 
      this->AcceptButton = this->btnView;
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->CancelButton = this->btnExitLocation;
      this->ClientSize = System::Drawing::Size(244, 357);
      this->Controls->Add(this->btnView);
      this->Controls->Add(this->btnExitLocation);
      this->Controls->Add(this->tabGraphType);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
      this->MinimumSize = System::Drawing::Size(250, 384);
      this->Name = L"DensimExtOutputForm";
      this->ShowInTaskbar = false;
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
      this->Text = L"Densim Graphs";
      this->Load += gcnew System::EventHandler(this, &DensimExtOutputForm::OnLoad);
      this->tabGraphType->ResumeLayout(false);
      this->tabPageLocation->ResumeLayout(false);
      this->tabPageVirus->ResumeLayout(false);
      this->ResumeLayout(false);

    }
#pragma endregion
};
}
