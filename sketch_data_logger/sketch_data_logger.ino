
#include <Wire.h>
#include <Adafruit_INA219.h>
Adafruit_INA219 ina219_A;
Adafruit_INA219 ina219_B(0x041);


float voltage_A, current_A, power_A, energy_A;
float voltage_B, current_B, power_B, energy_B;
uint32_t timer = 0;
#include <SD.h>
#include <SPI.h>
#include <DS3231.h>

File myFile;
RTClib rtc;

int pinCS = 10; // Pin 10 on Arduino Uno

void setup() {
  pinMode(12, OUTPUT);
  pinMode(2, OUTPUT);
    Serial.begin(115200);
  // SD Card Initialization
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
  Wire.begin(); 

 ina219_A.begin();
  ina219_B.begin();
  delay(1000);
}

void loop() {

  DateTime now = rtc.now();

 voltage_A = ina219_A.getBusVoltage_V() + ina219_A.getShuntVoltage_mV() * 1e-3;
  current_A = ina219_A.getCurrent_mA();
  power_A = ina219_A.getPower_mW();
  energy_A = energy_A + power_A * (millis() - timer) * (2.77778e-7);

  voltage_B = ina219_B.getBusVoltage_V() + ina219_B.getShuntVoltage_mV() * 1e-3;
  current_B = ina219_B.getCurrent_mA();
  power_B = ina219_B.getPower_mW();
  energy_B = energy_B + power_B * (millis() - timer) * (2.77778e-7);

  timer = millis();
  String message =  
        String(now.hour(), DEC) +
  "," + String(now.minute(), DEC) +
  "," + String(now.second(), DEC) +
  "," + String(voltage_A) + 
  "," + String(power_A) + 
  "," + String(current_A) +
  "," + String(energy_A) + 
  "," + String(voltage_B) + 
  "," + String(current_B) +
  "," + String(power_B) + 
  "," + String(energy_B); 
  
  
  
  
  Serial.print("POST data to SD card:" );
  Serial.println(message);


 
  myFile = SD.open("probe0.txt", FILE_WRITE);
 
  if (myFile) {  
     digitalWrite(2, 1);  
    myFile.println(message);
    myFile.close(); 
    

}  else {
    Serial.println("error opening test.txt");
  }
  delay(1000);
  digitalWrite(2, 0);
  delay(4000);
}
