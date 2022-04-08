#include <atomic>
#include <iostream>
#include <mutex>

#include "spdlog/async.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#include "log.h"

std::atomic<Log*> Log::instance = nullptr;
Log::Free         Log::free;
Log::Log() {
    // 日志格式
    const std::string pattern = "[%Y-%m-%d %T.%e] [logger:%n] [process:%P] [thread:%t] [level:%^%l%$]: %v";
    try {
        // 在创建异步logger前指定队列大小、线程大小(8192大小的队列、2个线程)，创建每日23:59生成日志文件的异步logger
        spdlog::init_thread_pool(8192, 2);
        std::shared_ptr<spdlog::logger> asyncLogger = spdlog::create_async<spdlog::sinks::daily_file_sink_mt>("asyncLogger", "./logs/LearnOpenGL.log", 23, 59);
        // 更改logger默认sink的格式化内容，并设置级别
        asyncLogger->sinks()[0]->set_pattern(pattern);
        asyncLogger->sinks()[0]->set_level(spdlog::level::debug);
#if defined(_DEBUG) || defined(DEBUG)
        // 创建在异步控制台打印的sink
        std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        // 设置控制台输出级别和格式
        console_sink->set_level(spdlog::level::debug);
        console_sink->set_pattern(pattern);
        // 将控控制台sink绑定到logger中
        asyncLogger->sinks().push_back(console_sink);
#endif
        // 注册logger到spdlog中，并设置替换默认logger
        spdlog::set_default_logger(asyncLogger);
        this->logger = asyncLogger;
    } catch (const spdlog::spdlog_ex& ex) {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }
};
Log::~Log() {
    /**
     * 析构前通知spdlog将要关闭
     * 让日志都flush刷到文件中
     */
    spdlog::shutdown();
    // 程序退出前清理spdlog
    spdlog::drop_all();
}
Log* Log::getInstance() {
    Log* tmp = instance.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire);
    if (tmp == nullptr) {
        static std::mutex           mtx;
        std::lock_guard<std::mutex> lock(mtx);
        tmp = instance.load(std::memory_order_relaxed);
        if (tmp == nullptr) {
            tmp = new Log();
            std::atomic_thread_fence(std::memory_order_release);
            instance.store(tmp, std::memory_order_relaxed);
        }
    }
    return tmp;
}
std::shared_ptr<spdlog::logger> Log::getLogger() {
    return this->logger;
}
Log::Free::Free() {}
Log::Free::~Free() {
    Log* local_instance = instance.load(std::memory_order_relaxed);
    if (local_instance != nullptr) {
        delete local_instance;
    }
}
