#pragma once
#include <vector>

class YIN {
public:
  YIN();
  YIN(int sr, unsigned int min_tau, unsigned int max_tau, int ws);
  YIN(int sr, unsigned int min_tau, unsigned int max_tau, int ws,
      std::vector<long> data);

public:
  void setSR(int sr);
  void setWS(int ws);
  void setData(std::vector<long> signalData);
  void setMaxTau(unsigned int maxtau);
  void setMinTau(unsigned int mintau);
  int getSR();
  std::vector<long> getData();
  unsigned int getMinTau();
  unsigned int getMaxTau();
  int getWS();

  std::vector<double> differenceFunction(std::vector<long> *data, int W);
  std::vector<double> cumulativeMeanNormalized(std::vector<long> *data);
  std::vector<std::vector<long>> segmentData(int W);

  std::vector<std::vector<double>> getPitches();

private:
  int sampleRate;
  unsigned int min_tau;
  unsigned int max_tau;
  int windowSize;
  std::vector<long> signalData;
};