#include "StdAfx.h"
#include "SequentialInfections.h"
#include <algorithm>

using namespace input;



SequentialInfection::SequentialInfection( std::string firstInfection, std::string secondInfection )
{
  InfectionType firstInfectionType_ = InfectionTypeFromString( firstInfection );
  InfectionType secondInfectionType_ = InfectionTypeFromString( secondInfection );

  SequenceOfInfection_.first = firstInfectionType_;
  SequenceOfInfection_.second = secondInfectionType_;
}
  


SequentialInfection::InfectionType
SequentialInfection::InfectionTypeFromString( std::string ssInfectionType )
{
  if( ssInfectionType == "1" ) {
    return One;
  }
  else if( ssInfectionType == "2" ) {
    return Two;
  }
  else if( ssInfectionType == "3" ) {
    return Three;
  }
  else if( ssInfectionType == "4" ) {
    return Four;
  }
  else if( ssInfectionType == "MAEA" ) {
    return MAEA;
  }
  else {
    throw;
  }
}



SequentialInfections::SequentialInfections( SequentialInfectionCollection seqInfColl )
{
  this->SequentialInfectionCollection_ = seqInfColl;
}



SequentialInfections::SequentialInfections( SequentialInfection * f1t2, SequentialInfection * f1t3, SequentialInfection * f1t4, 
                                            SequentialInfection * f2t1, SequentialInfection * f2t3, SequentialInfection * f2t4,
                                            SequentialInfection * f3t1, SequentialInfection * f3t2, SequentialInfection * f3t4,
                                            SequentialInfection * f4t1, SequentialInfection * f4t2, SequentialInfection * f4t3,
                                            SequentialInfection * fMt1, SequentialInfection * fMt2, SequentialInfection * fMt3, SequentialInfection * fMt4 )
{
  SequentialInfectionCollection_.push_back( f1t2 );
  SequentialInfectionCollection_.push_back( f1t3 );
  SequentialInfectionCollection_.push_back( f1t4 );
  SequentialInfectionCollection_.push_back( f2t1 );
  SequentialInfectionCollection_.push_back( f2t3 );
  SequentialInfectionCollection_.push_back( f2t4 );
  SequentialInfectionCollection_.push_back( f3t1 );
  SequentialInfectionCollection_.push_back( f3t2 );
  SequentialInfectionCollection_.push_back( f3t4 );
  SequentialInfectionCollection_.push_back( f4t1 );
  SequentialInfectionCollection_.push_back( f4t2 );
  SequentialInfectionCollection_.push_back( f4t3 );
  SequentialInfectionCollection_.push_back( fMt1 );
  SequentialInfectionCollection_.push_back( fMt2 );
  SequentialInfectionCollection_.push_back( fMt3 );
  SequentialInfectionCollection_.push_back( fMt4 );
}



SequentialInfections::~SequentialInfections(void)
{}



SequentialInfection *
SequentialInfections::GetSequentialInfection( SequentialInfection::InfectionType firstInfectionType,
                                              SequentialInfection::InfectionType secondInfectionType )
{
  SequentialInfectionCollection::iterator itSi;

  itSi = std::find_if( SequentialInfectionCollection_.begin(),
                       SequentialInfectionCollection_.end(),
                       FindSequenceOfInfection(firstInfectionType, secondInfectionType) );

  if( itSi != SequentialInfectionCollection_.end() ) {
    return *itSi;
  }
  else {
    return NULL;
  }
}



SequentialInfection *
SequentialInfections::GetSequentialInfection( std::string firstInfection, std::string secondInfection )
{
  return GetSequentialInfection( SequentialInfection::InfectionTypeFromString(firstInfection),
                                  SequentialInfection::InfectionTypeFromString(secondInfection) );
}
