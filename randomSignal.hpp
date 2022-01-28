#pragma once
#include <cmath>
#include <cstdlib>
#include <time.h>

static int x = 0;
class randomSignal {
  int hz;
  int amplitude;
public:
  randomSignal() {
    srand(time(NULL) % 1000);
    hz = rand() % (442 - 88) + 88; // 100HZ ~ 500HZ
    amplitude = rand() % 801 + 200;
  }
public:
  long operator()() {
    // printf("x value generate with: %f \n", sin(2 * M_PI / 10 * (x)));
    return amplitude * sin(2 * M_PI / hz * (x++)); // 440hz
  }
};
