#include <iostream>
#include <vector>

int compare(int firstElement, int secondElement) {
    if (firstElement > secondElement)
        return 1;
    else if (firstElement < secondElement)
        return -1;
    else
        return 0;
}

void sortVector(std::vector<int> *prices, int firstElement, int lastElement) {

    if (lastElement - firstElement == 0)
        return;
        
    else if (lastElement - firstElement == 1) {
        if (compare((*prices)[firstElement], (*prices)[lastElement]) < 0) {
            int tmp = (*prices)[firstElement];
            (*prices)[firstElement] = (*prices)[lastElement];
            (*prices)[lastElement] = tmp;
        }
        
    } else {
        int middle = (firstElement + (lastElement - firstElement) / 2) + 1;

        sortVector(prices, firstElement, middle - 1);
        sortVector(prices, middle, lastElement);

        int first = firstElement;
        int second = middle;
        std::vector<int> middlePrices(lastElement - firstElement + 1);

        for (int i = 0; i <= lastElement - firstElement; ++i) {
            
            if (compare((*prices)[first], (*prices)[second]) >= 1) {
                middlePrices[i] = (*prices)[first++];
                
                if (first == middle) {
                    for (int j = i + 1; j <= lastElement - firstElement; ++j) 
                        middlePrices[j] = (*prices)[second++];
                    break;
                }
                
            } else {
                middlePrices[i] = (*prices)[second++];
                
                if (second == lastElement + 1) {
                    for (int j = i + 1; j <= lastElement - firstElement; ++j)
                        middlePrices[j] = (*prices)[first++];
                    break;
                }
            }
        }

        for (int i = 0; i <= lastElement - firstElement; ++i)
            (*prices)[firstElement + i] = middlePrices[i];
    }
}

int main() {

    int item, ord;
    std::cin >> item >> ord;

    std::vector<int> prices(item);
    for (int i = 0; i < (int) item; ++i)
        std::cin >> prices[i];

    sortVector(&prices, 0, prices.size() - 1);

    int totalSum = 0;

    for (int i = 0; i < item; ++i)
        if ((i+1) % (ord) != 0)
            totalSum += prices[i];

    printf("%d", totalSum);

    return 0;
}