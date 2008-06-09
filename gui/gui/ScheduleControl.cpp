#include "StdAfx.h"
#include "ScheduleControl.h"

using namespace gui;



ScheduleControl::ScheduleControl( BindingSource ^ LocationBinding_, String ^ scheduleBindingSite )
: LocationBinding_(LocationBinding_),
  SingleScheduleBinding_(gcnew BindingSource()),
  WeeklyScheduleBinding_(gcnew BindingSource()),
  MonthlyScheduleBinding_(gcnew BindingSource()),
  YearlyScheduleBinding_(gcnew BindingSource()),
  PeriodicScheduleBinding_(gcnew BindingSource()),
  ScheduleBindingSite_(scheduleBindingSite)
{
	InitializeComponent();

  SingleScheduleBinding_->DataSource = gcnew SingleSchedule();
  WeeklyScheduleBinding_->DataSource = gcnew WeeklySchedule();
  MonthlyScheduleBinding_->DataSource = gcnew MonthlySchedule();
  YearlyScheduleBinding_->DataSource = gcnew YearlySchedule();
  PeriodicScheduleBinding_->DataSource = gcnew PeriodicSchedule();

  cboxMonthlyStartMonth->DataSource = System::Enum::GetValues( gui::Months::typeid );
}



ScheduleControl::~ScheduleControl()
{
  if( components ) {
		delete components;
	}
}



System::Void
ScheduleControl::OnLoad( System::Object ^ sender, System::EventArgs ^ e )
{
  DataBindings->Add( "CurrentSchedule", LocationBinding_, ScheduleBindingSite_, false, DataSourceUpdateMode::OnPropertyChanged);


  // single schedule bindings
  dateTimeSingleStart->DataBindings->Add( "MinDate", LocationBinding_, "Weather.MinDate", false, DataSourceUpdateMode::Never );
  dateTimeSingleStart->DataBindings->Add( "MaxDate", LocationBinding_, "Weather.MaxDate", false, DataSourceUpdateMode::Never );
  dateTimeSingleStart->DataBindings->Add( "Value", SingleScheduleBinding_, "Date", false, DataSourceUpdateMode::OnPropertyChanged );


  // weekly schedule bindings
  dateTimeWeeklyStart->DataBindings->Add( "MinDate", LocationBinding_, "Weather.MinDate", false, DataSourceUpdateMode::Never );
  dateTimeWeeklyStart->DataBindings->Add( "MaxDate", LocationBinding_, "Weather.MaxDate", false, DataSourceUpdateMode::Never );
  dateTimeWeeklyStart->DataBindings->Add( "Value", WeeklyScheduleBinding_, "StartDate", false, DataSourceUpdateMode::OnPropertyChanged );

  numWeeklyInterval->DataBindings->Add( "Text", WeeklyScheduleBinding_, "WeekInterval", false, DataSourceUpdateMode::OnPropertyChanged );

  checkSunday->DataBindings->Add( "Checked", WeeklyScheduleBinding_, "Sunday", false, DataSourceUpdateMode::OnPropertyChanged );
  checkMonday->DataBindings->Add( "Checked", WeeklyScheduleBinding_, "Monday", false, DataSourceUpdateMode::OnPropertyChanged );
  checkTuesday->DataBindings->Add( "Checked", WeeklyScheduleBinding_, "Tuesday", false, DataSourceUpdateMode::OnPropertyChanged );
  checkWednesday->DataBindings->Add( "Checked", WeeklyScheduleBinding_, "Wednesday", false, DataSourceUpdateMode::OnPropertyChanged );
  checkThursday->DataBindings->Add( "Checked", WeeklyScheduleBinding_, "Thursday", false, DataSourceUpdateMode::OnPropertyChanged );
  checkFriday->DataBindings->Add( "Checked", WeeklyScheduleBinding_, "Friday", false, DataSourceUpdateMode::OnPropertyChanged );
  checkSaturday->DataBindings->Add( "Checked", WeeklyScheduleBinding_, "Saturday", false, DataSourceUpdateMode::OnPropertyChanged );

  checkWeeklyEnd->DataBindings->Add( "Checked", WeeklyScheduleBinding_, "UseStopDate", false, DataSourceUpdateMode::OnPropertyChanged );

  dateTimeWeeklyEnd->DataBindings->Add( "MinDate", LocationBinding_, "Weather.MinDate", false, DataSourceUpdateMode::Never );
  dateTimeWeeklyEnd->DataBindings->Add( "MaxDate", LocationBinding_, "Weather.MaxDate", false, DataSourceUpdateMode::Never );
  dateTimeWeeklyEnd->DataBindings->Add( "Enabled", WeeklyScheduleBinding_, "UseStopDate", false, DataSourceUpdateMode::OnPropertyChanged );
  dateTimeWeeklyEnd->DataBindings->Add( "Value", WeeklyScheduleBinding_, "StopDate", false, DataSourceUpdateMode::OnPropertyChanged );


  // monthly schedule bindings
  cboxMonthlyStartMonth->DataBindings->Add( "SelectedItem", MonthlyScheduleBinding_, "StartMonth", false, DataSourceUpdateMode::OnPropertyChanged );
  cboxMonthlyStartYear->ValueMember = "Index";
  cboxMonthlyStartYear->DisplayMember = "Index";
  cboxMonthlyStartYear->DataBindings->Add( "DataSource", LocationBinding_, "Weather.YearsBindingList" );
  cboxMonthlyStartYear->DataBindings->Add( "SelectedValue", MonthlyScheduleBinding_, "StartYear", false, DataSourceUpdateMode::OnPropertyChanged );
  numMonthlyInterval->DataBindings->Add( "Text", MonthlyScheduleBinding_, "MonthInterval", false, DataSourceUpdateMode::OnPropertyChanged );
  cboxMonthlyDay->DataBindings->Add( "SelectedItem", MonthlyScheduleBinding_, "DayOfMonth", false, DataSourceUpdateMode::OnPropertyChanged );
  checkMonthlyEnd->DataBindings->Add( "Checked", MonthlyScheduleBinding_, "UseStopDate", false, DataSourceUpdateMode::OnPropertyChanged );
  dateTimeMonthlyEnd->DataBindings->Add( "MinDate", LocationBinding_, "Weather.MinDate", false, DataSourceUpdateMode::Never );
  dateTimeMonthlyEnd->DataBindings->Add( "MaxDate", LocationBinding_, "Weather.MaxDate", false, DataSourceUpdateMode::Never );
  dateTimeMonthlyEnd->DataBindings->Add( "Enabled", MonthlyScheduleBinding_, "UseStopDate",false,  DataSourceUpdateMode::OnPropertyChanged );
  dateTimeMonthlyEnd->DataBindings->Add( "Value", MonthlyScheduleBinding_, "StopDate", false, DataSourceUpdateMode::OnPropertyChanged );


  // yearly schedule bindings
  cboxYearlyStart->ValueMember = "Index";
  cboxYearlyStart->DisplayMember = "Index";
  cboxYearlyStart->DataBindings->Add( "DataSource", LocationBinding_, "Weather.YearsBindingList" );
  cboxYearlyStart->DataBindings->Add( "SelectedValue", YearlyScheduleBinding_, "StartYear", false, DataSourceUpdateMode::OnPropertyChanged );
  numYearlyInterval->DataBindings->Add( "Text", YearlyScheduleBinding_, "YearInterval", false, DataSourceUpdateMode::OnPropertyChanged );
  numYearlyDay->DataBindings->Add( "Text", YearlyScheduleBinding_, "DayOfYear", false, DataSourceUpdateMode::OnPropertyChanged );


  // periodic schedule bindings
  dateTimePeriodicStart->DataBindings->Add( "MinDate", LocationBinding_, "Weather.MinDate", false, DataSourceUpdateMode::Never );
  dateTimePeriodicStart->DataBindings->Add( "MaxDate", LocationBinding_, "Weather.MaxDate", false, DataSourceUpdateMode::Never );
  dateTimePeriodicStart->DataBindings->Add( "Value", PeriodicScheduleBinding_, "StartDate", false, DataSourceUpdateMode::OnPropertyChanged );
  numPeriodicInterval->DataBindings->Add( "Text", PeriodicScheduleBinding_, "TreatmentInterval", false, DataSourceUpdateMode::OnPropertyChanged );
  checkPeriodicTreatments->DataBindings->Add( "Checked", PeriodicScheduleBinding_, "UseTreatments", false, DataSourceUpdateMode::OnPropertyChanged );
  numPeriodicTreatments->DataBindings->Add( "Enabled", PeriodicScheduleBinding_, "UseTreatments", false, DataSourceUpdateMode::OnPropertyChanged );
  numPeriodicTreatments->DataBindings->Add( "Text", PeriodicScheduleBinding_, "NumberOfTreatments", false, DataSourceUpdateMode::OnPropertyChanged );
  checkPeriodicStop->DataBindings->Add( "Checked", PeriodicScheduleBinding_, "UseStopDate", false, DataSourceUpdateMode::OnPropertyChanged );
  dateTimePeriodicStop->DataBindings->Add( "MinDate", LocationBinding_, "Weather.MinDate", false, DataSourceUpdateMode::Never );
  dateTimePeriodicStop->DataBindings->Add( "MaxDate", LocationBinding_, "Weather.MaxDate", false, DataSourceUpdateMode::Never );
  dateTimePeriodicStop->DataBindings->Add( "Enabled", PeriodicScheduleBinding_, "UseStopDate", false, DataSourceUpdateMode::OnPropertyChanged );
  dateTimePeriodicStop->DataBindings->Add( "Value", PeriodicScheduleBinding_, "StopDate", false, DataSourceUpdateMode::OnPropertyChanged );
}



System::Void
ScheduleControl::OnSelectedIndexChanged( System::Object ^ sender, System::EventArgs ^ e )
{
  int selectedTab = tabSchedule->SelectedIndex;
  if( selectedTab ==  0 ) {
    CurrentSchedule_ = (SingleSchedule^) SingleScheduleBinding_->DataSource;
  }
  else if( selectedTab == 1 ) {
    CurrentSchedule_ = (WeeklySchedule^) WeeklyScheduleBinding_->DataSource;
  }
  else if( selectedTab == 2 ) {
    CurrentSchedule_ = (MonthlySchedule^) MonthlyScheduleBinding_->DataSource;
  }
  else if( selectedTab == 3 ) {
    CurrentSchedule_ = (YearlySchedule^) YearlyScheduleBinding_->DataSource;
  }
  else if( selectedTab == 4 ) {
    CurrentSchedule_ = (PeriodicSchedule^) PeriodicScheduleBinding_->DataSource;
  }
  NotifyPropertyChanged( "CurrentSchedule" );
}



System::Void
ScheduleControl::MonthIndexToMonthString( System::Object ^ sender, ConvertEventArgs ^ cea )
{
  // converting month index to string representation
  cea->Value = System::Enum::GetName( gui::Months::typeid, cea->Value );
}



Schedule ^
ScheduleControl::CurrentSchedule::get(void)
{
  return CurrentSchedule_;
}



void
ScheduleControl::CurrentSchedule::set( Schedule ^ schedule )
{
  if( schedule == nullptr ) {
    return;
  }
  else if( CurrentSchedule != nullptr && CurrentSchedule_->Equals(schedule) ) {
    return;    
  }

  CurrentSchedule_ = schedule;
  System::Type ^ schedType = CurrentSchedule_->GetType();
  if( schedType == SingleSchedule::typeid ) {
    SingleScheduleBinding_->DataSource = gcnew SingleSchedule((SingleSchedule^) schedule );
  }

  if( schedType == WeeklySchedule::typeid ) {
    WeeklyScheduleBinding_->DataSource = gcnew WeeklySchedule((WeeklySchedule^) schedule );
  }

  if( schedType == MonthlySchedule::typeid ) {
    MonthlyScheduleBinding_->DataSource = gcnew MonthlySchedule((MonthlySchedule^) schedule );
  }

  if( schedType == YearlySchedule::typeid ) {
    YearlyScheduleBinding_->DataSource = gcnew YearlySchedule((YearlySchedule^) schedule );
  }

  if( schedType == PeriodicSchedule::typeid ) {
    PeriodicScheduleBinding_->DataSource = gcnew PeriodicSchedule((PeriodicSchedule^) schedule );
  }

  DateTime minDate = ((gui::Location^) LocationBinding_->Current)->Weather->MinDate;
  DateTime maxDate = ((gui::Location^) LocationBinding_->Current)->Weather->MaxDate;

  SingleSchedule ^ ss = (SingleSchedule^) SingleScheduleBinding_->DataSource;
  WeeklySchedule ^ ws = (WeeklySchedule^) WeeklyScheduleBinding_->DataSource;
  MonthlySchedule ^ ms = (MonthlySchedule^) MonthlyScheduleBinding_->DataSource;
  YearlySchedule ^ ys = (YearlySchedule^) YearlyScheduleBinding_->DataSource;
  PeriodicSchedule ^ ps = (PeriodicSchedule^) PeriodicScheduleBinding_->DataSource;

  if( ss->Date < minDate ) {
    ss->Date = minDate;
  }
  if( ss->Date > maxDate ) {
    ss->Date = maxDate;
  }

  ws->MinDate = minDate;
  ws->MaxDate = maxDate;

  ms->MinDate = minDate;
  ms->MaxDate = maxDate;

  ys->MinDate = minDate;
  ys->MaxDate = maxDate;

  ps->MinDate = minDate;
  ps->MaxDate = maxDate;

  numPeriodicInterval->Maximum = (maxDate - minDate).Days;

  tabSchedule->SelectTab( schedule->ScheduleTypeIndex );
  NotifyPropertyChanged("CurrentSchedule");
}
