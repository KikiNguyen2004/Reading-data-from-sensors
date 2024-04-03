#include <WiFi.h>
#include <HTTPClient.h>

//declare library and connection for DHT11
#include "DHT.h"
#define DHTPIN 32     // what digital pin the DHT sensor is connected to
#define DHTTYPE DHT11   // there are multiple kinds of DHT sensors
DHT dht(DHTPIN, DHTTYPE);

// declare variables for MQ6 smoke sensor
int sensor = 4;
int sensor1;

// declare variables for Wifi
const char* ssid = "7 Tran Phu";
const char* password = "manhquan259";

// Domain Name with full URL Path for HTTP POST Request
const char* serverName = "http://api.thingspeak.com/update";

// write API Key provided by thingspeak
String apiKey = "DBOWJC05JOQ3PHG2";

 

void setup() {
//setup for DHT11
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();

//setup for smoke sensor
  pinMode(sensor, INPUT);

//setup for wifi
  WiFi.begin(ssid, password);

  Serial.println("Connecting");

  while(WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println("");

  Serial.print("Connected to WiFi network with IP Address: ");

  Serial.println(WiFi.localIP());

  
}

void loop() {

  //Read smoke figures from ESP32
  sensor1 = analogRead(sensor);
  Serial.println(sensor1);

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

  if(WiFi.status()== WL_CONNECTED){

      WiFiClient client;

      HTTPClient http;

      delay(1000); // wait for 10 seconds

      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      // Data to send with HTTP POST
      String httpRequestData = "api_key=" + apiKey + "&field1=" + String(sensor1);     

      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
      Serial.println(httpResponseCode);
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
}