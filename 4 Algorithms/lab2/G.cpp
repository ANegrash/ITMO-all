#include <vector>
#include <string>
#include <iostream>

int main() {
    const int alfabetSize = 26;
    const int differenceInAscii = 97;
    std::vector<int> symbolWeightVector(alfabetSize, 0);
    std::vector<int> symbolNumberVector(alfabetSize, 0);
    std::vector<int> charsInMiddle(alfabetSize, 0);
    std::vector<char> inputCharsVector(alfabetSize, 0);

    std::string input_string;
    std::cin >> input_string;

    int countChars = input_string.size();

    for (int i = 0; i <= countChars - 1; i++) {
        symbolNumberVector[input_string.at(i) - differenceInAscii] += 1;
    }

    for (int i = 0; i < alfabetSize; i++) {
        std::cin >> symbolWeightVector[i];
    }

    for (int i = 0; i < alfabetSize; i++) {
        int maxWeight = -1;
        int indexOfMaxWeight = -1;
        
        for (int j = 0; j < alfabetSize; j++) {
            if (maxWeight < symbolWeightVector[j]) {
                maxWeight = symbolWeightVector[j];
                indexOfMaxWeight = j;
            }
        }
        
        inputCharsVector[i] = (char) (indexOfMaxWeight + differenceInAscii);
        symbolWeightVector[indexOfMaxWeight] = -1;
    }

    for (int i = 0; i < alfabetSize; i++) {
        if (symbolNumberVector[inputCharsVector[i] - differenceInAscii] == 1) {
            charsInMiddle.at(inputCharsVector[i] - differenceInAscii) = 1;
            symbolNumberVector[inputCharsVector[i] - differenceInAscii] = 0;
        } else
        if (symbolNumberVector[inputCharsVector[i] - differenceInAscii] == 2) {
            symbolNumberVector[inputCharsVector[i] - differenceInAscii] = 1;
            printf("%c", inputCharsVector[i]);
        } else
        if (symbolNumberVector[inputCharsVector[i] - differenceInAscii] >= 3) {
            charsInMiddle.at(inputCharsVector[i] - differenceInAscii) = symbolNumberVector[inputCharsVector[i] - 97] - 2;
            symbolNumberVector[inputCharsVector[i] - differenceInAscii] = 1;
            printf("%c", inputCharsVector[i]);
        }
    }

    for (int i = 0; i < alfabetSize; i++) {
        int sizeOfChars = charsInMiddle[inputCharsVector[i] - differenceInAscii];
        
        for (int j = 0; j < sizeOfChars; j++) {
            printf("%c", inputCharsVector[i]);
        }
    }

    for (int i = alfabetSize - 1; i >= 0; i--) {
        if (symbolNumberVector[inputCharsVector[i] - differenceInAscii] == 1) {
            printf("%c", inputCharsVector[i]);
        }
    }

    return 0;
}