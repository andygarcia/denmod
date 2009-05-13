#include "StdAfx.h"
#include "HelpForm.h"

using namespace parsedos;



HelpForm::HelpForm(void)
{
	InitializeComponent();
  tabPageCimsim->BackColor = SystemColors::Control;
  tabPageDensim->BackColor = SystemColors::Control;
}



HelpForm::~HelpForm()
{
  if( components ) {
		delete components;
	}
}
