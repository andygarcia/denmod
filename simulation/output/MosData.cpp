#include "StdAfx.h"
#include "MosData.h"
#include <algorithm>
#include <string>

using namespace boost::gregorian;
using namespace sim::output;



YearlyMosData::YearlyMosData(void)
{}



YearlyMosData::~YearlyMosData(void)
{}



DailyMosData &
YearlyMosData::GetDailyMosData( date d )
{
  return YearlyMosData_[d];
}



void
YearlyMosData::AddDailyMosData( date d, DailyMosData dailyMosData )
{
  YearlyMosData_[d] = dailyMosData;
}



MosData::MosData(void)
{}



MosData::~MosData(void)
{}



date_period
MosData::GetMosDataPeriod(void)
{
  int firstYear = YearlyMosDataCollection_.begin()->first;
  int lastYear = (--(YearlyMosDataCollection_.end()))->first;

  date firstDate = date( firstYear, 1, 1 );
  date lastDate = date( lastYear, 12, 31 );

  return date_period(firstDate, lastDate);
}



DailyMosData&
MosData::GetMosData( date d )
{
  return YearlyMosDataCollection_[d.year()].GetDailyMosData(d);
}

  
YearlyMosData&
MosData::GetYearlyMosData( int year )
{
  return YearlyMosDataCollection_[year];
}



void
MosData::AddYearlyMosData( int year, YearlyMosData yearlyMosData )
{
  YearlyMosDataCollection_[year] = yearlyMosData;
}

