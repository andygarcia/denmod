#pragma once

using namespace System;
using namespace System::Collections;


public ref class SensitivityAnalysis
{
// Constructors
private:
  static SensitivityAnalysis(void);

public:
  SensitivityAnalysis(void);
  virtual ~SensitivityAnalysis(void);

// Methods
public:
  static void ModifyLocation( gui::Location ^ location, Generic::List<String^> ^ paramNames, Generic::List<double> ^ paramValues );

private:
  static void SetDmlParameter( gui::Location ^ location, String ^ dmlName, Object ^ value );
  static String ^ GetDmlNameFromSa( String ^ saName );


// Fields
private:
  static Generic::Dictionary<String^,String^> ^ _saNamesToDmlNames;
};


//ref class SensitivityAnalysisParameter
//{
//public:
//  SensitivityAnalysisParameter(void);
//  virtual ~SensitivityAnalysisParameter(void);
//};
//
