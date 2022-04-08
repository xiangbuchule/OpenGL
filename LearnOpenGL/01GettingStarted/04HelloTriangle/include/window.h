#ifndef __GLFWWINDOW_H__
#define __GLFWWINDOW_H__

#include <string>
#include <vector>

#include "glad/glad.h"

#include "GLFW/glfw3.h"

class Window {
  private:
    // 窗口指针
    GLFWwindow* window;

    /**
     * 窗口属性
     */
    // 窗口在那个显示器上
    GLFWmonitor* monitor;
    // 窗口标题
    std::string* title;
    // 窗口宽
    mutable GLint width;
    // 窗口高
    mutable GLint height;
    // 共享窗口，不需要setter方法
    GLFWwindow* sharedWindow;
    // 窗口图标数组
    std::vector<GLFWimage>* icons;
    // 窗口的位置
    mutable GLint xPos;
    mutable GLint yPos;
    // 宽高限制
    GLint maxWidth;
    GLint maxHeight;
    GLint minWidth;
    GLint minHeight;
    // 窗口比例
    GLint widthRatio;
    GLint heightRatio;
    // 帧缓冲宽高，不需要setter
    GLint framebufferWidth;
    GLint framebufferHeight;
    // 窗口距离系统窗口边距，不需要setter
    GLint left;
    GLint top;
    GLint right;
    GLint bottom;
    // 窗口内容比例，DPI比例，不需要setter
    GLfloat xScale;
    GLfloat yScale;
    // 窗口分辨率、刷新率、窗口内容位置，只有全屏时才有用
    GLint contentXPos;
    GLint contentYPos;
    GLint resolutionWidth;
    GLint resolutionHeight;
    GLint refreshRate;

    /**
     * 窗口状态判断
     */
    // 是否被销毁
    GLboolean isDestroy;
    // 窗口大小，1是最小化，2是正常，3是最大化，4是全屏化
    GLuint windowState;

    /**
     * 私有方法
     */
    // 窗口变化时更新窗口各种属性
    void updateWindowProperties();

  public:
    // 构造
    Window();
    Window(const Window& window);
    // getter and setter
    GLFWwindow*            getWindow() const;
    Window&                setWindow(GLFWwindow* const window);
    GLFWmonitor*           getMonitor() const;
    Window&                setMonitor(GLFWmonitor* const monitor);
    std::string            getTitle() const;
    Window&                setTitle(const std::string& title);
    GLint                  getWidth() const;
    Window&                setWidth(const GLint& width);
    GLint                  getHeight() const;
    Window&                setHeight(const GLint& height);
    GLFWwindow*            getSharedWindow() const;
    std::vector<GLFWimage> getIcons() const;
    Window&                setIcons(const std::vector<GLFWimage>& icons);
    GLint                  getXPos() const;
    Window&                setXPos(const GLint& xPos);
    GLint                  getYPos() const;
    Window&                setYPos(const GLint& yPos);
    GLint                  getMaxWidth() const;
    Window&                setMaxWidth(const GLint& maxWidth);
    GLint                  getMaxHeight() const;
    Window&                setMaxHeight(const GLint& maxHeight);
    GLint                  getMinWidth() const;
    Window&                setMinWidth(const GLint& minWidth);
    GLint                  getMinHeight() const;
    Window&                setMinHeight(const GLint& minHeight);
    GLint                  getWidthRatio() const;
    Window&                setWidthRatio(const GLint& widthRatio);
    GLint                  getHeightRatio() const;
    Window&                setHeightRatio(const GLint& heightRatio);
    GLint                  getFramebufferWidth();
    GLint                  getFramebufferHeight();
    GLint                  getLeft();
    GLint                  getTop();
    GLint                  getRight();
    GLint                  getBottom();
    GLfloat                getXScale();
    GLfloat                getYScale();
    GLfloat                getOpacity() const;
    Window&                setOpacity(const GLfloat& opacity);
    GLint                  getContentXPos() const;
    Window&                setContentXPos(const GLint& contentXPos);
    GLint                  getContentYPos() const;
    Window&                setContentYPos(const GLint& contentYPos);
    GLint                  getResolutionWidth() const;
    Window&                setResolutionWidth(const GLint& resolutionWidth);
    GLint                  getResolutionHeight() const;
    Window&                setResolutionHeight(const GLint& resolutionHeight);
    GLint                  getRefreshRate() const;
    Window&                setRefreshRate(const GLint& refreshRate);

    GLuint  getWindowState() const;
    Window& setWindowState(const GLuint& windowState);
    /**
     * 其他窗口相关方法
     */
    // 使用该窗口成为OpenGL上下文
    Window& use();
    /**
     * 设置各种窗口状态
     */
    // 销毁窗口
    Window& destroyWindow();
    // 关闭窗口
    Window& setWindowShouldClose(const GLint& value);
    // 设置窗口位置
    Window& setWindowPos(const GLint& xPos, const GLint& yPos);
    // 设置窗口大小
    Window& setWindowSize(const GLint& width, const GLint& height);
    // 设置窗口大小限制
    Window& setWindowSizeLimits(const GLint& minWidth, const GLint& minHeight, const GLint& maxWidth, const GLint& maxHeight);
    // 设置窗口比例
    Window& setWindowAspectRatio(const GLint& widthRatio, const GLint& heightRatio);
    // 设置窗口最小化/图标化
    Window& setIconifyWindow();
    // 设置窗口正常化
    Window& setRestoreWindow();
    // 设置窗口最大化
    Window& setMaximizeWindow();
    // 设置窗口全屏
    Window& setFullyWindow();
    // 设置窗口显示
    Window& setShowWindow();
    // 设置窗口隐藏
    Window& setHideWindow();
    // 设置聚焦到该窗口
    Window& setFocusWindow();
    // 设置窗口属性
    Window& setWindowAttributes(const GLint& windowAttribute, const GLint& option);
    // 设置窗口是否可调整大小
    Window& isWindowResizable(const GLint& option);
    // 设置窗口是否具有边框
    Window& isWindowDecorated(const GLint& option);
    // 设置窗口是否自动图标化
    Window& isWindowAutoIconify(const GLint& option);
    // 设置窗口是否浮动(在最顶层)
    Window& isWindowFloating(const GLint& option);
    // 设置窗口是否可透明(即窗口透明度是否生效)
    Window& isWindowTransparentFramebuffer(const GLint& option);
    // 设置窗口是否在显示时获得焦点
    Window& isWindowFocusOnShow(const GLint& option);
    // 设置窗口小图标闪烁，提示用户注意该窗口
    Window& setRequestWindowAttention();
    // 设置窗口的用户指针
    Window& setWindowUserPointer(void* pointer);
    /**
     * 获取各种窗口状态
     */
    // 获取窗口是否关闭
    GLint getWindowShouldClose() const;
    // 获取窗口位置
    void getWindowPos(GLint* const xPos, GLint* const yPos) const;
    // 获取窗口大小
    void getWindowSize(GLint* const width, GLint* const height) const;
    // 获取帧缓冲大小
    void getFramebufferSize(GLint* const width, GLint* const height);
    // 获取窗口距离系统窗口边距
    void getWindowFrameSize(GLint* const left, GLint* const top, GLint* const right, GLint* const bottom);
    // 获取窗口内容比例，DPI比例
    void getWindowContentScale(GLfloat* const xScale, GLfloat* const yScale);
    // 获取窗口是否隐藏
    GLint getWindowIsShow() const;
    // 获取窗口是否聚焦
    GLint getWindowIsFocus() const;
    // 获取窗口属性
    GLint getWindowAttributes(const GLint& windowAttribute) const;
    // 获取窗口是否可调整大小
    GLint getWindowIsResizable() const;
    // 获取窗口是否具有边框
    GLint getWindowIsDecorated() const;
    // 获取窗口是否具有边框
    GLint getWindowIsAutoIconify() const;
    // 获取窗口是否浮动(在最顶层)
    GLint getWindowIsFloating() const;
    // 获取窗口是否可透明(即窗口透明度是否生效)
    GLint getWindowIsTransparentFramebuffer() const;
    // 获取窗口是否在显示时获得焦点
    GLint getWindowIsFocusOnShow() const;
    // 获取窗口的用户指针
    void* getWindowUserPointer(void* pointer) const;
    /**
     * 设置各种窗口回调函数
     */
    // 指定窗口的位置变化时调用的回调
    Window& bindWindowPosCallback(GLFWwindowposfun callback);
    // 指定窗口的大小变化时调用的回调
    Window& bindWindowSizeCallback(GLFWwindowsizefun callback);
    // 指定窗口的关闭时调用的回调
    Window& bindWindowCloseCallback(GLFWwindowclosefun callback);
    // 指定窗口的刷新时调用的回调
    Window& bindWindowRefreshCallback(GLFWwindowrefreshfun callback);
    // 指定窗口的焦点发生变化时调用的回调
    Window& bindWindowFocusCallback(GLFWwindowfocusfun callback);
    // 指定窗口的图标化回调
    Window& bindWindowIconifyCallback(GLFWwindowiconifyfun callback);
    // 指定窗口的最大化回调
    Window& bindWindowMaximizeCallback(GLFWwindowmaximizefun callback);
    // 指定窗口的帧缓冲区调整大小回调
    Window& bindFramebufferSizeCallback(GLFWframebuffersizefun callback);
    // 指定窗口的窗口内容缩放回调，DPI
    Window& bindWindowContentScaleCallback(GLFWwindowcontentscalefun callback);
    // 指定窗口的按键输入回调
    Window& bindWindowKeyCallback(GLFWkeyfun callback);
    // 交换窗口双缓冲
    Window& swapBuffers();
    // 取消使用该窗口成为OpenGL上下文
    Window& unUse();
    // 析构
    ~Window();
};

#endif