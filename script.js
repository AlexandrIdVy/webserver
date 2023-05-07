let socket;                                       // Определяем переменную для объекта WebSocket
let getObject;                                    // Определяем переменную для запроса данных с сервера
let req;                                          // Определяем переменную для хранения и передачи объекта
let blynk = false;                                // Флаг для проверки соединения с сервером Blynk
const btn1 = document.querySelector('.btn1');              // Ищем в html класс кнопки и записываем в переменную 
const btn2 = document.querySelector('.btn2');

let led1 = btn1.querySelector('.text-btn');               // Ищем в html класс текста внутри кнопки и записываем в переменную
let led2 = btn2.querySelector('.text-btn');

const temp = document.querySelector('.temp');             
const hum = document.querySelector('.hum');
const con = document.querySelector('.blynk-connect');

function initWebSocket() {
  socket = new WebSocket('ws://' + window.location.hostname + ':88/');      // Создаем объект
  socket.onmessage = (evt) => getMessage(evt);                              // Получаем данные и отправляем их в функцию getMessage
}

// Функция для парсинга данных
function getMessage(evt) {

  let obj = JSON.parse(evt.data);      // Создали объект и записали в него полученный JSON                            

// Проверяем какое состояние у светодиода 1
  if (obj.LEDone.State) {
    led1.textContent = 'Led 1 ON';        // Меняем текст кнопки
    btn1.setAttribute('name', 'ON');      // Меняем атрибут кнопки
  }
  else {
    led1.textContent = 'Led 1 OFF';
    btn1.setAttribute('name', 'OFF');
  }
// Проверяем какое состояние у светодиода 2
  if (obj.LEDtwo.State) {
    led2.textContent = 'Led 2 ON';
    btn2.setAttribute('name', 'ON');
  }
  else {
    led2.textContent = 'Led 2 OFF';
    btn2.setAttribute('name', 'OFF');
  }
// Проверяем какое состояние связи с сервером Blynk
// Если связь с сервером Blynk восстанавилась, 
// отправляем запрос на ESP для обновления виджетов в интефейсе блинк
  if (obj.Blynk) {
    if(blynk) {
      req = {
        Devnum: 3,           
      }      
      socket.send(JSON.stringify(req));
      blynk = false;
      req = {
        Devnum: 0 
      }  
    }    
  }
  else {
    blynk = true;
  }

  con.textContent = obj.Blynk;                    // Записываем в блок BLYNK сосотояние Connect
  temp.textContent = obj.Meteo.Temperature;       // Записываем температуру
  hum.textContent = obj.Meteo.Humidity;           // Записываем влажность  
}

// --- Функция отправки состояния кнопки на ESP8266
function sendValueBtn(btn, devnum, led) {
    
    if (btn.name === 'OFF')
    {
      req = {
        Devnum: devnum,
        [led]: {
          State: true 
        }        
      }
      btn.name = 'ON';
      socket.send(JSON.stringify(req));
      console.log("true"); 
      console.log(req);        
    }
    else {
      req = {
        Devnum: devnum,
        [led]: {
         State: false 
        }       
      }
      btn.name = 'OFF';
      socket.send(JSON.stringify(req)); 
      console.log("false"); 
      console.log(req);       
    }
    
    req = {
      Devnum: 0 
    }     
} 

function startInterval() {
  req = {
    Devnum: 0 
  }  
  getObject = setInterval(() => socket.send(JSON.stringify(req)), 2000); 
}

function stopInterval() {
  clearInterval(getObject);
}

function checkDocumnetVisibility() {
  if (document.hidden) {
    stopInterval();    
  }
  else {
    startInterval();   
  }
}

document.addEventListener('visibilitychange', () => setTimeout(() => checkDocumnetVisibility(), 250));
window.addEventListener('DOMContentLoaded', () => {
  initWebSocket();
  startInterval();  
});
btn1.addEventListener('click', () => sendValueBtn(btn1, 1, 'LEDone'));
btn2.addEventListener('click', () => sendValueBtn(btn2, 2, 'LEDtwo'));


