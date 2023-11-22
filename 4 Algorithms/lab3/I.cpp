#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

int main() {
    int countCars;
    int maxCarsOnFloor;
    int countOrderRows;
    int countOperations = 0;
    
    cin >> countCars;
    cin >> maxCarsOnFloor;
    cin >> countOrderRows;

    if (countCars <= maxCarsOnFloor) {
        countOperations = countCars;
    } else {
        if (countOrderRows <= maxCarsOnFloor) {
            countOperations = countOrderRows;
        } else {
            vector<int> fullCarsVector(countOrderRows);
            vector<vector<int>> carsOrder(countCars);
            vector<int> orderIteration(countCars, 0);
            unordered_map<int, int> carsOnFloor;
            map<int, int, greater<int>> orderCarsOnFloor;
            int carDifference = 0;

            for (int i = 0; i < countOrderRows; i++) {
                int playPosition;
                cin >> playPosition;
                fullCarsVector[i] = playPosition;
                carsOrder[playPosition - 1].push_back(i);
            }

            for (int i = 0; i < countOrderRows; i++) {
                int number_car = fullCarsVector[i];
                auto car_operating = carsOnFloor.find(number_car);

                if (car_operating != carsOnFloor.end()) {
                    orderCarsOnFloor.erase(car_operating->second);
                } else {
                    countOperations++;
                    if (orderCarsOnFloor.size() == maxCarsOnFloor) {
                        auto floorAndNot = orderCarsOnFloor.begin();
                        int firstCar = floorAndNot->first;
                        int secondCar = floorAndNot->second;
                        
                        orderCarsOnFloor.erase(firstCar);
                        carsOnFloor.erase(secondCar);
                    }
                }

                int iterOrder = ++orderIteration[number_car - 1];
                int nextPosition = 0;

                if (iterOrder < carsOrder[number_car - 1].size()) {
                    nextPosition = carsOrder[number_car - 1][iterOrder];
                } else {
                    nextPosition = (countOrderRows + (carDifference++));
                }
                
                orderCarsOnFloor[nextPosition] = number_car;
                carsOnFloor[number_car] = nextPosition;
            }
        }
    } 

    printf("%d", countOperations);

    return 0;
}