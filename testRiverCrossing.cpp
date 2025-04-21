#include "RiverCrossing.h"

int main() {
    RiverCrossing r(100);
    State* s = r.solve();
    int* arr = new int[3]{1, 2, 3};
    int combCount = 0;
    int** combs = r.combinaciones(arr, 3, 3, combCount);

    for (int i = 0; i < combCount; i++) {
        cout << "Combinacion " << i + 1 << ": ";
        for (int j = 0; j < 3 && combs[i][j] != 0; j++) {
            cout << combs[i][j] << " ";
        }
        cout << endl;
    }

    // Liberar memoria
    for (int i = 0; i < combCount; i++) {
        delete[] combs[i];
    }
    delete[] combs;
    delete[] arr;

    return 0;
}