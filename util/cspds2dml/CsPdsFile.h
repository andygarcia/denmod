#pragma once



namespace cspds2dml {

public ref class CsPdsFile
{
public:
  CsPdsFile( System::String ^ filename );
  ~CsPdsFile(void);

public:
  void Parse(void);

public:
  property gui::Location ^ Location {
    gui::Location ^ get(void);
  }

private:
  System::String ^ _filename;
  gui::Location ^ _location;
};

};
