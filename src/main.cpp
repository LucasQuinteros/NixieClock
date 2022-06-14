#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include "Time.cpp"
#include "Nixie.cpp" 
#include "prueba.html"
const char* ssid = "Fibertel WiFi678 2.4GHz"; //Fibertel WiFi678
const char* password = "01410929085"; //0147673708


ESP8266WebServer server(80);
bool ota_flag = false;
uint16_t time_elapsed = 0;

Nixie First(D5);
Nixie Second(D6);
Nixie Three(D7);
Nixie Fourth(D4);

int i=0;
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
void handleTIME(){
	String time = Tiempolocal();
	server.send(200, "text/plane", time);
}
void setup() {
  // put your setup code here, to run once:
  //pinMode(D5,OUTPUT);
  /*pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(D3,OUTPUT);
  //pinMode(LED_BUILTIN,OUTPUT);

  //digitalWrite(D5,HIGH);
  digitalWrite(D6,HIGH);
  digitalWrite(D7,HIGH);
  digitalWrite(D4,HIGH);*/
  pinMode(D3,OUTPUT);
  digitalWrite(D3,HIGH);
  digitalWrite(D3,LOW);



  
  
  Serial.begin(115200);
  IPAddress ip(192, 168, 0, 50);
  IPAddress gateway(192, 168, 0, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress dns(1, 1, 1, 1);
  WiFi.config(ip,gateway,subnet,dns);



  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  configTime(-3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("OK");
  user_init();

  ArduinoOTA.begin();
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  

  delay(500);
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/readTIME", handleTIME);
  server.on("/restart",[](){
    ota_flag = true;
    time_elapsed = 0;
    server.send(200, "text/plane", "Restarting... Please reload page");
    //ESP.restart();
  });
  server.begin();                  //Start server
  Serial.println("HTTP server started");
  delay(1000);

  String time = Tiempolocal();
  Serial.println(time);
  //time.replace(":","0");
  time.remove(2,1);
  //Serial.println(time);
  int Hora = time.toInt();
  
  Serial.println(Hora / 1000);
  First.display(Hora / 1000);

  Hora = (Hora%1000);
  Serial.println(Hora/100);
  Second.display(Hora / 100);

  Hora = (Hora % 100);
  Serial.println(Hora/10);
  Three.display(Hora / 10);

  Hora = (Hora % 10);
  Serial.println(Hora);
  Fourth.display(Hora);

  
  
  
  
  
  
  //First.display(5);
  /*Nixie Second(D6);
  Nixie Three(D7);
  Nixie Fourth(D4);
  
  Second.display(6);
  Three.display(7);
  Fourth.display(4);*/
  
  //5109
}

void loop() {
  

  /*
  delay(500);
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(D5,LOW);
    digitalWrite(D6,LOW);
    digitalWrite(D7,LOW);
    digitalWrite(D4,LOW);
    //digitalWrite(LED_BUILTIN,HIGH);

    delay(500);

    digitalWrite(D5,HIGH);
    digitalWrite(D6,HIGH);
    digitalWrite(D7,HIGH);
    digitalWrite(D4,HIGH);
    //digitalWrite(LED_BUILTIN,LOW);
  }*/
  if(ota_flag){
    uint16_t timer_start = millis();
    while(time_elapsed < 15000){
      ArduinoOTA.handle();
      time_elapsed = millis() - timer_start;
      delay(10);
    }
    ota_flag = false;
  }
  server.handleClient();          //Handle client requests
  if (tickOccured){
        
        String time = Tiempolocal();
        time.remove(2,1);
        int Hora = time.toInt();

        Serial.println(Hora / 1000);
        First.display(Hora / 1000);

        Hora = (Hora%1000);
        Serial.println(Hora/100);
        Second.display(Hora / 100);

        Hora = (Hora % 100);
        Serial.println(Hora/10);
        Three.display(Hora / 10);

        Hora = (Hora % 10);
        Serial.println(Hora);
        Fourth.display(Hora);

    if( espera ){

        espera = false;
    }
	tickOccured=false;	
  }


  
}


