// code adopted from the following codeproject resources:
// http://www.codeproject.com/KB/miscctrl/CustomSplashScreen.aspx
// which was licensed using the Code Project Open License:
// http://www.codeproject.com/info/cpol10.aspx

#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace gui {

	public ref class SplashForm : public System::Windows::Forms::Form
	{
	public:
		SplashForm(void);
	protected:
		~SplashForm();

  public:
		static void ShowSplash(void);
		static void ShowSplash( int fadeinTime, String ^ text );
		static void Fadeout(void);
  protected:
    virtual System::Void OnClick(System::EventArgs ^ e) override;
    virtual System::Void OnClosing(System::ComponentModel::CancelEventArgs ^ e) override;
  private:
    System::Void FadeoutTick(System::Object ^ sender, System::EventArgs ^ e);

  private:
		static SplashForm ^ _instance = nullptr;
    static Threading::Thread ^ _splashThread = nullptr;
    Timer ^ _fadeTimer;
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
  private:
		void InitializeComponent(void)
		{
      this->SuspendLayout();
      // 
      // SplashForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->BackColor = System::Drawing::Color::Fuchsia;
      this->ClientSize = System::Drawing::Size(320, 240);
      this->ControlBox = false;
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
      this->Name = L"SplashForm";
      this->ShowInTaskbar = false;
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
      this->Text = L"SplashForm";
      this->TopMost = true;
      this->TransparencyKey = System::Drawing::Color::Fuchsia;
      this->ResumeLayout(false);

    }
#pragma endregion
	};
}
