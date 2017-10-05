#ifndef GLAMOUR_TIMER_HPP
#define GLAMOUR_TIMER_HPP

#include "includes.hpp"

class Timer {
public:
    explicit Timer(const std::string& name): timerName(name) {
        glGenQueries(2, queryIds);
    }

    void begin() {
        glBeginQuery(GL_TIME_ELAPSED, queryIds[back]);
    }

    GLuint64 end() {
        glEndQuery(GL_TIME_ELAPSED);
        glGetQueryObjectui64v(queryIds[front], GL_QUERY_RESULT, &elapsedTime);

        totalTicks++;

        double msTime = elapsedTime / 1000000.0f; // get in ms

        if (totalTicks > 1) {
            maxTime = maxTime < msTime ? msTime : maxTime;
            minTime = minTime > msTime ? msTime : minTime;
            meanTime += (msTime - meanTime) / (totalTicks + 1); // Cumulative Moving Average
        }

        if (totalTicks % 30 == 0) {
            std::cout << "'" << timerName << "': " << msTime << "ms" << std::endl;
        }

        // swap queries
        front = back;
        back = ++back %2;

        return elapsedTime;
    }

    ~Timer() {
        std::cout << "=========================================================" << std::endl;
        std::cout << "Timer info for '" << timerName << "'" << std::endl << std::endl;
        std::cout << "Max time for single frame draw: " << maxTime << "ms" << std::endl;
        std::cout << "Min time for single frame draw: " << minTime << "ms" << std::endl;
        std::cout << "Mean time for " << totalTicks << " frames: " << meanTime << "ms" << std::endl;
        std::cout << "=========================================================" << std::endl;
    }

private:
    std::string timerName;
    GLuint queryIds[2];
    int front = 0, back = 1;

    GLuint64 elapsedTime = 0;
    double maxTime = 0;
    double minTime = 9223372036854775807; // max GLuint64
    double meanTime = 0;
    GLuint64 totalTicks = 0;
};


#endif //GLAMOUR_TIMER_HPP
