#include <vector>
#include <algorithm>
#include <iostream>
#include <deque>
using namespace std;

struct StructureMemory {
    bool isEmpty;
    int beforeElement;
    int dimension;
    int place;
    StructureMemory *before;
    StructureMemory *after;

    StructureMemory(
        bool isEmpty, 
        int beforeElement, 
        int dimension, 
        StructureMemory *before, 
        StructureMemory *after
    ) {
        this->isEmpty = isEmpty;
        this->beforeElement = beforeElement;
        this->dimension = dimension;
        place = -1;
        
        this->before = before;
        if (before)
            before->after = this;
        
        this->after = after;
        if (after)
            after->before = this;
    }

    void remove() {
        if (after)
            after->before = before;
        
        if (before)
            before->after = after;
    }

};

struct OtherData {
    vector<StructureMemory *> customData;

    void removeItemData(StructureMemory *structure);

    void plusItemData(StructureMemory *structurePart);

    int father(int f) {
        return (f - 1) / 2;
    }

    int l(int left) {
        return 2 * left + 1;
    }

    int r(int right) {
        return 2 * right + 2;
    }

    void streamIn(int place);

    void streamOut(int place);

    void otherDataPop(int place);

    void otherDataPush(StructureMemory *structurePart);

    void tradePartStructure(int pos1, int pos2) {
        StructureMemory *temp = customData[pos1];
        customData[pos1] = customData[pos2];
        customData[pos2] = temp;
        customData[pos1]->place = pos1;
        customData[pos2]->place = pos2;
    }

    bool isGreater(int bigger, int lower) {
        bool result = customData[bigger]->dimension > customData[lower]->dimension;
        return result;
    }
};

void OtherData::streamIn(int place) {
    while (father(place) > -1 && isGreater(place, father(place))) {
        tradePartStructure(father(place), place);
        place = father(place);
    }
}

void OtherData::streamOut(int place) {
    while (true) {
        int currentPlace = place;
        
        if (l(place) < customData.size() && isGreater(l(place), currentPlace))
            currentPlace = l(place);
        
        if (r(place) < customData.size() && isGreater(r(place), currentPlace))
            currentPlace = r(place);
        
        if (currentPlace == place)
            return;
        
        tradePartStructure(currentPlace, place);
        place = currentPlace;
    }
}

void OtherData::otherDataPop(int place) {
    if (customData.size() >= 2 && place <= customData.size() - 2)
        tradePartStructure(place, customData.size() - 1);

    customData.pop_back();
    
    if (!customData.empty() && place <= customData.size() - 1) {
        streamOut(place);
        streamIn(place);
    }
}

void OtherData::otherDataPush(StructureMemory *structurePart) {
    structurePart->place = customData.size();
    customData.push_back(structurePart);
    streamIn(structurePart->place);
}

void OtherData::removeItemData(StructureMemory *structure) {
    int place = structure->place;
    otherDataPop(place);
    delete structure;
}

void OtherData::plusItemData(StructureMemory *structurePart) {
    structurePart->isEmpty = true;

    bool beforeEmpty = structurePart->before && structurePart->before->isEmpty;
    bool afterEmpty = structurePart->after && structurePart->after->isEmpty;

    if (!(beforeEmpty || afterEmpty)) {
        otherDataPush(structurePart);
        return;
    }
    
    if (!afterEmpty) {
        structurePart->before->dimension += structurePart->dimension;
        streamIn(structurePart->before->place);
        structurePart->remove();
        delete structurePart;
        return;
    }
    
    if (!beforeEmpty) {
        structurePart->after->dimension += structurePart->dimension;
        structurePart->after->beforeElement = structurePart->beforeElement;
        streamIn(structurePart->after->place);
        structurePart->remove();
        delete structurePart;
        return;
    }

    structurePart->before->dimension += structurePart->after->dimension;
    StructureMemory *toRemove = structurePart->after;
    structurePart->after->remove();
    removeItemData(toRemove);
    
    structurePart->before->dimension += structurePart->dimension;
    streamIn(structurePart->before->place);
    structurePart->remove();
    delete structurePart;
}

int main() {
    OtherData oData;
    int sizeMem;
    int orderNumber;
    cin >> sizeMem >> orderNumber;

    vector<StructureMemory *> all_memory(orderNumber, nullptr);
    StructureMemory *fullStructure = new StructureMemory(true, 0, sizeMem, nullptr, nullptr);
    oData.otherDataPush(fullStructure);

    for (int i = 0; i < orderNumber; i++) {
        
        int item;
        cin >> item;

        if (item >= 1) {
            
            if (!oData.customData.empty()) {
                
                StructureMemory *structure = oData.customData[0];
                if (structure->dimension > item - 1) {
                    
                    StructureMemory *structurePointer = new StructureMemory(false, structure->beforeElement, item, structure->before, structure);
                    all_memory[i] = structurePointer;

                    structure->beforeElement += item;
                    structure->dimension -= item;
                    
                    if (structure->dimension == 0) {
                        structure->remove();
                        oData.removeItemData(structure);
                    } else
                        oData.streamOut(structure->place);

                    printf("%d\n", structurePointer->beforeElement + 1);
                    continue;
                }
            }

            printf("%d\n", -1);
        } else {
            item = abs(item) - 1;
            
            if (all_memory[item]) {
                
                if (!all_memory[item]->isEmpty) {
                    oData.plusItemData(all_memory[item]);
                    all_memory[item] = nullptr;
                }
            }
        }
    }
}