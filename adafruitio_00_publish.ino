
#include <HX711.h>

#include "config.h"



// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = D6;
const int LOADCELL_SCK_PIN = D7;

HX711 scale;


float kalibrasyon = 2196;


AdafruitIO_Feed *Sucell = io.feed("sucell");

void setup() {

  Serial.begin(115200);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
 
  scale.set_scale(kalibrasyon); //kalibirasyon değeri
  scale.tare(); 
 
  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.println(io.statusText());
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

void loop() {


double siseSuMiktari = 500 ;

  io.run();
  Serial.println("--------------");
  Serial.print("Ölçülen miktar: ");
 double deger = scale.get_units();

   if (deger  < 0)
  {
    deger  = 0.00;
  }

  Serial.print(deger);
  Serial.println(" ml");

  
  double deger1;
  //icilen miktar hesabi
  deger1 = siseSuMiktari- deger;

    Serial.print("İçilen miktar: ");
    Serial.print(deger1);
    Serial.println(" ml");

  
 Sucell->save(deger1);
  delay(3000);

  }
