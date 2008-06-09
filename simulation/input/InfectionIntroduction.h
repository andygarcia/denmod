#ifndef INPUT_INFECTIONINTRODUCTION_H
#define INPUT_INFECTIONINTRODUCTION_H

#include "Schedule.h"



namespace input {


class SerotypeIntroduction
{
public:
  SerotypeIntroduction(void) {}
  virtual ~SerotypeIntroduction(void) {}

public:
  int Humans_;
  int Mosquitoes_;
  Schedule * Schedule_;
};



class InfectionIntroduction
{
public:
  InfectionIntroduction(void);
  virtual ~InfectionIntroduction(void);

  SerotypeIntroduction * GetSerotype( int i );

public:
  SerotypeIntroduction * Dengue1_;
  SerotypeIntroduction * Dengue2_;
  SerotypeIntroduction * Dengue3_;
  SerotypeIntroduction * Dengue4_;
};

};

#endif
