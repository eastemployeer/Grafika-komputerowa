#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <iostream>
// Copyright 2020 Kamil Zaborowski [legal/copyright]
using std::cout;
using std::cin;
using std::endl;

typedef float point3[3];
typedef float point2[2];
GLfloat position[] = {0.0, 0.0, 0.0, 1.0};
int orientation = 1;
static GLfloat theta[] = {0.0, 0.0, 0.0};
// ilosc punktów
int n;
static const GLfloat min_zoom_value = 1.0;
static const GLfloat max_zoom_value = 20.0;
GLfloat rand_position[] = {-150.0, 0.0, 0.0, 1.0};

static GLfloat viewer[] = {0.0, 0.0, 10.0};

static GLfloat epsilon = 0.0;   // kąt obrotu obiektu w y
static GLfloat epsilon1 = 0.0;   // kąt obrotu obiektu w x
static GLfloat pix2angleY;     // przelicznik pikseli na stopnie Y
static GLfloat pix2angleX;  // przelicznik pikseli na stopnie X

int color = 1;

static GLint status = 0;       // stan klawiszy myszy
// 0 - nic nie naciśnięto
// 1 - LPM
// 2 - Scroll up
// 3 - Scroll down

static int x_pos_old = 0;       // poprzednia pozycja kursora myszy
static int y_pos_old = 0;

static int delta_x = 0;        // różnica pomiędzy pozycją bieżącą
static int delta_y = 0;
int reset = 0;  // 1 - wcisniety zostal klawisz r
void RenderScene(void);

void Mouse(int btn, int state, int x, int y) {
    if (btn == 3 && state == GLUT_DOWN) {
        status = 2;
        RenderScene();
    }
    if (btn == 4 && state == GLUT_DOWN) {
        status = 3;
        RenderScene();
    }

    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        x_pos_old = x;
        y_pos_old = y;
        status = 1;          // wcięnięty został lewy klawisz myszy
    } else {
        status = 0;          // nie został wcięnięty żaden klawisz
    }
}
void Motion(GLsizei x, GLsizei y) {
    delta_x = x-x_pos_old;  // obliczenie różnicy położenia kursora myszy
    delta_y = y-y_pos_old;
    x_pos_old = x;  // podstawienie bieżącego położenia jako poprzednie
    y_pos_old = y;

    glutPostRedisplay();     // przerysowanie obrazu sceny
}
void Egg(int n) {
    point3 table3D[n][n];
    point2 table[n][n];
    point3 normalVector[n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // wypełnianie tablic z u i v
            table[i][j][0] = static_cast<float>(i)/(n-1);
            table[i][j][1] = static_cast<float>(j)/(n-1);

            // przeliczanie na 3D
            table3D[i][j][0] = static_cast<float>((
                    -90*pow(table[i][j][0], 5)
                    +225*pow(table[i][j][0], 4)
                    -270*pow(table[i][j][0], 3)
                    +180*pow(table[i][j][0], 2)
                    -45*table[i][j][0])*cos(M_PI*table[i][j][1]));

            table3D[i][j][1] = static_cast<float>(
                    160*pow(table[i][j][0], 4)
                    -320*pow(table[i][j][0], 3)
                    +160*pow(table[i][j][0], 2)-5);

            table3D[i][j][2] = static_cast<float>((
                    -90*pow(table[i][j][0], 5)
                    +225*pow(table[i][j][0], 4)
                    -270*pow(table[i][j][0], 3)
                    +180*pow(table[i][j][0], 2)
                    -45*table[i][j][0])*sin(M_PI*table[i][j][1]));

            float x_u = static_cast<float>((
                    -450*pow(table[i][j][0], 4)
                    +900*pow(table[i][j][0], 3)
                    -810*pow(table[i][j][0], 2)
                    +360*table[i][j][0]-45)*cos(M_PI*table[i][j][1]));
            float x_v = static_cast<float>(
                    M_PI*(90*pow(table[i][j][0], 5)
                    -225*pow(table[i][j][0], 4)
                    +270*pow(table[i][j][0], 3)
                    -180*pow(table[i][j][0], 2)
                    +45*table[i][j][0])*sin(M_PI*table[i][j][1]));
            float y_u = static_cast<float>(
                    640*pow(table[i][j][0], 3)
                    -960*pow(table[i][j][0], 2)
                    +320*table[i][j][0]);
            float y_v = 0;
            float z_u = static_cast<float>((
                    -450*pow(table[i][j][0], 4)
                    +900*pow(table[i][j][0], 3)
                    -810*pow(table[i][j][0], 2)+
                    360*table[i][j][0]-45)*sin(M_PI*table[i][j][1]));
            float z_v = static_cast<float>(
                    -M_PI*(90*pow(table[i][j][0], 5)
                    -225*pow(table[i][j][0], 4)
                    +270*pow(table[i][j][0], 3)
                    -180*pow(table[i][j][0], 2)
                    +45*table[i][j][0])*cos(M_PI*table[i][j][1]));
            normalVector[i][j][0] = y_u*z_v-z_u*y_v;
            normalVector[i][j][1] = z_u*x_v-x_u*z_v;
            normalVector[i][j][2] = x_u*y_v-y_u*x_v;

       float length = sqrt(
               pow(normalVector[i][j][0], 2)
               +pow(normalVector[i][j][1], 2)
               +pow(normalVector[i][j][2], 2));
            if (i < n / 2) {
                if (normalVector[i][j][0] != 0)
                normalVector[i][j][0] = (y_u*z_v-z_u*y_v) / length;
                if (normalVector[i][j][1] != 0)
                normalVector[i][j][1] = (z_u*x_v-x_u*z_v) / length;
                if (normalVector[i][j][2] != 0)
                normalVector[i][j][2] = (x_u*y_v-y_u*x_v) / length;
            } else if (i > n / 2) {
                if (normalVector[i][j][0] != 0)
                normalVector[i][j][0] = -1 * (y_u*z_v-z_u*y_v) / length;
                if (normalVector[i][j][1] != 0)
                normalVector[i][j][1] = -1 * (z_u*x_v-x_u*z_v) / length;
                if (normalVector[i][j][2] != 0)
                normalVector[i][j][2] = -1 * (x_u*y_v-y_u*x_v) / length;
            }
        }
    }
        // TRIANGLES
       for (int i = 0; i< n-1; i++) {
            for (int j = 0; j < n-1; j++) {
                glBegin(GL_TRIANGLES);
               // glColor3fv(colors[i][j]);
               glNormal3fv(normalVector[i][j]);
               glVertex3fv(table3D[i][j]);
               // glColor3fv(colors[i][j+1]);
                glNormal3fv(normalVector[i][j+1]);
                glVertex3fv(table3D[i][j+1]);
               // glColor3fv(colors[i+1][j]);
                glNormal3fv(normalVector[i+1][j]);
                glVertex3fv(table3D[i+1][j]);
                glEnd();

                glBegin(GL_TRIANGLES);
               // glColor3fv(colors[i+1][j]);
                glNormal3fv(normalVector[i+1][j]);
                glVertex3fv(table3D[i+1][j]);
               // glColor3fv(colors[i+1][j+1]);
                glNormal3fv(normalVector[i+1][j+1]);
                glVertex3fv(table3D[i+1][j+1]);
                // glColor3fv(colors[i][j+1]);
                glNormal3fv(normalVector[i][j+1]);
                glVertex3fv(table3D[i][j+1]);
                glEnd();
            }
        }
}

void checkMovementAndZoom() {
    if (status == 1) {
        // modyfikacja kąta obrotu o kat proporcjonalny
        epsilon += delta_x*pix2angleX*2;
        epsilon1 += delta_y*pix2angleY*2;
    }
    if (status == 2) {
        viewer[2] += 1.0;
        if (viewer[2] > max_zoom_value)
            viewer[2] = max_zoom_value;

        if (viewer[2] < min_zoom_value)
            viewer[2] = min_zoom_value;
    }
    if (status == 3) {
        viewer[2] -= 1.0;
        if (viewer[2] > max_zoom_value)
            viewer[2] = max_zoom_value;

        if (viewer[2] < min_zoom_value)
            viewer[2] = min_zoom_value;
    }
}
void checkReset() {
    // przywracanie wartosci domyslnych wszystkim zmiennym
    if (reset == 1) {
        viewer[2] = 10.0;
        epsilon = 0.0;
        epsilon1 = 0.0;
        theta[0] = 0.0;
        theta[1] = 0.0;
        reset = 0;
    }
}

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Czyszczenie okna aktualnym kolorem czyszczącym

    glLoadIdentity();
    // Czyszczenie macierzy bieżącej

    gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    checkReset();
    checkMovementAndZoom();

    glTranslated(0, -5, 0);
    gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

if (status == 1) {
    position[0] += delta_x;
    position[1] -= delta_y;

    glLightfv(GL_LIGHT0, GL_POSITION, position);
}
if (color == 1) {
    GLfloat light_ambient[] = {0.3, 0.0, 1.0, 1.0 };
    GLfloat light_diffuse[] = { 0.0, 0.5, 0.6, 1.0 };
    GLfloat light_specular[] = { 0.1, 0.2, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}
    if (color == 2) {
        GLfloat light_ambient[] = {1.0, 0.0, 0.3, 1.0 };
        GLfloat light_diffuse[] = { 0.6, 0.5, 0.0, 1.0 };
        GLfloat light_specular[] = { 1.0, 0.2, 0.1, 1.0 };
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    }
    if (color == 3) {
        GLfloat light_ambient[] = {0.3, 1.0, 0.3, 1.0 };
        GLfloat light_diffuse[] = { 0.6, 0.7, 0.0, 1.0 };
        GLfloat light_specular[] = { 0.2, 1.0, 0.1, 1.0 };
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    }
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[0], 1.0, 0.0, 0.0);

    // Axes();
    Egg(n);

    glFlush();
    // Przekazanie poleceń rysujących do wykonania

    glutSwapBuffers();
}
void keys(unsigned char key, int x, int y) {
    if (key == 'b') color = 1;
    if (key == 'r') color = 2;
    if (key == 'g') color = 3;
    if (key == 'q') orientation = 1;  // obrót wokol x - po osi poziomej
    if (key == 'w') orientation = 2;  // obrót wokól y - po osi pionowej
    RenderScene();
}

void MyInit(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess = { 100.0 };
    GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[] = {1.0, 0.0, 0.3, 1.0 };
    GLfloat light_diffuse[] = { 0.6, 0.5, 0.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 0.2, 0.1, 1.0 };
    GLfloat att_constant = { 1.0 };
    GLfloat att_linear = { (GLfloat) 0.05 };
    GLfloat att_quadratic = { (GLfloat) 0.001 };

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);

    glShadeModel(GL_SMOOTH);  // właczenie łagodnego cieniowania
    glEnable(GL_LIGHTING);   // właczenie systemu oświetlenia sceny
    glEnable(GL_LIGHT0);     // włączenie źródła o numerze 0
    glEnable(GL_DEPTH_TEST);  // włączenie mechanizmu z-bufora
}


void ChangeSize(GLsizei horizontal, GLsizei vertical ) {
    pix2angleX = 360/(static_cast<float>(horizontal));
    pix2angleY = 360/(static_cast<float>(vertical));

    GLfloat AspectRatio;
    // Deklaracja zmiennej AspectRatio  okreslajacej proporcje
    // wymiarów okna

    if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0

        vertical = 1;

    glViewport(0, 0, horizontal, vertical);
    // Ustawienie wielkosciokna okna widoku (viewport)
    // W tym przypadku od (0,0) do (horizontal, vertical)

    glMatrixMode(GL_PROJECTION);
    // Przelaczenie macierzy biezacej na macierz projekcji

    glLoadIdentity();
    // Czyszcznie macierzy biezacej

    AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
    // Wyznaczenie wspólczynnika  proporcji okna
    // Gdy okno nie jest kwadratem wymagane jest okreslenie tak zwanej
    // przestrzeni ograniczajacej pozwalajacej zachowac wlasciwe
    // proporcje rysowanego obiektu.
    // Do okreslenia przestrzeni ograniczjacej sluzy funkcja
    // glOrtho(...)

    gluPerspective(70, 1.0, 1.0, 30.0);
    // Ustawienie parametrów dla rzutu perspektywicznego
    glMatrixMode(GL_MODELVIEW);
    // Przelaczenie macierzy biezacej na macierz widoku modelu

    glLoadIdentity();
    // Czyszcenie macierzy biezacej
}
void moveLight() {
    if (rand_position[0] < 150)
        rand_position[0] += 0.7;
    else
        rand_position[0] =- 150.0;
    glLightfv(GL_LIGHT0, GL_POSITION, rand_position);
    glutPostRedisplay();
}
void spinEgg() {
    // kliknięcie "q" - obracanie się wokół x
    if (orientation == 1) {
        theta[0] -= 0.25;
        if (theta[0] > 360.0) theta[0] -= 360.0;
    }
    // kliknięcie "w" - obracanie się wokol y
    if (orientation == 2) {
        theta[1] -= 0.25;
        if (theta[1] > 360.0) theta[1] -= 360.0;
    }
    glutPostRedisplay();
}

int main(int arg, char **argv) {
    cout << "Podaj N: " << endl;
    cin >> n;
    srand(time(NULL));
    glutInit(&arg, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(300, 300);

    glutCreateWindow("Jajko");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutIdleFunc(moveLight);

    glutKeyboardFunc(keys);
    glutMouseFunc(Mouse);
    glutMotionFunc(Motion);
    MyInit();

    glEnable(GL_DEPTH_TEST);


    // Włączenie mechanizmu usuwania powierzchni niewidocznych

    glutMainLoop();
    // Funkcja uruchamia szkielet biblioteki GLUT
    return 0;
    "\n";
}
