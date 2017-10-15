Стэковый калькулятор.

Установка:

    git clone https://github.com/dkutre/calucator.git

Сборка:

    mkdir build
    cd build
    cmake ..
    make

Для тестов

    cmake .. -DTESTS=ON
    make

Запуск:

    ./bin/Debug/parser

Используется:

    Catch
