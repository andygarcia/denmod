#include "stdafx.h"
#include "Output.h"
#include "OutputTypes.h"
#include <cmath>

using namespace gui::output;



OutputInfo::OutputInfo( int id, gui::output::OutputInfoAttribute ^ OutputInfoAttribute )
: _id(id),
  _outputInfoAttribute( OutputInfoAttribute )
{}



OutputInfo::~OutputInfo(void)
{}



Output ^
OutputInfo::CreateNewOutput(void)
{
  Output ^ newOutput = gcnew Output(this);
  return newOutput;
}



static
OutputCollections::OutputCollections(void)
{
  _cimsimLocation = GetOutputInfoCollection( OutputTypes::Cimsim::Location::typeid );
  _cimsimContainer = GetOutputInfoCollection( OutputTypes::Cimsim::Container::typeid );
  _densimLocation = GetOutputInfoCollection( OutputTypes::Densim::Location::typeid );
  _densimSerotype = GetOutputInfoCollection( OutputTypes::Densim::Serotype::typeid );
}



OutputInfoCollection ^
OutputCollections::GetOutputInfoCollection( System::Type ^ type )
{
  // generate a collection of OutputInfo object for this type by using
  // reflection to access OutputInfoAttribute on members
  OutputInfoCollection ^ Output = gcnew OutputInfoCollection();

  array<Reflection::FieldInfo^> ^ fields = type->GetFields( Reflection::BindingFlags::Static | Reflection::BindingFlags::GetField | Reflection::BindingFlags::Public );
  for each( Reflection::FieldInfo ^ fi in fields ) {
    OutputInfoAttribute ^ sia = GetOutputInfoAttribute( fi );
    int id = Convert::ToInt32( fi->GetValue(nullptr) );
    OutputInfo ^ si = gcnew OutputInfo( id, sia );
    Output->Add( id, si );
  }

  return Output;
}



OutputInfoAttribute ^
OutputCollections::GetOutputInfoAttribute( Reflection::FieldInfo ^ fi )
{
  // find a OutputInfoAttribute on this member
  array<Object^> ^ OutputInfoAttributes = fi->GetCustomAttributes( OutputInfoAttribute::typeid, false );
  if( OutputInfoAttributes->Length > 0 ) {
    OutputInfoAttribute ^ sia = (OutputInfoAttribute^) OutputInfoAttributes[0];
    return sia;
  }
  else {
    // should only be called on enum types
    throw gcnew Exception( "No OutputInfoAttribute was found on " + fi->Name );
  }
}



IndexedOutputCollection ^
OutputCollections::CreateNewOutputCollection( System::Type ^ outputType )
{
  OutputInfoCollection ^ sic = nullptr;

  // find which collection of OutputInfo to use to create new Output collection
  if( outputType == OutputTypes::Cimsim::Location::typeid ) {
    sic = _cimsimLocation;
  }
  else if( outputType == OutputTypes::Cimsim::Container::typeid ) {
    sic = _cimsimContainer;
  }
  else if( outputType == OutputTypes::Densim::Location::typeid ) {
    sic = _densimLocation;
  }
  else if( outputType == OutputTypes::Densim::Serotype::typeid ) {
    sic = _densimSerotype;
  }
  else {
    // invalid type argument
    throw gcnew System::ArgumentException( "GetOutputCollection(), invalid outputType" );
  }

  IndexedOutputCollection ^ outputs = gcnew IndexedOutputCollection();
  for each( OutputInfo ^ oi in sic->Values ) {
    Output ^ o = oi->CreateNewOutput();
    outputs->Add( oi->Id, o );
  }
  return outputs;
}



Collections::Generic::List<double> ^ 
Output::GetWeeklyData( TimePeriodFunction function )
{
  Collections::Generic::List<double> ^ weeklyData = gcnew Collections::Generic::List<double>();

  int numDays = _data->Count;
  int intervalSize = 7;

  // go from current date for period of 7 days (include current day)
  for( int i = 0; i < numDays; i += intervalSize ) {

    // get data for current week
    int count = numDays - i >= intervalSize ? intervalSize : numDays - i;
    Collections::Generic::List<double> ^ week = _data->GetRange( i, count );

    // sum and average current week
    double sum = 0.0;
    for each( double d in week ) {
      sum += d;
    }

    if( function == TimePeriodFunction::Sum ) {
      weeklyData->Add( sum );
    }
    else { // function == TimePeriodFunction::Average
      double average = sum / week->Count;
      weeklyData->Add( average );
    }
  }

  return weeklyData;
}



Collections::Generic::List<double> ^ 
Output::GetMonthlyData( DateTime startDate, DateTime stopDate, TimePeriodFunction function )
{
  Collections::Generic::List<double> ^ monthlyData = gcnew Collections::Generic::List<double>();

  // end of the month is one day before the start of the next month
  DateTime endOfMonth = DateTime( startDate.Year, startDate.Month, 1 ).AddMonths( 1 ).AddDays( -1 );
  int i = 0;
  for( DateTime dt = startDate; dt <= stopDate; ) {

    // interval for the last month can end at some specified
    // stopDate and not neccesarily the end of the month
    if( endOfMonth > stopDate ) {
      endOfMonth = stopDate;
    }

    int count = (endOfMonth - dt).Days + 1;

    // get data for current month
    Collections::Generic::List<double> ^ month = _data->GetRange( i, count );

    // sum and average current month
    double sum = 0.0;
    for each( double d in month ) {
      sum += d;
    }
    if( function == TimePeriodFunction::Sum ) {
      monthlyData->Add( sum );
    }
    else { // function == TimePeriodFunction::Average
      double average = sum / month->Count;
      monthlyData->Add( average );
    }

    // next interval begins on the day after end of the current month
    i = i + count;
    dt = endOfMonth.AddDays( 1 );
    // and goes to the end of the next month
    endOfMonth = dt.AddMonths( 1 ).AddDays( -1 );
  }

  return monthlyData;
}



SimOutput::SimOutput( DateTime startDate, DateTime stopDate )
: _startDate(startDate),
  _stopDate(stopDate),
  _dates(gcnew Collections::Generic::List<DateTime>())
{
  // create list of Dates
  DateTime date = _startDate;
  while( date <= _stopDate ) {
    _dates->Add( date );
    date = date.AddDays(1);
  }
}



SimOutput::~SimOutput(void)
{}



void
SimOutput::GenerateWeeks(void)
{
  int numDays = (_stopDate - _startDate).Days + 1;
  int numWeeks = (int) ceil( (double) numDays / 7.0 );

  _weeks = gcnew Collections::Generic::List<int>( numWeeks );
  for( int i = 1; i <= numWeeks; ++i ) {
    _weeks->Add( i );
  }
}



void
SimOutput::GenerateMonths(void)
{
  _months = gcnew Collections::Generic::List<DateTime>();

  DateTime dt = DateTime( _startDate.Year, _startDate.Month, 1 );
  while( dt <= _stopDate ) {
    _months->Add( dt );
    dt = dt.AddMonths( 1 );
  }
}



CimsimOutput::CimsimOutput( DateTime startDate, DateTime stopDate )
: SimOutput( startDate, stopDate ),
  _location(OutputCollections::CreateNewOutputCollection( OutputTypes::Cimsim::Location::typeid )),
  _containers(gcnew Collections::Generic::Dictionary<int,IndexedOutputCollection^>())
{}



CimsimOutput::~CimsimOutput(void)
{}



void
CimsimOutput::AddContainerType( int containerId )
{
  IndexedOutputCollection ^ containerOutput = OutputCollections::CreateNewOutputCollection( OutputTypes::Cimsim::Container::typeid );
  _containers->Add( containerId, containerOutput );
}



DensimOutput::DensimOutput( DateTime startDate, DateTime stopDate )
: SimOutput( startDate, stopDate ),
  _location(OutputCollections::CreateNewOutputCollection( OutputTypes::Densim::Location::typeid )),
  _serotypes( gcnew Collections::Generic::Dictionary<int,IndexedOutputCollection^>())
{
  for( int serotypeId = 1; serotypeId <= 4; ++serotypeId ) {
    IndexedOutputCollection ^ serotypeOutput = OutputCollections::CreateNewOutputCollection( OutputTypes::Densim::Serotype::typeid );
    _serotypes->Add( serotypeId, serotypeOutput );
  }
}



DensimOutput::~DensimOutput(void)
{}
