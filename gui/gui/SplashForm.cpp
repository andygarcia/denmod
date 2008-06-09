#include "StdAfx.h"
#include "SplashForm.h"

using namespace gui;



SplashForm::SplashForm(void)
{
	InitializeComponent();

  // load image from resource
  Resources::ResourceManager ^ rm = gcnew Resources::ResourceManager( "gui.gui", Reflection::Assembly::GetExecutingAssembly() );
  Bitmap ^ b = (Bitmap ^ ) rm->GetObject( "Splash16.bmp" );
  BackgroundImage = b;

	// size to background image
	this->Size = this->BackgroundImage->Size;
  this->StartPosition = FormStartPosition::CenterScreen;

	// fade out timer
	if( this->components == nullptr ) {
    this->components = gcnew System::ComponentModel::Container();
	}
  _fadeTimer = gcnew Timer(this->components);
}



SplashForm::~SplashForm()
{
	if( components ) {
		delete components;
	}
}



void
SplashForm::ShowSplash(void)
{
	// show splash with no fading
	ShowSplash(0, "About Dengue Models" );
}



void
SplashForm::ShowSplash( int fadeinTime, String ^ text )
{
  // only show if not showing already
  if( _instance == nullptr ) {
    _instance = gcnew SplashForm();

    // if text specified, add border and title
    if( !String::IsNullOrEmpty(text) ) {
      _instance->FormBorderStyle = Windows::Forms::FormBorderStyle::FixedSingle;
      _instance->Text = text;
    }

    // hide initially so as to avoid a nasty pre paint flicker
    _instance->Opacity = 0;
    _instance->Show();

    // process the initial paint events
    Application::DoEvents();

    // perform the fade in
    if( fadeinTime > 0 ) {
	    // set the timer interval so that we fade out at the same speed.
      int fadeStep = (int) Math::Round((double)fadeinTime/20);
      _instance->_fadeTimer->Interval = fadeStep;

	    for (int i = 0; i <= fadeinTime; i += fadeStep){
        Threading::Thread::Sleep(fadeStep);
		    _instance->Opacity += 0.05;
	    }
    }
    else {
	    // set the timer interval so that we fade out instantly.
	    _instance->_fadeTimer->Interval = 1;
    }
    _instance->Opacity = 1;
	}
}



void
SplashForm::Fadeout(void)
{
	// only fadeout if we are currently visible.
	if( _instance != nullptr ) {
    _instance->BeginInvoke( gcnew MethodInvoker(_instance, &SplashForm::Close) );
		
		// process the close on the Splash Thread.
    Application::DoEvents();
	}
}



void
SplashForm::OnClick(System::EventArgs ^ e)
{
	// if we are displaying as a about dialog we need to provide a way out.
	this->Close();
}



void
SplashForm::OnClosing(System::ComponentModel::CancelEventArgs ^ e)
{
  Form::OnClosing(e);
	
	// close immediately if the timer interval is set to 1 indicating no fade
	if( this->_fadeTimer->Interval == 1) {
		e->Cancel = false;
    _instance = nullptr;
		return;
	}

	// only use the timer to fade out if we have a mainform running otherwise there will be no message pump
  if( Application::OpenForms->Count > 1 ) {
    if( this->Opacity > 0 ) {
      e->Cancel = true;
      this->Opacity -= 0.05;

      // use the timer to iteratively call the close method thereby keeping the GUI thread available for other processes.
      this->_fadeTimer->Tick -= gcnew EventHandler(this, &SplashForm::FadeoutTick);
      this->_fadeTimer->Tick += gcnew EventHandler(this, &SplashForm::FadeoutTick);
      this->_fadeTimer->Start();
    }
    else {
      e->Cancel = false;
      this->_fadeTimer->Stop();

      // clear the instance variable so we can reshow the splash, and ensure that we don't try to close it twice
      _instance = nullptr;
    }
  }
  else {
    if( this->Opacity > 0 ) {
      // sleep on this thread to slow down the fade as there is no message pump running
      System::Threading::Thread::Sleep(this->_fadeTimer->Interval);
      _instance->Opacity -= 0.05;

      // iteratively call the close method
      this->Close();
    }
    else {
      e->Cancel = false;

      // clear the instance variable so we can reshow the splash, and ensure that we don't try to close it twice
      _instance = nullptr;
    }
	}
}	



System::Void
SplashForm::FadeoutTick(Object ^ sender, System::EventArgs ^ e)
{
	this->Close();
}
