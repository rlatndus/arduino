#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "i2rAp";
const char* password = "00000000";

const int ledPin =  LED_BUILTIN;// the number of the LED pin

void setupWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup(void){
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  setupWifi();
}

void loop(void){
  HTTPClient http;    //Declare object of class HTTPClient
 
  http.begin("http://192.168.4.1/");     //Specify request destination
  
  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload
 
  //Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
  //Serial.println(payload[7]);
  if(payload[7]=='1')
    digitalWrite(ledPin, LOW);
  else
    digitalWrite(ledPin, HIGH);
 
  http.end();  //Close connection
  delay(2000);  //GET Data at every 5 seconds
}
