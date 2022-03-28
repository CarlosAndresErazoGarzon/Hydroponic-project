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
#include "SdFat.h"

void saveData(String text);
void setup();
void loop();
#line 13 "c:/Users/anes_/Documents/Hidroponicos/Hydroponic-project/src/sensor.ino"
SYSTEM_MODE(MANUAL);

// TEMPERATURE

#define DHT8PIN 8
#define DHT7PIN 7
//#define DHT21PIN 6
#define DHTYPE11 DHT11
#define DHTYPE22 DHT22

DHT dht1(DHT8PIN, DHTYPE11);
DHT dht2(DHT7PIN, DHTYPE22);

#define DHT1SIZE 2
#define DHT2SIZE 1

float dht1Temp = 0;
float dht1Hum = 0;

float dht2Temp = 0;
float dht2Hum = 0;

// HYGROMETER

#define HYGROD5 D5
#define HYGROA1 A1
#define HYGROD4 D4
#define HYGROA2 A2

int hygro1Hum = 0;
int hygro2hum = 0;

// LUX

GA1A12S202 lux2(A4);
GA1A12S202 lux3(A3);

float lux1lux = 0;
float lux2lux = 0;

// Primary SPI with DMA
// SCK => D13, MISO => D12, MOSI => D11, SS => D14/A5 (default)
SdFat sd;
const uint8_t chipSelect = SS;

File myFile;

void saveData(String text)
{
	delay(5000);

	if (!sd.begin(chipSelect, SPI_FULL_SPEED))
	{
		sd.initErrorHalt();
	}

	if (!myFile.open("data.csv", O_RDWR | O_CREAT | O_AT_END))
	{
		sd.errorHalt("opening test.txt for write failed");
	}

	Serial.print("Writing to data.csv");
	Serial.print("\n");
	Serial.print(text);
	myFile.println(text);

	myFile.close();
	Serial.println("done.");
}

void setup()
{
	Serial.begin(9600);
	Serial.println("Sensor reading test!");

	dht1.begin();
	dht2.begin();

	pinMode(HYGROD5, INPUT_PULLDOWN);
	pinMode(HYGROD4, INPUT_PULLDOWN);
}

void loop()
{

	bool cent = true;
	int contCent = 0;

	hygro1Hum = 0;
	hygro2hum = 0;
	dht1Hum = 0;
	dht1Temp = 0;
	dht2Hum = 0;
	dht2Temp = 0;
	lux1lux = 0;
	lux2lux = 0;

	// This number will overflow (go back to zero), after approximately 49 days
	unsigned long time = millis();

	hygro1Hum = analogRead(HYGROA1);
	hygro2hum = analogRead(HYGROA2);

	//Rectify that the data is read
	while (cent)
	{
		if (dht1Hum != 0 && dht1Temp != 0)
		{
			break;
		}
		else if (dht1Hum == 0)
		{
			delay(500);
			dht1Hum = dht1.getHumidity();
		}
		else if (dht1Temp == 0)
		{
			delay(500);
			dht1Temp = dht1.getTempCelcius();
		}
		contCent++;
		if (contCent == 5)
		{
			cent = false;
		}
	}

	dht2Hum = dht2.getHumidity();
	dht2Temp = dht2.getTempCelcius();
	lux1lux = lux2.getLux(true);
	lux2lux = lux3.getLux(true);

	//BOARDTIME HYGRO1 HYGRO2 HUM1 TEMP1 HUM2 TEMP2 LUX1 LUX2
	String text = String(time) + "," +
				  String(hygro1Hum) + "," + String(hygro2hum) + "," +
				  String(dht1Hum) + "," + String(dht1Temp) + "," +
				  String(dht2Hum) + "," + String(dht2Temp) + "," +
				  String(lux1lux) + "," + String(lux2lux);

	//Save the data on the SD card
	saveData(text);

	delay(900);
	//delay(900000);
}