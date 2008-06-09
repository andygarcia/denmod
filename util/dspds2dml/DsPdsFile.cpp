#include "StdAfx.h"
#include "DsPdsFile.h"
#include "DlyFile.h"
#include <vector>

using namespace System;
using namespace System::IO;




DsPdsFile ^
DsPdsFile::Open( String ^ filename )
{
  DsPdsFile ^ pf = gcnew DsPdsFile( filename );
  pf->Parse();
  return pf;
}



DsPdsFile::DsPdsFile( String ^ filename )
: Filename_(filename),
  loc(new ds::port::Location())
{}




DsPdsFile::~DsPdsFile()
{
  delete loc;
}



ds::port::Location *
DsPdsFile::GetLocation(void)
{
  return loc;
}

void
DsPdsFile::Parse(void)
{
  using namespace ds::port;

  // open pds file and parse
  StreamReader ^ sr;
  sr = gcnew StreamReader( Filename_ );

  // read location parameters
  String ^ WeatherPath = sr->ReadLine();
  String ^ OutputPath = sr->ReadLine();
  String ^ TempPath = sr->ReadLine();
  String ^ CimPopPath = sr->ReadLine();
  String ^ CimMosPath = sr->ReadLine();
  String ^ DemFile = sr->ReadLine();
  String ^ VirFile = sr->ReadLine();
  String ^ SerFile = sr->ReadLine();
  String ^ BioFile = sr->ReadLine();
  String ^ CimMosFile = sr->ReadLine();
  String ^ CimPopFile = sr->ReadLine();
  String ^ WeaFile = sr->ReadLine();

  loc->VirusIntro.push_back( VirusIntroductionProfile() );
  for( int i = 1; i <= 4; ++i ) {
    String ^ virusLine = sr->ReadLine();
    array<String^> ^ subStrings = virusLine->Split( gcnew array<wchar_t>{ ',' } );

    VirusIntroductionProfile vip;
    vip.Trts = Int32::Parse( subStrings[0] );
    vip.SDay = Int32::Parse( subStrings[1] );
    vip.Intv = Int32::Parse( subStrings[2] );
    vip.Hums = Single::Parse( subStrings[3] );
    vip.Mosq = Single::Parse( subStrings[4] );
    loc->VirusIntro.push_back( vip );
  }

  loc->SeqInfPrms.push_back( SequentialInfectionParms() );
  for( int i = 1; i <= 12; ++i ) {
    String ^ seqLine = sr->ReadLine();
    array<String^> ^ subStrings = seqLine->Split( gcnew array<wchar_t>{ ',' } );

    SequentialInfectionParms sip;
    sip.Min = Int32::Parse( subStrings[0] );
    sip.Max = Int32::Parse( subStrings[1] );
    sip.Prob = Single::Parse( subStrings[2] );
    sip.CutOff = Single::Parse( subStrings[3] );
    sip.Mortality = Single::Parse( subStrings[4] );

    loc->SeqInfPrms.push_back( sip );
  }

  loc->MAEAInfPrms.push_back( MAEAInfectionParms() );
  for( int i = 1; i <= 4; ++i ) {
    String ^ maeaLine = sr->ReadLine();
    array<String^> ^ subStrings = maeaLine->Split( gcnew array<wchar_t>{ ',' } );

    MAEAInfectionParms mip;
    mip.Prob = Single::Parse( subStrings[0] );
    mip.Mortality = Single::Parse( subStrings[1] );

    loc->MAEAInfPrms.push_back( mip );
  }
  sr->Close();


  // read DEM file
  sr = gcnew StreamReader( TempPath + DemFile );
  loc->PopProp.push_back( HumanDemo() );
  for( int i = 1; i <= 18; ++i ) {
    String ^ demLine = sr->ReadLine();
    array<String^> ^ subStrings = demLine->Split( gcnew array<wchar_t>{ ',' } );

    HumanDemo hd;
    hd.Rank = Int32::Parse( subStrings[0] );
    hd.Prop = Single::Parse( subStrings[1] );
    hd.DRate = Single::Parse( subStrings[2] );
    hd.BRate = Single::Parse( subStrings[3] );

    loc->PopProp.push_back( hd );
  }

  array<String ^> ^ subStrings = sr->ReadLine()->Split( gcnew array<wchar_t>{ ',' } );
  loc->HumHostDensity = Single::Parse( subStrings[0] );
  loc->ClusterSize = Single::Parse( subStrings[1] );
  sr->Close();


  // read VIR file
  sr = gcnew StreamReader( TempPath + VirFile );
  loc->Virus.push_back( VirusDesc() );
  for( int i = 1; i <= 4; ++i ) {
    String ^ virLine = sr->ReadLine();
    array<String^> ^ subStrings = virLine->Split( gcnew array<wchar_t>{ ',' } );

    VirusDesc vd;
    vd.Viremia = Single::Parse( subStrings[0] );
    vd.Incub = Int32::Parse( subStrings[1] );
    vd.Durat = Int32::Parse( subStrings[2] );

    loc->Virus.push_back( vd );
  }

  subStrings = sr->ReadLine()->Split( gcnew array<wchar_t>{ ',' } );
  loc->HumToMosLTiter = Single::Parse( subStrings[0] );
  loc->HumToMosLInf = Single::Parse( subStrings[1] );
  loc->HumToMosHTiter = Single::Parse( subStrings[2] );
  loc->HumToMosHInf = Single::Parse( subStrings[3] );

  subStrings = sr->ReadLine()->Split( gcnew array<wchar_t>{ ',' } );
  loc->EipLTiter = Single::Parse( subStrings[0] );
  loc->EipLFactor = Single::Parse( subStrings[1] );
  loc->EipHTiter = Single::Parse( subStrings[2] );
  loc->EipHFactor = Single::Parse( subStrings[3] );

  subStrings = sr->ReadLine()->Split( gcnew array<wchar_t>{ ',' } );
  loc->StochTransNum = Single::Parse( subStrings[0] );
  loc->MosqToHumProb = Single::Parse( subStrings[1] );

  subStrings = sr->ReadLine()->Split( gcnew array<wchar_t>{ ',' } );
  loc->EnzKinDR = Single::Parse( subStrings[0] );
  loc->EnzKinEA = Single::Parse( subStrings[1] );
  loc->EnzKinEI = Single::Parse( subStrings[2] );
  loc->EnzKinTI = Single::Parse( subStrings[3] );
  sr->Close();


  // Read SER file
  sr = gcnew StreamReader( TempPath + SerFile );
  loc->SerProp.push_back( std::vector<float>( 4+1, 0 ) );
  for( int i = 1; i <= 18; ++i ) {
    String ^ serLine = sr->ReadLine();
    array<String^> ^ subStrings = serLine->Split( gcnew array<wchar_t>{ ',' } );

    std::vector<float> rankSer;
    rankSer.push_back( 0 );
    rankSer.push_back( Single::Parse(subStrings[1]) );
    rankSer.push_back( Single::Parse(subStrings[2]) );
    rankSer.push_back( Single::Parse(subStrings[3]) );
    rankSer.push_back( Single::Parse(subStrings[4]) );

    loc->SerProp.push_back( rankSer );
  }

  subStrings = sr->ReadLine()->Split( gcnew array<wchar_t>{ ',' } );
  loc->MANADurat = Single::Parse( subStrings[0] );
  loc->MAEADurat = Single::Parse( subStrings[1] );
  loc->HetImmunDurat = Single::Parse( subStrings[2] );
  sr->Close();


  // Read BIO file
  sr = gcnew StreamReader( TempPath + BioFile );
  subStrings = sr->ReadLine()->Split( gcnew array<wchar_t>{ ',' } );
  loc->PropOnHum = Single::Parse( subStrings[0] );
  loc->FdAttempts = Single::Parse( subStrings[1] );
  loc->PropDifHost = Single::Parse( subStrings[2] );
  loc->PropOutdoor = Single::Parse( subStrings[3] );

  subStrings = sr->ReadLine()->Split( gcnew array<wchar_t>{ ',' } );
  loc->DBloodLWt = Single::Parse( subStrings[0] );
  loc->DBloodUWt = Single::Parse( subStrings[1] );
  loc->DBloodUProp = Single::Parse( subStrings[2] );
  loc->DBloodLProp = Single::Parse( subStrings[3] );


  // Read MOS files
  DirectoryInfo ^ di = gcnew DirectoryInfo( CimMosPath );

  // TODO - fix this to only search for mos files based on specified file, i.e. lamesa87.mos, etc.
  array<FileInfo^> ^ mosFiles = di->GetFiles( "*.mos", SearchOption::TopDirectoryOnly );
  for each( FileInfo ^ fi in mosFiles ) {
    // convert from binary .mos to text .mst
    Diagnostics::Process ^ proc = gcnew Diagnostics::Process();
    proc->StartInfo->WorkingDirectory = CimMosPath;
    proc->StartInfo->FileName = "c:\\pds\\output\\mos2txt.exe";
    proc->StartInfo->Arguments = fi->Name;
    proc->StartInfo->CreateNoWindow = true;
    proc->StartInfo->UseShellExecute = false;
    proc->Start();
  }

  // now process plain text files
  array<FileInfo^> ^ mstFiles = di->GetFiles( "*.mst", SearchOption::TopDirectoryOnly );
  int yearIndex = 1;
  for each( FileInfo ^ fi in mstFiles ) {
    sr = gcnew StreamReader( fi->FullName );

    std::vector<CimSimOutDescription> year;
    year.push_back( CimSimOutDescription() );
    for( int i = 1; i <= 365; ++i ) {
      String ^ mosLine = sr->ReadLine();
      array<String^> ^ subStrings = mosLine->Split( gcnew array<wchar_t>{ ',' } );

      CimSimOutDescription csod;
      csod.NewDlyFemales = Single::Parse( subStrings[0] );
      csod.AvgDlyWeight = Single::Parse( subStrings[1] );
      csod.OverallSurv = Single::Parse( subStrings[2] );
      csod.AdultDev = Single::Parse( subStrings[3] );

      year.push_back( csod );
    }
    loc->CimsimDataByYear[yearIndex] = year;
    yearIndex++;
  }


  // Read POP file
  sr = gcnew StreamReader( CimPopPath + CimPopFile );

  subStrings = sr->ReadLine()->Split( gcnew array<wchar_t>{ ',' } );
  int iYr = Int32::Parse( subStrings[0] );
  int iEggs = Int32::Parse( subStrings[1] );
  int iLarvae = Int32::Parse( subStrings[2] );
  int iPupae = Int32::Parse( subStrings[3] );

  subStrings = sr->ReadLine()->Split( gcnew array<wchar_t>{ ',' } );
  int iPreAdults = Int32::Parse( subStrings[0] );
  int iOviAdults = Int32::Parse( subStrings[1] );

  int NumberOfContainers = Int32::Parse( sr->ReadLine() );

  std::vector<float> CtHts = std::vector<float>( NumberOfContainers+1, 0 );

  // limits match, proceed with read
  // read container demographics
  for( int i = 1; i <= NumberOfContainers; ++i ) {
    sr->ReadLine();
    sr->ReadLine();
    CtHts[i] = Single::Parse( sr->ReadLine() );
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
    sr->ReadLine();
  }

  // dimension egg arrays & read eggs
  for( int ii = 1; ii <= NumberOfContainers; ++ii ) {
    for( int i = 1; i <= dsport::CINT( (CtHts[ii] / 2) + .2f ); ++i ) {
      sr->ReadLine();
      for( int j = 1; j <= iEggs; ++j ) {
        sr->ReadLine();
      }
    }
  }

  // read larvae
  for( int i = 1; i <= iLarvae; ++i ) {
    for( int j = 1; j <= NumberOfContainers; ++j ) {
      sr->ReadLine();
      sr->ReadLine();
      sr->ReadLine();
    }
  }
  for( int i = 1; i <= NumberOfContainers; ++i ) {
    sr->ReadLine();
  }

  // read pupae
  for( int i = 1; i <= iPupae; ++i ) {
    for( int j = 1; j <= NumberOfContainers; ++j ) {
      sr->ReadLine();
    }
  }
  for( int i = 1; i <= NumberOfContainers; ++i ) {
    sr->ReadLine();
  }


  loc->NewMosqSusc = std::vector<float>( (iPreAdults+1) + 1, 0 );
  loc->NewMosqSuscCD = std::vector<float>( (iPreAdults+1) + 1, 0 );
  // read preovi-adults
  for( int i = 1; i <= iPreAdults; ++i ) {
    subStrings = sr->ReadLine()->Split( gcnew array<wchar_t>{ ',' } );
    loc->NewMosqSusc[i] = Single::Parse( subStrings[0] );
    loc->NewMosqSuscCD[i] = Single::Parse( subStrings[1] );
  }
  sr->ReadLine();

  loc->OldMosqSusc = std::vector<float>( (iOviAdults+1) + 1, 0 );
  loc->OldMosqSuscCD = std::vector<float>( (iOviAdults+1) + 1, 0 );
  // read old adults
  for( int i = 1; i <= iOviAdults; ++i ) {
    subStrings = sr->ReadLine()->Split( gcnew array<wchar_t>{ ',' } );
    loc->OldMosqSusc[i] = Single::Parse( subStrings[0] );
    loc->OldMosqSuscCD[i] = Single::Parse( subStrings[1] );
  }

  // read adult weights
  for( int i = 1; i <= 5; ++i ) {
    sr->ReadLine();
  }

  // read adult age distribution
  for( int i = 1; i <= iOviAdults; ++i ) {
    sr->ReadLine();
  }

  // read graphics
  sr->ReadLine();

  // container environment
  for( int i = 1; i <= NumberOfContainers; ++i ) {
    sr->ReadLine();
    sr->ReadLine();
  }

  sr->ReadLine();

  for( int i = 1; i <= NumberOfContainers; ++i ) {
    for( int j = 1; j <= 5; ++j ) {
      String ^ test = sr->ReadLine();
    }
  }

  // Weather files
  di = gcnew DirectoryInfo( WeatherPath );
  String ^ base = WeaFile->Substring(0,6);
  array<FileInfo ^> ^ weaFiles = di->GetFiles( base + "*.dly", SearchOption::TopDirectoryOnly );

  for each( FileInfo ^ fi in weaFiles ) {
    DlyFile ^ df = DlyFile::Open( fi->FullName );
    loc->Weather_->AddYear( df->GetWeatherYear() );
  }
}
