#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include <math.h>

using namespace std;
typedef float point3[3];
typedef float point2[2];
int type=3;
int orientation=1;
static GLfloat theta[] = {0.0, 0.0,0.0};
int n;


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



void RenderScene(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Czyszczenie okna aktualnym kolorem czyszczącym

    glLoadIdentity();
    // Czyszczenie macierzy bieżącej



   glRotatef(theta[0], 1.0, 0.0, 0.0);

   glRotatef(theta[1], 0.0, 1.0, 0.0);

    glTranslated(0,-5,0);

    Egg(n);


    glFlush();
    // Przekazanie poleceń rysujących do wykonania



    glutSwapBuffers();
    //

}


void keys(unsigned char key,int x,int y){
    if(key == 'p') type=1;
    if(key == 'l') type=2;
    if(key == 't') type=3;
    if(key == 'q') orientation=1; // obrót wokol x - po osi poziomej
    if(key =='w') orientation=2; //obrót wokól y - po osi pionowej
    RenderScene();
}

void MyInit(void)
{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}


void ChangeSize(GLsizei horizontal, GLsizei vertical )
{

    GLfloat AspectRatio;
    // Deklaracja zmiennej AspectRatio  określającej proporcję
    // wymiarów okna

    if(vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0

        vertical = 1;

    glViewport(0, 0, horizontal, vertical);
    // Ustawienie wielkościokna okna widoku (viewport)
    // W tym przypadku od (0,0) do (horizontal, vertical)

    glMatrixMode(GL_PROJECTION);
    // Przełączenie macierzy bieżącej na macierz projekcji

    glLoadIdentity();
    // Czyszcznie macierzy bieżącej

    AspectRatio = (GLfloat)horizontal/(GLfloat)vertical;
    // Wyznaczenie współczynnika  proporcji okna
    // Gdy okno nie jest kwadratem wymagane jest określenie tak zwanej
    // przestrzeni ograniczającej pozwalającej zachować właściwe
    // proporcje rysowanego obiektu.
    // Do okreslenia przestrzeni ograniczjącej służy funkcja
    // glOrtho(...)

    if(horizontal <= vertical)

        glOrtho(-7.5,7.5,-7.5/AspectRatio,7.5/AspectRatio,10.0, -10.0);

    else

        glOrtho(-7.5*AspectRatio,7.5*AspectRatio,-7.5,7.5,10.0,-10.0);

    glMatrixMode(GL_MODELVIEW);
    // Przełączenie macierzy bieżącej na macierz widoku modelu

    glLoadIdentity();
    // Czyszcenie macierzy bieżącej

}


void spinEgg()
{
    //kliknięcie "q" - obracanie się wokół x
    if(orientation==1) {
        theta[0] -= 0.25;
        if (theta[0] > 360.0) theta[0] -= 360.0;
    }
    //kliknięcie "w" - obracanie się wokol y
    if(orientation==2) {
        theta[1] -= 0.25;
        if (theta[1] > 360.0) theta[1] -= 360.0;
    }
    glutPostRedisplay();
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
    MyInit();

    glEnable(GL_DEPTH_TEST);


    // Włączenie mechanizmu usuwania powierzchni niewidocznych

    glutMainLoop();
    // Funkcja uruchamia szkielet biblioteki GLUT
return 0;
}