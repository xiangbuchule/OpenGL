#include <string>
#include <vector>

#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include "project.h"
#include "render.h"
#include "shader.h"

// 绘制三角形
void drawTriangle(GLFWwindow* window) {
    // 创建shader
    Shader* shader = new Shader("./shader/triangle.vert", "./shader/triangle.frag");
    (*shader).compileAll();

    // 创建顶点数组对象，用来存储多个顶点缓冲对象
    GLuint VAO;
    /**
     * OpenGL生成顶点数组对象
     * 1、生成的顶点数组对象数量
     * 2、生成的顶点数组对象存储位置
     * 可以这样使用，一次生成4个
     * GLuint VAOS[4];
     * glGenVertexArrays(sizeof(VAOS), VAOS);
     */
    glGenVertexArrays(1, &VAO);
    /**
     * OpenGL绑定VAO顶点数组对象，让后续创建的
     * VBO顶点缓冲对象可以存储到其中
     */
    glBindVertexArray(VAO);

    // 设置三个顶点
    GLfloat vertex[] = {
        -0.5f, -0.5f, 0.0f, // 左(xyz)
        0.5f, -0.5f, 0.0f,  // 右(xyz)
        0.0f, 0.5f, 0.0f    // 上(xyz)
    };
    // 定义顶点缓冲对象VBO
    GLuint VBO;
    /**
     * OpenGL生成缓冲区对象
     * 1、生成的缓冲区对象数量
     * 2、生成的缓冲区存储位置
     * 可以这样使用，一次生成3个
     * GLuint buffers[3];
     * glGenBuffers(sizeof(buffers), buffers);
     */
    glGenBuffers(1, &VBO);
    // 设置该顶点缓冲对象VBO的类型为数组缓冲GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    /**
     * 将定义的顶点数据拷贝到这个顶点缓冲对象VBO中去
     * 1、数据类型：数组缓冲类型
     * 2、数据量大小：顶点数组的大小
     * 3、数据：就是定义的顶点
     * 4、数据类型：由于这是写死的顶点数据，数据不会变
     *   1. GL_STATIC_DRAW 数据不会或几乎不会改变。
     *   2. GL_DYNAMIC_DRAW 数据会被改变很多。
     *   3. GL_STREAM_DRAW 数据每次绘制时都会改变。
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    /**
     * 设置顶点着色器如何解析我们写死的顶点
     * 在顶点数组中，每三个元素数据为一组，
     * 表示一个顶点，所有定义了三个顶点。
     * 那么就让顶点着色器安装这种方式来解析
     * 顶点数组。
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    // 启用我们设置的让顶点着色器如何去解析顶点
    glEnableVertexAttribArray(0);
    /**
     * 当配置了如何去解析我们的顶点时即glVertexAttribPointer方法后，
     * 那么就可以解绑顶点缓冲对象VBO了，该顶点缓冲数组和其顶点解析方式
     * 就已经存入前边绑定的顶点数组对象VAO了，所以不在需要绑定它了。
     */
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /**
     * 由于这里只用了一个顶点缓冲对象VBO，所有的顶点缓冲对象VBO及其
     * 顶点解析方式都存入了顶点数组对象VAO中了，所以我们也不需要再持续
     * 绑定顶点数组对象了，可以将其解绑了。
     */
    glBindVertexArray(0);

    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        renderTriangle(window, VAO, shader);
    }

    // 不会再使用顶点数组对象VAO了，解绑并删除
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    // 不会再使用顶点缓冲对象VBO了，由于前边已经解绑了，只删除
    glDeleteBuffers(1, &VBO);
    // 不会再使用着色器程序了，解绑并删除
    (*shader).unUse();
    delete shader;
    shader = nullptr;
}

// 绘制四边形
void drawQuadrangle(GLFWwindow* window) {
    // 创建shader
    Shader* shader = new Shader();
    (*shader).readVertexSourceFile("./shader/triangle.vert").readFragmentSourceFile("./shader/triangle.frag").compileAll();

    // 设置四个顶点
    GLfloat vertex[] = {
        0.5f, 0.5f, 0.0f,   // 右上角(xyz)
        0.5f, -0.5f, 0.0f,  // 右下角(xyz)
        -0.5f, -0.5f, 0.0f, // 左下角(xyz)
        -0.5f, 0.5f, 0.0f   // 左上角(xyz)
    };
    // 设置顶点绘制顺序索引
    GLuint index[] = {
        0, 1, 2, // 右下三角形
        2, 3, 0  // 左上三角形
    };

    // 创建顶点数组对象，用来存储多个顶点缓冲对象
    GLuint VAO;
    /**
     * OpenGL生成顶点数组对象
     * 1、生成的顶点数组对象数量
     * 2、生成的顶点数组对象存储位置
     * 可以这样使用，一次生成4个
     * GLuint VAOS[4];
     * glGenVertexArrays(sizeof(VAOS), VAOS);
     */
    glGenVertexArrays(1, &VAO);
    /**
     * OpenGL绑定VAO顶点数组对象，让后续创建的
     * VBO顶点缓冲对象可以存储到其中
     */
    glBindVertexArray(VAO);

    // 创建顶点索引缓冲对象，用来存储顶点绘制顺序索引
    GLuint EBO;
    /**
     * OpenGL生成缓冲区对象
     * 1、生成的缓冲区对象数量
     * 2、生成的缓冲区存储位置
     * 可以这样使用，一次生成5个
     * GLuint buffers[5];
     * glGenBuffers(sizeof(buffers), buffers);
     */
    glGenBuffers(1, &EBO);
    // 设置该顶点索引缓冲对象EBO的类型为数组缓冲GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    /**
     * 将定义的顶点数据拷贝到这个顶点缓冲对象EBO中去
     * 1、数据类型：数组缓冲类型
     * 2、数据量大小：顶点数组的大小
     * 3、数据：就是定义的顶点
     * 4、数据类型：由于这是写死的顶点数据，数据不会变
     *   1. GL_STATIC_DRAW 数据不会或几乎不会改变。
     *   2. GL_DYNAMIC_DRAW 数据会被改变很多。
     *   3. GL_STREAM_DRAW 数据每次绘制时都会改变。
     */
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

    // 定义顶点缓冲对象VBO
    GLuint VBO;
    /**
     * OpenGL生成缓冲区对象
     * 1、生成的缓冲区对象数量
     * 2、生成的缓冲区存储位置
     * 可以这样使用，一次生成3个
     * GLuint buffers[3];
     * glGenBuffers(sizeof(buffers), buffers);
     */
    glGenBuffers(1, &VBO);
    // 设置该顶点缓冲对象VBO的类型为数组缓冲GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    /**
     * 将定义的顶点数据拷贝到这个顶点缓冲对象VBO中去
     * 1、数据类型：数组缓冲类型
     * 2、数据量大小：顶点数组的大小
     * 3、数据：就是定义的顶点
     * 4、数据类型：由于这是写死的顶点数据，数据不会变
     *   1. GL_STATIC_DRAW 数据不会或几乎不会改变。
     *   2. GL_DYNAMIC_DRAW 数据会被改变很多。
     *   3. GL_STREAM_DRAW 数据每次绘制时都会改变。
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    /**
     * 设置顶点着色器如何解析我们写死的顶点
     * 在顶点数组中，每三个元素数据为一组，
     * 表示一个顶点，所有定义了三个顶点。
     * 那么就让顶点着色器安装这种方式来解析
     * 顶点数组。
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    // 启用我们设置的让顶点着色器如何去解析顶点
    glEnableVertexAttribArray(0);
    /**
     * 当配置了如何去解析我们的顶点时即glVertexAttribPointer方法后，
     * 那么就可以解绑顶点缓冲对象VBO了，该顶点缓冲数组和其顶点解析方式
     * 就已经存入前边绑定的顶点数组对象VAO了，所以不在需要绑定它了。
     */
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /**
     * 由于这里只用了一个顶点缓冲对象VBO，所有的顶点缓冲对象VBO及其
     * 顶点解析方式都存入了顶点数组对象VAO中了，所以我们也不需要再持续
     * 绑定顶点数组对象了，可以将其解绑了。
     */
    glBindVertexArray(0);

    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        renderQuadrangle(window, VAO, shader);
    }

    // 不会再使用顶点数组对象VAO了，解绑并删除
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    // 不会再使用顶点缓冲对象VBO了，由于前边已经解绑了，只删除
    glDeleteBuffers(1, &EBO);
    // 不会再使用顶点缓冲对象VBO了，由于前边已经解绑了，只删除
    glDeleteBuffers(1, &VBO);
    // 不会再使用着色器程序了，解绑并删除
    (*shader).unUse();
    delete shader;
    shader = nullptr;
}

// 添加更多顶点到数据中，使用glDrawArrays，尝试绘制两个彼此相连的三角形
void drawTowDifferentTriangles(GLFWwindow* window) {
    // 创建shader
    Shader* shader = new Shader();
    (*shader).readAllSourceFile("./shader/triangle.vert", "./shader/triangle.frag").compileAll();

    // 创建顶点数组对象，用来存储多个顶点缓冲对象
    GLuint VAO;
    /**
     * OpenGL生成顶点数组对象
     * 1、生成的顶点数组对象数量
     * 2、生成的顶点数组对象存储位置
     * 可以这样使用，一次生成4个
     * GLuint VAOS[4];
     * glGenVertexArrays(sizeof(VAOS), VAOS);
     */
    glGenVertexArrays(1, &VAO);
    /**
     * OpenGL绑定VAO顶点数组对象，让后续创建的
     * VBO顶点缓冲对象可以存储到其中
     */
    glBindVertexArray(VAO);

    // 设置三个顶点
    GLfloat vertex[] = {
        // 第一个三角形
        0.5f, 0.5f, 0.0f,   // 右上(xyz)
        0.5f, -0.5f, 0.0f,  // 右下(xyz)
        -0.5f, -0.5f, 0.0f, // 左下(xyz)
        // 第二个三角形
        -0.5f, -0.5f, 0.0f, // 左下(xyz)
        -0.5f, 0.5f, 0.0f,  // 左上(xyz)
        0.5f, 0.5f, 0.0f    // 右上(xyz)
    };
    // 定义顶点缓冲对象VBO
    GLuint VBO;
    /**
     * OpenGL生成缓冲区对象
     * 1、生成的缓冲区对象数量
     * 2、生成的缓冲区存储位置
     * 可以这样使用，一次生成3个
     * GLuint buffers[3];
     * glGenBuffers(sizeof(buffers), buffers);
     */
    glGenBuffers(1, &VBO);
    // 设置该顶点缓冲对象VBO的类型为数组缓冲GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    /**
     * 将定义的顶点数据拷贝到这个顶点缓冲对象VBO中去
     * 1、数据类型：数组缓冲类型
     * 2、数据量大小：顶点数组的大小
     * 3、数据：就是定义的顶点
     * 4、数据类型：由于这是写死的顶点数据，数据不会变
     *   1. GL_STATIC_DRAW 数据不会或几乎不会改变。
     *   2. GL_DYNAMIC_DRAW 数据会被改变很多。
     *   3. GL_STREAM_DRAW 数据每次绘制时都会改变。
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    /**
     * 设置顶点着色器如何解析我们写死的顶点
     * 在顶点数组中，每三个元素数据为一组，
     * 表示一个顶点，所有定义了三个顶点。
     * 那么就让顶点着色器安装这种方式来解析
     * 顶点数组。
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    // 启用我们设置的让顶点着色器如何去解析顶点
    glEnableVertexAttribArray(0);
    /**
     * 当配置了如何去解析我们的顶点时即glVertexAttribPointer方法后，
     * 那么就可以解绑顶点缓冲对象VBO了，该顶点缓冲数组和其顶点解析方式
     * 就已经存入前边绑定的顶点数组对象VAO了，所以不在需要绑定它了。
     */
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /**
     * 由于这里只用了一个顶点缓冲对象VBO，所有的顶点缓冲对象VBO及其
     * 顶点解析方式都存入了顶点数组对象VAO中了，所以我们也不需要再持续
     * 绑定顶点数组对象了，可以将其解绑了。
     */
    glBindVertexArray(0);

    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        renderQuadrangleByMoreVertex(window, VAO, shader);
    }

    // 不会再使用顶点数组对象VAO了，解绑并删除
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    // 不会再使用顶点缓冲对象VBO了，由于前边已经解绑了，只删除
    glDeleteBuffers(1, &VBO);
    // 不会再使用着色器程序了，解绑并删除
    (*shader).unUse();
    delete shader;
    shader = nullptr;
}

// 创建相同的两个三角形，但对它们的数据使用不同的VAO和VBO
void drawTowTriangles(GLFWwindow* window) {
    // 创建shader
    Shader* shader = new Shader("./shader/triangle.vert", "./shader/triangle.frag");
    (*shader).compileAll();

    // 创建顶点数组对象，用来存储多个顶点缓冲对象
    GLuint VAO[2];
    /**
     * OpenGL生成顶点数组对象
     * 1、生成的顶点数组对象数量
     * 2、生成的顶点数组对象存储位置
     * 可以这样使用，一次生成4个
     * GLuint VAOS[4];
     * glGenVertexArrays(sizeof(VAOS), VAOS);
     */
    glGenVertexArrays(sizeof(VAO) / sizeof(GLuint), VAO);

    // 设置三个顶点
    GLfloat vertex1[] = {
        // 第一个三角形
        0.5f, 0.5f, 0.0f,  // 右上(xyz)
        0.5f, -0.5f, 0.0f, // 右下(xyz)
        -0.5f, -0.5f, 0.0f // 左下(xyz)
    };
    GLfloat vertex2[] = {
        // 第二个三角形
        -0.5f, -0.5f, 0.0f, // 左下(xyz)
        -0.5f, 0.5f, 0.0f,  // 左上(xyz)
        0.5f, 0.5f, 0.0f    // 右上(xyz)
    };

    /**
     * OpenGL绑定VAO顶点数组对象，让后续创建的
     * VBO顶点缓冲对象可以存储到其中
     */
    glBindVertexArray(VAO[0]);
    // 定义顶点缓冲对象VBO
    GLuint VBO[2];
    /**
     * OpenGL生成缓冲区对象
     * 1、生成的缓冲区对象数量
     * 2、生成的缓冲区存储位置
     * 可以这样使用，一次生成3个
     * GLuint buffers[3];
     * glGenBuffers(sizeof(buffers), buffers);
     */
    glGenBuffers(sizeof(VBO) / sizeof(GLuint), VBO);
    // 设置该顶点缓冲对象VBO的类型为数组缓冲GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    /**
     * 将定义的顶点数据拷贝到这个顶点缓冲对象VBO中去
     * 1、数据类型：数组缓冲类型
     * 2、数据量大小：顶点数组的大小
     * 3、数据：就是定义的顶点
     * 4、数据类型：由于这是写死的顶点数据，数据不会变
     *   1. GL_STATIC_DRAW 数据不会或几乎不会改变。
     *   2. GL_DYNAMIC_DRAW 数据会被改变很多。
     *   3. GL_STREAM_DRAW 数据每次绘制时都会改变。
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex1), vertex1, GL_STATIC_DRAW);
    /**
     * 设置顶点着色器如何解析我们写死的顶点
     * 在顶点数组中，每三个元素数据为一组，
     * 表示一个顶点，所有定义了三个顶点。
     * 那么就让顶点着色器安装这种方式来解析
     * 顶点数组。
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    // 启用我们设置的让顶点着色器如何去解析顶点
    glEnableVertexAttribArray(0);
    /**
     * 当配置了如何去解析我们的顶点时即glVertexAttribPointer方法后，
     * 那么就可以解绑顶点缓冲对象VBO了，该顶点缓冲数组和其顶点解析方式
     * 就已经存入前边绑定的顶点数组对象VAO了，所以不在需要绑定它了。
     */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    /**
     * 由于这里只用了一个顶点缓冲对象VBO，所有的顶点缓冲对象VBO及其
     * 顶点解析方式都存入了顶点数组对象VAO中了，所以我们也不需要再持续
     * 绑定顶点数组对象了，可以将其解绑切换VAO绑定。
     */
    glBindVertexArray(VAO[1]);
    /**
     * 绑定第二个VBO顶点缓冲数组
     */
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    /**
     * 将定义的顶点数据拷贝到这个顶点缓冲对象VBO中去
     * 1、数据类型：数组缓冲类型
     * 2、数据量大小：顶点数组的大小
     * 3、数据：就是定义的顶点
     * 4、数据类型：由于这是写死的顶点数据，数据不会变
     *   1. GL_STATIC_DRAW 数据不会或几乎不会改变。
     *   2. GL_DYNAMIC_DRAW 数据会被改变很多。
     *   3. GL_STREAM_DRAW 数据每次绘制时都会改变。
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex2), vertex2, GL_STATIC_DRAW);
    /**
     * 设置顶点着色器如何解析我们写死的顶点
     * 在顶点数组中，每三个元素数据为一组，
     * 表示一个顶点，所有定义了三个顶点。
     * 那么就让顶点着色器安装这种方式来解析
     * 顶点数组。
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    // 启用我们设置的让顶点着色器如何去解析顶点
    glEnableVertexAttribArray(0);
    /**
     * 当配置了如何去解析我们的顶点时即glVertexAttribPointer方法后，
     * 那么就可以解绑顶点缓冲对象VBO了，该顶点缓冲数组和其顶点解析方式
     * 就已经存入前边绑定的顶点数组对象VAO了，所以不在需要绑定它了。
     */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    /**
     * 由于这里只用了一个顶点缓冲对象VBO，所有的顶点缓冲对象VBO及其
     * 顶点解析方式都存入了顶点数组对象VAO中了，所以我们也不需要再持续
     * 绑定顶点数组对象了，可以将其解绑。
     */
    glBindVertexArray(0);

    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        renderTowTriangles(window, VAO, shader);
    }

    // 不会再使用顶点数组对象VAO了，解绑并删除
    glBindVertexArray(0);
    glDeleteVertexArrays(sizeof(VAO) / sizeof(GLuint), VAO);
    // 不会再使用顶点缓冲对象VBO了，由于前边已经解绑了，只删除
    glDeleteBuffers(sizeof(VBO) / sizeof(GLuint), VBO);
    // 不会再使用着色器程序了，解绑并删除
    (*shader).unUse();
    delete shader;
    shader = nullptr;
}

// 创建两个着色器程序，第二个程序使用一个不同的片段着色器，输出黄色；再次绘制这两个三角形，让其中一个输出为黄色
void towShader(GLFWwindow* window) {
    // 创建shader
    Shader* shader1 = new Shader("./shader/triangle.vert", "./shader/triangle.frag");
    (*shader1).compileAll();
    // 创建shader
    Shader* shader2 = new Shader(*shader1);
    (*shader2).readFragmentSourceFile("./shader/triangle2.frag").compileAll();
    // 指针数组
    Shader* shader[2] = {shader1, shader2};

    // 创建顶点数组对象，用来存储多个顶点缓冲对象
    GLuint VAO[2];
    /**
     * OpenGL生成顶点数组对象
     * 1、生成的顶点数组对象数量
     * 2、生成的顶点数组对象存储位置
     * 可以这样使用，一次生成4个
     * GLuint VAOS[4];
     * glGenVertexArrays(sizeof(VAOS), VAOS);
     */
    glGenVertexArrays(sizeof(VAO) / sizeof(GLuint), VAO);

    // 设置三个顶点
    GLfloat vertex1[] = {
        // 第一个三角形
        0.5f, 0.5f, 0.0f,  // 右上(xyz)
        0.5f, -0.5f, 0.0f, // 右下(xyz)
        -0.5f, -0.5f, 0.0f // 左下(xyz)
    };
    GLfloat vertex2[] = {
        // 第二个三角形
        -0.5f, -0.5f, 0.0f, // 左下(xyz)
        -0.5f, 0.5f, 0.0f,  // 左上(xyz)
        0.5f, 0.5f, 0.0f    // 右上(xyz)
    };

    /**
     * OpenGL绑定VAO顶点数组对象，让后续创建的
     * VBO顶点缓冲对象可以存储到其中
     */
    glBindVertexArray(VAO[0]);
    // 定义顶点缓冲对象VBO
    GLuint VBO[2];
    /**
     * OpenGL生成缓冲区对象
     * 1、生成的缓冲区对象数量
     * 2、生成的缓冲区存储位置
     * 可以这样使用，一次生成3个
     * GLuint buffers[3];
     * glGenBuffers(sizeof(buffers), buffers);
     */
    glGenBuffers(sizeof(VBO) / sizeof(GLuint), VBO);
    // 设置该顶点缓冲对象VBO的类型为数组缓冲GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    /**
     * 将定义的顶点数据拷贝到这个顶点缓冲对象VBO中去
     * 1、数据类型：数组缓冲类型
     * 2、数据量大小：顶点数组的大小
     * 3、数据：就是定义的顶点
     * 4、数据类型：由于这是写死的顶点数据，数据不会变
     *   1. GL_STATIC_DRAW 数据不会或几乎不会改变。
     *   2. GL_DYNAMIC_DRAW 数据会被改变很多。
     *   3. GL_STREAM_DRAW 数据每次绘制时都会改变。
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex1), vertex1, GL_STATIC_DRAW);
    /**
     * 设置顶点着色器如何解析我们写死的顶点
     * 在顶点数组中，每三个元素数据为一组，
     * 表示一个顶点，所有定义了三个顶点。
     * 那么就让顶点着色器安装这种方式来解析
     * 顶点数组。
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    // 启用我们设置的让顶点着色器如何去解析顶点
    glEnableVertexAttribArray(0);
    /**
     * 当配置了如何去解析我们的顶点时即glVertexAttribPointer方法后，
     * 那么就可以解绑顶点缓冲对象VBO了，该顶点缓冲数组和其顶点解析方式
     * 就已经存入前边绑定的顶点数组对象VAO了，所以不在需要绑定它了。
     */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    /**
     * 由于这里只用了一个顶点缓冲对象VBO，所有的顶点缓冲对象VBO及其
     * 顶点解析方式都存入了顶点数组对象VAO中了，所以我们也不需要再持续
     * 绑定顶点数组对象了，可以将其解绑切换VAO绑定。
     */
    glBindVertexArray(VAO[1]);
    /**
     * 绑定第二个VBO顶点缓冲数组
     */
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    /**
     * 将定义的顶点数据拷贝到这个顶点缓冲对象VBO中去
     * 1、数据类型：数组缓冲类型
     * 2、数据量大小：顶点数组的大小
     * 3、数据：就是定义的顶点
     * 4、数据类型：由于这是写死的顶点数据，数据不会变
     *   1. GL_STATIC_DRAW 数据不会或几乎不会改变。
     *   2. GL_DYNAMIC_DRAW 数据会被改变很多。
     *   3. GL_STREAM_DRAW 数据每次绘制时都会改变。
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex2), vertex2, GL_STATIC_DRAW);
    /**
     * 设置顶点着色器如何解析我们写死的顶点
     * 在顶点数组中，每三个元素数据为一组，
     * 表示一个顶点，所有定义了三个顶点。
     * 那么就让顶点着色器安装这种方式来解析
     * 顶点数组。
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    // 启用我们设置的让顶点着色器如何去解析顶点
    glEnableVertexAttribArray(0);
    /**
     * 当配置了如何去解析我们的顶点时即glVertexAttribPointer方法后，
     * 那么就可以解绑顶点缓冲对象VBO了，该顶点缓冲数组和其顶点解析方式
     * 就已经存入前边绑定的顶点数组对象VAO了，所以不在需要绑定它了。
     */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    /**
     * 由于这里只用了一个顶点缓冲对象VBO，所有的顶点缓冲对象VBO及其
     * 顶点解析方式都存入了顶点数组对象VAO中了，所以我们也不需要再持续
     * 绑定顶点数组对象了，可以将其解绑。
     */
    glBindVertexArray(0);

    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        renderTowTrianglesByTowShader(window, VAO, shader);
    }

    // 不会再使用顶点数组对象VAO了，解绑并删除
    glBindVertexArray(0);
    glDeleteVertexArrays(sizeof(VAO) / sizeof(GLuint), VAO);
    // 不会再使用顶点缓冲对象VBO了，由于前边已经解绑了，只删除
    glDeleteBuffers(sizeof(VBO) / sizeof(GLuint), VBO);
    // 不会再使用着色器程序了，解绑并删除
    shader1->unUse();
    shader2->unUse();
    delete shader1, shader2;
    shader1   = nullptr;
    shader2   = nullptr;
    shader[0] = nullptr;
    shader[1] = nullptr;
}
