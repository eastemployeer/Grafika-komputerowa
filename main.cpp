#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>

typedef float point2[2];
static int levels;
using namespace std;

void Init(){
    //kolor tła
    glClearColor(0.25f,0.25f,0.25f,0.25f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
float getColor(){
    float color=static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
    return color;
}
void fillMiddleSquare(point2 new_down_left,point2 new_down_right,point2 new_up_right,point2 new_up_left){
    glBegin(GL_POLYGON);
    glColor4f(0.25f,0.25f,0.25f,0.0f);
    glVertex2fv(new_down_left);
    glColor4f(0.25f,0.25f,0.25f,0.0f);
    glVertex2fv(new_up_left);
    glColor4f(0.25f,0.25f,0.25f,0.0f);
    glVertex2fv(new_up_right);
    glColor4f(0.25f,0.25f,0.25f,0.0f);
    glVertex2fv(new_down_right);
    glEnd();
}
void ChangeSize(GLsizei horizontal, GLsizei vertical)

{

    GLfloat AspectRatio;
    if(vertical==0)
        vertical = 1;

    glViewport(0, 0, horizontal, vertical);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    AspectRatio = (GLfloat)horizontal/(GLfloat)vertical;
    if(horizontal <= vertical)

        glOrtho(-100.0,100.0,-100.0/AspectRatio,100.0/AspectRatio,1.0,-1.0);

    else

        glOrtho(-100.0*AspectRatio,100.0*AspectRatio,-100.0,100.0,1.0,-1.0);

    glMatrixMode(GL_MODELVIEW);


    glLoadIdentity();

}
void split(point2 down_left,float new_edge,int levels){

    if(levels==1) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {

                float perturbationX= static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(new_edge*0.65)));
                float perturbationY= static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(new_edge*0.65)));

                point2 new_down_left = {down_left[0] + (j * new_edge)+perturbationX, down_left[1] + (i * new_edge)+perturbationY};
                point2 new_down_right = {down_left[0] + (j * new_edge) + new_edge+perturbationX, down_left[1] + (i * new_edge)+perturbationY};
                point2 new_up_left = {down_left[0] + (j * new_edge)+perturbationX, down_left[1] + new_edge + (i * new_edge)+perturbationY};
                point2 new_up_right = {down_left[0] + (j * new_edge) + new_edge+perturbationX, down_left[1] +new_edge+ (i * new_edge)+perturbationY};

                if(j==1 && i==1){

                    fillMiddleSquare(new_down_left,new_down_right,new_up_right,new_up_left);
                }
                else {
                    glBegin(GL_POLYGON);
                    glColor3f(getColor(),getColor(),getColor());
                    glVertex2fv(new_down_left);
                    glColor3f(getColor(),getColor(),getColor());
                    glVertex2fv(new_up_left);
                    glColor3f(getColor(),getColor(),getColor());
                    glVertex2fv(new_up_right);
                    glColor3f(getColor(),getColor(),getColor());
                    glVertex2fv(new_down_right);
                    glEnd();

                }

            }

        }
    }
    else if(levels>1){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){

                point2 new_down_left = {down_left[0] + (j * new_edge), down_left[1] + (i * new_edge)};
                point2 new_down_right = {down_left[0] + (j * new_edge) + new_edge, down_left[1] + (i * new_edge)};
                point2 new_up_left = {down_left[0] + (j * new_edge), down_left[1] + new_edge + (i * new_edge)};
                point2 new_up_right = {down_left[0] + (j * new_edge) + new_edge, down_left[1] +new_edge+ (i * new_edge)};
                if(j==1 && i==1){
                    fillMiddleSquare(new_down_left,new_down_right,new_up_right,new_up_left);
                }
                else {
                    float smaller_edge=(new_down_right[0]-new_down_left[0])/3;
                    split(new_down_left,smaller_edge,levels-1);
                }

            }
        }


    }

}


void render(){
    glClear(GL_COLOR_BUFFER_BIT);
    point2 left = {-85,-85};
    point2 right = {85,-85};
    float new_edge = (right[0] - left[0])/3;
    split(left,new_edge,levels);
    glFlush();
}

int main(int arg, char **argv){

    cout<<"Ile poziomów?"<<endl;
    cin>>levels;
    srand(time(NULL));

    glutInit(&arg,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Dywan Sierpinskiego");
    glutDisplayFunc(render);
    glutReshapeFunc(ChangeSize);
    Init();
    glutMainLoop();
}















