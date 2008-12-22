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



void
PopData::AddContainerData( ContainerPopData * cpd )
{
  Containers_.insert( std::pair<int,ContainerPopData*>(cpd->Id,cpd) );
}



ContainerPopData *
PopData::GetContainerData( int containerId ) const
{
  ContainerPopDataCollection::const_iterator iter  = Containers_.find( containerId );

  if( iter != Containers_.end() ) {
    return iter->second;
  }
  else {
    // queried for non existent container
    throw;
  }

}



ContainerPopData *
PopData::GetClonedContainerData( int containerId, int cloneId ) const
{
  ContainerPopDataCollection::const_iterator iter = Containers_.find( containerId );

  if( iter != Containers_.end() ) {
    // now search for specific clone
    ContainerPopDataCollection::const_iterator last = Containers_.upper_bound( containerId );
    for( ; iter != last; ++iter ) {
      if( iter->second->CloneId == cloneId ) {
        return iter->second;
      }
    }
  }
  else {
    // queried for non existent container
    throw;
  }
}
