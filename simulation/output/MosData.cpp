#include "StdAfx.h"
#include "MosData.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

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



void
MosData::WriteMstFiles(void)
{
  // this method provides the .MST files that are expected by
  // converter utilities written in PDS 7.1.  This allows us to move
  // data from cimsim 3.0 into densim 1.0 and 2.0
  date_period dp = GetMosDataPeriod();

  int firstYear = dp.begin().year();
  int lastYear = dp.end().year();

  for( int i = firstYear; i <= lastYear; ++i ) {
    std::stringstream ss;
    ss << i;
    std::string fourDigitYear = ss.str();
    std::string twoDigitYear = fourDigitYear.substr(2,2);

    std::string filename = "iquito" + twoDigitYear + ".mst";

    std::ofstream mstFile;
    mstFile.open( filename.c_str() );

    YearlyMosData yearMosData = _yearlyMosData[i];

    day_iterator itDay = day_iterator( date(i,1,1) );
    date feb28th = date(i,2,28);
    date endOfYear = date(i,12,31);

    // output from jan 1st to feb 28th
    for( itDay = day_iterator(date(i,1,1)); itDay <= feb28th; ++itDay ) {
      date d = *itDay;
      DailyMosData & dmd = yearMosData.GetDailyMosData(d);

      mstFile << " " << dmd.NewFemales << " , " << dmd.AverageWeight << " , "
              << dmd.OverallSurvival << " , " << dmd.AdultDevelopment << " " << std::endl;
    }

    // continue output from mar 1st to end of year
    for( itDay = day_iterator(date(i,3,1)); itDay <= endOfYear; ++itDay ) {
      date d = *itDay;
      DailyMosData & dmd = yearMosData.GetDailyMosData(d);

      mstFile << " " << dmd.NewFemales << " , " << dmd.AverageWeight << " , "
              << dmd.OverallSurvival << " , " << dmd.AdultDevelopment << " " << std::endl;
    }

    mstFile.close();
  }
}



void
MosData::WriteMosFiles(void)
{
  // dump in csv format
  date_period dp = GetMosDataPeriod();

  int firstYear = dp.begin().year();
  int lastYear = dp.end().year();

  for( int i = firstYear; i <= lastYear; ++i ) {
    std::stringstream ss;
    ss << i;
    std::string fourDigitYear = ss.str();

    std::string filename = fourDigitYear + ".mos";

    std::ofstream mosFile;
    mosFile.open( filename.c_str() );

    YearlyMosData yearMosData = _yearlyMosData[i];

    day_iterator itDay = day_iterator( date(i,1,1) );
    date endOfYear = date(i,12,31);

    // output from jan 1st to feb 28th
    for( itDay = day_iterator(date(i,1,1)); itDay <= endOfYear; ++itDay ) {
      date d = *itDay;
      DailyMosData & dmd = yearMosData.GetDailyMosData(d);

      mosFile << " " << dmd.NewFemales << " , " << dmd.AverageWeight << " , "
              << dmd.OverallSurvival << " , " << dmd.AdultDevelopment << " , "
              << dmd.NewFemaleWeight << dmd.AgeIndependentSurvival << " "
              << std::endl;
    }

    mosFile.close();
  }


}



date_period
MosData::GetMosDataPeriod(void)
{
  int firstYear = _yearlyMosData.begin()->first;
  int lastYear = (--(_yearlyMosData.end()))->first;

  date firstDate = date( firstYear, 1, 1 );
  date lastDate = date( lastYear, 12, 31 );

  return date_period(firstDate, lastDate);
}



DailyMosData&
MosData::GetMosData( date d )
{
  return _yearlyMosData[d.year()].GetDailyMosData(d);
}

  
YearlyMosData&
MosData::GetYearlyMosData( int year )
{
  return _yearlyMosData[year];
}



void
MosData::AddYearlyMosData( int year, YearlyMosData yearlyMosData )
{
  _yearlyMosData[year] = yearlyMosData;
}

