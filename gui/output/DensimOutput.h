#pragma once

#include "Charts.h"

using namespace System;



namespace gui {
namespace output {

typedef array<double> DetailedSeroprevalence;

public ref class SerotypeOutput
{
public:
  SerotypeOutput(void)
  : _classSpecificSeroprevalence(gcnew Collections::Generic::Dictionary<int,DetailedSeroprevalence^>())
  {}
  virtual ~SerotypeOutput(void) {}

public:
  property array<double> ^ EipDevelopmentRate {
    array<double> ^ get(void) {
      return _eipDevelopmentRate;
    }
    void set(array<double> ^ a) {
      _eipDevelopmentRate = a;
    }
  }

  property array<double> ^ InfectiveMosquitoes {
    array<double> ^ get(void) {
      return _infectiveMosquitoes;
    }
    void set(array<double> ^ a) {
      _infectiveMosquitoes = a;
    }
  }

  property array<double> ^ PersonsIncubating {
    array<double> ^ get(void) {
      return _personsIncubating;
    }
    void set(array<double> ^ a) {
      _personsIncubating = a;
    }
  }

  property array<double> ^ PersonsViremic {
    array<double> ^ get(void) {
      return _personsViremic;
    }
    void set(array<double> ^ a) {
      _personsViremic = a;
    }
  }

  property array<double> ^ PersonsWithVirus {
    array<double> ^ get(void) {
      return _personsWithVirus;
    }
    void set(array<double> ^ a) {
      _personsWithVirus = a;
    }
  }

  property array<int> ^ InitialSeroDistribution {
    array<int> ^ get(void) {
      return _initialSeroDistribution;
    }
    void set(array<int> ^ a) {
      _initialSeroDistribution = a;
    }
  }

  property array<int> ^ FinalSeroDistribution {
    array<int> ^ get(void) {
      return _finalSeroDistribution;
    }
    void set(array<int> ^ a) {
      _finalSeroDistribution = a;
    }
  }

  property DetailedSeroprevalence ^ ClassSpecificSeroprevalence[int] {
    DetailedSeroprevalence ^ get(int seroClass) {
      return _classSpecificSeroprevalence[seroClass];
    }
    void set(int seroClass, DetailedSeroprevalence ^ ds) {
      _classSpecificSeroprevalence[seroClass] = ds;
    }
  }


private:
  array<double> ^ _eipDevelopmentRate;
  array<double> ^ _infectiveMosquitoes;
  array<double> ^ _personsIncubating;
  array<double> ^ _personsViremic;
  array<double> ^ _personsWithVirus;

  array<int> ^ _initialSeroDistribution;
  array<int> ^ _finalSeroDistribution;

  Collections::Generic::Dictionary<int,DetailedSeroprevalence^> ^ _classSpecificSeroprevalence;
};



public ref class DensimOutput : SimOutput
{
private:
  static DensimOutput(void);

public:
  DensimOutput( double humanDensity, DateTime startDate, DateTime stopDate );
  virtual ~DensimOutput(void);

public:
  output::Chart ^ CreateChart( ChartInfo ^ chartInfo );
  output::Chart ^ CreateDetailedSeroprevalenceChart( int seroClass );

public:
  property array<int> ^ InitialAgeDistribution {
    array<int> ^ get(void) {
      return _initialAgeDistribution;
    }
    void set(array<int> ^ a) {
      _initialAgeDistribution = a;
    }
  }

  property array<int> ^ FinalAgeDistribution {
    array<int> ^ get(void) {
      return _finalAgeDistribution;
    }
    void set(array<int> ^ a) {
      _finalAgeDistribution = a;
    }
  }

  property array<int> ^ BirthsByClass {
    array<int> ^ get(void) {
      return _birthsByClass;
    }
    void set(array<int> ^ a) {
      _birthsByClass = a;
    }
  }

  property array<int> ^ DeathsByClass {
    array<int> ^ get(void) {
      return _deathsByClass;
    }
    void set(array<int> ^ a) {
      _deathsByClass = a;
    }
  }

  property array<double> ^ PopulationSize {
    array<double> ^ get(void) {
      return _populationSize;
    }
    void set(array<double> ^ a) {
      _populationSize = a;
    }
  }

  property array<double> ^ FemaleMosquitoesInSimulationArea {
    array<double> ^ get(void) {
      return _femaleMosquitoesInSimulationArea;
    }
    void set(array<double> ^ a) {
      _femaleMosquitoesInSimulationArea = a;
    }
  }

  property array<double> ^ PotentiallyInfectiveBites {
    array<double> ^ get(void) {
      return _potentiallyInfectiveBites;
    }
    void set(array<double> ^ a) {
      _potentiallyInfectiveBites = a;
    }
  }

  property SerotypeOutput ^ Serotypes[int] {
    SerotypeOutput ^ get(int serotype) {
      return _serotypes[serotype-1];
    }
    void set(int serotype, SerotypeOutput ^ so) {
      _serotypes[serotype] = so;
    }
  }

private:
  double _humanDensity;
  int _numDays;

  array<int> ^ _initialAgeDistribution;
  array<int> ^ _finalAgeDistribution;
  array<int> ^ _birthsByClass;
  array<int> ^ _deathsByClass;

  array<double> ^ _populationSize;
  array<double> ^ _femaleMosquitoesInSimulationArea;
  array<double> ^ _potentiallyInfectiveBites;
  
  Collections::Generic::Dictionary<int,SerotypeOutput^> ^ _serotypes;

  //NewCases,
  //PredictedHFSS,
  //DeathsHFSS

  static Collections::Generic::Dictionary<int,String^> ^ _seroClasses;
};

};
};
