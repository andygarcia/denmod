#include "StdAfx.h"
#include "Location.h"

using namespace input;



Location::Location(void)
{
#ifdef _DEBUG
  _doDebugOutput = true;
#else
  _doDebugOutput = false;
#endif
}



Location::~Location(void)
{
  for( std::vector<Container*>::iterator itCont = Containers_.begin(); itCont != Containers_.end(); ++itCont ) {
    delete *itCont;
  }
  Containers_.clear();

  for( std::vector<Control*>::iterator itCtrl = Controls_.begin(); itCtrl != Controls_.end(); ++itCtrl ) {
    delete *itCtrl;
  }
  Controls_.clear();

  delete Biology_;
  delete Weather_;
  delete Demographics_;
  delete Serology_;
  delete Virology_;
  delete InfectionIntroduction_;
  delete SequentialInfections_;
}



Container *
Location::FindContainerByName( std::string name )
{
  std::vector<Container*>::iterator itCont;
  for( itCont = Containers_.begin(); itCont != Containers_.end(); ++itCont ) {
    if( (*itCont)->Name_ == name ) {
      return *itCont;
    }
  }
  return NULL;
}
