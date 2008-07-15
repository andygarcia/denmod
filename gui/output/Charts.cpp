#include "StdAfx.h"
#include "Charts.h"

using namespace gui::output;



static
ChartInfos::ChartInfos(void)
{
  _cimsimLocation = gcnew ChartInfoCollection();
  _cimsimContainer = gcnew ChartInfoCollection();
  _densimLocation = gcnew ChartInfoCollection();
  _densimSerotype = gcnew ChartInfoCollection();

  _groupToCollection = gcnew Collections::Generic::Dictionary<Group,ChartInfoCollection^>();
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
  _cimsimContainer->Add( CimsimContainer::Immatures );
  _cimsimContainer->Add( CimsimContainer::Eggs );
  _cimsimContainer->Add( CimsimContainer::Larvae );
  _cimsimContainer->Add( CimsimContainer::Pupae );
  _cimsimContainer->Add( CimsimContainer::AveragePupalWeight );
  _cimsimContainer->Add( CimsimContainer::NewFemales );
  _cimsimContainer->Add( CimsimContainer::CumulativeFemales );
  _cimsimContainer->Add( CimsimContainer::Oviposition );

  _densimLocation->Add( DensimLocation::AgeDistribution );
  _densimLocation->Add( DensimLocation::SimulationArea );
  _densimLocation->Add( DensimLocation::PopulationSize );
  _densimLocation->Add( DensimLocation::BirthsAndDeaths );
  _densimLocation->Add( DensimLocation::FemaleMosquitoesInArea );
  _densimLocation->Add( DensimLocation::FemaleMosquitoesPerPerson );
  _densimLocation->Add( DensimLocation::FemaleMosquitoSurvival );
  _densimLocation->Add( DensimLocation::FemaleMosquitoWetWeight );

  _densimSerotype->Add( DensimSerotype::EipDevelopmentRate );
  _densimSerotype->Add( DensimSerotype::InfectiveMosquitoes );
  _densimSerotype->Add( DensimSerotype::PersonsIncubating );
  _densimSerotype->Add( DensimSerotype::PersonsViremic );
  _densimSerotype->Add( DensimSerotype::PersonsWithVirus );
}



ChartInfoCollection ^
ChartInfos::GetChartInfoCollection( Group outputGroup )
{
  return _groupToCollection[outputGroup];
}



static
ChartInfos::CimsimLocation::CimsimLocation(void)
{
  Females = gcnew ChartInfo();
  Females->Name = "Females";
  Females->GraphInfos->Add( GraphInfos::CimsimLocation::Females );

  AverageFemaleWetWeight = gcnew ChartInfo();
  AverageFemaleWetWeight->Name = "Average Female Wet Weight";
  AverageFemaleWetWeight->GraphInfos->Add( GraphInfos::CimsimLocation::AverageFemaleWetWeight );

  Oviposition = gcnew ChartInfo();
  Oviposition->Name = "Oviposition";
  Oviposition->GraphInfos->Add( GraphInfos::CimsimLocation::Oviposition );

  Weather = gcnew ChartInfo();
  Weather->Name = "Weather";
  Weather->GraphInfos->Add( GraphInfos::CimsimLocation::Weather );
}



static
ChartInfos::CimsimContainer::CimsimContainer(void)
{
    ContainerDensity = gcnew ChartInfo();
    ContainerDensity->Name = "Container Density";
    ContainerDensity->GraphInfos->Add( GraphInfos::CimsimContainer::ContainerDensity );

    Depth = gcnew ChartInfo();
    Depth->Name = "Water Depth";
    Depth->GraphInfos->Add( GraphInfos::CimsimContainer::Depth );

    Food = gcnew ChartInfo();
    Food->Name = "Food";
    Food->GraphInfos->Add( GraphInfos::CimsimContainer::Food );

    WaterTemperature = gcnew ChartInfo();
    WaterTemperature->Name = "Water Temperature";
    WaterTemperature->GraphInfos->Add( GraphInfos::CimsimContainer::WaterTemperature );

    Immatures = gcnew ChartInfo();
    Immatures->Name = "All immature life stages";
    Immatures->GraphInfos->Add( GraphInfos::CimsimContainer::Eggs );
    Immatures->GraphInfos->Add( GraphInfos::CimsimContainer::Larvae );
    Immatures->GraphInfos->Add( GraphInfos::CimsimContainer::Pupae );

    Eggs = gcnew ChartInfo();
    Eggs->Name = "Eggs";
    Eggs->GraphInfos->Add( GraphInfos::CimsimContainer::Eggs );

    Larvae = gcnew ChartInfo();
    Larvae->Name = "Larvae";
    Larvae->GraphInfos->Add( GraphInfos::CimsimContainer::Larvae );

    Pupae = gcnew ChartInfo();
    Pupae->Name = "Pupae";
    Pupae->GraphInfos->Add( GraphInfos::CimsimContainer::Pupae );

    AveragePupalWeight = gcnew ChartInfo();
    AveragePupalWeight->Name = "Average Pupal Weight";
    AveragePupalWeight->GraphInfos->Add( GraphInfos::CimsimContainer::AveragePupalWeight );

    NewFemales = gcnew ChartInfo();
    NewFemales->Name = "New Females";
    NewFemales->GraphInfos->Add( GraphInfos::CimsimContainer::NewFemales );

    CumulativeFemales = gcnew ChartInfo();
    CumulativeFemales->Name = "Cumulative Females";
    CumulativeFemales->GraphInfos->Add( GraphInfos::CimsimContainer::CumulativeFemales );

    Oviposition = gcnew ChartInfo();
    Oviposition->Name = "Oviposition";
    Oviposition->GraphInfos->Add( GraphInfos::CimsimContainer::Oviposition );
}



static
ChartInfos::DensimLocation::DensimLocation(void)
{
  AgeDistribution = gcnew ChartInfo();
  AgeDistribution->Name= "Age Distributions";
  AgeDistribution->GraphInfos->Add( GraphInfos::DensimLocation::InitialAgeDistribution );
  AgeDistribution->GraphInfos->Add( GraphInfos::DensimLocation::FinalAgeDistribution );

  SimulationArea = gcnew ChartInfo();
  SimulationArea->Name= "Simulation Area";
  SimulationArea->GraphInfos->Add( GraphInfos::DensimLocation::SimulationArea );

  PopulationSize = gcnew ChartInfo();
  PopulationSize->Name= "Population Size";
  PopulationSize->GraphInfos->Add( GraphInfos::DensimLocation::PopulationSize );

  BirthsAndDeaths = gcnew ChartInfo();
  BirthsAndDeaths->Name= "Births and Deaths";
  BirthsAndDeaths->GraphInfos->Add( GraphInfos::DensimLocation::BirthsByClass );
  BirthsAndDeaths->GraphInfos->Add( GraphInfos::DensimLocation::BirthPercentagesByClass );
  BirthsAndDeaths->GraphInfos->Add( GraphInfos::DensimLocation::DeathsByClass );
  BirthsAndDeaths->GraphInfos->Add( GraphInfos::DensimLocation::DeathPercentagesByClass );

  FemaleMosquitoesInArea = gcnew ChartInfo();
  FemaleMosquitoesInArea->Name= "Female Mosquitoes In Area";
  FemaleMosquitoesInArea->GraphInfos->Add( GraphInfos::DensimLocation::FemaleMosquitoesInSimulationArea );

  FemaleMosquitoesPerPerson = gcnew ChartInfo();
  FemaleMosquitoesPerPerson->Name= "Female Mosquitoes Per Person";
  FemaleMosquitoesPerPerson->GraphInfos->Add( GraphInfos::DensimLocation::FemaleMosquitoesPerPerson );

  FemaleMosquitoSurvival = gcnew ChartInfo();
  FemaleMosquitoSurvival->Name= "Female Mosquito Survival";
  FemaleMosquitoSurvival->GraphInfos->Add( GraphInfos::DensimLocation::FemaleMosquitoSurvival );

  FemaleMosquitoWetWeight = gcnew ChartInfo();
  FemaleMosquitoWetWeight->Name= "Female Mosquito Wet Weight";
  FemaleMosquitoWetWeight->GraphInfos->Add( GraphInfos::DensimLocation::FemaleMosquitoWetWeight );
}



static
ChartInfos::DensimSerotype::DensimSerotype(void)
{
  EipDevelopmentRate = gcnew ChartInfo();
  EipDevelopmentRate->Name = "EIP Development Rate";
  EipDevelopmentRate->GraphInfos->Add( GraphInfos::DensimSerotype::EipDevelopmentRate );

  InfectiveMosquitoes = gcnew ChartInfo();
  InfectiveMosquitoes->Name = "Infective Mosquitoes";
  InfectiveMosquitoes->GraphInfos->Add( GraphInfos::DensimSerotype::InfectiveMosquitoes );
  
  PersonsIncubating = gcnew ChartInfo();
  PersonsIncubating->Name = "Persons Incubating";
  PersonsIncubating->GraphInfos->Add( GraphInfos::DensimSerotype::PersonsIncubating );
  
  PersonsViremic = gcnew ChartInfo();
  PersonsViremic->Name = "Persons Viremic";
  PersonsViremic->GraphInfos->Add( GraphInfos::DensimSerotype::PersonsViremic );
  
  PersonsWithVirus = gcnew ChartInfo();
  PersonsWithVirus->Name = "Persons With Virus";
  PersonsWithVirus->GraphInfos->Add( GraphInfos::DensimSerotype::PersonsWithVirus );
}
