# Trabajo sistemas operativos

### Funcionamiento
La aplicacion toma 8 inputs: NombreUsuario, Vector de Numeros, Path archivo a crear, Texto a escribir en el archivo creado, Path archivo a contar, Path salida del conteo.

Primero se verifica que este usuario este en la base de datos (users.txt), de ser el caso muestra un menu con las opciones de la aplicacion, el user puede indicar que opcion quiere tomar, si tiene los permisos entonces hara la accion, sino indicara que no tiene el permiso en especifico.
Antes de mostrar el menu muestra el nombre del user y su rol, el rol establece que permisos tendra.
se tienen 10 opciones:

+ 0.- Salir 
+ 1.- Sumar Vector
+ 2.- Promedio del Vector
+ 3.- Moda del Vector
+ 4.- Contar elementos del Vector
+ 5.- Crear archivo txt
+ 6.- Escribir en archivo creado txt
+ 7.- Contar palabras en el archivo dado
+ 8.- Preparar datos para indice invertido
+ 9.- Crear Indice invertido
  
Cualquier otro seleccion sera indicada como una funcionalidad no implementada.
La opcion 5 verifica que el archivo este creado, si este no es el caso creara el archivo.
La opcion 6 tambien verifica que el archivo este creado pero si no es el caso solamente lo indicara , si el archivo existe entonces escribe el texto pasado en los parametros al ejecutar el programa en el archivo.
Opcion 7 busca el archivo con el path entregado al ejecutar y crea un archivo con el conteo de las palabras, la salida es dejada en el path entregado de salida.
Opcion 8 carga los archivos 'file___.txt' entregados en la carpeta RawFiles, realiza el conteo de los mismo y deja el resultado en la carpeta OutputFiles
Opcion 9 toma los archivos creados por la opcion 8 y crea un solo archivo '.idx', el cual es una combinacion de todos las salidas de conteo de la opcion 8

El programa se dividio en 6 archivos.cpp y uno .h:
main.cpp : Es la columna del codigo y desde el mismo se llaman a las funciones que presentes en el main y en otros archivos.cpp,contiene la funcion separarTextoFormatoNormal que crea un vector de vectores de inputs con un formato var11,var12,var13;var21,var22,var23;var31,var,32,var33;

funcionesVerificacion : contiene funciones de verificacion, por ahora solo tiene verificarArchivo que devuelve true si un archivo existe.
    
funcionesMenu.cpp : contiene funciones relacionadas con el menu de la aplicacion, como mostrarMenu que imprime el menu en la consola y ver seleccion que se encarga de tomar el input del usuario y determinar si se permite la operacion o no, si se permite llama a la operacion si no indica que no se puede hacer la operacion.

funcionesParaUsuario : contiene funciones que son usadas para los usuarios que no eran exactamentes metodos de usuario, por ejemplo el verificarUsuario que verifica que un usuario existe en la base de datos o crear usuario que hace todos los procesos necesarios para crear un usuario (por ejemplo hacer el parse del vector de numeros, ver que rol es el usuario,etc).

funcionesParse : funciones principalmente de separacion de string o tranformacion de los mismos a otros tipos de datos, se tiene separarStringPorComaVectorInt que toma un string y devuelve un vector<int>, separarStringPorComaVectorString que hace lo mismo pero devuelve un vector<string> y vectorstoi que pasa un vector<string> a vector<int>.

Usuario.cpp : es para tener un objeto usuario, tiene principalmente los atributos del usuario (nombre,rol,vector de numeros, vector de permisos) y sus metodos, estos ultimos son todos los permisos que un usuario puede tener, se tienen tambien un metodo de verificacion de permiso para evitar que usuarios no usen permisos que no tienen.

funciones.h : donde se declaran las funciones y que luego puede ser llamado a los dintintos archivos.cpp.

Tambien se tiene una carpeta ProgramasExternos donde se tienen 4 programas externos:
eliminarSimbolos.py: elimina simbolos de un txt y deja la salida en la carpeta processedFiles
contarPalabras.py: toma la salida de eliminarSimbolos y cuenta las palabras, luego guarda la salida en la carpeta outputFiles
main.cpp: hace el mismo funcionamiento de los 2 programas anteriores pero usando multiples threads
main2.cpp: toma la salida de main.cpp y crea el indice invertido


### Compilacion

Usar en la carpeta Trabajo4

    -set -o allexport 
    source config/.env
    make all
    
Usar en la carpeta PregramasExternos 

    make

### Ejecutar

Usar en la consola dentro de Trabajo4 usar ./app -u user -v vector -f pathArchivoACrear -t TextoParaArchivoCreado -i PathArchivoConteo -o PathSalidaConteo
-u: El user es el nombre del usuario que se quiere usar, la aplicacion es case sensitive asi que juan != Juan. Ej: Kylian
-v: El vector de numeros es un string de numeros separados por ','. Ej: 1,4,5,1,23,14,441
-f nombre de un archivo. Ej: nombre.txt
-t El texto es un string. Ej: Hola
-i nombre del archivo a realizar el conteo ej = harryPotter.txt, este archivo debe de estar en data/Files/RawFiles
-o nombre del archivo de salida del conteo, ej = salida.txt, este archivo se guarda en OutputFiles

    Ejemplo de entrada: ./app -u Pol -v 3,1,4,5,2,2,3 -f intento4.txt -t hola -i harryPotter.txt -o salida.txt

### Estructura Bases de dato

Se tienen 3 bases de datos y 1 archivo .env
menu.txt: base de datos con el menu del programa tiene formato proceso,numero del proceso

    ej: sumar,1
permisos.txt: tiene los roles y sus respectivos permisos

    ej: admin,1,2,3,4,5,6,7,8;userRookie,1,4;userGeneral,1,2,3,4;
user.txt: son los usuarios seguidos por su rol

    ej: Pol,admin;Kylian,userGeneral
    ej: Kylian,userGeneral;Pol,admin;
    
config.en: contiene las variables de entorno que se van a cargar al usar el source config.env, las variables estan en mayusculas y los valores son paths principalmente, todo junto.

    ej: DB_USERS=BasesDatos/users.txt
    
