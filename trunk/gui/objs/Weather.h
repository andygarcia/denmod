#pragma once

#include "NotifyValidateEditBase.h"
#include <algorithm>

#pragma managed( push, off )
#include "../../simulation/input/Weather.h"
#pragma managed( pop )

using namespace System::Xml;
using namespace System::Xml::Schema;
using namespace System::Xml::Serialization;
using namespace System::Collections;
using System::DateTime;
using System::ComponentModel::BindingList;
using namespace ValidationFramework;



namespace gui {



[XmlRoot("Day")]
public ref class WeatherDay : public NotifyValidateEditBase
{
// Constants
  static const int MILLIMETERS_PER_CENTIMETERS = 10;

// Enums
public:
  enum class VaporPressureMethod {
    GoffGrach = 0,
    MagnusTeten
  };

// Constructors
public:
  WeatherDay(void);
  ~WeatherDay(void);

// Methods
public:
  input::WeatherDay * GetSimObject(void);
  void CalculateSaturationDeficit( VaporPressureMethod method );

private:
  static double GoffGrach( double temperatureCelsius );
  static double MagnusTeten( double temperatureCelsius );

// Properties
public:
  [XmlAttribute(AttributeName="relHum")]
  property double RelHum {
    double get(void) {
      return RelHum_;
    }
    void set(double d) {
      RelHum_ = d;
      NotifyPropertyChanged( "RelHum" );
    }
  }

  [XmlAttribute(AttributeName="rain")]
  property double Rain {
    double get(void) {
      return Rain_;
    }
    void set(double d) {
      Rain_ = d;
      NotifyPropertyChanged( "Rain" );
    }
  }


  [XmlAttribute(AttributeName="satDef")]
  property double SatDef {
    double get(void) {
      return SatDef_;
    }
    void set(double d) {
      SatDef_ = d;
      NotifyPropertyChanged( "SatDef" );
    }
  }


  [XmlAttribute(AttributeName="maxTemp")]
  property double MaxTemp {
    double get(void) {
      return MaxTemp_;
    }
    void set(double d) {
      MaxTemp_ = d;
      NotifyPropertyChanged( "MaxTemp" );
    }
  }


  [XmlAttribute(AttributeName="avgTemp")]
  property double AvgTemp {
    double get(void) {
      return AvgTemp_;
    }
    void set(double d) {
      AvgTemp_ = d;
      NotifyPropertyChanged( "AvgTemp" );
    }
  }


  [XmlAttribute(AttributeName="minTemp")]
  property double MinTemp {
    double get(void) {
      return MinTemp_;
    }
    void set(double d) {
      MinTemp_ = d;
      NotifyPropertyChanged( "MinTemp" );
    }
  }

  [XmlAttribute(AttributeName="index")]
  property int Index {
    int get(void) {
      return Index_;
    }
    void set(int i) {
      Index_ = i;
      NotifyPropertyChanged( "Index" );
    }
  }

private:
  int Index_;
  double MinTemp_;
  double AvgTemp_;
  double MaxTemp_;
  double SatDef_;
  double Rain_;
  double RelHum_;
};



[XmlRoot("Year")]
public ref class WeatherYear : public NotifyValidateEditBase, IXmlSerializable
{
// Enum
public:
  enum class ImportSourceEnum {
    None = 0,
    Excel,
    Dly
  };

// Constructors
public:
  WeatherYear(void);
  ~WeatherYear(void);

// Methods
public:
  static WeatherYear ^ OpenFromXls( System::String ^ filename );
  static WeatherYear ^ OpenFromDly( System::String ^ filename );

  input::WeatherYear * GetSimObject(void);

  virtual void WriteXml( XmlWriter ^ xw );
  virtual void ReadXml( XmlReader ^ xr );
  virtual XmlSchema ^ GetSchema(void);

private:
  static System::Data::OleDb::OleDbConnection ^ TryExcelConnection( System::String ^ filename );
    
// Properties
public:
  [XmlAttribute(AttributeName="source")]
  property System::String ^ Source {
    System::String ^ get(void);
    void set(System::String ^ i);
  }

  [XmlAttribute(AttributeName="elevation")]
  property System::String ^ Elevation {
    System::String ^ get(void);
    void set(System::String ^ i);
  }

  [XmlAttribute(AttributeName="longitude")]
  property System::String ^ Longitude {
    System::String ^ get(void);
    void set(System::String ^ i);
  }

  [XmlAttribute(AttributeName="latitude")]
  property System::String ^ Latitude {
    System::String ^ get(void);
    void set(System::String ^ i);
  }

  [XmlAttribute(AttributeName="country")]
  property System::String ^ Country {
    System::String ^ get(void);
    void set(System::String ^ i);
  }

  [XmlAttribute(AttributeName="province")]
  property System::String ^ Province {
    System::String ^ get(void);
    void set(System::String ^ i);
  }

  [XmlAttribute(AttributeName="city")]
  property System::String ^ City {
    System::String ^ get(void);
    void set(System::String ^ i);
  }

  [XmlAttribute(AttributeName="index")]
  [CompareIntRule( 0, CompareOperator::GreaterThan, ErrorMessage = "Invalid year." )]
  property int Index {
    int get(void);
    void set(int i);
  }

  [XmlArrayItem(ElementName="Day",Type=gui::WeatherDay::typeid)]
  property BindingList<WeatherDay^>^ Days {
    BindingList<WeatherDay^>^ get(void);
    void set( BindingList<WeatherDay^>^ d );
  }

  [XmlIgnore]
  property DateTime MinDate {
    DateTime get(void);
  }

  [XmlIgnore]
  property DateTime MaxDate {
    DateTime get(void);
  }

  [XmlIgnore]
  property ImportSourceEnum ImportSource {
    ImportSourceEnum get(void) {
      return ImportSource_;
    }
  }
private:
  int Index_;
  System::String ^ City_;
  System::String ^ Province_;
  System::String ^ Country_;
  System::String ^ Latitude_;
  System::String ^ Longitude_;
  System::String ^ Elevation_;
  System::String ^ Source_;

  BindingList<WeatherDay^> ^ Days_;

  ImportSourceEnum ImportSource_;
};



public ref class ExcelWeatherDataException : public System::Exception
{
public:
  ExcelWeatherDataException( int rowIndex, System::Exception ^ innerException )
  : Exception("Error in excel file at row " + rowIndex, innerException),
    _rowIndex(rowIndex)
  {}

public:
  property int RowIndex {
    int get(void) {
      return _rowIndex;
    }
  }
protected:
  int _rowIndex;
};



public ref class DlyWeatherDataException : public System::Exception
{
public:
  DlyWeatherDataException( int rowIndex, System::Exception ^ innerException )
  : Exception("Error in excel file at row " + rowIndex, innerException),
    _rowIndex(rowIndex)
  {}

public:
  property int RowIndex {
    int get(void) {
      return _rowIndex;
    }
  }
protected:
  int _rowIndex;
};



public ref class WeatherData : public NotifyValidateEditBase
{
// Constructors
public:
  WeatherData(void);
  ~WeatherData(void);

// Methods
public:
  input::Weather * GetSimObject(void);

  void AddWeatherYear( WeatherYear ^ wy );
  bool IsWeatherYearAvailable( int year );
  WeatherYear ^ GetWeatherYear( int year );
  WeatherDay ^ GetWeather( DateTime dt );
  void RemoveWeatherYear( int year );

  bool IsWeatherDataContiguous(void);
  Generic::List<int> ^ GetMissingWeatherYears(void);

// Properties
public:
  [XmlElementAttribute(ElementName="Year",Type=gui::WeatherYear::typeid)]
  property BindingList<WeatherYear^> ^ Years {
    BindingList<WeatherYear^> ^ get(void);
    void set( BindingList<WeatherYear^> ^ bl );
  }

  [XmlIgnore]
  property DateTime MinDate {
    DateTime get(void);
  }

  [XmlIgnore]
  property DateTime MaxDate {
    DateTime get(void);
  }

  [XmlIgnore]
  property int NumberOfYears {
    int get(void);
  }

  [XmlIgnore]
  property bool IsWeatherAvailable {
    bool get(void) {
      if( Years_->Count == 0 ) {
        return false;
      }
      else {
        return true;
      }
    }
  }

private:
  BindingList<WeatherYear^> ^ Years_;
};

};
