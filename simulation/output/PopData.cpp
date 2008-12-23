#include "StdAfx.h"
#include "PopData.h"

using namespace sim::output;



PopData::PopData(void)
{
}



PopData::~PopData(void)
{
  ContainerPopDataCollection::iterator itCtnr;
  for( itCtnr = _containers.begin(); itCtnr != _containers.end(); ++itCtnr ) {
    delete itCtnr->second;
  }
}



void
PopData::AddContainerData( ContainerPopData * cpd )
{
  _containers.insert( std::pair<int,ContainerPopData*>(cpd->Id,cpd) );
}



ContainerPopData *
PopData::GetContainerData( int containerId ) const
{
  // search for container id
  ContainerPopDataCollection::const_iterator iter = _containers.find( containerId );

  if( iter == _containers.end() ) {
    // queried non existant container
    throw;
  }
  else {
    return iter->second;
  }
}



ContainerPopData *
PopData::GetClonedContainerData( int containerId, int cloneId ) const
{
  // search for container id
  ContainerPopDataCollection::const_iterator iter = _containers.find( containerId );

  if( iter == _containers.end() ) {
    // queried non existant container
    throw;
  }


  // search for clone id
  ContainerPopDataCollection::const_iterator last = _containers.upper_bound( containerId );

  for( ; iter != last; ++iter ) {
    if( iter->second->CloneId == cloneId ) {
      return iter->second;
    }
  }

  // queried non existant clone
  throw;
}
