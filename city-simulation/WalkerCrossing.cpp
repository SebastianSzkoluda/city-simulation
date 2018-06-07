#include "WalkerCrossing.h"



WalkerCrossing::WalkerCrossing(bool isFreeC, vector<vector<int>> &p) {
  isFree = isFreeC;
  wDPoints = p;
}

void WalkerCrossing::takeWalkerCrossing(){
  std::unique_lock<std::mutex> l(mutexCrossing);
  cvCrossing.wait(l, [this](){return isFree == true;});
  isFree = false;
  l.unlock();
}

void WalkerCrossing::releaseWalkerCrossing(){
  std::unique_lock<std::mutex> l(mutexCrossing);
  isFree = true;
  cvCrossing.notify_one();
  l.unlock();
}
