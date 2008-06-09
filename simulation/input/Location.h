#ifndef LOCATION_H
#define LOCATION_H

#include "Container.h"
#include "Weather.h"
#include "Biology.h"
#include "Control.h"
#include "Demographics.h"
#include "Serology.h"
#include "Virology.h"
#include "InfectionIntroduction.h"
#include "SequentialInfections.h"
#include <string>
#include <vector>



namespace input {


class Location
{
public:
  Location(void);
  ~Location(void);

  Container * FindContainerByName( std::string name );

public:
  std::string Name_;
  std::string Notes_;

  std::vector<Container*> Containers_;
  std::vector<Control*> Controls_;  

  Biology * Biology_;
  Weather * Weather_;

  Demographics * Demographics_;
  Serology * Serology_;
  Virology * Virology_;
  InfectionIntroduction * InfectionIntroduction_;
  SequentialInfections * SequentialInfections_;

  bool _doDebugOutput;
};

};

#endif
