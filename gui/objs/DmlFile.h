#pragma once

#include "Location.h"



namespace gui {

public ref class DmlFile
{
public:
  static DmlFile ^ CreateNew(void);
public:
  DmlFile( System::String ^ filename );
  DmlFile( System::String ^ filename, System::IO::Stream ^ stream );
  DmlFile( System::String ^ filename, gui::Location ^ location );

  void Save();
  void Save( System::String ^ filename );

private:
  ~DmlFile();

public:
  property System::String ^ Filename {
    System::String ^ get(void) {
      return _filename;
    }
    void set( System::String ^ filename ) {
      _filename = filename;
    }
  }

  property gui::Location ^ Location {
    gui::Location ^ get(void) {
      return _location;
    }
  }

  property bool IsValid {
    bool get(void) {
      return _isValid;
    }
  }

  property bool IsReadOnly {
    bool get(void) {
      return _isReadOnly;
    }
  }

  property bool IsNew {
    bool get(void) {
      return _isNew;
    }
  }

private:
  System::String ^ _filename;
  gui::Location ^ _location;
  bool _isValid;
  bool _isNew;
  bool _isReadOnly;
};

};
