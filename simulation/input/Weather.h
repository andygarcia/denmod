// ============================================================================ //
// Weather.h                                                                    //
//                                                                              //
// All indicies for years and day have a one-to-one correspondence with the     // 
// calendar, so these classes in effect use one's indexing.                     //
// ============================================================================ //
#ifndef WEATHER_H
#define WEATHER_H

#include <map>
#include <vector>
#include "Control.h"



namespace input {


class WeatherDay
{
public:
  int Index_;
  double MaxTemp_;
  double MinTemp_;
  double AvgTemp_;
  double SatDef_;
  double Precip_;
  double RelHum_;
};



class WeatherYear
{
public:
  typedef std::map<int, WeatherDay*> WeatherDayCollection;

public:
  WeatherYear(void);
  virtual ~WeatherYear(void);

  void AddDay( WeatherDay * wd );
  WeatherDay * GetDay( int day );
  int GetNumberOfDays(void);

public:
  int Index_;
  std::string City_;
  std::string Province_;
  std::string Country_;
  std::string Latitude_;
  std::string Longitude_;
  std::string Elevation_;
  std::string Source_;

private:
  WeatherDayCollection Days_;
};



class Weather
{
public:
  typedef std::map<int, WeatherYear*> WeatherYearCollection;

public:
  Weather(void);
  virtual ~Weather(void);

  void AddYear( WeatherYear * wy );
  boost::gregorian::date_period GetWeatherPeriod(void);
  WeatherYear * GetWeatherForYear( int year );
  WeatherYear * GetWeatherForIndex( int index );

private:
  WeatherYearCollection Years_;
};

};

#endif
