#ifndef HUMAN_H
#define HUMAN_H
#include "Crossing.h"
#include "Parking.h"
#include "Car.h"
#include "WalkerCrossing.h"
#include "TramCrossing.h"
#include <iostream>

using namespace std;

enum HumanDirection{
  l, r, u, d
};

class Human {
private:
  int decision;
  int humanPositionX;
  int humanPositionY;
  bool humanChangedState;
  bool streetChangedState;
  int streetSize;
  int streetStep;
  int tmpHumanX;
  int tmpHumanY;
  bool running;
  int **carTable;
  char **cityTable;
  int counter,counter1,counter2,counter3;
  HumanDirection direct;
  WalkerCrossing **walkerCrossings;
  TramCrossing** tramCrossings;

public:
  Human(int posX,int posY,int **cT,char **ciT,HumanDirection dir,WalkerCrossing **walkerCrossing,TramCrossing** tramCrossings);
  bool getHumanChangedState(){return humanChangedState;}
  void setHumanChangedState(bool p){humanChangedState = p;}
  bool getStreetChangedState(){return streetChangedState;}
  void setStreetChangedState(bool p){streetChangedState = p;}
  int getStreetSize(){ return streetSize; }
  int getStreetStep(){ return streetStep; }
  int getTmpHumanPositionX(){return tmpHumanX;}
  int getTmpHumanPositionY(){return tmpHumanY;}
  int getHumanPositionX(){return humanPositionX;}
  int getHumanPositionY(){return humanPositionY;}
  void tryToWalkThroughTramCrossing();
  void tryToWalkThroughStreet();
  void walk();
  void breakWalking();
};

#endif
