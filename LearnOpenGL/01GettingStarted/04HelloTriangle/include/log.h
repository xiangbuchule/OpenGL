#ifndef __LOG_H__
#define __LOG_H__

#include <atomic>

#include "spdlog/spdlog.h"

/**
 * 单例日志对象
 * 支持多线程
 */
class Log {
  private:
    // 实例指针对象
    static std::atomic<Log*>        instance;
    std::shared_ptr<spdlog::logger> logger;
    // 构造析构
    Log();
    ~Log();
    // 用来析构的类
    class Free {
      public:
        Free();
        ~Free();
    };
    static Free free;
    // 去掉各种默认方法
    Log(const Log&) = delete;
    Log(Log&&)      = delete;
    Log& operator=(const Log&) = delete;
    Log& operator=(Log&&) = delete;

  public:
    // 获取实例
    static Log* getInstance();
    // 获取logger
    std::shared_ptr<spdlog::logger> getLogger();
};

// 定义宏，易于使用
#define logTrace(...) SPDLOG_LOGGER_CALL(Log::getInstance()->getLogger(), spdlog::level::trace, __VA_ARGS__)
#define logDebug(...) SPDLOG_LOGGER_CALL(Log::getInstance()->getLogger(), spdlog::level::debug, __VA_ARGS__)
#define logInfo(...)  SPDLOG_LOGGER_CALL(Log::getInstance()->getLogger(), spdlog::level::info, __VA_ARGS__)
#define logWarn(...)  SPDLOG_LOGGER_CALL(Log::getInstance()->getLogger(), spdlog::level::warn, __VA_ARGS__)
#define logError(...) SPDLOG_LOGGER_CALL(Log::getInstance()->getLogger(), spdlog::level::err, __VA_ARGS__)
#define logFlush()    Log::getInstance()->getLogger()->flush()

#endif