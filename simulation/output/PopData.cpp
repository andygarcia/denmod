#include "StdAfx.h"
#include "PopData.h"

using namespace sim::output;



PopData::PopData(void)
{
}



PopData::~PopData(void)
{
  ContainerPopDataCollection::iterator itCtnr;
  for( itCtnr = Containers_.begin(); itCtnr != Containers_.end(); ++itCtnr ) {
    delete itCtnr->second;
  }
}
