#include "StdAfx.h"
#include "MainForm.h"
#include "SplashForm.h"
#include "WeatherForm.h"

using namespace gui;



MainForm::MainForm(void)
: ActiveDocument(nullptr),
  LocationBinding(gcnew BindingSource())
{
	InitializeComponent();
  Initialize();
  NewDocument();
}



MainForm::MainForm(String ^ filename)
: ActiveDocument(nullptr),
  LocationBinding(gcnew BindingSource())
{
	InitializeComponent();
  Initialize();
  OpenDocument(filename);
}



void
MainForm::Initialize(void)
{
  CimsimPanel_ = gcnew CimsimPanel( LocationBinding );
  DensimPanel_ = gcnew DensimPanel( LocationBinding );

  // anchor all sides of panels for resizing
  AnchorStyles allAnchors = static_cast<AnchorStyles>((((AnchorStyles::Top | AnchorStyles::Bottom) | AnchorStyles::Left) | AnchorStyles::Right));
  CimsimPanel_->Anchor = allAnchors;
  DensimPanel_->Anchor = allAnchors;

  tabpgCimsim->Controls->Add(CimsimPanel_);
  tabpgDensim->Controls->Add(DensimPanel_);
}



MainForm::~MainForm()
{
  if( components ) {
		delete components;
	}
}



bool
MainForm::NewDocument(void)
{
  // check if active document can be closed
  if( !CloseDocument() )
    return false;

  // clear existing data ...
  ActiveDocument = DmlFile::CreateNew();
  // set initial document data and state
  UpdateBindings();
  UpdateTitleBar();

  return true;
}



bool
MainForm::OpenDocument( String ^ newFilename)
{
  // check if active document can be closed
  if( !CloseDocument() )
    return false;

  // get the file to open
  OpenFileDialog ^ ofd = gcnew OpenFileDialog();
  ofd->Filter = "Dengue Model Locations (*.dml)|*.dml";
  if( String::IsNullOrEmpty(newFilename) ) {
    if( ofd->ShowDialog(this) != ::DialogResult::OK ) {
      return false;
    }
    newFilename = ofd->FileName;
  }

  // read file
  DmlFile ^ df = gcnew DmlFile( newFilename );
  if( df->IsValid == false ) {
    return false;
  }
  
  ActiveDocument = df;
  UpdateBindings();
  UpdateTitleBar();

  // and possibly enabled weather related gui elements
  if( ActiveDocument->Location->IsWeatherAvailable ) {
    DensimPanel_->IsWeatherAvailable = true;
  }
  return true;
}



void
MainForm::OpenSampleLocation(void)
{
  // load sample location from resource
  Resources::ResourceManager ^ rm = gcnew Resources::ResourceManager( "gui.gui", Reflection::Assembly::GetExecutingAssembly() );
  array<Byte> ^ bytes = (array<Byte> ^) rm->GetObject( "Sample.dml" );
  IO::MemoryStream ^ stream = gcnew IO::MemoryStream( bytes );

  DmlFile ^ df = gcnew DmlFile( "Sample.dml", stream );

  ActiveDocument = df;
  UpdateBindings();
  UpdateTitleBar();

  // and possibly enabled weather related gui elements
  if( ActiveDocument->Location->IsWeatherAvailable ) {
    DensimPanel_->IsWeatherAvailable = true;
  }
}


    
bool
MainForm::SaveDocument( MainForm::SaveType saveType )
{
  // new or read only files must be saved as
  if( ActiveDocument->IsNew || ActiveDocument->IsReadOnly ) {
    saveType = SaveType::SaveAs;
  }

  // default to using existing filename
  String ^ filename = ActiveDocument->Filename;


  // prompt user with dialog for save as 
  if( saveType == SaveType::SaveAs ) {
    SaveFileDialog ^ sfd = gcnew SaveFileDialog();
    if( ActiveDocument->IsNew ) {
      sfd->FileName = filename;
    }
    else {
      sfd->InitialDirectory = IO::Path::GetDirectoryName( filename );
      sfd->FileName = IO::Path::GetFileName( filename );
    }

    sfd->Filter = "Dengue Model Locations (*.dml)|*.dml";
    if( sfd->ShowDialog(this) != Windows::Forms::DialogResult::OK ) {
      return false;
    }
    // possible filename change
    filename = sfd->FileName;
  }


  // ensure correct extension
  IO::FileInfo ^ fi = gcnew IO::FileInfo(filename);
  if( fi->Extension->Equals(".dml", StringComparison::CurrentCultureIgnoreCase) == false ) {
    filename = filename + ".dml";
  }


  // save file
  try {
    ActiveDocument->Save(filename);
  }
  catch( Exception ^ e ) {
    Diagnostics::Trace::WriteLine(e->ToString());
  }


  // update title
  UpdateTitleBar();
  return true;
}



bool
MainForm::CloseDocument(void)
{
  // no open document, or no changes yet
  if( ActiveDocument == nullptr ) {
    return true;
  }
  else if( !IsDocumentDirty() ) {
    return true;
  }

  // prompt user
  ::DialogResult dr = MessageBox::Show( this, "Save changes?", Application::ProductName, MessageBoxButtons::YesNoCancel );

  if( dr == ::DialogResult::Yes ) {
    return SaveDocument(SaveType::Save);
  }
  else if( dr == ::DialogResult::No ) {
    return true;
  }
  else if( dr == ::DialogResult::Cancel ) {
    return false;
  }
  else {
    Diagnostics::Debug::Assert(false);
    return false;
  }
}



bool 
MainForm::IsDocumentDirty(void)
{
  // TODO
  return false;
}



void
MainForm::UpdateBindings(void)
{
  // active document changed, update binding source
  LocationBinding->DataSource = ActiveDocument->Location;

  // and mark as clean
  //ActiveDocument->GetLocation()->IsDirty = false;
}



System::Void
MainForm::OnLoad(System::Object^  sender, System::EventArgs^  e)
{
  SplashForm::ShowSplash( 50, "" );

  tboxLocName->DataBindings->Add( "Text", LocationBinding, "Name" );
  rboxNotes->DataBindings->Add( "Text", LocationBinding, "Notes" );
  
  lboxWeather->DisplayMember = "Index";
  lboxWeather->ValueMember = "Index";
  lboxWeather->DataBindings->Add( "DataSource", LocationBinding, "Weather.YearsBindingList" );

  // TODO - start using a pre compiled assembly
  // load xml serializer assembly during splash screen
  Xml::Serialization::XmlSerializer ^ xs = gcnew Xml::Serialization::XmlSerializer( gui::Location::typeid );
  delete xs;

  //ActiveDocument->GetLocation()->IsDirty = false;

  SplashForm::Fadeout();
}



System::Void
MainForm::MenuItemHandler( System::Object^ sender, System::EventArgs^ e )
{
  if( sender->Equals(newToolStripMenuItem) || sender->Equals(newToolStripButton) ){
    NewDocument();
  }
  else if( sender->Equals(openToolStripMenuItem) || sender->Equals(openToolStripButton) ) {
    OpenDocument(nullptr);
  }
  else if( sender->Equals(tsmiOpenSampleLocation) ) {
    OpenSampleLocation();
  }
  else if( sender->Equals(saveToolStripMenuItem) || sender->Equals(saveToolStripButton) ) {
    SaveDocument( SaveType::Save );
  }
  else if( sender->Equals(saveAsToolStripMenuItem) ) {
    SaveDocument( SaveType::SaveAs );
  }
  else if( sender->Equals(openWeatherTemplateToolStripMenuItem) ) {
    OpenWeatherTemplate();
  }
  else if( sender->Equals(exitToolStripMenuItem) ) {
    Application::Exit();
  }
}



System::Void
MainForm::OnImportWeather( System::Object ^ sender, System::EventArgs ^ e )
{
  // add to this location's existing weather
  WeatherData ^ weather = ActiveDocument->Location->Weather;
  OpenFileDialog ^ ofd = gcnew OpenFileDialog();
  ofd->Filter = "Excel 97-2003 Spreadsheet (*.xls)|*.xls|CIMSiM/DENSiM 1.0 (*.dly)|*.dly";
  if( ofd->ShowDialog(this) != ::DialogResult::OK ) {
    return;
  }

  // basic checks on file selection
  IO::FileInfo ^ fi = gcnew IO::FileInfo( ofd->FileName );
  if( !fi->Exists ) {
    MessageBox::Show( "File does not exist.");
    return;
  }

  // get weather year from file
  WeatherYear ^ wy = nullptr;
  if( String::Compare(fi->Extension, ".xls", StringComparison::CurrentCultureIgnoreCase) == 0 ) {
    try {
      wy = WeatherYear::OpenFromXls( ofd->FileName );
    }
    catch( gui::ExcelWeatherDataException ^ e ) {
      MessageBox::Show( "Error in excel file at row " + e->RowIndex + ".  Please use weather template file and documentation to create weather spreadsheets." );
      return;
    }
  }
  else if( String::Compare(fi->Extension, ".dly", StringComparison::CurrentCultureIgnoreCase) == 0 ) {
    wy = WeatherYear::OpenFromDly( ofd->FileName );
  }
  else {
    MessageBox::Show( "Unrecognized file type." );
    return;
  }

  // use import form to finish process
  WeatherForm ^ wf = gcnew WeatherForm( LocationBinding, wy );
  if( wf->ShowDialog() != ::DialogResult::OK ) {
    return;
  }

  // add year to location, possibly replacing existing year
  if( weather->IsWeatherYearAvailable( wy->Index ) ) {
    weather->RemoveWeatherYear( wy->Index );
  }
  weather->AddWeatherYear( wy );
  DensimPanel_->IsWeatherAvailable = true;
}



System::Void
MainForm::OnCloneWeather( System::Object ^ sender, System::EventArgs ^ e )
{
}



System::Void
MainForm::OnRemoveWeather( System::Object ^ sender, System::EventArgs ^ e )
{
  if( lboxWeather->SelectedItem == nullptr ) {
    // no weather year selected
    return;
  }

  int newIndex = lboxWeather->SelectedIndex - 1;
  int yearToRemove = Convert::ToInt32( lboxWeather->SelectedValue );

  WeatherData ^ weather = ActiveDocument->Location->Weather;
  weather->RemoveWeatherYear( yearToRemove );
}



void
MainForm::OpenWeatherTemplate(void)
{
}



void
MainForm::UpdateTitleBar(void)
{
  String ^ filename = ActiveDocument->Filename;
  if( filename != "Untitled.dml" ) {
    filename = System::IO::Path::GetFileName(ActiveDocument->Filename);
  }
  String ^ readOnly = ActiveDocument->IsReadOnly ? "[Read-Only]" : "";
  String ^ dirty = IsDocumentDirty() ? "*" : "";

  String ^ productName = Application::ProductName;

  // TODO, which version is correct?
  //String ^ version = Application::ProductVersion;
  String ^ version = System::Reflection::Assembly::GetExecutingAssembly()->GetName()->Version->ToString();

  
  Text = String::Format( "{0} {1} - [{2} - {3}]", filename, readOnly, productName, version );
}
