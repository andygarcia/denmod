#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



namespace gui {

	public ref class WeatherForm : public System::Windows::Forms::Form
	{
  // Constructors
	public:
		WeatherForm( BindingSource ^ locationBinding, WeatherYear ^ weatheryear );
	protected:
		~WeatherForm();

  // Methods
  private:
    System::Void OnLoad( System::Object ^ sender, System::EventArgs ^ e );
    System::Void OnOk( System::Object ^ sender, System::EventArgs ^ e );

    // Members
  private:
    BindingSource ^ LocationBinding_;
    WeatherYear ^ WeatherYear_;
  private: System::Windows::Forms::DataGridView^  dgvWeather;


  private: System::Windows::Forms::GroupBox^  gboxDescription;
  private: System::Windows::Forms::TextBox^  tboxElevation;
  private: System::Windows::Forms::Label^  lblElevation;
  private: System::Windows::Forms::TextBox^  tboxLongitude;
  private: System::Windows::Forms::Label^  lblLongitude;
  private: System::Windows::Forms::TextBox^  tboxLatitude;
  private: System::Windows::Forms::Label^  lblLatitude;
  private: System::Windows::Forms::TextBox^  tboxCountry;
  private: System::Windows::Forms::Label^  lblCountry;
  private: System::Windows::Forms::TextBox^  tboxProvince;
  private: System::Windows::Forms::Label^  lblProvince;
  private: System::Windows::Forms::TextBox^  tboxYear;
  private: System::Windows::Forms::Label^  lblYear;
  private: System::Windows::Forms::TextBox^  tboxCity;
  private: System::Windows::Forms::Label^  lblCity;
  private: System::Windows::Forms::TextBox^  tboxSource;
  private: System::Windows::Forms::Label^  lblSource;
  private: System::Windows::Forms::GroupBox^  gboxPreview;
  private: System::Windows::Forms::Button^  btnOk;
  private: System::Windows::Forms::Button^  btnCancel;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcDay;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcMinTemp;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcAvgTemp;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcMaxTemp;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcRain;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcRelHum;
  private: System::Windows::Forms::DataGridViewTextBoxColumn^  dgvcSatDef;
  private: System::Windows::Forms::ErrorProvider^  errPro;
  private: System::ComponentModel::IContainer^  components;

















#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->components = (gcnew System::ComponentModel::Container());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle29 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle30 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle31 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle32 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle33 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle34 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle35 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
      this->dgvWeather = (gcnew System::Windows::Forms::DataGridView());
      this->gboxDescription = (gcnew System::Windows::Forms::GroupBox());
      this->tboxCity = (gcnew System::Windows::Forms::TextBox());
      this->tboxElevation = (gcnew System::Windows::Forms::TextBox());
      this->lblElevation = (gcnew System::Windows::Forms::Label());
      this->lblCity = (gcnew System::Windows::Forms::Label());
      this->tboxLongitude = (gcnew System::Windows::Forms::TextBox());
      this->lblLongitude = (gcnew System::Windows::Forms::Label());
      this->tboxLatitude = (gcnew System::Windows::Forms::TextBox());
      this->lblLatitude = (gcnew System::Windows::Forms::Label());
      this->tboxSource = (gcnew System::Windows::Forms::TextBox());
      this->lblSource = (gcnew System::Windows::Forms::Label());
      this->tboxCountry = (gcnew System::Windows::Forms::TextBox());
      this->lblCountry = (gcnew System::Windows::Forms::Label());
      this->tboxProvince = (gcnew System::Windows::Forms::TextBox());
      this->lblProvince = (gcnew System::Windows::Forms::Label());
      this->lblYear = (gcnew System::Windows::Forms::Label());
      this->tboxYear = (gcnew System::Windows::Forms::TextBox());
      this->gboxPreview = (gcnew System::Windows::Forms::GroupBox());
      this->btnOk = (gcnew System::Windows::Forms::Button());
      this->btnCancel = (gcnew System::Windows::Forms::Button());
      this->dgvcDay = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcMinTemp = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcAvgTemp = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcMaxTemp = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcRain = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcRelHum = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->dgvcSatDef = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
      this->errPro = (gcnew System::Windows::Forms::ErrorProvider(this->components));
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvWeather))->BeginInit();
      this->gboxDescription->SuspendLayout();
      this->gboxPreview->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errPro))->BeginInit();
      this->SuspendLayout();
      // 
      // dgvWeather
      // 
      this->dgvWeather->AllowUserToAddRows = false;
      this->dgvWeather->AllowUserToDeleteRows = false;
      this->dgvWeather->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->dgvWeather->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
      this->dgvWeather->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
      this->dgvWeather->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
      this->dgvWeather->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(7) {this->dgvcDay, this->dgvcMinTemp, 
        this->dgvcAvgTemp, this->dgvcMaxTemp, this->dgvcRain, this->dgvcRelHum, this->dgvcSatDef});
      this->dgvWeather->Location = System::Drawing::Point(6, 19);
      this->dgvWeather->Name = L"dgvWeather";
      this->dgvWeather->ReadOnly = true;
      this->dgvWeather->RowHeadersVisible = false;
      this->dgvWeather->Size = System::Drawing::Size(660, 250);
      this->dgvWeather->TabIndex = 0;
      // 
      // gboxDescription
      // 
      this->gboxDescription->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->gboxDescription->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
      this->gboxDescription->Controls->Add(this->tboxCity);
      this->gboxDescription->Controls->Add(this->tboxElevation);
      this->gboxDescription->Controls->Add(this->lblElevation);
      this->gboxDescription->Controls->Add(this->lblCity);
      this->gboxDescription->Controls->Add(this->tboxLongitude);
      this->gboxDescription->Controls->Add(this->lblLongitude);
      this->gboxDescription->Controls->Add(this->tboxLatitude);
      this->gboxDescription->Controls->Add(this->lblLatitude);
      this->gboxDescription->Controls->Add(this->tboxSource);
      this->gboxDescription->Controls->Add(this->lblSource);
      this->gboxDescription->Controls->Add(this->tboxCountry);
      this->gboxDescription->Controls->Add(this->lblCountry);
      this->gboxDescription->Controls->Add(this->tboxProvince);
      this->gboxDescription->Controls->Add(this->lblProvince);
      this->gboxDescription->Location = System::Drawing::Point(12, 38);
      this->gboxDescription->Name = L"gboxDescription";
      this->gboxDescription->Size = System::Drawing::Size(672, 136);
      this->gboxDescription->TabIndex = 2;
      this->gboxDescription->TabStop = false;
      this->gboxDescription->Text = L"Description:";
      // 
      // tboxCity
      // 
      this->tboxCity->Location = System::Drawing::Point(64, 19);
      this->tboxCity->Name = L"tboxCity";
      this->tboxCity->Size = System::Drawing::Size(100, 20);
      this->tboxCity->TabIndex = 1;
      // 
      // tboxElevation
      // 
      this->tboxElevation->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->tboxElevation->Location = System::Drawing::Point(566, 71);
      this->tboxElevation->Name = L"tboxElevation";
      this->tboxElevation->Size = System::Drawing::Size(100, 20);
      this->tboxElevation->TabIndex = 13;
      // 
      // lblElevation
      // 
      this->lblElevation->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->lblElevation->AutoSize = true;
      this->lblElevation->Location = System::Drawing::Point(489, 74);
      this->lblElevation->Name = L"lblElevation";
      this->lblElevation->Size = System::Drawing::Size(71, 13);
      this->lblElevation->TabIndex = 12;
      this->lblElevation->Text = L"Elevation (m):";
      // 
      // lblCity
      // 
      this->lblCity->AutoSize = true;
      this->lblCity->Location = System::Drawing::Point(31, 22);
      this->lblCity->Name = L"lblCity";
      this->lblCity->Size = System::Drawing::Size(27, 13);
      this->lblCity->TabIndex = 0;
      this->lblCity->Text = L"City:";
      // 
      // tboxLongitude
      // 
      this->tboxLongitude->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->tboxLongitude->Location = System::Drawing::Point(566, 45);
      this->tboxLongitude->Name = L"tboxLongitude";
      this->tboxLongitude->Size = System::Drawing::Size(100, 20);
      this->tboxLongitude->TabIndex = 11;
      // 
      // lblLongitude
      // 
      this->lblLongitude->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->lblLongitude->AutoSize = true;
      this->lblLongitude->Location = System::Drawing::Point(503, 48);
      this->lblLongitude->Name = L"lblLongitude";
      this->lblLongitude->Size = System::Drawing::Size(57, 13);
      this->lblLongitude->TabIndex = 10;
      this->lblLongitude->Text = L"Longitude:";
      // 
      // tboxLatitude
      // 
      this->tboxLatitude->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->tboxLatitude->Location = System::Drawing::Point(566, 19);
      this->tboxLatitude->Name = L"tboxLatitude";
      this->tboxLatitude->Size = System::Drawing::Size(100, 20);
      this->tboxLatitude->TabIndex = 9;
      // 
      // lblLatitude
      // 
      this->lblLatitude->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->lblLatitude->AutoSize = true;
      this->lblLatitude->Location = System::Drawing::Point(509, 22);
      this->lblLatitude->Name = L"lblLatitude";
      this->lblLatitude->Size = System::Drawing::Size(51, 13);
      this->lblLatitude->TabIndex = 8;
      this->lblLatitude->Text = L"Latitutde:";
      // 
      // tboxSource
      // 
      this->tboxSource->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->tboxSource->Location = System::Drawing::Point(64, 97);
      this->tboxSource->Name = L"tboxSource";
      this->tboxSource->Size = System::Drawing::Size(602, 20);
      this->tboxSource->TabIndex = 7;
      // 
      // lblSource
      // 
      this->lblSource->AutoSize = true;
      this->lblSource->Location = System::Drawing::Point(14, 100);
      this->lblSource->Name = L"lblSource";
      this->lblSource->Size = System::Drawing::Size(44, 13);
      this->lblSource->TabIndex = 6;
      this->lblSource->Text = L"Source:";
      // 
      // tboxCountry
      // 
      this->tboxCountry->Location = System::Drawing::Point(64, 71);
      this->tboxCountry->Name = L"tboxCountry";
      this->tboxCountry->Size = System::Drawing::Size(100, 20);
      this->tboxCountry->TabIndex = 5;
      // 
      // lblCountry
      // 
      this->lblCountry->AutoSize = true;
      this->lblCountry->Location = System::Drawing::Point(12, 74);
      this->lblCountry->Name = L"lblCountry";
      this->lblCountry->Size = System::Drawing::Size(46, 13);
      this->lblCountry->TabIndex = 4;
      this->lblCountry->Text = L"Country:";
      // 
      // tboxProvince
      // 
      this->tboxProvince->Location = System::Drawing::Point(64, 45);
      this->tboxProvince->Name = L"tboxProvince";
      this->tboxProvince->Size = System::Drawing::Size(100, 20);
      this->tboxProvince->TabIndex = 3;
      // 
      // lblProvince
      // 
      this->lblProvince->AutoSize = true;
      this->lblProvince->Location = System::Drawing::Point(6, 48);
      this->lblProvince->Name = L"lblProvince";
      this->lblProvince->Size = System::Drawing::Size(52, 13);
      this->lblProvince->TabIndex = 2;
      this->lblProvince->Text = L"Province:";
      // 
      // lblYear
      // 
      this->lblYear->AutoSize = true;
      this->lblYear->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->lblYear->Location = System::Drawing::Point(33, 15);
      this->lblYear->Name = L"lblYear";
      this->lblYear->Size = System::Drawing::Size(37, 13);
      this->lblYear->TabIndex = 0;
      this->lblYear->Text = L"Year:";
      // 
      // tboxYear
      // 
      this->tboxYear->Location = System::Drawing::Point(76, 12);
      this->tboxYear->Name = L"tboxYear";
      this->tboxYear->Size = System::Drawing::Size(50, 20);
      this->tboxYear->TabIndex = 1;
      // 
      // gboxPreview
      // 
      this->gboxPreview->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
        | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->gboxPreview->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
      this->gboxPreview->Controls->Add(this->dgvWeather);
      this->gboxPreview->Location = System::Drawing::Point(12, 183);
      this->gboxPreview->Name = L"gboxPreview";
      this->gboxPreview->Size = System::Drawing::Size(672, 275);
      this->gboxPreview->TabIndex = 3;
      this->gboxPreview->TabStop = false;
      this->gboxPreview->Text = L"Preview:";
      // 
      // btnOk
      // 
      this->btnOk->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnOk->DialogResult = System::Windows::Forms::DialogResult::OK;
      this->btnOk->Location = System::Drawing::Point(528, 464);
      this->btnOk->Name = L"btnOk";
      this->btnOk->Size = System::Drawing::Size(75, 23);
      this->btnOk->TabIndex = 4;
      this->btnOk->Text = L"OK";
      this->btnOk->UseVisualStyleBackColor = true;
      this->btnOk->Click += gcnew System::EventHandler(this, &WeatherForm::OnOk);
      // 
      // btnCancel
      // 
      this->btnCancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
      this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
      this->btnCancel->Location = System::Drawing::Point(609, 464);
      this->btnCancel->Name = L"btnCancel";
      this->btnCancel->Size = System::Drawing::Size(75, 23);
      this->btnCancel->TabIndex = 5;
      this->btnCancel->Text = L"Cancel";
      this->btnCancel->UseVisualStyleBackColor = true;
      // 
      // dgvcDay
      // 
      this->dgvcDay->DataPropertyName = L"Index";
      dataGridViewCellStyle29->Format = L"N0";
      dataGridViewCellStyle29->NullValue = nullptr;
      this->dgvcDay->DefaultCellStyle = dataGridViewCellStyle29;
      this->dgvcDay->HeaderText = L"Day of Year";
      this->dgvcDay->Name = L"dgvcDay";
      this->dgvcDay->ReadOnly = true;
      this->dgvcDay->Width = 89;
      // 
      // dgvcMinTemp
      // 
      this->dgvcMinTemp->DataPropertyName = L"MinTemp";
      dataGridViewCellStyle30->Format = L"N1";
      dataGridViewCellStyle30->NullValue = nullptr;
      this->dgvcMinTemp->DefaultCellStyle = dataGridViewCellStyle30;
      this->dgvcMinTemp->HeaderText = L"Min. Temp (C)";
      this->dgvcMinTemp->Name = L"dgvcMinTemp";
      this->dgvcMinTemp->ReadOnly = true;
      this->dgvcMinTemp->Width = 99;
      // 
      // dgvcAvgTemp
      // 
      this->dgvcAvgTemp->DataPropertyName = L"AvgTemp";
      dataGridViewCellStyle31->Format = L"N1";
      dataGridViewCellStyle31->NullValue = nullptr;
      this->dgvcAvgTemp->DefaultCellStyle = dataGridViewCellStyle31;
      this->dgvcAvgTemp->HeaderText = L"Avg. Temp (C)";
      this->dgvcAvgTemp->Name = L"dgvcAvgTemp";
      this->dgvcAvgTemp->ReadOnly = true;
      this->dgvcAvgTemp->Width = 101;
      // 
      // dgvcMaxTemp
      // 
      this->dgvcMaxTemp->DataPropertyName = L"MaxTemp";
      dataGridViewCellStyle32->Format = L"N1";
      dataGridViewCellStyle32->NullValue = nullptr;
      this->dgvcMaxTemp->DefaultCellStyle = dataGridViewCellStyle32;
      this->dgvcMaxTemp->HeaderText = L"Max. Temp (C)";
      this->dgvcMaxTemp->Name = L"dgvcMaxTemp";
      this->dgvcMaxTemp->ReadOnly = true;
      this->dgvcMaxTemp->Width = 102;
      // 
      // dgvcRain
      // 
      this->dgvcRain->DataPropertyName = L"Rain";
      dataGridViewCellStyle33->Format = L"N2";
      this->dgvcRain->DefaultCellStyle = dataGridViewCellStyle33;
      this->dgvcRain->HeaderText = L"Rain (mm)";
      this->dgvcRain->Name = L"dgvcRain";
      this->dgvcRain->ReadOnly = true;
      this->dgvcRain->Width = 80;
      // 
      // dgvcRelHum
      // 
      this->dgvcRelHum->DataPropertyName = L"RelHum";
      dataGridViewCellStyle34->Format = L"N1";
      dataGridViewCellStyle34->NullValue = nullptr;
      this->dgvcRelHum->DefaultCellStyle = dataGridViewCellStyle34;
      this->dgvcRelHum->HeaderText = L"Relative Humidity (%)";
      this->dgvcRelHum->Name = L"dgvcRelHum";
      this->dgvcRelHum->ReadOnly = true;
      this->dgvcRelHum->Width = 108;
      // 
      // dgvcSatDef
      // 
      this->dgvcSatDef->DataPropertyName = L"SatDef";
      dataGridViewCellStyle35->Format = L"N2";
      dataGridViewCellStyle35->NullValue = nullptr;
      this->dgvcSatDef->DefaultCellStyle = dataGridViewCellStyle35;
      this->dgvcSatDef->HeaderText = L"Saturation Deficit (mbars)";
      this->dgvcSatDef->Name = L"dgvcSatDef";
      this->dgvcSatDef->ReadOnly = true;
      this->dgvcSatDef->Width = 107;
      // 
      // errPro
      // 
      this->errPro->ContainerControl = this;
      // 
      // WeatherForm
      // 
      this->AcceptButton = this->btnOk;
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->CancelButton = this->btnCancel;
      this->ClientSize = System::Drawing::Size(696, 493);
      this->Controls->Add(this->btnCancel);
      this->Controls->Add(this->btnOk);
      this->Controls->Add(this->gboxPreview);
      this->Controls->Add(this->tboxYear);
      this->Controls->Add(this->lblYear);
      this->Controls->Add(this->gboxDescription);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
      this->MinimumSize = System::Drawing::Size(380, 380);
      this->Name = L"WeatherForm";
      this->ShowInTaskbar = false;
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
      this->Text = L"Weather";
      this->Load += gcnew System::EventHandler(this, &WeatherForm::OnLoad);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvWeather))->EndInit();
      this->gboxDescription->ResumeLayout(false);
      this->gboxDescription->PerformLayout();
      this->gboxPreview->ResumeLayout(false);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->errPro))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  };
}
