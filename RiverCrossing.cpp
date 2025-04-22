#include "RiverCrossing.h"

RiverCrossing::RiverCrossing(int size) {
//    open = new Stack(size); // se cambio a heap
    open = new Heap(size);
    all = new Stack(size);
    psgs = 3;
    capacidad = 1; // capacidad del barco
    incompMtrx = new Graph(3);
    incompMtrx->addEdge(ZORRO, CABRA);
    incompMtrx->addEdge(CABRA, REPOLLO);
    boats = new Boat[1];
    for(int i = 0; i < 1; i++) {
        boats[i].setupBoat(i, psgs, 100);
    }
}

RiverCrossing::~RiverCrossing(){
    delete open;
    delete all;
}

State* RiverCrossing::solve() {
    // paso 1: generar estado inicial e insertar en open
    State *init = new State();
    init->setInitialState(psgs, boats);
    init->printState();
    open->push(init);
    all->push(init);

    // paso 2: mientras open no este vacio
    while (open->top != 0) { // recordar que top es el lugar vacío en el arreglo
        State *s = open->pop();
        cout << "[RiverCrossing::solve] NUEVA ITERACION! :D. Camino actual: " << endl;
        s->printPath();
        cout << endl;

        // paso 3: preguntamos si es la solucion
        if (s->isFinalState()) {
            return s;
        }

        int combCount = 0;

        int* arr = s->getPassengers(psgs, combCount);


        int** combs = combinaciones(arr, psgs, capacidad, combCount); // Generar combinaciones

        cout << "[RiverCrossing::solve] Combinaciones generadas: " << combCount << endl;

        for (int i = 0; i < combCount; i++) {
            cout << "[RiverCrossing::solve] Verificando si cruzar con {";
            for (int j = 0; j < capacidad ; j++) {
                cout << combs[i][j] - 1 << " ";
            }
            cout << "}" << endl;
            State *ns = s->cross(combs[i], capacidad, incompMtrx); // Intentar cruzar con esta combinación
            if (ns != nullptr) {
                priorityCalc(ns);
                capacidadCalc(ns);
                if (!all->find(ns)) {
                    cout << "[RiverCrossing::solve] Estado no estaba en stack. Actualizando heap y stack..." << endl;
                    ns->printState();
                    all->push(ns);
                    open->push(ns);
                }else{
                    cout << "[RiverCrossing::solve] Estado ya estaba en stack. No se agrega." << endl;
                }
            }

        }

        cout << "[RiverCrossing::solve] Heap: " << endl;
        open->printHeap();
        cout << endl;

        // Liberar memoria de las combinaciones (problemas en combs[2])
        // for (int i = 0; i < combCount; i++) {
        //     if (combs[i] == nullptr || sizeof(combs[i]) == 0) {
        //         cout << "Error: combs[" << i << "] es nullptr, no se libera." << endl;
        //     } else {
        //         cout << "Liberando combs[" << i << "]." << endl;
        //         // Imprimir la combinación antes de liberar
        //         cout << "Combinación: {";
        //         for (int j = 0; combs[i][j] != -1; j++) {
        //             cout << combs[i][j] << (combs[i][j + 1] != 0 ? ", " : "");
        //         }
        //         cout << "}" << endl;
        //         delete[] combs[i];
        //         combs[i] = nullptr; // Prevenir doble liberación
        //     }
        // }
        
        

    }

    return nullptr; // caso nuestra búsqueda no llegó a solución
}

void RiverCrossing::capacidadCalc(State* s){
    // Se calcula la capacidad del barco como la cantidad de pasajeros en la orilla activa
    int count = 0;
    for (int i = 0; i < sizeof(s->boats); i++) {
        s->boats[i].updateFuelAmt();
        if (!s->boats[i].isEmpty()) {
            count += s->boats[i].size;
        }
    }
    capacidad = count;
}


// NOTA: para capacidad = 3, esto hace 10 fokin combinaciones... o hago caso especial, o cambio heuristica. si usas pasos en vez de all->currentSize, el caso con capacidad 3 es 4 pasos, y el caso con capacidad 1 es 9 pasos en vez de 8. estudiar esta heuristica...
void RiverCrossing::priorityCalc(State* s) {
    // Se calcula la prioridad como la cantidad de elementos en la orilla
    // izquierda que no son incompatibles entre si
    s->priority = s->depth * 2;
    for (int i = 0; i < 3; i++) {
        if (s->Der[i]) {
            s->priority++;
        }
    }
}

int** RiverCrossing::combinaciones(int* arr, int n, int size, int& combCount) {
    cout << "[RiverCrossing::combinaciones] INPUT: " << endl;
    cout << "arr: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "n: " << n << endl;
    cout << "size: " << size << endl;
    cout << "combCount: " << combCount << endl;

    // Determinar el tamaño real de `arr` (sin valores <= 0)
    int cantReal = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            cantReal++;
        }
    }
    int* arrReal = new int[cantReal];
    int idx = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            arrReal[idx++] = arr[i];
        }
    }
    n = cantReal; // Actualizar `n` al tamaño real

    // Determinar la cantidad máxima de combinaciones posibles
    int maxCombinations = (1 << n) - 1; // 2^n - 1 combinaciones
    combCount = 0;

    // Crear el arreglo 2D para almacenar combinaciones (+1 para la combinación adicional)
    int** output = new int*[maxCombinations + 1];
    for (int i = 0; i < maxCombinations; i++) {
        output[i] = new int[size](); // Inicializa en ceros
    }

    // Generar combinaciones desde el tamaño más grande hacia el más pequeño
    for (int r = size; r >= 1; r--) {
        int* data = new int[r]; // Espacio temporal para una combinación
        combinacion(output, arrReal, data, 0, n - 1, 0, r, combCount);
        delete[] data; // Liberar memoria del temporal
    }

    // Agregar combinación adicional: solo `-1` al principio, seguido de ceros
    output[combCount] = new int[size](); // Inicializa en ceros
    output[combCount][0] = -1;          // Establecer el primer elemento en -1
    combCount++;

    delete[] arrReal; // Liberar memoria de `arrReal`
    return output;
}

void RiverCrossing::combinacion(int**& output, int* arr, int* data, int start, int end, int index, int r, int& combIndex) {
    // Caso base: combinación completa
    if (index == r) {
        for (int i = 0; i < r; i++) {
            output[combIndex][i] = data[i]; // Copiar al resultado
        }
        combIndex++;
        return;
    }

    // Generar combinaciones recursivamente
    for (int i = start; i <= end && end - i + 1 >= r - index; i++) {
        data[index] = arr[i];
        combinacion(output, arr, data, i + 1, end, index + 1, r, combIndex);
    }
}
