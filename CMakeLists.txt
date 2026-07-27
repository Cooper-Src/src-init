cmake_minimum_required(VERSION 3.20)

project(src-init LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL CONFIG REQUIRED)
find_package(cJSON CONFIG REQUIRED)

add_executable(src-init
    src/main.cpp
    src/command.cpp
    src/http_client.cpp
    src/github_provider.cpp
    src/manifest_generator.cpp
    src/manifest_writer.cpp
)

target_include_directories(src-init PRIVATE
    include
)

target_link_libraries(src-init PRIVATE
    CURL::libcurl
    cjson
)