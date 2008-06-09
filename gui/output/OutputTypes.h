#pragma once

#include "Output.h"

using namespace System;



namespace gui {
namespace output {

public enum class OutputsTypes2 : int
{


};


public ref class OutputTypes abstract sealed
{
public:
  ref class Cimsim abstract sealed
  {
  public:
    enum class Location : int
    {
      [OutputInfoAttribute(Name="Total Eggs",Units="#/ha")]
      TotalEggs,
      [OutputInfoAttribute(Name="Total Larvae",Units="#/ha")]
      TotalLarvae,
      [OutputInfoAttribute(Name="Total Pupae",Units="#/ha")]
      TotalPupae,
      [OutputInfoAttribute(Name="Total Females",Units="#/ha")]
      TotalFemales,
      [OutputInfoAttribute(Name="New Females",Units="#/ha")]
      NewFemales,
      [OutputInfoAttribute(Name="Average Female Weight",Units="mg")]
      AverageFemaleWeight,
      [OutputInfoAttribute(Name="Oviposition",Units="#")]
      Oviposition,
      [OutputInfoAttribute(Name="Maximum Temperature",Units="C")]
      MaximumTemperature,
      [OutputInfoAttribute(Name="Average Temperature",Units="C")]
      AverageTemperature,
      [OutputInfoAttribute(Name="Minimum Temperature",Units="C")]
      MinimumTemperature,
      [OutputInfoAttribute(Name="Rainfall",Units="mm")]
      Rainfall,
      [OutputInfoAttribute(Name="Relative Humidity",Units="%")]
      RelativeHumidity,
      [OutputInfoAttribute(Name="Saturation Deficit",Units="mbars")]
      SaturationDeficit
    };

    enum class Container : int
    {
      [OutputInfoAttribute(Name="Depth",Units="cm")]
      Depth = Cimsim::Location::SaturationDeficit + 1,
      [OutputInfoAttribute(Name="Food",Units="mg")]
      Food,
      [OutputInfoAttribute(Name="Maximum Water Temperature",Units="C")]
      MaximumTemperature,
      [OutputInfoAttribute(Name="Minimum Water Temperature",Units="C")]
      MinimumTemperature,
      [OutputInfoAttribute(Name="Eggs",Units="#")]
      Eggs,
      [OutputInfoAttribute(Name="Larvae",Units="#")]
      Larvae,
      [OutputInfoAttribute(Name="Pupae",Units="#")]
      Pupae,
      [OutputInfoAttribute(Name="Average Pupal Weight",Units="mg")]
      AveragePupalWeight,
      [OutputInfoAttribute(Name="New Females",Units="#")]
      NewFemales,
      [OutputInfoAttribute(Name="Cumulative Females",Units="#")]
      CumulativeFemales,
      [OutputInfoAttribute(Name="Oviposition",Units="#")]
      Oviposition,
      [OutputInfoAttribute(Name="Untreated Density",Units="#/ha")]
      UntreatedDensity,
      [OutputInfoAttribute(Name="Treated Density",Units="#/ha")]
      TreatedDensity,
      [OutputInfoAttribute(Name="Excluded Density",Units="#/ha")]
      ExcludedDensity
    };
  };

  ref class Densim abstract sealed
  {
  public:
    enum class Location : int
    {
      [OutputInfoAttribute(Name="Initial Age Distribution",Units="# of individuals")]
      InitialAgeDistribution,
      [OutputInfoAttribute(Name="Final Age Distribution",Units="# of individuals")]
      FinalAgeDistribution,
      [OutputInfoAttribute(Name="Simulation Area",Units="ha")]
      SimulationArea,
      [OutputInfoAttribute(Name="Population Size",Units="# of individuals")]
      PopulationSize,

      [OutputInfoAttribute(Name="Births by Class",Units="# births")]
      BirthsByClass,
      [OutputInfoAttribute(Name="Deaths by Class",Units="# of individuals")]
      DeathsByClass,
      [OutputInfoAttribute(Name="Birth Percentages by Class",Units="# of individuals")]
      BirthPercentagesByClass,
      [OutputInfoAttribute(Name="Death Percentages by Class",Units="# of individuals")]
      DeathPercentagesByClass,

      [OutputInfoAttribute(Name="Female Mosquitoes in Area",Units="# in area")]
      FemaleMosquitoesInSimulationArea,
      [OutputInfoAttribute(Name="Female Mosquitoes per Hectare",Units="# / ha")]
      FemaleMosquitoesPerHectare,
      [OutputInfoAttribute(Name="Female Mosquitoes per Person",Units="# / person")]
      FemaleMosquitoesPerPerson,
      [OutputInfoAttribute(Name="Female Survival",Units="")]
      FemaleMosquitoSurvival,
      [OutputInfoAttribute(Name="Female Mosquitoes Wet Weight",Units="mg")]
      FemaleMosquitoWetWeight,

      [OutputInfoAttribute(Name="EIP Development Rate",Units="1/day")]
      EipDevelopmentRate,
      [OutputInfoAttribute(Name="Infective Mosquitoes",Units="# of infective mosquitoes")]
      InfectiveMosquitoes,
      [OutputInfoAttribute(Name="Potentially Infective Bites",Units="# of bites")]
      PotentiallyInfectiveBites,

      [OutputInfoAttribute(Name="Persons Incubating",Units="# of persons incubating")]
      PersonsIncubating,
      [OutputInfoAttribute(Name="Persons Viremic",Units="# of persons viremic")]
      PersonsViremic,
      [OutputInfoAttribute(Name="Persons with Virus",Units="# of persons incubating or viremic")]
      PersonsWithVirus,

      //GeneralSeroprevalence,
      //DetailedSeroprevalence,

      //NewCases,
      //PredictedHFSS,
      //DeathsHFSS
    };
    enum class Serotype : int
    {

    };
  };

};

};
};
