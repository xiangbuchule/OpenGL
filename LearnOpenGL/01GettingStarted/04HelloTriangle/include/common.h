#ifndef __COMMON_H__
#define __COMMON_H__

#include "glad/glad.h"

#include "GLFW/glfw3.h"

// 退出程序方法
void exitApplication();

/**
 * GLFW相关函数
 */
// 初始化GLFW
void glfw_init();
// 定义帧缓冲大小回调函数
void framebuffer_size_callback(GLFWwindow* window, GLint width, GLint height);
// 定义窗口大小回调函数
void window_size_callback(GLFWwindow* window, GLint width, GLint height);
// 按键回调函数
void input_key_callback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods);
// 文本输入回调函数
void input_char_callback(GLFWwindow* window, GLuint codepoint);

#endif
