// MATH_DLL_EXPORTS macro is set in CMakeLists.txt
#include<map>
#include<iostream>
#include<mutex>
#include<string>
#include<vector>
#include<Windows.h>
#include "math_operations.h"

std::vector<int> vec = std::vector<int>(10*1024*1024);
// Global map with some initial values
std::map<int, std::string> globalMap = {{1,"dadadad"},{2,"qeqeqeqe"},{3,"fdfdfdfd"},{4,"fdfdfdfd"},{5,"xcxcxc"},{6,"nmnm"}};
// Mutex to ensure thread-safe access to the global map
std::mutex mapMutex;
std::vector<int> vec1 = std::vector<int>(1024 * 1024);
// Function to show map contents with thread safety
MATH_API int showmap(int a, int b){
    // Lock the mutex to ensure thread-safe access
    //std::lock_guard<std::mutex> lock(mapMutex);
    
    //std::cout << "Map contents (thread-safe):" << std::endl;
    //for(auto it = globalMap.begin(); it != globalMap.end(); it++)
    globalMap[a%3] = std::to_string(a) + std::to_string(b);
    //std::cout << "Key: " << a%3 << ", Value: " << globalMap[a%3] << std::endl;
    
    
    // Add the function parameters to demonstrate usage
    //globalMap[a] = b;
    //std::cout << "Added pair (" << a << ", " << b << ") to the map" << std::endl;
    
    return static_cast<int>(globalMap.size()); // Return the size of the map as a result
}


// Add function implementation
MATH_API int add(int a, int b)
{
    return a + b;
}

// Subtract function implementation
MATH_API int subtract(int a, int b)
{
    return a - b;
}

// Multiply function implementation
MATH_API int multiply(int a, int b)
{
    return a * b;
}

// Divide function implementation
MATH_API double divide(int a, int b)
{
    // Avoid division by zero
    if (b == 0)
    {
        return 0.0; // In real application, should throw exception or return error code
    }
    return static_cast<double>(a) / b;
}
MATH_API void fillvec(int a){
    for(int i=0;i<10;i++)
        vec[i] = a;
}
MATH_API void fillvec1(int a){
    for(int i=0;i<vec1.size();i++)
        vec1[i] = a;
}
BOOL WINAPI DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    switch (fdwReason) {
    case DLL_PROCESS_DETACH:
        // 释放DLL分配的全局资源
        //delete vec;
        //vec.shrink_to_fit();
        //vec1.clear();
        //vec1.shrink_to_fit();
        // 其他清理操作
        break;

        // 其他事件处理...
    case DLL_PROCESS_ATTACH:
        // 初始化逻辑
        break;
    }
    return TRUE;
}
