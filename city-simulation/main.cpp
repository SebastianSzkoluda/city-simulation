#include <iostream>
#include <ncurses.h>
#include <fstream>
#include <thread>
#include <stdlib.h>
#include <mutex>
#include <condition_variable>
#include <vector>
#include "Car.h"
#include "Crossing.h"
#include "Parking.h"
#include "Human.h"
#include "WalkerCrossing.h"
#include "TramCrossing.h"
#include "Tram.h"
#define LIGHT_RED 12
#define LIGHT_GREEN 10

using namespace std;
char **cityTable;
int **carTable;
fstream file;
int a,b,c,di;

void drawCity() {


  start_color();
  init_color(COLOR_RED,139,69,19);
  init_pair(1,COLOR_BLACK, COLOR_WHITE);
  init_pair(2,COLOR_WHITE, COLOR_GREEN);
  init_pair(3,COLOR_WHITE,COLOR_RED);
  init_pair(4,COLOR_WHITE, COLOR_BLACK);
  init_pair(5,COLOR_WHITE, COLOR_YELLOW);
  init_pair(6,COLOR_WHITE, COLOR_BLUE);
  init_pair(7,COLOR_WHITE, COLOR_MAGENTA);
  init_pair(8,COLOR_WHITE, COLOR_CYAN);


  bkgd(COLOR_PAIR(1));

  for(int i=0;i < a; i++){
    for(int j = 0; j < b; j++){
      if( cityTable[i][j] == '0'){
        move(i,j);
        attron(COLOR_PAIR(4));
        addch(' ');
        attroff(COLOR_PAIR(4));

      }
      else if( cityTable[i][j] == '7'){
        move(i,j);
        attron(COLOR_PAIR(2));
        addch(' ');
        attroff(COLOR_PAIR(2));

      }
      else if( cityTable[i][j] == '8'){
        move(i,j);
        attron(COLOR_PAIR(3));
        addch(' ');
        attroff(COLOR_PAIR(3));

      }
      else if( cityTable[i][j] == '.'){
        move(i,j);
        attron(COLOR_PAIR(4));
        addch('.');
        attroff(COLOR_PAIR(4));

      }
      attron(COLOR_PAIR(4));
      mvprintw(20,42,"Ilosc wolnych");
      mvprintw(21,44,"miejsc: %d",5);
      attroff(COLOR_PAIR(4));

    }
  }
}

void readMapFromFile(){

  file.open("data.txt",ios::in);
  file >> a;
  file >> b;

  cityTable = new char*[a];
  for(int i=0;i < a; i++){
    cityTable[i] = new char[b];
    for(int j = 0; j < b; j++){
      file >> cityTable[i][j];
    }
  }
}

void updateWorldState(Car **cars,Parking *parking,Human **humans,Tram* tram,StreetLight** lights){
  int actualParkingY = 25;
  drawCity();
  nodelay(stdscr, TRUE);
  for(;;){
    if((di = getch())!=27){
      for(int i=0;i<13;i++){
        if(cars[i]->changed){

          attron(COLOR_PAIR(4));
          mvprintw(cars[i]->tmpY,cars[i]->tmpX,"%s",".");

          attroff(COLOR_PAIR(4));
          attron(COLOR_PAIR(cars[i]->color));
          mvprintw(cars[i]->positionY,cars[i]->positionX,"%s"," ");
          attroff(COLOR_PAIR(cars[i]->color));

         carTable[cars[i]->tmpY][cars[i]->tmpX] = 0;
         carTable[cars[i]->positionY][cars[i]->positionX] = 1;


          cars[i]->changed = false;

        }

        if(cars[i]->parkingStateChanged == true){

          attron(COLOR_PAIR(4));
          mvprintw(cars[i]->positionY,cars[i]->positionX,"%s",".");
          carTable[cars[i]->positionY][cars[i]->positionX] = 0;

          mvprintw(20,42,"Ilosc wolnych");
          mvprintw(21,44,"miejsc: %d",parking->getParkingBufor());
          attroff(COLOR_PAIR(4));

          for(int j = 38;j<49;j+=2){
            if(carTable[actualParkingY][j] == 0){
              attron(COLOR_PAIR(cars[i]->color));
              mvprintw(actualParkingY,j,"%s"," ");
              cars[i]->tmpParkingX = j;
              carTable[actualParkingY][j] = 1;
              attroff(COLOR_PAIR(cars[i]->color));

              break;
            }
          }

          cars[i]->parkingStateChanged = false;

        }
        if(cars[i]->releaseParkingState == true){

          attron(COLOR_PAIR(4));
          mvprintw(actualParkingY,cars[i]->tmpParkingX,"%s"," ");
          carTable[actualParkingY][cars[i]->tmpParkingX] = 0;
          mvprintw(20,42,"Ilosc wolnych");
          mvprintw(21,44,"miejsc: %d",parking->getParkingBufor());

          attroff(COLOR_PAIR(4));


          cars[i]->releaseParkingState = false;
        }

      }
      for(int j=0;j<5;j++){
        if(humans[j]->getHumanChangedState() == true){

          if(humans[j]->getStreetChangedState() == true){
            if(humans[j]->getStreetStep() == 0){
              attron(COLOR_PAIR(3));
              mvprintw(humans[j]->getTmpHumanPositionY(),humans[j]->getTmpHumanPositionX()," ");
              attroff(COLOR_PAIR(3));
              attron(COLOR_PAIR(4));
              mvprintw(humans[j]->getHumanPositionY(),humans[j]->getHumanPositionX(),"O");
              attroff(COLOR_PAIR(4));

            }
            else if(humans[j]->getStreetStep() < humans[j]->getStreetSize()-1){
              if(cityTable[humans[j]->getTmpHumanPositionY()][humans[j]->getTmpHumanPositionX()] == '.'){
                attron(COLOR_PAIR(4));
                mvprintw(humans[j]->getTmpHumanPositionY(),humans[j]->getTmpHumanPositionX(),".");
                mvprintw(humans[j]->getHumanPositionY(),humans[j]->getHumanPositionX(),"O");
                attroff(COLOR_PAIR(4));

              }
              else{
                attron(COLOR_PAIR(4));
                mvprintw(humans[j]->getTmpHumanPositionY(),humans[j]->getTmpHumanPositionX()," ");
                mvprintw(humans[j]->getHumanPositionY(),humans[j]->getHumanPositionX(),"O");
                attroff(COLOR_PAIR(4));

              }

            }
            else if(humans[j]->getStreetStep() == humans[j]->getStreetSize()-1){
              attron(COLOR_PAIR(4));
              mvprintw(humans[j]->getTmpHumanPositionY(),humans[j]->getTmpHumanPositionX()," ");
              attroff(COLOR_PAIR(4));
              attron(COLOR_PAIR(3));
              mvprintw(humans[j]->getHumanPositionY(),humans[j]->getHumanPositionX(),"O");
              attroff(COLOR_PAIR(3));

            }

          }else{
            attron(COLOR_PAIR(3));
            mvprintw(humans[j]->getTmpHumanPositionY(),humans[j]->getTmpHumanPositionX()," ");
            mvprintw(humans[j]->getHumanPositionY(),humans[j]->getHumanPositionX(),"O");
            attroff(COLOR_PAIR(3));

          }

        }
      }

      if(tram->getTramStateChanged() == true){

        if(tram->getTramX()+ 14 >= 96){
          attron(COLOR_PAIR(4));
          mvprintw(tram->getTmpTramY(),tram->getTmpTramX(),".");
          mvprintw(tram->getTramY(),tram->getTramX(),".");
          attroff(COLOR_PAIR(4));

        }else{
          attron(COLOR_PAIR(4));
          mvprintw(tram->getTmpTramY(),tram->getTmpTramX(),".");
          attroff(COLOR_PAIR(4));
          attron(COLOR_PAIR(5));
          mvprintw(tram->getTramY(),tram->getTramX(),"                ");
          attroff(COLOR_PAIR(5));

        }

        tram->setTramStateChanged(false);
      }

      for(int i=0;i<4;i++){
        if(lights[i]->getlightStateChanged() == true){

          if(lights[i]->getLightColor() == RED){

            init_color(LIGHT_RED,1000,0,0);
            init_pair(9,COLOR_BLACK,LIGHT_RED);
            attron(COLOR_PAIR(9));
            mvprintw(lights[i]->getLightY(),lights[i]->getLightX(),"  ");
            attroff(COLOR_PAIR(9));


            lights[i]->setlightStateChanged(false);
          }
          else if(lights[i]->getLightColor() == GREEN){

            init_color(LIGHT_GREEN,0,1000,0);
            init_pair(10,COLOR_BLACK,LIGHT_GREEN);
            attron(COLOR_PAIR(10));
            mvprintw(lights[i]->getLightY(),lights[i]->getLightX(),"  ");
            attroff(COLOR_PAIR(10));


            lights[i]->setlightStateChanged(false);
          }
        }
      }
      timeout(10);
    }
    else {
      return;
    }

  }
}

int main(){

  srand(time(NULL));
  readMapFromFile();

  carTable = new int*[a];
  for(int i=0;i < a; i++){
    carTable[i] = new int[b];
    for(int j = 0; j < b; j++){
      carTable[i][j] = 0;
    }
  }

  //Threads
  Car** cars = new Car*[13];
  Human** humans = new Human*[5];
  StreetLight** lights = new StreetLight*[4];
  Tram* tram;

  //Resources
  WalkerCrossing** walkerCrossings = new WalkerCrossing*[4];
  TramCrossing** tramCrossings = new TramCrossing*[6];
  Crossing** crossings = new Crossing*[4];
  LightResource* lightResource;
  Parking* parking;


  vector<vector<int>>forFirst = {{20,8},{33,10},{17,12},{30,14}};
  vector<vector<int>>forSecond = {{64,8},{77,10},{61,12},{74,14}};
  vector<vector<int>>forThird = {{20,30},{33,32},{17,34},{30,36}};
  vector<vector<int>>forFourth = {{64,30},{77,32},{61,34},{74,36}};

  vector<vector<int>>forFirstWC = {{47,30},{45,36},{43,34},{49,32}};
  vector<vector<int>>forSecondWC = {{61,20},{77,22},{64,18},{74,24}};
  vector<vector<int>>forThirdWC = {{40,8},{38,14},{36,12},{42,10}};
  vector<vector<int>>forFourthWC = {{17,21},{33,19},{30,23},{20,17}};

  vector<vector<int>>one = {{20,1},{20,1}};
  vector<vector<int>>two = {{30,5},{30,5}};
  vector<vector<int>>three = {{33,2},{33,4}};
  vector<vector<int>>four = {{61,2},{61,4}};
  vector<vector<int>>five = {{64,1},{64,1}};
  vector<vector<int>>six = {{74,5},{74,5}};



  vector<vector<int>> parkingPoints = {{46,12},{49,10}};

  parking = new Parking(parkingPoints);

  lightResource = new LightResource(true);


  crossings[0] = new Crossing(true,forFirst,false);
  crossings[1] = new Crossing(true,forSecond,false);
  crossings[2] = new Crossing(true,forThird,true);
  crossings[3] = new Crossing(true,forFourth,false);

  walkerCrossings[0] = new WalkerCrossing(true,forFirstWC);
  walkerCrossings[1] = new WalkerCrossing(true,forSecondWC);
  walkerCrossings[2] = new WalkerCrossing(true,forThirdWC);
  walkerCrossings[3] = new WalkerCrossing(true,forFourthWC);

  tramCrossings[0] = new TramCrossing(true,one);
  tramCrossings[1] = new TramCrossing(true,two);
  tramCrossings[2] = new TramCrossing(true,three);
  tramCrossings[3] = new TramCrossing(true,four);
  tramCrossings[4] = new TramCrossing(true,five);
  tramCrossings[5] = new TramCrossing(true,six);

  tram = new Tram(0,3,cityTable,carTable,tramCrossings);

  lights[0] = new StreetLight(18,31,lightResource);
  lights[1] = new StreetLight(31,31,lightResource);
  lights[2] = new StreetLight(18,35,lightResource);
  lights[3] = new StreetLight(31,35,lightResource);

  cars[0] = new Car(0,12,RIGHT,5,crossings, parking,carTable,cityTable,walkerCrossings,tramCrossings,lights);
  cars[1] = new Car(96,10,LEFT,6,crossings, parking,carTable,cityTable,walkerCrossings,tramCrossings,lights);
  cars[2] = new Car(30,43,UP,7,crossings, parking,carTable,cityTable,walkerCrossings,tramCrossings,lights);
  cars[3] = new Car(20,0,DOWN,8,crossings, parking,carTable,cityTable,walkerCrossings,tramCrossings,lights);
  cars[4] = new Car(1,34,RIGHT,5,crossings, parking,carTable,cityTable,walkerCrossings,tramCrossings,lights);
  cars[5] = new Car(96,32,LEFT,6,crossings, parking,carTable,cityTable,walkerCrossings,tramCrossings,lights);
  cars[6] = new Car(74,43,UP,7,crossings, parking,carTable,cityTable,walkerCrossings,tramCrossings,lights);
  cars[7] = new Car(64,0,DOWN,1,crossings, parking,carTable,cityTable,walkerCrossings,tramCrossings,lights);
  cars[8] = new Car(2,12,RIGHT,7,crossings, parking,carTable,cityTable,walkerCrossings,tramCrossings,lights);
  cars[9] = new Car(3,34,RIGHT,1,crossings, parking,carTable,cityTable,walkerCrossings,tramCrossings,lights);
  cars[10] = new Car(94,32,LEFT,6,crossings, parking,carTable,cityTable,walkerCrossings,tramCrossings,lights);
  cars[11] = new Car(74,41,UP,2,crossings, parking,carTable,cityTable,walkerCrossings,tramCrossings,lights);
  cars[12] = new Car(64,2,DOWN,6,crossings, parking,carTable,cityTable,walkerCrossings,tramCrossings,lights);

  humans[0] = new Human(45,8,carTable,cityTable,r,walkerCrossings,tramCrossings);
  humans[1] = new Human(33,30,carTable,cityTable,r,walkerCrossings,tramCrossings);
  humans[2] = new Human(33,36,carTable,cityTable,r,walkerCrossings,tramCrossings);
  humans[3] = new Human(95,30,carTable,cityTable,l,walkerCrossings,tramCrossings);
  humans[4] = new Human(1,14,carTable,cityTable,l,walkerCrossings,tramCrossings);



  std::thread tramThread (&Tram::tryToDrive, tram);

  std::thread* carThreads = new std::thread[13];
  for(int i=0;i<13;i++){
    carThreads[i] = std::thread(&Car::drive, cars[i]);
  }
  std::thread* humanThreads = new std::thread[5];
  for(int j=0;j<5;j++){
    humanThreads[j] = std::thread(&Human::walk, humans[j]);
  }
  std::thread* lightThreads = new std::thread[4];
  for(int j=0;j<4;j++){
    lightThreads[j] = std::thread(&StreetLight::startControl, lights[j]);
  }


  initscr();
  noecho();
  curs_set(0);

  updateWorldState(cars,parking,humans,tram,lights);

  for(int i=0;i<13;i++){
    cars[i]->breakRunning();
  }
  for(int i=0;i<5;i++){
    humans[i]->breakWalking();
  }
  for(int i=0;i<4;i++){
    lights[i]->stopControl();
  }
  tram->breakDriving();

  for(int i=0;i<13;i++){
    carThreads[i].join();
  }
  for(int i=0;i<5;i++){
    humanThreads[i].join();
  }
  for(int i=0;i<4;i++){
    lightThreads[i].join();
  }
  tramThread.join();



  endwin();

  delete[] cars;

  delete[] carThreads;

  delete[] humans;

  delete[] humanThreads;

  delete[] lights;

  delete[] lightThreads;


  return 0;
}
