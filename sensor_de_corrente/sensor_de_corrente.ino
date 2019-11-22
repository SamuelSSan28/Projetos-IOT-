// --- Bibliotecas ---
#include "EmonLib.h"            //Biblioteca para o sensor de corrente
#include "DHT.h"                //biblioteca do sensor de umidade e temperatura
#include <ESP8266WiFi.h> //lib para conectar o wifi do ESP201
#include <ESP8266WiFiMulti.h>//lib para as funções addAP e  run
#include <SPI.h>  //protocolo síncrono de dados serial

// =============================================================================================================
// --- Mapeamento de Hardware ---
#define     pin_sct     A0     //sensor de corrente

// --- Constantes do Projeto ---
#define     rede       220     //tensão da rede local 220V
#define      n          50     //número de pontos da média móvel

// =============================================================================================================
// --- Declaração de Objetos ---
EnergyMonitor emon1;            //cria objeto para sensor de corrente
// =============================================================================================================

void setup(){
  pinMode(pin_sct, INPUT);             //entrada para sensor de corrente
  //Pino, calibracao - Cur Const= Ratio/BurdenR. 2000/33 = 60
  emon1.current(pin_sct, 60);
  
  Serial.begin(9600);
}

void loop() {
  double Irms = emon1.calcIrms(1480);   //Calcula a corrente
  Serial.print("Corrente: " + String(Irms));
  Serial.print("    Potencia: " + String(Irms*220));
  Serial.println();
    delay(1000);
  }
