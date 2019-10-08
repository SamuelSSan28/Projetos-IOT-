#include <ESP8266WiFi.h> //lib para conectar o wifi do ESP201
#include <SPI.h> //protocolo síncrono de dados serial

//ip da rede local
IPAddress local_IP(192, 168, 10, 11);
//gateway da rede local
IPAddress gateway(192, 168, 10, 10);
//subnet é uma divisão lógica da rede local
IPAddress subnet(255, 255, 255, 0);

//define servidor na porta 5000 do protocolo TCP
WiFiServer servidor(5000);

void setup()
{
  Serial.begin(9600);
  
  //escreve no display "Definindo modo"
  escreva("Definindo modo", true, 1000, false);
  
  //configura modo como access point
  WiFi.mode(WIFI_AP);
  
  //escreve no display "Pronto"
  escreva("Pronto!", false, 1000, true);
  
  //escreve no display "Definindo AP"
  escreva("Definindo AP", true, 1000, false);

  //enquanto a interface de rede do access point não for configurada, exibe "."
  while (!(WiFi.softAPConfig(local_IP, gateway, subnet))) 
    escreva(".", false, 100, false);  
  
  //escreve no display "Definindo AP"
  escreva("Pronto!", false, 1000, true);

  //escreve no display "Definindo rede"
  escreva("Definindo rede", true, 1000, false);

  //enquanto a rede não for definida, escreve "."
  //parametros: WiFi.softAP(nomeDoAccessPoint, senhaRede, canal, redeVisivel)
  //canal: canal usado pelo ESP, pode ser do 1 ao 11
  //redeVisivel: a rede pode ou não aparecer para outros serviços 
  while (!(WiFi.softAP("WiFi_Range", "12341234", 6, false))) 
    escreva(".", false, 100, false);
  
  //escreve no display "Definindo AP"
  escreva("Pronto!", false, 1000, true);

  //escreve no display "Endereco IP"
  escreva("Endereco IP", true, 1000, false);
  
  //escreve no display o ip do servidor
  escreva(WiFi.softAPIP().toString(), false, 1000, true);
  
  //escreve no display "Iniciando"
  escreva("Iniciando", true, 10, false);
  
  //escreve no display "servidor"
  escreva("servidor...", true, 1000, false);

  //inicializa servidor
  servidor.begin();

  //define servidor para trabalhar sem delay
  //caso seja setado como true, tem o intuito de reduzir o tráfego TCP / IP de pequenos pacotes 
  servidor.setNoDelay(true);
  
  //escreve no display "Pronto!"
  escreva("Pronto!", false, 1000, true);
  
  //escreve no display "Aguardando STA"
  escreva("Aguardando STA", true, 1000, false);
}

void loop()
{
  //enquanto a quantidade de estações conectadas no servidor for zero
  //ou seja, ninguém conectou ainda
  while (WiFi.softAPgetStationNum() == 0)
  {
    //aguarda 1 segundo
    delay(1000);

    //se alguém conectou
    if (WiFi.softAPgetStationNum() != 0)
    {
      //exibe mensagem
      escreva("STA conectada!", true, 1000, false);
    }
  }

  //obtém o cliente que está conectado ao servidor
  WiFiClient client = servidor.available();
  
  if (client)
  {
    //enquanto o cliente estiver conectado
    while (client.connected())
    {
      //se houver dados, leia
      if (client.available())
      { 
        //recebe dados do cliente
        String msg = client.readStringUntil('\n');
        
        //exibe a força do sinal da estação
        escreva(msg, true, 1000, true);        
        
        //espera até que todos os caracteres de saída no buffer tenham sido enviados
        client.flush();
      }
    }
    //aguarda envio
    delay(1); 

    // fecha conexão
    client.stop();
  }
}

//escreve no display de acordo com os parametros
//nl = pular linha
//intervalo = tempo enviado para o delay
//limpar = limpa a tela do display
void escreva(String texto, boolean nl, int intervalo, boolean limpar)
{
  //se deseja pular linha no display, então pula
  if (nl) 
    Serial.println(texto);
  else  //se não, exibe texto sem pular linha
    Serial.print(texto);

  //aguarda o intervalo passado por parametro
  delay(intervalo);
  
}
