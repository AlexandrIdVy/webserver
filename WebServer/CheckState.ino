// --- Функция опроса датчика DHT

void getMeteo() {
  
  uint32_t currentMS = millis();                              // Определяем переменную для функции времени millis()
  
  if ( currentMS - delayMS >= DHT11_SAMPLE_DELAY ) {
    delayMS = currentMS;                                      // Сбрасываем таймер
    
    h = dht.readHumidity();                                   // Записываем в переменную h значение влажности
    t = dht.readTemperature();                                // Записываем в переменную t значение температуры 

    docSend["Meteo"]["Temperature"] = serialized(String(t,1));           // Записываем в JSON объект Meto значение переменной h   
    docSend["Meteo"]["Humidity"] = serialized(String(h,0));              // Записываем в JSON объект Meto значение переменной t
    //client.publish(co2_t_topic.c_str(), String(t,1).c_str(), true);   
    //client.publish(co2_c_topic.c_str(), String(h,0).c_str(), true);  
  } 

}

// --- Функция проверки состояния светодиода 1

void checkState1(bool val){
  
 if (val) {
    LEDonoff1 = true;    
    docSend[0]["id"] = 1;
    docSend[0]["type"] = "switch";
    docSend[0]["state"] = true;
    docSend[0]["location"] = "зал";
    docSend[0]["on"] = true;
    docSend[0]["image"] = "tv";
    docSend[0]["name"] = "телевизор";    
  }
  else {
    LEDonoff1 = false;    
    docSend[0]["id"] = 1;
    docSend[0]["type"] = "switch";
    docSend[0]["state"] = true;
    docSend[0]["location"] = "зал";
    docSend[0]["on"] = false;
    docSend[0]["image"] = "tv";
    docSend[0]["name"] = "телевизор"; 
 }   
  
}

// --- Функция проверки состояния светодиода 2

void checkState2(bool val){
  
 if (val) {
    LEDonoff2 = true;    
    docSend[1]["id"] = 2;
    docSend[1]["type"] = "switch";
    docSend[1]["state"] = true;
    docSend[1]["location"] = "зал";
    docSend[1]["on"] = true;
    docSend[1]["image"] = "sound";
    docSend[1]["name"] = "колонки";    
  }
  else {
    LEDonoff2 = false;    
    docSend[1]["id"] = 2;
    docSend[1]["type"] = "switch";
    docSend[1]["state"] = true;
    docSend[1]["location"] = "зал";
    docSend[1]["on"] = true;
    docSend[1]["image"] = "sound";
    docSend[1]["name"] = "колонки"; 
 }   
  
}
