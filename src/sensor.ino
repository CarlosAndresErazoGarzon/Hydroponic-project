/*
 * Project Hydroponic-project
 * Description:
 * Author:
 * Date: 27/02/2022
 */

#include "Adafruit_DHT.h"
#include "GA1A12S202.h"
#include "Ubidots.h"

#ifndef UBIDOTS_TOKEN
#define UBIDOTS_TOKEN "" // Put here your Ubidots TOKEN
#endif

Ubidots ubidots(UBIDOTS_TOKEN, UBI_UDP);

//TEMPERATURE

#define DHT8PIN 8
#define DHT7PIN 7
//#define DHT21PIN 6
#define DHTYPE11 DHT11
#define DHTYPE22 DHT22

DHT dht1(DHT8PIN, DHTYPE11);
DHT dht2(DHT7PIN, DHTYPE22);
//DHT dht12(DHT12PIN, DHTYPE);
//DHT dht21(DHT21PIN, DHTYPE);
//DHT dht1Sensors[] = {dht11, dht12};
//DHT dht2Sensors[] = {dht21};

#define DHT1SIZE 2
#define DHT2SIZE 1

//HYGROMETER

#define HYGROD5 D5
#define HYGROA1 A1
#define HYGROD4 D4
#define HYGROA2 A2

//LUX

GA1A12S202 lux1(A5);
GA1A12S202 lux2(A4);
GA1A12S202 lux3(A3);




// setup() runs once, when the device is first turned on.
void setup()
{
	Serial.begin(9600);
	Serial.println("Sensor reading test!");

	dht1.begin();
	dht2.begin();

	pinMode(HYGROD5, INPUT_PULLDOWN);
	pinMode(HYGROD4, INPUT_PULLDOWN);
	

	//ubidots.setDebug(true);
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{

	bool bufferSent = false;

	Serial.print("HYGRO1: ");
	//Serial.print(analogRead(HYGROA1));
	ubidots.add("T-HYGRO1", analogRead(HYGROA1));
	Serial.print(" ");
	Serial.println(digitalRead(HYGROD5));
	Serial.print("HYGRO2: ");
	//Serial.print(analogRead(HYGROA2));
	ubidots.add("T-HYGRO2", analogRead(HYGROA2));
	Serial.print(" ");
	Serial.println(digitalRead(HYGROD4));

	Serial.print("DHT1: ");
	//Serial.print(dht1.getHumidity());
	ubidots.add("T-HUM1", dht1.getHumidity());
	Serial.print(" ");
	//Serial.println(dht1.getTempCelcius());
	ubidots.add("T-TEMP1", dht1.getTempCelcius());

	Serial.print("DHT2: ");
	//Serial.print(dht2.getHumidity());
	ubidots.add("T-HUM2", dht2.getHumidity());
	Serial.print(" ");
	//Serial.println(dht2.getTempCelcius());
	ubidots.add("T-TEMP2", dht2.getTempCelcius());

	Serial.print("LUX1: ");
	//Serial.println(lux1.getLux(true));
	ubidots.add("T-LUX1", lux1.getLux(true));
	Serial.print("LUX2: ");
	//Serial.println(lux2.getLux(true));
	ubidots.add("T-LUX2", lux2.getLux(true));
	Serial.print("LUX3: ");
	//Serial.println(lux3.getLux(true));
	ubidots.add("T-LUX3", lux3.getLux(true));
	

	bufferSent = ubidots.send(); // Will send data to a device label that matches the device Id

	if (bufferSent)
	{
		// Do something if values were sent properly
		Serial.println("Values sent by the device");
	}

	delay(900000);

}

// Particle.publish("temperature", String(h)); // publish to cloud YA FUNCIONA!!!