#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>

#include "nlohmann/json.hpp"

// 读取配置文件
nlohmann::json readConfig(const std::string& filePath);

// 配置window全局变量
void configWindow(const nlohmann::json& json);

#endif