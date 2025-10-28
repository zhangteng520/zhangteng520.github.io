// main.cpp - 主程序，多线程延迟加载动态库
#include <iostream>
#include <thread>
#include <vector>
#include <dlfcn.h> // 用于动态加载库

// 线程函数：加载动态库并调用其函数
void thread_func() {
    // 延迟加载动态库
    void* handle = dlopen("./libmylib.so", RTLD_LAZY);
    if (!handle) {
        std::cerr << "dlopen error: " << dlerror() << std::endl;
        return;
    }

    // 获取库函数地址
    typedef void (*lib_func)();
    lib_func func = (lib_func)dlsym(handle, "library_function");
    if (!func) {
        std::cerr << "dlsym error: " << dlerror() << std::endl;
        dlclose(handle);
        return;
    }

    // 调用库函数
    func();

    // 关闭库句柄（实际应用中可能不会立即关闭）
    dlclose(handle);
}

int main() {
    std::cout << "Main thread starting..." << std::endl;

    // 创建多个线程同时加载动态库
    std::vector<std::thread>vec;
    for(int i = 0 ; i < 10;i++){
        vec.push_back(std::thread(thread_func));
    }

    for(auto&i:vec){
        i.join();
    }

    std::cout << "Main thread exiting..." << std::endl;
    return 0;
}
