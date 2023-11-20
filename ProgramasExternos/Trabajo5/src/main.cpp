#include "../include/funciones.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Paso el txt a un vector de vectores, cada sub-vector sera un usuario y sus permisos (todo en string)
    vector<vector<string>> usuarios;
    usuarios = separarTextoFormatoNormal(string(getenv("DB_USERS")));

    // Entrada en la consola, paso los valores de las flags a su respectiva variable
    char c;
    string nombreUsuario, vectorNumerosStr, nombreNuevoTxt, textoNuevoTxt,  nombreTexto, nombreTextoSalidaConteo;
    vector<int> vectorNumerosInt;
    while ((c = getopt(argc, argv, "u:v:f:t:i:o:")) != -1) {
        switch (c) {
        case 'u': { // user
            nombreUsuario = optarg;
            break;
        }
        case 'v': { // vector 
            vectorNumerosStr = optarg;
            vectorNumerosInt = separarStringPorComaVectorInt(vectorNumerosStr);
            break;
        }
        case 'f': { // path para crear archivo
            nombreNuevoTxt = optarg;
            break;
        }
        case 't': { // texto
            textoNuevoTxt = optarg;
            break;
        }
        case 'i': { // path para cargar archivo
            nombreTexto = optarg;
            break;
        }
        case 'o': { // path de salida para los resultados
            nombreTextoSalidaConteo = optarg;
            break;
        }
        }
    }

    // Verificar si el usuario esta en la base de datos, es case sensitive, el i sera en index usuarios si es que existe el user
    int i = 0;
    if (verificarUsuario(usuarios, i, nombreUsuario) == false) {
        cout << "Usuario no esta registrado" << endl;
    }
    // Si el usuario si existe
    else {
        // Creo el objeto user, tiene como atributos el nombre,permisos,vector de numeros
        usuario user = crearUsuario(i, usuarios, vectorNumerosInt);
        // Muestro el menu, si se mueve la base de datos menu deberia se mostrarlo ordenado igualmente
        cout << "###############################" << endl;
        cout << "User: " << user.getNombre() << " | Rol: " << user.getRol() << endl;
        cout << "###############################" << endl;
        mostrarMenu();
        cout << "###############################" << endl;
        bool seguir = true;
        while (seguir) {
            int selecion;
            cout << "Seleccione una opcion: ";
            cin >> selecion;
            verSeleccion(seguir,user,selecion,nombreNuevoTxt,textoNuevoTxt, nombreTexto, nombreTextoSalidaConteo);
            cout << "###############################" << endl;
        }
    }
}

// Funciones

// carga texto que este en formato var11,var12,var13;var21,var22,var33; y lo pasa a un vector de vectores. 
vector<vector<string>> separarTextoFormatoNormal(string pathArchivo) {
    vector<vector<string>> vectorSalida;
    string lineaTxt;
    ifstream archivoTxt(pathArchivo);
    if (archivoTxt.is_open()) {
        while (getline(archivoTxt, lineaTxt)) {
            // cout << lineaTxt << endl;
        }
        archivoTxt.close();
    }
    // separo para crear sub-vectores, separo si aparece ;
    vector<string> subVector;
    istringstream stream(lineaTxt);
    string valoresString;
    while (getline(stream, valoresString, ';')) {
        subVector.push_back(valoresString);
    }
    // separos los valores si aparece una ,
    // recorro el subVector para separar, luego lo agrego al vectorSalida
    for (int i = 0; i < subVector.size(); ++i) {
        vector<string> valoresVector;
        istringstream stream(subVector[i]);
        string temporal;
        while (getline(stream, temporal, ',')) {
            valoresVector.push_back(temporal);
        }
        vectorSalida.push_back(valoresVector);
    }
    return vectorSalida;
}