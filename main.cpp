#include "Includes.h"

#include "Person.h"
#include "Camera.h"
#include "Scene.h"
#include "Game.h"

void init();
void display();
void background(int n);
void keyboard(unsigned char key, int x, int y);
void passiveMotion(int x, int y);

Game * game = new Game();

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("BlockSoccer");

    init();

    background(100);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(passiveMotion);
    glutMainLoop();

    return 0;
}

void init()
{
    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0);

    glViewport(0, 0, 800, 600);

    game->getCurrentRound()->init();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display()
{
    game->getCurrentRound()->display();

    glutSwapBuffers();
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    game->getCurrentRound()->keyboard(key, x, y);
}

void passiveMotion(int x, int y)
{
    game->getCurrentRound()->passiveMotion(x, y);
}

void background(int time)
{
    game->getCurrentRound()->background();

    glutPostRedisplay();

    glutTimerFunc(time, background, time);
}
