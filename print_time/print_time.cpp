#include <chrono>
#include <ctime>
#include <iostream>

template <typename Duration>
void print_time(tm t, Duration fraction) {
    using namespace std::chrono;
    std::printf("[%04u-%02u-%02u %02u:%02u:%02u.%03u]\n", t.tm_year + 1900,
                t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec,
                static_cast<unsigned>(fraction / milliseconds(1)));

    // VS2013's library has a bug which may require you to replace
    // "fraction / milliseconds(1)" with
    // "duration_cast<milliseconds>(fraction).count()"
}

int main(int, char**) {
    using namespace std;
    using namespace std::chrono;

    system_clock::time_point now = system_clock::now();
    system_clock::duration tp = now.time_since_epoch();

    tp -= duration_cast<seconds>(tp);

    time_t tt = system_clock::to_time_t(now);

    print_time(*gmtime(&tt), tp);
    print_time(*localtime(&tt), tp);
}
