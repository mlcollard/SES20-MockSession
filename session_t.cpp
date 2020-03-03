/*
    session_t.cpp

    Test the class Session
*/

#include <cassert>
#include <unistd.h>
#include <chrono>

class Clock {
public:
    virtual std::time_t start() const = 0;
    virtual std::time_t now() const = 0;
};

class TimeClock : public Clock {
    virtual std::time_t start() const { return now(); }
    virtual std::time_t now() const { return std::time(nullptr); }
};

class Session {
public:
    Session() : start_time(std::chrono::system_clock::now()) {}
    void stop() { stop_time = std::chrono::system_clock::now(); }
    int seconds() { return std::chrono::duration_cast<std::chrono::seconds>(stop_time - start_time).count(); }
private:
    std::chrono::system_clock::time_point start_time;
    std::chrono::system_clock::time_point stop_time;
};

int main() {

    // 2-second session
    {
        Session s;
        sleep(2);
        s.stop();
        assert(s.seconds() == 2);
    }

    // 10-second session
    {
        Session s;
        sleep(10);
        s.stop();
        assert(s.seconds() == 10);
    }

    return 0;
}
