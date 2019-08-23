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

IPAddress local_IP(192, 168, 10, 110); //Cria uma instância da classe IPAddress e define o ip do servidor

// =============================================================================================================
// --- Protótipos das Funções ---
long moving_average();       //Função para filtro de média móvel

// --- Variáveis Globais ---
short     screens   = 0x01;               //variável para seleção de menus
 
boolean   but_flag  = 0x00,               //flag auxiliar para o botão
          amp_unity = 0x00;               //flag de modificação de múltiplo de unidade de corrente

double    temperatura = 0x00,             //armazena a temperatura em inteiro
          umidade     = 0x00;             //armazena a umidade em inteiro

double    filtrado;                       //receberá os valores filtrados para temperatura e umidade

double    numbers[n];                     //vetor com os valores para média móvel

// =============================================================================================================



void setup(){
  //Mudanças:
  dht.begin();                          //inicia a comunicação com o dht
  pinMode(pin_sct, INPUT);             //entrada para sensor de corrente
  //Pino, calibracao - Cur Const= Ratio/BurdenR. 2000/33 = 60
  emon1.current(pin_sct, 60);
  //------
  
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
  
  double Irms = emon1.calcIrms(1480);   //Calcula a corrente
   temperatura = dht.readTemperature();
   umidade     = dht.readHumidity();

  
  //porta 5000 do protocolo TCP, deve ser a mesma utilizada pelo servidor
  const uint16_t port = 9999;
  //endereço ip, deve ser o mesmo utilizado pelo servidor
  const char * host = "10.94.15.69";

  //inicializa a lib do cliente
  WiFiClient client;

  //se o cliente não estiver conectado, exibe "Falha..."
  if (!client.connect(host, port)) 
  {
    escreva("Falha...", 1000);
    return;
  }else{
    client.println(" ");
    client.println("Disnel");
    client.println(temperatura); 
    client.println(Irms); 
    client.println(umidade); 
    client.println("fim"); 
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
