#include <codecvt>
#include <fstream>
#include <locale>
#include <string>

#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include "common.h"
#include "convert.h"
#include "global.h"
#include "log.h"
#include "project.h"

// 退出程序方法
void exitApplication() {
    // 销毁释放glfw使用的资源
    glfwTerminate();
    // 退出
    exit(-1);
}

// 初始化GLFW
void glfw_init() {
    // glfw的实例化与配置
    if (!glfwInit()) {
        logError("couldn't init GLFW");
        logFlush();
        exit(-1);
    }
    // glfw的上下文主版本3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfw的上下文次版本3，和起来3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 设置glfw的OpenGL模式为核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    // 如果是Mac平台，需设置GLFW_OPENGL_FORWARD_COMPAT
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

// 帧缓冲回调函数
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, GLint width, GLint height) {
    // 当窗口大小改变时修改OpenGL的视口大小与窗口一致
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// 定义窗口大小回调函数
void window_size_callback(GLFWwindow* window, GLint width, GLint height) {
    // 当窗口大小改变时修改窗口的内容大小与窗口一致，交换双缓冲
    glfwSwapBuffers(window);
}

// 按键回调函数
void input_key_callback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods) {
    // escap按键触发事件
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action) {
        // 如果处于文本输入模式
        if (isCharInput) {
            // escap按键表示退出文本输入模式
            glfwSetCharCallback(window, nullptr);
            isCharInput = !isCharInput;
        } else {
            // 如果不处于文本输入模式，escap按键表示退出程序
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        return;
    }
    // 绑定按键输入回调函数，绑定tab按键，即按tab开始文字输入
    // 只有不处于文本输入模式时才触发
    if (!isCharInput && GLFW_KEY_TAB == key && (GLFW_PRESS == action)) {
        isCharInput = !isCharInput;
        glfwSetCharCallback(window, input_char_callback);
        return;
    }
    // 绑定~键为线框模式切换
    if (!isCharInput && GLFW_KEY_GRAVE_ACCENT == key && GLFW_PRESS == action) {
        if (isInLineMode) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            isInLineMode = !isInLineMode;
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            isInLineMode = !isInLineMode;
        }
        return;
    }
    // 绑定上键为增加不透明度
    if (!isCharInput && GLFW_KEY_UP == key && (GLFW_PRESS == action || GLFW_REPEAT == action)) {
        windowOpacity += windowOpacityChange;
        if (1.0f < windowOpacity) windowOpacity = 1.0f;
        glfwSetWindowOpacity(window, windowOpacity);
        return;
    }
    // 绑定下键为减少不透明度
    if (!isCharInput && GLFW_KEY_DOWN == key && GLFW_PRESS == action || GLFW_REPEAT == action) {
        windowOpacity -= windowOpacityChange;
        if (windowOpacityChange > windowOpacity) windowOpacity = windowOpacityChange;
        glfwSetWindowOpacity(window, windowOpacity);
        return;
    }
}

// 文本输入回调函数
void input_char_callback(GLFWwindow* window, GLuint codepoint) {
    // glfw输入时捕获的是unicode码，将输入的unicode码转为utf-8字符
    logInfo(unicodeToUTF8(codepoint));
    logFlush();
}
