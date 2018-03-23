#include <iostream>
#include <thread>

class thread_guard {
public:
    explicit thread_guard(std::thread t) :
        t_(std::move(t))
    {}

    ~thread_guard()
    {
        if (t_.joinable()) {
            t_.join();
        }
    }

    thread_guard(const thread_guard& guard) = delete;
    thread_guard& operator=(const thread_guard& guard) = delete;

private:
    std::thread t_;
};


void hello()
{
    std::cout << "Hello, Concurrent World!\n";
}

int main()
{

    std::thread t(hello);
    std::thread t2([]() {
        std::cout << "Hello from lambda!\n";
    });
    try {
        throw 0;
    } catch (...) {
        t.join();
        t2.join();
    }
    thread_guard guard(std::thread{hello});

    return 0;
}

