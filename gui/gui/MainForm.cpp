#include "StdAfx.h"
#include "MainForm.h"
#include "SplashForm.h"
#include "AboutDialog.h"
#include "WeatherForm.h"
#include "OptionsForm.h"

using namespace gui;



MainForm::MainForm(void)
: _activeDocument(nullptr),
  LocationBinding(gcnew BindingSource())
{
	InitializeComponent();
  NewDocument();
  Initialize();
}



MainForm::MainForm(String ^ filename)
: _activeDocument(nullptr),
  LocationBinding(gcnew BindingSource())
{
	InitializeComponent();
  OpenDocument(filename);
  Initialize();
}



void
MainForm::Initialize(void)
{
  ReadSettings();

  // create cimsim and densim panels
  _cimsimPanel = gcnew CimsimPanel( LocationBinding, _userSettings );
  _densimPanel = gcnew DensimPanel( LocationBinding );

  // anchor all sides of panels for resizing
  AnchorStyles allAnchors = static_cast<AnchorStyles>((((AnchorStyles::Top | AnchorStyles::Bottom) | AnchorStyles::Left) | AnchorStyles::Right));
  _cimsimPanel->Anchor = allAnchors;
  _densimPanel->Anchor = allAnchors;

  tabpgCimsim->Controls->Add(_cimsimPanel);
  tabpgDensim->Controls->Add(_densimPanel);
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

  // create new file and set active
  _activeDocument = DmlFile::CreateNew();

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
  
  _activeDocument = df;
  UpdateBindings();
  UpdateTitleBar();

  return true;
}



void
MainForm::OpenSampleLocation(void)
{
  // check if active document can be closed
  if( !CloseDocument() )
    return;

  // load sample location from resource
  Resources::ResourceManager ^ rm = gcnew Resources::ResourceManager( "gui.gui", Reflection::Assembly::GetExecutingAssembly() );
  array<Byte> ^ bytes = (array<Byte> ^) rm->GetObject( "Sample.dml" );
  IO::MemoryStream ^ stream = gcnew IO::MemoryStream( bytes );

  DmlFile ^ df = gcnew DmlFile( "Sample.dml", stream );

  _activeDocument = df;
  UpdateBindings();
  UpdateTitleBar();
}


    
bool
MainForm::SaveDocument( MainForm::SaveType saveType )
{
  // new or read only files must be saved as
  if( _activeDocument->IsNew || _activeDocument->IsReadOnly ) {
    saveType = SaveType::SaveAs;
  }

  // default to using existing filename
  String ^ filename = _activeDocument->Filename;


  // prompt user with dialog for save as 
  if( saveType == SaveType::SaveAs ) {
    SaveFileDialog ^ sfd = gcnew SaveFileDialog();
    if( _activeDocument->IsNew ) {
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
    _activeDocument->Save(filename);
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
  if( _activeDocument == nullptr ) {
    return true;
  }
  else if( !IsDocumentDirty() ) {
    return true;
  }


  System::String ^ shortFilename =  IO::Path::GetFileNameWithoutExtension( _activeDocument->Filename );

  // prompt user
  ::DialogResult dr = MessageBox::Show( this, "Do you want to save the changes to " + shortFilename + " ?",
                                        Application::ProductName, MessageBoxButtons::YesNoCancel,
                                        MessageBoxIcon::Exclamation, MessageBoxDefaultButton::Button1);

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
  return true;
}



void
MainForm::UpdateBindings(void)
{
  // active document changed, update binding source
  LocationBinding->DataSource = _activeDocument->Location;

  // and mark as clean
  //_activeDocument->GetLocation()->IsDirty = false;
}



System::Void
MainForm::OnLoad(System::Object^  sender, System::EventArgs^  e)
{
  SplashForm::ShowSplash( 50, "" );

  tboxLocName->DataBindings->Add( "Text", LocationBinding, "Name", false, DataSourceUpdateMode::OnPropertyChanged );
  //rboxNotes->DataBindings->Add( "Text", LocationBinding, "Notes", false, DataSourceUpdateMode::OnPropertyChanged );
  rboxNotes->DataBindings->Add( "Text", LocationBinding, "Notes" );
  
  lboxWeather->DisplayMember = "Index";
  lboxWeather->ValueMember = "Index";
  lboxWeather->DataBindings->Add( "DataSource", LocationBinding, "Weather.YearsBindingList" );

  // TODO - start using a pre compiled assembly, loading it during splash screen
  Xml::Serialization::XmlSerializer ^ xs = gcnew Xml::Serialization::XmlSerializer( gui::Location::typeid );
  delete xs;

  //_activeDocument->GetLocation()->IsDirty = false;
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
  else if( sender->Equals(optionsToolStripMenuItem) ) {
    ShowOptions();
  }
  else if( sender->Equals(openWeatherTemplateToolStripMenuItem) ) {
    OpenWeatherTemplate();
  }
  else if( sender->Equals(exitToolStripMenuItem) ) {
    Exit();
  }
  else if( sender->Equals(tsmiHelpAbout) ) {
    ShowAbout();
  }
}



void
MainForm::ShowOptions(void)
{
  OptionsForm ^ of = gcnew OptionsForm( _userSettings );
  of->ShowDialog();
}



System::Void
MainForm::OnImportWeather( System::Object ^ sender, System::EventArgs ^ e )
{
  // add to this location's existing weather
  WeatherData ^ weather = _activeDocument->Location->Weather;
  OpenFileDialog ^ ofd = gcnew OpenFileDialog();
  ofd->Filter = "Excel 97-2003 Spreadsheet (*.xls)|*.xls|CIMSiM/DENSiM 1.0 (*.dly)|*.dly";
  ofd->Multiselect = true;
  if( ofd->ShowDialog(this) != ::DialogResult::OK ) {
    return;
  }

  for each( String ^ filename in ofd->FileNames ) {
    // basic checks on file selection
    IO::FileInfo ^ fi = gcnew IO::FileInfo( filename );
    if( !fi->Exists ) {
      MessageBox::Show( "File does not exist.");
      continue;
    }

    // get weather year from file
    WeatherYear ^ wy = nullptr;
    if( String::Compare(fi->Extension, ".xls", StringComparison::CurrentCultureIgnoreCase) == 0 ) {
      try {
        wy = WeatherYear::OpenFromXls( filename );
      }
      catch( gui::ExcelWeatherDataException ^ e ) {
        MessageBox::Show( "Error in excel file at row " + e->RowIndex + ".  Please use weather template file and documentation to create weather spreadsheets." );
        continue;
      }
    }
    else if( String::Compare(fi->Extension, ".dly", StringComparison::CurrentCultureIgnoreCase) == 0 ) {
      try {
        wy = WeatherYear::OpenFromDly( filename );
      }
      catch( gui::DlyWeatherDataException ^ e ) {
        MessageBox::Show( "Error in DLY file for day " + e->RowIndex + ".  Make sure DLY data is valid." );
        continue;
      }
    }
    else {
      MessageBox::Show( "Unrecognized file type." );
      continue;
    }

    // use import form to finish process
    WeatherForm ^ wf = gcnew WeatherForm( WeatherFormMode::Import, LocationBinding, wy );
    if( wf->ShowDialog() != ::DialogResult::OK ) {
      return;
    }

    // add year to location, possibly replacing existing year
    if( weather->IsWeatherYearAvailable( wy->Index ) ) {
      weather->RemoveWeatherYear( wy->Index );
    }
    weather->AddWeatherYear( wy );
  }
}



System::Void
MainForm::OnViewWeather(System::Object^  sender, System::EventArgs^  e)
{
  if( lboxWeather->SelectedItem == nullptr ) {
    // no weather year selected
    return;
  }

  int year = Convert::ToInt32( lboxWeather->SelectedValue );
  WeatherYear ^ wy = _activeDocument->Location->Weather[year];

  wy->BeginEdit();
  WeatherForm ^ wf = gcnew WeatherForm( WeatherFormMode::Edit, LocationBinding, wy );
  if( wf->ShowDialog() == ::DialogResult::OK ) {
    wy->EndEdit();
  }
  else {
    wy->CancelEdit();
  }
}



System::Void
MainForm::OnCloneWeather( System::Object ^ sender, System::EventArgs ^ e )
{
  throw gcnew InvalidOperationException( "OnCloneWeather() not implemented." );
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

  WeatherData ^ weather = _activeDocument->Location->Weather;
  weather->RemoveWeatherYear( yearToRemove );
}



void
MainForm::OpenWeatherTemplate(void)
{
}



System::Void
MainForm::OnFormClosing( System::Object ^ sender, System::Windows::Forms::FormClosingEventArgs ^ e )
{
  // cancel close unless a result of Application::Exit() in MainForm::Exit()
  if( e->CloseReason == ::CloseReason::UserClosing ) {
    e->Cancel = true;
    Exit();
  }
}



void
MainForm::Exit(void)
{
  // first close document (possibly prompting save)
  if( !CloseDocument() ) {
    return;
  }

  // save possible changes to user settings
  WriteSettings();

  Application::Exit();
}



void
MainForm::ReadSettings(void)
{
  using namespace IO;
  using namespace Xml::Serialization;

  // read user settings
  String ^ filename;
  filename = Path::Combine( Environment::GetFolderPath(Environment::SpecialFolder::ApplicationData), Application::CompanyName );
  filename = Path::Combine( filename, Application::ProductName );
  filename = Path::Combine( filename, "denmod.cfg" );

  try {
    FileStream ^ fs = gcnew FileStream( filename, FileMode::Open );
    XmlSerializer ^ xs = gcnew XmlSerializer( gui::Settings::typeid );
    _userSettings = dynamic_cast<gui::Settings^>( xs->Deserialize(fs) );
  }
  catch( Exception ^ e ) {
    // unable to open/deserialize file, WriteSettings will create
    Diagnostics::Trace::WriteLine(e->ToString());
    _userSettings = gcnew Settings();
  }
}



void
MainForm::WriteSettings(void)
{
  using namespace IO;
  using namespace Xml::Serialization;

  // write user settings
  String ^ filename;
  filename = Path::Combine( Environment::GetFolderPath(Environment::SpecialFolder::ApplicationData), Application::CompanyName );
  filename = Path::Combine( filename, Application::ProductName );
  filename = Path::Combine( filename, "denmod.cfg" );

  FileStream ^ fs = gcnew FileStream( filename, FileMode::OpenOrCreate );

  XmlSerializer ^ xs = gcnew XmlSerializer( gui::Settings::typeid );
  xs->Serialize( fs, _userSettings );
}



void
MainForm::UpdateTitleBar(void)
{
  String ^ filename = _activeDocument->Filename;
  if( filename != "Untitled.dml" ) {
    filename = System::IO::Path::GetFileName(_activeDocument->Filename);
  }
  String ^ readOnly = _activeDocument->IsReadOnly ? "[Read-Only]" : "";
  String ^ dirty = IsDocumentDirty() ? "*" : "";
  String ^ productName = Application::ProductName;
  String ^ version = DM_VERSION;

  
  Text = String::Format( "{0} {1} - [{2} - {3}]", filename, readOnly, productName, version );
}



void
MainForm::ShowAbout(void)
{
  AboutDialog ^ ad = gcnew AboutDialog();
  ad->ShowDialog();
}
