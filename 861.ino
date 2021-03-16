
/*Modified by
 * Technical Team,REES52
 */

// Include the correct display library
// For a connection via I2C using Wire include
#include <Wire.h> 
#include "SSD1306.h"

//#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>
///////is this needed for BlynkTimer

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
//char auth[] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

// Your WiFi credentials.
// Set password to "" for open networks.
//char ssid[] = "XXXX";
//char pass[] = "XXXXXX";

#include <DHT.h>

////all of these includes come from the ZIP libraries we have added 

//#define DHTPIN 4     // what pin we're connected to
#define DHTPIN D2
#define DHTTYPE DHT11   // DHT 11

// Initialize the OLED display i2C
//D3 -> SDA
//D5 -> SCL

// Initialize the OLED display using Wire library
SSD1306  display(0x3C, D3, D5);

DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;
////heres the issue - commented as i thought it was to do with the blynk software 
//is this okay to use as a timer feature on its own

void setup(){
  Serial.begin(115200);
  // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  dht.begin(); // initialize dht
 
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8080);
  timer.setInterval(1000L, sendSensor);
}

void displayWeather(){ //Creating a function to read and display temperature and humidity on OLED display
  float h = dht.readHumidity();
  // Read temperature as Celsius
  delay(3000);
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  //delay(3000);
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)){
    display.clear(); // clearing the display
    display.drawString(5,0, "DHT Failed!");
    return;
  }
  display.clear();
  display.drawString(30, 0, "Weather");
  display.drawString(0, 20, "Humidity: " + String(h) + "%\t"); 
  display.drawString(0, 40, "Temp: " + String(t) + "°C"); 
  //Uncomment to get temperature in farenheit
  //display.drawString(0, 40, "Temp: " + String(f) + "°F"); 

}

//is loop the same as main() in other languages - doesnt need to be called 
//event driven programming - has a game loop 
void loop(){
  //Blynk.run(); // Running the blynk code
  displayWeather(); //Calling back the displayWeather function
  display.display();
  timer.run();
}

//sending data to server - no longer needed
void sendSensor()
{
  /*float h = dht.readHumidity();  //Read the humidity
  delay(3000);
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }*/
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  //Blynk.virtualWrite(V5, h);
  //Blynk.virtualWrite(V6, t);
}
