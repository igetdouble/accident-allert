  #include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <BlynkSimpleEsp8266.h>
#include "credentials.h"
#define BLYNK_PRINT Serial
WiFiClientSecure client;
TinyGPSPlus gps;
SoftwareSerial serial_gps(4, 5);//D2 D1 <> RX,TX NodeMCU <> TX,RX Ublox Neo
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  Serial.begin(115200);
  serial_gps.begin(9600);
  Serial.println(F("POWER ON"));
  if(millis()>25000&&gps.charsProcessed()<10){
    Serial.println(F("No GPS Detected : check wiring."));
    while(true);
  }
  wifi += ssid;
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  Serial.print("Connecting Wifi to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  bot.sendMessage(defaultChatId, "POWER ON");
  bot.sendMessage(defaultChatId, wifi);
  Serial.println("");
  Serial.println(wifi);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Blynk.begin(auth, ssid, password);
  pinMode(buzz,OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(cekpin, OUTPUT);
  delay(10);
  digitalWrite(ledPin, HIGH);
  digitalWrite(cekpin, LOW);
  digitalWrite(buzz,0);
}

void loop() {
  
  while(serial_gps.available()>0){
    if(gps.encode(serial_gps.read())){
      if(gps.location.isValid()){
        lat_str=String(gps.location.lat(),6);
        lng_str=String(gps.location.lng(),6);
        digitalWrite(ledPin, LOW);  
        digitalWrite(buzz, 1);
        int adxl = checkadxl();
        Blynk.run();
        int cek_pin = digitalRead(cekpin);
        if(cek_pin == HIGH && cekpin_flag == 0){
          ifttt_gps(lat_str, lng_str, adxl);
          Serial.println(buf+lat_str+","+lng_str);
          cekpin_flag++;
        }      
        else if(cek_pin == LOW){
          cekpin_flag=0;
        }
        if (adxl > 465){
          int adxl = 560;
          Serial.println(adxl);
          flag++;
          digitalWrite(ledPin, LOW);
          digitalWrite(buzz,1);
          Serial.println(buf+lat_str+","+lng_str);
          ifttt_ifttt(lat_str, lng_str);
          ifttt_telegram(lat_str, lng_str);
          ifttt_line(lat_str, lng_str);
          ifttt_messenger(lat_str, lng_str);
          ifttt_gmail(lat_str, lng_str);
        }
      }
      digitalWrite(ledPin, HIGH);  
      digitalWrite(buzz, 0);
    }
  }
}
void ifttt_gps(String value1, String value2, int value3){
  if(client.connected()){
    client.stop();
  }
  client.flush();
  if(client.connect(HOSTIFTTT,443)){
    Serial.println("Telegram Connected");
    String toSend = "GET /trigger/";
    toSend += EVENTO_GPS;
    toSend += "/with/key/";
    toSend += IFTTTKEY;
    toSend += "?value1=";
    toSend += value1;
    toSend += "&value2=";
    toSend += value2;
    toSend += "&value3=";
    toSend += value3;
    toSend += " HTTP/1.1\r\n";
    toSend += "Host: ";
    toSend += HOSTIFTTT;
    toSend += "\r\n";
    toSend += "Connection: close\r\n\r\n";

    client.print(toSend);
  }
  client.flush();
  client.stop();
}
void ifttt_telegram(String value1, String value2){
  if(client.connected()){
    client.stop();
  }
  client.flush();
  if(client.connect(HOSTIFTTT,443)){
    Serial.println("Telegram Connected");
    String toSend = "GET /trigger/";
    toSend += EVENTO_TELEGRAM;
    toSend += "/with/key/";
    toSend += IFTTTKEY;
    toSend += "?value1=";
    toSend += value1;
    toSend += "&value2=";
    toSend += value2;
    //toSend += "&value3=";
    //toSend += value3;
    toSend += " HTTP/1.1\r\n";
    toSend += "Host: ";
    toSend += HOSTIFTTT;
    toSend += "\r\n";
    toSend += "Connection: close\r\n\r\n";

    client.print(toSend);
  }
  client.flush();
  client.stop();
}
void ifttt_ifttt(String value1, String value2){
  if(client.connected()){
    client.stop();
  }
  client.flush();
  if(client.connect(HOSTIFTTT,443)){
    Serial.println("IFTTT Connected");
    String toSend = "GET /trigger/";
    toSend += EVENTO_IFTTT;
    toSend += "/with/key/";
    toSend += IFTTTKEY;
    toSend += "?value1=";
    toSend += value1;
    toSend += "&value2=";
    toSend += value2;
    //toSend += "&value3=";
    //toSend += value3;
    toSend += " HTTP/1.1\r\n";
    toSend += "Host: ";
    toSend += HOSTIFTTT;
    toSend += "\r\n";
    toSend += "Connection: close\r\n\r\n";

    client.print(toSend);
  }
  client.flush();
  client.stop();
}
void ifttt_line(String value1, String value2){
  if(client.connected()){
    client.stop();
  }
  client.flush();
  if(client.connect(HOSTIFTTT,443)){
    Serial.println("LINE Connected");
    String toSend = "GET /trigger/";
    toSend += EVENTO_LINE;
    toSend += "/with/key/";
    toSend += IFTTTKEY;
    toSend += "?value1=";
    toSend += value1;
    toSend += "&value2=";
    toSend += value2;
    //toSend += "&value3=";
    //toSend += value3;
    toSend += " HTTP/1.1\r\n";
    toSend += "Host: ";
    toSend += HOSTIFTTT;
    toSend += "\r\n";
    toSend += "Connection: close\r\n\r\n";

    client.print(toSend);
  }
  client.flush();
  client.stop();
}
void ifttt_messenger(String value1, String value2){
  if(client.connected()){
    client.stop();
  }
  client.flush();
  if(client.connect(HOSTIFTTT,443)){
    Serial.println("Messenger Connected");
    String toSend = "GET /trigger/";
    toSend += EVENTO_MESSENGER;
    toSend += "/with/key/";
    toSend += IFTTTKEY;
    toSend += "?value1=";
    toSend += value1;
    toSend += "&value2=";
    toSend += value2;
    //toSend += "&value3=";
    //toSend += value3;
    toSend += " HTTP/1.1\r\n";
    toSend += "Host: ";
    toSend += HOSTIFTTT;
    toSend += "\r\n";
    toSend += "Connection: close\r\n\r\n";

    client.print(toSend);
  }
  client.flush();
  client.stop();
}
void ifttt_gmail(String value1, String value2){
  if(client.connected()){
    client.stop();
  }
  client.flush();
  if(client.connect(HOSTIFTTT,443)){
    Serial.println("Gmail Connected");
    String toSend = "GET /trigger/";
    toSend += EVENTO_GMAIL;
    toSend += "/with/key/";
    toSend += IFTTTKEY;
    toSend += "?value1=";
    toSend += value1;
    toSend += "&value2=";
    toSend += value2;
    //toSend += "&value3=";
    //toSend += value3;
    toSend += " HTTP/1.1\r\n";
    toSend += "Host: ";
    toSend += HOSTIFTTT;
    toSend += "\r\n";
    toSend += "Connection: close\r\n\r\n";

    client.print(toSend);
  }
  client.flush();
  client.stop();
}
int checkadxl() {
  int value1 = analogRead(xpin);
  Serial.print("ADXL value: ");
  Serial.println(value1);
  return value1;
}
