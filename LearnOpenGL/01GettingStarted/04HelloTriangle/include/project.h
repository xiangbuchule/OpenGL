#ifndef __POJECT_H__
#define __POJECT_H__

#include "glad/glad.h"

#include "GLFW/glfw3.h"

// 绘制三角形
void drawTriangle(GLFWwindow* window);

// 绘制四边形
void drawQuadrangle(GLFWwindow* window);

// 添加更多顶点到数据中，使用glDrawArrays，尝试绘制两个彼此相连的三角形
void drawTowDifferentTriangles(GLFWwindow* window);

// 创建相同的两个三角形，但对它们的数据使用不同的VAO和VBO
void drawTowTriangles(GLFWwindow* window);

// 创建两个着色器程序，第二个程序使用一个不同的片段着色器，输出黄色；再次绘制这两个三角形，让其中一个输出为黄色
void towShader(GLFWwindow* window);

#endif
