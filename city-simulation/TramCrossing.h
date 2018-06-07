#ifndef TRAMCROSSING_H
#define TRAMCROSSING_H
#include <mutex>
#include <condition_variable>
#include <vector>
#include <iostream>

using namespace std;

class TramCrossing{
private:
  std::mutex mutexCrossing;
  std::condition_variable cvCrossing;
  bool isFree;

public:
  vector<vector<int>> tramPoints;
  TramCrossing(bool isFreeC, vector<vector<int>> &p);

  void takeTramCrossing();
  void releaseTramCrossing();

};
#endif
