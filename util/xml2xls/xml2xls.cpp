// xml2xls.cpp : main project file.

#include "stdafx.h"
#include "InputForm.h"

using namespace xml2xls;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew InputForm());
	return 0;
}
