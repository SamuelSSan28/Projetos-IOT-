# Projetos-IOT
  Projetos desenvolvidos no laboratório Disnel.
  
## AR_CONTROLE
  - Clona um controle de ar condicionado e registra o uso em BD via sockets
  - Microntrolador: ESP8266
  - Modulos: Receptor IR, LED IR, Controle
  
 ## Envia_Dados_Dos_Sensores_XBEE
  - Comunicação entre 2 modulos Xbee V1 para enviar dados de sensores aclopados ao arduino
  - Microntrolador: Arduino Mega.
  - Modulos: Xbee V1, Adaptador do Xbee pro arduino, Sensor DHT22, Sensor de Reflectancia,Sensor LDR.
  - Extra: Software XCTU para configuração dos XBEE
 
 ## Sensores_Capacete
  - Tentativa de inserir os sensores de temperatura, reflectancia e luminosidade para indentificar se um capacete está sendo utilizado.(Faltou o capacete)
  - Microntrolador: Arduino Nano
  - Modulos: Sensor DHT22, Sensor de Reflectancia,Sensor LDR.
 
 ## Xbee_Comunicacao
  - Teste de comunicação entre 2 modulos Xbee V1 
  - Microntrolador: Arduino Mega.
  - Modulos: Xbee V1, Adaptador do Xbee pro arduino
  - Extra: Software XCTU para configuração dos XBEE
  
## Server_TCP - nodeMCU
  - Cria um servidor local (TCP/IP) em um ESP8266 
  - Microntrolador: ESP8266.
 
 ## Clientepy - nodeMCU
  - Envia dados de corrente e temperatura para um servidor 
  - Microntrolador: ESP8266.
  - Modulos: Sensor DHT22, Sensor SCT013.
  
  ## Controle_wifi_MQTT
  - Clona um controle de ar condicionado e registra o uso em um BD utilizando o protocolo MQTT
  - Microntrolador: ESP8266
  - Modulos: Receptor IR, LED IR
  - Broker: Mosquitto

 ## Py2
  - Envia dados de temperatura e humidade para um servidor 
  - Microntrolador: ESP8266
  - Modulos: Sensor DHT22, Sensor SCT013.
  
## Sensor_de_corrente
  - Envia dados de corrente para um servidor 
  - Microntrolador: ESP8266
  - Modulos: Sensor SCT013
  - Extra: Código Adaptado pra o ESP8266 baseado no do [Portal Vida de Silicio](https://portal.vidadesilicio.com.br/sct-013-sensor-de-corrente-alternada/)

## Template_sensor_ppgccufpi
  - Clona um controle de ar condicionado e registra o uso em um BD utilizando o protocolo MQTT/Controle com IR 
  - Microntrolador: ESP8266
  - Modulos: Receptor IR, LED IR, Controle
  - Extra: App MQTT Dash para enviar comandos pelo celular
  - Broker: Mosquitto
  
