#include <fstream>
#include <string>

#include "common.h"
#include "config.h"
#include "global.h"
#include "log.h"
#include "nlohmann/json.hpp"

// 读取配置文件
nlohmann::json readConfig(const std::string& filePath) {
    // 读取配置json
    std::ifstream* input = nullptr;
    try {
        input = new std::ifstream(filePath);
    } catch (const std::exception& e) {
        logError("配置文件读取失败: {}", filePath);
        exitApplication();
    }
    nlohmann::json json = nlohmann::json();
    *input >> json;
    delete input;
    return json;
}

// 配置window全局变量
void configWindow(const nlohmann::json& json) {
    try {
        windowTitle            = json.at("window").at("title").at("value").get<std::string>();
        screenWidth            = json.at("window").at("width").at("value").get<GLint>();
        screenHeight           = json.at("window").at("height").at("value").get<GLint>();
        windowOpacity          = json.at("window").at("opacity").at("value").get<GLfloat>();
        windowOpacityChange    = json.at("window").at("opacityChangeSize").at("value").get<GLfloat>();
        isInLineMode           = json.at("window").at("isInLineMode").at("value").get<GLboolean>();
        isCharInput            = json.at("window").at("isInCharInputMode").at("value").get<GLboolean>();
        windowState            = json.at("window").at("state").at("value").get<GLint>();
        windowContentXPos      = json.at("window").at("fullWindowAttributes").at("contentXPos").at("value").get<GLint>();
        windowContentYPos      = json.at("window").at("fullWindowAttributes").at("contentYPos").at("value").get<GLint>();
        windowResolutionWidth  = json.at("window").at("fullWindowAttributes").at("resolutionWidth").at("value").get<GLint>();
        windowResolutionHeight = json.at("window").at("fullWindowAttributes").at("resolutionHeight").at("value").get<GLint>();
        windowRefreshRate      = json.at("window").at("fullWindowAttributes").at("refreshRate").at("value").get<GLint>();
    } catch (const std::exception& e) {
        logError("记录配置数据失败: {}", e.what());
        exitApplication();
    }
}
