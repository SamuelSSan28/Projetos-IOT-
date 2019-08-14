#include <dht.h>   //biblioteca do sensor de umidade e temperatura

#define dht_pin 7  //pino de sinal do dht11 ligado no digital 5
#define pinSensorRefletancia  8 //PINO DIGITAL UTILIZADO PELO MÓDULO
#define ldrPin 0 //LDR no pino analígico 8
#define pinLed 52

dht   my_dht;   //objeto para o sensor
int ldrValor = 0; //Valor lido do LDR
float    temperatura = 0x00,   //armazena a temperatura em float
       umidade     = 0x00;   //armazena a umidade em float  


void setup(){
  pinMode(pinSensorRefletancia, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(pinLed, OUTPUT);
  Serial.begin (9600); //INICIALIZA A SERIAL
}

void loop(){
  ldrValor = analogRead(ldrPin);
  //se o valor lido for maior que 500, liga o led (quanto mais próximo de 1023 mais escuro está)
 if (ldrValor >= 900) {
      digitalWrite(13,0);
      delay(1000);
 // senão, apaga o led
 }else 
    digitalWrite(13,1);
 
 //imprime o valor lido do LDR no monitor serial
 Serial.print("Sensor LDR: ");
 Serial.println(ldrValor);
 Serial.print("\n\n");
 
  if(digitalRead(pinSensorRefletancia) == LOW){ //SE LEITURA DO PINO FOR IGUAL A LOW, FAZ
    Serial.println ("Sensor de Reflectancia: Objeto detectado"); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.print("\n\n");
    delay(1000);
  }

  my_dht.read22(dht_pin);
  temperatura = my_dht.temperature;
  //umidade     = my_dht.humidity;
 Serial.print("Temperatura: ");
 Serial.print(temperatura);
 Serial.print("\n\n");


  delay(1000);
  
}
