#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <filesystem>
#include <vector>
#include "../include/json.hpp"
#include <unistd.h>

using namespace std;\

// ./makeCircular ../Trabajo5/data/databases/ circular.dre

// Funcion que hace parse de un string segun un char delimitador
vector<string> parseString(string data, char delimiter){
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

void makeCircular(string root_path,string dirs,string data){
    size_t posRoot = root_path.find("=");
    root_path = root_path.substr(posRoot+1);
    // le quito el "dirs=" y lo paso los dirs a un vector
    size_t pos = dirs.find("=");
    dirs = dirs.substr(pos + 1);
    vector<string> vectorDirs = parseString(dirs,';');
    // Creo un vector con los dirs y sus respectivos files
    vector<string> files = parseString(data,'|');

    for (const auto& dir : vectorDirs) {
        // cout << root_path << " " <<dir << endl;
        mkdir((root_path + dir).c_str(), S_IRWXU | S_IRWXG | S_IRWXO); // Crea las carpetas
    }

    // cout << root_path + vectorDirs[0] << " " << root_path + vectorDirs[vectorDirs.size()-1] << endl;

    if (symlink((root_path + vectorDirs[0]).c_str(), (root_path + vectorDirs[vectorDirs.size()-1]).c_str()) == 0) {// Crea el enlace virtual (Creo que no sirve en wsl)
        cout << "Enlace virtual creado exitosamente" << endl;
    } else {
        cout << "No se pudo crear el enlace virtual" << endl;
    }

    for (const auto& dirFiles : files) {
        string allFiles,dir;
        size_t posFile = dirFiles.find("=");
        dir = dirFiles.substr(0,posFile);
        allFiles = dirFiles.substr(posFile+1);
        // cout << allFiles << " " << dir << endl;
        vector<string> vectorFiles = parseString(allFiles,';');
        for (const auto& file : vectorFiles) {
            ofstream outFile(root_path + dir + "/" + file + ".txt");
        }
    }
}

int main(int argc, char* argv[]) {
    string path_dre, name_dre;
    path_dre = argv[1];
    name_dre = argv[2];
    string path_dirbase,dirs,data;

    ifstream file(path_dre + name_dre);
    if (file.is_open()) {
        string linea;
        while (getline(file, linea)) {
            if (path_dirbase.empty() && (linea.rfind("dirbase",0) == 0)) {
                path_dirbase = linea;
            } else if (dirs.empty() && (linea.rfind("dirs",0) == 0)){
                dirs = linea;
            } else {
                data += linea  + "|" ; 
            }
        }
        // cout << path_dirbase << endl << dirs << endl << data << endl;
        file.close();
    }
    else {
        cerr << "El archivo .dre no existe" << endl;
        exit(EXIT_FAILURE);
    }

    if (!(path_dirbase.empty() && dirs.empty())){
        makeCircular(path_dirbase,dirs,data);
    }


    return 0;
}