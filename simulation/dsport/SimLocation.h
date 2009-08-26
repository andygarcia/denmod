#ifndef DS_SIMLOCATION_H
#define DS_SIMLOCATION_H

#include <string>
#include <vector>
#include "SimClasses.h"
#include "../input/Location.h"
#include "../input/Control.h"
#include "../output/DensimOutput.h"
#include "../output/MosData.h"
#include "../output/PopData.h"



namespace sim {
namespace dsport {

class SimLocation
{
// Constructors
public:
  SimLocation( const input::Location * location, output::MosData * mosData );
  ~SimLocation(void);

// Methods
public:
  void Start(void);
  void Start( boost::gregorian::date startDate, boost::gregorian::date stopDate );

  output::DensimOutput * GetSimOutput(void);

private:

};

};
};

#endif
