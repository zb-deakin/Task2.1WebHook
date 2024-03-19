#include <DHT.h>
#include <DHT_U.h>

#include <WiFiNINA.h>    // arduino wifi library
#include <ThingSpeak.h>  // thingspeak library
#include "secrets.h"     // secrets for thingspeak library

// setup DHT22 on pin 12
#define DHTTYPE DHT22
#define DHTPIN 12
DHT dht(DHTPIN, DHTTYPE);

// setup wifi
char wifiAccessPointName[] = WIFI_NAME;
char wifiPassword[] = WIFI_PASSWORD;
int wifiConnectionStatus = WL_IDLE_STATUS;
WiFiClient wifiClient;

// setup thingspeak
unsigned long thingSpeakChannelId = THINGSPEAK_CHANNEL_ID;
const char* thingSpeakApiWriteKey = THINGSPEAK_API_WRITE_KEY;
int httpSuccess = 200;

void setup() {
  Serial.begin(9600);

  // wait until connected to the internet
  while (wifiConnectionStatus != WL_CONNECTED) {
    Serial.println("Connecting to " + String(wifiAccessPointName));

    wifiConnectionStatus = WiFi.begin(wifiAccessPointName, wifiPassword);

    // wait 5 seconds for connection to start
    delay(5000);
  }

  // initilize the sensor and ThingSpeak
  dht.begin();
  ThingSpeak.begin(wifiClient);
}

void loop() {
  float celsiusTemperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.println("celsiusTemperature: " + String(celsiusTemperature));
  Serial.println("humidity: " + String(humidity));

  // if there is an error, jump out of the loop early to try again
  if (isnan(celsiusTemperature) || isnan(humidity)) {
    Serial.println(F("Temperature or humidity did not ready correctly"));
    return;
  }

  // send value to thingspeak
  ThingSpeak.setField(1, celsiusTemperature);
  ThingSpeak.setField(2, humidity);

  int httpResponseCode = ThingSpeak.writeFields(thingSpeakChannelId, thingSpeakApiWriteKey);

  if (httpResponseCode == httpSuccess) {
    Serial.println("THINGSPEAK SUCCESS: Temperature and Humidity reading sent to channel correctly");
  } else {
    Serial.println("THINGSPEAK FAILED: HTTP Response code received " + String(httpResponseCode));
  }

  // wait 60 seconds between each write
  delay(60000);
}
