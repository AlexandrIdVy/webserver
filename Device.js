//класс для добавления виджетов устройств
export default class Device {
  constructor(deviceSelector, device, wsConnect) {
    this._id = device.id;
    this._type = device.type;
    this._state = device.state;
    this._location = device.location;
    this._on = device.on;
    this._image = device.image;
    this._name = device.name;
    this._deviceSelector = deviceSelector;
    this._wsConnect = wsConnect;
  }

  // получаем шаблон виджета устройства
  _getTemplate() {
    const deviceElement = document.querySelector(this._deviceSelector).content;

    return deviceElement;
  }

  // устанавливаем слушателей
  _setEventListener() {
    this._imageSwitch = this._element.querySelector('.device__img');
    this._imageSwitch.addEventListener('click', () => this._handleSwitchClick());
  }

  // меняем состояние выключателя
  _handleSwitchClick() {
    this._switch.checked = !this._switch.checked;
    this._sendJsonState(this._switch.checked);
  }

  // устанавливаем текущее состояние выключателя
  _addStateSwitch() {
    this._switch.checked = this._on;
  }

  // устанавливаем состояние устройства
  _addStateClass() {
    if (this._state) {
      this._element.classList.add('state_online');
      this._stateSelector.textContent = 'Online';
    }
    else {
      this._element.classList.add('state_offline');
      this._stateSelector.textContent = 'Offline';
    }
  }

  // отправляем json на сервер
  _sendJsonState(checked) {
    if (checked) {
      this._wsConnect.sendMessage(this._id, checked);
      console.log('on');
    }
    else {
      this._wsConnect.sendMessage(this._id, checked);
      console.log('off');
    }

  }

  // создаем виджет устроства
  generateDevice() {
    this._element = this._getTemplate().querySelector('.device').cloneNode(true);
    this._setEventListener();
    this._stateSelector = this._element.querySelector('.device__state');
    this._addStateClass();
    this._element.querySelector('.device__location').textContent = this._location;
    this._switch = this._element.querySelector('.device__input_type_switch');
    this._switch.id = this._id;
    this._addStateSwitch();
    this._imageSwitch.src = '/' + this._image + '.png';
    this._element.querySelector('.device__name').textContent = this._name;

    return this._element;
  }

}
