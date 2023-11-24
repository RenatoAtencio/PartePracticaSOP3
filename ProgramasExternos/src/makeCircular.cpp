#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <filesystem>
#include <vector>
#include "../include/json.hpp"


using namespace std;\

// ./makeCircular ../Trabajo5/data/databases/ circular.dre

vector<string> parseData(string data){
    vector<string> files;
    istringstream stream(data);
    string file;
    while (getline(stream, file, '|')) {
        files.push_back(file);
    }
    // for (const auto& e : files) {
    //     cout << e << endl;
    // }
    return files;
}

void makeCircular(string root_path,string dirs,string data){
    vector<string> files = parseData(data);
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