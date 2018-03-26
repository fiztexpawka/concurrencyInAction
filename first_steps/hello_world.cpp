#include <iostream>
#include <thread>
#include <string>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>

class thread_guard {
public:
    explicit thread_guard(std::thread t) :
        t_(std::move(t))
    {
        if (!t_.joinable()) {
            throw std::logic_error("You have no logic to pass this");
        }
    }

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

std::atomic<bool> badCommunicator = {false};

template<class T>
void async_generate_sequence(std::vector<T>& data)
{
    const std::ptrdiff_t size = 1000;
    data.resize(size, T());
    std::iota(std::begin(data), std::end(data), 10);
    badCommunicator = true;
}

template<class T>
void async_sort(std::vector<T>& data)
{
    while (!badCommunicator) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    std::sort(std::begin(data), std::end(data), std::greater<T>());
}

// Strange struct :)
struct SomeData {
    SomeData(int initialValue = 42);

    void operator() ()
    {
        std::cout << curValue_ << std::endl;
    }

    int curValue_;
};

SomeData::SomeData(const int initialValue) :
    curValue_(initialValue)
{}

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

    std::vector<int> data;
    thread_guard generator{std::thread{async_generate_sequence<int>, std::ref(data)}};
    std::thread sorter_thread{async_sort<int>, std::ref(data)};
    thread_guard write_magic{std::thread(SomeData(45))};
    sorter_thread.join();
    std::cout << "size: " << data.size() << " is sorted: " <<
        (std::is_sorted(std::begin(data), std::end(data), std::greater<int>()) ? "True\n" : "False\n");

    return 0;
}

