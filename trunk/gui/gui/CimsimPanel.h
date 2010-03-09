#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace gui {

	public ref class CimsimPanel : public System::Windows::Forms::UserControl
	{
	public:
    CimsimPanel( BindingSource ^ locationBinding );
	protected:
		~CimsimPanel();
  private: System::Windows::Forms::SplitContainer^  splitCimsim;

  private:
    Collections::Generic::Dictionary<System::Type^, System::Type^> ^ ControlFormMapping;
    UserSettings ^ _userSettings;

  private:
    void RunCimsim(void);

    System::Void OnLoad( System::Object ^ sender, System::EventArgs ^ e );

    System::Void OnAddContainer( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnEditContainer( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnRemoveContainer( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnCopyContainer( System::Object ^ sender, System::EventArgs ^ e );

    System::Void OnMouseMoveContainers( System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e );
    System::Void OnMouseLeaveContainers( System::Object ^ sender, System::EventArgs ^ e );

    System::Void OnAddControl( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnEditControl( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnRemoveControl( System::Object ^ sender, System::EventArgs ^ e );

    System::Void OnClickBiology( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnRunFoodFitter( System::Object^ sender, System::EventArgs^ e );

    System::Void OnRunCimsim( System::Object ^ sender, System::EventArgs ^ e );

  private:
    gui::Location ^ GetLocation(void);
    BindingSource ^ LocationBinding;

    // tooltips
    DateTime dtContainerLastShown;
    int PreviousContainerHoverIndex;

  private: System::Windows::Forms::ToolTip^  ttContainers;
  private: System::Windows::Forms::Button^  btnRunSim;
  private: System::Windows::Forms::Button^  btnBiology;
  private: System::Windows::Forms::GroupBox^  gboxControls;
  private: System::Windows::Forms::ListBox^  lboxControls;
  private: System::Windows::Forms::Button^  btnRemoveControl;
  private: System::Windows::Forms::Button^  btnAddControl;
  private: System::Windows::Forms::Button^  btnEditControl;
  private: System::Windows::Forms::GroupBox^  gboxContainer;
  private: System::Windows::Forms::Button^  btnRemoveContainer;
  private: System::Windows::Forms::Button^  btnEditContainer;
  private: System::Windows::Forms::Button^  btnAddContainer;
  private: System::Windows::Forms::ListBox^  lboxContainers;
  private: System::Windows::Forms::Button^  btnFoodFitter;
  private: System::Windows::Forms::Button^  btnCopyContainer;

  private: System::Windows::Forms::Button^  btnImportContainer;
  private: System::Windows::Forms::Button^  btnImportControl;
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
      this->btnRunSim = (gcnew System::Windows::Forms::Button());
      this->btnBiology = (gcnew System::Windows::Forms::Button());
      this->gboxControls = (gcnew System::Windows::Forms::GroupBox());
      this->lboxControls = (gcnew System::Windows::Forms::ListBox());
      this->btnRemoveControl = (gcnew System::Windows::Forms::Button());
      this->btnImportControl = (gcnew System::Windows::Forms::Button());
      this->btnAddControl = (gcnew System::Windows::Forms::Button());
      this->btnEditControl = (gcnew System::Windows::Forms::Button());
      this->gboxContainer = (gcnew System::Windows::Forms::GroupBox());
      this->btnFoodFitter = (gcnew System::Windows::Forms::Button());
      this->btnRemoveContainer = (gcnew System::Windows::Forms::Button());
      this->btnEditContainer = (gcnew System::Windows::Forms::Button());
      this->btnCopyContainer = (gcnew System::Windows::Forms::Button());
      this->btnImportContainer = (gcnew System::Windows::Forms::Button());
      this->btnAddContainer = (gcnew System::Windows::Forms::Button());
      this->lboxContainers = (gcnew System::Windows::Forms::ListBox());
      this->ttContainers = (gcnew System::Windows::Forms::ToolTip(this->components));
      this->splitCimsim = (gcnew System::Windows::Forms::SplitContainer());
      this->gboxControls->SuspendLayout();
      this->gboxContainer->SuspendLayout();
      this->splitCimsim->Panel1->SuspendLayout();
      this->splitCimsim->Panel2->SuspendLayout();
      this->splitCimsim->SuspendLayout();
      this->SuspendLayout();
      // 
      // btnRunSim
      // 
      this->btnRunSim->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnRunSim->Location = System::Drawing::Point(282, 303);
      this->btnRunSim->Name = L"btnRunSim";
      this->btnRunSim->Size = System::Drawing::Size(100, 23);
      this->btnRunSim->TabIndex = 32;
      this->btnRunSim->Text = L"Run CIMSiM...";
      this->btnRunSim->UseVisualStyleBackColor = true;
      this->btnRunSim->Click += gcnew System::EventHandler(this, &CimsimPanel::OnRunCimsim);
      // 
      // btnBiology
      // 
      this->btnBiology->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
      this->btnBiology->Location = System::Drawing::Point(9, 303);
      this->btnBiology->Name = L"btnBiology";
      this->btnBiology->Size = System::Drawing::Size(75, 23);
      this->btnBiology->TabIndex = 30;
      this->btnBiology->Text = L"Biology";
      this->btnBiology->UseVisualStyleBackColor = true;
      this->btnBiology->Click += gcnew System::EventHandler(this, &CimsimPanel::OnClickBiology);
      // 
      // gboxControls
      // 
      this->gboxControls->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->gboxControls->Controls->Add(this->lboxControls);
      this->gboxControls->Controls->Add(this->btnRemoveControl);
      this->gboxControls->Controls->Add(this->btnImportControl);
      this->gboxControls->Controls->Add(this->btnAddControl);
      this->gboxControls->Controls->Add(this->btnEditControl);
      this->gboxControls->Location = System::Drawing::Point(3, 3);
      this->gboxControls->Name = L"gboxControls";
      this->gboxControls->Size = System::Drawing::Size(379, 294);
      this->gboxControls->TabIndex = 15;
      this->gboxControls->TabStop = false;
      this->gboxControls->Text = L"Control Interventions";
      // 
      // lboxControls
      // 
      this->lboxControls->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->lboxControls->FormattingEnabled = true;
      this->lboxControls->Location = System::Drawing::Point(87, 19);
      this->lboxControls->Name = L"lboxControls";
      this->lboxControls->Size = System::Drawing::Size(286, 264);
      this->lboxControls->TabIndex = 2;
      this->lboxControls->DoubleClick += gcnew System::EventHandler(this, &CimsimPanel::OnEditControl);
      // 
      // btnRemoveControl
      // 
      this->btnRemoveControl->Location = System::Drawing::Point(6, 77);
      this->btnRemoveControl->Name = L"btnRemoveControl";
      this->btnRemoveControl->Size = System::Drawing::Size(75, 23);
      this->btnRemoveControl->TabIndex = 1;
      this->btnRemoveControl->Text = L"Remove";
      this->btnRemoveControl->UseVisualStyleBackColor = true;
      this->btnRemoveControl->Click += gcnew System::EventHandler(this, &CimsimPanel::OnRemoveControl);
      // 
      // btnImportControl
      // 
      this->btnImportControl->Location = System::Drawing::Point(6, 106);
      this->btnImportControl->Name = L"btnImportControl";
      this->btnImportControl->Size = System::Drawing::Size(75, 23);
      this->btnImportControl->TabIndex = 1;
      this->btnImportControl->Text = L"Import";
      this->btnImportControl->UseVisualStyleBackColor = true;
      this->btnImportControl->Visible = false;
      // 
      // btnAddControl
      // 
      this->btnAddControl->Location = System::Drawing::Point(6, 19);
      this->btnAddControl->Name = L"btnAddControl";
      this->btnAddControl->Size = System::Drawing::Size(75, 23);
      this->btnAddControl->TabIndex = 1;
      this->btnAddControl->Text = L"Add";
      this->btnAddControl->UseVisualStyleBackColor = true;
      this->btnAddControl->Click += gcnew System::EventHandler(this, &CimsimPanel::OnAddControl);
      // 
      // btnEditControl
      // 
      this->btnEditControl->Location = System::Drawing::Point(6, 48);
      this->btnEditControl->Name = L"btnEditControl";
      this->btnEditControl->Size = System::Drawing::Size(75, 23);
      this->btnEditControl->TabIndex = 1;
      this->btnEditControl->Text = L"Edit";
      this->btnEditControl->UseVisualStyleBackColor = true;
      this->btnEditControl->Click += gcnew System::EventHandler(this, &CimsimPanel::OnEditControl);
      // 
      // gboxContainer
      // 
      this->gboxContainer->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->gboxContainer->Controls->Add(this->btnFoodFitter);
      this->gboxContainer->Controls->Add(this->btnRemoveContainer);
      this->gboxContainer->Controls->Add(this->btnEditContainer);
      this->gboxContainer->Controls->Add(this->btnCopyContainer);
      this->gboxContainer->Controls->Add(this->btnImportContainer);
      this->gboxContainer->Controls->Add(this->btnAddContainer);
      this->gboxContainer->Controls->Add(this->lboxContainers);
      this->gboxContainer->Location = System::Drawing::Point(3, 3);
      this->gboxContainer->Name = L"gboxContainer";
      this->gboxContainer->Size = System::Drawing::Size(379, 294);
      this->gboxContainer->TabIndex = 16;
      this->gboxContainer->TabStop = false;
      this->gboxContainer->Text = L"Containers";
      // 
      // btnFoodFitter
      // 
      this->btnFoodFitter->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
      this->btnFoodFitter->Location = System::Drawing::Point(6, 265);
      this->btnFoodFitter->Name = L"btnFoodFitter";
      this->btnFoodFitter->Size = System::Drawing::Size(75, 23);
      this->btnFoodFitter->TabIndex = 34;
      this->btnFoodFitter->Text = L"Food Fitter";
      this->btnFoodFitter->UseVisualStyleBackColor = true;
      this->btnFoodFitter->Click += gcnew System::EventHandler(this, &CimsimPanel::OnRunFoodFitter);
      // 
      // btnRemoveContainer
      // 
      this->btnRemoveContainer->Location = System::Drawing::Point(6, 77);
      this->btnRemoveContainer->Name = L"btnRemoveContainer";
      this->btnRemoveContainer->Size = System::Drawing::Size(75, 23);
      this->btnRemoveContainer->TabIndex = 1;
      this->btnRemoveContainer->Text = L"Remove";
      this->btnRemoveContainer->UseVisualStyleBackColor = true;
      this->btnRemoveContainer->Click += gcnew System::EventHandler(this, &CimsimPanel::OnRemoveContainer);
      // 
      // btnEditContainer
      // 
      this->btnEditContainer->Location = System::Drawing::Point(6, 48);
      this->btnEditContainer->Name = L"btnEditContainer";
      this->btnEditContainer->Size = System::Drawing::Size(75, 23);
      this->btnEditContainer->TabIndex = 1;
      this->btnEditContainer->Text = L"Edit";
      this->btnEditContainer->UseVisualStyleBackColor = true;
      this->btnEditContainer->Click += gcnew System::EventHandler(this, &CimsimPanel::OnEditContainer);
      // 
      // btnCopyContainer
      // 
      this->btnCopyContainer->Location = System::Drawing::Point(6, 106);
      this->btnCopyContainer->Name = L"btnCopyContainer";
      this->btnCopyContainer->Size = System::Drawing::Size(75, 23);
      this->btnCopyContainer->TabIndex = 1;
      this->btnCopyContainer->Text = L"Copy";
      this->btnCopyContainer->UseVisualStyleBackColor = true;
      this->btnCopyContainer->Click += gcnew System::EventHandler(this, &CimsimPanel::OnCopyContainer);
      // 
      // btnImportContainer
      // 
      this->btnImportContainer->Location = System::Drawing::Point(6, 135);
      this->btnImportContainer->Name = L"btnImportContainer";
      this->btnImportContainer->Size = System::Drawing::Size(75, 23);
      this->btnImportContainer->TabIndex = 1;
      this->btnImportContainer->Text = L"Import";
      this->btnImportContainer->UseVisualStyleBackColor = true;
      this->btnImportContainer->Visible = false;
      // 
      // btnAddContainer
      // 
      this->btnAddContainer->Location = System::Drawing::Point(6, 19);
      this->btnAddContainer->Name = L"btnAddContainer";
      this->btnAddContainer->Size = System::Drawing::Size(75, 23);
      this->btnAddContainer->TabIndex = 1;
      this->btnAddContainer->Text = L"Add";
      this->btnAddContainer->UseVisualStyleBackColor = true;
      this->btnAddContainer->Click += gcnew System::EventHandler(this, &CimsimPanel::OnAddContainer);
      // 
      // lboxContainers
      // 
      this->lboxContainers->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->lboxContainers->FormattingEnabled = true;
      this->lboxContainers->Location = System::Drawing::Point(87, 19);
      this->lboxContainers->Name = L"lboxContainers";
      this->lboxContainers->Size = System::Drawing::Size(286, 264);
      this->lboxContainers->TabIndex = 0;
      this->lboxContainers->Tag = L"289, 173";
      this->lboxContainers->DoubleClick += gcnew System::EventHandler(this, &CimsimPanel::OnEditContainer);
      this->lboxContainers->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &CimsimPanel::OnMouseMoveContainers);
      this->lboxContainers->MouseLeave += gcnew System::EventHandler(this, &CimsimPanel::OnMouseLeaveContainers);
      // 
      // ttContainers
      // 
      this->ttContainers->AutoPopDelay = 5000;
      this->ttContainers->InitialDelay = 500;
      this->ttContainers->ReshowDelay = 500;
      // 
      // splitCimsim
      // 
      this->splitCimsim->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->splitCimsim->Location = System::Drawing::Point(6, 6);
      this->splitCimsim->Name = L"splitCimsim";
      // 
      // splitCimsim.Panel1
      // 
      this->splitCimsim->Panel1->Controls->Add(this->btnBiology);
      this->splitCimsim->Panel1->Controls->Add(this->gboxContainer);
      // 
      // splitCimsim.Panel2
      // 
      this->splitCimsim->Panel2->Controls->Add(this->btnRunSim);
      this->splitCimsim->Panel2->Controls->Add(this->gboxControls);
      this->splitCimsim->Size = System::Drawing::Size(774, 329);
      this->splitCimsim->SplitterDistance = 385;
      this->splitCimsim->TabIndex = 33;
      // 
      // CimsimPanel
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->BackColor = System::Drawing::Color::Transparent;
      this->Controls->Add(this->splitCimsim);
      this->MinimumSize = System::Drawing::Size(457, 245);
      this->Name = L"CimsimPanel";
      this->Padding = System::Windows::Forms::Padding(3);
      this->Size = System::Drawing::Size(786, 341);
      this->Tag = L"786, 341";
      this->Load += gcnew System::EventHandler(this, &CimsimPanel::OnLoad);
      this->gboxControls->ResumeLayout(false);
      this->gboxContainer->ResumeLayout(false);
      this->splitCimsim->Panel1->ResumeLayout(false);
      this->splitCimsim->Panel2->ResumeLayout(false);
      this->splitCimsim->ResumeLayout(false);
      this->ResumeLayout(false);

    }
#pragma endregion
  };
}
