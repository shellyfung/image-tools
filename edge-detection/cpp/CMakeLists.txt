cmake_minimum_required(VERSION 2.8)

project(edgeDetection)

set(OpenCV_DIR D:/OpenCV410/build/install)


find_package(OpenCV REQUIRED)

file(GLOB hdrs "include/*.h" "include/*.hpp")
file(GLOB srcs "src/*.cpp")
file(GLOB test "test/*.cpp" "test/*.h")


source_group("include" FILES ${hdrs})
source_group("src" FILES ${srcs})
source_group("test" FILES ${test})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${OpenCV_INCLUDE_DIRS}")

add_executable(${PROJECT_NAME} ${hdrs} ${srcs} ${test}) 
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})