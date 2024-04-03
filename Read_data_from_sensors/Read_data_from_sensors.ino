int sensor = 4;
float sensor1;

//declare library and connection for DHT11
#include "DHT.h"
#define DHTPIN 32     // what digital pin the DHT sensor is connected to
#define DHTTYPE DHT11   // there are multiple kinds of DHT sensors
DHT dht(DHTPIN, DHTTYPE);

void setup() {
//setup for DHT11
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();

//setup for smoke sensor
pinMode(sensor, INPUT);
}

void loop() {
//loop for smoke sensor
sensor1 = analogRead(sensor);
Serial.println(sensor1);
delay(1000);

//Read DHT11 temperature and humidity
delay(2000);
float h = dht.readHumidity();
// Read temperature as Celsius (the default)
float t = dht.readTemperature();
if (isnan(h) || isnan(t)) {
Serial.println("Failed to read from DHT sensor!");
  return;
}
// Read temperature and humidity from ESP32
Serial.print("Humidity: ");
Serial.print(h);
Serial.print(" %\t");
Serial.print("Temperature: ");
Serial.print(t);
Serial.print(" *C ");
}
