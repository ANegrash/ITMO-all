#include <iostream>
#include <deque>
#include <string>

using namespace std;

class CustomClass {
public:
    CustomClass *nextPos;
    CustomClass *prevPos;
    int value;

    CustomClass(CustomClass *nextPosIn = nullptr, CustomClass *prevPosIn = nullptr, int valueIn = 0) {
        nextPos = nextPosIn;
        prevPos = prevPosIn;
        value = valueIn;
    }
};

class GoblinsList {
public:
    CustomClass *firstGoblin;
    CustomClass *lastGoblin;
    CustomClass *middlePosition;
    int size;

    GoblinsList(CustomClass *firstGoblinIn = nullptr, CustomClass *lastGoblinIn = nullptr, CustomClass *middlePositionIn = nullptr, int sizeIn = 0) {
        firstGoblin = firstGoblinIn;
        lastGoblin = lastGoblinIn;
        middlePosition = middlePositionIn;
        size = sizeIn;
    }

};

void push_first(GoblinsList *goblinsList, int val) {
    goblinsList->size++;
    
    if (goblinsList->firstGoblin != nullptr) {
        auto custClass = new CustomClass(goblinsList->firstGoblin, nullptr, val);
        goblinsList->firstGoblin->prevPos = custClass;
        goblinsList->firstGoblin = custClass;
        
        if (goblinsList->size % 2 == 1 && goblinsList->size > 1)
            if (goblinsList->middlePosition->prevPos != nullptr)
                goblinsList->middlePosition = goblinsList->middlePosition->prevPos;
                
    } else {
        auto custClass = new CustomClass(nullptr, nullptr, val);
        goblinsList->firstGoblin = custClass;
        goblinsList->middlePosition = custClass;
        goblinsList->lastGoblin = custClass;
    }
}

int pop_back(GoblinsList *goblinsList) {
    goblinsList->size--;
    int lastGoblinPos = goblinsList->lastGoblin->value;

    if (goblinsList->size == 0) {
        goblinsList->firstGoblin = nullptr;
        goblinsList->lastGoblin = nullptr;
        goblinsList->middlePosition = nullptr;
    } else {
        if (goblinsList->size % 2 == 1)
            goblinsList->middlePosition = goblinsList->middlePosition->prevPos;

        goblinsList->lastGoblin = goblinsList->lastGoblin->prevPos;
        goblinsList->lastGoblin->nextPos = nullptr;
    }

    return lastGoblinPos;
}

void push_middle(GoblinsList *goblinsList, int val) {
    goblinsList->size++;
    
    if (goblinsList->middlePosition == nullptr) {
        auto custClass = new CustomClass(nullptr, nullptr, val);
        goblinsList->middlePosition = custClass;
        goblinsList->lastGoblin = custClass;
        goblinsList->firstGoblin = custClass;
    } else {
        auto custClass = new CustomClass(nullptr, nullptr, val);

        if ((goblinsList->size) % 2 == 0 && goblinsList->size > 1) {
            custClass->prevPos = goblinsList->middlePosition->prevPos;
            goblinsList->middlePosition->prevPos = custClass;
            custClass->nextPos = goblinsList->middlePosition;
            
            if (custClass->prevPos != nullptr)
                custClass->prevPos->nextPos = custClass;
            else
                goblinsList->firstGoblin = custClass;

        } else {
            custClass->prevPos = goblinsList->middlePosition->prevPos;
            custClass->nextPos = goblinsList->middlePosition;
            goblinsList->middlePosition->prevPos = custClass;
            
            if (custClass->prevPos != nullptr)
                custClass->prevPos->nextPos = custClass;
            else
                goblinsList->firstGoblin = custClass;

            goblinsList->middlePosition = custClass;
        }
    }
}

int main() {
    int goblinsOrderNum;
    cin >> goblinsOrderNum;

    auto *goblinsList = new GoblinsList();

    for (int i = 0; i < goblinsOrderNum; ++i) {
        string query;
        cin >> query;
        
        if (query.at(0) == '+') {
            string queryNum;
            cin >> queryNum;
            push_first(goblinsList, stoi(queryNum));
        } else if (query.at(0) == '-') {
            int minusQueryResult = pop_back(goblinsList);
            printf("%d\n", minusQueryResult);
        } else if (query.at(0) == '*') {
            string queryNum;
            cin >> queryNum;
            push_middle(goblinsList, stoi(queryNum));
        }
    }

    return 0;
}