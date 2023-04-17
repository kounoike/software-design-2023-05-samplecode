cmake_minimum_required(VERSION 3.23)
project(opencv-demo LANGUAGES CXX)

set(CMAKE_TOOLCHAIN_FILE $EMSDK/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake)
set(ENBALE_PIC FALSE)
set(BUILD_SHARED_LIBS OFF)
set(BUILD_ZLIB ON)
set(WITH_ITT OFF)
set(WITH_IPP OFF)
set(BUILD_LIST core,imgproc)
set(CPU_BASELINE '')
set(CPU_DISPATCH '')
set(CV_ENABLE_INTRINSICS ON)
set(CMAKE_CXX_FLAGS "-s USE_PTHREADS=0 -msimd128")
include(FetchContent)
FetchContent_Declare(
  opencv
  GIT_REPOSITORY https://github.com/opencv/opencv.git
  GIT_TAG 4.7.0
)
FetchContent_MakeAvailable(opencv)

add_executable(opencv-demo src/main.cpp)
target_link_options(opencv-demo PRIVATE
  "SHELL:-s MODULARIZE=1" "SHELL:-s EXPORT_NAME=createModule" "SHELL:--bind"
)
target_include_directories(opencv-demo PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR} ${opencv_SOURCE_DIR}/include
  ${OPENCV_MODULE_opencv_core_LOCATION}/include ${OPENCV_MODULE_opencv_imgproc_LOCATION}/include
)
target_link_libraries(opencv-demo opencv_core opencv_imgproc)
set_property(TARGET opencv-demo PROPERTY SUFFIX .js)
