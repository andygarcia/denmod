#include "StdAfx.h"
#include "ScheduleForm.h"

using namespace gui;


ScheduleForm::ScheduleForm( DateTime minDate, DateTime maxDate, Schedule ^ schedule )
{
	InitializeComponent();

  MinDate_ = minDate;
  MaxDate_ = maxDate;

  OriginalSchedule_ = schedule;
  CurrentSchedule_ = OriginalSchedule_;

  // add years, months, and days to respective combo boxes
  for( int i = MinDate_.Year; i <= MaxDate_.Year; ++i ) {
    cboxMonthlyStartYear->Items->Add( i );
    cboxYearlyStart->Items->Add( i );
  }
  for( int i = 1; i <= 28; ++i ) {
    cboxMonthlyDay->Items->Add( i );
  }
  cboxMonthlyStartMonth->Items->AddRange( gcnew cli::array< System::Object^  >(12) {L"January", L"February", L"March", 
    L"April", L"May", L"June", L"July", L"August", L"September", L"October", L"November", L"December"});
}



ScheduleForm::~ScheduleForm()
{
  if( components ) {
		delete components;
	}
}



Schedule ^
ScheduleForm::GetSchedule(void)
{
  return CurrentSchedule_;
}
    


System::Void
ScheduleForm::OnLoad(System::Object^  sender, System::EventArgs^  e)
{
  tabSchedule->SelectedIndex = CurrentSchedule_->ScheduleTypeIndex;
}
    
    
    
System::Void
ScheduleForm::OnChangeSchedule(System::Object^  sender, System::Windows::Forms::TabControlEventArgs^  e)
{
  // schedule tab was changed
  int newPageIndex = this->tabSchedule->SelectedIndex;

  if( newPageIndex == (int) Schedule::ScheduleType::Single ) {
    if( SingleSchedule_ == nullptr ) {
      SingleSchedule_ = gcnew SingleSchedule();
      SingleSchedule_->StartDate = OriginalSchedule_->StartDate;
      dateTimeSingleStart->DataBindings->Add( "Value", SingleSchedule_, "StartDate" );
    }
    CurrentSchedule_ = SingleSchedule_;
  }
  else if( newPageIndex == (int) Schedule::ScheduleType::Weekly ) {
    if( WeeklySchedule_ == nullptr ) {
      WeeklySchedule_ = gcnew WeeklySchedule();
      WeeklySchedule_->StartDate = OriginalSchedule_->StartDate;
      WeeklySchedule_->UseStopDate = OriginalSchedule_->UseStopDate;
      WeeklySchedule_->StopDate = MaxDate_;

      dateTimeWeeklyStart->DataBindings->Add( "Value", WeeklySchedule_, "StartDate" );
      numWeeklyInterval->DataBindings->Add( "Text", WeeklySchedule_, "WeekInterval" );
      checkSunday->DataBindings->Add( "Checked", WeeklySchedule_, "Sunday" );
      checkMonday->DataBindings->Add( "Checked", WeeklySchedule_, "Monday" );
      checkTuesday->DataBindings->Add( "Checked", WeeklySchedule_, "Tuesday" );
      checkWednesday->DataBindings->Add( "Checked", WeeklySchedule_, "Wednesday" );
      checkThursday->DataBindings->Add( "Checked", WeeklySchedule_, "Thursday" );
      checkFriday->DataBindings->Add( "Checked", WeeklySchedule_, "Friday" );
      checkSaturday->DataBindings->Add( "Checked", WeeklySchedule_, "Saturday" );

      checkWeeklyEnd->DataBindings->Add( "Checked", WeeklySchedule_, "UseStopDate", false, DataSourceUpdateMode::OnPropertyChanged );
      dateTimeWeeklyEnd->DataBindings->Add( "Enabled", WeeklySchedule_, "UseStopDate" );
      dateTimeWeeklyEnd->DataBindings->Add( "Value", WeeklySchedule_, "StopDate" );
    }
    CurrentSchedule_ = WeeklySchedule_;
  }
  else if( newPageIndex == (int) Schedule::ScheduleType::Monthly ) {
    if( MonthlySchedule_ == nullptr ) {
      MonthlySchedule_ = gcnew MonthlySchedule();
      MonthlySchedule_->StartDate = OriginalSchedule_->StartDate;
      MonthlySchedule_->UseStopDate = OriginalSchedule_->UseStopDate;
      MonthlySchedule_->StopDate = MaxDate_;

      cboxMonthlyStartMonth->DataBindings->Add( "SelectedIndex", MonthlySchedule_, "StartMonth" );
      cboxMonthlyStartYear->DataBindings->Add( "SelectedItem", MonthlySchedule_, "StartYear" );

      numMonthlyInterval->DataBindings->Add( "Text", MonthlySchedule_, "MonthInterval" );

      cboxMonthlyDay->DataBindings->Add( "SelectedItem", MonthlySchedule_, "DayOfMonth" );

      checkMonthlyEnd->DataBindings->Add( "Checked", MonthlySchedule_, "UseStopDate", false, DataSourceUpdateMode::OnPropertyChanged );
      dateTimeMonthlyEnd->DataBindings->Add( "Enabled", MonthlySchedule_, "UseStopDate" );
      dateTimeMonthlyEnd->DataBindings->Add( "Value", MonthlySchedule_, "StopDate" );
    }
    CurrentSchedule_ = MonthlySchedule_;
  }
  else if( newPageIndex == (int) Schedule::ScheduleType::Yearly ) {
    if( YearlySchedule_ == nullptr ) {
      YearlySchedule_ = gcnew YearlySchedule();
      YearlySchedule_->StartDate = OriginalSchedule_->StartDate;
      cboxYearlyStart->DataBindings->Add( "SelectedItem", YearlySchedule_, "StartYear" );
      numYearlyInterval->DataBindings->Add( "Text", YearlySchedule_, "YearInterval" );
      numYearlyDay->DataBindings->Add( "Text", YearlySchedule_, "DayOfYear" );
    }
    CurrentSchedule_ = YearlySchedule_;
  }
  else if( newPageIndex == (int) Schedule::ScheduleType::Periodic ) {
    if( PeriodicSchedule_ == nullptr ) {
      PeriodicSchedule_ = gcnew PeriodicSchedule();
      PeriodicSchedule_->StartDate = OriginalSchedule_->StartDate;
      PeriodicSchedule_->UseStopDate = OriginalSchedule_->UseStopDate;
      PeriodicSchedule_->StopDate = MaxDate_;

      dateTimePeriodicStart->DataBindings->Add( "Value", PeriodicSchedule_, "StartDate" );
      numPeriodicInterval->DataBindings->Add( "Text", PeriodicSchedule_, "TreatmentInterval" );

      checkPeriodicTreatments->DataBindings->Add( "Checked", PeriodicSchedule_, "UseTreatments", false, DataSourceUpdateMode::OnPropertyChanged );
      numPeriodicTreatments->DataBindings->Add( "Enabled", PeriodicSchedule_, "UseTreatments" );
      numPeriodicTreatments->DataBindings->Add( "Text", PeriodicSchedule_, "NumberOfTreatments" );

      checkPeriodicStop->DataBindings->Add( "Checked", PeriodicSchedule_, "UseStopDate", false, DataSourceUpdateMode::OnPropertyChanged );
      dateTimePeriodicStop->DataBindings->Add( "Enabled", PeriodicSchedule_, "UseStopDate" );
      dateTimePeriodicStop->DataBindings->Add( "Value", PeriodicSchedule_, "StopDate" );
    }
    CurrentSchedule_ = PeriodicSchedule_;
  }
}
