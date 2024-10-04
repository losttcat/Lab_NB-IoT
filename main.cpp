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
String apn = "";
String user = "";
String password = "";
String band = ";
String Network = "";

// MQTT
String clientID = "";
String userBroker = "";
String passwordBroker = "";
String broker = "";
int port = 0;

// msg
String topic1 = "user/feeds/nombrefeed";
String topic2 = "user/feeds/nombrefeed";
String topic3 = "user/feeds/nombrefeed";
float battery;             

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

  // Credenciales y conectar a NB-IoT

  
}

void loop() {

  	// Revisar si la coneción a NB-IoT sigue

  battery = (analogRead(PIN_VBAT) * REAL_VBAT_MV_PER_LSB /1000);

	// Actualizar temperatura y humedad y printear

  	// Insertar comandos AT

 	// Conectarse al broker

	// Enviar mensajes



}

