#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <vector>
#include <math.h>

using namespace std;
typedef float point3[3];
typedef float point2[2];
int type=3;
int orientation=1;
static GLfloat theta[] = {0.0, 0.0,0.0};
int n; //ilosc punktów
static const GLfloat min_zoom_value = 1.0;
static const GLfloat max_zoom_value = 20.0;


static GLfloat viewer[]= {0.0, 0.0, 10.0};

static GLfloat epsilon = 0.0;   // kąt obrotu obiektu w y
static GLfloat epsilon1 = 0.0;   // kąt obrotu obiektu w x
static GLfloat pix2angleY;     // przelicznik pikseli na stopnie Y
static GLfloat pix2angleX;  // przelicznik pikseli na stopnie X

static GLint status = 0;       // stan klawiszy myszy
// 0 - nic nie naciśnięto
// 1 - LPM
//2 - Scroll up
//3 - Scroll down

static int x_pos_old=0;       // poprzednia pozycja kursora myszy
static int y_pos_old=0;

static int delta_x = 0;        // różnica pomiędzy pozycją bieżącą
static int delta_y = 0;
int reset=0; //1 - wcisniety zostal klawisz r
void RenderScene(void);


void Axes(void)
{

    point3  x_min = {-5.0, 0.0, 0.0};
    point3  x_max = { 5.0, 0.0, 0.0};
    // pocz?tek i koniec obrazu osi x

    point3  y_min = {0.0, -5.0, 0.0};
    point3  y_max = {0.0,  5.0, 0.0};
    // pocz?tek i koniec obrazu osi y

    point3  z_min = {0.0, 0.0, -5.0};
    point3  z_max = {0.0, 0.0,  5.0};
    //  pocz?tek i koniec obrazu osi y

    glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
    glBegin(GL_LINES); // rysowanie osi x

    glVertex3fv(x_min);
    glVertex3fv(x_max);

    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
    glBegin(GL_LINES);  // rysowanie osi y

    glVertex3fv(y_min);
    glVertex3fv(y_max);

    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
    glBegin(GL_LINES); // rysowanie osi z

    glVertex3fv(z_min);
    glVertex3fv(z_max);

    glEnd();

}
void Mouse(int btn, int state, int x, int y)
{
    if(btn==3 && state == GLUT_DOWN){
        status=2;
        RenderScene();
    }
    if(btn==4 && state == GLUT_DOWN){
        status=3;
        RenderScene();
    }

  if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        x_pos_old=x;
        y_pos_old=y;
        status = 1;          // wcięnięty został lewy klawisz myszy
    }
  else
      status = 0;          // nie został wcięnięty żaden klawisz
}
void Motion( GLsizei x, GLsizei y )
{

    delta_x=x-x_pos_old;     // obliczenie różnicy położenia kursora myszy
    delta_y=y-y_pos_old;

    x_pos_old=x;            // podstawienie bieżącego położenia jako poprzednie
    y_pos_old=y;

    glutPostRedisplay();     // przerysowanie obrazu sceny
}

void Egg(int n){
//vector<vector<point2>>table(n,vector<point2>(n));
//vector<vector<point3>>table3D(n,vector<point3>(n));
point3 table3D[n][n];
point2 table[n][n];


for(int i=0;i<n;i++){

    for(int j=0;j<n;j++){
        //wypełnianie tablic z u i v
        table[i][j][0]=(float)i/(n-1);
        table[i][j][1]=(float)j/(n-1);

        //przeliczanie na 3D
        table3D[i][j][0]=(float)((-90*pow(table[i][j][0], 5) + 225*pow(table[i][j][0], 4) - 270*pow(table[i][j][0], 3) + 180*pow(table[i][j][0],2) - 45*table[i][j][0])*cos(M_PI*table[i][j][1]));
        table3D[i][j][1]=(float)(160*pow(table[i][j][0], 4) - 320*pow(table[i][j][0], 3) + 160*pow(table[i][j][0], 2));
        table3D[i][j][2] = (float)((-90*pow(table[i][j][0], 5) + 225*pow(table[i][j][0], 4) - 270*pow(table[i][j][0], 3) + 180*pow(table[i][j][0],2) - 45*table[i][j][0])*sin(M_PI*table[i][j][1]));
    }
}
if(type==1) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            glBegin(GL_POINTS);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3fv(table3D[i][j]);
            glEnd();
        }
    }
}
else if(type==2){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1;j++){
            glBegin(GL_LINES);
            glColor3f(0.0f,1.0f,0.0f);
            //linia pionowa
            glVertex3fv(table3D[i][j]);
            glVertex3fv(table3D[i+1][j]);
            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.0f,1.0f,0.0f);
            //linia pozioma
            glVertex3fv(table3D[i][j]);
            glVertex3fv(table3D[i][j+1]);
            glEnd();

            glBegin(GL_LINES);
            glColor3f(0.0f,1.0f,0.0f);
            //linia skośna
            glVertex3fv(table3D[i][j+1]);
            glVertex3fv(table3D[i+1][j]);
            glEnd();
        }
    }
}
else if(type==3){
   point3 colors[n][n];

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            colors[i][j][0]=static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
            colors[i][j][1]=static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
            colors[i][j][2]=static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
        }
    }
 for(int i=0;i<n-1;i++){
     for(int j=0;j<n-1;j++){
         glBegin(GL_TRIANGLES);
         glColor3fv(colors[i][j]);
         glVertex3fv(table3D[i][j]);
         glColor3fv(colors[i][j+1]);
         glVertex3fv(table3D[i][j+1]);
         glColor3fv(colors[i+1][j]);
         glVertex3fv(table3D[i+1][j]);
         glEnd();

         glBegin(GL_TRIANGLES);
         glColor3fv(colors[i+1][j]);
         glVertex3fv(table3D[i+1][j]);
         glColor3fv(colors[i+1][j+1]);
         glVertex3fv(table3D[i+1][j+1]);
         glColor3fv(colors[i][j+1]);
         glVertex3fv(table3D[i][j+1]);
         glEnd();
     }
 }
}
}
void checkMovementAndZoom(){
    if(status==1)
    {
        epsilon += delta_x*pix2angleX;    // modyfikacja kąta obrotu o kat proporcjonalny
        epsilon1 +=delta_y*pix2angleY;

    }
    if(status == 2)
    {
        viewer[2] += 1.0;
        if (viewer[2] > max_zoom_value)
            viewer[2] = max_zoom_value;

        if(viewer[2] < min_zoom_value)
            viewer[2] = min_zoom_value;

    }
   if(status == 3)
    {
        viewer[2] -=1.0;
        if (viewer[2] > max_zoom_value)
            viewer[2] = max_zoom_value;

        if(viewer[2] < min_zoom_value)
            viewer[2] = min_zoom_value;
    }

}
void checkReset(){
    //przywracanie wartosci domyslnych wszystkim zmiennym
    if(reset==1){
        viewer[2]=10.0;
        epsilon=0.0;
        epsilon1=0.0;
        theta[0]=0.0;
        theta[1]=0.0;
        reset=0;
    }
}
void RenderScene(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Czyszczenie okna aktualnym kolorem czyszczącym

    glLoadIdentity();
    // Czyszczenie macierzy bieżącej

    gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    checkReset();
    checkMovementAndZoom();

    glTranslated(0,-5,0);
    gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    glRotatef(epsilon, 0.0, 1.0, 0.0);  //obrót obiektu o nowy kąt
    glRotatef(epsilon1,1.0,0.0,0.0);


    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[0], 1.0, 0.0, 0.0);

    Axes();
    Egg(n);

    glFlush();
    // Przekazanie poleceń rysujących do wykonania

    glutSwapBuffers();
}


void keys(unsigned char key,int x,int y){
    if(key == 'p') type=1;
    if(key == 'l') type=2;
    if(key == 't') type=3;
    if(key == 'q') orientation=1; // obrót wokol x - po osi poziomej
    if(key =='w') orientation=2; //obrót wokól y - po osi pionowej
    if(key=='r') reset=1;
    RenderScene();
}

void MyInit(void)
{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

    pix2angleX = 360/(float)horizontal;  // przeliczenie pikseli na stopnie
    pix2angleY = 360/(float)vertical;  // przeliczenie pikseli na stopnie

    glMatrixMode(GL_PROJECTION);
    // Przełączenie macierzy bieżącej na macierz projekcji

    glLoadIdentity();
    // Czyszcznie macierzy bieżącej

    gluPerspective(70, 1.0, 1.0, 50.0);
    // Ustawienie parametrów dla rzutu perspektywicznego


    if(horizontal <= vertical)
        glViewport(0, (vertical-horizontal)/2, horizontal, horizontal);

    else
        glViewport((horizontal-vertical)/2, 0, vertical, vertical);
    // Ustawienie wielkości okna okna widoku (viewport) w zależności
    // relacji pomiędzy wysokością i szerokością okna

    glMatrixMode(GL_MODELVIEW);
    // Przełączenie macierzy bieżącej na macierz widoku modelu

    glLoadIdentity();
    // Czyszczenie macierzy bieżącej

}

void spinEgg() {
    if (status != 1) {
        //kliknięcie "q" - obracanie się wokół x
        if (orientation == 1) {
            theta[0] -= 0.25;
            if (theta[0] > 360.0) theta[0] -= 360.0;
        }
        //kliknięcie "w" - obracanie się wokol y
        if (orientation == 2) {
            theta[1] -= 0.25;
            if (theta[1] > 360.0) theta[1] -= 360.0;
        }
        glutPostRedisplay();
    }
}

int main(int arg,char **argv)
{
    cout<<"Podaj N: "<<endl;
    cin>>n;
    srand(time(NULL));
    glutInit(&arg,argv);




    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);

    glutInitWindowSize(300, 300);

    glutCreateWindow("Jajko");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutIdleFunc(spinEgg);

    glutKeyboardFunc(keys);
    glutMouseFunc(Mouse);
    glutMotionFunc(Motion);

    MyInit();

    glEnable(GL_DEPTH_TEST);


    // Włączenie mechanizmu usuwania powierzchni niewidocznych

    glutMainLoop();
    // Funkcja uruchamia szkielet biblioteki GLUT
return 0;
}