#include "AdafruitIO_WiFi.h"
#include <Adafruit_NeoPixel.h>
#include <DHT.h>

#define PIN_NEOPIXEL 15
#define PIN_DHT11 14
#define NUMPIXELS 16
#define DHTTYPE DHT11
float temp;

DHT dht(PIN_DHT11, DHTTYPE);
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

#define IO_USERNAME  "Adolff_0"
#define IO_KEY       "aio_aWgl22ofVeah5xWQ6SNvbQMQSl8Z"

#define WIFI_SSID      "Balam"
#define WIFI_PASS      "0987654321"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

AdafruitIO_Feed *TEM = io.feed("tem");

//int SEN=14;

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to Adafruit IO");
          io.connect();
      while(io.status() < AIO_CONNECTED) {
      Serial.print(".");
      delay(500);
      
    }

    Serial.println();
    Serial.println(io.statusText());
     dht.begin();
  pixels.begin();
  pixels.clear();
}

void loop() {
  io.run();
  envio_datos();
  

  int numPixelsToLight = map(temp, 17, 34, 0, NUMPIXELS);
  numPixelsToLight = constrain(numPixelsToLight, 0, NUMPIXELS);

  for(int i=0; i<numPixelsToLight; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
  }

  for(int i=numPixelsToLight; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }

  pixels.show();
  delay(1000);
}



void envio_datos(){
 temp = dht.readTemperature();

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" *C");
  TEM->save(temp);
  delay(6500);


//float por=digitalRead(PIN_DHT11);
//Serial.println(por);
//
}
