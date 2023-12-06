uint32_t timer;                                 //Variable zum Speichern der Zeit nach jeder Bewegung

int servoPosition = 90;

uint32_t timer;                                 //Variable zum Speichern der Zeit nach jeder Bewegung

//Einstellungen
#define treshold 2                             //Differenz zwischen den Werten der Sensoren, an denen das Gerät 1 Grad macht

#define photoA_pin A2                            //Pins definieren
#define photoB_pin A3
#define servo_pin 0
#define mosfet_pin 1

#include <Servo8Bit.h>                              //Bibliotek für die Servomotorkontrolle

Servo8Bit myservo;                                  //Servoobjekt erstellen, um ein Servo zu steuern

void setup() {
myservo.attach(0);
pinMode(mosfet_pin, OUTPUT);
digitalWrite(mosfet_pin, 1);
myservo.write(servoPosition);
delay(1000);
digitalWrite(mosfet_pin, 0);
}

void loop() {

uint32_t startup = millis();


int photoA = analogRead(photoA_pin) + correctA;
int photoB = analogRead(photoB_pin) + correctB;

int a = photoA-photoB;

if(abs(a)>=treshold){
  int direction = abs(diff) / diff;
  digitalWrite(mosfet_pin, 1);
  myservo.write(direction * degrees);
  timer = millis();
}
if(timer >= 1000){
digitalWrite(mosfet_pin, 0);
}
}
