export default class DeviceUpdate {
  constructor(device) {
    this._on = device.on;
    this._id = document.getElementById(device.id);
  }

  update() {
    this._id.checked = this._on;
  }
}
