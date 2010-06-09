#include "StdAfx.h"
#include "DmlFile.h"

using namespace System;
using namespace System::Xml;
using namespace System::Xml::XPath;
using namespace gui;



DmlFile ^
DmlFile::CreateNew(void)
{
  DmlFile ^ df = gcnew DmlFile( "Untitled.dml", gcnew gui::Location() );
  df->_isNew = true;

  return df;
}



DmlFile::DmlFile( System::String ^ filename )
: _filename(filename),
  _location(nullptr),
  _isValid(false)
{
  using namespace System::IO;
  using namespace System::Xml::Serialization;

  // open file as read/write or read-only
  FileStream ^ fs;
  if( (File::GetAttributes(_filename) & FileAttributes::ReadOnly) == FileAttributes::ReadOnly ) {
    fs = gcnew FileStream( _filename, FileMode::Open, FileAccess::Read );
    _isReadOnly = true;
  }
  else {
    fs = gcnew FileStream( _filename, FileMode::Open, FileAccess::ReadWrite );
    _isReadOnly = false;
  }

  // create deserializer
  XmlSerializer ^ xs;
  try {
    xs = gcnew XmlSerializer( gui::Location::typeid );
  }
  catch( Exception ^ e ) {
    System::Diagnostics::Debug::WriteLine( "DmlFile(): Exception in XmlSerializer(): " + e->Message );
  }

  // deserialize file to object
  try {
    _location  = (gui::Location^) xs->Deserialize( fs );
    _isValid = true;
  }
  catch( Exception ^ e ) {
    System::Diagnostics::Debug::WriteLine( "DmlFile(): Exception in Deserialize(): ", e->Message );
  }

  fs->Close();
}



DmlFile::DmlFile( String ^ filename, System::IO::Stream ^ stream )
: _filename(filename),
  _location(nullptr),
  _isNew(true),
  _isValid(false)
{
  using namespace System::IO;
  using namespace System::Xml::Serialization;

  // create deserializer
  XmlSerializer ^ xs;
  try {
    xs = gcnew XmlSerializer( gui::Location::typeid );
  }
  catch( Exception ^ e ) {
    System::Diagnostics::Debug::WriteLine( "DmlFile(): Exception in XmlSerializer(): " + e->Message );
  }

  // deserialize file to object
  try {
    _location  = (gui::Location^) xs->Deserialize( stream );
    _isValid = true;
  }
  catch( Exception ^ e ) {
    System::Diagnostics::Debug::WriteLine( "DmlFile(): Exception in Deserialize(): ", e->Message );
  }
}



DmlFile::DmlFile( System::String ^ filename, gui::Location ^ location )
: _filename(filename),
  _location(location),
  _isValid(false)
{}



DmlFile::~DmlFile()
{
}



void
DmlFile::Save()
{
  using namespace System::IO;
  using namespace System::Xml::Serialization;

  try {
    XmlSerializer ^ xs = gcnew XmlSerializer( gui::Location::typeid );
    TextWriter ^ tw = gcnew StreamWriter( _filename );

    xs->Serialize( tw, _location );
    tw->Close();

    this->_isNew = false;
    this->_isReadOnly = false;
  }
  catch( Exception ^ e ) {
    System::Diagnostics::Debug::WriteLine( "DmlFile::Save():  " + e->Message );
  }
}



void
DmlFile::Save( String ^ newFilename )
{
  this->_filename = newFilename;
  this->Save();
}
