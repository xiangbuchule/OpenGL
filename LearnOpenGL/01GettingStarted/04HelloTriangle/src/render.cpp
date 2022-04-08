#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include "render.h"
#include "shader.h"

// 渲染第一个三角形
void renderTriangle(GLFWwindow* window, GLuint VAO, Shader* shader) {
    // 渲染背景
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    /**
     * 由于我们前边解绑了顶点数组对象，
     * 这里渲染时需要用到其中的顶点数据
     * 所以我们再绑定一次
     */
    glBindVertexArray(VAO);
    // 使用我们编译配置好的着色器程序
    (*shader).use();
    // 渲染三角形
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // 交换窗口的双缓冲
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    // 每渲染一次轮询监听事件
    glfwPollEvents();
}
// 使用顶点索引数组渲染四边形
void renderQuadrangle(GLFWwindow* window, GLuint VAO, Shader* shader) {
    // 渲染背景
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    /**
     * 由于我们前边解绑了顶点数组对象，
     * 这里渲染时需要用到其中的顶点数据
     * 所以我们再绑定一次
     */
    glBindVertexArray(VAO);
    // 使用我们编译配置好的着色器程序
    (*shader).use();
    // 渲染四角形
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // 交换窗口的双缓冲
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    // 轮询监听事件
    glfwPollEvents();
}
// 使用更多顶点来渲染四边形
void renderQuadrangleByMoreVertex(GLFWwindow* window, GLuint VAO, Shader* shader) {
    // 渲染背景
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    /**
     * 由于我们前边解绑了顶点数组对象，
     * 这里渲染时需要用到其中的顶点数据
     * 所以我们再绑定一次
     */
    glBindVertexArray(VAO);
    // 使用我们编译配置好的着色器程序
    (*shader).use();
    // 渲染三角形
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // 交换窗口的双缓冲
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    // 轮询监听事件
    glfwPollEvents();
}
// 创建相同的两个三角形，但对它们的数据使用不同的VAO和VBO
void renderTowTriangles(GLFWwindow* window, GLuint VAO[2], Shader* shader) {
    // 渲染背景
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 使用我们编译配置好的着色器程序
    (*shader).use();

    /**
     * 由于我们前边解绑了顶点数组对象，
     * 这里渲染时需要用到其中的顶点数据
     * 所以我们再绑定一次
     */
    glBindVertexArray(VAO[0]);
    // 渲染三角形
    glDrawArrays(GL_TRIANGLES, 0, 3);

    /**
     * 由于我们前边解绑了顶点数组对象，
     * 这里渲染时需要用到其中的顶点数据
     * 所以我们再绑定一次
     */
    glBindVertexArray(VAO[1]);
    // 渲染三角形
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // 交换窗口的双缓冲
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    // 轮询监听事件
    glfwPollEvents();
}
// 创建两个着色器程序，第二个程序使用一个不同的片段着色器，输出黄色；再次绘制这两个三角形，让其中一个输出为黄色
void renderTowTrianglesByTowShader(GLFWwindow* window, GLuint VAO[2], Shader* shader[2]) {
    // 渲染背景
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 使用我们编译配置好的着色器程序
    shader[0]->use();

    /**
     * 由于我们前边解绑了顶点数组对象，
     * 这里渲染时需要用到其中的顶点数据
     * 所以我们再绑定一次
     */
    glBindVertexArray(VAO[0]);
    // 渲染三角形
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // 使用我们编译配置好的着色器程序
    shader[1]->use();
    /**
     * 由于我们前边解绑了顶点数组对象，
     * 这里渲染时需要用到其中的顶点数据
     * 所以我们再绑定一次
     */
    glBindVertexArray(VAO[1]);
    // 渲染三角形
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // 交换窗口的双缓冲
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    // 轮询监听事件
    glfwPollEvents();
}
