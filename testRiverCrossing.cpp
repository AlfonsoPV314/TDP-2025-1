#include "RiverCrossing.h"
#include <chrono>


int main() {
    int psgs = 9;
    int capacidad = 0; // capacidad del barco
    int boatCant = 3; // cantidad de barcos
    Boat* boats = new Boat[boatCant];
    boats[0].setupBoat(0, 1, 100);
    boats[1].setupBoat(1, 2, 98);
    boats[2].setupBoat(2, 1, 99);
    for(int i = 0; i < boatCant; i++) {
        capacidad += boats[i].capacidad;
    }
    Graph* incompMtrx = new Graph(psgs);
    incompMtrx->addEdge(0, 2);
    incompMtrx->addEdge(1, 3);
    incompMtrx->addEdge(1, 5);
    incompMtrx->addEdge(1, 6);
    incompMtrx->addEdge(2, 4);
    incompMtrx->addEdge(2, 7);
    incompMtrx->addEdge(3, 4);
    incompMtrx->addEdge(4, 5);
    incompMtrx->addEdge(4, 6);
    incompMtrx->addEdge(5, 7);
    incompMtrx->addEdge(5, 8);
    incompMtrx->addEdge(6, 7);
    incompMtrx->addEdge(6, 8);
    RiverCrossing r(100, psgs, boatCant, boats, incompMtrx);
    auto start = std::chrono::high_resolution_clock::now();
    State* s = r.solve(boats);
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