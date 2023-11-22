#include <iostream>
#include <limits>
int glodalArray[600000];

    void create(int orderArray[], int znachenie, int leftBorder, int rightBorder) {
        if (leftBorder != rightBorder) {
            auto middleElement = (leftBorder + rightBorder) / 2;
            int znachenieX2 = znachenie + znachenie;
            
            create(orderArray, znachenieX2, leftBorder, middleElement);
            create(orderArray, znachenieX2 + 1, middleElement + 1, rightBorder);
            glodalArray[znachenie] = std::min(glodalArray[znachenieX2 + 1], glodalArray[znachenieX2]);
        } else {
            glodalArray[znachenie] = orderArray[leftBorder];
        }
    }
    
    int minimalInt(int firstInteger, int levayaGranitsa, int pravayaGranitsa, int levayaGranitsaDereva, int pravayaGranitsaDereva) {
        if (pravayaGranitsaDereva < levayaGranitsa) {
            return std::numeric_limits<int>::max();
        } else if(pravayaGranitsa + 1 <= levayaGranitsaDereva) {
            return std::numeric_limits<int>::max();
        } else if (levayaGranitsaDereva - levayaGranitsa >= 0 && pravayaGranitsaDereva - pravayaGranitsa <= 0) {
            return glodalArray[firstInteger];
        } else {
            int middleElement = (levayaGranitsaDereva + pravayaGranitsaDereva) / 2;
            int dvoynoyFirstInt = firstInteger + firstInteger;
            int leftElement = minimalInt(dvoynoyFirstInt, levayaGranitsa, std::min(pravayaGranitsa, middleElement), levayaGranitsaDereva, middleElement);
            int rightElement = minimalInt(dvoynoyFirstInt + 1, std::max(levayaGranitsa, middleElement + 1), pravayaGranitsa, middleElement + 1, pravayaGranitsaDereva);
            return std::min(leftElement, rightElement);
        }
    }
    
    int main() {
        int orderSize, windowSize;
        std::cin >> orderSize >> windowSize;
        
        int orderOfInts[orderSize];
        orderSize = orderSize - 1;
        
        for (int i = 0; i <= orderSize; i++) {
            std::cin >> orderOfInts[i];
        }
        
        create(orderOfInts, 1, 0, orderSize);
        
        int leftBorder = 0;
        int rightBorder = windowSize - 1;
        
        while (rightBorder <= orderSize) {
            int resultedItem = minimalInt(1, leftBorder, rightBorder, 0, orderSize);
            std::cout << resultedItem << " ";
            leftBorder += 1;
            rightBorder += 1;
        }
        
        std::cout << std::endl;
        
        return 0;
        
    }