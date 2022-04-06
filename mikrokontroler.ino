#include "DHT.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SPI.h>

#define DHTTYPE DHT11  
#define DHTPIN4 D4     
#define DHTPIN5 D5     

DHT dht4(DHTPIN4, DHTTYPE);
DHT dht5(DHTPIN5, DHTTYPE);

const char* ssid = "wifiSSID"; 
const char* password = "wifiPassword!";

byte server[] = {192, 168, 43, 136};   

WiFiClient client;  

void setup()
{
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Got IP: "); Serial.print(WiFi.localIP());
  Serial.println("");
  delay(1000);
  Serial.println("connecting...");
  
  dht4.begin();
  dht5.begin();
  pinMode(A0, INPUT);
}

static unsigned long lastMillis = 0;
void loop()
{
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
	
  float humidity4 = dht4.readHumidity();
  float temperature4 = dht4.readTemperature();
  float humidity5 = dht5.readHumidity();
  float temperature5 = dht5.readTemperature();
  float cahaya = analogRead(A0);

  delay(10); 

  if (millis() - lastMillis > 60000)
  {
    lastMillis = millis(); 
	Sending_To_phpmyadmindatabase(humidity4, humidity5, temperature4, temperature5, cahaya);   
  }
}

void Sending_To_phpmyadmindatabase(float humidityData1, float humidityData2, float temperatureData1, float temperatureData2, float cahaya){
   if (client.connect(server, 80)) {
    Serial.println("connected to local server");
    
    Serial.print("GET /arduino/kondisiTaman.php?humidityData1=");
    client.print("GET /arduino/kondisiTaman.php?humidityData1=");     
    Serial.println(humidityData1);
    client.print(humidityData1);
	
    client.print("&humidityData2=");
    Serial.println("&humidityData2=");
    client.print(humidityData2);
    Serial.println(humidityData2);
	
	client.print("&temperatureData1=");
    Serial.println("&temperatureData1=");
    client.print(temperatureData1);
    Serial.println(temperatureData1);
	
	client.print("&temperatureData2=");
    Serial.println("&temperatureData2=");
    client.print(temperatureData2);
    Serial.println(temperatureData2);
	
	client.print("&cahaya=");
    Serial.println("&cahaya=");
    client.print(cahaya);
    Serial.println(cahaya);
	
    client.print(" ");      
    client.print("HTTP/1.1");
    client.println();
 
    client.println("Host: 192.168.43.136"); 
    client.println("Connection: close");
    client.println(); 
    
  } else {
    Serial.println("connection failed");
  }
 }