#include "Adafruit_SHT31.h"
#include <WiFi.h>
#include "ThingSpeak.h"

const char *ssid = "Y NHI - LAU 2_2.4G"; // your network SSID (name)
const char *password = "xanhdotimvang";  // your network password

WiFiClient client;

unsigned long myChannelNumber = 2160109;
const char *myWriteAPIKey = "2YWBFMR0GUEH4U3G";

Adafruit_SHT31 sht31;
unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

void initSHT31()
{
  Serial.println("Init SHT31");
  if (!sht31.begin(0x44))
  {
    Serial.println("Couldn't find SHT31!");
    while (1)
      delay(1);
  }
}

void connectWifi()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect");
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, password);
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
}

void setup()
{
  Serial.begin(9600);
  initSHT31();
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}

void loop()
{
  if ((millis() - lastTime) > timerDelay)
  {
    connectWifi();
    float temperature = sht31.readTemperature();
    float humidity = sht31.readHumidity();

    if (!isnan(temperature))
    {
      int statusCodeTem = ThingSpeak.writeField(myChannelNumber, 1, temperature, myWriteAPIKey);

      if (statusCodeTem == 200)
      {
        Serial.println("The new temperature is sent.");
      }
      else
      {
        Serial.println("Fail to send temperature to Thingspeak (" + String(statusCodeTem) + ")");
      }
    }
    lastTime = millis();
  }
}
