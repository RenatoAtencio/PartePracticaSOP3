#include "../include/funciones.h"

using namespace std;

// Verifica la existencia de un archivo
bool verificarArchivo(string path){
    ifstream file(path);
    return (file.good());
}