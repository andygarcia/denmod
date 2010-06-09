#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace gui {

	public ref class AboutDialog : public System::Windows::Forms::Form
	{
	public:
		AboutDialog(void)
		{
			InitializeComponent();
		}

	protected:
		~AboutDialog()
		{
			if( components ) {
				delete components;
			}
		}

  private:
    System::Void OnImageClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
    {
      // bounds for link panels are relative to form
      // e->Location coordinates are relative to pboxAbout
      int x = e->X + pboxAbout->Location.X;
      int y = e->Y + pboxAbout->Location.Y;

      // determine if mouse click is in link area
      if( pnlTahijaLink->Bounds.Contains(x, y) ) {
        System::Diagnostics::Process::Start( "www.tahija.or.id" );
      }
      else if( pnlGatesLink->Bounds.Contains(x, y) ) {
        System::Diagnostics::Process::Start( "www.gatesfoundation.org" );
      }
    }

  private:
    System::Void OnImageMouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
    {
      // bounds for link panels are relative to form
      // e->Location coordinates are relative to pboxAbout
      int x = e->X + pboxAbout->Location.X;
      int y = e->Y + pboxAbout->Location.Y;

      // determine if mouse click is in link area
      if( pnlTahijaLink->Bounds.Contains(x, y) ||pnlGatesLink->Bounds.Contains(x, y) ) {
        // use hand cursor
        System::Windows::Forms::Cursor::Current = System::Windows::Forms::Cursors::Hand;
      }
      else {
        System::Windows::Forms::Cursor::Current = System::Windows::Forms::Cursors::Default;
      }
    }


  private: System::Windows::Forms::PictureBox^  pboxAbout;
  private: System::Windows::Forms::Button^  btnOk;
  private: System::Windows::Forms::Panel^  pnlTahijaLink;
  private: System::Windows::Forms::Panel^  pnlGatesLink;
  protected: 

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
      System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(AboutDialog::typeid));
      this->pboxAbout = (gcnew System::Windows::Forms::PictureBox());
      this->btnOk = (gcnew System::Windows::Forms::Button());
      this->pnlTahijaLink = (gcnew System::Windows::Forms::Panel());
      this->pnlGatesLink = (gcnew System::Windows::Forms::Panel());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pboxAbout))->BeginInit();
      this->SuspendLayout();
      // 
      // pboxAbout
      // 
      this->pboxAbout->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pboxAbout.Image")));
      this->pboxAbout->Location = System::Drawing::Point(12, 12);
      this->pboxAbout->Name = L"pboxAbout";
      this->pboxAbout->Size = System::Drawing::Size(320, 420);
      this->pboxAbout->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
      this->pboxAbout->TabIndex = 0;
      this->pboxAbout->TabStop = false;
      this->pboxAbout->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &AboutDialog::OnImageMouseMove);
      this->pboxAbout->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AboutDialog::OnImageClick);
      // 
      // btnOk
      // 
      this->btnOk->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->btnOk->Location = System::Drawing::Point(257, 438);
      this->btnOk->Name = L"btnOk";
      this->btnOk->Size = System::Drawing::Size(75, 23);
      this->btnOk->TabIndex = 2;
      this->btnOk->Text = L"OK";
      this->btnOk->UseVisualStyleBackColor = true;
      // 
      // pnlTahijaLink
      // 
      this->pnlTahijaLink->BackColor = System::Drawing::SystemColors::Control;
      this->pnlTahijaLink->Cursor = System::Windows::Forms::Cursors::Hand;
      this->pnlTahijaLink->Location = System::Drawing::Point(39, 327);
      this->pnlTahijaLink->Name = L"pnlTahijaLink";
      this->pnlTahijaLink->Size = System::Drawing::Size(168, 18);
      this->pnlTahijaLink->TabIndex = 0;
      // 
      // pnlGatesLink
      // 
      this->pnlGatesLink->Cursor = System::Windows::Forms::Cursors::Hand;
      this->pnlGatesLink->Location = System::Drawing::Point(39, 384);
      this->pnlGatesLink->Name = L"pnlGatesLink";
      this->pnlGatesLink->Size = System::Drawing::Size(233, 18);
      this->pnlGatesLink->TabIndex = 1;
      // 
      // AboutDialog
      // 
      this->AcceptButton = this->btnOk;
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->CancelButton = this->btnOk;
      this->ClientSize = System::Drawing::Size(344, 473);
      this->Controls->Add(this->btnOk);
      this->Controls->Add(this->pboxAbout);
      this->Controls->Add(this->pnlTahijaLink);
      this->Controls->Add(this->pnlGatesLink);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
      this->MaximizeBox = false;
      this->MinimizeBox = false;
      this->Name = L"AboutDialog";
      this->ShowInTaskbar = false;
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
      this->Text = L"About Dengue Models";
      this->TransparencyKey = System::Drawing::Color::Magenta;
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pboxAbout))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  };
}
