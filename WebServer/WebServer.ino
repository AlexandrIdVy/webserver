#include <ESP8266WiFi.h>                                                  // Библиотека для создания Wi-Fi подключения (клиент или точка доступа)
#include <WebSocketsServer.h>                                             // Библиотека для создания WebSocketsServer'а
#include <ESP8266WebServer.h>                                             // Библиотека для управления устройством по HTTP (например из браузера)
#include <LittleFS.h>                                                     // Библиотека для работы с файловой системой
#include <SimpleFTPServer.h>                                             // Библиотека для работы с LittleFS по FTP
#include <DHT.h>                                                          // Библиотека для работы с датчиком температуры и влажности "DHT"
#include <ArduinoJson.h>                                                  // Библиотека для чтения и создания JSON запросов
#include <PubSubClient.h>

const char ssid[] = "";
const char pass[] = "";

#define LED_1 16                                                      // Определяем номер контакта для вклчения светодиода 1
#define LED_2 5                                                       // Определяем номер контакта для вклчения светодиода 2

#define DHTPIN 13                                                     // Определяем номер контакта для получения данных DHT
#define DHTTYPE DHT11                                                 // Определяем тип используемого датчика DHT
#define DHT11_SAMPLE_DELAY 2000                                       // Устанавливаем переодичность опроса датчика DHT

uint32_t delayMS = 0;                                                 // Определяем переменную таймера
uint32_t delayMSBlynk = 0;                                            // Определяем переменную таймера
float h;                                                              // Определяем переменную значения влажности
float t;                                                              // Определяем переменную значения температуры

String JSONtxt = "";                                                  // Определяем переменную для хранения JSON

boolean LEDonoff1 = true;                                                // Определяем переменную для хранения состояни светодиода 1
boolean LEDonoff2 = true;                                                // Определяем переменную для хранения состояни светодиода 2

// MQTT
const char* mqtt_server = "";
const int mqtt_port = ;
const char* mqtt_user = "";
const char* mqtt_password = "";

// RELAY and SENSOR
const String relay_topic = "/sound";
const String relay_topic_state = "/sound/state";
const String relay2_topic = "/tv";
const String relay2_topic_state = "/tv/state";
const String co2_t_topic = "/mhz19/temperature";
const String co2_c_topic = "/mhz19/co2";

DHT dht(DHTPIN, DHTTYPE);                                               // Инициализируем датчик DHT
FtpServer ftpSrv;                                                       // Создаём объект для работы с FTP
ESP8266WebServer server(80);                                            // Определяем объект и порт сервера для работы с HTTP
WebSocketsServer webSocket = WebSocketsServer(88);                      // Определяем объект и порт сервера для работы с WebSocketsServer

WiFiClient espClient;
PubSubClient client(espClient);

DynamicJsonDocument docGet(200);                                        // Выделяем память для полученного Json
DynamicJsonDocument docSend(400);                                       // Выделяем память для отправленного Json

void setup() {
  Serial.begin(9600);                                   // Инициализируем вывод данных на серийный порт со скоростью 9600 бод
  pinMode(LED_1, OUTPUT);                               // Определяем режим пин LED_1
  pinMode(LED_2, OUTPUT);                               // Определяем режим пин LED_2   
  WiFi.begin(ssid, pass);                               // Соединяемся с WiFi-сетью 
  while(WiFi.status() != WL_CONNECTED) { delay(500); }  // -- Делаем задержку в пол секунды, пока соединение не установится

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
  //Serial.println(WiFi.localIP());                     // Выводим локальный IP-адрес ESP8266
  //Serial.println(WiFi.macAddress());                  // Выводим mac фадрес
  checkState1(digitalRead(LED_1));                      // Проверяем состояние пина светодиода 
  checkState2(digitalRead(LED_2));                      // Проверяем состояние пина светодиода
  LittleFS.begin();                             // Инициализируем работу с файловой системой  
  server.on("/", handleHTML);                 // Подключаем главную страницу вебсервера index.html
  server.on("/index.css", handleCSS);           // Подключаем стили css.css
  server.on("/index.js", handleJS);          // Подключаем стили script.js
  server.on("/constants.js", handleConstantsJS);          // Подключаем стили script.js
  server.on("/Section.js", handleSectionJS);          // Подключаем стили script.js
  server.on("/Device.js", handleDeviceJS);          // Подключаем стили script.js
  server.on("/Request.js", handleRequestJS);          // Подключаем стили script.js    
  server.on("/sound.png", handleSoundPNG);          // Подключаем стили script.js
  server.on("/tv.png", handleTvPNG);          // Подключаем стили script.js  
  server.begin();                             // Инициализируем Web-сервер
  webSocket.begin();                          // Инициализируем WebSocketsServer
  webSocket.onEvent(webSocketEvent);          // Возвращаем события, когда они происходят
  ftpSrv.begin("relay","relay");              // Поднимаем FTP-сервер для удобства отладки работы HTML (логин: relay, пароль: relay)
  dht.begin();                                // Инициализируем DHT    
}

void loop() {
  if (client.connected()) {     
    client.loop();    
  }
  else {
    reconnect(); 
  }  
                                    
  server.handleClient();                      // Обработчик HTTP-событий (отлавливает HTTP-запросы к устройству и обрабатывает их в соответствии с выше описанным алгоритмом)
  ftpSrv.handleFTP();                         // Обработчик FTP-соединений
  //getMeteo();                                 // Запускаем опрос DHT
  webSocket.loop();                           // Запускаем WebSocketsServer 
}
