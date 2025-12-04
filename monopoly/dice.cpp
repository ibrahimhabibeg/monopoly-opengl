#include "constants.h"
#include "dice.h"
#include <cstdlib>
#include <cmath>
#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <windows.h>
#include <GL/gl.h>
#include <Gl/glut.h>
#endif

static void drawDot(float x, float y)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < DICE_DOT_NO_OF_SEGMENTS; ++i)
    {
        float theta = 2.0f * M_PI * float(i) / (float(DICE_DOT_NO_OF_SEGMENTS));
        glVertex3f(x + DICE_DOT_RADIUS * cos(theta), y + DICE_DOT_RADIUS * sin(theta), 0.0f);
    }
    glEnd();
}

static void drawDotsOnFace(int face, float size)
{

    if (face == 1)
    {
        drawDot(0, 0);
    }
    else if (face == 2)
    {
        drawDot(-.25f * size, -.25f * size);
        drawDot(.25f * size, .25f * size);
    }
    else if (face == 3)
    {
        drawDot(0, 0);
        drawDot(-.25f * size, -.25f * size);
        drawDot(.25f * size, .25f * size);
    }
    else if (face == 4)
    {
        drawDot(-.25f * size, -.25f * size);
        drawDot(.25f * size, .25f * size);
        drawDot(-.25f * size, .25f * size);
        drawDot(.25f * size, -.25f * size);
    }
    else if (face == 5)
    {
        drawDot(0, 0);
        drawDot(-.25f * size, -.25f * size);
        drawDot(.25f * size, .25f * size);
        drawDot(-.25f * size, .25f * size);
        drawDot(.25f * size, -.25f * size);
    }
    else if (face == 6)
    {
        drawDot(-.25f * size, -.3f * size);
        drawDot(.25f * size, .3f * size);
        drawDot(-.25f * size, .3f * size);
        drawDot(.25f * size, -.3f * size);
        drawDot(-.25f * size, 0);
        drawDot(.25f * size, 0);
    }
}

int cube_vertices[6][4][3] = {
    {{-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}},
    {{1, -1, 1}, {1, -1, -1}, {1, 1, -1}, {1, 1, 1}},
    {{-1, 1, -1}, {-1, 1, 1}, {1, 1, 1}, {1, 1, -1}},
    {{-1, -1, 1}, {-1, -1, -1}, {1, -1, -1}, {1, -1, 1}},
    {{-1, -1, -1}, {-1, -1, 1}, {-1, 1, 1}, {-1, 1, -1}},
    {{1, -1, -1}, {-1, -1, -1}, {-1, 1, -1}, {1, 1, -1}},
};

int face_rotations[6][4] = {
    {0, 0, 0, 0},
    {90, 0, 1, 0},
    {90, 1, 0, 0},
    {-90, 1, 0, 0},
    {-90, 0, 1, 0},
    {180, 1, 0, 0},
};

Dice::Dice(float end_x, float end_y, float size, double anim_duration_ms)
    : start_x(end_x), start_y(end_y), end_x(end_x), end_y(end_y), size(size), anim_duration_ms(anim_duration_ms), value(1), rolling(false)
{
    reset();
}

void Dice::drawCube()
{
    glPushMatrix();
    glTranslatef(x + size / 2, y + size / 2, size / 2);

    glRotatef(-face_rotations[value - 1][0],
              face_rotations[value - 1][1],
              face_rotations[value - 1][2],
              face_rotations[value - 1][3]);

    glRotatef(angle_x, 1.0f, 0.0f, 0.0f);
    glRotatef(angle_y, 0.0f, 1.0f, 0.0f);

    for (int i = 0; i < 6; i++)
    {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POLYGON);
        for (int j = 0; j < 4; j++)
        {
            glVertex3f(cube_vertices[i][j][0] * size / 2,
                       cube_vertices[i][j][1] * size / 2,
                       cube_vertices[i][j][2] * size / 2);
        }
        glEnd();
        glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glRotatef(face_rotations[i][0],
                  face_rotations[i][1],
                  face_rotations[i][2],
                  face_rotations[i][3]);
        glTranslatef(0, 0, size / 2 + 0.01);
        drawDotsOnFace(i + 1, size);
        glPopMatrix();
    }

    glPopMatrix();
}

void Dice::roll()
{
    if (rolling)
        return;
    rolling = true;
    roll_start_time = glutGet(GLUT_ELAPSED_TIME);
    x = start_x;
    y = start_y;
    angle_x = 0.0f;
    angle_y = 0.0f;
    value = (rand() % 6) + 1;

    start_x = rand() % (int)(BOARD_WIDTH - size);
    start_y = rand() % (int)(BOARD_HEIGHT - size);
}

void Dice::updateAnimation(double now_ms)
{
    if (!rolling)
        return;
    double elapsed = now_ms - roll_start_time;
    double t = elapsed / anim_duration_ms;
    x = (1.0f - t) * start_x + t * end_x;
    y = (1.0f - t) * start_y + t * end_y;
    angle_x = 360.0f * t * DICE_X_NUMBER_FLIPS;
    angle_y = 360.0f * t * DICE_Y_NUMBER_FLIPS;
    if (elapsed >= anim_duration_ms)
    {
        reset();
    }
}

void Dice::draw()
{
    glEnable(GL_DEPTH_TEST);
    float timeNow = glutGet(GLUT_ELAPSED_TIME);
    if (rolling)
    {
        updateAnimation(timeNow);
    }
    drawCube();
    glDisable(GL_DEPTH_TEST);
}

int Dice::getValue() const { return value; }
bool Dice::isRolling() const { return rolling; }
void Dice::reset()
{
    rolling = false;
    roll_start_time = 0.0;
    x = end_x;
    y = end_y;
    angle_x = 0.0f;
    angle_y = 0.0f;
}
