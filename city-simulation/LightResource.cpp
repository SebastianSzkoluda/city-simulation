#include "LightResource.h"

LightResource::LightResource(bool isFree) {
  this->isFree = isFree;
}

void LightResource::lightGreen(){
  std::unique_lock<std::mutex> l(mutexLight);
  cvLight.wait(l, [this](){return isFree == true;});
  isFree = false;
  l.unlock();
}

void LightResource::lightRed(){
  std::unique_lock<std::mutex> l(mutexLight);
  isFree = true;
  cvLight.notify_one();
  l.unlock();
}
