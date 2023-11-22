#include <iostream>
#include <vector>

bool isRighter (int minDist, std::vector<int> *positions, int cows) {
    int beforePos = positions->at(0);
    int cowCounter = 1;
    
    for (int i = 1; i < positions->size(); ++i) {
        if (positions->at(i) - beforePos >= minDist) {
            cowCounter++;
            beforePos = positions->at(i);
            if (cowCounter == cows) 
                return true;
        }
    }
    return false;
}

int main() {
    int p, cow;
    std::cin >> p >> cow;
    std::vector<int> positions(p);
    for (int i = 0; i < (int) p; ++i)
        std::cin >> positions[i];

    int leftEnd = 1;
    int rightEnd = positions[positions.size() - 1];

    while (rightEnd - leftEnd != 1) {
        int center = (rightEnd + leftEnd) / 2;
        if (isRighter(center, &positions, cow))
           leftEnd = center;
        else
            rightEnd = center;
    }

    printf("%d", leftEnd);

    return 0;
}