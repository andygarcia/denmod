#pragma once

ref class ExcelOutput
{
public:
  ExcelOutput(void);
  virtual ~ExcelOutput(void);

  static System::String ^ GetXml( Dundas::Charting::WinControl::Chart ^ chart );
};
