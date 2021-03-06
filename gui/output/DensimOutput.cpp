#include "stdafx.h"
#include "Enums.h"
#include "DensimOutput.h"

using namespace gui::output;



static
DensimOutput::DensimOutput(void)
{
  _seroClasses = gcnew Collections::Generic::Dictionary<int,String^>();
  _seroClasses->Add( 1, "MANA" );
  _seroClasses->Add( 2, "MAEA" );
  _seroClasses->Add( 3, "0-1 years" );
  _seroClasses->Add( 4, "1-4 years" );
  _seroClasses->Add( 5, "5-9" );
  _seroClasses->Add( 6, "10-14" );
  _seroClasses->Add( 7, "15-19" );
  _seroClasses->Add( 8, "20-24" );
  _seroClasses->Add( 9, "25-29" );
  _seroClasses->Add( 10, "30-34" );
  _seroClasses->Add( 11, "35-39" );
  _seroClasses->Add( 12, "40-44" );
  _seroClasses->Add( 13, "45-49" );
  _seroClasses->Add( 14, "50-54" );
  _seroClasses->Add( 15, "55-59" );
  _seroClasses->Add( 16, "60-64" );
  _seroClasses->Add( 17, "65-69" );
  _seroClasses->Add( 18, "70-74" );
  _seroClasses->Add( 19, "75-79" );
  _seroClasses->Add( 20, "80+" );
  _seroClasses->Add( 21, "15-44" );
  _seroClasses->Add( 22, "45-80+" );
  _seroClasses->Add( 23, "0-80+" );
}



DensimOutput::DensimOutput( String ^ name, double humanDensity, DateTime startDate, DateTime stopDate )
: SimOutput(name, startDate, stopDate),
  _humanDensity(humanDensity),
  _serotypes(gcnew Collections::Generic::Dictionary<int, SerotypeOutput ^>())
{}



DensimOutput::~DensimOutput(void)
{}



void
DensimOutput::SaveToDisk( IO::DirectoryInfo ^ di )
{
  // save all densim output into target directory
  System::String ^ directory = di->FullName;
  System::String ^ locFile = directory + "\\DENSiM - Location.xml";
  System::String ^ demFile = directory + "\\DENSiM - Demographics.xml";
  System::String ^ serFile = directory + "\\DENSiM - Serology.xml";

  // write general location file
  IO::FileStream ^ fs = gcnew IO::FileStream( locFile, System::IO::FileMode::Create );
  IO::StreamWriter ^ sw = gcnew IO::StreamWriter( fs );
  WriteLocationWorkbook( sw );
  sw->Close();

  // write demographics file
  fs = gcnew IO::FileStream( demFile, IO::FileMode::Create );
  sw = gcnew IO::StreamWriter( fs );
  WriteDemographicsWorkbook( sw );
  sw->Close();

  // write serology file
  fs = gcnew IO::FileStream( serFile, IO::FileMode::Create );
  sw = gcnew IO::StreamWriter( fs );
  WriteSerologyWorkbook( sw );
  sw->Close();

  // write virus file with per-serotype data
  System::String ^ virusFile = directory + "\\DENSiM - Virus.xml";
  fs = gcnew IO::FileStream( virusFile, IO::FileMode::Create );
  sw = gcnew IO::StreamWriter( fs );
  WriteVirusWorkbook( sw );
  sw->Close();
}



void
DensimOutput::WriteDemographicsWorkbook( IO::StreamWriter ^ sw )
{
  // demographics - includes age distributions, births and deaths
  List<String^> ^ headers = gcnew List<String^>();
  List<String^> ^ classIndices = gcnew List<String^>();
  List<array<double>^> ^ data = gcnew List<array<double>^>();

  headers->Add( "Age class" );
  headers->Add( "Initial age distribution" );
  headers->Add( "Births" );
  headers->Add( "Deaths" );
  headers->Add( "Final age distribution" );

  for( int i = 1; i <=18; ++i ) {
    classIndices->Add( Convert::ToString(i) );
  }

  data->Add( _initialAgeDistribution );
  data->Add( _birthsByClass );
  data->Add( _deathsByClass );
  data->Add( _finalAgeDistribution );

  WriteWorkbookOpen( sw );
  WriteWorkbookStyles( sw );
  WriteClassWorksheet( sw, "Demographics", headers, classIndices, data );
  WriteWorkbookClose( sw );
}


void
DensimOutput::WriteSerologyWorkbook( IO::StreamWriter ^ sw )
{
  // demographics - includes age distributions, births and deaths
  List<String^> ^ headers = gcnew List<String^>();
  List<String^> ^ classIndices = gcnew List<String^>();
  List<array<double>^> ^ data = gcnew List<array<double>^>();

  headers->Add( "Age class" );
  headers->Add( "Dengue 1 Initial Distribution" );
  headers->Add( "Dengue 2 Initial Distribution" );
  headers->Add( "Dengue 3 Initial Distribution" );
  headers->Add( "Dengue 4 Initial Distribution" );
  headers->Add( "Dengue 1 Final Distribution" );
  headers->Add( "Dengue 2 Final Distribution" );
  headers->Add( "Dengue 3 Final Distribution" );
  headers->Add( "Dengue 4 Final Distribution" );

  for( int i = 1; i <= 18; ++i ) {
    classIndices->Add( Convert::ToString(i) );
  }

  data->Add( _serotypes[1]->InitialSeroDistribution );
  data->Add( _serotypes[2]->InitialSeroDistribution );
  data->Add( _serotypes[3]->InitialSeroDistribution );
  data->Add( _serotypes[4]->InitialSeroDistribution );
  data->Add( _serotypes[1]->FinalSeroDistribution );
  data->Add( _serotypes[2]->FinalSeroDistribution );
  data->Add( _serotypes[3]->FinalSeroDistribution );
  data->Add( _serotypes[4]->FinalSeroDistribution );

  WriteWorkbookOpen( sw );
  WriteWorkbookStyles( sw );
  WriteClassWorksheet( sw, "Serology", headers, classIndices, data );
  WriteWorkbookClose( sw );
}



void
DensimOutput::WriteLocationWorkbook( IO::StreamWriter ^ sw )
{
  List<String^> ^ headers = gcnew List<String^>();
  List<array<double>^> ^ data = gcnew List<array<double>^>();

  headers->Add( "Date" );
  headers->Add( "Population Size" );
  headers->Add( "Female Mosquitoes in Area" );
  headers->Add( "Potentially Infective Bites" );

  data->Add( _populationSize );
  data->Add( _femaleMosquitoesInSimulationArea );
  data->Add( _potentiallyInfectiveBites );

  WriteWorkbookOpen( sw );
  WriteWorkbookStyles( sw );
  WriteDailyWorksheet( sw, "Location", headers, _dates, data );
  WriteWorkbookClose( sw );
}



void
DensimOutput::WriteVirusWorkbook( IO::StreamWriter ^ sw )
{
  // open workbook for writing
  WriteWorkbookOpen( sw );
  WriteWorkbookStyles( sw );

  // create header and data format
  List<String^> ^ headers = gcnew List<String^>();
  List<array<double>^> ^ data = gcnew List<array<double>^>();

  headers->Add( "Date" );
  headers->Add( "EIP Development Rate" );
  headers->Add( "Infective Mosquitoes" );
  headers->Add( "Persons Incubating" );
  headers->Add( "Persons Viremic" );
  headers->Add( "Persons with Virus" );

  // add header listings for detailed seroprevalence
  List<EnumText^> ^ seroclassHeaders = EnumText::ConvertEnumForBinding( SeroClass() );
  for each( EnumText ^ et in seroclassHeaders ) {
    headers->Add( et->DisplayName );
  }


  // create per-serotype worksheets based on serotype data
  for( int i = 1; i <= 4; ++i ) {
    data->Add( _serotypes[i]->EipDevelopmentRate );
    data->Add( _serotypes[i]->InfectiveMosquitoes );
    data->Add( _serotypes[i]->PersonsIncubating );
    data->Add( _serotypes[i]->PersonsViremic );
    data->Add( _serotypes[i]->PersonsWithVirus );
    for( int seroclass = 1; seroclass <= 23; ++seroclass ) {
      data->Add( _serotypes[i]->ClassSpecificSeroprevalence[seroclass] );
    }

    // write per-serotype worksheet to open workbook
    WriteDailyWorksheet( sw, String::Format("Dengue {0}", i), headers, _dates, data );

    // clear data for next serotype
    data->Clear();
  }

  // close workbook
  WriteWorkbookClose( sw );
}



Chart ^
DensimOutput::CreateChart( ChartInfo ^ chartInfo )
{
  Chart ^ chart = gcnew Chart( chartInfo->Name, chartInfo->Periodic );

  ChartIds chartId = chartInfo->ChartId;

  if( chartId == ChartIds::DensimMain ) {
    // counts
    array<double> ^ d1InfectedProportion = gcnew array<double>( _numberOfDays );
    array<double> ^ d2InfectedProportion = gcnew array<double>( _numberOfDays );
    array<double> ^ d3InfectedProportion = gcnew array<double>( _numberOfDays );
    array<double> ^ d4InfectedProportion = gcnew array<double>( _numberOfDays );

    // proportions
    for( int i = 0; i < _numberOfDays; ++i ) {
      d1InfectedProportion[i] = _serotypes[1]->PersonsWithVirus[i] / _populationSize[i];
      d2InfectedProportion[i] = _serotypes[2]->PersonsWithVirus[i] / _populationSize[i];
      d3InfectedProportion[i] = _serotypes[3]->PersonsWithVirus[i] / _populationSize[i];
      d4InfectedProportion[i] = _serotypes[4]->PersonsWithVirus[i] / _populationSize[i];
    }

    DatedOutput ^ d1 = gcnew DatedOutput( "Dengue 1", _startDate, _stopDate, d1InfectedProportion );
    DatedOutput ^ d2 = gcnew DatedOutput( "Dengue 2", _startDate, _stopDate, d2InfectedProportion );
    DatedOutput ^ d3 = gcnew DatedOutput( "Dengue 3", _startDate, _stopDate, d3InfectedProportion );
    DatedOutput ^ d4 = gcnew DatedOutput( "Dengue 4", _startDate, _stopDate, d4InfectedProportion );

    Plot ^ p = gcnew Plot();
    p->PlotType = "Line";
    p->Title = "Proportion of population infected";
    p->AxisX = "Date";
    p->AxisY = "proportion infected";
    p->MinYAxis = 0.0;
    p->MaxYAxis = 0.0;
    p->PrimaryOutputs->Add( d1 );
    p->PrimaryOutputs->Add( d2 );
    p->PrimaryOutputs->Add( d3 );
    p->PrimaryOutputs->Add( d4 );

    chart->Plots->Add( p );
  }

  else if( chartId == ChartIds::DensimAgeDistributions ) {
    ClassOutput ^ initial = gcnew ClassOutput( "Initial age distribution", _initialAgeDistribution );
    ClassOutput ^ final = gcnew ClassOutput( "Final age distribution", _finalAgeDistribution );

    Plot ^ p1 = gcnew Plot();
    p1->PlotType = "Column";
    p1->Title = "Initial age distribution";
    p1->AxisX = "Age class";
    p1->AxisY = "# of individuals";
    p1->PrimaryOutputs->Add( initial );

    Plot ^ p2 = gcnew Plot();
    p2->PlotType = "Column";
    p2->Title = "Final age distribution";
    p2->AxisX = "Age class";
    p2->AxisY = "# of individuals";
    p2->PrimaryOutputs->Add( final );

    chart->Plots->Add( p1 );
    chart->Plots->Add( p2 );
  }

  else if( chartId == ChartIds::DensimSimulationArea ) {
    array<double> ^ areaData = gcnew array<double>( _numberOfDays );
    for( int i = 0; i < _numberOfDays; ++i ) {
      areaData[i] = _populationSize[i] / _humanDensity;
    }

    DatedOutput ^ area = gcnew DatedOutput( "Simulation area", _startDate, _stopDate, areaData );

    Plot ^ p = gcnew Plot();
    p->Title = "Simulation area in hectares";
    p->AxisX = "Date";
    p->AxisY = "Area (ha)";
    p->PlotType = "Line";
    p->PrimaryOutputs->Add( area );

    chart->Plots->Add( p );
  }

  else if( chartId == ChartIds::DensimPopulationSize ) {
    DatedOutput ^ population = gcnew DatedOutput( "Population size", _startDate, _stopDate, _populationSize );

    Plot ^ p = gcnew Plot();
    p->Title = "Population size";
    p->AxisX = "Date";
    p->AxisY = "# of individuals";
    p->PlotType = "Line";
    p->PrimaryOutputs->Add( population );

    chart->Plots->Add( p );
  }

  else if( chartId == ChartIds::DensimBirthsAndDeaths ) {
    ClassOutput ^ births = gcnew ClassOutput( "Births by age class", _birthsByClass );
    ClassOutput ^ deaths = gcnew ClassOutput( "Deaths by age class", _deathsByClass );

    array<double> ^ birthPercentagesData = gcnew array<double>(18);
    array<double> ^ deathPercentagesData = gcnew array<double>(18);
    for( int i = 0; i < 18; ++i ) {
      if( _finalAgeDistribution[i] != 0 ) {
        birthPercentagesData[i] = _birthsByClass[i] / _finalAgeDistribution[i];
        deathPercentagesData[i] = _deathsByClass[i] / _finalAgeDistribution[i];
      }
      else {
        birthPercentagesData[i] = 0;
        deathPercentagesData[i] = 0;
      }
    }
    ClassOutput ^ birthPercentages = gcnew ClassOutput( "Birth percentages by age class", _birthsByClass );
    ClassOutput ^ deathPercentages = gcnew ClassOutput( "Death percentages by age class", _deathsByClass );

    Plot ^ p1 = gcnew Plot();
    p1->PlotType = "Column";
    p1->Title = "Births by age class";
    p1->AxisX = "Age class";
    p1->AxisY = "# of births";
    p1->PrimaryOutputs->Add( births );

    Plot ^ p2 = gcnew Plot();
    p2->PlotType = "Column";
    p2->Title = "Deaths by age class";
    p2->AxisX = "Age class";
    p2->AxisY = "# of deaths";
    p2->PrimaryOutputs->Add( deaths );

    Plot ^ p3 = gcnew Plot();
    p3->PlotType = "Column";
    p3->Title = "Birth percentages by age class";
    p3->AxisX = "Age class";
    p3->AxisY = "Percentage of births";
    p3->PrimaryOutputs->Add( birthPercentages );

    Plot ^ p4 = gcnew Plot();
    p4->PlotType = "Column";
    p4->Title = "Death percentages by age class";
    p4->AxisX = "Age class";
    p4->AxisY = "Percentage of deaths";
    p4->PrimaryOutputs->Add( deathPercentages );

    chart->Plots->Add( p1 );
    chart->Plots->Add( p2 );
    chart->Plots->Add( p3 );
    chart->Plots->Add( p4 );
  }

  else if( chartId == ChartIds::DensimFemaleMosquitoesInArea ) {
    DatedOutput ^ females = gcnew DatedOutput( "Female mosquitos in simulation area", _startDate, _stopDate, _femaleMosquitoesInSimulationArea );

    Plot ^ p = gcnew Plot();
    p->PlotType = "Line";
    p->Title = "Female mosquitoes in simulation area";
    p->AxisX = "Date";
    p->AxisY = "# of female mosquitoes";
    p->PrimaryOutputs->Add( females );

    chart->Plots->Add( p );
  }

  else if( chartId == ChartIds::DensimFemaleMosquitoesPerPerson ) {
    array<double> ^ femalePerPersonData = gcnew array<double>( _numberOfDays );
    for( int i = 0; i < _numberOfDays; ++i ) {
      femalePerPersonData[i] = _femaleMosquitoesInSimulationArea[i] / _populationSize[i];
    }
    DatedOutput ^ femalesPerPerson = gcnew DatedOutput( "Females per person", _startDate, _stopDate, femalePerPersonData );

    Plot ^ p = gcnew Plot();
    p->PlotType = "Line";
    p->Title = "Female mosquitoes per person";
    p->AxisX = "Date";
    p->AxisY = "# female mosquitoes";
    p->PrimaryOutputs->Add( femalesPerPerson );

    chart->Plots->Add( p );
  }

  //else if( chartId == ChartIds::DensimFemaleMosquitoSurvival ) {
  //}

  //else if( chartId == ChartIds::DensimFemaleMosquitoWetWeight ) {
  //}

  else if( chartId == ChartIds::DensimEipDevelopmentRate ) {
    DatedOutput ^ d1 = gcnew DatedOutput( "Dengue 1", _startDate, _stopDate, _serotypes[1]->EipDevelopmentRate );
    DatedOutput ^ d2 = gcnew DatedOutput( "Dengue 2", _startDate, _stopDate, _serotypes[2]->EipDevelopmentRate );
    DatedOutput ^ d3 = gcnew DatedOutput( "Dengue 3", _startDate, _stopDate, _serotypes[3]->EipDevelopmentRate );
    DatedOutput ^ d4 = gcnew DatedOutput( "Dengue 4", _startDate, _stopDate, _serotypes[4]->EipDevelopmentRate );

    Plot ^ p = gcnew Plot();
    p->PlotType = "Line";
    p->Title = "EIP Development Rate";
    p->AxisX = "Date";
    p->AxisY = L"day ⁻¹";
    p->PrimaryOutputs->Add( d1 );
    p->PrimaryOutputs->Add( d2 );
    p->PrimaryOutputs->Add( d3 );
    p->PrimaryOutputs->Add( d4 );

    chart->Plots->Add( p );
  }
  
  else if( chartId == ChartIds::DensimInfectiveMosquitoes ) {
    DatedOutput ^ d1 = gcnew DatedOutput( "Dengue 1", _startDate, _stopDate, _serotypes[1]->InfectiveMosquitoes );
    DatedOutput ^ d2 = gcnew DatedOutput( "Dengue 2", _startDate, _stopDate, _serotypes[2]->InfectiveMosquitoes );
    DatedOutput ^ d3 = gcnew DatedOutput( "Dengue 3", _startDate, _stopDate, _serotypes[3]->InfectiveMosquitoes );
    DatedOutput ^ d4 = gcnew DatedOutput( "Dengue 4", _startDate, _stopDate, _serotypes[4]->InfectiveMosquitoes );

    Plot ^ p = gcnew Plot();
    p->Title = "Infective Mosquitoes";
    p->AxisX = "Date";
    p->AxisY = "# of infective mosquitoes";
    p->PlotType = "Line";
    p->PrimaryOutputs->Add( d1 );
    p->PrimaryOutputs->Add( d2 );
    p->PrimaryOutputs->Add( d3 );
    p->PrimaryOutputs->Add( d4 );

    chart->Plots->Add( p );
  }
  
  else if( chartId == ChartIds::DensimPersonsIncubating ) {
    DatedOutput ^ d1 = gcnew DatedOutput( "Dengue 1", _startDate, _stopDate, _serotypes[1]->PersonsIncubating );
    DatedOutput ^ d2 = gcnew DatedOutput( "Dengue 2", _startDate, _stopDate, _serotypes[2]->PersonsIncubating );
    DatedOutput ^ d3 = gcnew DatedOutput( "Dengue 3", _startDate, _stopDate, _serotypes[3]->PersonsIncubating );
    DatedOutput ^ d4 = gcnew DatedOutput( "Dengue 4", _startDate, _stopDate, _serotypes[4]->PersonsIncubating );

    Plot ^ p = gcnew Plot();
    p->Title = "Persons Incubating";
    p->AxisX = "Date";
    p->AxisY = "# of persons";
    p->PlotType = "Line";
    p->PrimaryOutputs->Add( d1 );
    p->PrimaryOutputs->Add( d2 );
    p->PrimaryOutputs->Add( d3 );
    p->PrimaryOutputs->Add( d4 );

    chart->Plots->Add( p );
  }
  
  else if( chartId == ChartIds::DensimPersonsViremic ) {
    DatedOutput ^ d1 = gcnew DatedOutput( "Dengue 1", _startDate, _stopDate, _serotypes[1]->PersonsViremic );
    DatedOutput ^ d2 = gcnew DatedOutput( "Dengue 2", _startDate, _stopDate, _serotypes[2]->PersonsViremic );
    DatedOutput ^ d3 = gcnew DatedOutput( "Dengue 3", _startDate, _stopDate, _serotypes[3]->PersonsViremic );
    DatedOutput ^ d4 = gcnew DatedOutput( "Dengue 4", _startDate, _stopDate, _serotypes[4]->PersonsViremic );

    Plot ^ p = gcnew Plot();
    p->Title = "Persons Viremic";
    p->AxisX = "Date";
    p->AxisY = "# of persons";
    p->PlotType = "Line";
    p->PrimaryOutputs->Add( d1 );
    p->PrimaryOutputs->Add( d2 );
    p->PrimaryOutputs->Add( d3 );
    p->PrimaryOutputs->Add( d4 );

    chart->Plots->Add( p );
  }

  else if( chartId == ChartIds::DensimPersonsWithVirus ) {
    DatedOutput ^ d1 = gcnew DatedOutput( "Dengue 1", _startDate, _stopDate, _serotypes[1]->PersonsWithVirus );
    DatedOutput ^ d2 = gcnew DatedOutput( "Dengue 2", _startDate, _stopDate, _serotypes[2]->PersonsWithVirus );
    DatedOutput ^ d3 = gcnew DatedOutput( "Dengue 3", _startDate, _stopDate, _serotypes[3]->PersonsWithVirus );
    DatedOutput ^ d4 = gcnew DatedOutput( "Dengue 4", _startDate, _stopDate, _serotypes[4]->PersonsWithVirus );

    Plot ^ p = gcnew Plot();
    p->Title = "Persons with Virus";
    p->AxisX = "Date";
    p->AxisY = "# of persons";
    p->PlotType = "Line";
    p->PrimaryOutputs->Add( d1 );
    p->PrimaryOutputs->Add( d2 );
    p->PrimaryOutputs->Add( d3 );
    p->PrimaryOutputs->Add( d4 );

    chart->Plots->Add( p );
  }

  else if( chartId == ChartIds::DensimGeneralSeroDistribution ) {
    ClassOutput ^ initialD1 = gcnew ClassOutput( "D1 - Initial", _serotypes[1]->InitialSeroDistribution );
    ClassOutput ^ initialD2 = gcnew ClassOutput( "D2 - Initial", _serotypes[2]->InitialSeroDistribution );
    ClassOutput ^ initialD3 = gcnew ClassOutput( "D3 - Initial", _serotypes[3]->InitialSeroDistribution );
    ClassOutput ^ initialD4 = gcnew ClassOutput( "D4 - Initial", _serotypes[4]->InitialSeroDistribution );

    ClassOutput ^ finalD1 = gcnew ClassOutput( "D1 - Final", _serotypes[1]->FinalSeroDistribution );
    ClassOutput ^ finalD2 = gcnew ClassOutput( "D2 - Final", _serotypes[2]->FinalSeroDistribution );
    ClassOutput ^ finalD3 = gcnew ClassOutput( "D3 - Final", _serotypes[3]->FinalSeroDistribution );
    ClassOutput ^ finalD4 = gcnew ClassOutput( "D4 - Final", _serotypes[4]->FinalSeroDistribution );

    Plot ^ p1 = gcnew Plot();
    p1->PlotType = "Column";
    p1->Title = "Dengue 1 - Initial and Final Serology Distribution";
    p1->AxisX = "Age Class";
    p1->AxisY = "# of individuals seropositive";
    p1->PrimaryOutputs->Add( initialD1 );
    p1->PrimaryOutputs->Add( finalD1 );

    Plot ^ p2 = gcnew Plot();
    p2->PlotType = "Column";
    p2->Title = "Dengue 2 - Initial and Final Serology Distribution";
    p2->AxisX = "Age Class";
    p2->AxisY = "# of individuals seropositive";
    p2->PrimaryOutputs->Add( initialD2 );
    p2->PrimaryOutputs->Add( finalD2 );

    Plot ^ p3 = gcnew Plot();
    p3->PlotType = "Column";
    p3->Title = "Dengue 3 - Initial and Final Serology Distribution";
    p3->AxisX = "Age Class";
    p3->AxisY = "# of individuals seropositive";
    p3->PrimaryOutputs->Add( initialD3 );
    p3->PrimaryOutputs->Add( finalD3 );

    Plot ^ p4 = gcnew Plot();
    p4->PlotType = "Column";
    p4->Title = "Dengue 4 - Initial and Final Serology Distribution";
    p4->AxisX = "Age Class";
    p4->AxisY = "# of individuals seropositive";
    p4->PrimaryOutputs->Add( initialD4 );
    p4->PrimaryOutputs->Add( finalD4 );

    chart->Plots->Add( p1 );
    chart->Plots->Add( p2 );
    chart->Plots->Add( p3 );
    chart->Plots->Add( p4 );
  }

  return chart;
}



Chart ^
DensimOutput::CreateDetailedSeroprevalenceChart( int seroClass )
{
  String ^ name = _seroClasses[seroClass];
  Chart ^ chart = gcnew Chart( name, false );

  DatedOutput ^ d1 = gcnew DatedOutput( "Dengue 1", _startDate, _stopDate, _serotypes[1]->ClassSpecificSeroprevalence[seroClass] );
  DatedOutput ^ d2 = gcnew DatedOutput( "Dengue 2", _startDate, _stopDate, _serotypes[2]->ClassSpecificSeroprevalence[seroClass] );
  DatedOutput ^ d3 = gcnew DatedOutput( "Dengue 3", _startDate, _stopDate, _serotypes[3]->ClassSpecificSeroprevalence[seroClass] );
  DatedOutput ^ d4 = gcnew DatedOutput( "Dengue 4", _startDate, _stopDate, _serotypes[4]->ClassSpecificSeroprevalence[seroClass] );

  Plot ^ p = gcnew Plot();
  p->PlotType = "Line";
  p->Title = "Age specific seroprevalence - " + name;
  p->AxisX = "name";
  p->AxisY = "% of individuals seropositive";
  p->MinYAxis = 0;
  p->MaxYAxis = 100;
  p->PrimaryOutputs->Add( d1 );
  p->PrimaryOutputs->Add( d2 );
  p->PrimaryOutputs->Add( d3 );
  p->PrimaryOutputs->Add( d4 );

  chart->Plots->Add( p );

  return chart;
}
