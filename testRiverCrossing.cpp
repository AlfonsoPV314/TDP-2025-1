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
    int arr[3] = {3, 2, 1};
    int* test = s->incompMtrx->sortByIncomp(arr, 3);
    for (int i = 0; i < 3; i++) {
        cout << test[i] << " ";
    }
    std::cout << std::endl;
    int combCount = 0;

    // Generar combinaciones
    int** combinations = r.combinaciones(test, 3, 3, combCount);

    // Imprimir las combinaciones generadas
    std::cout << "Se generaron " << combCount << " combinaciones:" << std::endl;
    for (int i = 0; i < combCount; i++) {
        std::cout << "Combinación " << i + 1 << ": ";
        for (int j = 0; j < 3 && combinations[i][j] > 0; j++) {
            std::cout << combinations[i][j] << " ";
        }
        std::cout << std::endl;
    }


    // Liberar memoria de las combinaciones
    for (int i = 0; i < combCount; i++) {
        delete[] combinations[i];
    }
    delete[] combinations;

    return 0;
}