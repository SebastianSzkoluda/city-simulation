#ifndef PARKING_H
#define PARKING_H
#include <mutex>
#include <condition_variable>
#include <vector>
#include <iostream>

using namespace std;


class Parking{
private:
  int parkingBufor;
  std::mutex mutexParking;
  std::condition_variable cvParking;
public:
  vector<vector<int>> parkingEntracePoints;
  Parking(vector<vector<int>> &p);

  int getParkingBufor(){return parkingBufor;}
  void takeParkingPlace();
  void releaseParkingPlace();
};


#endif
