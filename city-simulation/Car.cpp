#include "Car.h"
#include <time.h>
#include <thread>
#include <chrono>

Car::Car(int startPositionX, int startPositionY, Direction startState,int carColor,Crossing **crossing,Parking *park,int **cT,char **ciT,WalkerCrossing **walkerCrossing,TramCrossing** tramCrossingx,StreetLight** lightx){
  positionX = startPositionX;
  positionY = startPositionY;
  state = startState;
  color = carColor;
  crossings = crossing;
  parking = park;
  carTable = cT;
  cityTable = ciT;
  walkerCrossings = walkerCrossing;
  tramCrossings = tramCrossingx;
  lights = lightx;
}

void Car::changeDirectionRandomly(){

  Direction randomDirection;

  if(state == RIGHT){
    do{
      randomDirection = Direction(rand()%4);
    }while(randomDirection == LEFT);

    if(randomDirection == RIGHT){
      state = RIGHT;
    }
    else if(randomDirection == DOWN){
      for(int i=0;i<3;i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        tmpX = positionX;
        tmpY = positionY;
        positionX++;
        changed = true;
      }
      state = DOWN;
    }
    else if(randomDirection == UP){
      for(int i=0;i<13;i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        tmpX = positionX;
        tmpY = positionY;
        positionX++;
        changed = true;
      }
      state = UP;
    }
  }

  else if(state == LEFT){
    do{
      randomDirection = Direction(rand()%4);
    }while(randomDirection == RIGHT);

    if(randomDirection == LEFT){
      state = LEFT;
    }
    else if(randomDirection == UP){
      for(int i=0;i<3;i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        tmpX = positionX;
        tmpY = positionY;
        positionX--;
        changed = true;
      }
      state = UP;
    }
    else if(randomDirection == DOWN){
      for(int i=0;i<13;i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        tmpX = positionX;
        tmpY = positionY;
        positionX--;
        changed = true;
      }
      state = DOWN;
    }
  }

  else if(state == DOWN){
    do{
      randomDirection = Direction(rand()%4);
    }while(randomDirection == UP);

    if(randomDirection == LEFT){
      for(int i=0;i<2;i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        tmpX = positionX;
        tmpY = positionY;
        positionY++;
        changed = true;
      }
      state = LEFT;
    }
    else if(randomDirection == RIGHT){
      for(int i=0;i<4;i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        tmpX = positionX;
        tmpY = positionY;
        positionY++;
        changed = true;
      }
      state = RIGHT;
    }
    else if(randomDirection == DOWN){
      state = DOWN;
    }
  }


  else if(state == UP){
    do{
      randomDirection = Direction(rand()%4);
    }while(randomDirection == DOWN);

    if(randomDirection == RIGHT){
      for(int i=0;i<2;i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        tmpX = positionX;
        tmpY = positionY;
        positionY--;
        changed = true;
      }
      state = RIGHT;
    }
    else if(randomDirection == LEFT){
      for(int i=0;i<4;i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        tmpX = positionX;
        tmpY = positionY;
        positionY--;
        changed = true;
      }
      state = LEFT;
    }
    else if(randomDirection == UP){
      state = UP;
    }
  }

}

void Car::tryToTakeParkingPlace(){
  for(int i = 0;i < 2; i++){
    if(positionX == parking->parkingEntracePoints[i][0] && positionY == parking->parkingEntracePoints[i][1]){
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      parking->takeParkingPlace();
      parkingStateChanged = true;
      std::this_thread::sleep_for(std::chrono::milliseconds(10000));
      parking->releaseParkingPlace();
      releaseParkingState = true;
    }
  }
}
void Car::tryToDriveThroughCrossingWithLights(){
  for(int i=0;i<4;i++){
    if(positionX == crossings[2]->crossingPoints[i][0] && positionY == crossings[2]->crossingPoints[i][1]){

      if(lights[i]->getLightColor() == GREEN){
        changeDirectionRandomly();
        if(state == RIGHT){

          for(int k=0;k<15;k++){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tmpX = positionX;
            tmpY = positionY;
            positionX++;
            changed = true;
            //  updateCarState();

          }

        }
        else if(state == LEFT){
          for(int k=0;k<15;k++){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tmpX = positionX;
            tmpY = positionY;
            positionX--;
            changed = true;
            //  updateCarState();
          }

        }else if(state == UP){
          for(int k=0;k<7;k++){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tmpX = positionX;
            tmpY = positionY;
            positionY--;
            changed = true;
            //  updateCarState();
          }

        }else if(state == DOWN){

          for(int k=0;k<7;k++){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tmpX = positionX;
            tmpY = positionY;
            positionY++;
            changed = true;
            //  updateCarState();

          }
        }
      }
      else{
        while(lights[i]->getLightColor() == RED)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }

    }
  }
}
void Car::tryToDriveThroughCrossing(){
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){

      if(positionX == crossings[i]->crossingPoints[j][0] && positionY == crossings[i]->crossingPoints[j][1] && i != 2){

        crossings[i]->takeCrossing();
        changeDirectionRandomly();

        if(state == RIGHT){

          for(int k=0;k<15;k++){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tmpX = positionX;
            tmpY = positionY;
            positionX++;
            changed = true;
            //  updateCarState();

          }


        }
        else if(state == LEFT){
          for(int k=0;k<15;k++){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tmpX = positionX;
            tmpY = positionY;
            positionX--;
            changed = true;
            //  updateCarState();
          }


        }else if(state == UP){
          for(int k=0;k<7;k++){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tmpX = positionX;
            tmpY = positionY;
            positionY--;
            changed = true;
            //  updateCarState();
          }


        }else if(state == DOWN){

          for(int k=0;k<7;k++){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tmpX = positionX;
            tmpY = positionY;
            positionY++;
            changed = true;
            //  updateCarState();

          }

        }
        crossings[i]->releaseCrossing();
      }

    }
  }
}
void Car::tryToDriveThroughTramCrossing(){
  for(int i=0;i<6;i++){
    for(int j=0;j<2;j++){
      if(positionX == tramCrossings[i]->tramPoints[j][0] && positionY == tramCrossings[i]->tramPoints[j][1]){
        if(tramCrossings[i]->tramPoints[j][0] == 20 && tramCrossings[i]->tramPoints[j][1] == 1){
          tramCrossings[i]->takeTramCrossing();
          for(int i=0;i<4;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tmpY = positionY;
            tmpX = positionX;
            positionY++;
            changed = true;
          }
          tramCrossings[i]->releaseTramCrossing();

        }
        else if(tramCrossings[i]->tramPoints[j][0] == 64 && tramCrossings[i]->tramPoints[j][1] == 1){
          tramCrossings[i]->takeTramCrossing();
          for(int i=0;i<4;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tmpY = positionY;
            tmpX = positionX;
            positionY++;
            changed = true;
          }
          tramCrossings[i]->releaseTramCrossing();
        }
        else if(tramCrossings[i]->tramPoints[j][0] == 30 && tramCrossings[i]->tramPoints[j][1] == 5){
          tramCrossings[i]->takeTramCrossing();
          for(int i=0;i<4;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tmpY = positionY;
            tmpX = positionX;
            positionY--;
            changed = true;
          }
          tramCrossings[i]->releaseTramCrossing();
        }
        else if(tramCrossings[i]->tramPoints[j][0] == 74 && tramCrossings[i]->tramPoints[j][1] == 5){
          tramCrossings[i]->takeTramCrossing();
          for(int i=0;i<4;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tmpY = positionY;
            tmpX = positionX;
            positionY--;
            changed = true;
          }
          tramCrossings[i]->releaseTramCrossing();

        }
      }

    }
  }
}

void Car::tryToDriveThroughWalkerCrossing(){
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      if(positionX == walkerCrossings[i]->wDPoints[j][0] && positionY == walkerCrossings[i]->wDPoints[j][1]){
        //std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        if(walkerCrossings[i]->wDPoints[j][0] == 43 && walkerCrossings[i]->wDPoints[j][1] == 34){
          walkerCrossings[i]->takeWalkerCrossing();
          for(int i=0;i<6;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tmpX = positionX;
            tmpY = positionY;
            positionX++;
            changed = true;

          }

          walkerCrossings[i]->releaseWalkerCrossing();


        }

        else if(walkerCrossings[i]->wDPoints[j][0] == 49 && walkerCrossings[i]->wDPoints[j][1] == 32){
          walkerCrossings[i]->takeWalkerCrossing();
          for(int i=0;i<6;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tmpX = positionX;
            tmpY = positionY;
            positionX--;
            changed = true;

          }

          walkerCrossings[i]->releaseWalkerCrossing();

        }

        else if(walkerCrossings[i]->wDPoints[j][0] == 64 && walkerCrossings[i]->wDPoints[j][1] == 18){
          walkerCrossings[i]->takeWalkerCrossing();
          for(int i=0;i<6;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tmpX = positionX;
            tmpY = positionY;
            positionY++;
            changed = true;

          }

          walkerCrossings[i]->releaseWalkerCrossing();

        }

        else if(walkerCrossings[i]->wDPoints[j][0] == 74 && walkerCrossings[i]->wDPoints[j][1] == 24){
          walkerCrossings[i]->takeWalkerCrossing();
          for(int i=0;i<6;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tmpX = positionX;
            tmpY = positionY;
            positionY--;
            changed = true;

          }


          walkerCrossings[i]->releaseWalkerCrossing();

        }

        else if(walkerCrossings[i]->wDPoints[j][0] == 36 && walkerCrossings[i]->wDPoints[j][1] == 12){
          walkerCrossings[i]->takeWalkerCrossing();
          for(int i=0;i<6;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tmpX = positionX;
            tmpY = positionY;
            positionX++;
            changed = true;

          }

          walkerCrossings[i]->releaseWalkerCrossing();

        }

        else if(walkerCrossings[i]->wDPoints[j][0] == 42 && walkerCrossings[i]->wDPoints[j][1] == 10){
          walkerCrossings[i]->takeWalkerCrossing();
          for(int i=0;i<6;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tmpX = positionX;
            tmpY = positionY;
            positionX--;
            changed = true;

          }


          walkerCrossings[i]->releaseWalkerCrossing();

        }
        else if(walkerCrossings[i]->wDPoints[j][0] == 30 && walkerCrossings[i]->wDPoints[j][1] == 23){
          walkerCrossings[i]->takeWalkerCrossing();
          for(int i=0;i<6;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tmpX = positionX;
            tmpY = positionY;
            positionY--;
            changed = true;

          }

          walkerCrossings[i]->releaseWalkerCrossing();

        }

        else if(walkerCrossings[i]->wDPoints[j][0] == 20 && walkerCrossings[i]->wDPoints[j][1] == 17){
          walkerCrossings[i]->takeWalkerCrossing();
          for(int i=0;i<6;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            tmpX = positionX;
            tmpY = positionY;
            positionY++;
            changed = true;

          }
          walkerCrossings[i]->releaseWalkerCrossing();

        }

      }
    }
  }
}
void Car::drive(){

  running = true;
  carTable[positionY][positionX] = 1;


  while(running){
    int counter;
    if(state == RIGHT && cityTable[positionY][positionX+1] == '.' && carTable[positionY][positionX+1] == 0){


      decision = rand()%2;
      if(decision == 1 && counter >= 2){
        tryToTakeParkingPlace();
        counter = 0;
      }
      else{
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        tmpX = positionX;
        tmpY = positionY;
        positionX++;
        changed = true;
        tryToDriveThroughCrossingWithLights();
        tryToDriveThroughCrossing();
        tryToDriveThroughWalkerCrossing();
      }
      counter++;
      if(positionX == 96){
        positionY -= 2;
        positionX = 96;
        state = LEFT;
      }

    }
    else if(state == LEFT && cityTable[positionY][positionX-1] == '.' && carTable[positionY][positionX-1] == 0){


      decision = rand()%2;
      if(decision == 1 && counter >= 2){
        tryToTakeParkingPlace();
        counter = 0;
      }
      else{
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        tmpX = positionX;
        tmpY = positionY;
        positionX--;
        changed = true;
        tryToDriveThroughCrossingWithLights();
        tryToDriveThroughCrossing();
        tryToDriveThroughWalkerCrossing();
      }
      counter++;
      if(positionX == 0){
        positionY += 2;
        positionX = 0;
        state = RIGHT;
      }

    }
    else if(state == UP && cityTable[positionY-1][positionX] == '.' && carTable[positionY-1][positionX] == 0){
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      tmpX = positionX;
      tmpY = positionY;
      positionY--;
      changed=true;
      tryToDriveThroughCrossingWithLights();
      tryToDriveThroughTramCrossing();
      tryToDriveThroughCrossing();
      tryToDriveThroughWalkerCrossing();
      if(positionY == 0){
        positionX -= 10;
        positionY = 0;
        state = DOWN;
      }


    }
    else if(state == DOWN && cityTable[positionY+1][positionX] == '.' && carTable[positionY+1][positionX] == 0){
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      tmpX = positionX;
      tmpY = positionY;
      positionY++;
      changed=true;
      tryToDriveThroughCrossingWithLights();
      tryToDriveThroughTramCrossing();
      tryToDriveThroughCrossing();
      tryToDriveThroughWalkerCrossing();
      if(positionY == 43){
        positionX += 10;
        positionY = 43;
        state = UP;
      }
    }
    else{
      carTable[positionY][positionX] = 1;
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  }
}

void Car::breakRunning(){
  running = false;
}
