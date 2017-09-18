#ifndef GLAMOUR_INCREMENTAL_HPP
#define GLAMOUR_INCREMENTAL_HPP


template<class T> class Incremental {
public:
    T value;
    Incremental(T v) : Incremental(v, 1.0f) {}
    Incremental(T v, T m): value(v), modifier(m) {}
    // prefix operators
    Incremental& operator++() {
        value += modifier;
        return *this;
    }
    Incremental& operator--() {
        value -= modifier;
        return *this;
    }
    operator T() const {
        return value;
    }
private:
    T modifier;
};


#endif //GLAMOUR_INCREMENTAL_HPP
