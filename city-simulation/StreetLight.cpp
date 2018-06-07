#include "StreetLight.h"
#include <thread>

StreetLight::StreetLight(int lX,int lY,LightResource* lightResource){
  this->lightX = lX;
  this->lightY = lY;
  this->lightResource = lightResource;
}

void StreetLight::startControl(){
  running = true;
  lightStateChanged = true;
  while(running){
    color = RED;
    lightStateChanged = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(rand()%100+50));
    lightResource->lightGreen();
    color = GREEN;
    lightStateChanged = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(rand()%5000+4500));
    lightResource->lightRed();
    color = RED;
    lightStateChanged = true;
  }
}

void StreetLight::stopControl(){
  running=false;
}
