#include <SoftwareSerial.h>
SoftwareSerial XBee(2, 3); // RX, TX

int ledPin = 13;

void setup(){
  Serial.begin(9600);
  XBee.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop(){
    digitalWrite(ledPin, HIGH); delay(1000); 
    String ldr = String(10);
    String temp = String(26.6);
    String reflec = "Objeto Encontrado";
    Serial.print("Sensor LDR: " + ldr + "\nTemperatura: " + temp + "\nSensor de Reflectancia: " + reflec );
    digitalWrite(ledPin, LOW);  delay(1000);
    
  }
