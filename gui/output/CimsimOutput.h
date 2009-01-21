#pragma once

#include "Charts.h"

using namespace System;



namespace gui {
namespace output {

public ref class ContainerOutput
{
public:
  ContainerOutput(void) {}
  ~ContainerOutput(void) {}

public:
  property array<double> ^ Depth {
     array<double> ^ get(void) {
       return _depth;
    }
    void set(array<double> ^ a) {
      _depth = a;
    }
  }

  property array<double> ^ Food {
     array<double> ^ get(void) {
       return _food;
    }
    void set(array<double> ^ a) {
      _food = a;
    }
  }

  property array<double> ^ MaxTemp {
     array<double> ^ get(void) {
       return _maxTemp;
    }
    void set(array<double> ^ a) {
      _maxTemp = a;
    }
  }

  property array<double> ^ MinTemp {
     array<double> ^ get(void) {
       return _minTemp;
    }
    void set(array<double> ^ a) {
      _minTemp = a;
    }
  }

  property array<double> ^ Eggs {
     array<double> ^ get(void) {
       return _eggs;
    }
    void set(array<double> ^ a) {
      _eggs = a;
    }
  }

  property array<double> ^ Larvae {
     array<double> ^ get(void) {
       return _larvae;
    }
    void set(array<double> ^ a) {
      _larvae = a;
    }
  }

  property array<double> ^ Pupae {
     array<double> ^ get(void) {
       return _pupae;
    }
    void set(array<double> ^ a) {
      _pupae = a;
    }
  }

  property array<double> ^ AvgDryPupWt {
     array<double> ^ get(void) {
       return _avgDryPupWt;
    }
    void set(array<double> ^ a) {
      _avgDryPupWt = a;
    }
  }

  property array<double> ^ NewFemales {
     array<double> ^ get(void) {
       return _newFemales;
    }
    void set(array<double> ^ a) {
      _newFemales = a;
    }
  }

  property array<double> ^ CumulativeFemales {
     array<double> ^ get(void) {
       return _cumulativeFemales;
    }
    void set(array<double> ^ a) {
      _cumulativeFemales = a;
    }
  }

  property array<double> ^ Oviposition {
     array<double> ^ get(void) {
       return _oviposition;
    }
    void set(array<double> ^ a) {
      _oviposition = a;
    }
  }

  property array<double> ^ TotalDensity {
     array<double> ^ get(void) {
       return _totalDensity;
    }
    void set(array<double> ^ a) {
      _totalDensity = a;
    }
  }

  property array<double> ^ UntreatedDensity {
     array<double> ^ get(void) {
       return _untreatedDensity;
    }
    void set(array<double> ^ a) {
      _untreatedDensity = a;
    }
  }

  property array<double> ^ TreatedDensity {
     array<double> ^ get(void) {
       return _treatedDensity;
    }
    void set(array<double> ^ a) {
      _treatedDensity = a;
    }
  }

  property array<double> ^ ExcludedDensity {
     array<double> ^ get(void) {
       return _excludedDensity;
    }
    void set(array<double> ^ a) {
      _excludedDensity = a;
    }
  }

  property array<double> ^ EggDevelopment {
     array<double> ^ get(void) {
       return _eggDevelopment;
    }
    void set(array<double> ^ a) {
      _eggDevelopment = a;
    }
  }

  property array<double> ^ LarvaeDevelopment {
     array<double> ^ get(void) {
       return _larvaeDevelopment;
    }
    void set(array<double> ^ a) {
      _larvaeDevelopment = a;
    }
  }

  property array<double> ^ PupaeDevelopment {
     array<double> ^ get(void) {
       return _pupaeDevelopment;
    }
    void set(array<double> ^ a) {
      _pupaeDevelopment = a;
    }
  }

private:
  array<double> ^ _depth;
  array<double> ^ _food;
  array<double> ^ _maxTemp;
  array<double> ^ _minTemp;
  array<double> ^ _eggs;
  array<double> ^ _larvae;
  array<double> ^ _pupae;
  array<double> ^ _avgDryPupWt;
  array<double> ^ _newFemales;
  array<double> ^ _cumulativeFemales;
  array<double> ^ _oviposition;
  array<double> ^ _totalDensity;
  array<double> ^ _untreatedDensity;
  array<double> ^ _treatedDensity;
  array<double> ^ _excludedDensity;
  array<double> ^ _eggDevelopment;
  array<double> ^ _larvaeDevelopment;
  array<double> ^ _pupaeDevelopment;
};



public ref class CimsimOutput : SimOutput
{
public:

public:
  CimsimOutput( DateTime startDate, DateTime stopDate );
  ~CimsimOutput(void);

public:
  output::Chart ^ CreateLocationChart( output::ChartIds chartId );
  output::Chart ^ CreateContainerChart( output::ChartIds chartId, int containerId );

  String ^ GetLocationExcelXml(void);
  String ^ GetContainerExcelXml( int containerId );

public:
  property DateTime StartDate {
    DateTime get(void) {
      return _startDate;
    }
  }

  property DateTime StopDate {
    DateTime get(void) {
      return _stopDate;
    }
  }

  property ContainerOutput ^ Containers[int] {
    ContainerOutput ^ get( int containerId ) {
      return _containers[containerId];
    }
    void set( int containerId, ContainerOutput ^ co ) {
      _containers[containerId] = co;
    }
  }

  property array<double> ^ TotalEggs {
    array<double> ^ get(void) {
      return _totalEggs;
    }
    void set(array<double> ^ a) {
      _totalEggs = a;
    }
  }

  property array<double> ^ TotalLarvae {
    array<double> ^ get(void) {
      return _totalLarvae;
    }
    void set(array<double> ^ a) {
      _totalLarvae = a;
    }
  }

  property array<double> ^ TotalPupae {
    array<double> ^ get(void) {
      return _totalPupae;
    }
    void set(array<double> ^ a) {
      _totalPupae = a;
    }
  }
  property array<double> ^ Females {
    array<double> ^ get(void) {
      return _females;
    }
    void set(array<double> ^ a) {
      _females = a;
    }
  }

  property array<double> ^ NewFemales {
    array<double> ^ get(void) {
      return _newFemales;
    }
    void set(array<double> ^ a) {
      _newFemales = a;
    }
  }

  property array<double> ^ HostSeekingFemales {
    array<double> ^ get(void) {
      return _hostSeekingFemales;
    }
    void set(array<double> ^ a) {
      _hostSeekingFemales = a;
    }
  }

  property array<double> ^ Oviposition {
    array<double> ^ get(void) {
      return _oviposition;
    }
    void set(array<double> ^ a) {
      _oviposition = a;
    }
  }

  property array<double> ^ AverageFemaleWeight {
    array<double> ^ get(void) {
      return _averageFemaleWeight;
    }
    void set(array<double> ^ a) {
      _averageFemaleWeight = a;
    }
  }

  property array<double> ^ MaximumTemperature {
    array<double> ^ get(void) {
      return _maximumTemperature;
    }
    void set(array<double> ^ a) {
      _maximumTemperature = a;
    }
  }

  property array<double> ^ AverageTemperature {
    array<double> ^ get(void) {
      return _averageTemperature;
    }
    void set(array<double> ^ a) {
      _averageTemperature = a;
    }
  }

  property array<double> ^ MinimumTemperature {
    array<double> ^ get(void) {
      return _minimumTemperature;
    }
    void set(array<double> ^ a) {
      _minimumTemperature = a;
    }
  }

  property array<double> ^ Rainfall {
    array<double> ^ get(void) {
      return _rainfall;
    }
    void set(array<double> ^ a) {
      _rainfall = a;
    }
  }

  property array<double> ^ RelativeHumidity {
    array<double> ^ get(void) {
      return _relativeHumidity;
    }
    void set(array<double> ^ a) {
      _relativeHumidity = a;
    }
  }

  property array<double> ^ SaturationDeficit {
    array<double> ^ get(void) {
      return _saturationDeficit;
    }
    void set(array<double> ^ a) {
      _saturationDeficit = a;
    }
  }


public:
  array<double> ^ _totalEggs;
  array<double> ^ _totalLarvae;
  array<double> ^ _totalPupae;
  array<double> ^ _females;
  array<double> ^ _newFemales;
  array<double> ^ _hostSeekingFemales;
  array<double> ^ _averageFemaleWeight;
  array<double> ^ _oviposition;

  array<double> ^ _maximumTemperature;
  array<double> ^ _averageTemperature;
  array<double> ^ _minimumTemperature;
  array<double> ^ _rainfall;
  array<double> ^ _relativeHumidity;
  array<double> ^ _saturationDeficit;

  Collections::Generic::Dictionary<int,ContainerOutput^> ^ _containers;
};

};
};
