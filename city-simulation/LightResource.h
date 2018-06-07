#ifndef LIGHTRESOURCE_H
#define LIGHTRESOURCE_H
#include <mutex>
#include <condition_variable>
#include <iostream>

using namespace std;

class LightResource{
private:
  std::mutex mutexLight;
  std::condition_variable cvLight;
  bool isFree;

public:
  LightResource(bool isFree);

  void lightGreen();
  void lightRed();

};
#endif
