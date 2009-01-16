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
  _cimsimContainer->Add( CimsimContainer::DevelopmentRates );

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



Chart ^
Chart::Create( ChartInfo ^ chartInfo, CimsimOutput ^ cimsimOutput, DensimOutput ^ densimOutput, Collections::Generic::List<int> ^ indices )
{
  Chart ^ chart = gcnew Chart();
  chart->_chartInfo = chartInfo;

  if( chartInfo == ChartInfos::CimsimLocation::Females ) {
    Plot ^ females = gcnew Plot();
    females->PlotType = "Line";
    females->Title = "Females per Hectare";
    females->AxisX = "Date";
    females->AxisY = "# of females per ha";
    females->PrimaryOutputs->Add( cimsimOutput->Location[OutputInfos::CimsimLocation::TotalFemales] );

    chart->Graphs->Add( females );
  }

  else if( chartInfo == ChartInfos::CimsimLocation::AverageFemaleWetWeight ) {
    Plot ^ averageFemaleWetWeight = gcnew Plot();
    averageFemaleWetWeight->PlotType = "Line";
    averageFemaleWetWeight->Title = "Average female wet weight";
    averageFemaleWetWeight->AxisX = "Date";
    averageFemaleWetWeight->AxisY = "Wet weight (mg)";
    averageFemaleWetWeight->PrimaryOutputs->Add( cimsimOutput->Location[OutputInfos::CimsimLocation::AverageFemaleWeight] );

    chart->Graphs->Add( averageFemaleWetWeight );
  }

  else if( chartInfo == ChartInfos::CimsimLocation::Oviposition ) {
    Plot ^ oviposition = gcnew Plot();
    oviposition->PlotType = "Line";
    oviposition->Title = "Oviposition";
    oviposition->AxisX = "Date";
    oviposition->AxisY = "# of eggs";
    oviposition->PrimaryOutputs->Add( cimsimOutput->Location[OutputInfos::CimsimLocation::Oviposition] );

    chart->Graphs->Add( oviposition );
  }

  else if( chartInfo == ChartInfos::CimsimLocation::Weather ) { 
    Plot ^ weather = gcnew Plot();
    weather->PlotType = "Line";
    weather->Title = "Weather";
    weather->AxisX = "Date";
    weather->AxisY = "°C / mm / mbars";
    weather->PrimaryOutputs->Add( cimsimOutput->Location[OutputInfos::CimsimLocation::MinimumTemperature] );
    weather->PrimaryOutputs->Add( cimsimOutput->Location[OutputInfos::CimsimLocation::AverageTemperature] );
    weather->PrimaryOutputs->Add( cimsimOutput->Location[OutputInfos::CimsimLocation::MaximumTemperature] );
    weather->PrimaryOutputs->Add( cimsimOutput->Location[OutputInfos::CimsimLocation::Rainfall] );
    weather->PrimaryOutputs->Add( cimsimOutput->Location[OutputInfos::CimsimLocation::RelativeHumidity] );
    weather->PrimaryOutputs->Add( cimsimOutput->Location[OutputInfos::CimsimLocation::SaturationDeficit] );

    chart->Graphs->Add( weather );
  }

  else if( chartInfo == ChartInfos::CimsimContainer::ContainerDensity ) {
    Plot ^ containerDensity = gcnew Plot();
    containerDensity->PlotType = "Line";
    containerDensity->Title = "Container densities";
    containerDensity->AxisX = "Date";
    containerDensity->AxisY = "# of containers per ha";
    for each( int i in indices ) {
      containerDensity->PrimaryOutputs->Add( cimsimOutput->Containers[i][OutputInfos::CimsimContainer::UntreatedDensity] );
      containerDensity->PrimaryOutputs->Add( cimsimOutput->Containers[i][OutputInfos::CimsimContainer::TreatedDensity] );
      containerDensity->PrimaryOutputs->Add( cimsimOutput->Containers[i][OutputInfos::CimsimContainer::ExcludedDensity] );
    }

    chart->Graphs->Add( containerDensity );
  }

  else if( chartInfo == ChartInfos::CimsimContainer::Depth ) {
    Plot ^ depth = gcnew Plot();
    depth->PlotType = "Line";
    depth->Title = "Water Depth";
    depth->AxisX = "Date";
    depth->AxisY = "cm";
    for each( int i in indices ) {
      depth->PrimaryOutputs->Add( cimsimOutput->Containers[i][OutputInfos::CimsimContainer::Depth] );
    }

    chart->Graphs->Add( depth );
  }

  else if( chartInfo == ChartInfos::CimsimContainer::Food ) {
    Plot ^ food = gcnew Plot();
    food->PlotType = "Line";
    food->Title = "Food";
    food->AxisX = "Date";
    food->AxisY = "mg";
    for each( int i in indices ) {
      food->PrimaryOutputs->Add( cimsimOutput->Containers[i][OutputInfos::CimsimContainer::Food] );
    }

    chart->Graphs->Add( food );
  }

  else if( chartInfo == ChartInfos::CimsimContainer::WaterTemperature ) {
    Plot ^ waterTemperature = gcnew Plot();
    waterTemperature->PlotType = "Line";
    waterTemperature->Title = "Water temperatures";
    waterTemperature->AxisX = "Date";
    waterTemperature->AxisY = "°C";
    for each( int i in indices ) {
      waterTemperature->PrimaryOutputs->Add( cimsimOutput->Containers[i][OutputInfos::CimsimContainer::MaximumTemperature] );
      waterTemperature->PrimaryOutputs->Add( cimsimOutput->Containers[i][OutputInfos::CimsimContainer::MinimumTemperature] );
    }

    chart->Graphs->Add( waterTemperature );
  }

  else if( chartInfo == ChartInfos::CimsimContainer::Immatures ) {
    Plot ^ eggs = gcnew Plot();
    eggs->PlotType = "Line";
    eggs->Title = "eggs";
    eggs->AxisX = "Date";
    eggs->AxisY = "# of eggs";
    for each( int i in indices ) {
      eggs->PrimaryOutputs->Add( cimsimOutput->Containers[i][OutputInfos::CimsimContainer::Eggs] );
    }

    Plot ^ larvae = gcnew Plot();
    larvae->PlotType = "Line";
    larvae->Title = "larvae";
    larvae->AxisX = "Date";
    larvae->AxisY = "# of larvae";
    for each( int i in indices ) {
      larvae->PrimaryOutputs->Add( cimsimOutput->Containers[i][OutputInfos::CimsimContainer::Larvae] );
    }

    Plot ^ pupae = gcnew Plot();
    pupae->PlotType = "Line";
    pupae->Title = "pupae";
    pupae->AxisX = "Date";
    pupae->AxisY = "# of pupae";
    for each( int i in indices ) {
      pupae->PrimaryOutputs->Add( cimsimOutput->Containers[i][OutputInfos::CimsimContainer::Pupae] );
    }

    chart->Graphs->Add( eggs );
    chart->Graphs->Add( larvae );
    chart->Graphs->Add( pupae );
  }

  else if( chartInfo == ChartInfos::CimsimContainer::Eggs ) {
    Plot ^ eggs = gcnew Plot();
    eggs->PlotType = "Line";
    eggs->Title = "eggs";
    eggs->AxisX = "Date";
    eggs->AxisY = "# of eggs";
    for each( int i in indices ) {
      eggs->PrimaryOutputs->Add( cimsimOutput->Containers[i][OutputInfos::CimsimContainer::Eggs] );
    }

    chart->Graphs->Add( eggs );
  }

  else if( chartInfo == ChartInfos::CimsimContainer::Larvae ) {
    Plot ^ larvae = gcnew Plot();
    larvae->PlotType = "Line";
    larvae->Title = "larvae";
    larvae->AxisX = "Date";
    larvae->AxisY = "# of larvae";
    for each( int i in indices ) {
      larvae->PrimaryOutputs->Add( cimsimOutput->Containers[i][OutputInfos::CimsimContainer::Larvae] );
    }

    chart->Graphs->Add( larvae );
  }


  else if( chartInfo == ChartInfos::CimsimContainer::Pupae ) {
    Plot ^ pupae = gcnew Plot();
    pupae->PlotType = "Line";
    pupae->Title = "pupae";
    pupae->AxisX = "Date";
    pupae->AxisY = "# of pupae";
    for each( int i in indices ) {
      pupae->PrimaryOutputs->Add( cimsimOutput->Containers[i][OutputInfos::CimsimContainer::Pupae] );
    }

    chart->Graphs->Add( pupae );
  }

  else if( chartInfo == ChartInfos::CimsimContainer::AveragePupalWeight ) {
    Plot ^ averagePupalWeight = gcnew Plot();
    averagePupalWeight->PlotType = "Line";
    averagePupalWeight->Title = "Average pupal weight";
    averagePupalWeight->AxisX = "Date";
    averagePupalWeight->AxisY = "mg";
    for each( int i in indices ) {
      averagePupalWeight->PrimaryOutputs->Add( cimsimOutput->Containers[i][OutputInfos::CimsimContainer::AveragePupalWeight] );
    }

    chart->Graphs->Add( averagePupalWeight );
  }

  else if( chartInfo == ChartInfos::CimsimContainer::NewFemales ) {
    Plot ^ newFemales = gcnew Plot();
    newFemales->PlotType = "Line";
    newFemales->Title = "New females";
    newFemales->AxisX = "Date";
    newFemales->AxisY = "# of new females";
    for each( int i in indices ) {
      newFemales->PrimaryOutputs->Add( cimsimOutput->Containers[i][OutputInfos::CimsimContainer::NewFemales] );
    }

    chart->Graphs->Add( newFemales );
  }
  
  else if( chartInfo == ChartInfos::CimsimContainer::CumulativeFemales ) {
    Plot ^ cumulativeFemales = gcnew Plot();
    cumulativeFemales->PlotType = "Line";
    cumulativeFemales->Title = "Cumulative females";
    cumulativeFemales->AxisX = "Date";
    cumulativeFemales->AxisY = "# of cumulative females";
    for each( int i in indices ) {
      cumulativeFemales->PrimaryOutputs->Add( cimsimOutput->Containers[i][OutputInfos::CimsimContainer::CumulativeFemales] );
    }

    chart->Graphs->Add( cumulativeFemales );
  }

  else if( chartInfo == ChartInfos::CimsimContainer::Oviposition ) {
    Plot ^ oviposition = gcnew Plot();
    oviposition->Title = "Oviposition";
    oviposition->AxisX = "Date";
    oviposition->AxisY = "# of eggs";
    oviposition->PlotType = "Line";
    for each( int i in indices ) {
      oviposition->PrimaryOutputs->Add( cimsimOutput->Containers[i][OutputInfos::CimsimContainer::Oviposition] );
    }

    chart->Graphs->Add( oviposition );
  }

  else if( chartInfo == ChartInfos::CimsimContainer::DevelopmentRates ) {
    Plot ^ g = gcnew Plot();
    g->Title = "Development Rates";
    g->AxisX = "Date";
    g->AxisY = "Development Rate";
    g->PlotType = "Line";
    for each( int i in indices ) {
      g->PrimaryOutputs->Add( cimsimOutput->Containers[i][OutputInfos::CimsimContainer::EggDevelopment] );
      g->PrimaryOutputs->Add( cimsimOutput->Containers[i][OutputInfos::CimsimContainer::LarvaeDevelopment] );
      g->PrimaryOutputs->Add( cimsimOutput->Containers[i][OutputInfos::CimsimContainer::PupaeDevelopment] );
    }

    chart->Graphs->Add( g );
  }

  else if( chartInfo == ChartInfos::DensimLocation::AgeDistribution ) {
    Plot ^ initialAgeDistribution = gcnew Plot();
    initialAgeDistribution->PlotType = "Column";
    initialAgeDistribution->Title = "Initial age distribution";
    initialAgeDistribution->AxisX = "Age class";
    initialAgeDistribution->AxisY = "# of individuals";
    initialAgeDistribution->PrimaryOutputs->Add( densimOutput->Location[OutputInfos::DensimLocation::InitialAgeDistribution] );

    Plot ^ finalAgeDistribution = gcnew Plot();
    finalAgeDistribution->PlotType = "Column";
    finalAgeDistribution->Title = "Final age distribution";
    finalAgeDistribution->AxisX = "Age class";
    finalAgeDistribution->AxisY = "# of individuals";
    finalAgeDistribution->PrimaryOutputs->Add( densimOutput->Location[OutputInfos::DensimLocation::FinalAgeDistribution] );

    chart->Graphs->Add( initialAgeDistribution );
    chart->Graphs->Add( finalAgeDistribution );
  }

  else if( chartInfo == ChartInfos::DensimLocation::SimulationArea ) {
    Plot ^ simulationArea = gcnew Plot();
    simulationArea->Title = "Simulation area in hectares";
    simulationArea->AxisX = "Date";
    simulationArea->AxisY = "Area (ha)";
    simulationArea->PlotType = "Line";
    simulationArea->PrimaryOutputs->Add( densimOutput->Location[OutputInfos::DensimLocation::SimulationArea] );

    chart->Graphs->Add( simulationArea );
  }

  else if( chartInfo == ChartInfos::DensimLocation::PopulationSize ) {
    Plot ^ populationSize = gcnew Plot();
    populationSize->Title = "Population size";
    populationSize->AxisX = "Date";
    populationSize->AxisY = "# of individuals";
    populationSize->PlotType = "Line";
    populationSize->PrimaryOutputs->Add( densimOutput->Location[OutputInfos::DensimLocation::PopulationSize] );

    chart->Graphs->Add( populationSize );
  }

  else if( chartInfo == ChartInfos::DensimLocation::BirthsAndDeaths ) {
    Plot ^ birthsByClass = gcnew Plot();
    birthsByClass->PlotType = "Column";
    birthsByClass->Title = "Births by age class";
    birthsByClass->AxisX = "Age class";
    birthsByClass->AxisY = "# of individuals";
    birthsByClass->PrimaryOutputs->Add( densimOutput->Location[OutputInfos::DensimLocation::BirthsByClass] );

    Plot ^ deathsByClass = gcnew Plot();
    deathsByClass->PlotType = "Column";
    deathsByClass->Title = "Deaths by age class";
    deathsByClass->AxisX = "Age class";
    deathsByClass->AxisY = "# DeathsByClass";
    deathsByClass->PrimaryOutputs->Add( densimOutput->Location[OutputInfos::DensimLocation::DeathsByClass] );

    // TODO - if generating Plot dynamically, also generate the percentage
    // data dynamically instead of having to pre calculate and store it in output object
    Plot ^ birthPercentagesByClass = gcnew Plot();
    birthPercentagesByClass->PlotType = "Column";
    birthPercentagesByClass->Title = "Birth percentages by age class";
    birthPercentagesByClass->AxisX = "Age class";
    birthPercentagesByClass->AxisY = "Percentage of births";
    birthPercentagesByClass->PrimaryOutputs->Add( densimOutput->Location[OutputInfos::DensimLocation::BirthPercentagesByClass] );

    Plot ^ deathPercentagesByClass = gcnew Plot();
    deathPercentagesByClass->PlotType = "Column";
    deathPercentagesByClass->Title = "Death percentages by age class";
    deathPercentagesByClass->AxisX = "Age class";
    deathPercentagesByClass->AxisY = "Percentage of deaths";
    deathPercentagesByClass->PrimaryOutputs->Add( densimOutput->Location[OutputInfos::DensimLocation::DeathPercentagesByClass] );

    chart->Graphs->Add( birthsByClass );
    chart->Graphs->Add( deathsByClass );
    chart->Graphs->Add( birthPercentagesByClass );
    chart->Graphs->Add( deathPercentagesByClass );
  }

  else if( chartInfo == ChartInfos::DensimLocation::FemaleMosquitoesInArea ) {
    Plot ^ femaleMosquitoesInArea = gcnew Plot();
    femaleMosquitoesInArea->PlotType = "Line";
    femaleMosquitoesInArea->Title = "Female mosquitoes in simulation area";
    femaleMosquitoesInArea->AxisX = "Date";
    femaleMosquitoesInArea->AxisY = "# of female mosquitoes";
    femaleMosquitoesInArea->PrimaryOutputs->Add( densimOutput->Location[OutputInfos::DensimLocation::FemaleMosquitoesInSimulationArea] );

    chart->Graphs->Add( femaleMosquitoesInArea );
  }

  else if( chartInfo == ChartInfos::DensimLocation::FemaleMosquitoesPerPerson ) {
    Plot ^ femaleMosquitoesPerPerson = gcnew Plot();
    femaleMosquitoesPerPerson->PlotType = "Line";
    femaleMosquitoesPerPerson->Title = "Female mosquitoes per person";
    femaleMosquitoesPerPerson->AxisX = "Date";
    femaleMosquitoesPerPerson->AxisY = "# female mosquitoes";
    femaleMosquitoesPerPerson->PrimaryOutputs->Add( densimOutput->Location[OutputInfos::DensimLocation::FemaleMosquitoesPerPerson] );

    chart->Graphs->Add( femaleMosquitoesPerPerson );
  }

  else if( chartInfo == ChartInfos::DensimLocation::FemaleMosquitoSurvival ) {
    Plot ^ femaleMosquitoSurvival = gcnew Plot();
    femaleMosquitoSurvival->PlotType = "Line";
    femaleMosquitoSurvival->Title = "Female mosquito survival";
    femaleMosquitoSurvival->AxisX = "Date";
    femaleMosquitoSurvival->AxisY = "Survival";
    femaleMosquitoSurvival->PrimaryOutputs->Add( densimOutput->Location[OutputInfos::DensimLocation::FemaleMosquitoSurvival] );

    chart->Graphs->Add( femaleMosquitoSurvival );
  }

  else if( chartInfo == ChartInfos::DensimLocation::FemaleMosquitoWetWeight ) {
    Plot ^ femaleMosquitoWetWeight = gcnew Plot();
    femaleMosquitoWetWeight->PlotType = "Line";
    femaleMosquitoWetWeight->Title = "Female mosquito wet weight";
    femaleMosquitoWetWeight->AxisX = "Date";
    femaleMosquitoWetWeight->AxisY = "Wet Weight (mg)";
    femaleMosquitoWetWeight->PrimaryOutputs->Add( densimOutput->Location[OutputInfos::DensimLocation::FemaleMosquitoWetWeight] );

    chart->Graphs->Add( femaleMosquitoWetWeight );
  }

  else if( chartInfo == ChartInfos::DensimSerotype::GeneralSeroprevalence ) {
    // sum counts
    Output ^ initSero = gcnew Output( gcnew ClassOutputInfo(Group::DensimLocation, "Initial Seroprevalence", "# of individual seropositive") );
    Output ^ finalSero = gcnew Output( gcnew ClassOutputInfo(Group::DensimLocation, "Final Seroprevalence", "# of individual seropositive") );

    // and calculated proportions based on initial and final population
    Output ^ initSeroProp = gcnew Output( gcnew ClassOutputInfo(Group::DensimLocation, "Initial Seroprevalence", "proportion of individuals seropostive") );
    Output ^ finalSeroProp = gcnew Output( gcnew ClassOutputInfo(Group::DensimLocation, "Initial Seroprevalence", "proportion of individuals seropostive") );

    Output ^ population = densimOutput->Location[OutputInfos::DensimLocation::PopulationSize];
    int initialPopulation = population->Data[0];
    int finalPopulation = population->Data[population->Data->Count - 1];

    for( int i = 1; i <= 18; ++i ) {
      // i is 1 index, Data is 0 index
      int initialTotal = densimOutput->Serotypes[1][OutputInfos::DensimSerotype::InitialSeroprevalence]->Data[i - 1]
                         + densimOutput->Serotypes[2][OutputInfos::DensimSerotype::InitialSeroprevalence]->Data[i - 1]
                         + densimOutput->Serotypes[3][OutputInfos::DensimSerotype::InitialSeroprevalence]->Data[i - 1]
                         + densimOutput->Serotypes[4][OutputInfos::DensimSerotype::InitialSeroprevalence]->Data[i - 1];

      initSero->Data->Add( initialTotal );
      initSeroProp->Data->Add( initialTotal / initialPopulation );

      int finalTotal = densimOutput->Serotypes[1][OutputInfos::DensimSerotype::FinalSeroprevalence]->Data[i - 1]
                       + densimOutput->Serotypes[2][OutputInfos::DensimSerotype::FinalSeroprevalence]->Data[i - 1]
                       + densimOutput->Serotypes[3][OutputInfos::DensimSerotype::FinalSeroprevalence]->Data[i - 1]
                       + densimOutput->Serotypes[4][OutputInfos::DensimSerotype::FinalSeroprevalence]->Data[i - 1];
      
      finalSero->Data->Add( finalTotal );
      finalSeroProp->Data->Add( finalTotal / finalPopulation );
    }

    Plot ^ initialSeroprevalence = gcnew Plot();
    initialSeroprevalence->PlotType = "Column";
    initialSeroprevalence->Title = "Initial Seroprevalence";
    initialSeroprevalence->AxisX = "Age Class";
    initialSeroprevalence->AxisY = "# of individuals seropositive";
    for( int i = 1; i <= 4; ++i ) {
      initialSeroprevalence->PrimaryOutputs->Add( densimOutput->Serotypes[i][OutputInfos::DensimSerotype::InitialSeroprevalence] );
      initialSeroprevalence->PrimaryOutputs[initialSeroprevalence->PrimaryOutputs->Count - 1]->Name = "Dengue " + 1;
    }

    Plot ^ finalSeroprevalence = gcnew Plot();
    finalSeroprevalence->PlotType = "Column";
    finalSeroprevalence->Title = "Final Seroprevalence";
    finalSeroprevalence->AxisX = "Age Class";
    finalSeroprevalence->AxisY = "# of individuals seropositive";
    for( int i = 1; i <= 4; ++i ) {
      finalSeroprevalence->PrimaryOutputs->Add( densimOutput->Serotypes[i][OutputInfos::DensimSerotype::FinalSeroprevalence] );
      finalSeroprevalence->PrimaryOutputs[finalSeroprevalence->PrimaryOutputs->Count - 1]->Name = "Dengue " + 1;
    }

  }

  else if( chartInfo == ChartInfos::DensimSerotype::EipDevelopmentRate ) {
    Plot ^ eipDevelopmentRate = gcnew Plot();
    eipDevelopmentRate->PlotType = "Line";
    eipDevelopmentRate->Title = "EIP Development Rate";
    eipDevelopmentRate->AxisX = "Date";
    eipDevelopmentRate->AxisY = L"day ⁻¹";
    for each( int i in indices ) {
      eipDevelopmentRate->PrimaryOutputs->Add( densimOutput->Serotypes[i][OutputInfos::DensimSerotype::EipDevelopmentRate] );
      eipDevelopmentRate->PrimaryOutputs[eipDevelopmentRate->PrimaryOutputs->Count - 1]->Name = "Dengue " + i;
    }

    chart->Graphs->Add( eipDevelopmentRate );
  }
  
  else if( chartInfo == ChartInfos::DensimSerotype::InfectiveMosquitoes ) {
    Plot ^ infectiveMosquitoes = gcnew Plot();
    infectiveMosquitoes->Title = "Infective Mosquitoes";
    infectiveMosquitoes->AxisX = "Date";
    infectiveMosquitoes->AxisY = "# of infective mosquitoes";
    infectiveMosquitoes->PlotType = "Line";
    for each( int i in indices ) {
      infectiveMosquitoes->PrimaryOutputs->Add( densimOutput->Serotypes[i][OutputInfos::DensimSerotype::InfectiveMosquitoes] );
      infectiveMosquitoes->PrimaryOutputs[infectiveMosquitoes->PrimaryOutputs->Count - 1]->Name = "Dengue " + i;
    }

    chart->Graphs->Add( infectiveMosquitoes );
  }
  
  else if( chartInfo == ChartInfos::DensimSerotype::PersonsIncubating ) {
    Plot ^ personsIncubating = gcnew Plot();
    personsIncubating->Title = "Persons Incubating";
    personsIncubating->AxisX = "Date";
    personsIncubating->AxisY = "# of persons";
    personsIncubating->PlotType = "Line";
    for each( int i in indices ) {
      personsIncubating->PrimaryOutputs->Add(  densimOutput->Serotypes[i][OutputInfos::DensimSerotype::PersonsIncubating] );
      personsIncubating->PrimaryOutputs[personsIncubating->PrimaryOutputs->Count - 1]->Name = "Dengue " + i;
    }

    chart->Graphs->Add( personsIncubating );
  }
  
  else if( chartInfo == ChartInfos::DensimSerotype::PersonsViremic ) {
    Plot ^ personsViremic = gcnew Plot();
    personsViremic->Title = "Persons Viremic";
    personsViremic->AxisX = "Date";
    personsViremic->AxisY = "# of persons";
    personsViremic->PlotType = "Line";
    for each( int i in indices ) {
      personsViremic->PrimaryOutputs->Add( densimOutput->Serotypes[i][OutputInfos::DensimSerotype::PersonsViremic] );
      personsViremic->PrimaryOutputs[personsViremic->PrimaryOutputs->Count - 1]->Name = "Dengue " + i;
    }

    chart->Graphs->Add( personsViremic );
  }

  else if( chartInfo == ChartInfos::DensimSerotype::PersonsWithVirus ) {
    Plot ^ personsWithVirus = gcnew Plot();
    personsWithVirus->Title = "Persons with Virus";
    personsWithVirus->AxisX = "Date";
    personsWithVirus->AxisY = "# of persons";
    personsWithVirus->PlotType = "Line";
    for each( int i in indices ) {
      personsWithVirus->PrimaryOutputs->Add( densimOutput->Serotypes[i][OutputInfos::DensimSerotype::PersonsWithVirus] );
      personsWithVirus->PrimaryOutputs[personsWithVirus->PrimaryOutputs->Count - 1]->Name = "Dengue " + i;
    }

    chart->Graphs->Add( personsWithVirus );
  }

  return chart;
}
