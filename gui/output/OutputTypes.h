#pragma once


using namespace System;



namespace gui {
namespace output {


ref class OutputInfo;

public ref class OutputInfoAttribute : public Attribute
{
public:
  property String ^ Name {
    String ^ get(void) {
      return _name;
    }
    void set(String ^ s) {
      _name = s;
    }
  }

  property String ^ Units {
    String ^ get(void) {
      return _units;
    }
    void set( String ^ s ) {
      _units = s;
    }
  }

private:
  String ^ _name;
  String ^ _units;
};



public enum class Group : int
{
  CimsimLocation = 0,
  CimsimContainer,
  DensimLocation,
  DensimSerotype
};



public ref class CimsimOutputs abstract sealed
{
public:
  ref class Location
  {
    [OutputInfoAttribute(Name="Total Eggs",Units="#/ha")]
    static OutputInfo ^ TotalEggs;

    [OutputInfoAttribute(Name="Total Larvae",Units="#/ha")]
    static OutputInfo ^ TotalLarvae;

    [OutputInfoAttribute(Name="Total Pupae",Units="#/ha")]
    static OutputInfo ^ TotalPupae;

    [OutputInfoAttribute(Name="Total Females",Units="#/ha")]
    static OutputInfo ^ TotalFemales;

    [OutputInfoAttribute(Name="New Females",Units="#/ha")]
    static OutputInfo ^ NewFemales;

    [OutputInfoAttribute(Name="Average Female Weight",Units="mg")]
    static OutputInfo ^ AverageFemaleWeight;

    [OutputInfoAttribute(Name="Oviposition",Units="#")]
    static OutputInfo ^ Oviposition;

    [OutputInfoAttribute(Name="Maximum Temperature",Units="C")]
    static OutputInfo ^ MaximumTemperature;

    [OutputInfoAttribute(Name="Average Temperature",Units="C")]
    static OutputInfo ^ AverageTemperature;

    [OutputInfoAttribute(Name="Minimum Temperature",Units="C")]
    static OutputInfo ^ MinimumTemperature;

    [OutputInfoAttribute(Name="Rainfall",Units="mm")]
    static OutputInfo ^ Rainfall;

    [OutputInfoAttribute(Name="Relative Humidity",Units="%")]
    static OutputInfo ^ RelativeHumidity;

    [OutputInfoAttribute(Name="Saturation Deficit",Units="mbars")]
    static OutputInfo ^ SaturationDeficit;
  };

  ref class Container
  {
    [OutputInfoAttribute(Name="Depth",Units="cm")]
    static OutputInfo ^ Depth;

    [OutputInfoAttribute(Name="Food",Units="mg")]
    static OutputInfo ^ Food;

    [OutputInfoAttribute(Name="Maximum Water Temperature",Units="C")]
    static OutputInfo ^ MaximumTemperature;

    [OutputInfoAttribute(Name="Minimum Water Temperature",Units="C")]
    static OutputInfo ^ MinimumTemperature;

    [OutputInfoAttribute(Name="Eggs",Units="#")]
    static OutputInfo ^ Eggs;

    [OutputInfoAttribute(Name="Larvae",Units="#")]
    static OutputInfo ^ Larvae;

    [OutputInfoAttribute(Name="Pupae",Units="#")]
    static OutputInfo ^ Pupae;

    [OutputInfoAttribute(Name="Average Pupal Weight",Units="mg")]
    static OutputInfo ^ AveragePupalWeight;

    [OutputInfoAttribute(Name="New Females",Units="#")]
    static OutputInfo ^ NewFemales;

    [OutputInfoAttribute(Name="Cumulative Females",Units="#")]
    static OutputInfo ^ CumulativeFemales;

    [OutputInfoAttribute(Name="Oviposition",Units="#")]
    static OutputInfo ^ Oviposition;

    [OutputInfoAttribute(Name="Untreated Density",Units="#/ha")]
    static OutputInfo ^ UntreatedDensity;

    [OutputInfoAttribute(Name="Treated Density",Units="#/ha")]
    static OutputInfo ^ TreatedDensity;

    [OutputInfoAttribute(Name="Excluded Density",Units="#/ha")]
    static OutputInfo ^ ExcludedDensity;
  };
};



ref class DensimOutputs abstract sealed
{
public:
  ref class Location
  {
    [OutputInfoAttribute(Name="Initial Age Distribution",Units="# of individuals")]
    static OutputInfo ^ InitialAgeDistribution;

    [OutputInfoAttribute(Name="Final Age Distribution",Units="# of individuals")]
    static OutputInfo ^ FinalAgeDistribution;

    [OutputInfoAttribute(Name="Simulation Area",Units="ha")]
    static OutputInfo ^ SimulationArea;

    [OutputInfoAttribute(Name="Population Size",Units="# of individuals")]
    static OutputInfo ^ PopulationSize;

    [OutputInfoAttribute(Name="Births by Class",Units="# births")]
    static OutputInfo ^ BirthsByClass;

    [OutputInfoAttribute(Name="Deaths by Class",Units="# of individuals")]
    static OutputInfo ^ DeathsByClass;
    
    [OutputInfoAttribute(Name="Birth Percentages by Class",Units="# of individuals")]
    static OutputInfo ^ BirthPercentagesByClass;
    
    [OutputInfoAttribute(Name="Death Percentages by Class",Units="# of individuals")]
    static OutputInfo ^ DeathPercentagesByClass;

    [OutputInfoAttribute(Name="Female Mosquitoes in Area",Units="# in area")]
    static OutputInfo ^ FemaleMosquitoesInSimulationArea;

    [OutputInfoAttribute(Name="Female Mosquitoes per Hectare",Units="# / ha")]
    static OutputInfo ^ FemaleMosquitoesPerHectare;

    [OutputInfoAttribute(Name="Female Mosquitoes per Person",Units="# / person")]
    static OutputInfo ^ FemaleMosquitoesPerPerson;

    [OutputInfoAttribute(Name="Female Survival",Units="")]
    static OutputInfo ^ FemaleMosquitoSurvival;

    [OutputInfoAttribute(Name="Female Mosquitoes Wet Weight",Units="mg")]
    static OutputInfo ^ FemaleMosquitoWetWeight;

    //GeneralSeroprevalence,
    //DetailedSeroprevalence,

    //NewCases,
    //PredictedHFSS,
    //DeathsHFSS
  };

  ref class Serotype
  {
  public:
    [OutputInfoAttribute(Name="EIP Development Rate",Units="1/day")]
    static OutputInfo ^ EipDevelopmentRate;

    [OutputInfoAttribute(Name="Infective Mosquitoes",Units="# of infective mosquitoes")]
    static OutputInfo ^ InfectiveMosquitoes;

    [OutputInfoAttribute(Name="Potentially Infective Bites",Units="# of bites")]
    static OutputInfo ^ PotentiallyInfectiveBites;

    [OutputInfoAttribute(Name="Persons Incubating",Units="# of persons incubating")]
    static OutputInfo ^ PersonsIncubating;

    [OutputInfoAttribute(Name="Persons Viremic",Units="# of persons viremic")]
    static OutputInfo ^ PersonsViremic;

    [OutputInfoAttribute(Name="Persons with Virus",Units="# of persons incubating or viremic")]
    static OutputInfo ^ PersonsWithVirus;
  };
};


};
};
