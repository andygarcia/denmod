#ifndef INPUT_VIROLOGY_H
#define INPUT_VIROLOGY_H



namespace input {

class VirusSerotype
{
public:
  VirusSerotype(void);
  VirusSerotype( int serotype, double viremia, int incubationDuration, int viremicDuration );
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
  VirusDevelopment(void)
  : RO25(3.359079E-3),
    DHA(15004.63),
    DHH(6.203379E+30),
    THALF(-2.17611E+30)
  {}
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
  HumanToMosquitoInfection(void)
  : LowTiterSetPoint_(4.00),
    LowTiterInfection_(0.100),
    HighTiterSetPoint_(8.00),
    HighTiterInfection_(1.00)
  {}
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
  EipTiterModification(void)
  : LowSetPoint_(1E+3),
    LowFactor_(1.25),
    HighSetPoint_(1E+8),
    HighFactor_(0.750)
  {}
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
  VirusSerotype & GetSerotype( unsigned int i );

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
