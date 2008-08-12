#include "StdAfx.h"
#include "Graphs.h"

using namespace gui::output;



Graph::Graph(void)
: _primaryOutputs(gcnew Collections::Generic::List<Output^>()),
  _secondaryOutputs(gcnew Collections::Generic::List<Output^>())
{}



Graph::~Graph(void)
{}
