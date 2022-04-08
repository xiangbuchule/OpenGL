#include <string>

#include "glad/glad.h"

#include "GLFW/glfw3.h"

/**
 * 设置窗口默认属性
 */
// 窗口标题
std::string windowTitle = "LearnOpenGL";
// 窗口宽高
GLint screenWidth  = 800;
GLint screenHeight = 600;
// 设置是否进入文字输入模式
GLboolean isCharInput = false;
// 设置是否处于线框模式
GLboolean isInLineMode = true;
// 窗口状态(1:最小化、2:正常化、3:最大化、4:全屏化)
GLint windowState = 2;
// 窗口不透明度
GLfloat windowOpacity = 1.0f;
// 窗口不透明度每次变化的大小
GLfloat windowOpacityChange = 0.01f;
// 全屏窗口属性
GLint windowContentXPos      = 0;
GLint windowContentYPos      = 0;
GLint windowResolutionWidth  = 800;
GLint windowResolutionHeight = 600;
GLint windowRefreshRate      = 30;
