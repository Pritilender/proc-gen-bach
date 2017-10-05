#ifndef GLAMOUR_RANGEINCREMENTAL_HPP
#define GLAMOUR_RANGEINCREMENTAL_HPP


#include "Incremental.hpp"

template<typename T> class RangeIncremental {
public:
    RangeIncremental(T v, T from, T to) : inc(v), from(from), to(to) {}
    RangeIncremental(T v, T from, T to, T m) : inc(v, m), from(from), to(to) {}
    RangeIncremental &operator++() {
        ++inc;
        if (inc > to) {
            inc.value = to;
        }
        return *this;
    }
    RangeIncremental &operator--() {
        --inc;
        if (inc < from) {
            inc.value = from;
        }
        return *this;
    }
    operator T() const {
        return inc;
    }

private:
    Incremental<T> inc;
    T from;
    T to;
};


#endif //GLAMOUR_RANGEINCREMENTAL_HPP
