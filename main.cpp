#include "ReadFile.h"

int main(int argc, char* argv[]){
    std::cout << "Enter file name: ";
    std::string fileName;
    std::getline(std::cin, fileName);
    ReadFile* read = new ReadFile(fileName);
}