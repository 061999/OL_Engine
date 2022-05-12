#include "Timer.h"

Timer::Timer():
    start(std::chrono::steady_clock::now()),
    last(std::chrono::steady_clock::now())
{}

float Timer::Duration()
{
    auto temp = std::chrono::steady_clock::now();
    std::chrono::duration<float> delta(temp - start);
    return delta.count();
}

float Timer::Delta()
{
    auto temp = std::chrono::steady_clock::now();
    std::chrono::duration<float> delta(temp - last);
    last = temp;
    return delta.count();
}
