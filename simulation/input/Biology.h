#ifndef BIOLOGY_H
#define BIOLOGY_H



namespace input
{

class Biology
{
public:
  Biology(void);
  ~Biology(void);

  class EggParameters {
  public:
    EggParameters(void);
    ~EggParameters(void);

    class DevelopmentParameters {
    public:
      DevelopmentParameters(void);
      ~DevelopmentParameters(void);
    public:
      double RO25;
      double DHA;
      double DHH;
      double THALF;
    };

    class TemperatureParameters {
    public:
      TemperatureParameters(void);
      ~TemperatureParameters(void);
    public:
      double LowLethalSurvival;
      double LowLethalThreshold;
      double LowThreshold;
      double HighThreshold;
      double HighLethalThreshold;
      double HighLethalSurvival;
    };

    class SaturationDeficitParameters {
    public:
      SaturationDeficitParameters(void);
      ~SaturationDeficitParameters(void);
    public:
      double WetSurvival;
      double HighSunExposureThreshold;
      double HighSunExposureSurvival;
      double LowThreshold;
      double HighThreshold;
      double LowSurvival;
      double HighSurvival;
    };

    class PredationParameters {
    public:
      PredationParameters(void);
      ~PredationParameters(void);
    public:
      double LowSurvival;
      double LowThreshold;
      double HighThreshold;
      double HighSurvival;
    };

    double MinimumHatchTemperature;
    double FloodHatchRatio;
    double SpontaneousHatchRatio;
    double NominalSurvival;
    DevelopmentParameters * Development;
    TemperatureParameters * Temperature;
    SaturationDeficitParameters * SaturationDeficit;
    PredationParameters * Predation;
  };

  class LarvaeParameters {
  public:
    LarvaeParameters(void);
    ~LarvaeParameters(void);

    class DevelopmentParameters {
    public:
      DevelopmentParameters(void);
      ~DevelopmentParameters(void);
    public:
      double RO25;
      double DHA;
      double DHH;
      double THALF;
    };

    class PupationWeightParameters {
    public:
      PupationWeightParameters(void);
      ~PupationWeightParameters(void);
    public:
      double Slope;
      double Intercept;
      double MinimumWeightForPupation;
      double MaximumDevelopment;
    };

    class TemperatureParameters {
    public:
      TemperatureParameters(void);
      ~TemperatureParameters(void);
    public:
      double LowLethalSurvival;
      double LowLethalThreshold;
      double LowThreshold;
      double HighThreshold;
      double HighLethalThreshold;
      double HighLethalSurvival;
    };

    class FoodParameters {
    public:
      FoodParameters(void);
      ~FoodParameters(void);
    public:
      bool UseRandomFood;
      double AssimilationRate;
      double ExploitationRate;
      double ExploitationRateIndependence;
      double MetabolicWeightLossRate;
      double MetabolicWeightLossExponent;
    };

    class FastingParameters {
    public:
      FastingParameters(void);
      ~FastingParameters(void);
    public:
      double NoFastingSurvival;
      double LipidReserveSurvival;
      double NoLipidReserveSurvival;
      double NonDepletableLipidReserve;
      double WeightToLipidSlope;
      double WeightToLipidConstant;
    };

    double WeightAtHatch;
    double ChronologicalBasisAt26C;
    double NominalSurvival;
    double PupationSurvival;
    double DryContainerSurvival;
    double MinimumWeightForSurvival;
    int NumberEulerSteps;
    double CadaverFoodRatio;
    DevelopmentParameters * Development;
    PupationWeightParameters * PupationWeight;
    TemperatureParameters * Temperature;
    FoodParameters * Food;
    FastingParameters * Fasting;
  };

  class PupaeParameters{
  public:
    PupaeParameters(void);
    ~PupaeParameters(void);

  public:
    class DevelopmentParameters {
    public:
      DevelopmentParameters(void);
      ~DevelopmentParameters(void);
    public:
      double RO25;
      double DHA;
      double DHH;
      double THALF;
    };

    class TemperatureParameters {
    public:
      TemperatureParameters(void);
      ~TemperatureParameters(void);
    public:
      double LowLethalSurvival;
      double LowLethalThreshold;
      double LowThreshold;
      double HighThreshold;
      double HighLethalThreshold;
      double HighLethalSurvival;
    };

    double NominalSurvival;
    double EmergenceSurvival;
    double FemaleEmergence;
    DevelopmentParameters * Development;
    TemperatureParameters * Temperature;
  };

  class AdultParameters{
  public:
    AdultParameters(void);
    ~AdultParameters(void);

    class AgeDependentSurvivalParameters {
    public:
      AgeDependentSurvivalParameters(void);
      ~AgeDependentSurvivalParameters(void);

    public:
      int CutoffAge;
      double YoungSurvival;
      double OldSurvival;

    public:
      double GetSurvival( int age );
    };

    class DevelopmentParameters {
    public:
      DevelopmentParameters(void);
      ~DevelopmentParameters(void);
    public:
      double RO25;
      double DHA;
      double DHH;
      double THALF;
    };

    class TemperatureParameters {
    public:
      TemperatureParameters(void);
      ~TemperatureParameters(void);
    public:
      double LowLethalSurvival;
      double LowLethalThreshold;
      double LowThreshold;
      double HighThreshold;
      double HighLethalThreshold;
      double HighLethalSurvival;
    };

    class SaturationDeficitParameters {
    public:
      SaturationDeficitParameters (void);
      ~SaturationDeficitParameters (void);
    public:
      double LowSurvival;
      double LowThreshold;
      double HighThreshold;
      double HighSurvival;
    };

    class DoubleBloodMealParameters {
    public:
      DoubleBloodMealParameters(void);
      ~DoubleBloodMealParameters(void);
    public:
      double LowWeightRatio;
      double LowWeightLimit;
      double HighWeightLimit;
      double HighWeightRatio;
    };

    double SecondDevelopmentThreshold;
    double NominalSurvival;
    double DryToWetWeightFactor;
    double FecundityFactor;
    double MinimumOvipositionTemperature;
    double ProportionOfFeedsOnHumans;
    double InterruptedFeedsPerMeal;
    double ProportionOfInterruptedFeedsOnDifferentHost;
    double ProportionOfAdultsRestingOutdoors;
    AgeDependentSurvivalParameters * AgeDependentSurvival;
    DevelopmentParameters * Development;
    TemperatureParameters * Temperature;
    SaturationDeficitParameters * SaturationDeficit;
    DoubleBloodMealParameters * DoubleBloodMeal;
  };

  EggParameters * Egg;
  LarvaeParameters * Larvae;
  PupaeParameters * Pupae;
  AdultParameters * Adult;
};

};

#endif
