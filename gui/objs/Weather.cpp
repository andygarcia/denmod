#include "StdAfx.h"
#include "Weather.h"
#include "Util.h"

using namespace gui;
using namespace System;


WeatherDay::WeatherDay(void)
{}



WeatherDay::~WeatherDay(void)
{}



void
WeatherDay::CalculateSaturationDeficit( VaporPressureMethod method )
{
  // first find vapor pressure at saturation using specified method
  double saturatedVaporPressure;
  if( method == VaporPressureMethod::GoffGrach ) {
    saturatedVaporPressure = GoffGrach( AvgTemp_ );
  }
  else if( method == VaporPressureMethod::MagnusTeten ) {
    saturatedVaporPressure = MagnusTeten( AvgTemp_ );
  }
  else {
    throw gcnew ArgumentException( "invalid vapor pressure calculation method.", "method" );
  }

  // use relative humidity to calculate current vapor pressure
  double currentVaporPressure = (RelHum_/100.0) * saturatedVaporPressure;

  // and now set the difference, the deficit, or drying power of air
  SatDef_ = saturatedVaporPressure - currentVaporPressure;
}



input::WeatherDay *
WeatherDay::GetSimObject(void)
{
  input::WeatherDay * wd = new input::WeatherDay();

  wd->Index_ = this->Index_;
  wd->MaxTemp_ = this->MaxTemp_;
  wd->MinTemp_ = this->MinTemp_;
  wd->AvgTemp_ = this->AvgTemp_;
  wd->SatDef_ = this->SatDef_;
  wd->Precip_ = this->Rain_;
  wd->RelHum_ = this->RelHum_;

  return wd;
}



double
WeatherDay::GoffGrach( double temperatureCelsius )
{
  double t = temperatureCelsius + 273.16;
  double term1 = -7.90298 * ((373.16/t)-1);
  double term2 = 5.02808 * log10(373.16/t);
  double term3 = -1.3816 * pow(10.0,-7) * (pow(10,11.344 * (1-t/373.16)) - 1);
  double term4 = 8.1328 * pow(10.0,-3) * (pow(10,-3.49149*(373.16/t-1)) - 1);
  double term5 = log10(1013.246);
  double loges = term1 + term2 + term3 + term4 + term5;
  double es = pow(10, loges);

  return es;
}



double
WeatherDay::MagnusTeten( double temperatureCelsius )
{
  double t = temperatureCelsius + 273.16;
  double es = 6.1078 * exp( 17.2693882 * (t-273.16) / (t-35.86) );
  return es;
}



WeatherYear::WeatherYear(void)
: Days_(gcnew BindingList<WeatherDay^>())
{}



WeatherYear::~WeatherYear(void)
{}



input::WeatherYear *
WeatherYear::GetSimObject(void)
{
  input::WeatherYear * wy = new input::WeatherYear();

  wy->Index_ = this->Index_;
  wy->City_ = toss(this->City_);
  wy->Province_ = toss(this->Province_);
  wy->Country_ = toss(this->Country_);
  wy->Latitude_ = toss(this->Latitude_);
  wy->Longitude_ = toss(this->Longitude_);
  wy->Elevation_ = toss(this->Elevation_);
  wy->Source_ = toss(this->Source_);

  for each( WeatherDay ^ wd in this->Days_ ) {
    wy->AddDay( wd->GetSimObject() );
  }

  return wy;
}



void
WeatherYear::WriteXml( XmlWriter ^ xw )
{
  XmlSerializer ^ xs = gcnew XmlSerializer( gui::WeatherDay::typeid );

  xw->WriteAttributeString( "index", Convert::ToString(Index_) );
  xw->WriteAttributeString( "city", City_ );
  xw->WriteAttributeString( "province", Province_ );
  xw->WriteAttributeString( "country", Country_ );
  xw->WriteAttributeString( "latitude", Latitude_ );
  xw->WriteAttributeString( "longitude", Longitude_ );
  xw->WriteAttributeString( "elevation", Elevation_ );
  xw->WriteAttributeString( "source", Source_ );

  for each( WeatherDay ^ wd in Days_ ) {
    xs->Serialize( xw, wd );
  }
}



void
WeatherYear::ReadXml( XmlReader ^ xr )
{
  XmlSerializer ^ xs = gcnew XmlSerializer( gui::WeatherDay::typeid );

  if( xr->HasAttributes ) {
    int numAttributes = xr->AttributeCount;
    this->Index_ = Convert::ToInt32( xr->GetAttribute("index") );
    this->City_ = xr->GetAttribute("city");
    this->Province_ = xr->GetAttribute("province");
    this->Country_ = xr->GetAttribute("country");
    this->Latitude_ = xr->GetAttribute("latitude");
    this->Longitude_ = xr->GetAttribute("longitude");
    this->Elevation_ = xr->GetAttribute("elevation");
    this->Source_ = xr->GetAttribute("source");
  }

  xr->ReadToDescendant("Day");

  while( xr->NodeType != XmlNodeType::EndElement ) {
    WeatherDay ^ wd = (WeatherDay^) xs->Deserialize(xr);
    this->Days_->Add( wd );
  }

  xr->ReadEndElement();
}



XmlSchema ^
WeatherYear::GetSchema(void)
{
  return nullptr;
}



String ^
WeatherYear::Source::get(void)
{
  return Source_;
}



void
WeatherYear::Source::set(String ^ i)
{
  Source_ = i;
  NotifyPropertyChanged( "Source" );
}



String ^
WeatherYear::Elevation::get(void)
{
  return Elevation_;
}



void
WeatherYear::Elevation::set(String ^ i)
{
  Elevation_ = i;
  NotifyPropertyChanged( "Elevation" );
}



String ^
WeatherYear::Longitude::get(void)
{
  return Longitude_;
}



void WeatherYear::Longitude::set(String ^ i)
{
  Longitude_ = i;
  NotifyPropertyChanged( "Longitude" );
}



String ^
WeatherYear::Latitude::get(void)
{
  return Latitude_;
}



void
WeatherYear::Latitude::set(String ^ i)
{
  Latitude_ = i;
  NotifyPropertyChanged( "Latitude" );
}



String ^
WeatherYear::Country::get(void)
{
  return Country_;
}



void
WeatherYear::Country::set(String ^ i)
{
  Country_ = i;
  NotifyPropertyChanged( "Country" );
}



String ^
WeatherYear::Province::get(void)
{
  return Province_;
}



void
WeatherYear::Province::set(String ^ i)
{
  Province_ = i;
  NotifyPropertyChanged( "Province" );
}



String ^
WeatherYear::City::get(void)
{
  return City_;
}



void
WeatherYear::City::set(String ^ i)
{
  City_ = i;
  NotifyPropertyChanged( "City" );
}



int
WeatherYear::Index::get(void)
{
  return Index_;
}



void
WeatherYear::Index::set(int i)
{
  if( i != Index_ ) {
    Index_ = i;
    NotifyAndValidate( "Index" );
  }
}



BindingList<WeatherDay^> ^
WeatherYear::Days::get(void)
{
  return Days_;
}



void
WeatherYear::Days::set( BindingList<WeatherDay^>^ bl )
{
  if( bl != Days_ ) {
    Days_ = bl;
    NotifyPropertyChanged( "Days" );
  }
}



DateTime
WeatherYear::MinDate::get(void)
{
  if( Days_->Count == 0 ) {
    return DateTime::MinValue;
  }
  else {
    DateTime dtJanFirst( Index_, 1, 1 );
    return dtJanFirst.AddDays( Days_[0]->Index - 1 );
  }
}



DateTime
WeatherYear::MaxDate::get(void)
{
  if( Days_->Count == 0 ) {
    return DateTime::MaxValue;
  }
  else {
    DateTime dtJanFirst( Index_, 1, 1 );
    return dtJanFirst.AddDays( Days_->Count - 1 );
  }
}



WeatherData::WeatherData(void)
: Years_(gcnew Generic::Dictionary<int,WeatherYear^>())
{}



WeatherData::~WeatherData(void)
{}


  
input::Weather *
WeatherData::GetSimObject(void)
{
  input::Weather * w = new input::Weather();

  for each( WeatherYear ^ wy in Years_->Values ) {
    w->AddYear( wy->GetSimObject() );
  }

  return w;
}



bool WeatherData::IsWeatherYearAvailable( int year )
{
  return Years->ContainsKey( year );
}



void
WeatherData::AddWeatherYear( WeatherYear ^ wy )
{
  Years_->Add( wy->Index, wy );
  NotifyPropertyChanged( "Years" );
  NotifyPropertyChanged( "YearsBindingList" );
  NotifyPropertyChanged( "MinDate" );
  NotifyPropertyChanged( "MaxDate" );
}



void
WeatherData::RemoveWeatherYear( int year )
{
  Years_->Remove(year);
  NotifyPropertyChanged( "Years" );
  NotifyPropertyChanged( "YearsBindingList" );
  NotifyPropertyChanged( "MinDate" );
  NotifyPropertyChanged( "MaxDate" );
}



bool
WeatherData::IsWeatherDataContiguous(void)
{
  int firstYear = this->MinDate.Year;
  int lastYear = this->MaxDate.Year;

  for( int i = firstYear + 1; i < lastYear; ++i ) {
    if( Years_->ContainsKey( i ) == false ) {
      return false;
    }
  }

  return true;
}



Generic::List<int> ^
WeatherData::GetMissingWeatherYears(void)
{
  Generic::List<int> ^ missingYears = gcnew Generic::List<int>( Years_->Count );

  int firstYear = this->MinDate.Year;
  int lastYear = this->MaxDate.Year;

  for( int i = firstYear + 1; i < lastYear; ++i ) {
    if( Years_->ContainsKey( i ) == false ) {
      missingYears->Add( i );
    }
  }

  return missingYears;
}



WeatherDay ^
WeatherData::GetWeather( DateTime dt )
{
  WeatherYear ^ wy = Years_[dt.Year];
  WeatherDay ^ wd = wy->Days[dt.DayOfYear-1];

  return wd;
}



void
WeatherData::WriteXml( XmlWriter ^ xw )
{
  XmlSerializer ^ yearSerializer = gcnew XmlSerializer( gui::WeatherYear::typeid );

  for each( WeatherYear ^ wy in Years_->Values ) {
    yearSerializer->Serialize( xw, wy );
  }
}



void
WeatherData::ReadXml( XmlReader ^ xr )
{
  // use default serialization for years/days
  XmlSerializer ^ yearSerializer = gcnew XmlSerializer( gui::WeatherYear::typeid );

  // possible to have dml file with no weather, <Weather />
  if( xr->IsEmptyElement ) {
    xr->Read();
    return;
  }

  // move from <Weather> to first <Year> and read successive years
  xr->ReadToDescendant("Year");
  while( xr->NodeType != XmlNodeType::EndElement ) {
    WeatherYear ^ wy = (WeatherYear^) yearSerializer->Deserialize(xr);
    this->Years_->Add( wy->Index, wy );
  }

  // move to </WeatherYear>
  xr->ReadEndElement();
}



WeatherYear ^ WeatherYear::OpenFromXls( String ^ filename )
{
  using namespace Data;
  using namespace System::Data::OleDb;

  // imported weather data
  DataTable ^ weatherData = gcnew DataTable();

  // try to get connection to file
  OleDbConnection ^ odc = nullptr;
  try {
    odc = WeatherYear::TryExcelConnection( filename );
    OleDbDataAdapter ^ odda = gcnew OleDbDataAdapter("SELECT * FROM [Weather$]", odc);
    odda->Fill( weatherData );
  }
  finally {
    odc->Close();
  }

  int numDays = weatherData->Rows->Count;
  array<double> ^ minTemps = gcnew array<double>(numDays);
  array<double> ^ avgTemps = gcnew array<double>(numDays);
  array<double> ^ maxTemps = gcnew array<double>(numDays);
  array<double> ^ rain = gcnew array<double>(numDays);
  array<double> ^ relHum = gcnew array<double>(numDays);

  gui::WeatherYear ^ wy = gcnew gui::WeatherYear();
  int lastGoodRow = 0;

  try {
    for( int i = 0; i < numDays; ++i ) {
      DataRow ^ curRow = weatherData->Rows[i];
      int dayIndex = Convert::ToInt32(curRow[0]);
      minTemps[i] = Convert::ToDouble(curRow[1]);
      avgTemps[i] = Convert::ToDouble(curRow[2]);
      maxTemps[i] = Convert::ToDouble(curRow[3]);
      rain[i] = Convert::ToDouble(curRow[4]);
      relHum[i] = Convert::ToDouble(curRow[5]);
      lastGoodRow = i;

      gui::WeatherDay ^ wd = gcnew gui::WeatherDay();
      wd->Index = dayIndex;
      wd->MinTemp = minTemps[i];
      wd->AvgTemp = avgTemps[i];
      wd->MaxTemp = maxTemps[i];
      wd->Rain = rain[i];
      wd->RelHum = relHum[i];
      wd->CalculateSaturationDeficit( gui::WeatherDay::VaporPressureMethod::MagnusTeten );

      wy->Days->Add( wd );
    }
  }
  catch( Exception ^ e ) {
    throw gcnew ExcelWeatherDataException( lastGoodRow, e );
  }

  wy->ImportSource_ = ImportSourceEnum::Excel;
  return wy;
}



WeatherYear ^ WeatherYear::OpenFromDly( String ^ filename )
{
  // read input from stream, using tokenization, and create weather year
  System::IO::StreamReader ^ sr = gcnew System::IO::StreamReader( filename );
  String ^ s;
  array<String^> ^ toks;
  WeatherYear ^ wy = gcnew WeatherYear();

  // year, city, province, and country
  s = sr->ReadLine();
  toks = s->Split(',');
  wy->Index = Convert::ToInt32(toks[0]->Trim('"'));
  wy->City = toks[1]->Trim('"');
  wy->Province = toks[2]->Trim('"');
  wy->Country = toks[3]->Trim('"');

  // lat, long, elevation
  s = sr->ReadLine();
  toks = s->Split(',');
  wy->Latitude = toks[0]->Trim('"');
  wy->Longitude = toks[1]->Trim('"');
  wy->Elevation = toks[2]->Trim('"');

  // source
  s = sr->ReadLine();
  toks = s->Split(',');
  wy->Source = toks[0]->Trim('"');

  // discard data headers and parse each day's weather data
  sr->ReadLine();
  System::Collections::Generic::List<WeatherDay^> ^ days = gcnew System::Collections::Generic::List<WeatherDay^>(366);
  while( !sr->EndOfStream ) {
    System::Text::RegularExpressions::Regex ^ r = gcnew System::Text::RegularExpressions::Regex( "\\d+\\.?\\d*" );
    System::Text::RegularExpressions::MatchCollection ^ mc = r->Matches( sr->ReadLine() );

    gui::WeatherDay ^ wd = gcnew gui::WeatherDay();
    wd->Index = Convert::ToInt32(mc[0]->Value);
    wd->MaxTemp = Convert::ToDouble(mc[1]->Value);
    wd->MinTemp = Convert::ToDouble(mc[2]->Value);
    wd->AvgTemp = Convert::ToDouble(mc[3]->Value);
    wd->SatDef = Convert::ToDouble(mc[4]->Value);
    wd->Rain = Convert::ToDouble(mc[5]->Value);
    wd->RelHum = Convert::ToDouble(mc[6]->Value);

    days->Add( wd );
  }

  // correct for possible leap year
  if( DateTime::IsLeapYear(wy->Index) ) {
    if( days->Count == 365 ) {
      // copy feb 28th to feb 29th, in zero index, copy 58 to 59
      gui::WeatherDay ^ feb28th = (WeatherDay ^) days[58];
      gui::WeatherDay ^ feb29th = gcnew WeatherDay();

      feb29th->Index = feb28th->Index + 1;
      feb29th->MaxTemp = feb28th->MaxTemp;
      feb29th->MinTemp = feb28th->MinTemp;
      feb29th->AvgTemp = feb28th->AvgTemp;
      feb29th->SatDef = feb28th->SatDef;
      feb29th->Rain = feb28th->Rain;
      feb29th->RelHum = feb28th->RelHum;

      days->Insert( 59, feb29th );

      // adjust indices by for remainder of year
      for( int i = 60; i <= 365; i++ ) {
        days[i]->Index++;
      }
    }
  }

  for each( WeatherDay ^ wd in days ) {
    wy->Days->Add( wd ); 
  }

  wy->ImportSource_ = ImportSourceEnum::Dly;
  return wy;
}



Data::OleDb::OleDbConnection ^
WeatherYear::TryExcelConnection( String ^ filename )
{
  using namespace Data::OleDb;

  // try opening excel file, accounting for different versions
  // first make a guess based on extension
  IO::FileInfo ^ fi = gcnew IO::FileInfo( filename );

  // build connection string to excel file
  OleDbConnectionStringBuilder ^ odcs = gcnew OleDbConnectionStringBuilder();
  odcs->DataSource = filename;

  // try 97-2003
  odcs->Provider = "Microsoft.Jet.OLEDB.4.0";
  odcs->Add( "Extended Properties", "Excel 8.0;HDR=Yes;IMEX=1" );
  OleDbConnection ^ odc = nullptr;
  try {
    odc = gcnew OleDbConnection( odcs->ConnectionString );
    odc->Open();
    return odc;
  }
  catch( Exception ^ e ) {
    Diagnostics::Debug::WriteLine( "WeatherYear::TryOpenExcelFile(): " + e->Message );
    odc->Close();
    odcs->Provider = "";
    odcs->Remove( "Extended Properties" );
  }

  // try 2007
  odcs->Provider = "Microsoft.ACE.OLEDB.12.0";
  odcs->Add( "Extended Properties", "Excel 12.0;HDR=Yes;" );
  try {
    odc = gcnew OleDbConnection( odcs->ConnectionString );
    odc->Open();
    return odc;
  }
  catch( Exception ^ e ) {
    Diagnostics::Debug::WriteLine( "WeatherYear::TryOpenExcelFile(): " + e->Message );
    odc->Close();
    odcs->Provider = "";
    odcs->Remove( "Extended Properties" );
  }

  // no attempt succeeded
  throw gcnew Exception( "Unrecognized Excel file format" );
}



XmlSchema ^
WeatherData::GetSchema(void)
{
  return nullptr;
}



Generic::Dictionary<int,WeatherYear^> ^
WeatherData::Years::get(void)
{
  return Years_;
}



void
WeatherData::Years::set( Generic::Dictionary<int,WeatherYear^> ^ d )
{
  Years_ = d;
  NotifyPropertyChanged( "Years" );
  NotifyPropertyChanged( "YearsBindingList" );
  NotifyPropertyChanged( "MinDate" );
  NotifyPropertyChanged( "MaxDate" );
}



BindingList<WeatherYear^> ^
WeatherData::YearsBindingList::get(void)
{
  BindingList<WeatherYear^> ^ bl = gcnew BindingList<WeatherYear^>();
  for each( WeatherYear ^ wy in Years_->Values ) {
    bl->Add( wy );
  }

  return bl;
}



DateTime WeatherData::MinDate::get(void)
{
  if( Years_->Count == 0 ) {
    return DateTime::MinValue;
  }
  else {
    DateTime minDate = DateTime::MaxValue;

    for each( WeatherYear ^ wy in Years->Values ) {
      if( wy->MinDate < minDate ) {
        minDate = wy->MinDate;
      }
    }
    return minDate;
  }
}



DateTime WeatherData::MaxDate::get(void)
{
  if( Years_->Count == 0 ) {
    return DateTime::MaxValue;
  }
  else {
    DateTime maxDate = DateTime::MinValue;

    for each( WeatherYear ^ wy in Years->Values ) {
      if( wy->MaxDate > maxDate ) {
        maxDate = wy->MaxDate;
      }
    }
    return maxDate;
  }
}



int
WeatherData::NumberOfYears::get(void)
{
  return Years_->Count;
}
