project(vezdecode30)
cmake_minimum_required(VERSION 3.16)

set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)

add_executable(vezde30 main.cpp)
target_link_libraries(vezde30 ${CURL_LIBRARIES})