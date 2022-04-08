#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <locale>
#include <string>
#include <codecvt>
#include <iostream>

// 定义帧缓冲回调函数
void framebuffer_size_callback(GLFWwindow* window, GLint width, GLint height);
// 按键回调函数
void input_key_callback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods);
// 文本输入回调函数
void input_char_callback(GLFWwindow* window, GLuint codepoint);
// unicode转utf-8
// https://blog.csdn.net/hongxingabc/article/details/82846396
std::string unicode_to_uft8(GLuint codepoint);

// 设置是否进入文字输入模式
GLboolean isCharInput = false;

int main() {
    // glfw的实例化与配置
    glfwInit();
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

    // 设置窗口宽高
    const GLuint SCR_WIDTH  = 800;
    const GLuint SCR_HEIGHT = 600;
    // 创建glfw窗口
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        // 销毁释放glfw使用的资源
        glfwTerminate();
        return -1;
    }
    // 设置glfw使用的上下文为创建的窗口
    glfwMakeContextCurrent(window);
    // 绑定窗口的帧缓冲回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // 设置按键回调函数
    glfwSetKeyCallback(window, input_key_callback);
    // 设置窗口不透明度
    // glfwSetWindowOpacity(window, 0.5f);

    // 使用加载OpenGL的函数
    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        // 销毁释放glfw使用的资源
        glfwTerminate();
        return -1;
    }

    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 渲染
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 交换窗口的双缓冲
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        // 轮询监听事件
        glfwPollEvents();
    }

    // 销毁释放glfw使用的资源
    glfwTerminate();
    return 0;
}

// 帧缓冲回调函数
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, GLint width, GLint height) {
    // 当窗口大小改变时修改OpenGL的视口大小与窗口一致
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// 按键回调函数
void input_key_callback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods) {
    // escap按键触发事件
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action) {
        // 如果处于文本输入模式
        if (isCharInput) {
            // escap按键表示退出文本输入模式
            glfwSetCharCallback(window, nullptr);
            isCharInput = false;
        } else {
            // 如果不处于文本输入模式，escap按键表示退出程序
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        return;
    }
    // 绑定按键输入回调函数，绑定tab按键，即按tab开始文字输入
    // 只有不处于文本输入模式时才触发
    if (!isCharInput && GLFW_KEY_TAB == key && GLFW_PRESS == action) {
        isCharInput = true;
        glfwSetCharCallback(window, input_char_callback);
        return;
    }
}

// 文本输入回调函数
void input_char_callback(GLFWwindow* window, GLuint codepoint) {
    // glfw输入时捕获的是unicode码，将输入的unicode码转为utf-8字符
    std::cout << unicode_to_uft8(codepoint) << std::endl;
}

// unicode转utf-8
std::string unicode_to_uft8(GLuint codepoint) {
    // 创建对象来操作转换
    // 需频繁调用，就会频繁创建对象
    // 考虑使用懒汉单例？考虑多线程懒汉单例？
#ifdef _MSC_VER
    // GBK在windows下的locale name
    // GBK在linux下的locale名可能是"zh_CN.GBK"
    const char* GBK_LOCALE_NAME = ".936";
    // 转换对象
    std::wstring_convert<std::codecvt_byname<wchar_t, char, std::mbstate_t>>* converterX = new std::wstring_convert<std::codecvt_byname<wchar_t, char, std::mbstate_t>>(new std::codecvt_byname<wchar_t, char, std::mbstate_t>(GBK_LOCALE_NAME));
#else
    // 转换对象
    std::wstring_convert<std::codecvt_utf8<wchar_t>>* converterX = new std::wstring_convert<std::codecvt_utf8<wchar_t>>();
#endif
    // 转utf-8
    std::string result = converterX->to_bytes(codepoint);
    // 释放对象
    delete converterX;
    converterX = nullptr;
    // 返回
    return result;
}