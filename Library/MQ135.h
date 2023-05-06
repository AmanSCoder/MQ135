/*#####################################################################*/
/*

# File          MQ135.cpp
# Authors       Aman Srivastava and Ashok Tirupatimahanti
# Adapted from  https://github.com/GeorgK/MQ135 by G.Krocker (Mad Frog Labs)
# License       GNU GPLv3

NOTE: Review the correction factor calculation. This currently relies on
        the datasheet but the information there seems to be wrong.

*/
/*#####################################################################*/

#ifndef MQ135_H
#define MQ135_H
#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

// The load resistance on the board
#define RLOAD 10.0

// Atmospheric concentration of CO2 (ppm) for calibration purposes
#define ATMOCO2 397.13
// Atmospheric concentration of CO (ppm) for calibration purposes
#define ATMOCO 0.1
// Atmospheric concentration of Ethanol (ppm) for calibration purposes
#define ATMOAlco 0
// Atmospheric concentration of Ammonia (ppm) for calibration purposes
#define ATMONH4 0
// Atmospheric concentration of Toluene (ppm) for calibration purposes
#define ATMOTolu 0
// Atmospheric concentration of Acetone (ppm) for calibration purposes
#define ATMOAcet 0

/***THESE RZero VALUES HAVE TO BE CALCULATED IN CLEAN ATMOSPHERE USING***/
/***THE getGASRZero() OR getGASCorrectedRZero(t,h) FUNCTIONS***/
// Calibration resistance at atmospheric CO2 level
#define CO2RZERO 930
// Calibration resistance at atmospheric CO level
#define CORZERO 930
// Calibration resistance at atmospheric Ethanol level
#define AlcoRZERO 930
// Calibration resistance at atmospheric Ammonia level
#define NH4RZERO 930
// Calibration resistance at atmospheric Toluene level
#define ToluRZERO 930
// Calibration resistance at atmospheric Acetone level
#define AcetRZERO 930


/***THESE PARAMETERS HAVE TO BE CALCULATED USING POWER REGRESSION ANALYSIS***/
/***AS MENTIONED IN THE README FILE***/
// Parameters for calculating ppm of CO2 from sensor resistance
#define CO2PARA 116.6020682
#define CO2PARB 2.769034857
// Parameters for calculating ppm of CO from sensor resistance
#define COPARA 522.6779
#define COPARB 3.8465
// Parameters for calculating ppm of Ethanol from sensor resistance
#define AlcoPARA 78.9230
#define AlcoPARB 3.2435
// Parameters for calculating ppm of Ammonia from sensor resistance
#define NH4PARA 101.3708
#define NH4PARB 2.5082
// Parameters for calculating ppm of Toluene from sensor resistance
#define ToluPARA 45.0673
#define ToluPARB 3.4835
// Parameters for calculating ppm of Acetone from sensor resistance
#define AcetPARA 34.2053
#define AcetPARB 3.5913

// Parameters to model temperature and humidity dependence
#define CORA 0.00035
#define CORB 0.02718
#define CORC 1.39538
#define CORD 0.0018

class MQ135
{
  private:
    uint8_t _pin;

  public:
    MQ135(uint8_t pin);
    float getCorrectionFactor(float t, float h);
    float getResistance();
    float getCorrectedResistance(float t, float h);

    float getCO2RZero();
    float getCO2CorrectedRZero(float t, float h);
    float getCO2PPM();
    float getCO2CorrectedPPM(float t, float h);

    float getCORZero();
    float getCOCorrectedRZero(float t, float h);
    float getCOPPM();
    float getCOCorrectedPPM(float t, float h);

    float getAlcoRZero();
    float getAlcoCorrectedRZero(float t, float h);
    float getAlcoPPM();
    float getAlcoCorrectedPPM(float t, float h);

    float getNH4RZero();
    float getNH4CorrectedRZero(float t, float h);
    float getNH4PPM();
    float getNH4CorrectedPPM(float t, float h);

    float getToluRZero();
    float getToluCorrectedRZero(float t, float h);
    float getToluPPM();
    float getToluCorrectedPPM(float t, float h);

    float getAcetRZero();
    float getAcetCorrectedRZero(float t, float h);
    float getAcetPPM();
    float getAcetCorrectedPPM(float t, float h);
};
#endif
