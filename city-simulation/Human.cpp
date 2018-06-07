#include "Human.h"
#include <time.h>
#include <thread>
#include <chrono>

Human::Human(int posX,int posY,int **cT,char **ciT,HumanDirection dir,WalkerCrossing **walkerCrossing,TramCrossing** tramCrossings){
  humanPositionX = posX;
  humanPositionY = posY;
  carTable = cT;
  cityTable = ciT;
  direct = dir;
  walkerCrossings = walkerCrossing;
  this->tramCrossings = tramCrossings;
}

void Human::walk(){
  running = true;

  counter=counter1=counter2=counter3=0;
  while(running){

    if(direct == r && cityTable[humanPositionY][humanPositionX+1] == '8'){


      decision = rand()%3;
      if(decision == 1){
        tryToWalkThroughStreet();

      }
      else{
        tryToWalkThroughTramCrossing();
        std::this_thread::sleep_for(std::chrono::milliseconds(rand()%200+150));
        tmpHumanY = humanPositionY;
        tmpHumanX = humanPositionX;
        humanPositionX++;
        humanChangedState = true;
        counter++;
        if(cityTable[humanPositionY+1][humanPositionX] == '8'){
          direct = d;
        }
        else if(cityTable[humanPositionY-1][humanPositionX] == '8'){
          direct = u;
        }
      }


      if(humanPositionX == 96){
        direct = l;
      }

    }
    else if(direct == l && cityTable[humanPositionY][humanPositionX-1] == '8'){
      decision = rand()%3;
      if(decision == 1){
        tryToWalkThroughStreet();

      }
      else{
        tryToWalkThroughTramCrossing();
        std::this_thread::sleep_for(std::chrono::milliseconds(rand()%200+150));
        tmpHumanY = humanPositionY;
        tmpHumanX = humanPositionX;
        humanPositionX--;
        humanChangedState = true;
        counter1++;
        if(cityTable[humanPositionY+1][humanPositionX] == '8'){
          direct = d;
        }
        else if(cityTable[humanPositionY-1][humanPositionX] == '8'){
          direct = u;
        }
      }

      if(humanPositionX == 0){
        direct = r;
      }

    }
    else if(direct == d && cityTable[humanPositionY+1][humanPositionX] == '8'){
      decision = rand()%3;
      if(decision == 1){
        tryToWalkThroughStreet();

      }
      else{
        tryToWalkThroughTramCrossing();
        std::this_thread::sleep_for(std::chrono::milliseconds(rand()%200+150));
        tmpHumanY = humanPositionY;
        tmpHumanX = humanPositionX;
        humanPositionY++;
        humanChangedState = true;
        counter2++;
        if(cityTable[humanPositionY][humanPositionX+1] == '8'){
          direct = r;
        }
        else if(cityTable[humanPositionY][humanPositionX-1] == '8'){
          direct = l;
        }
      }

      if(humanPositionY == 43){
        direct = u;
      }

    }
    else if(direct == u && cityTable[humanPositionY-1][humanPositionX] == '8'){
      decision = rand()%3;
      if(decision == 1){
        tryToWalkThroughStreet();

      }
      else{
        tryToWalkThroughTramCrossing();
        std::this_thread::sleep_for(std::chrono::milliseconds(rand()%200+150));
        tmpHumanY = humanPositionY;
        tmpHumanX = humanPositionX;
        humanPositionY--;
        humanChangedState = true;
        counter3++;
        if(cityTable[humanPositionY][humanPositionX+1] == '8'){
          direct = r;
        }
        else if(cityTable[humanPositionY][humanPositionX-1] == '8'){
          direct = l;
        }
      }

      if(humanPositionY == 0){
        direct = d;
      }

    }
  }

}
void Human::tryToWalkThroughTramCrossing(){
  for(int i=0;i<6;i++){
    for(int j=0;j<2;j++){
      if(humanPositionX == tramCrossings[i]->tramPoints[j][0] && humanPositionY == tramCrossings[i]->tramPoints[j][1]){
        if(tramCrossings[i]->tramPoints[j][0] == 33 && tramCrossings[i]->tramPoints[j][1] == 2){
          tramCrossings[i]->takeTramCrossing();
          for(int i=0;i<3;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(rand()%200+150));
            tmpHumanY = humanPositionY;
            tmpHumanX = humanPositionX;
            humanPositionY++;
            humanChangedState = true;
            streetStep = i;
            streetSize = 3;
          }
          tramCrossings[i]->releaseTramCrossing();

        }
        if(tramCrossings[i]->tramPoints[j][0] == 61 && tramCrossings[i]->tramPoints[j][1] == 2){
          tramCrossings[i]->takeTramCrossing();
          for(int i=0;i<3;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(rand()%200+150));
            tmpHumanY = humanPositionY;
            tmpHumanX = humanPositionX;
            humanPositionY++;
            humanChangedState = true;
            streetStep = i;
            streetSize = 3;
          }
          tramCrossings[i]->releaseTramCrossing();
        }
        if(tramCrossings[i]->tramPoints[j][0] == 33 && tramCrossings[i]->tramPoints[j][1] == 4){
          tramCrossings[i]->takeTramCrossing();
          for(int i=0;i<3;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(rand()%200+150));
            tmpHumanY = humanPositionY;
            tmpHumanX = humanPositionX;
            humanPositionY--;
            humanChangedState = true;
            streetStep = i;
            streetSize = 3;
          }
          tramCrossings[i]->releaseTramCrossing();
        }
        if(tramCrossings[i]->tramPoints[j][0] == 61 && tramCrossings[i]->tramPoints[j][1] == 4){
          tramCrossings[i]->takeTramCrossing();
          for(int i=0;i<3;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(rand()%200+150));
            tmpHumanY = humanPositionY;
            tmpHumanX = humanPositionX;
            humanPositionY--;
            humanChangedState = true;
            streetStep = i;
            streetSize = 3;
          }
          tramCrossings[i]->releaseTramCrossing();
        }
      }

    }
  }
}
void Human::tryToWalkThroughStreet(){

decision = 0;

  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      if(humanPositionX == walkerCrossings[i]->wDPoints[j][0] && humanPositionY == walkerCrossings[i]->wDPoints[j][1]){
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        if(walkerCrossings[i]->wDPoints[j][0] == 47 && walkerCrossings[i]->wDPoints[j][1] == 30){
          walkerCrossings[i]->takeWalkerCrossing();
          for(int i=0;i<6;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(rand()%200+150));
            tmpHumanY = humanPositionY;
            tmpHumanX = humanPositionX;
            humanPositionY++;
            streetChangedState = true;
            streetStep = i;
            streetSize = 6;
          }
          std::this_thread::sleep_for(std::chrono::milliseconds(500));
          walkerCrossings[i]->releaseWalkerCrossing();

          direct = l;
          tmpHumanY = humanPositionY;
          tmpHumanX = humanPositionX;
          humanPositionX--;
          streetChangedState = true;

          streetChangedState = false;

        }

        else if(walkerCrossings[i]->wDPoints[j][0] == 45 && walkerCrossings[i]->wDPoints[j][1] == 36){
          walkerCrossings[i]->takeWalkerCrossing();
          for(int i=0;i<6;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(rand()%200+150));
            tmpHumanY = humanPositionY;
            tmpHumanX = humanPositionX;
            humanPositionY--;
            streetChangedState = true;
            streetStep = i;
            streetSize = 6;

          }
          std::this_thread::sleep_for(std::chrono::milliseconds(500));
          walkerCrossings[i]->releaseWalkerCrossing();

          direct = l;
          tmpHumanY = humanPositionY;
          tmpHumanX = humanPositionX;
          humanPositionX--;
          streetChangedState = true;

          streetChangedState = false;
        }

        else if(walkerCrossings[i]->wDPoints[j][0] == 61 && walkerCrossings[i]->wDPoints[j][1] == 20){
          walkerCrossings[i]->takeWalkerCrossing();
          for(int i=0;i<16;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(rand()%200+150));
            tmpHumanY = humanPositionY;
            tmpHumanX = humanPositionX;
            humanPositionX++;
            streetChangedState = true;
            streetStep = i;
            streetSize = 16;

          }
          std::this_thread::sleep_for(std::chrono::milliseconds(500));
          walkerCrossings[i]->releaseWalkerCrossing();

          direct = u;
          tmpHumanY = humanPositionY;
          tmpHumanX = humanPositionX;
          humanPositionY--;
          streetChangedState = true;

          streetChangedState = false;
        }

        else if(walkerCrossings[i]->wDPoints[j][0] == 77 && walkerCrossings[i]->wDPoints[j][1] == 22){
          walkerCrossings[i]->takeWalkerCrossing();
          for(int i=0;i<16;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(rand()%200+150));
            tmpHumanY = humanPositionY;
            tmpHumanX = humanPositionX;
            humanPositionX--;
            streetChangedState = true;
            streetStep = i;
            streetSize = 16;

          }

          std::this_thread::sleep_for(std::chrono::milliseconds(500));
          walkerCrossings[i]->releaseWalkerCrossing();
          direct = d;
          tmpHumanY = humanPositionY;
          tmpHumanX = humanPositionX;
          humanPositionY++;
          streetChangedState = true;

          streetChangedState = false;
        }

        else if(walkerCrossings[i]->wDPoints[j][0] == 40 && walkerCrossings[i]->wDPoints[j][1] == 8){
          walkerCrossings[i]->takeWalkerCrossing();
          for(int i=0;i<6;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(rand()%200+150));
            tmpHumanY = humanPositionY;
            tmpHumanX = humanPositionX;
            humanPositionY++;
            streetChangedState = true;
            streetStep = i;
            streetSize = 6;

          }
          std::this_thread::sleep_for(std::chrono::milliseconds(500));
          walkerCrossings[i]->releaseWalkerCrossing();

          direct = r;
          tmpHumanY = humanPositionY;
          tmpHumanX = humanPositionX;
          humanPositionX++;
          streetChangedState = true;

          streetChangedState = false;
        }

        else if(walkerCrossings[i]->wDPoints[j][0] == 38 && walkerCrossings[i]->wDPoints[j][1] == 14){
          walkerCrossings[i]->takeWalkerCrossing();
          for(int i=0;i<6;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(rand()%200+150));
            tmpHumanY = humanPositionY;
            tmpHumanX = humanPositionX;
            humanPositionY--;
            streetChangedState = true;
            streetStep = i;
            streetSize = 6;

          }

          std::this_thread::sleep_for(std::chrono::milliseconds(500));
          walkerCrossings[i]->releaseWalkerCrossing();
          direct = r;
          tmpHumanY = humanPositionY;
          tmpHumanX = humanPositionX;
          humanPositionX++;
          streetChangedState = true;

          streetChangedState = false;
        }
        else if(walkerCrossings[i]->wDPoints[j][0] == 17 && walkerCrossings[i]->wDPoints[j][1] == 21){
          walkerCrossings[i]->takeWalkerCrossing();
          for(int i=0;i<16;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(rand()%200+150));
            tmpHumanY = humanPositionY;
            tmpHumanX = humanPositionX;
            humanPositionX++;
            streetChangedState = true;
            streetStep = i;
            streetSize = 16;

          }

          std::this_thread::sleep_for(std::chrono::milliseconds(500));
          walkerCrossings[i]->releaseWalkerCrossing();
          direct = d;
          tmpHumanY = humanPositionY;
          tmpHumanX = humanPositionX;
          humanPositionY++;
          streetChangedState = true;

          streetChangedState = false;
        }

        else if(walkerCrossings[i]->wDPoints[j][0] == 33 && walkerCrossings[i]->wDPoints[j][1] == 19){
          walkerCrossings[i]->takeWalkerCrossing();
          for(int i=0;i<16;i++){
            std::this_thread::sleep_for(std::chrono::milliseconds(rand()%200+150));
            tmpHumanY = humanPositionY;
            tmpHumanX = humanPositionX;
            humanPositionX--;
            streetChangedState = true;
            streetStep = i;
            streetSize = 16;

          }

          std::this_thread::sleep_for(std::chrono::milliseconds(500));
          walkerCrossings[i]->releaseWalkerCrossing();
          direct = d;
          tmpHumanY = humanPositionY;
          tmpHumanX = humanPositionX;
          humanPositionY++;
          streetChangedState = true;

          streetChangedState = false;
        }





      }
    }
  }
}


void Human::breakWalking(){
  running = false;
}
