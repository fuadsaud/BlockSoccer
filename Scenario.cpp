#include "Scenario.h"

Scenario::Scenario(float w) {
    width = w;
}

void Scenario::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderGround();
    renderLines();
    renderGoal();
}

float Scenario::getWidth() {
    return width;
}

float Scenario::getLenght() {
    return width / 2;
}

void Scenario::renderGround() {
    glColor3f(0.14, 0.34, 0.02);
    glBegin(GL_QUADS);
        glVertex3f(-width / 2, 0, -width / 4);
        glVertex3f(-width / 2, 0,  width / 4);
        glVertex3f( width / 2, 0,  width / 4);
        glVertex3f( width / 2, 0, -width / 4);

    glEnd();
}

void Scenario::renderLines() {
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(2);

    glColor3f(1, 1, 1);

    glBegin(GL_LINE_LOOP);
        glVertex3f(-width / 2 + 1.5, 0.01, -width / 4 + 1.5);
        glVertex3f( width / 2 - 1.5, 0.01, -width / 4 + 1.5);
        glVertex3f( width / 2 - 1.5, 0.01,  width / 4 - 1.5);
        glVertex3f(-width / 2 + 1.5, 0.01,  width / 4 - 1.5);
        glVertex3f(-width / 2 + 1.5, 0.01, -width / 4 + 1.5);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(0, 0.01, -width / 4 + 1.5);
        glVertex3f(0, 0.01,  width / 4 - 1.5);
    glEnd();

    glBegin(GL_LINE_LOOP);
        for (unsigned int i = 0; i < 360; i++) {
            float angle = i * M_PI / 180;
            glVertex3f(cos(angle) * 4, 0.01, sin(angle) * 4);
        }
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(-width / 2 + 1.5, 0.01, -13);
        glVertex3f(-width / 2 + 15,  0.01, -13);
        glVertex3f(-width / 2 + 15,  0.01,  13);
        glVertex3f(-width / 2 + 1.5, 0.01,  13);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(-width / 2 + 1.5, 0.01, -7);
        glVertex3f(-width / 2 + 8,   0.01, -7);
        glVertex3f(-width / 2 + 8,   0.01,  7);
        glVertex3f(-width / 2 + 1.5, 0.01,  7);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(width / 2 - 1.5, 0.01, -7);
        glVertex3f(width / 2 - 8,   0.01, -7);
        glVertex3f(width / 2 - 8,   0.01,  7);
        glVertex3f(width / 2 -1.5,  0.01,  7);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(width / 2 - 1.5, 0.01, -13);
        glVertex3f(width / 2 - 15,  0.01, -13);
        glVertex3f(width / 2 - 15,  0.01,  13);
        glVertex3f(width / 2 - 1.5, 0.01,  13);
    glEnd();

    glBegin(GL_LINE_LOOP);
        for (unsigned int i = 90; i < 270; i++) {
            float angle = i * M_PI / 180;
            glVertex3f(cos(angle) * 2 + width / 2 - 15, 0.01, sin(angle) * 4);
        }
    glEnd();

    glBegin(GL_LINE_LOOP);
        for (unsigned int i = 270; i < 450; i++) {
            float angle = i * M_PI / 180;
            glVertex3f(cos(angle) * 2 - width / 2 + 15, 0.01, sin(angle) * 4);
        }
    glEnd();
}

void Scenario::renderGoal() {
    glPushMatrix();
        glTranslatef(width / 2 - 1.5, 0, -5);
        glRotatef(-90, 1, 0, 0);
        GLUquadricObj * quadObj = gluNewQuadric();
        gluCylinder(quadObj, 0.1, 0.1, 3.5, 10, 10);

        glTranslatef(0, -10, 0);
        gluCylinder(quadObj, 0.1, 0.1, 3.5, 10, 10);

        glTranslatef(0, 0, 3.4);
        glRotatef(-90, 1, 0, 0);
        gluCylinder(quadObj, 0.1, 0.1, 10, 10, 10);
    glPopMatrix();
}
