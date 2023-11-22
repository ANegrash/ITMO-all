#include <iostream>
#include <vector>

int main() {
    int allFlowers;
    std::cin >> allFlowers;
    int firstFlower = 0;
    int lastFlower = 0;
    int lineSize = 0;
    
    int firstMax = 0, lastMax = 0;
    int maxSizeOfLine = 0;
    int flower = -1, countFlowers = 1;

    for (int i = 0; i < allFlowers; ++i) {
        int flowerType = -1;
        std::cin >> flowerType;
        
        if (flower == flowerType) {
            countFlowers++;
            
            if (countFlowers >= 3) {
                firstFlower = lastFlower;
                lastFlower = i - 1;
                lineSize = lastFlower - firstFlower + 1;
                
                if (lineSize > maxSizeOfLine) {
                    firstMax = firstFlower;
                    lastMax = lastFlower;
                    maxSizeOfLine = lastMax - firstMax + 1;
                }
            }
        } else {
            flower = flowerType;
            countFlowers = 1;
        }
    }

    firstFlower = lastFlower;
    lastFlower = allFlowers - 1;
    lineSize = lastFlower - firstFlower + 1;
    
    if (lineSize > maxSizeOfLine) {
        firstMax = firstFlower;
        lastMax = lastFlower;
    }
    
    firstMax++;
    lastMax++;

    printf("%d %d", firstMax, lastMax);

    return 0;
}