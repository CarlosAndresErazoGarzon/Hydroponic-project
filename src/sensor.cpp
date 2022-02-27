/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/anes_/Documents/Hidroponicos/Hydroponic-project/sensor/src/sensor.ino"
/*
 * Project sensor
 * Description:
 * Author:
 * Date:
 */

#include "Adafruit_DHT.h"

void setup();
void loop();
#line 10 "c:/Users/anes_/Documents/Hidroponicos/Hydroponic-project/sensor/src/sensor.ino"
#define DHTPIN 8
#define DHTYPE DHT11

DHT dht(DHTPIN, DHTYPE);


// setup() runs once, when the device is first turned on.
void setup() {
	Serial.begin(9600); 
	Serial.println("DHTxx test!");

	dht.begin();

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.


// Reading temperature or humidity takes about 250 milliseconds!
// Sensor readings may also be up to 2 seconds 'old' (its a 
// very slow sensor)
	float h = dht.getHumidity();
// Read temperature as Celsius
	float t = dht.getTempCelcius();
  
// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(t)) {
		Serial.println("Failed to read from DHT sensor!");
		return;
	}

// Compute heat index
// Must send in temp in Fahrenheit!
	float hi = dht.getHeatIndex();
	float dp = dht.getDewPoint();

  Serial.print("Humedad: ");
	Serial.println(h); 
  Serial.print("Temperatura: ");
	Serial.println(t); 
  Serial.print("Heat index: ");
	Serial.println(hi);
  Serial.print("Dew Point: ");
	Serial.println(dp);

	//Particle.publish("temperature", String(h)); // publish to cloud YA FUNCIONA!!!
  delay(5000);

}