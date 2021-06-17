// include the library code:
#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>

#define PIN 2
#define NUMPIXELS 4 // numero de leds

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//init variables
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

// Mise a jour des couleurs
void set_color(int redColor, int greenColor, int blueColor){
  for(int i = 0; i<NUMPIXELS; i++){
    pixels.setPixelColor(i,pixels.Color(redColor, greenColor, blueColor));    
  }
  pixels.show();
}

//Allume Bande 4 LED
void allume_led(int num, int airQuality){
  if (airQuality < 5) {
    pixels.setPixelColor(num, 0, 255, 0);
    Serial.print("La LED est de couleur vert ");
    lcd.print("Qual air bonne  ");

    lcd.setCursor(0, 1);
    lcd.print("32.^C 48% (0v0)");
  } 
  else if (airQuality < 8){
    pixels.setPixelColor(num, 255, 255, 0);
    Serial.print("La LED est de couleur jaune ");
    lcd.print("Qual air moyenne");
    
    lcd.setCursor(0, 1);
    lcd.print("32.^C 48% (0_0)");
  } 
  else {
    pixels.setPixelColor(num, 255, 0, 0);
    Serial.print("La LED est de couleur rouge ");
    lcd.print("Qual air mauvaise");
    
    lcd.setCursor(0, 1);
    lcd.print("32.^C 48% (0^0)");
  }
  pixels.show();
}

//Init Bande 4 LED
void init_led(int k) {
  allume_led(1,k);
}


/////////////////////////////////////


void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  //lcd.print("32^C 48%");
  
  
  if (Serial.available() > 0) {
  	int s = Serial.read();
    Serial.println(s);
    init_led(s);

  }

}

void setup() {
  pixels.begin();
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
 
  set_color(255,0,255);
  
  //Bande à 4 LED
  init_led(8);
  pixels.show();


}