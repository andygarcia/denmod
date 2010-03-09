#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace testgui {

	public ref class Testing : public System::Windows::Forms::Form
	{
	public:
		Testing(void);
	protected:
		~Testing();

  private:
    System::Void OnValidatingOutputDirectory(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);
    System::Void OnBrowseDml( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnBrowseOutput( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnRun( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnDragDropInput(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
    System::Void OnDragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);


  private: System::Windows::Forms::Label^  lblDmlFile;
  private: System::Windows::Forms::TextBox^  tboxDmlFile;
  private: System::Windows::Forms::Button^  btnBrowseDml;
  private: System::Windows::Forms::Label^  lblOutput;
  private: System::Windows::Forms::TextBox^  tboxOutput;
  private: System::Windows::Forms::Button^  btnBrowseOutput;
  private: System::Windows::Forms::Label^  lblRuns;
  private: System::Windows::Forms::NumericUpDown^  numRuns;
  private: System::Windows::Forms::Button^  btnRun;
  private: System::Windows::Forms::GroupBox^  gboxUsage;
  private: System::Windows::Forms::RichTextBox^  rboxUsage;
  private: System::Windows::Forms::ErrorProvider^  errPro;
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
      System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Testing::typeid));
      this->tboxDmlFile = (gcnew System::Windows::Forms::TextBox());
      this->btnBrowseDml = (gcnew System::Windows::Forms::Button());
      this->lblDmlFile = (gcnew System::Windows::Forms::Label());
      this->btnRun = (gcnew System::Windows::Forms::Button());
      this->lblOutput = (gcnew System::Windows::Forms::Label());
      this->tboxOutput = (gcnew System::Windows::Forms::TextBox());
      this->btnBrowseOutput = (gcnew System::Windows::Forms::Button());
      this->lblRuns = (gcnew System::Windows::Forms::Label());
      this->numRuns = (gcnew System::Windows::Forms::NumericUpDown());
      this->gboxUsage = (gcnew System::Windows::Forms::GroupBox());
      this->rboxUsage = (gcnew System::Windows::Forms::RichTextBox());
      this->errPro = (gcnew System::Windows::Forms::ErrorProvider(this->components));
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numRuns))->BeginInit();
      this->gboxUsage->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errPro))->BeginInit();
      this->SuspendLayout();
      // 
      // tboxDmlFile
      // 
      this->tboxDmlFile->AllowDrop = true;
      this->tboxDmlFile->Location = System::Drawing::Point(105, 14);
      this->tboxDmlFile->Name = L"tboxDmlFile";
      this->tboxDmlFile->Size = System::Drawing::Size(433, 20);
      this->tboxDmlFile->TabIndex = 0;
      this->tboxDmlFile->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &Testing::OnDragDropInput);
      this->tboxDmlFile->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &Testing::OnDragEnter);
      // 
      // btnBrowseDml
      // 
      this->btnBrowseDml->Location = System::Drawing::Point(562, 12);
      this->btnBrowseDml->Name = L"btnBrowseDml";
      this->btnBrowseDml->Size = System::Drawing::Size(32, 23);
      this->btnBrowseDml->TabIndex = 1;
      this->btnBrowseDml->Text = L"...";
      this->btnBrowseDml->UseVisualStyleBackColor = true;
      this->btnBrowseDml->Click += gcnew System::EventHandler(this, &Testing::OnBrowseDml);
      // 
      // lblDmlFile
      // 
      this->lblDmlFile->AutoSize = true;
      this->lblDmlFile->Location = System::Drawing::Point(44, 17);
      this->lblDmlFile->Name = L"lblDmlFile";
      this->lblDmlFile->Size = System::Drawing::Size(55, 13);
      this->lblDmlFile->TabIndex = 2;
      this->lblDmlFile->Text = L".DML File:";
      // 
      // btnRun
      // 
      this->btnRun->Location = System::Drawing::Point(519, 95);
      this->btnRun->Name = L"btnRun";
      this->btnRun->Size = System::Drawing::Size(75, 23);
      this->btnRun->TabIndex = 3;
      this->btnRun->Text = L"Run";
      this->btnRun->UseVisualStyleBackColor = true;
      this->btnRun->Click += gcnew System::EventHandler(this, &Testing::OnRun);
      // 
      // lblOutput
      // 
      this->lblOutput->AutoSize = true;
      this->lblOutput->Location = System::Drawing::Point(12, 46);
      this->lblOutput->Name = L"lblOutput";
      this->lblOutput->Size = System::Drawing::Size(87, 13);
      this->lblOutput->TabIndex = 4;
      this->lblOutput->Text = L"Output Directory:";
      // 
      // tboxOutput
      // 
      this->tboxOutput->AllowDrop = true;
      this->tboxOutput->Location = System::Drawing::Point(105, 43);
      this->tboxOutput->Name = L"tboxOutput";
      this->tboxOutput->Size = System::Drawing::Size(433, 20);
      this->tboxOutput->TabIndex = 5;
      this->tboxOutput->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &Testing::OnDragDropInput);
      this->tboxOutput->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &Testing::OnValidatingOutputDirectory);
      this->tboxOutput->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &Testing::OnDragEnter);
      // 
      // btnBrowseOutput
      // 
      this->btnBrowseOutput->Location = System::Drawing::Point(562, 41);
      this->btnBrowseOutput->Name = L"btnBrowseOutput";
      this->btnBrowseOutput->Size = System::Drawing::Size(32, 23);
      this->btnBrowseOutput->TabIndex = 1;
      this->btnBrowseOutput->Text = L"...";
      this->btnBrowseOutput->UseVisualStyleBackColor = true;
      this->btnBrowseOutput->Click += gcnew System::EventHandler(this, &Testing::OnBrowseOutput);
      // 
      // lblRuns
      // 
      this->lblRuns->AutoSize = true;
      this->lblRuns->Location = System::Drawing::Point(42, 73);
      this->lblRuns->Name = L"lblRuns";
      this->lblRuns->Size = System::Drawing::Size(57, 13);
      this->lblRuns->TabIndex = 6;
      this->lblRuns->Text = L"# of Runs:";
      // 
      // numRuns
      // 
      this->numRuns->Location = System::Drawing::Point(105, 71);
      this->numRuns->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {30, 0, 0, 0});
      this->numRuns->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numRuns->Name = L"numRuns";
      this->numRuns->Size = System::Drawing::Size(42, 20);
      this->numRuns->TabIndex = 7;
      this->numRuns->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->numRuns->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      // 
      // gboxUsage
      // 
      this->gboxUsage->Controls->Add(this->rboxUsage);
      this->gboxUsage->Location = System::Drawing::Point(12, 124);
      this->gboxUsage->Name = L"gboxUsage";
      this->gboxUsage->Size = System::Drawing::Size(582, 109);
      this->gboxUsage->TabIndex = 9;
      this->gboxUsage->TabStop = false;
      this->gboxUsage->Text = L"Usage";
      // 
      // rboxUsage
      // 
      this->rboxUsage->BackColor = System::Drawing::SystemColors::Control;
      this->rboxUsage->BorderStyle = System::Windows::Forms::BorderStyle::None;
      this->rboxUsage->Location = System::Drawing::Point(6, 19);
      this->rboxUsage->Name = L"rboxUsage";
      this->rboxUsage->Size = System::Drawing::Size(570, 84);
      this->rboxUsage->TabIndex = 0;
      this->rboxUsage->Text = resources->GetString(L"rboxUsage.Text");
      // 
      // errPro
      // 
      this->errPro->ContainerControl = this;
      // 
      // Testing
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(606, 246);
      this->Controls->Add(this->gboxUsage);
      this->Controls->Add(this->numRuns);
      this->Controls->Add(this->lblRuns);
      this->Controls->Add(this->tboxOutput);
      this->Controls->Add(this->lblOutput);
      this->Controls->Add(this->btnRun);
      this->Controls->Add(this->lblDmlFile);
      this->Controls->Add(this->btnBrowseOutput);
      this->Controls->Add(this->btnBrowseDml);
      this->Controls->Add(this->tboxDmlFile);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
      this->Name = L"Testing";
      this->Text = L"CIMSiM Testing Frontend";
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numRuns))->EndInit();
      this->gboxUsage->ResumeLayout(false);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errPro))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  };
}
