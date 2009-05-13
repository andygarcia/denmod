#include "StdAfx.h"
#include "MainForm.h"
#include "HelpForm.h"

using namespace System::IO;
using namespace parsedos;



MainForm::MainForm(void)
{
	InitializeComponent();

  String ^ configFile = Application::StartupPath + "\\parsedos.config";
  XmlDocument ^ cfgXML = gcnew XmlDocument();
  try {
    cfgXML->Load( configFile );
    XmlNode ^ xmln;

    xmln = cfgXML->DocumentElement->SelectSingleNode( "CimsimInputURI" );
    tboxCimsimInput->Text = xmln->FirstChild->Value;

    xmln = cfgXML->DocumentElement->SelectSingleNode( "DensimInputURI" );
    tboxDensimInput->Text = xmln->FirstChild->Value;

    xmln = cfgXML->DocumentElement->SelectSingleNode( "ExcelEnabled" );
    cboxXml->Checked = Convert::ToBoolean( xmln->FirstChild->Value );

    xmln = cfgXML->DocumentElement->SelectSingleNode( "TextEnabled" );
    cboxTxt->Checked = Convert::ToBoolean( xmln->FirstChild->Value );
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
  String ^ configFile = Application::StartupPath + "\\parsedos.config";
  XmlDocument ^ cfgXml = gcnew XmlDocument();
  try {
    cfgXml->Load( configFile );
    XmlNode ^ xmln;

    xmln = cfgXml->DocumentElement->SelectSingleNode( "CimsimInputURI" );
    xmln->FirstChild->Value = tboxCimsimInput->Text;

    xmln = cfgXml->DocumentElement->SelectSingleNode( "DensimInputURI" );
    xmln->FirstChild->Value = tboxDensimInput->Text;

    xmln = cfgXml->DocumentElement->SelectSingleNode( "ExcelEnabled" );
    xmln->FirstChild->Value = Convert::ToString( cboxXml->Checked );

    xmln = cfgXml->DocumentElement->SelectSingleNode( "TextEnabled" );
    xmln->FirstChild->Value = Convert::ToString( cboxTxt->Checked );
    
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
    XmlElement ^ inputNode = cfgXml->CreateElement( "CimsimInputURI" );
    rootNode->AppendChild( inputNode );
    XmlText ^ inputText = cfgXml->CreateTextNode( tboxCimsimInput->Text );
    inputNode->AppendChild( inputText );

    // create and append InputURI element and value
    inputNode = cfgXml->CreateElement( "DensimInputURI" );
    rootNode->AppendChild( inputNode );
    inputText = cfgXml->CreateTextNode( tboxDensimInput->Text );
    inputNode->AppendChild( inputText );

    // create and append InputURI element and value
    inputNode = cfgXml->CreateElement( "ExcelEnabled" );
    rootNode->AppendChild( inputNode );
    inputText = cfgXml->CreateTextNode( Convert::ToString(cboxXml->Checked) );
    inputNode->AppendChild( inputText );

    // create and append InputURI element and value
    inputNode = cfgXml->CreateElement( "TextEnabled" );
    rootNode->AppendChild( inputNode );
    inputText = cfgXml->CreateTextNode( Convert::ToString(cboxTxt->Checked) );
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
  if( !Directory::Exists( tboxCimsimInput->Text ) ) {
    MessageBox::Show( "Unable to find input directory" );
    return;
  }

  // parse files
  DirectoryInfo ^ di = gcnew DirectoryInfo( tboxCimsimInput->Text );
  CimsimParser ^ cp = gcnew CimsimParser( di );
  cp->Parse();

  // save output
  if( cboxXml->Checked ) {
    cp->SaveToDisk( CimsimParser::OutputType::XML );
  }
  if( cboxTxt->Checked ) {
    cp->SaveToDisk( CimsimParser::OutputType::ASCII );
  }
}



System::Void
MainForm::OnHelp( System::Object ^ sender, System::EventArgs ^ e )
{
  HelpForm ^ hf = gcnew HelpForm();
  hf->ShowDialog();
}



System::Void
MainForm::OnBrowseInput(System::Object^  sender, System::EventArgs^  e)
{
  FolderBrowserDialog ^ fbd = gcnew FolderBrowserDialog();
  fbd->SelectedPath = tboxCimsimInput->Text;
  if( fbd->ShowDialog() == Windows::Forms::DialogResult::OK ) {
    if( sender == btnCimsimBrowse ) {
      tboxCimsimInput->Text = fbd->SelectedPath;
    }
    if( sender == btnDensimBrowse ) {
      tboxDensimInput->Text = fbd->SelectedPath;
    }
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

      TextBox ^ tbox = static_cast<TextBox^>(sender);
      tbox->Text = ao[0]->ToString();
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
