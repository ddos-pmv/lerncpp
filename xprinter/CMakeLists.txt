cmake_minimum_required(VERSION 3.16)
project(xprinter)

set(CMAKE_CXX_STANDARD 17)

# Подключаем необходимые модули Qt
find_package(Qt6 COMPONENTS
        Core
        PrintSupport
        Pdf
        Gui
        Widgets
        Network
        REQUIRED)

# Указываем исходники проекта
add_executable(xprinter
        main.cpp)

# Связываем с библиотеками Qt
target_link_libraries(xprinter
        Qt6::Pdf
        Qt6::PrintSupport
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Network

)
