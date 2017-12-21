cmake_minimum_required(VERSION 3.4)

project(mining)

file(GLOB all_src "*.hpp" "*.cpp" "thirdparty/*.cpp" "thirdparty/*.h")
add_executable(miner ${all_src})

set(BOOST_ROOT "/usr/local/boost_1_65_0")

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wno-unused -g")
set(CMAKE_EXE_LINKER_FLAGS "-g")

find_package(SFML 2 REQUIRED graphics window system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(miner ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

target_link_libraries(miner stdc++fs)
target_link_libraries(miner tgui)

install(TARGETS miner DESTINATION /usr/local/bin)