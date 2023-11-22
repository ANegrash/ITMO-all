#include <vector>
#include <iostream>
using namespace std;

struct City {
    vector<int> distances;
    vector<bool> isCan;
    bool isUse = false;
};

int getCenter(int l, int r){
    return (l + r) / 2;
}

void disableCity(vector<City> &cities) {
    for (int i = 0; i <= cities.size() - 1; i++)
        cities[i].isUse = false;
}

void offCity(vector<City> &cities, int item) {
    cities[item].isUse = true;
    
    for (int i = 0; i <= cities.size() - 1; i++)
        if (!(cities[i].isUse) && cities[item].isCan[i])
            offCity(cities, i);
}

void onCity(vector<City> &cities, int item) {
    cities[item].isUse = true;
    
    for (int i = 0; i <= cities.size() - 1; i++)
        if (!(cities[i].isUse) && cities[i].isCan[item])
            onCity(cities, i);
}

void enableCityDist(int checkableDistance, vector<City> &cities) {
    for (int i = 0; i <= cities.size() - 1; i++)
        for (int j = 0; j <= cities.size() - 1; j++)
            cities[i].isCan[j] = cities[i].distances[j] <= checkableDistance;
}

int main() {
    int size;
    cin >> size;
    if (size != 1) {
        vector<City> cities(size);
        int lBorder = 0;
        int rBorder = INT32_MAX;
    
        for (int i = 0; i <= size - 1; i++) {
            cities[i].distances.resize(size);
            cities[i].isCan.resize(size);
            
            for (int k = 0; k <= size - 1; k++) {
                int temp;
                cin >> temp;
                cities[i].distances[k] = temp;
            }
        }
    
        while (lBorder < rBorder) {
            int center = getCenter(lBorder, rBorder);
            
            enableCityDist(center, cities);
            disableCity(cities);
            onCity(cities, 0);
            
            bool used = true;
            for (int i = 0; (i <= size - 1) && used; i++)
                used &= cities[i].isUse;
            
            if (used) {
                disableCity(cities);
                offCity(cities, 0);
                
                for (int i = 0; (i <= size - 1) && used; i++)
                    used &= cities[i].isUse;
            }
            
            if (used)
                rBorder = center;
            else
                lBorder = center + 1;
        }
    
        cout << lBorder;
    } else 
        cout << 0;

    return 0;
}