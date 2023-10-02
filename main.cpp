#include <Arduino.h>
#include <Wire.h>
#include <SparkFun_SHTC3.h>
#include <StarterKitNB.h>
#include "ADC121C021.h"

//Definitions
#define EN_PIN WB_IO6	 //Logic high enables the device. Logic low disables the device
#define ALERT_PIN WB_IO5 //a high indicates that the respective limit has been violated.
#define MQ2_ADDRESS 0x51 //the device i2c address
#define RatioMQ2CleanAir (1.0) //RS / R0 = 1.0 ppm
#define MQ2_RL (10.0)		   //the board RL = 10KΩ  can adjust

#define PIN_VBAT WB_A0
#define VBAT_MV_PER_LSB (0.73242188F) // 3.0V ADC range and 12 - bit ADC resolution = 3000mV / 4096
#define VBAT_DIVIDER_COMP (1.73)      // Compensation factor for the VBAT divider, depend on the board (por default 1.73); 1905
#define REAL_VBAT_MV_PER_LSB (VBAT_DIVIDER_COMP * VBAT_MV_PER_LSB)

// Objects
StarterKitNB sk;
SHTC3 mySHTC3;
ADC121C021 MQ2;

// NB-IoT
String apn;
String user;
String password;
String band;
String Network;

// MQTT
String clientID;
String userBroker;
String passwordBroker;
String broker;
int port;

// msg
String topic1;
String topic2;
String topic3;
String topic4;
float batery;             

// temp&hum
String hum = "";
String temp = "";
void errorDecoder(SHTC3_Status_TypeDef message)             
{
  switch(message)
  {
    case SHTC3_Status_Nominal : Serial.println("Nominal"); break;
    case SHTC3_Status_Error : Serial.println("Error"); break;
    case SHTC3_Status_CRC_Fail : Serial.println("CRC Fail"); break;
    default : Serial.println("Unknown return code"); break;
  }
}

// PPM
float sensorPPM;

void setup() {

  sk.Setup();
  delay(500);

  Wire.begin();
  errorDecoder(mySHTC3.begin()); 
  delay(500);
  pinMode(ALERT_PIN, INPUT);
	pinMode(EN_PIN, OUTPUT);
	digitalWrite(EN_PIN, HIGH);
  while (!(MQ2.begin(MQ2_ADDRESS, Wire)))
	{
		Serial.println("please check gas device!!!");
		delay(200);
	}
  MQ2.configCycleTime(CYCLE_TIME_32);
	MQ2.configAlertHold(Disable);		
	MQ2.configAlertFlag(Disable);		
	MQ2.configAlertPin(Enable);			
	MQ2.configPolarity(High);			
	MQ2.setAlertLowThreshold(1);		
	MQ2.setAlertHighThreshold(2500);	 
  MQ2.setRL(MQ2_RL);
	MQ2.setA(-0.890);			
	MQ2.setB(1.125);			
	MQ2.setRegressionMethod(0); 
  float calcR0 = 0;
	for (int i = 1; i <= 100; i++)
	{
		calcR0 += MQ2.calibrateR0(RatioMQ2CleanAir);
	}
	MQ2.setR0(calcR0 / 10);
	if (isinf(calcR0))
	{
		Serial.println("Warning: Conection issue founded, R0 is infite");
		while (1)
			;
	}
	if (calcR0 == 0)
	{
		Serial.println("Warning: Conection issue founded, R0 is zero");
		while (1)
			;
	}
	Serial.printf("R0 Value is:%3.2f\r\n", MQ2.getR0());

  /*
    Codigo para conectarse a NB-IoT
  */
  
}

void loop() {

  /*
    Codigo para verificar la conexión a NB-IoT
  */

  SHTC3_Status_TypeDef result = mySHTC3.update();
  hum = String(mySHTC3.toPercent());
  temp = String(mySHTC3.toDegC());
  sensorPPM = MQ2.readSensor();
  batery = (analogRead(PIN_VBAT) * REAL_VBAT_MV_PER_LSB /1000);

  /*
    Codigo para hacer los print con "Serial.prinln(variable);"
  */
	
  /*
    Codigo para enviar mensajes al broker
  */

  delay(1000);

}

