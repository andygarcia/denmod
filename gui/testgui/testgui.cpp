// testgui.cpp : main project file.

#include "stdafx.h"
#include "Testing.h"

using namespace testgui;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Testing());
	return 0;
}
