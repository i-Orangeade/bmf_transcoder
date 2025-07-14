cmake_minimum_required(VERSION 3.10)
project(bmf_transcoder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BMF_TRANSCODER ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FFMPEG REQUIRED 
    libavcodec 
    libavformat 
    libavutil 
    libswscale 
    libswresample
)

# 查找fmt库
pkg_check_modules(FMT REQUIRED fmt)
include_directories(${FMT_INCLUDE_DIRS})

# 配置BMF路径
if(DEFINED ENV{BMF_ROOT_PATH})
    set(BMF_ROOT_PATH $ENV{BMF_ROOT_PATH})
else()
    set(BMF_ROOT_PATH "/home/orangeade/BMF/build/output/bmf")
endif()

# 验证BMF路径有效性
if(NOT EXISTS "${BMF_ROOT_PATH}/include/builder.hpp" OR NOT EXISTS "${BMF_ROOT_PATH}/lib")
    message(FATAL_ERROR "BMF路径无效！请检查BMF_ROOT_PATH: ${BMF_ROOT_PATH}")
endif()

# 添加源文件
set(SOURCES
    src/main.cpp
    src/transcoder.cpp
)

# 添加头文件目录
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${BMF_ROOT_PATH}/include
    ${FFMPEG_INCLUDE_DIRS}
)

# 添加库文件目录
link_directories(
    ${BMF_ROOT_PATH}/lib
    ${FFMPEG_LIBRARY_DIRS}
)

# 创建可执行文件
add_executable(bmf_transcoder ${SOURCES})

# 链接依赖库
target_link_libraries(bmf_transcoder
    PRIVATE
    bmf_module_sdk
    engine
    hmp
    ${FMT_LIBRARIES}
    avformat
    avcodec
    avutil
    swscale
    swresample
)