#pragma once
#include <cstdint>

typedef std::uint16_t pw_t;

class PointWell {
public:

    //constructors
    PointWell() {Current = 1; Max = 1;}
    explicit PointWell(pw_t m, pw_t c) {
        Current = c;
        Max = m;
        if (Current > Max) Current = Max;
    }


    // returns true if set successfully
    bool setMax(pw_t new_max) {
        if (new_max == 0)
            return false;
        
        Max = new_max;

        if (Current > Max) Current = Max;

        return true;
    }

    void decrease(pw_t amt) {
        if (amt > Current) {
            Current = 0;
            return;
        }

        Current -= amt;
    }

    void increase(pw_t amt) {
        if (amt + Current > Max) {
            Current = Max;
            return;
        }

        Current += amt;
    }

    void restore() { Current = Max; }

    pw_t getMax() { return Max; }

    pw_t getCurrent() { return Current; }

private:
    pw_t Current;
    pw_t Max;

};