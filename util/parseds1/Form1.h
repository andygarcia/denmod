#pragma once

#include "DensimPrn.h"



namespace ParsePRN {

	using namespace System;
  using namespace System::Xml;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;
  using namespace System::IO;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();

      String ^ configFile = Application::StartupPath + "\\parseprn.config";
      XmlDocument ^ cfgXML = gcnew XmlDocument();
      try {
        cfgXML->Load( configFile );
        XmlNode ^ xmln;

        xmln = cfgXML->DocumentElement->SelectSingleNode( "InputURI" );
        if( xmln->HasChildNodes ) tboxInput->Text = xmln->FirstChild->Value;

        xmln = cfgXML->DocumentElement->SelectSingleNode( "OutputURI" );
        if( xmln->HasChildNodes ) tboxOutput->Text = xmln->FirstChild->Value;
      }
      catch( FileNotFoundException ^ e ) {
        // no config loaded, destructor will create new config file
        Console::WriteLine( e->Message );
      }
      catch( Exception ^ e ) {
        Console::WriteLine( e->Message );
      }
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}

      // save config
      String ^ configFile = Application::StartupPath + "\\parseprn.config";
      XmlDocument ^ cfgXml = gcnew XmlDocument();
      try {
        cfgXml->Load( configFile );
        XmlNode ^ xmln;

        xmln = cfgXml->DocumentElement->SelectSingleNode( "InputURI" );
        if( xmln->HasChildNodes ) {
          xmln->FirstChild->Value = tboxInput->Text;
        }
        else {
          xmln->AppendChild( cfgXml->CreateTextNode( tboxInput->Text ) );
        }

        xmln = cfgXml->DocumentElement->SelectSingleNode( "OutputURI" );
        if( xmln->HasChildNodes ) {
          xmln->FirstChild->Value = tboxOutput->Text;
        }
        else {
          xmln->AppendChild( cfgXml->CreateTextNode( tboxOutput->Text ) );
        }
        
        cfgXml->Save( configFile );
      }
      catch( FileNotFoundException ^ e ) {
        System::Console::WriteLine( e->Message );

        // create the file
        XmlDeclaration ^ declaration = cfgXml->CreateXmlDeclaration( "1.0", "utf-8", nullptr );

        // create and append the root element
        XmlElement ^ rootNode  = cfgXml->CreateElement( "configuration" );
        cfgXml->InsertBefore( declaration, cfgXml->DocumentElement ); 
        cfgXml->AppendChild(rootNode);

        // create and append InputURI element and value
        XmlElement ^ inputNode = cfgXml->CreateElement( "InputURI" );
        rootNode->AppendChild( inputNode );
        XmlText ^ inputText = cfgXml->CreateTextNode( tboxInput->Text );
        inputNode->AppendChild( inputText );
        
        // create and append OutputURI element and value
        XmlElement ^ outputNode = cfgXml->CreateElement( "OutputURI" );
        rootNode->AppendChild( outputNode );
        XmlText ^ outputText = cfgXml->CreateTextNode( tboxOutput->Text );
        outputNode->AppendChild( outputText );

        cfgXml->Save( configFile );
      }
      catch( Exception ^ e ) {
        System::Console::WriteLine( e->Message );
      }
		}

  private: System::Windows::Forms::Label^  lblInput;
  private: System::Windows::Forms::Label^  lblOutput;
  private: System::Windows::Forms::TextBox^  tboxInput;
  private: System::Windows::Forms::TextBox^  tboxOutput;
  private: System::Windows::Forms::Button^  button1;
  private: System::Windows::Forms::Button^  btnInput;
  private: System::Windows::Forms::Button^  btnOutput;

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
      this->lblInput = (gcnew System::Windows::Forms::Label());
      this->lblOutput = (gcnew System::Windows::Forms::Label());
      this->tboxInput = (gcnew System::Windows::Forms::TextBox());
      this->tboxOutput = (gcnew System::Windows::Forms::TextBox());
      this->button1 = (gcnew System::Windows::Forms::Button());
      this->btnInput = (gcnew System::Windows::Forms::Button());
      this->btnOutput = (gcnew System::Windows::Forms::Button());
      this->SuspendLayout();
      // 
      // lblInput
      // 
      this->lblInput->AutoSize = true;
      this->lblInput->Location = System::Drawing::Point(12, 19);
      this->lblInput->Name = L"lblInput";
      this->lblInput->Size = System::Drawing::Size(79, 13);
      this->lblInput->TabIndex = 0;
      this->lblInput->Text = L"Input Directory:";
      // 
      // lblOutput
      // 
      this->lblOutput->AutoSize = true;
      this->lblOutput->Location = System::Drawing::Point(12, 45);
      this->lblOutput->Name = L"lblOutput";
      this->lblOutput->Size = System::Drawing::Size(84, 13);
      this->lblOutput->TabIndex = 3;
      this->lblOutput->Text = L"OutputDirectory:";
      // 
      // tboxInput
      // 
      this->tboxInput->AllowDrop = true;
      this->tboxInput->Location = System::Drawing::Point(102, 16);
      this->tboxInput->Name = L"tboxInput";
      this->tboxInput->Size = System::Drawing::Size(423, 20);
      this->tboxInput->TabIndex = 1;
      this->tboxInput->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &Form1::OnDragDropInput);
      this->tboxInput->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &Form1::OnDragEnter);
      // 
      // tboxOutput
      // 
      this->tboxOutput->AllowDrop = true;
      this->tboxOutput->Location = System::Drawing::Point(102, 42);
      this->tboxOutput->Name = L"tboxOutput";
      this->tboxOutput->Size = System::Drawing::Size(423, 20);
      this->tboxOutput->TabIndex = 4;
      this->tboxOutput->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &Form1::OnDragDropOutput);
      this->tboxOutput->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &Form1::OnDragEnter);
      // 
      // button1
      // 
      this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->button1->Location = System::Drawing::Point(484, 75);
      this->button1->Name = L"button1";
      this->button1->Size = System::Drawing::Size(75, 23);
      this->button1->TabIndex = 6;
      this->button1->Text = L"Parse";
      this->button1->UseVisualStyleBackColor = true;
      this->button1->Click += gcnew System::EventHandler(this, &Form1::OnParse);
      // 
      // btnInput
      // 
      this->btnInput->Location = System::Drawing::Point(535, 16);
      this->btnInput->Name = L"btnInput";
      this->btnInput->Size = System::Drawing::Size(24, 20);
      this->btnInput->TabIndex = 2;
      this->btnInput->Text = L"...";
      this->btnInput->UseVisualStyleBackColor = true;
      this->btnInput->Click += gcnew System::EventHandler(this, &Form1::OnBrowseInput);
      // 
      // btnOutput
      // 
      this->btnOutput->Location = System::Drawing::Point(535, 42);
      this->btnOutput->Name = L"btnOutput";
      this->btnOutput->Size = System::Drawing::Size(24, 20);
      this->btnOutput->TabIndex = 5;
      this->btnOutput->Text = L"...";
      this->btnOutput->UseVisualStyleBackColor = true;
      this->btnOutput->Click += gcnew System::EventHandler(this, &Form1::OnBrowseOutput);
      // 
      // Form1
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(571, 110);
      this->Controls->Add(this->btnOutput);
      this->Controls->Add(this->btnInput);
      this->Controls->Add(this->button1);
      this->Controls->Add(this->tboxOutput);
      this->Controls->Add(this->tboxInput);
      this->Controls->Add(this->lblOutput);
      this->Controls->Add(this->lblInput);
      this->Name = L"Form1";
      this->Text = L"DENSiM 1.0 Output Parser";
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion

  private:
    System::Void OnParse(System::Object^  sender, System::EventArgs^  e)
    {
      System::String ^ previousDirectory = System::Environment::CurrentDirectory;
      System::Environment::CurrentDirectory = tboxInput->Text;

      array<String^>^ dFiles = Directory::GetFiles( tboxInput->Text, "DG*" );
      array<String^>^ rFiles = Directory::GetFiles( tboxInput->Text, "RG*" );
      if( dFiles->Length > 0 && rFiles->Length > 0 ) {
        Windows::Forms::MessageBox::Show( "Both DS 1.0 and RC 1.0 output files exists.  Check directory contents." );
        return;
      }

      DensimPrn ^ dp = gcnew DensimPrn( tboxInput->Text );
      dp->Parse();
      System::Environment::CurrentDirectory = tboxOutput->Text;
      dp->Output();

      System::Environment::CurrentDirectory = previousDirectory;
    }
  private:
    System::Void OnBrowseInput(System::Object^  sender, System::EventArgs^  e)
    {
      FolderBrowserDialog ^ fbd = gcnew FolderBrowserDialog();
      fbd->SelectedPath = tboxInput->Text;
      if( fbd->ShowDialog() == Windows::Forms::DialogResult::OK ) {
        tboxInput->Text = fbd->SelectedPath;
      }
    }
  private:
    System::Void OnBrowseOutput(System::Object^  sender, System::EventArgs^  e)
    {
      FolderBrowserDialog ^ fbd = gcnew FolderBrowserDialog();
      fbd->SelectedPath = tboxOutput->Text;
      if( fbd->ShowDialog() == Windows::Forms::DialogResult::OK ) {
        tboxOutput->Text = fbd->SelectedPath;
      }
    }
  private:
    System::Void OnDragDropInput(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
    {
      if( e->Data->GetDataPresent( DataFormats::FileDrop ) ) {
        array<Object ^> ^ a = (array<Object ^>^) e->Data->GetData( DataFormats::FileDrop );
        if( a != nullptr ) {
          if( a->Length > 1 ) {}  // more than one file dragged... ignore and simply read first filedrop
          tboxInput->Text = a[0]->ToString();
        }
      }
    }
  private:
    System::Void OnDragDropOutput(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
    {
      if( e->Data->GetDataPresent( DataFormats::FileDrop ) ) {
        array<Object ^> ^ a = (array<Object ^>^) e->Data->GetData( DataFormats::FileDrop );
        if( a != nullptr ) {
          if( a->Length > 1 ) {}  // more than one file dragged... ignore and simply read first filedrop
          tboxOutput->Text = a[0]->ToString();
        }
      }
    }
  private:
    System::Void OnDragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
    {
      if( e->Data->GetDataPresent( DataFormats::FileDrop ) ) {
        e->Effect = DragDropEffects::Copy;
      }
      else {
        e->Effect = DragDropEffects::None;
      }
    }
  };
}
