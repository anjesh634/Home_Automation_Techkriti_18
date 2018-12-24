#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "iitk";
const char* password = "8charpassword";

const char * udpAddress = "192.168.43.171";
const int udpPort = 3333 ;

String buff;



WiFiUDP udp;

void setup()
{
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");


  Serial.printf("Web server started, open %s in a web browser\n", WiFi.localIP().toString().c_str());
}


// prepare a web page to be send to a client (web browser)


void loop()
{
    if(Serial.available()){
    buff = Serial.readStringUntil('\n');
    char charBuf[buff.length() + 1];
    buff.toCharArray(charBuf, buff.length() + 1);
    udp.beginPacket(udpAddress,udpPort);
    udp.printf("%u    %s",millis(),charBuf);
    udp.endPacket();
    }
  }

