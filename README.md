Сгенерировать мейк-файлы: 
  cmake -B./build -S.
Скомпелировать все проекты:
  cmake --build build
Запуск тестов:
  cd build && ctest
Запуск расчёта числа пи (из директории build):
  ./MeowPi/MeowPi
