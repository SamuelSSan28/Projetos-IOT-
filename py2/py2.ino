// --- Bibliotecas ---
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
ESP8266WiFiMulti WiFiMulti; //cria uma instância da classe ESP8266WiFiMulti
IPAddress local_IP(192, 168, 10, 110); //Cria uma instância da classe IPAddress e define o ip do servidor

// =============================================================================================================
// --- Variáveis Globais ---
int msg_Server = 0;
double    temperatura = 0x00,             //armazena a temperatura em inteiro
          umidade     = 0x00;             //armazena a umidade em inteiro

// =============================================================================================================



void setup(){
  //Mudanças:
  dht.begin();                          //inicia a comunicação com o dht
  pinMode(pin_sct, INPUT);             //entrada para sensor de corrente
  
  Serial.begin(9600);
  //configura modo como estação
  WiFi.mode(WIFI_STA);

  //escreve no display "Definindo rede"
  escreva("Definindo rede",1000);
  
  //parametros: WiFi.softAP(nomeDoAccessPoint, senhaRede)
  //redeVisivel: a rede pode ou não aparecer para outros serviços 
  WiFiMulti.addAP("UFPI", "");
  
  escreva("CONECTANDO NA REDE.....", 1000);

  //enquanto o cliente não estiver conectado, escreve "."
  while (WiFiMulti.run() != WL_CONNECTED) 
  escreva(".", 1000);

  //escreve no display "Pronto"
  escreva("CONECTADO!",1000);

  //escreve no display "Endereco IP:"
  escreva("Endereco IP:",1000);
    
  //escreve no display o ip local
  escreva(WiFi.localIP().toString(), 1000);
  
  //escreve no display "Conectando Com servidor..."
  escreva("Conectando Com servidor...",1000);
  
}

void loop() 
{
   temperatura = dht.readTemperature();
   umidade     = dht.readHumidity();

  
  //porta 5000 do protocolo TCP, deve ser a mesma utilizada pelo servidor
  const uint16_t port = 9999;
  //endereço ip, deve ser o mesmo utilizado pelo servidor
  const char * host = "10.13.46.137";

  //inicializa a lib do cliente
  WiFiClient client;
    
  //se o cliente não estiver conectado, exibe "Falha..."
  if (!client.connect(host, port)) {
    escreva("Falha...", 1000);
  }else{    
    client.println(" ");
    client.println(temperatura);  
    client.println(umidade); 

    while (client.connected() || client.available())   {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        Serial.println(line);
        msg_Server = line.toInt();
        client.stop();
      }
    }
    
  }

  if(msg_Server == 1){
    Serial.println("Liga Ar");
    }
  
  delay(1000);
}

//escreve no monitor Serial 
void escreva(String texto, int intervalo)
{
  Serial.println(texto);
  //aguarda o intervalo passado por parametro
  delay(intervalo);
}
