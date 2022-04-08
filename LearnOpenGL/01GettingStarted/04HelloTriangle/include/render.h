/**
 * 渲染函数
 */
#ifndef __RENDER_H__
#define __RENDER_H__

#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include "shader.h"

// 渲染第一个三角形
void renderTriangle(GLFWwindow* window, GLuint VAO, Shader* shader);
// 使用顶点索引数组渲染四边形
void renderQuadrangle(GLFWwindow* window, GLuint VAO, Shader* shader);
// 使用更多顶点来渲染四边形
void renderQuadrangleByMoreVertex(GLFWwindow* window, GLuint VAO, Shader* shader);
// 创建相同的两个三角形，但对它们的数据使用不同的VAO和VBO
void renderTowTriangles(GLFWwindow* window, GLuint VAO[2], Shader* shader);
// 创建相同的两个三角形，两个三角形使用不同的shader
void renderTowTrianglesByTowShader(GLFWwindow* window, GLuint VAO[2], Shader* shader[2]);

#endif