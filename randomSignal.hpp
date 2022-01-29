#pragma once
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <iostream>

static int x = 0;
class randomSignal {
  int hz;
  int amplitude;
public:
  randomSignal() {
    srand(time(NULL) % 1000);
    hz = rand() % (442 - 88) + 88; // 100HZ ~ 500HZ
    printf("\n[INFO]========Random Signal hz is:\x1B[1;31m%i\033[0m\n", hz);
    amplitude = rand() % 801 + 200;
  }
public:
  long operator()(int sampleRate = 44100) {
    int tau = sampleRate / hz;
    // printf("x value generate with: %f \n", sin(2 * M_PI / 10 * (x)));
    // return amplitude * sin(2 * M_PI / hz * (x++)); // x is hz cycle
    return amplitude * sin(2 * M_PI / tau * (x++)); // x is tau cycle
  }
};
