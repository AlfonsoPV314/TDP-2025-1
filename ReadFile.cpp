#include "ReadFile.h"

// Entradas: nombre del archivo (std::string)
// Salidas: ReadFile nuevo (ReadFile)
// Descripcion: Constructor de un ReadFile. Lee un archivo de acuerdo a las especificaciones del enunciado.
ReadFile::ReadFile(std::string nombreArchivo) {
    Graph* incompMtrx;  // matriz de incompatibilidades
    int boatCant = 0, psgs = 0; // cantidades de botes y pasajeros
    Vector* boatVector = new Vector();  // vector de botes (arreglo dinámico)
    Boat* boats;    // arreglo estático de botes (para cuando sepa cuantos botes hay)

    // Abrir el archivo en modo lectura
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) { // Verificar si el archivo se abrió correctamente
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    std::string linea; // Variable para almacenar cada línea leída
    int i = 0;

    while (std::getline(archivo, linea)) { // Leer línea por línea,
        std::istringstream iss(linea); // stream de texto
        int indxAux = 0;
        int edgeAux;
        while (iss) { // Mientras haya contenido en el stream
            int numero;
            iss >> numero; 
            if (iss) { // si aun queda contenido en el stream
                if(i == 0){
                    // ya que es la primera linea, se asigna a psgs
                    psgs = numero;
                    incompMtrx = new Graph(psgs);
                }
                else if(i == 1){
                    // ya que es la segunda linea, se asigna el tamaño del vector de incompatibilidades
                    boatCant++;
                    boatVector->push(numero);
                }
                else if(i == 2){
                    // ya que es la tercera linea, se asigna el fuel del bote
                    boats[indxAux].setFuel(numero);
                    indxAux++;
                }
                else{
                    if(indxAux == 0){
                        // estoy leyendo vertices pero aun no se el siguiente vertice para la arista
                        edgeAux = numero;
                        indxAux++;
                    }
                    else{
                        // estoy leyendo vertices. Ahora que se los 2 vertices, puedo crear arista
                        incompMtrx->addEdge(edgeAux, numero);
                        indxAux = 0;
                    }
                }
            } else {
                if(i == 1){
                    // he terminado de leer la segunda linea! creando el arreglo de botes
                    boats = new Boat[boatCant];
                    for(int j = 0; j < boatCant; j++){
                        boats[j].setIdSize(j, boatVector->getPos(j));
                    }
                }
                indxAux = 0;
                i++;
            }
        }
    }
    RiverCrossing r(1000, psgs, boatCant, boats, incompMtrx);
    auto start = std::chrono::high_resolution_clock::now();
    State* s = r.solve(boats);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << endl << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl << endl;
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