#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace gui {

	public ref class CimsimExtOutputForm : public System::Windows::Forms::Form
	{
	public:
    CimsimExtOutputForm( gui::Location ^ location );
	protected:
		~CimsimExtOutputForm();
  private: System::Windows::Forms::ComboBox^  cboxTimePeriod;
  protected: 
  private: System::Windows::Forms::Label^  lblTimePeriod;


  protected: 

  private:
    gui::Location ^ Location_;

  private:
    System::Void OnLoad(System::Object^  sender, System::EventArgs^  e);
    System::Void OnView(System::Object^  sender, System::EventArgs^  e);
    System::Void OnViewLocationGraph(System::Object^  sender, System::EventArgs^  e);
    System::Void OnViewContainerGraph(System::Object^  sender, System::EventArgs^  e);
    System::Void OnSelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);

  private: System::Windows::Forms::TabControl^  tabGraphType;
  private: System::Windows::Forms::TabPage^  tabPageLocation;
  private: System::Windows::Forms::TabPage^  tabPageContainer;
  private: System::Windows::Forms::ListBox^  lboxLocationGraphs;
  private: System::Windows::Forms::ListBox^  lboxContainerGraphs;
  private: System::Windows::Forms::Button^  btnView;


  private: System::Windows::Forms::ComboBox^  cboxContainers;
  private: System::Windows::Forms::Button^  btnExit;



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
      this->tabPageContainer = (gcnew System::Windows::Forms::TabPage());
      this->cboxContainers = (gcnew System::Windows::Forms::ComboBox());
      this->lboxContainerGraphs = (gcnew System::Windows::Forms::ListBox());
      this->btnExit = (gcnew System::Windows::Forms::Button());
      this->btnView = (gcnew System::Windows::Forms::Button());
      this->cboxTimePeriod = (gcnew System::Windows::Forms::ComboBox());
      this->lblTimePeriod = (gcnew System::Windows::Forms::Label());
      this->tabGraphType->SuspendLayout();
      this->tabPageLocation->SuspendLayout();
      this->tabPageContainer->SuspendLayout();
      this->SuspendLayout();
      // 
      // tabGraphType
      // 
      this->tabGraphType->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->tabGraphType->Controls->Add(this->tabPageLocation);
      this->tabGraphType->Controls->Add(this->tabPageContainer);
      this->tabGraphType->Location = System::Drawing::Point(12, 12);
      this->tabGraphType->Name = L"tabGraphType";
      this->tabGraphType->SelectedIndex = 0;
      this->tabGraphType->Size = System::Drawing::Size(273, 227);
      this->tabGraphType->TabIndex = 0;
      // 
      // tabPageLocation
      // 
      this->tabPageLocation->Controls->Add(this->lboxLocationGraphs);
      this->tabPageLocation->Location = System::Drawing::Point(4, 24);
      this->tabPageLocation->Name = L"tabPageLocation";
      this->tabPageLocation->Padding = System::Windows::Forms::Padding(3);
      this->tabPageLocation->Size = System::Drawing::Size(265, 199);
      this->tabPageLocation->TabIndex = 0;
      this->tabPageLocation->Text = L"Location Graphs";
      this->tabPageLocation->UseVisualStyleBackColor = true;
      // 
      // lboxLocationGraphs
      // 
      this->lboxLocationGraphs->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->lboxLocationGraphs->FormattingEnabled = true;
      this->lboxLocationGraphs->Location = System::Drawing::Point(6, 6);
      this->lboxLocationGraphs->Name = L"lboxLocationGraphs";
      this->lboxLocationGraphs->Size = System::Drawing::Size(253, 186);
      this->lboxLocationGraphs->TabIndex = 0;
      this->lboxLocationGraphs->SelectedIndexChanged += gcnew System::EventHandler(this, &CimsimExtOutputForm::OnSelectedIndexChanged);
      this->lboxLocationGraphs->DoubleClick += gcnew System::EventHandler(this, &CimsimExtOutputForm::OnViewLocationGraph);
      // 
      // tabPageContainer
      // 
      this->tabPageContainer->Controls->Add(this->cboxContainers);
      this->tabPageContainer->Controls->Add(this->lboxContainerGraphs);
      this->tabPageContainer->Location = System::Drawing::Point(4, 24);
      this->tabPageContainer->Name = L"tabPageContainer";
      this->tabPageContainer->Padding = System::Windows::Forms::Padding(3);
      this->tabPageContainer->Size = System::Drawing::Size(265, 199);
      this->tabPageContainer->TabIndex = 1;
      this->tabPageContainer->Text = L"Container Graphs";
      this->tabPageContainer->UseVisualStyleBackColor = true;
      // 
      // cboxContainers
      // 
      this->cboxContainers->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->cboxContainers->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxContainers->FormattingEnabled = true;
      this->cboxContainers->Location = System::Drawing::Point(6, 6);
      this->cboxContainers->Name = L"cboxContainers";
      this->cboxContainers->Size = System::Drawing::Size(253, 21);
      this->cboxContainers->TabIndex = 0;
      // 
      // lboxContainerGraphs
      // 
      this->lboxContainerGraphs->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->lboxContainerGraphs->FormattingEnabled = true;
      this->lboxContainerGraphs->Location = System::Drawing::Point(6, 33);
      this->lboxContainerGraphs->Name = L"lboxContainerGraphs";
      this->lboxContainerGraphs->Size = System::Drawing::Size(253, 160);
      this->lboxContainerGraphs->TabIndex = 1;
      this->lboxContainerGraphs->DoubleClick += gcnew System::EventHandler(this, &CimsimExtOutputForm::OnViewContainerGraph);
      // 
      // btnExit
      // 
      this->btnExit->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->btnExit->Location = System::Drawing::Point(210, 272);
      this->btnExit->Name = L"btnExit";
      this->btnExit->Size = System::Drawing::Size(75, 23);
      this->btnExit->TabIndex = 3;
      this->btnExit->Text = L"Exit";
      this->btnExit->UseVisualStyleBackColor = true;
      // 
      // btnView
      // 
      this->btnView->Location = System::Drawing::Point(129, 272);
      this->btnView->Name = L"btnView";
      this->btnView->Size = System::Drawing::Size(75, 23);
      this->btnView->TabIndex = 2;
      this->btnView->Text = L"View";
      this->btnView->UseVisualStyleBackColor = true;
      this->btnView->Click += gcnew System::EventHandler(this, &CimsimExtOutputForm::OnView);
      // 
      // cboxTimePeriod
      // 
      this->cboxTimePeriod->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxTimePeriod->FormattingEnabled = true;
      this->cboxTimePeriod->Location = System::Drawing::Point(198, 245);
      this->cboxTimePeriod->Name = L"cboxTimePeriod";
      this->cboxTimePeriod->Size = System::Drawing::Size(83, 21);
      this->cboxTimePeriod->TabIndex = 4;
      // 
      // lblTimePeriod
      // 
      this->lblTimePeriod->AutoSize = true;
      this->lblTimePeriod->Location = System::Drawing::Point(126, 248);
      this->lblTimePeriod->Name = L"lblTimePeriod";
      this->lblTimePeriod->Size = System::Drawing::Size(66, 13);
      this->lblTimePeriod->TabIndex = 5;
      this->lblTimePeriod->Text = L"Time Period:";
      // 
      // CimsimExtOutputForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->CancelButton = this->btnExit;
      this->ClientSize = System::Drawing::Size(297, 307);
      this->Controls->Add(this->lblTimePeriod);
      this->Controls->Add(this->tabGraphType);
      this->Controls->Add(this->cboxTimePeriod);
      this->Controls->Add(this->btnExit);
      this->Controls->Add(this->btnView);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
      this->MaximizeBox = false;
      this->MinimizeBox = false;
      this->Name = L"CimsimExtOutputForm";
      this->ShowInTaskbar = false;
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
      this->Text = L"CIMSiM Graphs";
      this->Load += gcnew System::EventHandler(this, &CimsimExtOutputForm::OnLoad);
      this->tabGraphType->ResumeLayout(false);
      this->tabPageLocation->ResumeLayout(false);
      this->tabPageContainer->ResumeLayout(false);
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  };
}
