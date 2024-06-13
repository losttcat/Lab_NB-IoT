#include <Arduino.h>
#include <Wire.h>
#include <SparkFun_SHTC3.h>
#include <StarterKitNB.h>

//Definitions
#define PIN_VBAT WB_A0
#define VBAT_MV_PER_LSB (0.73242188F) // 3.0V ADC range and 12 - bit ADC resolution = 3000mV / 4096
#define VBAT_DIVIDER_COMP (1.73)      // Compensation factor for the VBAT divider, depend on the board (por default 1.73); 1905
#define REAL_VBAT_MV_PER_LSB (VBAT_DIVIDER_COMP * VBAT_MV_PER_LSB)

// Objects
StarterKitNB sk;
SHTC3 mySHTC3;

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

void setup() {

  sk.Setup();
  delay(500);

  Wire.begin();
  errorDecoder(mySHTC3.begin()); 
  delay(500);

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
  batery = (analogRead(PIN_VBAT) * REAL_VBAT_MV_PER_LSB /1000);

  /*
    Codigo para hacer los print con "Serial.prinln(variable);"
  */

  /*
    Código para ver si el último mensaje fue enviado, sino se conecta al broker
  */
	
  /*
    Codigo para enviar mensajes al broker
  */

  delay(1000);

}

