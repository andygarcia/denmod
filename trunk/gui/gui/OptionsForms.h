#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace gui {

	/// <summary>
	/// Summary for OptionsForms
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class OptionsForms : public System::Windows::Forms::Form
	{
	public:
		OptionsForms(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~OptionsForms()
		{
			if (components)
			{
				delete components;
			}
		}
  private: System::Windows::Forms::Button^  btnOk;
  protected: 

  private: System::Windows::Forms::Button^  btnCancel;
  private: System::Windows::Forms::CheckBox^  chkImmaturesScaled;
  private: System::Windows::Forms::CheckBox^  chkStochasticAdvancement;

  protected: 


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
      this->btnOk = (gcnew System::Windows::Forms::Button());
      this->btnCancel = (gcnew System::Windows::Forms::Button());
      this->chkImmaturesScaled = (gcnew System::Windows::Forms::CheckBox());
      this->chkStochasticAdvancement = (gcnew System::Windows::Forms::CheckBox());
      this->SuspendLayout();
      // 
      // btnOk
      // 
      this->btnOk->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnOk->Location = System::Drawing::Point(168, 76);
      this->btnOk->Name = L"btnOk";
      this->btnOk->Size = System::Drawing::Size(75, 23);
      this->btnOk->TabIndex = 0;
      this->btnOk->Text = L"OK";
      this->btnOk->UseVisualStyleBackColor = true;
      // 
      // btnCancel
      // 
      this->btnCancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnCancel->Location = System::Drawing::Point(249, 76);
      this->btnCancel->Name = L"btnCancel";
      this->btnCancel->Size = System::Drawing::Size(75, 23);
      this->btnCancel->TabIndex = 0;
      this->btnCancel->Text = L"Cancel";
      this->btnCancel->UseVisualStyleBackColor = true;
      // 
      // chkImmaturesScaled
      // 
      this->chkImmaturesScaled->AutoSize = true;
      this->chkImmaturesScaled->Location = System::Drawing::Point(12, 12);
      this->chkImmaturesScaled->Name = L"chkImmaturesScaled";
      this->chkImmaturesScaled->Size = System::Drawing::Size(268, 17);
      this->chkImmaturesScaled->TabIndex = 1;
      this->chkImmaturesScaled->Text = L"Scale immatures on CIMSiM\'s main output by 100\'s.";
      this->chkImmaturesScaled->UseVisualStyleBackColor = true;
      // 
      // chkStochasticAdvancement
      // 
      this->chkStochasticAdvancement->AutoSize = true;
      this->chkStochasticAdvancement->Location = System::Drawing::Point(12, 35);
      this->chkStochasticAdvancement->Name = L"chkStochasticAdvancement";
      this->chkStochasticAdvancement->Size = System::Drawing::Size(239, 17);
      this->chkStochasticAdvancement->TabIndex = 2;
      this->chkStochasticAdvancement->Text = L"Use stochasticity for all stage advancements.";
      this->chkStochasticAdvancement->UseVisualStyleBackColor = true;
      // 
      // OptionsForms
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(336, 111);
      this->Controls->Add(this->chkStochasticAdvancement);
      this->Controls->Add(this->chkImmaturesScaled);
      this->Controls->Add(this->btnCancel);
      this->Controls->Add(this->btnOk);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
      this->Name = L"OptionsForms";
      this->Text = L"Options";
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
	};
}
