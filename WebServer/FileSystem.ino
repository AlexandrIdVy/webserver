// --- Функция, возвращающая необходимый заголовок типа содержимого в зависимости от расширения файла ---

String getContentType(String filename){                                 
  if (filename.endsWith(".html")) return "text/html";                   // Если файл заканчивается на ".html", то возвращаем заголовок "text/html" и завершаем выполнение функции
  else if (filename.endsWith(".css")) return "text/css";                // Если файл заканчивается на ".css", то возвращаем заголовок "text/css" и завершаем выполнение функции
  else if (filename.endsWith(".js")) return "application/javascript";   // Если файл заканчивается на ".js", то возвращаем заголовок "application/javascript" и завершаем выполнение функции
  //else if (filename.endsWith(".png")) return "image/png";               // Если файл заканчивается на ".png", то возвращаем заголовок "image/png" и завершаем выполнение функции  
  //else if (filename.endsWith(".gif")) return "image/gif";               // Если файл заканчивается на ".gif", то возвращаем заголовок "image/gif" и завершаем выполнение функции 
  return "text/plain";                                                  // Если ни один из типов файла не совпал, то считаем что содержимое файла текстовое, отдаем соответствующий заголовок и завершаем выполнение функции
}

// --- Функция работы с файловой системой ---

bool handleFileRead(String path){                                       
  if(path.endsWith("/")) path += "index.html";                          // Если устройство вызывается по корневому адресу, то должен вызываться файл index.html (добавляем его в конец адреса)
  String contentType = getContentType(path);                            // С помощью функции getContentType (описана ниже) определяем по типу файла (в адресе обращения) какой заголовок необходимо возвращать по его вызову
  if(LittleFS.exists(path)){                                              // Если в файловой системе существует файл по адресу обращения
    File file = LittleFS.open(path, "r");                                 // Открываем файл для чтения
    size_t sent = server.streamFile(file, contentType);                 // Выводим содержимое файла по HTTP, указывая заголовок типа содержимого contentType
    file.close();                                                       // Закрываем файл
    return true;                                                        // Завершаем выполнение функции, возвращая результатом ее исполнения true (истина)
  }
  return false;                                                         // Завершаем выполнение функции, возвращая результатом ее исполнения false (если не обработалось предыдущее условие)
}

// --- Функция обработки index.html ---

void handleHTML(){
  handleFileRead("/index.html");                                        // Ищем файл в файловой системе
}

// --- Функция обработки css.css ---

void handleCSS(){
  handleFileRead("/index.css");                                          // Ищем файл в файловой системе
}

// --- Функция обработки script.js ---

void handleJS(){
  handleFileRead("/index.js");                                          // Ищем файл в файловой системе
}

void handleConstantsJS(){
  handleFileRead("/constants.js");                                          // Ищем файл в файловой системе
}
void handleSectionJS(){
  handleFileRead("/Section.js");                                          // Ищем файл в файловой системе
}
void handleDeviceJS(){
  handleFileRead("/Device.js");                                          // Ищем файл в файловой системе
}
void handleRequestJS(){
  handleFileRead("/Request.js");                                          // Ищем файл в файловой системе
}
void handleSoundPNG(){
  handleFileRead("/sound.png");                                          // Ищем файл в файловой системе
}
void handleTvPNG(){
  handleFileRead("/tv.png");                                          // Ищем файл в файловой системе
}
