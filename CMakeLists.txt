# CMakeList.txt: проект CMake для Deque; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("Engine-Wrapper-for-int")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Engine-Wrapper-for-int "engine.h" "wrapper.h" "main.cpp" )

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
