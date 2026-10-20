cmake_minimum_required(VERSION 3.10)
project(DynamicArray)

# Требуем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указываем компилятору, где лежат заголовочные файлы
include_directories(include)

# Собираем исполняемый файл main из наших исходников
add_executable(main src/main.cpp src/DynamicArray.cpp)