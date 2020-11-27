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
public:
    virtual std::time_t start() const { return now(); }
    virtual std::time_t now() const { return std::time(nullptr); }
};

class TenSecondClock : public Clock {
public:
    virtual std::time_t start() const { return 0; }
    virtual std::time_t now() const { return 10; }
};

class TenMinuteClock : public Clock {
public:
    virtual std::time_t start() const { return 0; }
    virtual std::time_t now() const { return 10 * 60; }
};

class ConfigurableClock : public Clock {
public:
    ConfigurableClock(std::time_t amount) : length(amount) {}
    virtual std::time_t start() const { return 0; }
    virtual std::time_t now() const { return length; }
private:
    std::time_t length;
};

class Session {
public:
    Session(const Clock& clock = TimeClock()) : clock(clock), start_time(clock.start()) {}
    void stop() { stop_time = clock.now(); }
    std::time_t seconds() { return stop_time - start_time; }
private:
    const Clock& clock;
    std::time_t start_time;
    std::time_t stop_time;
};

int main() {

    // 10-minute session
    {
        ConfigurableClock clock(10 * 60);
        Session s(clock);
        s.stop();
        assert(s.seconds() == 10 * 60);
    }

    // 2-second session
    {
        Session s;
        sleep(2);
        s.stop();
        assert(s.seconds() == 2);
    }

    // 10-second session
    {
        TenSecondClock clock;
        Session s(clock);
        s.stop();
        assert(s.seconds() == 10);
    }

    return 0;
}
