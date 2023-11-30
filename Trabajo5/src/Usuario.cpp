#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <map>

using namespace std;

class usuario {
private:
    string nombre;
    string rol;
    vector<int> numeros;
    vector<int> permisos;

public:
    // Constructor
    usuario(string nombreInput, string rolInput, vector<int> numerosInput, vector<int> permisosInput) {
        nombre = nombreInput;
        rol = rolInput;
        numeros = numerosInput;
        permisos = permisosInput;
    }

    // Funciones get
    string getNombre() {
        return nombre;
    }

    string getRol() {
        return rol;
    }

    // Funciones para permisos
    bool verificarPermiso(int permiso) {
        for (int p : permisos) {
            if (p == permiso) {
                return true;
            }
        }
        return false;
    }

    void salir() {
        cout << "A salido del programa" << endl;
    }

    int sumaVector() {
        int suma = 0;
        for (int val1 : numeros) {
            suma += val1;
        }
        return suma;
    }

    float promedioVector() {
        float suma = sumaVector();
        return suma / numeros.size();
    }

    int modaVector() {
        unordered_map<int, int> frecuencia;
        for (int num : numeros) {
            frecuencia[num]++;
        }
        int moda = numeros[0];
        int maxFrecuencia = 0;
        for (const auto& pair : frecuencia) {
            if (pair.second > maxFrecuencia) {
                moda = pair.first;
                maxFrecuencia = pair.second;
            }
        }
        return moda;
    }

    int contarVector() {
        return numeros.size();
    }

    void crearArchivo(string path) {
        ofstream file(path);
        file.open(path);
        file.close();
    }

    void escribirArchivo(string path, string texto) {
        ofstream file(path, std::ios::app);
        if (file.is_open()) {
            file << texto << endl;
            file.close();
            cout << "6.- Contenido agregado al archivo." << endl;
        }
        else {
            cout << "No se pudo abrir el archivo." << endl;
        }
    }

    void contarPalabras(string nombreArchivo, string pathSalidaConteo) {
        // Llamar a la programa externo, eliminar simbolos y contar palabras, elminar el archivo temporal al final
        // Ya verifique que el archivo existe
        string commandElimSimbolos = "python3 " + string(getenv("PATH_PROGRAMAS_EXTERNOS_PYTHON")) + "eliminarSimbolos.py " + nombreArchivo;
        int successElimSimbolos = system(commandElimSimbolos.c_str());
        if (successElimSimbolos == 0) {
            cout << "Se llamo al proceso para eliminar simbolos correctamente" << endl;
            string commandContarPalabras = "python3 " + string(getenv("PATH_PROGRAMAS_EXTERNOS_PYTHON")) + "contarPalabras.py " + nombreArchivo + " " + pathSalidaConteo;
            int successContarPalabras = system(commandContarPalabras.c_str());
            if (successContarPalabras == 0) {
                cout << "Se llamo al proceso para contar palabras correctamente" << endl;
            }
            else {
                cout << "No se pudo llamar al proceso para contar palabras" << endl;
                // quisas deberia quitar el processed file si falla
            }
        }
        else {
            cout << "No se pudo llamar al proceso para eliminar simbolos" << endl;
        }
    }

    void prepararArchivosIndice() {
        ifstream file;
        string path_outputFiles = getenv("PATH_OUTPUTFILES");
        string indexFile_name = getenv("DOT_IDX_NAME");
        file.open(path_outputFiles + indexFile_name);
        if (file) { // Si existe el file.idx lo borra
            remove((path_outputFiles + indexFile_name).c_str());
        }
        string path_prog_externos = getenv("PATH_PROGRAMAS_EXTERNOS_CPP");
        string count_name = getenv("COUNTWORD_NAME");
        string commandPrepArchivos = path_prog_externos + count_name + " " + string(getenv("EXTENSION")) + " " + string(getenv("PATH_RAWFILES")) + " " + path_outputFiles+ " " + string(getenv("AMOUNT_THREADS"));
        int successPrepararArchivos = system(commandPrepArchivos.c_str());
        if (successPrepararArchivos == 0) {
            cout << "Proceso fue llamado correctamente" << endl;
        }
        else {
            cout << "No se pudo llamar al proceso" << endl;
        }
    }

    void crearIndiceInvertido() {
        ifstream file;
        string path_outputFiles = getenv("PATH_OUTPUTFILES");
        string indexFile_name = getenv("DOT_IDX_NAME");
        file.open(path_outputFiles + indexFile_name);
        if (!file) {
            string path_prog_externos = getenv("PATH_PROGRAMAS_EXTERNOS_CPP");
            string makeIndex_name = getenv("MAKE_INVERTEDINDEX_NAME");
            string commandCrearIndice = path_prog_externos + makeIndex_name + " " + path_outputFiles + " " + path_outputFiles + indexFile_name;
            // cout << commandCrearIndice << endl;
            int successIndice = system(commandCrearIndice.c_str());
            if (successIndice != 0) {
                cout << "Hubo un error al crear el indice" << endl;
            }
        }
        else {
            cout << "El file.idx ya fue creado" << endl;
        }file.close();
    }

    void buscador() {
        ifstream file;
        int topk = atoi(getenv("TOPK")) ;
        string path_outputFiles = getenv("PATH_OUTPUTFILES");
        string indexFile_name = getenv("DOT_IDX_NAME");
        file.open(path_outputFiles + indexFile_name);
        if (topk <= 4) {
            cout << "La variable de entorno TOPK debe ser mayor a 4" << endl;
        }
        else if (!file) {
            cout << "El file.idx aun no ha sido creado (Usar 9)" << endl;
        }
        else {
            string path_prog_externos = getenv("PATH_PROGRAMAS_EXTERNOS_CPP");
            string invertedIndex_name = getenv("INVERTEDINDEX_SEARCHER_NAME");
            string comandoBusqueda = path_prog_externos + invertedIndex_name + " " + path_outputFiles + indexFile_name + " " + to_string(topk);
            // cout << comandoBusqueda << endl;
            int successBusqueda = system(comandoBusqueda.c_str());
            if (successBusqueda != 0) {
                cout << "Hubo un error al crear el indice" << endl;
            }
        }
        file.close();
    }

    void makeTreeDirectory(string dit_name) {
        ifstream file;
        string path_databases = getenv("PATH_DATABASES");
        // string dit_name = getenv("DOT_DIT_NAME");
        file.open(path_databases + dit_name);
        if (!file) {
            cout << "El archivo: " << dit_name << " no existe en el path: " << path_databases << endl;
        }
        else {
            string path_prog_externos = getenv("PATH_PROGRAMAS_EXTERNOS_CPP");
            string make_tree_name = getenv("MAKE_TREE_NAME");
            string commandoMakeTree = path_prog_externos + make_tree_name + " " + path_databases + " " + dit_name;
            // cout << commandoMakeTree << endl;
            int success = system(commandoMakeTree.c_str());
            if (success != 0) {
                cerr << "Hubo un error al llamar al programa externo: '" << make_tree_name << "'" << endl;
            }
            else {
                cout << "Se crearon los directorios correctamente (metodo tree)" << endl;
                cout << "Usar 'tree' en la consola para ver la estructura (En linux y en la carpeta correspondiente)" << endl;
            }
        }
    }

    void makeCircularDirectory(string dre_name) {
        ifstream file;
        string path_databases = getenv("PATH_DATABASES");
        // string dre_name = getenv("DOT_DRE_NAME");
        file.open(path_databases + dre_name);
        if (!file) {
            cout << "El archivo: " << dre_name << " no existe en el path: " << path_databases << endl;
        }
        else {
            string path_prog_externos = getenv("PATH_PROGRAMAS_EXTERNOS_CPP");
            string make_circular_name = getenv("MAKE_CIRCULAR_NAME");
            string commandoMakeCircular = path_prog_externos + make_circular_name + " " + path_databases + " " + dre_name;
            // cout << commandoMakeCircular << endl;
            int success = system(commandoMakeCircular.c_str());
            if (success != 0) {
                cerr << "Hubo un error al llamar al programa externo: '" << make_circular_name << "'" << endl;
            }
            else {
                cout << "Se crearon el directorios correctamente (metodo circular)" << endl;
                cout << "Usar 'tree' en la consola para ver la estructura (En linux y en la carpeta correspondiente)" << endl;
            }
        }
    }

    void makeGraph(string gra_name) {
        ifstream file;
        string path_databases = getenv("PATH_DATABASES");
        // string gra_name = getenv("DOT_GRA_NAME");
        file.open(path_databases + gra_name);
        if (!file) {
            cout << "El archivo: " << gra_name << " no existe en el path: " << path_databases << endl;
        }
        else {
            string path_prog_externos = getenv("PATH_PROGRAMAS_EXTERNOS_CPP");
            string make_graph_name = getenv("MAKE_GRAPH_NAME");
            string commandoMakeTreGraph = path_prog_externos + make_graph_name + " " + path_databases + " " + gra_name;
            // cout << commandoMakeTreGraph << endl;
            int success = system(commandoMakeTreGraph.c_str());
            if (success != 0) {
                cerr << "Hubo un error al llamar al programa externo: '" << make_graph_name << "'" << endl;
            }
            else {
                cout << "Se creo correctamente la grafica" << endl;
            }
        }
    }

};