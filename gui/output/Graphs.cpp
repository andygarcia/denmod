#include "StdAfx.h"
#include "Graphs.h"

using namespace gui::output;



Graph ^
GraphInfo::CreateGraph( CimsimOutput ^ cimsimOutput, DensimOutput ^ densimOutput )
{
  Graph ^ g = gcnew Graph(this);

  for each( OutputInfo ^ oi in _graphType ) {
    if( oi->OutputGroup == Group::CimsimLocation ) {
      Output ^ output = cimsimOutput->Location[oi];
      g->PrimaryOutputs->Add(output);
    }
    else if( oi->OutputGroup == Group::CimsimContainer ) {
      Output ^ output = cimsimOutput->Containers[_containerId][oi];
      g->PrimaryOutputs->Add(output);
    }
    if( oi->OutputGroup == Group::DensimLocation ) {
      Output ^ output = densimOutput->Location[oi];
      g->PrimaryOutputs->Add(output);
    }
    else if( oi->OutputGroup == Group::CimsimContainer ) {
      Output ^ output = densimOutput->Serotypes[_serotypeId][oi];
      g->PrimaryOutputs->Add(output);
    }
  }
  return g;
}



static
GraphInfos::GraphInfos(void)
{

  //[GraphAttribute(Title="Females per Hectare", AxisX="Date", AxisY="# of females per ha", ChartType="Line")]
  //[GraphOutputAttribute( OutputInfos::CimsimLocation::TotalFemales )]
  CimsimLocation::Females->Title = "Females per Hectare";
  Females->AxisX = "Date";
  Females->AxisY = "# of females per ha";
  Females->GraphType = "Line";

  //[GraphAttribute(Title="Average Female Wet Weight", AxisX="Date", AxisY="Wet Weight (mg)", ChartType="Line")]
  //static GraphInfo ^ AverageFemaleWetWeight = gcnew GraphInfo { OutputInfos::CimsimLocation::AverageFemaleWeight };

  //[GraphAttribute(Title="Oviposition", AxisX="Date", AxisY="# of eggs", ChartType="Line")]
  //static GraphInfo ^ Oviposition = gcnew GraphInfo { OutputInfos::CimsimLocation::Oviposition };

  //[GraphAttribute(Title="Weather", AxisX="Date", AxisY="°C / mm / mbars", ChartType="Line")]
  //static GraphInfo ^ Weather = gcnew GraphInfo { OutputInfos::CimsimLocation::MinimumTemperature,
  //                                               OutputInfos::CimsimLocation::AverageTemperature,
  //                                               OutputInfos::CimsimLocation::MaximumTemperature,
  //                                               OutputInfos::CimsimLocation::Rainfall,
  //                                               OutputInfos::CimsimLocation::RelativeHumidity,
  //                                               OutputInfos::CimsimLocation::SaturationDeficit };


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



GraphInfoCollection ^
GraphInfos::GetGraphInfoCollection( System::Type ^ type )
{
  using namespace System::Reflection;

  // generate a collection of GraphInfo object for this type by using
  // reflection to access GraphInfoAttribute on members
  GraphInfoCollection ^ graphInfos = gcnew GraphInfoCollection();
  array<MemberInfo^> ^ graphTypes = type->FindMembers( MemberTypes::Field, BindingFlags::Static, Type::FilterName, "GraphType" );
  for each( MemberInfo ^ mi in graphTypes ) {
  }

  array<FieldInfo^> ^ fields = type->GetFields( BindingFlags::Static | BindingFlags::GetField | BindingFlags::Public );
  for each( FieldInfo ^ fi in fields ) {
    GraphType ^ gt = (GraphType^) fi->GetValue( type );
    GraphAttribute ^ ga = GetCustomAttribute<GraphAttribute^>( fi, true );

    GraphInfo ^ gi = gcnew GraphInfo( gt, ga );
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
