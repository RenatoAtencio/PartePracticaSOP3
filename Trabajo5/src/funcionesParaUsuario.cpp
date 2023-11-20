#include "../include/funciones.h"
#include <vector>
#include <string>

using namespace std;

bool verificarUsuario(vector<vector<string>> usuarios, int& index, string nombreUsuario) {
    while (index < usuarios.size() && nombreUsuario != usuarios[index][0]) {
        index++;
    }
    if (index == usuarios.size()) {
        return false;
    }
    return true;
}

usuario crearUsuario(int index, vector<vector<string>> usuarios, vector<int> vectorUserInt) {
    vector<int> permisosInt;
    string userRol = usuarios[index][1];
    vector<vector<string>> rolesYPermisos;
    rolesYPermisos = separarTextoFormatoNormal(getenv("DB_PERMISOS"));
    int i = 0;
    while ((i < rolesYPermisos.size()) && (userRol != rolesYPermisos[i][0])) {
        i++;
    }
    permisosInt = vectorstoi(rolesYPermisos[i]);
    usuario user(usuarios[index][0],rolesYPermisos[i][0], vectorUserInt, permisosInt);
    return user;
}