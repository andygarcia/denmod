#pragma once

#include "CimsimPanel.h"
#include "DensimPanel.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace gui {

	public ref class MainForm : public System::Windows::Forms::Form
	{
  // Enums
  private:
    enum class SaveType {
      Save,
      SaveAs,
      SaveCopyAs
    };

  // Constructors
	public:
		MainForm(void);
    MainForm(System::String ^ filename);
    void Initialize(void);
	protected:
		~MainForm();
  
  // Methods
  private:
    bool NewDocument(void);
    bool OpenDocument(System::String ^ newFilename);
    void OpenSampleLocation(void);
    bool SaveDocument(SaveType type);
    bool CloseDocument(void);
    bool IsDocumentDirty(void);

    void UpdateBindings(void);
    void UpdateTitleBar(void);

    System::Void OnLoad( System::Object ^ sender, System::EventArgs ^ e );
    System::Void MenuItemHandler( System::Object^ sender, System::EventArgs^ e );

    System::Void OnImportWeather( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnCloneWeather( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnRemoveWeather( System::Object ^ sender, System::EventArgs ^ e );
    void OpenWeatherTemplate(void);

    void ShowAbout(void);

  private:
    CimsimPanel ^ CimsimPanel_;
    DensimPanel ^ DensimPanel_;

    DmlFile ^ ActiveDocument;

  private: System::Windows::Forms::MenuStrip^  menuStrip;
  private: System::Windows::Forms::ToolStrip^  toolStrip;

  private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
  private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
  private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem;
  private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;



  private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;









  private: System::Windows::Forms::ToolStripMenuItem^  toolsToolStripMenuItem;

  private: System::Windows::Forms::ToolStripMenuItem^  optionsToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^  tsmiHelpAbout;





  private: System::Windows::Forms::ToolStripButton^  newToolStripButton;
  private: System::Windows::Forms::ToolStripButton^  openToolStripButton;
  private: System::Windows::Forms::ToolStripButton^  saveToolStripButton;
  private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator;




  private: System::Windows::Forms::ToolStripButton^  helpToolStripButton;
  private: System::Windows::Forms::ListBox^  lboxWeather;
  private: System::Windows::Forms::Label^  lblLocName;
  private: System::Windows::Forms::TextBox^  tboxLocName;
  private: System::Windows::Forms::RichTextBox^  rboxNotes;
  private: System::Windows::Forms::Label^  lblLocNotes;
  private: System::Windows::Forms::TabControl^  tabSimulations;

  private: System::Windows::Forms::TabPage^  tabpgCimsim;
  private: System::Windows::Forms::TabPage^  tabpgDensim;


  private: System::Windows::Forms::TabControl^  tabLocation;

  private: System::Windows::Forms::TabPage^  tabpgLocation;


  private: System::Windows::Forms::Button^  btnAddWeather;
  private: System::Windows::Forms::BindingSource^  LocationBinding;
  private: System::Windows::Forms::Button^  btnRemoveWeather;


  private: System::Windows::Forms::TabControl^  tabWeather;
  private: System::Windows::Forms::TabPage^  tabpgWeather;
private: System::Windows::Forms::ToolStripMenuItem^  openWeatherTemplateToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  tsmiOpenSampleLocation;





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
      System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
      this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
      this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->tsmiOpenSampleLocation = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
      this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
      this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->toolsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->openWeatherTemplateToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->tsmiHelpAbout = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->toolStrip = (gcnew System::Windows::Forms::ToolStrip());
      this->newToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
      this->openToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
      this->saveToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
      this->toolStripSeparator = (gcnew System::Windows::Forms::ToolStripSeparator());
      this->helpToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
      this->lboxWeather = (gcnew System::Windows::Forms::ListBox());
      this->lblLocName = (gcnew System::Windows::Forms::Label());
      this->tboxLocName = (gcnew System::Windows::Forms::TextBox());
      this->rboxNotes = (gcnew System::Windows::Forms::RichTextBox());
      this->lblLocNotes = (gcnew System::Windows::Forms::Label());
      this->tabSimulations = (gcnew System::Windows::Forms::TabControl());
      this->tabpgCimsim = (gcnew System::Windows::Forms::TabPage());
      this->tabpgDensim = (gcnew System::Windows::Forms::TabPage());
      this->tabLocation = (gcnew System::Windows::Forms::TabControl());
      this->tabpgLocation = (gcnew System::Windows::Forms::TabPage());
      this->btnRemoveWeather = (gcnew System::Windows::Forms::Button());
      this->btnAddWeather = (gcnew System::Windows::Forms::Button());
      this->LocationBinding = (gcnew System::Windows::Forms::BindingSource(this->components));
      this->tabWeather = (gcnew System::Windows::Forms::TabControl());
      this->tabpgWeather = (gcnew System::Windows::Forms::TabPage());
      this->menuStrip->SuspendLayout();
      this->toolStrip->SuspendLayout();
      this->tabSimulations->SuspendLayout();
      this->tabLocation->SuspendLayout();
      this->tabpgLocation->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->LocationBinding))->BeginInit();
      this->tabWeather->SuspendLayout();
      this->tabpgWeather->SuspendLayout();
      this->SuspendLayout();
      // 
      // menuStrip
      // 
      this->menuStrip->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->fileToolStripMenuItem, 
        this->toolsToolStripMenuItem, this->helpToolStripMenuItem});
      this->menuStrip->Location = System::Drawing::Point(0, 0);
      this->menuStrip->Name = L"menuStrip";
      this->menuStrip->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
      this->menuStrip->Size = System::Drawing::Size(816, 24);
      this->menuStrip->TabIndex = 1;
      this->menuStrip->Text = L"menuStrip1";
      // 
      // fileToolStripMenuItem
      // 
      this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {this->newToolStripMenuItem, 
        this->openToolStripMenuItem, this->tsmiOpenSampleLocation, this->toolStripSeparator2, this->saveToolStripMenuItem, this->saveAsToolStripMenuItem, 
        this->toolStripSeparator3, this->exitToolStripMenuItem});
      this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
      this->fileToolStripMenuItem->Size = System::Drawing::Size(35, 20);
      this->fileToolStripMenuItem->Text = L"&File";
      // 
      // newToolStripMenuItem
      // 
      this->newToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"newToolStripMenuItem.Image")));
      this->newToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
      this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
      this->newToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
      this->newToolStripMenuItem->Size = System::Drawing::Size(185, 22);
      this->newToolStripMenuItem->Text = L"&New";
      this->newToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::MenuItemHandler);
      // 
      // openToolStripMenuItem
      // 
      this->openToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"openToolStripMenuItem.Image")));
      this->openToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
      this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
      this->openToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
      this->openToolStripMenuItem->Size = System::Drawing::Size(185, 22);
      this->openToolStripMenuItem->Text = L"&Open";
      this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::MenuItemHandler);
      // 
      // tsmiOpenSampleLocation
      // 
      this->tsmiOpenSampleLocation->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tsmiOpenSampleLocation.Image")));
      this->tsmiOpenSampleLocation->ImageTransparentColor = System::Drawing::Color::Magenta;
      this->tsmiOpenSampleLocation->Name = L"tsmiOpenSampleLocation";
      this->tsmiOpenSampleLocation->Size = System::Drawing::Size(185, 22);
      this->tsmiOpenSampleLocation->Text = L"O&pen Sample Location";
      this->tsmiOpenSampleLocation->Click += gcnew System::EventHandler(this, &MainForm::MenuItemHandler);
      // 
      // toolStripSeparator2
      // 
      this->toolStripSeparator2->Name = L"toolStripSeparator2";
      this->toolStripSeparator2->Size = System::Drawing::Size(182, 6);
      // 
      // saveToolStripMenuItem
      // 
      this->saveToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"saveToolStripMenuItem.Image")));
      this->saveToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
      this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
      this->saveToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
      this->saveToolStripMenuItem->Size = System::Drawing::Size(185, 22);
      this->saveToolStripMenuItem->Text = L"&Save";
      this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::MenuItemHandler);
      // 
      // saveAsToolStripMenuItem
      // 
      this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
      this->saveAsToolStripMenuItem->Size = System::Drawing::Size(185, 22);
      this->saveAsToolStripMenuItem->Text = L"Save &As";
      this->saveAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::MenuItemHandler);
      // 
      // toolStripSeparator3
      // 
      this->toolStripSeparator3->Name = L"toolStripSeparator3";
      this->toolStripSeparator3->Size = System::Drawing::Size(182, 6);
      // 
      // exitToolStripMenuItem
      // 
      this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
      this->exitToolStripMenuItem->Size = System::Drawing::Size(185, 22);
      this->exitToolStripMenuItem->Text = L"E&xit";
      this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::MenuItemHandler);
      // 
      // toolsToolStripMenuItem
      // 
      this->toolsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->optionsToolStripMenuItem, 
        this->openWeatherTemplateToolStripMenuItem});
      this->toolsToolStripMenuItem->Name = L"toolsToolStripMenuItem";
      this->toolsToolStripMenuItem->Size = System::Drawing::Size(45, 20);
      this->toolsToolStripMenuItem->Text = L"&Tools";
      // 
      // optionsToolStripMenuItem
      // 
      this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
      this->optionsToolStripMenuItem->Size = System::Drawing::Size(203, 22);
      this->optionsToolStripMenuItem->Text = L"&Options";
      // 
      // openWeatherTemplateToolStripMenuItem
      // 
      this->openWeatherTemplateToolStripMenuItem->Name = L"openWeatherTemplateToolStripMenuItem";
      this->openWeatherTemplateToolStripMenuItem->Size = System::Drawing::Size(203, 22);
      this->openWeatherTemplateToolStripMenuItem->Text = L"Open Weather Template...";
      this->openWeatherTemplateToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::MenuItemHandler);
      // 
      // helpToolStripMenuItem
      // 
      this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->tsmiHelpAbout});
      this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
      this->helpToolStripMenuItem->Size = System::Drawing::Size(41, 20);
      this->helpToolStripMenuItem->Text = L"&Help";
      // 
      // tsmiHelpAbout
      // 
      this->tsmiHelpAbout->Name = L"tsmiHelpAbout";
      this->tsmiHelpAbout->Size = System::Drawing::Size(152, 22);
      this->tsmiHelpAbout->Text = L"&About...";
      this->tsmiHelpAbout->Click += gcnew System::EventHandler(this, &MainForm::MenuItemHandler);
      // 
      // toolStrip
      // 
      this->toolStrip->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
      this->toolStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->newToolStripButton, 
        this->openToolStripButton, this->saveToolStripButton, this->toolStripSeparator, this->helpToolStripButton});
      this->toolStrip->Location = System::Drawing::Point(0, 24);
      this->toolStrip->Name = L"toolStrip";
      this->toolStrip->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
      this->toolStrip->Size = System::Drawing::Size(816, 25);
      this->toolStrip->TabIndex = 2;
      this->toolStrip->Text = L"toolStrip1";
      // 
      // newToolStripButton
      // 
      this->newToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
      this->newToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"newToolStripButton.Image")));
      this->newToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
      this->newToolStripButton->Name = L"newToolStripButton";
      this->newToolStripButton->Size = System::Drawing::Size(23, 22);
      this->newToolStripButton->Text = L"&New";
      this->newToolStripButton->Click += gcnew System::EventHandler(this, &MainForm::MenuItemHandler);
      // 
      // openToolStripButton
      // 
      this->openToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
      this->openToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"openToolStripButton.Image")));
      this->openToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
      this->openToolStripButton->Name = L"openToolStripButton";
      this->openToolStripButton->Size = System::Drawing::Size(23, 22);
      this->openToolStripButton->Text = L"&Open";
      this->openToolStripButton->Click += gcnew System::EventHandler(this, &MainForm::MenuItemHandler);
      // 
      // saveToolStripButton
      // 
      this->saveToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
      this->saveToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"saveToolStripButton.Image")));
      this->saveToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
      this->saveToolStripButton->Name = L"saveToolStripButton";
      this->saveToolStripButton->Size = System::Drawing::Size(23, 22);
      this->saveToolStripButton->Text = L"&Save";
      this->saveToolStripButton->Click += gcnew System::EventHandler(this, &MainForm::MenuItemHandler);
      // 
      // toolStripSeparator
      // 
      this->toolStripSeparator->Name = L"toolStripSeparator";
      this->toolStripSeparator->Size = System::Drawing::Size(6, 25);
      // 
      // helpToolStripButton
      // 
      this->helpToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
      this->helpToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"helpToolStripButton.Image")));
      this->helpToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
      this->helpToolStripButton->Name = L"helpToolStripButton";
      this->helpToolStripButton->Size = System::Drawing::Size(23, 22);
      this->helpToolStripButton->Text = L"He&lp";
      // 
      // lboxWeather
      // 
      this->lboxWeather->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->lboxWeather->FormattingEnabled = true;
      this->lboxWeather->Location = System::Drawing::Point(87, 6);
      this->lboxWeather->Name = L"lboxWeather";
      this->lboxWeather->Size = System::Drawing::Size(145, 82);
      this->lboxWeather->Sorted = true;
      this->lboxWeather->TabIndex = 32;
      // 
      // lblLocName
      // 
      this->lblLocName->AutoSize = true;
      this->lblLocName->Location = System::Drawing::Point(6, 9);
      this->lblLocName->Margin = System::Windows::Forms::Padding(3);
      this->lblLocName->Name = L"lblLocName";
      this->lblLocName->Size = System::Drawing::Size(38, 13);
      this->lblLocName->TabIndex = 27;
      this->lblLocName->Text = L"Name:";
      // 
      // tboxLocName
      // 
      this->tboxLocName->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->tboxLocName->Location = System::Drawing::Point(50, 6);
      this->tboxLocName->Name = L"tboxLocName";
      this->tboxLocName->Size = System::Drawing::Size(469, 20);
      this->tboxLocName->TabIndex = 28;
      // 
      // rboxNotes
      // 
      this->rboxNotes->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->rboxNotes->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->rboxNotes->Location = System::Drawing::Point(50, 32);
      this->rboxNotes->Name = L"rboxNotes";
      this->rboxNotes->Size = System::Drawing::Size(469, 56);
      this->rboxNotes->TabIndex = 29;
      this->rboxNotes->Text = L"";
      // 
      // lblLocNotes
      // 
      this->lblLocNotes->AutoSize = true;
      this->lblLocNotes->Location = System::Drawing::Point(6, 32);
      this->lblLocNotes->Name = L"lblLocNotes";
      this->lblLocNotes->Size = System::Drawing::Size(38, 13);
      this->lblLocNotes->TabIndex = 26;
      this->lblLocNotes->Text = L"Notes:";
      // 
      // tabSimulations
      // 
      this->tabSimulations->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->tabSimulations->Controls->Add(this->tabpgCimsim);
      this->tabSimulations->Controls->Add(this->tabpgDensim);
      this->tabSimulations->Location = System::Drawing::Point(10, 179);
      this->tabSimulations->MinimumSize = System::Drawing::Size(794, 369);
      this->tabSimulations->Name = L"tabSimulations";
      this->tabSimulations->SelectedIndex = 0;
      this->tabSimulations->Size = System::Drawing::Size(794, 370);
      this->tabSimulations->TabIndex = 33;
      // 
      // tabpgCimsim
      // 
      this->tabpgCimsim->Location = System::Drawing::Point(4, 24);
      this->tabpgCimsim->Name = L"tabpgCimsim";
      this->tabpgCimsim->Padding = System::Windows::Forms::Padding(3);
      this->tabpgCimsim->Size = System::Drawing::Size(786, 342);
      this->tabpgCimsim->TabIndex = 0;
      this->tabpgCimsim->Text = L"CIMSiM";
      this->tabpgCimsim->UseVisualStyleBackColor = true;
      // 
      // tabpgDensim
      // 
      this->tabpgDensim->Location = System::Drawing::Point(4, 24);
      this->tabpgDensim->Name = L"tabpgDensim";
      this->tabpgDensim->Padding = System::Windows::Forms::Padding(3);
      this->tabpgDensim->Size = System::Drawing::Size(786, 342);
      this->tabpgDensim->TabIndex = 1;
      this->tabpgDensim->Text = L"DENSiM";
      this->tabpgDensim->UseVisualStyleBackColor = true;
      // 
      // tabLocation
      // 
      this->tabLocation->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->tabLocation->Controls->Add(this->tabpgLocation);
      this->tabLocation->Location = System::Drawing::Point(12, 52);
      this->tabLocation->Name = L"tabLocation";
      this->tabLocation->SelectedIndex = 0;
      this->tabLocation->Size = System::Drawing::Size(533, 121);
      this->tabLocation->TabIndex = 35;
      // 
      // tabpgLocation
      // 
      this->tabpgLocation->Controls->Add(this->tboxLocName);
      this->tabpgLocation->Controls->Add(this->rboxNotes);
      this->tabpgLocation->Controls->Add(this->lblLocName);
      this->tabpgLocation->Controls->Add(this->lblLocNotes);
      this->tabpgLocation->Location = System::Drawing::Point(4, 24);
      this->tabpgLocation->Name = L"tabpgLocation";
      this->tabpgLocation->Padding = System::Windows::Forms::Padding(3);
      this->tabpgLocation->Size = System::Drawing::Size(525, 93);
      this->tabpgLocation->TabIndex = 0;
      this->tabpgLocation->Text = L"Location";
      this->tabpgLocation->UseVisualStyleBackColor = true;
      // 
      // btnRemoveWeather
      // 
      this->btnRemoveWeather->Location = System::Drawing::Point(6, 35);
      this->btnRemoveWeather->Name = L"btnRemoveWeather";
      this->btnRemoveWeather->Size = System::Drawing::Size(75, 23);
      this->btnRemoveWeather->TabIndex = 34;
      this->btnRemoveWeather->Text = L"Remove";
      this->btnRemoveWeather->UseVisualStyleBackColor = true;
      this->btnRemoveWeather->Click += gcnew System::EventHandler(this, &MainForm::OnRemoveWeather);
      // 
      // btnAddWeather
      // 
      this->btnAddWeather->Location = System::Drawing::Point(6, 6);
      this->btnAddWeather->Name = L"btnAddWeather";
      this->btnAddWeather->Size = System::Drawing::Size(75, 23);
      this->btnAddWeather->TabIndex = 33;
      this->btnAddWeather->Text = L"Add";
      this->btnAddWeather->UseVisualStyleBackColor = true;
      this->btnAddWeather->Click += gcnew System::EventHandler(this, &MainForm::OnImportWeather);
      // 
      // tabWeather
      // 
      this->tabWeather->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->tabWeather->Controls->Add(this->tabpgWeather);
      this->tabWeather->Location = System::Drawing::Point(551, 52);
      this->tabWeather->Name = L"tabWeather";
      this->tabWeather->SelectedIndex = 0;
      this->tabWeather->Size = System::Drawing::Size(246, 121);
      this->tabWeather->TabIndex = 0;
      // 
      // tabpgWeather
      // 
      this->tabpgWeather->Controls->Add(this->lboxWeather);
      this->tabpgWeather->Controls->Add(this->btnRemoveWeather);
      this->tabpgWeather->Controls->Add(this->btnAddWeather);
      this->tabpgWeather->Location = System::Drawing::Point(4, 24);
      this->tabpgWeather->Name = L"tabpgWeather";
      this->tabpgWeather->Padding = System::Windows::Forms::Padding(3);
      this->tabpgWeather->Size = System::Drawing::Size(238, 93);
      this->tabpgWeather->TabIndex = 0;
      this->tabpgWeather->Text = L"Weather";
      this->tabpgWeather->UseVisualStyleBackColor = true;
      // 
      // MainForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->BackColor = System::Drawing::SystemColors::ControlLight;
      this->ClientSize = System::Drawing::Size(816, 560);
      this->Controls->Add(this->tabWeather);
      this->Controls->Add(this->tabLocation);
      this->Controls->Add(this->tabSimulations);
      this->Controls->Add(this->toolStrip);
      this->Controls->Add(this->menuStrip);
      this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
      this->MinimumSize = System::Drawing::Size(824, 589);
      this->Name = L"MainForm";
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
      this->Text = L"Dengue Models 3.0";
      this->Load += gcnew System::EventHandler(this, &MainForm::OnLoad);
      this->menuStrip->ResumeLayout(false);
      this->menuStrip->PerformLayout();
      this->toolStrip->ResumeLayout(false);
      this->toolStrip->PerformLayout();
      this->tabSimulations->ResumeLayout(false);
      this->tabLocation->ResumeLayout(false);
      this->tabpgLocation->ResumeLayout(false);
      this->tabpgLocation->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->LocationBinding))->EndInit();
      this->tabWeather->ResumeLayout(false);
      this->tabpgWeather->ResumeLayout(false);
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  };
}
