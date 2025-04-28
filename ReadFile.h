#include <iostream>
#include <string>
// fstream es para entrada y salida desde archivos
#include <fstream>
// manejo de cadenas de texto como si fuesen stream, --> la gracia es que hay deteccion automatica del tipo de dato
#include <sstream>
#include <chrono>

#include "RiverCrossing.h"


class ReadFile{
    public:        
        ReadFile(std::string nombreArchivo);
        ~ReadFile();
};