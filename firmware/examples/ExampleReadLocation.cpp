#include "jsonlite/jsonlite.h"
#include "M2XStreamClient/M2XStreamClient.h"

char feedId[] = "<feed id>";          // Feed you want to post to
char m2xKey[] = "<M2X access key>";   // Your M2X access key

TCPClient client;
M2XStreamClient m2xClient(&client, m2xKey);

void on_location_found(const char* name,
                       double latitude,
                       double longitude,
                       double elevation,
                       const char* timestamp,
                       int index,
                       void* context) {
  Serial.print("Found a location, index:");
  Serial.println(index);
  Serial.print("Name: ");
  Serial.println(name);
  Serial.print("Latitude: ");
  Serial.println(latitude);
  Serial.print("Longitude: ");
  Serial.println(longitude);
  Serial.print("Elevation: ");
  Serial.println(elevation);
  Serial.print("Timestamp: ");
  Serial.println(timestamp);
}

void setup() {
  Serial.begin(9600);

  while (!WiFi.ready()) {
    Serial.println("Waiting for WIFI connection...");
    // wait 2 seconds for connection
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();
}

void loop() {
  int response = m2xClient.readLocation(feedId, on_location_found, NULL);
  Serial.print("M2x client response code: ");
  Serial.println(response);

  if (response == -1) while(1) ;

  delay(5000);
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}