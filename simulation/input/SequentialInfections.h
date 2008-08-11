#ifndef INPUT_SEQUENTIAL_INFECTIONS_H
#define INPUT_SEQUENTIAL_INFECTIONS_H

#include <string>
#include <utility>
#include <vector>



namespace input {


class SequentialInfection
{
public:
  enum InfectionType {
    One = 1,
    Two = 2,
    Three = 3,
    Four = 4,
    MAEA = 5
  };
  typedef std::pair<InfectionType, InfectionType> SequenceOfInfection;

public:
  SequentialInfection( std::string firstInfection, std::string secondInfection );
  virtual ~SequentialInfection(void) {}

  static InfectionType InfectionTypeFromString( std::string ssInfectionType );

  InfectionType GetFirstInfectionType();
  InfectionType GetSecondInfectionType();

public:
  SequenceOfInfection SequenceOfInfection_;
  int MinMonths_;
  int MaxMonths_;
  double Probability_;
  int AtRiskCutoffAge_;
  double Mortality_;
};



class SequentialInfections
{
public:
  typedef std::vector<SequentialInfection*> SequentialInfectionCollection;

public:
  SequentialInfections( SequentialInfectionCollection seqInfColl );

  SequentialInfections( SequentialInfection * f1t2, SequentialInfection * f1t3, SequentialInfection * f1t4, 
                        SequentialInfection * f2t1, SequentialInfection * f2t3, SequentialInfection * f2t4,
                        SequentialInfection * f3t1, SequentialInfection * f3t2, SequentialInfection * f3t4,
                        SequentialInfection * f4t1, SequentialInfection * f4t2, SequentialInfection * f4t3,
                        SequentialInfection * fMt1, SequentialInfection * fMt2, SequentialInfection * fMt3, SequentialInfection * fMt4 );

  virtual ~SequentialInfections(void);

public:
  SequentialInfection * GetSequentialInfection( SequentialInfection::InfectionType firstInfectionType,
                                                SequentialInfection::InfectionType secondInfectionType );
  SequentialInfection * GetSequentialInfection( std::string firstInfection, std::string secondInfection );
  SequentialInfection * GetSequentialInfection( int firstSerotype, int secondSerotype );
  SequentialInfection * GetMaeaSequentialInfection( int serotype );

private:
  SequentialInfectionCollection SequentialInfectionCollection_;
};



class FindSequenceOfInfection
{
public:
  FindSequenceOfInfection( SequentialInfection::InfectionType firstInf, SequentialInfection::InfectionType secondInf )
  {
    this->SequenceOfInfection_.first = firstInf;
    this->SequenceOfInfection_.second = secondInf;
  }

  bool operator() (SequentialInfection * si) const
  {
    if( si->SequenceOfInfection_.first == this->SequenceOfInfection_.first
      && si->SequenceOfInfection_.second == this->SequenceOfInfection_.second ) {
      return true;
    }
    else {
      return false;
    }
  } 

private:
  SequentialInfection::SequenceOfInfection SequenceOfInfection_;
};


};

#endif
