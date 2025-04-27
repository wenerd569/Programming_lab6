cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_EXE_LINKER_FLAGS "-static")
#[options]
#nlohmann_json/*:shared=False
#magic_enum/*:shared=False



project(ProgLab5)

include_directories(include)

find_package(magic_enum REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED COMPONENTS system asio beast CONFIG)
# 

file(GLOB FRONTEND1 "src/frontend/*/*/*.cpp")
file(GLOB FRONTEND2 "src/frontend/*/*.cpp")
file(GLOB FRONTEND3 "src/frontend/*.cpp")
file(GLOB BACKEND1 "src/backend/*.cpp")
file(GLOB COMMON1 "src/common/*.cpp")

add_executable(${PROJECT_NAME}_back ${BACKEND1} ${COMMON1})
target_compile_features(${PROJECT_NAME}_back PUBLIC cxx_std_20)

target_link_libraries(${PROJECT_NAME}_back PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME}_back PRIVATE Boost::boost Boost::system Boost::thread)


add_executable(${PROJECT_NAME}_front ${FRONTEND1} ${FRONTEND2} ${FRONTEND3} ${COMMON1})
target_compile_features(${PROJECT_NAME}_front PUBLIC cxx_std_20)

target_link_libraries(${PROJECT_NAME}_front PRIVATE magic_enum::magic_enum)
target_link_libraries(${PROJECT_NAME}_front PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME}_front PRIVATE Boost::boost Boost::system Boost::thread)

