## Установка и запуск

### Требования
- Компилятор C++ с поддержкой C++11 и выше
- `make` для сборки проекта (опционально)

### Сборка
1. Создайте директорию сборки и выполните сборку:

   ```bash

   /simpleChat$ mkdir build
   /simpleChat$ cd build
   simpleChat/build$ cmake ..
   simpleChat/build$ cmake --build .
   ```
2. Запустите сервер:
   ```bash
   simpleChat/build$ SIMPLE_CHAT
   ```
3. Запустите клиентов:
   ```bash
   simpleChat/build$ SIMPLE_CLIENT
   ```
