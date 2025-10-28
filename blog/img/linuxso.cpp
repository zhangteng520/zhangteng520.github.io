// mylib.cpp - 动态库实现
#include <iostream>
#include <thread>
#include <atomic>

// 全局计数器，用于演示线程不安全问题
static std::atomic<int> counter(0);

// 初始化函数，会在库加载时执行
__attribute__((constructor)) 
static void init() {
    // 模拟一个非线程安全的初始化过程
    std::cout << "Library initializing... Thread ID: " 
              << std::this_thread::get_id() << std::endl;
    
    // 这里模拟一些需要互斥的初始化操作
    int temp = counter.load();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 增加并发冲突概率
    counter.store(temp + 1);
    
    std::cout << "Library initialized. Counter: " << counter << std::endl;
}

// 库提供的函数
extern "C" {
    void library_function() {
    std::cout << "Calling library function. Counter value: " << counter << std::endl;
    }
}
