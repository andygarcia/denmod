#include "StdAfx.h"
#include "InfectionIntroduction.h"

using namespace input;



InfectionIntroduction::InfectionIntroduction(void)
{
}



InfectionIntroduction::~InfectionIntroduction(void)
{
}



SerotypeIntroduction *
InfectionIntroduction::GetSerotype( int i )
{
  switch( i ) {
    case 1:
      return Dengue1_;
      break;
    case 2:
      return Dengue2_;
      break;
    case 3:
      return Dengue3_;
      break;
    case 4:
      return Dengue4_;
      break;
    default:
      // problems...
      return NULL;
  }
}