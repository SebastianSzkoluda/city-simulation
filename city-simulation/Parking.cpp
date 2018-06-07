#include "Parking.h"


Parking::Parking(vector<vector<int>> &p){
  parkingBufor = 5;
  parkingEntracePoints = p;
}

void Parking::takeParkingPlace() {
  std::unique_lock<std::mutex> l(mutexParking);
  cvParking.wait(l, [this](){return parkingBufor > 0;});
  parkingBufor--;
  l.unlock();
}

void Parking::releaseParkingPlace() {
  std::unique_lock<std::mutex> l(mutexParking);
  parkingBufor++;
  cvParking.notify_all();
  l.unlock();
}
