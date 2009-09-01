#include "StdAfx.h"
#include "Virology.h"

using namespace input;



VirusSerotype::VirusSerotype(void)
{}



VirusSerotype::VirusSerotype( int serotype, double viremia, int incubationDuration, int viremicDuration )
: Serotype_(serotype),
  Viremia_(viremia),
  IncubationDuration_(incubationDuration),
  ViremicDuration_(viremicDuration)
{}



VirusSerotype::~VirusSerotype(void)
{}



Virology::Virology(void)
: Dengue1_(VirusSerotype(1, 1000, 4, 5)),
  Dengue2_(VirusSerotype(1, 10000, 4, 5)),
  Dengue3_(VirusSerotype(1, 100000, 4, 5)),
  Dengue4_(VirusSerotype(1, 1000000, 4, 5)),
  MosquitoToHumanNominalProbabilityOfInfection_(0.900),
  MosquitoCountForStochasticity(0)
{}



Virology::~Virology(void)
{}


VirusSerotype &
Virology::GetSerotype( unsigned int i )
{
  if( i < 1 || i > 4 ) {
    throw "Bad Index";
  }

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
      throw;
  }
}
