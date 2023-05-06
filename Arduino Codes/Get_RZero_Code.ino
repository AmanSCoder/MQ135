#include "MQ135.h"
#include <dht11.h>
dht11 DHT11;
const int MQ135pin=A0;
MQ135 gasSensor = MQ135(MQ135pin);
const int dht11Pin=A1;
const int n=1000;


void setup() {
  Serial.begin( 9600);
  pinMode(MQ135pin,INPUT);
  pinMode(dht11Pin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  float CO2RZero=0;
  float CORZero=0;
  float AlcoRZero=0;
  float NH4RZero=0;
  float ToluRZero=0;
  float AcetRZero=0;

  for(int i=0;i<n;i++)
  {
  CO2RZero+=gasSensor.getCO2RZero();
  CORZero+=gasSensor.getCORZero();
  AlcoRZero+=gasSensor.getAlcoRZero();
  NH4RZero+=gasSensor.getNH4RZero();
  ToluRZero+=gasSensor.getToluRZero();
  AcetRZero+=gasSensor.getAcetRZero();
  }
  CO2RZero/=n;
  CORZero/=n;
  AlcoRZero/=n;
  NH4RZero/=n;
  ToluRZero/=n;
  AcetRZero/=n;
  Serial.print("CO2RZero:");
  Serial.println(CO2RZero);

  Serial.print("CORZero:");
  Serial.println(CORZero);

  Serial.print("AlcoRZero:");
  Serial.println(AlcoRZero);

  Serial.print("NH4RZero:");
  Serial.println(NH4RZero);

  Serial.print("ToluRZero:");
  Serial.println(ToluRZero);

  Serial.print("AcetRZero:");
  Serial.println(AcetRZero);
}
