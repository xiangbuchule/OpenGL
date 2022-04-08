# cmake需要的最低版本
cmake_minimum_required (VERSION 3.12)
# 主项目名
project(Main)

# =====================================
# ============= 设置库类型 =============
# =====================================
if (POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()
# 设置默认构建动态库
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# =====================================
# ========= 设置c/cpp编译选项 ==========
# =====================================
# 设置c编译版本
set(CMAKE_C_STANDARD 11)
# 设置c++编译版本
set(CMAKE_CXX_STANDARD 17)
# 设置c编译器
# set(CMAKE_C_COMPILER "gcc")
# message(${CMAKE_C_COMPILER})
# 设置cpp编译器
# set(CMAKE_CXX_COMPILER "g++")
# message(${CMAKE_CXX_COMPILER})
# 设置c/cpp编译Debug与Release的编译参数
# Clang编译选项与MSVC相似
if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
    # using Clang
    message("-- using Clang compile")
elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    # using GCC
    message("-- using GCC compile")
    set(CMAKE_C_FLAGS_DEBUG "-O0 -g3 -ggdb3")
    set(CMAKE_C_FLAGS_RELEASE "-O3 -Wall")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -ggdb3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall")
elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    # using Visual Studio
    message("-- using MSVC compile")
    set(CMAKE_C_FLAGS_DEBUG "/Od /Zi /MDd")
    set(CMAKE_C_FLAGS_RELEASE "/Ox /Wall /MD")
    set(CMAKE_CXX_FLAGS_DEBUG "/Od /Zi /MDd")
    set(CMAKE_CXX_FLAGS_RELEASE "/Ox /Wall /MD")
endif()

# =====================================
# ========= 设置额外编译选项 ===========
# =====================================
# 设置编码
set(CompileCode UTF-8)
if(MSVC)
    add_compile_options(/source-charset:${CompileCode} /execution-charset:${CompileCode})
endif()
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-finput-charset=${CompileCode} -fexec-charset=${CompileCode} -fwide-exec-charset=${CompileCode})
endif()

# =====================================
# === 设置编译版本是Debug还是Release ===
# =====================================
# 判断命令传入的是否为空，如果为空，默认Debug
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# =====================================
# =========== 生成第三方库 =============
# =====================================
set(THIRD_PARTY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty)
add_subdirectory("${THIRD_PARTY_PATH}")

# =====================================
# ============ 添加子项目 ==============
# =====================================
set(LEARNOPENGL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/LearnOpenGL)
add_subdirectory("${LEARNOPENGL_PATH}")