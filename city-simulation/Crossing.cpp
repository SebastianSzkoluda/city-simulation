#include "Crossing.h"



Crossing::Crossing(bool isFreeC, vector<vector<int>> &p,bool ifCrossingHaveLights) {
  isFree = isFreeC;
  crossingPoints = p;
  this->ifCrossingHaveLights = ifCrossingHaveLights;
}

void Crossing::takeCrossing(){
  std::unique_lock<std::mutex> l(mutexCrossing);
  cvCrossing.wait(l, [this](){return isFree == true;});
  isFree = false;
  l.unlock();
}

void Crossing::releaseCrossing(){
  std::unique_lock<std::mutex> l(mutexCrossing);
  isFree = true;
  cvCrossing.notify_one();
  l.unlock();
}
