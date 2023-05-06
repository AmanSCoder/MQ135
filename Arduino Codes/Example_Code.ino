#include "MQ135.h"
#include <dht11.h>
dht11 DHT11;
const int MQ135pin=A0;
MQ135 gasSensor = MQ135(MQ135pin);
const int dht11Pin=A1;
const int n=1000;

void setup()
{
  Serial.begin(9600 );
  pinMode(MQ135pin,INPUT);
 pinMode(dht11Pin,INPUT);
}

void loop()
{
  float CO2PPM=0;
  float COPPM=0;
  float AlcoPPM=0;
  float NH4PPM=0;
  float ToluPPM=0;
  float AcetPPM=0;
 float CorrectedCO2PPM=0;
 float CorrectedCOPPM=0;
 float CorrectedAlcoPPM=0;
 float CorrectedNH4PPM=0;
 float CorrectedToluPPM=0;
 float CorrectedAcetPPM=0;
 float chk=DHT11.read(dht11Pin);
 float humd=0;
 float temp=0;
  for(int i=0;i<n;i++)
  {
    CO2PPM+=gasSensor.getCO2PPM();
    COPPM+=gasSensor.getCOPPM();
    AlcoPPM+=gasSensor.getAlcoPPM();
    NH4PPM+=gasSensor.getNH4PPM();
    ToluPPM+=gasSensor.getToluPPM();
    AcetPPM+=gasSensor.getAcetPPM();
   humd=(float)DHT11.humidity;
   temp=(float)DHT11.temperature;
   CorrectedCO2PPM+=gasSensor.getCO2CorrectedPPM(temp,humd);
   CorrectedCOPPM+=gasSensor.getCOCorrectedPPM(temp,humd);
   CorrectedAlcoPPM+=gasSensor.getAlcoCorrectedPPM(temp,humd);
   CorrectedNH4PPM+=gasSensor.getNH4CorrectedPPM(temp,humd);
   CorrectedToluPPM+=gasSensor.getToluCorrectedPPM(temp,humd);
   CorrectedAcetPPM+=gasSensor.getAcetCorrectedPPM(temp,humd);
    
  }
  CO2PPM/=n;
  COPPM/=n;
  AlcoPPM/=n;
  NH4PPM/=n;
  ToluPPM/=n;
  AcetPPM/=n;
 CorrectedCO2PPM/=n;
 CorrectedCOPPM/=n;
 CorrectedAlcoPPM/=n;
 CorrectedNH4PPM/=n;
 CorrectedToluPPM/=n;
 CorrectedAcetPPM/=n;
  Serial.print("CO2:");
  Serial.println(CO2PPM);

  Serial.print("CO:");
  Serial.println(COPPM);

  Serial.print("Alco:");
  Serial.println(AlcoPPM);

  Serial.print("NH4:");
  Serial.println(NH4PPM);

  Serial.print("Tolu:");
  Serial.println(ToluPPM);

  Serial.print("Acet:");
  Serial.println(AcetPPM);

 Serial.print("Temperature  (C): ");
 Serial.println(temp);
 Serial.print("Humidity (%): ");
 Serial.println(humd);
 Serial.print("Corrected CO2:");
 Serial.println(CorrectedCO2PPM);

 Serial.print("Corrected CO:");
 Serial.println(CorrectedCOPPM);

 Serial.print("Corrected Alco:");
 Serial.println(CorrectedAlcoPPM);

 Serial.print("Corrected NH4:");
 Serial.println(CorrectedNH4PPM);

 Serial.print("Corrected Tolu:");
 Serial.println(CorrectedToluPPM);

 Serial.print("Corrected Acet:");
 Serial.println(CorrectedAcetPPM);
 Serial.println();

  delay(1000);


}
