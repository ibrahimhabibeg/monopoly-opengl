#include <tuple>
#include <vector>
using std::vector;

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <windows.h>
#include <GL/gl.h>
#include <Gl/glut.h>
#endif


#include "constants.h"
#include "game_manager.h"

GameManager gameManager;

void draw(void)
{
//    double now_ms = glutGet(GLUT_ELAPSED_TIME);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gameManager.draw();
    glFlush();
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'r' || key == 'R')
    {
        gameManager.rollDice();
    }
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0.0, BOARD_WIDTH, 0.0, BOARD_HEIGHT, -40.0, 40.0);
}
int main(int argc, char **argv)
{
//    srand(42);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Monopoly Board");
    init();
    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
