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



DensimOutput::DensimOutput( double humanDensity, DateTime startDate, DateTime stopDate )
: SimOutput(startDate, stopDate),
  _humanDensity(humanDensity),
  _serotypes(gcnew Collections::Generic::Dictionary<int, SerotypeOutput ^>())
{
  _numDays = (stopDate - startDate).Days + 1;
}



DensimOutput::~DensimOutput(void)
{}



Chart ^
DensimOutput::CreateChart( ChartInfo ^ chartInfo )
{
  Chart ^ chart = gcnew Chart( chartInfo->Name, chartInfo->Periodic );

  ChartIds chartId = chartInfo->ChartId;

  if( chartId == ChartIds::DensimMain ) {
    // counts
    array<double> ^ d1InfectedProportion = gcnew array<double>( _numDays );
    array<double> ^ d2InfectedProportion = gcnew array<double>( _numDays );
    array<double> ^ d3InfectedProportion = gcnew array<double>( _numDays );
    array<double> ^ d4InfectedProportion = gcnew array<double>( _numDays );

    // proportions
    for( int i = 0; i < _populationSize->Length; ++i ) {
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
    ClassOutput<int> ^ initial = gcnew ClassOutput<int>( "Initial age distribution", _initialAgeDistribution );
    ClassOutput<int> ^ final = gcnew ClassOutput<int>( "Final age distribution", _finalAgeDistribution );

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
    array<double> ^ areaData = gcnew array<double>( _numDays );
    for( int i = 0; i < _populationSize->Length; ++i ) {
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
    ClassOutput<int> ^ births = gcnew ClassOutput<int>( "Births by age class", _birthsByClass );
    ClassOutput<int> ^ deaths = gcnew ClassOutput<int>( "Deaths by age class", _deathsByClass );

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
    ClassOutput<int> ^ birthPercentages = gcnew ClassOutput<int>( "Birth percentages by age class", _birthsByClass );
    ClassOutput<int> ^ deathPercentages = gcnew ClassOutput<int>( "Death percentages by age class", _deathsByClass );

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
    array<double> ^ femalePerPersonData = gcnew array<double>( _numDays );
    for( int i = 0; i < _numDays; ++i ) {
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
  //  Plot ^ p = gcnew Plot();
  //  femaleMosquitoSurvival->PlotType = "Line";
  //  femaleMosquitoSurvival->Title = "Female mosquito survival";
  //  femaleMosquitoSurvival->AxisX = "Date";
  //  femaleMosquitoSurvival->AxisY = "Survival";
  //  femaleMosquitoSurvival->PrimaryOutputs->Add( densimOutput->Location[OutputInfos::DensimLocation::FemaleMosquitoSurvival] );

  //  chart->Plots->Add( femaleMosquitoSurvival );
  //}

  //else if( chartId == ChartIds::DensimFemaleMosquitoWetWeight ) {
  //  Plot ^ p = gcnew Plot();
  //  femaleMosquitoWetWeight->PlotType = "Line";
  //  femaleMosquitoWetWeight->Title = "Female mosquito wet weight";
  //  femaleMosquitoWetWeight->AxisX = "Date";
  //  femaleMosquitoWetWeight->AxisY = "Wet Weight (mg)";
  //  femaleMosquitoWetWeight->PrimaryOutputs->Add( densimOutput->Location[OutputInfos::DensimLocation::FemaleMosquitoWetWeight] );

  //  chart->Plots->Add( femaleMosquitoWetWeight );
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
    ClassOutput<int> ^ initialD1 = gcnew ClassOutput<int>( "Dengue 1", _serotypes[1]->InitialSeroDistribution );
    ClassOutput<int> ^ initialD2 = gcnew ClassOutput<int>( "Dengue 2", _serotypes[2]->InitialSeroDistribution );
    ClassOutput<int> ^ initialD3 = gcnew ClassOutput<int>( "Dengue 3", _serotypes[3]->InitialSeroDistribution );
    ClassOutput<int> ^ initialD4 = gcnew ClassOutput<int>( "Dengue 4", _serotypes[4]->InitialSeroDistribution );

    ClassOutput<int> ^ finalD1 = gcnew ClassOutput<int>( "Dengue 1", _serotypes[1]->FinalSeroDistribution );
    ClassOutput<int> ^ finalD2 = gcnew ClassOutput<int>( "Dengue 2", _serotypes[2]->FinalSeroDistribution );
    ClassOutput<int> ^ finalD3 = gcnew ClassOutput<int>( "Dengue 3", _serotypes[3]->FinalSeroDistribution );
    ClassOutput<int> ^ finalD4 = gcnew ClassOutput<int>( "Dengue 4", _serotypes[4]->FinalSeroDistribution );

    Plot ^ p1 = gcnew Plot();
    p1->PlotType = "Column";
    p1->Title = "Initial Serology Distribution";
    p1->AxisX = "Age Class";
    p1->AxisY = "# of individuals seropositive";

    Plot ^ p2 = gcnew Plot();
    p2->PlotType = "Column";
    p2->Title = "Final Serology Distribution";
    p2->AxisX = "Age Class";
    p2->AxisY = "# of individuals seropositive";

    chart->Plots->Add( p1 );
    chart->Plots->Add( p2 );
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
