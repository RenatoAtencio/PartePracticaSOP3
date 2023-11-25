#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <GL/glut.h>

using namespace std;

struct Point {
    float x, y;
};

string title;
vector<Point> points;

void loadData(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo" << endl;
        exit(EXIT_FAILURE);
    }
    string line;
    while (getline(file, line)) {
        /*if (line.find("titulo:") != string::npos) {
            title = line.substr(line.find(":") + 1);
        }*/
         if (line.find("x:") != string::npos && line.find("y:") != string::npos) {
            Point p;
            sscanf(line.c_str(), "x:%f,y:%f", &p.x, &p.y);
            points.push_back(p);
        }
    }
    file.close();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_LINES);
    glVertex2f(-100.0, 0.0);
    glVertex2f(100.0, 0.0);
    glVertex2f(0.0, -100.0);
    glVertex2f(0.0, 100.0);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (const auto& point : points) {
        glVertex2f(point.x, point.y);
    }
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(90.0, -2.0);
    for (char c : "X") {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glRasterPos2f(-5.0, 90.0);
    for (char c : "Y") {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glRasterPos2f(-40.0, 90.0);
    for (char c : title) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0); // Establece el rango de -100 a 100 en ambos ejes
}

// Comentar las funciones
// ver si se puede solo mostrar el primer cuadrante de la grafica
int main(int argc, char** argv) {
    if (argc != 3) {
        cerr << "Para ejecutar use: " << argv[0] << " <ruta_archivo.gra> <nombre_archivo.gra>" << endl;
        return EXIT_FAILURE;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Grafico de Lineas");

    init();
    string fullPath = string(argv[1]) + string(argv[2]);
    loadData(fullPath);

    cout << "Para continuar cerrar la grafica" << endl;
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

// usar ./grafico ../Trabajo5/data/databases/ datos.gra