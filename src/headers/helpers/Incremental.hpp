#ifndef GLAMOUR_INCREMENTAL_HPP
#define GLAMOUR_INCREMENTAL_HPP


template<typename T> class Incremental {
public:
    T value;
    Incremental(T v) : Incremental(v, 1.0f) {}
    Incremental(T v, T m): value(v), modifier(m) {}
    virtual ~Incremental() = default;
    // prefix operators
    virtual Incremental& operator++() {
        value += modifier;
        return *this;
    }
    virtual Incremental& operator--() {
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
