#ifndef WALKERCROSSING_H
#define WALKERCROSSING_H
#include <mutex>
#include <condition_variable>
#include <vector>
#include <iostream>

using namespace std;

class WalkerCrossing{
private:
  std::mutex mutexCrossing;
  std::condition_variable cvCrossing;
  bool isFree;

public:
  vector<vector<int>> wDPoints;
  WalkerCrossing(bool isFreeC, vector<vector<int>> &p);

  void takeWalkerCrossing();
  void releaseWalkerCrossing();

};
#endif
