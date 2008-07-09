#include "StdAfx.h"
#include "Graphs.h"

using namespace gui::output;



Graph ^
GraphInfo::CreateGraph( CimsimOutput ^ cimsimOutput, DensimOutput ^ densimOutput )
{
  Graph ^ g = gcnew Graph(this);

  for each( OutputInfo ^ oi in _primaryOutputs ) {
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
    else if( oi->OutputGroup == Group::DensimSerotype ) {
      Output ^ output = densimOutput->Serotypes[_serotypeId][oi];
      g->PrimaryOutputs->Add(output);
    }
  }
  return g;
}



static
GraphInfos::GraphInfos(void)
{
  _cimsimLocation = gcnew GraphInfoCollection();
  _cimsimContainer = gcnew GraphInfoCollection();

  _groupToCollection = gcnew Collections::Generic::Dictionary<Group,GraphInfoCollection^>();
  _groupToCollection->Add( Group::CimsimLocation, _cimsimLocation );
  _groupToCollection->Add( Group::CimsimContainer, _cimsimContainer );
  _groupToCollection->Add( Group::DensimLocation, _densimLocation );
  _groupToCollection->Add( Group::DensimSerotype, _densimSerotype );

  _cimsimLocation->Add( CimsimLocation::Females );
  _cimsimLocation->Add( CimsimLocation::AverageFemaleWetWeight );
  _cimsimLocation->Add( CimsimLocation::Oviposition );
  _cimsimLocation->Add( CimsimLocation::Weather );

  _cimsimContainer->Add( CimsimContainer::ContainerDensity );
  _cimsimContainer->Add( CimsimContainer::Depth );
  _cimsimContainer->Add( CimsimContainer::Food );
  _cimsimContainer->Add( CimsimContainer::WaterTemperature );
  _cimsimContainer->Add( CimsimContainer::Eggs );
  _cimsimContainer->Add( CimsimContainer::Larvae );
  _cimsimContainer->Add( CimsimContainer::Pupae );
  _cimsimContainer->Add( CimsimContainer::AveragePupalWeight );
  _cimsimContainer->Add( CimsimContainer::NewFemales );
  _cimsimContainer->Add( CimsimContainer::CumulativeFemales );
  _cimsimContainer->Add( CimsimContainer::Oviposition );
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



static
GraphInfos::CimsimLocation::CimsimLocation(void)
{
  Females = gcnew GraphInfo();
  Females->Title = "Females per Hectare";
  Females->AxisX = "Date";
  Females->AxisY = "# of females per ha";
  Females->GraphType = "Line";
  Females->PrimaryOutputs->Add( OutputInfos::CimsimLocation::TotalFemales );

  AverageFemaleWetWeight = gcnew GraphInfo();
  AverageFemaleWetWeight->Title = "Average female wet weight";
  AverageFemaleWetWeight->AxisX = "Date";
  AverageFemaleWetWeight->AxisY = "Wet weight (mg)";
  AverageFemaleWetWeight->GraphType = "Line";
  AverageFemaleWetWeight->PrimaryOutputs->Add( OutputInfos::CimsimLocation::AverageFemaleWeight );

  Oviposition = gcnew GraphInfo();
  Oviposition->Title = "Oviposition";
  Oviposition->AxisX = "Date";
  Oviposition->AxisY = "# of eggs";
  Oviposition->GraphType = "Line";
  Oviposition->PrimaryOutputs->Add( OutputInfos::CimsimLocation::Oviposition );


  Weather = gcnew GraphInfo();
  Weather->Title = "Weather";
  Weather->AxisX = "Date";
  Weather->AxisY = "°C / mm / mbars";
  Weather->GraphType = "Line";
  Weather->PrimaryOutputs->Add( OutputInfos::CimsimLocation::MinimumTemperature );
  Weather->PrimaryOutputs->Add( OutputInfos::CimsimLocation::AverageTemperature );
  Weather->PrimaryOutputs->Add( OutputInfos::CimsimLocation::MaximumTemperature );
  Weather->PrimaryOutputs->Add( OutputInfos::CimsimLocation::Rainfall );
  Weather->PrimaryOutputs->Add( OutputInfos::CimsimLocation::RelativeHumidity );
  Weather->PrimaryOutputs->Add( OutputInfos::CimsimLocation::SaturationDeficit );
}



static
GraphInfos::CimsimContainer::CimsimContainer(void)
{
  ContainerDensity = gcnew GraphInfo();
  ContainerDensity->Title = "Container densities";
  ContainerDensity->AxisX = "Date";
  ContainerDensity->AxisY = "# of contaienrs per ha";
  ContainerDensity->GraphType = "Line";
  ContainerDensity->PrimaryOutputs->Add( OutputInfos::CimsimContainer::UntreatedDensity );
  ContainerDensity->PrimaryOutputs->Add( OutputInfos::CimsimContainer::TreatedDensity );
  ContainerDensity->PrimaryOutputs->Add( OutputInfos::CimsimContainer::ExcludedDensity );

  Depth = gcnew GraphInfo();
  Depth->Title = "Water Depth";
  Depth->AxisX = "Date";
  Depth->AxisY = "cm";
  Depth->GraphType = "Line";
  Depth->PrimaryOutputs->Add( OutputInfos::CimsimContainer::Depth );

  Food = gcnew GraphInfo();
  Food->Title = "Food";
  Food->AxisX = "Date";
  Food->AxisY = "mg";
  Food->GraphType = "Line";
  Food->PrimaryOutputs->Add( OutputInfos::CimsimContainer::Food );

  WaterTemperature = gcnew GraphInfo();
  WaterTemperature->Title = "Water temperature";
  WaterTemperature->AxisX = "Date";
  WaterTemperature->AxisY = "°C";
  WaterTemperature->GraphType = "Line";
  WaterTemperature->PrimaryOutputs->Add( OutputInfos::CimsimContainer::MaximumTemperature );
  WaterTemperature->PrimaryOutputs->Add( OutputInfos::CimsimContainer::MinimumTemperature );

  Eggs = gcnew GraphInfo();
  Eggs->Title = "Eggs";
  Eggs->AxisX = "Date";
  Eggs->AxisY = "# of eggs";
  Eggs->GraphType = "Line";
  Eggs->PrimaryOutputs->Add( OutputInfos::CimsimContainer::Eggs );

  Larvae = gcnew GraphInfo();
  Larvae->Title = "Larvae";
  Larvae->AxisX = "Date";
  Larvae->AxisY = "# of larvae";
  Larvae->GraphType = "Line";
  Larvae->PrimaryOutputs->Add( OutputInfos::CimsimContainer::Larvae );

  Pupae = gcnew GraphInfo();
  Pupae->Title = "Pupae";
  Pupae->AxisX = "Date";
  Pupae->AxisY = "# of pupae";
  Pupae->GraphType = "Line";
  Pupae->PrimaryOutputs->Add( OutputInfos::CimsimContainer::Pupae );

  AveragePupalWeight = gcnew GraphInfo();
  AveragePupalWeight->Title = "Average pupal weight";
  AveragePupalWeight->AxisX = "Date";
  AveragePupalWeight->AxisY = "mg";
  AveragePupalWeight->GraphType = "Line";
  AveragePupalWeight->PrimaryOutputs->Add( OutputInfos::CimsimContainer::AveragePupalWeight );

  NewFemales = gcnew GraphInfo();
  NewFemales->Title = "New females";
  NewFemales->AxisX = "Date";
  NewFemales->AxisY = "# of new females";
  NewFemales->GraphType = "Line";
  NewFemales->PrimaryOutputs->Add( OutputInfos::CimsimContainer::NewFemales );

  CumulativeFemales = gcnew GraphInfo();
  CumulativeFemales->Title = "Cumulative females";
  CumulativeFemales->AxisX = "Date";
  CumulativeFemales->AxisY = "# of cumulative females";
  CumulativeFemales->GraphType = "Line";
  CumulativeFemales->PrimaryOutputs->Add( OutputInfos::CimsimContainer::CumulativeFemales );

  Oviposition = gcnew GraphInfo();
  Oviposition->Title = "Oviposition";
  Oviposition->AxisX = "Date";
  Oviposition->AxisY = "# of eggs";
  Oviposition->GraphType = "Line";
  Oviposition->PrimaryOutputs->Add( OutputInfos::CimsimContainer::Oviposition );
}



static
GraphInfos::DensimLocation::DensimLocation(void)
{
  InitialAgeDistribution = gcnew GraphInfo();
  InitialAgeDistribution->Title = "Initial age distribution";
  InitialAgeDistribution->AxisX = "Age class";
  InitialAgeDistribution->AxisY = "# of individuals";
  InitialAgeDistribution->GraphType = "Line";
  InitialAgeDistribution->PrimaryOutputs->Add( OutputInfos::DensimLocation::InitialAgeDistribution );

  FinalAgeDistribution = gcnew GraphInfo();
  FinalAgeDistribution->Title = "Final age distribution";
  FinalAgeDistribution->AxisX = "Age class";
  FinalAgeDistribution->AxisY = "# of individuals";
  FinalAgeDistribution->GraphType = "Line";
  FinalAgeDistribution->PrimaryOutputs->Add( OutputInfos::DensimLocation::FinalAgeDistribution );

  SimulationArea = gcnew GraphInfo();
  SimulationArea->Title = "Simulation area in hectares";
  SimulationArea->AxisX = "Date";
  SimulationArea->AxisY = "Area (ha)";
  SimulationArea->GraphType = "Line";
  SimulationArea->PrimaryOutputs->Add( OutputInfos::DensimLocation::SimulationArea );

  PopulationSize = gcnew GraphInfo();
  PopulationSize->Title = "Population size";
  PopulationSize->AxisX = "Date";
  PopulationSize->AxisY = "# of individuals";
  PopulationSize->GraphType = "Line";
  PopulationSize->PrimaryOutputs->Add( OutputInfos::DensimLocation::PopulationSize );

  BirthsByClass = gcnew GraphInfo();
  BirthsByClass->Title = "Births by age class";
  BirthsByClass->AxisX = "Age class";
  BirthsByClass->AxisY = "# of individuals";
  BirthsByClass->GraphType = "Line";
  BirthsByClass->PrimaryOutputs->Add( OutputInfos::DensimLocation::BirthsByClass );

  DeathsByClass = gcnew GraphInfo();
  DeathsByClass->Title = "Deaths by age class";
  DeathsByClass->AxisX = "Age class";
  DeathsByClass->AxisY = "# DeathsByClass";
  DeathsByClass->GraphType = "Line";
  DeathsByClass->PrimaryOutputs->Add( OutputInfos::DensimLocation::DeathsByClass );

  BirthPercentagesByClass = gcnew GraphInfo();
  BirthPercentagesByClass->Title = "Birth percentages by age class";
  BirthPercentagesByClass->AxisX = "Age class";
  BirthPercentagesByClass->AxisY = "Percentage of births";
  BirthPercentagesByClass->GraphType = "Line";
  BirthPercentagesByClass->PrimaryOutputs->Add( OutputInfos::DensimLocation::BirthPercentagesByClass );

  DeathPercentagesByClass = gcnew GraphInfo();
  DeathPercentagesByClass->Title = "Death percentages by age class";
  DeathPercentagesByClass->AxisX = "Age class";
  DeathPercentagesByClass->AxisY = "Percentage of deaths";
  DeathPercentagesByClass->GraphType = "Line";
  DeathPercentagesByClass->PrimaryOutputs->Add( OutputInfos::DensimLocation::DeathPercentagesByClass );

  FemaleMosquitoesInSimulationArea = gcnew GraphInfo();
  FemaleMosquitoesInSimulationArea->Title = "Female mosquitoes in simulation area";
  FemaleMosquitoesInSimulationArea->AxisX = "Date";
  FemaleMosquitoesInSimulationArea->AxisY = "# of female mosquitoes";
  FemaleMosquitoesInSimulationArea->GraphType = "Line";
  FemaleMosquitoesInSimulationArea->PrimaryOutputs->Add( OutputInfos::DensimLocation::FemaleMosquitoesInSimulationArea );

  FemaleMosquitoesPerPerson = gcnew GraphInfo();
  FemaleMosquitoesPerPerson->Title = "Female mosquitoes per person";
  FemaleMosquitoesPerPerson->AxisX = "Date";
  FemaleMosquitoesPerPerson->AxisY = "# female mosquitoes";
  FemaleMosquitoesPerPerson->GraphType = "Line";
  FemaleMosquitoesPerPerson->PrimaryOutputs->Add( OutputInfos::DensimLocation::FemaleMosquitoesPerPerson );

  FemaleMosquitoSurvival = gcnew GraphInfo();
  FemaleMosquitoSurvival->Title = "Female mosquito survival";
  FemaleMosquitoSurvival->AxisX = "Date";
  FemaleMosquitoSurvival->AxisY = "Survival";
  FemaleMosquitoSurvival->GraphType = "Line";
  FemaleMosquitoSurvival->PrimaryOutputs->Add( OutputInfos::DensimLocation::FemaleMosquitoSurvival );

  FemaleMosquitoWetWeight = gcnew GraphInfo();
  FemaleMosquitoWetWeight->Title = "Female mosquito wet weight";
  FemaleMosquitoWetWeight->AxisX = "Date";
  FemaleMosquitoWetWeight->AxisY = "Wet Weight (mg)";
  FemaleMosquitoWetWeight->GraphType = "Line";
  FemaleMosquitoWetWeight->PrimaryOutputs->Add( OutputInfos::DensimLocation::FemaleMosquitoWetWeight );
}
