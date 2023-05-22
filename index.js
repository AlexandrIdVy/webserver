import { devices, url } from './constants.js';
import Section from './Section.js';
import Device from './Device.js';
import Request from './Request.js';
import DeviceUpdate from './DeviceUpdate.js';

// создаем экземпляр класса для добавления устройств в указанную секцию
const devicesList = new Section({
  renderer: item => devicesList.addItem(createDevice(item))
}, devices);

const devicesUpdate = new Section({
  renderer: item => updateDevice(item)
}, devices);

// создаем экземпляр класса для подключения websocket
const request = new Request(url);

request.connect()
  .then(resolve => {
    resolve.send(JSON.stringify({ id: 0 }));
    resolve.onmessage = (evt) => {
      devicesList.render(JSON.parse(evt.data));
      devicesUpdate.update(JSON.parse(evt.data));
    }
    //request.startInterval();
  })
  .catch(err => console.log(err));


// создаем виджет устройства
function createDevice(device) {
  const widget = new Device('#device-template', device, request);

  return widget.generateDevice();
}

function updateDevice(device) {
  const widget = new DeviceUpdate(device);

  return widget.update();
}


// Функция для парсинга данных
function getMessage(evt) {

  let obj = JSON.parse(evt.data);      // Создали объект и записали в него полученный JSON
  console.log(obj);
// Проверяем какое состояние у светодиода 1
  /* if (obj.LEDone.State) {
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
      //socket.send(JSON.stringify(req));
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
  hum.textContent = obj.Meteo.Humidity;           // Записываем влажность */
}

// --- Функция отправки состояния кнопки на ESP8266
/* function sendValueBtn(btn, devnum, led) {

    if (btn.name === 'OFF')
    {
      req = {
        Devnum: devnum,
        [led]: {
          State: true
        }
      }
      btn.name = 'ON';
      //socket.send(JSON.stringify(req));
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
      //socket.send(JSON.stringify(req));
      console.log("false");
      console.log(req);
    }

    req = {
      Devnum: 0
    }
} */





/* window.addEventListener('DOMContentLoaded', () => {
  socket.onmessage = (evt) => getMessage(evt);                              // Получаем данные и отправляем их в функцию getMessage
  startInterval();
}); */
/* btn1.addEventListener('click', () => sendValueBtn(btn1, 1, 'LEDone'));
btn2.addEventListener('click', () => sendValueBtn(btn2, 2, 'LEDtwo')); */


