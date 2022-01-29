#pragma once
#include <vector>

/* 
Implementation Approach:
  - Generate taus and their errors, store into vector
  - Search in the vector to Find the best tau
*/
class YIN {
public:
  YIN();
  YIN(int sr, unsigned int min_freq, unsigned int max_freq, int ws, double thrs);
  YIN(int sr, unsigned int min_freq, unsigned int max_freq, int ws, double thrs, 
      std::vector<long> data);

public:
  void setSR(int sr);
  void setWS(int ws);
  void setData(std::vector<long> signalData);
  void setMaxFreq(unsigned int maxfreq);
  void setMinFreq(unsigned int minfreq);
  void setThreshold(double thrs);
  int getSR();
  std::vector<long> getData();
  unsigned int getMinFreq();
  unsigned int getMaxFreq();
  unsigned int getMinTau();
  unsigned int getMaxTau();
  int getWS();
  double getThreshold();
  double getFreq(std::vector<double> &data, double threshold = -1);


  std::vector<double> differenceFunction(std::vector<long> &data, int W = -1);
  std::vector<double> cumulativeMeanNormalized(std::vector<double> &data);
  std::vector<std::vector<long>> segmentData(int W = -1);

  std::vector<std::vector<double>> getPitches();

  bool checkWindowSize(int ws = -1);
  void updateTaus();

private:
  int sampleRate;
  double threshold;
  unsigned int min_freq;
  unsigned int max_freq;
  unsigned int min_tau;
  unsigned int max_tau;
  int windowSize;
  std::vector<long> signalData;
};