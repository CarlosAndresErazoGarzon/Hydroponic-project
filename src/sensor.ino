/*
 * Project Hydroponic-project
 * Description: For reading 6 sensors
 * Author:
 * Date: 04/04/2022
 */

#include "Adafruit_DHT.h"
#include "GA1A12S202.h"
#include "Ubidots.h"
#include "SdFat.h"

SYSTEM_MODE(MANUAL);	//Working offline

#define DHTYPE22 DHT22
#define DHT8PIN 8	//First dht22 sensor on D8
#define DHT7PIN 7	//Second dht22 sensor on D7
#define HYGROD5 D5	//Digital input for the first yl100 sensor
#define HYGROA1 A1	//Analog input for the first yl100 sensor
#define HYGROD4 D4	//Digital input for the second yl100 sensor
#define HYGROA2 A2	//Analog input for the second yl100 sensor
#define GAA4 A4	//First light sensor
#define GAA3 A3	//Second light sensor

DHT dht1(DHT8PIN, DHTYPE22);
DHT dht2(DHT7PIN, DHTYPE22);
GA1A12S202 lux1(GAA4);
GA1A12S202 lux2(GAA3);

// Primary SPI with DMA
// SCK => D13, MISO => D12, MOSI => D11, SS => D14/A5 (default)
SdFat sd;
const uint8_t chipSelect = SS;
File myFile;

float dht1Temp;
float dht1Hum;
float dht2Temp;
float dht2Hum;
int hygro1Hum;
int hygro2hum;
float lux1lux;
float lux2lux;
uint64_t argon_time;

//Save data to sd
void saveData()
{
	//BOARDTIME HYGRO1 HYGRO2 HUM1 TEMP1 HUM2 TEMP2 LUX1 LUX2
	String time_board = "%lu", argon_time;
	String text = time_board + "," +
				  String(hygro1Hum) + "," + String(hygro2hum) + "," +
				  String(dht1Hum) + "," + String(dht1Temp) + "," +
				  String(dht2Hum) + "," + String(dht2Temp) + "," +
				  String(lux1lux) + "," + String(lux2lux);

	if (!sd.begin(chipSelect, SPI_FULL_SPEED))
	{
		sd.initErrorHalt();
	}

	if (!myFile.open("data.csv", O_RDWR | O_CREAT | O_AT_END))
	{
		sd.errorHalt("Opening test.txt for write failed");
	}

	Serial.print("Writing to data.csv");
	Serial.print("\n");
	Serial.print(text);
	myFile.println(text);

	myFile.close();
	Serial.println("\nDone.");
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
	//Reset
	hygro1Hum = 0;
	hygro2hum = 0;
	dht1Hum = 0;
	dht1Temp = 0;
	dht2Hum = 0;
	dht2Temp = 0;
	lux1lux = 0;
	lux2lux = 0;

	//Read
	argon_time = System.millis();
	hygro1Hum = analogRead(HYGROA1);
	hygro2hum = analogRead(HYGROA2);
	dht2Hum = dht2.getHumidity();
	dht2Temp = dht2.getTempCelcius();
	lux1lux = lux1.getLux(true);
	lux2lux = lux2.getLux(true);

	saveData();
	delay(900000);	//15 min.
}