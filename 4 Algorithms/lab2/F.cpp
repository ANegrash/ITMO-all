#include "iostream"
#include "string"
#include "vector"
#include "map"
#include "list"
#include "algorithm"

int compare(std::string first, std::string second) {
    int minSize = std::min(first.size(), second.size());
    
    for (int i = 0; i < minSize; ++i) {
        if (first.at(i) == second.at(i))
            continue;
        else {
            if (first.at(i) > second.at(i))
                return 1;
            else
                return -1;
        }
    }
    
    if (first.size() == second.size())
        return 0;
    else {
        int maxSize = std::max(first.size(), second.size());
        bool isFirstBigger = first.size() > second.size();
        
        for (int i = minSize; i < maxSize + minSize; ++i) {
            char firstChar, secondChar;
            
            if (isFirstBigger) {
                if (i >= maxSize)
                    firstChar = second.at(i - maxSize);
                else
                    firstChar = first.at(i);
            } else
                firstChar = second.at(i - minSize);
            
            if (isFirstBigger)
                secondChar = first.at(i - minSize);
            else {
                if (i >= maxSize)
                    secondChar = first.at(i - maxSize);
                else
                    secondChar = second.at(i);
            }
            
            if (firstChar > secondChar)
                return 1;
            else if (firstChar < secondChar)
                return -1;
        }
        return 0;
    }
}

void sortVector(std::vector<std::string> *strings, int firstElement, int lastElement) {

    if (lastElement - firstElement == 0)
        return;
        
    else if (lastElement - firstElement == 1) {
        
        if (compare((*strings)[firstElement], (*strings)[lastElement]) < 0) {
            std::string string = (*strings)[firstElement];
            (*strings)[firstElement] = (*strings)[lastElement];
            (*strings)[lastElement] = string;
        }
        
    } else {
        int middleIter = (firstElement + (lastElement - firstElement) / 2) + 1;

        sortVector(strings, firstElement, middleIter - 1);
        sortVector(strings, middleIter, lastElement);

        int firstIter = firstElement;
        int secondIter = middleIter;
        std::vector<std::string> middleStrs(lastElement - firstElement + 1);

        for (int i = 0; i <= lastElement - firstElement; ++i) {
            
            if (compare((*strings)[firstIter], (*strings)[secondIter]) >= 1) {
                middleStrs[i] = (*strings)[firstIter++];
                
                if (firstIter == middleIter) {
                    for (int j = i + 1; j <= lastElement - firstElement; ++j)
                        middleStrs[j] = (*strings)[secondIter++];
                    break;
                }
                
            } else {
                middleStrs[i] = (*strings)[secondIter++];
                
                if (secondIter == lastElement + 1) {
                    for (int j = i + 1; j <= lastElement - firstElement; ++j)
                        middleStrs[j] = (*strings)[firstIter++];
                    break;
                }
                
            }
        }

        for (int i = 0; i <= lastElement - firstElement; ++i)
            (*strings)[firstElement + i] = middleStrs[i];
    }
}


int main() {
    std::list<std::string> strings;
    std::string str;

    while (std::cin >> str) {
        strings.push_front(str);
    }

    std::vector<std::string> strs(strings.size());
    int size = strings.size();
    for (int i = 0; i < size; ++i) {
        strs[i] = strings.front();
        strings.pop_front();
    }

    sortVector(&strs, 0, strs.size() - 1);
    
    for (const std::string &string : strs)
        printf("%s", string.c_str());

    return 0;

}