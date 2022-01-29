#include "yin.hpp"
#include "randomSignal.hpp"
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <vector>

YIN::YIN() {
  puts("Default YIN alg constructor");
  sampleRate = 44100;
  threshold = 0.3;
  min_freq = 100;
  max_freq = 500;
  int seconds = 10;
  updateTaus();
  int ws = 0;
  puts("Please enter a window size");
  while (!(std::cin >> ws) || !checkWindowSize(ws) || ws > sampleRate * seconds) {
    puts("Please enter a valid integer!");
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  windowSize = ws;
  
  signalData.resize(sampleRate * seconds); // Default: 10s
  std::generate(signalData.begin(), signalData.end(), randomSignal());
  std::cout << "SignalData's size: " << signalData.size() << std::endl;
  std::cout << "Time: " << seconds << "s" << std::endl;
}

YIN::YIN(int sr, unsigned int min_f0, unsigned int max_f0, int ws, double thrs)
    : sampleRate(sr), min_freq(min_f0), max_freq(max_f0), windowSize(ws),
      threshold(thrs) {
  updateTaus();
}

YIN::YIN(int sr, unsigned int min_f0, unsigned int max_f0, int ws, double thrs,
         std::vector<long> data)
    : sampleRate(sr), min_freq(min_f0), max_freq(max_f0), windowSize(ws),
      threshold(thrs), signalData(data) {
  updateTaus();
}

void YIN::setSR(int sr) { sampleRate = sr; }
void YIN::setWS(int ws) { windowSize = ws; }
void YIN::setThreshold(double thrs) { threshold = thrs; }
void YIN::setData(std::vector<long> signalData) {
  this->signalData = signalData;
}
void YIN::setMaxFreq(unsigned int maxfreq) { this->max_freq = maxfreq; }
void YIN::setMinFreq(unsigned int minfreq) { this->min_freq = minfreq; }

void YIN::updateTaus() {
  min_tau = sampleRate / max_freq;
  max_tau = sampleRate / min_freq;
}

int YIN::getSR() { return sampleRate; }
std::vector<long> YIN::getData() { return signalData; }
unsigned int YIN::getMinFreq() { return min_freq; }
unsigned int YIN::getMaxFreq() { return max_freq; }
unsigned int YIN::getMinTau() { return min_tau; }
unsigned int YIN::getMaxTau() { return max_tau; }
int YIN::getWS() { return windowSize; }
double YIN::getThreshold() { return threshold; }

// Data processing
std::vector<std::vector<long>> YIN::segmentData(int W) {
  /*
  param:
    W: window size
      default: windowSize
  */
  int ws = windowSize;
  if (W > 0) {
    ws = W;
  }
  printf("[INFO]========Checking with window size %i\n", ws);
  std::vector<long> buff;
  std::vector<std::vector<long>> windows;

  std::vector<long>::iterator from = signalData.begin();
  while (signalData.end() != from &
         from + ws <= signalData.end()) { // Omit last bit of "residuals"
    buff.assign(from, from + ws);
    windows.push_back(buff);
    buff.clear();
    from += ws;
  }

  return windows;
}

std::vector<double> YIN::differenceFunction(std::vector<long> &data, int W) {
  /*
  Params:
    - data: windowed signal data (with window size = this->windowSize)
    - int W: window size, or len of data
        default W = -1 (-> using this->windowSize)
  Returns:
    difference values for taus [min_tau ~ max_tau]
    note: differences[k], k != tau, k = tau - min_tau, differences[tau_to_access
  - min_tau] = difference(tau_to_access) note: len(differences) = max_tau -
  min_tau
  */
  puts("=====Difference Function Outputs======");
  int window = windowSize;
  if (W > 0) {
    window = W;
  }
  // Check data & window length
  int dataSize = data.size();
  std::cout << "maxtau: " << max_tau * 2 << std::endl;
  std::cout << "dataSize: " << dataSize << std::endl;
  assert(max_tau * 2 <
         dataSize);           // Must be 2 * F0 fundamental frequency to work
                              // @TODO: Improvement here
  assert(window <= dataSize); // window size cannot be bigger than data len!!

  std::vector<double> differences;
  // differences.push_back(0); // tau = 0 case // no such case

  /// $   d_t(\tau) = sum_{j=1}^{W}(x_j - x_{j+r})^2   $
  for (int tau = min_tau; tau <= max_tau; tau++) { // Sum each tau
    long difference = 0; // Big Sum value, store into this variable
    for (int j = 1; j < window - tau; j++) { // Sum each j
      long diff = data[j] - data[j + tau];
      difference += diff * diff;
    }
    differences.push_back(difference);
  }
  return differences;
}

std::vector<double> YIN::cumulativeMeanNormalized(std::vector<double> &dfData) {
  /*
  Param:
    dfData: differenceFunction result
  Return:
    d't(tau) differences

  Implementation: search in range [min_tau, max_tau] (no tau=0 case)
    sizeof(cumdiffs) = max_tau - min_tau
  */
  std::vector<double> cumdiffs;
  std::vector<double> cumsumData;
  double temp;
  puts("================Test cumsumData============");
  for (int i = 0; i < dfData.size(); i++) {
    temp += dfData[i];
    cumsumData.push_back(temp);
    std::cout << temp << " ";
  }
  puts("\n========================================\n");
  

  /*
    d't(r) = {   dt(r) / (1/(r+1)) sum_{j=min_tau} (dj)          }
  */
  for (int i = 0; i < dfData.size(); i++) {
    double diff = dfData[i] / ( (1.0 / (i + 1)) * cumsumData[i] ); 
    cumdiffs.push_back(diff);
  }
  return cumdiffs;
}

std::vector<std::vector<double>> YIN::getPitches() {
  ;
  return {};
}

double YIN::getFreq(std::vector<double> &data, double threshold){
  if (threshold > 0){
    puts("******[getFreq with threshold] Under Construction******");
    return 0;
  }
  auto mx = std::min_element(data.begin(), data.end());
  int tau_final = mx - data.begin();
  double freq = (double) sampleRate / (double) (tau_final + min_tau);
  printf("\x1B[1;31m Best F0 Estimate: %f\033[0m\n", freq);
  return freq;
}

bool YIN::checkWindowSize(int ws) {
  /* Check if a valid window size
  Params:
    ws: default -1,
    returns: bool -> is it okay to use this ws?
  */
  int window = windowSize;
  if (ws > -1) {
    window = ws;
  }
  puts("[INFO]========Checking window size");
  std::cout << "Min freq: " << min_freq << "\nMax tau: " << max_tau
            << "\nWindow Size: " << window << std::endl;
  bool check = ((max_tau + 1) * 2) < window; // take ceiling
  if (!check) {
    puts("[ERROR]========Your window size is too small!");
    std::cout << "Suggested window size: ws >" << (max_tau + 1) * 2
              << std::endl;
  }
  return check;
}