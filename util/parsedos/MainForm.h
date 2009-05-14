#pragma once


namespace parsedos {

	using namespace System;
  using namespace System::Xml;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;
  using namespace System::IO;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void);
	protected:
		~MainForm();

  private:
    System::Void OnParse(System::Object^  sender, System::EventArgs^  e);
    System::Void OnHelp( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnBrowseInput(System::Object^  sender, System::EventArgs^  e);
    System::Void OnDragDropInput(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
    System::Void OnDragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);

    void ParseCimsim(void);
    void ParseDensim(void);

  private: System::Windows::Forms::TextBox^  tboxCimsimInput;
  private: System::Windows::Forms::Button^  btnCimsimBrowse;




  private: System::Windows::Forms::Button^  btnParse;





  private: System::Windows::Forms::Button^  btnHelp;
  private: System::Windows::Forms::CheckBox^  cboxXml;
  private: System::Windows::Forms::CheckBox^  cboxTxt;


  private: System::Windows::Forms::GroupBox^  gboxOutput;
  private: System::Windows::Forms::GroupBox^  gboxCimsimInput;
  private: System::Windows::Forms::TabControl^  tabCimsimDensim;


  private: System::Windows::Forms::TabPage^  tabPageCimsim;
  private: System::Windows::Forms::TabPage^  tabPageDensim;
  private: System::Windows::Forms::GroupBox^  gboxDensimInput;
  private: System::Windows::Forms::TextBox^  tboxDensimInput;
  private: System::Windows::Forms::Button^  btnDensimBrowse;











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
      this->tboxCimsimInput = (gcnew System::Windows::Forms::TextBox());
      this->btnParse = (gcnew System::Windows::Forms::Button());
      this->btnCimsimBrowse = (gcnew System::Windows::Forms::Button());
      this->btnHelp = (gcnew System::Windows::Forms::Button());
      this->cboxXml = (gcnew System::Windows::Forms::CheckBox());
      this->cboxTxt = (gcnew System::Windows::Forms::CheckBox());
      this->gboxOutput = (gcnew System::Windows::Forms::GroupBox());
      this->gboxCimsimInput = (gcnew System::Windows::Forms::GroupBox());
      this->tabCimsimDensim = (gcnew System::Windows::Forms::TabControl());
      this->tabPageCimsim = (gcnew System::Windows::Forms::TabPage());
      this->tabPageDensim = (gcnew System::Windows::Forms::TabPage());
      this->gboxDensimInput = (gcnew System::Windows::Forms::GroupBox());
      this->tboxDensimInput = (gcnew System::Windows::Forms::TextBox());
      this->btnDensimBrowse = (gcnew System::Windows::Forms::Button());
      this->gboxOutput->SuspendLayout();
      this->gboxCimsimInput->SuspendLayout();
      this->tabCimsimDensim->SuspendLayout();
      this->tabPageCimsim->SuspendLayout();
      this->tabPageDensim->SuspendLayout();
      this->gboxDensimInput->SuspendLayout();
      this->SuspendLayout();
      // 
      // tboxCimsimInput
      // 
      this->tboxCimsimInput->AllowDrop = true;
      this->tboxCimsimInput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
      this->tboxCimsimInput->Location = System::Drawing::Point(6, 19);
      this->tboxCimsimInput->Name = L"tboxCimsimInput";
      this->tboxCimsimInput->Size = System::Drawing::Size(179, 20);
      this->tboxCimsimInput->TabIndex = 1;
      this->tboxCimsimInput->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::OnDragDropInput);
      this->tboxCimsimInput->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::OnDragEnter);
      // 
      // btnParse
      // 
      this->btnParse->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->btnParse->Location = System::Drawing::Point(178, 172);
      this->btnParse->Name = L"btnParse";
      this->btnParse->Size = System::Drawing::Size(75, 23);
      this->btnParse->TabIndex = 6;
      this->btnParse->Text = L"Parse";
      this->btnParse->UseVisualStyleBackColor = true;
      this->btnParse->Click += gcnew System::EventHandler(this, &MainForm::OnParse);
      // 
      // btnCimsimBrowse
      // 
      this->btnCimsimBrowse->Anchor = System::Windows::Forms::AnchorStyles::Right;
      this->btnCimsimBrowse->Location = System::Drawing::Point(191, 18);
      this->btnCimsimBrowse->Name = L"btnCimsimBrowse";
      this->btnCimsimBrowse->Size = System::Drawing::Size(24, 20);
      this->btnCimsimBrowse->TabIndex = 2;
      this->btnCimsimBrowse->Text = L"...";
      this->btnCimsimBrowse->UseVisualStyleBackColor = true;
      this->btnCimsimBrowse->Click += gcnew System::EventHandler(this, &MainForm::OnBrowseInput);
      // 
      // btnHelp
      // 
      this->btnHelp->Location = System::Drawing::Point(12, 172);
      this->btnHelp->Name = L"btnHelp";
      this->btnHelp->Size = System::Drawing::Size(75, 23);
      this->btnHelp->TabIndex = 6;
      this->btnHelp->Text = L"Help";
      this->btnHelp->UseVisualStyleBackColor = true;
      this->btnHelp->Click += gcnew System::EventHandler(this, &MainForm::OnHelp);
      // 
      // cboxXml
      // 
      this->cboxXml->AutoSize = true;
      this->cboxXml->Location = System::Drawing::Point(6, 19);
      this->cboxXml->Name = L"cboxXml";
      this->cboxXml->Size = System::Drawing::Size(139, 17);
      this->cboxXml->TabIndex = 7;
      this->cboxXml->Text = L"Excel Spreadsheet (xml)";
      this->cboxXml->UseVisualStyleBackColor = true;
      // 
      // cboxTxt
      // 
      this->cboxTxt->AutoSize = true;
      this->cboxTxt->Location = System::Drawing::Point(6, 42);
      this->cboxTxt->Name = L"cboxTxt";
      this->cboxTxt->Size = System::Drawing::Size(96, 17);
      this->cboxTxt->TabIndex = 7;
      this->cboxTxt->Text = L"Plain Text (.txt)";
      this->cboxTxt->UseVisualStyleBackColor = true;
      // 
      // gboxOutput
      // 
      this->gboxOutput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->gboxOutput->Controls->Add(this->cboxXml);
      this->gboxOutput->Controls->Add(this->cboxTxt);
      this->gboxOutput->Location = System::Drawing::Point(12, 98);
      this->gboxOutput->Name = L"gboxOutput";
      this->gboxOutput->Size = System::Drawing::Size(241, 68);
      this->gboxOutput->TabIndex = 8;
      this->gboxOutput->TabStop = false;
      this->gboxOutput->Text = L"Output Formats:";
      // 
      // gboxCimsimInput
      // 
      this->gboxCimsimInput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->gboxCimsimInput->Controls->Add(this->tboxCimsimInput);
      this->gboxCimsimInput->Controls->Add(this->btnCimsimBrowse);
      this->gboxCimsimInput->Location = System::Drawing::Point(6, 3);
      this->gboxCimsimInput->Name = L"gboxCimsimInput";
      this->gboxCimsimInput->Size = System::Drawing::Size(221, 45);
      this->gboxCimsimInput->TabIndex = 8;
      this->gboxCimsimInput->TabStop = false;
      this->gboxCimsimInput->Text = L"Input Directory";
      // 
      // tabCimsimDensim
      // 
      this->tabCimsimDensim->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->tabCimsimDensim->Controls->Add(this->tabPageCimsim);
      this->tabCimsimDensim->Controls->Add(this->tabPageDensim);
      this->tabCimsimDensim->Location = System::Drawing::Point(12, 12);
      this->tabCimsimDensim->Name = L"tabCimsimDensim";
      this->tabCimsimDensim->SelectedIndex = 0;
      this->tabCimsimDensim->Size = System::Drawing::Size(241, 80);
      this->tabCimsimDensim->TabIndex = 9;
      // 
      // tabPageCimsim
      // 
      this->tabPageCimsim->Controls->Add(this->gboxCimsimInput);
      this->tabPageCimsim->Location = System::Drawing::Point(4, 22);
      this->tabPageCimsim->Name = L"tabPageCimsim";
      this->tabPageCimsim->Padding = System::Windows::Forms::Padding(3);
      this->tabPageCimsim->Size = System::Drawing::Size(233, 54);
      this->tabPageCimsim->TabIndex = 0;
      this->tabPageCimsim->Text = L"CIMSiM";
      this->tabPageCimsim->UseVisualStyleBackColor = true;
      // 
      // tabPageDensim
      // 
      this->tabPageDensim->Controls->Add(this->gboxDensimInput);
      this->tabPageDensim->Location = System::Drawing::Point(4, 22);
      this->tabPageDensim->Name = L"tabPageDensim";
      this->tabPageDensim->Padding = System::Windows::Forms::Padding(3);
      this->tabPageDensim->Size = System::Drawing::Size(233, 54);
      this->tabPageDensim->TabIndex = 1;
      this->tabPageDensim->Text = L"DENSiM";
      this->tabPageDensim->UseVisualStyleBackColor = true;
      // 
      // gboxDensimInput
      // 
      this->gboxDensimInput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->gboxDensimInput->Controls->Add(this->tboxDensimInput);
      this->gboxDensimInput->Controls->Add(this->btnDensimBrowse);
      this->gboxDensimInput->Location = System::Drawing::Point(6, 3);
      this->gboxDensimInput->Name = L"gboxDensimInput";
      this->gboxDensimInput->Size = System::Drawing::Size(221, 45);
      this->gboxDensimInput->TabIndex = 10;
      this->gboxDensimInput->TabStop = false;
      this->gboxDensimInput->Text = L"Input Directory";
      // 
      // tboxDensimInput
      // 
      this->tboxDensimInput->AllowDrop = true;
      this->tboxDensimInput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->tboxDensimInput->Location = System::Drawing::Point(6, 19);
      this->tboxDensimInput->Name = L"tboxDensimInput";
      this->tboxDensimInput->Size = System::Drawing::Size(179, 20);
      this->tboxDensimInput->TabIndex = 1;
      this->tboxDensimInput->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::OnDragDropInput);
      this->tboxDensimInput->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::OnDragEnter);
      // 
      // btnDensimBrowse
      // 
      this->btnDensimBrowse->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->btnDensimBrowse->Location = System::Drawing::Point(191, 18);
      this->btnDensimBrowse->Name = L"btnDensimBrowse";
      this->btnDensimBrowse->Size = System::Drawing::Size(24, 20);
      this->btnDensimBrowse->TabIndex = 2;
      this->btnDensimBrowse->Text = L"...";
      this->btnDensimBrowse->UseVisualStyleBackColor = true;
      this->btnDensimBrowse->Click += gcnew System::EventHandler(this, &MainForm::OnBrowseInput);
      // 
      // MainForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(265, 209);
      this->Controls->Add(this->tabCimsimDensim);
      this->Controls->Add(this->gboxOutput);
      this->Controls->Add(this->btnHelp);
      this->Controls->Add(this->btnParse);
      this->MaximumSize = System::Drawing::Size(1024, 239);
      this->MinimumSize = System::Drawing::Size(239, 239);
      this->Name = L"MainForm";
      this->Text = L"DENMOD 1.0 (DOS) Output Parser";
      this->gboxOutput->ResumeLayout(false);
      this->gboxOutput->PerformLayout();
      this->gboxCimsimInput->ResumeLayout(false);
      this->gboxCimsimInput->PerformLayout();
      this->tabCimsimDensim->ResumeLayout(false);
      this->tabPageCimsim->ResumeLayout(false);
      this->tabPageDensim->ResumeLayout(false);
      this->gboxDensimInput->ResumeLayout(false);
      this->gboxDensimInput->PerformLayout();
      this->ResumeLayout(false);

    }
#pragma endregion
  };
}
