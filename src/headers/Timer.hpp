#ifndef GLAMOUR_TIMER_HPP
#define GLAMOUR_TIMER_HPP

#include <queue>
#include "includes.hpp"

class Timer {
public:
    explicit Timer(const std::string& name): timerName(name) {
//        glGenQueries(2, queryIds);
    }

    void begin() {
        GLuint queryId;
        glGenQueries(1, &queryId);
        queries.push(queryId);
        glBeginQuery(GL_TIME_ELAPSED, queryId);
    }

    GLuint64 end() {
        glEndQuery(GL_TIME_ELAPSED);

        GLuint64 isAvailable;
        GLuint queryId = queries.front();
        glGetQueryObjectui64v(queryId, GL_QUERY_RESULT_AVAILABLE, &isAvailable);

        if (isAvailable != 0) {
//            std::cout << "AVAILABLEEEE" << std::endl;

            queries.pop();
            glGetQueryObjectui64v(queryId, GL_QUERY_RESULT, &elapsedTime);

            totalTicks++;

            double msTime = elapsedTime / 1000000.0f; // get in ms

            if (totalTicks > 1) {
                maxTime = maxTime < msTime ? msTime : maxTime;
                minTime = minTime > msTime ? msTime : minTime;
                meanTime += (msTime - meanTime) / (totalTicks + 1); // Cumulative Moving Average
            }

//            if (totalTicks % 30 == 0) {
//                std::cout << "'" << timerName << "': " << msTime << "ms" << std::endl;
//            }

        } else {
//            std::cout << "Nope..." << std::endl;
        }



//        // swap queries
//        front = back;
//        back = ++back %2;

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
//    GLuint queryIds[2];
    std::queue<GLuint> queries;
//    int front = 0, back = 1;

    GLuint64 elapsedTime = 0;
    double maxTime = 0;
    double minTime = 9223372036854775807; // max GLuint64
    double meanTime = 0;
    GLuint64 totalTicks = 0;
};


#endif //GLAMOUR_TIMER_HPP
