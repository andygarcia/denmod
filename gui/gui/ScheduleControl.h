#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace gui {


  public ref class ScheduleControl : public System::Windows::Forms::UserControl, INotifyPropertyChanged
	{
	public:
    ScheduleControl( BindingSource ^ locationBinding, String ^ scheduleBindingSite );
		~ScheduleControl(void);

  public:
    [System::ComponentModel::Bindable(true)]
    property Schedule ^ CurrentSchedule {
      Schedule ^ get(void);
      void set( Schedule ^ schedule );
    }

  public:
    virtual event System::ComponentModel::PropertyChangedEventHandler ^ PropertyChanged;

  protected:
    void NotifyPropertyChanged(System::String ^ info) {
      PropertyChanged( this, gcnew System::ComponentModel::PropertyChangedEventArgs(info) );
    }

  private:
    void SetSchedulePanel(void);
    System::Void OnLoad( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnScheduleChange( System::Object ^ sender, System::EventArgs ^ e );

  private:
    BindingSource ^ LocationBinding_;
    String ^ ScheduleBindingSite_;
    Schedule ^ CurrentSchedule_;
    UserControl ^ CurrentSchedulePanel;

  private: System::Windows::Forms::Label^  lblSchedule;
  private: System::Windows::Forms::ComboBox^  cboxSchedule;

  private: System::Windows::Forms::Panel^  panelSchedule;



	private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->lblSchedule = (gcnew System::Windows::Forms::Label());
      this->cboxSchedule = (gcnew System::Windows::Forms::ComboBox());
      this->panelSchedule = (gcnew System::Windows::Forms::Panel());
      this->SuspendLayout();
      // 
      // lblSchedule
      // 
      this->lblSchedule->AutoSize = true;
      this->lblSchedule->Location = System::Drawing::Point(3, 6);
      this->lblSchedule->Name = L"lblSchedule";
      this->lblSchedule->Size = System::Drawing::Size(55, 13);
      this->lblSchedule->TabIndex = 2;
      this->lblSchedule->Text = L"Schedule:";
      // 
      // cboxSchedule
      // 
      this->cboxSchedule->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      this->cboxSchedule->FormattingEnabled = true;
      this->cboxSchedule->Location = System::Drawing::Point(64, 3);
      this->cboxSchedule->Name = L"cboxSchedule";
      this->cboxSchedule->Size = System::Drawing::Size(122, 21);
      this->cboxSchedule->TabIndex = 3;
      this->cboxSchedule->SelectionChangeCommitted += gcnew System::EventHandler(this, &ScheduleControl::OnScheduleChange);
      // 
      // panelSchedule
      // 
      this->panelSchedule->Location = System::Drawing::Point(64, 30);
      this->panelSchedule->Name = L"panelSchedule";
      this->panelSchedule->Size = System::Drawing::Size(420, 200);
      this->panelSchedule->TabIndex = 17;
      this->panelSchedule->Visible = false;
      // 
      // ScheduleControl
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->Controls->Add(this->panelSchedule);
      this->Controls->Add(this->cboxSchedule);
      this->Controls->Add(this->lblSchedule);
      this->Name = L"ScheduleControl";
      this->Size = System::Drawing::Size(491, 238);
      this->Load += gcnew System::EventHandler(this, &ScheduleControl::OnLoad);
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  };
}
