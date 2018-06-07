#ifndef CAR_H
#define CAR_H
#include "StreetLight.h"
#include "Crossing.h"
#include "Parking.h"
#include "WalkerCrossing.h"
#include "TramCrossing.h"
#include <iostream>


using namespace std;

enum Direction{
  LEFT, RIGHT, UP, DOWN
};

class Car {
public:
  bool changed;
  bool parkingStateChanged;
  bool releaseParkingState;
  bool running;
  int positionX;
  int positionY;
  int tmpX;
  int tmpY;
  int color;
  int decision;
  int tmpParkingX;
  Crossing **crossings;
  Parking *parking;
  WalkerCrossing **walkerCrossings;
  int **carTable;
  char **cityTable;
  Direction state;
  TramCrossing** tramCrossings;
  StreetLight** lights;


  Car(int startPositionX, int startPositionY, Direction startState,int carColor,Crossing **crossing,Parking *park,int **cT,char **ciT,WalkerCrossing **walkerCrossing,TramCrossing** tramCrossingx,StreetLight** lightx);

  int getParkingStateChanged(){ return parkingStateChanged; }
  int getDecision(){ return decision; }
  int getColor(){ return color; }
  int getPositionX(){ return positionX; }
  int getPositionY(){ return positionY; }
  bool getChanged(){ return changed; }
  void setChanged(bool chan){ changed = chan; }

  void changeDirectionRandomly();
  void tryToTakeParkingPlace();
  void tryToDriveThroughCrossing();
  void tryToDriveThroughTramCrossing();
  void tryToDriveThroughWalkerCrossing();
  void tryToDriveThroughCrossingWithLights();
  void drive();
  void breakRunning();
};

#endif // CAR_H
