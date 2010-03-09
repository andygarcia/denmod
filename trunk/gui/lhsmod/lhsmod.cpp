// lhsmod.cpp : main project file.

#include "stdafx.h"
#include "LhsForm.h"

using namespace lhsmod;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew LhsForm());
	return 0;
}
