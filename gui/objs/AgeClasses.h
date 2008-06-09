#pragma once



namespace gui
{

public ref class AgeClasses
{
public:
  static System::String ^ AgeRankToAgeClass( int rank ) {
    return AgeClassesStrings[rank - 1];
  }

private:
  static array<System::String^> ^ AgeClassesStrings = { "< 1", "1-4", "5-9", "10-14",
                                                        "15-19", "20-24", "25-29", "30-34", "35-39",
                                                        "40-44", "45-49", "50-54", "55-59", "60-64",
                                                        "65-69", "70-74", "75-79", "> 80" };
};

};
