#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <string>

#include "glad/glad.h"

#include "GLFW/glfw3.h"

/**
 * 设置窗口默认属性
 */
// 窗口标题
extern std::string windowTitle;

// 窗口宽高
extern GLint screenWidth;
extern GLint screenHeight;
// 设置是否进入文字输入模式
extern GLboolean isCharInput;
// 设置是否处于线框模式
extern GLboolean isInLineMode;
// 窗口不透明度
extern GLfloat windowOpacity;
// 窗口不透明度每次变化的大小
extern GLfloat windowOpacityChange;
// 窗口状态(1:最小化、2:正常化、3:最大化、4:全屏化)
extern GLint windowState;
// 全屏窗口属性
extern GLint windowContentXPos;
extern GLint windowContentYPos;
extern GLint windowResolutionWidth;
extern GLint windowResolutionHeight;
extern GLint windowRefreshRate;

/**
 * 窗口显示状态
 */
// 最小化
#define WINDOW_MIN_STATE 1
// 正常化
#define WINDOW_NORMAL_STATE 2
// 最大化
#define WINDOW_MAX_STATE 3
// 全屏化
#define WINDOW_FULL_STATE 4

#endif
