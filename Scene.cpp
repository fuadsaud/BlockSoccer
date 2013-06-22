#include "Scene.h"

Scene::Scene(Game *  g) {
    game = g;
    scenario = new Scenario(100);
    player = new Person(PLAYER_MOVEMENT_AMOUNT);
    camera = new Camera(player);
    ball = new Ball(player);

    opponents.push_back(
        Person(new Point(10, 0, 0), PLAYER_MOVEMENT_AMOUNT * 0.1)
    );
    opponents.push_back(
        Person(new Point(10, 0, -10), PLAYER_MOVEMENT_AMOUNT * 0.1)
    );
    opponents.push_back(
        Person(new Point(10, 0, 10), PLAYER_MOVEMENT_AMOUNT * 0.1)
    );
    opponents.push_back(
        Person(new Point(11, 0, 0), PLAYER_MOVEMENT_AMOUNT * 0.1)
    );

    goalKepper = new Person(new Point(48, 0, 0), PLAYER_MOVEMENT_AMOUNT * 0.1);

    init(camera);
}

void Scene::init(Camera * camera) {
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glutSetCursor(GLUT_CURSOR_NONE);

    camera->syncWithPerson();
}

void Scene::display() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // drawScenario();
    scenario->render();
    goalKepper->render();

    for (unsigned int i = 0; i < opponents.size(); i++) {
        opponents[i].render();
    }

    ball->render();
    player->render();
}

void Scene::background() {
    ballBehavior();
    adversaryTeamBehavior();
    collisionMonitor();
    glutPostRedisplay();
}

void Scene::keyboard(const char key, int x, int y) {
    switch (key) {
        case 'w':
        case 'W':
            player->move(Object::FRONT);
            break;
        case 's':
        case 'S':
            player->move(Object::BACK);
            break;
        case 'a':
        case 'A':
            player->move(Object::LEFT);
            break;
        case 'd':
        case 'D':
            player->move(Object::RIGHT);
            break;
        case ' ':
            ball->detach();
            break;
        case 'q':
        case 'Q':
            exit(0);
    }

    camera->syncWithPerson();
}

void Scene::passiveMotion(int x, int y) {
    float height = 800, width = 600;

    if (x != width / 2) {
        float distance = (x - width / 2) / 10;

        player->rotate(distance);
        camera->syncWithPerson();

        glutWarpPointer(width / 2, height / 2);
    }
}

void Scene::adversaryTeamBehavior() {
    Point * playerPosition = player->getPosition();

    srand(time(0));

    for (unsigned int i = 0; i < opponents.size(); i++) {
        opponents[i].lookAt(playerPosition);
        opponents[i].move(Person::FRONT);
    }

    goalKepper->lookAt(playerPosition);

    Point * kp = goalKepper->getPosition();
    float move = playerPosition->z;

    if (move > 5) move = 5;
    else if (move < -5) move = -5;

    kp->z = move;
}

void Scene::ballBehavior() {
    if (!ball->isAttached()) ball->go();
}

void Scene::collisionMonitor() {
    Point * ballPosition = ball->getPosition();

    std::vector<Person> allOpponents(opponents);
    allOpponents.push_back(*goalKepper);

    if (!player->isInside(scenario)) end(false); // GAME OVER!

    // This checks whether the ball is outside the field.
    if (!ball->isInside(scenario)) {
        if (ballPosition->x > 50 && // Was it on the goal side of the field?
            ballPosition->z > -5 && // Was it a goal?
            ballPosition->z < 5) {
            end(true);
        } else {
            end(false);
        }
    }

    for (unsigned int i = 0; i < allOpponents.size(); i++) {
        Object * opponent = &((Object) allOpponents[i]);

        if (player->collidingWith(opponent) ||
            ball->collidingWith(opponent)) {
            end(false);
        }

        for (unsigned int j = i + 1; j < opponents.size(); j++) {
            if (opponents[j].collidingWith(opponent)) {
                opponents[j].move(Object::FRONT);
                opponents[i].move(Object::BACK);
            }
        }
    }
}

void Scene::end(bool success) {
    // TODO show results on the window
    game->endRound(success);
}
