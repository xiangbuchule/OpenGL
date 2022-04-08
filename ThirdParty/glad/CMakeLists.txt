# cmake需要的最低版本
cmake_minimum_required (VERSION 3.12)
# 项目名
project(glad)

# =====================================
# ============= 设置源文件 =============
# =====================================
# 设置源文件（.c/.cpp文件）的位置
set(GLAD_SOURCES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
# 添加源文件
aux_source_directory(${GLAD_SOURCES_PATH} GLAD_SOURCES_FILES)

# =====================================
# ============= 生成库文件 =============
# =====================================
# 生成glad库
if(BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${GLAD_SOURCES_FILES})
else()
    add_library(${PROJECT_NAME} STATIC ${GLAD_SOURCES_FILES})
endif()

# =====================================
# ============= 设置头文件 =============
# =====================================
# 设置include文件（.h文件）的位置
set(GLAD_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
# 包含头文件路径
target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${GLAD_INCLUDE_PATH}
)

# =====================================
# ========== 设置生成目标属性 ==========
# =====================================
if(BUILD_SHARED_LIBS)
    if(MSVC OR (WIN32 AND (CMAKE_C_COMPILER_ID STREQUAL "Clang")))
        # 设置生成动态库时，生成的需要导入lib文件名的后缀
        set_target_properties(${PROJECT_NAME} PROPERTIES IMPORT_SUFFIX ".lib")
        # 添加宏，设置导处dll时也导出对应的lib文件
        # MSVC和win下的MSVC编译的Clang都应该这么设置
        # MSVC编译的Clang在win下类似MSVC套壳
        target_compile_definitions(
            ${PROJECT_NAME}
            PRIVATE GLAD_GLAPI_EXPORT
            PRIVATE GLAD_GLAPI_EXPORT_BUILD
        )
    else()
        set_target_properties(${PROJECT_NAME} PROPERTIES IMPORT_SUFFIX ".a")
    endif()
endif()