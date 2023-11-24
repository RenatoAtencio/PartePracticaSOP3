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
        file.open("data/Files/OutputFiles/file.idx");
        if (file) { // Si existe el file.idx lo borra
            remove("data/Files/OutputFiles/file.idx");
        }
        string commandPrepArchivos = "../ProgramasExternos/countWords " + string(getenv("EXTENSION")) + " " + string(getenv("PATH_RAWFILES")) + " " + string(getenv("PATH_OUTPUTFILES")) + " " + string(getenv("AMOUNT_THREADS"));
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
        file.open("data/Files/OutputFiles/file.idx");
        if (!file) {
            file.close();
            string commandCrearIndice = "../ProgramasExternos/makeInvertedIndex " + string(getenv("PATH_OUTPUTFILES")) + " " + string(getenv("INVERTED_INDEX_FILE"));
            int successIndice = system(commandCrearIndice.c_str());
            if (successIndice != 0) {
                cout << "Hubo un error al crear el indice" << endl;
            }
        }
        else {
            cout << "El file.idx ya fue creado" << endl;
        }
    }

    void buscador() {
        ifstream file;
        file.open("data/Files/OutputFiles/file.idx");
        if (atoi(getenv("TOPK")) <= 4) {
            cout << "La variable de entorno TOPK debe ser mayor a 4" << endl;
        }
        else if (!file) {
            cout << "El file.idx aun no ha sido creado (Usar 9)" << endl;
        }
        else {
            string comandoBusqueda = "../ProgramasExternos/invertedIndexSearcher " + string(getenv("INVERTED_INDEX_FILE")) + " " + string(getenv("TOPK"));
            cout << comandoBusqueda << endl;
            int successBusqueda = system(comandoBusqueda.c_str());
            if (successBusqueda != 0) {
                cout << "Hubo un error al crear el indice" << endl;
            }
        }
    }
};