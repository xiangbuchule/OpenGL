#include <atomic>
#include <iostream>
#include <mutex>

#include "convert.h"

std::atomic<Convert*> Convert::instance = nullptr;
Convert::Free         Convert::free;
Convert::Convert() {
    this->convertPointer = new std::wstring_convert<std::codecvt_utf8<wchar_t>>();
};
Convert::~Convert() {
    delete convertPointer;
}
Convert* Convert::getInstance() {
    Convert* tmp = instance.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire);
    if (tmp == nullptr) {
        static std::mutex           mtx;
        std::lock_guard<std::mutex> lock(mtx);
        tmp = instance.load(std::memory_order_relaxed);
        if (tmp == nullptr) {
            tmp = new Convert();
            std::atomic_thread_fence(std::memory_order_release);
            instance.store(tmp, std::memory_order_relaxed);
        }
    }
    return tmp;
}
std::wstring_convert<std::codecvt_utf8<wchar_t>>* Convert::getConvertPointer() {
    return this->convertPointer;
}
std::string Convert::UnicodeToUTF8(unsigned int codepoint) {
    return this->convertPointer->to_bytes(codepoint);
}
std::string Convert::UnicodeToUTF8(const std::vector<unsigned int>& codepoints) {
    std::string result = "";
    if (codepoints.size() > 0) {
        for (size_t i = 0; i < codepoints.size(); i++) {
            result.append(this->convertPointer->to_bytes(codepoints[i]));
        }
    }
    return result;
}
Convert::Free::Free() {}
Convert::Free::~Free() {
    Convert* local_instance = instance.load(std::memory_order_relaxed);
    if (local_instance != nullptr) {
        delete local_instance;
    }
}
