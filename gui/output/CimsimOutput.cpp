#include "stdafx.h"
#include "Enums.h"
#include "CimsimOutput.h"

using namespace gui::output;



CimsimOutput::CimsimOutput( String ^ name, DateTime startDate, DateTime stopDate )
: SimOutput(name, startDate, stopDate),
  _containers(gcnew Collections::Generic::Dictionary<int,ContainerOutput^>())
{}



CimsimOutput::~CimsimOutput(void)
{}



void
CimsimOutput::SaveToDisk( IO::DirectoryInfo ^ di )
{
  // save all cimsim output into target directory
  System::String ^ directory = di->FullName;

  // write location file
  System::String ^ locationFile = directory + "\\CIMSiM - Location Totals.xml";
  System::IO::FileStream ^ fs = gcnew System::IO::FileStream( locationFile, System::IO::FileMode::Create );
  System::IO::StreamWriter ^ sw = gcnew System::IO::StreamWriter( fs );
  WriteLocationWorkbook( sw );
  sw->Close();

  // write container file
  System::String ^ containerFile = directory + "\\CIMSiM - Containers.xml";
  fs = gcnew System::IO::FileStream( containerFile, System::IO::FileMode::Create );
  sw = gcnew System::IO::StreamWriter( fs );
  WriteContainerWorkbook( sw );
  sw->Close();
}



void
CimsimOutput::WriteLocationWorkbook( IO::StreamWriter ^ sw )
{
  // first pull data for workbook
  List<String^> ^ headers = gcnew List<String^>();
  List<array<double>^> ^ data = gcnew List<array<double>^>();

  // create headers (including date)
  headers->Add( "Date" );
  headers->Add( "Total Eggs" );
  headers->Add( "Total Larvae" );
  headers->Add( "Total Pupae" );
  headers->Add( "Total Females" );
  headers->Add( "New Females" );
  headers->Add( "Host Seeking Females" );
  headers->Add( "Ovipositing Females" );
  headers->Add( "Average Female Wet Weight" );
  headers->Add( "Oviposition" );
  headers->Add( "Maximum Temperature" );
  headers->Add( "Average Temperature" );
  headers->Add( "Minimum Temperature" );
  headers->Add( "Rainfall" );
  headers->Add( "Relative Humidity" );
  headers->Add( "Saturation Deficit" );

  // create data
  data->Add( _totalEggs );
  data->Add( _totalLarvae );
  data->Add( _totalPupae );
  data->Add( _females);
  data->Add( _newFemales );
  data->Add( _hostSeekingFemales );
  data->Add( _ovipositingFemales );
  data->Add( _averageFemaleWeight );
  data->Add( _oviposition );
  data->Add( _maximumTemperature );
  data->Add( _averageTemperature );
  data->Add( _minimumTemperature );
  data->Add( _rainfall );
  data->Add( _relativeHumidity );
  data->Add( _saturationDeficit );

  // second write actual xml output
  WriteWorkbookOpen( sw );
  WriteWorkbookStyles( sw );
  WriteDailyWorksheet( sw, "Location", headers, _dates, data );
  WriteWorkbookClose( sw );
}


void
CimsimOutput::WriteContainerWorkbook( IO::StreamWriter ^ sw )
{
  WriteWorkbookOpen( sw );
  WriteWorkbookStyles( sw );
  WriteContainerWorksheets( sw );
  WriteWorkbookClose( sw );
}



void
CimsimOutput::WriteContainerWorksheets( IO::StreamWriter ^ sw )
{
  // first create headers for each container's worksheet
  List<String^> ^ headers = gcnew List<String^>();
  headers->Add( "Date" );
  headers->Add( "Depth" );
  headers->Add( "Food" );
  headers->Add( "Food Addition" );
  headers->Add( "Food Consumption" );
  headers->Add( "Cadaver Food Contribution" );
  headers->Add( "Maximum Temperature" );
  headers->Add( "Minimum Temperature" );
  headers->Add( "Eggs" );
  headers->Add( "Larvae" );
  headers->Add( "Larvae Fasting" );
  headers->Add( "Larvae Death From Fasting" );
  headers->Add( "Pupae" );
  headers->Add( "Average Pupal Weight" );
  headers->Add( "New Females" );
  headers->Add( "Cumulative Females" );
  headers->Add( "Oviposition" );
  headers->Add( "Untreated Density" );
  headers->Add( "Treated Density" );
  headers->Add( "Excluded Density" );
  headers->Add( "Egg Development Rate" );
  headers->Add( "Larvae Development Rate" );
  headers->Add( "Pupae Development Rate" );

  // now process each container's output
  for each( ContainerOutput ^ co in _containers->Values ) {

    // collect this container's data
    List<array<double>^> ^ data = gcnew List<array<double>^>();
    data->Add( co->Depth );
    data->Add( co->Food );
    data->Add( co->FoodAddition );
    data->Add( co->FoodConsumption );
    data->Add( co->CadaverFoodContribution );
    data->Add( co->MaxTemp );
    data->Add( co->MinTemp );
    data->Add( co->Eggs );
    data->Add( co->Larvae );
    data->Add( co->LarvaeFasting );
    data->Add( co->LarvaeDeathFromFasting );
    data->Add( co->Pupae );
    data->Add( co->AvgDryPupWt );
    data->Add( co->NewFemales );
    data->Add( co->CumulativeFemales );
    data->Add( co->Oviposition );
    data->Add( co->UntreatedDensity );
    data->Add( co->TreatedDensity );
    data->Add( co->ExcludedDensity );
    data->Add( co->EggDevelopment );
    data->Add( co->LarvaeDevelopment );
    data->Add( co->PupaeDevelopment );

    // write this container's data
    WriteDailyWorksheet( sw, co->Name, headers, _dates, data );
  }
}



Chart ^
CimsimOutput::CreateLocationChart( ChartIds chartId )
{
  Chart ^ chart;

  if( chartId == ChartIds::CimsimMain ) {
    DatedOutput ^ totalEggs = gcnew DatedOutput( "Total Eggs", _startDate, _stopDate, _totalEggs );
    DatedOutput ^ totalLarvae = gcnew DatedOutput( "Total Larvae", _startDate, _stopDate, _totalLarvae );
    DatedOutput ^ totalPupae = gcnew DatedOutput( "Total Pupae", _startDate, _stopDate, _totalPupae );
    DatedOutput ^ females = gcnew DatedOutput( "Females", _startDate, _stopDate, _females );

    Plot ^ p = gcnew Plot();
    p->PlotType = "Line";
    p->Title = "All life stages";
    p->AxisX = "Date";
    p->AxisY = "# per ha";
    p->PrimaryOutputs->Add( totalEggs );
    p->PrimaryOutputs->Add( totalLarvae );
    p->PrimaryOutputs->Add( totalPupae );
    p->PrimaryOutputs->Add( females );

    chart = gcnew Chart( "CIMSiM", true );
    chart->Plots->Add( p );
  }

  else if( chartId == ChartIds::CimsimMainScaled ) {
    array<double> ^ adjustedEggs = gcnew array<double>( _numberOfDays );
    array<double> ^ adjustedLarvae = gcnew array<double>( _numberOfDays );

    // adjust eggs and larvae to 100's count similar to CS 1.0 main output
    for( int i = 0; i < _numberOfDays; ++i ) {
      adjustedEggs[i] = _totalEggs[i] / 100.0;
      adjustedLarvae[i] = _totalLarvae[i] / 100.0;
    }

    DatedOutput ^ totalEggs = gcnew DatedOutput( "Total Eggs (100)", _startDate, _stopDate, adjustedEggs );
    DatedOutput ^ totalLarvae = gcnew DatedOutput( "Total Larvae (100)", _startDate, _stopDate, adjustedLarvae );
    DatedOutput ^ totalPupae = gcnew DatedOutput( "Total Pupae", _startDate, _stopDate, _totalPupae );
    DatedOutput ^ females = gcnew DatedOutput( "Females", _startDate, _stopDate, _females );

    Plot ^ p = gcnew Plot();
    p->PlotType = "Line";
    p->Title = "All life stages";
    p->AxisX = "Date";
    p->AxisY = "# per ha";
    p->PrimaryOutputs->Add( totalEggs );
    p->PrimaryOutputs->Add( totalLarvae );
    p->PrimaryOutputs->Add( totalPupae );
    p->PrimaryOutputs->Add( females );

    chart = gcnew Chart( "CIMSiM", true );
    chart->Plots->Add( p );
  }

  else if( chartId == ChartIds::CimsimFemales ) {
    DatedOutput ^ females = gcnew DatedOutput( "Females", _startDate, _stopDate, _females );
    DatedOutput ^ newFemales = gcnew DatedOutput( "New Females", _startDate, _stopDate, _newFemales );
    DatedOutput ^ hostSeekingFemales = gcnew DatedOutput( "Host Seeking Females", _startDate, _stopDate, _hostSeekingFemales );
    DatedOutput ^ ovipositingFemales = gcnew DatedOutput( "Ovipositing Females", _startDate, _stopDate, _ovipositingFemales );

    Plot ^ p = gcnew Plot();
    p->PlotType = "Line";
    p->Title = "Females per Hectare";
    p->AxisX = "Date";
    p->AxisY = "# of females per ha";
    p->PrimaryOutputs->Add( females );
    p->PrimaryOutputs->Add( newFemales );
    p->PrimaryOutputs->Add( hostSeekingFemales );
    p->PrimaryOutputs->Add( ovipositingFemales );

    chart = gcnew Chart( "Females per hectare", true );
    chart->Plots->Add( p );
  }

  else if( chartId == ChartIds::CimsimAverageFemaleWetWeight ) {
    DatedOutput ^ weight = gcnew DatedOutput( "Average female wet weight", _startDate, _stopDate, _averageFemaleWeight );

    Plot ^ p = gcnew Plot();
    p->PlotType = "Line";
    p->Title = "Average female wet weight";
    p->AxisX = "Date";
    p->AxisY = "mg";
    p->PrimaryOutputs->Add( weight );

    chart = gcnew Chart( "Average female wet weight", true );
    chart->Plots->Add( p );
  }

  else if( chartId == ChartIds::CimsimOviposition ) {
    DatedOutput ^ oviposition = gcnew DatedOutput( "Oviposition", _startDate, _stopDate, _oviposition );

    Plot ^ p = gcnew Plot();
    p->PlotType = "Line";
    p->Title = "Oviposition";
    p->AxisX = "Date";
    p->AxisY = "# of eggs";
    p->PrimaryOutputs->Add( oviposition );

    chart = gcnew Chart( "Oviposition", true );
    chart->Plots->Add( p );
  }

  else if( chartId == ChartIds::CimsimWeather ) {
    DatedOutput ^ maxTemp = gcnew DatedOutput( "Maximum Temperature", _startDate, _stopDate, _maximumTemperature );
    DatedOutput ^ avgTemp = gcnew DatedOutput( "Average Temperature", _startDate, _stopDate, _averageTemperature );
    DatedOutput ^ minTemp = gcnew DatedOutput( "Minimum Temperature", _startDate, _stopDate, _minimumTemperature );
    DatedOutput ^ rainFall = gcnew DatedOutput( "Rainfall", _startDate, _stopDate, _rainfall );
    DatedOutput ^ relHum = gcnew DatedOutput( "Relative Humidity", _startDate, _stopDate, _relativeHumidity );
    DatedOutput ^ satDef = gcnew DatedOutput( "Saturation Deficit", _startDate, _stopDate, _saturationDeficit );

    Plot ^ p = gcnew Plot();
    p->PlotType = "Line";
    p->Title = "Weather";
    p->AxisX = "Date";
    p->AxisY = "°C / mm / mbars";
    p->PrimaryOutputs->Add( maxTemp );
    p->PrimaryOutputs->Add( avgTemp );
    p->PrimaryOutputs->Add( minTemp );
    p->PrimaryOutputs->Add( rainFall );
    p->PrimaryOutputs->Add( relHum );
    p->PrimaryOutputs->Add( satDef );

    chart = gcnew Chart( "Weather", true );
    chart->Plots->Add( p );
  }

  else {
    throw gcnew InvalidOperationException( "chartId not found." );
  }

  return chart;
}



Chart ^
CimsimOutput::CreateContainerChart( ChartIds chartId, int containerId )
{
  if( !_containers->ContainsKey( containerId ) ) {
    throw gcnew InvalidOperationException( "containerId not found" );
  }

  Chart ^ chart;

  if( chartId == ChartIds::ContainerDensity ) {
    DatedOutput ^ untreated = gcnew DatedOutput( "Untreated Density", _startDate, _stopDate, _containers[containerId]->UntreatedDensity );
    DatedOutput ^ treated = gcnew DatedOutput( "Treated Density", _startDate, _stopDate, _containers[containerId]->TreatedDensity );
    DatedOutput ^ excluded = gcnew DatedOutput( "Excluded Density", _startDate, _stopDate, _containers[containerId]->ExcludedDensity );

    Plot ^ p = gcnew Plot();
    p->PlotType = "Line";
    p->Title = "Container densities";
    p->AxisX = "Date";
    p->AxisY = "# of containers per ha";
    p->PrimaryOutputs->Add( untreated );
    p->PrimaryOutputs->Add( treated );
    p->PrimaryOutputs->Add( excluded );

    chart = gcnew Chart( "Container densities", true );
    chart->Plots->Add( p );
  }

  else if( chartId == ChartIds::ContainerDepth ) {
    DatedOutput ^ depth = gcnew DatedOutput( "Water depth", _startDate, _stopDate, _containers[containerId]->Depth );

    Plot ^ p = gcnew Plot();
    p->PlotType = "Line";
    p->Title = "Water Depth";
    p->AxisX = "Date";
    p->AxisY = "cm";
    p->PrimaryOutputs->Add( depth );

    chart = gcnew Chart( "Water Depth", true );
    chart->Plots->Add( p );
  }

  else if( chartId == ChartIds::ContainerFood ) {
    DatedOutput ^ food = gcnew DatedOutput( "Food", _startDate, _stopDate, _containers[containerId]->Food );
    DatedOutput ^ foodAddition = gcnew DatedOutput( "Food Additions", _startDate, _stopDate, _containers[containerId]->FoodAddition );
    DatedOutput ^ foodConsumption = gcnew DatedOutput( "Food Consumption", _startDate, _stopDate, _containers[containerId]->FoodConsumption );
    DatedOutput ^ cadaverFoodContribution = gcnew DatedOutput( "Cadaver Contributions", _startDate, _stopDate, _containers[containerId]->CadaverFoodContribution );

    Plot ^ p = gcnew Plot();
    p->PlotType = "Line";
    p->Title = "Food";
    p->AxisX = "Date";
    p->AxisY = "mg";
    p->PrimaryOutputs->Add( food );
    p->PrimaryOutputs->Add( foodAddition );
    p->PrimaryOutputs->Add( foodConsumption );
    p->PrimaryOutputs->Add( cadaverFoodContribution );

    chart = gcnew Chart( "Food", true );
    chart->Plots->Add( p );
  }

  else if( chartId == ChartIds::ContainerWaterTemperature ) {
    DatedOutput ^ maxTemp = gcnew DatedOutput( "Maximum Temperature", _startDate, _stopDate, _containers[containerId]->MaxTemp );
    DatedOutput ^ minTemp = gcnew DatedOutput( "Minimum Temperature", _startDate, _stopDate, _containers[containerId]->MinTemp );

    Plot ^ p = gcnew Plot();
    p->PlotType = "Line";
    p->Title = "Water temperatures";
    p->AxisX = "Date";
    p->AxisY = "°C";
    p->PrimaryOutputs->Add( maxTemp );
    p->PrimaryOutputs->Add( minTemp );

    chart = gcnew Chart( "Water temperatures", true );
    chart->Plots->Add( p );
  }

  else if( chartId == ChartIds::ContainerImmatures ) {
    DatedOutput ^ eggs = gcnew DatedOutput( "Eggs", _startDate, _stopDate, _containers[containerId]->Eggs );
    DatedOutput ^ larvae = gcnew DatedOutput( "Larvae", _startDate, _stopDate, _containers[containerId]->Larvae );
    DatedOutput ^ pupae = gcnew DatedOutput( "Pupae", _startDate, _stopDate, _containers[containerId]->Pupae );

    Plot ^ p1 = gcnew Plot();
    p1->PlotType = "Line";
    p1->Title = "Eggs";
    p1->AxisX = "Date";
    p1->AxisY = "# of eggs";
    p1->PrimaryOutputs->Add( eggs );

    Plot ^ p2 = gcnew Plot();
    p2->PlotType = "Line";
    p2->Title = "Larvae";
    p2->AxisX = "Date";
    p2->AxisY = "# of larvae";
    p2->PrimaryOutputs->Add( larvae );

    Plot ^ p3 = gcnew Plot();
    p3->PlotType = "Line";
    p3->Title = "Pupae";
    p3->AxisX = "Date";
    p3->AxisY = "# of pupae";
    p3->PrimaryOutputs->Add( pupae );

    chart = gcnew Chart( "Immature lifestages", true );
    chart->Plots->Add( p1 );
    chart->Plots->Add( p2 );
    chart->Plots->Add( p3 );
  }

  else if( chartId == ChartIds::ContainerEggs ) {
    DatedOutput ^ eggs = gcnew DatedOutput( "Eggs", _startDate, _stopDate, _containers[containerId]->Eggs );

    Plot ^ p = gcnew Plot();
    p->PlotType = "Line";
    p->Title = "eggs";
    p->AxisX = "Date";
    p->AxisY = "# of eggs";
    p->PrimaryOutputs->Add( eggs );

    chart = gcnew Chart( "Eggs", true );
    chart->Plots->Add( p );
  }

  else if( chartId == ChartIds::ContainerLarvae ) {
    DatedOutput ^ larvae = gcnew DatedOutput( "Larvae", _startDate, _stopDate, _containers[containerId]->Larvae );

    Plot ^ p = gcnew Plot();
    p->PlotType = "Line";
    p->Title = "larvae";
    p->AxisX = "Date";
    p->AxisY = "# of larvae";
    p->PrimaryOutputs->Add( larvae );

    chart = gcnew Chart( "Larvae", true );
    chart->Plots->Add( p );
  }


  else if( chartId == ChartIds::ContainerPupae ) {
    DatedOutput ^ pupae = gcnew DatedOutput( "Pupae", _startDate, _stopDate, _containers[containerId]->Pupae );

    Plot ^ p = gcnew Plot();
    p->PlotType = "Line";
    p->Title = "pupae";
    p->AxisX = "Date";
    p->AxisY = "# of pupae";
    p->PrimaryOutputs->Add( pupae );

    chart = gcnew Chart( "Pupae", true );
    chart->Plots->Add( p );
  }

  else if( chartId == ChartIds::ContainerAveragePupalWeight ) {
    DatedOutput ^ weight = gcnew DatedOutput( "Average Dry Pupal Weight", _startDate, _stopDate, _containers[containerId]->AvgDryPupWt );

    Plot ^ p = gcnew Plot();
    p->PlotType = "Line";
    p->Title = "Average dry pupal weight";
    p->AxisX = "Date";
    p->AxisY = "mg";
    p->PrimaryOutputs->Add( weight );

    chart = gcnew Chart( "Average dry pupal weight", true );
    chart->Plots->Add( p );
  }

  else if( chartId == ChartIds::ContainerNewFemales ) {
    DatedOutput ^ newFemales = gcnew DatedOutput( "New Females", _startDate, _stopDate, _containers[containerId]->NewFemales );

    Plot ^ p = gcnew Plot();
    p->PlotType = "Line";
    p->Title = "New females";
    p->AxisX = "Date";
    p->AxisY = "# of new females";
    p->PrimaryOutputs->Add( newFemales );

    chart = gcnew Chart( "New females", true );
    chart->Plots->Add( p );
  }
  
  else if( chartId == ChartIds::ContainerCumulativeFemales ) {
    DatedOutput ^ cumFemales = gcnew DatedOutput( "Cumulative Females", _startDate, _stopDate, _containers[containerId]->CumulativeFemales );

    Plot ^ p = gcnew Plot();
    p->PlotType = "Line";
    p->Title = "Cumulative females";
    p->AxisX = "Date";
    p->AxisY = "# of cumulative females";
    p->PrimaryOutputs->Add( cumFemales );

    chart = gcnew Chart( "Cumulative females", true );
    chart->Plots->Add( p );
  }

  else if( chartId == ChartIds::ContainerOviposition ) {
    DatedOutput ^ oviposition = gcnew DatedOutput( "Oviposition Females", _startDate, _stopDate, _containers[containerId]->Oviposition );

    Plot ^ p = gcnew Plot();
    p->Title = "Oviposition";
    p->AxisX = "Date";
    p->AxisY = "# of eggs";
    p->PlotType = "Line";
    p->PrimaryOutputs->Add( oviposition );

    chart = gcnew Chart( "Oviposition", true );
    chart->Plots->Add( p );
  }

  else if( chartId == ChartIds::ContainerDevelopmentRates ) {
    DatedOutput ^ eggDev = gcnew DatedOutput( "Egg Development Rate", _startDate, _stopDate, _containers[containerId]->EggDevelopment );
    DatedOutput ^ larvaeDev = gcnew DatedOutput( "Larvae Development Rate", _startDate, _stopDate, _containers[containerId]->LarvaeDevelopment );
    DatedOutput ^ pupaeDev = gcnew DatedOutput( "Pupae Development Rate", _startDate, _stopDate, _containers[containerId]->PupaeDevelopment );

    Plot ^ p = gcnew Plot();
    p->Title = "Development Rates";
    p->AxisX = "Date";
    p->AxisY = "Development Rate";
    p->PlotType = "Line";
    p->PrimaryOutputs->Add( eggDev );
    p->PrimaryOutputs->Add( larvaeDev );
    p->PrimaryOutputs->Add( pupaeDev );

    chart = gcnew Chart( "Development rates", true );
    chart->Plots->Add( p );
  }

  else {
    throw gcnew InvalidOperationException( "chartId not found." );
  }

  return chart;
}
