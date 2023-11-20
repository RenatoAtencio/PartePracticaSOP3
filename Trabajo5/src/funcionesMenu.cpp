#include "../include/funciones.h"

using namespace std;

int usoPrep = 0;

void verSeleccion(bool& seguir, usuario user, int userInput, string nombreNuevoTxt, string textoNuevoTxt, string nombreTexto, string nombreArchivoSalidaConteo) {
    if (userInput >= 1 && userInput <= 13) {
        if (!user.verificarPermiso(userInput)) {
            cout << "No tiene este permiso" << endl;
            return;
        }
    }
   
    switch (userInput) {
    case 0: { // Salir
        seguir = false;
        user.salir();
        break;
    }
    case 1: { // Sumar
        if (user.verificarPermiso(1)) {
            int suma = user.sumaVector();
            cout << "1.- La suma del vector es: " << suma << endl;
        }
        break;
    }
    case 2: { // Promedio
        if (user.verificarPermiso(2)) {
            float promedio = user.promedioVector();
            cout << "2.- El promedio del vector es: " << promedio << endl;
        }
        break;
    }
    case 3: { // Moda
        if (user.verificarPermiso(3)) {
            int moda = user.modaVector();
            cout << "3.- La moda del vector es: " << moda << endl;
        }
        break;
    }
    case 4: { // Contar
        if (user.verificarPermiso(4)) {
            int cantidad = user.contarVector();
            cout << "4.- El vector tiene " << cantidad << " numeros" << endl;
        }
        break;
    }
    case 5: { // Crear archivo
        if (user.verificarPermiso(5)) {
            string pathNuevoArchivo = string(getenv("PATH_OUTPUTFILES")) + nombreNuevoTxt;
            if (verificarArchivo(pathNuevoArchivo) == false) {
                user.crearArchivo(pathNuevoArchivo);
                cout << "5.- El archivo fue creado" << endl;
            }
            else {
                cout << "5.- El archivo ya existe" << endl;
            }
        }
        break;
    }
    case 6: { // Escribir en archivo
        if (user.verificarPermiso(6)) {
            string pathNuevoArchivo = getenv("PATH_OUTPUTFILES") + nombreNuevoTxt;
            if (verificarArchivo(pathNuevoArchivo) == false) {
                cout << "6.- El archivo aun no ha sido creado" << endl;
            }
            else {
                user.escribirArchivo(pathNuevoArchivo, textoNuevoTxt);
            }
        }
        break;
    }
    case 7: { // Contar Palabras
        if (user.verificarPermiso(7)) {
            string pathTexto = getenv("PATH_RAWFILES") + nombreTexto;
            if (verificarArchivo(pathTexto) == false) {
                cout << "El archivo no existe" << endl;
            }
            else if (string(getenv("PATH_RAWFILES")) == string(getenv("PATH_OUTPUTFILES"))) {
                cout << "Las carpetas In y Out no pueden ser la misma" << endl;
            }
            else {
                user.contarPalabras(nombreTexto, nombreArchivoSalidaConteo);
            }
            break;
        }
    }
    case 8: {
        if (user.verificarPermiso(8)) {
            if (stoi(getenv("AMOUNT_THREADS")) > 10 || stoi(getenv("AMOUNT_THREADS")) <= 0) {
                cout << "La cantidad de threads definidos es invalida" << endl;
            }
            else if (string(getenv("PATH_RAWFILES")) == string(getenv("PATH_OUTPUTFILES"))) {
                cout << "Las carpetas In y Out no pueden ser la misma" << endl;
            }
            else {
                user.prepararArchivosIndice();
                usoPrep = 1;
            }
        }
        break;
    }
    case 9: {
        if ((user.verificarPermiso(9)) && (usoPrep == 1)) {
            user.crearIndiceInvertido();
        }
        else if (usoPrep == 0) {
            cout << "Debe usar la opcion 8 antes de usar la opcion 9" << endl;
        }
        break;
    }
    case 10: {
        if ((user.verificarPermiso(10))) {
            user.buscador();
        }
        break;
    }
    case 11: {
        if (user.verificarPermiso(11)) {
            cout << "Operacion 11" <<  endl;
        }
        break;
    }
    case 12: {
        if (user.verificarPermiso(12)) {
            cout << "Operacion 12" << endl;
        }
        break;
    }
    case 13: {
        if (user.verificarPermiso(13)) {
            cout << "Operacion 13" << endl;
        }
        break;
    }
    default: { // Cualquier otro caso
        cout << "Esta funcionalidad no esta implementada" << endl;
    }
    }
}

void mostrarMenu() {
    ifstream menu(getenv("DB_MENU"));
    vector<vector<string>> opciones(14);
    string linea;
    while (getline(menu, linea)) {
        vector<string> v1;
        v1 = separarStringPorComaVectorString(linea);
        int opcion = stoi(v1[1]);
        opciones[opcion] = v1;
    }
    for (int i = 0; i < opciones.size();i++) {
        cout << opciones[i][0] << endl;
    }
}
