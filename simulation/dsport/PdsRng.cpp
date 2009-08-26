#include "StdAfx.h"
#include "PdsRng.h"




PdsRng::PdsRng(void)
: _x0(_defaultSeed)
{}



PdsRng::PdsRng( int seed )
: _x0(seed)
{}



PdsRng::~PdsRng(void)
{}



float
PdsRng::Next(void)
{
  _x1 = (_x0 * _a + _c) & _mask;
  _x0 = _x1;

  return static_cast<float>(_x1) / _mask;
}