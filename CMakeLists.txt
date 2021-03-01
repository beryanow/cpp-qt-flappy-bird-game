cmake_minimum_required(VERSION 3.10)
project(flappy_bird)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/Users/beryanow/Qt/5.15.2/clang_64/lib/cmake")

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5MultiMedia REQUIRED)
#find_package(Qt5MediaPlayer REQUIRED)

add_executable(flappy_bird Floor.cpp Floor.h Main.cpp GameWindow.cpp GameWindow.h Pipe.cpp Pipe.h Resources.qrc Bird.cpp Bird.h Digit.cpp Digit.h)

target_link_libraries(flappy_bird Qt5::Core)
target_link_libraries(flappy_bird Qt5::Widgets)
target_link_libraries(flappy_bird Qt5::Quick)