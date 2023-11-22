#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class Dot {

public:
    int type = 0;
    int path = INT32_MAX;
    bool used = false;
    bool isDifferent = false;
    int starting = -1;
    
    Dot *low_X = nullptr;
    Dot *high_X = nullptr;
    Dot *low_Y = nullptr;
    Dot *high_Y = nullptr;

    void process(Dot *point, int position) {
        if (position == 0) {
            low_X = point;
            point->low_Y = this;
        } else if (position == 1){
            high_X = point;
            point->high_Y = this;
        } else if (position == 2){
            low_Y = point;
            point->low_X = this;
        } else if (position == 3){
            high_Y = point;
            point->high_X = this;
        }
    }
};

int dotComp(Dot *first, Dot *second) {
    if (first)
        if (second)
            return first->path > second->path;
        else
            return false;
    else
        return true;
}

void newPoint(vector<Dot *> &pointsVector, Dot *coordinate, int position, int starting) {
    if (coordinate) {
        if (coordinate->type) {
            int newPosition = position + coordinate->type;
            
            if (!coordinate->isDifferent) {
                coordinate->isDifferent = true;
                coordinate->path = newPosition;
                pointsVector.push_back(coordinate);
                push_heap(pointsVector.begin(), pointsVector.end(), dotComp);
                coordinate->starting = starting;
            } else {
                if (newPosition < coordinate->path) {
                    coordinate->path = newPosition;
                    coordinate->starting = starting;
                    make_heap(pointsVector.begin(), pointsVector.end(), dotComp);
                }
            }
        }
    }
}

int main() {
    int h, w, startX, startY, endX, endY;
    cin >> h >> w >> startY >> startX >> endY >> endX;
    int pole = w * h;
    vector<Dot> vectorDots(pole);

    Dot *firstDot = nullptr;
    Dot *lastDot = nullptr;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (j == startX - 1 && i == startY - 1)
                firstDot = &vectorDots[w * i + j];
            if (j == endX - 1 && i == endY - 1)
                lastDot = &vectorDots[w * i + j];
            if (i < h - 1)
                vectorDots[(w * i + j)].process(&vectorDots[(w * (i + 1) + j)], 2);
            if (j < w - 1)
                vectorDots[(w * i + j)].process(&vectorDots[(w * i + j + 1)], 1);
            
            char type;
            cin >> type;
            if (type == '.')
                vectorDots[(w * i + j)].type = 1;
            else if (type == 'W')
                vectorDots[(w * i + j)].type = 2;
            else if (type == '#')
                vectorDots[(w * i + j)].type = 0;
        }
    }

    vector<Dot *> allPoints;
    allPoints.reserve(pole);

    firstDot->path = 0;
    firstDot->isDifferent = true;

    allPoints.push_back(firstDot);

    for (int k = 0; k < pole && !lastDot->used && allPoints[0]; k++) {
        Dot *stepDot = allPoints[0];
        pop_heap(allPoints.begin(), allPoints.end(), dotComp);
        allPoints.pop_back();
        stepDot->used = true;

        newPoint(allPoints, stepDot->low_X, stepDot->path, 2);
        newPoint(allPoints, stepDot->high_X, stepDot->path, 3);
        newPoint(allPoints, stepDot->low_Y, stepDot->path, 0);
        newPoint(allPoints, stepDot->high_Y, stepDot->path, 1);
    }

    int size = lastDot->path;
    if (size == INT32_MAX)
        printf("%d", -1);
    else {
        printf("%d\n", size);
        
        vector<char> route(size);
        Dot *current = lastDot;
        int sdvig = 0;
        for (int i = size - 1; i >= 0; i--) {
            int ord = current->starting;
            if (current->type == 2)
                sdvig++;
            
            if (ord == 0){
                route[i] = 'S';
                current = current->low_X;
            } else if (ord == 1){
                route[i] = 'W';
                current = current->high_X;
            } else if (ord == 2){
                route[i] = 'N';
                current = current->low_Y;
            } else if (ord == 3){
                route[i] = 'E';
                current = current->high_Y;
            }
        }
    
        for (int i = sdvig; i < size; i++)
            printf("%c", route[i]);
    }

    return 0;
}