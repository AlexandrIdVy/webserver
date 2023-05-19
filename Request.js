export default class Request {
  constructor(url) {
    this._url = url;
  }

  // коннектимся к websocket
  connect() {
    return new Promise((resolve, reject) => {

      this._socket = new WebSocket(this._url);

        this._socket.onopen = () => {
          console.log('Соединение установлено');
          document.addEventListener('visibilitychange', this._checkDocumnetVisibility);
          this._startInterval();
          resolve(this._socket);
        }

        this._socket.onerror = () => {
          reject('Устанавливаем соединение');
          this.connect(this._url)
            .catch(err => console.log(err));
        }
    });
  }


  // пуск/останов запросов на сервер при открытии/сворачивания вкладки или окна браузера
 _checkDocumnetVisibility = () => {
        setTimeout(() => {
      if (document.hidden) {
        this._stopInterval();
        //clearInterval(this._startTimer);
      }
      else {
        this._startInterval();
      }
    }, 250);
    }

  // отпраляем запросы на сервер
  _startInterval() {
    this._startTimer = setInterval(() => {
      if (this._socket.readyState === 1) {
        this._socket.send(JSON.stringify({ Devnum: 0 }));
        console.log('Отправка данных');
      }
      else {
        console.log('Соединение потеряно');
        this._stopInterval();
        document.removeEventListener('visibilitychange', this._checkDocumnetVisibility);
        this.connect(this._url)
          .catch(err => console.log(err));
      }}, 2000);
  }

  _stopInterval() {
    clearInterval(this._startTimer);
  }
}
