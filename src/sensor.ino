/*
 * Project Hydroponic-project
 * Description:
 * Author:
 * Date: 27/02/2022
 */

#include "Adafruit_DHT.h"
#include "GA1A12S202.h"


#define DHTPIN 8
#define DHTYPE DHT11

SYSTEM_THREAD(ENABLED);

DHT dht1(DHTPIN, DHTYPE);
DHT dhtSensors[] = {dht1};
#define DHTSIZE 1
volatile int counter = 0;

GA1A12S202 lux1(A5);
GA1A12S202 luxSensors[] = {lux1};
#define LUXSIZE 1

float rawRange = 1024; // 3.3v
float logRange = 5.0; // 3.3v = 10^5 lux

Thread TR("tempReadThread", tempRead);
Thread LR("lightReadThread", lightRead);

// setup() runs once, when the device is first turned on.
void setup() 
{
	Serial.begin(9600); 
	Serial.println("Sensor reading test!");

	dht1.begin();
}

// loop() runs over and over again, as quickly as it can execute.
void loop() 
{

	//tempRead();
	//lightRead();
  
	delay(5000);
}

void tempRead()
{

	float h = 0;
	float t = 0;
	float sumH = 0;
	float sumT = 0;
	float averageH = 0;
	float averageT = 0;


	for (int i = 0 ; i < DHTSIZE ; i++)
	{
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

	//Send averages to the cloud

	delay(5000);
	tempRead();
	//os_thread_delay_until(&lastThreadTime, 2000);
}

void lightRead()
{

	float l = 0;
	float sumL = 0;
	float averageL = 0;

	for (int i = 0 ; i < LUXSIZE ; i++)
	{
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

	delay(5000);
	lightRead();
}

//Particle.publish("temperature", String(h)); // publish to cloud YA FUNCIONA!!!