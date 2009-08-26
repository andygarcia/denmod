#include "StdAfx.h"
#include "Location.h"

using namespace ds::port;



Location::Location(void)
{
  Weather_ = new csinput::Weather();
}


Location::~Location(void)
{
  delete Weather_;
}
