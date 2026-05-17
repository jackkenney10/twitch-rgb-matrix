// Based on Adafruit_NeoMatrix example

#include <TwitchApi.h>
#define USING_AXTLS
#include <ESP8266WiFi.h>
//#include <WiFiClientSecure.h>
#include "WiFiClientSecureAxTLS.h"
using namespace axTLS;

#include <ArduinoJson.h> // This Sketch doesn't technically need this, but the library does so it must be installed.
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN D3

//------- Replace the following! ------
char ssid[] = "";         // your network SSID (name)
char password[] = ""; // your network key

// Create a new application on https://dev.twitch.tv/
#define TWITCH_CLIENT_ID ""

// Username of who you are getting the data for (e.g. "ninja")
#define TWITCH_LOGIN ""

WiFiClientSecure client;
TwitchApi twitch(client, TWITCH_CLIENT_ID);
UserData user;
FollowerData followerData;
String followerName;
String follower = "Recent follower: ";

unsigned long delayBetweenRequests = 58500; // Time between requests (1 minute)
unsigned long requestDueTime = 0;               //time when request due

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(15, 10, PIN,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(50);


    Serial.begin(115200);

    // kss._debug = true;

    // Set WiFi to station mode and disconnect from an AP if it was Previously
    // connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    // Attempt to connect to Wifi network:
    Serial.print("Connecting Wifi: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    IPAddress ip = WiFi.localIP();
    Serial.println(ip);
}

void loop() {

 static int i = 0;
 i++;
 if (millis() > requestDueTime) {
    user = twitch.getUserData(TWITCH_LOGIN);
    if(!user.error) {
      followerData = twitch.getFollowerData(user.id);
      if(!followerData.error){
         requestDueTime = millis() + delayBetweenRequests;
         followerName = followerData.fromName;
        Serial.println(followerData.fromName);
      }  
    }
 }

  //matrix.fillScreen(0);
  for(int y = 0; y < 10; y++)
    for(int x = 0; x < 15; x++)
      if(y & 1)
        matrix.setPixelColor(14 - x + y * 15, matrix.gamma32(matrix.ColorHSV((((x + y) * 256 * 8 + i * 128 * 2))/8)));
      else
        matrix.setPixelColor(x + y * 15, matrix.gamma32(matrix.ColorHSV((((x + y) * 256 * 8 + i * 128 * 2))/8)));
  matrix.setTextColor(matrix.Color(0, 0, 0));
  matrix.setCursor(-((millis() / 50) & 127) + 15, 1);
  matrix.print(followerName);
  matrix.show();
  yield();

}
