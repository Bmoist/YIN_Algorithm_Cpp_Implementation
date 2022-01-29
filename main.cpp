#include "yin.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>
#include <functional>

#define audio                                                                  \
  "/Users/bmois/Documents/GitHub/YIN_Algorithm_Cpp_Implementation/"            \
  "clarinet.wav"

template <class T> void printVector(std::vector<T> &vector) {
  for (typename std::vector<T>::iterator it = vector.begin();
       it != vector.end(); it++) {
    if(it - vector.begin() > 500){
      std::cout << "\\n*** Omitting " << vector.end() - it << " more entries..\n";
      puts("\n========End of printVector Output========");
      return;
    }
    std::cout << *it << " ";
  }
  puts("\n========End of printVector Output========");

}

void test01() {
  YIN yy;
  auto test = yy.getData();
  // puts("\n\nData sample: \n============");
  // for (int i = 0; i < yy.getWS(); i++) {
  //   std::cout << test[i] << " ";
  // }
  puts("\n\n=============\n");
  system("read -n 1 -s -p \"Press any key to continue...\"");
  system("clear");

  // Segment Data test
  auto data = yy.segmentData();
  std::cout << "How many windows ? <-" << data.size() << std::endl;
  puts("\n======Window sample======");
  printVector(data[0]);

  system("read -n 1 -s -p \"Press any key to continue...\"");
  system("clear");

  // Difference function test
  auto myDF = yy.differenceFunction(data[0]);
  printVector(myDF);
  puts("\n========================================");

  yy.getFreq(myDF);
  puts("========================================");
  system("read -n 1 -s -p \"Press any key to continue...\"");
  system("clear");

  // Cumulative Mean Normalized DF test
  auto cumcum = yy.cumulativeMeanNormalized(myDF);
  printVector(cumcum);
  yy.getFreq(cumcum);
  puts("========================================");

}

int main() { test01(); }