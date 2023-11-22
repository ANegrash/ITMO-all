#include <iostream>
#include <stack>
#include <vector>

int main() {
    std::string inputStr;
    std::cin >> inputStr;
    std::deque<std::pair<int, char>> zoo;

    int numOfAnimals = 0;
    int numOfTraps = 0;
    short smallLetterComp = 96;
    short bigLetterComp = 91;
    
    std::string imp = "Impossible";
    std::string posi = "Possible\n";

    for (int i = 0; i < inputStr.size(); ++i) {
        std::pair<int, char> pair;
        pair.second = inputStr[i];
        
        if (pair.second > smallLetterComp)
            pair.first = ++numOfAnimals;
        else if (pair.second < bigLetterComp)
            pair.first = ++numOfTraps;
            
        zoo.push_back(pair);
    }

    std::vector<int> order(zoo.size() / 2, 0);

    int zooSize = zoo.size();
    int difference = 0;
    
    for (int i = 0; i < zooSize; ++i) {
        std::pair<int, char> currentPair = zoo.front();
        zoo.pop_front();
        int compare = ((int) currentPair.second) - ((int) zoo.front().second);
        
        if (compare == 32) {
            order[zoo.front().first - 1] = currentPair.first;
            zoo.pop_front();
            
            if (difference > 0 && !zoo.empty()) {
                currentPair = zoo.back();
                zoo.pop_back();
                zoo.push_front(currentPair);
                difference--;
            }

        } else if (compare == -32) {
            order[currentPair.first - 1] = zoo.front().first;
            zoo.pop_front();
            
            if (difference > 0 && !zoo.empty()) {
                currentPair = zoo.back();
                zoo.pop_back();
                zoo.push_front(currentPair);
                difference--;
            }
            
        } else if (difference == 0) {
            int comparePrev = ((int) currentPair.second) - ((int) zoo.back().second);
            
            if (comparePrev == 32) {
                order[zoo.back().first - 1] = currentPair.first;
                zoo.pop_back();
            } else if (comparePrev == -32) {
                order[currentPair.first - 1] = zoo.back().first;
                zoo.pop_back();
            } else {
                zoo.push_back(currentPair);
                difference++;
                
                if (difference >= zoo.size()) {
                    printf("%s", imp.c_str());
                    return 0;
                }
            }
            
        } else {
            zoo.push_back(currentPair);
            difference++;
            
            if (difference >= zoo.size()) {
                printf("%s", imp.c_str());
                return 0;
            }
            
        }
        
        if (zoo.empty())
            break;
    }

    printf("%s", posi.c_str());
    for (int ord : order)
        printf("%d ", ord);

    return 0;
}