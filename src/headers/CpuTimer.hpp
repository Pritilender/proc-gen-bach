#ifndef GLITTERING_GLAMOUR_CPUTIMER_HPP
#define GLITTERING_GLAMOUR_CPUTIMER_HPP

#include <string>
#include <chrono>
#include <iostream>

class CpuTimer {
public:
    explicit CpuTimer(const std::string& name): name(name) {}
    ~CpuTimer() {
        std::cout << "=========================================================" << std::endl;
        std::cout << "Timer info for '" << name << "'" << std::endl << std::endl;
        std::cout << "Max time for single frame draw: " << maxTime << "ms" << std::endl;
        std::cout << "Min time for single frame draw: " << minTime << "ms" << std::endl;
        std::cout << "Mean time for " << ticks << " frames: " << meanTime << "ms" << std::endl;
        std::cout << "Last time " << lastTime << "ms" << std::endl;
        std::cout << "=========================================================" << std::endl;
    }
    void start() {
        begin = std::chrono::high_resolution_clock::now();
    };
    void stop() {
        end = std::chrono::high_resolution_clock::now();
        ticks++;

        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

        if (ticks > 1) {
            maxTime = maxTime < time ? time : maxTime;
            minTime = minTime > time ? time: minTime;
            meanTime += (time - meanTime) / (ticks + 1);
        } else {
            lastTime = time;
        }
    };

private:
    std::chrono::high_resolution_clock::time_point begin;
    std::chrono::high_resolution_clock::time_point end;
    std::string name;
    long long int maxTime = 0;
    long long int minTime = 9223372036854775807;
    double meanTime = 0;
    long long int lastTime = 0;
    long long int ticks = 0;
};


#endif //GLITTERING_GLAMOUR_CPUTIMER_HPP
