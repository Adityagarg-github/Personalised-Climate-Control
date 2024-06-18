const int analogIn = A0;
int RawValue = 0;
int buttonPin = 3;
int buttonPin2 = 4;
int buttonInput = 1;
int buttonInput2 = 1;
int buttonState = 0;
int buttonState2 = 0;
int peltier = A1;
int count1=0;
int count2=0;
int temp=0;
int dimvalue=100;
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd_1(0x27,16,2);
#include <DHT11.h>
DHT11 dht11(2);

void setup()
{
    // Initialize serial communication to allow debugging and data readout.
    // Using a baud rate of 9600 bps.
     lcd_1.init();                      // initialize the lcd 
    lcd_1.init();
  // Print a message to the LCD.
    lcd_1.backlight();
    pinMode(buttonPin, INPUT);
    pinMode(buttonPin2, INPUT);
     pinMode(peltier, OUTPUT);
    Serial.begin(9600);
}
void loop(){
int temperature = dht11.readTemperature();
temp=temperature;
// if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT )
//     {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" °C");
        lcd_1.print(temperature);
        lcd_1.print("C ");
    // }
        lcd_1.print(temperature);
        lcd_1.print("C ");
        for(int i=0;i<10;i++){
          delay(500);
          lcd_1.print(temperature);
          lcd_1.print("C ");
        }
     delay(1000);
    // digitalWrite(peltier, HIGH);

buttonInput = digitalRead(buttonPin);
buttonInput2=digitalRead(buttonPin2);

if (buttonInput == 0) {

  if (buttonState == 0) {

    buttonState = 1;

  } else {

    buttonState = 0;

  }
  delay(500);

}

if (buttonInput2 == 0) {

  if (buttonState2 == 0) {

    buttonState2 = 1;

  } else {

    buttonState2 = 0;

  }
  delay(500);

}

if (buttonState == 1) {
  count1++;
  if(count1%10==9){
    temperature++;
    if(temperature>temp+1){
    temperature--;
    }
  }
  dimvalue+=5;
  if(dimvalue>=253){
    dimvalue=250;
  }
  analogWrite(peltier, dimvalue); // Look first on how much voltage your peltier unit can handle 255 = 5V

  } 
  if(buttonState2==1) {
    count2++;
    if(count2%10==9){
      temperature--;
      if(temperature<temp-1){
        temperature++;
      }
    }
    dimvalue-=5;
    if(dimvalue<=5){
      dimvalue=5;
    }
  analogWrite(peltier, dimvalue);

  }

  delay(500);
}


