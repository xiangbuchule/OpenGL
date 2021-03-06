#include <fstream>
#include <string>

#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include "common.h"
#include "log.h"
#include "shader.h"

Shader::Shader() {
    this->fileReader             = new std::ifstream();
    this->vertexSourceFilePath   = nullptr;
    this->fragmentSourceFilePath = nullptr;
    this->vertexSource           = new std::string();
    this->fragmentSource         = new std::string();
    this->vertexShader           = glCreateShader(GL_VERTEX_SHADER);
    this->fragmentShader         = glCreateShader(GL_FRAGMENT_SHADER);
    this->shaderProgram          = glCreateProgram();
}
Shader::Shader(const std::string& vertexSourceFilePath, const std::string& fragmentSourceFilePath) {
    this->fileReader             = new std::ifstream();
    this->vertexSourceFilePath   = new std::string(vertexSourceFilePath);
    this->fragmentSourceFilePath = new std::string(fragmentSourceFilePath);
    this->vertexSource           = this->readFile(this->vertexSourceFilePath);
    this->fragmentSource         = this->readFile(this->fragmentSourceFilePath);
    this->vertexShader           = glCreateShader(GL_VERTEX_SHADER);
    this->fragmentShader         = glCreateShader(GL_FRAGMENT_SHADER);
    this->shaderProgram          = glCreateProgram();
}
Shader::Shader(const Shader& shader) {
    this->fileReader             = new std::ifstream();
    this->vertexSourceFilePath   = new std::string(shader.getVertexSourceFilePath());
    this->fragmentSourceFilePath = new std::string(shader.getFragmentSourceFilePath());
    this->vertexSource           = new std::string(shader.getVertexSource());
    this->fragmentSource         = new std::string(shader.getFragmentSource());
    this->vertexShader           = glCreateShader(GL_VERTEX_SHADER);
    this->fragmentShader         = glCreateShader(GL_FRAGMENT_SHADER);
    this->shaderProgram          = glCreateProgram();
}

std::string* Shader::readFile(const std::string* const filePath) {
    this->fileReader->open(*filePath, std::ios::in);
    if (!this->fileReader->is_open()) {
        exit(-1);
    }
    std::string* fileContents = new std::string((std::istreambuf_iterator<char>(*this->fileReader)), std::istreambuf_iterator<char>());
    this->fileReader->close();
    this->fileReader->clear(std::ios::goodbit);
    return fileContents;
}

std::string Shader::getVertexSourceFilePath() const {
    return *this->vertexSourceFilePath;
}
Shader& Shader::setVertexSourceFilePath(const std::string& vertexSourceFilePath) {
    delete this->vertexSourceFilePath;
    this->vertexSourceFilePath = new std::string(vertexSourceFilePath);
    return *this;
}
std::string Shader::getFragmentSourceFilePath() const {
    return *this->fragmentSourceFilePath;
}
Shader& Shader::setFragmentSourceFilePath(const std::string& fragmentSourceFilePath) {
    delete this->fragmentSourceFilePath;
    this->fragmentSourceFilePath = new std::string(fragmentSourceFilePath);
    return *this;
}
Shader& Shader::setAllShaderFilePath(const std::string& vertexSourceFilePath, const std::string& fragmentSourceFilePath) {
    delete this->vertexSourceFilePath, this->fragmentSourceFilePath;
    this->vertexSourceFilePath   = new std::string(vertexSourceFilePath);
    this->fragmentSourceFilePath = new std::string(fragmentSourceFilePath);
    return *this;
}
std::string Shader::getVertexSource() const {
    return *this->vertexSource;
}
Shader& Shader::setVertexSource(const std::string& vertexSource) {
    delete this->vertexSource;
    this->vertexSource = new std::string(vertexSource);
    return *this;
}
std::string Shader::getFragmentSource() const {
    return *this->fragmentSource;
}
Shader& Shader::setFragmentSource(const std::string& fragmentSource) {
    delete this->fragmentSource;
    this->fragmentSource = new std::string(fragmentSource);
    return *this;
}
GLuint Shader::getVertexShader() const {
    return this->vertexShader;
}
Shader& Shader::setVertexShader(const GLuint& vertexShader) {
    this->vertexShader = vertexShader;
    return *this;
}
GLuint Shader::getFragmentShader() const {
    return this->fragmentShader;
}
Shader& Shader::setFragmentShader(const GLuint& fragmentShader) {
    this->fragmentShader = fragmentShader;
    return *this;
}
GLuint Shader::getShaderProgram() const {
    return this->shaderProgram;
}
Shader& Shader::setShaderProgram(const GLuint& shaderProgram) {
    this->shaderProgram = shaderProgram;
    return *this;
}

Shader& Shader::readAllSourceFile() {
    this->readVertexSourceFile();
    this->readFragmentSourceFile();
    return *this;
}
Shader& Shader::readAllSourceFile(const std::string& vertexSourceFilePath, const std::string& fragmentSourceFilePath) {
    this->readVertexSourceFile(vertexSourceFilePath);
    this->readFragmentSourceFile(fragmentSourceFilePath);
    return *this;
}
Shader& Shader::readVertexSourceFile() {
    delete this->vertexSource;
    this->vertexSource = this->readFile(this->vertexSourceFilePath);
    return *this;
}
Shader& Shader::readVertexSourceFile(const std::string& vertexSourceFilePath) {
    this->setVertexSourceFilePath(vertexSourceFilePath);
    this->readVertexSourceFile();
    return *this;
}
Shader& Shader::readFragmentSourceFile() {
    delete this->fragmentSource;
    this->fragmentSource = this->readFile(this->fragmentSourceFilePath);
    return *this;
}
Shader& Shader::readFragmentSourceFile(const std::string& fragmentSourceFilePath) {
    this->setFragmentSourceFilePath(fragmentSourceFilePath);
    this->readFragmentSourceFile();
    return *this;
}
Shader& Shader::compileAll() {
    this->compileAllShader();
    this->link();
    return *this;
}
Shader& Shader::compileAllShader() {
    this->compileVertexShader();
    this->compileFragmentShader();
    return *this;
}
Shader& Shader::compileAllShader(const std::string& vertexSourceFilePath, const std::string& fragmentSourceFilePath) {
    this->setAllShaderFilePath(vertexSourceFilePath, fragmentSourceFilePath);
    this->readAllSourceFile();
    this->compileAllShader();
    return *this;
}
Shader& Shader::compileVertexShader() {
    /**
     * ??????????????????????????????????????????
     * 1??????????????????
     * 2?????????????????????????????????????????????
     * 3???????????????
     * 4?????????????????????
     */
    const GLchar* nowVertexSource = this->vertexSource->c_str();
    glShaderSource(this->vertexShader, 1, &nowVertexSource, nullptr);
    // ?????????????????????????????????
    glCompileShader(this->vertexShader);
    if (!this->isVertexShaderCompileSuccess()) {
        logError("vertexShader compiled failed !!! ===> {}", this->getVertexShaderCompileInfo());
        logFlush();
        // ????????????
        exitApplication();
    }
    return *this;
}
Shader& Shader::compileVertexShader(const std::string& vertexSourceFilePath) {
    this->readVertexSourceFile(vertexSourceFilePath);
    this->compileVertexShader();
    return *this;
}
Shader& Shader::compileFragmentShader() {
    /**
     * ??????????????????????????????????????????
     * 1??????????????????
     * 2???????????????????????????????????????????????????
     * 3???????????????
     * 4?????????????????????
     */
    const GLchar* nowFragmentSource = this->fragmentSource->c_str();
    glShaderSource(this->fragmentShader, 1, &nowFragmentSource, nullptr);
    // ???????????????????????????
    glCompileShader(this->fragmentShader);
    if (!this->isFragmentShaderCompileSuccess()) {
        logError("fragmentShader compiled failed !!! ===> {}", this->getFragmentShaderCompileInfo());
        logFlush();
        // ????????????
        exitApplication();
    }
    return *this;
}
Shader& Shader::compileFragmentShader(const std::string& fragmentSourceFilePath) {
    this->readVertexSourceFile(fragmentSourceFilePath);
    this->compileFragmentShader();
    return *this;
}
bool Shader::isVertexShaderCompileSuccess() {
    // ????????????????????????????????????????????????
    GLint success;
    // ???OpenGL??????????????????????????????????????????
    glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &success);
    return (success) ? true : false;
}
bool Shader::isFragmentShaderCompileSuccess() {
    // ????????????????????????????????????????????????
    GLint success;
    // ???OpenGL??????????????????????????????????????????
    glGetShaderiv(this->fragmentShader, GL_COMPILE_STATUS, &success);
    return (success) ? true : false;
}
bool Shader::isShaderCompileSuccess() {
    return (this->isVertexShaderCompileSuccess() && this->isFragmentShaderCompileSuccess()) ? true : false;
}
bool Shader::isShaderProgramLinkSuccess() {
    // ??????????????????????????????????????????
    GLint success;
    // ???OpenGL??????????????????????????????????????????
    glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
    return (success) ? true : false;
}
std::string Shader::getVertexShaderCompileInfo() {
    // ????????????????????????????????????
    GLchar infoLog[512];
    // ??????????????????
    glGetShaderInfoLog(this->vertexShader, sizeof(infoLog), nullptr, infoLog);
    std::string result(infoLog);
    return result;
}
std::string Shader::getFragmentShaderCompileInfo() {
    // ????????????????????????????????????
    GLchar infoLog[512];
    // ??????????????????
    glGetShaderInfoLog(this->fragmentShader, sizeof(infoLog), nullptr, infoLog);
    std::string result(infoLog);
    return result;
}
std::string Shader::getShaderProgramLinkInfo() {
    // ????????????????????????????????????
    GLchar infoLog[512];
    // ??????????????????
    glGetProgramInfoLog(this->shaderProgram, sizeof(infoLog), nullptr, infoLog);
    std::string result(infoLog);
    return result;
}
Shader& Shader::changeAllShader(const std::string& vertexSourceFilePath, const std::string& fragmentSourceFilePath) {
    this->setAllShaderFilePath(vertexSourceFilePath, fragmentSourceFilePath);
    this->readAllSourceFile();
    this->compileAll();
    return *this;
}
Shader& Shader::changeVertexShader(const std::string& vertexSourceFilePath) {
    this->setVertexSourceFilePath(vertexSourceFilePath);
    this->readVertexSourceFile();
    this->compileAll();
    return *this;
}
Shader& Shader::changeFragmentShader(const std::string& fragmentSourceFilePath) {
    this->setFragmentSourceFilePath(fragmentSourceFilePath);
    this->readFragmentSourceFile();
    this->compileAll();
    return *this;
}
Shader& Shader::link() {
    // ?????????????????????????????????????????????????????????
    glAttachShader(this->shaderProgram, this->vertexShader);
    glAttachShader(this->shaderProgram, this->fragmentShader);
    // ???????????????????????????
    glLinkProgram(this->shaderProgram);
    if (!this->isShaderProgramLinkSuccess()) {
        logError("shaderProgram linked failed !!! ===> {} ", this->getShaderProgramLinkInfo());
        logFlush();
        // ????????????
        exitApplication();
    }
    return *this;
}
Shader& Shader::use() {
    glUseProgram(this->shaderProgram);
    return *this;
}
Shader& Shader::unUse() {
    glUseProgram(0);
    return *this;
}

Shader& Shader::setBool(const std::string& parameterName, bool data) {
    glUniform1i(glGetUniformLocation(this->shaderProgram, parameterName.c_str()), (int)data);
    return *this;
}
Shader& Shader::setInt(const std::string& parameterName, int data) {
    glUniform1i(glGetUniformLocation(this->shaderProgram, parameterName.c_str()), data);
    return *this;
}
Shader& Shader::setFloat(const std::string& parameterName, float data) {
    glUniform1f(glGetUniformLocation(this->shaderProgram, parameterName.c_str()), data);
    return *this;
}

Shader::~Shader() {
    // ??????????????????????????????????????????
    delete this->vertexSource, this->fragmentSource, this->fileReader, this->vertexSourceFilePath, this->fragmentSourceFilePath;
    // ????????????
    this->unUse();
    // ?????????????????????????????????
    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragmentShader);
    glDeleteProgram(this->shaderProgram);
}