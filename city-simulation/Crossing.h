#ifndef CROSSING_H
#define CROSSING_H
#include <mutex>
#include <condition_variable>
#include <vector>
#include <iostream>

using namespace std;

class Crossing{
private:
  std::mutex mutexCrossing;
  std::condition_variable cvCrossing;
  bool isFree;
  bool ifCrossingHaveLights;

public:
  vector<vector<int>> crossingPoints;
  Crossing(bool isFreeC, vector<vector<int>> &p,bool ifCrossingHaveLights);
  bool getIfCrossingHaveLights(){return ifCrossingHaveLights; }
  void takeCrossing();
  void releaseCrossing();

};
#endif
