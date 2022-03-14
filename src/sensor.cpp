/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/anes_/Documents/Hidroponicos/Hydroponic-project/src/sensor.ino"
/*
 * Project Hydroponic-project
 * Description:
 * Author:
 * Date: 27/02/2022
 */

#include "Adafruit_DHT.h"
#include "GA1A12S202.h"
#include "Ubidots.h"

void setup();
void loop();
void tempRead(int group);
void lightRead();
#line 12 "c:/Users/anes_/Documents/Hidroponicos/Hydroponic-project/src/sensor.ino"
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
GA1A12S202 luxSensors[] = {lux1};
#define LUXSIZE 1



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

	delay(900);

	//tempRead(1);
	//tempRead(2);
	//lightRead();

	Serial.print("HYGRO1: ");
	Serial.print(analogRead(HYGROA1));
	Serial.print(" ");
	Serial.println(digitalRead(HYGROD5));
	Serial.print("HYGRO2: ");
	Serial.print(analogRead(HYGROA2));
	Serial.print(" ");
	Serial.println(digitalRead(HYGROD4));

	Serial.print("DHT1: ");
	Serial.print(dht1.getHumidity());
	Serial.print(" ");
	Serial.print(dht1.getTempCelcius());

	Serial.print("DHT2: ");
	Serial.print(dht2.getHumidity());
	Serial.print(" ");
	Serial.print(dht2.getTempCelcius());
	

	//delay(9000);

	//tempRead(1);
	//tempRead(2);
	//lightRead();

	//bufferSent = ubidots.send(); // Will send data to a device label that matches the device Id

	if (bufferSent)
	{
		// Do something if values were sent properly
		Serial.println("Values sent by the device");
	}

	//delay(120000);

	//System.sleep(900);
}

void tempRead(int group)
{

	float h = 0;
	float t = 0;
	float sumH = 0;
	float sumT = 0;
	float averageH = 0;
	float averageT = 0;

	int DHTSIZE = 0;

	if (group == 1)
	{
		Serial.println("PRIMER GRUPO");
		DHTSIZE = DHT1SIZE;

		for (int i = 0; i < DHTSIZE; i++)
		{

			h = dht1Sensors[i].getHumidity();
			t = dht1Sensors[i].getTempCelcius();

			Serial.print("Sensor DHT: ");
			Serial.println(i);
			Serial.print("Humedad: ");
			Serial.println(h);
			Serial.print("Temperatura: ");
			Serial.println(t);

			sumH = sumH + h;
			sumT = sumT + t;
		}
	}
	else
	{
		Serial.println("SEGUNDO GRUPO");
		DHTSIZE = DHT2SIZE;

		for (int i = 0; i < DHTSIZE; i++)
		{

			h = dht2Sensors[i].getHumidity();
			t = dht2Sensors[i].getTempCelcius();

			Serial.print("Sensor DHT: ");
			Serial.println(i);
			Serial.print("Humedad: ");
			Serial.println(h);
			Serial.print("Temperatura: ");
			Serial.println(t);

			sumH = sumH + h;
			sumT = sumT + t;
		}
	}

	averageT = sumT / DHTSIZE;
	Serial.print("Promedio temperatura: ");
	Serial.println(averageT);

	averageH = sumH / DHTSIZE;
	Serial.print("Promedio humedad: ");
	Serial.println(averageH);

	if (group == 1)
	{
		ubidots.add("hum1", averageH);
		ubidots.add("temp1", averageT);
	}
	else
	{
		ubidots.add("hum2", averageH);
		ubidots.add("temp2", averageT);
	}
}

void lightRead()
{

	float l = 0;
	float sumL = 0;
	float averageL = 0;
	bool bufferSent = false;

	for (int i = 0; i < LUXSIZE; i++)
	{
		l = luxSensors[i].getLux(true);

		Serial.print("Sensor LUX: ");
		Serial.println(i);
		Serial.print("Luz: ");
		Serial.println(l);

		sumL = sumL + l;
	}

	averageL = sumL / LUXSIZE;
	Serial.print("Promedio temperatura: ");
	Serial.println(averageL);

	ubidots.add("Lux1", averageL);
}

// Particle.publish("temperature", String(h)); // publish to cloud YA FUNCIONA!!!