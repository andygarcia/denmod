#ifndef INPUT_VIROLOGY_H
#define INPUT_VIROLOGY_H



namespace input {


class VirusSerotype
{
public:
  VirusSerotype(void);
  virtual ~VirusSerotype(void);

public:
  int Serotype_;
  double Viremia_;
  int IncubationDuration_;
  int ViremicDuration_;
};



class VirusDevelopment
{
public:
  VirusDevelopment(void) {}
  ~VirusDevelopment(void) {}

public:
  double RO25;
  double DHA;
  double DHH;
  double THALF;
};


class HumanToMosquitoInfection
{
public:
  HumanToMosquitoInfection(void) {}
  virtual ~HumanToMosquitoInfection(void) {}

public:
  double LowTiterSetPoint_;
  double LowTiterInfection_;
  double HighTiterSetPoint_;
  double HighTiterInfection_;
};



class EipTiterModification
{
public:
  EipTiterModification(void) {}
  virtual ~EipTiterModification(void) {}

public:
  double LowSetPoint_;
  double LowFactor_;
  double HighSetPoint_;
  double HighFactor_;
};



class Eip
{
public:
  Eip(void) {}
  virtual ~Eip(void) {}

public:
  VirusDevelopment Development_;
  EipTiterModification EipTiterModification_;
};



class Virology
{
public:
  Virology(void);
  virtual ~Virology(void);

public:
  VirusSerotype Dengue1_;
  VirusSerotype Dengue2_;
  VirusSerotype Dengue3_;
  VirusSerotype Dengue4_;

  HumanToMosquitoInfection HumanToMosquitoInfection_;
  double MosquitoToHumanNominalProbabilityOfInfection_;
  double MosquitoCountForStochasticity;
  Eip Eip_;
};

};

#endif
