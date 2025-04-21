#include "RiverCrossing.h"

int main() {
    RiverCrossing r(100);
    State* s = r.solve();
    cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
    if (s != nullptr) {
        cout << "[main] Solucion encontrada!" << endl;
        s->printPath();
        cout << endl;
    } else {
        cout << "[main] No se encontro solucion." << endl;
    }
    cout << "en " << r.pasos << " pasos" <<endl;
    int* arr = new int[3]{4, 2, 1};
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