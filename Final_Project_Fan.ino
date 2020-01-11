#include <Keypad.h>
#include <dht.h>
#include <LiquidCrystal.h>
#include <AFMotor.h>
#define dht_apin A8

dht DHT;

LiquidCrystal lcd(53, 51, 49, 47, 45, 43);

AF_DCMotor motor(1);

const byte ROWS = 4; 
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {22, 25, 26, 29};
byte colPins[COLS] = {30, 33, 34, 37};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

static const unsigned long REFRESH_INTERVAL = 2000; 
static unsigned long lastRefreshTime = 0;

void setup() {
  lcd.begin(16,2);
  motor.setSpeed(255);
  motor.run(RELEASE);
  Serial.begin(9600);
}

long t = 25;
int y = 0;

void loop() {

  char customKey1 = customKeypad.getKey();  

  DHT.read11(dht_apin);

  float temperature = DHT.temperature;

    if (millis() - lastRefreshTime >= REFRESH_INTERVAL){  
    lastRefreshTime += REFRESH_INTERVAL;
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.print(temperature, 2);
    lcd.print(" C ");
    Serial.println(temperature, 2);

    if (temperature > t){  
    motor.run(FORWARD);
  }

  if (temperature <= t){
    motor.run(RELEASE);
  }
  
    }
    
    lcd.setCursor(0,1);
    lcd.print("PRESS * FOR MENU");  
  
  

  if (customKey1 == '*'){

    for (int z  = 0; z < 1; z+=0){
    customKey1 = ' ';
    
    while(y != 1){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("A) Temp Set Point");
    lcd.setCursor(0, 1);
    lcd.print("B) Fan Speed");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("C) Fan On/Off");
    lcd.setCursor(0, 1);
    lcd.print("D) Exit Menu");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Choose Option Or");
    lcd.setCursor(0, 1);
    lcd.print("Press # To Redo");
    y = 1;
    }

    char customKey2 = customKeypad.getKey();    

    if(customKey2){

    y = 0;

    for(int i = 0; i < 1; i+=0){
            
      if (customKey2 == 'A'){
        
        lcd.clear();
        customKey2 == ' ';
        lcd.setCursor(0,0);
        lcd.print("Enter Temp Range");
        delay(500);
        
        for (int j = 0; j < 1; j+=0){
            char customKey3 = customKeypad.getKey();

            if (customKey3){
              lcd.setCursor(0, 1);
              lcd.print(customKey3);
              
                  for (int k = 0; k < 1; k+=0){
                    char customKey4 = customKeypad.getKey();
              
                    if (customKey4){
                      lcd.setCursor(1, 1);
                      lcd.print(customKey4);
                  
                      t = (10*(customKey3 - '0') + (customKey4 - '0'));
                  
                      delay(2000);
                      k++;
                      j++;
                    }

                  }
            
              }
             
          }
          
          lcd.clear();
          i++;
            
        }
        else if(customKey2 == 'B'){
          lcd.clear();
          customKey2 = ' ';
          i++;
        }

        else if(customKey2 == 'C'){
          lcd.clear();
          customKey2 = ' ';
          i++;
          char customKeyIO = customKeypad.getKey();

          lcd.setCursor(0, 0);
          lcd.print("A: OFF  B: ON");
          
          lcd.setCursor(0,1);
        }

        else if(customKey2 == 'D'){
          lcd.clear();
          customKey2 = ' ';
          i++;
          z++;
        }

        else if (customKey2 == '#'){
          lcd.clear();
          customKey2 = ' ';
          i++;
          
        }
        
        else{
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Invalid Option");
          delay(1500);
          lcd.clear();
          i++;
        }
      }
      }
    }
  }
  
}
