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
void tempRead();
void lightRead();
#line 12 "c:/Users/anes_/Documents/Hidroponicos/Hydroponic-project/src/sensor.ino"
#ifndef UBIDOTS_TOKEN
#define UBIDOTS_TOKEN ""  // Put here your Ubidots TOKEN
#endif

Ubidots ubidots(UBIDOTS_TOKEN, UBI_UDP);


#define DHTPIN 8
#define DHTYPE DHT11


DHT dht1(DHTPIN, DHTYPE);
DHT dhtSensors[] = {dht1};
#define DHTSIZE 1


GA1A12S202 lux1(A5);
GA1A12S202 luxSensors[] = {lux1};
#define LUXSIZE 1


// setup() runs once, when the device is first turned on.
void setup() {
	Serial.begin(9600); 
	Serial.println("Sensor reading test!");

	dht1.begin();
	ubidots.setDebug(true);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {

	bool bufferSent = false;

	delay(9000);

	tempRead();
	lightRead();

	delay(9000);

	tempRead();
	lightRead();


	bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id

	if (bufferSent) {
	// Do something if values were sent properly
	Serial.println("Values sent by the device");
	}

	
	System.sleep(900);

}

void tempRead(){

	float h = 0;
	float t = 0;
	float sumH = 0;
	float sumT = 0;
	float averageH = 0;
	float averageT = 0;


	for (int i = 0 ; i < DHTSIZE ; i++){

		h = dhtSensors[i].getHumidity();
		t = dhtSensors[i].getTempCelcius();

		Serial.print("Sensor DHT: ");
		Serial.println(i);
		Serial.print("Humedad: ");
		Serial.println(h); 
		Serial.print("Temperatura: ");
		Serial.println(t); 

		sumH = sumH + h;
		sumT = sumT + t;
	}

	averageT = sumT/DHTSIZE;
	Serial.print("Promedio temperatura: ");
	Serial.println(averageT);

	averageH = sumH/DHTSIZE;
	Serial.print("Promedio humedad: ");
	Serial.println(averageH);


	ubidots.add("hum1", averageH);
	ubidots.add("temp1", averageT);

}

void lightRead(){

	float l = 0;
	float sumL = 0;
	float averageL = 0;
	bool bufferSent = false;

	for (int i = 0 ; i < LUXSIZE ; i++){
		l = luxSensors[i].getLux(true);

		Serial.print("Sensor LUX: ");
		Serial.println(i);
		Serial.print("Luz: ");
		Serial.println(l); 

		sumL = sumL + l;
	}

	averageL = sumL/LUXSIZE;
	Serial.print("Promedio temperatura: ");
	Serial.println(averageL);

	ubidots.add("Lux1", averageL);
}



//Particle.publish("temperature", String(h)); // publish to cloud YA FUNCIONA!!!