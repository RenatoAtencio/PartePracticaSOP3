#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <filesystem>
#include <vector>
#include "../include/json.hpp"
#include <unistd.h>

using namespace std;
namespace fs = std::filesystem;

// ejecutar: ./makeCircular ../Trabajo5/data/databases/ circular.dre

// Funcion que hace parse de un string segun un char delimitador
vector<string> parseString(string data, char delimiter) {
    vector<string> files;
    istringstream stream(data);
    string file;
    while (getline(stream, file, delimiter)) {
        files.push_back(file);
    }
    // for (const auto& e : files) {
    //     cout << e << endl;
    // }
    return files;
}

void makeCircular(string root_path, string dirs, string data) {
    size_t posRoot = root_path.find("=");
    root_path = root_path.substr(posRoot + 1);
    // cout << root_path << endl;
    // Verificacion carpeta dirbase
    if (!fs::exists(root_path) && !fs::is_directory(root_path)) {
        cout << "La carpeta '" << root_path << "' no existe." << endl;
        exit(EXIT_FAILURE);
    }

    // le quito el "dirs=" y lo paso los dirs a un vector
    size_t pos = dirs.find("=");
    dirs = dirs.substr(pos + 1);
    vector<string> vectorDirs = parseString(dirs, ';');
    // Creo un vector con los dirs y sus respectivos files
    vector<string> files = parseString(data, '|');

    // Crea los directorios
    for (const auto& dir : vectorDirs) {
        // cout << root_path << " " <<dir << endl;
        mkdir((root_path + dir).c_str(), S_IRWXU | S_IRWXG | S_IRWXO); // Crea las carpetas
    }

    // cout << root_path + vectorDirs[0] << " " << root_path + vectorDirs[vectorDirs.size()-1] << endl;
    // Crea el enlace virtual (Creo que no sirve en wsl)
    
    string carpeta1 = root_path + vectorDirs[0];
    string carpeta2 = root_path + vectorDirs[vectorDirs.size() - 1];
    string enlace_virtual = "enlace_virtual";

    try {
        fs::create_symlink(carpeta1, carpeta2 + "/" + enlace_virtual);
        cout << "Enlace simbólico creado correctamente." << endl;
    } catch (const exception& e) {
        cerr << "Error al crear enlace simbólico: " << e.what() << endl;
    }


    // Crea los files en sus respectivas carpetas
    for (const auto& dirFiles : files) {
        string allFiles, dir;
        size_t posFile = dirFiles.find("=");
        dir = dirFiles.substr(0, posFile);
        allFiles = dirFiles.substr(posFile + 1);
        // cout << allFiles << " " << dir << endl;
        vector<string> vectorFiles = parseString(allFiles, ';');
        for (const auto& file : vectorFiles) {
            ofstream outFile(root_path + dir + "/" + file);
            if (!outFile.is_open()) {
                cerr << "No se pudo crear el archivo: " << file << endl;
            }
        }
    }
}

int main(int argc, char* argv[]) {
if (argc != 3) {
        cerr << "Para ejecutar use: " << argv[0] << " <ruta_archivo.dre> <nombre_archivo.dre>" << endl;
        return EXIT_FAILURE;
    }
    string path_dre, name_dre;
    path_dre = argv[1];
    name_dre = argv[2];
    string path_dirbase, dirs, data;

    // Parse del path_dirbase y los dirs
    ifstream file(path_dre + name_dre);
    if (file.is_open()) {
        string linea;
        while (getline(file, linea)) {
            if (path_dirbase.empty() && (linea.rfind("dirbase", 0) == 0)) {
                path_dirbase = linea;
                // cout << path_dirbase << endl;
            }
            else if (dirs.empty() && (linea.rfind("dirs", 0) == 0)) {
                dirs = linea;
            }
            else {
                data += linea + "|";
            }
        }
        // cout << path_dirbase << endl << dirs << endl << data << endl;
        file.close();
    }
    else {
        cerr << "El archivo '" << name_dre << "' no existe en el path indicado" << endl;
        exit(EXIT_FAILURE);
    }

    // Llamo a la funcion makeCiruclar si existen los valores de dirbase y dirs, sino tiro error
    if (!path_dirbase.empty() && !dirs.empty()) {
        makeCircular(path_dirbase, dirs, data);
    }
    else {
        cerr << "El archivo .dre no contiene dirbase o dirs" << endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}