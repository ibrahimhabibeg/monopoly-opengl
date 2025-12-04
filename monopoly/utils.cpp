#include "utils.h"
#include "constants.h"
#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <windows.h>
#include <GL/gl.h>
#include <Gl/glut.h>
#endif

// There are NUM_CELLS cells on the board
// The cells are numbered from 0 to NUM_CELLS
// Go (bottom right) is cell 0 and numbering moves clockwise
// The last cell (NUM_CELLS-1) is the huge square in the middle of the board
std::tuple<float, float> get_cell_bottom_left(int cell_num)
{
    float x;
    float y;

    if (cell_num < 0 || cell_num >= NUM_CELLS)
    {
        x = -1;
        y = -1;
    }
    else if (cell_num == goCell)
    {
        x = goCellX;
        y = goCellY;
    }
    else if (cell_num < jailCell)
    {
        x = goCellX - BORDER_WIDTH - HR_CELL_WIDTH - ((cell_num - (goCell + 1)) * (HR_CELL_WIDTH + BORDER_WIDTH));
        y = goCellY;
    }
    else if (cell_num == jailCell)
    {
        x = jailCellX;
        y = jailCellY;
    }
    else if (cell_num < freeParkingCell)
    {
        x = jailCellX;
        y = jailCellY + BIG_CELL_HEIGHT + BORDER_WIDTH + ((cell_num - (jailCell + 1)) * (VR_CELL_HEIGHT + BORDER_WIDTH));
    }
    else if (cell_num == freeParkingCell)
    {
        x = freeParkingCellX;
        y = freeParkingCellY;
    }
    else if (cell_num < goToJailCell)
    {
        x = freeParkingCellX + BIG_CELL_WIDTH + BORDER_WIDTH + ((cell_num - (freeParkingCell + 1)) * (HR_CELL_WIDTH + BORDER_WIDTH));
        y = freeParkingCellY;
    }
    else if (cell_num == goToJailCell)
    {
        x = goToJailCellX;
        y = goToJailCellY;
    }
    else if (cell_num < NUM_CELLS - 1)
    {
        x = goToJailCellX;
        y = goToJailCellY - BORDER_WIDTH - VR_CELL_HEIGHT - ((cell_num - (goToJailCell + 1)) * (VR_CELL_HEIGHT + BORDER_WIDTH));
    }
    else
    {
        x = BORDER_WIDTH + BIG_CELL_WIDTH + BORDER_WIDTH;
        y = BORDER_WIDTH + BIG_CELL_HEIGHT + BORDER_WIDTH;
    }
    return std::make_tuple(x, y);
}

std::tuple<float, float> get_cell_center(int cell_num)
{
    float x, y;
    std::tie(x, y) = get_cell_bottom_left(cell_num);
    if (cell_num == NUM_CELLS - 1)
    {
        x += CENTER_BOX_WIDTH / 2.0f;
        y += CENTER_BOX_HEIGHT / 2.0f;
    }
    else if (cell_num == goCell || cell_num == jailCell || cell_num == freeParkingCell || cell_num == goToJailCell)
    {
        x += BIG_CELL_WIDTH / 2.0f;
        y += BIG_CELL_HEIGHT / 2.0f;
    }
    else if (cell_num < jailCell || (cell_num > freeParkingCell && cell_num < goToJailCell))
    {
        x += HR_CELL_WIDTH / 2.0f;
        y += HR_CELL_HEIGHT / 2.0f;
    }
    else
    {
        x += VR_CELL_WIDTH / 2.0f;
        y += VR_CELL_HEIGHT / 2.0f;
    }
    return std::make_tuple(x, y);
}

std::tuple<float, float> get_colored_bar_bottom_left(int cell_num)
{
    if (cell_num < 0 || cell_num >= NUM_CELLS || cell_num == goCell || cell_num == jailCell || cell_num == freeParkingCell || cell_num == goToJailCell || cell_num == NUM_CELLS - 1)
    {
        return std::make_tuple(-1.0, -1.0);
    }
    float x, y;
    auto t = get_cell_bottom_left(cell_num);
    x = std::get<0>(t);
    y = std::get<1>(t);
    if (cell_num < jailCell)
    {
        return std::make_tuple(x, y + HR_CELL_HEIGHT - HR_CELL_COLORED_BAR_HEIGHT);
    }
    else if (cell_num < freeParkingCell)
    {
        return std::make_tuple(x + VR_CELL_WIDTH - VR_CELL_COLORED_BAR_WIDTH, y);
    }
    else if (cell_num < goToJailCell)
    {
        return std::make_tuple(x, y);
    }
    else
    {
        return std::make_tuple(x, y);
    }
}

void draw_rectangle(float x, float y, float width, float height)
{
    glBegin(GL_POLYGON);
    glVertex3f(x, y, 0.0);
    glVertex3f(x + width, y, 0.0);
    glVertex3f(x + width, y + height, 0.0);
    glVertex3f(x, y + height, 0.0);
    glEnd();
}