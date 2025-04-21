#include <iostream>
#include "MetaVector.h"

using namespace std;

// Function to find all combinations of passengers
void findCombs(Vector* psgs, MetaVector* comb, Vector* temp, int numPsgs, int start) {
    if (start == numPsgs) {
        return;
    }
    for (int i = start; i < numPsgs; i++) {
        temp->push(psgs->getPos(i));  // Add current passenger to temporary combination
        int* clonedData = new int[temp->current];  // Clone the current combination
        for (int j = 0; j < temp->current; j++) {
            clonedData[j] = temp->data[j];
        }
        comb->push(clonedData);  // Add the cloned combination to MetaVector
        findCombs(psgs, comb, temp, numPsgs, i + 1); // Recursive call
        temp->pop();  // Backtrack
    }
}

int main() {
    // Initialize a static array of passengers
    int arr[3] = {1, 2, 3};

    // Create a Vector for passengers
    Vector psgs(arr, 3);

    // Create a MetaVector to store all combinations
    MetaVector comb;

    // Create a temporary Vector for building combinations
    Vector temp;

    // Generate all combinations
    findCombs(&psgs, &comb, &temp, psgs.current, 0);

    // Print all combinations
    for (int i = 0; i < comb.current; i++) {
        cout << "Combination " << i + 1 << ": ";
        int* combination = comb.getPos(i);  // Get the int* array from MetaVector
        for (int j = 0; combination[j] != 0; j++) {  // Iterate through the combination
            cout << combination[j] << " ";
        }
        cout << endl;
    }

    return 0;
}
