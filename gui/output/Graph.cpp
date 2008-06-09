#include "StdAfx.h"
#include "Graph.h"

using namespace gui::output;



Graph ^
Graph::CreateGraph( GraphTypes::Cimsim::Location graphType, CimsimOutput ^ cimsimOutput )
{
  // create graph from graph info
  GraphInfo ^ gi = GraphCollections::GetGraphInfo( graphType );
  Graph ^ g = gcnew Graph( gi );

  // add primary outputs
  for each( int outputId in gi->GraphPrimaryOutputAttribute->OutputIds ) {
    g->_primaryOutputs->Add( cimsimOutput->Location[outputId] );
  }

  // add secondary outputs if any
  if( gi->GraphSecondaryOutputAttribute != nullptr ) {
    for each( int outputId in gi->GraphSecondaryOutputAttribute->OutputIds ) {
      g->_secondaryOutputs->Add( cimsimOutput->Location[outputId] );
    }
  }

  return g;
}



Graph ^
Graph::CreateGraph( GraphTypes::Cimsim::Container graphType, CimsimOutput ^ cimsimOutput, int containerId )
{
  GraphInfo ^ gi = GraphCollections::GetGraphInfo( graphType );
  Graph ^ g = gcnew Graph( gi );

  for each( int outputId in gi->GraphPrimaryOutputAttribute->OutputIds ) {
    g->_primaryOutputs->Add( cimsimOutput->Containers[containerId][outputId] );
  }

  if( gi->GraphSecondaryOutputAttribute != nullptr ) {
    for each( int outputId in gi->GraphSecondaryOutputAttribute->OutputIds ) {
      g->_secondaryOutputs->Add( cimsimOutput->Containers[containerId][outputId] );
    }
  }

  return g;
}



static
GraphCollections::GraphCollections(void)
{
  _cimsimLocation = GetGraphInfoCollection( GraphTypes::Cimsim::Location::typeid );
  _cimsimContainer = GetGraphInfoCollection( GraphTypes::Cimsim::Container::typeid );
  _densimLocation = GetGraphInfoCollection( GraphTypes::Densim::Location::typeid );
  _densimSerotype = GetGraphInfoCollection( GraphTypes::Densim::Serotype::typeid );
}



generic<typename T> where T : ref class
T
GraphCollections::GetCustomAttribute( Reflection::FieldInfo ^ fi, bool mustExist )
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
GraphCollections::GetGraphInfoCollection( System::Type ^ type )
{
  // generate a collection of GraphInfo object for this type by using
  // reflection to access GraphInfoAttribute on members
  GraphInfoCollection ^ graphInfos = gcnew GraphInfoCollection();

  array<Reflection::FieldInfo^> ^ fields = type->GetFields( Reflection::BindingFlags::Static | Reflection::BindingFlags::GetField | Reflection::BindingFlags::Public );
  for each( Reflection::FieldInfo ^ fi in fields ) {
    GraphPrimaryOutputAttribute ^ gpoa = GetCustomAttribute<GraphPrimaryOutputAttribute^>( fi, true );
    GraphSecondaryOutputAttribute ^ gsoa = GetCustomAttribute<GraphSecondaryOutputAttribute^>( fi, false );
    GraphTitlesAttribute ^ gta = GetCustomAttribute<GraphTitlesAttribute^>( fi, true );

    int id = Convert::ToInt32( fi->GetValue(nullptr) );
    GraphInfo ^ gi = gcnew GraphInfo( id, gpoa, gsoa, gta );
    graphInfos->Add( id, gi );
  }

  return graphInfos;
}



ComponentModel::BindingList<GraphInfo^> ^
GraphCollections::GetGraphInfoBindingList( System::Type ^ type )
{
  ComponentModel::BindingList<GraphInfo^> ^ graphInfos = gcnew ComponentModel::BindingList<GraphInfo^>();

  GraphInfoCollection ^ gic = nullptr;

  // find which collection of GraphInfo to use to create binding list
  if( type == GraphTypes::Cimsim::Location::typeid ) {
    gic = _cimsimLocation;
  }
  else if( type == GraphTypes::Cimsim::Container::typeid ) {
    gic = _cimsimContainer;
  }
  else if( type == GraphTypes::Densim::Location::typeid ) {
    gic = _densimLocation;
  }
  else if( type == GraphTypes::Densim::Serotype::typeid ) {
    gic = _densimSerotype;
  }
  else {
    // invalid type argument
    throw gcnew System::ArgumentException( "GetGraphInfoBindingList(), invalid type" );
  }

  Array ^ enumValues = Enum::GetValues( type );
  for each( int i in enumValues ) {
    graphInfos->Add( gic[i] );
  }

  return graphInfos;
}



GraphInfo ^
GraphCollections::GetGraphInfo( GraphTypes::Cimsim::Location graphType )
{
  int graphId = (int) graphType;
  return _cimsimLocation[graphId];
}



GraphInfo ^
GraphCollections::GetGraphInfo( GraphTypes::Cimsim::Container graphType )
{
  int graphId = (int) graphType;
  return _cimsimContainer[graphId];
}



GraphInfo ^
GraphCollections::GetGraphInfo( GraphTypes::Densim::Location graphType )
{
  int graphId = (int) graphType;
  return _densimLocation[graphId];
}



GraphInfo ^
GraphCollections::GetGraphInfo( GraphTypes::Densim::Serotype graphType )
{
  int graphId = (int) graphType;
  return _densimSerotype[graphId];
}
