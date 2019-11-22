// --- Bibliotecas ---
#include "EmonLib.h"            //Biblioteca para o sensor de corrente
#include "DHT.h"                //biblioteca do sensor de umidade e temperatura
#include <ESP8266WiFi.h> //lib para conectar o wifi do ESP201
#include <ESP8266WiFiMulti.h>//lib para as funções addAP e  run
#include <SPI.h>  //protocolo síncrono de dados serial

// =============================================================================================================
// --- Mapeamento de Hardware ---
#define     pin_sct     A0     //sensor de corrente
#define     dht_pin    5       //pino de sinal do dht22 ligado no digital 5

// Definindo o sensor DHT11
#define dht_type DHT22

// Inicializando o sensor DHT
DHT dht(dht_pin, dht_type, 15);

// --- Constantes do Projeto ---
#define     rede       220     //tensão da rede local 220V
#define      n          50     //número de pontos da média móvel

// =============================================================================================================
// --- Declaração de Objetos ---
EnergyMonitor emon1;            //cria objeto para sensor de corrente

ESP8266WiFiMulti WiFiMulti; //cria uma instância da classe ESP8266WiFiMulti

// =============================================================================================================

// --- Variáveis Globais ---
short     screens   = 0x01;               //variável para seleção de menus
 
boolean   but_flag  = 0x00,               //flag auxiliar para o botão
          amp_unity = 0x00;               //flag de modificação de múltiplo de unidade de corrente

double    temperatura = 0x00,             //armazena a temperatura em inteiro
          umidade     = 0x00;             //armazena a umidade em inteiro

double    filtrado;                       //receberá os valores filtrados para temperatura e umidade

const uint16_t port = 9999;   //porta  do protocolo TCP, deve ser a mesma utilizada pelo servidor 

const char * host = "10.94.15.69";  //endereço ip, deve ser o mesmo utilizado pelo servidor

double    numbers[n];                     //vetor com os valores para média móvel

// =============================================================================================================



void setup(){
  dht.begin();                          //inicia a comunicação com o dht
  pinMode(pin_sct, INPUT);             //entrada para sensor de corrente
  //Pino, calibracao - Cur Const= Ratio/BurdenR. 2000/33 = 60
  emon1.current(pin_sct, 39);
  
  Serial.begin(9600);
  //configura modo como estação
  WiFi.mode(WIFI_STA);
  
  WiFiMulti.addAP("UFPI", ""); //parametros: WiFi.softAP(nomeDoAccessPoint, senhaRede)
  
  escreva("CONECTANDO NA REDE.....", 1000);

  //enquanto o cliente não estiver conectado, escreve "."
  while (WiFiMulti.run() != WL_CONNECTED) 
    escreva(".", 1000); 
}

void loop() {
  double Irms = emon1.calcIrms(2000);   //Calcula a corrente
  Serial.print("Corrente: " + String(Irms));
  Serial.println("   Potencia: " + String(Irms * 234));
   temperatura = dht.readTemperature();
   umidade     = dht.readHumidity();

  WiFiClient client;  //inicializa a lib do cliente
  
  //se o cliente não estiver conectado, exibe "Falha..."
  if (!client.connect(host, port)) {
    escreva("Falha...", 1000);
    client.stop();
    return;
  }else{
    client.println(" ");
    client.println("0"); //tipo de node
    client.println(4); //id do node
    client.println(temperatura); 
    client.println(Irms); //Corrente 
    client.println(umidade); 
    client.println("fim");
    client.stop(); 
    delay(10000);
  }
}

//escreve no monitor Serial 
void escreva(String texto, int intervalo)
{
  Serial.println(texto);
  //aguarda o intervalo passado por parametro
  delay(intervalo);
}
