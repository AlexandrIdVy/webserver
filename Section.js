export default class Section {

  constructor({renderer}, containerSelector) {
    this._renderer = renderer;
    this._container = document.querySelector(containerSelector);
    this._rendered = false;
  }
  //отрисовываем элементы
  render(items) {
    if (!this._rendered) {
      items.forEach((item, index, arr) => {
        if(index === arr.length-1) {
          this._rendered = true;
        }
        this._renderer(item);
      });
    }
  }
  // обновляем элементы
  update(items) {
    items.forEach(item => this._renderer(item));
  }
  //принимаем DOM-элемент и добавляем его в конец контейнера
  addItem(element) {
    this._container.append(element);
  }
}
