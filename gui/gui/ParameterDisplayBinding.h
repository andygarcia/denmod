#pragma once



namespace gui {



public ref class ParameterDisplayBinding : public System::Windows::Forms::Binding
{
#pragma region Constructors
public:
  ParameterDisplayBinding( System::String ^ propertyName, System::Object ^ dataSource, System::String ^ dataMember );
  ParameterDisplayBinding( System::String ^ propertyName, System::Object ^ dataSource, System::String ^ dataMember,
                  System::Windows::Forms::DataSourceUpdateMode dataSourceUpdateMode );
  virtual ~ParameterDisplayBinding(void);
#pragma endregion

#pragma region Methods
protected:
  virtual void OnFormat( System::Windows::Forms::ConvertEventArgs ^ cea ) override;
  System::String ^ FormatDouble(double d);
#pragma endregion

#pragma region Fields
private:
  ParameterDisplayAttribute ^ _parameterDisplayAttribute;
#pragma endregion
};

};
