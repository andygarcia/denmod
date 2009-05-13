#include "StdAfx.h"
#include "HelpForm.h"

using namespace parsedos;



HelpForm::HelpForm(void)
{
	InitializeComponent();
  tabPageDensim->BackColor = SystemColors::Control;
}



HelpForm::~HelpForm()
{
  if( components ) {
		delete components;
	}
}
