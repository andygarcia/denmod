#ifndef DSPDSFILE_H
#define DSPDSFILE_H

#include "../dsport/Location.h"



public ref class DsPdsFile
{
public:
  static DsPdsFile ^ Open( System::String ^ filename );

  ds::port::Location * GetLocation(void);


private:
  DsPdsFile( System::String ^ filename );
  ~DsPdsFile();

  void Parse(void);

private:
  System::String ^ Filename_;
  ds::port::Location * loc;
};

#endif
