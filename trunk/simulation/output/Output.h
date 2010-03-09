#ifndef OUTPUT_OUTPUT_H
#define OUTPUT_OUTPUT_H

#include <vector>
#include <boost/date_time/gregorian/gregorian.hpp>


namespace sim {
namespace output {


template<typename T>
class Output
{
public:
  Output(void)
  {
    throw "Not supported. sim::output::Output must be constructed using a date range";
  }

  Output( boost::gregorian::date startDate, boost::gregorian::date stopDate )
  : _data((startDate-stopDate).days() + 1 ),
    _startDate(startDate),
    _stopDate(stopDate)
  {}

  virtual ~Output(void)
  {}

public:

  void PushData( T dataValue )
  {
    _data.push_back(dataValue);
  }

  T & GetDate( boost::gregorian::date d )
  {
    return _data[GetIndexFromDate(d)];
  }

  std::vector<T> GetDateRange(boost::gregorian::date rangeStartDate, boost::gregorian::date rangeStopDate )
  {
    int startIndex = GetIndexFromDate( rangeStartDate );
    int stopIndex = GetIndexFromDate( rangeStopDate );

    std::vector<T> rangeData = std::vector<T>( _data.begin() + startIndex, _data.begin() + stopIndex );

    return rangeData;
  }


  std::vector<T> & GetAllDates(void)
  {
    return _data;
  }

private:
  int GetIndexFromDate( boost::gregorian::date d )
  {
    return (d - _startDate).days();
  }

private:
  boost::gregorian::date _startDate;
  boost::gregorian::date _stopDate;
  std::vector<T> _data;
};

};
};

#endif
