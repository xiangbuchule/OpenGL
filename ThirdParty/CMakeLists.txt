# cmake需要的最低版本
cmake_minimum_required (VERSION 3.12)
# 项目名
project(ThirdParty)

# =====================================
# ========== 设置库生成位置 ===========
# =====================================
if(BUILD_SHARED_LIBS)
    set(THIRD_PARTY_TARGET_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin/shared)
else()
    set(THIRD_PARTY_TARGET_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin/static)
endif()
if(NOT MSVC)
    set(THIRD_PARTY_TARGET_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
endif()
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${THIRD_PARTY_TARGET_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${THIRD_PARTY_TARGET_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${THIRD_PARTY_TARGET_PATH})

# =====================================
# =========== 生成第三方库 ============
# =====================================
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glad)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/spdlog)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE STRING "Debug Postfix for lib, samples and tools OFF")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/assimp)
