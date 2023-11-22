#include <iostream>
#include <vector>
#include <list>
using namespace std;

struct CustomStruct {
    list<CustomStruct *> listItems;
    int key = -1;
    bool isChecked = false;
};

void chainCheck(CustomStruct *strItem) {
    for (auto &&listItems :strItem->listItems) {
        if (listItems->isChecked)
            continue;
        else {
            listItems->isChecked = true;
            chainCheck(listItems);
        }
    }
}

int main() {
    int countPigs;
    cin >> countPigs;

    vector<CustomStruct> moneyPigs(countPigs);

    for (int i = 0; i < countPigs; ++i) {
        int keyPosition = 0;
        cin >> keyPosition;
        moneyPigs[i].key = keyPosition - 1;
        moneyPigs[keyPosition - 1].listItems.push_front(&moneyPigs[i]);
    }

    int countResult = 0;

    for (int i = 0; i < countPigs; ++i) {
        
        if (moneyPigs[i].listItems.empty() && !moneyPigs[i].isChecked) {
            countResult++;
            moneyPigs[i].isChecked = true;
            CustomStruct *listItem = &moneyPigs[i];
            
            while (!moneyPigs[listItem->key].isChecked) {
                moneyPigs[listItem->key].isChecked = true;
                chainCheck(listItem);
                listItem = &moneyPigs[listItem->key];
            }
            chainCheck(listItem);
        }
    }

    for (int i = 0; i < countPigs; ++i) {
        
        if (!moneyPigs[i].isChecked) {
            countResult++;
            moneyPigs[i].isChecked = true;
            CustomStruct *listItem = &moneyPigs[i];
            
            while (!moneyPigs[listItem->key].isChecked) {
                moneyPigs[listItem->key].isChecked = true;
                listItem = &moneyPigs[listItem->key];
            }
        }
    }

    printf("%d", countResult);

    return 0;
}