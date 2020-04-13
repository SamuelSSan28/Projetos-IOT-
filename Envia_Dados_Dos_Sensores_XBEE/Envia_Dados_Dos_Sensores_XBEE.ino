#include <dht.h>   //biblioteca do sensor de umidade e temperatura

#define temp_pin 53 //pino de sinal do dht11 ligado no digital 5
#define pinSensorRefletancia 51 //PINO DIGITAL UTILIZADO PELO MÓDULO
#define ldrPin A10 //LDR no pino analígico A10

dht   my_dht;   //objeto para o sensor
int ldrValor = 0; //Valor lido do LDR
float    temperatura = 0x00,   //armazena a temperatura em float
       umidade     = 0x00;   //armazena a umidade em float  

void setup(){
  pinMode(pinSensorRefletancia, INPUT); //DEFINE O PINO COMO ENTRADA
  Serial.begin (9600); //INICIALIZA A SERIAL
}

void loop(){
  String reflec = "Nenhum objeto encontrado\n";
  ldrValor = analogRead(ldrPin);
  String ldr = String(ldrValor);
 
  if(digitalRead(pinSensorRefletancia) == LOW){ //SE LEITURA DO PINO FOR IGUAL A LOW, FAZ
    reflec = "Objeto Encontrado\n";
  }

  my_dht.read22(temp_pin);
  temperatura = my_dht.temperature;
  //umidade     = my_dht.humidity;
  
  String temp = String(temperatura);
  
  Serial.print("Sensor LDR: " + ldr + "\nTemperatura: " + temp + "\nSensor de Reflectancia: " + reflec + "--------------\n");// envia informacoes pro outro XBEE
  delay(200);
  
}
