#ifdef __linux
    #include <GL/gl.h>
    #include <GL/glut.h>
    #include <GL/glut.h>
#elif __APPLE__
    #include <OpenGL/GL.h>
    #include <OpenGL/GLU.h>
    #include <GLUT/GLUT.h>
#endif
#include "Person.h"
#include "Camera.h"
#include "Scene.h"

void init();
void display();
void keyboard(unsigned char key, int x, int y);


Scene scene;

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("BlockSoccer");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}

void init()
{
    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0);

    glViewport(0, 0, 800, 600);

    scene.init();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1, 0, 1);
    glBegin(GL_QUADS);
        glVertex3f(-10, 0, -10);
        glVertex3f(-10, 0,  10);
        glVertex3f( 10, 0,  10);
        glVertex3f( 10, 0, -10);
    glEnd();

    scene.display();

    glutSwapBuffers();
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    scene.keyboardAction(key,x,y);
    glutPostRedisplay();
}
