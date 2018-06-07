#ifndef TRAM_H
#define TRAM_H
#include "TramCrossing.h"
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

class Tram {
private:
int tramX;
int tramY;
int tmpTramX;
int tmpTramY;
bool tramStateChanged;
bool running;
char **cityTable;
int **carTable;
TramCrossing** tramCrossings;

public:
  Tram(int tramX,int tramY,char **cityTable,int **carTable,TramCrossing** tramCrossings);
  int getTramX(){return tramX;}
  int getTramY(){return tramY;}
  int getTmpTramX(){return tmpTramX;}
  int getTmpTramY(){return tmpTramY;}
  bool getTramStateChanged(){ return tramStateChanged; }
  void setTramStateChanged(bool state){ tramStateChanged = state; }
  void tryToDrive();
  void breakDriving();
  void startDriveThroughCity();
};

#endif
