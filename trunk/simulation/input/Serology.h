#ifndef INPUT_SEROLOGY_H
#define INPUT_SEROLOGY_H

#include <vector>



namespace input {


class SerologyClass
{
public:
  SerologyClass(void) {}
  virtual ~SerologyClass(void) {}

public:
  int Rank_;
  double Dengue1_;
  double Dengue2_;
  double Dengue3_;
  double Dengue4_;
};



class Serology
{
public:
  Serology(void);
  virtual ~Serology(void);

public:
  std::vector<SerologyClass> SerologyData_;
  int ManaDuration_;
  int MaeaDuration_;
  int HetDuration_;
};

};

#endif
