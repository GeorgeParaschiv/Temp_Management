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
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {22, 25, 26, 29};
byte colPins[COLS] = {30, 33, 34, 37};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

static const unsigned long REFRESH_INTERVAL1 = 2000;
static unsigned long lastRefreshTime1 = 0;
static unsigned long lastRefreshTime2 = 0;

int a = 1;
int b = 1;
int c = 0;


void setup() {
  lcd.begin(16, 2);
  motor.setSpeed(128);
  motor.run(RELEASE);
  Serial.begin(9600);
}

long t = 28;
int y = 0;

void loop() {

  char menu = customKeypad.getKey();

  DHT.read11(dht_apin);

  float temperature = DHT.temperature;

  if (millis() - lastRefreshTime1 >= REFRESH_INTERVAL1) { //Refreshes Temperature every 2 seconds
    lastRefreshTime1 += REFRESH_INTERVAL1;
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature, 2);
    lcd.print(" C ");
    Serial.println(temperature, 2);

    if (temperature > t) {
      motor.run(FORWARD);
    }

    if (temperature <= t) {
      motor.run(RELEASE);
    }

  }

  lcd.setCursor(0, 1);
  lcd.print("PRESS * FOR MENU");

  if (menu == '*') {

    for (int z  = 0; z < 1; z += 0) {
      menu = ' ';
      char menu_choice;
      unsigned long k = millis();

      while (y != 1) {

        if (a == 1 && y != 1) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("A) Temp Setpoint");
          lcd.setCursor(0, 1);
          lcd.print("B) Fan Speed");
          a = 0;
        }

        menu_choice = customKeypad.getKey();

        if (menu_choice == 'A' || menu_choice == 'B' || menu_choice == 'C' || menu_choice == 'D') {
          y = 1;
          a = 1;
        }

        if ((millis() - k >= REFRESH_INTERVAL1) && y != 1) {
          k += REFRESH_INTERVAL1;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("C) Manual/Auto ");
          lcd.setCursor(0, 1);
          lcd.print("D) Exit Menu");
          c = 0;

          while (c != 1) {

            menu_choice = customKeypad.getKey();

            if (menu_choice == 'A' || menu_choice == 'B' || menu_choice == 'C' || menu_choice == 'D') {
              y = 1;
              a = 1;
              c = 1;
            }

            if ((millis() - k >= REFRESH_INTERVAL1) && y != 1) {
              k += REFRESH_INTERVAL1;
              a = 1;
              c = 1;
            }
          }
        }
      }

      if (menu_choice == 'A' || menu_choice == 'B' || menu_choice == 'C' || menu_choice == 'D') {

        y = 0;

        for (int i = 0; i < 1; i += 0) {

          if (menu_choice == 'A') { //TEMP SETPOINT

            lcd.clear();
            menu_choice == ' ';
            lcd.setCursor(0, 0);
            lcd.print("Enter Temp Point");
            delay(500);

            for (int j = 0; j < 1; j += 0) {
              char temp_digit1 = customKeypad.getKey();

              if (temp_digit1) {
                lcd.setCursor(0, 1);
                lcd.print(temp_digit1);

                for (int k = 0; k < 1; k += 0) {
                  char temp_digit2 = customKeypad.getKey();

                  if (temp_digit2) {
                    lcd.setCursor(1, 1);
                    lcd.print(temp_digit2);
                    lcd.print(" Degrees C");

                    t = (10 * (temp_digit1 - '0') + (temp_digit2 - '0'));

                    if (temperature > t) {
                      motor.run(FORWARD);
                    }

                    if (temperature <= t) {
                      motor.run(RELEASE);
                    }

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
          else if (menu_choice == 'B') { //FAN SPEED CONTROL
            lcd.clear();
            menu_choice = ' ';


            lcd.setCursor(0, 0);
            lcd.print("1)Speed 0-100:");
            lcd.setCursor(0, 1);

            int s = 0;
            int t = 0;

            while (s != 1) {
              char speed1 = customKeypad.getKey();

              if (speed1) {
                lcd.print(speed1);
                while (t != 1) {
                  char speed2 = customKeypad.getKey();

                  if (speed2) {
                    lcd.print(speed2);
                    lcd.print("%");
                    delay(1000);
                    motor.setSpeed( (int) (((0.1 * (speed1 - '0')) + (0.01 * (speed2 - '0'))) * 255));
                    speed1 = ' ';
                    speed2 = ' ';
                    t = 1;
                    s = 1;
                  }
                }
              }

            }
            i++;
          }

          else if (menu_choice == 'C') {
            lcd.clear();
            menu_choice = ' ';
            i++;
            char manual_or_auto = customKeypad.getKey();

            lcd.setCursor(0, 0);
            lcd.print("A: OFF  B: ON");

            lcd.setCursor(0, 1);


          }

          else if (menu_choice == 'D') {
            lcd.clear();
            menu_choice = ' ';
            i++;
            z++;
          }

          else {
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
