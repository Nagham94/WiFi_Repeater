#include <WiFi.h>
//#include <WiFiClient.h>
//#include <WiFiAP.h>

char ssid[] = "Nagham";
char pass[] = "12344321";

unsigned long timestart=0;
unsigned long timeOut=0;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("ESP32_AP", "1234"); // Set the repeater SSID and pass
  
  Serial.println("Repeater started");
  Serial.print("Network SSID: ");
  Serial.println(WiFi.softAPSSID());
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  // Connect to the existing WiFi network
  wifi_init();
  timestart=millis();

}

void loop() {
  if(millis()-timestart>2000 && WiFi.status()  != WL_CONNECTED){
                Serial.println("Reconnecting to wifi .......");
                //Software Reset
              WiFi.disconnect(); 
              wifi_init();
               WiFi.reconnect();
                timestart=millis();
        }

  if(millis()-timestart>5000){
  int numStations = WiFi.softAPgetStationNum();
  // Show the number of connected stations
  Serial.print("Number of connected stations: ");
  Serial.println(numStations);
  timestart=millis();
  }
}

int  wifi_init(void){
  WiFi.begin(ssid,pass);
  Serial.print("Connecting");

  timeOut=millis();
  while (WiFi.status()  != WL_CONNECTED && millis()-timeOut <10000 ) {
          delay(500);
          Serial.print(".");
  }
  if(WiFi.status()  != WL_CONNECTED){
      Serial.println("I cam't Connected Wifi...");
      return 0;
  }
  else{

      Serial.println("Conected .. Your IP is ");
      Serial.println(WiFi.localIP());
      Serial.print("Strngeth = ");
      Serial.print(WiFi.RSSI());
      return 1;
  }
}