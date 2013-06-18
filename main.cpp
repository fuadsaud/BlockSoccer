#include "Includes.h"

#include "Person.h"
#include "Camera.h"
#include "Game.h"

void init();
void display();
void background();
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

    glutIdleFunc(background);

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

    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_WIDTH));

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

void background()
{
    game->getCurrentRound()->background();

}
