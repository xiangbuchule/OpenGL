#include <string>

#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include "common.h"
#include "global.h"
#include "log.h"
#include "window.h"

/**
 * 私有方法
 */
// 窗口变化时更新窗口各种属性
void Window::updateWindowProperties() {
    // 设置窗口大小
    glfwGetWindowSize(this->window, &(this->width), &(this->height));
    // 设置窗口位置
    glfwGetWindowPos(this->window, &(this->xPos), &(this->yPos));
    // 设置帧缓冲大小
    glfwGetFramebufferSize(this->window, &(this->framebufferWidth), &(this->framebufferHeight));
    // 设置窗口边距
    glfwGetWindowFrameSize(this->window, &(this->left), &(this->top), &(this->right), &(this->bottom));
    // 设置窗口内容比例，DPI
    glfwGetWindowContentScale(this->window, &(this->xScale), &(this->yScale));
}

/**
 * 构造
 */
Window::Window() {
    // 设置窗口属性
    this->monitor      = nullptr;
    this->title        = new std::string(windowTitle);
    this->width        = screenWidth;
    this->height       = screenHeight;
    this->sharedWindow = nullptr;
    // 创建glfw窗口
    this->window = glfwCreateWindow(this->width, this->height, this->title->c_str(), this->monitor, this->sharedWindow);
    if (nullptr == this->window) {
        logError("Failed to create GLFW window !!!");
        logFlush();
        exitApplication();
    }
    // 设置窗口图标
    this->icons = new std::vector<GLFWimage>();
    // 设置窗口位置
    glfwGetWindowPos(this->window, &(this->xPos), &(this->yPos));
    // 设置窗口限制
    this->maxWidth  = GLFW_DONT_CARE;
    this->maxHeight = GLFW_DONT_CARE;
    this->minWidth  = GLFW_DONT_CARE;
    this->minHeight = GLFW_DONT_CARE;
    // 设置窗口比例
    this->widthRatio  = GLFW_DONT_CARE;
    this->heightRatio = GLFW_DONT_CARE;
    // 设置帧缓冲大小
    glfwGetFramebufferSize(this->window, &(this->framebufferWidth), &(this->framebufferHeight));
    // 设置窗口边距
    glfwGetWindowFrameSize(this->window, &(this->left), &(this->top), &(this->right), &(this->bottom));
    // 设置窗口内容比例，DPI
    glfwGetWindowContentScale(this->window, &(this->xScale), &(this->yScale));
    // 设置全屏窗口属性
    this->contentXPos      = windowContentXPos;
    this->contentYPos      = windowContentYPos;
    this->resolutionWidth  = windowResolutionWidth;
    this->resolutionHeight = windowResolutionHeight;
    this->refreshRate      = windowRefreshRate;
    // 设置窗口大小状态为正常
    this->windowState = WINDOW_NORMAL_STATE;
    // 窗口是否销毁
    this->isDestroy = false;
}
Window::Window(const Window& window) {
    // 设置窗口属性
    this->monitor = nullptr;
    this->title   = new std::string(window.getTitle());
    window.getWindowSize(&(this->width), &(this->height));
    this->sharedWindow = window.getSharedWindow();
    // 创建glfw窗口
    this->window = glfwCreateWindow(this->width, this->height, this->title->c_str(), this->monitor, this->sharedWindow);
    if (nullptr == this->window) {
        logError("Failed to create GLFW window !!!");
        logFlush();
        exitApplication();
    }
    // 设置窗口图标
    this->icons = new std::vector<GLFWimage>(window.getIcons());
    if (0 < this->icons->size())
        glfwSetWindowIcon(this->window, (GLint)this->icons->size(), this->icons->data());
    // 设置窗口位置
    window.getWindowPos(&(this->xPos), &(this->yPos));
    glfwGetWindowPos(this->window, &(this->xPos), &(this->yPos));
    // 设置窗口限制
    this->maxWidth  = window.getMaxWidth();
    this->maxHeight = window.getMaxHeight();
    this->minWidth  = window.getMinWidth();
    this->minHeight = window.getMinHeight();
    // 设置窗口比例
    this->widthRatio  = window.getWidthRatio();
    this->heightRatio = window.getHeightRatio();
    // 设置帧缓冲大小
    glfwGetFramebufferSize(this->window, &(this->framebufferWidth), &(this->framebufferHeight));
    // 设置窗口边距
    glfwGetWindowFrameSize(this->window, &(this->left), &(this->top), &(this->right), &(this->bottom));
    // 设置窗口内容比例，DPI
    glfwGetWindowContentScale(this->window, &(this->xScale), &(this->yScale));
    // 设置窗口透明度
    glfwSetWindowOpacity(this->window, window.getOpacity());
    // 设置全屏窗口属性
    this->contentXPos      = window.getContentXPos();
    this->contentYPos      = window.getContentYPos();
    this->resolutionWidth  = window.getResolutionWidth();
    this->resolutionHeight = window.getResolutionHeight();
    this->refreshRate      = window.getRefreshRate();
    // 设置窗口可见
    if (GLFW_FALSE == window.getWindowIsShow())
        glfwHideWindow(this->window);
    // 设置窗口自动图标化
    if (GLFW_TRUE == window.getWindowIsAutoIconify())
        glfwSetWindowAttrib(this->window, GLFW_AUTO_ICONIFY, GLFW_TRUE);
    // 设置窗口会透明
    if (GLFW_FALSE == window.getWindowIsTransparentFramebuffer())
        glfwSetWindowAttrib(this->window, GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);
    // 设置窗口是否可调整大小
    if (GLFW_FALSE == window.getWindowIsResizable())
        glfwSetWindowAttrib(this->window, GLFW_RESIZABLE, GLFW_FALSE);
    // 设置窗口大小状态为正常
    this->windowState = WINDOW_NORMAL_STATE;
    // 窗口是否销毁
    this->isDestroy = false;
}
/**
 * getter and setter
 */
GLFWwindow* Window::getWindow() const {
    return this->window;
}
Window& Window::setWindow(GLFWwindow* const window) {
    this->window = window;
    return *this;
}
GLFWmonitor* Window::getMonitor() const {
    return this->monitor;
}
Window& Window::setMonitor(GLFWmonitor* const monitor) {
    glfwSetWindowMonitor(this->window, monitor, this->contentXPos, this->contentYPos, this->resolutionWidth, this->resolutionHeight, this->refreshRate);
    this->monitor = monitor;
    return *this;
}
std::string Window::getTitle() const {
    return *(this->title);
}
Window& Window::setTitle(const std::string& title) {
    glfwSetWindowTitle(this->window, title.c_str());
    this->title = new std::string(title);
    return *this;
}
GLint Window::getWidth() const {
    glfwGetWindowSize(this->window, &(this->width), &(this->height));
    return this->width;
}
Window& Window::setWidth(const GLint& width) {
    glfwSetWindowSize(this->window, width, this->height);
    this->width = width;
    return *this;
}
GLint Window::getHeight() const {
    glfwGetWindowSize(this->window, &(this->width), &(this->height));
    return this->height;
}
Window& Window::setHeight(const GLint& height) {
    glfwSetWindowSize(this->window, this->width, height);
    this->height = height;
    return *this;
}
GLFWwindow* Window::getSharedWindow() const {
    return this->sharedWindow;
}
std::vector<GLFWimage> Window::getIcons() const {
    return *(this->icons);
}
Window& Window::setIcons(const std::vector<GLFWimage>& icons) {
    delete this->icons;
    this->icons = new std::vector<GLFWimage>(icons);
    glfwSetWindowIcon(this->window, (GLint)this->icons->size(), this->icons->data());
    return *this;
}
GLint Window::getXPos() const {
    glfwGetWindowPos(this->window, &(this->xPos), &(this->yPos));
    return this->xPos;
}
Window& Window::setXPos(const GLint& xPos) {
    glfwSetWindowPos(this->window, xPos, this->yPos);
    this->xPos = xPos;
    return *this;
}
GLint Window::getYPos() const {
    glfwGetWindowPos(this->window, &(this->xPos), &(this->yPos));
    return this->yPos;
}
Window& Window::setYPos(const GLint& yPos) {
    glfwSetWindowPos(this->window, this->xPos, yPos);
    this->yPos = yPos;
    return *this;
}
GLint Window::getMaxWidth() const {
    return this->maxWidth;
}
Window& Window::setMaxWidth(const GLint& maxWidth) {
    glfwSetWindowSizeLimits(this->window, this->minWidth, this->minHeight, maxWidth, this->maxHeight);
    this->maxWidth = maxWidth;
    return *this;
}
GLint Window::getMaxHeight() const {
    return this->maxHeight;
}
Window& Window::setMaxHeight(const GLint& maxHeight) {
    glfwSetWindowSizeLimits(this->window, this->minWidth, this->minHeight, this->maxWidth, maxHeight);
    this->maxHeight = maxHeight;
    return *this;
}
GLint Window::getMinWidth() const {
    return this->minWidth;
}
Window& Window::setMinWidth(const GLint& minWidth) {
    glfwSetWindowSizeLimits(this->window, minWidth, this->minHeight, this->maxWidth, this->maxHeight);
    this->minWidth = minWidth;
    return *this;
}
GLint Window::getMinHeight() const {
    return this->minHeight;
}
Window& Window::setMinHeight(const GLint& minHeight) {
    glfwSetWindowSizeLimits(this->window, this->minWidth, minHeight, this->maxWidth, this->maxHeight);
    this->minHeight = minHeight;
    return *this;
}
GLint Window::getWidthRatio() const {
    return this->widthRatio;
}
Window& Window::setWidthRatio(const GLint& widthRatio) {
    glfwSetWindowAspectRatio(this->window, widthRatio, this->heightRatio);
    this->widthRatio = widthRatio;
    return *this;
}
GLint Window::getHeightRatio() const {
    return this->heightRatio;
}
Window& Window::setHeightRatio(const GLint& heightRatio) {
    glfwSetWindowAspectRatio(this->window, this->widthRatio, heightRatio);
    this->heightRatio = heightRatio;
    return *this;
}
GLint Window::getFramebufferWidth() {
    glfwGetFramebufferSize(this->window, &(this->framebufferWidth), &(this->framebufferHeight));
    return this->framebufferWidth;
}
GLint Window::getFramebufferHeight() {
    glfwGetFramebufferSize(this->window, &(this->framebufferWidth), &(this->framebufferHeight));
    return this->framebufferHeight;
}
GLint Window::getLeft() {
    glfwGetWindowFrameSize(this->window, &(this->left), &(this->top), &(this->right), &(this->bottom));
    return this->left;
}
GLint Window::getTop() {
    glfwGetWindowFrameSize(this->window, &(this->left), &(this->top), &(this->right), &(this->bottom));
    return this->top;
}
GLint Window::getRight() {
    glfwGetWindowFrameSize(this->window, &(this->left), &(this->top), &(this->right), &(this->bottom));
    return this->right;
}
GLint Window::getBottom() {
    glfwGetWindowFrameSize(this->window, &(this->left), &(this->top), &(this->right), &(this->bottom));
    return this->bottom;
}
GLfloat Window::getXScale() {
    glfwGetWindowContentScale(this->window, &(this->xScale), &(this->yScale));
    return this->xScale;
}
GLfloat Window::getYScale() {
    glfwGetWindowContentScale(this->window, &(this->xScale), &(this->yScale));
    return this->yScale;
}
GLfloat Window::getOpacity() const {
    return glfwGetWindowOpacity(this->window);
}
Window& Window::setOpacity(const GLfloat& opacity) {
    glfwSetWindowOpacity(this->window, opacity);
    return *this;
}
GLint Window::getContentXPos() const {
    return this->contentXPos;
}
Window& Window::setContentXPos(const GLint& contentXPos) {
    if (WINDOW_FULL_STATE == this->windowState) {
        glfwSetWindowMonitor(this->window, this->monitor, contentXPos, this->contentYPos, this->resolutionWidth, this->resolutionHeight, this->refreshRate);
        this->updateWindowProperties();
    }
    this->contentXPos = contentXPos;
    return *this;
}
GLint Window::getContentYPos() const {
    return this->contentYPos;
}
Window& Window::setContentYPos(const GLint& contentYPos) {
    if (WINDOW_FULL_STATE == this->windowState) {
        glfwSetWindowMonitor(this->window, this->monitor, this->contentXPos, contentYPos, this->resolutionWidth, this->resolutionHeight, this->refreshRate);
        this->updateWindowProperties();
    }
    this->contentYPos = contentYPos;
    return *this;
}
GLint Window::getResolutionWidth() const {
    return this->resolutionWidth;
}
Window& Window::setResolutionWidth(const GLint& resolutionWidth) {
    if (WINDOW_FULL_STATE == this->windowState) {
        glfwSetWindowMonitor(this->window, this->monitor, this->contentXPos, this->contentYPos, resolutionWidth, this->resolutionHeight, this->refreshRate);
        this->updateWindowProperties();
    }
    this->resolutionWidth = resolutionWidth;
    return *this;
}
GLint Window::getResolutionHeight() const {
    return this->resolutionHeight;
}
Window& Window::setResolutionHeight(const GLint& resolutionHeight) {
    if (WINDOW_FULL_STATE == this->windowState) {
        glfwSetWindowMonitor(this->window, this->monitor, this->contentXPos, this->contentYPos, this->resolutionWidth, resolutionHeight, this->refreshRate);
        this->updateWindowProperties();
    }
    this->resolutionHeight = resolutionHeight;
    return *this;
}
GLint Window::getRefreshRate() const {
    return this->refreshRate;
}
Window& Window::setRefreshRate(const GLint& refreshRate) {
    if (WINDOW_FULL_STATE == this->windowState) {
        glfwSetWindowMonitor(this->window, this->monitor, this->contentXPos, this->contentYPos, this->resolutionWidth, this->resolutionHeight, refreshRate);
        this->updateWindowProperties();
    }
    this->refreshRate = refreshRate;
    return *this;
}

GLuint Window::getWindowState() const {
    return this->windowState;
}
Window& Window::setWindowState(const GLuint& windowState) {
    if (this->windowState = windowState)
        return *this;
    this->windowState = windowState;
    switch (windowState) {
        case WINDOW_MIN_STATE:
            glfwIconifyWindow(this->window);
            break;
        case WINDOW_NORMAL_STATE:
            glfwRestoreWindow(this->window);
            break;
        case WINDOW_MAX_STATE:
            glfwMaximizeWindow(this->window);
            break;
        case WINDOW_FULL_STATE:
            if (nullptr == this->monitor) this->monitor = glfwGetPrimaryMonitor();
            glfwSetWindowMonitor(this->window, this->monitor, this->contentXPos, this->contentYPos, this->resolutionWidth, this->resolutionHeight, this->refreshRate);
            break;
        default:
            break;
    }
    this->updateWindowProperties();
    return *this;
}
/**
 * 其他窗口相关方法
 */
// 使用该窗口成为OpenGL上下文
Window& Window::use() {
    glfwMakeContextCurrent(this->window);
    return *this;
}
/**
 * 设置各种窗口状态
 */
// 销毁窗口
Window& Window::destroyWindow() {
    this->isDestroy = true;
    glfwDestroyWindow(this->window);
    return *this;
}
// 关闭窗口
Window& Window::setWindowShouldClose(const GLint& value) {
    glfwSetWindowShouldClose(this->window, value);
    return *this;
}
// 设置窗口位置
Window& Window::setWindowPos(const GLint& xPos, const GLint& yPos) {
    glfwSetWindowPos(this->window, xPos, yPos);
    this->xPos = xPos;
    this->yPos = yPos;
    return *this;
}
// 设置窗口大小
Window& Window::setWindowSize(const GLint& width, const GLint& height) {
    glfwSetWindowSize(this->window, width, height);
    this->width  = width;
    this->height = height;
    return *this;
}
// 设置窗口大小限制
Window& Window::setWindowSizeLimits(const GLint& minWidth, const GLint& minHeight, const GLint& maxWidth, const GLint& maxHeight) {
    glfwSetWindowSizeLimits(this->window, minWidth, minHeight, maxWidth, maxHeight);
    this->minWidth  = minWidth;
    this->minHeight = minHeight;
    this->maxWidth  = maxWidth;
    this->maxHeight = maxHeight;
    return *this;
}
// 设置窗口比例
Window& Window::setWindowAspectRatio(const GLint& widthRatio, const GLint& heightRatio) {
    glfwSetWindowAspectRatio(this->window, widthRatio, heightRatio);
    this->widthRatio  = widthRatio;
    this->heightRatio = heightRatio;
    return *this;
}
// 设置窗口最小化/图标化
Window& Window::setIconifyWindow() {
    glfwIconifyWindow(this->window);
    this->windowState = WINDOW_MIN_STATE;
    this->updateWindowProperties();
    return *this;
}
// 设置窗口正常化
Window& Window::setRestoreWindow() {
    glfwRestoreWindow(this->window);
    this->windowState = WINDOW_NORMAL_STATE;
    this->updateWindowProperties();
    return *this;
}
// 设置窗口最大化
Window& Window::setMaximizeWindow() {
    glfwMaximizeWindow(this->window);
    this->windowState = WINDOW_MAX_STATE;
    this->updateWindowProperties();
    return *this;
}
// 设置窗口全屏
Window& Window::setFullyWindow() {
    if (nullptr == this->monitor)
        this->monitor = glfwGetPrimaryMonitor();
    glfwSetWindowMonitor(this->window, this->monitor, this->contentXPos, this->contentYPos, this->resolutionWidth, this->resolutionHeight, this->refreshRate);
    this->windowState = WINDOW_FULL_STATE;
    this->updateWindowProperties();
    return *this;
}
// 设置窗口显示
Window& Window::setShowWindow() {
    if (GLFW_FALSE == glfwGetWindowAttrib(this->window, GLFW_VISIBLE))
        glfwShowWindow(this->window);
    return *this;
}
// 设置窗口隐藏
Window& Window::setHideWindow() {
    if (GLFW_TRUE == glfwGetWindowAttrib(this->window, GLFW_VISIBLE))
        glfwHideWindow(this->window);
    return *this;
}
// 设置聚焦到该窗口
Window& Window::setFocusWindow() {
    if (GLFW_FALSE == glfwGetWindowAttrib(this->window, GLFW_FOCUSED))
        glfwFocusWindow(this->window);
    return *this;
}
// 设置窗口属性
Window& Window::setWindowAttributes(const GLint& windowAttribute, const GLint& option) {
    glfwSetWindowAttrib(this->window, windowAttribute, option);
    return *this;
}
// 设置窗口是否可调整大小
Window& Window::isWindowResizable(const GLint& option) {
    if (option != glfwGetWindowAttrib(this->window, GLFW_RESIZABLE))
        glfwSetWindowAttrib(this->window, GLFW_RESIZABLE, option);
    return *this;
}
// 设置窗口是否具有边框
Window& Window::isWindowDecorated(const GLint& option) {
    if (option != glfwGetWindowAttrib(this->window, GLFW_DECORATED)) {
        glfwSetWindowAttrib(this->window, GLFW_DECORATED, option);
        this->updateWindowProperties();
    }
    return *this;
}
// 设置窗口是否自动图标化
Window& Window::isWindowAutoIconify(const GLint& option) {
    if (option != glfwGetWindowAttrib(this->window, GLFW_AUTO_ICONIFY)) {
        glfwSetWindowAttrib(this->window, GLFW_AUTO_ICONIFY, option);
        this->updateWindowProperties();
    }
    return *this;
}
// 设置窗口是否浮动(在最顶层)
Window& Window::isWindowFloating(const GLint& option) {
    if (option != glfwGetWindowAttrib(this->window, GLFW_FLOATING))
        glfwSetWindowAttrib(this->window, GLFW_FLOATING, option);
    return *this;
}
// 设置窗口是否可透明(即窗口透明度是否生效)
Window& Window::isWindowTransparentFramebuffer(const GLint& option) {
    if (option != glfwGetWindowAttrib(this->window, GLFW_TRANSPARENT_FRAMEBUFFER))
        glfwSetWindowAttrib(this->window, GLFW_TRANSPARENT_FRAMEBUFFER, option);
    return *this;
}
// 设置窗口是否在显示时获得焦点
Window& Window::isWindowFocusOnShow(const GLint& option) {
    if (option != glfwGetWindowAttrib(this->window, GLFW_FOCUS_ON_SHOW))
        glfwSetWindowAttrib(this->window, GLFW_FOCUS_ON_SHOW, option);
    return *this;
}
// 设置窗口小图标闪烁，提示用户注意该窗口
Window& Window::setRequestWindowAttention() {
    glfwRequestWindowAttention(this->window);
    return *this;
}
// 设置窗口的用户指针
Window& Window::setWindowUserPointer(void* pointer) {
    glfwSetWindowUserPointer(this->window, pointer);
    return *this;
}
/**
 * 获取各种窗口状态
 */
// 获取窗口是否关闭
GLint Window::getWindowShouldClose() const {
    return glfwWindowShouldClose(this->window);
}
// 获取窗口位置
void Window::getWindowPos(GLint* const xPos, GLint* const yPos) const {
    glfwGetWindowPos(this->window, xPos, yPos);
    this->xPos = *xPos;
    this->yPos = *yPos;
}
// 获取窗口大小
void Window::getWindowSize(GLint* const width, GLint* const height) const {
    glfwGetWindowSize(this->window, width, height);
    this->width  = *width;
    this->height = *height;
}
// 获取帧缓冲大小
void Window::getFramebufferSize(GLint* const width, GLint* const height) {
    glfwGetFramebufferSize(this->window, width, height);
    this->framebufferWidth  = *width;
    this->framebufferHeight = *height;
}
// 获取窗口距离系统窗口边距
void Window::getWindowFrameSize(GLint* const left, GLint* const top, GLint* const right, GLint* const bottom) {
    glfwGetWindowFrameSize(this->window, left, top, right, bottom);
    this->left   = *left;
    this->top    = *top;
    this->right  = *right;
    this->bottom = *bottom;
}
// 获取窗口内容比例，DPI比例
void Window::getWindowContentScale(GLfloat* const xScale, GLfloat* const yScale) {
    glfwGetWindowContentScale(this->window, xScale, yScale);
    this->xScale = *xScale;
    this->yScale = *yScale;
}
// 获取窗口是否隐藏
GLint Window::getWindowIsShow() const {
    return glfwGetWindowAttrib(this->window, GLFW_VISIBLE);
}
// 获取窗口是否聚焦
GLint Window::getWindowIsFocus() const {
    return glfwGetWindowAttrib(this->window, GLFW_FOCUSED);
}
// 获取窗口属性
GLint Window::getWindowAttributes(const GLint& windowAttribute) const {
    return glfwGetWindowAttrib(this->window, windowAttribute);
}
// 获取窗口是否可调整大小
GLint Window::getWindowIsResizable() const {
    return glfwGetWindowAttrib(this->window, GLFW_RESIZABLE);
}
// 获取窗口是否具有边框
GLint Window::getWindowIsDecorated() const {
    return glfwGetWindowAttrib(this->window, GLFW_DECORATED);
}
// 获取窗口是否具有边框
GLint Window::getWindowIsAutoIconify() const {
    return glfwGetWindowAttrib(this->window, GLFW_AUTO_ICONIFY);
}
// 获取窗口是否浮动(在最顶层)
GLint Window::getWindowIsFloating() const {
    return glfwGetWindowAttrib(this->window, GLFW_FLOATING);
}
// 获取窗口是否可透明(即窗口透明度是否生效)
GLint Window::getWindowIsTransparentFramebuffer() const {
    return glfwGetWindowAttrib(this->window, GLFW_TRANSPARENT_FRAMEBUFFER);
}
// 获取窗口是否在显示时获得焦点
GLint Window::getWindowIsFocusOnShow() const {
    return glfwGetWindowAttrib(this->window, GLFW_FOCUS_ON_SHOW);
}
// 获取窗口的用户指针
void* Window::getWindowUserPointer(void* pointer) const {
    return glfwGetWindowUserPointer(this->window);
}
/**
 * 设置各种窗口回调函数
 */
// 指定窗口的位置变化时调用的回调
Window& Window::bindWindowPosCallback(GLFWwindowposfun callback) {
    glfwSetWindowPosCallback(this->window, callback);
    return *this;
}
// 指定窗口的大小变化时调用的回调
Window& Window::bindWindowSizeCallback(GLFWwindowsizefun callback) {
    glfwSetWindowSizeCallback(this->window, callback);
    return *this;
}
// 指定窗口的关闭时调用的回调
Window& Window::bindWindowCloseCallback(GLFWwindowclosefun callback) {
    glfwSetWindowCloseCallback(this->window, callback);
    return *this;
}
// 指定窗口的刷新时调用的回调
Window& Window::bindWindowRefreshCallback(GLFWwindowrefreshfun callback) {
    glfwSetWindowRefreshCallback(this->window, callback);
    return *this;
}
// 指定窗口的焦点发生变化时调用的回调
Window& Window::bindWindowFocusCallback(GLFWwindowfocusfun callback) {
    glfwSetWindowFocusCallback(this->window, callback);
    return *this;
}
// 指定窗口的图标化回调
Window& Window::bindWindowIconifyCallback(GLFWwindowiconifyfun callback) {
    glfwSetWindowIconifyCallback(this->window, callback);
    return *this;
}
// 指定窗口的最大化回调
Window& Window::bindWindowMaximizeCallback(GLFWwindowmaximizefun callback) {
    glfwSetWindowMaximizeCallback(this->window, callback);
    return *this;
}
// 指定窗口的帧缓冲区调整大小回调
Window& Window::bindFramebufferSizeCallback(GLFWframebuffersizefun callback) {
    glfwSetFramebufferSizeCallback(this->window, callback);
    return *this;
}
// 指定窗口的窗口内容缩放回调
Window& Window::bindWindowContentScaleCallback(GLFWwindowcontentscalefun callback) {
    glfwSetWindowContentScaleCallback(this->window, callback);
    return *this;
}
// 指定窗口的按键输入回调
Window& Window::bindWindowKeyCallback(GLFWkeyfun callback) {
    glfwSetKeyCallback(this->window, callback);
    return *this;
}
// 交换窗口双缓冲
Window& Window::swapBuffers() {
    glfwSwapBuffers(this->window);
    return *this;
}
// 取消使用该窗口成为OpenGL上下文
Window& Window::unUse() {
    glfwMakeContextCurrent(nullptr);
    return *this;
}
// 析构
Window::~Window() {
    glfwDestroyWindow(this->window);
    this->window    = nullptr;
    this->isDestroy = true;
    this->monitor   = nullptr;
    delete this->title, this->icons;
}