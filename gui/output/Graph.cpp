#include "StdAfx.h"
#include "Graph.h"

using namespace gui::output;



static
GraphInfos::GraphInfos(void)
{
  _cimsimLocation = GetGraphInfoCollection( GraphInfos::CimsimLocation::typeid );
  _cimsimContainer = GetGraphInfoCollection( GraphInfos::CimsimContainer::typeid );
  _densimLocation = GetGraphInfoCollection( GraphInfos::DensimLocation::typeid );
  _densimSerotype = GetGraphInfoCollection( GraphInfos::DensimSerotype::typeid );

  _groupToCollection = gcnew Collections::Generic::Dictionary<Group,GraphInfoCollection^>();
  _groupToCollection->Add( Group::CimsimLocation, _cimsimLocation );
  _groupToCollection->Add( Group::CimsimContainer, _cimsimContainer );
  _groupToCollection->Add( Group::DensimLocation, _densimLocation );
  _groupToCollection->Add( Group::DensimSerotype, _densimSerotype );
}



generic<typename T> where T : ref class
T
GraphInfos::GetCustomAttribute( Reflection::FieldInfo ^ fi, bool mustExist )
{
  // find a GraphInfoAttribute on this member
  array<Object^> ^ attributes = fi->GetCustomAttributes( T::typeid, false );
  int numAttributes = attributes->Length;

  if( mustExist && numAttributes == 0 ) {
    throw gcnew Exception( "No custom attribute of type " + T::typeid + " was found on " + fi->Name );
  }
  else if( numAttributes == 1 ) {
    T t = (T) attributes[0];
    return t;
  }
  else if( mustExist ) {
    throw gcnew Exception( "More than one custom attribute of type " + T::typeid + " found on " + fi->Name );
  }
  else {
    return T();
  }
}



GraphInfoCollection ^
GraphInfos::GetGraphInfoCollection( System::Type ^ type )
{
  // generate a collection of GraphInfo object for this type by using
  // reflection to access GraphInfoAttribute on members
  GraphInfoCollection ^ graphInfos = gcnew GraphInfoCollection();

  array<Reflection::FieldInfo^> ^ fields = type->GetFields( Reflection::BindingFlags::Static | Reflection::BindingFlags::GetField | Reflection::BindingFlags::Public );
  for each( Reflection::FieldInfo ^ fi in fields ) {
    GraphTitlesAttribute ^ gta = GetCustomAttribute<GraphTitlesAttribute^>( fi, true );

    GraphInfo ^ gi = gcnew GraphInfo( gta );
    graphInfos->Add( gi );
  }

  return graphInfos;
}



ComponentModel::BindingList<GraphInfo^> ^
GraphInfos::GetGraphInfoBindingList( Group graphGroup )
{
  ComponentModel::BindingList<GraphInfo^> ^ graphInfos = gcnew ComponentModel::BindingList<GraphInfo^>();

  GraphInfoCollection ^ gic = _groupToCollection[graphGroup];

  for each( GraphInfo ^ gi in gic ) {
    graphInfos->Add( gi );
  }

  return graphInfos;
}
