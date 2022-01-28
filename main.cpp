#include "yin.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>

#define audio                                                                  \
  "/Users/bmois/Documents/GitHub/YIN_Algorithm_Cpp_Implementation/"            \
  "clarinet.wav"

void test01() {
  YIN yy;
  auto test = yy.getData();
  std::cout << "TEST SIZE: " << test.size() << std::endl;
  puts("Data sample: ");
  for (int i = 0; i < test.size() / 5000; i ++) {
    std::cout << test[i] << " ";
    if (i % yy.getMaxTau() == 0) {
      puts("\n\n=============\n");
    }
  }
  system("read -n 1 -s -p \"Press any key to continue...\"");
  system("clear");
  
}

int main() { 
  test01();
}