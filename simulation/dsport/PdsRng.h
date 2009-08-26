#ifndef PDSRNG_H
#define PDSRNG_H

class PdsRng
{
public:
  PdsRng();
  PdsRng(int seed);
  ~PdsRng(void);

public:
  float Next();

private:
  unsigned long _x0;
  unsigned long _x1;

  static const unsigned long _defaultSeed = 327680;  // 0x50000L;
  static const unsigned long _a = 1140671485;         // 0x43fd43fdL
  static const unsigned long _c = 12820163;           // 0xc39ec3L
  static const long _mask = 0xffffffL;                // 0xffffffL
};

#endif
