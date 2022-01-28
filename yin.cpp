#include "yin.hpp"
#include "randomSignal.hpp"
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <vector>

YIN::YIN() {
  puts("Default YIN alg constructor");
  sampleRate = 44100;
  min_tau = 100;
  max_tau = 500;
  int ws;
  puts("Please enter a window size");
  while (!(std::cin >> ws)) {
    puts("Please enter a valid integer!");
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  windowSize = ws;
  signalData.resize(sampleRate * 10);
  std::generate(signalData.begin(), signalData.end(), randomSignal());
  std::cout << "SignalData's size: " << signalData.size() << std::endl;
}

YIN::YIN(int sr, unsigned int min_tau, unsigned int max_tau, int ws)
    : sampleRate(sr), min_tau(min_tau), max_tau(max_tau), windowSize(ws) {}

YIN::YIN(int sr, unsigned int min_tau, unsigned int max_tau, int ws,
         std::vector<long> data)
    : sampleRate(sr), min_tau(min_tau), max_tau(max_tau), windowSize(ws),
      signalData(data) {}

void YIN::setSR(int sr) { sampleRate = sr; }
void YIN::setWS(int ws) { windowSize = ws; }
void YIN::setData(std::vector<long> signalData) {
  this->signalData = signalData;
}
void YIN::setMaxTau(unsigned int maxtau) { this->max_tau = maxtau; }

void YIN::setMinTau(unsigned int mintau) { this->min_tau = mintau; }

int YIN::getSR() { return sampleRate; }
std::vector<long> YIN::getData() { return signalData; };
unsigned int YIN::getMinTau() { return min_tau; }
unsigned int YIN::getMaxTau() { return max_tau; }
int YIN::getWS() { return windowSize; }

std::vector<double> YIN::differenceFunction(std::vector<long> *data,
                                            int W = -1) {
  /*
  Params:
    - data: windowed signal data (with window size = this->windowSize)
    - int W: window size, or len of data
        default W = -1 (-> using this->windowSize)
  Returns:
    difference values for tau [0 ~ max_tau]
  */
  int window = windowSize;
  if (W > 0) {
    window = W;
  }
  // Check data & window length
  int dataSize = data->size();
  assert(max_tau * 2 > dataSize); // Must be 2 * F0 fundamental frequency to work
                                  // @TODO: Improvement here
  assert(window < dataSize); // data[window]


  std::vector<int> taus;
  std::vector<double> differences;
  differences.push_back(0);            // tau = 0 case
  for (int i = 0; i <= max_tau; i++) { // Any better way of doing this?
    taus.push_back(i);
  }

  /// $   d_t(\tau) = sum_{j=1}^{W}(x_j - x_{j+r})^2   $
  for (int i = 1; i < taus.size(); i++) { // Sum each tau
    int tau = taus[i];
    long difference = 0;
    for (int j = 1; j < window - tau; j++) { // Sum each j
      long diff = (*data)[j] - (*data)[j + tau];
      difference += diff * diff;
    }
    differences.push_back(difference);
  }
  return differences;
}

std::vector<double> YIN::cumulativeMeanNormalized(std::vector<long> *data) {
  ;
  return {};
}

std::vector<std::vector<long>> YIN::segmentData(int W = -1) {
  /*
  param:
    W: window size
      default: windowSize
  */
  int ws = windowSize;
  if (W > 0) {
    ws = W;
  }
  std::vector<long> buff;
  std::vector<long>::iterator from = signalData.begin();
  while(signalData.end() != from & from + ws <= signalData.end()){ // Omit last bit of "residuals"
    buff.assign(from, from + ws);
    from += ws;
  }


  return {};
}

std::vector<std::vector<double>> YIN::getPitches() {
  ;
  return {};
}
