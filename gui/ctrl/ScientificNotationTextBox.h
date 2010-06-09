#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace ctrl {

	public ref class ScientificNotationTextBox : public TextBox
	{
	public:
		ScientificNotationTextBox(void);
	protected:
		~ScientificNotationTextBox();

  public:
    [BindableAttribute(true)]
    [BrowsableAttribute(true)]
    [CategoryAttribute("Appearance")]
    [DefaultValueAttribute(0)]
    property System::String ^ Value {
      System::String ^ get(void);
      void set(System::String ^ s);
    }

    event EventHandler ^ ValueChanged;

    void OnValueChanged(void)
    {
      ValueChanged( this, gcnew EventArgs() );
    }
  
  protected:
    virtual void OnKeyPress( System::Windows::Forms::KeyPressEventArgs ^ e ) override;
    virtual void OnGotFocus( System::EventArgs ^ e ) override;
    virtual void OnLeave( System::EventArgs ^ e ) override;

  private:
    System::String ^ Value_;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->SuspendLayout();
      // 
      // ScientificNotationTextBox
      // 
      this->Size = System::Drawing::Size(80, 20);
      this->Text = L"0";
      this->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
      this->ResumeLayout(false);

    }
#pragma endregion
	};
}
