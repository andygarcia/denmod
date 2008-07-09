#include "stdafx.h"
#include "Enums.h"
#include "Outputs.h"
#include <cmath>

using namespace gui::output;



OutputInfo::OutputInfo( Group outputGroup, String ^ name, String ^ units )
: _name(name),
  _units(units),
  _outputGroup(outputGroup)
{}



OutputInfo::~OutputInfo(void)
{
}



static
OutputInfos::OutputInfos(void)
{
  _groupToType = gcnew Collections::Generic::Dictionary<Group,Type^>();
  _groupToType->Add( Group::CimsimLocation, CimsimLocation::typeid );
  _groupToType->Add( Group::CimsimContainer, CimsimContainer::typeid );
  _groupToType->Add( Group::DensimLocation, DensimLocation::typeid );
  _groupToType->Add( Group::DensimSerotype, DensimSerotype::typeid );

  _cimsimLocation = GetOutputInfoCollection( Group::CimsimLocation );
  _cimsimContainer = GetOutputInfoCollection( Group::CimsimContainer );
  _densimLocation = GetOutputInfoCollection( Group::DensimLocation );
  _densimSerotype = GetOutputInfoCollection( Group::DensimSerotype );

  _groupToCollection = gcnew Collections::Generic::Dictionary<Group,OutputInfoCollection^>();
  _groupToCollection->Add( Group::CimsimLocation, _cimsimLocation );
  _groupToCollection->Add( Group::CimsimContainer, _cimsimContainer );
  _groupToCollection->Add( Group::DensimLocation, _densimLocation );
  _groupToCollection->Add( Group::DensimSerotype, _densimSerotype );
}



OutputInfoCollection ^
OutputInfos::GetOutputInfoCollection( Group outputGroup )
{
  // generate a collection of OutputInfo object for this type by using
  // reflection to access OutputInfoAttribute on members
  OutputInfoCollection ^ outputInfos = gcnew OutputInfoCollection();

  Type ^ type = _groupToType[outputGroup];

  array<Reflection::FieldInfo^> ^ fields = type->GetFields( Reflection::BindingFlags::Static | Reflection::BindingFlags::GetField | Reflection::BindingFlags::Public );
  for each( Reflection::FieldInfo ^ fi in fields ) {
    OutputInfo ^ oi = (OutputInfo^) fi->GetValue( type );
    outputInfos->Add( oi );
    fi->SetValue( type, oi );
  }

  return outputInfos;
}



OutputMap ^
OutputInfos::CreateNewOutputMap( Group outputGroup, DateTime startDate, DateTime stopDate )
{
  OutputInfoCollection ^ oic = _groupToCollection[outputGroup];

  OutputMap ^ outputs = gcnew OutputMap();
  for each( OutputInfo ^ oi in oic ) {
    Output ^ o;
    if( oi->GetType() == DatedOutputInfo::typeid ) {
      o = gcnew DatedOutput( oi, startDate, stopDate );
    }
    else {
      o = gcnew Output( oi );
    }
    outputs->Add( oi, o );
  }
  return outputs;
}



static
OutputInfos::CimsimLocation::CimsimLocation(void)
{
  TotalEggs = gcnew DatedOutputInfo( Group::CimsimLocation, "TotalEggs", "#/ha" );
  TotalLarvae = gcnew DatedOutputInfo( Group::CimsimLocation, "TotalLarvae", "#/ha" );
  TotalPupae = gcnew DatedOutputInfo( Group::CimsimLocation, "TotalPupae", "#/ha" );
  TotalFemales = gcnew DatedOutputInfo( Group::CimsimLocation, "TotalFemales", "#/ha" );
  NewFemales = gcnew DatedOutputInfo( Group::CimsimLocation, "NewFemales", "#/ha" );
  AverageFemaleWeight = gcnew DatedOutputInfo( Group::CimsimLocation, "AverageFemaleWeight", "mg" );
  Oviposition = gcnew DatedOutputInfo( Group::CimsimLocation, "Oviposition", "#" );
  MaximumTemperature = gcnew DatedOutputInfo( Group::CimsimLocation, "MaximumTemperature", "C" );
  AverageTemperature = gcnew DatedOutputInfo( Group::CimsimLocation, "AverageTemperature", "C" );
  MinimumTemperature = gcnew DatedOutputInfo( Group::CimsimLocation, "MinimumTemperature", "C" );
  Rainfall = gcnew DatedOutputInfo( Group::CimsimLocation, "Rainfall", "mm" );
  RelativeHumidity = gcnew DatedOutputInfo( Group::CimsimLocation, "RelativeHumidity", "%" );
  SaturationDeficit = gcnew DatedOutputInfo( Group::CimsimLocation, "SaturationDeficit", "mbars" );
}



static
OutputInfos::CimsimContainer::CimsimContainer()
{
  Depth = gcnew DatedOutputInfo( Group::CimsimContainer, "Depth", "cm" );
  Food = gcnew DatedOutputInfo( Group::CimsimContainer, "Food", "mg" );
  MaximumTemperature = gcnew DatedOutputInfo( Group::CimsimContainer, "MaximumTemperature", "C" );
  MinimumTemperature = gcnew DatedOutputInfo( Group::CimsimContainer, "MinimumTemperature", "C" );
  Eggs = gcnew DatedOutputInfo( Group::CimsimContainer, "Eggs", "#" );
  Larvae = gcnew DatedOutputInfo( Group::CimsimContainer, "Larvae", "#" );
  Pupae = gcnew DatedOutputInfo( Group::CimsimContainer, "Pupae", "#" );
  AveragePupalWeight = gcnew DatedOutputInfo( Group::CimsimContainer, "AveragePupalWeight", "mg" );
  NewFemales = gcnew DatedOutputInfo( Group::CimsimContainer, "NewFemales", "#" );
  CumulativeFemales = gcnew DatedOutputInfo( Group::CimsimContainer, "CumulativeFemales", "#" );
  Oviposition = gcnew DatedOutputInfo( Group::CimsimContainer, "Oviposition", "#" );
  UntreatedDensity = gcnew DatedOutputInfo( Group::CimsimContainer, "UntreatedDensity", "#/ha" );
  TreatedDensity = gcnew DatedOutputInfo( Group::CimsimContainer, "TreatedDensity", "#/ha" );
  ExcludedDensity = gcnew DatedOutputInfo( Group::CimsimContainer, "ExcludedDensity", "#/ha" );
}



static
OutputInfos::DensimLocation::DensimLocation()
{
  InitialAgeDistribution = gcnew DatedOutputInfo( Group::DensimLocation, "InitialAgeDistribution", "# of individuals" );
  FinalAgeDistribution = gcnew DatedOutputInfo( Group::DensimLocation, "FinalAgeDistribution", "# of individuals" );
  SimulationArea = gcnew DatedOutputInfo( Group::DensimLocation, "SimulationArea", "ha" );
  PopulationSize = gcnew DatedOutputInfo( Group::DensimLocation, "PopulationSize", "# of individuals" );
  BirthsByClass = gcnew DatedOutputInfo( Group::DensimLocation, "BirthsByClass", "# births" );
  DeathsByClass = gcnew DatedOutputInfo( Group::DensimLocation, "DeathsByClass", "# of individuals" );
  BirthPercentagesByClass = gcnew DatedOutputInfo( Group::DensimLocation, "BirthPercentagesByClass", "# of individuals" );
  DeathPercentagesByClass = gcnew DatedOutputInfo( Group::DensimLocation, "DeathPercentagesByClass", "# of individuals" );
  FemaleMosquitoesInSimulationArea = gcnew DatedOutputInfo( Group::DensimLocation, "FemaleMosquitoesInSimulationArea", "# in area" );
  FemaleMosquitoesPerHectare = gcnew DatedOutputInfo( Group::DensimLocation, "FemaleMosquitoesPerHectare", "# / ha" );
  FemaleMosquitoesPerPerson = gcnew DatedOutputInfo( Group::DensimLocation, "FemaleMosquitoesPerPerson", "# / person" );
  FemaleMosquitoSurvival = gcnew DatedOutputInfo( Group::DensimLocation, "FemaleMosquitoSurvival", "" );
  FemaleMosquitoWetWeight = gcnew DatedOutputInfo( Group::DensimLocation, "FemaleMosquitoWetWeight", "mg" );
}



static
OutputInfos::DensimSerotype::DensimSerotype()
{
  EipDevelopmentRate = gcnew DatedOutputInfo( Group::DensimSerotype, "EipDevelopmentRate", "1/day" );
  InfectiveMosquitoes = gcnew DatedOutputInfo( Group::DensimSerotype, "InfectiveMosquitoes", "# of infective mosquitoes" );
  PotentiallyInfectiveBites = gcnew DatedOutputInfo( Group::DensimSerotype, "PotentiallyInfectiveBites", "# of bites" );
  PersonsIncubating = gcnew DatedOutputInfo( Group::DensimSerotype, "PersonsIncubating", "# of persons incubating" );
  PersonsViremic = gcnew DatedOutputInfo( Group::DensimSerotype, "PersonsViremic", "# of persons viremic" );
  PersonsWithVirus = gcnew DatedOutputInfo( Group::DensimSerotype, "PersonsWithVirus", "# of persons incubating or viremic" );
}


Collections::Generic::List<double> ^ 
DatedOutput::GetWeeklyData( TimePeriodFunction function )
{
  Collections::Generic::List<double> ^ weeklyData = gcnew Collections::Generic::List<double>();

  int numDays = Data->Count;
  int intervalSize = 7;

  // go from current date for period of 7 days (include current day)
  for( int i = 0; i < numDays; i += intervalSize ) {

    // get data for current week
    int count = numDays - i >= intervalSize ? intervalSize : numDays - i;
    Collections::Generic::List<double> ^ week = Data->GetRange( i, count );

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
DatedOutput::GetMonthlyData( DateTime startDate, DateTime stopDate, TimePeriodFunction function )
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
    Collections::Generic::List<double> ^ month = Data->GetRange( i, count );

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
: SimOutput(startDate, stopDate),
  _location(OutputInfos::CreateNewOutputMap( Group::CimsimLocation, startDate, stopDate)),
  _containers(gcnew Collections::Generic::Dictionary<int,OutputMap^>())
{}



CimsimOutput::~CimsimOutput(void)
{}



void
CimsimOutput::AddContainerType( int containerId )
{
  OutputMap ^ containerOutput = OutputInfos::CreateNewOutputMap( Group::CimsimContainer, _startDate, _stopDate );
  _containers->Add( containerId, containerOutput );
}



String ^
SimOutput::GenerateExcelXml( Collections::Generic::List<DateTime> ^ dates, Collections::Generic::List<Output^> ^ columns )
{
  System::Text::StringBuilder ^ sb = gcnew System::Text::StringBuilder();

  // write XML file header
  sb->Append("<?xml version=\"1.0\"?>" + Environment::NewLine);
  sb->Append("<?mso-application progid=\"Excel.Sheet\"?>" + Environment::NewLine);
  sb->Append("<Workbook xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\"" + Environment::NewLine);
  sb->Append(" xmlns:o=\"urn:schemas-microsoft-com:office:office\"" + Environment::NewLine);
  sb->Append(" xmlns:x=\"urn:schemas-microsoft-com:office:excel\"" + Environment::NewLine);
  sb->Append(" xmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\"" + Environment::NewLine);
  sb->Append(" xmlns:html=\"http://www.w3.org/TR/REC-html40\">" + Environment::NewLine);

  sb->Append(" <DocumentProperties xmlns=\"urn:schemas-microsoft-com:office:office\">" + Environment::NewLine);
  sb->Append("  <Author>Dengue Models</Author>" + Environment::NewLine );
  sb->Append("  <LastAuthor>Dengue Models</LastAuthor>" + Environment::NewLine);
  sb->Append("  <Created>" + DateTime::Now.ToString("s") + "</Created>" + Environment::NewLine);
  sb->Append("  <Version>12.00</Version>" + Environment::NewLine);
  sb->Append(" </DocumentProperties>" + Environment::NewLine);

  sb->AppendLine( " <Styles>");
  sb->AppendLine( "  <Style ss:ID=\"Default\" ss:Name=\"Normal\">" );
  sb->AppendLine( "   <Alignment ss:Vertical=\"Center\"/>" );
  sb->AppendLine( "  </Style>" );
  sb->AppendLine( " </Styles>" );
  sb->AppendLine( " <Worksheet ss:Name=\"Sheet1\">" );
  sb->AppendLine( "  <Table>");

  // if any data to save exists...
  if( columns->Count > 0 && dates->Count > 0 ) {

    // date header
    sb->AppendLine( "   <Row>" );
    sb->AppendLine( "    <Cell><Data ss:Type=\"String\">Date</Data></Cell>" );

    // header for each output column
    for( int i = 0; i < columns->Count; ++i ) {
      int columnIndex = i + 2;
      String ^ cellString = String::Format( "    <Cell><Data ss:Type=\"String\">{1}</Data></Cell>", Convert::ToString( columnIndex ), columns[i]->Name );
      sb->Append( cellString );
      sb->Append( Environment::NewLine );
    }
    sb->AppendLine( "   </Row>" );


    // daily rows of data
    for( int i = 0; i < dates->Count; ++i ) {
      sb->Append("   <Row>" + Environment::NewLine);

      // date cell
      String ^ cellString = String::Format( "    <Cell><Data ss:Type=\"String\">{1}</Data></Cell>", Convert::ToString(0), dates[i].ToString("yyyy-MM-dd") );
      sb->Append(cellString + Environment::NewLine );
      
      // column cells
      for( int j = 0; j < columns->Count; ++j ) {

        cellString = String::Format( "    <Cell><Data ss:Type=\"Number\">{1}</Data></Cell>",
                                     Convert::ToString( j + 2 ),
                                     Convert::ToDouble( columns[j]->Data[i] ));
        sb->Append(cellString + Environment::NewLine);
      }

      sb->Append("   </Row>" + Environment::NewLine);
    }
  }

  // close all XML tags
  sb->Append("  </Table>" + Environment::NewLine);
  sb->Append(" </Worksheet>" + Environment::NewLine);
  sb->Append("</Workbook>" + Environment::NewLine);

  return sb->ToString();

}


  
String ^
CimsimOutput::GetLocationExcelXml(void)
{
  OutputCollection ^ outputs = gcnew OutputCollection();
  for each( Output ^ output in _location->Values ) {
    outputs->Add( output );
  }

  return GenerateExcelXml( Dates, outputs );
}



String ^
CimsimOutput::GetContainerExcelXml( int containerId )
{
  OutputCollection ^ outputs = gcnew OutputCollection();
  for each( Output ^ output in _containers[containerId]->Values ) {
    outputs->Add( output );
  }

  return GenerateExcelXml( Dates, outputs );
}



DensimOutput::DensimOutput( DateTime startDate, DateTime stopDate )
: SimOutput(startDate, stopDate),
  _location(OutputInfos::CreateNewOutputMap(Group::DensimLocation, startDate, stopDate)),
  _serotypes(gcnew Collections::Generic::Dictionary<int,OutputMap^>())
{
  for( int serotypeId = 1; serotypeId <= 4; ++serotypeId ) {
    OutputMap ^ serotypeOutput = OutputInfos::CreateNewOutputMap( Group::DensimSerotype, startDate, stopDate );
    _serotypes->Add( serotypeId, serotypeOutput );
  }
}



DensimOutput::~DensimOutput(void)
{}
