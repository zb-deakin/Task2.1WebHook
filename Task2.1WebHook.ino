#include <DHT.h>
#include <DHT_U.h>

#include <WiFiNINA.h>                     // arduino wifi library
#include "wifi-thingspeak-credentials.h"  // secrets for thingspeak library
#include <ThingSpeak.h>                   // thingspeak library

// use a DHT22 on pin 12
#define DHTTYPE DHT22
#define DHTPIN 12
DHT dht(DHTPIN, DHTTYPE);

// setup wifi
char wifiAccessPointName[] = WIFI_NAME;
char wifiPassword[] = WIFI_PASSWORD;
WiFiClient wifiClient;

// setup thingspeak
unsigned long thingSpeakChannelId = THINGSPEAK_CHANNEL_ID;
const char* thingSpeakApiWriteKey = THINGSPEAK_API_WRITE_KEY;
int thingSpeakChannelFieldIndex = 1;
int success = 200;

// setup light sensor variables
int lightSensorPin = A0;
int lightSensorValue;

void setup() {
  Serial.begin(9600);
  dht.begin();

  // // wifi is needed for
  // if (WiFi.status() == WL_NO_MODULE) {
  //   Serial.println("Communication with WiFi module failed!");

  //   // if the wifi is not working stop the program from running
  //   while (true) {
  //     continue;
  //   }
  // }

  // ThingSpeak.begin(wifiClient);  //Initialize ThingSpeak
}

void loop() {

  // Connect or reconnect to WiFi
  // if (WiFi.status() != WL_CONNECTED) {
  //   Serial.print("Connecting to Wifi Access Point: ");
  //   Serial.println(wifiAccessPointName);

  //   while (WiFi.status() != WL_CONNECTED) {
  //     WiFi.begin(wifiAccessPointName, wifiPassword);
  //     Serial.println("Trying to connect ...");
  //     delay(1000);
  //   }
  //   Serial.println("\nConnected.");
  // }

  float humidity = dht.readHumidity();
  float celsiusTemperature = dht.readTemperature();

  Serial.println("humidity: " + String(humidity));
  Serial.println("celsiusTemperature: " + String(celsiusTemperature));

  // if there is an error, jump out of the loop early to try again
  if (isnan(humidity) || isnan(celsiusTemperature)) {
    Serial.println(F("Temperature or humidity did not ready correctly"));
    return;
  }

 delay(500);

  // // get light-level reading
  // lightSensorValue = analogRead(lightSensorPin);
  // // give it a moment to convert from analogue to digital value
  // delay(10);
  // // print captured value
  // Serial.println(lightSensorValue);

  // // send value to thingspeak
  // int httpResponseCode = ThingSpeak.writeField(thingSpeakChannelId, thingSpeakChannelFieldIndex, lightSensorValue, thingSpeakApiWriteKey);
  // if (httpResponseCode == success) {
  //   Serial.println("THINGSPEAK SUCCESS: Light-level reading sent to channel correctly");
  // } else {
  //   Serial.println("THINGSPEAK FAILED: HTTP Response code received " + String(httpResponseCode));
  // }

  // wait 30 seconds between each write
  // delay(30000);
}
