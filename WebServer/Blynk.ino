void callback(char* topic, byte* payload, unsigned int length) {
    
  String data_pay;
  for (int i = 0; i < length; i++) {
    data_pay += String((char)payload[i]);
  }

    Serial.println(data_pay);
    
  if( String(topic) == relay_topic ){
        if(data_pay == "1") LEDonoff1 = true;
        if(data_pay == "0") LEDonoff1 = false;
    }

  if( String(topic) == relay2_topic ){
        if(data_pay == "1") LEDonoff2 = true;
        if(data_pay == "0") LEDonoff2 = false;
    }  
    
    checkState1(LEDonoff1);
    checkState2(LEDonoff2);
    digitalWrite(LED_1, LEDonoff1);
    digitalWrite(LED_2, LEDonoff2);    
}

void reconnect() {
  uint32_t currentMS = millis();                              // Определяем переменную для функции времени millis()
    String clientId = "ESP8266-" + WiFi.macAddress();    

    if ( currentMS - delayMSBlynk >= 30000 ) {                // Усанавливаем таймер
       delayMSBlynk = currentMS;                              // Сбрасываем таймер
         
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("connected");
      docSend["Blynk"] = true;    
      
      client.publish(relay_topic_state.c_str(), String(LEDonoff1).c_str(), LEDonoff1);
      client.publish(relay_topic.c_str(), String(LEDonoff1).c_str(), LEDonoff1);              
      client.publish(relay2_topic_state.c_str(), String(LEDonoff2).c_str(), LEDonoff2);
      client.publish(relay2_topic.c_str(), String(LEDonoff2).c_str(), LEDonoff2);

      client.subscribe( (relay_topic + "/#").c_str() );
      client.subscribe( (relay2_topic + "/#").c_str() );

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      docSend["Blynk"] = false;
      delay(5000);
    }  
   }
}
