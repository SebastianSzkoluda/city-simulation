#ifndef STREETLIGHT_H
#define STREETLIGHT_H
#include <iostream>
#include <mutex>
#include <thread>
#include "LightResource.h"

using namespace std;
enum LightColor{
  RED, GREEN
};
class StreetLight{
private:
int lightX;
int lightY;
LightColor color;
bool running;
LightResource* lightResource;
bool lightStateChanged;

public:
  StreetLight(int lX,int lY,LightResource* lightResource);
  void stopControl();
  void startControl();
  bool getlightStateChanged(){return lightStateChanged; }
  void setlightStateChanged(bool state){lightStateChanged = state; }
  int getLightX(){return lightX; }
  int getLightY(){return lightY; }
  LightColor getLightColor(){ return color; }

};

#endif
