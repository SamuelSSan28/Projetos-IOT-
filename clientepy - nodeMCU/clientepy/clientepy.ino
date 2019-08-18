#include <ESP8266WiFi.h> //lib para conectar o wifi do ESP201
#include <ESP8266WiFiMulti.h>//lib para as funções addAP e  run
#include <SPI.h>  //protocolo síncrono de dados serial

//cria uma instância da classe ESP8266WiFiMulti
ESP8266WiFiMulti WiFiMulti;

//Criar uma instância da classe IPAddress e define o ip do servidor
IPAddress local_IP(192, 168, 10, 110);

void setup() 
{
  
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
    client.println("local");
    client.println("Temperatura"); 
    client.println("Corrente"); 
    client.println("Umidade"); 
    client.println("Data"); 
    client.println("Horario"); 
    client.println("fim"); 
    delay(10000);
  }
}

//escreve no monitor Serial de acordo com os parametros
//intervalo = tempo enviado para o delay
void escreva(String texto, int intervalo)
{
  Serial.println(texto);
  //aguarda o intervalo passado por parametro
  delay(intervalo);
}
