#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;
namespace fs = filesystem;

int main(int argc, char* argv[]) {
    unordered_map<string, vector<pair<string, int>>> invertedIndex;

    if (argc < 3) {
        cerr << "No dio suficientes argumentos";
        return 1;  // Termina el programa con un código de error
    }

    string nombreCarpetaOut = argv[1];
    string pathOutput = "../Trabajo5/" + nombreCarpetaOut;
    for (const auto& entry : fs::directory_iterator(pathOutput)) {
        if (entry.is_regular_file()) {
            // Verifica si el nombre del archivo comienza con "file"
            string filename = entry.path().filename();
            if (filename.rfind("file",0) == 0) {
                ifstream inputFile(entry.path());
                string line;
            
                while (getline(inputFile, line)) {
                    
                    istringstream iss(line);
                    string word;
                    int count;

                    if (getline(iss, word, ',') && iss >> count) {
                        // Agrega la palabra y su información al índice invertido
                        invertedIndex[word].emplace_back(filename, count);
                    }
                }
            }
        }
    }

    // Escribe el índice invertido en el archivo "indiceInvertido.idx"
    string nombreIndexFile = argv[2];
    string pathIndex = "../Trabajo5/" + nombreIndexFile;
    ofstream outputFile(pathIndex);
    for (const auto& entry : invertedIndex) {
        outputFile << entry.first << ":";
        for (const auto& info : entry.second) {
            outputFile << "(" << info.first << "," << info.second << ");";
        }
        outputFile << "\n";
    }

    cout << "El proceso pid = " << getpid() << " genero el archivo: " << nombreIndexFile << endl;


    return 0;
}
