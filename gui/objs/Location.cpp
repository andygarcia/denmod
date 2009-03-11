#include "StdAfx.h"
#include "Location.h"
#include "Weather.h"
#include "Util.h"
#include <numeric>

using namespace gui;



Location::Location(void)
: Name_(System::String::Empty),
  Notes_(System::String::Empty),
  Containers_(gcnew BindingList<gui::Container^>()),
  Controls_(gcnew BindingList<Control^>()),
  Weather_(gcnew WeatherData()),
  Biology_(gcnew BiologyParameters()),
  Demographics_(gcnew DemographicParameters()),
  Serology_(gcnew SerologyParameters()),
  Virology_(gcnew VirologyParameters()),
  InfectionIntroduction_(gcnew InfectionIntroductionParameters()),
  SequentialInfections_(gcnew SequentialInfectionParameters()),
  _isCimsimCompleted(false),
  CimsimOutput_(nullptr),
  _isDensimCompleted(false),
  DensimOutput_(nullptr),
  MosData_(NULL)
{
}



Location::~Location(void)
{
  delete MosData_;
}



input::Location *
Location::GetSimObject(void)
{
  input::Location * location = new input::Location();

  location->Name_ = toss(this->Name);
  location->Notes_ = toss(this->Notes);

  for each( gui::Container ^ ctnr in this->Containers ) {
    location->Containers_.push_back( ctnr->GetSimObject() );
  }

  for each( gui::Control ^ ctrl in this->Controls ) {
    location->Controls_.push_back( ctrl->GetSimObject() );
  }

  location->Biology_ = Biology_->GetSimObject();
  location->Weather_ = Weather_->GetSimObject();
  location->Demographics_ = Demographics_->GetSimObject();
  location->Serology_ = Serology_->GetSimObject();
  location->Virology_ = Virology_->GetSimObject();
  location->InfectionIntroduction_ = InfectionIntroduction_->GetSimObject();
  location->SequentialInfections_ = SequentialInfections_->GetSimObject();

  return location;
}



int
Location::ContainerNameCount( System::String ^ name )
{
  int nameCount = 0;

  for each( Container ^ c in Containers_ ) {
    if( c->Name == name ) {
      nameCount++;
    }
  }

  return nameCount;
}


  
void
Location::RenameContainer( gui::Container ^ container, System::String ^ previousName )
{
  for each( Control ^ c in Controls ) {
    System::Type ^ ctrlType = c->GetType();
    if( ctrlType == SourceReduction::typeid ) {
      SourceReduction ^ sr = (SourceReduction ^) c;
      for each( SourceReductionTarget ^ srt in sr->Targets ) {
        if( srt->Name == previousName ) {
          srt->Name = container->Name;
        }
      }
    }
    if( ctrlType == OvipositionExclusion::typeid ) {
      OvipositionExclusion ^ oe = (OvipositionExclusion^) c;
      for each( OvipositionExclusionTarget ^ oet in oe->Targets ) {
        if( oet->Name == previousName ) {
          oet->Name = container->Name;
        }
      }
    }
    if( ctrlType == EggDestruction::typeid ) {
      EggDestruction ^ ed = (EggDestruction^) c;
      for each( EggDestructionTarget ^ edt in ed->Targets ) {
        if( edt->Name == previousName ) {
          edt->Name = container->Name;
        }
      }
    }
    if( ctrlType == Larvicide::typeid ) {
      Larvicide ^ li = (Larvicide^) c;
      for each( LarvicideTarget ^ lit in li->Targets ) {
        if( lit->Name == previousName ) {
          lit->Name = container->Name;
        }
      }
    }
  }
}



bool
Location::RemoveContainer( gui::Container ^ container )
{
  // must also remove container from any targetted controls
  for each( Control ^ c in Controls ) {
    System::Type ^ ctrlType = c->GetType();
    if( ctrlType == SourceReduction::typeid ) {
      SourceReduction ^ sr = (SourceReduction ^) c;
      SourceReductionTarget ^ removeTarget;
      for each( SourceReductionTarget ^ srt in sr->Targets ) {
        if( srt->Name == container->Name ) {
          removeTarget = srt;
        }
      }
      sr->Targets->Remove( removeTarget );
    }
    if( ctrlType == OvipositionExclusion::typeid ) {
      OvipositionExclusion ^ oe = (OvipositionExclusion ^) c;
      OvipositionExclusionTarget ^ removeTarget;
      for each( OvipositionExclusionTarget ^ oet in oe->Targets ) {
        if( oet->Name == container->Name ) {
          removeTarget = oet;
        }
      }
      oe->Targets->Remove( removeTarget );
    }
    if( ctrlType == EggDestruction::typeid ) {
      EggDestruction ^ ed = (EggDestruction ^) c;
      EggDestructionTarget ^ removeTarget;
      for each( EggDestructionTarget ^ edt in ed->Targets ) {
        if( edt->Name == container->Name ) {
          removeTarget = edt;
        }
      }
      ed->Targets->Remove( removeTarget );
    }
    if( ctrlType == Larvicide::typeid ) {
      Larvicide ^ li = (Larvicide ^) c;
      LarvicideTarget ^ removeTarget;
      for each( LarvicideTarget ^ lt in li->Targets ) {
        if( lt->Name == container->Name ) {
          removeTarget = lt;
        }
      }
      li->Targets->Remove( removeTarget );
    }
  }

  return Containers_->Remove( container );
}



void
Location::AddControl( gui::Control ^ control )
{
  Controls_->Add( control );
}



bool
Location::RemoveControl( gui::Control ^ control )
{
  return Controls_->Remove( control );
}



int
Location::GetNumberOfControls( System::Type ^ controlType )
{
  int numControls = 0;
  
  for each( gui::Control ^ c in Controls_ ) {
    if( c->GetType() == controlType ) {
      numControls++;
    }
  }

  return numControls;
}



System::Void
Location::ResetBiology(System::Void)
{
  Biology->LoadDefaultValues();
}



void
Location::RunCimsim( bool usePop )
{
  // run cimsim, using all available weather
  DateTime startDate = Weather_->MinDate;
  DateTime stopDate = Weather_->MaxDate;

  RunCimsim( usePop, startDate, stopDate );
}



void
Location::RunCimsim( bool usePop, DateTime startDate, DateTime stopDate )
{
  int startYear = startDate.Year;
  int stopYear = stopDate.Year;

  if( !Weather_->IsWeatherYearAvailable(startYear) ) {
    throw gcnew System::ArgumentOutOfRangeException( "startYear", "startYear must have weather available" );
  }

  if( !Weather_->IsWeatherYearAvailable(stopYear) ) {
    throw gcnew System::ArgumentOutOfRangeException( "stopYear", "stopYear must have weather available" );
  }


  // clear any existing output
  if( _isCimsimCompleted ) {
    delete CimsimOutput;
    delete MosData_;
    System::GC::Collect();
  }


  // get unmanaged simulation object, representing input parameters for simulation
  input::Location * loc = GetSimObject();
  sim::cs::Simulation * cssim;

  // find start and stop dates for simulation
  boost::gregorian::date bStartDate = boost::gregorian::date( startYear, 1, 1 );
  boost::gregorian::date bStopDate = boost::gregorian::date( stopYear, 12, 31 );


  // run simulation, optionally using equillbrium population
  cssim = new sim::cs::Simulation( loc, bStartDate, bStopDate, usePop );
  cssim->Start();
  _isCimsimCompleted = true;

  // simulation complete, process output for use by gui and densim
  sim::output::CimsimOutput * cd = cssim->GetSimOutput();
  MosData_ = cd->GetMosData();

  // copy output to managed classes
  CimsimOutput_ = ProcessCimsimOutput( cd, startDate, stopDate );

  // delete input object, simulation, and managed output
  delete loc;
  delete cssim;
  delete cd;
}


array<double> ^
ArrayFromDoubleVector( std::vector<double> & vector )
{
  array<double> ^ values = gcnew array<double>(vector.size());

  for( unsigned int i = 0; i < vector.size(); ++i ) {
    values[i] = vector[i];
  }

  return values;
}



output::CimsimOutput ^
Location::ProcessCimsimOutput( sim::output::CimsimOutput * uco, DateTime startDate, DateTime stopDate )
{
  // managed cimsim output
  output::CimsimOutput ^ mco = gcnew output::CimsimOutput( Name_, startDate, stopDate );

  // get dates in boost format
  boost::gregorian::date bStartDate = boost::gregorian::date( startDate.Year, startDate.Month, startDate.Day );
  boost::gregorian::date bStopDate = boost::gregorian::date( stopDate.Year, stopDate.Month, stopDate.Day );

  // copy location data
  mco->TotalEggs = ArrayFromDoubleVector( uco->GetTotalEggs(bStartDate, bStopDate) );
  mco->TotalLarvae = ArrayFromDoubleVector( uco->GetTotalLarvae(bStartDate, bStopDate) );
  mco->TotalPupae = ArrayFromDoubleVector( uco->GetTotalPupae(bStartDate, bStopDate) );
  mco->Females = ArrayFromDoubleVector( uco->GetFemales(bStartDate, bStopDate) );
  mco->NewFemales = ArrayFromDoubleVector( uco->GetNewFemales(bStartDate, bStopDate) );
  mco->HostSeekingFemales = ArrayFromDoubleVector( uco->GetHostSeekingFemales(bStartDate, bStopDate) );
  mco->OvipositingFemales = ArrayFromDoubleVector( uco->GetOvipositingFemales(bStartDate, bStopDate) );
  mco->AverageFemaleWeight = ArrayFromDoubleVector( uco->GetAverageFemaleWeight(bStartDate, bStopDate) );
  mco->Oviposition = ArrayFromDoubleVector( uco->GetOviposition(bStartDate, bStopDate) );

  // copy weather data
  int numDays = (stopDate - startDate).Days + 1;
  mco->MaximumTemperature = gcnew array<double>(numDays);
  mco->AverageTemperature = gcnew array<double>(numDays);
  mco->MinimumTemperature = gcnew array<double>(numDays);
  mco->Rainfall = gcnew array<double>(numDays);
  mco->RelativeHumidity = gcnew array<double>(numDays);
  mco->SaturationDeficit = gcnew array<double>(numDays);

  for( DateTime dt = startDate; dt <= stopDate; dt = dt.AddDays(1) ) {
    int index = (dt - startDate).Days;
    WeatherDay ^ wd = Weather->GetWeather( dt );
    mco->MaximumTemperature[index] = wd->MaxTemp;
    mco->AverageTemperature[index] = wd->AvgTemp;
    mco->MinimumTemperature[index] = wd->MinTemp;
    mco->Rainfall[index] = wd->Rain;
    mco->RelativeHumidity[index] = wd->RelHum;
    mco->SaturationDeficit[index] = wd->SatDef;
  }


  // copy container data
  for each( Container ^ c in Containers ) {
    output::ContainerOutput ^ co = gcnew output::ContainerOutput( c->Name, c->Id );

    co->Depth = ArrayFromDoubleVector( uco->GetDepth(bStartDate, bStopDate, c->Id) );
    co->Food = ArrayFromDoubleVector( uco->GetFood(bStartDate, bStopDate, c->Id) );
    co->FoodAddition = ArrayFromDoubleVector( uco->GetFoodAddition(bStartDate, bStopDate, c->Id) );
    co->FoodConsumption = ArrayFromDoubleVector( uco->GetFoodConsumption(bStartDate, bStopDate, c->Id) );
    co->CadaverFoodContribution = ArrayFromDoubleVector( uco->GetCadaverFoodContribution(bStartDate, bStopDate, c->Id) );
    co->MaxTemp = ArrayFromDoubleVector( uco->GetMaxTemp(bStartDate, bStopDate, c->Id) );
    co->MinTemp = ArrayFromDoubleVector( uco->GetMinTemp(bStartDate, bStopDate, c->Id) );
    co->Eggs = ArrayFromDoubleVector( uco->GetEggs(bStartDate, bStopDate, c->Id) );
    co->Larvae = ArrayFromDoubleVector( uco->GetLarvae(bStartDate, bStopDate, c->Id) );
    co->LarvaeFasting = ArrayFromDoubleVector( uco->GetLarvaeFasting(bStartDate, bStopDate, c->Id) );
    co->LarvaeDeathFromFasting = ArrayFromDoubleVector( uco->GetLarvaeDeathFromFasting(bStartDate, bStopDate, c->Id) );
    co->Pupae = ArrayFromDoubleVector( uco->GetPupae(bStartDate, bStopDate, c->Id) );
    co->AvgDryPupWt = ArrayFromDoubleVector( uco->GetAvgDryPupWt(bStartDate, bStopDate, c->Id) );
    co->NewFemales = ArrayFromDoubleVector( uco->GetNewFemales(bStartDate, bStopDate, c->Id) );
    co->CumulativeFemales = ArrayFromDoubleVector( uco->GetCumulativeFemales(bStartDate, bStopDate, c->Id) );
    co->Oviposition = ArrayFromDoubleVector( uco->GetOviposition(bStartDate, bStopDate, c->Id) );
    co->TotalDensity = ArrayFromDoubleVector( uco->GetTotalDensity(bStartDate, bStopDate, c->Id) );
    co->UntreatedDensity = ArrayFromDoubleVector( uco->GetUntreatedDensity(bStartDate, bStopDate, c->Id) );
    co->TreatedDensity = ArrayFromDoubleVector( uco->GetTreatedDensity(bStartDate, bStopDate, c->Id) );
    co->ExcludedDensity = ArrayFromDoubleVector( uco->GetExcludedDensity(bStartDate, bStopDate, c->Id) );
    co->EggDevelopment = ArrayFromDoubleVector( uco->GetEggDevelopment(bStartDate, bStopDate, c->Id) );
    co->LarvaeDevelopment = ArrayFromDoubleVector( uco->GetLarvaeDevelopment(bStartDate, bStopDate, c->Id) );
    co->PupaeDevelopment = ArrayFromDoubleVector( uco->GetPupaeDevelopment(bStartDate, bStopDate, c->Id) );

    mco->Containers[c->Id] = co;
  }

  return mco;
}



void
Location::RunFoodFitIteration( int numberOfRuns, DateTime surveyBegin, DateTime surveyEnd )
{
  // convert to boost dates
  boost::gregorian::date surveyStartDate( surveyBegin.Year, surveyBegin.Month, surveyBegin.Day );
  boost::gregorian::date surveyStopDate( surveyEnd.Year, surveyEnd.Month, surveyEnd.Day );

  // create simulation
  input::Location * loc = GetSimObject();
  sim::cs::FoodFitSimulation * foodSim = new sim::cs::FoodFitSimulation( loc, surveyStartDate, surveyStopDate );
  std::map<std::string,double> & predictions = foodSim->DoIteration( numberOfRuns );

  // save predicted observations
  for each( gui::Container ^ c in Containers_ ) {
    c->PredictedPerContainer = predictions[toss(c->Name)];
  }

  delete loc;
}



void
Location::BeginFoodFit()
{
  for each( Container ^ c in Containers_ ) {
    c->BeginFoodFit();
  }
}



void
Location::EndFoodFit(bool saveFitData)
{
  for each( Container ^ c in Containers_ ) {
    c->EndFoodFit( saveFitData );
  }
}



FoodFitTotals ^
Location::GetFoodFitTotals(void)
{
  // tabulate food fit totals for further use in fitting
  double totalObserved = 0;
  double totalPredicted = 0;
  for each( Container ^ c in Containers_ ) {
    totalObserved = totalObserved + c->ObservedPerHectare;
    totalPredicted = totalPredicted + c->PredictedPerHectare;
  }
  double difference = totalObserved - totalPredicted;
  double ratio = totalObserved / totalPredicted;

  FoodFitTotals ^ fft = gcnew FoodFitTotals();
  fft->TotalObservedPupaePerHa = totalObserved;
  fft->TotalPredictedPupaePerHa = totalPredicted;
  fft->Difference = difference;
  fft->Ratio = ratio;

  return fft;
}



void
Location::RunDensim(void)
{
  // run densim using all available cimsim data
  DateTime startDate;
  DateTime stopDate;

  throw gcnew System::InvalidOperationException( "RunDensim() not implemented" );
}



void
Location::RunDensim( DateTime startDate, DateTime stopDate )
{
  int startYear = startDate.Year;
  int stopYear = stopDate.Year;

  if( !Weather_->IsWeatherYearAvailable(startYear) ) {
    throw gcnew System::ArgumentOutOfRangeException( "startYear", "startYear must have weather available" );
  }

  if( !Weather_->IsWeatherYearAvailable(stopYear) ) {
    throw gcnew System::ArgumentOutOfRangeException( "stopYear", "stopYear must have weather available" );
  }

  if( !_isCimsimCompleted ) {
    throw gcnew System::Exception( "IsCimsimCompleted == false.  No cimsim data exists for densim." );
  }

  if( _isDensimCompleted ) {
  }

  // TODO - why regenerate a new object - especially if old one was what was used for CIMSiM
  // possibly even different?
  const input::Location * loc = GetSimObject();

  // find start and stop dates for simulation
  boost::gregorian::date bStartDate = boost::gregorian::date( startYear, 1, 1 );
  boost::gregorian::date bStopDate = boost::gregorian::date( stopYear, 12, 31 );

  sim::ds::Simulation * dssim = new sim::ds::Simulation( loc, MosData_ );
  dssim->Start( bStartDate, bStopDate );
  _isDensimCompleted = true;

  // simulation complete, process output for use by gui
  sim::output::DensimOutput * dd = dssim->GetSimOutput();
  DensimOutput_ = ProcessDensimOutput( dd, startDate, stopDate );

  delete loc;     // delete input object (no longer needed, regenerated on next run)
  delete dssim;   // delete sim and its output (now processed into managed data)
}


array<double> ^
DoubleArrayFromIntVector( std::vector<int> & vector )
{
  array<double> ^ values = gcnew array<double>(vector.size());

  for( unsigned int i = 0; i < vector.size(); ++i ) {
    values[i] = (vector[i]);
  }

  return values;
}



output::DensimOutput ^
Location::ProcessDensimOutput( sim::output::DensimOutput * udo, DateTime startDate, DateTime stopDate )
{
  // managed cimsim output
  output::DensimOutput ^ mdo = gcnew output::DensimOutput( Name_, Demographics_->HumanHostDensity, startDate, stopDate );

  // get dates in boost format
  boost::gregorian::date bStartDate = boost::gregorian::date( startDate.Year, startDate.Month, startDate.Day );
  boost::gregorian::date bStopDate = boost::gregorian::date( stopDate.Year, stopDate.Month, stopDate.Day );

  // copy data
  mdo->InitialAgeDistribution = DoubleArrayFromIntVector( udo->GetInitialAgeDistribution() );
  mdo->FinalAgeDistribution = DoubleArrayFromIntVector( udo->GetFinalAgeDistribution() );
  mdo->BirthsByClass = DoubleArrayFromIntVector( udo->GetBirths() );
  mdo->DeathsByClass = DoubleArrayFromIntVector( udo->GetDeaths() );
  mdo->PopulationSize = DoubleArrayFromIntVector( udo->GetPopulation() );
  mdo->FemaleMosquitoesInSimulationArea = ArrayFromDoubleVector( udo->GetMosqTotal() );
  mdo->PotentiallyInfectiveBites = DoubleArrayFromIntVector( udo->GetPotentiallyInfectiveBites() );

  for( int serotype = 1; serotype <= 4; ++serotype ) {
    output::SerotypeOutput ^ so = gcnew output::SerotypeOutput();

    so->EipDevelopmentRate = ArrayFromDoubleVector( udo->GetEipDevelopmentRate(serotype) );
    so->InfectiveMosquitoes = ArrayFromDoubleVector( udo->GetInfectiveMosquitoes(serotype) );
    so->PersonsIncubating  = ArrayFromDoubleVector( udo->GetPersonsIncubating(serotype) );
    so->PersonsViremic = ArrayFromDoubleVector( udo->GetPersonsViremic(serotype) );
    so->PersonsWithVirus = ArrayFromDoubleVector( udo->GetPersonsWithVirus(serotype) );
    so->InitialSeroDistribution = DoubleArrayFromIntVector( udo->GetInitialSeroDistribution(serotype) );
    so->FinalSeroDistribution = DoubleArrayFromIntVector( udo->GetFinalSeroDistribution(serotype) );

    for( int seroClass = 1; seroClass <= 23; ++seroClass ) {
      so->ClassSpecificSeroprevalence[seroClass] = ArrayFromDoubleVector( udo->GetDetailedSeroprevalence(seroClass, serotype) );
    }

    mdo->Serotypes[serotype] = so;
  }

  return mdo;
}
