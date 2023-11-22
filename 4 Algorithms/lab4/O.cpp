#include <iostream>
#include <vector>
#include <set>
using namespace std;

    struct LKSHats {
        set<LKSHats *> neighbors;
        bool isChecked = false;
        bool splitting = false;
    };
    
    bool isSplitted(vector<LKSHats> &vectorLKSHats, LKSHats *currentLKSHonok, bool splitting = true) {
        currentLKSHonok->splitting = splitting;
        currentLKSHonok->isChecked = true;
        
        for (auto &&newLKSHonok:currentLKSHonok->neighbors) {
            if (newLKSHonok->isChecked) {
                if (newLKSHonok->splitting == splitting) {
                    return false;
                }
            } else {
                bool res = isSplitted(vectorLKSHats, newLKSHonok, !splitting);
                if (!res) {
                    return res;
                }
            }
        }
        return true;
    }
    
    int main() {
        
        int countLKSHATs;
        int countPars;
        cin >> countLKSHATs >> countPars;
        bool isYes = true;
        vector<LKSHats> LKSHatsVector(countLKSHATs);
    
        for (int i = 0; i <= countPars - 1; i++) {
            int responser;
            int reciever;
            cin >> responser;
            cin >> reciever;
            LKSHatsVector[reciever - 1].neighbors.insert(&LKSHatsVector[responser - 1]);
            LKSHatsVector[responser - 1].neighbors.insert(&LKSHatsVector[reciever - 1]);
        }
    
        for (int i = 0; i <= LKSHatsVector.size() - 1 && isYes; i++) {
            if (!LKSHatsVector[i].isChecked) {
                isYes &= isSplitted(LKSHatsVector, &LKSHatsVector[i]);
            }
        }
    
        if (isYes) {
            printf("YES");
        } else {
            printf("NO");
        }
    
        return 0;
    }
