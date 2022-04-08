# cmake需要的最低版本
cmake_minimum_required (VERSION 3.12)
# 项目名
project(04HelloTriangle)

# =====================================
# ========== 设置程序生成路径 =========
# =====================================
if(MSVC)
    set(TARGET_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")
else()
    set(TARGET_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
endif()
set(EXECUTABLE_OUTPUT_PATH "${TARGET_PATH}")
if (MSVC)
    set(TARGET_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
endif()

# =====================================
# =========== 使用的模块库 ============
# =====================================
# 设置glad库
set(GLAD glad)
# 设置glfw库
set(GLFW glfw)
# 设置spdlog库
set(SPDLOG spdlog)
# 设置json库
set(JSON json)
# 设置glm库
set(GLM glm)
# 设置stb库
set(STB stb)
# 设置assimp库
set(ASSIMP assimp)

# =====================================
# ============ 设置源文件 =============
# =====================================
# 设置源文件（.c/.cpp文件）的位置
set(SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")
# 添加源文件
file(GLOB_RECURSE SOURCE_FILE ${SOURCE_PATH}/*.cpp)

# =====================================
# ========== 设置库文件位置 ===========
# =====================================
# 设置需要连接的库的路径
if(BUILD_SHARED_LIBS)
    set(THIRD_PARTY_LIBRARY_PATH "${THIRD_PARTY_PATH}/bin/shared")
else()
    set(THIRD_PARTY_LIBRARY_PATH "${THIRD_PARTY_PATH}/bin/static")
endif()
set(THIRD_PARTY_LIBRARY_PATH "${THIRD_PARTY_LIBRARY_PATH}/${CMAKE_BUILD_TYPE}")
link_directories(
    ${THIRD_PARTY_LIBRARY_PATH}
)

# =====================================
# =========== 生成可执行文件 ==========
# =====================================
# 创建的可执行文件
add_executable(${PROJECT_NAME} ${SOURCE_FILE})
# 添加构建依赖，使得在构建改项目时先构建其他依赖项目
add_dependencies(${PROJECT_NAME} ${GLAD} ${GLFW} ${SPDLOG} ${ASSIMP})

# =====================================
# ============ 设置头文件 =============
# =====================================
# 设置include文件（.h文件）的位置
set(TARGET_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(GLAD_INCLUDE_PATH "${THIRD_PARTY_PATH}/${GLAD}/include")
set(GLFW_INCLUDE_PATH "${THIRD_PARTY_PATH}/${GLFW}/include")
set(SPDLOG_INCLUDE_PATH "${THIRD_PARTY_PATH}/${SPDLOG}/include")
set(JSON_INCLUDE_PATH "${THIRD_PARTY_PATH}/${JSON}/single_include")
set(GLM_INCLUDE_PATH "${THIRD_PARTY_PATH}/${GLM}")
set(STB_INCLUDE_PATH "${THIRD_PARTY_PATH}/${STB}")
set(ASSIMP_INCLUDE_PATH "${THIRD_PARTY_PATH}/${ASSIMP}/include")
# 包含头文件路径
target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${TARGET_INCLUDE_PATH}
    ${GLAD_INCLUDE_PATH}
    ${GLFW_INCLUDE_PATH}
    ${SPDLOG_INCLUDE_PATH}
    ${JSON_INCLUDE_PATH}
    ${GLM_INCLUDE_PATH}
    ${STB_INCLUDE_PATH}
    ${ASSIMP_INCLUDE_PATH}
)

# =====================================
# =========== 添加编译宏参数 ==========
# =====================================
if(BUILD_SHARED_LIBS AND (MSVC OR (WIN32 AND CMAKE_C_COMPILER_ID STREQUAL "Clang")))
    # 添加宏，设置调用使用glad的动态库函数时使用__declspec(dllimport)
    # 因为glad的库动态库函数使用__declspec(dllexport)来导出生成dll对应的.lib文件
    # 所以调用其函数时需使用对应的__declspec(dllimport)
    # 使用MSVC和win下的MSVC编译的Clang都会出现该问题
    # MSVC编译的Clang在win下类似MSVC套壳
    target_compile_definitions(
        ${PROJECT_NAME}
        PRIVATE GLAD_GLAPI_EXPORT
    )
endif()

# =====================================
# ============== 连接库 ===============
# =====================================
target_link_libraries(${PROJECT_NAME} ${GLAD} ${GLFW} ${SPDLOG} ${ASSIMP})
if((NOT BUILD_SHARED_LIBS) AND UNIX)
    target_link_libraries(${PROJECT_NAME} dl pthread)
endif()

# =====================================
# ==== 复制库文件到可执行文件路径 =====
# =====================================
# 如果glad、glfw是生成的动态库复制动态库到执行路径
if(BUILD_SHARED_LIBS)
    # 添加拷贝库文件命令
    add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${GLFW}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${GLAD}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${SPDLOG}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${ASSIMP}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()
# 复制其他文件
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${TARGET_PATH}/config"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/config" "${TARGET_PATH}/config"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${TARGET_PATH}/shader"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/shader" "${TARGET_PATH}/shader"
)

# =====================================
# ========== 安装生成的程序 ===========
# =====================================
# 设置安装的目录
set(INSTALL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/Install/${CMAKE_BUILD_TYPE}")
# 安装生成的程序
if(BUILD_SHARED_LIBS)
    install(
        TARGETS ${PROJECT_NAME} ${GLAD} ${GLFW} ${SPDLOG} ${ASSIMP}
        RUNTIME DESTINATION ${INSTALL_PATH}
        LIBRARY DESTINATION ${INSTALL_PATH}
    )
else()
    install(
        TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${INSTALL_PATH}
    )
endif()
# 安装其他文件
install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/shader" "${CMAKE_CURRENT_SOURCE_DIR}/config"
    DESTINATION ${INSTALL_PATH}
)