#include "TramCrossing.h"



TramCrossing::TramCrossing(bool isFreeC, vector<vector<int>> &p) {
  isFree = isFreeC;
  tramPoints = p;
}

void TramCrossing::takeTramCrossing(){
  std::unique_lock<std::mutex> l(mutexCrossing);
  cvCrossing.wait(l, [this](){return isFree == true;});
  isFree = false;
  l.unlock();
}

void TramCrossing::releaseTramCrossing(){
  std::unique_lock<std::mutex> l(mutexCrossing);
  isFree = true;
  cvCrossing.notify_one();
  l.unlock();
}
