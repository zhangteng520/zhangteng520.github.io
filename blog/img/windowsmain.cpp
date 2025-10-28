#include <iostream>
#include <Windows.h>
#include <thread>
#include <chrono>
#include <vector>

// Define function pointer types
typedef int (*AddFunc)(int, int);
typedef int (*SubtractFunc)(int, int);
typedef int (*MultiplyFunc)(int, int);
typedef double (*DivideFunc)(int, int);
typedef int (*ShowMapFunc)(int, int);
typedef int (*VecFun)(int);
typedef int (*VecFun1)(int);
// Function to load DLL and get function addresses
void ThreadFun(int a) {
    // Load DLL inside the thread
    HMODULE hDll = LoadLibrary(TEXT("math_operations.dll"));
    VecFun showMapFunc = (VecFun)GetProcAddress(hDll, "fillvec");
	int result = showMapFunc(a);
    FreeLibrary(hDll);
}
void ThreadFun1(int a) {
    // Load DLL inside the thread
    HMODULE hDll = LoadLibrary(TEXT("math_operations.dll"));
    VecFun1 showMapFunc = (VecFun1)GetProcAddress(hDll, "fillvec1");
    int result = showMapFunc(a);
    FreeLibrary(hDll);
}
// Thread function that calls showmap with delay
void threadFunction(int threadId, int delayMs, int a, int b) {
    // Wait for the specified delay
    //std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    
    // Load DLL inside the thread
    HMODULE hDll = LoadLibrary(TEXT("math_operations.dll"));
    
    if (hDll != NULL) {
        // Get the function address
        ShowMapFunc showMapFunc = (ShowMapFunc)GetProcAddress(hDll, "showmap");
    
    if (showMapFunc != NULL) {
        std::cout << "Thread " << threadId << " (delay: " << delayMs << "ms) calling showmap(" << a << ", " << b << ")" << std::endl;
        int result = showMapFunc(a, b);
        std::cout << "Thread " << threadId << " showmap returned: " << result << std::endl;
        } else {
            std::cout << "Thread " << threadId << " failed to get showmap function address" << std::endl;
        }
        
        // Free the DLL after use
        FreeLibrary(hDll);
    } else {
        DWORD errorCode = GetLastError();
        std::cout << "Thread " << threadId << " failed to load DLL. Error code: " << errorCode << std::endl;
    }
}

int main() {
    int a = 10, b = 5;
    
    std::cout << "Dynamic DLL Loading (Late Binding) Example:" << std::endl;
    std::cout << "a = " << a << ", b = " << b << std::endl;
    
    // Create multiple threads to call showmap with different delays
    std::cout << "\nCreating multiple threads to call showmap with different delays..." << std::endl;
    
    for(int i = 0 ; i< 1;i++){
    std::vector<std::thread> threads;
    //threads.push_back(std::thread(ThreadFun1, 1));
    threads.push_back(std::thread(ThreadFun, 1));
        // Thread 3: 1000ms delay, add pair (30, 40)
    //threads.push_back(std::thread(threadFunction, 3, 1000, 1, 40));
    // Thread 1: No delay, add pair (10, 20)
    //threads.push_back(std::thread(threadFunction, 1, 0, 3, 20));
    
    // Thread 2: 500ms delay, add pair (20, 30)
    //threads.push_back(std::thread(threadFunction, 2, 500, 2, 30));
    

    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}
	Sleep(60000);
    std::cout << "\nAll threads have completed their execution." << std::endl;
    
    return 0;
}