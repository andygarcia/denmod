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
  _isDensimCompleted(false),
  MosData_(NULL),
  DensimData_(NULL),
  DensimSeries_(gcnew OutputSeries()),
  SerotypeSeries_(gcnew SerotypeOutputSeries())
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
    input::Control * simCtrl = ctrl->GetSimObject();
    location->Controls_.push_back( simCtrl );
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
  const input::Location * loc = GetSimObject();
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



void CopyVectorToOutput( std::vector<double> & vector, output::Output ^ output )
{
  for( unsigned int i = 0; i < vector.size(); ++i ) {
    output->Data->Add( vector[i] );
  }

}



output::CimsimOutput ^
Location::ProcessCimsimOutput( sim::output::CimsimOutput * uco, DateTime startDate, DateTime stopDate )
{
  // managed cimsim output
  output::CimsimOutput ^ mco = gcnew output::CimsimOutput( startDate, stopDate );

  // get dates in boost format
  boost::gregorian::date bStartDate = boost::gregorian::date( startDate.Year, startDate.Month, startDate.Day );
  boost::gregorian::date bStopDate = boost::gregorian::date( stopDate.Year, stopDate.Month, stopDate.Day );

  // copy data
  CopyVectorToOutput( uco->GetTotalEggs(bStartDate, bStopDate), mco->Location[(int)output::OutputTypes::Cimsim::Location::TotalEggs] );
  CopyVectorToOutput( uco->GetTotalLarvae(bStartDate, bStopDate), mco->Location[(int)output::OutputTypes::Cimsim::Location::TotalLarvae] );
  CopyVectorToOutput( uco->GetTotalPupae(bStartDate, bStopDate), mco->Location[(int)output::OutputTypes::Cimsim::Location::TotalPupae] );
  CopyVectorToOutput( uco->GetFemales(bStartDate, bStopDate), mco->Location[(int)output::OutputTypes::Cimsim::Location::TotalFemales] );
  CopyVectorToOutput( uco->GetNewFemales( bStartDate, bStopDate ), mco->Location[(int)output::OutputTypes::Cimsim::Location::NewFemales] );
  CopyVectorToOutput( uco->GetAverageFemaleWeight(bStartDate, bStopDate), mco->Location[(int)output::OutputTypes::Cimsim::Location::AverageFemaleWeight] );
  CopyVectorToOutput( uco->GetOviposition(bStartDate, bStopDate), mco->Location[(int)output::OutputTypes::Cimsim::Location::Oviposition] );

  // TODO - should we cache weather information again? hmmm, dunno, would be useful for comparisons where different weather was used
  // ok, how to seed this?
  //MaximumTemperature,
  //AverageTemperature,
  //MinimumTemperature,
  //Rainfall,
  //RelativeHumidity,
  //SaturationDeficit

  for each( Container ^ c in Containers ) {
    int id = c->Id;

    mco->AddContainerType( id );

    CopyVectorToOutput( uco->GetDepth(bStartDate, bStopDate, id), mco->Containers[id][(int)gui::output::OutputTypes::Cimsim::Container::Depth] );
    CopyVectorToOutput( uco->GetFood(bStartDate, bStopDate, id), mco->Containers[id][(int)gui::output::OutputTypes::Cimsim::Container::Food] );
    CopyVectorToOutput( uco->GetMaxTemp(bStartDate, bStopDate, id), mco->Containers[id][(int)gui::output::OutputTypes::Cimsim::Container::MaximumTemperature] );
    CopyVectorToOutput( uco->GetMinTemp(bStartDate, bStopDate, id), mco->Containers[id][(int)gui::output::OutputTypes::Cimsim::Container::MinimumTemperature] );
    CopyVectorToOutput( uco->GetEggs(bStartDate, bStopDate, id), mco->Containers[id][(int)gui::output::OutputTypes::Cimsim::Container::Eggs] );
    CopyVectorToOutput( uco->GetLarvae(bStartDate, bStopDate, id), mco->Containers[id][(int)gui::output::OutputTypes::Cimsim::Container::Larvae] );
    CopyVectorToOutput( uco->GetPupae(bStartDate, bStopDate, id), mco->Containers[id][(int)gui::output::OutputTypes::Cimsim::Container::Pupae] );
    CopyVectorToOutput( uco->GetAvgDryPupWt(bStartDate, bStopDate, id), mco->Containers[id][(int)gui::output::OutputTypes::Cimsim::Container::AveragePupalWeight] );
    CopyVectorToOutput( uco->GetNewFemales(bStartDate, bStopDate, id), mco->Containers[id][(int)gui::output::OutputTypes::Cimsim::Container::NewFemales] );
    CopyVectorToOutput( uco->GetCumulativeFemales(bStartDate, bStopDate, id), mco->Containers[id][(int)gui::output::OutputTypes::Cimsim::Container::CumulativeFemales] );
    CopyVectorToOutput( uco->GetOviposition(bStartDate, bStopDate, id), mco->Containers[id][(int)gui::output::OutputTypes::Cimsim::Container::Oviposition] );
    CopyVectorToOutput( uco->GetUntreatedDensity(bStartDate, bStopDate, id), mco->Containers[id][(int)gui::output::OutputTypes::Cimsim::Container::UntreatedDensity] );
    CopyVectorToOutput( uco->GetTreatedDensity(bStartDate, bStopDate, id), mco->Containers[id][(int)gui::output::OutputTypes::Cimsim::Container::TreatedDensity] );
    CopyVectorToOutput( uco->GetExcludedDensity(bStartDate, bStopDate, id), mco->Containers[id][(int)gui::output::OutputTypes::Cimsim::Container::ExcludedDensity] );
  }

  return mco;
}



void
Location::TestingRunCimsim(void)
{
  // run cs 3.0 and csp 1.0 (w/o processing output)
  input::Location * loc = GetSimObject();
  boost::gregorian::date startDate = loc->Weather_->GetWeatherPeriod().begin();
  boost::gregorian::date stopDate = loc->Weather_->GetWeatherPeriod().end();

  sim::cs::Simulation cs3( loc, startDate, stopDate );
  cs3.Start();

  sim::csp::csport csp1( *loc );
  csp1.cimmain();
}

  
  
void
Location::RunFoodFitIteration( int numberOfRuns, DateTime surveyBegin, DateTime surveyEnd )
{
  // convert to boost dates
  boost::gregorian::date surveyStartDate( surveyBegin.Year, surveyBegin.Month, surveyBegin.Day );
  boost::gregorian::date surveyStopDate( surveyEnd.Year, surveyEnd.Month, surveyEnd.Day );

  // create simulation
  const input::Location * loc = GetSimObject();
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
Location::RunDensim( int startYear, int stopYear )
{
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
    for each( Dundas::Charting::WinControl::Series ^ series in DensimSeries_->Values ) {
      delete series;
    }
    DensimSeries_->Clear();

    for each( OutputSeries ^ outputSeries in SerotypeSeries_->Values ) {
      for each( Dundas::Charting::WinControl::Series ^ series in outputSeries->Values ) {
        delete series;
      }
    }
    SerotypeSeries_->Clear();
  }

  // TODO - why regenerate a new object - especially if old one was what was used for CIMSiM
  // possibly even different?
  const input::Location * loc = GetSimObject();

  // find start and stop dates for simulation
  boost::gregorian::date startDate = boost::gregorian::date( startYear, 1, 1 );
  boost::gregorian::date stopDate = boost::gregorian::date( stopYear, 12, 31 );

  sim::ds::Simulation * dssim = new sim::ds::Simulation( loc, MosData_ );
  dssim->Start( startDate, stopDate );

  // process output
  DensimData_ = dssim->GetSimOutput();
  _isDensimCompleted = true;

  delete loc;     // delete input object (no longer needed, regenerated on next run)
  delete dssim;   // delete sim and its output (now processed into managed data)
}
