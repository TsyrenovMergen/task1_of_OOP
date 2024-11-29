# task1_of_OOP
в терминале в папке googletest1
установка googletest:
git clone https://github.com/google/googletest.git -b v1.15.2
cd googletest
mkdir build
cd build
cmake ..
для *nix систем:
make
sudo make install
cd ..
cd ..
запуск самого cmake:
cmake -S. -Bbuild
cmake --build build

запуск main:
./build/BA_main

запуск гугл тестов:
./build/tests/BA_test

папка lib - там лижит библиотека с классом BitArray

папка tests - там лежат тесты

main.cpp - само приложение
