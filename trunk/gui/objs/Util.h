#pragma once

#include <string>

#pragma managed(push,off)
#include <boost/date_time/gregorian/gregorian.hpp>
#pragma managed(pop)

using namespace System::Runtime::InteropServices;



namespace gui {

  static std::string toss( System::String ^ s )
  {
    // convert .NET System::String to std::string
    const char* cstr = (const char*) (Marshal::StringToHGlobalAnsi(s)).ToPointer();
    std::string sstr = cstr;
    Marshal::FreeHGlobal(System::IntPtr((void*)cstr));
    return sstr;
  }

  static System::DateTime ToDateTime( boost::gregorian::date d )
  {
    // convert boost date to .net date
    return System::DateTime( d.year(), d.month(), d.day() );
  }

  static boost::gregorian::date ToBoostDate( System::DateTime dt )
  {
    // convert .net date to boost date
    return boost::gregorian::date( dt.Year, dt.Month, dt.Day );
  }

}
