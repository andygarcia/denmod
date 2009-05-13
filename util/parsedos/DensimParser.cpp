#include "stdafx.h"
#include "DensimParser.h"
#include "ExcelOutput.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;



std::string toss( String ^ s );


static
DensimParser::DensimParser(void)
{


}


DensimParser::DensimParser( DirectoryInfo ^ inputDirectory)
: _inputDirectory(inputDirectory),
  _parseCompleted(false),
  _locationFiles(gcnew List<LocationFile^>()),
  _containerNames(gcnew List<String^>()),
  _containerHeaders(gcnew List<String^>()),
  _containerData(gcnew Dictionary<String^,Dictionary<String^,List<String^>^>^>()),
  _containerSurvivals(gcnew Dictionary<String^,List<SurvivalFile^>^>()),
  _larvalDataFiles(gcnew List<LarvalDataFile^>())
{}



DensimParser::~DensimParser(void)
{}



void
DensimParser::Parse(void)
{

}



void
DensimParser::SaveToDisk( OutputType outputType )
{

}
