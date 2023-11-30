#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <filesystem>
#include "../include/json.hpp"


using namespace std;
using json = nlohmann::json;
namespace fs = std::filesystem;

// Función para cargar datos desde un archivo con formato JSON
json loadJSON(const string& filename) {
    json jsonData;
    ifstream file(filename);
    if (file.is_open()) {
        file >> jsonData;
        file.close();
    }
    else {
        cerr << "No existe el archivo .dit" << endl;
        exit(EXIT_FAILURE);
    }
    return jsonData;
}

// Crea y le da permisos a los archivos !(Agregar una extension path)
void createFile(string filePath, json file) {
    // Crear archivo
    string fileName, contenido, permiso;
    fileName = file["nombre"];
    contenido = file["contenido"];

    ofstream outFile(filePath + fileName);
    if (!outFile.is_open()) {
        cerr << "No se pudo abrir el archivo: "  << fileName << endl;
        return;
    }
    outFile << contenido;
    outFile.close();

    fs::permissions(
        filePath + fileName,
        fs::perms::owner_read | fs::perms::owner_write |
        fs::perms::group_read | fs::perms::group_write |
        fs::perms::others_read | fs::perms::others_write,
        fs::perm_options::remove
    );
    // Darle permisos al archivo (No funciona correcto)
    for (const auto& permiso : file["permisos"]) {
        if (permiso == "lectura") {
            fs::permissions(
                filePath + fileName,
                fs::perms::owner_read | fs::perms::group_read | fs::perms::group_read,
                fs::perm_options::add
            );
            // cout << filePath + fileName << " lectura" << endl;
        }
        if (permiso == "escritura") {
            fs::permissions(
                filePath + fileName,
                fs::perms::owner_write | fs::perms::group_write | fs::perms::group_write,
                fs::perm_options::add
            );
            // cout << filePath + fileName << " escritura" << endl;
        }
    }
}

// Funcion que toma el path de una carpeta y el arreglo de objetos de la misma
void createDirectory(string directoryPath, json directoryArray) {
    string directoryName;
    // Recorro el arreglo de objetos
    for (const auto& elem : directoryArray) {
        // si el objeto es un archivo llamo a la funcion createFile con el path del archivo y el elem (que contiene el nombre, contenido y permisos)
        if (elem["tipo"] == "archivo") {
            // cout << directoryPath << " " << elem["nombre"] << endl;
            createFile(directoryPath, elem);
        }
        // si es un directorio llamo a esta misma funcion pero con el path correspondiente, tambien se pasa el arreglo de objetos de la carpeta a crear
        else if (elem["tipo"] == "directorio") {
            directoryName = elem["nombre"];
            mkdir((directoryPath + directoryName).c_str(), S_IRWXU | S_IRWXG | S_IRWXO); // Crea el directorio
            createDirectory(directoryPath + directoryName + "/", elem["objetos"]); // paso el path correspondiente (no olvidar el /)
        }
    }
    return;
}

void makeTree(json treeJson) {
    string treeRoot;
    json treeObjs;

    try {
        treeRoot = treeJson["dirBase"];
    }
    catch (const exception& e) {
        cerr << "Formato del .dit invalido: 'dirBase' no existe" << endl;
        exit(EXIT_FAILURE);
    }

    // cout << treeRoot << endl;
    // Verificacion carpeta tree
    if (!fs::exists(treeRoot) && !fs::is_directory(treeRoot)) {
        cout << "La carpeta '" << treeRoot << "' no existe por lo tanto se creara." << endl;
        mkdir((treeRoot).c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
    }

    try {
        treeObjs = treeJson["objetos"];
    }
    catch (const exception& e) {
        cerr << "Formato del .dit invalido: 'objetos' no existe" << endl;
        exit(EXIT_FAILURE);
    }

    // Llamo a la funcion recursiva createDirectory, toma el path de la carpeta y el arreglo de objetos de la misma (La primera ejecucion el con el dirBase)
    createDirectory(treeRoot, treeObjs);
}

// Toma el path y el nombre del archivo .dit
int main(int argc, char* argv[]) {
    string path_dir, name_dir;
    path_dir = argv[1];
    name_dir = argv[2];
    json treeJson = loadJSON(path_dir + name_dir);

    // Comienzo la creacion de las carpetas y archivos
    makeTree(treeJson);
    cout << "Creacion exitosa" << endl;
    return 0;
}

/*
    Falta:
        - arreglar la asignacion de permisos
        - verificaciones de existencia de los archivos (quizas al correr borramos todo lo del archivo tree antes)
        - ver si agregamos la extension del archivo como argumento
        - verificar el formato del .dit

    Ejecutar en la carpeta ProgramasExternos con
        ./makeTree ../Trabajo5/data/databases/ arbol.dit
*/