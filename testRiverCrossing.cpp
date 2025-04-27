#include "RiverCrossing.h"
#include <chrono>


int main() {
    RiverCrossing r(1000);
    auto start = std::chrono::high_resolution_clock::now();
    State* s = r.solve();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
    if (s != nullptr) {
        s->printPath();
        cout << endl;
        cout << "en " << s->depth << " pasos" <<endl;
    } 
    cout << "Tiempo de ejecución: " << duration.count() << " ms" << endl;

    // // Test de combinaciones
    // int arr[3] = {1, 2, 3};
    // int* test = arr;
    // for (int i = 0; i < 3; i++) {
    //     cout << test[i] << " ";
    // }
    // std::cout << std::endl;
    // int combCount = 0;

    // // Generar combinaciones
    // int** combinations = r.combinaciones(test, 3, 1, combCount);

    // // Imprimir las combinaciones generadas
    // std::cout << "Se generaron " << combCount << " combinaciones:" << std::endl;
    // for (int i = 0; i < combCount; i++) {
    //     std::cout << "Combinación " << i + 1 << ": ";
    //     for (int j = 0; j < 3 ; j++) {
    //         std::cout << combinations[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }


    // // Liberar memoria de las combinaciones
    // for (int i = 0; i < combCount; i++) {
    //     delete[] combinations[i];
    // }
    // delete[] combinations;

    return 0;
}