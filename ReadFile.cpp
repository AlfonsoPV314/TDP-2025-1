#include "ReadFile.h"

ReadFile::ReadFile(std::string nombreArchivo) {
    Graph* incompMtrx;
    int boatCant = 0, psgs = 0;
    Vector* boatVector = new Vector();
    Boat* boats;
    // Abrir el archivo en modo lectura
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) { // Verificar si el archivo se abrió correctamente
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    std::string linea; // Variable para almacenar cada línea leída
    int i = 0;

    while (std::getline(archivo, linea)) { // Leer línea por línea, falso si no logra lleer mas lineas
        std::cout << linea << std::endl;
        std::istringstream iss(linea); /// stream de texto
        int indxAux = 0;
        int edgeAux;
        while (iss) { // Mientras haya contenido en el stream
            int numero;
            iss >> numero; // NOTAR  que >> es un operador de extracción, no es una función
            // NOTAR que se detecta automaticamente el tipo de dato
            if (iss) { // si aun queda contenido en el stream
                // std::cout << "Número leído: " << numero;
                if(i == 0){
                    // std::cout << ", ya que es la primera linea, se asigna a psgs" << std::endl;
                    psgs = numero;
                    incompMtrx = new Graph(psgs);
                }
                else if(i == 1){
                    // cout << ", ya que es la segunda linea, se asigna el tamaño del vector de incompatibilidades" << endl;
                    boatCant++;
                    boatVector->push(numero);
                }
                else if(i == 2){
                    // std::cout << ", ya que es la tercera linea, se asigna el fuel del bote " << indxAux << std::endl;
                    boats[indxAux].setFuel(numero);
                    indxAux++;
                }
                else{
                    if(indxAux == 0){
                        // std::cout << ", estoy leyendo vertices pero aun no se el siguiente vertice para la arista" << std::endl;
                        edgeAux = numero;
                        indxAux++;
                    }
                    else{
                        // std::cout << ", estoy leyendo vertices: la arista es entre " << edgeAux << " y " << numero << std::endl;
                        incompMtrx->addEdge(edgeAux, numero);
                        indxAux = 0;
                    }
                }
            } else {
                if(i == 1){
                    // std::cout << "he terminado de leer la segunda linea! creando el arreglo de " << boatCant << " botes..." << std::endl;
                    boats = new Boat[boatCant];
                    for(int j = 0; j < boatCant; j++){
                        // std::cout << "Barco " << j << " creado con capacidad " << boatVector->getPos(j) << std::endl;
                        boats[j].setIdSize(j, boatVector->getPos(j));
                    }
                }
                indxAux = 0;
                i++;
                // std::cerr << "Pasando a la siguiente linea..." << std::endl;
            }
        }
    }
    RiverCrossing r(1000, psgs, boatCant, boats, incompMtrx);
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
    else{
        cout << "No se encontró solución." << endl;
    }
    cout << "Tiempo de ejecución: " << duration.count() << " ms" << endl;

    archivo.close();
}