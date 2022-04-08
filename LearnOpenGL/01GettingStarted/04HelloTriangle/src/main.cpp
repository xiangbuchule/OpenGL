#include <string>

#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include "common.h"
#include "config.h"
#include "global.h"
#include "log.h"
#include "nlohmann/json.hpp"
#include "project.h"

int main(int argc, char* argv[]) {
    // 初始化glfw
    glfw_init();

    // 读取json配置
    nlohmann::json* json = new nlohmann::json(readConfig("./config/window.json"));
    configWindow(*json);

    // 创建glfw窗口
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, windowTitle.c_str(), nullptr, nullptr);
    if (nullptr == window) {
        logError("Failed to create GLFW window !!!");
        logFlush();
        exitApplication();
    }
    // 设置glfw使用的上下文为创建的窗口
    glfwMakeContextCurrent(window);
    // 加载OpenGL的函数
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        logError("Failed to initialize GLAD !!!");
        logFlush();
        exitApplication();
    }
    // 设置glfw窗口属性
    switch (windowState) {
        case WINDOW_FULL_STATE: {
            glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), windowContentXPos, windowContentYPos, windowResolutionWidth, windowResolutionHeight, windowRefreshRate);
            GLint width, height;
            glfwGetWindowSize(window, &width, &height);
            glViewport(windowContentXPos, windowContentYPos, width, height);
        } break;
        case WINDOW_NORMAL_STATE: {
            GLint width, height;
            glfwGetWindowSize(window, &width, &height);
            glViewport(0, 0, width, height);
        } break;
        case WINDOW_MAX_STATE:
            glfwMaximizeWindow(window);
            {
                GLint width, height;
                glfwGetWindowSize(window, &width, &height);
                glViewport(0, 0, width, height);
            }
            break;
        case WINDOW_MIN_STATE:
            glfwIconifyWindow(window);
            break;
        default:
            break;
    }
    glfwSetWindowOpacity(window, windowOpacity);
    if (isCharInput) glfwSetCharCallback(window, input_char_callback);
    // 设置线框模式
    if (isInLineMode) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 绑定窗口的帧缓冲大小回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // 绑定窗口大小回调
    glfwSetWindowSizeCallback(window, window_size_callback);
    // 设置按键回调函数
    glfwSetKeyCallback(window, input_key_callback);

    // 绘制三角形
    // drawTriangle(window);
    // 绘制四边形
    // drawQuadrangle(window);
    // 添加更多顶点到数据中，使用glDrawArrays，尝试绘制两个彼此相连的三角形
    // drawTowDifferentTriangles(window);
    // 创建相同的两个三角形，但对它们的数据使用不同的VAO和VBO
    // drawTowTriangles(window);
    // 创建两个着色器程序，第二个程序使用一个不同的片段着色器，输出黄色；再次绘制这两个三角形，让其中一个输出为黄色
    towShader(window);

    // 销毁释放glfw使用的资源
    glfwTerminate();
    return 0;
}
