#ifndef __SHADER_H__
#define __SHADER_H__

#include <fstream>
#include <string>

#include "glad/glad.h"

#include "GLFW/glfw3.h"

class Shader {
  private:
    // 订单着色器源码文件路径
    std::string* vertexSourceFilePath;
    // 片段着色器源码文件路径
    std::string* fragmentSourceFilePath;
    // 订单着色器源码
    std::string* vertexSource;
    // 片段着色器源码
    std::string* fragmentSource;
    // 订单着色器
    GLuint vertexShader;
    // 片段着色器
    GLuint fragmentShader;
    // 着色器程序
    GLuint shaderProgram;
    // 文件对象
    std::ifstream* fileReader;
    // 读取文件方法
    std::string* readFile(const std::string* const filePath);

  public:
    /**
     * constructor
     * 构造器
     */
    Shader();
    Shader(const std::string& vertexSourceFilePath, const std::string& fragmentSourceFilePath);
    Shader(const Shader& shader);
    /**
     * getter and setter
     * getter和setter方法
     */
    std::string getVertexSourceFilePath() const;
    Shader&     setVertexSourceFilePath(const std::string& vertexSourceFilePath);
    std::string getFragmentSourceFilePath() const;
    Shader&     setFragmentSourceFilePath(const std::string& fragmentSourceFilePath);
    Shader&     setAllShaderFilePath(const std::string& vertexSourceFilePath, const std::string& fragmentSourceFilePath);
    std::string getVertexSource() const;
    Shader&     setVertexSource(const std::string& vertexSource);
    std::string getFragmentSource() const;
    Shader&     setFragmentSource(const std::string& fragmentSource);
    GLuint      getVertexShader() const;
    Shader&     setVertexShader(const GLuint& vertexShader);
    GLuint      getFragmentShader() const;
    Shader&     setFragmentShader(const GLuint& fragmentShader);
    GLuint      getShaderProgram() const;
    Shader&     setShaderProgram(const GLuint& shaderProgram);
    /**
     * compile and link
     * 编译链接着色器程序
     */
    Shader&     readAllSourceFile();
    Shader&     readAllSourceFile(const std::string& vertexSourceFilePath, const std::string& fragmentSourceFilePath);
    Shader&     readVertexSourceFile();
    Shader&     readVertexSourceFile(const std::string& vertexSourceFilePath);
    Shader&     readFragmentSourceFile();
    Shader&     readFragmentSourceFile(const std::string& fragmentSourceFilePath);
    Shader&     compileAll();
    Shader&     compileAllShader();
    Shader&     compileAllShader(const std::string& vertexSourceFilePath, const std::string& fragmentSourceFilePath);
    Shader&     compileVertexShader();
    Shader&     compileVertexShader(const std::string& vertexSourceFilePath);
    Shader&     compileFragmentShader();
    Shader&     compileFragmentShader(const std::string& fragmentSourceFilePath);
    bool        isFragmentShaderCompileSuccess();
    bool        isVertexShaderCompileSuccess();
    bool        isShaderCompileSuccess();
    bool        isShaderProgramLinkSuccess();
    std::string getVertexShaderCompileInfo();
    std::string getFragmentShaderCompileInfo();
    std::string getShaderProgramLinkInfo();
    Shader&     changeAllShader(const std::string& vertexSourceFilePath, const std::string& fragmentSourceFilePath);
    Shader&     changeVertexShader(const std::string& vertexSourceFilePath);
    Shader&     changeFragmentShader(const std::string& fragmentSourceFilePath);
    Shader&     link();
    Shader&     use();
    Shader&     unUse();
    /**
     * set uniform
     * 设置着色器里的uniform变量
     */
    Shader& setBool(const std::string& parameterName, bool data);
    Shader& setInt(const std::string& parameterName, int data);
    Shader& setFloat(const std::string& parameterName, float data);
    /**
     * destructor
     * 析构
     */
    ~Shader();
};

#endif