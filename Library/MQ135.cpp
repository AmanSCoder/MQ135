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

#include "MQ135.h"

/*#####################################################################*/

/*

# This is an initialisation of the MQ135 sensor with a given pin number.

# Argument:: pin -> pin number to which the sensor is connected.

*/

MQ135::MQ135(uint8_t pin)
{
    _pin = pin;
}

/*#####################################################################*/

/*

# This function returns the correction factor for the temperature and humidity.
# This correction factor can be used to eliminate the error caused due to the change
    in temperature and humidity, and get the corrected PPM of particular gas.

# Arguments:: t -> Atmospheric Temperature 
              h -> Relative Humidity 

*/

float MQ135::getCorrectionFactor(float t, float h)
{
    return CORA * t * t - CORB * t + CORC - (h - 33.) * CORD;
}

/*#####################################################################*/

/*

# This fucntion returns the resistance of the sensor in kOhm by reading the
    analog output from the sensor.

*/

float MQ135::getResistance()
{
    int val = analogRead(_pin);
    return ((1023. / (float)val) * 5. - 1.) * RLOAD;
}

/*#####################################################################*/

/*

# This fucntion returns the corrected resistance (in kOhm) of the sensor
    using the correction factor.

# Arguments:: t -> Atmospheric Temperature 
              h -> Relative Humidity 

*/

float MQ135::getCorrectedResistance(float t, float h)
{
    return getResistance() / getCorrectionFactor(t, h);
}

/*----X----X----X----Functions for CO2 PPM calculations----X----X----X----*/

/*

# This function is used for calculating the RZero value (in kOhms)
    according to the concentration of the gas in clean atmosphere.

    **THIS FUNCTION HAS TO BE RUN IN CLEAN ATMOSPHERE TO GET THE VALUE OF**
    **RZero AND THAT VALUE HAS TO BE UPDATED IN THE HEADER FILE (MQ135.H)**

*/

float MQ135::getCO2RZero()
{
    return getResistance() * pow((ATMOCO2 / CO2PARA), (1. / CO2PARB));
}

/*#####################################################################*/

/*

# This function gives the corrected value of RZero (in kOhms) using the
    correction factor.

    **HAS TO BE RUN IN CLEAN ATMOSPHERE**

# Arguments:: t -> Atmospheric Temperature 
              h -> Relative Humidity 

*/

float MQ135::getCO2CorrectedRZero(float t, float h)
{
    return getCorrectedResistance(t, h) * pow((ATMOCO2 / CO2PARA), (1. / CO2PARB));
}

/*#####################################################################*/

/*

# This function returns the PPM concentration WITHOUT taking the
    correction factor into consideration.

*/

float MQ135::getCO2PPM()
{
    return CO2PARA * pow((getResistance() / CO2RZERO), -CO2PARB);
}

/*#####################################################################*/

/*

# This function returns the CORRECTED PPM concentration taking the
    correction factor into consideration.

# Arguments:: t -> Atmospheric Temperature 
              h -> Relative Humidity 
              
*/

float MQ135::getCO2CorrectedPPM(float t, float h)
{
    return CO2PARA * pow((getCorrectedResistance(t, h) / CO2RZERO), -CO2PARB);
}

/*----X----X----X----Functions for CO PPM calculations----X----X----X----*/

/*

# This function is used for calculating the RZero value (in kOhms)
    according to the concentration of the gas in clean atmosphere.

    **THIS FUNCTION HAS TO BE RUN IN CLEAN ATMOSPHERE TO GET THE VALUE OF**
    **RZero AND THAT VALUE HAS TO BE UPDATED IN THE HEADER FILE (MQ135.H)**

*/

float MQ135::getCORZero()
{
    return getResistance() * pow((ATMOCO / COPARA), (1. / COPARB));
}

/*#####################################################################*/

/*

# This function gives the corrected value of RZero (in kOhms) using the
    correction factor.

    **HAS TO BE RUN IN CLEAN ATMOSPHERE**

# Arguments:: t -> Atmospheric Temperature 
              h -> Relative Humidity 

*/

float MQ135::getCOCorrectedRZero(float t, float h)
{
    return getCorrectedResistance(t, h) * pow((ATMOCO / COPARA), (1. / COPARB));
}

/*#####################################################################*/

/*

# This function returns the PPM concentration WITHOUT taking the
    correction factor into consideration.

*/

float MQ135::getCOPPM()
{
    return COPARA * pow((getResistance() / CORZERO), -COPARB);
}

/*#####################################################################*/

/*

# This function returns the CORRECTED PPM concentration taking the
    correction factor into consideration.

# Arguments:: t -> Atmospheric Temperature 
              h -> Relative Humidity 
              
*/

float MQ135::getCOCorrectedPPM(float t, float h)
{
    return COPARA * pow((getCorrectedResistance(t, h) / CORZERO), -COPARB);
}

/*----X----X----X----Functions for Ethanol PPM calculations----X----X----X----*/

/*

# This function is used for calculating the RZero value (in kOhms)
    according to the concentration of the gas in clean atmosphere.

    **THIS FUNCTION HAS TO BE RUN IN CLEAN ATMOSPHERE TO GET THE VALUE OF**
    **RZero AND THAT VALUE HAS TO BE UPDATED IN THE HEADER FILE (MQ135.H)**

*/

float MQ135::getAlcoRZero()
{
    return getResistance() * pow((ATMOAlco / AlcoPARA), (1. / AlcoPARB));
}

/*#####################################################################*/

/*

# This function gives the corrected value of RZero (in kOhms) using the
    correction factor.

    **HAS TO BE RUN IN CLEAN ATMOSPHERE**

# Arguments:: t -> Atmospheric Temperature 
              h -> Relative Humidity 

*/

float MQ135::getAlcoCorrectedRZero(float t, float h)
{
    return getCorrectedResistance(t, h) * pow((ATMOAlco / AlcoPARA), (1. / AlcoPARB));
}

/*#####################################################################*/

/*

# This function returns the PPM concentration WITHOUT taking the
    correction factor into consideration.

*/

float MQ135::getAlcoPPM()
{
    return AlcoPARA * pow((getResistance() / AlcoRZERO), -AlcoPARB);
}

/*#####################################################################*/

/*

# This function returns the CORRECTED PPM concentration taking the
    correction factor into consideration.

# Arguments:: t -> Atmospheric Temperature 
              h -> Relative Humidity 
              
*/

float MQ135::getAlcoCorrectedPPM(float t, float h)
{
    return AlcoPARA * pow((getCorrectedResistance(t, h) / AlcoRZERO), -AlcoPARB);
}

/*----X----X----X----Functions for Ammonia PPM calculations----X----X----X----*/

/*

# This function is used for calculating the RZero value (in kOhms)
    according to the concentration of the gas in clean atmosphere.

    **THIS FUNCTION HAS TO BE RUN IN CLEAN ATMOSPHERE TO GET THE VALUE OF**
    **RZero AND THAT VALUE HAS TO BE UPDATED IN THE HEADER FILE (MQ135.H)**

*/

float MQ135::getNH4RZero()
{
    return getResistance() * pow((ATMONH4 / NH4PARA), (1. / NH4PARB));
}

/*#####################################################################*/

/*

# This function gives the corrected value of RZero (in kOhms) using the
    correction factor.

    **HAS TO BE RUN IN CLEAN ATMOSPHERE**

# Arguments:: t -> Atmospheric Temperature 
              h -> Relative Humidity 

*/

float MQ135::getNH4CorrectedRZero(float t, float h)
{
    return getCorrectedResistance(t, h) * pow((ATMONH4 / NH4PARA), (1. / NH4PARB));
}

/*#####################################################################*/

/*

# This function returns the PPM concentration WITHOUT taking the
    correction factor into consideration.

*/

float MQ135::getNH4PPM()
{
    return NH4PARA * pow((getResistance() / NH4RZERO), -NH4PARB);
}

/*#####################################################################*/

/*

# This function returns the CORRECTED PPM concentration taking the
    correction factor into consideration.

# Arguments:: t -> Atmospheric Temperature 
              h -> Relative Humidity 
              
*/

float MQ135::getNH4CorrectedPPM(float t, float h)
{
    return NH4PARA * pow((getCorrectedResistance(t, h) / NH4RZERO), -NH4PARB);
}

/*----X----X----X----Functions for Toluene PPM calculations----X----X----X----*/

/*

# This function is used for calculating the RZero value (in kOhms)
    according to the concentration of the gas in clean atmosphere.

    **THIS FUNCTION HAS TO BE RUN IN CLEAN ATMOSPHERE TO GET THE VALUE OF**
    **RZero AND THAT VALUE HAS TO BE UPDATED IN THE HEADER FILE (MQ135.H)**

*/

float MQ135::getToluRZero()
{
    return getResistance() * pow((ATMOTolu / ToluPARA), (1. / ToluPARB));
}

/*#####################################################################*/

/*

# This function gives the corrected value of RZero (in kOhms) using the
    correction factor.

    **HAS TO BE RUN IN CLEAN ATMOSPHERE**

# Arguments:: t -> Atmospheric Temperature 
              h -> Relative Humidity 

*/

float MQ135::getToluCorrectedRZero(float t, float h)
{
    return getCorrectedResistance(t, h) * pow((ATMOTolu / ToluPARA), (1. / ToluPARB));
}

/*#####################################################################*/

/*

# This function returns the PPM concentration WITHOUT taking the
    correction factor into consideration.

*/

float MQ135::getToluPPM()
{
    return ToluPARA * pow((getResistance() / ToluRZERO), -ToluPARB);
}

/*#####################################################################*/

/*

# This function returns the CORRECTED PPM concentration taking the
    correction factor into consideration.

# Arguments:: t -> Atmospheric Temperature 
              h -> Relative Humidity 
              
*/

float MQ135::getToluCorrectedPPM(float t, float h)
{
    return ToluPARA * pow((getCorrectedResistance(t, h) / ToluRZERO), -ToluPARB);
}

/*----X----X----X----Functions for Acetone PPM calculations----X----X----X----*/

/*

# This function is used for calculating the RZero value (in kOhms)
    according to the concentration of the gas in clean atmosphere.

    **THIS FUNCTION HAS TO BE RUN IN CLEAN ATMOSPHERE TO GET THE VALUE OF**
    **RZero AND THAT VALUE HAS TO BE UPDATED IN THE HEADER FILE (MQ135.H)**

*/

float MQ135::getAcetRZero()
{
    return getResistance() * pow((ATMOAcet / AcetPARA), (1. / AcetPARB));
}

/*#####################################################################*/

/*

# This function gives the corrected value of RZero (in kOhms) using the
    correction factor.

    **HAS TO BE RUN IN CLEAN ATMOSPHERE**

# Arguments:: t -> Atmospheric Temperature 
              h -> Relative Humidity 

*/

float MQ135::getAcetCorrectedRZero(float t, float h)
{
    return getCorrectedResistance(t, h) * pow((ATMOAcet / AcetPARA), (1. / AcetPARB));
}

/*#####################################################################*/

/*

# This function returns the PPM concentration WITHOUT taking the
    correction factor into consideration.

*/

float MQ135::getAcetPPM()
{
    return AcetPARA * pow((getResistance() / AcetRZERO), -AcetPARB);
}

/*#####################################################################*/

/*

# This function returns the CORRECTED PPM concentration taking the
    correction factor into consideration.

# Arguments:: t -> Atmospheric Temperature 
              h -> Relative Humidity 
              
*/

float MQ135::getAcetCorrectedPPM(float t, float h)
{
    return AcetPARA * pow((getCorrectedResistance(t, h) / AcetRZERO), -AcetPARB);
}

/*----X----X----X----X----X----END OF FILE----X----X----X----X----X----*/