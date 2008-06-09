#include "stdafx.h"
#include "Weather.h"
#include <algorithm>

using namespace boost::gregorian;
using namespace input;



Weather::Weather(void)
{}



Weather::~Weather(void)
{
  WeatherYearCollection::iterator itWy;
  for( itWy = Years_.begin(); itWy != Years_.end(); ++itWy ) {
    delete itWy->second;
  }
}



void
Weather::AddYear( WeatherYear * wy )
{
  Years_[wy->Index_] = wy;
}



WeatherYear *
Weather::GetWeatherForYear( int year )
{
  return Years_[year];
}



WeatherYear *
Weather::GetWeatherForIndex( int index )
{
  std::map<int, WeatherYear*>::iterator itYear = Years_.begin();
  int i;
  for( i = 1; i < index; ++i ) {
    itYear++;
  }
  return itYear->second;
}



boost::gregorian::date_period
Weather::GetWeatherPeriod(void)
{
  int firstYear = Years_.begin()->first;
  int lastYear = (--(Years_.end()))->first;

  date firstDate = date( firstYear, 1, 1 );
  date lastDate = date( lastYear, 12, 31 );

  return date_period(firstDate, lastDate);
}



WeatherYear::WeatherYear(void)
{}



WeatherYear::~WeatherYear(void)
{
  WeatherDayCollection::iterator itWd;
  for( itWd = Days_.begin(); itWd != Days_.end(); ++itWd ) {
    delete itWd->second;
  }  
}



void
WeatherYear::AddDay( WeatherDay * wd )
{
  Days_[wd->Index_] = wd;
}


int
WeatherYear::GetNumberOfDays(void)
{
  return (int) Days_.size();
}



WeatherDay *
WeatherYear::GetDay( int day )
{
  return Days_[day];
}
