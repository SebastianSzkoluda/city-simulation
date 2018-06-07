#include "Tram.h"
#include <thread>



Tram::Tram(int tramX,int tramY,char **cityTable,int **carTable,TramCrossing** tramCrossings){
  this->tramX = tramX;
  this->tramY = tramY;
  this->cityTable = cityTable;
  this->carTable = carTable;
  this->tramCrossings = tramCrossings;
}
void Tram::startDriveThroughCity(){
  if(tramX == 0){
    tramCrossings[0]->takeTramCrossing();
    tramCrossings[1]->takeTramCrossing();
    tramCrossings[2]->takeTramCrossing();
  }
  if(tramX == 34){

      tramCrossings[0]->releaseTramCrossing();
      tramCrossings[1]->releaseTramCrossing();
      tramCrossings[2]->releaseTramCrossing();

      tramCrossings[5]->takeTramCrossing();
      tramCrossings[3]->takeTramCrossing();
      tramCrossings[4]->takeTramCrossing();
      for(int i=34;i<97;i++){
        carTable[3][i] = 1;
      }

  }
  if(tramX == 90){
      tramCrossings[3]->releaseTramCrossing();
      tramCrossings[4]->releaseTramCrossing();
      tramCrossings[5]->releaseTramCrossing();
      for(int i=34;i<97;i++){
        carTable[3][i] = 0;
      }
  }
}

void Tram::tryToDrive(){
  running = true;

  while(running)
{

  startDriveThroughCity();
  std::this_thread::sleep_for(std::chrono::milliseconds(rand()%150+100));
  tmpTramX = tramX;
  tmpTramY = tramY;
  tramX++;
  tramStateChanged=true;

  if(tramX == 96){
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    tramX = 0;
  }
}


}

void Tram::breakDriving(){
  running = false;
}
