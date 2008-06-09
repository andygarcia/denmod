#include "StdAfx.h"
#include "MainForm.h"

using namespace System::IO;
using namespace parsecs1;



MainForm::MainForm(void)
{
	InitializeComponent();

  String ^ configFile = Application::StartupPath + "\\parsecs1.config";
  XmlDocument ^ cfgXML = gcnew XmlDocument();
  try {
    cfgXML->Load( configFile );
    XmlNode ^ xmln;

    xmln = cfgXML->DocumentElement->SelectSingleNode( "InputURI" );
    tboxInput->Text = xmln->FirstChild->Value;
  }
  catch( FileNotFoundException ^ e ) {
    // no config loaded, destructor will create new config file
    Console::WriteLine( e->Message );
  }
  catch( Exception ^ e ) {
    Console::WriteLine( e->Message );
  }
}



MainForm::~MainForm()
{
	if( components ) {
		delete components;
	}

  // save config
  String ^ configFile = Application::StartupPath + "\\parsecs1.config";
  XmlDocument ^ cfgXml = gcnew XmlDocument();
  try {
    cfgXml->Load( configFile );
    XmlNode ^ xmln;

    xmln = cfgXml->DocumentElement->SelectSingleNode( "InputURI" );
    xmln->FirstChild->Value = tboxInput->Text;
    
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

    // save xml to disk
    cfgXml->Save( configFile );
  }
  catch( Exception ^ e ) {
    System::Console::WriteLine( e->Message );
  }
}



System::Void
MainForm::OnParse(System::Object^  sender, System::EventArgs^  e)
{
  System::String ^ previousDirectory = System::Environment::CurrentDirectory;
  CimsimParser ^ cp = gcnew CimsimParser();

  if( chkLocation->Checked ) {
    System::Environment::CurrentDirectory = tboxInput->Text;
    if( cp->ParseLocation() ) {
    //cp->OutputLocation( CimsimParser::OutputType::ASCII );
    cp->OutputLocation( CimsimParser::OutputType::XML );
    }
  }
  if( chkContainer->Checked ) {
    System::Environment::CurrentDirectory = tboxInput->Text;
    if( cp->ParseContainer() ) {
      //cp->OutputContainer( CimsimParser::OutputType::ASCII );
      cp->OutputContainer( CimsimParser::OutputType::XML );
    }
  }
  if( chkSurvivals->Checked ) {
    System::Environment::CurrentDirectory = tboxInput->Text;
    if( cp->ParseSurvivals() ) {
      //cp->OutputSurvivals( CimsimParser::OutputType::ASCII );
      cp->OutputSurvivals( CimsimParser::OutputType::XML );
    }
  }
  if( chkLarvalData->Checked ) {
    System::Environment::CurrentDirectory = tboxInput->Text;
    if( cp->ParseLarvalData() ) {
      //cp->OutputLarvalData( CimsimParser::OutputType::ASCII );
      cp->OutputLarvalData( CimsimParser::OutputType::XML );
    }
  }

  System::Environment::CurrentDirectory = previousDirectory;
}



System::Void
MainForm::OnBrowseInput(System::Object^  sender, System::EventArgs^  e)
{
  FolderBrowserDialog ^ fbd = gcnew FolderBrowserDialog();
  fbd->SelectedPath = tboxInput->Text;
  if( fbd->ShowDialog() == Windows::Forms::DialogResult::OK ) {
    tboxInput->Text = fbd->SelectedPath;
  }
}



System::Void
MainForm::OnDragDropInput(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
{
  if( e->Data->GetDataPresent( DataFormats::FileDrop ) ) {
    array<Object ^> ^ ao = (array<Object ^>^) e->Data->GetData( DataFormats::FileDrop );
    if( ao != nullptr ) {
      if( ao->Length > 1 )
      {
        // more than one file dragged... ignore and simply read first filedrop
      }
      // TODO: check for dml file?
      String ^ firstFile = ao[0]->ToString();
      FileInfo ^ fi = gcnew FileInfo( firstFile );

      tboxInput->Text = ao[0]->ToString();
    }
  }
}



System::Void
MainForm::OnDragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
{
  if( e->Data->GetDataPresent( DataFormats::FileDrop ) ) {
    e->Effect = DragDropEffects::Copy;
  }
  else {
    e->Effect = DragDropEffects::None;
  }
}
