#include <iostream>
#include <thread>
#include <string>

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

void cout_word(const std::string& word)
{
    std::cout << word << std::endl;
}

int main()
{

    std::thread t(hello);
    std::thread t2([]() {
        std::cout << "Hello from lambda!\n";
    });
    std::thread t3(cout_word, "the best words");
    try {
        throw 0;
    } catch (...) {
        t.join();
        t2.join();
    }
    thread_guard guard(std::thread{hello});
    t3.join();

    return 0;
}

