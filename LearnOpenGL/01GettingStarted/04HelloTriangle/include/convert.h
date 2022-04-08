#ifndef __CONVERT_H__
#define __CONVERT_H__

#include <atomic>
#include <codecvt>
#include <locale>
#include <string>
#include <vector>

/**
 * 单例unicode码转utf8对象
 * 支持多线程
 * https://blog.csdn.net/hongxingabc/article/details/82846396
 */
class Convert {
  private:
    // 实例指针对象
    static std::atomic<Convert*> instance;
    // unicode和utf-8转换对象
    std::wstring_convert<std::codecvt_utf8<wchar_t>>* convertPointer;
    // 构造析构
    Convert();
    ~Convert();
    // 用来析构的类
    class Free {
      public:
        Free();
        ~Free();
    };
    static Free free;
    // 去掉各种默认方法
    Convert(const Convert&) = delete;
    Convert(Convert&&)      = delete;
    Convert& operator=(const Convert&) = delete;
    Convert& operator=(Convert&&) = delete;

  public:
    // 获取实例
    static Convert* getInstance();
    // 获取代码转换的实例
    std::wstring_convert<std::codecvt_utf8<wchar_t>>* getConvertPointer();
    // unicode码转utf-8
    std::string UnicodeToUTF8(unsigned int codepoint);
    // unicode码数组转utf-8字符串
    std::string UnicodeToUTF8(const std::vector<unsigned int>& codepoints);
};

// 定义宏，方便使用
#define unicodeToUTF8(codepoints) Convert::getInstance()->UnicodeToUTF8(codepoints)

#endif
