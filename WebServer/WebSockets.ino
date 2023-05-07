// --- Функциия проверки событий websocket --- 
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){    // (номер клиента, тип события, массив данных, длина массива)
  switch (type) {                                                                     // Проверяем тип события
    case WStype_TEXT: {                                                               // Если пришел текст
      DeserializationError error = deserializeJson(docGet, payload);                 // Разбираем JSON
      int DeviceNumber = 0;                                                           // Определяем переменную для записи номера устройства из JSON  
      if (error) {                                                                    // Проверяем, если удалось разобрать JSON
        DeviceNumber;
        break;
      } else {  
       DeviceNumber = docGet["Devnum"];                                                // Записываем номера устройства из JSON       
      switch (DeviceNumber) {                                                         // Проверяем номер устройства
        case 1: {                    
          bool LED1 = docGet["LEDone"]["State"];                                     // Обновляем состояние светодиода 1
          checkState1(LED1);          
          digitalWrite(LED_1, LEDonoff1);
          client.publish(relay_topic_state.c_str(), String(LEDonoff1).c_str(), LEDonoff1);
          }
        break;             
        case 2: {                                                                     // Обновляем состояние светодиода 2
          bool LED2 = docGet["LEDtwo"]["State"];
          checkState2(LED2);          
          digitalWrite(LED_2, LEDonoff2);
          client.publish(relay2_topic_state.c_str(), String(LEDonoff2).c_str(), LEDonoff2);
          }
        break;                      
        default:
        break;
      }          
     }    
           JSONtxt="";                                                                 // Очищаем переменную JSONtxt от предыдущих значений
          serializeJson(docSend, JSONtxt);                                             // Записываем JSON объект в переменную JSONtxt
      webSocket.broadcastTXT(JSONtxt);                                                // Передаем значение переменной JSONtxt в index.html               
    }
    break;
    default:
    break;
  }
}
