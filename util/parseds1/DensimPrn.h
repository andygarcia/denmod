// ====================================================================== //
// Find in the specified directory the following files and parse them
// into appropriate excel spreadsheets:
//
// DG0.PRN    - Persons with virus
// DG1.DEM    - Age Distribution
// DG2.PRN    - Population Growth
// DG3.PRN    - Simulation Area
// DG4.PRN    - Female Mosquitoes
// DG5.PRN    - Mosquito Survival
// DG6.PRN    - Mosquitoes with Virus in Salivary Glands
// DG7.PRN    - EIP Development Rate
// DG8.PRN    - Mosquito Wet Weight
// DG9.PRN    - Mosquitoes per Person
// DG10.PRN   - Viremic Persons
// DG11.SER   - General Seroprevalence
// DG121.PRN  - Detailed Seroprevalence, first eight demographic ranks
// DG122.PRN  - Detailed Seroprevalence, second eight demographic ranks
// DG13.PRN   - Potential Inoculations Subject to Susceptibility
// DG14.PRN   - Persons incubating virus
// DG15.PRN   - Persons viremic and incubating
// DG16.PRN   - New cases
// ====================================================================== //
#pragma once

#include <map>
#include <string>
#include <vector>
#include <vcclr.h>


std::string toss( System::String ^ s );

ref class PrnFile;
ref class PrnData;

ref class DensimPrn
{
public:
  DensimPrn( System::String ^ directory );
  ~DensimPrn(void);


  void Parse(void);
  void Output(void);

private:
  void ParseDailyData( System::String ^ filePrefix );
  void ParseClassData( System::String ^ filePrefix );

  void OutputMainGraph(void);
  void OutputDemographics(void);
  void OutputSeroprevalence(void);
  void OutputFemales(void);
  void OutputCaseData(void);
  void OutputEIP(void);

  System::String ^ Dir_;
  typedef std::map<int, gcroot<PrnFile^>> GraphCollection;
  GraphCollection * Graphs_;
};



ref class PrnFile
{
public:
  PrnFile( System::String ^ filename );
  System::String ^ GetFilename(void) { return this->Filename_; }
  int GetGraphNumber(void) { return this->GraphNumber_; }
  int GetNumHeaders(void) { return this->Headers_->Length; }

protected:
  System::String ^ Filename_;
  System::String ^ Title_;
  int GraphNumber_;
  array<System::String ^> ^ Headers_;
};



ref class DailyDataPrnFile : public PrnFile
{
public:
  DailyDataPrnFile( System::String ^ filename );

  virtual void Parse(void);
  PrnData ^ GetData(void);

public:
  PrnData ^ Data_;
};



ref class ClassDataPrnFile : public PrnFile
{
public:
  ClassDataPrnFile( System::String ^ filename ) : PrnFile( filename ) {}

  virtual void Parse(void);

  array<System::String ^, 2> ^ InitialData_;
  array<System::String ^, 2> ^ FinalData_;
};



ref class PrnData
{
public:
  PrnData( int rowLength );

  void Add( System::String ^ s );
  int GetNumRows(void);
  array<System::String^> ^ GetRow( int iRow );


private:
  int RowLength_;
  System::Collections::ArrayList ^ Data_;
};
